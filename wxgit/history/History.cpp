/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Signature.hpp"
#include "wxgit/history/History.hpp"

namespace wxgit {
namespace history {
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
History::History(wxWindow* parent)
  : super(parent, wxID_ANY)
{
  AppendTextColumn("Message");
  AppendTextColumn("Committer");
  AppendTextColumn("Date");
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
History::~History() {
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
  }
  commits_ = commits;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
