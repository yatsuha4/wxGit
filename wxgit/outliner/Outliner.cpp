#include "wxgit/MainFrame.hpp"
#include "wxgit/Menu.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/history/History.hpp"
#include "wxgit/outliner/Node.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/Repository.hpp"

namespace wxgit::outliner
{
    /**
     * @brief コンストラクタ
     * @param[in] mainFrame メインフレーム
     */
    Outliner::Outliner(MainFrame* mainFrame)
        : super(mainFrame, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                wxTR_DEFAULT_STYLE)
    {
        Bind(wxEVT_TREE_SEL_CHANGED, &Outliner::onSelectionChanged, this);
        //Bind(wxEVT_TREE_ITEM_CONTEXT_MENU, &Outliner::onContextMenu, this);
    }

    /**
     * @brief メインフレームを取得する
     * @return メインフレーム
     */
    MainFrame* Outliner::getMainFrame() const
    {
        return static_cast<MainFrame*>(GetParent());
    }

    /**
     * @brief 
     */
    Node* Outliner::appendNode(Node* node, Node* parent)
    {
        auto id = AppendItem((parent ? parent->GetId() : GetRootItem()), 
                             node->getName());
        SetItemData(id, node);
        node->onAppend(this);
        if(parent)
        {
            parent->onAppendChild(*this, node);
        }
        return node;
    }

    /*
     * @brief 
     */
    void Outliner::removeNode(Node* node)
    {
        wxTreeItemIdValue cookie;
        for(auto child = GetFirstChild(node->GetId(), cookie);
            child.IsOk();
            child = GetNextChild(child, cookie))
        {
            removeNode(static_cast<Node*>(GetItemData(child)));
        }
        if(auto parent = getParentNode(node))
        {
            parent->onRemoveChild(*this, node);
        }
        Delete(node->GetId());
    }

    /**
     * @brief 親ノードを取得する
     * @param[in] node ノード
     * @return 親ノード
     */
    Node* Outliner::getParentNode(Node* node) const
    {
        auto id = GetItemParent(node->GetId());
        return id.IsOk() ? static_cast<Node*>(GetItemData(id)) : nullptr;
    }

    /**
     * @copydoc Serializable::serialize
     */
    wxXmlNode* Outliner::serialize() const
    {
        auto xml = Serializable::serialize();
        wxTreeItemIdValue cookie;
        for(auto iter = GetFirstChild(GetRootItem(), cookie);
            iter.IsOk();
            iter = GetNextSibling(iter))
        {
            xml->AddChild(static_cast<Node*>(GetItemData(iter))->serialize());
        }
        return xml;
    }

    /**
     * @brief 
     */
    bool Outliner::deserialize(const wxXmlNode* xml)
    {
        if(Serializable::deserialize(xml))
        {
            for(auto iter = xml->GetChildren(); iter; iter = iter->GetNext())
            {
                if(auto node = Node::Create(iter->GetName()))
                {
                    node->deserialize(iter);
                    appendNode(node);
                }
                else
                {
                    Warning("illegal node", iter);
                }
            }
            return true;
        }
        return false;
    }

    /**
     * @brief 
     */
    void Outliner::onSelectionChanged(wxTreeEvent& event)
    {
        auto node = static_cast<Node*>(GetItemData(event.GetItem()));
        if(auto repository = dynamic_cast<Repository*>(node))
        {
            getMainFrame()->setRepository(repository->getRepository());
        }
    }

    /**
     * @brief 
     */
    void Outliner::onContextMenu(wxTreeEvent& event)
    {
        if(auto node = static_cast<Node*>(GetItemData(event.GetItem())))
        {
            if(auto menu = node->getContextMenu())
            {
                PopupMenu(menu);
            }
        }
    }
}
