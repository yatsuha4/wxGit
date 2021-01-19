/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
/***********************************************************************//**
	@brief 
***************************************************************************/
class MainFrame
  : public wxFrame
{
  using super = wxFrame;

 private:
  wxStatusBar* statusBar_;
  wxAuiNotebook* notebook_;
  RepoBrowser* repoBrowser_;

 public:
  MainFrame();
  ~MainFrame() override;

 private:
  void setupMenuBar();
  void setupToolBar();
  void onSelectMenu(wxCommandEvent& event);

  void onClose(wxCloseEvent& event);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
