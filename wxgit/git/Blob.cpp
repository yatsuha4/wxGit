#include "wxgit/git/Blob.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] blob ブロブ
     */
    Blob::Blob(git_blob* blob)
        : blob_(blob)
    {
    }

    /**
     * @brief デストラクタ
     */
    Blob::~Blob()
    {
        git_blob_free(blob_);
    }

    /**
     */
    BlobPtr Blob::Lookup(git_repository* repository, const git_oid* id)
    {
        git_blob* blob;
        if(git_blob_lookup(&blob, repository, id) == GIT_OK)
        {
            return std::make_shared<Blob>(blob);
        }
        return nullptr;
    }

    /**
     */
    BlobPtr Blob::CreateFromWorkdir(git_repository* repository, const Path& path)
    {
        git_oid id;
        if(git_blob_create_from_workdir(&id, repository, path) == GIT_OK)
        {
            return Lookup(repository, &id);
        }
        return nullptr;
    }
}
