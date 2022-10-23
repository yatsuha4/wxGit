#pragma once

namespace wxgit::git
{
    /**
     * @brief ブロブ
     */
    class Blob
    {
    private:
        git_blob* blob_;
        wxFileName path_;

    public:
        Blob(git_blob* blob, const wxFileName& path);
        ~Blob();

        WXEDITOR_GETTER(Path, path_);
    };
}
