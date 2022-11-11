#pragma once

namespace wxgit::git
{
    /**
     * @brief コミット
     */
    class Commit
        : public std::enable_shared_from_this<Commit>
    {
    private:
        std::weak_ptr<Repository> repository_;
        git_commit* commit_;
        git_tree* tree_;
        wxString message_;
        SignaturePtr committer_;
        wxDateTime time_;
        std::vector<BlobPtr> blobs_;

    public:
        Commit(const RepositoryPtr& repository, git_commit* commit);
        ~Commit();

        RepositoryPtr getRepository() const;

        WXEDITOR_GETTER(Message, message_);
        WXEDITOR_GETTER(Committer, committer_);
        WXEDITOR_GETTER(Time, time_);

        const std::vector<BlobPtr>& fetchBlobs();
        DiffPtr createDiff() const;

    private:
        void parseTree(git_tree* tree, const Path& dir);
    };
}
