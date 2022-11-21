#pragma once

#include "wxgit/Window.hpp"
#include "wxgit/git/Diff.hpp"

namespace wxgit
{
    /**
     * @brief 差分表示
     */
    class DiffWindow
        : public Window<wxTextCtrl>
    {
        using super = Window<wxTextCtrl>;

    public:
        DiffWindow(MainFrame* mainFrame);
        ~DiffWindow() override = default;

        void clear();
        void showDelta(const git::Diff::Delta& delta);

    private:
        static wxString LineToString(int line);
    };
}
