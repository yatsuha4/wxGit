#pragma once

namespace wxgit
{
    /**
     * @brief コミットウィンドウ
     */
    class CommitWindow
        : public wxWindow
    {
        using super = wxWindow;

    private:
        wxTextCtrl* messageText_;
        wxStaticText* signatureText_;
        git::SignaturePtr signature_;

    public:
        CommitWindow(MainFrame* mainFrame);
        ~CommitWindow() override = default;

        void setSignature(const git::SignaturePtr& signature);
    };
}
