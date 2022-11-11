#pragma once

namespace wxgit::git
{
    /**
     * @brief インデックス
     */
    class Index
    {
    private:
        std::weak_ptr<Repository> repository_;
        git_index* index_;

    public:
        Index(const RepositoryPtr& repository, git_index* index);
        ~Index();

        RepositoryPtr getRepository() const;

        bool add(const Path& path);
        bool cancel(const Path& path);
        bool remove(const Path& path, git_index_stage_t stage);
        bool write();

    private:
        static int UpdateCancel(const char* path, const char* pathspec, void* payload);
    };
}
