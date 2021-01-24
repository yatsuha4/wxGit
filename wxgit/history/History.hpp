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
  History(MainFrame* mainFrame);
  ~History() override = default;

  MainFrame* getMainFrame() const;

  void showCommits(const std::vector<git::CommitPtr>& commits);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
