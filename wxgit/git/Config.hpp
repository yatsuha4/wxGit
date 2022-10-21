#pragma once

namespace wxgit::git
{
    /**
     * @brief 設定
     */
    class Config
    {
    private:
        static const char* NAME;
        static const char* EMAIL;

        git_config* config_;

    public:
        Config(git_config* config);
        ~Config();

        wxString getName() const;
        bool setName(const wxString& name);

        wxString getEmail() const;
        bool setEmail(const wxString& email);

    private:
        wxString getString(const char* name) const;
        bool setString(const char* name, const wxString& value);
    };
}
