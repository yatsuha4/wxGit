namespace wxgit::git
{
    /**
     */
    class Status
    {
    private:
        git_status_list* list_;

    public:
        Status(git_status_list* list);
        ~Status();
    };
}
