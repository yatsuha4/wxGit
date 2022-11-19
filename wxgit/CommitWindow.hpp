#pragma once

#include "wxgit/Window.hpp"

namespace wxgit
{
    /**
     * @brief コミットウィンドウ
     */
    class CommitWindow
        : public Window<wxWindow>
    {
        using super = Window<wxWindow>;

    private:
        wxTextCtrl* messageText_;
        wxStaticText* signatureText_;
        wxButton* commitButton_;
        git::SignaturePtr signature_;

    public:
        CommitWindow(MainFrame* mainFrame);
        ~CommitWindow() override = default;

        void setSignature(const git::SignaturePtr& signature);
        void setCanCommit(bool canCommit);

    private:
        void onButtonCommit(wxCommandEvent& event);
    };
}
