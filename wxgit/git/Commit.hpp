#pragma once

#include "wxgit/git/RepositoryReference.hpp"

namespace wxgit::git
{
    /**
     * @brief コミット
     */
    class Commit
        : public std::enable_shared_from_this<Commit>, 
          public RepositoryReference
    {
    private:
        git_commit* commit_;
        wxString message_;
        SignaturePtr committer_;
        wxDateTime time_;

    public:
        Commit(const RepositoryPtr& repository, git_commit* commit);
        ~Commit();

        WXEDITOR_GETTER(Commit, commit_);
        WXEDITOR_GETTER(Message, message_);
        WXEDITOR_GETTER(Committer, committer_);
        WXEDITOR_GETTER(Time, time_);

        DiffPtr createDiff() const;
    };
}
