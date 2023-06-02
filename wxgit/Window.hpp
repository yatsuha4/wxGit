#pragma once

namespace wxgit
{
    /**
     * @brief ウィンドウ
     */
    template <class T>
    class Window
        : public T
    {
    private:
        MainFrame* mainFrame_;

    public:
        /**
         * @brief コンストラクタ
         * @param[in] parent 親ウィンドウ
         */
        template <class... Args>
        Window(wxWindow* parent, Args&&... args)
            : T(parent, args...), 
              mainFrame_(MainFrame::Get(parent))
        {
        }

        /**
         * @brief デストラクタ
         */
        ~Window() override = default;

        WXEDITOR_GETTER(MainFrame, mainFrame_);
    };
}
