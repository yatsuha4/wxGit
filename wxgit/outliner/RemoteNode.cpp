#include "wxgit/git/Remote.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/RefspecNode.hpp"
#include "wxgit/outliner/RemoteNode.hpp"

namespace wxgit::outliner
{
    /**
     * @brief コンストラクタ
     * @param[in] remote リモート
     */
    RemoteNode::RemoteNode(const git::RemotePtr& remote)
        : remote_(remote)
    {
        setName(remote->getName());
    }

    /**
     * @brief デストラクタ
     */
    RemoteNode::~RemoteNode()
    {
    }

    /**
     */
    void RemoteNode::onAppend(Outliner* outliner)
    {
        super::onAppend(outliner);
        auto& refspecs = remote_->getRefspecs();
        if(!refspecs.empty())
        {
            auto folder = new Node();
            folder->setName("Branch");
            outliner->appendNode(folder, this);
            for(auto& refspec : refspecs)
            {
                outliner->appendNode(new RefspecNode(refspec), folder);
            }
        }
    }
}
