#pragma once

namespace wxgit::git
{
    /**
     * @brief
     */
    class Reference
    {
    private:
        std::weak_ptr<Repository> repository_;
        git_reference* reference_;
        wxString name_;

    public:
        Reference(const RepositoryPtr& repository, git_reference* reference);
        ~Reference();

        WXEDITOR_GETTER(Name, name_);
        bool isBranch() const;

    protected:
        WXEDITOR_GETTER(Reference, reference_);
    };
}
