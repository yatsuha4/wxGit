#include "wxgit/DiffWindow.hpp"
#include "wxgit/FileWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/git/Status.hpp"

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
        clear();
        diff_ = diff;
        for(auto& delta : diff->getDeltas())
        {
            appendDelta(delta);
        }
        update();
    }

    /**
     * @brief ステータスを表示する
     * @param[in] status ステータス
     */
    void FileWindow::showStatus(const git::StatusPtr& status)
    {
        clear();
        status_ = status;
        for(auto& entry : status->getEntries())
        {
            appendDelta(entry.getIndexToWorkdir());
        }
        update();
    }

    /**
     * @brief 内容を消去する
     */
    void FileWindow::clear()
    {
        DeleteAllItems();
        diff_.reset();
        status_.reset();
        pathList_ = std::make_shared<PathList>();
    }

    /**
     * @brief デルタを表示する
     * @param[in] delta デルタ
     */
    void FileWindow::appendDelta(const git::Diff::Delta& delta)
    {
        switch(delta.getStatus())
        {
        case GIT_DELTA_ADDED:
        case GIT_DELTA_DELETED:
        case GIT_DELTA_MODIFIED:
        case GIT_DELTA_UNTRACKED:
            pathList_->append(delta.getNewFile().getPath(), new ItemData(delta));
            break;
        default:
            break;
        }
    }

    /**
     */
    void FileWindow::update()
    {
        update(GetRootItem(), wxEmptyString, pathList_->update());
        pathList_.reset();
    }

    /**
     */
    void FileWindow::update(const wxTreeListItem& parent, 
                            const wxString& parentPath, 
                            const std::shared_ptr<PathList::Item>& item)
    {
        auto path = item->getPath();
        if(!parentPath.IsEmpty())
        {
            path.MakeRelativeTo(parentPath);
        }
        auto id = AppendItem(parent, path.GetFullPath(wxPATH_UNIX));
        SetItemData(id, item->getData());
        for(auto& child : item->getChildren())
        {
            update(id, item->getPath().GetFullPath(), child);
        }
    }

    /**
     */
    void FileWindow::onSelectionChanged(wxTreeListEvent& event)
    {
        if(auto data = static_cast<ItemData*>(GetItemData(event.GetItem())))
        {
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
