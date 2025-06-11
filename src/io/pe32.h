/* clang-format off */
/*
 * @file pe32.h
 * @date 2025-04-27
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
        IMAGE_DOS_HEADER *_dos_header = nullptr;
        IMAGE_NT_HEADERS32 *_nt_headers = nullptr;
        IMAGE_SECTION_HEADER *_section_header = nullptr;
        std::vector<IMAGE_DATA_DIRECTORY> _data_table_list = {};
        std::vector<IMAGE_SECTION_HEADER> _section_header_list = {};
        std::vector<std::string> _export_func_name = {};
        std::vector<uint32_t> _export_func_addr = {};
        std::vector<uint16_t> _export_func_ordinal = {};
        uint32_t error_code = 0;
        volatile bool is_64bit = false;

        enum DataDirectoryEntry {
            DIRECTORY_ENTRY_EXPORT = 0,
            DIRECTORY_ENTRY_IMPORT = 1,
            DIRECTORY_ENTRY_RESOURCE = 2,
            DIRECTORY_ENTRY_EXCEPTION = 3,
            DIRECTORY_ENTRY_SECURITY = 4,
            DIRECTORY_ENTRY_BASE_RELOC = 5,
            DIRECTORY_ENTRY_DEBUG = 6,
            DIRECTORY_ENTRY_COPYRIGHT = 7,
            DIRECTORY_ENTRY_ARCHITECTURE = 7,
            DIRECTORY_ENTRY_GLOBAL_PTR = 8,
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

        explicit pe32(const char *file_name);

        explicit pe32(const wchar_t *file_name);

        explicit pe32(HANDLE file_handle);

        ~pe32() = default;

        [[nodiscard]] bool parse() const;

        [[nodiscard]] bool is_32bits() const;

        [[nodiscard]] bool is_64bits() const;

        bool get_dos_header(IMAGE_DOS_HEADER &dos_header);

        bool set_dos_header(IMAGE_DOS_HEADER &dos_header);

        bool get_nt_headers(IMAGE_NT_HEADERS32 &nt_headers);

        bool set_nt_headers(IMAGE_NT_HEADERS32 &nt_headers);

        bool get_nt_signature(uint32_t &signature);

        bool set_nt_signature(uint32_t &signature);

        bool get_file_header(IMAGE_FILE_HEADER &file_header);

        bool set_file_header(IMAGE_FILE_HEADER &file_header);

        bool get_optional_header(IMAGE_OPTIONAL_HEADER32 &optional_header);

        bool set_optional_header(IMAGE_OPTIONAL_HEADER32 &optional_header);

        std::vector<IMAGE_DATA_DIRECTORY> get_data_table();

        bool set_data_table(std::vector<IMAGE_DATA_DIRECTORY> &data_table);

        std::vector<IMAGE_SECTION_HEADER> get_section_headers();

        bool
        set_section_headers(std::vector<IMAGE_SECTION_HEADER> &section_headers);

        bool get_export_table(IMAGE_EXPORT_DIRECTORY &export_table);

        bool set_export_table(IMAGE_EXPORT_DIRECTORY &export_table);

        std::vector<std::string>
        get_export_func_name_string(const IMAGE_EXPORT_DIRECTORY *export_table);

        std::vector<uint32_t>
        get_export_func_name(const IMAGE_EXPORT_DIRECTORY *export_table);

        bool set_export_func_name(const IMAGE_EXPORT_DIRECTORY *export_table,
                                  std::vector<uint32_t> &func_name_addrs);

        std::vector<uint32_t>
        get_export_func_addr(const IMAGE_EXPORT_DIRECTORY *export_table);

        bool set_export_func_addr(const IMAGE_EXPORT_DIRECTORY *export_table,
                                  std::vector<uint32_t> &func_addrs);

        std::vector<uint16_t>
        get_export_func_ordinal(const IMAGE_EXPORT_DIRECTORY *export_table);

        bool set_export_func_ordinal(const IMAGE_EXPORT_DIRECTORY *export_table,
                                     std::vector<uint16_t> &func_ordinals);

        std::vector<IMAGE_IMPORT_DESCRIPTOR> get_import_table();

        bool
        set_import_table(std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table);

        std::vector<std::string> get_import_table_dll_name_strings(
                const std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table);

        std::vector<uint32_t> get_import_table_dll_name(
                const std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table);

        bool set_import_table_dll_name(
                std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table,
                const std::vector<uint32_t> &dll_names);

        std::vector<uint32_t> get_import_table_first_thunk(
                const std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table);

        bool set_import_table_first_thunk(
                std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table,
                const std::vector<uint32_t> &first_thunks);

        std::vector<IMAGE_THUNK_DATA32>
        get_import_table_thunk_data(const uint32_t &first_thunk);

        bool set_import_table_thunk_data(
                const uint32_t &first_thunk,
                std::vector<IMAGE_THUNK_DATA32> &thunk_datas);

        std::vector<std::string> get_import_table_func_name_strings(
                const std::vector<IMAGE_THUNK_DATA32> &thunk_datas);

        struct ImportTableFuncName {
            uint16_t hint;
            std::string name;
        };

        std::vector<ImportTableFuncName> get_import_table_func_name(
                const std::vector<IMAGE_THUNK_DATA32> &thunk_datas);

        bool set_import_table_func_name(
                const std::vector<IMAGE_THUNK_DATA32> &thunk_datas,
                const std::vector<ImportTableFuncName> &func_name);

        std::vector<std::pair<uint64_t, uint32_t>>
        get_import_table_func_ordinal(
                const std::vector<IMAGE_THUNK_DATA32> &thunk_datas);

        bool set_import_table_func_ordinal(
                const uint32_t &first_thunk,
                std::vector<IMAGE_THUNK_DATA32> &thunk_datas,
                const std::vector<std::pair<uint64_t, uint32_t>>
                        &func_ordinals);

        // std::pair<ForwarderChain,OriginalFirstThunk>
        std::vector<std::pair<uint32_t, uint32_t>>
        get_import_table_forwarder_chain(
                const std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table);

        // std::pair<ForwarderChain,OriginalFirstThunk>
        bool set_import_table_forwarder_chain(
                std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table,
                const std::vector<std::pair<uint32_t, uint32_t>>
                        &forwarder_chain);

        std::vector<std::string> get_import_table_forwarder_string(
                const std::vector<std::pair<uint32_t, uint32_t>>
                        &forwarder_chain);

        std::vector<uint64_t> get_import_table_forwarder_string_addr(
                const std::vector<std::pair<uint32_t, uint32_t>>
                        &forwarder_chain);

        bool set_import_table_forwarder_string_addr(
                const std::vector<std::pair<uint32_t, uint32_t>>
                        &forwarder_chain,
                const std::vector<uint64_t> &forwarder_string_addrs);

        struct RelocationTable {
            uint32_t virtual_address;
            uint32_t size_of_block;
            std::vector<uint16_t> items;
        };

        std::vector<RelocationTable> get_relocation_table();

        bool set_relocation_table(
                const std::vector<RelocationTable> &relocation_table);

        // std::tuple<raw item value, item type, real offset>
        std::vector<std::tuple<uint16_t, uint16_t, uint32_t>>
        get_relocation_table_item(const RelocationTable &relocation);

        bool set_relocation_table_item(
                RelocationTable &relocation,
                const std::vector<std::tuple<uint16_t, uint16_t, uint32_t>>
                        &items);

        IMAGE_SECTION_HEADER find_section_header(uint32_t rva);

        // relative virtual address to file offset address
        int64_t rva_to_foa(uint32_t rva);

        uint32_t foa_to_rva(const IMAGE_SECTION_HEADER &section_header,
                            int64_t foa);

        std::string datetime(uint32_t timestamp);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::io
#endif // PE32_H
