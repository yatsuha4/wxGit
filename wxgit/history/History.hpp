#pragma once

namespace wxgit::history
{
    class History
	: public wxListCtrl
    {
	using super = wxListCtrl;

    private:
	std::vector<git::CommitPtr> commits_;

    public:
	History(MainFrame* mainFrame);
	~History() override = default;

	MainFrame* getMainFrame() const;

	void showCommits(const std::vector<git::CommitPtr>& commits);
    };
}
