#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Config.hpp"
#include "wxgit/git/Diff.hpp"
#include "wxgit/git/Index.hpp"
#include "wxgit/git/Path.hpp"
#include "wxgit/git/Reference.hpp"
#include "wxgit/git/Remote.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/git/Signature.hpp"
#include "wxgit/git/Status.hpp"
#include "wxgit/git/Tree.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     */
    Repository::Repository(git_repository* repository)
	: repository_(repository)
    {
        git_config* config;
        if(git_repository_config(&config, repository_) == GIT_OK)
        {
            config_ = std::make_shared<Config>(config);
        }
    }

    /**
     * @brief デストラクタ
     */
    Repository::~Repository()
    {
        git_repository_free(repository_);
    }

    /**
     * @brief ファイルパスを取得する
     * @return ファイルパス
     */
    Path Repository::getPath() const
    {
        return Path(git_repository_path(repository_)).getDir();
    }

    /**
     * @brief 作業ディレクトリを取得する
     * @return 作業ディレクトリ
     */
    Path Repository::getWorkDir() const
    {
        return Path(git_repository_workdir(repository_)).getDir();
    }

    /**
     * @brief 名前を取得する
     * @return 名前
     */
    wxString Repository::getName() const
    {
        return getWorkDir().toString(wxPATH_UNIX);
    }

    /**
     * @brief ネームスペースを取得する
     * @return ネームスペース
     */
    wxString Repository::getNamespace() const
    {
        return wxString::FromUTF8(git_repository_get_namespace(repository_));
    }

    /**
     * @brief
     */
    ReferencePtr Repository::takeHead()
    {
        git_reference* reference;
        if(git_repository_head(&reference, repository_) != GIT_OK)
        {
            return nullptr;
        }
        return std::make_shared<Reference>(shared_from_this(), reference);
    }

    /**
     * @brief ローカルブランチのリストを取得する
     * @return ローカルブランチのリスト
     */
    std::vector<ReferencePtr> Repository::takeLocalBranches()
    {
        return takeBranches(GIT_BRANCH_LOCAL);
    }

    /**
     * @brief リモートブランチのリストを取得する
     * @return リモートブランチのリスト
     */
    std::vector<ReferencePtr> Repository::takeRemoteBranches()
    {
        return takeBranches(GIT_BRANCH_REMOTE);
    }

    /**
     */
    const std::vector<CommitPtr>& Repository::getCommits(bool update)
    {
	if(update || commits_.empty())
	{
            git_revwalk* walk = nullptr;
            if(git_revwalk_new(&walk, repository_) == GIT_OK)
            {
                if(git_revwalk_push_head(walk) == GIT_OK)
                {
                    auto self = shared_from_this();
                    git_oid oid;
                    while(git_revwalk_next(&oid, walk) == GIT_OK)
                    {
                        if(auto commit = lookupCommit(oid))
                        {
                            commits_.push_back(commit);
                        }
                    }
                }
                git_revwalk_free(walk);
            }
	}
	return commits_;
    }

    /**
     * @brief ステータスを取得する
     * @return ステータス
     */
    StatusPtr Repository::takeStatus()
    {
        git_status_options options;
        if(git_status_options_init(&options, GIT_STATUS_OPTIONS_VERSION) == GIT_OK)
        {
            options.flags = GIT_STATUS_OPT_DEFAULTS;
            options.rename_threshold = 50;
            git_status_list* list;
            if(git_status_list_new(&list, repository_, &options) == GIT_OK)
            {
                return std::make_shared<Status>(shared_from_this(), list);
            }
        }
        return nullptr;
    }

    /**
     * @brief リモートを取得する
     * @return リモート
     */
    std::vector<RemotePtr> Repository::takeRemotes()
    {
        std::vector<RemotePtr> result;
        auto repository = shared_from_this();
        git_strarray names;
        if(git_remote_list(&names, repository_) == GIT_OK)
        {
            for(int i = 0; i < names.count; ++i)
            {
                git_remote* remote;
                if(git_remote_lookup(&remote, repository_, names.strings[i]) == GIT_OK)
                {
                    result.push_back(std::make_shared<Remote>(repository, remote));
                }
            }
            git_strarray_free(&names);
        }
        return result;
    }

    /**
     * @brief シグネチャを取得する
     * @return シグネチャ
     */
    SignaturePtr Repository::takeSignature() const
    {
        git_signature* signature;
        if(git_signature_default(&signature, repository_) == GIT_OK)
        {
            return std::make_shared<Signature>(signature);
        }
        return nullptr;
    }

    /**
     * @brief 作業ディレクトリとの差分を作成する
     * @return 差分
     */
    DiffPtr Repository::createDiff()
    {
        DiffPtr result;
        git_reference* reference;
        if(git_repository_head(&reference, repository_) == GIT_OK)
        {
            git_tree* tree;
            if(git_reference_peel(reinterpret_cast<git_object**>(&tree), 
                                  reference, 
                                  GIT_OBJECT_TREE) == GIT_OK)
            {
                git_diff_options options;
                git_diff_options_init(&options, GIT_DIFF_OPTIONS_VERSION);
                options.flags = 
                    GIT_DIFF_NORMAL;
                /*
                  |
                    GIT_DIFF_INCLUDE_UNTRACKED |
                    GIT_DIFF_SHOW_UNTRACKED_CONTENT;
                */
                git_diff* diff;
                if(git_diff_tree_to_workdir(&diff, repository_, tree, &options) == GIT_OK)
                {
                    result = std::make_shared<Diff>(shared_from_this(), diff);
                }
                git_tree_free(tree);
            }
            git_reference_free(reference);
        }
        return result;
    }

    /**
     * @brief インデックスを取得する
     * @return インデックス
     */
    IndexPtr Repository::takeIndex()
    {
        if(!index_)
        {
            git_index* index;
            if(git_repository_index(&index, repository_) == GIT_OK)
            {
                index_ = std::make_shared<Index>(shared_from_this(), index);
            }
        }
        return index_;
    }

    /**
     * @brief コミット
     * @param[in] message メッセージ
     */
    CommitPtr Repository::commit(const wxString& message)
    {
        auto head = takeHead();
        auto parent = head ? head->takeCommit()->getCommit() : nullptr;
        auto index = takeIndex();
        auto tree = index->writeTree();
        auto signature = takeSignature();
        git_oid oid;
        auto result = git_commit_create_v(&oid, 
                                          repository_, 
                                          "HEAD", 
                                          signature->getSignature(), 
                                          signature->getSignature(), 
                                          nullptr, 
                                          message.ToUTF8(), 
                                          tree ? tree->getTree() : nullptr, 
                                          parent ? 1 : 0, 
                                          parent);
        if(result == GIT_OK)
        {
            return lookupCommit(oid);
        }
        return nullptr;
    }

    /**
     * @brief ツリーを取得する
     * @param[in] oid ツリーのオブジェクトID
     * @return ツリー
     */
    TreePtr Repository::lookupTree(const git_oid& oid) const
    {
        git_tree* tree;
        if(git_tree_lookup(&tree, repository_, &oid) == GIT_OK)
        {
            return std::make_shared<Tree>(tree);
        }
        return nullptr;
    }

    /**
     * @brief リポジトリを開く
     * @param[in] dir ディレクトリ
     * @return 開いたリポジトリ
     */
    RepositoryPtr Repository::Open(const Path& dir)
    {
	git_repository* repository;
        if(git_repository_open(&repository, dir) != GIT_OK)
        {
            return nullptr;
        }
        return std::make_shared<Repository>(repository);
    }

    /**
     * @brief リポジトリを初期化する
     * @param[in] dir ディレクトリ
     * @return 初期化したリポジトリ
     */
    RepositoryPtr Repository::Init(const Path& dir, bool isBare)
    {
        git_repository* repository;
        if(git_repository_init(&repository, dir, isBare) != GIT_OK)
        {
            return nullptr;
        }
        return std::make_shared<Repository>(repository);
    }

    /**
     */
    CommitPtr Repository::lookupCommit(const git_oid& oid)
    {
        git_commit* commit;
        if(git_commit_lookup(&commit, repository_, &oid) == GIT_OK)
        {
            return std::make_shared<Commit>(shared_from_this(), commit);
        }
        return nullptr;
    }

    /**
     */
    std::vector<ReferencePtr> Repository::takeBranches(git_branch_t type)
    {
	std::vector<ReferencePtr> branches;
        git_branch_iterator* iterator;
        if(git_branch_iterator_new(&iterator, repository_, type) == GIT_OK)
        {
            auto repository = shared_from_this();
            git_reference* reference;
            while(git_branch_next(&reference, &type, iterator) == GIT_OK)
            {
                branches.push_back(std::make_shared<Reference>(repository, reference));
            }
            git_branch_iterator_free(iterator);
        }
	return branches;
    }
}
