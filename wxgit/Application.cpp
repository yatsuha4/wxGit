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
  loadPreference();
  return true;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Application::savePreference() {
  wxXmlDocument document;
  auto root = new wxXmlNode(wxXML_ELEMENT_NODE, Version.GetName());
  root->AddChild(mainFrame_->serialize());
  document.SetRoot(root);
  auto path = GetPreferencePath();
  wxLogDebug("save '%s'", path.GetFullPath());
  document.Save(path.GetFullPath());
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Application::loadPreference() {
  auto path = GetPreferencePath();
  wxXmlDocument xml(path.GetFullPath());
  if(xml.IsOk()) {
    wxLogDebug("load '%s'", path.GetFullPath());
    auto root = xml.GetRoot();
    if(root->GetName() == Version.GetName()) {
      for(auto iter = root->GetChildren(); iter; iter = root->GetNext()) {
        if(iter->GetName() == MainFrame::GetSerialName()) {
          mainFrame_->deserialize(iter);
        }
        else {
          Serializable::Warning("illegal node", iter);
        }
      }
    }
    else {
      Serializable::Warning("illegal preference", root);
    }
  }
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
