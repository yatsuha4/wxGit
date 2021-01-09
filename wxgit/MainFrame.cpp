/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/Application.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/Menu.hpp"
#include "wxgit/RepoBrowser.hpp"

namespace wxgit {
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
MainFrame::MainFrame()
  : super(nullptr, wxID_ANY, Application::Version.GetName(), 
          wxDefaultPosition, wxSize(960, 640)), 
    toolBar_(CreateToolBar()), 
    statusBar_(CreateStatusBar()), 
    notebook_(new wxAuiNotebook(this, wxID_ANY)), 
    repoBrowser_(new RepoBrowser(notebook_))
{
  setupMenuBar();
  notebook_->AddPage(repoBrowser_, "Repository");
  statusBar_->PushStatusText(Application::Version.ToString());
  Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
MainFrame::~MainFrame() {
}
/***********************************************************************//**
	@brief メニューバーを設定する
***************************************************************************/
void MainFrame::setupMenuBar() {
  auto menuBar = new wxMenuBar();
  {
    auto menu = new wxMenu();
    menu->Append(MENU_FILE_QUIT, "Quit");
    menuBar->Append(menu, "File");
  }
  {
    auto menu = new wxMenu();
    menu->Append(MENU_REPOSITORY_ADD, "Add");
    menuBar->Append(menu, "Repository");
  }
  SetMenuBar(menuBar);
  Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::onSelectMenu, this);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void MainFrame::onSelectMenu(wxCommandEvent& event) {
  switch(event.GetId()) {
  case MENU_FILE_QUIT:
  case wxID_EXIT:
    Close();
    break;
  default:
    break;
  }
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void MainFrame::onClose(wxCloseEvent& event) {
  if(event.CanVeto()) {
    Destroy();
  }
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
