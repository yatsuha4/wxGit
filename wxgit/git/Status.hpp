﻿#include "wxgit/git/Diff.hpp"

namespace wxgit::git
{
    /**
     */
    class Status
    {
    public:
        class Entry
        {
        private:
            git_status_t status_;
            Diff::Delta headToIndex_;
            Diff::Delta indexToWorkdir_;

        public:
            Entry(const git_status_entry* entry);
            ~Entry() = default;

            WXEDITOR_GETTER(HeadToIndex, headToIndex_);
            WXEDITOR_GETTER(IndexToWorkdir, indexToWorkdir_);
        };

    private:
        std::weak_ptr<Repository> repository_;
        git_status_list* list_;
        std::vector<Entry> entries_;

    public:
        Status(const RepositoryPtr& repository, git_status_list* list);
        ~Status();

        RepositoryPtr getRepository() const;
        WXEDITOR_GETTER(Entries, entries_);
    };
}
