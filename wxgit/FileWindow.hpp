#pragma once

#include "wxgit/PathList.hpp"
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
        PathListPtr pathList_;

    public:
        FileWindow(MainFrame* mainFrame);
        ~FileWindow() override = default;

        MainFrame* getMainFrame() const;

        void showDiff(const git::DiffPtr& diff);
        void showStatus(const git::StatusPtr& status);

    private:
        void clear();
        void appendDelta(const git::Diff::Delta& delta);
        void update();
        void update(const wxTreeListItem& parent, 
                    const wxString& parentPath, 
                    const std::shared_ptr<PathList::Item>& item);

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
