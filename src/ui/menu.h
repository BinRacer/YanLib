//
// Created by forkernel on 2025/4/30.
//

#ifndef MENU_H
#define MENU_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class menu {
    private:
        unsigned long error_code = 0;

    public:
        menu(const menu &other) = delete;

        menu(menu &&other) = delete;

        menu &operator=(const menu &other) = delete;

        menu &operator=(menu &&other) = delete;

        menu() = default;

        ~menu() = default;

        HMENU create_menu();

        HMENU create_popup_menu();

        HMENU load_menu(HINSTANCE instance_handle,
                        const wchar_t *menu_name);

        HMENU load_menu_indirect(const MENUTEMPLATEW *menu_template);

        bool append_menu(HMENU menu_handle,
                         unsigned int flag,
                         UINT_PTR id_new_item,
                         const wchar_t *new_item);

        bool insert_menu(HMENU menu_handle,
                         unsigned int position,
                         unsigned int flag,
                         UINT_PTR id_new_item,
                         const wchar_t *new_item);

        bool remove_menu(HMENU menu_handle,
                         unsigned int position,
                         unsigned int flag);

        bool delete_menu(HMENU menu_handle,
                         unsigned int position,
                         unsigned int flag);

        bool modify_menu(HMENU menu_handle,
                         unsigned int position,
                         unsigned int flag,
                         UINT_PTR id_new_item,
                         const wchar_t *new_item);

        bool set_menu(HWND hwnd, HMENU menu_handle);

        bool set_menu_info(HMENU menu_handle, const MENUINFO *memu_info);

        bool get_menu_info(HMENU menu_handle, MENUINFO *memu_info);

        bool get_menu_bar_info(HWND hwnd,
                               long id_object,
                               long id_item,
                               MENUBARINFO *menu_bar_info);

        unsigned int get_menu_state(HMENU menu_handle, unsigned int id, unsigned int flag);

        int get_menu_string(HMENU menu_handle,
                            unsigned int id_item,
                            wchar_t *text,
                            int cch_max,
                            unsigned int flag);

        HMENU get_sub_menu(HMENU menu_handle, int pos);

        HMENU get_system_menu(HWND hwnd, bool revert);

        long get_menu_check_mark_dimensions();

        bool is_menu(HMENU menu_handle);

        bool end_menu();

        bool destroy_menu(HMENU menu_handle);

        bool draw_menu_bar(HWND hwnd);

        bool insert_menu_item(HMENU menu_handle,
                              unsigned int item,
                              bool is_pos,
                              const MENUITEMINFOW *menu_item_info);

        bool get_menu_item_info(HMENU menu_handle,
                                unsigned int item,
                                bool is_pos,
                                MENUITEMINFOW *menu_item_info);

        bool set_menu_item_info(HMENU menu_handle,
                                unsigned int item,
                                bool is_pos,
                                const MENUITEMINFOW *menu_item_info);


        unsigned int get_menu_default_item(HMENU menu_handle,
                                           bool is_pos,
                                           unsigned int flag);

        bool set_menu_default_item(HMENU menu_handle,
                                   unsigned int item,
                                   bool is_pos);

        unsigned long get_menu_context_help_id(HMENU menu_handle);

        bool set_menu_context_help_id(HMENU menu_handle, unsigned long param);


        int get_menu_item_count(HMENU menu_handle);

        unsigned int get_menu_item_id(HMENU menu_handle, int pos);


        bool get_menu_item_rect(HWND hwnd,
                                HMENU menu_handle,
                                unsigned int item,
                                RECT *rect);

        BOOL set_menu_item_bitmaps(HMENU menu_handle,
                                   unsigned int position,
                                   unsigned int flag,
                                   HBITMAP bitmap_unchecked_handle,
                                   HBITMAP bitmap_checked_handle);

        int menu_item_from_point(HWND hwnd,
                                 HMENU menu_handle,
                                 POINT point_screen);

        bool hilite_menu_item(HWND hwnd,
                              HMENU menu_handle,
                              unsigned int id_hilite_item,
                              unsigned int hilite);

        unsigned long check_menu_item(HMENU menu_handle,
                                      unsigned int id_check_item,
                                      unsigned int check);

        bool check_menu_radio_item(HMENU menu_handle,
                                   unsigned int first,
                                   unsigned int last,
                                   unsigned int check,
                                   unsigned int flag);

        int enable_menu_item(HMENU menu_handle,
                             unsigned int id_enable_item,
                             unsigned int enable);

        bool track_popup_menu(HMENU menu_handle,
                              unsigned int flag,
                              int x,
                              int y,
                              int reserved,
                              HWND hwnd,
                              const RECT *rect);

        bool track_popup_menu(HMENU menu_handle,
                              unsigned int flag,
                              int x,
                              int y,
                              HWND hwnd,
                              TPMPARAMS *tpm_params);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //MENU_H
