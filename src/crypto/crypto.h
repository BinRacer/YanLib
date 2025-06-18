/* clang-format off */
/*
 * @file crypto.h
 * @date 2025-06-17
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
#ifndef CRYPTO_H
#define CRYPTO_H
#include <wincrypt.h>
#include <cstdint>
namespace YanLib::crypto {
    enum class AesPadding : uint8_t {
        PKCS7,
        ISO10126,
        ANSIX923,
    };

    enum class AesMode : uint32_t {
        CBC = CRYPT_MODE_CBC,
        ECB = CRYPT_MODE_ECB,
        // OFB = CRYPT_OFB,
        CFB = CRYPT_MODE_CFB,
        // CTS = CRYPT_CTS,
    };

    enum class RsaKeyBits : uint32_t {
        Bit384 = 0x01800000,  // 384 bits
        Bit512 = 0x02000000,  // 512 bits
        Bit768 = 0x03000000,  // 768 bits
        Bit1024 = 0x04000000, // 1024 bits
        Bit1536 = 0x06000000, // 1536 bits
        Bit2048 = 0x08000000, // 2048 bits
        Bit3072 = 0x0C000000, // 3072 bits
        Bit4096 = 0x10000000, // 4096 bits
        Bit8192 = 0x20000000, // 8192 bits
        Bit16384 = 0x40000000 // 16,384 bits
    };
} // namespace YanLib::crypto
#endif // CRYPTO_H
