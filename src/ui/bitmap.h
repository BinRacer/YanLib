//
// Created by forkernel on 2025/4/30.
//

#ifndef BITMAP_H
#define BITMAP_H
#include <Windows.h>

namespace YanLib::ui {
    class bitmap {
    public:
        bitmap(const bitmap &other) = delete;

        bitmap(bitmap &&other) = delete;

        bitmap &operator=(const bitmap &other) = delete;

        bitmap &operator=(bitmap &&other) = delete;

        bitmap() = default;

        ~bitmap() = default;

        static HBITMAP load_bitmap(HINSTANCE hinstance_handle,
                                   const wchar_t *bitmap_name);
    };
}
#endif //BITMAP_H
