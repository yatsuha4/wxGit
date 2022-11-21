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
	AppendTextColumn(_("Message"));
	AppendTextColumn(_("Committer"));
	AppendTextColumn(_("Date"));
        Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &LogWindow::onSelectionChanged, this);
    }

    /**
     */
    MainFrame* LogWindow::getMainFrame() const
    {
	return static_cast<MainFrame*>(GetParent());
    }

    /**
     * @brief 全消去
     */
    void LogWindow::clear()
    {
	DeleteAllItems();
        commits_.clear();
    }

    /**
     */
    void LogWindow::showCommits(const std::vector<git::CommitPtr>& commits)
    {
        clear();
        getMainFrame()->showIndicator(true);
        Freeze();
	int index = 0;
	for(auto& commit : commits)
	{
            insertCommit(commit, index++);
	    wxYield();
	}
        /*
        SetColumnWidth(Column::MESSAGE, wxLIST_AUTOSIZE);
        SetColumnWidth(Column::COMMITTER, wxLIST_AUTOSIZE);
        SetColumnWidth(Column::DATE, wxLIST_AUTOSIZE);
        */
        Thaw();
        getMainFrame()->showIndicator(false);
    }

    /**
     */
    void LogWindow::insertCommit(const git::CommitPtr& commit, int index)
    {
        wxVector<wxVariant> row;
        auto message = commit->getMessage();
        wxRegEx("(^\\s+)|(\\s+$)").ReplaceAll(&message, "");
        wxRegEx("\\s+").ReplaceAll(&message, " ");
        row.push_back(message);
        row.push_back(commit->getCommitter()->getName());
        row.push_back(commit->getCommitter()->getWhen().Format("%F %R"));
        InsertItem(index, row);
        commits_.insert(commits_.begin() + index, commit);
    }

    /**
     */
    void LogWindow::onSelectionChanged(wxDataViewEvent& event)
    {
        auto index = ItemToRow(event.GetItem());
        if(index != wxNOT_FOUND)
        {
            auto& commit = commits_.at(index);
            if(auto diff = commit->createDiff())
            {
                getMainFrame()->getFileWindow()->showDiff(diff);
            }
        }
    }
}
