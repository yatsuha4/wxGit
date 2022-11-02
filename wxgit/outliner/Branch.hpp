#pragma once

#include "wxgit/outliner/Node.hpp"

namespace wxgit::outliner
{
    /**
     * @brief ブランチノード
     */
    class Branch
        : public Node
    {
        using super = Node;

    private:
        git::BranchPtr branch_;

    public:
        Branch(const git::BranchPtr& branch);
        ~Branch() override = default;

    protected:
        void onAppend(Outliner* outliner) override;
    };
}
