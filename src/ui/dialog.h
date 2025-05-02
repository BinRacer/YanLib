//
// Created by forkernel on 2025/4/30.
//

#ifndef DIALOG_H
#define DIALOG_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class dialog {
    private:
        DWORD error_code = 0;

    public:
        dialog(const dialog &other) = delete;

        dialog(dialog &&other) = delete;

        dialog &operator=(const dialog &other) = delete;

        dialog &operator=(dialog &&other) = delete;

        dialog() = default;

        ~dialog() = default;

        INT_PTR create_dialog(HINSTANCE instance_handle,
                              const wchar_t *template_name,
                              HWND hwnd_parent,
                              DLGPROC dialog_func);

        INT_PTR create_dialog(HINSTANCE instance_handle,
                              const wchar_t *template_name,
                              HWND hwnd_parent,
                              DLGPROC dialog_func,
                              LPARAM init_param);

        INT_PTR create_dialog_indirect(HINSTANCE instance_handle,
                                       LPCDLGTEMPLATEW dialog_template,
                                       HWND hwnd_parent,
                                       DLGPROC dialog_func);

        INT_PTR create_dialog_indirect(HINSTANCE instance_handle,
                                       LPCDLGTEMPLATEW dialog_template,
                                       HWND hwnd_parent,
                                       DLGPROC dialog_func,
                                       LPARAM init_param);

        HWND create_dialog_modeless(HINSTANCE instance_handle,
                                    const wchar_t *template_name,
                                    HWND hwnd_parent,
                                    DLGPROC dialog_func);

        HWND create_dialog_modeless(HINSTANCE instance_handle,
                                    const wchar_t *template_name,
                                    HWND hwnd_parent,
                                    DLGPROC dialog_func,
                                    LPARAM init_param);

        HWND create_dialog_indirect_modeless(HINSTANCE instance_handle,
                                             LPCDLGTEMPLATEW dialog_template,
                                             HWND hwnd_parent,
                                             DLGPROC dialog_func);

        HWND create_dialog_indirect_modeless(HINSTANCE instance_handle,
                                             LPCDLGTEMPLATEW dialog_template,
                                             HWND hwnd_parent,
                                             DLGPROC dialog_func,
                                             LPARAM init_param);

        bool end_dialog(HWND hwnd_dialog, INT_PTR result);

        bool check_dialog_button(HWND hwnd_dialog, int id_button, UINT check);

        LRESULT default_dialog_proc(HWND hwnd_dialog,
                                    UINT msg,
                                    WPARAM w_param,
                                    LPARAM l_param);

        int dialog_dir_list(HWND hwnd_dialog,
                            wchar_t *path_spec,
                            int id_listbox,
                            int id_static_path,
                            UINT file_type);

        int dialog_dir_list_combobox(HWND hwnd_dialog,
                                     wchar_t *path_spec,
                                     int id_combobox,
                                     int id_static_path,
                                     UINT filetype);

        bool dialog_dir_select_combobox(HWND hwnd_dialog,
                                        wchar_t *text,
                                        int cch_size,
                                        int id_combobox);

        bool dialog_dir_select(HWND hwnd_dialog,
                               wchar_t *text,
                               int cch_size,
                               int id_listbox);

        int get_dialog_ctrl_id(HWND hwnd_ctrl);

        HWND get_dialog_item(HWND hwnd_dialog, int id_dialog_item);

        std::pair<UINT, bool> get_dialog_item_int(HWND hwnd_dialog,
                                                  int id_dialog_item,
                                                  bool is_signed);

        bool set_dialog_item_int(HWND hwnd_dialog,
                                 int id_dialog_item,
                                 UINT value,
                                 bool is_signed);

        UINT get_dialog_item_text(HWND hwnd_dialog,
                                  int id_dialog_item,
                                  wchar_t *text,
                                  int cch_max);

        bool set_dialog_item_text(HWND hwnd_dialog,
                                  int id_dialog_item,
                                  const wchar_t *text);

        HWND get_next_dialog_group_item(HWND hwnd_dialog,
                                        HWND hwnd_ctrl,
                                        bool previous);

        HWND get_next_dialog_tab_item(HWND hwnd_dialog,
                                      HWND hwnd_ctrl,
                                      bool previous);

        UINT is_dialog_button_checked(HWND hwnd_dialog, int id_button);

        long get_dialog_base_units();

        DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS
        get_dialog_control_dpi_change_behavior(HWND hwnd_dialog);

        bool set_dialog_control_dpi_change_behavior(
            HWND hwnd_dialog,
            DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS mask,
            DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS values);

        DIALOG_DPI_CHANGE_BEHAVIORS
        get_dialog_dpi_change_behavior(HWND hwnd_dialog);

        bool set_dialog_dpi_change_behavior(
            HWND hwnd_dialog,
            DIALOG_DPI_CHANGE_BEHAVIORS mask,
            DIALOG_DPI_CHANGE_BEHAVIORS values);

        bool map_dialog_rect(HWND hwnd_dialog, LPRECT rect);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //DIALOG_H
