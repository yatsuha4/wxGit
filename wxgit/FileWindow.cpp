#include "wxgit/DiffWindow.hpp"
#include "wxgit/FileWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/git/Index.hpp"
#include "wxgit/git/Repository.hpp"
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
        Bind(wxEVT_TREELIST_ITEM_CHECKED, &FileWindow::onItemChecked, this);
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
            appendDelta(delta, wxCHK_UNCHECKED);
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
        if(!status->getEntries().empty())
        {
            for(auto& entry : status->getEntries())
            {
                if(entry.getHeadToIndex().isValid())
                {
                    appendDelta(entry.getHeadToIndex(), 
                                entry.getIndexToWorkdir().isValid()
                                ? wxCHK_UNDETERMINED
                                : wxCHK_CHECKED);
                }
                else if(entry.getIndexToWorkdir().isValid())
                {
                    appendDelta(entry.getIndexToWorkdir(), wxCHK_UNCHECKED);
                }
            }
            update();
        }
    }

    /**
     * @brief リポジトリを取得する
     * @return リポジトリ
     */
    git::RepositoryPtr FileWindow::getRepository() const
    {
        return diff_
            ? diff_->getRepository()
            : status_
            ? status_->getRepository()
            : nullptr;
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
     * @param[in] state チェック状態
     */
    void FileWindow::appendDelta(const git::Diff::Delta& delta, wxCheckBoxState state)
    {
        switch(delta.getStatus())
        {
        case GIT_DELTA_ADDED:
        case GIT_DELTA_DELETED:
        case GIT_DELTA_MODIFIED:
        case GIT_DELTA_UNTRACKED:
            pathList_->append(delta.getNewFile().getPath(), new ItemData(delta, state));
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
    bool FileWindow::update(const wxTreeListItem& parent, 
                            const wxString& parentPath, 
                            const std::shared_ptr<PathList::Item>& item)
    {
        auto path = item->getPath();
        if(!path.IsOk())
        {
            path.Assign(getRepository()->getWorkDir());
        }
        else if(!parentPath.IsEmpty())
        {
            path.MakeRelativeTo(parentPath);
        }
        auto id = AppendItem(parent, path.GetFullPath(wxPATH_UNIX));
        SetItemData(id, item->getData());
        bool check = true;
        for(auto& child : item->getChildren())
        {
            check = (update(id, item->getPath().GetFullPath(), child) && check);
        }
        if(auto data = dynamic_cast<ItemData*>(item->getData()))
        {
            CheckItem(id, data->getState());
            check = (check && (data->getState() == wxCHK_CHECKED));
        }
        else
        {
            CheckItem(id, (check ? wxCHK_CHECKED : wxCHK_UNCHECKED));
        }
        Expand(id);
        return check;
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
    void FileWindow::onItemChecked(wxTreeListEvent& event)
    {
        onCheckItem(event.GetItem(), 
                    GetCheckedState(event.GetItem()), 
                    event.GetOldCheckedState());
        status_->getRepository()->takeIndex()->write();
    }

    /**
     */
    void FileWindow::onCheckItem(wxTreeListItem item, 
                                 wxCheckBoxState state, 
                                 wxCheckBoxState oldState)
    {
        CheckItem(item, state);
        if(auto data = static_cast<ItemData*>(GetItemData(item)))
        {
            if(state != oldState)
            {
                switch(state)
                {
                case wxCHK_CHECKED:
                    addDelta(data->getDelta());
                    break;
                case wxCHK_UNCHECKED:
                    removeDelta(data->getDelta());
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            for(auto child = GetFirstChild(item);
                child.IsOk();
                child = GetNextSibling(child))
            {
                onCheckItem(child, state, GetCheckedState(child));
            }
        }
    }

    /**
     */
    void FileWindow::addDelta(const git::Diff::Delta& delta)
    {
        switch(delta.getStatus())
        {
        case GIT_DELTA_MODIFIED:
        case GIT_DELTA_UNTRACKED:
            status_->getRepository()->takeIndex()->addByPath(delta.getNewFile().getPath());
            break;
        default:
            break;
        }
    }

    /**
     */
    void FileWindow::removeDelta(const git::Diff::Delta& delta)
    {
        switch(delta.getStatus())
        {
        case GIT_DELTA_MODIFIED:
        case GIT_DELTA_UNTRACKED:
            status_->getRepository()->takeIndex()->removeByPath(delta.getNewFile().getPath());
            break;
        default:
            break;
        }
    }

    /**
     */
    FileWindow::ItemData::ItemData(const git::Diff::Delta& delta, wxCheckBoxState state)
        : delta_(delta), 
          state_(state)
    {
    }
}
