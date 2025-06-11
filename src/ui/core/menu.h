/* clang-format off */
/*
 * @file menu.h
 * @date 2025-04-30
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
#ifndef MENU_H
#define MENU_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::ui::core {
#ifndef MENUFLAG
#define MENUFLAG

    enum class MenuFlag : uint32_t {
        // MF_* flag
        Insert = MF_INSERT,
        Change = MF_CHANGE,
        Append = MF_APPEND,
        Delete = MF_DELETE,
        Remove = MF_REMOVE,
        ByCommand = MF_BYCOMMAND,
        ByPosition = MF_BYPOSITION,
        Separator = MF_SEPARATOR,
        Enabled = MF_ENABLED,
        Grayed = MF_GRAYED,
        Disabled = MF_DISABLED,
        Unchecked = MF_UNCHECKED,
        Checked = MF_CHECKED,
        UseCheckBitmaps = MF_USECHECKBITMAPS,
        String = MF_STRING,
        Bitmap = MF_BITMAP,
        OwnerDraw = MF_OWNERDRAW,
        Popup = MF_POPUP,
        MenuBarBreak = MF_MENUBARBREAK,
        MenuBreak = MF_MENUBREAK,
        UnHiLite = MF_UNHILITE,
        HiLite = MF_HILITE,
        Default = MF_DEFAULT,
        SysMenu = MF_SYSMENU,
        Help = MF_HELP,
        RightJustify = MF_RIGHTJUSTIFY,
        MouseSelect = MF_MOUSESELECT,
        End = MF_END,
        // MFT_* flag
        TString = MFT_STRING,
        TBitmap = MFT_BITMAP,
        TMenuBarBreak = MFT_MENUBARBREAK,
        TMenuBreak = MFT_MENUBREAK,
        TOwnerDraw = MFT_OWNERDRAW,
        TRadioCheck = MFT_RADIOCHECK,
        TSeparator = MFT_SEPARATOR,
        TRightOrder = MFT_RIGHTORDER,
        TRightJustify = MFT_RIGHTJUSTIFY,
        // MFS_* flag
        SGrayed = MFS_GRAYED,
        SDisabled = MFS_DISABLED,
        SChecked = MFS_CHECKED,
        SHiLite = MFS_HILITE,
        SEnabled = MFS_ENABLED,
        SUnchecked = MFS_UNCHECKED,
        SUnHiLite = MFS_UNHILITE,
        SDefault = MFS_DEFAULT,
    };

    inline MenuFlag operator|(MenuFlag a, MenuFlag b) {
        return static_cast<MenuFlag>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
#ifndef OBJECTID
#define OBJECTID

    enum class ObjectID : int32_t {
        Window = OBJID_WINDOW,
        SysMenu = OBJID_SYSMENU,
        TitleBar = OBJID_TITLEBAR,
        Menu = OBJID_MENU,
        Client = OBJID_CLIENT,
        VScroll = OBJID_VSCROLL,
        HScroll = OBJID_HSCROLL,
        SizeGrip = OBJID_SIZEGRIP,
        Caret = OBJID_CARET,
        Cursor = OBJID_CURSOR,
        Alert = OBJID_ALERT,
        Sound = OBJID_SOUND,
        QueryClassNameIDX = OBJID_QUERYCLASSNAMEIDX,
        NativeOM = OBJID_NATIVEOM,
    };
#endif
#ifndef MENUSEARCH
#define MENUSEARCH

    enum class MenuSearch : uint32_t {
        Default = 0,
        ShowDisabled = GMDI_USEDISABLED,
        Recursion = GMDI_GOINTOPOPUPS,
    };

    inline MenuSearch operator|(MenuSearch a, MenuSearch b) {
        return static_cast<MenuSearch>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef TRACKPOPUPMENU
#define TRACKPOPUPMENU

    enum class TrackPopup : uint32_t {
        LeftButton = TPM_LEFTBUTTON,
        RightButton = TPM_RIGHTBUTTON,
        LeftAlign = TPM_LEFTALIGN,
        CenterAlign = TPM_CENTERALIGN,
        RightAlign = TPM_RIGHTALIGN,
        TopAlign = TPM_TOPALIGN,
        VCenterAlign = TPM_VCENTERALIGN,
        BottomAlign = TPM_BOTTOMALIGN,
        Horizontal = TPM_HORIZONTAL,
        Vertical = TPM_VERTICAL,
        NoNotify = TPM_NONOTIFY,
        ReturnCmd = TPM_RETURNCMD,
        Recurse = TPM_RECURSE,
        HorPosAnimation = TPM_HORPOSANIMATION,
        HorNegAnimation = TPM_HORNEGANIMATION,
        VerPosAnimation = TPM_VERPOSANIMATION,
        VerNegAnimation = TPM_VERNEGANIMATION,
        NoAnimation = TPM_NOANIMATION,
        LayoutRtl = TPM_LAYOUTRTL,
        WorkArea = TPM_WORKAREA,
    };

    inline TrackPopup operator|(TrackPopup a, TrackPopup b) {
        return static_cast<TrackPopup>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

#endif
    class menu {
    private:
        std::vector<HMENU> menu_handles = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

    public:
        menu(const menu &other) = delete;

        menu(menu &&other) = delete;

        menu &operator=(const menu &other) = delete;

        menu &operator=(menu &&other) = delete;

        menu() = default;

        ~menu();

        HMENU create(bool is_popup = false);

        HMENU load(HINSTANCE instance_handle, const char *menu_name);

        HMENU load(HINSTANCE instance_handle, const wchar_t *menu_name);

        struct MenuItemTemplate {
            uint16_t option;
            uint16_t id;
            std::wstring text;
        };

        struct MenuItemTemplateEx {
            uint32_t type;
            uint32_t state;
            uint32_t id;
            uint16_t flags;
            std::wstring text;
        };

        HMENU load(const std::vector<MenuItemTemplate> &menu_templates);

        HMENU load(uint32_t help_id,
                   const std::vector<MenuItemTemplateEx> &menu_templates);

        bool append(HMENU menu_handle,
                    uintptr_t item_id,
                    const char *item_text,
                    MenuFlag flag = MenuFlag::String);

        bool append(HMENU menu_handle,
                    uintptr_t item_id,
                    const wchar_t *item_text,
                    MenuFlag flag = MenuFlag::String);

        bool insert(HMENU menu_handle,
                    uint32_t pos,
                    uintptr_t item_id,
                    const char *item_text,
                    MenuFlag flag = MenuFlag::ByPosition | MenuFlag::String);

        bool insert(HMENU menu_handle,
                    uint32_t pos,
                    uintptr_t item_id,
                    const wchar_t *item_text,
                    MenuFlag flag = MenuFlag::ByPosition | MenuFlag::String);

        bool remove(HMENU menu_handle, uint32_t pos, bool by_pos = true);

        bool release(HMENU menu_handle, uint32_t pos, bool by_pos = true);

        bool close();

        bool destroy(HMENU menu_handle);

        bool modify(HMENU menu_handle,
                    uint32_t pos,
                    uintptr_t item_id,
                    const char *item_text,
                    MenuFlag flag = MenuFlag::ByPosition | MenuFlag::String);

        bool modify(HMENU menu_handle,
                    uint32_t pos,
                    uintptr_t item_id,
                    const wchar_t *item_text,
                    MenuFlag flag = MenuFlag::ByPosition | MenuFlag::String);

        HMENU get_menu(HWND window_handle);

        bool set_menu(HWND window_handle, HMENU menu_handle);

        bool get_info(HMENU menu_handle, MENUINFO *memu_info);

        bool set_info(HMENU menu_handle, const MENUINFO *memu_info);

        bool get_bar_info(HWND window_handle,
                          int32_t item_id,
                          MENUBARINFO *menu_bar_info,
                          ObjectID flag = ObjectID::Menu);

        uint32_t get_state(HMENU menu_handle, uint32_t pos, bool by_pos = true);

        int32_t get_string(HMENU menu_handle,
                           uint32_t pos,
                           std::string &text,
                           bool by_pos = true);

        int32_t get_string(HMENU menu_handle,
                           uint32_t pos,
                           std::wstring &text,
                           bool by_pos = true);

        HMENU get_sub_menu(HMENU menu_handle, int32_t pos);

        HMENU get_system_menu(HWND window_handle, bool revert = false);

        // std::pair<width, height>
        std::pair<int16_t, int16_t> get_marker_bitmap_size();

        bool is_menu(HMENU menu_handle);

        bool draw_bar(HWND window_handle);

        bool insert_item(HMENU menu_handle,
                         uint32_t pos,
                         const MENUITEMINFOA *menu_item_info,
                         bool is_pos = true);

        bool insert_item(HMENU menu_handle,
                         uint32_t pos,
                         const MENUITEMINFOW *menu_item_info,
                         bool is_pos = true);

        bool get_item_info(HMENU menu_handle,
                           uint32_t pos,
                           MENUITEMINFOA *menu_item_info,
                           bool is_pos = true);

        bool get_item_info(HMENU menu_handle,
                           uint32_t pos,
                           MENUITEMINFOW *menu_item_info,
                           bool is_pos = true);

        bool set_item_info(HMENU menu_handle,
                           uint32_t pos,
                           const MENUITEMINFOA *menu_item_info,
                           bool is_pos = true);

        bool set_item_info(HMENU menu_handle,
                           uint32_t pos,
                           const MENUITEMINFOW *menu_item_info,
                           bool is_pos = true);

        uint32_t get_default_item(HMENU menu_handle,
                                  bool is_pos = true,
                                  MenuSearch search = MenuSearch::Recursion);

        bool
        set_default_item(HMENU menu_handle, uint32_t pos, bool is_pos = true);

        uint32_t get_context_help_id(HMENU menu_handle);

        bool set_context_help_id(HMENU menu_handle, uint32_t help_id);

        int32_t get_item_count(HMENU menu_handle);

        uint32_t get_item_id(HMENU menu_handle, int32_t pos);

        bool get_item_rect(HWND window_handle,
                           HMENU menu_handle,
                           uint32_t pos,
                           RECT *rect);

        bool set_item_bitmaps(HMENU menu_handle,
                              uint32_t pos,
                              HBITMAP unchecked_handle,
                              HBITMAP checked_handle,
                              bool is_pos = true);

        int32_t get_item(HWND window_handle, HMENU menu_handle, POINT screen);

        bool hilite_item(HWND window_handle,
                         HMENU menu_handle,
                         uint32_t pos,
                         MenuFlag flag = MenuFlag::ByPosition |
                                 MenuFlag::HiLite);

        bool unhilite_item(HWND window_handle,
                           HMENU menu_handle,
                           uint32_t pos,
                           MenuFlag flag = MenuFlag::ByPosition |
                                   MenuFlag::UnHiLite);

        MenuFlag check_item(HMENU menu_handle,
                            uint32_t pos,
                            MenuFlag flag = MenuFlag::ByPosition |
                                    MenuFlag::Checked);

        MenuFlag uncheck_item(HMENU menu_handle,
                              uint32_t pos,
                              MenuFlag flag = MenuFlag::ByPosition |
                                      MenuFlag::Unchecked);

        bool check_radio(HMENU menu_handle,
                         uint32_t first,
                         uint32_t last,
                         uint32_t check,
                         bool is_pos = true);

        MenuFlag enable_item(HMENU menu_handle,
                             uint32_t pos,
                             MenuFlag flag = MenuFlag::ByPosition |
                                     MenuFlag::Enabled);

        MenuFlag disable_item(HMENU menu_handle,
                              uint32_t pos,
                              MenuFlag flag = MenuFlag::ByPosition |
                                      MenuFlag::Disabled);

        bool track_popup(HMENU menu_handle,
                         int32_t x,
                         int32_t y,
                         HWND window_handle,
                         TrackPopup flag = TrackPopup::RightAlign |
                                 TrackPopup::BottomAlign |
                                 TrackPopup::ReturnCmd |
                                 TrackPopup::LeftButton);

        bool track_popup(HMENU menu_handle,
                         int32_t x,
                         int32_t y,
                         HWND window_handle,
                         TPMPARAMS *tpm_params = nullptr,
                         TrackPopup flag = TrackPopup::RightAlign |
                                 TrackPopup::BottomAlign |
                                 TrackPopup::ReturnCmd |
                                 TrackPopup::LeftButton);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // MENU_H
