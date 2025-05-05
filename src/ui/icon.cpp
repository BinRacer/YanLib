//
// Created by forkernel on 2025/4/30.
//

#include "icon.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HICON icon::create_icon(HINSTANCE instance_handle,
                            int width,
                            int height,
                            uint8_t planes,
                            uint8_t bits_pixel,
                            const uint8_t *and_bits,
                            const uint8_t *xor_bits) {
        HICON result = CreateIcon(instance_handle,
                                  width,
                                  height,
                                  planes,
                                  bits_pixel,
                                  and_bits,
                                  xor_bits);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HICON icon::create_icon_from_resource(uint8_t *res_buf,
                                          unsigned long res_size,
                                          bool is_icon,
                                          unsigned long version) {
        HICON result = CreateIconFromResource(res_buf,
                                              res_size,
                                              is_icon ? TRUE : FALSE,
                                              version);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HICON icon::create_icon_from_resource(uint8_t *res_buf,
                                          unsigned long res_size,
                                          bool is_icon,
                                          unsigned long version,
                                          int desired_width,
                                          int desired_height,
                                          unsigned int flag) {
        HICON result = CreateIconFromResourceEx(res_buf,
                                                res_size,
                                                is_icon ? TRUE : FALSE,
                                                version,
                                                desired_width,
                                                desired_height,
                                                flag);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HICON icon::create_icon_indirect(ICONINFO* icon_info) {
        HICON result = CreateIconIndirect(icon_info);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HICON icon::load_icon(HINSTANCE instance_handle, const wchar_t *icon_name) {
        HICON result = LoadIconW(instance_handle, icon_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HICON icon::copy_icon(HICON icon_handle) {
        HICON result = CopyIcon(icon_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool icon::draw_icon(HDC dc_handle, int x, int y, HICON icon_handle) {
        if (!DrawIcon(dc_handle, x, y, icon_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool icon::draw_icon(HDC dc_handle,
                         int x_left,
                         int y_top,
                         HICON icon_handle,
                         int cx_width,
                         int cy_width,
                         unsigned int step_if_ani_cur,
                         HBRUSH hbr_flicker_free_draw,
                         unsigned int flag) {
        if (!DrawIconEx(dc_handle,
                        x_left,
                        y_top,
                        icon_handle,
                        cx_width,
                        cy_width,
                        step_if_ani_cur,
                        hbr_flicker_free_draw,
                        flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool icon::destroy_icon(HICON icon_handle) {
        if (!DestroyIcon(icon_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool icon::get_icon_info(HICON icon_handle, ICONINFO* icon_info) {
        if (!GetIconInfo(icon_handle, icon_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool icon::get_icon_info(HICON icon_handle, ICONINFOEXW* icon_info) {
        return GetIconInfoExW(icon_handle, icon_info);
    }

    int icon::lookup_icon_id_from_directory(uint8_t *res_buf, bool is_icon) {
        int result = LookupIconIdFromDirectory(res_buf, is_icon);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int icon::lookup_icon_id_from_directory(uint8_t *res_buf,
                                            bool is_icon,
                                            int desired_width,
                                            int desired_height,
                                            unsigned int flag) {
        int result = LookupIconIdFromDirectoryEx(res_buf,
                                                 is_icon,
                                                 desired_width,
                                                 desired_height,
                                                 flag);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    unsigned int icon::private_extract_icons(const wchar_t *file_name,
                                     int icon_index,
                                     int icon_width,
                                     int icon_height,
                                     HICON *icon_handle,
                                     unsigned int *icon_id,
                                     unsigned int icon_count,
                                     unsigned int flag) {
        return PrivateExtractIconsW(file_name,
                                    icon_index,
                                    icon_width,
                                    icon_height,
                                    icon_handle,
                                    icon_id,
                                    icon_count,
                                    flag);
    }

    unsigned long icon::err_code() const {
        return error_code;
    }

    std::string icon::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring icon::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
