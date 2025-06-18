/* clang-format off */
/*
 * @file image_list.h
 * @date 2025-05-26
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
#ifndef IMAGE_LIST_H
#define IMAGE_LIST_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <commoncontrols.h>
#include <minwindef.h>
#include <objidlbase.h>
#include <winnt.h>
#include <Unknwnbase.h>
#include <windef.h>
#include <cstdint>
#include <vector>
#include "ui/core/core.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class image_list {
    public:
        image_list(const image_list &other) = delete;

        image_list(image_list &&other) = delete;

        image_list &operator=(const image_list &other) = delete;

        image_list &operator=(image_list &&other) = delete;

        image_list() = default;

        ~image_list() = default;

        static HIMAGELIST create(int32_t width,
                                 int32_t height,
                                 int32_t init,
                                 int32_t grow,
                                 ILCreateFlag flag = ILCreateFlag::Color32);

        static int32_t add(HIMAGELIST image_list_handle,
                           HBITMAP bitmap_handle,
                           HBITMAP mask_bitmap_handle = nullptr);

        static int32_t add_mask(HIMAGELIST image_list_handle,
                                HBITMAP bitmap_handle,
                                COLORREF mask);

        static HRESULT com_create_instance(IImageList *image_list,
                                           const IUnknown *unknown = nullptr);

        static HRESULT com_create_instance(IImageList2 *image_list,
                                           const IUnknown *unknown = nullptr);

        static HRESULT query_interface(HIMAGELIST image_list_handle,
                                       IImageList *image_list);

        static HRESULT query_interface(HIMAGELIST image_list_handle,
                                       IImageList2 *image_list);

        static HIMAGELIST read(IStream *stream);

        static HRESULT read(IStream *stream, IImageList *image_list);

        static HRESULT read(IStream *stream, IImageList2 *image_list);

        static bool write(IStream *stream, HIMAGELIST image_list_handle);

        static bool
        write(IStream *stream, HIMAGELIST image_list_handle, HRESULT *error);

        static HIMAGELIST merge(HIMAGELIST image_list_handle1,
                                int32_t index1,
                                HIMAGELIST image_list_handle2,
                                int32_t index2,
                                int32_t offset_x,
                                int32_t offset_y);

        static bool replace(HIMAGELIST image_list_handle,
                            int32_t index,
                            HBITMAP bitmap_handle,
                            HBITMAP mask_bitmap_handle = nullptr);

        static bool copy(HIMAGELIST image_list_handle_dst,
                         int32_t index_dst,
                         HIMAGELIST image_list_handle_src,
                         int32_t index_src);

        static bool swap(HIMAGELIST image_list_handle_dst,
                         int32_t index_dst,
                         HIMAGELIST image_list_handle_src,
                         int32_t index_src);

        static HIMAGELIST duplicate(HIMAGELIST image_list_handle);

        static bool remove(HIMAGELIST image_list_handle, int32_t index);

        static bool remove_all(HIMAGELIST image_list_handle);

        static bool destroy(HIMAGELIST image_list_handle);

        static bool begin_drag(HIMAGELIST image_list_handle,
                               int32_t index,
                               int32_t hotspot_x,
                               int32_t hotspot_y);

        static bool drag_enter(HWND window_handle, int32_t x, int32_t y);

        static bool drag_leave(HWND window_handle);

        static bool drag_move(int32_t x, int32_t y);

        static bool drag_show();

        static bool drag_hide();

        static HIMAGELIST get_drag_image(POINT *point,
                                         POINT *hotspot = nullptr);

        static bool set_drag_cursor_image(HIMAGELIST image_list_handle,
                                          int32_t index,
                                          int32_t hotspot_x,
                                          int32_t hotspot_y);

        static void end_drag();

        static HIMAGELIST load_image(const char *file_path,
                                     int32_t width,
                                     COLORREF mask = CLR_DEFAULT,
                                     HINSTANCE instance_handle = nullptr,
                                     core::ImageFlag flag = core::ImageFlag::LoadFromFile |
                                             core::ImageFlag::CreateDibSection);

        static HIMAGELIST load_image(const wchar_t *file_path,
                                     int32_t width,
                                     COLORREF mask = CLR_DEFAULT,
                                     HINSTANCE instance_handle = nullptr,
                                     core::ImageFlag flag = core::ImageFlag::LoadFromFile |
                                             core::ImageFlag::CreateDibSection);

        static int32_t get_image_count(HIMAGELIST image_list_handle);

        static bool set_image_count(HIMAGELIST image_list_handle,
                                    uint32_t count);

        static bool get_image_info(HIMAGELIST image_list_handle,
                                   int32_t index,
                                   IMAGEINFO *image_info);

        static bool set_overlay_image(HIMAGELIST image_list_handle,
                                      int32_t index,
                                      int32_t overlay_index);

        static int32_t add_icon(HIMAGELIST image_list_handle,
                                HICON icon_handle);

        static HICON extract_icon(HIMAGELIST image_list_handle, int32_t index);

        static HICON get_icon(HIMAGELIST image_list_handle,
                              int32_t index,
                              ILDrawFlag flag = ILDrawFlag::Normal);

        static bool get_icon_size(HIMAGELIST image_list_handle,
                                  int32_t *width,
                                  int32_t *height);

        static bool set_icon_size(HIMAGELIST image_list_handle,
                                  int32_t width,
                                  int32_t height);

        static int32_t replace_icon(HIMAGELIST image_list_handle,
                                    int32_t index,
                                    HICON icon_handle);

        static HIMAGELIST load_bitmap(const char *bitmap_file,
                                      int32_t width,
                                      COLORREF mask = CLR_NONE,
                                      HINSTANCE instance_handle = nullptr);

        static HIMAGELIST load_bitmap(const wchar_t *bitmap_file,
                                      int32_t width,
                                      COLORREF mask = CLR_NONE,
                                      HINSTANCE instance_handle = nullptr);

        static bool draw(HIMAGELIST image_list_handle,
                         int32_t index,
                         HDC dc_handle,
                         int32_t x,
                         int32_t y,
                         ILDrawFlag flag = ILDrawFlag::Normal);

        static bool draw(HIMAGELIST image_list_handle,
                         int32_t index,
                         HDC dc_handle,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         COLORREF background = CLR_DEFAULT,
                         COLORREF foreground = CLR_DEFAULT,
                         ILDrawFlag flag = ILDrawFlag::Normal);

        static bool draw(IMAGELISTDRAWPARAMS *image_list_draw_params);

        static COLORREF get_background_color(HIMAGELIST image_list_handle);

        static COLORREF set_background_color(HIMAGELIST image_list_handle,
                                             COLORREF background);
    };
} // namespace YanLib::ui::components
#endif // IMAGE_LIST_H
