#include "wxgit/git/Remote.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] remote リモート
     */
    Remote::Remote(RepositoryPtr& repository, git_remote* remote)
        : repository_(repository_), 
          remote_(remote), 
          name_(wxString::FromUTF8(git_remote_name(remote)))
    {
    }

    /**
     * @brief リポジトリ
     */
    RepositoryPtr Remote::getRepository() const
    {
        return repository_.lock();
    }

    /**
     * @brief デストラクタ
     */
    Remote::~Remote()
    {
        git_remote_free(remote_);
    }
}
