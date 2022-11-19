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
    public:
        /**
         * @brief コンストラクタ
         * @param[in] mainFrame メインフレーム(親)
         */
        template <class... Args>
        Window(MainFrame* mainFrame, Args&&... args)
            : T(mainFrame, args...)
        {
        }

        /**
         * @brief デストラクタ
         */
        ~Window() override = default;

        /**
         * @brief メインフレームを取得する
         * @return メインフレーム
         */
        MainFrame* getMainFrame() const
        {
            return static_cast<MainFrame*>(T::GetParent());
        }
    };
}
