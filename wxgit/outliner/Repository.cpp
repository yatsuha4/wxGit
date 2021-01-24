/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/Menu.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/outliner/Branch.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/Repository.hpp"

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief コンストラクタ
        @param[in] dir ディレクトリ
***************************************************************************/
Repository::Repository(const wxString& dir)
  : dir_(dir)
{
}
/***********************************************************************//**
	@copydoc Node::getContextMenu
***************************************************************************/
wxMenu* Repository::getContextMenu() {
  auto menu = new Menu();
  menu->append(Menu::Id::REPOSITORY_REMOVE);
  return menu;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
wxXmlNode* Repository::serialize() const {
  auto xml = super::serialize();
  xml->AddAttribute("dir", dir_);
  return xml;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Repository::deserialize(const wxXmlNode* xml) {
  if(super::deserialize(xml)) {
    dir_ = xml->GetAttribute("dir");
    return true;
  }
  return false;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Repository::onAppend(Outliner* outliner, const wxTreeListItem& id) {
  super::onAppend(outliner, id);
  if(getName().IsEmpty()) {
    setName(wxFileName(dir_).GetName());
  }
  wxFileName dir(dir_, ".git");
  repository_ = std::make_shared<git::Repository>(dir);
  appendBranches("Local branch", GIT_BRANCH_LOCAL);
  appendBranches("Remote branch", GIT_BRANCH_REMOTE);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Repository::appendBranches(const wxString& name, git_branch_t type) {
  auto branches = repository_->getBranches(type);
  if(!branches.empty()) {
    auto folder = new Node();
    folder->setName(name);
    getOutliner()->appendNode(folder, this);
    for(auto& branch: branches) {
      getOutliner()->appendNode(new Branch(branch), folder);
    }
  }
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
