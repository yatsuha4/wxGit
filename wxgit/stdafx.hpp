/***********************************************************************//**
	@file
***************************************************************************/
#include <memory>
#include <vector>
/***********************************************************************//**
	@brief 
***************************************************************************/
#define _FILE_OFFSET_BITS 64
#define __WXMAC__
#define __WXOSX__
#define __WXOSX_COCOA__
#include "wx/wx.h"
#include "wx/artprov.h"
#include "wx/aui/auibook.h"
#include "wx/filename.h"
#include "wx/treelist.h"
/***********************************************************************//**
	@brief 
***************************************************************************/
#include <git2.h>
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

#define WXGIT_ACCESSOR(name, var)               \
  WXGIT_SETTER(name, var)                       \
  WXGIT_GETTER(name, var)
/***********************************************************************//**
	@brief 
***************************************************************************/
namespace wxgit {
WXGIT_DECLARE_CLASS(Application)
WXGIT_DECLARE_CLASS(MainFrame)
WXGIT_DECLARE_CLASS(RepoBrowser)
namespace git {
WXGIT_DECLARE_CLASS(Branch);
WXGIT_DECLARE_CLASS(Repository)
}
namespace outliner {
WXGIT_DECLARE_CLASS(Item)
WXGIT_DECLARE_CLASS(Outliner)
WXGIT_DECLARE_CLASS(Repository)
}
}
/***********************************************************************//**
	$Id$
***************************************************************************/
