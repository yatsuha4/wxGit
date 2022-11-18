#include "wxgit/git/Reference.hpp"
#include "wxgit/outliner/BranchNode.hpp"

namespace wxgit::outliner
{
    /**
     * @brief コンストラクタ
     * @param[in] branch ブランチ
     */
    BranchNode::BranchNode(const git::ReferencePtr& branch)
        : super(branch->getBranchName()), 
          branch_(branch)
    {
    }

    /**
     */
    void BranchNode::onAppend(Outliner* outliner)
    {
        super::onAppend(outliner);
        setBold(branch_->isHead());
    }
}
