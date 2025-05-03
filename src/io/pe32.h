//
// Created by forkernel on 2025/4/27.
//

#ifndef PE32_H
#define PE32_H
#include <Windows.h>
#include <string>
#include "mem/mmap.h"

namespace YanLib::io {
    class pe32 {
    private:
        mem::mmap mmap = {};
        HANDLE mmap_handle = nullptr;
        void *addr = nullptr;
        PIMAGE_DOS_HEADER _dos_header = nullptr;
        PIMAGE_NT_HEADERS32 _nt_headers = nullptr;
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
        pe32(const pe32 &other) = delete;

        pe32(pe32 &&other) = delete;

        pe32 &operator=(const pe32 &other) = delete;

        pe32 &operator=(pe32 &&other) = delete;

        pe32() = delete;

        explicit pe32(const wchar_t *file_name);

        explicit pe32(HANDLE file_handle);

        ~pe32() = default;

        bool parse();

        bool is_32bits() const;

        bool is_64bits() const;

        bool get_dos_header(IMAGE_DOS_HEADER &dos_header);

        bool set_dos_header(IMAGE_DOS_HEADER &dos_header);

        bool get_nt_headers(IMAGE_NT_HEADERS32 &nt_headers);

        bool set_nt_headers(IMAGE_NT_HEADERS32 &nt_headers);

        bool get_nt_signature(DWORD &signature);

        bool set_nt_signature(DWORD &signature);

        bool get_file_header(IMAGE_FILE_HEADER &file_header);

        bool set_file_header(IMAGE_FILE_HEADER &file_header);

        bool get_optional_header(IMAGE_OPTIONAL_HEADER32 &optional_header);

        bool set_optional_header(IMAGE_OPTIONAL_HEADER32 &optional_header);

        std::vector<IMAGE_DATA_DIRECTORY> get_data_table();

        bool set_data_table(std::vector<IMAGE_DATA_DIRECTORY> &data_table);

        std::vector<IMAGE_SECTION_HEADER> get_section_headers();

        bool set_section_headers(std::vector<IMAGE_SECTION_HEADER> &section_headers);

        bool get_export_table(IMAGE_EXPORT_DIRECTORY &export_table);

        bool set_export_table(IMAGE_EXPORT_DIRECTORY &export_table);

        std::vector<std::string> get_export_func_name_string(
            IMAGE_EXPORT_DIRECTORY *export_table);

        std::vector<DWORD> get_export_func_name(
            IMAGE_EXPORT_DIRECTORY *export_table);

        bool set_export_func_name(IMAGE_EXPORT_DIRECTORY *export_table,
                                  std::vector<DWORD> &func_name_addrs);

        std::vector<DWORD> get_export_func_addr(
            IMAGE_EXPORT_DIRECTORY *export_table);

        bool set_export_func_addr(IMAGE_EXPORT_DIRECTORY *export_table,
                                  std::vector<DWORD> &func_addrs);

        std::vector<WORD> get_export_func_ordinal(
            IMAGE_EXPORT_DIRECTORY *export_table);

        bool set_export_func_ordinal(IMAGE_EXPORT_DIRECTORY *export_table,
                                     std::vector<WORD> &func_ordinals);

        std::vector<IMAGE_IMPORT_DESCRIPTOR> get_import_table();

        bool set_import_table(std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table);

        std::vector<std::string> get_import_table_dll_name_strings(
            std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table);

        std::vector<DWORD> get_import_table_dll_name(
            std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table);

        bool set_import_table_dll_name(
            std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table,
            std::vector<DWORD> &dll_names);

        std::vector<DWORD> get_import_table_first_thunk(
            std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table);

        bool set_import_table_first_thunk(
            std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table,
            std::vector<DWORD> &first_thunks);

        std::vector<IMAGE_THUNK_DATA32> get_import_table_thunk_data(
            DWORD &first_thunk);

        bool set_import_table_thunk_data(
            DWORD &first_thunk,
            std::vector<IMAGE_THUNK_DATA32> &thunk_datas);

        std::vector<std::string> get_import_table_func_name_strings(
            std::vector<IMAGE_THUNK_DATA32> &thunk_datas);

        struct ImportTableFuncName {
            WORD hint;
            std::string name;
        };

        std::vector<ImportTableFuncName> get_import_table_func_name(
            std::vector<IMAGE_THUNK_DATA32> &thunk_datas);

        bool set_import_table_func_name(
            std::vector<IMAGE_THUNK_DATA32> &thunk_datas,
            std::vector<ImportTableFuncName> &func_name);

        std::vector<std::pair<ULONGLONG, DWORD> > get_import_table_func_ordinal(
            std::vector<IMAGE_THUNK_DATA32> &thunk_datas);

        bool set_import_table_func_ordinal(
            DWORD &first_thunk,
            std::vector<IMAGE_THUNK_DATA32> &thunk_datas,
            std::vector<std::pair<ULONGLONG, DWORD> > &func_ordinals);

        // std::pair<ForwarderChain,OriginalFirstThunk>
        std::vector<std::pair<DWORD, DWORD> > get_import_table_forwarder_chain(
            std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table);

        // std::pair<ForwarderChain,OriginalFirstThunk>
        bool set_import_table_forwarder_chain(
            std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table,
            std::vector<std::pair<DWORD, DWORD> > &forwarder_chain);

        std::vector<std::string> get_import_table_forwarder_string(
            std::vector<std::pair<DWORD, DWORD> > &forwarder_chain);

        std::vector<ULONGLONG> get_import_table_forwarder_string_addr(
            std::vector<std::pair<DWORD, DWORD> > &forwarder_chain);

        bool set_import_table_forwarder_string_addr(
            std::vector<std::pair<DWORD, DWORD> > &forwarder_chain,
            std::vector<ULONGLONG> &forwarder_string_addrs);

        struct RelocationTable {
            DWORD virtual_address;
            DWORD size_of_block;
            std::vector<WORD> items;
        };

        std::vector<RelocationTable> get_relocation_table();

        bool set_relocation_table(
            std::vector<RelocationTable> &relocation_table);

        // std::tuple<raw item value, item type, real offset>
        std::vector<std::tuple<WORD, WORD, DWORD> > get_relocation_table_item(
            RelocationTable &relocation);

        bool set_relocation_table_item(
            RelocationTable &relocation,
            std::vector<std::tuple<WORD, WORD, DWORD> > &items);

        IMAGE_SECTION_HEADER find_section_header(DWORD rva);

        // relative virtual address to file offset address
        int64_t rva_to_foa(DWORD rva);

        DWORD foa_to_rva(IMAGE_SECTION_HEADER &section_header, int64_t foa);

        std::string datetime(DWORD timestamp);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //PE32_H
