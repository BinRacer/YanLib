//
// Created by forkernel on 2025/4/2.
//

#include <iostream>
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

namespace io = YanLib::io;
namespace hash = YanLib::hash;
namespace crypto = YanLib::crypto;

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
    // std::vector<unsigned char> input_vec(input.begin(), input.end());
    // std::vector<unsigned char> encode_vec = crypto::base64::encode(input_vec);
    // std::vector<unsigned char> decode_vec = crypto::base64::decode(encode_vec);
    // std::for_each(encode_vec.begin(), encode_vec.end(), [](unsigned char c) {
    //     std::cout << c;
    // });
    // std::cout << std::endl;
    // std::for_each(decode_vec.begin(), decode_vec.end(), [](unsigned char c) {
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

    std::string encode_string = crypto::base16::encode_string("Hello World!你好");
    std::string decode_string = crypto::base16::decode_string(encode_string);
    std::cout << encode_string << std::endl;
    std::cout << decode_string << std::endl;
    encode_string = crypto::base32::encode_string("Hello World!你好");
    decode_string = crypto::base32::decode_string(encode_string);
    std::cout << encode_string << std::endl;
    std::cout << decode_string << std::endl;
    encode_string = crypto::base58::encode_string("Hello World!你好");
    decode_string = crypto::base58::decode_string(encode_string);
    std::cout << encode_string << std::endl;
    std::cout << decode_string << std::endl;
    encode_string = crypto::base62::encode_string("Hello World!你好世界");
    decode_string = crypto::base62::decode_string(encode_string);
    std::cout << encode_string << std::endl;
    std::cout << decode_string << std::endl;
    encode_string = crypto::base85::encode_string("Hello World!你好世界");
    decode_string = crypto::base85::decode_string(encode_string);
    std::cout << encode_string << std::endl;
    std::cout << decode_string << std::endl;
    encode_string = crypto::base91::encode_string("Hello World!你好世界");
    decode_string = crypto::base91::decode_string(encode_string);
    std::cout << encode_string << std::endl;
    std::cout << decode_string << std::endl;
    return 0;
}
