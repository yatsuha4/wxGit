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
  ~Node() override = default;

  void setName(const wxString& name);
  WXEDITOR_GETTER(Name, name_);

  WXEDITOR_GETTER(Outliner, outliner_);
  WXEDITOR_GETTER(Id, id_);

  virtual void onAppend(Outliner* outliner, const wxTreeListItem& id);

  virtual void onAppendChild(Outliner& outliner, Node* child) {}
  virtual void onRemoveChild(Outliner& outliner, Node* child) {}

  virtual wxMenu* getContextMenu();

  wxXmlNode* serialize() const override;
  bool deserialize(const wxXmlNode* xml) override;
  WXGIT_GET_SERIAL_NAME(Node);

  static Node* Create(const wxString& serialName);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
