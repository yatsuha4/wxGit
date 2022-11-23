#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Diff.hpp"
#include "wxgit/git/Path.hpp"
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
        : RepositoryReference(repository), 
          commit_(commit), 
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
        git_commit_free(commit_);
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
}
