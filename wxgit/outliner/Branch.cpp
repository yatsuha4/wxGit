#include "wxgit/git/Branch.hpp"
#include "wxgit/outliner/Branch.hpp"

namespace wxgit::outliner
{
    /**
     * @brief コンストラクタ
     */
    Branch::Branch(const git::BranchPtr& branch)
        : branch_(branch)
    {
        setName(branch->getName());
    }

    /**
     */
    void Branch::onAppend(Outliner* outliner)
    {
        super::onAppend(outliner);
        setBold(branch_->isHead());
    }
}
