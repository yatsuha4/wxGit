#pragma once

#include "wxgit/Serializable.hpp"

namespace wxgit::outliner
{
    /**
     * @brief ノード基底クラス
     */
    class Node
        : public wxTreeItemData, 
          public Serializable
    {
    private: 
        wxString name_;
        Outliner* outliner_;

    public:
        Node();
        ~Node() override = default;

        void setName(const wxString& name);
        WXEDITOR_GETTER(Name, name_);

        WXEDITOR_GETTER(Outliner, outliner_);

        virtual void onAppend(Outliner* outliner);

        virtual void onAppendChild(Outliner& outliner, Node* child) {}
        virtual void onRemoveChild(Outliner& outliner, Node* child) {}

        virtual wxMenu* getContextMenu();

        wxXmlNode* serialize() const override;
        bool deserialize(const wxXmlNode* xml) override;
        WXGIT_GET_SERIAL_NAME(Node);

        static Node* Create(const wxString& serialName);

        void setBold(bool isBold);
    };
}
