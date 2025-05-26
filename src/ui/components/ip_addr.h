//
// Created by forkernel on 2025/5/26.
//

#ifndef IP_ADDR_H
#define IP_ADDR_H
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
#include <sstream>
#include <cwctype>
#include <vector>
#include "helper/convert.h"
#pragma comment(lib, "Comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
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
#ifndef IPADDRMESSAGE
#define IPADDRMESSAGE
    enum class IPAddrMessage : uint32_t {
        ClearAddress = IPM_CLEARADDRESS,
        GetAddress = IPM_GETADDRESS,
        IsBlank = IPM_ISBLANK,
        SetAddress = IPM_SETADDRESS,
        SetFocus = IPM_SETFOCUS,
        SetRange = IPM_SETRANGE,
    };
#endif
#ifndef IPADDRNOTIFY
#define IPADDRNOTIFY
    enum class IPAddrNotify : uint32_t {
        FieldChanged = IPN_FIELDCHANGED,
    };
#endif
    class ip_addr {
    private:
        uint32_t error_code = 0;

    public:
        ip_addr(const ip_addr &other) = delete;

        ip_addr(ip_addr &&other) = delete;

        ip_addr &operator=(const ip_addr &other) = delete;

        ip_addr &operator=(ip_addr &&other) = delete;

        HWND create(uintptr_t ip_addr_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border);

        uint32_t make(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

        uint32_t make_range(uint8_t low, uint8_t high);

        uint8_t first(uint32_t ip);

        uint8_t second(uint32_t ip);

        uint8_t third(uint32_t ip);

        uint8_t fourth(uint32_t ip);

        bool get(HWND ip_addr_handle, uint32_t *ip);

        void set(HWND ip_addr_handle, uint32_t ip);

        void clear(HWND ip_addr_handle);

        bool is_empty(HWND ip_addr_handle);

        void set_focus(HWND ip_addr_handle, uint8_t index);

        bool set_range(HWND ip_addr_handle,
                       uint8_t index,
                       uint8_t low = 0,
                       uint8_t high = 255);

        std::string ip_to_string(uint32_t ip);

        std::wstring ip_to_wstring(uint32_t ip);

        bool ip_from_string(const std::string &ip, uint32_t *result);

        bool ip_from_wstring(const std::wstring &ip, uint32_t *result);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::components
#endif // IP_ADDR_H
