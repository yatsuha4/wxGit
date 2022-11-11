#include "wxgit/git/Reference.hpp"
#include "wxgit/outliner/Branch.hpp"

namespace wxgit::outliner
{
    /**
     * @brief コンストラクタ
     * @param[in] branch ブランチ
     */
    Branch::Branch(const git::ReferencePtr& branch)
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
