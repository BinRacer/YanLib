/* clang-format off */
/*
 * @file image_list.cpp
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
#include "image_list.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    HIMAGELIST image_list::create(int32_t width,
                                  int32_t height,
                                  int32_t init,
                                  int32_t grow,
                                  ILCreateFlag flag) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_WIN95_CLASSES;
        InitCommonControlsEx(&icc);
        return ImageList_Create(width, height, static_cast<uint32_t>(flag),
                                init, grow);
    }

    int32_t image_list::add(HIMAGELIST image_list_handle,
                            HBITMAP bitmap_handle,
                            HBITMAP mask_bitmap_handle) {
        return ImageList_Add(image_list_handle, bitmap_handle,
                             mask_bitmap_handle);
    }

    int32_t image_list::add_mask(HIMAGELIST image_list_handle,
                                 HBITMAP bitmap_handle,
                                 COLORREF mask) {
        return ImageList_AddMasked(image_list_handle, bitmap_handle, mask);
    }

    HRESULT image_list::com_create_instance(IImageList *image_list,
                                            const IUnknown *unknown) {
        return ImageList_CoCreateInstance(CLSID_ImageList, unknown,
                                          IID_IImageList,
                                          reinterpret_cast<void **>(
                                                  &image_list));
    }

    HRESULT image_list::com_create_instance(IImageList2 *image_list,
                                            const IUnknown *unknown) {
        return ImageList_CoCreateInstance(CLSID_ImageList, unknown,
                                          IID_IImageList2,
                                          reinterpret_cast<void **>(
                                                  &image_list));
    }

    HRESULT image_list::query_interface(HIMAGELIST image_list_handle,
                                        IImageList *image_list) {
        return HIMAGELIST_QueryInterface(image_list_handle, IID_IImageList,
                                         reinterpret_cast<void **>(
                                                 &image_list));
    }

    HRESULT image_list::query_interface(HIMAGELIST image_list_handle,
                                        IImageList2 *image_list) {
        return HIMAGELIST_QueryInterface(image_list_handle, IID_IImageList2,
                                         reinterpret_cast<void **>(
                                                 &image_list));
    }

    HIMAGELIST image_list::read(IStream *stream) {
        return ImageList_Read(stream);
    }

    HRESULT image_list::read(IStream *stream, IImageList *image_list) {
        return ImageList_ReadEx(ILP_NORMAL, stream, IID_IImageList,
                                reinterpret_cast<void **>(&image_list));
    }

    HRESULT image_list::read(IStream *stream, IImageList2 *image_list) {
        return ImageList_ReadEx(ILP_NORMAL, stream, IID_IImageList2,
                                reinterpret_cast<void **>(&image_list));
    }

    bool image_list::write(IStream *stream, HIMAGELIST image_list_handle) {
        return ImageList_Write(image_list_handle, stream);
    }

    bool image_list::write(IStream *stream,
                           HIMAGELIST image_list_handle,
                           HRESULT *error) {
        if (!error) {
            return false;
        }
        const HRESULT result =
                ImageList_WriteEx(image_list_handle, ILP_NORMAL, stream);
        *error = result;
        if (result != S_OK) {
            return false;
        }
        return true;
    }

    HIMAGELIST image_list::merge(HIMAGELIST image_list_handle1,
                                 int32_t index1,
                                 HIMAGELIST image_list_handle2,
                                 int32_t index2,
                                 int32_t offset_x,
                                 int32_t offset_y) {
        return ImageList_Merge(image_list_handle1, index1, image_list_handle2,
                               index2, offset_x, offset_y);
    }

    bool image_list::replace(HIMAGELIST image_list_handle,
                             int32_t index,
                             HBITMAP bitmap_handle,
                             HBITMAP mask_bitmap_handle) {
        return ImageList_Replace(image_list_handle, index, bitmap_handle,
                                 mask_bitmap_handle);
    }

    bool image_list::copy(HIMAGELIST image_list_handle_dst,
                          int32_t index_dst,
                          HIMAGELIST image_list_handle_src,
                          int32_t index_src) {
        return ImageList_Copy(image_list_handle_dst, index_dst,
                              image_list_handle_src, index_src, ILCF_MOVE);
    }

    bool image_list::swap(HIMAGELIST image_list_handle_dst,
                          int32_t index_dst,
                          HIMAGELIST image_list_handle_src,
                          int32_t index_src) {
        return ImageList_Copy(image_list_handle_dst, index_dst,
                              image_list_handle_src, index_src, ILCF_SWAP);
    }

    HIMAGELIST image_list::duplicate(HIMAGELIST image_list_handle) {
        return ImageList_Duplicate(image_list_handle);
    }

    bool image_list::remove(HIMAGELIST image_list_handle, int32_t index) {
        return ImageList_Remove(image_list_handle, index);
    }

    bool image_list::remove_all(HIMAGELIST image_list_handle) {
        return ImageList_RemoveAll(image_list_handle);
    }

    bool image_list::destroy(HIMAGELIST image_list_handle) {
        return ImageList_Destroy(image_list_handle);
    }

    bool image_list::begin_drag(HIMAGELIST image_list_handle,
                                int32_t index,
                                int32_t hotspot_x,
                                int32_t hotspot_y) {
        return ImageList_BeginDrag(image_list_handle, index, hotspot_x,
                                   hotspot_y);
    }

    bool image_list::drag_enter(HWND window_handle, int32_t x, int32_t y) {
        return ImageList_DragEnter(window_handle, x, y);
    }

    bool image_list::drag_leave(HWND window_handle) {
        return ImageList_DragLeave(window_handle);
    }

    bool image_list::drag_move(int32_t x, int32_t y) {
        return ImageList_DragMove(x, y);
    }

    bool image_list::drag_show() {
        return ImageList_DragShowNolock(TRUE);
    }

    bool image_list::drag_hide() {
        return ImageList_DragShowNolock(FALSE);
    }

    HIMAGELIST image_list::get_drag_image(POINT *point, POINT *hotspot) {
        return ImageList_GetDragImage(point, hotspot);
    }

    bool image_list::set_drag_cursor_image(HIMAGELIST image_list_handle,
                                           int32_t index,
                                           int32_t hotspot_x,
                                           int32_t hotspot_y) {
        return ImageList_SetDragCursorImage(image_list_handle, index, hotspot_x,
                                            hotspot_y);
    }

    void image_list::end_drag() {
        ImageList_EndDrag();
    }

    HIMAGELIST image_list::load_image(const char *file_path,
                                      int32_t width,
                                      COLORREF mask,
                                      HINSTANCE instance_handle,
                                      ImageFlag flag) {
        return ImageList_LoadImageA(instance_handle, file_path, width, 0, mask,
                                    IMAGE_BITMAP, static_cast<uint32_t>(flag));
    }

    HIMAGELIST image_list::load_image(const wchar_t *file_path,
                                      int32_t width,
                                      COLORREF mask,
                                      HINSTANCE instance_handle,
                                      ImageFlag flag) {
        return ImageList_LoadImageW(instance_handle, file_path, width, 0, mask,
                                    IMAGE_BITMAP, static_cast<uint32_t>(flag));
    }

    int32_t image_list::get_image_count(HIMAGELIST image_list_handle) {
        return ImageList_GetImageCount(image_list_handle);
    }

    bool image_list::set_image_count(HIMAGELIST image_list_handle,
                                     uint32_t count) {
        return ImageList_SetImageCount(image_list_handle, count);
    }

    bool image_list::get_image_info(HIMAGELIST image_list_handle,
                                    int32_t index,
                                    IMAGEINFO *image_info) {
        return ImageList_GetImageInfo(image_list_handle, index, image_info);
    }

    bool image_list::set_overlay_image(HIMAGELIST image_list_handle,
                                       int32_t index,
                                       int32_t overlay_index) {
        return ImageList_SetOverlayImage(image_list_handle, index,
                                         overlay_index);
    }

    int32_t image_list::add_icon(HIMAGELIST image_list_handle,
                                 HICON icon_handle) {
        return ImageList_AddIcon(image_list_handle, icon_handle);
    }

    HICON image_list::extract_icon(HIMAGELIST image_list_handle,
                                   int32_t index) {
        return ImageList_ExtractIcon(nullptr, image_list_handle, index);
    }

    HICON image_list::get_icon(HIMAGELIST image_list_handle,
                               int32_t index,
                               ILDrawFlag flag) {
        return ImageList_GetIcon(image_list_handle, index,
                                 static_cast<uint32_t>(flag));
    }

    bool image_list::get_icon_size(HIMAGELIST image_list_handle,
                                   int32_t *width,
                                   int32_t *height) {
        return ImageList_GetIconSize(image_list_handle, width, height);
    }

    bool image_list::set_icon_size(HIMAGELIST image_list_handle,
                                   int32_t width,
                                   int32_t height) {
        return ImageList_SetIconSize(image_list_handle, width, height);
    }

    int32_t image_list::replace_icon(HIMAGELIST image_list_handle,
                                     int32_t index,
                                     HICON icon_handle) {
        return ImageList_ReplaceIcon(image_list_handle, index, icon_handle);
    }

    HIMAGELIST image_list::load_bitmap(const char *bitmap_file,
                                       int32_t width,
                                       COLORREF mask,
                                       HINSTANCE instance_handle) {
        return ImageList_LoadImageA(instance_handle, bitmap_file, width, 0,
                                    mask, IMAGE_BITMAP, 0);
    }

    HIMAGELIST image_list::load_bitmap(const wchar_t *bitmap_file,
                                       int32_t width,
                                       COLORREF mask,
                                       HINSTANCE instance_handle) {
        return ImageList_LoadImageW(instance_handle, bitmap_file, width, 0,
                                    mask, IMAGE_BITMAP, 0);
    }

    bool image_list::draw(HIMAGELIST image_list_handle,
                          int32_t index,
                          HDC dc_handle,
                          int32_t x,
                          int32_t y,
                          ILDrawFlag flag) {
        return ImageList_Draw(image_list_handle, index, dc_handle, x, y,
                              static_cast<uint32_t>(flag));
    }

    bool image_list::draw(HIMAGELIST image_list_handle,
                          int32_t index,
                          HDC dc_handle,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          COLORREF background,
                          COLORREF foreground,
                          ILDrawFlag flag) {
        return ImageList_DrawEx(image_list_handle, index, dc_handle, x, y,
                                width, height, background, foreground,
                                static_cast<uint32_t>(flag));
    }

    bool image_list::draw(IMAGELISTDRAWPARAMS *image_list_draw_params) {
        return ImageList_DrawIndirect(image_list_draw_params);
    }

    COLORREF image_list::get_background_color(HIMAGELIST image_list_handle) {
        return ImageList_GetBkColor(image_list_handle);
    }

    COLORREF image_list::set_background_color(HIMAGELIST image_list_handle,
                                              COLORREF background) {
        return ImageList_SetBkColor(image_list_handle, background);
    }
} // namespace YanLib::ui::components
