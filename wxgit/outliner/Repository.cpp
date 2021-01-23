/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/git/Repository.hpp"
#include "wxgit/outliner/Branch.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/Repository.hpp"

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief コンストラクタ
        @param[in] name 名前
        @param[in] repository リポジトリ
***************************************************************************/
Repository::Repository(const wxString& name, 
                       const git::RepositoryPtr& repository)
  : super(name), 
    repository_(repository)
{
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
Repository::~Repository() {
}
/***********************************************************************//**
	@brief 
***************************************************************************/
Repository* Repository::Append(Outliner& outliner, 
                               const wxString& name, 
                               const git::RepositoryPtr& repository) {
  auto node = new Repository(name, repository);
  outliner.appendNode(node);
  node->appendBranches(outliner, "Local branch", GIT_BRANCH_LOCAL);
  node->appendBranches(outliner, "Remote branch", GIT_BRANCH_REMOTE);
  return node;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
Node* Repository::appendBranches(Outliner& outliner, 
                                 const wxString& name, 
                                 git_branch_t type) {
  auto branches = repository_->getBranches(type);
  if(branches.empty()) {
    return nullptr;
  }
  auto folder = outliner.appendNode(new Node(name), this);
  for(auto& branch: branches) {
    outliner.appendNode(new Branch(branch), folder);
  }
  return folder;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
