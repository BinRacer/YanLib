//
// Created by forkernel on 2025/4/30.
//

#include "bitmap.h"

namespace YanLib::ui {
    HBITMAP bitmap::load_bitmap(HINSTANCE hinstance_handle,
                                const wchar_t *bitmap_name) {
        return LoadBitmapW(hinstance_handle, bitmap_name);
    }
}
