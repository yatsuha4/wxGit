#include "wxgit/command/CommandBase.hpp"

namespace wxgit::command
{
    /**
     * @brief コンストラクタ
     * @param[in] name 名前
     * @param[in] mainFrame メインフレーム
     */
    CommandBase::CommandBase(const wxString& name, MainFrame* mainFrame)
        : super(true, name), 
          mainFrame_(mainFrame)
    {
    }
}
