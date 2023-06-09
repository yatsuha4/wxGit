#include "wxgit/ProgressDialog.hpp"

namespace wxgit
{
    /**
     * @brief コンストラクタ
     * @param[in] title タイトル
     * @param[in] message メッセージ
     */
    ProgressDialog::ProgressDialog(const wxString& title, const wxString& message)
        : super(title, message)
    {
    }

    /**
     */
    void ProgressDialog::onProgress(const wxString& message, int current, int total)
    {
        SetRange(total);
        Update(current, message);
    }
}
