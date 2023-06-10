#include "wxgit/MainFrame.hpp"
#include "wxgit/command/CloseRepositoryCommand.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/RepositoryNode.hpp"

namespace wxgit::command
{
    /**
     * @brief コンストラクタ
     * @param[in] mainFrame メインフレーム
     * @param[in] node 削除するノード
     */
    CloseRepositoryCommand::CloseRepositoryCommand(MainFrame* mainFrame, 
                                                   outliner::RepositoryNode* node)
        : super(wxString::Format(_("Remove %s"), node->getName()), mainFrame), 
          node_(node), 
          repository_(node->getRepository())
    {
    }

    /**
     */
    bool CloseRepositoryCommand::Do()
    {
        getMainFrame()->closeRepository(node_);
        node_ = nullptr;
        return true;
    }

    /**
     */
    bool CloseRepositoryCommand::Undo()
    {
        node_ = getMainFrame()->openRepository(repository_);
        return true;
    }
}
