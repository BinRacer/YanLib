//
// Created by forkernel on 2025/6/4.
//

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
        LANGID result = GetMUILanguage();
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
        HMODULE dll = LoadLibraryW(L"Comctl32.dll");
        if (dll == nullptr)
            return false;
        typedef int32_t(WINAPI * MirrorIcon)(HICON *, HICON *);
        auto fn = reinterpret_cast<MirrorIcon>(
                GetProcAddress(dll, reinterpret_cast<const char *>(414)));
        if (fn == nullptr) {
            FreeLibrary(dll);
            return false;
        }
        bool result = fn(icon_handle_small, icon_handle_large);
        FreeLibrary(dll);
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
        HMODULE dll = LoadLibraryW(L"Comctl32.dll");
        if (dll == nullptr)
            return false;
        typedef int32_t(WINAPI *
                        DrawTextWrap)(_In_ HDC, _Inout_ const wchar_t *,
                                      _In_ int32_t, _Inout_ RECT *,
                                      _In_ uint32_t, _In_ DRAWTEXTPARAMS *);
        auto fn = reinterpret_cast<DrawTextWrap>(
                GetProcAddress(dll, reinterpret_cast<const char *>(415)));
        if (fn == nullptr) {
            FreeLibrary(dll);
            return false;
        }
        auto temp = helper::convert::str_to_wstr(text, code_page);
        int32_t result = fn(dc_handle, temp.data(), temp.size(), rect,
                            static_cast<uint32_t>(format), param);
        FreeLibrary(dll);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t general::draw_text_wrap(HDC dc_handle,
                                    std::wstring &text,
                                    RECT *rect,
                                    TextFormat format,
                                    DRAWTEXTPARAMS *param) {
        HMODULE dll = LoadLibraryW(L"Comctl32.dll");
        if (dll == nullptr)
            return false;
        typedef int32_t(WINAPI *
                        DrawTextWrap)(_In_ HDC, _Inout_ const wchar_t *,
                                      _In_ int32_t, _Inout_ RECT *,
                                      _In_ uint32_t, _In_ DRAWTEXTPARAMS *);
        auto fn = reinterpret_cast<DrawTextWrap>(
                GetProcAddress(dll, reinterpret_cast<const char *>(415)));
        if (fn == nullptr) {
            FreeLibrary(dll);
            return false;
        }
        int32_t result = fn(dc_handle, text.data(), text.size(), rect,
                            static_cast<uint32_t>(format), param);
        FreeLibrary(dll);
        if (!result) {
            error_code = GetLastError();
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
        HMODULE dll = LoadLibraryW(L"Comctl32.dll");
        if (dll == nullptr)
            return false;
        typedef int32_t(WINAPI *
                        DrawTextExPrivWrap)(_In_ HDC, _Inout_ wchar_t *,
                                            _In_ int32_t, _Inout_ RECT *,
                                            _In_ uint32_t,
                                            _In_ DRAWTEXTPARAMS *);
        auto fn = reinterpret_cast<DrawTextExPrivWrap>(
                GetProcAddress(dll, reinterpret_cast<const char *>(416)));
        if (fn == nullptr) {
            FreeLibrary(dll);
            return false;
        }
        auto temp = helper::convert::str_to_wstr(text, code_page);
        int32_t result = fn(dc_handle, temp.data(), temp.size(), rect,
                            static_cast<uint32_t>(format), param);
        FreeLibrary(dll);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t general::draw_text_priv_wrap(HDC dc_handle,
                                         std::wstring &text,
                                         RECT *rect,
                                         TextFormat format,
                                         DRAWTEXTPARAMS *param) {
        HMODULE dll = LoadLibraryW(L"Comctl32.dll");
        if (dll == nullptr)
            return false;
        typedef int32_t(WINAPI *
                        DrawTextExPrivWrap)(_In_ HDC, _Inout_ wchar_t *,
                                            _In_ int32_t, _Inout_ RECT *,
                                            _In_ uint32_t,
                                            _In_ DRAWTEXTPARAMS *);
        auto fn = reinterpret_cast<DrawTextExPrivWrap>(
                GetProcAddress(dll, reinterpret_cast<const char *>(416)));
        if (fn == nullptr) {
            FreeLibrary(dll);
            return false;
        }
        int32_t result = fn(dc_handle, text.data(), text.size(), rect,
                            static_cast<uint32_t>(format), param);
        FreeLibrary(dll);
        if (!result) {
            error_code = GetLastError();
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
        HMODULE dll = LoadLibraryW(L"Comctl32.dll");
        if (dll == nullptr)
            return false;
        typedef int32_t(WINAPI *
                        ExtTextOutWrap)(_In_ HDC, _In_ int32_t, _In_ int32_t,
                                        _In_ uint32_t, _In_ const RECT *,
                                        _In_ const wchar_t *, _In_ uint32_t,
                                        _In_ const int32_t *);
        auto fn = reinterpret_cast<ExtTextOutWrap>(
                GetProcAddress(dll, reinterpret_cast<const char *>(417)));
        if (fn == nullptr) {
            FreeLibrary(dll);
            return false;
        }
        auto temp = helper::convert::str_to_wstr(text, code_page);
        int32_t result = fn(dc_handle, x, y, static_cast<uint32_t>(option),
                            rect, temp.data(), temp.size(), dx);
        FreeLibrary(dll);
        if (!result) {
            error_code = GetLastError();
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
        HMODULE dll = LoadLibraryW(L"Comctl32.dll");
        if (dll == nullptr)
            return false;
        typedef int32_t(WINAPI *
                        ExtTextOutWrap)(_In_ HDC, _In_ int32_t, _In_ int32_t,
                                        _In_ uint32_t, _In_ const RECT *,
                                        _In_ const wchar_t *, _In_ uint32_t,
                                        _In_ const int32_t *);
        auto fn = reinterpret_cast<ExtTextOutWrap>(
                GetProcAddress(dll, reinterpret_cast<const char *>(417)));
        if (fn == nullptr) {
            FreeLibrary(dll);
            return false;
        }
        int32_t result = fn(dc_handle, x, y, static_cast<uint32_t>(option),
                            rect, text.data(), text.size(), dx);
        FreeLibrary(dll);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool general::get_text_extent_point32_wrap(HDC dc_handle,
                                               std::string &text,
                                               SIZE *size,
                                               helper::CodePage code_page) {
        HMODULE dll = LoadLibraryW(L"Comctl32.dll");
        if (dll == nullptr)
            return false;
        typedef int32_t(WINAPI * GetTextExtentPoint32Wrap)(_In_ HDC,
                                                           _In_ const wchar_t *,
                                                           _In_ uint32_t,
                                                           _Out_ SIZE *);
        auto fn = reinterpret_cast<GetTextExtentPoint32Wrap>(
                GetProcAddress(dll, reinterpret_cast<const char *>(420)));
        if (fn == nullptr) {
            FreeLibrary(dll);
            return false;
        }
        auto temp = helper::convert::str_to_wstr(text, code_page);
        int32_t result = fn(dc_handle, temp.data(), temp.size(), size);
        FreeLibrary(dll);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool general::get_text_extent_point32_wrap(HDC dc_handle,
                                               std::wstring &text,
                                               SIZE *size) {
        HMODULE dll = LoadLibraryW(L"Comctl32.dll");
        if (dll == nullptr)
            return false;
        typedef int32_t(WINAPI * GetTextExtentPoint32Wrap)(_In_ HDC,
                                                           _In_ const wchar_t *,
                                                           _In_ uint32_t,
                                                           _Out_ SIZE *);
        auto fn = reinterpret_cast<GetTextExtentPoint32Wrap>(
                GetProcAddress(dll, reinterpret_cast<const char *>(420)));
        if (fn == nullptr) {
            FreeLibrary(dll);
            return false;
        }
        int32_t result = fn(dc_handle, text.data(), text.size(), size);
        FreeLibrary(dll);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
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

    void *dpa::get_ptr(HDPA dpa_handle, int32_t index) {
        return DPA_GetPtr(dpa_handle, index);
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

    bool dsa::get_item(HDSA dsa_handle, int32_t index, void *item) {
        return DSA_GetItem(dsa_handle, index, item);
    }

    bool dsa::set_item(HDSA dsa_handle, int32_t index, void *item) {
        return DSA_SetItem(dsa_handle, index, item);
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
