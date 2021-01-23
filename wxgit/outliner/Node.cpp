﻿/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/outliner/Node.hpp"

namespace wxgit {
namespace outliner {
/***********************************************************************//**
	@brief コンストラクタ
        @param[in] text 表示名
***************************************************************************/
Node::Node(const wxString& text)
  : text_(text), 
    outliner_(nullptr)
{
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
Node::~Node() {
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Node::link(Outliner* outliner, const wxTreeListItem& id) {
  wxASSERT(!outliner_);
  outliner_ = outliner;
  id_ = id;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Node::unlink() {
  wxASSERT(outliner_);
  outliner_ = nullptr;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
