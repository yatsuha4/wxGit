#include "wxgit/Application.hpp"
#include "wxgit/CommitWindow.hpp"
#include "wxgit/DiffWindow.hpp"
#include "wxgit/FileWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/Menu.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/history/History.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/RepositoryNode.hpp"

namespace wxgit
{
    /**
     * @brief 
     */
    enum
    {
        LAYER_HISTORY, 
        LAYER_FILE, 
        LAYER_COMMIT, 
        LAYER_OUTLINER
    };

    /**
     * @brief コンストラクタ
     */
    MainFrame::MainFrame(Application* application)
        : super(nullptr, wxID_ANY, Application::Version.GetName(), 
                wxDefaultPosition, wxSize(960, 640)), 
          application_(application), 
          statusBar_(CreateStatusBar()), 
          auiManager_(new wxAuiManager(this)), 
          outliner_(new outliner::Outliner(this)), 
          history_(new history::History(this)), 
          fileWindow_(new FileWindow(this)), 
          diffWindow_(new DiffWindow(this)), 
          commitWindow_(new CommitWindow(this)), 
          menuNode_(nullptr)
    {
        setupMenuBar();
        setupToolBar();
        //notebook_->AddPage(repoBrowser_, "Repository");
        statusBar_->PushStatusText(Application::Version.ToString());
        auiManager_->AddPane(outliner_, 
                             wxAuiPaneInfo().
                             Name("Outliner").
                             Caption("Outliner").
                             CloseButton(false).
                             Left().
                             BestSize(200, 800).
                             Layer(LAYER_OUTLINER));
        auiManager_->AddPane(history_, 
                             wxAuiPaneInfo().
                             Name("History").
                             Caption("History").
                             CloseButton(false).
                             CenterPane().
                             Layer(LAYER_HISTORY));
        auiManager_->AddPane(commitWindow_, 
                             wxAuiPaneInfo().
                             Name("Commit").
                             Caption("Commit").
                             CloseButton(false).
                             Bottom().
                             Layer(LAYER_COMMIT));
        auiManager_->AddPane(fileWindow_, 
                             wxAuiPaneInfo().
                             Name("File").
                             Caption("File").
                             CloseButton(false).
                             BestSize(800, 800).
                             Bottom().
                             Layer(LAYER_FILE));
        auiManager_->AddPane(diffWindow_, 
                             wxAuiPaneInfo().
                             Name("Diff").
                             Caption("Diff").
                             CloseButton(false).
                             BestSize(800, 800).
                             Bottom().
                             Layer(LAYER_FILE));
        auiManager_->Update();
        Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
    }

    /**
     * @brief デストラクタ
     */
    MainFrame::~MainFrame()
    {
        auiManager_->UnInit();
    }

    /**
     * @brief リポジトリノードをセットする
     * @param[in] node リポジトリノード
     */
    void MainFrame::setRepositoryNode(outliner::RepositoryNode* node)
    {
        if(node != repositoryNode_)
        {
            repositoryNode_ = node;
            if(auto repository = getRepository())
            {
                getHistory()->showCommits(repository->getCommits());
                getCommitWindow()->setSignature(repository->takeSignature());
            }
        }
    }

    /**
     * @brief リポジトリを取得する
     * @return リポジトリ
     */
    const git::RepositoryPtr& MainFrame::getRepository() const
    {
        return repositoryNode_ ? repositoryNode_->getRepository() : nullptr;
    }

    /**
     * @copydoc Serializable::serialize
     */
    wxXmlNode* MainFrame::serialize() const
    {
        auto xml = Serializable::serialize();
        auto size = GetSize();
        xml->AddAttribute("width", wxString::Format("%d", size.GetWidth()));
        xml->AddAttribute("height", wxString::Format("%d", size.GetHeight()));
        xml->AddAttribute("perspective", auiManager_->SavePerspective());
        xml->AddChild(outliner_->serialize());
        return xml;
    }

    /**
     * @copydoc Serializable::deserialize
     */
    bool MainFrame::deserialize(const wxXmlNode* xml)
    {
        if(Serializable::deserialize(xml))
        {
            int width, height;
            if(xml->GetAttribute("width").ToInt(&width) && 
               xml->GetAttribute("height").ToInt(&height))
            {
                SetSize(width, height);
            }
            wxString perspective;
            if(xml->GetAttribute("perspective", &perspective))
            {
                //auiManager_->LoadPerspective(perspective);
            }
            for(auto child = xml->GetChildren(); child; child = child->GetNext())
            {
                if(child->GetName() == outliner::Outliner::GetSerialName())
                {
                    outliner_->deserialize(child);
                }
                else
                {
                    Warning("illegal node", child);
                }
            }
            return true;
        }
        return false;
    }

    /**
     * @brief ポップアップメニューを開く
     * @param[in] node ノード
     * @param[in] menu メニュー
     */
    void MainFrame::popupMenu(outliner::Node* node, wxMenu* menu)
    {
        menuNode_ = node;
        auto result = PopupMenu(menu);
        menuNode_ = nullptr;
    }

    /**
     * @brief メニューバーを設定する
     */
    void MainFrame::setupMenuBar()
    {
        auto menuBar = new wxMenuBar();
        {
            auto menu = new Menu();
            menu->append(Menu::Id::FILE_QUIT);
            menuBar->Append(menu, "File");
        }
        {
            auto menu = new Menu();
            menu->append(Menu::Id::REPOSITORY_OPEN);
            menu->append(Menu::Id::REPOSITORY_CLONE);
            menuBar->Append(menu, "Repository");
        }
        SetMenuBar(menuBar);
        Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::onSelectMenu, this);
    }

    /**
     * @brief ツールバーを設定する
     */
    void MainFrame::setupToolBar()
    {
        auto toolBar = CreateToolBar(wxTB_DEFAULT_STYLE | wxTB_TEXT);
        toolBar->AddTool(static_cast<int>(Menu::Id::REPOSITORY_CLONE), 
                         Menu::GetText(Menu::Id::REPOSITORY_CLONE), 
                         wxArtProvider::GetBitmap(wxART_COPY));
        toolBar->AddTool(static_cast<int>(Menu::Id::REPOSITORY_OPEN), 
                         Menu::GetText(Menu::Id::REPOSITORY_OPEN), 
                         wxArtProvider::GetBitmap(wxART_FILE_OPEN));
        toolBar->AddTool(static_cast<int>(Menu::Id::REPOSITORY_INIT), 
                         Menu::GetText(Menu::Id::REPOSITORY_INIT), 
                         wxArtProvider::GetBitmap(wxART_NEW));
        toolBar->AddTool(static_cast<int>(Menu::Id::WORK_STATUS), 
                         Menu::GetText(Menu::Id::WORK_STATUS), 
                         wxArtProvider::GetBitmap(wxART_PLUS));
        toolBar->Realize();
        Bind(wxEVT_TOOL, &MainFrame::onSelectMenu, this);
    }

    /**
     * @brief 
     */
    void MainFrame::onSelectMenu(wxCommandEvent& event)
    {
        auto id = static_cast<Menu::Id>(event.GetId());
        switch(id)
        {
        case Menu::Id::FILE_QUIT:
            Close();
            break;
        case Menu::Id::REPOSITORY_OPEN:
            openRepository();
            break;
        case Menu::Id::REPOSITORY_INIT:
            initRepository();
            break;
        case Menu::Id::REPOSITORY_CLOSE:
            if(auto node = dynamic_cast<outliner::RepositoryNode*>(menuNode_))
            {
                closeRepository(node);
            }
            break;
        case Menu::Id::WORK_STATUS:
            status();
            break;
        default:
            break;
        }
    }

    /**
     * @brief 
     */
    void MainFrame::onClose(wxCloseEvent& event)
    {
        if(event.CanVeto())
        {
            application_->savePreference();
            Destroy();
        }
    }

    /**
     * @brief ローカルリポジトリを開く
     */
    void MainFrame::openRepository()
    {
        wxDirDialog dialog(this, _("Select repository"));
        if(dialog.ShowModal() == wxID_OK)
        {
            git::Path dir(dialog.GetPath());
            if(auto repository = git::Repository::Open(git::Path(dir, ".git")))
            {
                outliner_->appendNode(new outliner::RepositoryNode(repository));
            }
        }
    }

    /**
     * @brief ローカルリポジトリを初期化する
     */
    void MainFrame::initRepository()
    {
        wxDirDialog dialog(this, "Select init repository");
        if(dialog.ShowModal() == wxID_OK)
        {
            git::Path dir(dialog.GetPath());
            if(auto repository = git::Repository::Init(dir))
            {
                outliner_->appendNode(new outliner::RepositoryNode(repository));
            }
        }
    }

    /**
     * @brief リポジトリを閉じる
     * @param[in] node リポジトリノード
     */
    void MainFrame::closeRepository(outliner::RepositoryNode* node)
    {
        if(node == repositoryNode_)
        {
            setRepositoryNode(nullptr);
        }
        outliner_->removeNode(node);
    }

    /**
     */
    void MainFrame::status()
    {
        if(auto repository = getRepository())
        {
            if(auto status = repository->takeStatus())
            {
                getFileWindow()->showStatus(status);
            }
        }
    }
}
