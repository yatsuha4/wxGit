#include "wxgit/git/Branch.hpp"
#include "wxgit/git/Commit.hpp"
#include "wxgit/git/Config.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/git/Status.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] dir ディレクトリ
     */
    Repository::Repository(const wxFileName& dir)
	: dir_(dir), 
	  repository_(nullptr), 
	  error_(GIT_ERROR)
    {
	error_ = git_repository_open(&repository_, dir.GetFullPath().c_str());
	if(isOk())
	{
	    git_config* config;
	    if(git_repository_config(&config, repository_) == GIT_OK)
	    {
		config_ = std::make_shared<Config>(config);
	    }
	}
    }

    /**
     * @brief デストラクタ
     */
    Repository::~Repository()
    {
	if(repository_)
	{
	    git_repository_free(repository_);
	}
    }

    /**
     */
    bool Repository::isOk() const
    {
	return error_ == GIT_OK;
    }

    /**
     */
    std::vector<BranchPtr> Repository::getBranches(git_branch_t type) const
    {
	std::vector<BranchPtr> branches;
	if(isOk())
	{
	    git_branch_iterator* iterator = nullptr;
	    if(git_branch_iterator_new(&iterator, repository_, type) == GIT_OK)
	    {
		git_reference* reference = nullptr;
		while(git_branch_next(&reference, &type, iterator) == GIT_OK)
		{
		    branches.push_back(std::make_shared<Branch>(reference, type));
		}
		git_branch_iterator_free(iterator);
	    }
	}
	return branches;
    }

    /**
     */
    const std::vector<CommitPtr>& Repository::getCommits(bool update)
    {
	if(update || commits_.empty())
	{
	    if(isOk())
	    {
		git_revwalk* walk = nullptr;
		if(git_revwalk_new(&walk, repository_) == GIT_OK)
		{
		    if(git_revwalk_push_head(walk) == GIT_OK)
		    {
			git_oid oid;
			while(git_revwalk_next(&oid, walk) == GIT_OK)
			{
			    git_commit* commit;
			    if(git_commit_lookup(&commit, repository_, &oid) == GIT_OK)
			    {
				commits_.push_back(std::make_shared<Commit>(commit));
			    }
			}
		    }
		    git_revwalk_free(walk);
		}
	    }
	}
	return commits_;
    }

    /**
     * @brief ステータスを取得する
     * @return ステータス
     */
    StatusPtr Repository::fetchStatus() const
    {
        git_status_options options;
        if(git_status_options_init(&options, GIT_STATUS_OPTIONS_VERSION) == GIT_OK)
        {
            git_status_list* list;
            if(git_status_list_new(&list, repository_, &options) == GIT_OK)
            {
                return std::make_shared<Status>(list);
            }
        }
        return nullptr;
    }
}
