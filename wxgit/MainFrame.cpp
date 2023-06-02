#include "wxgit/Application.hpp"
#include "wxgit/CommitWindow.hpp"
#include "wxgit/DiffWindow.hpp"
#include "wxgit/FileWindow.hpp"
#include "wxgit/Id.hpp"
#include "wxgit/LogWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/SideView.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/RepositoryNode.hpp"

namespace wxgit
{
    /**
     * @brief 
     */
    enum
    {
        LAYER_LOG, 
        LAYER_FILE, 
        LAYER_COMMIT, 
        LAYER_OUTLINER
    };

    /**
     * @brief コンストラクタ
     */
    MainFrame::MainFrame(Application* application)
        : super(nullptr, wxID_ANY, Application::Version.GetName()), 
          application_(application), 
          statusBar_(CreateStatusBar()), 
          auiManager_(new wxAuiManager(this)), 
          sideView_(new SideView(this)), 
          logWindow_(new LogWindow(this)), 
          diffWindow_(new DiffWindow(this)), 
          commitWindow_(new CommitWindow(this)), 
          menuNode_(nullptr)
    {
        SetClientSize(FromDIP(wxSize(1200, 900)));
        setupMenuBar();
        setupToolBar();
        statusBar_->PushStatusText(Application::Version.ToString());
        auiManager_->AddPane(sideView_, 
                             wxAuiPaneInfo().
                             Name("SideView").
                             Caption("SideView").
                             CloseButton(false).
                             Left().
                             BestSize(FromDIP(wxSize(300, 900))).
                             Layer(LAYER_OUTLINER));
        auiManager_->AddPane(logWindow_, 
                             wxAuiPaneInfo().
                             Name("Log").
                             Caption("Log").
                             CloseButton(false).
                             CenterPane().
                             Layer(LAYER_LOG));
        auiManager_->AddPane(commitWindow_, 
                             wxAuiPaneInfo().
                             Name("Commit").
                             Caption("Commit").
                             CloseButton(false).
                             Bottom().
                             BestSize(FromDIP(wxSize(900, 100))).
                             Layer(LAYER_COMMIT));
        auiManager_->AddPane(diffWindow_, 
                             wxAuiPaneInfo().
                             Name("Diff").
                             Caption("Diff").
                             CloseButton(false).
                             BestSize(FromDIP(wxSize(500, 500))).
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
     * @brief アウトライナを取得する
     * @param[in] show ファイルウィンドウを表示する
     * @return アウトライナ
     */
    outliner::Outliner* MainFrame::getOutliner(bool show) const
    {
        auto sideView = getSideView();
        auto outliner = sideView->getOutliner();
        if(show)
        {
            sideView->show(outliner);
        }
        return outliner;
    }

    /**
     * @brief ファイルウィンドウを取得する
     * @param[in] show ファイルウィンドウを表示する
     * @return ファイルウィンドウ
     */
    FileWindow* MainFrame::getFileWindow(bool show) const
    {
        auto sideView = getSideView();
        auto fileWindow = sideView->getFileWindow();
        if(show)
        {
            sideView->show(fileWindow);
        }
        return fileWindow;
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
                getLogWindow()->showCommits(repository->getCommits());
                getCommitWindow()->setSignature(repository->takeSignature());
                status();
            }
        }
    }

    /**
     * @brief リポジトリを取得する
     * @return リポジトリ
     */
    git::RepositoryPtr MainFrame::getRepository() const
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
        xml->AddChild(getOutliner()->serialize());
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
                //SetSize(width, height);
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
                    getOutliner()->deserialize(child);
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
            auto menu = new wxMenu();
            menu->Append(ID_FILE_QUIT, _("Quit"));
            menuBar->Append(menu, _("File"));
        }
        {
            auto menu = new wxMenu();
            menu->Append(ID_REPOSITORY_OPEN, _("Open"));
            menu->Append(ID_REPOSITORY_CLONE, _("Clone"));
            menuBar->Append(menu, _("Repository"));
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
        toolBar->AddTool(ID_REPOSITORY_CLONE, 
                         _("Clone"), 
                         wxArtProvider::GetBitmap(wxART_COPY));
        toolBar->AddTool(ID_REPOSITORY_OPEN, 
                         _("Open"), 
                         wxArtProvider::GetBitmap(wxART_FILE_OPEN));
        toolBar->AddTool(ID_REPOSITORY_INIT, 
                         _("Init"), 
                         wxArtProvider::GetBitmap(wxART_NEW));
        toolBar->AddTool(ID_WORK_STATUS, 
                         _("Status"), 
                         wxArtProvider::GetBitmap(wxART_PLUS));
        toolBar->AddStretchableSpace();
        toolBar->Realize();
        Bind(wxEVT_TOOL, &MainFrame::onSelectMenu, this);
    }

    /**
     * @brief 
     */
    void MainFrame::onSelectMenu(wxCommandEvent& event)
    {
        switch(event.GetId())
        {
        case ID_FILE_QUIT:
            Close();
            break;
        case ID_REPOSITORY_OPEN:
            openRepository();
            break;
        case ID_REPOSITORY_INIT:
            initRepository();
            break;
        case ID_REPOSITORY_CLOSE:
            if(auto node = dynamic_cast<outliner::RepositoryNode*>(menuNode_))
            {
                closeRepository(node);
            }
            break;
        case ID_WORK_STATUS:
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
                getOutliner()->appendNode(new outliner::RepositoryNode(repository));
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
                getOutliner()->appendNode(new outliner::RepositoryNode(repository));
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
        getOutliner()->removeNode(node);
    }

    /**
     */
    void MainFrame::status()
    {
        if(auto repository = getRepository())
        {
            if(auto status = repository->takeStatus())
            {
                getFileWindow(true)->showStatus(status);
            }
        }
    }

    /**
     */
    MainFrame* MainFrame::Get(wxWindow* window)
    {
        while(window)
        {
            if(auto mainFrame = dynamic_cast<MainFrame*>(window))
            {
                return mainFrame;
            }
            window = window->GetParent();
        }
        return nullptr;
    }
}
