#pragma once

#include "wxgit/Serializable.hpp"

namespace wxgit::outliner
{
    /**
     * @brief アウトライナ
     */
    class Outliner
        : public wxTreeListCtrl, 
          public Serializable
    {
        using super = wxTreeListCtrl;

    public:
        Outliner(MainFrame* mainFrame);
        ~Outliner() override = default;

        MainFrame* getMainFrame() const;

        Node* appendNode(Node* node, Node* parent = nullptr);
        void removeNode(Node* node);

        Node* getParentNode(Node* node) const;

        wxXmlNode* serialize() const override;
        bool deserialize(const wxXmlNode* xml) override;
        WXGIT_GET_SERIAL_NAME(Outliner);

    private:
        void onSelectionChanged(wxTreeListEvent& event);
        void onContextMenu(wxTreeListEvent& event);
    };
}
