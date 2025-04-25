//
// Created by forkernel on 2025/4/24.
//

#include "pe64.h"
#include "helper/convert.h"
#include <memory>

namespace YanLib::io {
    pe64::pe64(const wchar_t *file_name) {
        do {
            mmap_handle = mmap.create(file_name);
            if (!mmap_handle) {
                error_code = mmap.err_code();
                break;
            }
            init();
        } while (false);
    }

    pe64::pe64(HANDLE file_handle) {
        do {
            mmap_handle = mmap.create(file_handle);
            if (!mmap_handle) {
                error_code = mmap.err_code();
                break;
            }
            init();
        } while (false);
    }

    void pe64::init() {
        do {
            addr = mmap.mmap_file(mmap_handle);
            if (!addr) {
                error_code = mmap.err_code();
                break;
            }
            _dos_header = static_cast<PIMAGE_DOS_HEADER>(addr);
            if (_dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
                break;
            }
            _nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS64>(
                static_cast<uint8_t *>(addr) +
                _dos_header->e_lfanew);
            if (_nt_headers->Signature != IMAGE_NT_SIGNATURE) {
                break;
            }
            _section_header = reinterpret_cast<PIMAGE_SECTION_HEADER>(
                reinterpret_cast<uint8_t *>(_nt_headers) +
                sizeof(IMAGE_NT_HEADERS64));
            if (_nt_headers->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64 ||
                _nt_headers->FileHeader.Machine == IMAGE_FILE_MACHINE_ARM64 ||
                _nt_headers->FileHeader.Machine == IMAGE_FILE_MACHINE_IA64 ||
                _nt_headers->FileHeader.Machine == IMAGE_FILE_MACHINE_ALPHA64 ||
                _nt_headers->FileHeader.Machine == IMAGE_FILE_MACHINE_AXP64) {
                is_64bit = true;
            }
        } while (false);
    }

    bool pe64::parse() {
        if (!mmap_handle ||
            !addr ||
            !_dos_header ||
            !_nt_headers ||
            !_section_header) {
            return false;
        }
        return true;
    }

    bool pe64::is_32bits() const {
        return !is_64bit;
    }

    bool pe64::is_64bits() const {
        return is_64bit;
    }

    bool pe64::get_dos_header(IMAGE_DOS_HEADER &dos_header) {
        if (!mmap.read(_dos_header,
                       reinterpret_cast<uint8_t *>(&dos_header),
                       sizeof(IMAGE_DOS_HEADER))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::set_dos_header(IMAGE_DOS_HEADER &dos_header) {
        if (!mmap.write(_dos_header,
                        reinterpret_cast<uint8_t *>(&dos_header),
                        sizeof(IMAGE_DOS_HEADER))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::get_nt_headers(IMAGE_NT_HEADERS64 &nt_headers) {
        if (!mmap.read(_nt_headers,
                       reinterpret_cast<uint8_t *>(&nt_headers),
                       sizeof(IMAGE_NT_HEADERS64))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::set_nt_headers(IMAGE_NT_HEADERS64 &nt_headers) {
        if (!mmap.write(_nt_headers,
                        reinterpret_cast<uint8_t *>(&nt_headers),
                        sizeof(IMAGE_NT_HEADERS64))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::get_nt_signature(DWORD &signature) {
        if (!mmap.read(_nt_headers,
                       reinterpret_cast<uint8_t *>(&signature),
                       sizeof(DWORD),
                       offsetof(IMAGE_NT_HEADERS64, Signature))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::set_nt_signature(DWORD &signature) {
        if (!mmap.write(_nt_headers,
                        reinterpret_cast<uint8_t *>(&signature),
                        sizeof(DWORD),
                        offsetof(IMAGE_NT_HEADERS64, Signature))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::get_file_header(IMAGE_FILE_HEADER &file_header) {
        if (!mmap.read(_nt_headers,
                       reinterpret_cast<uint8_t *>(&file_header),
                       sizeof(IMAGE_FILE_HEADER),
                       offsetof(IMAGE_NT_HEADERS64, FileHeader))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::set_file_header(IMAGE_FILE_HEADER &file_header) {
        if (!mmap.write(_nt_headers,
                        reinterpret_cast<uint8_t *>(&file_header),
                        sizeof(IMAGE_FILE_HEADER),
                        offsetof(IMAGE_NT_HEADERS64, FileHeader))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::get_optional_header(IMAGE_OPTIONAL_HEADER64 &optional_header) {
        if (!mmap.read(_nt_headers,
                       reinterpret_cast<uint8_t *>(&optional_header),
                       sizeof(IMAGE_OPTIONAL_HEADER64),
                       offsetof(IMAGE_NT_HEADERS64, OptionalHeader))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::set_optional_header(IMAGE_OPTIONAL_HEADER64 &optional_header) {
        if (!mmap.write(_nt_headers,
                        reinterpret_cast<uint8_t *>(&optional_header),
                        sizeof(IMAGE_OPTIONAL_HEADER64),
                        offsetof(IMAGE_NT_HEADERS64, OptionalHeader))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    std::vector<IMAGE_DATA_DIRECTORY> pe64::get_data_table() {
        constexpr size_t entries = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
        _data_table_list.resize(entries);
        if (!mmap.read(_nt_headers,
                       reinterpret_cast<uint8_t *>(_data_table_list.data()),
                       sizeof(IMAGE_DATA_DIRECTORY) * entries,
                       offsetof(IMAGE_NT_HEADERS64, OptionalHeader) +
                       offsetof(IMAGE_OPTIONAL_HEADER64, DataDirectory))) {
            error_code = mmap.err_code();
            return {};
        }
        return _data_table_list;
    }

    bool pe64::set_data_table(std::vector<IMAGE_DATA_DIRECTORY> &data_table) {
        constexpr size_t entries = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
        if (data_table.size() != entries) {
            return false;
        }
        if (!mmap.write(_nt_headers,
                        reinterpret_cast<uint8_t *>(data_table.data()),
                        sizeof(IMAGE_DATA_DIRECTORY) * entries,
                        offsetof(IMAGE_NT_HEADERS64, OptionalHeader) +
                        offsetof(IMAGE_OPTIONAL_HEADER64, DataDirectory))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    std::vector<IMAGE_SECTION_HEADER> pe64::get_section_headers() {
        const size_t count = _nt_headers->FileHeader.NumberOfSections;
        _section_header_list.resize(count);
        if (!mmap.read(_section_header,
                       reinterpret_cast<uint8_t *>(
                           _section_header_list.data()),
                       sizeof(IMAGE_SECTION_HEADER) * count)) {
            error_code = mmap.err_code();
            return {};
        }
        return _section_header_list;
    }

    bool
    pe64::set_section_headers(std::vector<IMAGE_SECTION_HEADER> &section_headers) {
        const size_t count = _nt_headers->FileHeader.NumberOfSections;
        if (section_headers.size() != count) {
            return false;
        }
        if (!mmap.write(_section_header,
                        reinterpret_cast<uint8_t *>(section_headers.data()),
                        sizeof(IMAGE_SECTION_HEADER) * count)) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::get_export_table(IMAGE_EXPORT_DIRECTORY &export_table) {
        if (_data_table_list.empty()) {
            get_data_table();
        }
        if (_data_table_list[DIRECTORY_ENTRY_EXPORT].Size == 0) {
            return false;
        }
        auto rva = _data_table_list[DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        auto offset = rva_to_foa(rva);
        if (offset == 0) {
            return false;
        }
        if (!mmap.read(_dos_header,
                       reinterpret_cast<uint8_t *>(&export_table),
                       sizeof(IMAGE_EXPORT_DIRECTORY),
                       offset)) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::set_export_table(IMAGE_EXPORT_DIRECTORY &export_table) {
        if (_data_table_list.empty()) {
            get_data_table();
        }
        if (_data_table_list[DIRECTORY_ENTRY_EXPORT].Size == 0) {
            return false;
        }
        auto rva = _data_table_list[DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        auto offset = rva_to_foa(rva);
        if (offset == 0) {
            return false;
        }
        if (!mmap.write(_dos_header,
                        reinterpret_cast<uint8_t *>(&export_table),
                        sizeof(IMAGE_EXPORT_DIRECTORY),
                        offset)) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }


    std::vector<std::string>
    pe64::get_export_func_name_string(IMAGE_EXPORT_DIRECTORY *export_table) {
        if (!export_table) {
            return {};
        }
        auto start_name_addr = reinterpret_cast<PDWORD>(
            reinterpret_cast<uint8_t *>(_dos_header) +
            rva_to_foa(export_table->AddressOfNames));
        std::vector<std::string> result;
        for (int i = 0; i < export_table->NumberOfNames; i++) {
            auto name_addr = reinterpret_cast<char *>(
                                 reinterpret_cast<uint8_t *>(_dos_header)) +
                             rva_to_foa(start_name_addr[i]);
            result.push_back(name_addr);
        }
        return result;
    }

    std::vector<DWORD>
    pe64::get_export_func_name(IMAGE_EXPORT_DIRECTORY *export_table) {
        if (!export_table) {
            return {};
        }
        std::vector<DWORD> result(export_table->NumberOfNames, 0);
        if (!mmap.read(_dos_header,
                       reinterpret_cast<uint8_t *>(result.data()),
                       sizeof(DWORD) * export_table->NumberOfNames,
                       rva_to_foa(export_table->AddressOfNames))) {
            error_code = mmap.err_code();
            return {};
        }
        return result;
    }

    bool pe64::set_export_func_name(IMAGE_EXPORT_DIRECTORY *export_table,
                                    std::vector<DWORD> &func_name_addrs) {
        if (!export_table ||
            func_name_addrs.size() != export_table->NumberOfNames) {
            return false;
        }
        if (!mmap.write(_dos_header,
                        reinterpret_cast<uint8_t *>(func_name_addrs.data()),
                        sizeof(DWORD) * export_table->NumberOfNames,
                        rva_to_foa(export_table->AddressOfNames))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    std::vector<DWORD>
    pe64::get_export_func_addr(IMAGE_EXPORT_DIRECTORY *export_table) {
        if (!export_table) {
            return {};
        }
        std::vector<DWORD> result(export_table->NumberOfFunctions, 0);
        if (!mmap.read(_dos_header,
                       reinterpret_cast<uint8_t *>(result.data()),
                       sizeof(DWORD) * export_table->NumberOfFunctions,
                       rva_to_foa(export_table->AddressOfFunctions))) {
            error_code = mmap.err_code();
            return {};
        }
        return result;
    }

    bool pe64::set_export_func_addr(IMAGE_EXPORT_DIRECTORY *export_table,
                                    std::vector<DWORD> &func_addrs) {
        if (!export_table ||
            func_addrs.size() != export_table->NumberOfFunctions) {
            return false;
        }
        if (!mmap.write(_dos_header,
                        reinterpret_cast<uint8_t *>(func_addrs.data()),
                        sizeof(DWORD) * export_table->NumberOfFunctions,
                        rva_to_foa(export_table->AddressOfFunctions))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    std::vector<WORD>
    pe64::get_export_func_ordinal(IMAGE_EXPORT_DIRECTORY *export_table) {
        if (!export_table) {
            return {};
        }
        std::vector<WORD> result(export_table->NumberOfFunctions, 0);
        if (!mmap.read(_dos_header,
                       reinterpret_cast<uint8_t *>(result.data()),
                       sizeof(WORD) * export_table->NumberOfFunctions,
                       rva_to_foa(export_table->AddressOfNameOrdinals))) {
            error_code = mmap.err_code();
            return {};
        }
        return result;
    }

    bool pe64::set_export_func_ordinal(IMAGE_EXPORT_DIRECTORY *export_table,
                                       std::vector<WORD> &func_ordinals) {
        if (!export_table ||
            func_ordinals.size() != export_table->NumberOfFunctions) {
            return false;
        }
        if (!mmap.write(_dos_header,
                        reinterpret_cast<uint8_t *>(func_ordinals.data()),
                        sizeof(WORD) * export_table->NumberOfFunctions,
                        rva_to_foa(export_table->AddressOfNameOrdinals))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    IMAGE_SECTION_HEADER pe64::find_section_header(DWORD rva) {
        IMAGE_SECTION_HEADER result = {};
        if (_section_header_list.empty()) {
            get_section_headers();
        }
        for (const auto &section: _section_header_list) {
            if (rva >= section.VirtualAddress &&
                rva <= section.VirtualAddress + section.SizeOfRawData) {
                memcpy_s(&result,
                         sizeof(IMAGE_SECTION_HEADER),
                         &section,
                         sizeof(IMAGE_SECTION_HEADER));
                break;
            }
        }
        return result;
    }

    int64_t pe64::rva_to_foa(DWORD rva) {
        int64_t result = 0;
        if (_section_header_list.empty()) {
            get_section_headers();
        }
        for (const auto &section: _section_header_list) {
            if (rva >= section.VirtualAddress &&
                rva <= section.VirtualAddress + section.SizeOfRawData) {
                result = rva - section.VirtualAddress;
                result += section.PointerToRawData;
                break;
            }
        }
        return result;
    }

    std::string pe64::datetime(DWORD timestamp) {
        FILETIME ft, ftLocal;
        SYSTEMTIME st;
        ULARGE_INTEGER uli;
        st.wYear = 1970;
        st.wMonth = 1;
        st.wDay = 1;
        st.wHour = 0;
        st.wMinute = 0;
        st.wSecond = 0;
        st.wMilliseconds = 0;
        SystemTimeToFileTime(&st, &ft);
        uli.HighPart = ft.dwHighDateTime;
        uli.LowPart = ft.dwLowDateTime;
        uli.QuadPart += static_cast<ULONGLONG>(10000000) * timestamp;
        ft.dwHighDateTime = uli.HighPart;
        ft.dwLowDateTime = uli.LowPart;
        FileTimeToLocalFileTime(&ft, &ftLocal);
        FileTimeToSystemTime(&ftLocal, &st);

        std::string result(64, '\0');
        int size = sprintf_s(result.data(),
                             result.size(),
                             "%04d-%02d-%02d %02d:%02d:%02d.%03d",
                             st.wYear, st.wMonth, st.wDay,
                             st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        result.resize(size);
        while (result.back() == '\0') {
            result.pop_back();
        }
        return result;
    }

    DWORD pe64::err_code() const {
        return error_code;
    }

    std::string pe64::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring pe64::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
