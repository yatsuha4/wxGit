#include "wxgit/git/Remote.hpp"
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
}
