#include "wxgit/git/Signature.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     */
    Signature::Signature(const git_signature* signature)
	: name_(wxString::FromUTF8(signature->name)), 
	  email_(signature->email), 
	  when_(static_cast<time_t>(signature->when.time))
    {
    }
}
