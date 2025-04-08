//
// Created by forkernel on 2025/4/2.
//

#include <iostream>
// #include "io/fs.h"
#include "io/http.h"
#include "io/ftp.h"
#include "crypto/md5.h"
#include "crypto/sha1.h"
#include "crypto/sha256.h"
#include "crypto/sha384.h"
#include "crypto/sha512.h"

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


    YanLib::crypto::md5 md5_file(L"C:\\Users\\curry\\Downloads\\license.dat");
    std::cout << md5_file.hash_string() << std::endl;
    YanLib::crypto::md5 md5_file2(L"C:\\Users\\curry\\Downloads\\binaryninjacore.dll");
    std::cout << md5_file2.hash_string() << std::endl;
    YanLib::crypto::md5 md5_string("123456");
    std::cout << md5_string.hash_string() << std::endl;


    // crypto::sha1 sha1_file(L"C:\\Users\\curry\\Downloads\\license.dat");
    // std::cout << sha1_file.hash_string() << std::endl;
    // crypto::sha1 sha1_file2(L"C:\\Users\\curry\\Downloads\\binaryninjacore.dll");
    // std::cout << sha1_file2.hash_string() << std::endl;
    // crypto::sha1 sha1_string("123456");
    // std::cout << sha1_string.hash_string() << std::endl;

    // crypto::sha256 sha256_file(L"C:\\Users\\curry\\Downloads\\license.dat");
    // std::cout << sha256_file.hash_string() << std::endl;
    // crypto::sha256 sha256_file2(L"C:\\Users\\curry\\Downloads\\binaryninjacore.dll");
    // std::cout << sha256_file2.hash_string() << std::endl;
    // crypto::sha256 sha256_string("123456");
    // std::cout << sha256_string.hash_string() << std::endl;

    // crypto::sha384 sha384_file(L"C:\\Users\\curry\\Downloads\\license.dat");
    // std::cout << sha384_file.hash_string() << std::endl;
    // crypto::sha384 sha384_file2(L"C:\\Users\\curry\\Downloads\\binaryninjacore.dll");
    // std::cout << sha384_file2.hash_string() << std::endl;
    // crypto::sha384 sha384_string("123456");
    // std::cout << sha384_string.hash_string() << std::endl;

    // crypto::sha512 sha512_file(L"C:\\Users\\curry\\Downloads\\license.dat");
    // std::cout << sha512_file.hash_string() << std::endl;
    // crypto::sha512 sha512_file2(L"C:\\Users\\curry\\Downloads\\binaryninjacore.dll");
    // std::cout << sha512_file2.hash_string() << std::endl;
    // crypto::sha512 sha512_string("123456");
    // std::cout << sha512_string.hash_string() << std::endl;
    return 0;
}
