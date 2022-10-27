#include "wxgit/git/Signature.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     */
    Signature::Signature(git_signature* signature)
	: Signature(const_cast<const git_signature*>(signature))
    {
        signature_ = signature;
    }
    /**
     * @brief コンストラクタ
     */
    Signature::Signature(const git_signature* signature)
	: signature_(nullptr), 
          name_(wxString::FromUTF8(signature->name)), 
          email_(signature->email), 
          when_(static_cast<time_t>(signature->when.time))
    {
    }

    /**
     * @brief デストラクタ
     */
    Signature::~Signature()
    {
        if(signature_)
        {
            git_signature_free(signature_);
        }
    }
}
