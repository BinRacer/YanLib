//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/31.
//

#ifndef LINK_H
#define LINK_H
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
#ifndef LINKSTYLE
#define LINKSTYLE
    enum class LinkStyle : uint32_t {
        Transparent = LWS_TRANSPARENT,
        IgnoreReturn = LWS_IGNORERETURN,
        NoPrefix = LWS_NOPREFIX,
        UseVisualStyle = LWS_USEVISUALSTYLE,
        UseCustomText = LWS_USECUSTOMTEXT,
        Right = LWS_RIGHT,
    };
    inline LinkStyle operator|(LinkStyle a, LinkStyle b) {
        return static_cast<LinkStyle>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }
#endif
#ifndef LINKMESSAGE
#define LINKMESSAGE
    enum class LinkMessage : uint32_t {
        GetIdealHeight = LM_GETIDEALHEIGHT,
        GetIdealSize = LM_GETIDEALSIZE,
        GetItem = LM_GETITEM,
        HitTest = LM_HITTEST,
        SetItem = LM_SETITEM,
    };
#endif
#ifndef LINKNOTIFY
#define LINKNOTIFY
    enum class LinkNotify : uint32_t {
        Click = NM_CLICK,
    };
#endif
    class link {
    private:
        uint32_t error_code = 0;

    public:
        link(const link &other) = delete;

        link(link &&other) = delete;

        link &operator=(const link &other) = delete;

        link &operator=(link &&other) = delete;

        link() = default;

        ~link() = default;

        HWND create(uintptr_t link_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LinkStyle style = LinkStyle::NoPrefix |
                            LinkStyle::UseVisualStyle |
                            LinkStyle::UseCustomText,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::TabStop);

        HWND create(const char *link_name,
                    uintptr_t link_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LinkStyle style = LinkStyle::NoPrefix |
                            LinkStyle::UseVisualStyle |
                            LinkStyle::UseCustomText,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::TabStop,
                    helper::CodePage code_page = helper::curr_code_page());

        HWND create(const wchar_t *link_name,
                    uintptr_t link_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LinkStyle style = LinkStyle::NoPrefix |
                            LinkStyle::UseVisualStyle |
                            LinkStyle::UseCustomText,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::TabStop);

        int64_t get_ideal_height(HWND link_handle);

        int64_t get_ideal_size(HWND link_handle, int32_t width, SIZE *size);

        bool get_item(HWND link_handle, LITEM *item);

        bool set_item(HWND link_handle, LITEM *item);

        bool hit_test(HWND link_handle, LHITTESTINFO *hit_test_info);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // LINK_H
