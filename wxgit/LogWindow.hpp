#pragma once

#include "wxgit/Window.hpp"

namespace wxgit
{
    class LogWindow
        : public Window<wxDataViewListCtrl>
    {
        using super = Window<wxDataViewListCtrl>;

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

        void clear();
        void showCommits(const std::vector<git::CommitPtr>& commits);
        void insertCommit(const git::CommitPtr& commit, int index = 0);

    private:
        void onSelectionChanged(wxDataViewEvent& event);
    };
}
