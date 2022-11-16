#include "wxgit/Menu.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/outliner/BranchNode.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/RemoteNode.hpp"
#include "wxgit/outliner/Repository.hpp"

namespace wxgit::outliner
{
    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     */
    Repository::Repository(const git::RepositoryPtr& repository)
        : repository_(repository)
    {
    }

    /**
     * @copydoc Node::getContextMenu
     */
    wxMenu* Repository::getContextMenu()
    {
        auto menu = new Menu();
        menu->append(Menu::Id::REPOSITORY_REMOVE);
        return menu;
    }

    /**
     * @copydoc Serializable::serialize
     */
    wxXmlNode* Repository::serialize() const
    {
        auto xml = super::serialize();
        xml->AddAttribute("dir", repository_->getWorkDir().toString());
        return xml;
    }

    /**
     * @copydoc Serializable::deserialize
     */
    bool Repository::deserialize(const wxXmlNode* xml)
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
    void Repository::onAppend(Outliner* outliner)
    {
        super::onAppend(outliner);
        if(repository_)
        {
            appendBranches("Local branch", repository_->takeLocalBranches());
            appendBranches("Remote branch", repository_->takeRemoteBranches());
            appendRemotes();
        }
    }

    /**
     * @brief 
     */
    void Repository::appendBranches(const wxString& name, 
                                    const std::vector<git::ReferencePtr>& branches)
    {
        if(!branches.empty())
        {
            auto folder = new Node();
            folder->setName(name);
            getOutliner()->appendNode(folder, this);
            for(auto& branch: branches)
            {
                getOutliner()->appendNode(new BranchNode(branch), folder);
            }
        }
    }

    /**
     * @brief リモートを追加する
     */
    void Repository::appendRemotes()
    {
        auto remotes = repository_->takeRemotes();
        if(!remotes.empty())
        {
            auto folder = new Node();
            folder->setName("Remote");
            getOutliner()->appendNode(folder, this);
            for(auto& remote : remotes)
            {
                getOutliner()->appendNode(new RemoteNode(remote), folder);
            }
        }
    }
}
