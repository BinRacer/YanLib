//
// Created by forkernel on 2025/5/18.
//

#include "window_aware.h"
#include "helper/convert.h"
namespace YanLib::ui {
DPI_AWARENESS_CONTEXT window_aware::get_dpi_context(HWND window_handle) {
    return GetWindowDpiAwarenessContext(window_handle);
}

bool window_aware::is_dpi_context_equal(DPI_AWARENESS_CONTEXT context1,
    DPI_AWARENESS_CONTEXT                                     context2) {
    return AreDpiAwarenessContextsEqual(context1, context2);
}

bool window_aware::is_proc_dpi() {
    return IsProcessDPIAware();
}

bool window_aware::is_valid_dpi_context(DPI_AWARENESS_CONTEXT context) {
    return IsValidDpiAwarenessContext(context);
}

uint32_t window_aware::dpi_context_to_dpi(DPI_AWARENESS_CONTEXT context) {
    return GetDpiFromDpiAwarenessContext(context);
}

DPI_AWARENESS window_aware::dpi_context_to_dpi_aware(
    DPI_AWARENESS_CONTEXT context) {
    return GetAwarenessFromDpiAwarenessContext(context);
}

DPI_AWARENESS_CONTEXT window_aware::get_proc_dpi_context(HANDLE proc_handle) {
    return GetDpiAwarenessContextForProcess(proc_handle);
}

HRESULT window_aware::get_proc_dpi_aware(HANDLE proc_handle,
    PROCESS_DPI_AWARENESS                      *dpi_aware) {
    return GetProcessDpiAwareness(proc_handle, dpi_aware);
}

HRESULT window_aware::set_proc_dpi_aware(PROCESS_DPI_AWARENESS dpi_aware) {
    return SetProcessDpiAwareness(dpi_aware);
}

bool window_aware::set_proc_dpi_context(DPI_AWARENESS_CONTEXT value) {
    if (!SetProcessDpiAwarenessContext(value)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

DPI_AWARENESS_CONTEXT window_aware::get_thread_dpi_context() {
    return GetThreadDpiAwarenessContext();
}

DPI_AWARENESS_CONTEXT window_aware::set_thread_dpi_context(
    DPI_AWARENESS_CONTEXT context) {
    return SetThreadDpiAwarenessContext(context);
}

uint32_t window_aware::err_code() const {
    return error_code;
}

std::string window_aware::err_string() const {
    std::string result = helper::convert::err_string(error_code);
    return result;
}

std::wstring window_aware::err_wstring() const {
    std::wstring result = helper::convert::err_wstring(error_code);
    return result;
}
} // namespace YanLib::ui