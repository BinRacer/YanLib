//
// Created by forkernel on 2025/4/30.
//

#include "menu.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HMENU menu::create_menu() {
        HMENU menu_handle = CreateMenu();
        if (!menu_handle) {
            error_code = GetLastError();
        }
        return menu_handle;
    }

    HMENU menu::create_popup_menu() {
        HMENU menu_handle = CreatePopupMenu();
        if (!menu_handle) {
            error_code = GetLastError();
        }
        return menu_handle;
    }

    HMENU menu::load_menu(HINSTANCE instance_handle, const wchar_t *menu_name) {
        HMENU menu_handle = LoadMenuW(instance_handle, menu_name);
        if (!menu_handle) {
            error_code = GetLastError();
        }
        return menu_handle;
    }

    HMENU menu::load_menu_indirect(const MENUTEMPLATEW *menu_template) {
        HMENU menu_handle = LoadMenuIndirectW(menu_template);
        if (!menu_handle) {
            error_code = GetLastError();
        }
        return menu_handle;
    }

    bool menu::append_menu(HMENU menu_handle,
                           UINT flag,
                           UINT_PTR id_new_item,
                           const wchar_t *new_item) {
        if (!AppendMenuW(menu_handle, flag, id_new_item, new_item)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::insert_menu(HMENU menu_handle,
                           UINT position,
                           UINT flag,
                           UINT_PTR id_new_item,
                           const wchar_t *new_item) {
        if (!InsertMenuW(menu_handle,
                         position,
                         flag,
                         id_new_item,
                         new_item)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::remove_menu(HMENU menu_handle, UINT position, UINT flag) {
        if (!RemoveMenu(menu_handle, position, flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::delete_menu(HMENU menu_handle, UINT position, UINT flag) {
        if (!DeleteMenu(menu_handle, position, flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::modify_menu(HMENU menu_handle,
                           UINT position,
                           UINT flag,
                           UINT_PTR id_new_item,
                           const wchar_t *new_item) {
        if (!ModifyMenuW(menu_handle,
                         position,
                         flag,
                         id_new_item,
                         new_item)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::set_menu(HWND hwnd, HMENU menu_handle) {
        if (!SetMenu(hwnd, menu_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::set_menu_info(HMENU menu_handle, LPCMENUINFO memu_info) {
        if (!SetMenuInfo(menu_handle, memu_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::get_menu_info(HMENU menu_handle, LPMENUINFO memu_info) {
        if (!GetMenuInfo(menu_handle, memu_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::get_menu_bar_info(HWND hwnd,
                                 LONG id_object,
                                 LONG id_item,
                                 PMENUBARINFO menu_bar_info) {
        if (!GetMenuBarInfo(hwnd, id_object, id_item, menu_bar_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    UINT menu::get_menu_state(HMENU menu_handle, UINT id, UINT flag) {
        return GetMenuState(menu_handle, id, flag);
    }

    int menu::get_menu_string(HMENU menu_handle,
                              UINT id_item,
                              wchar_t *text,
                              int cch_max,
                              UINT flag) {
        return GetMenuStringW(menu_handle,
                              id_item,
                              text,
                              cch_max,
                              flag);
    }

    HMENU menu::get_sub_menu(HMENU menu_handle, int pos) {
        return GetSubMenu(menu_handle, pos);
    }

    HMENU menu::get_system_menu(HWND hwnd, bool revert) {
        return GetSystemMenu(hwnd, revert ? TRUE : FALSE);
    }

    LONG menu::get_menu_check_mark_dimensions() {
        return GetMenuCheckMarkDimensions();
    }

    bool menu::is_menu(HMENU menu_handle) {
        return IsMenu(menu_handle);
    }

    bool menu::end_menu() {
        if (!EndMenu()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::destroy_menu(HMENU menu_handle) {
        if (!DestroyMenu(menu_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::draw_menu_bar(HWND hwnd) {
        if (!DrawMenuBar(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::insert_menu_item(HMENU menu_handle,
                                UINT item,
                                bool is_pos,
                                LPCMENUITEMINFOW menu_item_info) {
        if (!InsertMenuItemW(menu_handle,
                             item,
                             is_pos ? TRUE : FALSE,
                             menu_item_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::get_menu_item_info(HMENU menu_handle,
                                  UINT item,
                                  bool is_pos,
                                  LPMENUITEMINFOW menu_item_info) {
        if (!GetMenuItemInfoW(menu_handle,
                              item,
                              is_pos ? TRUE : FALSE,
                              menu_item_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::set_menu_item_info(HMENU menu_handle,
                                  UINT item,
                                  bool is_pos,
                                  LPCMENUITEMINFOW menu_item_info) {
        if (!SetMenuItemInfoW(menu_handle,
                              item,
                              is_pos ? TRUE : FALSE,
                              menu_item_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    UINT menu::get_menu_default_item(HMENU menu_handle,
                                     bool is_pos,
                                     UINT flag) {
        UINT result = GetMenuDefaultItem(menu_handle,
                                         is_pos ? TRUE : FALSE,
                                         flag);
        if (result == static_cast<UINT>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    bool menu::set_menu_default_item(HMENU menu_handle,
                                     UINT item,
                                     bool is_pos) {
        if (!SetMenuDefaultItem(menu_handle,
                                item,
                                is_pos ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD menu::get_menu_context_help_id(HMENU menu_handle) {
        return GetMenuContextHelpId(menu_handle);
    }

    bool menu::set_menu_context_help_id(HMENU menu_handle, DWORD param) {
        if (!SetMenuContextHelpId(menu_handle, param)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int menu::get_menu_item_count(HMENU menu_handle) {
        int result = GetMenuItemCount(menu_handle);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    UINT menu::get_menu_item_id(HMENU menu_handle, int pos) {
        return GetMenuItemID(menu_handle, pos);
    }

    bool menu::get_menu_item_rect(HWND hwnd,
                                  HMENU menu_handle,
                                  UINT item,
                                  LPRECT rect) {
        if (!GetMenuItemRect(hwnd,
                             menu_handle,
                             item,
                             rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    BOOL menu::set_menu_item_bitmaps(HMENU menu_handle,
                                     UINT position,
                                     UINT flag,
                                     HBITMAP bitmap_unchecked_handle,
                                     HBITMAP bitmap_checked_handle) {
        if (!SetMenuItemBitmaps(menu_handle,
                                position,
                                flag,
                                bitmap_unchecked_handle,
                                bitmap_checked_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }


    int menu::menu_item_from_point(HWND hwnd,
                                   HMENU menu_handle,
                                   POINT point_screen) {
        return MenuItemFromPoint(hwnd,
                                 menu_handle,
                                 point_screen);
    }

    bool menu::hilite_menu_item(HWND hwnd,
                                HMENU menu_handle,
                                UINT id_hilite_item,
                                UINT hilite) {
        return HiliteMenuItem(hwnd,
                              menu_handle,
                              id_hilite_item,
                              hilite);
    }

    DWORD menu::check_menu_item(HMENU menu_handle,
                                UINT id_check_item,
                                UINT check) {
        return CheckMenuItem(menu_handle, id_check_item, check);
    }

    bool menu::check_menu_radio_item(HMENU menu_handle,
                                     UINT first,
                                     UINT last,
                                     UINT check,
                                     UINT flag) {
        if (!CheckMenuRadioItem(menu_handle, first, last, check, flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int menu::enable_menu_item(HMENU menu_handle,
                               UINT id_enable_item,
                               UINT enable) {
        return EnableMenuItem(menu_handle, id_enable_item, enable);
    }

    bool menu::track_popup_menu(HMENU menu_handle,
                                UINT flag,
                                int x,
                                int y,
                                int reserved,
                                HWND hwnd,
                                const RECT *rect) {
        if (!TrackPopupMenu(menu_handle,
                            flag,
                            x,
                            y,
                            reserved,
                            hwnd,
                            rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::track_popup_menu(HMENU menu_handle,
                                UINT flag,
                                int x,
                                int y,
                                HWND hwnd,
                                LPTPMPARAMS tpm_params) {
        if (!TrackPopupMenuEx(menu_handle,
                              flag,
                              x,
                              y,
                              hwnd,
                              tpm_params)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD menu::err_code() const {
        return error_code;
    }

    std::string menu::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring menu::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
