cmake_minimum_required(VERSION 3.30)
project(YanLib)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(UNICODE _UNICODE)

add_library(YanLib STATIC
        src/helper/helper.h
        src/helper/convert.cpp
        src/helper/convert.h
        src/helper/string.cpp
        src/helper/string.h
        src/helper/autoclean.cpp
        src/helper/autoclean.h
        src/sync/sync.h
        src/sync/mutex.cpp
        src/sync/mutex.h
        src/sync/fence.cpp
        src/sync/fence.h
        src/sync/rwlock.cpp
        src/sync/rwlock.h
        src/sync/semaphore.cpp
        src/sync/semaphore.h
        src/sync/event.cpp
        src/sync/event.h
        src/sync/timer.cpp
        src/sync/timer.h
        src/sync/barrier.cpp
        src/sync/barrier.h
        src/sync/condvar.cpp
        src/sync/condvar.h
        src/mem/mem.h
        src/mem/mmap.cpp
        src/mem/mmap.h
        src/mem/allocate.cpp
        src/mem/allocate.h
        src/mem/heap.cpp
        src/mem/heap.h
        src/io/io.h
        src/io/fs.cpp
        src/io/fs.h
        src/io/comp_port.cpp
        src/io/comp_port.h
        src/io/tcp_server.cpp
        src/io/tcp_server.h
        src/io/tcp_client.cpp
        src/io/tcp_client.h
        src/io/udp_server.cpp
        src/io/udp_server.h
        src/io/udp_client.cpp
        src/io/udp_client.h
        src/io/http.cpp
        src/io/http.h
        src/io/ftp.cpp
        src/io/ftp.h
        src/hash/md5.cpp
        src/hash/md5.h
        src/hash/sha1.cpp
        src/hash/sha1.h
        src/hash/sha256.cpp
        src/hash/sha256.h
        src/hash/sha384.cpp
        src/hash/sha384.h
        src/hash/sha512.cpp
        src/hash/sha512.h
        src/crypto/crypto.h
        src/crypto/base16.cpp
        src/crypto/base16.h
        src/crypto/base32.cpp
        src/crypto/base32.h
        src/crypto/base58.cpp
        src/crypto/base58.h
        src/crypto/base62.cpp
        src/crypto/base62.h
        src/crypto/base64.cpp
        src/crypto/base64.h
        src/crypto/base85.cpp
        src/crypto/base85.h
        src/crypto/base91.cpp
        src/crypto/base91.h
        src/crypto/base92.cpp
        src/crypto/base92.h
        src/crypto/base100.cpp
        src/crypto/base100.h
        src/crypto/uuencode.cpp
        src/crypto/uuencode.h
        src/crypto/xxencode.cpp
        src/crypto/xxencode.h
        src/crypto/vigenere.cpp
        src/crypto/vigenere.h
        src/crypto/aes.cpp
        src/crypto/aes.h
        src/crypto/aes192.cpp
        src/crypto/aes192.h
        src/crypto/aes256.cpp
        src/crypto/aes256.h
        src/crypto/rsa.cpp
        src/crypto/rsa.h
        src/sys/sys.h
        src/sys/security.cpp
        src/sys/security.h
        src/sys/proc.cpp
        src/sys/proc.h
        src/sys/thread.cpp
        src/sys/thread.h
        src/sys/thread_pool.cpp
        src/sys/thread_pool.h
        src/sys/fiber.cpp
        src/sys/fiber.h
        src/sys/job.cpp
        src/sys/job.h
        src/sys/snapshot.cpp
        src/sys/snapshot.h
        src/sys/processor.cpp
        src/sys/processor.h
        src/ui/core/core.h
        src/ui/core/window.cpp
        src/ui/core/window.h
        src/ui/core/window_class.cpp
        src/ui/core/window_class.h
        src/ui/core/window_prop.cpp
        src/ui/core/window_prop.h
        src/ui/core/window_hook.cpp
        src/ui/core/window_hook.h
        src/ui/core/window_pos.cpp
        src/ui/core/window_pos.h
        src/ui/core/window_aware.cpp
        src/ui/core/window_aware.h
        src/ui/core/window_behavior.cpp
        src/ui/core/window_behavior.h
        src/ui/core/message.cpp
        src/ui/core/message.h
        src/ui/core/dialog.cpp
        src/ui/core/dialog.h
        src/ui/core/menu.cpp
        src/ui/core/menu.h
        src/ui/core/icon.cpp
        src/ui/core/icon.h
        src/ui/core/cursor.cpp
        src/ui/core/cursor.h
        src/ui/core/caret.cpp
        src/ui/core/caret.h
        src/ui/core/image.cpp
        src/ui/core/image.h
        src/ui/core/clipboard.cpp
        src/ui/core/clipboard.h
        src/ui/core/desktop.cpp
        src/ui/core/desktop.h
        src/ui/core/keyboard.cpp
        src/ui/core/keyboard.h
        src/ui/core/mouse.cpp
        src/ui/core/mouse.h
        src/ui/core/touch.cpp
        src/ui/core/touch.h
        src/ui/core/accelerator.cpp
        src/ui/core/accelerator.h
        src/ui/core/notify.cpp
        src/ui/core/notify.h
        src/ui/gdi/gdi.h
        src/ui/gdi/bitmap.cpp
        src/ui/gdi/bitmap.h
        src/ui/gdi/display.cpp
        src/ui/gdi/display.h
        src/ui/gdi/monitor.cpp
        src/ui/gdi/monitor.h
        src/ui/gdi/dc.cpp
        src/ui/gdi/dc.h
        src/ui/gdi/rect.cpp
        src/ui/gdi/rect.h
        src/ui/gdi/region.cpp
        src/ui/gdi/region.h
        src/ui/gdi/font.cpp
        src/ui/gdi/font.h
        src/ui/gdi/text.cpp
        src/ui/gdi/text.h
        src/ui/gdi/brush.cpp
        src/ui/gdi/brush.h
        src/ui/gdi/clip.cpp
        src/ui/gdi/clip.h
        src/ui/gdi/palette.cpp
        src/ui/gdi/palette.h
        src/ui/gdi/coordinate.cpp
        src/ui/gdi/coordinate.h
        src/ui/gdi/shape.cpp
        src/ui/gdi/shape.h
        src/ui/gdi/line.cpp
        src/ui/gdi/line.h
        src/ui/gdi/arc.cpp
        src/ui/gdi/arc.h
        src/ui/gdi/bezier.cpp
        src/ui/gdi/bezier.h
        src/ui/gdi/pen.cpp
        src/ui/gdi/pen.h
        src/ui/gdi/path.cpp
        src/ui/gdi/path.h
        src/ui/gdi/meta.cpp
        src/ui/gdi/meta.h
        src/ui/gdi/paint.cpp
        src/ui/gdi/paint.h
        src/ui/components/components.h
        src/ui/components/button.cpp
        src/ui/components/button.h
        src/ui/components/animate.cpp
        src/ui/components/animate.h
        src/ui/components/combo_box.cpp
        src/ui/components/combo_box.h
        src/ui/components/datetime.cpp
        src/ui/components/datetime.h
        src/ui/components/edit.cpp
        src/ui/components/edit.h
        src/ui/components/header.cpp
        src/ui/components/header.h
        src/ui/components/hot_key.cpp
        src/ui/components/hot_key.h
        src/ui/components/image_list.cpp
        src/ui/components/image_list.h
        src/ui/components/ip_addr.cpp
        src/ui/components/ip_addr.h
        src/ui/components/list_box.cpp
        src/ui/components/list_box.h
        src/ui/components/list_view.cpp
        src/ui/components/list_view.h
        src/ui/components/calendar.cpp
        src/ui/components/calendar.h
        src/ui/components/page.cpp
        src/ui/components/page.h
        src/ui/components/progress.cpp
        src/ui/components/progress.h
        src/ui/components/property.cpp
        src/ui/components/property.h
        src/ui/components/rebar.cpp
        src/ui/components/rebar.h
        src/ui/components/rich_edit.cpp
        src/ui/components/rich_edit.h
        src/ui/components/scroll.cpp
        src/ui/components/scroll.h
        src/ui/components/label.cpp
        src/ui/components/label.h
        src/ui/components/status.cpp
        src/ui/components/status.h
        src/ui/components/link.cpp
        src/ui/components/link.h
        src/ui/components/tab.cpp
        src/ui/components/tab.h
        src/ui/components/task_dialog.cpp
        src/ui/components/task_dialog.h
        src/ui/components/tool_bar.cpp
        src/ui/components/tool_bar.h
        src/ui/components/tool_tips.cpp
        src/ui/components/tool_tips.h
        src/ui/components/track.cpp
        src/ui/components/track.h
        src/ui/components/tree.cpp
        src/ui/components/tree.h
        src/ui/components/up_down.cpp
        src/ui/components/up_down.h
        src/ui/components/general.cpp
        src/ui/components/general.h
)

set_target_properties(YanLib PROPERTIES
        DEBUG_POSTFIX "d"
        COMPILE_DEFINITIONS_DEBUG "_DEBUG"
)

set_target_properties(YanLib PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/build/lib/x64/Debug"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/build/lib/x64/Release"
)

set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/dist")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E env PYTHONUTF8=1 python "${PROJECT_SOURCE_DIR}/scripts/export_headers.py"
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
        VERBATIM
)

target_include_directories(YanLib
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY git@github.com:google/googletest.git
        GIT_TAG v1.16.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(test)