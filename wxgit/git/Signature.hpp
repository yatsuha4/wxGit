#pragma once

namespace wxgit::git
{
    /**
     * @brief シグネチャ
     */
    class Signature
    {
    private:
	wxString name_;
	wxString email_;
	wxDateTime when_;

    public:
	Signature() = default;
	Signature(const git_signature* signature);
	~Signature() = default;

	WXEDITOR_ACCESSOR(Name, name_);
	WXEDITOR_ACCESSOR(Email, email_);
	WXEDITOR_ACCESSOR(When, when_);
    };
}
