#pragma once

#include "wxgit/Window.hpp"
#include "wxgit/git/Diff.hpp"

namespace wxgit
{
    /**
     * @brief 差分表示
     */
    class DiffWindow
        : public Window<wxListCtrl>
    {
        using super = Window<wxListCtrl>;

    private:
        enum Column
        {
            OLD_LINE, 
            NEW_LINE, 
            CONTENT
        };

    public:
        DiffWindow(MainFrame* mainFrame);
        ~DiffWindow() override = default;

        void showDelta(const git::Diff::Delta& delta);

    private:
        static wxString LineToString(int line);
    };
}
