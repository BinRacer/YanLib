#include <gtest/gtest.h>
#include "io/fs.h"
namespace io = YanLib::io;

class io_fs_wide : public testing::Test {
protected:
    static LARGE_INTEGER date_to_large_integer(const SYSTEMTIME &st) {
        FILETIME ft;
        if (!SystemTimeToFileTime(&st, &ft)) {
            return {};
        }
        ULARGE_INTEGER uli;
        uli.LowPart = ft.dwLowDateTime;
        uli.HighPart = ft.dwHighDateTime;

        LARGE_INTEGER li;
        li.QuadPart = static_cast<int64_t>(uli.QuadPart);
        return li;
    }

    static SYSTEMTIME large_integer_to_date(const LARGE_INTEGER &liTime) {
        FILETIME ft;
        SYSTEMTIME stUTC, stLocal;
        ft.dwLowDateTime = liTime.LowPart;
        ft.dwHighDateTime = liTime.HighPart;
        FileTimeToSystemTime(&ft, &stUTC);
        SystemTimeToTzSpecificLocalTime(nullptr, &stUTC, &stLocal);
        return stLocal;
    }

    void SetUp() override {
        EXPECT_TRUE(fs_util.get_temp_path(temp_path));
        EXPECT_GT(temp_path.size(), 0);
        while (temp_path.back() == L'\\') {
            temp_path.pop_back();
        }

        fs_test_dir.append(temp_path);
        fs_test_dir.append(L"\\fs_test");

        read_notepad.append(fs_test_dir);
        read_notepad.append(L"\\notepad.exe.read");

        write_notepad.append(fs_test_dir);
        write_notepad.append(L"\\notepad.exe.write");

        if (!fs_util.is_exists(fs_test_dir.data())) {
            EXPECT_TRUE(fs_util.mkdir(fs_test_dir.data()));
        }
        EXPECT_TRUE(fs_util.copy(notepad, read_notepad.data()));

        EXPECT_TRUE(fs_util.is_exists(temp_path.data()));
        EXPECT_TRUE(fs_util.is_exists(notepad));
        EXPECT_TRUE(fs_util.is_exists(read_notepad.data()));
    }

    std::wstring temp_path;
    const wchar_t *notepad = L"C:\\Windows\\System32\\notepad.exe";
    std::wstring read_notepad;
    std::wstring write_notepad;
    std::wstring fs_test_dir;
    io::fs_util fs_util;
};

TEST_F(io_fs_wide, read_check) {
    io::fs read_file(read_notepad.data());
    int64_t file_size = read_file.size();
    EXPECT_GT(file_size, 0);

    std::vector<uint8_t> buffer(32, L'\0');
    uint32_t bytes_read = 0;
    EXPECT_TRUE(read_file.read(buffer.data(), buffer.size(), &bytes_read));

    EXPECT_EQ(read_file.seek(0, io::MoveMethod::Begin), 0);
    EXPECT_EQ(read_file.read_bytes(1024).size(), 1024);

    EXPECT_EQ(read_file.seek(0, io::MoveMethod::Begin), 0);
    EXPECT_EQ(read_file.read_string(1024).size(), 1024);

    EXPECT_EQ(read_file.seek(0, io::MoveMethod::Begin), 0);
    EXPECT_EQ(read_file.read_bytes_to_end().size(), file_size);

    EXPECT_EQ(read_file.seek(0, io::MoveMethod::Begin), 0);
    EXPECT_EQ(read_file.read_string_to_end().size(), file_size);
}

TEST_F(io_fs_wide, write_check) {
    io::fs read_file(read_notepad.data());
    io::fs write_file(write_notepad.data(),
                      io::DesiredAccess::Read | io::DesiredAccess::Write,
                      io::ShareMode::Read | io::ShareMode::Write, nullptr,
                      io::CreationDisposition::CreateAlways);
    std::vector<uint8_t> buffer(32, L'\0');
    uint32_t bytes_read = 0;
    uint32_t bytes_written = 0;
    EXPECT_EQ(read_file.seek(0, io::MoveMethod::Begin), 0);
    EXPECT_TRUE(read_file.read(buffer.data(), buffer.size(), &bytes_read));
    EXPECT_TRUE(write_file.write(buffer.data(), buffer.size(), &bytes_written));

    EXPECT_EQ(read_file.seek(0, io::MoveMethod::Begin), 0);
    auto bytes = read_file.read_bytes(1024);
    EXPECT_EQ(write_file.write_bytes(bytes), bytes.size());

    EXPECT_EQ(read_file.seek(0, io::MoveMethod::Begin), 0);
    auto string = read_file.read_string(1024);
    EXPECT_EQ(write_file.write_string(string), string.size());
}

TEST_F(io_fs_wide, info_check) {
    io::fs read_file(read_notepad.data());
    auto file_basic_info = std::make_unique<FILE_BASIC_INFO>();
    EXPECT_TRUE(read_file.get_info(FileBasicInfo, file_basic_info.get(),
                                   sizeof(FILE_BASIC_INFO)));
    // SYSTEMTIME st = {};
    // st.wYear = 1970;
    // st.wMonth = 1;
    // st.wDay = 1;
    // file_basic_info->CreationTime = date_to_large_integer(st);
    auto raw_date = large_integer_to_date(file_basic_info->CreationTime);
    raw_date.wYear = 1970;
    raw_date.wMonth = 1;
    raw_date.wDay = 1;
    file_basic_info->CreationTime = date_to_large_integer(raw_date);
    EXPECT_TRUE(read_file.set_info(FileBasicInfo, file_basic_info.get(),
                                   sizeof(FILE_BASIC_INFO)));
}

TEST_F(io_fs_wide, lock_check) {
    io::fs read_file(read_notepad.data());
    io::fs write_file(write_notepad.data(),
                      io::DesiredAccess::Read | io::DesiredAccess::Write,
                      io::ShareMode::Read | io::ShareMode::Write, nullptr,
                      io::CreationDisposition::CreateAlways);
    EXPECT_TRUE(read_file.lock());
    EXPECT_TRUE(read_file.unlock());

    EXPECT_TRUE(write_file.lock());
    EXPECT_TRUE(write_file.unlock());
}

TEST_F(io_fs_wide, attr_check) {
    uint32_t attr = fs_util.get_attr(read_notepad.data());
    EXPECT_EQ(attr, FILE_ATTRIBUTE_ARCHIVE);
    EXPECT_TRUE(fs_util.set_attr(read_notepad.data(),
                                 attr | FILE_ATTRIBUTE_READONLY));
    EXPECT_TRUE(fs_util.set_attr(read_notepad.data(),
                                 attr & ~FILE_ATTRIBUTE_READONLY));
}

TEST_F(io_fs_wide, volume_info_check) {
    io::fs read_file(read_notepad.data());
    auto info = std::make_unique<io::VolumeInfoW>();
    EXPECT_TRUE(read_file.get_volume_info(info.get()));
    EXPECT_EQ(wcscmp(info->volume_name, L"Windows"), 0);
    EXPECT_EQ(wcscmp(info->file_system_name, L"NTFS"), 0);
    // EXPECT_EQ(info->serial_number, 485725206);
}

TEST_F(io_fs_wide, type_check) {
    io::fs read_file(read_notepad.data());
    EXPECT_EQ(read_file.file_type(), io::FileType::Disk);
    EXPECT_EQ(fs_util.get_drive_type(L"C:\\"), io::DriveType::Fixed);
}

TEST_F(io_fs_wide, path_name) {
    io::fs read_file(read_notepad.data());
    std::wstring path_name;
    EXPECT_TRUE(read_file.get_final_path_name(path_name));
    EXPECT_TRUE(path_name.substr(4) == read_notepad);

    EXPECT_TRUE(read_file.is_short_name_enabled());
}

TEST_F(io_fs_wide, volume_name) {
    auto volume_path_name = fs_util.get_volume_path_name(read_notepad.data());
    EXPECT_EQ(wcscmp(volume_path_name.data(), L"C:\\"), 0);

    std::vector<std::wstring> volume_names;
    EXPECT_TRUE(fs_util.ls_volume_name(volume_names));
    EXPECT_GT(volume_names.size(), 0);
    auto volume_path_names_for_volume_name =
            fs_util.get_volume_path_names_for_volume_name(
                    volume_names[0].data());
    EXPECT_EQ(wcscmp(volume_path_names_for_volume_name.data(), L"C:\\"), 0);

    auto volume_name_for_volume_mount_point =
            fs_util.get_volume_name_for_volume_mount_point(L"C:\\");
    EXPECT_NE(volume_name_for_volume_mount_point.find(L"\\\\?\\Volume{"),
              std::wstring::npos);
}

TEST_F(io_fs_wide, temp_name) {
    std::wstring temp;
    EXPECT_TRUE(fs_util.get_temp_path(temp));
    EXPECT_NE(temp.find(temp_path), std::wstring::npos);

    auto temp_name = fs_util.get_temp_file_name(temp_path.data(), L"aaa");
    EXPECT_NE(temp_name.find(temp_path), std::wstring::npos);
    EXPECT_NE(temp_name.find(L"aaa"), std::wstring::npos);
    EXPECT_NE(temp_name.find(L"tmp"), std::wstring::npos);
}

TEST_F(io_fs_wide, long_short_check) {
    auto long_name = fs_util.get_long_path_name(L"C:\\PROGRA~1");
    EXPECT_NE(long_name.find(L"C:\\Program Files"), std::wstring::npos);
    auto short_name = fs_util.get_short_path_name(L"C:\\Program Files\\");
    EXPECT_NE(short_name.find(L"C:\\PROGRA~1"), std::wstring::npos);
}

TEST_F(io_fs_wide, disk_check) {
    std::wstring logical_drive_strings;
    EXPECT_TRUE(fs_util.get_logical_drive_strings(logical_drive_strings));
    EXPECT_NE(logical_drive_strings.find(L"C:\\"), std::wstring::npos);

    EXPECT_TRUE(fs_util.get_logica_drives() & 4);

    constexpr wchar_t windows_name[] = L"C:\\Windows\\System32\\..\\..\\";
    auto full_path_name = fs_util.get_full_path_name(windows_name);
    EXPECT_NE(full_path_name.find(L"C:\\"), std::wstring::npos);

    auto disk_space_info = std::make_unique<DISK_SPACE_INFORMATION>();
    EXPECT_TRUE(fs_util.get_disk_space_info(temp_path.data(),
                                            disk_space_info.get()));

    auto disk_space_info4 = std::make_unique<io::DiskFreeSpace4>();
    EXPECT_TRUE(fs_util.get_disk_free_space(temp_path.data(),
                                            disk_space_info4.get()));

    auto disk_space_info3 = std::make_unique<io::DiskFreeSpace3>();
    EXPECT_TRUE(fs_util.get_disk_free_space(temp_path.data(),
                                            disk_space_info3.get()));
    auto compressed_file_size =
            fs_util.get_compressed_file_size(read_notepad.data());
    EXPECT_GT(compressed_file_size, 0);
}

TEST_F(io_fs_wide, device_check) {
    auto dos_device = fs_util.get_dos_device(L"C:");
    EXPECT_NE(dos_device.find(L"\\Device\\HarddiskVolume"), std::wstring::npos);

    std::vector<std::wstring> dos_device_list;
    EXPECT_TRUE(fs_util.get_dos_device(dos_device_list));
    EXPECT_GT(dos_device_list.size(), 0);
}

TEST_F(io_fs_wide, list_check) {
    std::vector<std::wstring> volume_name_list;
    EXPECT_TRUE(fs_util.ls_volume_name(volume_name_list));
    EXPECT_GT(volume_name_list.size(), 0);
    for (const auto &volume_name : volume_name_list) {
        EXPECT_NE(volume_name.find(L"\\\\?\\Volume{"), std::wstring::npos);
    }

    std::vector<std::wstring> device_name_list;
    EXPECT_TRUE(fs_util.ls_device_name(device_name_list));
    EXPECT_GT(device_name_list.size(), 0);
    for (const auto &device_name : device_name_list) {
        EXPECT_NE(device_name.find(L"\\Device\\HarddiskVolume"),
                  std::wstring::npos);
    }

    auto list_detail = fs_util.ls_detail(temp_path.data());
    EXPECT_GT(list_detail.size(), 0);

    auto list = fs_util.ls(temp_path.data());
    EXPECT_GT(list.size(), 0);

    auto list_full_path = fs_util.ls_full_path(temp_path.data());
    EXPECT_GT(list_full_path.size(), 0);

    auto list_all_files = fs_util.ls_all_files(fs_test_dir.data());
    EXPECT_GT(list_all_files.size(), 0);

    auto list_all_dirs = fs_util.ls_all_dirs(temp_path.data());
    EXPECT_GT(list_all_dirs.size(), 0);
}

TEST_F(io_fs_wide, mkdir_and_rm_check) {
    for (int i = 0; i < 5; i++) {
        EXPECT_GT(fs_util.get_temp_file_name(fs_test_dir.data(), L"aaa").size(),
                  0);
    }
    for (int i = 0; i < 5; i++) {
        auto temp_name = fs_test_dir;
        temp_name.append(L"\\dir");
        temp_name.append(std::to_wstring(i));
        EXPECT_TRUE(fs_util.mkdir(temp_name.data()));
    }

    for (int i = 0; i < 5; i++) {
        auto temp_name = fs_test_dir;
        temp_name.append(L"\\multi");
        temp_name.append(std::to_wstring(i));
        temp_name.append(L"\\one");
        temp_name.append(L"\\two");
        temp_name.append(L"\\three");
        EXPECT_TRUE(fs_util.mkdir_all(temp_name.data()));
    }

    auto files = fs_util.ls_all_files(fs_test_dir.data());
    for (auto file : files) {
        if (file.find(L"notepad") == std::wstring::npos) {
            EXPECT_TRUE(fs_util.rm_file(file.data()));
        }
    }

    auto dirs = fs_util.ls_full_path(fs_test_dir.data());
    for (auto dir : dirs) {
        if (dir.find(L"dir") != std::wstring::npos) {
            EXPECT_TRUE(fs_util.rm_dir(dir.data()));
        }
        if (dir.find(L"multi") != std::wstring::npos) {
            EXPECT_TRUE(fs_util.rm_dir_all(dir.data()));
        }
    }
}

TEST_F(io_fs_wide, copy_check) {
    std::wstring copy_name = read_notepad;
    copy_name.append(L".copy");
    EXPECT_TRUE(fs_util.copy(read_notepad.data(), copy_name.data()));

    std::wstring copy_name2 = read_notepad;
    copy_name2.append(L".copy2");
    EXPECT_TRUE(fs_util.copy_all(read_notepad.data(), copy_name2.data()));
}

TEST_F(io_fs_wide, rename_check) {
    std::wstring raw_name = read_notepad;
    raw_name.append(L".copy");
    std::wstring rename_name = read_notepad;
    rename_name.append(L".rename");
    EXPECT_TRUE(fs_util.rename(raw_name.data(), rename_name.data()));
    EXPECT_TRUE(fs_util.replace(rename_name.data(), raw_name.c_str()));
}
