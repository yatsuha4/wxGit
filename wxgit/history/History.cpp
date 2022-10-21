#include "wxgit/MainFrame.hpp"
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Signature.hpp"
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
	AppendColumn(wxT("Message"));
	AppendColumn(wxT("Committer"));
	AppendColumn(wxT("Date"));
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
	long index = 0;
	for(auto& commit : commits)
	{
	    InsertItem(index, commit->getMessage());
	    SetItem(index, 1, commit->getCommitter()->getName());
	    SetItem(index, 2, commit->getCommitter()->getWhen().Format("%F %R"));
	    wxYield();
	    ++index;
	}
	commits_ = commits;
    }
}
