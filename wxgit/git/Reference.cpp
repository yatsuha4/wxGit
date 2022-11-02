#include "wxgit/git/Reference.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     * @param[in] reference リファレンス
     */
    Reference::Reference(const RepositoryPtr& repository, git_reference* reference)
        : repository_(repository), 
          reference_(reference), 
          name_(wxString::FromUTF8(git_reference_name(reference_)))
    {
    }

    /**
     * @brief デストラクタ
     */
    Reference::~Reference()
    {
        git_reference_free(reference_);
    }
}
