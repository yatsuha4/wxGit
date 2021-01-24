/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "wxgit/Serializable.hpp"

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief ノード基底クラス
***************************************************************************/
class Node
  : public wxClientData, 
    public Serializable
{
 private: 
  wxString name_;
  Outliner* outliner_;
  wxTreeListItem id_;

 public:
  Node();
  ~Node() override;

  WXGIT_ACCESSOR(Name, name_);
  WXGIT_GETTER(Outliner, outliner_);
  WXGIT_GETTER(Id, id_);

  virtual void onAppend(Outliner* outliner, const wxTreeListItem& id);

  virtual void onAppendChild(Outliner& outliner, Node* child) {}
  virtual void onRemoveChild(Outliner& outliner, Node* child) {}

  wxXmlNode* serialize() const override;
  bool deserialize(const wxXmlNode* xml) override;
  WXGIT_GET_SERIAL_NAME(Node);

  static Node* Deserialize(const wxXmlNode* xml);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
