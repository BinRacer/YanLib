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
                         uint32_t flag,
                         UINT_PTR id_new_item,
                         const wchar_t *new_item);

        bool insert_menu(HMENU menu_handle,
                         uint32_t position,
                         uint32_t flag,
                         UINT_PTR id_new_item,
                         const wchar_t *new_item);

        bool remove_menu(HMENU menu_handle,
                         uint32_t position,
                         uint32_t flag);

        bool delete_menu(HMENU menu_handle,
                         uint32_t position,
                         uint32_t flag);

        bool modify_menu(HMENU menu_handle,
                         uint32_t position,
                         uint32_t flag,
                         UINT_PTR id_new_item,
                         const wchar_t *new_item);

        HMENU get_menu(HWND hwnd);

        bool set_menu(HWND hwnd, HMENU menu_handle);

        bool set_menu_info(HMENU menu_handle, const MENUINFO *memu_info);

        bool get_menu_info(HMENU menu_handle, MENUINFO *memu_info);

        bool get_menu_bar_info(HWND hwnd,
                               long id_object,
                               long id_item,
                               MENUBARINFO *menu_bar_info);

        uint32_t get_menu_state(HMENU menu_handle, uint32_t id, uint32_t flag);

        int32_t get_menu_string(HMENU menu_handle,
                            uint32_t id_item,
                            wchar_t *text,
                            int32_t cch_max,
                            uint32_t flag);

        HMENU get_sub_menu(HMENU menu_handle, int32_t pos);

        HMENU get_system_menu(HWND hwnd, bool revert);

        long get_menu_check_mark_dimensions();

        bool is_menu(HMENU menu_handle);

        bool end_menu();

        bool destroy_menu(HMENU menu_handle);

        bool draw_menu_bar(HWND hwnd);

        bool insert_menu_item(HMENU menu_handle,
                              uint32_t item,
                              bool is_pos,
                              const MENUITEMINFOW *menu_item_info);

        bool get_menu_item_info(HMENU menu_handle,
                                uint32_t item,
                                bool is_pos,
                                MENUITEMINFOW *menu_item_info);

        bool set_menu_item_info(HMENU menu_handle,
                                uint32_t item,
                                bool is_pos,
                                const MENUITEMINFOW *menu_item_info);


        uint32_t get_menu_default_item(HMENU menu_handle,
                                           bool is_pos,
                                           uint32_t flag);

        bool set_menu_default_item(HMENU menu_handle,
                                   uint32_t item,
                                   bool is_pos);

        unsigned long get_menu_context_help_id(HMENU menu_handle);

        bool set_menu_context_help_id(HMENU menu_handle, unsigned long param);


        int32_t get_menu_item_count(HMENU menu_handle);

        uint32_t get_menu_item_id(HMENU menu_handle, int32_t pos);


        bool get_menu_item_rect(HWND hwnd,
                                HMENU menu_handle,
                                uint32_t item,
                                RECT *rect);

        BOOL set_menu_item_bitmaps(HMENU menu_handle,
                                   uint32_t position,
                                   uint32_t flag,
                                   HBITMAP bitmap_unchecked_handle,
                                   HBITMAP bitmap_checked_handle);

        int32_t menu_item_from_point(HWND hwnd,
                                 HMENU menu_handle,
                                 POINT point_screen);

        bool hilite_menu_item(HWND hwnd,
                              HMENU menu_handle,
                              uint32_t id_hilite_item,
                              uint32_t hilite);

        unsigned long check_menu_item(HMENU menu_handle,
                                      uint32_t id_check_item,
                                      uint32_t check);

        bool check_menu_radio_item(HMENU menu_handle,
                                   uint32_t first,
                                   uint32_t last,
                                   uint32_t check,
                                   uint32_t flag);

        int32_t enable_menu_item(HMENU menu_handle,
                             uint32_t id_enable_item,
                             uint32_t enable);

        bool track_popup_menu(HMENU menu_handle,
                              uint32_t flag,
                              int32_t x,
                              int32_t y,
                              int32_t reserved,
                              HWND hwnd,
                              const RECT *rect);

        bool track_popup_menu(HMENU menu_handle,
                              uint32_t flag,
                              int32_t x,
                              int32_t y,
                              HWND hwnd,
                              TPMPARAMS *tpm_params);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //MENU_H
