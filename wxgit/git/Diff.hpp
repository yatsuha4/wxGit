#pragma once

namespace wxgit::git
{
    /**
     * @brief 差分
     */
    class Diff
    {
    private:
        git_diff* diff_;

    public:
        Diff(git_diff* diff);
        ~Diff();

        std::vector<wxFileName> getPathes() const;
    };
}
