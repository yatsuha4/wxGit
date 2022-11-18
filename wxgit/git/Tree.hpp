#pragma once

namespace wxgit::git
{
    /**
     */
    class Tree
    {
    public:
        class Entry
        {
        private:
            const git_tree_entry* entry_;

        public:
            Entry(const git_tree_entry* entry);
            ~Entry() = default;

            wxString getType() const;
            wxString getName() const;
        };

    private:
        git_tree* tree_;
        std::vector<Entry> entries_;

    public:
        Tree(git_tree* tree);
        ~Tree();

        WXEDITOR_GETTER(Tree, tree_);
        WXEDITOR_GETTER(Entries, entries_);

    private:
        static int OnWalk(const char* root, const git_tree_entry* entry, void* payload);
        int onWalk(const char* root, const git_tree_entry* entry);
    };
}
