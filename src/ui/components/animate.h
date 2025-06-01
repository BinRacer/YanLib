//
// Created by forkernel on 2025/5/24.
//

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
#include "helper/convert.h"
#pragma comment(lib, "Comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "user32.lib")
namespace YanLib::components {
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
        uint32_t error_code = 0;

    public:
        animate(const animate &other) = delete;

        animate(animate &&other) = delete;

        animate &operator=(const animate &other) = delete;

        animate &operator=(animate &&other) = delete;

        animate() = default;

        ~animate() = default;

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

        bool open(HWND animate_handle,
                  char *file_name,
                  helper::CodePage code_page = helper::CodePage::GB2312);

        bool open(HWND animate_handle, wchar_t *file_name);

        bool open(HWND animate_handle,
                  HINSTANCE dll_handle,
                  char *file_name,
                  helper::CodePage code_page = helper::CodePage::GB2312);

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
} // namespace YanLib::components
#endif // ANIMATE_H
