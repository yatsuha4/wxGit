#include "wxgit/git/Blob.hpp"
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Diff.hpp"
#include "wxgit/git/Path.hpp"

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
    Path Diff::File::getPath() const
    {
        return Path(file_.path);
    }

    /**
     * @brief ブロブを取得する
     * @param[in] repository リポジトリ
     */
    BlobPtr Diff::File::takeBlob(git_repository* repository) const
    {
        if((file_.flags & GIT_DIFF_FLAG_VALID_ID) != 0)
        {
            return Blob::Lookup(repository, &file_.id);
        }
        return Blob::CreateFromWorkdir(repository, getPath());
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
     * @brief 正規かどうか調べる
     * @return 正規なとき真
     */
    bool Diff::Delta::isValid() const
    {
        return delta_ != nullptr;
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
    void Diff::Delta::createHunks(git_repository* repository)
    {
        if(!isValid())
        {
            return;
        }
        if(auto oldBlob = getOldFile().takeBlob(repository))
        {
            if(auto newBlob = getNewFile().takeBlob(repository))
            {
                git_diff_options options;
                git_diff_options_init(&options, GIT_DIFF_OPTIONS_VERSION);
                auto result = git_diff_blobs(oldBlob->getBlob(), 
                                             delta_->old_file.path, 
                                             newBlob->getBlob(), 
                                             delta_->new_file.path, 
                                             &options, 
                                             Diff::Delta::OnFile, 
                                             Diff::Delta::OnBinary, 
                                             Diff::Delta::OnHunk, 
                                             Diff::Delta::OnLine, 
                                             this);
                wxLogDebug("result = %d", result);
            }
        }
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
     */
    int Diff::Delta::OnFile(const git_diff_delta* delta, 
                            float progress, 
                            void* payload)
    {
        return GIT_OK;
    }

    /**
     */
    int Diff::Delta::OnBinary(const git_diff_delta* delta, 
                              const git_diff_binary* binary, 
                              void* payload)
    {
        return GIT_OK;
    }

    /**
     */
    int Diff::Delta::OnHunk(const git_diff_delta*, 
                            const git_diff_hunk* hunk, 
                            void* payload)
    {
        auto delta = reinterpret_cast<Diff::Delta*>(payload);
        delta->getHunks().emplace_back(hunk);
        return GIT_OK;
    }

    /**
     */
    int Diff::Delta::OnLine(const git_diff_delta*, 
                            const git_diff_hunk* hunk, 
                            const git_diff_line* line, 
                            void* payload)
    {
        auto delta = reinterpret_cast<Diff::Delta*>(payload);
        delta->findHunk(hunk).getLines().emplace_back(line);
        return GIT_OK;
    }

    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     * @param[in] diff 差分
     */
    Diff::Diff(const RepositoryPtr& repository, git_diff* diff)
        : RepositoryReference(repository), 
          diff_(diff)
    {
        git_diff_foreach(diff, 
                         Diff::OnFile, 
                         Diff::OnBinary, 
                         Diff::OnHunk, 
                         Diff::OnLine, 
                         this);
    }

    /**
     * @brief コンストラクタ
     * @param[in] commit コミット
     * @param[in] diff 差分
     */
    Diff::Diff(const ConstCommitPtr& commit, git_diff* diff)
        : Diff(commit->getRepository(), diff)
    {
        commit_ = commit;
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
