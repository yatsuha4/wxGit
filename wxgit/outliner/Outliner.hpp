#pragma once

#include "wxgit/Serializable.hpp"

namespace wxgit::outliner
{
    /**
     * @brief アウトライナ
     */
    class Outliner
        : public wxTreeCtrl, 
          public Serializable
    {
        using super = wxTreeCtrl;

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

        template <class T>
        T* findParentNode(Node* node) const
        {
            for(auto iter = node; iter; iter = getParentNode(iter))
            {
                if(auto parent = dynamic_cast<T*>(iter))
                {
                    return parent;
                }
            }
            return nullptr;
        }

    private:
        void onSelectionChanged(wxTreeEvent& event);
        void onContextMenu(wxTreeEvent& event);
    };
}
