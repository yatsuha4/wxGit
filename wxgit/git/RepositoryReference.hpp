#pragma once

namespace wxgit::git
{
    /**
     * @brief リポジトリ参照
     */
    class RepositoryReference
    {
    private:
        std::weak_ptr<Repository> repository_;

    public:
        RepositoryReference(const RepositoryPtr& repository);
        ~RepositoryReference() = default;

        RepositoryPtr getRepository() const;
    };
}
