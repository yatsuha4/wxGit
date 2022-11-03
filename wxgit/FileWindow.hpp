#pragma once

#include "wxgit/git/Diff.hpp"

namespace wxgit
{
    /**
     * @brief ファイル一覧
     */
    class FileWindow
        : public wxTreeListCtrl
    {
        using super = wxTreeListCtrl;

    private:
        git::DiffPtr diff_;
        git::StatusPtr status_;

    public:
        FileWindow(MainFrame* mainFrame);
        ~FileWindow() override = default;

        MainFrame* getMainFrame() const;

        void showDiff(const git::DiffPtr& diff);
        void showStatus(const git::StatusPtr& status);

    private:
        void clear();
        void showDelta(const git::Diff::Delta& delta);
        void onSelectionChanged(wxTreeListEvent& event);

    private:
        class ItemData
            : public wxClientData
        {
        private:
            const git::Diff::Delta& delta_;

        public:
            ItemData(const git::Diff::Delta& delta);
            ~ItemData() = default;

            WXEDITOR_GETTER(Delta, delta_);
        };
    };
}
