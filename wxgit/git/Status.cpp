#include "wxgit/git/Status.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     * @param[in] list リスト
     */
    Status::Status(const RepositoryPtr& repository, git_status_list* list)
        : RepositoryReference(repository), 
          list_(list)
    {
        for(size_t i = 0, n = git_status_list_entrycount(list_); i < n; ++i)
        {
            auto entry = git_status_byindex(list_, i);
            switch(entry->status)
            {
            case GIT_STATUS_IGNORED:
                break;
            default:
                entries_.emplace_back(entry);
                break;
            }
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
     * @brief コンストラクタ
     */
    Status::Entry::Entry(const git_status_entry* entry)
        : status_(entry->status), 
          headToIndex_(entry->head_to_index), 
          indexToWorkdir_(entry->index_to_workdir)
    {
    }
}
