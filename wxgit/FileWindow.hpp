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

    public:
        FileWindow(MainFrame* mainFrame);
        ~FileWindow() override = default;

        MainFrame* getMainFrame() const;

        void showDiff(const git::DiffPtr& diff);

    private:
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
