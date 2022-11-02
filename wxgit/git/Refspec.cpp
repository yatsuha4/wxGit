#include "wxgit/git/Refspec.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] refspec
     */
    Refspec::Refspec(const git_refspec* refspec)
        : refspec_(refspec), 
          src_(wxString::FromUTF8(git_refspec_src(refspec_))), 
          dst_(wxString::FromUTF8(git_refspec_dst(refspec_)))
    {
    }

    /**
     * @brief デストラクタ
     */
    Refspec::~Refspec()
    {
        //git_refspec_free(refspec_);
    }
}
