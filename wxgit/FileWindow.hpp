#pragma once

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

        void showDiff(const git::DiffPtr& diff);
    };
}
