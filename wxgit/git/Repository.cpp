#include "wxgit/git/Branch.hpp"
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Config.hpp"
#include "wxgit/git/Diff.hpp"
#include "wxgit/git/Index.hpp"
#include "wxgit/git/Remote.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/git/Signature.hpp"
#include "wxgit/git/Status.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] dir ディレクトリ
     */
    Repository::Repository(const wxFileName& dir)
	: dir_(dir), 
	  repository_(nullptr), 
	  error_(GIT_ERROR)
    {
	error_ = git_repository_open(&repository_, dir.GetFullPath().c_str());
	if(isOk())
	{
	    git_config* config;
	    if(git_repository_config(&config, repository_) == GIT_OK)
	    {
		config_ = std::make_shared<Config>(config);
	    }
	}
    }

    /**
     * @brief デストラクタ
     */
    Repository::~Repository()
    {
	if(repository_)
	{
	    git_repository_free(repository_);
	}
    }

    /**
     */
    bool Repository::isOk() const
    {
	return error_ == GIT_OK;
    }

    /**
     */
    std::vector<BranchPtr> Repository::getBranches(git_branch_t type)
    {
	std::vector<BranchPtr> branches;
	if(isOk())
	{
	    git_branch_iterator* iterator = nullptr;
	    if(git_branch_iterator_new(&iterator, repository_, type) == GIT_OK)
	    {
                auto repository = shared_from_this();
		git_reference* reference = nullptr;
		while(git_branch_next(&reference, &type, iterator) == GIT_OK)
		{
		    branches.push_back(std::make_shared<Branch>(repository, reference, type));
		}
		git_branch_iterator_free(iterator);
	    }
	}
	return branches;
    }

    /**
     */
    const std::vector<CommitPtr>& Repository::getCommits(bool update)
    {
	if(update || commits_.empty())
	{
	    if(isOk())
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
			    git_commit* commit;
			    if(git_commit_lookup(&commit, repository_, &oid) == GIT_OK)
			    {
				commits_.push_back(std::make_shared<Commit>(self, commit));
			    }
			}
		    }
		    git_revwalk_free(walk);
		}
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
     * @brief シグネチャを取得(生成)する
     * @return シグネチャ
     */
    SignaturePtr Repository::createSignature() const
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
    DiffPtr Repository::createDiff() const
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
                    result = std::make_shared<Diff>(diff);
                }
                git_tree_free(tree);
            }
            git_reference_free(reference);
        }
        return result;
    }

    /**
     * @brief インデックスを生成する
     * @return インデックス
     */
    IndexPtr Repository::createIndex() const
    {
        git_index* index;
        if(git_repository_index(&index, repository_) == GIT_OK)
        {
            return std::make_shared<Index>(index);
        }
        return nullptr;
    }

    /**
     * @brief
     */
    ReferencePtr Repository::head()
    {
        git_reference* reference;
        if(git_repository_head(&reference, repository_) == GIT_OK)
        {
            return std::make_shared<Reference>(shared_from_this(), reference);
        }
        return nullptr;
    }
}
