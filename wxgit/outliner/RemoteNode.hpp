#pragma once

#include "wxgit/outliner/Node.hpp"

namespace wxgit::outliner
{
    /**
     * @brief リモートノード
     */
    class RemoteNode
        : public Node
    {
        using super = Node;

    private:
        git::RemotePtr remote_;

    public:
        RemoteNode(const git::RemotePtr& remote);
        ~RemoteNode() override;

    protected:
        void onAppend(Outliner* outliner) override;
    };
}
