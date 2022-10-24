#include "wxgit/FileWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/git/Diff.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] mainFrame メインフレーム
     */
    FileWindow::FileWindow(MainFrame* mainFrame)
        : super(mainFrame)
    {
    }

    /**
     * @brief 差分を表示する
     * @param[in] diff 差分
     */
    void FileWindow::showDiff(const git::DiffPtr& diff)
    {
        DeleteAllItems();
        diff_ = diff;
        auto root = AddRoot(wxT("ROOT"));
        for(auto& delta : diff->getDeltas())
        {
            switch(delta.getStatus())
            {
            case GIT_DELTA_ADDED:
            case GIT_DELTA_DELETED:
            case GIT_DELTA_MODIFIED:
                AppendItem(root, delta.getNewFile().getPath().GetFullPath(wxPATH_UNIX));
                break;
            default:
                break;
            }
        }
        Expand(root);
    }
}
