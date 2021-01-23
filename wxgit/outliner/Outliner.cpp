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
void Outliner::appendItem(Item* item, Item* parent) {
  auto id = AppendItem((parent ? parent->getId() : GetRootItem()), 
                       item->getText());
  SetItemData(id, item);
  item->link(this, id);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Outliner::removeItem(Item* item) {
  for(auto child = GetFirstChild(item->getId());
      child.IsOk();
      child = GetNextItem(child)) {
    removeItem(static_cast<Item*>(GetItemData(child)));
  }
  DeleteItem(item->getId());
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
