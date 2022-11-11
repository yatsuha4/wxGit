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
        git::ReferencePtr branch_;

    public:
        Branch(const git::ReferencePtr& branch);
        ~Branch() override = default;

    protected:
        void onAppend(Outliner* outliner) override;
    };
}
