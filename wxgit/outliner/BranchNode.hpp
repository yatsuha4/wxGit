#pragma once

#include "wxgit/outliner/Node.hpp"

namespace wxgit::outliner
{
    /**
     * @brief ブランチノード
     */
    class BranchNode
        : public Node
    {
        using super = Node;

    private:
        git::ReferencePtr branch_;

    public:
        BranchNode(const git::ReferencePtr& branch);
        ~BranchNode() override = default;

    protected:
        void onAppend(Outliner* outliner) override;
    };
}
