/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/git/Branch.hpp"
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Repository.hpp"

namespace wxgit {
namespace git {
/***********************************************************************//**
	@brief コンストラクタ
	@param[in] dir ディレクトリ
***************************************************************************/
Repository::Repository(const wxFileName& dir)
  : dir_(dir), 
    repository_(nullptr), 
    error_(0)
{
  error_ = git_repository_open(&repository_, dir.GetFullPath().c_str());
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
Repository::~Repository() {
  if(repository_) {
    git_repository_free(repository_);
  }
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Repository::isError() const {
  return error_ != 0;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::vector<BranchPtr> Repository::getBranches(git_branch_t type) const {
  std::vector<BranchPtr> branches;
  git_branch_iterator* iterator;
  if(git_branch_iterator_new(&iterator, repository_, type) == 0) {
    git_reference* reference;
    while(git_branch_next(&reference, &type, iterator) == 0) {
      branches.push_back(std::make_shared<Branch>(reference, type));
    }
  }
  git_branch_iterator_free(iterator);
  return branches;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::vector<CommitPtr> Repository::getCommits() const {
  std::vector<CommitPtr> commits;
  git_revwalk* walk;
  if(git_revwalk_new(&walk, repository_) == 0) {
    if(git_revwalk_push_head(walk) == 0) {
      git_oid oid;
      while(git_revwalk_next(&oid, walk) == 0) {
        git_commit* commit;
        if(git_commit_lookup(&commit, repository_, &oid) == 0) {
          commits.push_back(std::make_shared<Commit>(commit));
        }
      }
    }
    git_revwalk_free(walk);
  }
  return commits;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
