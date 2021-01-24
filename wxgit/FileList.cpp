/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/FileList.hpp"
#include "wxgit/MainFrame.hpp"

namespace wxgit {
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
FileList::FileList(MainFrame* mainFrame)
  : super(mainFrame, wxID_ANY)
{
  AppendToggleColumn("Stage");
  AppendTextColumn("Dir");
  AppendTextColumn("File");
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void FileList::show(const std::vector<wxFileName>& files) {
  DeleteAllItems();
  files_ = files;
  for(auto& file : files) {
    wxVector<wxVariant> item;
    item.push_back(false);
    item.push_back(file.GetPath());
    item.push_back(file.GetFullName());
    AppendItem(item);
  }
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
