#include "wxgit/git/Status.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     * @param[in] list リスト
     */
    Status::Status(const RepositoryPtr& repository, git_status_list* list)
        : repository_(repository), 
          list_(list)
    {
        for(size_t i = 0, n = git_status_list_entrycount(list_); i < n; ++i)
        {
            entries_.emplace_back(git_status_byindex(list_, i));
        }
    }

    /**
     * @brief デストラクタ
     */
    Status::~Status()
    {
        git_status_list_free(list_);
    }

    /**
     */
    RepositoryPtr Status::getRepository() const
    {
        return repository_.lock();
    }

    /**
     * @brief コンストラクタ
     */
    Status::Entry::Entry(const git_status_entry* entry)
        : status_(entry->status), 
          headToIndex_(entry->head_to_index), 
          indexToWorkdir_(entry->index_to_workdir)
    {
    }
}
