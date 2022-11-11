#pragma once

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
	int error_;
	wxFileName workDir_;
	std::vector<CommitPtr> commits_;
	ConfigPtr config_;
        IndexPtr index_;

    public:
	Repository(const wxFileName& dir);
	~Repository();

	WXEDITOR_GETTER(WorkDir, workDir_);
	WXEDITOR_GETTER(Config, config_);
        wxString getNamespace() const;

	bool isOk() const;

	std::vector<BranchPtr> getBranches(git_branch_t type);
	const std::vector<CommitPtr>& getCommits(bool update = false);
        StatusPtr takeStatus();
        std::vector<RemotePtr> takeRemotes();

        SignaturePtr createSignature() const;

        DiffPtr createDiff();

        IndexPtr takeIndex();

        ReferencePtr head();
    };
}
