#pragma once

namespace wxgit
{
    /**
     * @brief メニュー
     */
    class Menu
        : public wxMenu
    {
        using super = wxMenu;

    public:
        enum class Id {
            TOP = wxID_HIGHEST, 

            FILE_QUIT, 

            REPOSITORY_CLONE, 
            REPOSITORY_OPEN, 
            REPOSITORY_INIT, 
            REPOSITORY_CLOSE, 

            WORK_STATUS, 

            BOTTOM
        };

    public:
        Menu() = default;
        ~Menu() override = default;

        wxMenuItem* append(Id id);

        static const char* GetText(Id id);
    };
}
