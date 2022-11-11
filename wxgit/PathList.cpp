#include "wxgit/PathList.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] path パス
     * @param[in] data データ
     */
    PathList::Item::Item(const wxFileName& path, wxClientData* data)
        : path_(path), 
          data_(data)
    {
    }

    /**
     * @brief コンストラクタ
     */
    PathList::PathList()
        : root_(std::make_shared<Item>(wxFileName(), nullptr))
    {
    }

    /**
     * @brief ファイルパスを追加する
     * @param[in] path 追加するファイルパス
     * @param[in] data データ
     * @return 追加した要素
     */
    std::shared_ptr<PathList::Item> PathList::append(const wxFileName& path, 
                                                     wxClientData* data)
    {
        auto dir = path.GetPath();
        auto parent = dir.IsEmpty() ? root_ : takeItem(wxFileName(dir));
        auto item = std::make_shared<Item>(path, data);
        parent->getChildren().push_back(item);
        items_.emplace(path.GetFullPath(), item);
        return item;
    }

    /**
     */
    const std::shared_ptr<PathList::Item>& PathList::update()
    {
        for(auto& child : root_->getChildren())
        {
            update(child);
        }
        return root_;
    }

    /**
     */
    std::shared_ptr<PathList::Item> PathList::takeItem(const wxFileName& path)
    {
        auto iter = items_.find(path.GetFullPath());
        if(iter != items_.end())
        {
            return iter->second;
        }
        return append(path);
    }

    /**
     */
    void PathList::update(std::shared_ptr<Item>& item)
    {
        if(item->getChildren().size() == 1)
        {
            item = item->getChildren().front();
            update(item);
        }
        for(auto& child : item->getChildren())
        {
            update(child);
        }
    }
}
