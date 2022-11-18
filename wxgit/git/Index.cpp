#include "wxgit/git/Index.hpp"
#include "wxgit/git/Path.hpp"
#include "wxgit/git/Repository.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] repository リポジトリ
     * @param[in] index インデックス
     */
    Index::Index(const RepositoryPtr& repository, git_index* index)
        : repository_(repository), 
          index_(index)
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
     * @brief リポジトリを取得する
     * @return リポジトリ
     */
    RepositoryPtr Index::getRepository() const
    {
        return repository_.lock();
    }

    /**
     * @brief ファイルパスを追加する
     * @param[in] path ファイルパス
     * @return 成功したとき真
     */
    bool Index::add(const Path& path)
    {
        return git_index_add_bypath(index_, path) == GIT_OK;
    }

    /**
     */
    bool Index::cancel(const Path& path)
    {
        return git_index_update_all(index_, nullptr, UpdateCancel, nullptr);
    }

    /**
     * @brief ファイルパスを削除する
     * @param[in] path ファイルパス
     * @param[in] stage ステージ
     * @return 成功したとき真
     */
    bool Index::remove(const Path& path, git_index_stage_t stage)
    {
        return git_index_remove(index_, path, stage) == GIT_OK;
    }

    /**
     * @brief インデックスを書き込む
     * @return 成功したとき真
     */
    bool Index::write()
    {
        return git_index_write(index_) == GIT_OK;
    }

    /**
     * @brief ツリーを取得する
     * @return ツリー
     */
    TreePtr Index::writeTree() const
    {
        git_oid oid;
        if(git_index_write_tree(&oid, index_) == GIT_OK)
        {
            return getRepository()->lookupTree(oid);
        }
        return nullptr;
    }

    int Index::UpdateCancel(const char* path, const char* pathspec, void* payload)
    {
        return 1;
    }
}
