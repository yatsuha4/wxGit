#pragma once

namespace wxgit::command
{
    /**
     * @brief コマンド基底クラス
     */
    class CommandBase
        : public wxCommand
    {
        using super = wxCommand;

    private:
        MainFrame* mainFrame_;

    public:
        CommandBase(const wxString& name, MainFrame* mainFrame);
        ~CommandBase() override = default;

        WXEDITOR_GETTER(MainFrame, mainFrame_);
    };
}
