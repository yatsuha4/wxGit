namespace wxgit::git
{
    /**
     * @brief ファイルパス
     */
    class Path
        : private wxFileName
    {
        using super = wxFileName;

    public:
        Path() = default;
        Path(const char* path);
        Path(const Path& src) = default;
        ~Path() = default;

        operator const char*() const;
    };
}
