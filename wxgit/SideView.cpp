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
     * @brief タブを表示する
     * @param[in] tab 表示するタブ
     */
    void SideView::show(Tab tab)
    {
        ChangeSelection(tab);
    }
}
