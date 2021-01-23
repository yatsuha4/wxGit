/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Outliner
  : public wxTreeListCtrl
{
  using super = wxTreeListCtrl;

 public:
  Outliner(wxWindow* parent);
  virtual ~Outliner();

  Node* appendNode(Node* node, Node* parent = nullptr);
  void removeNode(Node* node);

  Node* getParentNode(Node* node) const;
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
