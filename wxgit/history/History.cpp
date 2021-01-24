/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/MainFrame.hpp"
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Signature.hpp"
#include "wxgit/history/History.hpp"

namespace wxgit {
namespace history {
/***********************************************************************//**
	@brief コンストラクタ
	@param[in] mainFrame メインフレーム
***************************************************************************/
History::History(MainFrame* mainFrame)
  : super(mainFrame, wxID_ANY)
{
  AppendTextColumn("Message");
  AppendTextColumn("Committer");
  AppendTextColumn("Date");
}
/***********************************************************************//**
	@brief 
***************************************************************************/
MainFrame* History::getMainFrame() const {
  return static_cast<MainFrame*>(GetParent());
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void History::showCommits(const std::vector<git::CommitPtr>& commits) {
  DeleteAllItems();
  for(auto& commit : commits) {
    wxVector<wxVariant> item;
    item.push_back(commit->getMessage());
    item.push_back(commit->getCommitter()->name);
    item.push_back(commit->getCommitter()->when.Format("%F %R"));
    AppendItem(item);
    wxYield();
  }
  commits_ = commits;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
