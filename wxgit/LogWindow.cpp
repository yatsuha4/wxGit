#include "wxgit/FileWindow.hpp"
#include "wxgit/LogWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/git/Blob.hpp"
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Diff.hpp"
#include "wxgit/git/Signature.hpp"
#include "wxgit/git/Tree.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] mainFrame メインフレーム
     */
    LogWindow::LogWindow(MainFrame* mainFrame)
	: super(mainFrame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT)
    {
	InsertColumn(Column::MESSAGE, wxT("Message"));
	InsertColumn(Column::COMMITTER, wxT("Committer"));
	InsertColumn(Column::DATE, wxT("Date"));
        Bind(wxEVT_LIST_ITEM_SELECTED, &LogWindow::onItemSelected, this);
    }

    /**
     */
    MainFrame* LogWindow::getMainFrame() const
    {
	return static_cast<MainFrame*>(GetParent());
    }

    /**
     */
    void LogWindow::showCommits(const std::vector<git::CommitPtr>& commits)
    {
	DeleteAllItems();
        Freeze();
	long index = 0;
	for(auto& commit : commits)
	{
            insertCommit(commit, index++);
	    wxYield();
	}
        SetColumnWidth(Column::MESSAGE, wxLIST_AUTOSIZE);
        SetColumnWidth(Column::COMMITTER, wxLIST_AUTOSIZE);
        SetColumnWidth(Column::DATE, wxLIST_AUTOSIZE);
        Thaw();
	commits_ = commits;
    }

    /**
     */
    void LogWindow::insertCommit(const git::CommitPtr& commit, int index)
    {
        InsertItem(index, commit->getMessage());
        SetItem(index, Column::COMMITTER, commit->getCommitter()->getName());
        SetItem(index, Column::DATE, commit->getCommitter()->getWhen().Format("%F %R"));
    }

    /**
     */
    void LogWindow::onItemSelected(wxListEvent& event)
    {
        auto& commit = commits_.at(event.GetIndex());
        if(auto diff = commit->createDiff())
        {
            getMainFrame()->getFileWindow()->showDiff(diff);
        }
    }
}
