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
Node* Node::Deserialize(const wxXmlNode* xml) {
  std::unique_ptr<Node> node;
  if(xml->GetName() == Node::GetSerialName()) {
    node.reset(new Node());
  }
  else if(xml->GetName() == Repository::GetSerialName()) {
    node.reset(new Repository());
  }
  else {
    return nullptr;
  }
  return node->deserialize(xml) ? node.release() : nullptr;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
