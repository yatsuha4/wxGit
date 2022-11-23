#include "wxgit/CommitWindow.hpp"
#include "wxgit/DiffWindow.hpp"
#include "wxgit/FileWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/git/Index.hpp"
#include "wxgit/git/Repository.hpp"

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
        if(!status->getEntries().empty())
        {
            for(auto& entry : status->getEntries())
            {
                appendEntry(entry);
            }
            update();
        }
        updateCheckFiles();
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
        checkFiles_.clear();
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
     * @brief ステータスのエントリを追加する
     * @param[in] entry ステータスのエントリ
     */
    void FileWindow::appendEntry(const git::Status::Entry& entry)
    {
        auto item = new EntryItem(entry);
        pathList_->append(item->getPath(), item);
    }

    /**
     */
    void FileWindow::update()
    {
        update(GetRootItem(), git::Path(), pathList_->update());
        pathList_.reset();
    }

    /**
     */
    bool FileWindow::update(const wxTreeListItem& parent, 
                            const git::Path& parentPath, 
                            const std::shared_ptr<PathList::Item>& item)
    {
        auto path = item->getPath();
        if(!path.isValid())
        {
            path = getRepository()->getWorkDir();
        }
        else if(parentPath.isValid())
        {
            path.makeRelativeTo(parentPath);
        }
        auto id = AppendItem(parent, path.toString(wxPATH_UNIX));
        SetItemData(id, item->getData());
        bool check = true;
        for(auto& child : item->getChildren())
        {
            check = (update(id, item->getPath(), child) && check);
        }
        if(auto data = dynamic_cast<EntryItem*>(item->getData()))
        {
            auto state = data->getState();
            CheckItem(id, state);
            check = (check && (state == wxCHK_CHECKED));
        }
        else
        {
            CheckItem(id, (check ? wxCHK_CHECKED : wxCHK_UNCHECKED));
        }
        Expand(id);
        return check;
    }

    /**
     * @brief チェックされたファイルのリストを更新する
     */
    void FileWindow::updateCheckFiles()
    {
        checkFiles_.clear();
        for(auto item = GetFirstItem(); item.IsOk(); item = GetNextItem(item))
        {
            if(auto data = dynamic_cast<EntryItem*>(GetItemData(item)))
            {
                if(GetCheckedState(item) != wxCHK_UNCHECKED)
                {
                    checkFiles_.push_back(data->getPath());
                }
            }
        }
        getMainFrame()->getCommitWindow()->setCanCommit(!checkFiles_.empty());
    }

    /**
     */
    void FileWindow::onSelectionChanged(wxTreeListEvent& event)
    {
        auto diffWindow = getMainFrame()->getDiffWindow();
        diffWindow->clear();
        if(auto data = GetItemData(event.GetItem()))
        {
            if(auto delta = dynamic_cast<ItemData*>(data))
            {
                diffWindow->showDelta(delta->getDelta());
            }
            else if(auto entry = dynamic_cast<EntryItem*>(data))
            {
                diffWindow->showDelta(entry->getEntry().getHeadToIndex());
                diffWindow->showDelta(entry->getEntry().getIndexToWorkdir());
            }
        }
    }

    /**
     */
    void FileWindow::onItemChecked(wxTreeListEvent& event)
    {
        onCheckItem(event.GetItem(), GetCheckedState(event.GetItem()));
        updateCheckFiles();
    }

    /**
     */
    void FileWindow::onCheckItem(wxTreeListItem item, wxCheckBoxState state)
    {
        if(auto data = dynamic_cast<EntryItem*>(GetItemData(item)))
        {
            if(state == wxCHK_UNCHECKED)
            {
                CheckItem(item, data->getState());
            }
        }
        else
        {
            for(auto child = GetFirstChild(item);
                child.IsOk();
                child = GetNextSibling(child))
            {
                CheckItem(child, state);
                onCheckItem(child, state);
            }
        }
    }

    /**
     */
    FileWindow::ItemData::ItemData(const git::Diff::Delta& delta)
        : delta_(delta)
    {
    }

    /**
     */
    FileWindow::EntryItem::EntryItem(const git::Status::Entry& entry)
        : entry_(entry)
    {
        wxASSERT(entry_.getHeadToIndex().isValid() ||
                 entry_.getIndexToWorkdir().isValid());
    }

    /**
     */
    git::Path FileWindow::EntryItem::getPath() const
    {
        return (entry_.getHeadToIndex().isValid()
                ? entry_.getHeadToIndex()
                : entry_.getIndexToWorkdir()).getNewFile().getPath();
    }

    /**
     */
    wxCheckBoxState FileWindow::EntryItem::getState() const
    {
        return entry_.getHeadToIndex().isValid()
            ? wxCHK_UNDETERMINED
            : wxCHK_UNCHECKED;
    }
}
