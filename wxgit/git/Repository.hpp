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

 public:
  Repository(const wxFileName& dir);
  ~Repository();

  WXGIT_GETTER(Dir, dir_)

  bool isError() const;

  std::vector<BranchPtr> getBranches(git_branch_t type) const;
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
