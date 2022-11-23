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
                wxEmptyString, 
                wxDefaultPosition, 
                wxDefaultSize, 
                wxTE_MULTILINE |
                wxTE_READONLY |
                wxTE_RICH)
    {
        SetFont(wxSystemSettings::GetFont(wxSYS_OEM_FIXED_FONT));
    }

    /**
     */
    void DiffWindow::clear()
    {
        SetLabel(wxEmptyString);
    }

    /**
     */
    void DiffWindow::showDelta(const git::Diff::Delta& delta)
    {
        if(!delta.isValid())
        {
            return;
        }
        Freeze();
        for(auto& hunk : delta.getHunks())
        {
            for(auto& line : hunk.getLines())
            {
                wxChar c = ' ';
                wxTextAttr attr;
                if(line.getOldLine() < 0)
                {
                    attr.SetBackgroundColour(wxColour(0xcc, 0xff, 0xcc));
                    c = '+';
                }
                else if(line.getNewLine() < 0)
                {
                    attr.SetBackgroundColour(wxColour(0xff, 0xcc, 0xcc));
                    c = '-';
                }
                SetDefaultStyle(attr);
                auto content(line.getContent());
                wxRegEx("\\s+$").Replace(&content, "");
                AppendText(wxString::Format("%-5s %-5s %c %s\n", 
                                            LineToString(line.getOldLine()), 
                                            LineToString(line.getNewLine()), 
                                            c, 
                                            content));
            }
        }
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
