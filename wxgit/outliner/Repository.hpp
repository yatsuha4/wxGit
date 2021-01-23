/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "wxgit/outliner/Item.hpp"

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Repository
  : public Item
{
  using super = Item;

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
