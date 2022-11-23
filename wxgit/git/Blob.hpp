#pragma once

#include "wxgit/git/Path.hpp"

namespace wxgit::git
{
    /**
     * @brief ブロブ
     */
    class Blob
    {
    private:
        git_blob* blob_;

    public:
        Blob(git_blob* blob);
        ~Blob();

        WXEDITOR_GETTER(Blob, blob_);

        static BlobPtr Lookup(git_repository* repository, const git_oid* id);
        static BlobPtr CreateFromWorkdir(git_repository* repository, const Path& path);
    };
}
