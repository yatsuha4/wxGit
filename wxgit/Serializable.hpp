/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Serializable {
 public:
  Serializable() = default;
  virtual ~Serializable() = default;

  virtual wxXmlNode* serialize() const = 0;
  virtual bool deserialize(const wxXmlNode* xml) = 0;

  virtual const char* getSerialName() const = 0;

  static void Warning(const wxString& message, const wxXmlNode* node);
};
/***********************************************************************//**
	@brief 
***************************************************************************/
#define WXGIT_GET_SERIAL_NAME(klass)            \
  const char* getSerialName() const override {  \
    return GetSerialName();                     \
  }                                             \
  static const char* GetSerialName() {          \
    return #klass;                              \
  }
/***********************************************************************//**
	$Id$
***************************************************************************/
}
