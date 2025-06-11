/* clang-format off */
/*
 * @file animate.h
 * @date 2025-05-24
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
#ifndef ANIMATE_H
#define ANIMATE_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <cstdint>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "helper/convert.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
#ifndef WINDOWSTYLE
#define WINDOWSTYLE

    enum class WindowStyle : uint32_t {
        Overlapped = WS_OVERLAPPED,
        Popup = WS_POPUP,
        Child = WS_CHILD,
        Minimize = WS_MINIMIZE,
        Visible = WS_VISIBLE,
        Disabled = WS_DISABLED,
        ClipSiblings = WS_CLIPSIBLINGS,
        ClipChildren = WS_CLIPCHILDREN,
        Maximize = WS_MAXIMIZE,
        Caption = WS_CAPTION,
        Border = WS_BORDER,
        DialogFrame = WS_DLGFRAME,
        VScroll = WS_VSCROLL,
        HScroll = WS_HSCROLL,
        SysMenu = WS_SYSMENU,
        ThickFrame = WS_THICKFRAME,
        Group = WS_GROUP,
        TabStop = WS_TABSTOP,
        MinimizeBox = WS_MINIMIZEBOX,
        MaximizeBox = WS_MAXIMIZEBOX,
        Tiled = WS_TILED,
        Iconic = WS_ICONIC,
        SizeBox = WS_SIZEBOX,
        TiledWindow = WS_TILEDWINDOW,
        OverlappedWindow = WS_OVERLAPPEDWINDOW,
        PopupWindow = WS_POPUPWINDOW,
        ChildWindow = WS_CHILDWINDOW,
    };

    inline WindowStyle operator|(WindowStyle a, WindowStyle b) {
        return static_cast<WindowStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef ANIMATESTYLE
#define ANIMATESTYLE

    enum class AnimateStyle : uint32_t {
        Center = ACS_CENTER,
        Transparent = ACS_TRANSPARENT,
        AutoPlay = ACS_AUTOPLAY,
        Timer = ACS_TIMER,
    };

    inline AnimateStyle operator|(AnimateStyle a, AnimateStyle b) {
        return static_cast<AnimateStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
#endif
#ifndef ANIMATEMESSAGE
#define ANIMATEMESSAGE

    enum class AnimateMessage : uint32_t {
        IsPlaying = ACM_ISPLAYING,
        Open = ACM_OPEN,
        Play = ACM_PLAY,
        Stop = ACM_STOP,
    };
#endif
#ifndef ANIMATENOTIFY
#define ANIMATENOTIFY

    enum class AnimateNotify : uint32_t {
        Start = ACN_START,
        Stop = ACN_STOP,
    };
#endif
    class animate {
    private:
        std::vector<HWND> animate_handles = {};
        std::vector<HWND> resource_handles = {};
        sync::rwlock animate_rwlock = {};
        sync::rwlock resource_rwlock = {};
        uint32_t error_code = 0;

    public:
        animate(const animate &other) = delete;

        animate(animate &&other) = delete;

        animate &operator=(const animate &other) = delete;

        animate &operator=(animate &&other) = delete;

        animate();

        ~animate();

        HWND create(uintptr_t animate_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    AnimateStyle style = AnimateStyle::AutoPlay,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const char *animate_name,
                    uintptr_t animate_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    AnimateStyle style = AnimateStyle::AutoPlay,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const wchar_t *animate_name,
                    uintptr_t animate_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    AnimateStyle style = AnimateStyle::AutoPlay,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        bool destroy(HWND animate_handle);

        bool open(HWND animate_handle,
                  const char *file_name,
                  helper::CodePage code_page = helper::curr_code_page());

        bool open(HWND animate_handle, wchar_t *file_name);

        bool open(HWND animate_handle,
                  HINSTANCE dll_handle,
                  const char *file_name,
                  helper::CodePage code_page = helper::curr_code_page());

        bool
        open(HWND animate_handle, HINSTANCE dll_handle, wchar_t *file_name);

        void close(HWND animate_handle);

        bool play(HWND animate_handle,
                  uint32_t from,
                  uint32_t to,
                  uint32_t repeat = 1);

        bool seek(HWND animate_handle, uint32_t frame_index);

        bool stop(HWND animate_handle);

        bool is_playing(HWND animate_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // ANIMATE_H
