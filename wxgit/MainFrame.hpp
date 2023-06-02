﻿#pragma once

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
        SideView* sideView_;
        LogWindow* logWindow_;
        DiffWindow* diffWindow_;
        CommitWindow* commitWindow_;
        outliner::RepositoryNode* repositoryNode_;
        outliner::Node* menuNode_;

    public:
        MainFrame(Application* application);
        ~MainFrame() override;

        WXEDITOR_GETTER(SideView, sideView_);
        WXEDITOR_GETTER(LogWindow, logWindow_);
        WXEDITOR_GETTER(DiffWindow, diffWindow_);
        WXEDITOR_GETTER(CommitWindow, commitWindow_);

        outliner::Outliner* getOutliner() const;
        FileWindow* getFileWindow() const;

        void setRepositoryNode(outliner::RepositoryNode* node);
        const git::RepositoryPtr& getRepository() const;

        wxXmlNode* serialize() const override;
        bool deserialize(const wxXmlNode* xml) override;

        WXGIT_GET_SERIAL_NAME(MainFrame);

        void popupMenu(outliner::Node* node, wxMenu* menu);

        void status();

        static MainFrame* Get(wxWindow* window);

    private:
        void setupMenuBar();
        void setupToolBar();

        void onSelectMenu(wxCommandEvent& event);
        void onClose(wxCloseEvent& event);

        void openRepository();
        void initRepository();
        void closeRepository(outliner::RepositoryNode* node);
    };
}
