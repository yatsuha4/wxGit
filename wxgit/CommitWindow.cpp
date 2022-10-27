#include "wxgit/CommitWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/git/Signature.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] mainFrame メインフレーム
     */
    CommitWindow::CommitWindow(MainFrame* mainFrame)
        : super(mainFrame, wxID_ANY), 
          messageText_(new wxTextCtrl(this, wxID_ANY)), 
          signatureText_(new wxStaticText(this, wxID_ANY, wxT("Sinature")))
    {
        auto vbox = new wxBoxSizer(wxVERTICAL);
        vbox->Add(messageText_, wxSizerFlags().Expand().Proportion(1));
        {
            auto hbox = new wxBoxSizer(wxHORIZONTAL);
            {
                hbox->Add(signatureText_, wxSizerFlags().Expand().Proportion(1));
                auto button = new wxButton(this, wxID_ANY, wxT("Commit"));
                hbox->Add(button);
            }
            vbox->Add(hbox, wxSizerFlags().Expand().Proportion(1));
        }
        SetSizerAndFit(vbox);
        Disable();
    }

    /**
     * @brief シグネチャをセットする
     * @param[in] signature シグネチャ
     */
    void CommitWindow::setSignature(const git::SignaturePtr& signature)
    {
        signature_ = signature;
        signatureText_->SetLabel(wxString::Format("%s <%s>", 
                                                  signature->getName(), 
                                                  signature->getEmail()));
    }
}
