#include "wxgit/git/Refspec.hpp"
#include "wxgit/outliner/RefspecNode.hpp"

namespace wxgit::outliner
{
    /**
     * @brief コンストラクタ
     * @param[in] refspec
     */
    RefspecNode::RefspecNode(const git::RefspecPtr& refspec)
        : refspec_(refspec)
    {
        setName(refspec_->getDst());
    }

    /**
     * @brief デストラクタ
     */
    RefspecNode::~RefspecNode()
    {
    }
}
