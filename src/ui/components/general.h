/* clang-format off */
/*
 * @file general.h
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
#ifndef GENERAL_H
#define GENERAL_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <WinUser.h>
#include <windef.h>
#include <minwindef.h>
#include <winnt.h>
#include <cstdint>
#include <string>
#include "helper/convert.h"
#include "ui/gdi/gdi.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class general {
    private:
        uint32_t error_code = 0;

    public:
        general(const general &other) = delete;

        general(general &&other) = delete;

        general &operator=(const general &other) = delete;

        general &operator=(general &&other) = delete;

        general() = default;

        ~general() = default;

        bool init_common_controls(const INITCOMMONCONTROLSEX *icc);

        INITCOMMONCONTROLSEX
        make_icc(InitCommControlsFlag flag = InitCommControlsFlag::ListView |
                         InitCommControlsFlag::TreeView |
                         InitCommControlsFlag::Bar | InitCommControlsFlag::Tab |
                         InitCommControlsFlag::UpDown |
                         InitCommControlsFlag::Progress |
                         InitCommControlsFlag::HotKey |
                         InitCommControlsFlag::Animate |
                         InitCommControlsFlag::Win95 |
                         InitCommControlsFlag::Date |
                         InitCommControlsFlag::UserEx |
                         InitCommControlsFlag::Cool |
                         InitCommControlsFlag::Internet |
                         InitCommControlsFlag::PageScroller |
                         InitCommControlsFlag::NativeFntCtl |
                         InitCommControlsFlag::Standard |
                         InitCommControlsFlag::Link);

        LANGID
        make_lang_id(GeneralLangID lang = GeneralLangID::ChineseSimplified,
                     GeneralSubLangId sub_lang =
                             GeneralSubLangId::ChineseSimplified);

        void init_mui_lang(LANGID lang_id);

        LANGID get_mui_lang();

        std::pair<GeneralLangID, GeneralSubLangId> get_mui_lang2();

        bool
        load_icon_metric(HINSTANCE instance_handle,
                         std::string &name,
                         HICON *icon_handle,
                         bool is_small = false,
                         helper::CodePage code_page = helper::curr_code_page());

        bool load_icon_metric(HINSTANCE instance_handle,
                              std::wstring &name,
                              HICON *icon_handle,
                              bool is_small = false);

        bool load_icon_with_scale_down(
                HINSTANCE instance_handle,
                std::string &name,
                int32_t width,
                int32_t height,
                HICON *icon_handle,
                helper::CodePage code_page = helper::curr_code_page());

        bool load_icon_with_scale_down(HINSTANCE instance_handle,
                                       std::wstring &name,
                                       int32_t width,
                                       int32_t height,
                                       HICON *icon_handle);

        bool mirror_icon(HICON *icon_handle_small, HICON *icon_handle_large);

        int32_t
        draw_shadow_text(HDC dc_handle,
                         std::string &text,
                         RECT *rect,
                         gdi::TextFormat format,
                         COLORREF text_color,
                         COLORREF shadow_color,
                         int32_t offset_x,
                         int32_t offset_y,
                         helper::CodePage code_page = helper::curr_code_page());

        int32_t draw_shadow_text(HDC dc_handle,
                                 std::wstring &text,
                                 RECT *rect,
                                 gdi::TextFormat format,
                                 COLORREF text_color,
                                 COLORREF shadow_color,
                                 int32_t offset_x,
                                 int32_t offset_y);

        int32_t
        draw_text_wrap(HDC dc_handle,
                       std::string &text,
                       RECT *rect,
                       gdi::TextFormat format,
                       DRAWTEXTPARAMS *param = nullptr,
                       helper::CodePage code_page = helper::curr_code_page());

        int32_t draw_text_wrap(HDC dc_handle,
                               std::wstring &text,
                               RECT *rect,
                               gdi::TextFormat format,
                               DRAWTEXTPARAMS *param = nullptr);

        int32_t draw_text_priv_wrap(
                HDC dc_handle,
                std::string &text,
                RECT *rect,
                gdi::TextFormat format,
                DRAWTEXTPARAMS *param = nullptr,
                helper::CodePage code_page = helper::curr_code_page());

        int32_t draw_text_priv_wrap(HDC dc_handle,
                                    std::wstring &text,
                                    RECT *rect,
                                    gdi::TextFormat format,
                                    DRAWTEXTPARAMS *param = nullptr);

        bool
        text_out_wrap(HDC dc_handle,
                      int32_t x,
                      int32_t y,
                      gdi::OutputOption option,
                      const RECT *rect,
                      std::string &text,
                      const int32_t dx[],
                      helper::CodePage code_page = helper::curr_code_page());

        bool text_out_wrap(HDC dc_handle,
                           int32_t x,
                           int32_t y,
                           gdi::OutputOption option,
                           const RECT *rect,
                           std::wstring &text,
                           const int32_t dx[]);

        bool get_text_extent_point32_wrap(
                HDC dc_handle,
                std::string &text,
                SIZE *size,
                helper::CodePage code_page = helper::curr_code_page());

        bool get_text_extent_point32_wrap(HDC dc_handle,
                                          std::wstring &text,
                                          SIZE *size);

        ReaderModeInfo
        make_reader_mode_info(HWND window_handle,
                              ReaderModeFlag flag,
                              RECT *rect,
                              ReaderScroll scroll_callback,
                              LPARAM lparam,
                              TranslateDispatch dispatch_callback);

        void do_reader_mode(ReaderModeInfo *reader_mode_info);

        void get_effective_client_rect(HWND window_handle,
                                       RECT *rect,
                                       const int32_t info[]);

        bool show_hide_menu_control(HWND window_handle,
                                    uintptr_t menu_item_id,
                                    int32_t info[]);

        // forward notify to SendMessageW
        LRESULT
        forward_notify(HWND window_handle, int32_t send_item_id, NMHDR *hdr);

        // forward notify to PostMessageW
        bool
        forward_notify2(HWND window_handle, int32_t send_item_id, NMHDR *hdr);

        typedef void(CALLBACK *HandleNotify)(HWND, int32_t, NMHDR *);

        void handle_notify(HWND window_handle,
                           WPARAM wparam,
                           LPARAM lparam,
                           HandleNotify fn);

        uint32_t index_to_state_image_mask(int32_t index);

        void dpi_scale(HWND window_handle);

        void
        set_window_theme(HWND window_handle,
                         std::string &theme,
                         helper::CodePage code_page = helper::curr_code_page());

        void set_window_theme(HWND window_handle, std::wstring &theme);

        void notify(HWND parent_window_handle, int64_t control_id, NMHDR *hdr);

        NotifyFormatRet notify_format(HWND parent_window_handle,
                                      HWND control_handle);

        NotifyFormatRet notify_format2(HWND control_handle,
                                       HWND parent_window_handle);

        int64_t get_version(HWND window_handle);

        int64_t set_version(HWND window_handle, int64_t version);

        bool is_ansi_format(HWND window_handle);

        bool is_unicode_format(HWND window_handle);

        void set_ansi_format(HWND window_handle);

        void set_unicode_format(HWND window_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };

    class dpa {
    public:
        dpa(const dpa &other) = delete;

        dpa(dpa &&other) = delete;

        dpa &operator=(const dpa &other) = delete;

        dpa &operator=(dpa &&other) = delete;

        dpa() = default;

        ~dpa() = default;

        static HDPA create(int32_t grow);

        static HDPA create(int32_t grow, HANDLE heap_handle);

        static HDPA clone(HDPA dpa_handle, HDPA new_dpa_handle);

        static int32_t insert_ptr(HDPA dpa_handle, int32_t index, void *ptr);

        static int32_t append_ptr(HDPA dpa_handle, void *ptr);

        static void *get_ptr(HDPA dpa_handle, int32_t index);

        static bool set_ptr(HDPA dpa_handle, int32_t index, void *ptr);

        static void **get_ptr_ptr(HDPA dpa_handle);

        static void *fast_get_ptr(HDPA dpa_handle, int32_t index);

        static void fast_delete_last_ptr(HDPA dpa_handle);

        static void *delete_ptr(HDPA dpa_handle, int32_t index);

        static bool delete_all_ptrs(HDPA dpa_handle);

        static bool destroy(HDPA dpa_handle);

        static int32_t get_ptr_count(HDPA dpa_handle);

        static int32_t set_ptr_count(HDPA dpa_handle, int32_t count);

        static int32_t get_ptr_index(HDPA dpa_handle, void *ptr);

        static uint64_t get_size(HDPA dpa_handle);

        static bool grow(HDPA dpa_handle, int32_t ptr_num);

        static int32_t search(HDPA dpa_handle,
                              void *search,
                              int32_t start,
                              PFNDACOMPARE compare,
                              LPARAM lparam,
                              DPASearchOption option);

        static bool sort(HDPA dpa_handle, PFNDACOMPARE compare, LPARAM lparam);

        static int32_t sorted_insert_ptr(HDPA dpa_handle,
                                         void *search,
                                         int32_t start,
                                         PFNDACOMPARE compare,
                                         LPARAM lparam,
                                         DPASearchOption option,
                                         void *ptr);

        static bool merge(HDPA dpa_handle_dst,
                          HDPA dpa_handle_src,
                          DPAMergeOption option,
                          PFNDACOMPARE compare,
                          PFNDPAMERGE merge,
                          LPARAM lparam);

        static void
        enum_callback(HDPA dpa_handle, PFNDAENUMCALLBACK callback, void *data);

        static void destroy_callback(HDPA dpa_handle,
                                     PFNDAENUMCALLBACK callback,
                                     void *data);

        static bool load_stream(HDPA *dpa_handle,
                                IStream *stream,
                                PFNDPASTREAM callback,
                                void *data);

        static bool save_stream(HDPA dpa_handle,
                                IStream *stream,
                                PFNDPASTREAM callback,
                                void *data);
    };

    class dsa {
    public:
        dsa(const dsa &other) = delete;

        dsa(dsa &&other) = delete;

        dsa &operator=(const dsa &other) = delete;

        dsa &operator=(dsa &&other) = delete;

        dsa() = default;

        ~dsa() = default;

        static HDSA create(int32_t item_size, int32_t item_count);

        static HDSA clone(HDSA dsa_handle);

        static int32_t insert_item(HDSA dsa_handle, int32_t index, void *item);

        static int32_t append_item(HDSA dsa_handle, void *item);

        static bool get_item(HDSA dsa_handle, int32_t index, void *item);

        static bool set_item(HDSA dsa_handle, int32_t index, void *item);

        static int32_t get_item_count(HDSA dsa_handle);

        static void *get_item_ptr(HDSA dsa_handle, int32_t index);

        static uint64_t get_size(HDSA dsa_handle);

        static bool sort(HDSA dsa_handle, PFNDACOMPARE compare, LPARAM lparam);

        static bool delete_item(HDSA dsa_handle, int32_t index);

        static bool delete_all_items(HDSA dsa_handle);

        static bool destroy(HDSA dsa_handle);

        static void
        enum_callback(HDSA dsa_handle, PFNDAENUMCALLBACK callback, void *data);

        static void destroy_callback(HDSA dsa_handle,
                                     PFNDAENUMCALLBACK callback,
                                     void *data);
    };
} // namespace YanLib::ui::components
#endif // GENERAL_H
