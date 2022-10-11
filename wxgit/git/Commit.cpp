﻿/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Signature.hpp"

namespace wxgit {
namespace git {
/***********************************************************************//**
	@brief コンストラクタ
	@param[in] commit コミット
***************************************************************************/
Commit::Commit(git_commit* commit)
  : commit_(commit), 
    message_(wxString::FromUTF8(git_commit_message(commit))), 
    committer_(std::make_shared<Signature>(git_commit_committer(commit))), 
    time_(static_cast<time_t>(git_commit_time(commit)))
{
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
Commit::~Commit() {
  git_commit_free(commit_);
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
