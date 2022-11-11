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
     * @brief コンストラクタ
     * @param[in] dir ディレクトリ
     * @param[in] name ファイル名
     */
    Path::Path(const Path& dir, const char* name)
        : super(dir.toUtf8(), wxString::FromUTF8(name), wxPATH_UNIX)
    {
    }

    /**
     */
    bool Path::isValid() const
    {
        return super::IsOk();
    }

    /**
     */
    const char* Path::toUtf8() const
    {
        string_ = GetFullPath(wxPATH_UNIX).utf8_string();
        return string_.c_str();
    }

    /**
     */
    Path::operator const char*() const
    {
        return toUtf8();
    }

    /**
     */
    wxString Path::toString(wxPathFormat format) const
    {
        return GetFullPath(format);
    }

    /**
     */
    Path Path::getDir() const
    {
        return Path(GetPath());
    }

    /**
     */
    bool Path::makeRelativeTo(const Path& base)
    {
        return super::MakeRelativeTo(base.toString());
    }

    /**
     */
    Path::Path(const wxString& path)
        : super(path)
    {
    }
}
