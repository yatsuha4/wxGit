﻿#pragma once

#include "wxgit/git/Diff.hpp"

namespace wxgit
{
    /**
     * @brief 差分表示
     */
    class DiffWindow
        : public wxListCtrl
    {
        using super = wxListCtrl;

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