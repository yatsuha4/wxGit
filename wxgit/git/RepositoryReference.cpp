#include "wxgit/git/RepositoryReference.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     */
    RepositoryReference::RepositoryReference(const RepositoryPtr& repository)
        : repository_(repository)
    {
    }

    /**
     * @brief リポジトリを取得する
     * @return リポジトリ
     */
    RepositoryPtr RepositoryReference::getRepository() const
    {
        return repository_.lock();
    }
}
