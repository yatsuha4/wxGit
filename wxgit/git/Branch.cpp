#include "wxgit/git/Branch.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     */
    Branch::Branch(const RepositoryPtr& repository, 
                   git_reference* reference, 
                   git_branch_t type)
        : super(repository, reference), 
          type_(type)
    {
    }

    /**
     * @brief
     */
    bool Branch::isHead() const
    {
        return git_branch_is_head(getReference());
    }
}
