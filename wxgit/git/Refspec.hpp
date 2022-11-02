#pragma once

namespace wxgit::git
{
    /**
     * @brief refspec
     */
    class Refspec
    {
    private:
        const git_refspec* refspec_;
        wxString src_;
        wxString dst_;

    public:
        Refspec(const git_refspec* refspec);
        ~Refspec();

        WXEDITOR_GETTER(Src, src_);
        WXEDITOR_GETTER(Dst, dst_);
    };
}
