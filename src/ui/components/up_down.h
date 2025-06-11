/* clang-format off */
/*
 * @file up_down.h
 * @date 2025-06-04
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
#ifndef UP_DOWN_H
#define UP_DOWN_H
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
#ifndef UPDOWNSTYLE
#define UPDOWNSTYLE
    enum class UpDownStyle : uint32_t {
        Wrap = UDS_WRAP,
        SetBuddyInt = UDS_SETBUDDYINT,
        AlignRight = UDS_ALIGNRIGHT,
        AlignLeft = UDS_ALIGNLEFT,
        AutoBuddy = UDS_AUTOBUDDY,
        ArrowKeys = UDS_ARROWKEYS,
        Horiz = UDS_HORZ,
        NoThousands = UDS_NOTHOUSANDS,
        HotTrack = UDS_HOTTRACK,
    };
    inline UpDownStyle operator|(UpDownStyle a, UpDownStyle b) {
        return static_cast<UpDownStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef UPDOWNMESSAGE
#define UPDOWNMESSAGE
    enum class UpDownMessage : uint32_t {
        GetAccel = UDM_GETACCEL,
        GetBase = UDM_GETBASE,
        GetBuddy = UDM_GETBUDDY,
        GetPos = UDM_GETPOS,
        GetPos32 = UDM_GETPOS32,
        GetRange = UDM_GETRANGE,
        GetRange32 = UDM_GETRANGE32,
        GetUnicodeFormat = UDM_GETUNICODEFORMAT,
        SetAccel = UDM_SETACCEL,
        SetBase = UDM_SETBASE,
        SetBuddy = UDM_SETBUDDY,
        SetPos = UDM_SETPOS,
        SetPos32 = UDM_SETPOS32,
        SetRange = UDM_SETRANGE,
        SetRange32 = UDM_SETRANGE32,
        SetUnicodeFormat = UDM_SETUNICODEFORMAT,
    };
#endif
#ifndef UPDOWNNOTIFY
#define UPDOWNNOTIFY
    enum class UpDownNotify : uint32_t {
        ReleasedCapture = NM_RELEASEDCAPTURE,
        DeltaPos = UDN_DELTAPOS,
    };
#endif
    class up_down {
    private:
        std::vector<HWND> up_down_handles = {};
        sync::rwlock up_down_rwlock = {};
        uint32_t error_code = 0;

    public:
        up_down(const up_down &other) = delete;

        up_down(up_down &&other) = delete;

        up_down &operator=(const up_down &other) = delete;

        up_down &operator=(up_down &&other) = delete;

        up_down();

        ~up_down();

        HWND create(uintptr_t up_down_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    UpDownStyle style = UpDownStyle::AlignRight |
                            UpDownStyle::SetBuddyInt | UpDownStyle::ArrowKeys |
                            UpDownStyle::HotTrack | UpDownStyle::Wrap |
                            UpDownStyle::AutoBuddy,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const char *up_down_name,
                    uintptr_t up_down_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    UpDownStyle style = UpDownStyle::AlignRight |
                            UpDownStyle::SetBuddyInt | UpDownStyle::ArrowKeys |
                            UpDownStyle::HotTrack | UpDownStyle::Wrap |
                            UpDownStyle::AutoBuddy,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const wchar_t *up_down_name,
                    uintptr_t up_down_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    UpDownStyle style = UpDownStyle::AlignRight |
                            UpDownStyle::SetBuddyInt | UpDownStyle::ArrowKeys |
                            UpDownStyle::HotTrack | UpDownStyle::Wrap |
                            UpDownStyle::AutoBuddy,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        bool destroy(HWND up_down_handle);

        HWND get_buddy(HWND up_down_handle);

        HWND set_buddy(HWND up_down_handle, HWND buddy_handle);

        // return value = accel.size()
        int64_t get_accel(HWND up_down_handle, std::vector<UDACCEL> &accel);

        bool set_accel(HWND up_down_handle, std::vector<UDACCEL> &accel);

        int64_t get_base(HWND up_down_handle);

        int64_t set_base(HWND up_down_handle, int64_t base);

        // std::pair<bool, pos>
        std::pair<bool, uint16_t> get_pos(HWND up_down_handle);

        uint16_t set_pos(HWND up_down_handle, uint16_t pos);

        uint32_t get_pos32(HWND up_down_handle, bool *is_ok);

        uint32_t set_pos32(HWND up_down_handle, uint32_t pos);

        // std::pair<min, max>
        std::pair<uint16_t, uint16_t> get_range(HWND up_down_handle);

        void set_range(HWND up_down_handle, uint16_t min, uint16_t max);

        void get_range32(HWND up_down_handle, uint32_t *min, uint32_t *max);

        void set_range32(HWND up_down_handle, uint32_t min, uint32_t max);

        bool is_ansi_format(HWND up_down_handle);

        bool is_unicode_format(HWND up_down_handle);

        void set_ansi_format(HWND up_down_handle);

        void set_unicode_format(HWND up_down_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // UP_DOWN_H
