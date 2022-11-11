#include "wxgit/git/Index.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] index インデックス
     */
    Index::Index(git_index* index)
        : index_(index)
    {
    }

    /**
     * @brief デストラクタ
     */
    Index::~Index()
    {
        git_index_free(index_);
    }

    /**
     * @brief ファイルパスを追加する
     * @param[in] path ファイルパス
     * @return 成功したとき真
     */
    bool Index::addByPath(const wxFileName& path)
    {
        return git_index_add_bypath(index_, path.GetFullPath(wxPATH_UNIX).ToUTF8()) == GIT_OK;
    }

    /**
     * @brief ファイルパスを削除する
     * @param[in] path ファイルパス
     * @return 成功したとき真
     */
    bool Index::removeByPath(const wxFileName& path)
    {
        return git_index_remove_bypath(index_, path.GetFullPath(wxPATH_UNIX).ToUTF8()) == GIT_OK;
    }

    /**
     * @brief インデックスを書き込む
     * @return 成功したとき真
     */
    bool Index::write()
    {
        return git_index_write(index_) == GIT_OK;
    }
}
