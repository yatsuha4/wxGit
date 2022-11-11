#include "wxgit/git/Path.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] path パス
     */
    Path::Path(const char* path)
        : super(wxString::FromUTF8(path), wxPATH_UNIX)
    {
    }

    /**
     */
    Path::operator const char*() const
    {
        return GetFullPath(wxPATH_UNIX).ToUTF8();
    }
}
