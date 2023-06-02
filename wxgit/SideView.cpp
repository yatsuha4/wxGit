#include "wxgit/FileWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/SideView.hpp"
#include "wxgit/outliner/Outliner.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] parent 親ウィンドウ
     */
    SideView::SideView(wxWindow* parent)
        : super(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                wxAUI_NB_TOP |
                wxAUI_NB_TAB_SPLIT |
                wxAUI_NB_SCROLL_BUTTONS), 
          outliner_(new outliner::Outliner(this)), 
          fileWindow_(new FileWindow(this))
    {
        AddPage(outliner_, _("Outliner"));
        AddPage(fileWindow_, _("File"));
    }

    /**
     * @brief ウィンドウを表示する
     * @param[in] window 表示するウィンドウ
     * @return 表示したとき真
     */
    bool SideView::show(wxWindow* window)
    {
        auto index = GetPageIndex(window);
        if(index == wxNOT_FOUND)
        {
            return false;
        }
        ChangeSelection(index);
        return true;
    }
}
