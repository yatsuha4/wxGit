#include "wxgit/MainFrame.hpp"
#include "wxgit/ProgressDialog.hpp"
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
        : super(_("Clone"), mainFrame), 
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
                wxTextEntryDialog dialog(getMainFrame(), _("Enter URL"));
                if(dialog.ShowModal() != wxID_OK)
                {
                    return false;
                }
                url_ = dialog.GetValue();
            }
            {
                wxDirDialog dialog(getMainFrame());
                if(dialog.ShowModal() != wxID_OK)
                {
                    return false;
                }
                path_ = dialog.GetPath();
            }
            {
                ProgressDialog progress(wxString::Format(_("Cloning %s"), url_));
                repository_ = git::Repository::Clone(url_, path_, &progress);
                if(!repository_)
                {
                    return false;
                }
            }
        }
        node_ = new outliner::RepositoryNode(repository_);
        getMainFrame()->getOutliner()->appendNode(node_);
        return true;
    }

    /**
     */
    bool CloneCommand::Undo()
    {
        getMainFrame()->getOutliner()->removeNode(node_);
        node_ = nullptr;
        return true;
    }
}
