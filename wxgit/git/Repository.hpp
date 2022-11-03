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
	wxFileName dir_;
	git_repository* repository_;
	int error_;
	std::vector<CommitPtr> commits_;
	ConfigPtr config_;

    public:
	Repository(const wxFileName& dir);
	~Repository();

	WXEDITOR_GETTER(Dir, dir_);
	WXEDITOR_GETTER(Config, config_);

	bool isOk() const;

	std::vector<BranchPtr> getBranches(git_branch_t type);
	const std::vector<CommitPtr>& getCommits(bool update = false);
        StatusPtr takeStatus();
        std::vector<RemotePtr> takeRemotes();

        SignaturePtr createSignature() const;

        DiffPtr createDiff() const;

        IndexPtr createIndex() const;

        ReferencePtr head();
    };
}
