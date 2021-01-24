/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
/***********************************************************************//**
	@brief 
***************************************************************************/
class FileList
  : public wxDataViewListCtrl
{
  using super = wxDataViewListCtrl;

 private:
  std::vector<wxFileName> files_;

 public:
  FileList(MainFrame* mainFrame);
  ~FileList() override = default;

  void show(const std::vector<wxFileName>& files);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
