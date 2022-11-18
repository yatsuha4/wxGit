#pragma once

#include "wxgit/git/RepositoryReference.hpp"

namespace wxgit::git
{
    /**
     * @brief
     */
    class Reference
        : public RepositoryReference
    {
    private:
        git_reference* reference_;
        wxString name_;

    public:
        Reference(const RepositoryPtr& repository, git_reference* reference);
        ~Reference();

        WXEDITOR_GETTER(Name, name_);

        bool isBranch() const;
        bool isHead() const;

        wxString getBranchName() const;

        CommitPtr takeCommit() const;

    protected:
        WXEDITOR_GETTER(Reference, reference_);
    };
}
