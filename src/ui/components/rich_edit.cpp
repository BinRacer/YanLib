/* clang-format off */
/*
 * @file rich_edit.cpp
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
#include "rich_edit.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    rich_edit::rich_edit() {
        rich_edit_dll = LoadLibraryW(L"msftedit.dll");
        if (!rich_edit_dll) {
            error_code = GetLastError();
        }
    }

    rich_edit::~rich_edit() {
        for (auto &handle : rich_edit_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        rich_edit_handles.clear();
        if (rich_edit_dll) {
            FreeLibrary(rich_edit_dll);
        }
    }

    HWND rich_edit::create(uintptr_t rich_edit_id,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           RichEditStyle style,
                           WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"RICHEDIT50W", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(rich_edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rich_edit_rwlock.write_lock();
        rich_edit_handles.push_back(result);
        rich_edit_rwlock.write_unlock();
        return result;
    }

    HWND rich_edit::create(const char *rich_edit_name,
                           uintptr_t rich_edit_id,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           RichEditStyle style,
                           WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "RICHEDIT50W", rich_edit_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(rich_edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rich_edit_rwlock.write_lock();
        rich_edit_handles.push_back(result);
        rich_edit_rwlock.write_unlock();
        return result;
    }

    HWND rich_edit::create(const wchar_t *rich_edit_name,
                           uintptr_t rich_edit_id,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           RichEditStyle style,
                           WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"RICHEDIT50W", rich_edit_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(rich_edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rich_edit_rwlock.write_lock();
        rich_edit_handles.push_back(result);
        rich_edit_rwlock.write_unlock();
        return result;
    }

    bool rich_edit::destroy(HWND rich_edit_handle) {
        if (!rich_edit_handle || !IsWindow(rich_edit_handle)) {
            return false;
        }
        rich_edit_rwlock.write_lock();
        const auto it = std::find(rich_edit_handles.begin(),
                                  rich_edit_handles.end(), rich_edit_handle);
        if (it != rich_edit_handles.end()) {
            *it = nullptr;
        }
        rich_edit_rwlock.write_unlock();
        if (!DestroyWindow(rich_edit_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool rich_edit::is_auto_url_detect_enabled(HWND rich_edit_handle) {
        return SendMessageW(rich_edit_handle, EM_GETAUTOURLDETECT, 0, 0);
    }

    bool rich_edit::set_auto_url_detect(HWND rich_edit_handle,
                                        REAutoUrlDetect state) {
        return SendMessageW(rich_edit_handle, EM_AUTOURLDETECT,
                            static_cast<uint32_t>(state), 0) == 0;
    }

    AutoCorrectProc rich_edit::get_auto_correct_proc(HWND rich_edit_handle) {
        return reinterpret_cast<AutoCorrectProc>(
                SendMessageW(rich_edit_handle, EM_GETAUTOCORRECTPROC, 0, 0));
    }

    bool rich_edit::set_auto_correct_proc(HWND rich_edit_handle,
                                          AutoCorrectProc func) {
        return SendMessageW(rich_edit_handle, EM_SETAUTOCORRECTPROC,
                            reinterpret_cast<WPARAM>(func), 0) == 0;
    }

    bool rich_edit::call_auto_correct_proc(HWND rich_edit_handle, wchar_t ch) {
        return SendMessageW(rich_edit_handle, EM_CALLAUTOCORRECTPROC, ch, 0) ==
                0;
    }

    void rich_edit::get_select(HWND rich_edit_handle, CHARRANGE *range) {
        SendMessageW(rich_edit_handle, EM_EXGETSEL, 0,
                     reinterpret_cast<LPARAM>(range));
    }

    void rich_edit::set_select(HWND rich_edit_handle, CHARRANGE *range) {
        SendMessageW(rich_edit_handle, EM_EXSETSEL, 0,
                     reinterpret_cast<LPARAM>(range));
    }

    int64_t rich_edit::get_select_text(HWND rich_edit_handle,
                                       std::string &text,
                                       helper::CodePage code_page) {
        return SendMessageW(
                rich_edit_handle, EM_GETSELTEXT, 0,
                reinterpret_cast<LPARAM>(
                        helper::convert::str_to_wstr(text, code_page).data()));
    }

    int64_t rich_edit::get_select_text(HWND rich_edit_handle,
                                       std::wstring &text) {
        return SendMessageW(rich_edit_handle, EM_GETSELTEXT, 0,
                            reinterpret_cast<LPARAM>(text.data()));
    }

    void rich_edit::show_select(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_HIDESELECTION, FALSE, 0);
    }

    void rich_edit::hide_select(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_HIDESELECTION, TRUE, 0);
    }

    RESelectType rich_edit::get_select_type(HWND rich_edit_handle) {
        return static_cast<RESelectType>(
                SendMessageW(rich_edit_handle, EM_SELECTIONTYPE, 0, 0));
    }

    int64_t rich_edit::find_text(HWND rich_edit_handle,
                                 FINDTEXTA *text,
                                 REFindStyle style) {
        return SendMessageW(rich_edit_handle, EM_FINDTEXT,
                            static_cast<uint32_t>(style),
                            reinterpret_cast<LPARAM>(text));
    }

    int64_t rich_edit::find_text2(HWND rich_edit_handle,
                                  FINDTEXTEXA *text,
                                  REFindStyle style) {
        return SendMessageW(rich_edit_handle, EM_FINDTEXTEX,
                            static_cast<uint32_t>(style),
                            reinterpret_cast<LPARAM>(text));
    }

    int64_t rich_edit::find_text(HWND rich_edit_handle,
                                 FINDTEXTW *text,
                                 REFindStyle style) {
        return SendMessageW(rich_edit_handle, EM_FINDTEXTW,
                            static_cast<uint32_t>(style),
                            reinterpret_cast<LPARAM>(text));
    }

    int64_t rich_edit::find_text2(HWND rich_edit_handle,
                                  FINDTEXTEXW *text,
                                  REFindStyle style) {
        return SendMessageW(rich_edit_handle, EM_FINDTEXTEXW,
                            static_cast<uint32_t>(style),
                            reinterpret_cast<LPARAM>(text));
    }

    int64_t rich_edit::find_word_break(HWND rich_edit_handle,
                                       int64_t index,
                                       REWordBreakStyle style) {
        return SendMessageW(rich_edit_handle, EM_FINDWORDBREAK,
                            static_cast<uint32_t>(style), index);
    }

    int64_t rich_edit::format_range(HWND rich_edit_handle,
                                    FORMATRANGE *range,
                                    bool render) {
        return SendMessageW(rich_edit_handle, EM_FORMATRANGE,
                            render ? TRUE : FALSE,
                            reinterpret_cast<LPARAM>(range));
    }

    bool rich_edit::display_band(HWND rich_edit_handle, RECT *rect) {
        return SendMessageW(rich_edit_handle, EM_DISPLAYBAND, 0,
                            reinterpret_cast<LPARAM>(rect));
    }

    void rich_edit::get_char_format(HWND rich_edit_handle,
                                    CHARFORMATW *format,
                                    RECharFormatStyle style) {
        SendMessageW(rich_edit_handle, EM_GETCHARFORMAT,
                     static_cast<uint32_t>(style),
                     reinterpret_cast<LPARAM>(format));
    }
    void rich_edit::get_char_format(HWND rich_edit_handle,
                                    CHARFORMAT2W *format,
                                    RECharFormatStyle style) {
        SendMessageW(rich_edit_handle, EM_GETCHARFORMAT,
                     static_cast<uint32_t>(style),
                     reinterpret_cast<LPARAM>(format));
    }

    bool rich_edit::set_char_format(HWND rich_edit_handle,
                                    CHARFORMATW *format,
                                    RECharFormatStyle style) {
        return SendMessageW(rich_edit_handle, EM_SETCHARFORMAT,
                            static_cast<uint32_t>(style),
                            reinterpret_cast<LPARAM>(format));
    }

    bool rich_edit::set_char_format(HWND rich_edit_handle,
                                    CHARFORMAT2W *format,
                                    RECharFormatStyle style) {
        return SendMessageW(rich_edit_handle, EM_SETCHARFORMAT,
                            static_cast<uint32_t>(style),
                            reinterpret_cast<LPARAM>(format));
    }

    void rich_edit::get_para_format(HWND rich_edit_handle, PARAFORMAT *format) {
        SendMessageW(rich_edit_handle, EM_GETPARAFORMAT, 0,
                     reinterpret_cast<LPARAM>(format));
    }

    void rich_edit::get_para_format(HWND rich_edit_handle,
                                    PARAFORMAT2 *format) {
        SendMessageW(rich_edit_handle, EM_GETPARAFORMAT, 0,
                     reinterpret_cast<LPARAM>(format));
    }

    bool rich_edit::set_para_format(HWND rich_edit_handle, PARAFORMAT *format) {
        return SendMessageW(rich_edit_handle, EM_SETPARAFORMAT, 0,
                            reinterpret_cast<LPARAM>(format));
    }

    bool rich_edit::set_para_format(HWND rich_edit_handle,
                                    PARAFORMAT2 *format) {
        return SendMessageW(rich_edit_handle, EM_SETPARAFORMAT, 0,
                            reinterpret_cast<LPARAM>(format));
    }

    RETextMode rich_edit::get_text_mode(HWND rich_edit_handle) {
        return static_cast<RETextMode>(
                SendMessageW(rich_edit_handle, EM_GETTEXTMODE, 0, 0));
    }

    bool rich_edit::set_text_mode(HWND rich_edit_handle, RETextMode mode) {
        return SendMessageW(rich_edit_handle, EM_SETTEXTMODE,
                            static_cast<uint32_t>(mode), 0);
    }

    REOption rich_edit::get_option(HWND rich_edit_handle) {
        return static_cast<REOption>(
                SendMessageW(rich_edit_handle, EM_GETOPTIONS, 0, 0));
    }

    REOption rich_edit::set_option(HWND rich_edit_handle,
                                   REOptionOP op,
                                   REOption option) {
        return static_cast<REOption>(
                SendMessageW(rich_edit_handle, EM_SETOPTIONS,
                             static_cast<uint32_t>(op),
                             static_cast<uint32_t>(option)));
    }

    ImeCompMode rich_edit::get_ime_comp_mode(HWND rich_edit_handle) {
        return static_cast<ImeCompMode>(
                SendMessageW(rich_edit_handle, EM_GETIMECOMPMODE, 0, 0));
    }

    int64_t rich_edit::get_ime_comp_text(HWND rich_edit_handle,
                                         std::string &buf,
                                         helper::CodePage code_page) {
        std::wstring temp(buf.size(), L'\0');
        IMECOMPTEXT ict = {};
        ict.cb = static_cast<int32_t>(buf.size() * sizeof(wchar_t));
        ict.flags = ICT_RESULTREADSTR;
        SendMessageW(rich_edit_handle, EM_GETIMECOMPTEXT,
                     reinterpret_cast<WPARAM>(&ict),
                     reinterpret_cast<LPARAM>(temp.data()));
        buf = helper::convert::wstr_to_str(temp, code_page);
        return static_cast<int64_t>(buf.size());
    }

    int64_t rich_edit::get_ime_comp_text(HWND rich_edit_handle,
                                         std::wstring &buf) {
        IMECOMPTEXT ict = {};
        ict.cb = static_cast<int32_t>(buf.size() * sizeof(wchar_t));
        ict.flags = ICT_RESULTREADSTR;
        return SendMessageW(rich_edit_handle, EM_GETIMECOMPTEXT,
                            reinterpret_cast<WPARAM>(&ict),
                            reinterpret_cast<LPARAM>(buf.data()));
    }

    bool rich_edit::has_ime_mode_bias(HWND rich_edit_handle) {
        return SendMessageW(rich_edit_handle, EM_GETIMEMODEBIAS, 0, 0) ==
                IMF_SMODE_PLAURALCLAUSE;
    }

    void rich_edit::set_ime_mode_bias(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_SETIMEMODEBIAS,
                     IMF_SMODE_PLAURALCLAUSE, IMF_SMODE_PLAURALCLAUSE);
    }

    void rich_edit::unset_ime_mode_bias(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_SETIMEMODEBIAS, IMF_SMODE_NONE,
                     IMF_SMODE_NONE);
    }

    ImeProperty rich_edit::get_ime_property(HWND rich_edit_handle) {
        return static_cast<ImeProperty>(SendMessageW(rich_edit_handle,
                                                     EM_GETIMEPROPERTY,
                                                     IGP_PROPERTY, 0));
    }

    ImeVersion rich_edit::get_ime_version(HWND rich_edit_handle) {
        return static_cast<ImeVersion>(SendMessageW(rich_edit_handle,
                                                    EM_GETIMEPROPERTY,
                                                    IGP_GETIMEVERSION, 0));
    }

    ImeUICap rich_edit::get_ime_ui(HWND rich_edit_handle) {
        return static_cast<ImeUICap>(
                SendMessageW(rich_edit_handle, EM_GETIMEPROPERTY, IGP_UI, 0));
    }

    ImeCompStrCap rich_edit::get_ime_comp_str(HWND rich_edit_handle) {
        return static_cast<ImeCompStrCap>(SendMessageW(rich_edit_handle,
                                                       EM_GETIMEPROPERTY,
                                                       IGP_SETCOMPSTR, 0));
    }

    ImeSelectCap rich_edit::get_ime_select(HWND rich_edit_handle) {
        return static_cast<ImeSelectCap>(SendMessageW(rich_edit_handle,
                                                      EM_GETIMEPROPERTY,
                                                      IGP_SELECT, 0));
    }

    ImeConversionMode
    rich_edit::get_ime_conversion_mode(HWND rich_edit_handle) {
        return static_cast<ImeConversionMode>(SendMessageW(rich_edit_handle,
                                                           EM_GETIMEPROPERTY,
                                                           IGP_CONVERSION, 0));
    }

    ImeSentenceMode rich_edit::get_ime_sentence_mode(HWND rich_edit_handle) {
        return static_cast<ImeSentenceMode>(SendMessageW(rich_edit_handle,
                                                         EM_GETIMEPROPERTY,
                                                         IGP_SENTENCE, 0));
    }

    bool rich_edit::is_ime(HWND rich_edit_handle) {
        return SendMessageW(rich_edit_handle, EM_ISIME, 0, 0);
    }

    ImeLangOption rich_edit::get_ime_lang_option(HWND rich_edit_handle) {
        return static_cast<ImeLangOption>(
                SendMessageW(rich_edit_handle, EM_GETLANGOPTIONS, 0, 0));
    }

    void rich_edit::set_ime_lang_option(HWND rich_edit_handle,
                                        ImeLangOption option) {
        SendMessageW(rich_edit_handle, EM_SETLANGOPTIONS, 0,
                     static_cast<uint32_t>(option));
    }

    REModeBias rich_edit::get_mode_bias(HWND rich_edit_handle) {
        return static_cast<REModeBias>(
                SendMessageW(rich_edit_handle, EM_GETCTFMODEBIAS, 0, 0));
    }

    void rich_edit::set_mode_bias(HWND rich_edit_handle, REModeBias mode) {
        SendMessageW(rich_edit_handle, EM_SETCTFMODEBIAS,
                     static_cast<uint32_t>(mode), 0);
    }

    bool rich_edit::is_tsf_keyboard_open(HWND rich_edit_handle) {
        return SendMessageW(rich_edit_handle, EM_GETCTFOPENSTATUS, 0, 0);
    }

    bool rich_edit::open_tsf_keyboard(HWND rich_edit_handle) {
        return SendMessageW(rich_edit_handle, EM_SETCTFOPENSTATUS, TRUE, 0);
    }

    bool rich_edit::close_tsf_keyboard(HWND rich_edit_handle) {
        return SendMessageW(rich_edit_handle, EM_SETCTFOPENSTATUS, FALSE, 0);
    }

    RichEditExtendStyle
    rich_edit::get_rich_edit_extend_style(HWND rich_edit_handle) {
        return static_cast<RichEditExtendStyle>(
                SendMessageW(rich_edit_handle, EM_GETEDITSTYLE, 0, 0));
    }

    RichEditExtendStyle2
    rich_edit::get_rich_edit_extend_style2(HWND rich_edit_handle) {
        return static_cast<RichEditExtendStyle2>(
                SendMessageW(rich_edit_handle, EM_GETEDITSTYLEEX, 0, 0));
    }

    void rich_edit::set_rich_edit_extend_style(HWND rich_edit_handle,
                                               RichEditExtendStyle style,
                                               RichEditExtendStyle mask) {
        SendMessageW(rich_edit_handle, EM_SETEDITSTYLE,
                     static_cast<uint32_t>(style), static_cast<uint32_t>(mask));
    }

    void rich_edit::set_rich_edit_extend_style2(HWND rich_edit_handle,
                                                RichEditExtendStyle style,
                                                RichEditExtendStyle mask) {
        SendMessageW(rich_edit_handle, EM_SETEDITSTYLEEX,
                     static_cast<uint32_t>(style), static_cast<uint32_t>(mask));
    }

    bool rich_edit::get_ellipsis_mode(HWND rich_edit_handle,
                                      REEllipsisMode mode) {
        return SendMessageW(rich_edit_handle, EM_GETELLIPSISMODE, 0,
                            static_cast<uint32_t>(mode));
    }

    bool rich_edit::set_ellipsis_mode(HWND rich_edit_handle,
                                      REEllipsisMode mode) {
        return SendMessageW(rich_edit_handle, EM_SETELLIPSISMODE, 0,
                            static_cast<uint32_t>(mode));
    }

    bool rich_edit::is_ellipsis_display(HWND rich_edit_handle) {
        return SendMessageW(rich_edit_handle, EM_GETELLIPSISSTATE, 0, 0);
    }

    REventMask rich_edit::get_event_mask(HWND rich_edit_handle) {
        return static_cast<REventMask>(
                SendMessageW(rich_edit_handle, EM_GETEVENTMASK, 0, 0));
    }

    REventMask rich_edit::set_event_mask(HWND rich_edit_handle,
                                         REventMask mask) {
        return static_cast<REventMask>(
                SendMessageW(rich_edit_handle, EM_SETEVENTMASK, 0,
                             static_cast<uint32_t>(mask)));
    }

    void rich_edit::get_hyphenate_info(HWND rich_edit_handle,
                                       HYPHENATEINFO *info) {
        SendMessageW(rich_edit_handle, EM_GETHYPHENATEINFO,
                     reinterpret_cast<WPARAM>(info), 0);
    }

    void rich_edit::set_hyphenate_info(HWND rich_edit_handle,
                                       HYPHENATEINFO *info) {
        SendMessageW(rich_edit_handle, EM_SETHYPHENATEINFO,
                     reinterpret_cast<WPARAM>(info), 0);
    }

    void rich_edit::get_bidirection_options(HWND rich_edit_handle,
                                            BIDIOPTIONS *option) {
        SendMessageW(rich_edit_handle, EM_GETBIDIOPTIONS, 0,
                     reinterpret_cast<LPARAM>(option));
    }

    void rich_edit::set_bidirection_options(HWND rich_edit_handle,
                                            BIDIOPTIONS *option) {
        SendMessageW(rich_edit_handle, EM_SETBIDIOPTIONS, 0,
                     reinterpret_cast<LPARAM>(option));
    }

    void rich_edit::get_scroll_pos(HWND rich_edit_handle, POINT *point) {
        SendMessageW(rich_edit_handle, EM_GETSCROLLPOS, 0,
                     reinterpret_cast<LPARAM>(point));
    }

    void rich_edit::set_scroll_pos(HWND rich_edit_handle, POINT *point) {
        SendMessageW(rich_edit_handle, EM_SETSCROLLPOS, 0,
                     reinterpret_cast<LPARAM>(point));
    }

    void rich_edit::show_vert_scroll_bar(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_SHOWSCROLLBAR, SB_VERT, TRUE);
    }

    void rich_edit::hide_vert_scroll_bar(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_SHOWSCROLLBAR, SB_VERT, FALSE);
    }

    void rich_edit::show_horiz_scroll_bar(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_SHOWSCROLLBAR, SB_HORZ, TRUE);
    }

    void rich_edit::hide_horiz_scroll_bar(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_SHOWSCROLLBAR, SB_HORZ, FALSE);
    }

    void rich_edit::show_both_scroll_bar(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_SHOWSCROLLBAR, SB_VERT | SB_HORZ,
                     TRUE);
    }

    void rich_edit::hide_both_scroll_bar(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_SHOWSCROLLBAR, SB_VERT | SB_HORZ,
                     FALSE);
    }

    bool rich_edit::get_zoom(HWND rich_edit_handle,
                             int32_t numerator,
                             int32_t denominator) {
        return SendMessageW(rich_edit_handle, EM_GETZOOM, numerator,
                            denominator);
    }

    bool rich_edit::set_zoom(HWND rich_edit_handle,
                             int32_t numerator,
                             int32_t denominator) {
        return SendMessageW(rich_edit_handle, EM_SETZOOM, numerator,
                            denominator);
    }

    bool rich_edit::can_redo(HWND rich_edit_handle) {
        return SendMessageW(rich_edit_handle, EM_CANREDO, 0, 0);
    }

    bool rich_edit::redo(HWND rich_edit_handle) {
        return SendMessageW(rich_edit_handle, EM_REDO, 0, 0);
    }

    RERedoState rich_edit::get_redo_state(HWND rich_edit_handle) {
        return static_cast<RERedoState>(
                SendMessageW(rich_edit_handle, EM_GETREDONAME, 0, 0));
    }

    REUndoState rich_edit::get_undo_state(HWND rich_edit_handle) {
        return static_cast<REUndoState>(
                SendMessageW(rich_edit_handle, EM_GETUNDONAME, 0, 0));
    }

    int64_t rich_edit::set_undo_limit(HWND rich_edit_handle, int64_t limit) {
        return SendMessageW(rich_edit_handle, EM_SETUNDOLIMIT, limit, 0);
    }

    REStoryType rich_edit::get_story_type(HWND rich_edit_handle,
                                          int64_t index) {
        return static_cast<REStoryType>(
                SendMessageW(rich_edit_handle, EM_GETSTORYTYPE, index, 0));
    }

    REStoryType rich_edit::set_story_type(HWND rich_edit_handle,
                                          int64_t index,
                                          REStoryType type) {
        return static_cast<REStoryType>(
                SendMessageW(rich_edit_handle, EM_SETSTORYTYPE, index, type));
    }

    bool rich_edit::get_table(HWND rich_edit_handle,
                              TABLEROWPARMS *row,
                              TABLECELLPARMS *cell) {
        return SendMessageW(rich_edit_handle, EM_GETTABLEPARMS,
                            reinterpret_cast<WPARAM>(row),
                            reinterpret_cast<LPARAM>(cell)) == S_OK;
    }

    bool rich_edit::set_table(HWND rich_edit_handle,
                              TABLEROWPARMS *row,
                              TABLECELLPARMS *cell) {
        return SendMessageW(rich_edit_handle, EM_SETTABLEPARMS,
                            reinterpret_cast<WPARAM>(row),
                            reinterpret_cast<LPARAM>(cell)) == S_OK;
    }

    bool rich_edit::insert_table(HWND rich_edit_handle,
                                 TABLEROWPARMS *row,
                                 TABLECELLPARMS *cell) {
        return SendMessageW(rich_edit_handle, EM_INSERTTABLE,
                            reinterpret_cast<WPARAM>(row),
                            reinterpret_cast<LPARAM>(cell)) == S_OK;
    }

    int64_t rich_edit::get_text(HWND rich_edit_handle,
                                GETTEXTEX *text,
                                std::string &buf,
                                helper::CodePage code_page) {
        std::wstring temp(buf.size(), L'\0');
        SendMessageW(rich_edit_handle, EM_GETTEXTEX,
                     reinterpret_cast<WPARAM>(text),
                     reinterpret_cast<LPARAM>(temp.data()));
        buf.clear();
        buf = helper::convert::wstr_to_str(temp, code_page);
        return static_cast<int64_t>(buf.size());
    }

    int64_t rich_edit::get_text(HWND rich_edit_handle,
                                GETTEXTEX *text,
                                std::wstring &buf) {
        return SendMessageW(rich_edit_handle, EM_GETTEXTEX,
                            reinterpret_cast<WPARAM>(text),
                            reinterpret_cast<LPARAM>(buf.data()));
    }

    int64_t rich_edit::get_text(HWND rich_edit_handle,
                                std::string &buf,
                                REGetTextFlag flag,
                                const char *default_char,
                                int32_t *used_default_char,
                                helper::CodePage code_page) {
        GETTEXTEX text = {};
        text.cb = buf.size() * sizeof(wchar_t);
        text.flags = static_cast<uint32_t>(flag);
        text.codepage = static_cast<uint32_t>(code_page);
        text.lpDefaultChar = default_char;
        text.lpUsedDefChar = used_default_char;
        std::wstring temp(buf.size(), L'\0');
        SendMessageW(rich_edit_handle, EM_GETTEXTEX,
                     reinterpret_cast<WPARAM>(&text),
                     reinterpret_cast<LPARAM>(temp.data()));
        buf.clear();
        buf = helper::convert::wstr_to_str(temp, code_page);
        return static_cast<int64_t>(buf.size());
    }

    int64_t rich_edit::get_text(HWND rich_edit_handle,
                                std::wstring &buf,
                                REGetTextFlag flag,
                                const char *default_char,
                                int32_t *used_default_char,
                                helper::CodePage code_page) {
        GETTEXTEX text = {};
        text.cb = buf.size() * sizeof(wchar_t);
        text.flags = static_cast<uint32_t>(flag);
        text.codepage = static_cast<uint32_t>(code_page);
        text.lpDefaultChar = default_char;
        text.lpUsedDefChar = used_default_char;
        return SendMessageW(rich_edit_handle, EM_GETTEXTEX,
                            reinterpret_cast<WPARAM>(&text),
                            reinterpret_cast<LPARAM>(buf.data()));
    }

    int64_t rich_edit::set_text(HWND rich_edit_handle,
                                SETTEXTEX *text,
                                std::string &buf,
                                helper::CodePage code_page) {
        std::wstring temp(buf.size(), L'\0');
        SendMessageW(rich_edit_handle, EM_SETTEXTEX,
                     reinterpret_cast<WPARAM>(text),
                     reinterpret_cast<LPARAM>(temp.data()));
        buf.clear();
        buf = helper::convert::wstr_to_str(temp, code_page);
        return static_cast<int64_t>(buf.size());
    }

    int64_t rich_edit::set_text(HWND rich_edit_handle,
                                SETTEXTEX *text,
                                std::wstring &buf) {
        return SendMessageW(rich_edit_handle, EM_SETTEXTEX,
                            reinterpret_cast<WPARAM>(text),
                            reinterpret_cast<LPARAM>(buf.data()));
    }

    int64_t rich_edit::set_text(HWND rich_edit_handle,
                                std::string &buf,
                                RESetTextFlag flag,
                                helper::CodePage code_page) {
        SETTEXTEX text = {};
        text.flags = static_cast<uint32_t>(flag);
        text.codepage = static_cast<uint32_t>(code_page);
        std::wstring temp(buf.size(), L'\0');
        SendMessageW(rich_edit_handle, EM_SETTEXTEX,
                     reinterpret_cast<WPARAM>(&text),
                     reinterpret_cast<LPARAM>(temp.data()));
        buf.clear();
        buf = helper::convert::wstr_to_str(temp, code_page);
        return static_cast<int64_t>(buf.size());
    }

    int64_t rich_edit::set_text(HWND rich_edit_handle,
                                std::wstring &buf,
                                RESetTextFlag flag,
                                helper::CodePage code_page) {
        SETTEXTEX text = {};
        text.flags = static_cast<uint32_t>(flag);
        text.codepage = static_cast<uint32_t>(code_page);
        return SendMessageW(rich_edit_handle, EM_SETTEXTEX,
                            reinterpret_cast<WPARAM>(&text),
                            reinterpret_cast<LPARAM>(buf.data()));
    }

    int64_t rich_edit::get_text_len(HWND rich_edit_handle,
                                    GETTEXTLENGTHEX *text_len) {
        return SendMessageW(rich_edit_handle, EM_GETTEXTLENGTHEX,
                            reinterpret_cast<WPARAM>(text_len), 0);
    }

    int64_t rich_edit::get_text_len(HWND rich_edit_handle,
                                    REGetTextLenFlag flag,
                                    helper::CodePage code_page) {
        GETTEXTLENGTHEX text_len = {};
        text_len.flags = static_cast<uint32_t>(flag);
        text_len.codepage = static_cast<uint32_t>(code_page);
        return SendMessageW(rich_edit_handle, EM_GETTEXTLENGTHEX,
                            reinterpret_cast<WPARAM>(&text_len), 0);
    }

    int64_t rich_edit::get_text_range(HWND rich_edit_handle,
                                      TEXTRANGEW *text_range) {
        return SendMessageW(rich_edit_handle, EM_GETTEXTRANGE, 0,
                            reinterpret_cast<LPARAM>(text_range));
    }

    int64_t rich_edit::get_text_range(HWND rich_edit_handle,
                                      int32_t first,
                                      int32_t last,
                                      std::string &buf,
                                      helper::CodePage code_page) {
        std::wstring temp(buf.size(), L'\0');
        TEXTRANGEW text_range = {};
        text_range.chrg.cpMin = first;
        text_range.chrg.cpMax = last;
        text_range.lpstrText = temp.data();
        SendMessageW(rich_edit_handle, EM_GETTEXTRANGE, 0,
                     reinterpret_cast<LPARAM>(&text_range));
        buf.clear();
        buf = helper::convert::wstr_to_str(temp, code_page);
        return static_cast<int64_t>(buf.size());
    }

    int64_t rich_edit::get_text_range(HWND rich_edit_handle,
                                      int32_t first,
                                      int32_t last,
                                      std::wstring &buf) {
        TEXTRANGEW text_range = {};
        text_range.chrg.cpMin = first;
        text_range.chrg.cpMax = last;
        text_range.lpstrText = buf.data();
        return SendMessageW(rich_edit_handle, EM_GETTEXTRANGE, 0,
                            reinterpret_cast<LPARAM>(&text_range));
    }

    bool rich_edit::get_touch_option(HWND rich_edit_handle,
                                     RETouchOption option) {
        return SendMessageW(rich_edit_handle, EM_GETTOUCHOPTIONS,
                            static_cast<uint32_t>(option), 0);
    }

    void rich_edit::set_touch_option(HWND rich_edit_handle,
                                     RETouchOption option,
                                     bool enable) {
        SendMessageW(rich_edit_handle, EM_SETTOUCHOPTIONS,
                     static_cast<uint32_t>(option), enable ? TRUE : FALSE);
    }

    RETypographyOption rich_edit::get_typography_option(HWND rich_edit_handle) {
        return static_cast<RETypographyOption>(
                SendMessageW(rich_edit_handle, EM_GETTYPOGRAPHYOPTIONS, 0, 0));
    }

    bool rich_edit::set_typography_option(HWND rich_edit_handle,
                                          RETypographyOption option,
                                          RETypographyOption mask) {
        return SendMessageW(rich_edit_handle, EM_SETTYPOGRAPHYOPTIONS,
                            static_cast<uint32_t>(option),
                            static_cast<uint32_t>(mask));
    }

    EDITWORDBREAKPROCEX rich_edit::get_word_break_proc(HWND rich_edit_handle) {
        return reinterpret_cast<EDITWORDBREAKPROCEX>(
                SendMessageW(rich_edit_handle, EM_GETWORDBREAKPROCEX, 0, 0));
    }

    EDITWORDBREAKPROCEX
    rich_edit::set_word_break_proc(HWND rich_edit_handle,
                                   EDITWORDBREAKPROCEX func) {
        return reinterpret_cast<EDITWORDBREAKPROCEX>(
                SendMessageW(rich_edit_handle, EM_SETWORDBREAKPROCEX, 0,
                             reinterpret_cast<LPARAM>(func)));
    }

    bool rich_edit::get_ole_interface(HWND rich_edit_handle,
                                      IRichEditOle **ole) {
        return SendMessageW(rich_edit_handle, EM_GETOLEINTERFACE, 0,
                            reinterpret_cast<LPARAM>(ole));
    }

    bool rich_edit::set_ole_callback(HWND rich_edit_handle,
                                     IRichEditOleCallback *callback) {
        return SendMessageW(rich_edit_handle, EM_SETOLECALLBACK, 0,
                            reinterpret_cast<LPARAM>(callback));
    }

    REPageRotate rich_edit::get_page_rotate(HWND rich_edit_handle) {
        return static_cast<REPageRotate>(
                SendMessageW(rich_edit_handle, EM_GETPAGEROTATE, 0, 0));
    }

    REPageRotate rich_edit::set_page_rotate(HWND rich_edit_handle,
                                            REPageRotate rotate) {
        return static_cast<REPageRotate>(
                SendMessageW(rich_edit_handle, EM_SETPAGEROTATE,
                             static_cast<uint32_t>(rotate), 0));
    }

    COLORREF rich_edit::set_background_color(HWND rich_edit_handle,
                                             COLORREF color,
                                             bool use_system_color) {
        return SendMessageW(rich_edit_handle, EM_SETBKGNDCOLOR,
                            use_system_color ? TRUE : FALSE, color);
    }

    bool rich_edit::set_font_size(HWND rich_edit_handle, int32_t size) {
        return SendMessageW(rich_edit_handle, EM_SETFONTSIZE, size, 0);
    }

    void rich_edit::set_palette(HWND rich_edit_handle,
                                HPALETTE palette_handle) {
        SendMessageW(rich_edit_handle, EM_SETPALETTE,
                     reinterpret_cast<WPARAM>(palette_handle), 0);
    }

    bool rich_edit::set_target_device(HWND rich_edit_handle,
                                      HDC dc_handle,
                                      int32_t width) {
        return SendMessageW(rich_edit_handle, EM_SETTARGETDEVICE,
                            reinterpret_cast<WPARAM>(dc_handle), width);
    }

    bool rich_edit::set_uia_name(HWND rich_edit_handle,
                                 std::string &name,
                                 helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(name, code_page);
        return SendMessageW(rich_edit_handle, EM_SETUIANAME, 0,
                            reinterpret_cast<LPARAM>(temp.data()));
    }

    bool rich_edit::set_uia_name(HWND rich_edit_handle, std::wstring &name) {
        return SendMessageW(rich_edit_handle, EM_SETUIANAME, 0,
                            reinterpret_cast<LPARAM>(name.data()));
    }

    bool rich_edit::can_paste(HWND rich_edit_handle, int64_t paste_format) {
        return SendMessageW(rich_edit_handle, EM_CANPASTE, paste_format, 0);
    }

    bool rich_edit::insert_image(HWND rich_edit_handle,
                                 RICHEDIT_IMAGE_PARAMETERS *image) {
        return SendMessageW(rich_edit_handle, EM_INSERTIMAGE, 0,
                            reinterpret_cast<LPARAM>(image)) == S_OK;
    }

    void rich_edit::paste_special(HWND rich_edit_handle,
                                  int64_t paste_format,
                                  REPASTESPECIAL *paste) {
        SendMessageW(rich_edit_handle, EM_PASTESPECIAL, paste_format,
                     reinterpret_cast<LPARAM>(paste));
    }

    void rich_edit::reconversion(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_RECONVERSION, 0, 0);
    }

    void rich_edit::request_resize(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_REQUESTRESIZE, 0, 0);
    }

    void rich_edit::stop_group_typing(HWND rich_edit_handle) {
        SendMessageW(rich_edit_handle, EM_STOPGROUPTYPING, 0, 0);
    }

    int64_t rich_edit::stream_in(HWND rich_edit_handle,
                                 EDITSTREAM *stream,
                                 REStreamFormat format) {
        return SendMessageW(rich_edit_handle, EM_STREAMIN,
                            static_cast<uint32_t>(format),
                            reinterpret_cast<LPARAM>(stream));
    }

    int64_t rich_edit::stream_out(HWND rich_edit_handle,
                                  EDITSTREAM *stream,
                                  REStreamFormat format) {
        return SendMessageW(rich_edit_handle, EM_STREAMOUT,
                            static_cast<uint32_t>(format),
                            reinterpret_cast<LPARAM>(stream));
    }

    void rich_edit::set_text_limit(HWND rich_edit_handle, int32_t limit) {
        SendMessageW(rich_edit_handle, EM_EXLIMITTEXT, 0, limit);
    }

    int64_t rich_edit::line_from_char(HWND rich_edit_handle,
                                      int64_t char_index) {
        return SendMessageW(rich_edit_handle, EM_EXLINEFROMCHAR, 0, char_index);
    }

    uint32_t rich_edit::err_code() const {
        return error_code;
    }

    std::string rich_edit::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring rich_edit::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
