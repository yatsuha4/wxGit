#pragma once

#include "wxgit/command/CommandBase.hpp"

namespace wxgit::command
{
    /**
     * @brief クローンコマンド
     */
    class CloneCommand
        : public CommandBase
    {
        using super = CommandBase;

    private:
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
