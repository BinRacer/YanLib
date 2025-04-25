//
// Created by forkernel on 2025/4/24.
//

#ifndef PE64_H
#define PE64_H
#include <Windows.h>
#include <string>
#include "mem/mmap.h"

namespace YanLib::io {
    class pe64 {
    private:
        mem::mmap mmap = {};
        HANDLE mmap_handle = nullptr;
        void *addr = nullptr;
        PIMAGE_DOS_HEADER _dos_header = nullptr;
        PIMAGE_NT_HEADERS64 _nt_headers = nullptr;
        PIMAGE_SECTION_HEADER _section_header = nullptr;
        std::vector<IMAGE_DATA_DIRECTORY> _data_table_list = {};
        std::vector<IMAGE_SECTION_HEADER> _section_header_list = {};
        std::vector<std::string> _export_func_name = {};
        std::vector<DWORD> _export_func_addr = {};
        std::vector<WORD> _export_func_ordinal = {};
        DWORD error_code = 0;
        volatile bool is_64bit = false;

        enum DataDirectoryEntry {
            DIRECTORY_ENTRY_EXPORT = 0,
            DIRECTORY_ENTRY_IMPORT = 1,
            DIRECTORY_ENTRY_RESOURCE = 2,
            DIRECTORY_ENTRY_EXCEPTION = 3,
            DIRECTORY_ENTRY_SECURITY = 4,
            DIRECTORY_ENTRY_BASERELOC = 5,
            DIRECTORY_ENTRY_DEBUG = 6,
            DIRECTORY_ENTRY_COPYRIGHT = 7,
            DIRECTORY_ENTRY_ARCHITECTURE = 7,
            DIRECTORY_ENTRY_GLOBALPTR = 8,
            DIRECTORY_ENTRY_TLS = 9,
            DIRECTORY_ENTRY_LOAD_CONFIG = 10,
            DIRECTORY_ENTRY_BOUND_IMPORT = 11,
            DIRECTORY_ENTRY_IAT = 12,
            DIRECTORY_ENTRY_DELAY_IMPORT = 13,
            DIRECTORY_ENTRY_COM_DESCRIPTOR = 14
        };

        void init();

    public:
        pe64(const pe64 &other) = delete;

        pe64(pe64 &&other) = delete;

        pe64 &operator=(const pe64 &other) = delete;

        pe64 &operator=(pe64 &&other) = delete;

        pe64() = delete;

        explicit pe64(const wchar_t *file_name);

        explicit pe64(HANDLE file_handle);

        ~pe64() = default;

        bool parse();

        bool is_32bits() const;

        bool is_64bits() const;

        bool get_dos_header(IMAGE_DOS_HEADER &dos_header);

        bool set_dos_header(IMAGE_DOS_HEADER &dos_header);

        bool get_nt_headers(IMAGE_NT_HEADERS64 &nt_headers);

        bool set_nt_headers(IMAGE_NT_HEADERS64 &nt_headers);

        bool get_nt_signature(DWORD &signature);

        bool set_nt_signature(DWORD &signature);

        bool get_file_header(IMAGE_FILE_HEADER &file_header);

        bool set_file_header(IMAGE_FILE_HEADER &file_header);

        bool get_optional_header(IMAGE_OPTIONAL_HEADER64 &optional_header);

        bool set_optional_header(IMAGE_OPTIONAL_HEADER64 &optional_header);

        std::vector<IMAGE_DATA_DIRECTORY> get_data_table();

        bool set_data_table(std::vector<IMAGE_DATA_DIRECTORY> &data_table);

        std::vector<IMAGE_SECTION_HEADER> get_section_headers();

        bool
        set_section_headers(std::vector<IMAGE_SECTION_HEADER> &section_headers);

        bool get_export_table(IMAGE_EXPORT_DIRECTORY &export_table);

        bool set_export_table(IMAGE_EXPORT_DIRECTORY &export_table);

        std::vector<std::string>
        get_export_func_name_string(IMAGE_EXPORT_DIRECTORY *export_table);

        std::vector<DWORD>
        get_export_func_name(IMAGE_EXPORT_DIRECTORY *export_table);

        bool set_export_func_name(IMAGE_EXPORT_DIRECTORY *export_table,
                                  std::vector<DWORD> &func_name_addrs);

        std::vector<DWORD>
        get_export_func_addr(IMAGE_EXPORT_DIRECTORY *export_table);

        bool set_export_func_addr(IMAGE_EXPORT_DIRECTORY *export_table,
                                  std::vector<DWORD> &func_addrs);

        std::vector<WORD>
        get_export_func_ordinal(IMAGE_EXPORT_DIRECTORY *export_table);

        bool set_export_func_ordinal(IMAGE_EXPORT_DIRECTORY *export_table,
                                     std::vector<WORD> &func_ordinals);

        IMAGE_SECTION_HEADER find_section_header(DWORD rva);

        // relative virtual address to file offset address
        int64_t rva_to_foa(DWORD rva);

        std::string datetime(DWORD timestamp);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //PE64_H
