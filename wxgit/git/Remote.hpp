#pragma once

namespace wxgit::git
{
    /**
     * @brief リモート
     */
    class Remote
    {
    private:
        std::weak_ptr<Repository> repository_;
        git_remote* remote_;
        wxString name_;

    public:
        Remote(RepositoryPtr& repository, git_remote* remote);
        ~Remote();

        RepositoryPtr getRepository() const;

        WXEDITOR_GETTER(Name, name_);
    };
}
