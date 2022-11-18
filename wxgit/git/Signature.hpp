#pragma once

namespace wxgit::git
{
    /**
     * @brief シグネチャ
     */
    class Signature
    {
    private:
        git_signature* signature_;
	wxString name_;
	wxString email_;
	wxDateTime when_;

    public:
	Signature(git_signature* signature);
	Signature(const git_signature* signature);
	~Signature();

        WXEDITOR_GETTER(Signature, signature_);
	WXEDITOR_ACCESSOR(Name, name_);
	WXEDITOR_ACCESSOR(Email, email_);
	WXEDITOR_ACCESSOR(When, when_);
    };
}
