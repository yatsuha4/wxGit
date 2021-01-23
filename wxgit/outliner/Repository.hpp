/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "wxgit/outliner/Node.hpp"

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Repository
  : public Node
{
  using super = Node;

 private:
  git::RepositoryPtr repository_;

 public:
  Repository(const wxString& name, const git::RepositoryPtr& repository);
  ~Repository() override;
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
