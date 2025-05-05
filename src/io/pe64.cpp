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
            _dos_header = static_cast<IMAGE_DOS_HEADER *>(addr);
            if (_dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
                break;
            }
            _nt_headers = reinterpret_cast<IMAGE_NT_HEADERS64 *>(
                static_cast<uint8_t *>(addr) +
                _dos_header->e_lfanew);
            if (_nt_headers->Signature != IMAGE_NT_SIGNATURE) {
                break;
            }
            _section_header = reinterpret_cast<IMAGE_SECTION_HEADER *>(
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

    bool pe64::get_nt_signature(unsigned long &signature) {
        if (!mmap.read(_nt_headers,
                       reinterpret_cast<uint8_t *>(&signature),
                       sizeof(unsigned long),
                       offsetof(IMAGE_NT_HEADERS64, Signature))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    bool pe64::set_nt_signature(unsigned long &signature) {
        if (!mmap.write(_nt_headers,
                        reinterpret_cast<uint8_t *>(&signature),
                        sizeof(unsigned long),
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

    bool pe64::set_section_headers(
        std::vector<IMAGE_SECTION_HEADER> &section_headers) {
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


    std::vector<std::string> pe64::get_export_func_name_string(
        IMAGE_EXPORT_DIRECTORY *export_table) {
        if (!export_table) {
            return {};
        }
        auto start_name_addr = reinterpret_cast<unsigned long *>(
            reinterpret_cast<uint8_t *>(_dos_header) +
            rva_to_foa(export_table->AddressOfNames));
        std::vector<std::string> result;
        for (int32_t i = 0; i < export_table->NumberOfNames; i++) {
            auto name_addr = reinterpret_cast<char *>(
                                 reinterpret_cast<uint8_t *>(_dos_header)) +
                             rva_to_foa(start_name_addr[i]);
            result.push_back(name_addr);
        }
        return result;
    }

    std::vector<unsigned long> pe64::get_export_func_name(
        IMAGE_EXPORT_DIRECTORY *export_table) {
        if (!export_table) {
            return {};
        }
        std::vector<unsigned long> result(export_table->NumberOfNames, 0);
        if (!mmap.read(_dos_header,
                       reinterpret_cast<uint8_t *>(result.data()),
                       sizeof(unsigned long) * export_table->NumberOfNames,
                       rva_to_foa(export_table->AddressOfNames))) {
            error_code = mmap.err_code();
            return {};
        }
        return result;
    }

    bool pe64::set_export_func_name(IMAGE_EXPORT_DIRECTORY *export_table,
                                    std::vector<unsigned long> &func_name_addrs) {
        if (!export_table ||
            func_name_addrs.size() != export_table->NumberOfNames) {
            return false;
        }
        if (!mmap.write(_dos_header,
                        reinterpret_cast<uint8_t *>(func_name_addrs.data()),
                        sizeof(unsigned long) * export_table->NumberOfNames,
                        rva_to_foa(export_table->AddressOfNames))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    std::vector<unsigned long> pe64::get_export_func_addr(
        IMAGE_EXPORT_DIRECTORY *export_table) {
        if (!export_table) {
            return {};
        }
        std::vector<unsigned long> result(export_table->NumberOfFunctions, 0);
        if (!mmap.read(_dos_header,
                       reinterpret_cast<uint8_t *>(result.data()),
                       sizeof(unsigned long) * export_table->NumberOfFunctions,
                       rva_to_foa(export_table->AddressOfFunctions))) {
            error_code = mmap.err_code();
            return {};
        }
        return result;
    }

    bool pe64::set_export_func_addr(IMAGE_EXPORT_DIRECTORY *export_table,
                                    std::vector<unsigned long> &func_addrs) {
        if (!export_table ||
            func_addrs.size() != export_table->NumberOfFunctions) {
            return false;
        }
        if (!mmap.write(_dos_header,
                        reinterpret_cast<uint8_t *>(func_addrs.data()),
                        sizeof(unsigned long) * export_table->NumberOfFunctions,
                        rva_to_foa(export_table->AddressOfFunctions))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    std::vector<uint16_t> pe64::get_export_func_ordinal(
        IMAGE_EXPORT_DIRECTORY *export_table) {
        if (!export_table) {
            return {};
        }
        std::vector<uint16_t> result(export_table->NumberOfFunctions, 0);
        if (!mmap.read(_dos_header,
                       reinterpret_cast<uint8_t *>(result.data()),
                       sizeof(uint16_t) * export_table->NumberOfFunctions,
                       rva_to_foa(export_table->AddressOfNameOrdinals))) {
            error_code = mmap.err_code();
            return {};
        }
        return result;
    }

    bool pe64::set_export_func_ordinal(IMAGE_EXPORT_DIRECTORY *export_table,
                                       std::vector<uint16_t> &func_ordinals) {
        if (!export_table ||
            func_ordinals.size() != export_table->NumberOfFunctions) {
            return false;
        }
        if (!mmap.write(_dos_header,
                        reinterpret_cast<uint8_t *>(func_ordinals.data()),
                        sizeof(uint16_t) * export_table->NumberOfFunctions,
                        rva_to_foa(export_table->AddressOfNameOrdinals))) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    std::vector<IMAGE_IMPORT_DESCRIPTOR> pe64::get_import_table() {
        if (_data_table_list.empty()) {
            get_data_table();
        }
        if (_data_table_list[DIRECTORY_ENTRY_IMPORT].Size == 0) {
            return {};
        }
        auto rva =
                _data_table_list[DIRECTORY_ENTRY_IMPORT].VirtualAddress;
        auto offset = rva_to_foa(rva);
        if (offset == 0) {
            return {};
        }
        auto import_table = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR *>(
            reinterpret_cast<uint8_t *>(_dos_header) + offset);
        size_t count = 0;
        while (import_table->OriginalFirstThunk ||
               import_table->TimeDateStamp ||
               import_table->ForwarderChain ||
               import_table->Name ||
               import_table->FirstThunk) {
            count++;
            import_table++;
        }
        std::vector<IMAGE_IMPORT_DESCRIPTOR> result(count, {});
        if (!mmap.read(_dos_header,
                       reinterpret_cast<uint8_t *>(result.data()),
                       sizeof(IMAGE_IMPORT_DESCRIPTOR) * count,
                       offset)) {
            error_code = mmap.err_code();
            return {};
        }
        return result;
    }

    bool pe64::set_import_table(std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table) {
        if (import_table.empty()) {
            return false;
        }
        if (_data_table_list.empty()) {
            get_data_table();
        }
        if (_data_table_list[DIRECTORY_ENTRY_IMPORT].Size == 0) {
            return false;
        }
        auto rva = _data_table_list[DIRECTORY_ENTRY_IMPORT].VirtualAddress;
        auto offset = rva_to_foa(rva);
        if (offset == 0) {
            return false;
        }
        if (!mmap.write(_dos_header,
                        reinterpret_cast<uint8_t *>(import_table.data()),
                        sizeof(IMAGE_IMPORT_DESCRIPTOR) * import_table.size(),
                        offset)) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    std::vector<std::string> pe64::get_import_table_dll_name_strings(
        std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table) {
        if (import_table.empty()) {
            return {};
        }
        std::vector<std::string> result;
        for (const auto &entry: import_table) {
            auto name = reinterpret_cast<char *>(
                reinterpret_cast<uint8_t *>(_dos_header) + rva_to_foa(entry.Name));
            result.push_back(name);
        }
        return result;
    }

    std::vector<unsigned long> pe64::get_import_table_dll_name(
        std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table) {
        if (import_table.empty()) {
            return {};
        }
        std::vector<unsigned long> result;
        for (const auto &entry: import_table) {
            result.push_back(entry.Name);
        }
        return result;
    }

    bool pe64::set_import_table_dll_name(
        std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table,
        std::vector<unsigned long> &dll_names) {
        if (import_table.empty() ||
            dll_names.empty() ||
            import_table.size() != dll_names.size()) {
            return false;
        }
        for (int32_t i = 0; i < import_table.size(); i++) {
            import_table[i].Name = dll_names[i];
        }
        return set_import_table(import_table);
    }

    std::vector<unsigned long> pe64::get_import_table_first_thunk(
        std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table) {
        if (import_table.empty()) {
            return {};
        }
        std::vector<unsigned long> result;
        for (const auto &entry: import_table) {
            result.push_back(entry.FirstThunk);
        }
        return result;
    }

    bool pe64::set_import_table_first_thunk(
        std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table,
        std::vector<unsigned long> &first_thunks) {
        if (import_table.empty() ||
            first_thunks.empty() ||
            import_table.size() != first_thunks.size()) {
            return false;
        }
        for (int32_t i = 0; i < import_table.size(); i++) {
            import_table[i].FirstThunk = first_thunks[i];
        }
        return set_import_table(import_table);
    }

    std::vector<IMAGE_THUNK_DATA64> pe64::get_import_table_thunk_data(
        unsigned long &first_thunk) {
        size_t offset = rva_to_foa(first_thunk);
        if (offset == 0) {
            return {};
        }
        auto thunk_data = reinterpret_cast<IMAGE_THUNK_DATA64 *>(
            reinterpret_cast<uint8_t *>(_dos_header) + offset);
        size_t count = 0;
        while (thunk_data->u1.AddressOfData != 0) {
            count++;
            thunk_data++;
        }
        std::vector<IMAGE_THUNK_DATA64> result(count, {});
        if (!mmap.read(_dos_header,
                       reinterpret_cast<uint8_t *>(result.data()),
                       sizeof(IMAGE_THUNK_DATA64) * count,
                       offset)) {
            error_code = mmap.err_code();
            return {};
        }
        return result;
    }

    bool pe64::set_import_table_thunk_data(
        unsigned long &first_thunk,
        std::vector<IMAGE_THUNK_DATA64> &thunk_datas) {
        if (thunk_datas.empty()) {
            return false;
        }
        size_t offset = rva_to_foa(first_thunk);
        if (offset == 0) {
            return false;
        }
        if (!mmap.write(_dos_header,
                        reinterpret_cast<uint8_t *>(thunk_datas.data()),
                        sizeof(IMAGE_THUNK_DATA64) * thunk_datas.size(),
                        offset)) {
            error_code = mmap.err_code();
            return false;
        }
        return true;
    }

    std::vector<std::string> pe64::get_import_table_func_name_strings(
        std::vector<IMAGE_THUNK_DATA64> &thunk_datas) {
        if (thunk_datas.empty()) {
            return {};
        }
        std::vector<std::string> result;
        for (const auto &entry: thunk_datas) {
            if (!(entry.u1.AddressOfData & IMAGE_ORDINAL_FLAG64)) {
                auto func_name = reinterpret_cast<IMAGE_IMPORT_BY_NAME *>(
                    reinterpret_cast<uint8_t *>(_dos_header) +
                    rva_to_foa(entry.u1.AddressOfData));
                result.push_back(reinterpret_cast<char *>(&func_name->Name));
            } else {
                result.push_back({});
            }
        }
        return result;
    }

    std::vector<pe64::ImportTableFuncName> pe64::get_import_table_func_name(
        std::vector<IMAGE_THUNK_DATA64> &thunk_datas) {
        if (thunk_datas.empty()) {
            return {};
        }
        std::vector<ImportTableFuncName> result;
        for (const auto &entry: thunk_datas) {
            if (!(entry.u1.AddressOfData & IMAGE_ORDINAL_FLAG64)) {
                auto func_name = reinterpret_cast<IMAGE_IMPORT_BY_NAME *>(
                    reinterpret_cast<uint8_t *>(_dos_header) +
                    rva_to_foa(entry.u1.AddressOfData));
                ImportTableFuncName temp_func_name = {};
                temp_func_name.hint = func_name->Hint;
                temp_func_name.name.append(
                    reinterpret_cast<char *>(&func_name->Name));
                result.push_back(temp_func_name);
            } else {
                result.push_back({});
            }
        }
        return result;
    }

    bool pe64::set_import_table_func_name(
        std::vector<IMAGE_THUNK_DATA64> &thunk_datas,
        std::vector<ImportTableFuncName> &func_name) {
        if (thunk_datas.empty() ||
            func_name.empty() ||
            thunk_datas.size() != func_name.size()) {
            return false;
        }
        int32_t is_all_ordinals = 0;
        for (int32_t i = 0; i < thunk_datas.size(); i++) {
            if (!(thunk_datas[i].u1.AddressOfData & IMAGE_ORDINAL_FLAG64)) {
                auto func_name_addr = reinterpret_cast<IMAGE_IMPORT_BY_NAME *>(
                    reinterpret_cast<uint8_t *>(_dos_header) +
                    rva_to_foa(thunk_datas[i].u1.AddressOfData));
                func_name_addr->Hint = func_name[i].hint;
                auto len = strlen(reinterpret_cast<char *>(
                    &(func_name_addr->Name)));
                memset(&(func_name_addr->Name), 0, len);
                memcpy_s(&(func_name_addr->Name),
                         func_name[i].name.size(),
                         func_name[i].name.data(),
                         func_name[i].name.size());
            } else {
                is_all_ordinals = is_all_ordinals + 1;
            }
        }
        if (is_all_ordinals == thunk_datas.size()) {
            return false;
        }
        return true;
    }

    std::vector<std::pair<uint64_t, unsigned long> > pe64::get_import_table_func_ordinal(
        std::vector<IMAGE_THUNK_DATA64> &thunk_datas) {
        if (thunk_datas.empty()) {
            return {};
        }
        std::vector<std::pair<uint64_t, unsigned long> > result;
        for (const auto &entry: thunk_datas) {
            if (entry.u1.Ordinal & IMAGE_ORDINAL_FLAG64) {
                result.push_back(
                    std::make_pair(
                        entry.u1.Ordinal,
                        static_cast<unsigned long>(entry.u1.Ordinal & 0xFFFF)));
            } else {
                result.push_back(std::make_pair(0, 0));
            }
        }
        return result;
    }

    bool pe64::set_import_table_func_ordinal(
        unsigned long &first_thunk,
        std::vector<IMAGE_THUNK_DATA64> &thunk_datas,
        std::vector<std::pair<uint64_t, unsigned long> > &func_ordinals) {
        if (thunk_datas.empty() ||
            func_ordinals.empty() ||
            thunk_datas.size() != func_ordinals.size()) {
            return false;
        }
        for (int32_t i = 0; i < thunk_datas.size(); i++) {
            if (thunk_datas[i].u1.Ordinal & IMAGE_ORDINAL_FLAG64) {
                thunk_datas[i].u1.Ordinal =
                        (func_ordinals[i].first & 0xFFFFFFFFFFFF0000)
                        | func_ordinals[i].second;
            }
        }
        return set_import_table_thunk_data(first_thunk, thunk_datas);
    }

    std::vector<std::pair<unsigned long, unsigned long> > pe64::get_import_table_forwarder_chain(
        std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table) {
        if (import_table.empty()) {
            return {};
        }
        std::vector<std::pair<unsigned long, unsigned long> > result;
        for (const auto &entry: import_table) {
            result.push_back(
                std::make_pair(
                    entry.ForwarderChain,
                    entry.OriginalFirstThunk));
        }
        return result;
    }

    bool pe64::set_import_table_forwarder_chain(
        std::vector<IMAGE_IMPORT_DESCRIPTOR> &import_table,
        std::vector<std::pair<unsigned long, unsigned long> > &forwarder_chain) {
        if (import_table.empty() ||
            forwarder_chain.empty() ||
            import_table.size() != forwarder_chain.size()) {
            return false;
        }
        for (int32_t i = 0; i < import_table.size(); i++) {
            import_table[i].ForwarderChain = forwarder_chain[i].first;
            import_table[i].OriginalFirstThunk = forwarder_chain[i].second;
        }
        return set_import_table(import_table);
    }

    std::vector<std::string> pe64::get_import_table_forwarder_string(
        std::vector<std::pair<unsigned long, unsigned long> > &forwarder_chain) {
        if (forwarder_chain.empty()) {
            return {};
        }

        std::vector<std::string> result;
        for (const auto &entry: forwarder_chain) {
            size_t offset = rva_to_foa(entry.second);
            auto original_thunk_data = reinterpret_cast<IMAGE_THUNK_DATA64 *>(
                reinterpret_cast<uint8_t *>(_dos_header) + offset);
            if (entry.first != static_cast<unsigned long>(-1)) {
                auto target_thunk_data = original_thunk_data[entry.first];
                auto forwarder_string =
                        reinterpret_cast<char *>(
                            reinterpret_cast<uint8_t *>(_dos_header)) +
                        rva_to_foa(target_thunk_data.u1.ForwarderString);
                result.push_back(forwarder_string);
            } else {
                result.push_back({});
            }
        }
        return result;
    }

    std::vector<uint64_t> pe64::get_import_table_forwarder_string_addr(
        std::vector<std::pair<unsigned long, unsigned long> > &forwarder_chain) {
        if (forwarder_chain.empty()) {
            return {};
        }

        std::vector<uint64_t> result;
        for (const auto &entry: forwarder_chain) {
            size_t offset = rva_to_foa(entry.second);
            auto original_thunk_data = reinterpret_cast<IMAGE_THUNK_DATA64 *>(
                reinterpret_cast<uint8_t *>(_dos_header) + offset);
            if (entry.first != static_cast<unsigned long>(-1)) {
                auto target_thunk_data = original_thunk_data[entry.first];
                result.push_back(target_thunk_data.u1.ForwarderString);
            } else {
                result.push_back(0);
            }
        }
        return result;
    }

    bool pe64::set_import_table_forwarder_string_addr(
        std::vector<std::pair<unsigned long, unsigned long> > &forwarder_chain,
        std::vector<uint64_t> &forwarder_string_addrs) {
        if (forwarder_chain.empty() ||
            forwarder_string_addrs.empty() ||
            forwarder_chain.size() != forwarder_string_addrs.size()) {
            return false;
        }

        int32_t is_no_forward = 0;
        for (int32_t i = 0; i < forwarder_chain.size(); i++) {
            size_t offset = rva_to_foa(forwarder_chain[i].second);
            auto original_thunk_data = reinterpret_cast<IMAGE_THUNK_DATA64 *>(
                reinterpret_cast<uint8_t *>(_dos_header) + offset);
            if (forwarder_chain[i].first != static_cast<unsigned long>(-1)) {
                auto target_thunk_data =
                        original_thunk_data[forwarder_chain[i].first];
                target_thunk_data.u1.ForwarderString =
                        forwarder_string_addrs[i];
            } else {
                is_no_forward++;
            }
        }
        if (is_no_forward == forwarder_chain.size()) {
            return false;
        }
        return true;
    }

    std::vector<pe64::RelocationTable> pe64::get_relocation_table() {
        if (_data_table_list.empty()) {
            get_data_table();
        }
        if (_data_table_list[DIRECTORY_ENTRY_BASERELOC].Size == 0) {
            return {};
        }
        auto rva =
                _data_table_list[DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
        auto offset = rva_to_foa(rva);
        if (offset == 0) {
            return {};
        }
        auto relocation_table = reinterpret_cast<IMAGE_BASE_RELOCATION *>(
            reinterpret_cast<uint8_t *>(_dos_header) + offset);
        std::vector<RelocationTable> result;
        while (relocation_table->VirtualAddress) {
            RelocationTable relocation = {};
            relocation.virtual_address = relocation_table->VirtualAddress;
            relocation.size_of_block = relocation_table->SizeOfBlock;
            auto item_addr = reinterpret_cast<uint16_t *>(
                reinterpret_cast<uint8_t *>(relocation_table) +
                sizeof(IMAGE_BASE_RELOCATION));
            auto item_count =
            (relocation_table->SizeOfBlock -
             sizeof(IMAGE_BASE_RELOCATION)) / sizeof(uint16_t);

            relocation.items.resize(item_count);
            memcpy_s(relocation.items.data(),
                     sizeof(uint16_t) * item_count,
                     item_addr,
                     sizeof(uint16_t) * item_count);
            result.push_back(relocation);
            relocation_table = reinterpret_cast<IMAGE_BASE_RELOCATION *>(
                reinterpret_cast<uint8_t *>(relocation_table) +
                relocation_table->SizeOfBlock);
        }
        return result;
    }

    bool pe64::set_relocation_table(
        std::vector<RelocationTable> &relocation_table) {
        if (_data_table_list.empty()) {
            get_data_table();
        }
        if (_data_table_list[DIRECTORY_ENTRY_BASERELOC].Size == 0) {
            return false;
        }
        auto rva =
                _data_table_list[DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
        auto offset = rva_to_foa(rva);
        if (offset == 0) {
            return false;
        }
        auto table = reinterpret_cast<IMAGE_BASE_RELOCATION *>(
            reinterpret_cast<uint8_t *>(_dos_header) + offset);
        for (const auto &entry: relocation_table) {
            auto item_addr = reinterpret_cast<uint16_t *>(
                reinterpret_cast<uint8_t *>(table) +
                sizeof(IMAGE_BASE_RELOCATION));
            auto item_count = (table->SizeOfBlock -
                               sizeof(IMAGE_BASE_RELOCATION)) / sizeof(uint16_t);
            memcpy_s(item_addr,
                     sizeof(uint16_t) * item_count,
                     entry.items.data(),
                     sizeof(uint16_t) * item_count);
            table->VirtualAddress = entry.virtual_address;
            table->SizeOfBlock = entry.size_of_block;
            table = reinterpret_cast<IMAGE_BASE_RELOCATION *>(
                reinterpret_cast<uint8_t *>(table) +
                table->SizeOfBlock);
        }
        return true;
    }

    std::vector<std::tuple<uint16_t, uint16_t, unsigned long> > pe64::get_relocation_table_item(
        RelocationTable &relocation) {
        if (!relocation.virtual_address ||
            !relocation.size_of_block) {
            return {};
        }
        std::vector<std::tuple<uint16_t, uint16_t, unsigned long> > result;
        for (const auto &entry: relocation.items) {
            uint16_t type = entry >> 12;
            unsigned long real_addr = relocation.virtual_address + (entry & 0x0FFF);
            result.push_back(std::make_tuple(
                entry,
                type,
                (IMAGE_REL_BASED_DIR64 == type) ? real_addr : 0));
        }
        return result;
    }

    bool pe64::set_relocation_table_item(
        RelocationTable &relocation,
        std::vector<std::tuple<uint16_t, uint16_t, unsigned long> > &items) {
        if (!relocation.virtual_address ||
            !relocation.size_of_block ||
            relocation.items.empty() ||
            items.empty() ||
            relocation.items.size() != items.size()) {
            return false;
        }
        for (int32_t i = 0; i < relocation.items.size(); i++) {
            relocation.items[i] =
                    std::get<1>(items[i]) << 12 |
                    ((std::get<2>(items[i]) -
                      relocation.virtual_address) & 0x0FFF);
        }
        return true;
    }

    IMAGE_SECTION_HEADER pe64::find_section_header(unsigned long rva) {
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

    int64_t pe64::rva_to_foa(unsigned long rva) {
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

    unsigned long pe64::foa_to_rva(IMAGE_SECTION_HEADER &section_header,
                                   int64_t foa) {
        return foa - section_header.PointerToRawData +
               section_header.VirtualAddress;
    }

    std::string pe64::datetime(unsigned long timestamp) {
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
        uli.QuadPart += static_cast<uint64_t>(10000000) * timestamp;
        ft.dwHighDateTime = uli.HighPart;
        ft.dwLowDateTime = uli.LowPart;
        FileTimeToLocalFileTime(&ft, &ftLocal);
        FileTimeToSystemTime(&ftLocal, &st);

        std::string result(64, '\0');
        int32_t size = sprintf_s(result.data(),
                             result.size(),
                             "%04d-%02d-%02d %02d:%02d:%02d.%03d",
                             st.wYear, st.wMonth, st.wDay,
                             st.wHour, st.wMinute, st.wSecond,
                             st.wMilliseconds);
        result.resize(size);
        while (result.back() == '\0') {
            result.pop_back();
        }
        return result;
    }

    unsigned long pe64::err_code() const {
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
