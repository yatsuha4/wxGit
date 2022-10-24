#include "wxgit/git/Diff.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] diff 差分
     */
    Diff::Diff(git_diff* diff)
        : diff_(diff)
    {
    }

    /**
     * @brief デストラクタ
     */
    Diff::~Diff()
    {
        git_diff_free(diff_);
    }

    /**
     */
    std::vector<wxFileName> Diff::getPathes() const
    {
        std::vector<wxFileName> pathes;
        for(size_t i = 0, n = git_diff_num_deltas(diff_); i < n; ++i)
        {
            auto delta = git_diff_get_delta(diff_, i);
            pathes.emplace_back(wxString::FromUTF8(delta->new_file.path), wxPATH_UNIX);
        }
        return pathes;
    }
}
