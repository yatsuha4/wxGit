#include "wxgit/git/Diff.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] file ファイル
     */
    Diff::File::File(const git_diff_file& file)
        : file_(file)
    {
    }

    /**
     * @brief パスを取得する
     * @return パス
     */
    wxFileName Diff::File::getPath() const
    {
        return wxFileName(wxString::FromUTF8(file_.path), wxPATH_UNIX);
    }

    /**
     */
    Diff::Line::Line(const git_diff_line* line)
        : origin_(static_cast<git_diff_line_t>(line->origin)), 
          oldLine_(line->old_lineno), 
          newLine_(line->new_lineno), 
          numLines_(line->num_lines), 
          contentOffset_(line->content_offset), 
          content_(line->content, wxConvAuto(), line->content_len)
    {
    }

    /**
     */
    Diff::Hunk::Hunk(const git_diff_hunk* hunk)
        : hunk_(hunk)
    {
    }

    /**
     * @brief コンストラクタ
     * @param[in] delta デルタ
     */
    Diff::Delta::Delta(const git_diff_delta* delta)
        : delta_(delta)
    {
    }

    /**
     */
    Diff::Hunk& Diff::Delta::findHunk(const git_diff_hunk* hunk)
    {
        auto found = std::find_if(hunks_.begin(), 
                                  hunks_.end(), 
                                  [&](auto& iter)
                                  {
                                      return iter.getHunk() == hunk;
                                  });
        wxASSERT(found != hunks_.end());
        return *found;
    }

    /**
     */
    git_delta_t Diff::Delta::getStatus() const
    {
        return delta_->status;
    }

    /**
     */
    Diff::File Diff::Delta::getOldFile() const
    {
        return Diff::File(delta_->old_file);
    }

    /**
     */
    Diff::File Diff::Delta::getNewFile() const
    {
        return Diff::File(delta_->new_file);
    }

    /**
     * @brief コンストラクタ
     * @param[in] diff 差分
     */
    Diff::Diff(git_diff* diff)
        : diff_(diff)
    {
        git_diff_foreach(diff, 
                         Diff::OnFile, 
                         Diff::OnBinary, 
                         Diff::OnHunk, 
                         Diff::OnLine, 
                         this);
    }

    /**
     * @brief デストラクタ
     */
    Diff::~Diff()
    {
        git_diff_free(diff_);
    }

    /**
     * @brief デルタを探す
     * @param[in] delta デルタ
     * @return deltaに一致するデルタ
     */
    Diff::Delta& Diff::findDelta(const git_diff_delta* delta)
    {
        auto found = std::find_if(deltas_.begin(), 
                                  deltas_.end(), 
                                  [&](auto& iter)
                                  {
                                      return iter.getDelta() == delta;
                                  });
        wxASSERT(found != deltas_.end());
        return *found;
    }

    /**
     */
    int Diff::OnFile(const git_diff_delta* delta, 
                     float progress, 
                     void* payload)
    {
        auto diff = reinterpret_cast<Diff*>(payload);
        diff->deltas_.emplace_back(delta);
        return GIT_OK;
    }

    /**
     */
    int Diff::OnBinary(const git_diff_delta* delta, 
                       const git_diff_binary* binary, 
                       void* payload)
    {
        return GIT_OK;
    }

    /**
     */
    int Diff::OnHunk(const git_diff_delta* delta, 
                     const git_diff_hunk* hunk, 
                     void* payload)
    {
        auto diff = reinterpret_cast<Diff*>(payload);
        diff->findDelta(delta).getHunks().emplace_back(hunk);
        return GIT_OK;
    }

    /**
     */
    int Diff::OnLine(const git_diff_delta* delta, 
                     const git_diff_hunk* hunk, 
                     const git_diff_line* line, 
                     void* payload)
    {
        auto diff = reinterpret_cast<Diff*>(payload);
        diff->findDelta(delta).findHunk(hunk).getLines().emplace_back(line);
        return GIT_OK;
    }
}
