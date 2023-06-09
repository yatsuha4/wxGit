#pragma once

namespace wxgit::command
{
    /**
     * @brief クローンコマンド
     */
    class CloneCommand
        : public wxCommand
    {
        using super = wxCommand;

    private:
        MainFrame* mainFrame_;
        wxString url_;
        wxString path_;
        git::RepositoryPtr repository_;
        outliner::RepositoryNode* node_;

    public:
        CloneCommand(MainFrame* mainFrame);
        ~CloneCommand() override = default;

        bool Do() override;
        bool Undo() override;
    };
}
