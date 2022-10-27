#pragma once

namespace wxgit::git
{
    /**
     * @brief 差分
     */
    class Diff
    {
    public:
        class File
        {
        private:
            const git_diff_file& file_;

        public:
            File(const git_diff_file& file);
            ~File() = default;

            wxFileName getPath() const;
        };

        class Line
        {
        private:
            git_diff_line_t origin_;
            int oldLine_;
            int newLine_;
            int numLines_;
            git_off_t contentOffset_;
            wxString content_;

        public:
            Line(const git_diff_line* line);
            ~Line() = default;

            WXEDITOR_GETTER(Origin, origin_);
            WXEDITOR_GETTER(OldLine, oldLine_);
            WXEDITOR_GETTER(NewLine, newLine_);
            WXEDITOR_GETTER(Content, content_);
        };

        class Hunk
        {
        private:
            const git_diff_hunk* hunk_;
            std::vector<Line> lines_;

        public:
            Hunk(const git_diff_hunk* hunk);
            ~Hunk() = default;

            WXEDITOR_GETTER(Hunk, hunk_);
            WXEDITOR_ACCESSOR(Lines, lines_);
        };

        class Delta
        {
        private:
            const git_diff_delta* delta_;
            std::vector<Hunk> hunks_;

        public:
            Delta(const git_diff_delta* delta);
            ~Delta() = default;

            WXEDITOR_GETTER(Delta, delta_);
            WXEDITOR_ACCESSOR(Hunks, hunks_);
            Hunk& findHunk(const git_diff_hunk* hunk);

            git_delta_t getStatus() const;
            File getOldFile() const;
            File getNewFile() const;
        };

    private:
        ConstCommitPtr commit_;
        git_diff* diff_;
        std::vector<Delta> deltas_;

    public:
        Diff(git_diff* diff);
        Diff(const ConstCommitPtr& commit, git_diff* diff);
        ~Diff();

        WXEDITOR_GETTER(Deltas, deltas_);
        Delta& findDelta(const git_diff_delta* delta);

    private:
        static int OnFile(const git_diff_delta* delta, 
                          float progress, 
                          void* payload);

        static int OnBinary(const git_diff_delta* delta, 
                            const git_diff_binary* binary, 
                            void* payload);

        static int OnHunk(const git_diff_delta* delta, 
                          const git_diff_hunk* hunk, 
                          void* payload);

        static int OnLine(const git_diff_delta* delta, 
                          const git_diff_hunk* hunk, 
                          const git_diff_line* line, 
                          void* payload);
    };
}
