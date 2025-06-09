//
// Created by forkernel on 2025/4/30.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::ui::core {
#ifndef IMAGEFLAG
#define IMAGEFLAG

    enum class ImageFlag : uint32_t {
        DefaultColor = LR_DEFAULTCOLOR,
        MonoChrome = LR_MONOCHROME,
        Color = LR_COLOR,
        CopyReturnOrg = LR_COPYRETURNORG,
        CopyDeleteOrg = LR_COPYDELETEORG,
        LoadFromFile = LR_LOADFROMFILE,
        LoadTransParent = LR_LOADTRANSPARENT,
        DefaultSize = LR_DEFAULTSIZE,
        VgaColor = LR_VGACOLOR,
        LoadMap3dColors = LR_LOADMAP3DCOLORS,
        CreateDibSection = LR_CREATEDIBSECTION,
        CopyFromResource = LR_COPYFROMRESOURCE,
        Shared = LR_SHARED,
    };

    inline ImageFlag operator|(ImageFlag a, ImageFlag b) {
        return static_cast<ImageFlag>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }
#endif
    class image {
    private:
        std::vector<HBITMAP> bitmap_handles = {};
        std::vector<HICON> icon_handles = {};
        std::vector<HCURSOR> cursor_handles = {};
        sync::rwlock bitmap_rwlock = {};
        sync::rwlock icon_rwlock = {};
        sync::rwlock cursor_rwlock = {};
        uint32_t error_code = 0;

    public:
        image(const image &other) = delete;

        image(image &&other) = delete;

        image &operator=(const image &other) = delete;

        image &operator=(image &&other) = delete;

        image() = default;

        ~image();

        HBITMAP load_bitmap(HINSTANCE instance_handle,
                            const char *image_name,
                            int32_t width,
                            int32_t height,
                            ImageFlag flag);

        HBITMAP load_bitmap(HINSTANCE instance_handle,
                            const wchar_t *image_name,
                            int32_t width,
                            int32_t height,
                            ImageFlag flag);

        HICON load_icon(HINSTANCE instance_handle,
                        const char *image_name,
                        int32_t width,
                        int32_t height,
                        ImageFlag flag);

        HICON load_icon(HINSTANCE instance_handle,
                        const wchar_t *image_name,
                        int32_t width,
                        int32_t height,
                        ImageFlag flag);

        HCURSOR load_cursor(HINSTANCE instance_handle,
                            const char *image_name,
                            int32_t width,
                            int32_t height,
                            ImageFlag flag);

        HCURSOR load_cursor(HINSTANCE instance_handle,
                            const wchar_t *image_name,
                            int32_t width,
                            int32_t height,
                            ImageFlag flag);

        HBITMAP
        copy_bitmap(HBITMAP bitmap_handle,
                    int32_t width,
                    int32_t height,
                    ImageFlag flag);

        HICON
        copy_icon(HICON icon_handle,
                  int32_t width,
                  int32_t height,
                  ImageFlag flag);

        HCURSOR
        copy_cursor(HCURSOR cursor_handle,
                    int32_t width,
                    int32_t height,
                    ImageFlag flag);

        bool destroy_bitmap(HBITMAP bitmap_handle);

        bool destroy_icon(HICON icon_handle);

        bool destroy_cursor(HCURSOR cursor_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // IMAGE_H
