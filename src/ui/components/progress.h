//
// Created by forkernel on 2025/5/29.
//

#ifndef PROGRESS_H
#define PROGRESS_H
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
#pragma comment(lib, "Comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "user32.lib")
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
#ifndef PROGRESSSTYLE
#define PROGRESSSTYLE
    enum class ProgressStyle : uint32_t {
        Marquee = PBS_MARQUEE,
        Smooth = PBS_SMOOTH,
        SmoothReverse = PBS_SMOOTHREVERSE,
        Vertical = PBS_VERTICAL,
    };
    inline ProgressStyle operator|(ProgressStyle a, ProgressStyle b) {
        return static_cast<ProgressStyle>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef PROGRESSSTATE
#define PROGRESSSTATE
    enum class ProgressState : uint32_t {
        Normal = PBST_NORMAL,
        Error = PBST_ERROR,
        Paused = PBST_PAUSED,
    };
#endif
#ifndef PROGRESSMESSAGE
#define PROGRESSMESSAGE
    enum class ProgressMessage : uint32_t {
        DeltaPos = PBM_DELTAPOS,
        GetBarColor = PBM_GETBARCOLOR,
        GetBackgroundColor = PBM_GETBKCOLOR,
        GetPos = PBM_GETPOS,
        GetRange = PBM_GETRANGE,
        GetState = PBM_GETSTATE,
        GetStep = PBM_GETSTEP,
        SetBarColor = PBM_SETBARCOLOR,
        SetBackgroundColor = PBM_SETBKCOLOR,
        SetMarquee = PBM_SETMARQUEE,
        SetPos = PBM_SETPOS,
        SetRange = PBM_SETRANGE,
        SetRange32 = PBM_SETRANGE32,
        SetState = PBM_SETSTATE,
        SetStep = PBM_SETSTEP,
        StepIt = PBM_STEPIT
    };
#endif
    class progress {
    private:
        uint32_t error_code = 0;

    public:
        progress(const progress &other) = delete;

        progress(progress &&other) = delete;

        progress &operator=(const progress &other) = delete;

        progress &operator=(progress &&other) = delete;

        progress() = default;

        ~progress() = default;

        HWND create(uintptr_t progress_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ProgressStyle style = ProgressStyle::Smooth,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const char *progress_name,
                    uintptr_t progress_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ProgressStyle style = ProgressStyle::Smooth,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const wchar_t *progress_name,
                    uintptr_t progress_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ProgressStyle style = ProgressStyle::Smooth,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        COLORREF get_bar_color(HWND progress_handle);

        COLORREF set_bar_color(HWND progress_handle, COLORREF color);

        COLORREF get_background_color(HWND progress_handle);

        COLORREF set_background_color(HWND progress_handle, COLORREF color);

        uint32_t get_pos(HWND progress_handle);

        uint32_t set_pos(HWND progress_handle, uint32_t pos);

        void get_range(HWND progress_handle, PBRANGE *range);

        bool set_range(HWND progress_handle, PBRANGE range);

        bool set_range(HWND progress_handle, int32_t low, int32_t high);

        void set_range32(HWND progress_handle, int32_t low, int32_t high);

        ProgressState get_state(HWND progress_handle);

        ProgressState set_state(HWND progress_handle, ProgressState state);

        uint32_t get_step(HWND progress_handle);

        uint32_t set_step(HWND progress_handle, uint32_t step);

        uint32_t set_delta_pos(HWND progress_handle, uint32_t increment);

        void enable_marquee(HWND progress_handle, int32_t milli_second = 0);

        void disable_marquee(HWND progress_handle, int32_t milli_second = 0);

        uint32_t forward_step(HWND progress_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // PROGRESS_H
