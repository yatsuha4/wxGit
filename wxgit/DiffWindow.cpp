#include "wxgit/DiffWindow.hpp"
#include "wxgit/MainFrame.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] mainFrame メインフレーム
     */
    DiffWindow::DiffWindow(MainFrame* mainFrame)
        : super(mainFrame, 
                wxID_ANY, 
                wxDefaultPosition, 
                wxDefaultSize, 
                wxLC_REPORT), 
          Window(mainFrame)
    {
        InsertColumn(Column::OLD_LINE, wxT("OldLine"));
        InsertColumn(Column::NEW_LINE, wxT("NewLine"));
        InsertColumn(Column::CONTENT, wxT("Content"));
        SetFont(wxSystemSettings::GetFont(wxSYS_OEM_FIXED_FONT));
    }

    /**
     */
    void DiffWindow::showDelta(const git::Diff::Delta& delta)
    {
        Freeze();
        DeleteAllItems();
        long index = 0;
        for(auto& hunk : delta.getHunks())
        {
            for(auto& line : hunk.getLines())
            {
                InsertItem(index, LineToString(line.getOldLine()));
                SetItem(index, Column::NEW_LINE, LineToString(line.getNewLine()));
                SetItem(index, Column::CONTENT, line.getContent());
                if(line.getOldLine() < 0)
                {
                    SetItemBackgroundColour(index, wxColour(0xcc, 0xff, 0xcc));
                }
                else if(line.getNewLine() < 0)
                {
                    SetItemBackgroundColour(index, wxColour(0xff, 0xcc, 0xcc));
                }
                ++index;
            }
        }
        SetColumnWidth(Column::OLD_LINE, wxLIST_AUTOSIZE);
        SetColumnWidth(Column::NEW_LINE, wxLIST_AUTOSIZE);
        SetColumnWidth(Column::CONTENT, wxLIST_AUTOSIZE);
        Thaw();
    }

    /**
     * @brief 行番号を文字列に変換する
     * @param[in] line 行番号
     * @return 行番号の文字列
     */
    wxString DiffWindow::LineToString(int line)
    {
        if(line >= 0)
        {
            return wxString::Format("%d", line);
        }
        return wxEmptyString;
    }
}
