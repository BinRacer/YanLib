/* clang-format off */
/*
 * @file general.cpp
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
#include "general.h"
#include <windowsx.h>
namespace YanLib::ui::components {
    bool general::init_common_controls(const INITCOMMONCONTROLSEX *icc) {
        return InitCommonControlsEx(icc);
    }

    INITCOMMONCONTROLSEX general::make_icc(InitCommControlsFlag flag) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = static_cast<uint32_t>(flag);
        return icc;
    }

    LANGID general::make_lang_id(GeneralLangID lang,
                                 GeneralSubLangId sub_lang) {
        return MAKELANGID(static_cast<uint16_t>(lang),
                          static_cast<uint16_t>(sub_lang));
    }

    void general::init_mui_lang(LANGID lang_id) {
        InitMUILanguage(lang_id);
    }

    LANGID general::get_mui_lang() {
        return GetMUILanguage();
    }

    std::pair<GeneralLangID, GeneralSubLangId> general::get_mui_lang2() {
        const LANGID result = GetMUILanguage();
        return std::make_pair(static_cast<GeneralLangID>(PRIMARYLANGID(result)),
                              static_cast<GeneralSubLangId>(SUBLANGID(result)));
    }

    bool general::load_icon_metric(HINSTANCE instance_handle,
                                   std::string &name,
                                   HICON *icon_handle,
                                   bool is_small,
                                   helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(name, code_page);
        return LoadIconMetric(instance_handle, temp.data(),
                              is_small ? LIM_SMALL : LIM_LARGE,
                              icon_handle) == S_OK;
    }

    bool general::load_icon_metric(HINSTANCE instance_handle,
                                   std::wstring &name,
                                   HICON *icon_handle,
                                   bool is_small) {
        return LoadIconMetric(instance_handle, name.data(),
                              is_small ? LIM_SMALL : LIM_LARGE,
                              icon_handle) == S_OK;
    }

    bool general::load_icon_with_scale_down(HINSTANCE instance_handle,
                                            std::string &name,
                                            int32_t width,
                                            int32_t height,
                                            HICON *icon_handle,
                                            helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(name, code_page);
        return LoadIconWithScaleDown(instance_handle, temp.data(), width,
                                     height, icon_handle) == S_OK;
    }

    bool general::load_icon_with_scale_down(HINSTANCE instance_handle,
                                            std::wstring &name,
                                            int32_t width,
                                            int32_t height,
                                            HICON *icon_handle) {
        return LoadIconWithScaleDown(instance_handle, name.data(), width,
                                     height, icon_handle) == S_OK;
    }

    bool general::mirror_icon(HICON *icon_handle_small,
                              HICON *icon_handle_large) {
        HMODULE comctl32 = nullptr;
        bool result = false;
        do {
            comctl32 = LoadLibraryW(L"Comctl32.dll");
            if (!comctl32) {
                error_code = GetLastError();
                break;
            }
            typedef int32_t(WINAPI * prototype)(HICON *, HICON *);
            const auto func = reinterpret_cast<prototype>(
                    GetProcAddress(comctl32,
                                   reinterpret_cast<const char *>(414)));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            result = func(icon_handle_small, icon_handle_large);
        } while (false);
        if (comctl32) {
            FreeLibrary(comctl32);
        }
        return result;
    }

    int32_t general::draw_shadow_text(HDC dc_handle,
                                      std::string &text,
                                      RECT *rect,
                                      TextFormat format,
                                      COLORREF text_color,
                                      COLORREF shadow_color,
                                      int32_t offset_x,
                                      int32_t offset_y,
                                      helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(text, code_page);
        return DrawShadowText(dc_handle, temp.data(), temp.size(), rect,
                              static_cast<uint32_t>(format), text_color,
                              shadow_color, offset_x, offset_y);
    }

    int32_t general::draw_text_wrap(HDC dc_handle,
                                    std::string &text,
                                    RECT *rect,
                                    TextFormat format,
                                    DRAWTEXTPARAMS *param,
                                    helper::CodePage code_page) {
        HMODULE comctl32 = nullptr;
        int32_t result = 0;
        do {
            comctl32 = LoadLibraryW(L"Comctl32.dll");
            if (!comctl32) {
                error_code = GetLastError();
                break;
            }
            typedef int32_t(WINAPI *
                            DrawTextWrap)(_In_ HDC, _Inout_ const wchar_t *,
                                          _In_ int32_t, _Inout_ RECT *,
                                          _In_ uint32_t, _In_ DRAWTEXTPARAMS *);
            const auto func = reinterpret_cast<DrawTextWrap>(
                    GetProcAddress(comctl32,
                                   reinterpret_cast<const char *>(415)));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            auto temp = helper::convert::str_to_wstr(text, code_page);
            result = func(dc_handle, temp.data(),
                          static_cast<int32_t>(temp.size()), rect,
                          static_cast<uint32_t>(format), param);
            if (!result) {
                error_code = GetLastError();
            }
        } while (false);
        if (comctl32) {
            FreeLibrary(comctl32);
        }
        return result;
    }

    int32_t general::draw_text_wrap(HDC dc_handle,
                                    std::wstring &text,
                                    RECT *rect,
                                    TextFormat format,
                                    DRAWTEXTPARAMS *param) {
        HMODULE comctl32 = nullptr;
        int32_t result = 0;
        do {
            comctl32 = LoadLibraryW(L"Comctl32.dll");
            if (!comctl32) {
                error_code = GetLastError();
                break;
            }
            typedef int32_t(WINAPI *
                            DrawTextWrap)(_In_ HDC, _Inout_ const wchar_t *,
                                          _In_ int32_t, _Inout_ RECT *,
                                          _In_ uint32_t, _In_ DRAWTEXTPARAMS *);
            const auto func = reinterpret_cast<DrawTextWrap>(
                    GetProcAddress(comctl32,
                                   reinterpret_cast<const char *>(415)));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            result = func(dc_handle, text.data(),
                          static_cast<int32_t>(text.size()), rect,
                          static_cast<uint32_t>(format), param);
            if (!result) {
                error_code = GetLastError();
            }
        } while (false);
        if (comctl32) {
            FreeLibrary(comctl32);
        }
        return result;
    }

    int32_t general::draw_shadow_text(HDC dc_handle,
                                      std::wstring &text,
                                      RECT *rect,
                                      TextFormat format,
                                      COLORREF text_color,
                                      COLORREF shadow_color,
                                      int32_t offset_x,
                                      int32_t offset_y) {
        return DrawShadowText(dc_handle, text.data(), text.size(), rect,
                              static_cast<uint32_t>(format), text_color,
                              shadow_color, offset_x, offset_y);
    }

    int32_t general::draw_text_priv_wrap(HDC dc_handle,
                                         std::string &text,
                                         RECT *rect,
                                         TextFormat format,
                                         DRAWTEXTPARAMS *param,
                                         helper::CodePage code_page) {
        HMODULE comctl32 = nullptr;
        int32_t result = 0;
        do {
            comctl32 = LoadLibraryW(L"Comctl32.dll");
            if (!comctl32) {
                error_code = GetLastError();
                break;
            }
            typedef int32_t(WINAPI *
                            DrawTextExPrivWrap)(_In_ HDC, _Inout_ wchar_t *,
                                                _In_ int32_t, _Inout_ RECT *,
                                                _In_ uint32_t,
                                                _In_ DRAWTEXTPARAMS *);
            const auto func = reinterpret_cast<DrawTextExPrivWrap>(
                    GetProcAddress(comctl32,
                                   reinterpret_cast<const char *>(416)));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            auto temp = helper::convert::str_to_wstr(text, code_page);
            result = func(dc_handle, temp.data(),
                          static_cast<int32_t>(temp.size()), rect,
                          static_cast<uint32_t>(format), param);
            if (!result) {
                error_code = GetLastError();
            }
        } while (false);
        if (comctl32) {
            FreeLibrary(comctl32);
        }
        return result;
    }

    int32_t general::draw_text_priv_wrap(HDC dc_handle,
                                         std::wstring &text,
                                         RECT *rect,
                                         TextFormat format,
                                         DRAWTEXTPARAMS *param) {
        HMODULE comctl32 = nullptr;
        int32_t result = 0;
        do {
            comctl32 = LoadLibraryW(L"Comctl32.dll");
            if (!comctl32) {
                error_code = GetLastError();
                break;
            }
            typedef int32_t(WINAPI *
                            DrawTextExPrivWrap)(_In_ HDC, _Inout_ wchar_t *,
                                                _In_ int32_t, _Inout_ RECT *,
                                                _In_ uint32_t,
                                                _In_ DRAWTEXTPARAMS *);
            const auto func = reinterpret_cast<DrawTextExPrivWrap>(
                    GetProcAddress(comctl32,
                                   reinterpret_cast<const char *>(416)));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            result = func(dc_handle, text.data(),
                          static_cast<int32_t>(text.size()), rect,
                          static_cast<uint32_t>(format), param);
            if (!result) {
                error_code = GetLastError();
            }
        } while (false);
        if (comctl32) {
            FreeLibrary(comctl32);
        }
        return result;
    }

    bool general::text_out_wrap(HDC dc_handle,
                                int32_t x,
                                int32_t y,
                                OutputOption option,
                                const RECT *rect,
                                std::string &text,
                                const int32_t dx[],
                                helper::CodePage code_page) {
        HMODULE comctl32 = nullptr;
        int32_t result = 0;
        do {
            comctl32 = LoadLibraryW(L"Comctl32.dll");
            if (!comctl32) {
                error_code = GetLastError();
                break;
            }
            typedef int32_t(WINAPI *
                            ExtTextOutWrap)(_In_ HDC, _In_ int32_t,
                                            _In_ int32_t, _In_ uint32_t,
                                            _In_ const RECT *,
                                            _In_ const wchar_t *, _In_ uint32_t,
                                            _In_ const int32_t *);
            const auto func = reinterpret_cast<ExtTextOutWrap>(
                    GetProcAddress(comctl32,
                                   reinterpret_cast<const char *>(417)));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            auto temp = helper::convert::str_to_wstr(text, code_page);
            result = func(dc_handle, x, y, static_cast<uint32_t>(option), rect,
                          temp.data(), temp.size(), dx);
            if (!result) {
                error_code = GetLastError();
            }
        } while (false);
        if (comctl32) {
            FreeLibrary(comctl32);
        }
        return result;
    }

    bool general::text_out_wrap(HDC dc_handle,
                                int32_t x,
                                int32_t y,
                                OutputOption option,
                                const RECT *rect,
                                std::wstring &text,
                                const int32_t dx[]) {
        HMODULE comctl32 = nullptr;
        int32_t result = 0;
        do {
            comctl32 = LoadLibraryW(L"Comctl32.dll");
            if (!comctl32) {
                error_code = GetLastError();
                break;
            }
            typedef int32_t(WINAPI *
                            ExtTextOutWrap)(_In_ HDC, _In_ int32_t,
                                            _In_ int32_t, _In_ uint32_t,
                                            _In_ const RECT *,
                                            _In_ const wchar_t *, _In_ uint32_t,
                                            _In_ const int32_t *);
            const auto func = reinterpret_cast<ExtTextOutWrap>(
                    GetProcAddress(comctl32,
                                   reinterpret_cast<const char *>(417)));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            result = func(dc_handle, x, y, static_cast<uint32_t>(option), rect,
                          text.data(), text.size(), dx);
            if (!result) {
                error_code = GetLastError();
            }
        } while (false);
        if (comctl32) {
            FreeLibrary(comctl32);
        }
        return result;
    }

    bool general::get_text_extent_point32_wrap(HDC dc_handle,
                                               std::string &text,
                                               SIZE *size,
                                               helper::CodePage code_page) {
        HMODULE comctl32 = nullptr;
        int32_t result = 0;
        do {
            comctl32 = LoadLibraryW(L"Comctl32.dll");
            if (!comctl32) {
                error_code = GetLastError();
                break;
            }
            typedef int32_t(
                    WINAPI *
                    GetTextExtentPoint32Wrap)(_In_ HDC, _In_ const wchar_t *,
                                              _In_ uint32_t, _Out_ SIZE *);
            const auto func = reinterpret_cast<GetTextExtentPoint32Wrap>(
                    GetProcAddress(comctl32,
                                   reinterpret_cast<const char *>(420)));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            auto temp = helper::convert::str_to_wstr(text, code_page);
            result = func(dc_handle, temp.data(), temp.size(), size);
            if (!result) {
                error_code = GetLastError();
            }
        } while (false);
        if (comctl32) {
            FreeLibrary(comctl32);
        }
        return result;
    }

    bool general::get_text_extent_point32_wrap(HDC dc_handle,
                                               std::wstring &text,
                                               SIZE *size) {
        HMODULE comctl32 = nullptr;
        int32_t result = 0;
        do {
            comctl32 = LoadLibraryW(L"Comctl32.dll");
            if (!comctl32) {
                error_code = GetLastError();
                break;
            }
            typedef int32_t(
                    WINAPI *
                    GetTextExtentPoint32Wrap)(_In_ HDC, _In_ const wchar_t *,
                                              _In_ uint32_t, _Out_ SIZE *);
            const auto func = reinterpret_cast<GetTextExtentPoint32Wrap>(
                    GetProcAddress(comctl32,
                                   reinterpret_cast<const char *>(420)));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            result = func(dc_handle, text.data(), text.size(), size);
            if (!result) {
                error_code = GetLastError();
            }
        } while (false);
        if (comctl32) {
            FreeLibrary(comctl32);
        }
        return result;
    }

    ReaderModeInfo
    general::make_reader_mode_info(HWND window_handle,
                                   ReaderModeFlag flag,
                                   RECT *rect,
                                   ReaderScroll scroll_callback,
                                   LPARAM lparam,
                                   TranslateDispatch dispatch_callback) {
        ReaderModeInfo info = {};
        info.size = sizeof(ReaderModeInfo);
        info.window_handle = window_handle;
        info.flag = static_cast<uint32_t>(flag);
        info.rect = rect;
        info.scroll_callback = scroll_callback;
        info.dispatch_callback = dispatch_callback;
        info.lparam = lparam;
        return info;
    }

    void general::do_reader_mode(ReaderModeInfo *reader_mode_info) {
        HMODULE comctl32 = nullptr;
        do {
            comctl32 = LoadLibraryW(L"Comctl32.dll");
            if (!comctl32) {
                error_code = GetLastError();
                break;
            }
            typedef void(WINAPI * DoReaderMode)(_In_ ReaderModeInfo *);
            const auto func = reinterpret_cast<DoReaderMode>(
                    GetProcAddress(comctl32,
                                   reinterpret_cast<const char *>(383)));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            func(reader_mode_info);
        } while (false);
        if (comctl32) {
            FreeLibrary(comctl32);
        }
    }

    void general::get_effective_client_rect(HWND window_handle,
                                            RECT *rect,
                                            const int32_t info[]) {
        GetEffectiveClientRect(window_handle, rect, info);
    }

    bool general::show_hide_menu_control(HWND window_handle,
                                         uintptr_t menu_item_id,
                                         int32_t info[]) {
        return ShowHideMenuCtl(window_handle, menu_item_id, info);
    }

    LRESULT general::forward_notify(HWND window_handle,
                                    int32_t send_item_id,
                                    NMHDR *hdr) {
        return FORWARD_WM_NOTIFY(window_handle, send_item_id, hdr,
                                 SendMessageW);
    }

    bool general::forward_notify2(HWND window_handle,
                                  int32_t send_item_id,
                                  NMHDR *hdr) {
        if (!(FORWARD_WM_NOTIFY(window_handle, send_item_id, hdr,
                                PostMessageW))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void general::handle_notify(HWND window_handle,
                                WPARAM wparam,
                                LPARAM lparam,
                                HandleNotify fn) {
        HANDLE_WM_NOTIFY(window_handle, wparam, lparam, fn);
    }

    uint32_t general::index_to_state_image_mask(int32_t index) {
        return INDEXTOSTATEIMAGEMASK(index);
    }

    void general::dpi_scale(HWND window_handle) {
        SendMessageW(window_handle, CCM_DPISCALE, TRUE, 0);
    }

    void general::set_window_theme(HWND window_handle,
                                   std::string &theme,
                                   helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(theme, code_page);
        SendMessageW(window_handle, CCM_SETWINDOWTHEME, 0,
                     reinterpret_cast<LPARAM>(temp.data()));
    }

    void general::set_window_theme(HWND window_handle, std::wstring &theme) {
        SendMessageW(window_handle, CCM_SETWINDOWTHEME, 0,
                     reinterpret_cast<LPARAM>(theme.data()));
    }

    void
    general::notify(HWND parent_window_handle, int64_t control_id, NMHDR *hdr) {
        SendMessageW(parent_window_handle, WM_NOTIFY, control_id,
                     reinterpret_cast<LPARAM>(hdr));
    }

    NotifyFormatRet general::notify_format(HWND parent_window_handle,
                                           HWND control_handle) {
        return static_cast<NotifyFormatRet>(
                SendMessageW(parent_window_handle, WM_NOTIFYFORMAT,
                             reinterpret_cast<WPARAM>(control_handle),
                             NF_QUERY));
    }

    NotifyFormatRet general::notify_format2(HWND control_handle,
                                            HWND parent_window_handle) {
        return static_cast<NotifyFormatRet>(
                SendMessageW(control_handle, WM_NOTIFYFORMAT,
                             reinterpret_cast<WPARAM>(parent_window_handle),
                             NF_REQUERY));
    }

    int64_t general::get_version(HWND window_handle) {
        return SendMessageW(window_handle, CCM_GETVERSION, 0, 0);
    }

    int64_t general::set_version(HWND window_handle, int64_t version) {
        return SendMessageW(window_handle, CCM_SETVERSION, version, 0);
    }

    bool general::is_ansi_format(HWND window_handle) {
        return !SendMessageW(window_handle, CCM_GETUNICODEFORMAT, 0, 0);
    }

    bool general::is_unicode_format(HWND window_handle) {
        return SendMessageW(window_handle, CCM_GETUNICODEFORMAT, 0, 0);
    }

    void general::set_ansi_format(HWND window_handle) {
        SendMessageW(window_handle, CCM_SETUNICODEFORMAT, FALSE, 0);
    }

    void general::set_unicode_format(HWND window_handle) {
        SendMessageW(window_handle, CCM_SETUNICODEFORMAT, TRUE, 0);
    }

    uint32_t general::err_code() const {
        return error_code;
    }

    std::string general::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring general::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components

namespace YanLib::ui::components {
    HDPA dpa::create(int32_t grow) {
        return DPA_Create(grow);
    }

    HDPA dpa::create(int32_t grow, HANDLE heap_handle) {
        return DPA_CreateEx(grow, heap_handle);
    }

    HDPA dpa::clone(HDPA dpa_handle, HDPA new_dpa_handle) {
        return DPA_Clone(dpa_handle, new_dpa_handle);
    }

    int32_t dpa::insert_ptr(HDPA dpa_handle, int32_t index, void *ptr) {
        return DPA_InsertPtr(dpa_handle, index, ptr);
    }

    int32_t dpa::append_ptr(HDPA dpa_handle, void *ptr) {
        return DPA_AppendPtr(dpa_handle, ptr);
    }

    void *dpa::get_ptr(HDPA dpa_handle, int32_t index) {
        return DPA_GetPtr(dpa_handle, index);
    }

    void **dpa::get_ptr_ptr(HDPA dpa_handle) {
        return DPA_GetPtrPtr(dpa_handle);
    }

    void *dpa::fast_get_ptr(HDPA dpa_handle, int32_t index) {
        return DPA_FastGetPtr(dpa_handle, index);
    }

    void dpa::fast_delete_last_ptr(HDPA dpa_handle) {
        DPA_FastDeleteLastPtr(dpa_handle);
    }

    bool dpa::set_ptr(HDPA dpa_handle, int32_t index, void *ptr) {
        return DPA_SetPtr(dpa_handle, index, ptr);
    }

    void *dpa::delete_ptr(HDPA dpa_handle, int32_t index) {
        return DPA_DeletePtr(dpa_handle, index);
    }

    bool dpa::delete_all_ptrs(HDPA dpa_handle) {
        return DPA_DeleteAllPtrs(dpa_handle);
    }

    bool dpa::destroy(HDPA dpa_handle) {
        return DPA_Destroy(dpa_handle);
    }

    int32_t dpa::get_ptr_count(HDPA dpa_handle) {
        return DPA_GetPtrCount(dpa_handle);
    }

    int32_t dpa::set_ptr_count(HDPA dpa_handle, int32_t count) {
        return DPA_SetPtrCount(dpa_handle, count);
    }

    int32_t dpa::get_ptr_index(HDPA dpa_handle, void *ptr) {
        return DPA_GetPtrIndex(dpa_handle, ptr);
    }

    uint64_t dpa::get_size(HDPA dpa_handle) {
        return DPA_GetSize(dpa_handle);
    }

    bool dpa::grow(HDPA dpa_handle, int32_t ptr_num) {
        return DPA_Grow(dpa_handle, ptr_num);
    }

    int32_t dpa::search(HDPA dpa_handle,
                        void *search,
                        int32_t start,
                        PFNDACOMPARE compare,
                        LPARAM lparam,
                        DPASearchOption option) {
        return DPA_Search(dpa_handle, search, start, compare, lparam,
                          static_cast<uint32_t>(option));
    }

    bool dpa::sort(HDPA dpa_handle, PFNDACOMPARE compare, LPARAM lparam) {
        return DPA_Sort(dpa_handle, compare, lparam);
    }

    int32_t dpa::sorted_insert_ptr(HDPA dpa_handle,
                                   void *search,
                                   int32_t start,
                                   PFNDACOMPARE compare,
                                   LPARAM lparam,
                                   DPASearchOption option,
                                   void *ptr) {
        return DPA_SortedInsertPtr(dpa_handle, search, start, compare, lparam,
                                   static_cast<uint32_t>(option), ptr);
    }

    bool dpa::merge(HDPA dpa_handle_dst,
                    HDPA dpa_handle_src,
                    DPAMergeOption option,
                    PFNDACOMPARE compare,
                    PFNDPAMERGE merge,
                    LPARAM lparam) {
        return DPA_Merge(dpa_handle_dst, dpa_handle_src,
                         static_cast<uint32_t>(option), compare, merge, lparam);
    }

    void dpa::enum_callback(HDPA dpa_handle,
                            PFNDAENUMCALLBACK callback,
                            void *data) {
        DPA_EnumCallback(dpa_handle, callback, data);
    }

    void dpa::destroy_callback(HDPA dpa_handle,
                               PFNDAENUMCALLBACK callback,
                               void *data) {
        DPA_DestroyCallback(dpa_handle, callback, data);
    }

    bool dpa::load_stream(HDPA *dpa_handle,
                          IStream *stream,
                          PFNDPASTREAM callback,
                          void *data) {
        return DPA_LoadStream(dpa_handle, callback, stream, data) == S_OK;
    }

    bool dpa::save_stream(HDPA dpa_handle,
                          IStream *stream,
                          PFNDPASTREAM callback,
                          void *data) {
        return DPA_SaveStream(dpa_handle, callback, stream, data) == S_OK;
    }
} // namespace YanLib::ui::components


namespace YanLib::ui::components {
    HDSA dsa::create(int32_t item_size, int32_t item_count) {
        return DSA_Create(item_size, item_count);
    }

    HDSA dsa::clone(HDSA dsa_handle) {
        return DSA_Clone(dsa_handle);
    }

    int32_t dsa::insert_item(HDSA dsa_handle, int32_t index, void *item) {
        return DSA_InsertItem(dsa_handle, index, item);
    }

    int32_t dsa::append_item(HDSA dsa_handle, void *item) {
        return DSA_AppendItem(dsa_handle, item);
    }

    bool dsa::get_item(HDSA dsa_handle, int32_t index, void *item) {
        return DSA_GetItem(dsa_handle, index, item);
    }

    bool dsa::set_item(HDSA dsa_handle, int32_t index, void *item) {
        return DSA_SetItem(dsa_handle, index, item);
    }

    int32_t dsa::get_item_count(HDSA dsa_handle) {
        return DSA_GetItemCount(dsa_handle);
    }

    void *dsa::get_item_ptr(HDSA dsa_handle, int32_t index) {
        return DSA_GetItemPtr(dsa_handle, index);
    }

    uint64_t dsa::get_size(HDSA dsa_handle) {
        return DSA_GetSize(dsa_handle);
    }

    bool dsa::sort(HDSA dsa_handle, PFNDACOMPARE compare, LPARAM lparam) {
        return DSA_Sort(dsa_handle, compare, lparam);
    }

    bool dsa::delete_item(HDSA dsa_handle, int32_t index) {
        return DSA_DeleteItem(dsa_handle, index);
    }

    bool dsa::delete_all_items(HDSA dsa_handle) {
        return DSA_DeleteAllItems(dsa_handle);
    }

    bool dsa::destroy(HDSA dsa_handle) {
        return DSA_Destroy(dsa_handle);
    }

    void dsa::enum_callback(HDSA dsa_handle,
                            PFNDAENUMCALLBACK callback,
                            void *data) {
        DSA_EnumCallback(dsa_handle, callback, data);
    }

    void dsa::destroy_callback(HDSA dsa_handle,
                               PFNDAENUMCALLBACK callback,
                               void *data) {
        DSA_DestroyCallback(dsa_handle, callback, data);
    }
} // namespace YanLib::ui::components
