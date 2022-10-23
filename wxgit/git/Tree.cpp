#include "wxgit/git/Tree.hpp"

namespace wxgit::git
{
    /**
     * @brief コンストラクタ
     * @param[in] tree ツリー
     */
    Tree::Tree(git_tree* tree)
        : tree_(tree)
    {
        git_tree_walk(tree_, GIT_TREEWALK_PRE, OnWalk, this);
    }

    /**
     * @brief デストラクタ
     */
    Tree::~Tree()
    {
        git_tree_free(tree_);
    }

    /**
     */
    int Tree::OnWalk(const char* root, const git_tree_entry* entry, void* payload)
    {
        return reinterpret_cast<Tree*>(payload)->onWalk(root, entry);
    }

    /**
     */
    int Tree::onWalk(const char* root, const git_tree_entry* entry)
    {
        entries_.emplace_back(entry);
        return GIT_OK;
    }

    /**
     */
    Tree::Entry::Entry(const git_tree_entry* entry)
        : entry_(entry)
    {
    }

    /**
     */
    wxString Tree::Entry::getType() const
    {
        switch(git_tree_entry_type(entry_))
        {
        case GIT_OBJECT_ANY:
            return wxT("ANY");
        case GIT_OBJECT_INVALID:
            return wxT("INVALID");
        case GIT_OBJECT_COMMIT:
            return wxT("COMMIT");
        case GIT_OBJECT_TREE:
            return wxT("TREE");
        case GIT_OBJECT_BLOB:
            return wxT("BLOB");
        case GIT_OBJECT_TAG:
            return wxT("TAG");
        case GIT_OBJECT_OFS_DELTA:
            return wxT("OFS_DELTA");
        case GIT_OBJECT_REF_DELTA:
            return wxT("REF_DELTA");
        default:
            return wxT("UNKNOWN");
        }
    }

    /**
     */
    wxString Tree::Entry::getName() const
    {
        return wxString::FromUTF8(git_tree_entry_name(entry_));
    }
}
