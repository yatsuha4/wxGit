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

  void appendItem(Item* item, Item* parent = nullptr);
  void removeItem(Item* item);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
