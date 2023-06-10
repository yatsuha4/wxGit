#pragma once

#include "wxgit/command/CommandBase.hpp"

namespace wxgit::command
{
    /**
     * @brief ノード削除コマンド
     */
    class CloseRepositoryCommand
        : public CommandBase
    {
        using super = CommandBase;

    private:
        outliner::RepositoryNode* node_;
        git::RepositoryPtr repository_;

    public:
        CloseRepositoryCommand(MainFrame* mainFrame, outliner::RepositoryNode* node);
        ~CloseRepositoryCommand() override = default;

        bool Do() override;
        bool Undo() override;
    };
}
