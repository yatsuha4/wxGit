#include "wxgit/DiffWindow.hpp"
#include "wxgit/FileWindow.hpp"
#include "wxgit/MainFrame.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] mainFrame メインフレーム
     */
    FileWindow::FileWindow(MainFrame* mainFrame)
        : super(mainFrame, 
                wxID_ANY, 
                wxDefaultPosition, 
                wxDefaultSize, 
                wxTL_MULTIPLE | 
                wxTL_CHECKBOX |
                wxTL_3STATE |
                wxTL_NO_HEADER)
    {
        AppendColumn("Path");
        Bind(wxEVT_TREELIST_SELECTION_CHANGED, &FileWindow::onSelectionChanged, this);
    }

    /**
     */
    MainFrame* FileWindow::getMainFrame() const
    {
        return static_cast<MainFrame*>(GetParent());
    }

    /**
     * @brief 差分を表示する
     * @param[in] diff 差分
     */
    void FileWindow::showDiff(const git::DiffPtr& diff)
    {
        DeleteAllItems();
        diff_ = diff;
        for(auto& delta : diff->getDeltas())
        {
            switch(delta.getStatus())
            {
            case GIT_DELTA_ADDED:
            case GIT_DELTA_DELETED:
            case GIT_DELTA_MODIFIED:
                {
                    auto path = delta.getNewFile().getPath().GetFullPath(wxPATH_UNIX);
                    auto item = AppendItem(GetRootItem(), path);
                    SetItemData(item, new ItemData(delta));
                }
                break;
            default:
                break;
            }
        }
    }

    /**
     */
    void FileWindow::onSelectionChanged(wxTreeListEvent& event)
    {
        if(auto data = static_cast<ItemData*>(GetItemData(event.GetItem())))
        {
            wxLogDebug(data->getDelta().getNewFile().getPath().GetFullPath());
            getMainFrame()->getDiffWindow()->showDelta(data->getDelta());
        }
    }

    /**
     */
    FileWindow::ItemData::ItemData(const git::Diff::Delta& delta)
        : delta_(delta)
    {
    }
}
