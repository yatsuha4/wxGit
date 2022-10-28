#pragma once

#include "wxgit/Serializable.hpp"

namespace wxgit
{
    class MainFrame
        : public wxFrame, 
          public Serializable
    {
        using super = wxFrame;

    private:
        Application* application_;
        wxStatusBar* statusBar_;
        std::unique_ptr<wxAuiManager> auiManager_;
        outliner::Outliner* outliner_;
        history::History* history_;
        FileWindow* fileWindow_;
        DiffWindow* diffWindow_;
        CommitWindow* commitWindow_;
        git::RepositoryPtr repository_;

    public:
        MainFrame(Application* application);
        ~MainFrame() override;

        WXEDITOR_GETTER(Outliner, outliner_);
        WXEDITOR_GETTER(History, history_);
        WXEDITOR_GETTER(FileWindow, fileWindow_);
        WXEDITOR_GETTER(DiffWindow, diffWindow_);
        WXEDITOR_GETTER(CommitWindow, commitWindow_);

        WXEDITOR_GETTER(Repository, repository_);
        void setRepository(const git::RepositoryPtr& repository);

        wxXmlNode* serialize() const override;
        bool deserialize(const wxXmlNode* xml) override;

        WXGIT_GET_SERIAL_NAME(MainFrame);

    private:
        void setupMenuBar();
        void setupToolBar();

        void onSelectMenu(wxCommandEvent& event);
        void onClose(wxCloseEvent& event);

        void addRepository();
        void status();
    };
}
