#include "wxgit/git/Blob.hpp"
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Diff.hpp"
#include "wxgit/git/Signature.hpp"
#include "wxgit/git/Tree.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     * @param[in] commit コミット
     */
    Commit::Commit(const RepositoryPtr& repository, git_commit* commit)
        : repository_(repository), 
          commit_(commit), 
          tree_(nullptr), 
          message_(wxString::FromUTF8(git_commit_message(commit))), 
          committer_(std::make_shared<Signature>(git_commit_committer(commit))), 
          time_(static_cast<time_t>(git_commit_time(commit)))
    {
    }

    /**
     * @brief デストラクタ
     */
    Commit::~Commit()
    {
        if(tree_)
        {
            git_tree_free(tree_);
        }
        git_commit_free(commit_);
    }

    /**
     * @brief リポジトリを取得する
     * @return リポジトリ
     */
    RepositoryPtr Commit::getRepository() const
    {
        return repository_.lock();
    }

    /**
     */
    const std::vector<BlobPtr>& Commit::fetchBlobs()
    {
        if(!tree_)
        {
            if(git_commit_tree(&tree_, commit_) == GIT_OK)
            {
                parseTree(tree_, wxFileName());
            }
        }
        return blobs_;
    }

    /**
     */
    DiffPtr Commit::createDiff() const
    {
        DiffPtr result;
        git_commit* parent;
        if(git_commit_parent(&parent, commit_, 0) == GIT_OK)
        {
            git_tree* parentTree;
            if(git_commit_tree(&parentTree, parent) == GIT_OK)
            {
                git_tree* tree;
                if(git_commit_tree(&tree, commit_) == GIT_OK)
                {
                    git_diff_options options;
                    if(git_diff_options_init(&options, GIT_DIFF_OPTIONS_VERSION) == GIT_OK)
                    {
                        git_diff* diff;
                        if(git_diff_tree_to_tree(&diff, 
                                                 git_commit_owner(commit_), 
                                                 parentTree, 
                                                 tree, 
                                                 &options) == GIT_OK)
                        {
                            result = std::make_shared<Diff>(shared_from_this(), diff);
                        }
                    }
                    git_tree_free(tree);
                }
                git_tree_free(parentTree);
            }
            git_commit_free(parent);
        }
        return result;
    }

    /**
     */
    void Commit::parseTree(git_tree* tree, const wxFileName& dir)
    {
        for(size_t i = 0, n = git_tree_entrycount(tree); i < n; ++i)
        {
            auto entry = git_tree_entry_byindex(tree, i);
            wxFileName path(dir.GetFullPath(), 
                            wxString::FromUTF8(git_tree_entry_name(entry)));
            switch(git_tree_entry_type(entry))
            {
            case GIT_OBJECT_TREE:
                {
                    git_tree* child;
                    if(git_tree_lookup(&child, 
                                       git_commit_owner(commit_), 
                                       git_tree_entry_id(entry)) == GIT_OK)
                    {
                        parseTree(child, path);
                        git_tree_free(child);
                    }
                }
                break;
            case GIT_OBJECT_BLOB:
                {
                    git_blob* blob;
                    if(git_blob_lookup(&blob, 
                                       git_commit_owner(commit_), 
                                       git_tree_entry_id(entry)) == GIT_OK)
                    {
                        blobs_.push_back(std::make_shared<Blob>(blob, path));
                    }
                }
                break;
            }
        }
    }
}
