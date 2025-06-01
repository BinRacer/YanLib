//
// Created by forkernel on 2025/6/1.
//

#ifndef TOOL_BAR_H
#define TOOL_BAR_H
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
#ifndef TOOLBARSTYLE
#define TOOLBARSTYLE
    enum class ToolBarStyle : uint32_t {
        Button = TBSTYLE_BUTTON,
        Sep = TBSTYLE_SEP,
        Check = TBSTYLE_CHECK,
        Group = TBSTYLE_GROUP,
        CheckGroup = TBSTYLE_CHECKGROUP,
        DropDown = TBSTYLE_DROPDOWN,
        AutoSize = TBSTYLE_AUTOSIZE,
        NoPrefix = TBSTYLE_NOPREFIX,
        ToolTips = TBSTYLE_TOOLTIPS,
        WrapAble = TBSTYLE_WRAPABLE,
        AltDrag = TBSTYLE_ALTDRAG,
        Flat = TBSTYLE_FLAT,
        List = TBSTYLE_LIST,
        CustomErase = TBSTYLE_CUSTOMERASE,
        RegisterDrop = TBSTYLE_REGISTERDROP,
        Transparent = TBSTYLE_TRANSPARENT,
    };
    inline ToolBarStyle operator|(ToolBarStyle a, ToolBarStyle b) {
        return static_cast<ToolBarStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
#endif
#ifndef COMMONSTYLE
#define COMMONSTYLE
    enum class CommonStyle : uint32_t {
        Top = CCS_TOP,
        NoMoveY = CCS_NOMOVEY,
        Bottom = CCS_BOTTOM,
        NoResize = CCS_NORESIZE,
        NoParentAlign = CCS_NOPARENTALIGN,
        Adjustable = CCS_ADJUSTABLE,
        NoDivider = CCS_NODIVIDER,
        Vert = CCS_VERT,
        Left = CCS_LEFT,
        Right = CCS_RIGHT,
        NoMoveX = CCS_NOMOVEX,
    };
    inline CommonStyle operator|(CommonStyle a, CommonStyle b) {
        return static_cast<CommonStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
    inline ToolBarStyle operator|(ToolBarStyle a, CommonStyle b) {
        return static_cast<ToolBarStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
    inline ToolBarStyle operator|(CommonStyle a, ToolBarStyle b) {
        return static_cast<ToolBarStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
    class tool_bar {
    private:
        uint32_t error_code = 0;

    public:
        tool_bar(const tool_bar &other) = delete;

        tool_bar(tool_bar &&other) = delete;

        tool_bar &operator=(const tool_bar &other) = delete;

        tool_bar &operator=(tool_bar &&other) = delete;

        tool_bar() = default;

        ~tool_bar() = default;

        HWND create(HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    ToolBarStyle style = ToolBarStyle::Flat |
                            ToolBarStyle::Transparent | ToolBarStyle::ToolTips |
                            ToolBarStyle::AltDrag | ToolBarStyle::CustomErase |
                            ToolBarStyle::RegisterDrop |
                            ToolBarStyle::AutoSize | CommonStyle::Top |
                            CommonStyle::NoParentAlign |
                            CommonStyle::Adjustable,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const char *tool_bar_name,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    ToolBarStyle style = ToolBarStyle::Flat |
                            ToolBarStyle::Transparent | ToolBarStyle::ToolTips |
                            ToolBarStyle::AltDrag | ToolBarStyle::CustomErase |
                            ToolBarStyle::RegisterDrop |
                            ToolBarStyle::AutoSize | CommonStyle::Top |
                            CommonStyle::NoParentAlign |
                            CommonStyle::Adjustable,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const wchar_t *tool_bar_name,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    ToolBarStyle style = ToolBarStyle::Flat |
                            ToolBarStyle::Transparent | ToolBarStyle::ToolTips |
                            ToolBarStyle::AltDrag | ToolBarStyle::CustomErase |
                            ToolBarStyle::RegisterDrop |
                            ToolBarStyle::AutoSize | CommonStyle::Top |
                            CommonStyle::NoParentAlign |
                            CommonStyle::Adjustable,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::components
#endif // TOOL_BAR_H
