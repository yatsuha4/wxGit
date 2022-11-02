#include "wxgit/Menu.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/outliner/Branch.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/RemoteNode.hpp"
#include "wxgit/outliner/Repository.hpp"

namespace wxgit::outliner
{
    /**
     * @brief コンストラクタ
     * @param[in] dir ディレクトリ
     */
    Repository::Repository(const wxString& dir)
        : dir_(dir)
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
        xml->AddAttribute("dir", dir_);
        return xml;
    }

    /**
     * @copydoc Serializable::deserialize
     */
    bool Repository::deserialize(const wxXmlNode* xml)
    {
        if(super::deserialize(xml))
        {
            dir_ = xml->GetAttribute("dir");
            return true;
        }
        return false;
    }

    /**
     */
    void Repository::onAppend(Outliner* outliner)
    {
        super::onAppend(outliner);
        if(getName().IsEmpty())
        {
            setName(wxFileName(dir_).GetName());
        }
        wxFileName dir(dir_, ".git");
        repository_ = std::make_shared<git::Repository>(dir);
        appendBranches("Local branch", GIT_BRANCH_LOCAL);
        appendBranches("Remote branch", GIT_BRANCH_REMOTE);
        appendRemotes();
    }

    /**
     * @brief 
     */
    void Repository::appendBranches(const wxString& name, git_branch_t type)
    {
        auto branches = repository_->getBranches(type);
        if(!branches.empty())
        {
            auto folder = new Node();
            folder->setName(name);
            getOutliner()->appendNode(folder, this);
            for(auto& branch: branches)
            {
                getOutliner()->appendNode(new Branch(branch), folder);
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
