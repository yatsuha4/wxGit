#pragma once

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
            wxFileName path_;
            wxClientData* data_;
            std::vector<std::shared_ptr<Item>> children_;

        public:
            Item(const wxFileName& path, wxClientData* data);
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

        std::shared_ptr<Item> append(const wxFileName& path, wxClientData* data = nullptr);
        const std::shared_ptr<Item>& update();

    private:
        std::shared_ptr<Item> takeItem(const wxFileName& path);
        std::shared_ptr<Item> findItem(const wxFileName& path) const;
        void update(std::shared_ptr<Item>& item);
    };
}
