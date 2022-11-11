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
	Path workDir_;
	ConfigPtr config_;
        IndexPtr index_;
	std::vector<CommitPtr> commits_;

    public:
        Repository(git_repository* repository);
	~Repository();

	WXEDITOR_GETTER(WorkDir, workDir_);
	WXEDITOR_GETTER(Config, config_);
        wxString getNamespace() const;

	std::vector<BranchPtr> getBranches(git_branch_t type);
	const std::vector<CommitPtr>& getCommits(bool update = false);
        StatusPtr takeStatus();
        std::vector<RemotePtr> takeRemotes();

        SignaturePtr createSignature() const;

        DiffPtr createDiff();

        IndexPtr takeIndex();

        ReferencePtr head();

	static RepositoryPtr Open(const wxFileName& dir);
        static RepositoryPtr Init(const wxFileName& dir, bool isBare = false);
    };
}
