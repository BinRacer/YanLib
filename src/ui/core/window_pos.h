/* clang-format off */
/*
 * @file window_pos.h
 * @date 2025-05-18
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#ifndef WINDOW_POS_H
#define WINDOW_POS_H
#include <Windows.h>
#include <string>

namespace YanLib::ui::core {
#ifndef POSFLAG
#define POSFLAG

    enum class PosFlag : uint32_t {
        NoSize = SWP_NOSIZE,
        NoMove = SWP_NOMOVE,
        NoZOrder = SWP_NOZORDER,
        NoRedraw = SWP_NOREDRAW,
        NoActivate = SWP_NOACTIVATE,
        FrameChanged = SWP_FRAMECHANGED,
        ShowWindow = SWP_SHOWWINDOW,
        HideWindow = SWP_HIDEWINDOW,
        NoCopyBits = SWP_NOCOPYBITS,
        NoOwnerZOrder = SWP_NOOWNERZORDER,
        NoSendChanging = SWP_NOSENDCHANGING,
        DrawFrame = SWP_DRAWFRAME,
        NoRepos = SWP_NOREPOSITION,
        DeferErase = SWP_DEFERERASE,
        AsyncWindowPos = SWP_ASYNCWINDOWPOS,
    };

    inline PosFlag operator|(PosFlag a, PosFlag b) {
        return static_cast<PosFlag>(static_cast<uint32_t>(a) |
                                    static_cast<uint32_t>(b));
    }
#endif
    class window_pos {
    private:
        uint32_t error_code = 0;

    public:
        window_pos(const window_pos &other) = delete;

        window_pos(window_pos &&other) = delete;

        window_pos &operator=(const window_pos &other) = delete;

        window_pos &operator=(window_pos &&other) = delete;

        window_pos() = default;

        ~window_pos() = default;

        HDWP prepare(int32_t window_num);

        HDWP add(HDWP window_pos_handle,
                 HWND window_handle,
                 HWND insert_after_window_handle = nullptr,
                 int32_t x = CW_USEDEFAULT,
                 int32_t y = CW_USEDEFAULT,
                 int32_t width = CW_USEDEFAULT,
                 int32_t height = CW_USEDEFAULT,
                 PosFlag flag = PosFlag::NoZOrder | PosFlag::ShowWindow);

        bool apply(HDWP window_pos_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // WINDOW_POS_H
