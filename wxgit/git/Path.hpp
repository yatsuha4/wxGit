#pragma once

namespace wxgit::git
{
    /**
     * @brief ファイルパス
     */
    class Path
        : private wxFileName
    {
        using super = wxFileName;

    private:
        mutable std::string string_;

    public:
        Path() = default;
        Path(const char* path);
        Path(const Path& dir, const char* name);
        Path(const wxFileName& path);
        Path(const Path& src) = default;
        ~Path() = default;

        bool isValid() const;

        const char* toUtf8() const;
        operator const char*() const;

        wxString toString(wxPathFormat format = wxPATH_NATIVE) const;
        Path getDir() const;

        bool makeRelativeTo(const Path& base);

    private:
        Path(const wxString& path);
    };
}
