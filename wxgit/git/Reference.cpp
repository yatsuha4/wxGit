#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Reference.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     * @param[in] reference リファレンス
     */
    Reference::Reference(const RepositoryPtr& repository, git_reference* reference)
        : RepositoryReference(repository), 
          reference_(reference), 
          name_(wxString::FromUTF8(git_reference_name(reference_)))
    {
    }

    /**
     * @brief デストラクタ
     */
    Reference::~Reference()
    {
        git_reference_free(reference_);
    }

    /**
     */
    bool Reference::isBranch() const
    {
        return git_reference_is_branch(reference_);
    }

    /**
     * @brief
     */
    bool Reference::isHead() const
    {
        return isBranch() && git_branch_is_head(reference_);
    }

    /**
     */
    CommitPtr Reference::takeCommit() const
    {
        git_object* commit;
        if(git_reference_peel(&commit, reference_, GIT_OBJECT_COMMIT))
        {
            return std::make_shared<Commit>(getRepository(), 
                                            reinterpret_cast<git_commit*>(commit));
        }
        return nullptr;
    }
}
