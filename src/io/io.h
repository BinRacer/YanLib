/* clang-format off */
/*
 * @file io.h
 * @date 2025-06-17
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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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
#ifndef IO_H
#define IO_H
#include <winnt.h>
#include <fileapi.h>
#include <WinBase.h>
#include <cstdint>
namespace YanLib::io {
    enum class DesiredAccess : uint32_t {
        None = 0,
        Read = GENERIC_READ,
        Write = GENERIC_WRITE,
        Execute = GENERIC_EXECUTE,
        All = GENERIC_ALL,
    };

    inline DesiredAccess operator|(DesiredAccess a, DesiredAccess b) {
        return static_cast<DesiredAccess>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class ShareMode : uint32_t {
        None = 0,
        Read = FILE_SHARE_READ,
        Write = FILE_SHARE_WRITE,
        Delete = FILE_SHARE_DELETE,
    };

    inline ShareMode operator|(ShareMode a, ShareMode b) {
        return static_cast<ShareMode>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }

    enum class CreationDisposition : uint32_t {
        CreateNew = CREATE_NEW,
        CreateAlways = CREATE_ALWAYS,
        OpenExisting = OPEN_EXISTING,
        OpenAlways = OPEN_ALWAYS,
        TruncateExisting = TRUNCATE_EXISTING,
    };

    enum class FlagAndAttr : uint32_t {
        // basic attributes
        ReadOnly = FILE_ATTRIBUTE_READONLY,
        Hidden = FILE_ATTRIBUTE_HIDDEN,
        System = FILE_ATTRIBUTE_SYSTEM,
        Directory = FILE_ATTRIBUTE_DIRECTORY,
        Archive = FILE_ATTRIBUTE_ARCHIVE,
        // special attributes
        Device = FILE_ATTRIBUTE_DEVICE,
        Normal = FILE_ATTRIBUTE_NORMAL,
        Temporary = FILE_ATTRIBUTE_TEMPORARY,
        SparseFile = FILE_ATTRIBUTE_SPARSE_FILE,
        ReparsePoint = FILE_ATTRIBUTE_REPARSE_POINT,
        // storage attributes
        Compressed = FILE_ATTRIBUTE_COMPRESSED,
        Offline = FILE_ATTRIBUTE_OFFLINE,
        NotContentIndexed = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
        Encrypted = FILE_ATTRIBUTE_ENCRYPTED,
        IntegrityStream = FILE_ATTRIBUTE_INTEGRITY_STREAM,
        // advice attributes
        Virtual = FILE_ATTRIBUTE_VIRTUAL,
        NoScrubData = FILE_ATTRIBUTE_NO_SCRUB_DATA,
        EA = FILE_ATTRIBUTE_EA,
        Pinned = FILE_ATTRIBUTE_PINNED,
        Unpinned = FILE_ATTRIBUTE_UNPINNED,
        // recall attributes
        RecallOnOpen = FILE_ATTRIBUTE_RECALL_ON_OPEN,
        RecallOnDataAccess = FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS,
        // basic flag
        WriteThrough = FILE_FLAG_WRITE_THROUGH,
        Overlapped = FILE_FLAG_OVERLAPPED,
        NoBuffering = FILE_FLAG_NO_BUFFERING,
        RandomAccess = FILE_FLAG_RANDOM_ACCESS,
        SequentialScan = FILE_FLAG_SEQUENTIAL_SCAN,
        DeleteOnClose = FILE_FLAG_DELETE_ON_CLOSE,
        BackupSemantics = FILE_FLAG_BACKUP_SEMANTICS,
        PosixSemantics = FILE_FLAG_POSIX_SEMANTICS,
        SessionAware = FILE_FLAG_SESSION_AWARE,
        OpenReparsePoint = FILE_FLAG_OPEN_REPARSE_POINT,
        OpenNoRecall = FILE_FLAG_OPEN_NO_RECALL,
        FirstPipeInstance = FILE_FLAG_FIRST_PIPE_INSTANCE,
        // security flag
        Anonymous = SECURITY_ANONYMOUS,
        Identification = SECURITY_IDENTIFICATION,
        Impersonation = SECURITY_IMPERSONATION,
        Delegation = SECURITY_DELEGATION,
        ContextTracking = SECURITY_CONTEXT_TRACKING,
        EffectiveOnly = SECURITY_EFFECTIVE_ONLY,
        SqosPresent = SECURITY_SQOS_PRESENT,
        ValidSqosFlags = SECURITY_VALID_SQOS_FLAGS,
    };

    inline FlagAndAttr operator|(FlagAndAttr a, FlagAndAttr b) {
        return static_cast<FlagAndAttr>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class MoveMethod : uint32_t {
        Begin = FILE_BEGIN,
        Current = FILE_CURRENT,
        End = FILE_END,
    };

    enum class LockMode : uint32_t {
        ExclusiveLock = LOCKFILE_EXCLUSIVE_LOCK,
        TryExclusiveLock = LOCKFILE_EXCLUSIVE_LOCK | LOCKFILE_FAIL_IMMEDIATELY,
    };

    enum class FileType : uint32_t {
        Unknown = FILE_TYPE_UNKNOWN,
        Disk = FILE_TYPE_DISK,
        Char = FILE_TYPE_CHAR,
        Pipe = FILE_TYPE_PIPE,
        Remote = FILE_TYPE_REMOTE,
    };

    enum class DriveType : uint32_t {
        Unknown = DRIVE_UNKNOWN,
        NoRootDir = DRIVE_NO_ROOT_DIR,
        Removable = DRIVE_REMOVABLE,
        Fixed = DRIVE_FIXED,
        Remote = DRIVE_REMOTE,
        CdRom = DRIVE_CDROM,
        RamDisk = DRIVE_RAMDISK,
    };

    enum class PathNameType : uint32_t {
        // Dos = VOLUME_NAME_DOS,
        Guid = VOLUME_NAME_GUID,
        Nt = VOLUME_NAME_NT,
        None = VOLUME_NAME_NONE,
        Normalized = FILE_NAME_NORMALIZED,
        Opened = FILE_NAME_OPENED,
    };

    inline PathNameType operator|(PathNameType a, PathNameType b) {
        return static_cast<PathNameType>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum DosControlCode : uint32_t {
        RawTargetPath = DDD_RAW_TARGET_PATH,
        RemoveDefinition = DDD_REMOVE_DEFINITION,
        ExactMatchOnRemove = DDD_EXACT_MATCH_ON_REMOVE,
        NoBroadcastSystem = DDD_NO_BROADCAST_SYSTEM,
        LuidBroadcastDrive = DDD_LUID_BROADCAST_DRIVE,
    };

    inline DosControlCode operator|(const DosControlCode a,
                                    const DosControlCode b) {
        return static_cast<DosControlCode>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }

    struct VolumeInfoA {
        char volume_name[MAX_PATH + 1];
        char file_system_name[MAX_PATH + 1];
        uint32_t serial_number;
        uint32_t file_system_flag;
    };

    struct VolumeInfoW {
        wchar_t volume_name[MAX_PATH + 1];
        wchar_t file_system_name[MAX_PATH + 1];
        uint32_t serial_number;
        uint32_t file_system_flag;
    };

    struct DiskFreeSpace4 {
        uint32_t sectors_per_cluster;
        uint32_t bytes_per_sector;
        uint32_t number_of_free_clusters;
        uint32_t total_number_of_clusters;
    };

    struct DiskFreeSpace3 {
        uint64_t free_bytes_available_to_caller;
        uint64_t total_number_of_bytes;
        uint64_t total_number_of_free_bytes;
    };
} // namespace YanLib::io
#endif // IO_H
