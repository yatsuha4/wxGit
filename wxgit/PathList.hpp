#pragma once

#include "wxgit/git/Path.hpp"

namespace wxgit
{
    /**
     * @brief パスリスト
     */
    class PathList
    {
    public:
        class Item
        {
        private:
            git::Path path_;
            wxClientData* data_;
            std::vector<std::shared_ptr<Item>> children_;

        public:
            Item(const git::Path& path, wxClientData* data);
            ~Item() = default;

            WXEDITOR_GETTER(Path, path_);
            WXEDITOR_GETTER(Data, data_);
            WXEDITOR_ACCESSOR(Children, children_);
        };

    private:
        std::shared_ptr<Item> root_;
        std::multimap<wxString, std::shared_ptr<Item>> items_;

    public:
        PathList();
        ~PathList() = default;

        std::shared_ptr<Item> append(const git::Path& path, wxClientData* data = nullptr);
        const std::shared_ptr<Item>& update();

    private:
        std::shared_ptr<Item> takeItem(const git::Path& path);
        std::shared_ptr<Item> findItem(const git::Path& path) const;
        void update(std::shared_ptr<Item>& item);
    };
}
