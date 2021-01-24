/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Application
  : public wxApp
{
  using super = wxApp;

 public:
  static const wxVersionInfo Version;

 private:
  MainFrame* mainFrame_;

 public:
  Application();
  ~Application() override;

  void savePreference();
  void loadPreference();

 protected:
  bool OnInit() override;
  int OnExit() override;

 private:
  static wxFileName GetPreferencePath();
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
