#pragma once

#include "wxgit/git/RepositoryReference.hpp"

namespace wxgit::git
{
    /**
     * @brief リモート
     */
    class Remote
        : public RepositoryReference
    {
    private:
        git_remote* remote_;
        wxString name_;
        std::vector<RefspecPtr> refspecs_;

    public:
        Remote(RepositoryPtr& repository, git_remote* remote);
        ~Remote();

        WXEDITOR_GETTER(Name, name_);
        WXEDITOR_GETTER(Refspecs, refspecs_);
    };
}
