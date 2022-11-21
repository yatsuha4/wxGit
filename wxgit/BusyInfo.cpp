#include "wxgit/BusyInfo.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     */
    BusyInfo::BusyInfo(const wxString& message, wxWindow* parent)
        : super(message, parent)
    {
    }
}
