﻿#include "wxgit/outliner/Node.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/RepositoryNode.hpp"

namespace wxgit::outliner
{
    /**
     * @brief デフォルトコンストラクタ
     */
    Node::Node()
        : Node(wxEmptyString)
    {
    }

    /**
     * @brief コンストラクタ
     * @param[in] name 名前
     */
    Node::Node(const wxString& name)
        : name_(name), 
          outliner_(nullptr)
    {
    }

    /**
     * @brief 
     */
    void Node::setName(const wxString& name)
    {
        name_ = name;
        if(outliner_)
        {
            outliner_->SetItemText(GetId(), name);
        }
    }

    /**
     * @brief 
     */
    void Node::onAppend(Outliner* outliner)
    {
        wxASSERT(!outliner_);
        outliner_ = outliner;
    }

    /**
     * @brief 
     */
    wxMenu* Node::getContextMenu()
    {
        return nullptr;
    }

    /**
     * @brief 
     */
    wxXmlNode* Node::serialize() const
    {
        auto xml = Serializable::serialize();
        xml->AddAttribute("name", name_);
        return xml;
    }

    /**
     * @brief 
     */
    bool Node::deserialize(const wxXmlNode* xml)
    {
        if(Serializable::deserialize(xml))
        {
            setName(xml->GetAttribute("name"));
            return true;
        }
        return false;
    }

    /**
     * @brief 
     */
    Node* Node::Create(const wxString& serialName)
    {
        if(serialName == Node::GetSerialName())
        {
            return new Node();
        }
        else if(serialName == RepositoryNode::GetSerialName())
        {
            return new RepositoryNode();
        }
        return nullptr;
    }

    /**
     * @brief
     */
    void Node::setBold(bool isBold)
    {
        outliner_->SetItemBold(GetId(), isBold);
    }
}
