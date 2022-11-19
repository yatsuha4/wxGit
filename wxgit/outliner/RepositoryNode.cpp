#include "wxgit/Id.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/outliner/BranchNode.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/RemoteNode.hpp"
#include "wxgit/outliner/RepositoryNode.hpp"

namespace wxgit::outliner
{
    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     */
    RepositoryNode::RepositoryNode(const git::RepositoryPtr& repository)
        : super(repository->getName()), 
          repository_(repository), 
          branch_(nullptr)
    {
    }

    /**
     * @copydoc Node::getContextMenu
     */
    wxMenu* RepositoryNode::getContextMenu()
    {
        auto menu = new wxMenu();
        menu->Append(ID_REPOSITORY_CLOSE, _("Close repository"));
        return menu;
    }

    /**
     * @copydoc Serializable::serialize
     */
    wxXmlNode* RepositoryNode::serialize() const
    {
        auto xml = super::serialize();
        xml->AddAttribute("dir", repository_->getWorkDir().toString());
        return xml;
    }

    /**
     * @copydoc Serializable::deserialize
     */
    bool RepositoryNode::deserialize(const wxXmlNode* xml)
    {
        if(super::deserialize(xml))
        {
            repository_ = git::Repository::Open(git::Path(xml->GetAttribute("dir")));
            return true;
        }
        return false;
    }

    /**
     */
    void RepositoryNode::onAppend(Outliner* outliner)
    {
        super::onAppend(outliner);
        if(repository_)
        {
            branch_ = new Node(_("Branch"));
            getOutliner()->appendNode(branch_, this);
            for(auto& branch : repository_->takeLocalBranches())
            {
                getOutliner()->appendNode(new BranchNode(branch), branch_);
            }
            appendRemotes();
        }
    }

    /**
     * @brief リモートを追加する
     */
    void RepositoryNode::appendRemotes()
    {
        auto remotes = repository_->takeRemotes();
        if(!remotes.empty())
        {
            auto folder = new Node(_("Remote"));
            getOutliner()->appendNode(folder, this);
            for(auto& remote : remotes)
            {
                getOutliner()->appendNode(new RemoteNode(remote), folder);
            }
        }
    }
}
