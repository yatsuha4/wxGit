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
        git::RepositoryPtr getRepository() const;

        void clear();
        void appendDelta(const git::Diff::Delta& delta, wxCheckBoxState state);
        void update();
        bool update(const wxTreeListItem& parent, 
                    const git::Path& parentPath, 
                    const std::shared_ptr<PathList::Item>& item);

        void onSelectionChanged(wxTreeListEvent& event);

        void onItemChecked(wxTreeListEvent& event);
        void onCheckItem(wxTreeListItem item, 
                         wxCheckBoxState state, 
                         wxCheckBoxState oldState);

        void addDelta(const git::Diff::Delta& delta);
        void removeDelta(const git::Diff::Delta& delta);

        class ItemData
            : public wxClientData
        {
        private:
            const git::Diff::Delta& delta_;
            wxCheckBoxState state_;

        public:
            ItemData(const git::Diff::Delta& delta, wxCheckBoxState state);
            ~ItemData() = default;

            WXEDITOR_GETTER(Delta, delta_);
            WXEDITOR_GETTER(State, state_);
        };
    };
}
