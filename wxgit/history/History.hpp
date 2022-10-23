#pragma once

namespace wxgit::history
{
    class History
	: public wxListCtrl
    {
	using super = wxListCtrl;

    private:
        enum Column
        {
            MESSAGE, 
            COMMITTER, 
            DATE
        };

    private:
	std::vector<git::CommitPtr> commits_;

    public:
	History(MainFrame* mainFrame);
	~History() override = default;

	MainFrame* getMainFrame() const;

	void showCommits(const std::vector<git::CommitPtr>& commits);

    private:
        void onItemSelected(wxListEvent& event);
    };
}
