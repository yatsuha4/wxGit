#include "wxgit/PathList.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] path パス
     */
    PathList::Item::Item(const wxFileName& path)
        : path_(path), 
          data_(nullptr)
    {
    }

    /**
     */
    PathList::PathList()
        : root_(std::make_shared<Item>(wxFileName()))
    {
    }

    /**
     */
    void PathList::append(const wxFileName& path, wxClientData* data)
    {
        takeItem(path)->setData(data);
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
        auto name = path.GetFullPath();
        auto iter = items_.find(name);
        if(iter != items_.end())
        {
            return iter->second;
        }
        auto dir = path.GetPath();
        auto parent = dir.IsEmpty() ? root_ : takeItem(wxFileName(dir));
        auto item = std::make_shared<Item>(path);
        parent->getChildren().push_back(item);
        items_.emplace(name, item);
        return item;
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
