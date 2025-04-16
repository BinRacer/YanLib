//
// Created by forkernel on 2025/4/2.
//

#include <iostream>
#include <process.h>

#include "src/io/http.h"
#include "src/io/ftp.h"
#include "src/hash/md5.h"
#include "src/hash/sha1.h"
#include "src/hash/sha256.h"
#include "src/hash/sha384.h"
#include "src/hash/sha512.h"
#include "src/io/fs.h"
#include "src/crypto/base64.h"
#include "src/crypto/base16.h"
#include "src/crypto/base32.h"
#include "src/crypto/base58.h"
#include "src/crypto/base62.h"
#include "src/crypto/base85.h"
#include "src/crypto/base91.h"
#include "src/crypto/base92.h"
#include "src/crypto/base100.h"
#include "src/crypto/uuencode.h"
#include "src/crypto/xxencode.h"
#include "src/crypto/vigenere.h"
#include "src/crypto/aes.h"
#include "src/crypto/aes192.h"
#include "src/crypto/aes256.h"
#include "src/crypto/rsa.h"
#include "src/helper/convert.h"
#include "src/mem/allocate.h"
#include "src/sys/proc.h"
#include "src/sys/security.h"

namespace io = YanLib::io;
namespace hash = YanLib::hash;
namespace crypto = YanLib::crypto;
namespace sys = YanLib::sys;

int main(int argc, const char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "Hello World!" << std::endl;
    std::cout << "你好" << std::endl;

    // io::fs fs;
    // fs.open(L"C:\\Users\\curry\\Downloads\\test.txt");
    // std::cout << fs.err_string() << std::endl;

    // auto url =
    //         L"https://download.microsoft.com/download/768f5d94-c365-4183-b55a-76d9abcebf52/KIT_BUNDLE_WDK_MEDIACREATION/wdksetup.exe";
    // auto file = L"C:\\Users\\curry\\Downloads\\wdksetup.exe";
    // auto content = io::http::read_string_to_end(url);
    // std::cout << content.size() << std::endl;
    // io::http::download(url, file);


    // auto url = L"ftp://user:123456@192.168.180.133:2222/";
    // io::ftp ftp(url);
    // ftp.url_crack();
    // ftp.open();
    // ftp.connect();
    // auto download = ftp.download(L".bashrc", L"C:\\Users\\curry\\Downloads\\bashrc2.txt");
    // auto file_download2 = ftp.open_file(L".bashrc");
    // auto download2 = ftp.download2(file_download2, L"C:\\Users\\curry\\Downloads\\bashrc.txt");
    // auto upload = ftp.upload(L"C:\\Users\\curry\\Downloads\\bashrc.txt", L"123456.txt");
    // auto upload2_hinternet = ftp.create_file(L"654321.txt");
    // auto upload2 = ftp.upload2(upload2_hinternet, L"C:\\Users\\curry\\Downloads\\bashrc.txt");
    // std::vector<std::wstring> files;
    // std::vector<std::wstring> dirs;
    // auto pwd = ftp.pwd();
    // auto ls = ftp.ls_full_path(files, dirs);
    // auto rm = ftp.rm(L"/123456.txt") && ftp.rm(L"654321.txt");
    // std::wcout << std::boolalpha << download << std::endl;
    // std::wcout << (download2 ? false : true) << std::endl;
    // std::wcout << upload << std::endl;
    // std::wcout << (upload2 ? false : true) << std::endl;
    // std::wcout << pwd << std::endl;
    // std::wcout << ls << std::endl;
    // std::wcout << rm << std::endl;


    // hash::md5 md5_file(L"C:\\Users\\curry\\Downloads\\license.dat");
    // std::cout << md5_file.hash_string() << std::endl;
    // hash::md5 md5_file2(L"C:\\Users\\curry\\Downloads\\binaryninjacore.dll");
    // std::cout << md5_file2.hash_string() << std::endl;
    // hash::md5 md5_string("123456");
    // std::cout << md5_string.hash_string() << std::endl;


    // hash::sha1 sha1_file(L"C:\\Users\\curry\\Downloads\\license.dat");
    // std::cout << sha1_file.hash_string() << std::endl;
    // hash::sha1 sha1_file2(L"C:\\Users\\curry\\Downloads\\binaryninjacore.dll");
    // std::cout << sha1_file2.hash_string() << std::endl;
    // hash::sha1 sha1_string("123456");
    // std::cout << sha1_string.hash_string() << std::endl;

    // hash::sha256 sha256_file(L"C:\\Users\\curry\\Downloads\\license.dat");
    // std::cout << sha256_file.hash_string() << std::endl;
    // hash::sha256 sha256_file2(L"C:\\Users\\curry\\Downloads\\binaryninjacore.dll");
    // std::cout << sha256_file2.hash_string() << std::endl;
    // hash::sha256 sha256_string("123456");
    // std::cout << sha256_string.hash_string() << std::endl;

    // hash::sha384 sha384_file(L"C:\\Users\\curry\\Downloads\\license.dat");
    // std::cout << sha384_file.hash_string() << std::endl;
    // hash::sha384 sha384_file2(L"C:\\Users\\curry\\Downloads\\binaryninjacore.dll");
    // std::cout << sha384_file2.hash_string() << std::endl;
    // hash::sha384 sha384_string("123456");
    // std::cout << sha384_string.hash_string() << std::endl;

    // hash::sha512 sha512_file(L"C:\\Users\\curry\\Downloads\\license.dat");
    // std::cout << sha512_file.hash_string() << std::endl;
    // hash::sha512 sha512_file2(L"C:\\Users\\curry\\Downloads\\binaryninjacore.dll");
    // std::cout << sha512_file2.hash_string() << std::endl;
    // hash::sha512 sha512_string("123456");
    // std::cout << sha512_string.hash_string() << std::endl;

    // std::string input = "Hello World!你好世界";
    // std::vector<uint8_t> input_vec(input.begin(), input.end());
    // std::vector<uint8_t> encode_vec = crypto::base64::encode(input_vec);
    // std::vector<uint8_t> decode_vec = crypto::base64::decode(encode_vec);
    // std::for_each(encode_vec.begin(), encode_vec.end(), [](uint8_t c) {
    //     std::cout << c;
    // });
    // std::cout << std::endl;
    // std::for_each(decode_vec.begin(), decode_vec.end(), [](uint8_t c) {
    //     std::cout << c;
    // });
    // std::cout << std::endl;

    // std::string encode_string = crypto::base64::encode_string("Hello World!你好世界");
    // std::string decode_string = crypto::base64::decode_string("SGVsbG8gV29ybGQh5L2g5aW95LiW55WM");
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // std::string encode_wstring = crypto::base64::encode_wstring(L"Hello World!");
    // std::string decode_wstring = crypto::base64::decode_wstring(L"SGVsbG8gV29ybGQh");
    // std::cout << encode_wstring << std::endl;
    // std::cout << decode_wstring << std::endl;

    // bool encode_file = crypto::base64::encode_file(
    //     L"C:\\Users\\curry\\Downloads\\license.dat",
    //     L"C:\\Users\\curry\\Downloads\\encode.txt"
    // );
    // bool decode_file = crypto::base64::decode_file(
    //     L"C:\\Users\\curry\\Downloads\\encode.txt",
    //     L"C:\\Users\\curry\\Downloads\\decode.txt");
    // std::cout << std::boolalpha << encode_file << std::endl;
    // std::cout << decode_file << std::endl;

    // std::string encode_string = crypto::base16::encode_string("Hello World!你好");
    // std::string decode_string = crypto::base16::decode_string(encode_string);
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // encode_string = crypto::base32::encode_string("Hello World!你好");
    // decode_string = crypto::base32::decode_string(encode_string);
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // encode_string = crypto::base58::encode_string("Hello World!你好");
    // decode_string = crypto::base58::decode_string(encode_string);
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // encode_string = crypto::base62::encode_string("Hello World!你好世界");
    // decode_string = crypto::base62::decode_string(encode_string);
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // encode_string = crypto::base85::encode_string("Hello World!你好世界");
    // decode_string = crypto::base85::decode_string(encode_string);
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // encode_string = crypto::base91::encode_string("Hello World!你好世界");
    // decode_string = crypto::base91::decode_string(encode_string);
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // encode_string = crypto::base92::encode_string("Hello World!你好世界");
    // decode_string = crypto::base92::decode_string(encode_string);
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // encode_string = crypto::base100::encode_string("the quick brown fox jumped over the lazy dog");
    // decode_string = crypto::base100::decode_string(
    //     "👫👟👜🐗👨👬👠👚👢🐗👙👩👦👮👥🐗👝👦👯🐗👡👬👤👧👜👛🐗👦👭👜👩🐗👫👟👜🐗👣👘👱👰🐗👛👦👞🐁");
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // encode_string = crypto::uuencode::encode_string("Hello World!你好世界");
    // decode_string = crypto::uuencode::decode_string(encode_string);
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // encode_string = crypto::xxencode::encode_string("Hello World!你好世界");
    // decode_string = crypto::xxencode::decode_string(encode_string);
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // encode_string = crypto::vigenere::encode_string("Hello World!你好世界", "Thisisakey");
    // decode_string = crypto::vigenere::decode_string(encode_string, "Thisisakey");
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;

    // using b16 = crypto::base16;
    // std::string data = "Hello,这是待加密的示例数据";
    // std::vector<uint8_t> data_vec(data.begin(), data.end());
    // std::string key = "1234567890abcdef";
    // std::vector<uint8_t> key_vec(key.begin(), key.end());
    // std::string iv = "1234567890abcdef";
    // std::vector<uint8_t> iv_vec(key.begin(), key.end());
    // std::cout << b16::encode_string(data) << std::endl;

    // crypto::aes encodeAES;
    // auto result = encodeAES.encode_ecb(data_vec, key_vec, crypto::AES_PADDING::PKCS7_PADDING);
    // std::cout << encodeAES.hex_string() << std::endl;
    // result = encodeAES.encode_ecb(data_vec, key_vec, crypto::AES_PADDING::ISO10126_PADDING);
    // std::cout << encodeAES.hex_string() << std::endl;
    // crypto::aes decodeAES;
    // decodeAES.decode_ecb(result, key_vec, crypto::AES_PADDING::ISO10126_PADDING);
    // std::cout << decodeAES.hex_string() << std::endl;
    // decodeAES.decode_ecb(result, key_vec, crypto::AES_PADDING::ISO10126_PADDING);
    // std::cout << decodeAES.hex_string() << std::endl;

    // std::cout << "----------------------------" << std::endl;
    // result = encodeAES.encode_cbc(data_vec, key_vec, iv_vec, crypto::AES_PADDING::PKCS7_PADDING);
    // std::cout << encodeAES.hex_string() << std::endl;
    // encodeAES.encode_cbc(data_vec, key_vec, iv_vec, crypto::AES_PADDING::ANSI_X923_PADDING);
    // std::cout << encodeAES.hex_string() << std::endl;
    // decodeAES.decode_cbc(result, key_vec, iv_vec, crypto::AES_PADDING::PKCS7_PADDING);
    // std::cout << decodeAES.hex_string() << std::endl;
    // result = encodeAES.encode_cfb(data_vec, key_vec, iv_vec, crypto::AES_PADDING::PKCS7_PADDING);
    // std::cout << encodeAES.hex_string() << std::endl;
    // encodeAES.encode_cfb(data_vec, key_vec, iv_vec, crypto::AES_PADDING::ANSI_X923_PADDING);
    // std::cout << encodeAES.hex_string() << std::endl;
    // decodeAES.decode_cfb(result, key_vec, iv_vec, crypto::AES_PADDING::PKCS7_PADDING);
    // std::cout << decodeAES.hex_string() << std::endl;


    // std::string data = "Hello World!你好世界";
    // std::vector<uint8_t> data_vec(data.begin(), data.end());
    // crypto::rsa rsa;
    // rsa.generate_key(crypto::RSA_2048BIT_KEY);
    // auto pub_key = rsa.pub_blob();
    // auto priv_key = rsa.priv_blob();
    // auto encode_data = rsa.encode_to_base64(data_vec, pub_key);
    // auto decode_data = rsa.decode(rsa.encode(data_vec, pub_key), priv_key);
    // // std::cout << rsa.pub_base64() << std::endl;
    // // std::cout << rsa.priv_base64() << std::endl;
    // std::cout << "-----------------" << std::endl;
    // std::string encode_string(encode_data.begin(), encode_data.end());
    // std::string decode_string(decode_data.begin(), decode_data.end());
    // std::cout << encode_string << std::endl;
    // std::cout << decode_string << std::endl;
    // std::cout << rsa.pub_pem() << std::endl;
    // std::cout << rsa.priv_pem() << std::endl;

    // sys::proc proc;
    // auto procs = proc.ls_procs();
    // auto threads = proc.ls_threads();
    // auto modules = proc.ls_modules(16980);
    // auto heaps = proc.ls_heaps(16980);
    // auto base = proc.get_curr_proc_image_base();
    // auto base2 = proc.get_proc_image_base(proc.curr_proc_handle());
    // auto cmdline = proc.get_proc_cmdline(nullptr);
    // auto cmdline2 = proc.get_proc_cmdline_wide(nullptr);

    // auto own = proc.get_proc_owner(nullptr);
    // auto own2 = proc.get_proc_owner_wide(nullptr);

    // sys::security security;
    // auto result1 = security.check_proc_elevation();
    // auto result2 = security.check_proc_integrity_level();
    return 0;
}
