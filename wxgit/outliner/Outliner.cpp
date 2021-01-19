/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/outliner/Item.hpp"
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
  appendItem(new Item("TEST"));
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
Outliner::~Outliner() {
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Outliner::appendItem(Item* item) {
  item->setId(AppendItem(GetRootItem(), item->getText()));
  SetItemData(item->getId(), item);
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
