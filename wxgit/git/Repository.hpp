#pragma once

#include "wxgit/git/Path.hpp"

namespace wxgit::git
{
    /**
     * @brief リポジトリ
     */
    class Repository
        : public std::enable_shared_from_this<Repository>
    {
    private:
	git_repository* repository_;
	ConfigPtr config_;
        IndexPtr index_;
	std::vector<CommitPtr> commits_;

    public:
        Repository(git_repository* repository);
	~Repository();

        WXEDITOR_GETTER(Repository, repository_);
	WXEDITOR_GETTER(Config, config_);

        Path getPath() const;
        Path getWorkDir() const;
        wxString getName() const;
        wxString getNamespace() const;

        ReferencePtr takeHead();
        std::vector<ReferencePtr> takeLocalBranches();
        std::vector<ReferencePtr> takeRemoteBranches();

	const std::vector<CommitPtr>& getCommits(bool update = false);

        StatusPtr takeStatus();
        std::vector<RemotePtr> takeRemotes();

        SignaturePtr takeSignature() const;

        DiffPtr createDiff();

        IndexPtr takeIndex();
        CommitPtr commit(const std::vector<Path>& files, 
                         const wxString& message);

        TreePtr lookupTree(const git_oid& oid) const;

	static RepositoryPtr Open(const Path& dir);
        static RepositoryPtr Init(const Path& dir, bool isBare = false);
        static RepositoryPtr Clone(const wxString& url, const Path& dir);

    private:
	std::vector<ReferencePtr> takeBranches(git_branch_t type);
        CommitPtr lookupCommit(const git_oid& oid);
    };
}
