#include "wxgit/Menu.hpp"

namespace wxgit
{
    /**
     * @brief 
     */
    wxMenuItem* Menu::append(Id id)
    {
        return super::Append(static_cast<int>(id), GetText(id));
    }

    /**
     * @brief 
     */
    const char* Menu::GetText(Id id)
    {
        static const char* LABELS[] =
        {
            "Quit", 

            "Clone", 
            "Add", 
            "Remove", 

            "Status"
        };
        return LABELS[static_cast<int>(id) - static_cast<int>(Id::TOP) - 1];
    }
}
