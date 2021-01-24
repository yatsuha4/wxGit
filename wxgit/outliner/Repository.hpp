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
  wxString dir_;
  git::RepositoryPtr repository_;

 public:
  Repository() = default;
  Repository(const wxString& dir);
  ~Repository() override = default;

  WXGIT_GETTER(Repository, repository_);

  wxMenu* getContextMenu() override;

  wxXmlNode* serialize() const override;
  bool deserialize(const wxXmlNode* xml) override;
  WXGIT_GET_SERIAL_NAME(Repository);

 protected:
  void onAppend(Outliner* outliner, const wxTreeListItem& id) override;

 private:
  void appendBranches(const wxString& name, git_branch_t type);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
