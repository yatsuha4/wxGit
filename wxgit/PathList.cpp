#include "wxgit/PathList.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] path パス
     * @param[in] data データ
     */
    PathList::Item::Item(const git::Path& path, wxClientData* data)
        : path_(path), 
          data_(data)
    {
    }

    /**
     * @brief コンストラクタ
     */
    PathList::PathList()
        : root_(std::make_shared<Item>(git::Path(), nullptr))
    {
    }

    /**
     * @brief ファイルパスを追加する
     * @param[in] path 追加するファイルパス
     * @param[in] data データ
     * @return 追加した要素
     */
    std::shared_ptr<PathList::Item> PathList::append(const git::Path& path, 
                                                     wxClientData* data)
    {
        auto dir = path.getDir();
        auto parent = dir.isValid() ? takeItem(dir) : root_;
        auto item = std::make_shared<Item>(path, data);
        parent->getChildren().push_back(item);
        items_.emplace(path.toString(), item);
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
    std::shared_ptr<PathList::Item> PathList::takeItem(const git::Path& path)
    {
        auto iter = items_.find(path.toString());
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
