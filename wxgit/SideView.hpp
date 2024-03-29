﻿#pragma once

#include "wxgit/Window.hpp"

namespace wxgit
{
    /**
     * @brief サイドビュー
     */
    class SideView
        : public Window<wxAuiNotebook>
    {
        using super = Window<wxAuiNotebook>;

    private:
        outliner::Outliner* outliner_;
        FileWindow* fileWindow_;

    public:
        SideView(wxWindow* parent);
        ~SideView() override = default;

        WXEDITOR_GETTER(Outliner, outliner_);
        WXEDITOR_GETTER(FileWindow, fileWindow_);

        bool show(wxWindow* window);
    };
}
