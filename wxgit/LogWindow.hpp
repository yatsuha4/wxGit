#pragma once

#include "wxgit/Window.hpp"

namespace wxgit
{
    class LogWindow
        : public Window<wxListCtrl>
    {
        using super = Window<wxListCtrl>;

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
        LogWindow(MainFrame* mainFrame);
        ~LogWindow() override = default;

        MainFrame* getMainFrame() const;

        void showCommits(const std::vector<git::CommitPtr>& commits);
        void insertCommit(const git::CommitPtr& commit, int index = 0);

    private:
        void onItemSelected(wxListEvent& event);
    };
}
