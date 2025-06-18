/* clang-format off */
/*
 * @file rich_edit.h
 * @date 2025-05-30
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
#ifndef RICH_EDIT_H
#define RICH_EDIT_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <minwindef.h>
#include <windef.h>
#include <Richedit.h>
#include <RichOle.h>
#include <cstdint>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "helper/convert.h"
#include "ui/core/core.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class rich_edit {
    private:
        HMODULE rich_edit_dll = nullptr;
        std::vector<HWND> rich_edit_handles = {};
        sync::rwlock rich_edit_rwlock = {};
        uint32_t error_code = 0;

    public:
        rich_edit(const rich_edit &other) = delete;

        rich_edit(rich_edit &&other) = delete;

        rich_edit &operator=(const rich_edit &other) = delete;

        rich_edit &operator=(rich_edit &&other) = delete;

        rich_edit();

        ~rich_edit();

        HWND create(uintptr_t rich_edit_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    RichEditStyle style = RichEditStyle::Multiline |
                            RichEditStyle::AutoHScroll |
                            RichEditStyle::AutoVScroll | RichEditStyle::Left |
                            RichEditStyle::WantReturn,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border |
                            core::WindowStyle::TabStop);

        HWND create(const char *rich_edit_name,
                    uintptr_t rich_edit_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    RichEditStyle style = RichEditStyle::Multiline |
                            RichEditStyle::AutoHScroll |
                            RichEditStyle::AutoVScroll | RichEditStyle::Left |
                            RichEditStyle::WantReturn,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border |
                            core::WindowStyle::TabStop);

        HWND create(const wchar_t *rich_edit_name,
                    uintptr_t rich_edit_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    RichEditStyle style = RichEditStyle::Multiline |
                            RichEditStyle::AutoHScroll |
                            RichEditStyle::AutoVScroll | RichEditStyle::Left |
                            RichEditStyle::WantReturn,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border |
                            core::WindowStyle::TabStop);

        bool destroy(HWND rich_edit_handle);

        bool is_auto_url_detect_enabled(HWND rich_edit_handle);

        bool
        set_auto_url_detect(HWND rich_edit_handle,
                            REAutoUrlDetect state = REAutoUrlDetect::EnableUrl);

        AutoCorrectProc get_auto_correct_proc(HWND rich_edit_handle);

        bool set_auto_correct_proc(HWND rich_edit_handle, AutoCorrectProc func);

        bool call_auto_correct_proc(HWND rich_edit_handle, wchar_t ch);

        void get_select(HWND rich_edit_handle, CHARRANGE *range);

        void set_select(HWND rich_edit_handle, CHARRANGE *range);

        int64_t
        get_select_text(HWND rich_edit_handle,
                        std::string &text,
                        helper::CodePage code_page = helper::curr_code_page());

        int64_t get_select_text(HWND rich_edit_handle, std::wstring &text);

        void show_select(HWND rich_edit_handle);

        void hide_select(HWND rich_edit_handle);

        RESelectType get_select_type(HWND rich_edit_handle);

        int64_t find_text(HWND rich_edit_handle,
                          FINDTEXTA *text,
                          REFindStyle style = REFindStyle::Down |
                                  REFindStyle::FindNext);

        int64_t find_text2(HWND rich_edit_handle,
                           FINDTEXTEXA *text,
                           REFindStyle style = REFindStyle::Down |
                                   REFindStyle::FindNext);

        int64_t find_text(HWND rich_edit_handle,
                          FINDTEXTW *text,
                          REFindStyle style = REFindStyle::Down |
                                  REFindStyle::FindNext);

        int64_t find_text2(HWND rich_edit_handle,
                           FINDTEXTEXW *text,
                           REFindStyle style = REFindStyle::Down |
                                   REFindStyle::FindNext);

        int64_t find_word_break(HWND rich_edit_handle,
                                int64_t index,
                                REWordBreakStyle style);

        int64_t format_range(HWND rich_edit_handle,
                             FORMATRANGE *range,
                             bool render = true);

        bool display_band(HWND rich_edit_handle, RECT *rect);

        void
        get_char_format(HWND rich_edit_handle,
                        CHARFORMATW *format,
                        RECharFormatStyle style = RECharFormatStyle::Selection);

        void
        get_char_format(HWND rich_edit_handle,
                        CHARFORMAT2W *format,
                        RECharFormatStyle style = RECharFormatStyle::Selection);

        bool
        set_char_format(HWND rich_edit_handle,
                        CHARFORMATW *format,
                        RECharFormatStyle style = RECharFormatStyle::Selection);

        bool
        set_char_format(HWND rich_edit_handle,
                        CHARFORMAT2W *format,
                        RECharFormatStyle style = RECharFormatStyle::Selection);

        void get_para_format(HWND rich_edit_handle, PARAFORMAT *format);

        void get_para_format(HWND rich_edit_handle, PARAFORMAT2 *format);

        bool set_para_format(HWND rich_edit_handle, PARAFORMAT *format);

        bool set_para_format(HWND rich_edit_handle, PARAFORMAT2 *format);

        RETextMode get_text_mode(HWND rich_edit_handle);

        bool set_text_mode(HWND rich_edit_handle, RETextMode mode);

        REOption get_option(HWND rich_edit_handle);

        REOption
        set_option(HWND rich_edit_handle, REOptionOP op, REOption option);

        ImeCompMode get_ime_comp_mode(HWND rich_edit_handle);

        int64_t get_ime_comp_text(
                HWND rich_edit_handle,
                std::string &buf,
                helper::CodePage code_page = helper::curr_code_page());

        int64_t get_ime_comp_text(HWND rich_edit_handle, std::wstring &buf);

        bool has_ime_mode_bias(HWND rich_edit_handle);

        void set_ime_mode_bias(HWND rich_edit_handle);

        void unset_ime_mode_bias(HWND rich_edit_handle);

        ImeProperty get_ime_property(HWND rich_edit_handle);

        ImeVersion get_ime_version(HWND rich_edit_handle);

        ImeUICap get_ime_ui(HWND rich_edit_handle);

        ImeCompStrCap get_ime_comp_str(HWND rich_edit_handle);

        ImeSelectCap get_ime_select(HWND rich_edit_handle);

        ImeConversionMode get_ime_conversion_mode(HWND rich_edit_handle);

        ImeSentenceMode get_ime_sentence_mode(HWND rich_edit_handle);

        bool is_ime(HWND rich_edit_handle);

        ImeLangOption get_ime_lang_option(HWND rich_edit_handle);

        void set_ime_lang_option(HWND rich_edit_handle, ImeLangOption option);

        REModeBias get_mode_bias(HWND rich_edit_handle);

        void set_mode_bias(HWND rich_edit_handle, REModeBias mode);

        bool is_tsf_keyboard_open(HWND rich_edit_handle);

        bool open_tsf_keyboard(HWND rich_edit_handle);

        bool close_tsf_keyboard(HWND rich_edit_handle);

        RichEditExtendStyle get_rich_edit_extend_style(HWND rich_edit_handle);

        RichEditExtendStyle2 get_rich_edit_extend_style2(HWND rich_edit_handle);

        void set_rich_edit_extend_style(HWND rich_edit_handle,
                                        RichEditExtendStyle style,
                                        RichEditExtendStyle mask);

        void set_rich_edit_extend_style2(HWND rich_edit_handle,
                                         RichEditExtendStyle style,
                                         RichEditExtendStyle mask);

        bool get_ellipsis_mode(HWND rich_edit_handle, REEllipsisMode mode);

        bool set_ellipsis_mode(HWND rich_edit_handle, REEllipsisMode mode);

        bool is_ellipsis_display(HWND rich_edit_handle);

        REventMask get_event_mask(HWND rich_edit_handle);

        REventMask set_event_mask(HWND rich_edit_handle, REventMask mask);

        void get_hyphenate_info(HWND rich_edit_handle, HYPHENATEINFO *info);

        void set_hyphenate_info(HWND rich_edit_handle, HYPHENATEINFO *info);

        void get_bidirection_options(HWND rich_edit_handle,
                                     BIDIOPTIONS *option);

        void set_bidirection_options(HWND rich_edit_handle,
                                     BIDIOPTIONS *option);

        void get_scroll_pos(HWND rich_edit_handle, POINT *point);

        void set_scroll_pos(HWND rich_edit_handle, POINT *point);

        void show_vert_scroll_bar(HWND rich_edit_handle);

        void hide_vert_scroll_bar(HWND rich_edit_handle);

        void show_horiz_scroll_bar(HWND rich_edit_handle);

        void hide_horiz_scroll_bar(HWND rich_edit_handle);

        void show_both_scroll_bar(HWND rich_edit_handle);

        void hide_both_scroll_bar(HWND rich_edit_handle);

        bool
        get_zoom(HWND rich_edit_handle, int32_t numerator, int32_t denominator);

        bool
        set_zoom(HWND rich_edit_handle, int32_t numerator, int32_t denominator);

        bool can_redo(HWND rich_edit_handle);

        bool redo(HWND rich_edit_handle);

        RERedoState get_redo_state(HWND rich_edit_handle);

        REUndoState get_undo_state(HWND rich_edit_handle);

        int64_t set_undo_limit(HWND rich_edit_handle, int64_t limit = 100);

        REStoryType get_story_type(HWND rich_edit_handle, int64_t index);

        REStoryType
        set_story_type(HWND rich_edit_handle, int64_t index, REStoryType type);

        bool get_table(HWND rich_edit_handle,
                       TABLEROWPARMS *row,
                       TABLECELLPARMS *cell);

        bool set_table(HWND rich_edit_handle,
                       TABLEROWPARMS *row,
                       TABLECELLPARMS *cell);

        bool insert_table(HWND rich_edit_handle,
                          TABLEROWPARMS *row,
                          TABLECELLPARMS *cell);

        // text->cb = buf.size()
        int64_t get_text(HWND rich_edit_handle,
                         GETTEXTEX *text,
                         std::string &buf,
                         helper::CodePage code_page = helper::curr_code_page());

        // text->cb = buf.size() * sizeof(wchar_t)
        int64_t
        get_text(HWND rich_edit_handle, GETTEXTEX *text, std::wstring &buf);

        int64_t get_text(HWND rich_edit_handle,
                         std::string &buf,
                         REGetTextFlag flag = REGetTextFlag::Default,
                         const char *default_char = nullptr,
                         int32_t *used_default_char = nullptr,
                         helper::CodePage code_page = helper::curr_code_page());

        int64_t get_text(HWND rich_edit_handle,
                         std::wstring &buf,
                         REGetTextFlag flag = REGetTextFlag::Default,
                         const char *default_char = nullptr,
                         int32_t *used_default_char = nullptr,
                         helper::CodePage code_page = helper::curr_code_page());

        int64_t set_text(HWND rich_edit_handle,
                         SETTEXTEX *text,
                         std::string &buf,
                         helper::CodePage code_page = helper::curr_code_page());

        int64_t
        set_text(HWND rich_edit_handle, SETTEXTEX *text, std::wstring &buf);

        int64_t set_text(HWND rich_edit_handle,
                         std::string &buf,
                         RESetTextFlag flag = RESetTextFlag::Default,
                         helper::CodePage code_page = helper::curr_code_page());

        int64_t set_text(HWND rich_edit_handle,
                         std::wstring &buf,
                         RESetTextFlag flag = RESetTextFlag::Default,
                         helper::CodePage code_page = helper::curr_code_page());


        int64_t get_text_len(HWND rich_edit_handle, GETTEXTLENGTHEX *text_len);

        int64_t
        get_text_len(HWND rich_edit_handle,
                     REGetTextLenFlag flag = REGetTextLenFlag::Default,
                     helper::CodePage code_page = helper::curr_code_page());

        int64_t get_text_range(HWND rich_edit_handle, TEXTRANGEW *text_range);

        int64_t
        get_text_range(HWND rich_edit_handle,
                       int32_t first,
                       int32_t last,
                       std::string &buf,
                       helper::CodePage code_page = helper::curr_code_page());

        int64_t get_text_range(HWND rich_edit_handle,
                               int32_t first,
                               int32_t last,
                               std::wstring &buf);

        bool get_touch_option(HWND rich_edit_handle, RETouchOption option);

        void set_touch_option(HWND rich_edit_handle,
                              RETouchOption option,
                              bool enable = true);

        RETypographyOption get_typography_option(HWND rich_edit_handle);

        bool set_typography_option(HWND rich_edit_handle,
                                   RETypographyOption option,
                                   RETypographyOption mask);

        EDITWORDBREAKPROCEX get_word_break_proc(HWND rich_edit_handle);

        EDITWORDBREAKPROCEX set_word_break_proc(HWND rich_edit_handle,
                                                EDITWORDBREAKPROCEX func);

        bool get_ole_interface(HWND rich_edit_handle, IRichEditOle **ole);

        bool set_ole_callback(HWND rich_edit_handle,
                              IRichEditOleCallback *callback);

        REPageRotate get_page_rotate(HWND rich_edit_handle);

        REPageRotate set_page_rotate(HWND rich_edit_handle,
                                     REPageRotate rotate);

        COLORREF set_background_color(HWND rich_edit_handle,
                                      COLORREF color,
                                      bool use_system_color = false);

        bool set_font_size(HWND rich_edit_handle, int32_t size);

        void set_palette(HWND rich_edit_handle, HPALETTE palette_handle);

        bool
        set_target_device(HWND rich_edit_handle, HDC dc_handle, int32_t width);

        bool
        set_uia_name(HWND rich_edit_handle,
                     std::string &name,
                     helper::CodePage code_page = helper::curr_code_page());

        bool set_uia_name(HWND rich_edit_handle, std::wstring &name);

        bool can_paste(HWND rich_edit_handle, int64_t paste_format = 0);

        bool insert_image(HWND rich_edit_handle,
                          RICHEDIT_IMAGE_PARAMETERS *image);

        void paste_special(HWND rich_edit_handle,
                           int64_t paste_format,
                           REPASTESPECIAL *paste);

        void reconversion(HWND rich_edit_handle);

        void request_resize(HWND rich_edit_handle);

        void stop_group_typing(HWND rich_edit_handle);

        int64_t stream_in(HWND rich_edit_handle,
                          EDITSTREAM *stream,
                          REStreamFormat format);

        int64_t stream_out(HWND rich_edit_handle,
                           EDITSTREAM *stream,
                           REStreamFormat format);

        void set_text_limit(HWND rich_edit_handle, int32_t limit = 0);

        int64_t line_from_char(HWND rich_edit_handle, int64_t char_index);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // RICH_EDIT_H
