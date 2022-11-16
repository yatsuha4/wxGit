#pragma once

#include "wxgit/outliner/Node.hpp"

namespace wxgit::outliner
{
    /**
     * @brief リポジトリノード
     */
    class RepositoryNode
        : public Node
    {
        using super = Node;

    private:
        git::RepositoryPtr repository_;

    public:
        RepositoryNode() = default;
        RepositoryNode(const git::RepositoryPtr& repository);
        ~RepositoryNode() override = default;

        WXEDITOR_GETTER(Repository, repository_);

        wxMenu* getContextMenu() override;

        wxXmlNode* serialize() const override;
        bool deserialize(const wxXmlNode* xml) override;
        WXGIT_GET_SERIAL_NAME(Repository);

    protected:
        void onAppend(Outliner* outliner) override;

    private:
        void appendBranches(const wxString& name, 
                            const std::vector<git::ReferencePtr>& branches);
        void appendRemotes();
    };
}
