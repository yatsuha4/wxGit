#pragma once

namespace wxgit
{
    /**
     * @brief ウィンドウ
     */
    class Window
    {
    private:
        MainFrame* mainFrame_;

    public:
        Window(MainFrame* mainFrame);
        ~Window() = default;

        WXEDITOR_GETTER(MainFrame, mainFrame_);
    };
}
