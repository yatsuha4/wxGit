#include "wxgit/git/Config.hpp"

namespace wxgit::git
{
    const char* Config::NAME = "user.name";
    const char* Config::EMAIL = "user.email";

    /**
     * @brief コンストラクタ
     * @param[in] config libgit2の設定データのポインタ
     */
    Config::Config(git_config* config)
        : config_(config)
    {
        wxASSERT(config);
    }

    /**
     * @brief デストラクタ
     */
    Config::~Config()
    {
        git_config_free(config_);
    }

    /**
     */
    wxString Config::getName() const
    {
        return getString(NAME);
    }

    /**
     */
    bool Config::setName(const wxString& name)
    {
        return setString(NAME, name);
    }

    /**
     */
    wxString Config::getEmail() const
    {
        return getString(EMAIL);
    }

    /**
     */
    bool Config::setEmail(const wxString& email)
    {
        return setString(EMAIL, email);
    }

    /**
     */
    wxString Config::getString(const char* name) const
    {
        const char* value;
        if(git_config_get_string(&value, config_, name) == GIT_OK)
        {
            return wxString::FromUTF8(value);
        }
        return wxString();
    }

    /**
     */
    bool Config::setString(const char* name, const wxString& value)
    {
        return git_config_set_string(config_, name, value.ToUTF8()) == GIT_OK;
    }
}
