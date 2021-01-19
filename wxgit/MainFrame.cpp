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
    statusBar_(CreateStatusBar()), 
    notebook_(new wxAuiNotebook(this, wxID_ANY)), 
    repoBrowser_(new RepoBrowser(notebook_))
{
  setupMenuBar();
  setupToolBar();
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
    menu->Append(Menu::MENU_FILE_QUIT, "Quit");
    menuBar->Append(menu, "File");
  }
  {
    auto menu = new wxMenu();
    menu->Append(Menu::MENU_REPOSITORY_ADD, "Add");
    menuBar->Append(menu, "Repository");
  }
  SetMenuBar(menuBar);
  Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::onSelectMenu, this);
}
/***********************************************************************//**
	@brief ツールバーを設定する
***************************************************************************/
void MainFrame::setupToolBar() {
  auto toolBar = CreateToolBar(wxTB_DEFAULT_STYLE | wxTB_TEXT);
  toolBar->AddTool(Menu::MENU_REPOSITORY_CLONE, "Clone", 
                   wxArtProvider::GetBitmap(wxART_COPY));
  toolBar->AddTool(Menu::MENU_REPOSITORY_ADD, "Add", 
                   wxArtProvider::GetBitmap(wxART_NEW));
  toolBar->Realize();
  Bind(wxEVT_TOOL, &MainFrame::onSelectMenu, this);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void MainFrame::onSelectMenu(wxCommandEvent& event) {
  switch(event.GetId()) {
  case Menu::MENU_FILE_QUIT:
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
