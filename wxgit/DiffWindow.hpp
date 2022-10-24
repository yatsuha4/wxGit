#pragma once

namespace wxgit
{
    /**
     * @brief 差分表示
     */
    class DiffWindow
        : public wxScrolledWindow
    {
        using super = wxScrolledWindow;

    public:
        DiffWindow(MainFrame* mainFrame);
        ~DiffWindow() override = default;
    };
}
