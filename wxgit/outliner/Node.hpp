﻿/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Node
  : public wxClientData
{
 private: 
  wxString text_;
  Outliner* outliner_;
  wxTreeListItem id_;

 public:
  Node(const wxString& text);
  ~Node() override;

  WXGIT_ACCESSOR(Text, text_);
  WXGIT_GETTER(Id, id_);

  void link(Outliner* outliner, const wxTreeListItem& id);
  void unlink();
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}