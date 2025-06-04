//
// Created by forkernel on 2025/6/4.
//

#include "general.h"
#include <windowsx.h>
namespace YanLib::components {
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
} // namespace YanLib::components
