﻿/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/history/History.hpp"

namespace wxgit {
namespace history {
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
History::History(wxWindow* parent)
  : super(parent, wxID_ANY)
{
  //AppendColumn("Description");
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
History::~History() {
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
