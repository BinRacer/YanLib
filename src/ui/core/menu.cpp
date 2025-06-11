/* clang-format off */
/*
 * @file menu.cpp
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
#include "menu.h"

#include <vector>

#include "helper/convert.h"

namespace YanLib::ui::core {
    menu::~menu() {
        for (auto &menu : menu_handles) {
            if (menu && IsMenu(menu)) {
                DestroyMenu(menu);
                menu = nullptr;
            }
        }
        menu_handles.clear();
    }

    HMENU menu::create(bool is_popup) {
        HMENU menu_handle = is_popup ? CreatePopupMenu() : CreateMenu();
        if (!menu_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        menu_handles.push_back(menu_handle);
        rwlock.write_unlock();
        return menu_handle;
    }

    HMENU menu::load(HINSTANCE instance_handle, const char *menu_name) {
        HMENU menu_handle = LoadMenuA(instance_handle, menu_name);
        if (!menu_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        menu_handles.push_back(menu_handle);
        rwlock.write_unlock();
        return menu_handle;
    }

    HMENU menu::load(HINSTANCE instance_handle, const wchar_t *menu_name) {
        HMENU menu_handle = LoadMenuW(instance_handle, menu_name);
        if (!menu_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        menu_handles.push_back(menu_handle);
        rwlock.write_unlock();
        return menu_handle;
    }

    HMENU menu::load(const std::vector<MenuItemTemplate> &menu_templates) {
        if (menu_templates.empty()) {
            return nullptr;
        }
        uint32_t size = sizeof(MENUITEMTEMPLATEHEADER) +
                (sizeof(MENUITEMTEMPLATE) + sizeof(wchar_t)) *
                        menu_templates.size();
        for (const auto &menu_template : menu_templates) {
            size += (menu_template.text.size() * sizeof(wchar_t));
        }
        std::vector<uint8_t> buffer(size, '\0');
        const auto header =
                reinterpret_cast<MENUITEMTEMPLATEHEADER *>(buffer.data());
        header->versionNumber = 0;
        header->offset = 0;
        auto menu_item = reinterpret_cast<MENUITEMTEMPLATE *>(
                buffer.data() + sizeof(MENUITEMTEMPLATEHEADER));
        for (const auto &menu_template : menu_templates) {
            menu_item->mtOption = menu_template.option;
            menu_item->mtID = menu_template.id;
            memcpy_s(menu_item->mtString,
                     menu_template.text.size() * sizeof(wchar_t),
                     menu_template.text.data(),
                     menu_template.text.size() * sizeof(wchar_t));
            menu_item = reinterpret_cast<MENUITEMTEMPLATE *>(
                    reinterpret_cast<uint8_t *>(menu_item->mtString) +
                    (menu_template.text.size() + 1) * sizeof(wchar_t));
        }
        HMENU menu_handle = LoadMenuIndirectW(buffer.data());
        if (!menu_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        menu_handles.push_back(menu_handle);
        rwlock.write_unlock();
        return menu_handle;
    }

    HMENU menu::load(uint32_t help_id,
                     const std::vector<MenuItemTemplateEx> &menu_templates) {
        if (menu_templates.empty()) {
            return nullptr;
        }
#pragma pack(push, 4)
        typedef struct {
            DWORD dwType;
            DWORD dwState;
            DWORD uId;
            WORD wFlags;
            WCHAR mtString[1];
        } MenuTemplateItem;
        typedef struct {
            DWORD dwVersion;
            DWORD dwOffset;
            DWORD dwHelpId;
        } MenuTemplateHeader;
#pragma pack(pop)
        uint32_t size = sizeof(MenuTemplateHeader) +
                (sizeof(MenuTemplateItem) + sizeof(wchar_t)) *
                        menu_templates.size();
        for (const auto &menu_template : menu_templates) {
            size += (menu_template.text.size() * sizeof(wchar_t));
        }
        std::vector<uint8_t> buffer(size, '\0');
        const auto header =
                reinterpret_cast<MenuTemplateHeader *>(buffer.data());
        header->dwVersion = 1;
        header->dwOffset = 4;
        header->dwHelpId = help_id;
        auto menu_item = reinterpret_cast<MenuTemplateItem *>(
                buffer.data() + sizeof(MenuTemplateHeader));
        for (const auto &menu_template : menu_templates) {
            menu_item->dwType = menu_template.type;
            menu_item->dwState = menu_template.state;
            menu_item->uId = menu_template.id;
            menu_item->wFlags = menu_template.flags;
            memcpy_s(menu_item->mtString,
                     menu_template.text.size() * sizeof(wchar_t),
                     menu_template.text.data(),
                     menu_template.text.size() * sizeof(wchar_t));
            menu_item = reinterpret_cast<MenuTemplateItem *>(
                    reinterpret_cast<uint8_t *>(menu_item->mtString) +
                    (menu_template.text.size() + 1) * sizeof(wchar_t));
        }
        HMENU menu_handle = LoadMenuIndirectW(buffer.data());
        if (!menu_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        menu_handles.push_back(menu_handle);
        rwlock.write_unlock();
        return menu_handle;
    }

    bool menu::append(HMENU menu_handle,
                      uintptr_t item_id,
                      const char *item_text,
                      MenuFlag flag) {
        if (!AppendMenuA(menu_handle, static_cast<uint32_t>(flag), item_id,
                         item_text)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::append(HMENU menu_handle,
                      uintptr_t item_id,
                      const wchar_t *item_text,
                      MenuFlag flag) {
        if (!AppendMenuW(menu_handle, static_cast<uint32_t>(flag), item_id,
                         item_text)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::insert(HMENU menu_handle,
                      uint32_t pos,
                      uintptr_t item_id,
                      const char *item_text,
                      MenuFlag flag) {
        if (!InsertMenuA(menu_handle, pos, static_cast<uint32_t>(flag), item_id,
                         item_text)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::insert(HMENU menu_handle,
                      uint32_t pos,
                      uintptr_t item_id,
                      const wchar_t *item_text,
                      MenuFlag flag) {
        if (!InsertMenuW(menu_handle, pos, static_cast<uint32_t>(flag), item_id,
                         item_text)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::remove(HMENU menu_handle, uint32_t pos, bool by_pos) {
        if (!RemoveMenu(menu_handle, pos,
                        by_pos ? MF_BYPOSITION : MF_BYCOMMAND)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::release(HMENU menu_handle, uint32_t pos, bool by_pos) {
        if (!menu_handle || !IsMenu(menu_handle)) {
            return false;
        }
        rwlock.write_lock();
        const auto it = std::find(menu_handles.begin(), menu_handles.end(),
                                  menu_handle);
        if (it != menu_handles.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        if (!DeleteMenu(menu_handle, pos,
                        by_pos ? MF_BYPOSITION : MF_BYCOMMAND)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::close() {
        if (!EndMenu()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::destroy(HMENU menu_handle) {
        if (!menu_handle || !IsMenu(menu_handle)) {
            return false;
        }
        rwlock.write_lock();
        const auto it = std::find(menu_handles.begin(), menu_handles.end(),
                                  menu_handle);
        if (it != menu_handles.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        if (!DestroyMenu(menu_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::modify(HMENU menu_handle,
                      uint32_t pos,
                      uintptr_t item_id,
                      const char *item_text,
                      MenuFlag flag) {
        if (!ModifyMenuA(menu_handle, pos, static_cast<uint32_t>(flag), item_id,
                         item_text)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::modify(HMENU menu_handle,
                      uint32_t pos,
                      uintptr_t item_id,
                      const wchar_t *item_text,
                      MenuFlag flag) {
        if (!ModifyMenuW(menu_handle, pos, static_cast<uint32_t>(flag), item_id,
                         item_text)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HMENU menu::get_menu(HWND window_handle) {
        return GetMenu(window_handle);
    }

    bool menu::set_menu(HWND window_handle, HMENU menu_handle) {
        if (!menu_handle || !IsMenu(menu_handle)) {
            return false;
        }
        rwlock.write_lock();
        const auto it = std::find(menu_handles.begin(), menu_handles.end(),
                                  menu_handle);
        if (it != menu_handles.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        if (!SetMenu(window_handle, menu_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::get_info(HMENU menu_handle, MENUINFO *memu_info) {
        if (!GetMenuInfo(menu_handle, memu_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::set_info(HMENU menu_handle, const MENUINFO *memu_info) {
        if (!SetMenuInfo(menu_handle, memu_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::get_bar_info(HWND window_handle,
                            int32_t item_id,
                            MENUBARINFO *menu_bar_info,
                            ObjectID flag) {
        if (!GetMenuBarInfo(window_handle, static_cast<int32_t>(flag), item_id,
                            menu_bar_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t menu::get_state(HMENU menu_handle, uint32_t pos, bool by_pos) {
        return GetMenuState(menu_handle, pos,
                            by_pos ? MF_BYPOSITION : MF_BYCOMMAND);
    }

    int32_t menu::get_string(HMENU menu_handle,
                             uint32_t pos,
                             std::string &text,
                             bool by_pos) {
        return GetMenuStringA(menu_handle, pos, text.data(),
                              static_cast<int32_t>(text.size()),
                              by_pos ? MF_BYPOSITION : MF_BYCOMMAND);
    }

    int32_t menu::get_string(HMENU menu_handle,
                             uint32_t pos,
                             std::wstring &text,
                             bool by_pos) {
        return GetMenuStringW(menu_handle, pos, text.data(),
                              static_cast<int32_t>(text.size()),
                              by_pos ? MF_BYPOSITION : MF_BYCOMMAND);
    }

    HMENU menu::get_sub_menu(HMENU menu_handle, int32_t pos) {
        return GetSubMenu(menu_handle, pos);
    }

    HMENU menu::get_system_menu(HWND window_handle, bool revert) {
        return GetSystemMenu(window_handle, revert ? TRUE : FALSE);
    }

    std::pair<int16_t, int16_t> menu::get_marker_bitmap_size() {
        const int32_t size = GetMenuCheckMarkDimensions();
        int16_t width = LOWORD(size);
        int16_t height = HIWORD(size);
        return std::make_pair(width, height);
    }

    bool menu::is_menu(HMENU menu_handle) {
        return IsMenu(menu_handle);
    }

    bool menu::draw_bar(HWND window_handle) {
        if (!DrawMenuBar(window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::insert_item(HMENU menu_handle,
                           uint32_t pos,
                           const MENUITEMINFOA *menu_item_info,
                           bool is_pos) {
        if (!InsertMenuItemA(menu_handle, pos, is_pos ? TRUE : FALSE,
                             menu_item_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::insert_item(HMENU menu_handle,
                           uint32_t pos,
                           const MENUITEMINFOW *menu_item_info,
                           bool is_pos) {
        if (!InsertMenuItemW(menu_handle, pos, is_pos ? TRUE : FALSE,
                             menu_item_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::get_item_info(HMENU menu_handle,
                             uint32_t pos,
                             MENUITEMINFOA *menu_item_info,
                             bool is_pos) {
        if (!GetMenuItemInfoA(menu_handle, pos, is_pos ? TRUE : FALSE,
                              menu_item_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::get_item_info(HMENU menu_handle,
                             uint32_t pos,
                             MENUITEMINFOW *menu_item_info,
                             bool is_pos) {
        if (!GetMenuItemInfoW(menu_handle, pos, is_pos ? TRUE : FALSE,
                              menu_item_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::set_item_info(HMENU menu_handle,
                             uint32_t pos,
                             const MENUITEMINFOA *menu_item_info,
                             bool is_pos) {
        if (!SetMenuItemInfoA(menu_handle, pos, is_pos ? TRUE : FALSE,
                              menu_item_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::set_item_info(HMENU menu_handle,
                             uint32_t pos,
                             const MENUITEMINFOW *menu_item_info,
                             bool is_pos) {
        if (!SetMenuItemInfoW(menu_handle, pos, is_pos ? TRUE : FALSE,
                              menu_item_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t
    menu::get_default_item(HMENU menu_handle, bool is_pos, MenuSearch search) {
        const uint32_t result =
                GetMenuDefaultItem(menu_handle, is_pos ? TRUE : FALSE,
                                   static_cast<uint32_t>(search));
        if (result == static_cast<uint32_t>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    bool menu::set_default_item(HMENU menu_handle, uint32_t pos, bool is_pos) {
        if (!SetMenuDefaultItem(menu_handle, pos, is_pos ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t menu::get_context_help_id(HMENU menu_handle) {
        return GetMenuContextHelpId(menu_handle);
    }

    bool menu::set_context_help_id(HMENU menu_handle, uint32_t help_id) {
        if (!SetMenuContextHelpId(menu_handle, help_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t menu::get_item_count(HMENU menu_handle) {
        const int32_t result = GetMenuItemCount(menu_handle);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t menu::get_item_id(HMENU menu_handle, int32_t pos) {
        return GetMenuItemID(menu_handle, pos);
    }

    bool menu::get_item_rect(HWND window_handle,
                             HMENU menu_handle,
                             uint32_t pos,
                             RECT *rect) {
        if (!GetMenuItemRect(window_handle, menu_handle, pos, rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::set_item_bitmaps(HMENU menu_handle,
                                uint32_t pos,
                                HBITMAP unchecked_handle,
                                HBITMAP checked_handle,
                                bool is_pos) {
        if (!SetMenuItemBitmaps(menu_handle, pos,
                                is_pos ? MF_BYPOSITION : MF_BYCOMMAND,
                                unchecked_handle, checked_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t
    menu::get_item(HWND window_handle, HMENU menu_handle, POINT screen) {
        return MenuItemFromPoint(window_handle, menu_handle, screen);
    }

    bool menu::hilite_item(HWND window_handle,
                           HMENU menu_handle,
                           uint32_t pos,
                           MenuFlag flag) {
        return HiliteMenuItem(window_handle, menu_handle, pos,
                              static_cast<uint32_t>(flag));
    }

    bool menu::unhilite_item(HWND window_handle,
                             HMENU menu_handle,
                             uint32_t pos,
                             MenuFlag flag) {
        return HiliteMenuItem(window_handle, menu_handle, pos,
                              static_cast<uint32_t>(flag));
    }

    MenuFlag menu::check_item(HMENU menu_handle, uint32_t pos, MenuFlag flag) {
        return static_cast<MenuFlag>(
                CheckMenuItem(menu_handle, pos, static_cast<uint32_t>(flag)));
    }

    MenuFlag
    menu::uncheck_item(HMENU menu_handle, uint32_t pos, MenuFlag flag) {
        return static_cast<MenuFlag>(
                CheckMenuItem(menu_handle, pos, static_cast<uint32_t>(flag)));
    }

    bool menu::check_radio(HMENU menu_handle,
                           uint32_t first,
                           uint32_t last,
                           uint32_t check,
                           bool is_pos) {
        if (!CheckMenuRadioItem(menu_handle, first, last, check,
                                is_pos ? MF_BYPOSITION : MF_BYCOMMAND)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    MenuFlag menu::enable_item(HMENU menu_handle, uint32_t pos, MenuFlag flag) {
        return static_cast<MenuFlag>(
                EnableMenuItem(menu_handle, pos, static_cast<uint32_t>(flag)));
    }

    MenuFlag
    menu::disable_item(HMENU menu_handle, uint32_t pos, MenuFlag flag) {
        return static_cast<MenuFlag>(
                EnableMenuItem(menu_handle, pos, static_cast<uint32_t>(flag)));
    }

    bool menu::track_popup(HMENU menu_handle,
                           int32_t x,
                           int32_t y,
                           HWND window_handle,
                           TrackPopup flag) {
        if (!TrackPopupMenu(menu_handle, static_cast<uint32_t>(flag), x, y, 0,
                            window_handle, nullptr)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool menu::track_popup(HMENU menu_handle,
                           int32_t x,
                           int32_t y,
                           HWND window_handle,
                           TPMPARAMS *tpm_params,
                           TrackPopup flag) {
        if (!TrackPopupMenuEx(menu_handle, static_cast<uint32_t>(flag), x, y,
                              window_handle, tpm_params)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t menu::err_code() const {
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
} // namespace YanLib::ui::core
