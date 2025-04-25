#include <gtest/gtest.h>
#include "io/fs.h"
namespace io = YanLib::io;

class io_fs : public ::testing::Test {
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
        li.QuadPart = uli.QuadPart;
        return li;
    }

    static SYSTEMTIME large_integer_to_date(LARGE_INTEGER &liTime) {
        FILETIME ft;
        SYSTEMTIME stUTC, stLocal;
        ft.dwLowDateTime = liTime.LowPart;
        ft.dwHighDateTime = liTime.HighPart;
        FileTimeToSystemTime(&ft, &stUTC);
        SystemTimeToTzSpecificLocalTime(nullptr, &stUTC, &stLocal);
        return stLocal;
    }

    void SetUp() override {
        temp_path = fs.get_temp_path();
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

        if (!fs.is_exists(fs_test_dir.data())) {
            EXPECT_TRUE(io::fs::mkdir(fs_test_dir.data()));
        }
        EXPECT_TRUE(io::fs::copy(notepad, read_notepad.data()));

        read_handle = fs.open(read_notepad.data());
        write_handle = fs.create(write_notepad.data());
        EXPECT_TRUE(read_handle);
        EXPECT_TRUE(write_handle);
    }

    std::wstring user_name;
    std::wstring temp_path;
    const wchar_t *notepad = L"C:\\Windows\\System32\\notepad.exe";
    std::wstring read_notepad;
    std::wstring write_notepad;
    std::wstring fs_test_dir;
    io::fs fs;
    HANDLE read_handle = INVALID_HANDLE_VALUE;
    HANDLE write_handle = INVALID_HANDLE_VALUE;
};

TEST_F(io_fs, pre_check) {
    EXPECT_TRUE(fs.is_exists(temp_path.data()));
    EXPECT_TRUE(fs.is_exists(notepad));
    EXPECT_TRUE(fs.is_exists(read_notepad.data()));
}

TEST_F(io_fs, read_check) {
    int64_t file_size = fs.size(read_handle);
    EXPECT_GT(file_size, 0);

    std::vector<uint8_t> buffer(32, L'\0');
    DWORD bytes_read = 0;
    EXPECT_TRUE(fs.read(read_handle, buffer.data(), buffer.size(), &bytes_read));

    EXPECT_EQ(fs.seek(read_handle, 0, FILE_BEGIN), 0);
    EXPECT_EQ(fs.read_bytes(read_handle, 1024).size(), 1024);

    EXPECT_EQ(fs.seek(read_handle, 0, FILE_BEGIN), 0);
    EXPECT_EQ(fs.read_string(read_handle, 1024).size(), 1024);

    EXPECT_EQ(fs.seek(read_handle, 0, FILE_BEGIN), 0);
    EXPECT_EQ(fs.read_wstring(read_handle, 512).size(), 512);

    EXPECT_EQ(fs.seek(read_handle, 0, FILE_BEGIN), 0);
    EXPECT_EQ(fs.read_bytes_to_end(read_handle).size(), file_size);

    EXPECT_EQ(fs.seek(read_handle, 0, FILE_BEGIN), 0);
    EXPECT_EQ(fs.read_string_to_end(read_handle).size(), file_size);

    EXPECT_EQ(fs.seek(read_handle, 0, FILE_BEGIN), 0);
    EXPECT_EQ(fs.read_wstring_to_end(read_handle).size(), file_size / sizeof(wchar_t));
}

TEST_F(io_fs, write_check) {
    std::vector<uint8_t> buffer(32, L'\0');
    DWORD bytes_read = 0;
    DWORD bytes_written = 0;
    EXPECT_EQ(fs.seek(read_handle, 0, FILE_BEGIN), 0);
    EXPECT_TRUE(fs.read(read_handle, buffer.data(), buffer.size(), &bytes_read));
    EXPECT_TRUE(fs.write(write_handle, buffer.data(), buffer.size(), &bytes_written));

    EXPECT_EQ(fs.seek(read_handle, 0, FILE_BEGIN), 0);
    auto bytes = fs.read_bytes(read_handle, 1024);
    EXPECT_EQ(fs.write_bytes(write_handle, bytes), bytes.size());

    EXPECT_EQ(fs.seek(read_handle, 0, FILE_BEGIN), 0);
    auto string = fs.read_string(read_handle, 1024);
    EXPECT_EQ(fs.write_string(write_handle, string), string.size());

    EXPECT_EQ(fs.seek(read_handle, 0, FILE_BEGIN), 0);
    auto wstring = fs.read_wstring(read_handle, 512);
    EXPECT_EQ(fs.write_wstring(write_handle, wstring), wstring.size());
}

TEST_F(io_fs, info_check) {
    auto file_basic_info = std::make_unique<FILE_BASIC_INFO>();
    EXPECT_TRUE(fs.get_info(read_handle, FileBasicInfo, file_basic_info.get(), sizeof(FILE_BASIC_INFO)));
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
    EXPECT_TRUE(fs.set_info(read_handle, FileBasicInfo, file_basic_info.get(), sizeof(FILE_BASIC_INFO)));
}

TEST_F(io_fs, lock_check) {
    EXPECT_TRUE(fs.lock(read_handle));
    EXPECT_TRUE(fs.unlock(read_handle));

    EXPECT_TRUE(fs.lock(write_handle));
    EXPECT_TRUE(fs.unlock(write_handle));
}

TEST_F(io_fs, attr_check) {
    DWORD attr = fs.get_attr(read_notepad.data());
    EXPECT_EQ(attr, FILE_ATTRIBUTE_ARCHIVE);
    EXPECT_TRUE(fs.set_attr(read_notepad.data(), attr | FILE_ATTRIBUTE_READONLY));
    EXPECT_TRUE(fs.set_attr(read_notepad.data(), attr & ~FILE_ATTRIBUTE_READONLY));
}

TEST_F(io_fs, volume_info_check) {
    auto info = std::make_unique<io::fs::VolumeInfo>();
    EXPECT_TRUE(fs.get_volume_info(read_handle, info.get()));
    EXPECT_EQ(wcscmp(info->volume_name, L"Windows"), 0);
    EXPECT_EQ(wcscmp(info->file_system_name, L"NTFS"), 0);
    // EXPECT_EQ(info->serial_number, 485725206);
}

TEST_F(io_fs, type_check) {
    EXPECT_EQ(fs.file_type(read_handle), FILE_TYPE_DISK);
    EXPECT_EQ(fs.get_drive_type(L"C:\\"), DRIVE_FIXED);
}

TEST_F(io_fs, path_name) {
    auto path_name = fs.get_final_path_name(read_handle);
    EXPECT_TRUE(path_name.substr(4) == read_notepad);

    EXPECT_TRUE(fs.is_short_name_enabled(read_handle));
}

TEST_F(io_fs, volume_name) {
    auto volume_path_name = fs.get_volume_path_name(read_notepad.data());
    EXPECT_EQ(wcscmp(volume_path_name.data(), L"C:\\"), 0);

    auto volume_names = io::fs::ls_volume_name();
    EXPECT_GT(volume_names.size(), 0);
    auto volume_path_names_for_volume_name = fs.get_volume_path_names_for_volume_name(volume_names[0].data());
    EXPECT_EQ(wcscmp(volume_path_names_for_volume_name.data(), L"C:\\"), 0);

    auto volume_name_for_volume_mount_point = fs.get_volume_name_for_volume_mount_point(L"C:\\");
    EXPECT_NE(volume_name_for_volume_mount_point.find(L"\\\\?\\Volume{"), std::wstring::npos);
}

TEST_F(io_fs, temp_name) {
    auto temp = fs.get_temp_path();
    EXPECT_NE(temp.find(temp_path), std::wstring::npos);

    auto temp_name = fs.get_temp_file_name(temp_path.data(), L"aaa");
    EXPECT_NE(temp_name.find(temp_path), std::wstring::npos);
    EXPECT_NE(temp_name.find(L"aaa"), std::wstring::npos);
    EXPECT_NE(temp_name.find(L"tmp"), std::wstring::npos);
}

TEST_F(io_fs, long_short_check) {
    auto long_name = fs.get_long_path_name(L"C:\\PROGRA~1");
    EXPECT_NE(long_name.find(L"C:\\Program Files"), std::wstring::npos);
    auto short_name = fs.get_short_path_name(L"C:\\Program Files\\");
    EXPECT_NE(short_name.find(L"C:\\PROGRA~1"), std::wstring::npos);
}

TEST_F(io_fs, disk_check) {
    auto logical_drive_strings = fs.get_logical_drive_strings();
    EXPECT_NE(logical_drive_strings.find(L"C:\\"), std::wstring::npos);

    EXPECT_TRUE(fs.get_logica_drives() & 4);

    constexpr wchar_t windows_name[] = L"C:\\Windows\\System32\\..\\..\\";
    auto full_path_name = fs.get_full_path_name(windows_name);
    EXPECT_NE(full_path_name.find(L"C:\\"), std::wstring::npos);

    auto disk_space_info = std::make_unique<DISK_SPACE_INFORMATION>();
    EXPECT_TRUE(fs.get_disk_space_info(temp_path.data(), disk_space_info.get()));

    auto disk_space_info4 = std::make_unique<io::fs::DiskFreeSpace4>();
    EXPECT_TRUE(fs.get_disk_free_space(temp_path.data(), disk_space_info4.get()));

    auto disk_space_info3 = std::make_unique<io::fs::DiskFreeSpace3>();
    EXPECT_TRUE(fs.get_disk_free_space(temp_path.data(), disk_space_info3.get()));
    auto compressed_file_size = fs.get_compressed_file_size(read_notepad.data());
    EXPECT_GT(compressed_file_size, 0);
}

TEST_F(io_fs, device_check) {
    auto dos_device = fs.get_dos_device(L"C:");
    EXPECT_NE(dos_device.find(L"\\Device\\HarddiskVolume"), std::wstring::npos);

    auto dos_device_list = fs.get_dos_device();
    EXPECT_GT(dos_device_list.size(), 0);
}

TEST_F(io_fs, list_check) {
    auto volume_name_list = io::fs::ls_volume_name();
    EXPECT_GT(volume_name_list.size(), 0);
    for (const auto &volume_name: volume_name_list) {
        EXPECT_NE(volume_name.find(L"\\\\?\\Volume{"), std::wstring::npos);
    }

    auto device_name_list = io::fs::ls_device_name();
    EXPECT_GT(device_name_list.size(), 0);
    for (const auto &device_name: device_name_list) {
        EXPECT_NE(device_name.find(L"\\Device\\HarddiskVolume"), std::wstring::npos);
    }

    auto list_detail = io::fs::ls_detail(temp_path.data());
    EXPECT_GT(list_detail.size(), 0);

    auto list = io::fs::ls(temp_path.data());
    EXPECT_GT(list.size(), 0);

    auto list_full_path = io::fs::ls_full_path(temp_path.data());
    EXPECT_GT(list_full_path.size(), 0);

    auto list_all_files = io::fs::ls_all_files(fs_test_dir.data());
    EXPECT_GT(list_all_files.size(), 0);

    auto list_all_dirs = io::fs::ls_all_dirs(temp_path.data());
    EXPECT_GT(list_all_dirs.size(), 0);
}

TEST_F(io_fs, mkdir_and_rm_check) {
    for (int i = 0; i < 5; i++) {
        EXPECT_GT(fs.get_temp_file_name(fs_test_dir.data(), L"aaa").size(), 0);
    }
    for (int i = 0; i < 5; i++) {
        auto temp_name = fs_test_dir;
        temp_name.append(L"\\dir");
        temp_name.append(std::to_wstring(i));
        EXPECT_TRUE(io::fs::mkdir(temp_name.data()));
    }

    for (int i = 0; i < 5; i++) {
        auto temp_name = fs_test_dir;
        temp_name.append(L"\\multi");
        temp_name.append(std::to_wstring(i));
        temp_name.append(L"\\one");
        temp_name.append(L"\\two");
        temp_name.append(L"\\three");
        EXPECT_TRUE(io::fs::mkdir_all(temp_name.data()));
    }


    auto files = io::fs::ls_all_files(fs_test_dir.data());
    for (auto file: files) {
        if (file.find(L"notepad") == std::wstring::npos) {
            EXPECT_TRUE(io::fs::rm_file(file.data()));
        }
    }

    auto dirs = io::fs::ls_full_path(fs_test_dir.data());
    for (auto dir: dirs) {
        if (dir.find(L"dir") != std::wstring::npos) {
            EXPECT_TRUE(io::fs::rm_dir(dir.data()));
        }
        if (dir.find(L"multi") != std::wstring::npos) {
            EXPECT_TRUE(io::fs::rm_dir_all(dir.data()));
        }
    }
}

TEST_F(io_fs, copy_check) {
    std::wstring copy_name = read_notepad;
    copy_name.append(L".copy");
    EXPECT_TRUE(io::fs::copy(read_notepad.data(), copy_name.data()));

    std::wstring copy_name2 = read_notepad;
    copy_name2.append(L".copy2");
    EXPECT_TRUE(io::fs::copy_all(read_notepad.data(), copy_name2.data()));
}

TEST_F(io_fs, rename_check) {
    std::wstring raw_name = read_notepad;
    raw_name.append(L".copy");
    std::wstring rename_name = read_notepad;
    rename_name.append(L".rename");
    EXPECT_TRUE(io::fs::rename(raw_name.data(), rename_name.data()));
    EXPECT_TRUE(io::fs::replace(rename_name.data(), raw_name.c_str()));
}
