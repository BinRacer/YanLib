cmake_minimum_required(VERSION 3.30)
project(YanLib)

set(CMAKE_CXX_STANDARD 20)

add_library(YanLib STATIC
        src/helper/convert.cpp
        src/helper/convert.h
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
        src/mem/mmap.cpp
        src/mem/mmap.h
        src/mem/allocate.cpp
        src/mem/allocate.h
        src/mem/heap.cpp
        src/mem/heap.h
        src/io/fs.cpp
        src/io/fs.h
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
)

# 公共头文件目录（仅暴露给外部使用者）
target_include_directories(YanLib
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# 私有头文件目录（仅内部使用）
target_include_directories(YanLib
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Lib)

add_executable(app main.cpp)

target_link_libraries(app PRIVATE YanLib)