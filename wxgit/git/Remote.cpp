#include "wxgit/git/Refspec.hpp"
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
        for(size_t i = 0, n = git_remote_refspec_count(remote); i < n; ++i)
        {
            refspecs_.push_back(std::make_shared<Refspec>(git_remote_get_refspec(remote_, i)));
        }
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
