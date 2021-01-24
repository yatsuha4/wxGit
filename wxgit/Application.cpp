/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/Application.hpp"
#include "wxgit/MainFrame.hpp"

namespace wxgit {
const wxVersionInfo Application::Version("wxGit", 0, 0, 1, "", "towerb.com");
/***********************************************************************//**
	@brief 
***************************************************************************/
Application::Application()
  : mainFrame_(nullptr)
{
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
Application::~Application() {
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Application::OnInit() {
  if(!super::OnInit()) {
    return false;
  }
  git_libgit2_init();
  mainFrame_ = new MainFrame(this);
  mainFrame_->Show(true);
  return true;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Application::savePreference() {
  wxXmlDocument document;
  auto root = new wxXmlNode(wxXML_ELEMENT_NODE, "wxGit");
  root->AddChild(mainFrame_->serialize());
  document.SetRoot(root);
  auto path = GetPreferencePath();
  wxLogDebug("save '%s'", path.GetFullPath());
  document.Save(path.GetFullPath());
}
/***********************************************************************//**
	@brief 
***************************************************************************/
int Application::OnExit() {
  return super::OnExit();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
wxFileName Application::GetPreferencePath() {
  auto& stdPaths = wxStandardPaths::Get();
  return wxFileName(stdPaths.GetUserConfigDir(), 
                    stdPaths.MakeConfigFileName(Version.GetName()));
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
