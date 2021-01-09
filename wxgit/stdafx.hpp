/***********************************************************************//**
	@file
***************************************************************************/
#include <vector>
/***********************************************************************//**
	@brief 
***************************************************************************/
#define _FILE_OFFSET_BITS 64
#define __WXMAC__
#define __WXOSX__
#define __WXOSX_COCOA__
#include "wx/wx.h"
#include "wx/aui/auibook.h"
/***********************************************************************//**
	@brief 
***************************************************************************/
#define WXGIT_DECLARE_CLASS(klass)                                      \
  class klass;                                                          \
  using klass##Ptr = std::shared_ptr<klass>;                            \
  using Const##klass##Ptr = std::shared_ptr<const klass>;               \

#define WXGIT_SETTER(name, var)                                         \
  auto set##name(const decltype(var)& value) -> decltype(*this)& {      \
    var = value;                                                        \
    return *this;                                                       \
  }

#define WXGIT_GETTER(name, var)                 \
  const decltype(var)& get##name() const {      \
    return var;                                 \
  }
/***********************************************************************//**
	@brief 
***************************************************************************/
namespace wxgit {
WXGIT_DECLARE_CLASS(Application);
WXGIT_DECLARE_CLASS(MainFrame);
WXGIT_DECLARE_CLASS(RepoBrowser);
}
/***********************************************************************//**
	$Id$
***************************************************************************/
