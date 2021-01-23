﻿/***********************************************************************//**
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
  DeleteItem(node->getId());
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}