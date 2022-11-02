#pragma once

#include "wxgit/git/Reference.hpp"

namespace wxgit::git
{
    class Branch
        : public Reference
    {
        using super = Reference;

    private:
        git_branch_t type_;

    public:
        Branch(const RepositoryPtr& repository, 
               git_reference* reference, 
               git_branch_t type);
        ~Branch() = default;

        bool isHead() const;
    };
}
