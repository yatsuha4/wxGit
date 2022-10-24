#include "wxgit/DiffWindow.hpp"
#include "wxgit/MainFrame.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] mainFrame メインフレーム
     */
    DiffWindow::DiffWindow(MainFrame* mainFrame)
        : super(mainFrame, wxID_ANY)
    {
    }
}
