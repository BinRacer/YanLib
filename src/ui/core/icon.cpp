/* clang-format off */
/*
 * @file icon.cpp
 * @date 2025-04-30
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
#include "icon.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    icon::~icon() {
        for (auto &icon : icon_handles) {
            if (icon) {
                DestroyIcon(icon);
                icon = nullptr;
            }
        }
        icon_handles.clear();
    }

    HICON icon::create(HINSTANCE instance_handle,
                       int32_t width,
                       int32_t height,
                       uint8_t planes,
                       uint8_t bits_pixel,
                       const uint8_t *and_bits,
                       const uint8_t *xor_bits) {
        HICON result = CreateIcon(instance_handle, width, height, planes,
                                  bits_pixel, and_bits, xor_bits);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        icon_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HICON icon::create(uint8_t *res_buf,
                       uint32_t res_size,
                       bool is_icon,
                       uint32_t version) {
        HICON result = CreateIconFromResource(res_buf, res_size,
                                              is_icon ? TRUE : FALSE, version);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        icon_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HICON icon::create(uint8_t *res_buf,
                       uint32_t res_size,
                       bool is_icon,
                       uint32_t version,
                       int32_t desired_width,
                       int32_t desired_height,
                       IconFlag flag) {
        HICON result = CreateIconFromResourceEx(res_buf, res_size,
                                                is_icon ? TRUE : FALSE, version,
                                                desired_width, desired_height,
                                                static_cast<uint32_t>(flag));
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        if (static_cast<uint32_t>(flag) & LR_SHARED) {
            return result;
        }
        rwlock.write_lock();
        icon_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HICON icon::create(ICONINFO *icon_info) {
        HICON result = CreateIconIndirect(icon_info);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        icon_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HICON icon::load(HINSTANCE instance_handle, const char *icon_name) {
        HICON result = LoadIconA(instance_handle, icon_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HICON icon::load(HINSTANCE instance_handle, const wchar_t *icon_name) {
        HICON result = LoadIconW(instance_handle, icon_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HICON icon::copy(HICON icon_handle) {
        HICON result = CopyIcon(icon_handle);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        icon_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    bool icon::draw(HDC dc_handle, int32_t x, int32_t y, HICON icon_handle) {
        if (!DrawIcon(dc_handle, x, y, icon_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool icon::draw(HDC dc_handle,
                    int32_t left,
                    int32_t top,
                    HICON icon_handle,
                    int32_t width,
                    int32_t height,
                    uint32_t step_if_ani_cur,
                    HBRUSH hbr_flicker_free_draw,
                    DrawIconFlag flag) {
        if (!DrawIconEx(dc_handle, left, top, icon_handle, width, height,
                        step_if_ani_cur, hbr_flicker_free_draw,
                        static_cast<uint32_t>(flag))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool icon::destroy(HICON icon_handle) {
        if (!icon_handle) {
            return false;
        }
        rwlock.write_lock();
        const auto it = std::find(icon_handles.begin(), icon_handles.end(),
                                  icon_handle);
        if (it != icon_handles.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        if (!DestroyIcon(icon_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool icon::get_info(HICON icon_handle, ICONINFO *icon_info) {
        if (!GetIconInfo(icon_handle, icon_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool icon::get_info(HICON icon_handle, ICONINFOEXA *icon_info) {
        return GetIconInfoExA(icon_handle, icon_info);
    }

    bool icon::get_info(HICON icon_handle, ICONINFOEXW *icon_info) {
        return GetIconInfoExW(icon_handle, icon_info);
    }

    int32_t icon::lookup_icon_id(uint8_t *res_buf, bool is_icon) {
        const int32_t result = LookupIconIdFromDirectory(res_buf, is_icon);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t icon::lookup_icon_id(uint8_t *res_buf,
                                 bool is_icon,
                                 int32_t desired_width,
                                 int32_t desired_height,
                                 IconFlag flag) {
        const int32_t result =
                LookupIconIdFromDirectoryEx(res_buf, is_icon, desired_width,
                                            desired_height,
                                            static_cast<uint32_t>(flag));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t icon::extract(const char *file_name,
                           int32_t icon_index,
                           int32_t icon_width,
                           int32_t icon_height,
                           std::vector<HICON> &icon_handle,
                           uint32_t *icon_id,
                           IconFlag flag) {
        return PrivateExtractIconsA(file_name, icon_index, icon_width,
                                    icon_height, icon_handle.data(), icon_id,
                                    icon_handle.size(),
                                    static_cast<uint32_t>(flag));
    }

    uint32_t icon::extract(const wchar_t *file_name,
                           int32_t icon_index,
                           int32_t icon_width,
                           int32_t icon_height,
                           std::vector<HICON> &icon_handle,
                           uint32_t *icon_id,
                           IconFlag flag) {
        return PrivateExtractIconsW(file_name, icon_index, icon_width,
                                    icon_height, icon_handle.data(), icon_id,
                                    icon_handle.size(),
                                    static_cast<uint32_t>(flag));
    }

    uint32_t icon::err_code() const {
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
} // namespace YanLib::ui::core
