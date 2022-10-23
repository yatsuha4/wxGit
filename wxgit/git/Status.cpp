#include "wxgit/git/Status.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] list リスト
     */
    Status::Status(git_status_list* list)
        : list_(list)
    {
    }

    /**
     * @brief デストラクタ
     */
    Status::~Status()
    {
        git_status_list_free(list_);
    }
}
