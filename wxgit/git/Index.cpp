#include "wxgit/git/Index.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] index インデックス
     */
    Index::Index(git_index* index)
        : index_(index)
    {
    }

    /**
     * @brief デストラクタ
     */
    Index::~Index()
    {
        git_index_free(index_);
    }
}
