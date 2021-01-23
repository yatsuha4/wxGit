/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/Application.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/Menu.hpp"
#include "wxgit/RepoBrowser.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/Repository.hpp"

namespace wxgit {
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
MainFrame::MainFrame()
  : super(nullptr, wxID_ANY, Application::Version.GetName(), 
          wxDefaultPosition, wxSize(960, 640)), 
    statusBar_(CreateStatusBar()), 
    auiManager_(this), 
    outliner_(new outliner::Outliner(this))
{
  setupMenuBar();
  setupToolBar();
  //notebook_->AddPage(repoBrowser_, "Repository");
  statusBar_->PushStatusText(Application::Version.ToString());
  auiManager_.AddPane(outliner_, wxAuiPaneInfo().Left());
  auiManager_.Update();
  Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
MainFrame::~MainFrame() {
  auiManager_.UnInit();
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
  case Menu::MENU_REPOSITORY_ADD:
    addRepository();
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
	@brief ローカルリポジトリを追加する
***************************************************************************/
void MainFrame::addRepository() {
  wxDirDialog dialog(this, "Select repository");
  if(dialog.ShowModal() == wxID_OK) {
    auto name = wxFileName(dialog.GetPath()).GetName();
    wxFileName dir(dialog.GetPath(), ".git");
    auto repository = std::make_shared<git::Repository>(dir);
    if(repository->isError()) {
    }
    else {
      outliner_->appendItem(new outliner::Repository(name, repository));
    }
  }
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
