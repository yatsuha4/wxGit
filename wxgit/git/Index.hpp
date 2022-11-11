#pragma once

namespace wxgit::git
{
    /**
     * @brief インデックス
     */
    class Index
    {
    private:
        git_index* index_;

    public:
        Index(git_index* index);
        ~Index();

        bool addByPath(const wxFileName& path);
        bool removeByPath(const wxFileName& path);
        bool write();
    };
}
