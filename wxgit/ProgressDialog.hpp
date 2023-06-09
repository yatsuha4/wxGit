#pragma once

#include "wxgit/git/ProgressListener.hpp"

namespace wxgit
{
    /**
     * @brief 進捗ダイアログ
     */
    class ProgressDialog
        : public wxProgressDialog, 
          public git::ProgressListener
    {
        using super = wxProgressDialog;

    public:
        ProgressDialog(const wxString& title, 
                       const wxString& message = wxEmptyString);
        ~ProgressDialog() override = default;

        void onProgress(const wxString& message, int current, int total) override;
    };
}
