/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
namespace git {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Repository {
 private:
  wxFileName dir_;
  git_repository* repository_;
  int error_;
  std::vector<CommitPtr> commits_;

 public:
  Repository(const wxFileName& dir);
  ~Repository();

  WXEDITOR_GETTER(Dir, dir_)

  bool isOk() const;

  std::vector<BranchPtr> getBranches(git_branch_t type) const;
  const std::vector<CommitPtr>& getCommits(bool update = false);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
