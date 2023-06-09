#include "wxgit/MainFrame.hpp"
#include "wxgit/command/CloneCommand.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/RepositoryNode.hpp"

namespace wxgit::command
{
    /**
     * @brief コンストラクタ
     */
    CloneCommand::CloneCommand(MainFrame* mainFrame)
        : super(true, _("Clone")), 
          mainFrame_(mainFrame), 
          node_(nullptr)
    {
    }

    /**
     * @brief 実行
     */
    bool CloneCommand::Do()
    {
        if(!repository_)
        {
            {
                wxTextEntryDialog dialog(mainFrame_, _("Enter URL"));
                if(dialog.ShowModal() != wxID_OK)
                {
                    return false;
                }
                url_ = dialog.GetValue();
            }
            {
                wxDirDialog dialog(mainFrame_);
                if(dialog.ShowModal() != wxID_OK)
                {
                    return false;
                }
                path_ = dialog.GetPath();
            }
            repository_ = git::Repository::Clone(url_, path_);
            if(!repository_)
            {
                return false;
            }
        }
        node_ = new outliner::RepositoryNode(repository_);
        mainFrame_->getOutliner()->appendNode(node_);
        return true;
    }

    /**
     */
    bool CloneCommand::Undo()
    {
        mainFrame_->getOutliner()->removeNode(node_);
        node_ = nullptr;
        return true;
    }
}
