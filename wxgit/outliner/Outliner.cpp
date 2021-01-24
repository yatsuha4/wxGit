/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/MainFrame.hpp"
#include "wxgit/Menu.hpp"
#include "wxgit/outliner/Node.hpp"
#include "wxgit/outliner/Outliner.hpp"

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief コンストラクタ
	@param[in] parent 親ウィンドウ
***************************************************************************/
Outliner::Outliner(MainFrame* mainFrame)
  : super(mainFrame, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
          wxTL_DEFAULT_STYLE | wxTL_NO_HEADER)
{
  AppendColumn("Name");
  Bind(wxEVT_TREELIST_ITEM_CONTEXT_MENU, &Outliner::onContextMenu, this);
}
/***********************************************************************//**
	@brief メインフレームを取得する
	@return メインフレーム
***************************************************************************/
MainFrame* Outliner::getMainFrame() const {
  return static_cast<MainFrame*>(GetParent());
}
/***********************************************************************//**
	@brief 
***************************************************************************/
Node* Outliner::appendNode(Node* node, Node* parent) {
  auto id = AppendItem((parent ? parent->getId() : GetRootItem()), 
                       node->getName());
  SetItemData(id, node);
  node->onAppend(this, id);
  if(parent) {
    parent->onAppendChild(*this, node);
  }
  return node;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Outliner::removeNode(Node* node) {
  for(auto child = GetFirstChild(node->getId());
      child.IsOk();
      child = GetNextItem(child)) {
    removeNode(static_cast<Node*>(GetItemData(child)));
  }
  if(auto parent = getParentNode(node)) {
    parent->onRemoveChild(*this, node);
  }
  DeleteItem(node->getId());
}
/***********************************************************************//**
	@brief 親ノードを取得する
	@param[in] node ノード
	@return 親ノード
***************************************************************************/
Node* Outliner::getParentNode(Node* node) const {
  auto id = GetItemParent(node->getId());
  return id.IsOk() ? static_cast<Node*>(GetItemData(id)) : nullptr;
}
/***********************************************************************//**
	@copydoc Serializable::serialize
***************************************************************************/
wxXmlNode* Outliner::serialize() const {
  auto xml = Serializable::serialize();
  for(auto iter = GetFirstChild(GetRootItem());
      iter.IsOk();
      iter = GetNextSibling(iter)) {
    xml->AddChild(static_cast<Node*>(GetItemData(iter))->serialize());
  }
  return xml;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Outliner::deserialize(const wxXmlNode* xml) {
  if(Serializable::deserialize(xml)) {
    for(auto iter = xml->GetChildren(); iter; iter = iter->GetNext()) {
      if(auto node = Node::Create(iter->GetName())) {
        node->deserialize(iter);
        appendNode(node);
      }
      else {
        Warning("illegal node", iter);
      }
    }
    return true;
  }
  return false;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Outliner::onContextMenu(wxTreeListEvent& event) {
  if(auto node = static_cast<Node*>(GetItemData(event.GetItem()))) {
    if(auto menu = node->getContextMenu()) {
      PopupMenu(menu);
    }
  }
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
