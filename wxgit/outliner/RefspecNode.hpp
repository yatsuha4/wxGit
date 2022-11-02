#pragma once

#include "wxgit/outliner/Node.hpp"

namespace wxgit::outliner
{
    /**
     * @brief
     */
    class RefspecNode
        : public Node
    {
        using super = Node;

    private:
        git::RefspecPtr refspec_;

    public:
        RefspecNode(const git::RefspecPtr& refspec);
        ~RefspecNode() override;
    };
}
