#pragma once

#include "wxgit/git/RepositoryReference.hpp"

namespace wxgit::git
{
    /**
     * @brief インデックス
     */
    class Index
        : public RepositoryReference
    {
    private:
        git_index* index_;

    public:
        Index(const RepositoryPtr& repository, git_index* index);
        ~Index();

        bool add(const Path& path);
        bool cancel(const Path& path);
        bool remove(const Path& path, git_index_stage_t stage);
        bool write();

        TreePtr writeTree() const;

    private:
        static int UpdateCancel(const char* path, const char* pathspec, void* payload);
    };
}
