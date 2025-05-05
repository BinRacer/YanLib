//
// Created by forkernel on 2025/5/4.
//

#ifndef PATH_H
#define PATH_H
#include <cstdint>
#include <Windows.h>

namespace YanLib::ui::gdi {
    class path {
    public:
        path(const path &other) = delete;

        path(path &&other) = delete;

        path &operator=(const path &other) = delete;

        path &operator=(path &&other) = delete;

        path() = default;

        ~path() = default;

        static bool begin_path(HDC dc_handle);

        static bool end_path(HDC dc_handle);

        static int32_t get_path(HDC dc_handle,
                            POINT *point,
                            uint8_t *type_array,
                            int32_t num);

        static bool fill_path(HDC dc_handle);

        static bool abort_path(HDC dc_handle);

        static bool flatten_path(HDC dc_handle);

        static bool stroke_and_fill_path(HDC dc_handle);

        static bool stroke_path(HDC dc_handle);

        static bool widen_path(HDC dc_handle);

        static HRGN path_to_region(HDC dc_handle);

        static bool close_figure(HDC dc_handle);

        static bool get_miter_limit(HDC dc_handle, FLOAT *limit);

        static bool set_miter_limit(HDC dc_handle, FLOAT limit, FLOAT *old);
    };
}
#endif //PATH_H
