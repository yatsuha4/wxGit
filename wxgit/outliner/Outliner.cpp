/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/outliner/Node.hpp"
#include "wxgit/outliner/Outliner.hpp"

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief コンストラクタ
	@param[in] parent 親ウィンドウ
***************************************************************************/
Outliner::Outliner(wxWindow* parent)
  : super(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
          wxTL_DEFAULT_STYLE | wxTL_NO_HEADER)
{
  AppendColumn("Name");
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
Outliner::~Outliner() {
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Outliner::appendNode(Node* node, Node* parent) {
  auto id = AppendItem((parent ? parent->getId() : GetRootItem()), 
                       node->getText());
  SetItemData(id, node);
  node->link(this, id);
  if(parent) {
    parent->onAppendChild(*this, node);
  }
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
	$Id$
***************************************************************************/
}
}
