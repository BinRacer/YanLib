//
// Created by forkernel on 2025/5/4.
//

#ifndef SHAPE_H
#define SHAPE_H
#include <Windows.h>

namespace YanLib::ui {
    class shape {
    public:
        shape(const shape &other) = delete;

        shape(shape &&other) = delete;

        shape &operator=(const shape &other) = delete;

        shape &operator=(shape &&other) = delete;

        shape() = default;

        ~shape() = default;

        static bool rectangle(HDC dc_handle,
                              int left, int top,
                              int right, int bottom);

        static int fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static bool round_rect(HDC dc_handle,
                               int left, int top,
                               int right, int bottom,
                               int width, int height);

        static int frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static bool invert_rect(HDC dc_handle, const RECT *rect);

        static bool ellipse(HDC dc_handle,
                            int left, int top,
                            int right, int bottom);

        static bool chord(HDC dc_handle,
                          int x1, int y1,
                          int x2, int y2,
                          int x3, int y3,
                          int x4, int y4);

        static bool poly_gon(HDC dc_handle, const POINT *point, int num);

        static bool poly_poly_gon(HDC dc_handle,
                                  const POINT *point,
                                  const INT *num_array,
                                  int num);

        static bool pie(HDC dc_handle,
                        int left, int top,
                        int right, int bottom,
                        int xr1, int yr1,
                        int xr2, int yr2);
    };
}
#endif //SHAPE_H
