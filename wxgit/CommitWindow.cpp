#include "wxgit/CommitWindow.hpp"
#include "wxgit/FileWindow.hpp"
#include "wxgit/LogWindow.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/git/Repository.hpp"
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
          signatureText_(new wxStaticText(this, wxID_ANY, _("Sinature"))), 
          commitButton_(new wxButton(this, wxID_ANY, _("Commit")))
    {
        auto vbox = new wxBoxSizer(wxVERTICAL);
        vbox->Add(messageText_, wxSizerFlags().Expand().Proportion(1));
        {
            auto hbox = new wxBoxSizer(wxHORIZONTAL);
            hbox->Add(signatureText_, wxSizerFlags().Expand().Proportion(1));
            hbox->Add(commitButton_);
            vbox->Add(hbox, wxSizerFlags().Expand());
        }
        SetSizerAndFit(vbox);
        setCanCommit(false);
        Bind(wxEVT_BUTTON, &CommitWindow::onButtonCommit, this, commitButton_->GetId());
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

    /**
     * @brief コミット可能かセットする
     * @param[in] canCommit コミット可能なとき真
     */
    void CommitWindow::setCanCommit(bool canCommit)
    {
        commitButton_->Enable(canCommit);
    }

    /**
     * @brief コミットボタンが押された
     */
    void CommitWindow::onButtonCommit(wxCommandEvent& event)
    {
        auto mainFrame = getMainFrame();
        auto message = messageText_->GetValue();
        if(message.IsEmpty())
        {
            wxMessageDialog dialog(mainFrame, 
                                   _("Message is empty"), 
                                   _("Commit"), 
                                   wxYES_NO | wxNO_DEFAULT |
                                   wxICON_WARNING |
                                   wxCENTRE);
            if(dialog.ShowModal() != wxYES)
            {
                return;
            }
        }
        if(auto commit = mainFrame->getRepository()->
           commit(mainFrame->getFileWindow()->getCheckFiles(), message))
        {
            mainFrame->getLogWindow()->insertCommit(commit);
            mainFrame->status();
        }
        else
        {
            wxLogError("commit failed");
        }
    }
}
