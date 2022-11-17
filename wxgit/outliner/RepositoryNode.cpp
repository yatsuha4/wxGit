﻿#include "wxgit/Menu.hpp"
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
        : repository_(repository)
    {
        setName(repository_->getName());
    }

    /**
     * @copydoc Node::getContextMenu
     */
    wxMenu* RepositoryNode::getContextMenu()
    {
        auto menu = new Menu();
        menu->append(Menu::Id::REPOSITORY_CLOSE);
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
            appendBranches("Local branch", repository_->takeLocalBranches());
            appendBranches("Remote branch", repository_->takeRemoteBranches());
            appendRemotes();
        }
    }

    /**
     * @brief 
     */
    void RepositoryNode::appendBranches(const wxString& name, 
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
    void RepositoryNode::appendRemotes()
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
