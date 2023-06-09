#pragma once

namespace wxgit::git
{
    /**
     * @brief 進捗を受け取る
     */
    class ProgressListener
    {
    public:
        ProgressListener() = default;
        virtual ~ProgressListener() = default;

        virtual void onProgress(const wxString& message, int current, int total) = 0;
    };
}
