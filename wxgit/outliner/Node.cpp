/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/outliner/Node.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/Repository.hpp"

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
Node::Node()
  : outliner_(nullptr)
{
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Node::setName(const wxString& name) {
  name_ = name;
  if(outliner_) {
    outliner_->SetItemText(id_, name);
  }
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Node::onAppend(Outliner* outliner, const wxTreeListItem& id) {
  wxASSERT(!outliner_);
  outliner_ = outliner;
  id_ = id;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
wxMenu* Node::getContextMenu() {
  return nullptr;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
wxXmlNode* Node::serialize() const {
  auto xml = Serializable::serialize();
  xml->AddAttribute("name", name_);
  return xml;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Node::deserialize(const wxXmlNode* xml) {
  if(Serializable::deserialize(xml)) {
    setName(xml->GetAttribute("name"));
    return true;
  }
  return false;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
Node* Node::Create(const wxString& serialName) {
  if(serialName == Node::GetSerialName()) {
    return new Node();
  }
  else if(serialName == Repository::GetSerialName()) {
    return new Repository();
  }
  return nullptr;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
