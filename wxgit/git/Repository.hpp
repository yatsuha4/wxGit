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

        SignaturePtr createSignature() const;

        DiffPtr createDiff();

        IndexPtr takeIndex();

	static RepositoryPtr Open(const Path& dir);
        static RepositoryPtr Init(const Path& dir, bool isBare = false);

    private:
	std::vector<ReferencePtr> takeBranches(git_branch_t type);
    };
}
