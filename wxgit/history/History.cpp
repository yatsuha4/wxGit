#include "wxgit/FileWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/git/Blob.hpp"
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Diff.hpp"
#include "wxgit/git/Signature.hpp"
#include "wxgit/git/Tree.hpp"
#include "wxgit/history/History.hpp"

namespace wxgit::history
{
    /**
     * @brief コンストラクタ
     * @param[in] mainFrame メインフレーム
     */
    History::History(MainFrame* mainFrame)
	: super(mainFrame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT)
    {
	InsertColumn(Column::MESSAGE, wxT("Message"));
	InsertColumn(Column::COMMITTER, wxT("Committer"));
	InsertColumn(Column::DATE, wxT("Date"));
        Bind(wxEVT_LIST_ITEM_SELECTED, &History::onItemSelected, this);
    }

    /**
     */
    MainFrame* History::getMainFrame() const
    {
	return static_cast<MainFrame*>(GetParent());
    }

    /**
     */
    void History::showCommits(const std::vector<git::CommitPtr>& commits)
    {
	DeleteAllItems();
        Freeze();
	long index = 0;
	for(auto& commit : commits)
	{
	    InsertItem(index, commit->getMessage());
	    SetItem(index, Column::COMMITTER, commit->getCommitter()->getName());
	    SetItem(index, Column::DATE, commit->getCommitter()->getWhen().Format("%F %R"));
	    wxYield();
	    ++index;
	}
        SetColumnWidth(Column::MESSAGE, wxLIST_AUTOSIZE);
        SetColumnWidth(Column::COMMITTER, wxLIST_AUTOSIZE);
        SetColumnWidth(Column::DATE, wxLIST_AUTOSIZE);
        Thaw();
	commits_ = commits;
    }

    /**
     */
    void History::onItemSelected(wxListEvent& event)
    {
        auto& commit = commits_.at(event.GetIndex());
        if(auto diff = commit->createDiff())
        {
            getMainFrame()->getFileWindow()->showDiff(diff);
        }
    }
}
