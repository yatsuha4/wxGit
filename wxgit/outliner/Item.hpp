﻿/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Item
  : public wxClientData
{
 private: 
  wxString text_;
  Outliner* outliner_;
  wxTreeListItem id_;

 public:
  Item(const wxString& text);
  ~Item() override;

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