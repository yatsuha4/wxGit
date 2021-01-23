/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
namespace history {
/***********************************************************************//**
	@brief 
***************************************************************************/
class History
  : public wxDataViewListCtrl
{
  using super = wxDataViewListCtrl;

 private:
  std::vector<git::CommitPtr> commits_;

 public:
  History(wxWindow* parent);
  ~History() override;

  void showCommits(const std::vector<git::CommitPtr>& commits);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
