﻿/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
namespace git {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Branch {
 private:
  git_reference* reference_;
  git_branch_t type_;

 public:
  Branch(git_reference* reference, git_branch_t type);
  ~Branch();
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}