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
        Path path_;

    public:
        Blob(git_blob* blob, const Path& path);
        ~Blob();

        WXEDITOR_GETTER(Path, path_);
    };
}
