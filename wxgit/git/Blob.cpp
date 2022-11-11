#include "wxgit/git/Blob.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] blob ブロブ
     * @param[in] path ファイルパス
     */
    Blob::Blob(git_blob* blob, const Path& path)
        : blob_(blob), 
          path_(path)
    {
    }

    /**
     * @brief デストラクタ
     */
    Blob::~Blob()
    {
        git_blob_free(blob_);
    }
}
