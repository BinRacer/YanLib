#include <gtest/gtest.h>
#include "io/pe64.h"
namespace io = YanLib::io;

class io_pe64 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    const wchar_t *zlib = L"..\\..\\test\\testdata\\zlibd1_64.dll";
};

TEST_F(io_pe64, pre_check) {
    io::pe64 pe64(zlib);
    EXPECT_TRUE(pe64.parse());
    EXPECT_TRUE(!pe64.is_32bits());
    EXPECT_TRUE(pe64.is_64bits());
}

TEST_F(io_pe64, dos_header_check) {
    io::pe64 pe64(zlib);
    auto     dos_header = std::make_unique<IMAGE_DOS_HEADER>();
    EXPECT_TRUE(pe64.get_dos_header(*dos_header));
    EXPECT_TRUE(dos_header->e_magic == IMAGE_DOS_SIGNATURE);

    dos_header->e_magic = IMAGE_NT_SIGNATURE;
    EXPECT_TRUE(pe64.set_dos_header(*dos_header));
    dos_header->e_magic = IMAGE_DOS_SIGNATURE;
    EXPECT_TRUE(pe64.set_dos_header(*dos_header));
}

TEST_F(io_pe64, nt_headers_check) {
    io::pe64 pe64(zlib);
    auto     nt_header = std::make_unique<IMAGE_NT_HEADERS64>();
    EXPECT_TRUE(pe64.get_nt_headers(*nt_header));
    EXPECT_TRUE(nt_header->Signature == IMAGE_NT_SIGNATURE);

    nt_header->Signature = IMAGE_DOS_SIGNATURE;
    EXPECT_TRUE(pe64.set_nt_headers(*nt_header));
    nt_header->Signature = IMAGE_NT_SIGNATURE;
    EXPECT_TRUE(pe64.set_nt_headers(*nt_header));

    uint32_t signature = 0;
    EXPECT_TRUE(pe64.get_nt_signature(signature));
    EXPECT_EQ(nt_header->Signature, signature);
    signature = 1234;
    EXPECT_TRUE(pe64.set_nt_signature(signature));
    signature = nt_header->Signature;
    EXPECT_TRUE(pe64.set_nt_signature(signature));
}

TEST_F(io_pe64, file_header_check) {
    io::pe64 pe64(zlib);
    auto     file_header = std::make_unique<IMAGE_FILE_HEADER>();
    EXPECT_TRUE(pe64.get_file_header(*file_header));
    EXPECT_EQ(file_header->Machine, IMAGE_FILE_MACHINE_AMD64);

    file_header->Machine = IMAGE_FILE_MACHINE_ARM64;
    EXPECT_TRUE(pe64.set_file_header(*file_header));
    file_header->Machine = IMAGE_FILE_MACHINE_AMD64;
    EXPECT_TRUE(pe64.set_file_header(*file_header));
}

TEST_F(io_pe64, optional_header_check) {
    io::pe64 pe64(zlib);
    auto     optional_header = std::make_unique<IMAGE_OPTIONAL_HEADER64>();
    EXPECT_TRUE(pe64.get_optional_header(*optional_header));
    EXPECT_EQ(optional_header->Magic, IMAGE_NT_OPTIONAL_HDR64_MAGIC);

    optional_header->Magic = IMAGE_NT_OPTIONAL_HDR32_MAGIC;
    EXPECT_TRUE(pe64.set_optional_header(*optional_header));
    optional_header->Magic = IMAGE_NT_OPTIONAL_HDR64_MAGIC;
    EXPECT_TRUE(pe64.set_optional_header(*optional_header));
}

TEST_F(io_pe64, data_table_check) {
    io::pe64 pe64(zlib);
    auto     data_table = pe64.get_data_table();
    EXPECT_EQ(data_table.size(), IMAGE_NUMBEROF_DIRECTORY_ENTRIES);

    auto export_table_backup = data_table[IMAGE_DIRECTORY_ENTRY_EXPORT];
    data_table[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress = 0;
    data_table[IMAGE_DIRECTORY_ENTRY_EXPORT].Size           = 0;
    EXPECT_TRUE(pe64.set_data_table(data_table));

    data_table[IMAGE_DIRECTORY_ENTRY_EXPORT] = export_table_backup;
    EXPECT_TRUE(pe64.set_data_table(data_table));
}

TEST_F(io_pe64, section_headers_check) {
    io::pe64 pe64(zlib);
    auto     section_headers = pe64.get_section_headers();
    EXPECT_GT(section_headers.size(), 0);

    char text_section_backup[IMAGE_SIZEOF_SHORT_NAME] = {};
    memcpy_s(text_section_backup, IMAGE_SIZEOF_SHORT_NAME,
        section_headers[0].Name, IMAGE_SIZEOF_SHORT_NAME);

    const char haha[IMAGE_SIZEOF_SHORT_NAME] = ".haha";
    memcpy_s(&section_headers[0].Name, IMAGE_SIZEOF_SHORT_NAME, haha,
        IMAGE_SIZEOF_SHORT_NAME);
    EXPECT_TRUE(pe64.set_section_headers(section_headers));

    memcpy_s(&section_headers[0].Name, IMAGE_SIZEOF_SHORT_NAME,
        text_section_backup, IMAGE_SIZEOF_SHORT_NAME);
    EXPECT_TRUE(pe64.set_section_headers(section_headers));
}

TEST_F(io_pe64, export_table_check) {
    io::pe64 pe64(zlib);
    auto     export_table_ptr = std::make_unique<IMAGE_EXPORT_DIRECTORY>();
    EXPECT_TRUE(pe64.get_export_table(*export_table_ptr));

    auto address_of_functions            = export_table_ptr->AddressOfFunctions;
    export_table_ptr->AddressOfFunctions = 0;
    EXPECT_TRUE(pe64.set_export_table(*export_table_ptr));
    export_table_ptr->AddressOfFunctions = address_of_functions;
    EXPECT_TRUE(pe64.set_export_table(*export_table_ptr));
}

TEST_F(io_pe64, export_func_name_check) {
    io::pe64 pe64(zlib);
    auto     export_table_ptr = std::make_unique<IMAGE_EXPORT_DIRECTORY>();
    EXPECT_TRUE(pe64.get_export_table(*export_table_ptr));

    auto func_name_addrs = pe64.get_export_func_name(export_table_ptr.get());
    EXPECT_EQ(func_name_addrs.size(), export_table_ptr->NumberOfNames);
    auto func_name_addrs_backup = func_name_addrs[0];
    func_name_addrs[0]          = 1234;
    EXPECT_TRUE(
        pe64.set_export_func_name(export_table_ptr.get(), func_name_addrs));
    func_name_addrs[0] = func_name_addrs_backup;
    EXPECT_TRUE(
        pe64.set_export_func_name(export_table_ptr.get(), func_name_addrs));

    auto func_name_strings =
        pe64.get_export_func_name_string(export_table_ptr.get());
    EXPECT_EQ(func_name_strings.size(), export_table_ptr->NumberOfNames);
}

TEST_F(io_pe64, export_func_addr_check) {
    io::pe64 pe64(zlib);
    auto     export_table_ptr = std::make_unique<IMAGE_EXPORT_DIRECTORY>();
    EXPECT_TRUE(pe64.get_export_table(*export_table_ptr));

    auto func_addrs = pe64.get_export_func_addr(export_table_ptr.get());
    EXPECT_EQ(func_addrs.size(), export_table_ptr->NumberOfFunctions);
    auto func_addrs_backup = func_addrs[0];
    func_addrs[0]          = 1234;
    EXPECT_TRUE(pe64.set_export_func_addr(export_table_ptr.get(), func_addrs));
    func_addrs[0] = func_addrs_backup;
    EXPECT_TRUE(pe64.set_export_func_addr(export_table_ptr.get(), func_addrs));
}

TEST_F(io_pe64, func_ordinals) {
    io::pe64 pe64(zlib);
    auto     export_table_ptr = std::make_unique<IMAGE_EXPORT_DIRECTORY>();
    EXPECT_TRUE(pe64.get_export_table(*export_table_ptr));

    auto func_ordinals = pe64.get_export_func_ordinal(export_table_ptr.get());
    EXPECT_EQ(func_ordinals.size(), export_table_ptr->NumberOfFunctions);
    auto func_ordinals_backup = func_ordinals[0];
    func_ordinals[0]          = 1234;
    EXPECT_TRUE(
        pe64.set_export_func_ordinal(export_table_ptr.get(), func_ordinals));
    func_ordinals[0] = func_ordinals_backup;
    EXPECT_TRUE(
        pe64.set_export_func_ordinal(export_table_ptr.get(), func_ordinals));
}

TEST_F(io_pe64, import_table_check) {
    io::pe64 pe64(zlib);
    auto     import_table = pe64.get_import_table();
    EXPECT_GT(import_table.size(), 0);

    auto dll_name        = import_table[0].Name;
    import_table[0].Name = 1234;
    EXPECT_TRUE(pe64.set_import_table(import_table));
    import_table[0].Name = dll_name;
    EXPECT_TRUE(pe64.set_import_table(import_table));
}

TEST_F(io_pe64, dll_name_check) {
    io::pe64 pe64(zlib);
    auto     import_table = pe64.get_import_table();
    EXPECT_GT(import_table.size(), 0);

    auto dll_name_strings =
        pe64.get_import_table_dll_name_strings(import_table);
    EXPECT_GT(dll_name_strings.size(), 0);

    auto dll_name = pe64.get_import_table_dll_name(import_table);
    EXPECT_GT(dll_name.size(), 0);

    auto dll_name_backup = dll_name[0];
    dll_name[0]          = 1234;
    EXPECT_TRUE(pe64.set_import_table_dll_name(import_table, dll_name));
    dll_name[0] = dll_name_backup;
    EXPECT_TRUE(pe64.set_import_table_dll_name(import_table, dll_name));
}

TEST_F(io_pe64, first_thunk_check) {
    io::pe64 pe64(zlib);
    auto     import_table = pe64.get_import_table();
    EXPECT_GT(import_table.size(), 0);

    auto first_thunk = pe64.get_import_table_first_thunk(import_table);
    EXPECT_GT(first_thunk.size(), 0);

    auto first_thunk_backup = first_thunk[0];
    first_thunk[0]          = 1234;
    EXPECT_TRUE(pe64.set_import_table_first_thunk(import_table, first_thunk));
    first_thunk[0] = first_thunk_backup;
    EXPECT_TRUE(pe64.set_import_table_first_thunk(import_table, first_thunk));
}

TEST_F(io_pe64, thunk_data_check) {
    io::pe64 pe64(zlib);
    auto     import_table = pe64.get_import_table();
    EXPECT_GT(import_table.size(), 0);
    auto first_thunk = pe64.get_import_table_first_thunk(import_table);
    EXPECT_GT(first_thunk.size(), 0);

    auto thunk_data = pe64.get_import_table_thunk_data(first_thunk[0]);
    EXPECT_GT(thunk_data.size(), 0);

    auto address_of_data           = thunk_data[0].u1.AddressOfData;
    thunk_data[0].u1.AddressOfData = 1234;
    EXPECT_TRUE(pe64.set_import_table_thunk_data(first_thunk[0], thunk_data));
    thunk_data[0].u1.AddressOfData = address_of_data;
    EXPECT_TRUE(pe64.set_import_table_thunk_data(first_thunk[0], thunk_data));
}

TEST_F(io_pe64, func_name_check) {
    io::pe64 pe64(zlib);
    auto     import_table = pe64.get_import_table();
    EXPECT_GT(import_table.size(), 0);
    auto first_thunk = pe64.get_import_table_first_thunk(import_table);
    EXPECT_GT(first_thunk.size(), 0);
    auto thunk_data = pe64.get_import_table_thunk_data(first_thunk[0]);
    EXPECT_GT(thunk_data.size(), 0);

    auto func_name_string = pe64.get_import_table_func_name_strings(thunk_data);
    EXPECT_GT(func_name_string.size(), 0);
    auto func_name = pe64.get_import_table_func_name(thunk_data);
    EXPECT_GT(func_name.size(), 0);

    auto func_name_backup = func_name[0].name;
    func_name[0].name     = "haha";
    EXPECT_TRUE(pe64.set_import_table_func_name(thunk_data, func_name));
    // auto func_name2 = pe64.get_import_table_func_name(thunk_data);
    // EXPECT_GT(func_name2.size(), 0);
    func_name[0].name = func_name_backup;
    EXPECT_TRUE(pe64.set_import_table_func_name(thunk_data, func_name));
    // auto func_name3 = pe64.get_import_table_func_name(thunk_data);
    // EXPECT_GT(func_name3.size(), 0);
}

TEST_F(io_pe64, func_ordinals_check) {
    io::pe64 pe64(zlib);
    auto     import_table = pe64.get_import_table();
    EXPECT_GT(import_table.size(), 0);
    auto first_thunk = pe64.get_import_table_first_thunk(import_table);
    EXPECT_GT(first_thunk.size(), 0);
    auto thunk_data = pe64.get_import_table_thunk_data(first_thunk[0]);
    EXPECT_GT(thunk_data.size(), 0);

    auto func_ordinals = pe64.get_import_table_func_ordinal(thunk_data);
    EXPECT_GT(func_ordinals.size(), 0);
    auto func_ordinals_backup = func_ordinals[0];
    func_ordinals[0]          = std::make_pair(1234, 1234);
    EXPECT_TRUE(pe64.set_import_table_func_ordinal(
        first_thunk[0], thunk_data, func_ordinals));
    func_ordinals[0] = func_ordinals_backup;
    EXPECT_TRUE(pe64.set_import_table_func_ordinal(
        first_thunk[0], thunk_data, func_ordinals));
}

TEST_F(io_pe64, forwarder_chain_check) {
    io::pe64 pe64(zlib);
    auto     import_table = pe64.get_import_table();
    EXPECT_GT(import_table.size(), 0);

    auto forwarder_chains = pe64.get_import_table_forwarder_chain(import_table);
    EXPECT_GT(forwarder_chains.size(), 0);
    auto forwarder_chain_backup = forwarder_chains[0];
    forwarder_chains[0]         = std::make_pair(1234, 1234);
    EXPECT_TRUE(
        pe64.set_import_table_forwarder_chain(import_table, forwarder_chains));
    forwarder_chains[0] = forwarder_chain_backup;
    EXPECT_TRUE(
        pe64.set_import_table_forwarder_chain(import_table, forwarder_chains));
}

TEST_F(io_pe64, forwarder_string_addr_check) {
    io::pe64 pe64(zlib);
    auto     import_table = pe64.get_import_table();
    EXPECT_GT(import_table.size(), 0);
    auto forwarder_chains = pe64.get_import_table_forwarder_chain(import_table);
    EXPECT_GT(forwarder_chains.size(), 0);

    auto forwarder_string =
        pe64.get_import_table_forwarder_string(forwarder_chains);
    EXPECT_GT(forwarder_string.size(), 0);

    auto forwarder_string_addrs =
        pe64.get_import_table_forwarder_string_addr(forwarder_chains);
    EXPECT_GT(forwarder_string_addrs.size(), 0);
    auto forwarder_string_addrs_backup = forwarder_string_addrs[0];
    forwarder_string_addrs[0]          = 1234;
    EXPECT_TRUE(pe64.set_import_table_forwarder_string_addr(
        forwarder_chains, forwarder_string_addrs));
    forwarder_string_addrs[0] = forwarder_string_addrs_backup;
    EXPECT_TRUE(pe64.set_import_table_forwarder_string_addr(
        forwarder_chains, forwarder_string_addrs));
}

TEST_F(io_pe64, relocation_table_check) {
    io::pe64 pe64(zlib);
    auto     relocation_table = pe64.get_relocation_table();
    EXPECT_GT(relocation_table.size(), 0);

    auto addr_backup                    = relocation_table[0].virtual_address;
    relocation_table[0].virtual_address = 0x1234;
    EXPECT_TRUE(pe64.set_relocation_table(relocation_table));
    relocation_table[0].virtual_address = addr_backup;
    EXPECT_TRUE(pe64.set_relocation_table(relocation_table));

    auto items = pe64.get_relocation_table_item(relocation_table[0]);
    EXPECT_GT(items.size(), 0);
    auto item_backup      = items[0];
    std::get<1>(items[0]) = IMAGE_REL_BASED_HIGHLOW;
    EXPECT_TRUE(pe64.set_relocation_table_item(relocation_table[0], items));
    EXPECT_TRUE(pe64.set_relocation_table(relocation_table));
    std::get<1>(items[0]) = IMAGE_REL_BASED_DIR64;
    EXPECT_TRUE(pe64.set_relocation_table_item(relocation_table[0], items));
    EXPECT_TRUE(pe64.set_relocation_table(relocation_table));
}

TEST_F(io_pe64, other_check) {
    io::pe64 pe64(zlib);
    auto     section_header = pe64.find_section_header(4096);
    EXPECT_EQ(
        strcmp(reinterpret_cast<char const *>(section_header.Name), ".text"),
        0);

    auto file_header = std::make_unique<IMAGE_FILE_HEADER>();
    EXPECT_TRUE(pe64.get_file_header(*file_header));
    auto datetime = pe64.datetime(file_header->TimeDateStamp);
    EXPECT_GT(datetime.size(), 0);
}
