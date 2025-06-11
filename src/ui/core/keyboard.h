/* clang-format off */
/*
 * @file keyboard.h
 * @date 2025-05-01
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
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <Windows.h>
#include <vector>
#include <string>
#include "sync/rwlock.h"
namespace YanLib::ui::core {
#ifndef KEYBOARDLAYOUT
#define KEYBOARDLAYOUT

    enum class KeyboardLayout : uint32_t {
        Activate = KLF_ACTIVATE,
        SubstituteOk = KLF_SUBSTITUTE_OK,
        ReOrder = KLF_REORDER,
        ReplaceLang = KLF_REPLACELANG,
        NoTellShell = KLF_NOTELLSHELL,
        SetForProcess = KLF_SETFORPROCESS,
        ShiftLock = KLF_SHIFTLOCK,
        Reset = KLF_RESET,
    };

    inline KeyboardLayout operator|(KeyboardLayout a, KeyboardLayout b) {
        return static_cast<KeyboardLayout>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }
#endif
#ifndef KEYBOARDID
#define KEYBOARDID

    enum class KeyboardID : uint32_t {
        AR_SA = 0x00000401,
        BG_BG = 0x00000402,
        CA_ES = 0x00000403,
        ZH_TW = 0x00000404,
        CS_CZ = 0x00000405,
        DA_DK = 0x00000406,
        DE_DE = 0x00000407,
        EL_GR = 0x00000408,
        EN_US = 0x00000409,
        ES_ES_TRADNL = 0x0000040A,
        FI_FI = 0x0000040B,
        FR_FR = 0x0000040C,
        HE_IL = 0x0000040D,
        HU_HU = 0x0000040E,
        IS_IS = 0x0000040F,
        IT_IT = 0x00000410,
        JA_JP = 0x00000411,
        KO_KR = 0x00000412,
        NL_NL = 0x00000413,
        NB_NO = 0x00000414,
        PL_PL = 0x00000415,
        PT_BR = 0x00000416,
        RM_CH = 0x00000417,
        RO_RO = 0x00000418,
        RU_RU = 0x00000419,
        HR_HR = 0x0000041A,
        SK_SK = 0x0000041B,
        SQ_AL = 0x0000041C,
        SV_SE = 0x0000041D,
        TH_TH = 0x0000041E,
        TR_TR = 0x0000041F,
        UR_PK = 0x00000420,
        ID_ID = 0x00000421,
        UK_UA = 0x00000422,
        BE_BY = 0x00000423,
        SL_SI = 0x00000424,
        ET_EE = 0x00000425,
        LV_LV = 0x00000426,
        LT_LT = 0x00000427,
        TG_CYRL_TJ = 0x00000428,
        FA_IR = 0x00000429,
        VI_VN = 0x0000042A,
        HY_AM = 0x0000042B,
        AZ_LATN_AZ = 0x0000042C,
        EU_ES = 0x0000042D,
        HSB_DE = 0x0000042E,
        MK_MK = 0x0000042F,
        ST_ZA = 0x00000430,
        TS_ZA = 0x00000431,
        TN_ZA = 0x00000432,
        VE_ZA = 0x00000433,
        XH_ZA = 0x00000434,
        ZU_ZA = 0x00000435,
        AF_ZA = 0x00000436,
        KA_GE = 0x00000437,
        FO_FO = 0x00000438,
        HI_IN = 0x00000439,
        MT_MT = 0x0000043A,
        SE_NO = 0x0000043B,
        YI_001 = 0x0000043D,
        MS_MY = 0x0000043E,
        KK_KZ = 0x0000043F,
        KY_KG = 0x00000440,
        SW_KE = 0x00000441,
        TK_TM = 0x00000442,
        UZ_LATN_UZ = 0x00000443,
        TT_RU = 0x00000444,
        BN_IN = 0x00000445,
        PA_IN = 0x00000446,
        GU_IN = 0x00000447,
        OR_IN = 0x00000448,
        TA_IN = 0x00000449,
        TE_IN = 0x0000044A,
        KN_IN = 0x0000044B,
        ML_IN = 0x0000044C,
        AS_IN = 0x0000044D,
        MR_IN = 0x0000044E,
        SA_IN = 0x0000044F,
        MN_MN = 0x00000450,
        BO_CN = 0x00000451,
        CY_GB = 0x00000452,
        KM_KH = 0x00000453,
        LO_LA = 0x00000454,
        MY_MM = 0x00000455,
        GL_ES = 0x00000456,
        KOK_IN = 0x00000457,
        SYR_SY = 0x0000045A,
        SI_LK = 0x0000045B,
        CHR_CHER_US = 0x0000045C,
        IU_CANS_CA = 0x0000045D,
        AM_ET = 0x0000045E,
        TZM_ARAB_MA = 0x0000045F,
        KS_ARAB = 0x00000460,
        NE_NP = 0x00000461,
        FY_NL = 0x00000462,
        PS_AF = 0x00000463,
        FIL_PH = 0x00000464,
        DV_MV = 0x00000465,
        FF_NG = 0x00000467,
        HA_LATN_NG = 0x00000468,
        YO_NG = 0x0000046A,
        QUZ_BO = 0x0000046B,
        NSO_ZA = 0x0000046C,
        BA_RU = 0x0000046D,
        LB_LU = 0x0000046E,
        KL_GL = 0x0000046F,
        IG_NG = 0x00000470,
        OM_ET = 0x00000472,
        TI_ET = 0x00000473,
        GN_PY = 0x00000474,
        HAW_US = 0x00000475,
        SO_SO = 0x00000477,
        II_CN = 0x00000478,
        ARN_CL = 0x0000047A,
        MOH_CA = 0x0000047C,
        BR_FR = 0x0000047E,
        UG_CN = 0x00000480,
        MI_NZ = 0x00000481,
        OC_FR = 0x00000482,
        CO_FR = 0x00000483,
        GSW_FR = 0x00000484,
        SAH_RU = 0x00000485,
        RW_RW = 0x00000487,
        WO_SN = 0x00000488,
        PRS_AF = 0x0000048C,
        GD_GB = 0x00000491,
        KU_ARAB_IQ = 0x00000492,
        ZH_CN = 0x00000804,
        DE_DE_PHONE_BOOK = 0x00010407,
    };

    inline std::wstring KbdIDToWString(KeyboardID id) {
        wchar_t buffer[9] = {};
        swprintf_s(buffer, sizeof(buffer) / sizeof(wchar_t), L"%08X", id);
        return buffer;
    }
#endif
#ifndef MODIFIERSKEY
#define MODIFIERSKEY

    enum class ModifiersKey : uint32_t {
        Alt = MOD_ALT,
        Control = MOD_CONTROL,
        Shift = MOD_SHIFT,
        Win = MOD_WIN,
        NoRepeat = MOD_NOREPEAT,
    };

    inline ModifiersKey operator|(ModifiersKey a, ModifiersKey b) {
        return static_cast<ModifiersKey>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum class ModKey6 : uint32_t {
        None = 0,
        Shift = 1,
        Control = 2,
        Alt = 4,
        HanKaKu = 8,
        Reserve1 = 16,
        Reserve2 = 32,
    };

    inline ModKey6 operator|(ModKey6 a, ModKey6 b) {
        return static_cast<ModKey6>(static_cast<uint32_t>(a) |
                                    static_cast<uint32_t>(b));
    }
#endif
#ifndef VIRTUALKEY
#define VIRTUALKEY

    enum class VirtualKey : uint32_t {
        LButton = 0x01,
        RButton = 0x02,
        Cancel = 0x03,
        MButton = 0x04,
        XButton1 = 0x05,
        XButton2 = 0x06,
        Back = 0x08,
        Tab = 0x09,
        Clear = 0x0C,
        Return = 0x0D,
        Shift = 0x10,
        Control = 0x11,
        Menu = 0x12,
        Pause = 0x13,
        Capital = 0x14,
        Kana = 0x15,
        Hangul = 0x15,
        ImeOn = 0x16,
        Junja = 0x17,
        Final = 0x18,
        Hanja = 0x19,
        Kanji = 0x19,
        ImeOff = 0x1A,
        Escape = 0x1B,
        Convert = 0x1C,
        NonConvert = 0x1D,
        Accept = 0x1E,
        ModeChange = 0x1F,
        Space = 0x20,
        Prior = 0x21,
        Next = 0x22,
        End = 0x23,
        Home = 0x24,
        Left = 0x25,
        Up = 0x26,
        Right = 0x27,
        Down = 0x28,
        Select = 0x29,
        Print = 0x2A,
        Execute = 0x2B,
        Snapshot = 0x2C,
        Insert = 0x2D,
        Delete = 0x2E,
        Help = 0x2F,
        Digit0 = 0x30,
        Digit1 = 0x31,
        Digit2 = 0x32,
        Digit3 = 0x33,
        Digit4 = 0x34,
        Digit5 = 0x35,
        Digit6 = 0x36,
        Digit7 = 0x37,
        Digit8 = 0x38,
        Digit9 = 0x39,
        A = 0x41,
        B = 0x42,
        C = 0x43,
        D = 0x44,
        E = 0x45,
        F = 0x46,
        G = 0x47,
        H = 0x48,
        I = 0x49,
        J = 0x4A,
        K = 0x4B,
        L = 0x4C,
        M = 0x4D,
        N = 0x4E,
        O = 0x4F,
        P = 0x50,
        Q = 0x51,
        R = 0x52,
        S = 0x53,
        T = 0x54,
        U = 0x55,
        V = 0x56,
        W = 0x57,
        X = 0x58,
        Y = 0x59,
        Z = 0x5A,
        LWin = 0x5B,
        RWin = 0x5C,
        Apps = 0x5D,
        Sleep = 0x5F,
        Numpad0 = 0x60,
        Numpad1 = 0x61,
        Numpad2 = 0x62,
        Numpad3 = 0x63,
        Numpad4 = 0x64,
        Numpad5 = 0x65,
        Numpad6 = 0x66,
        Numpad7 = 0x67,
        Numpad8 = 0x68,
        Numpad9 = 0x69,
        Multiply = 0x6A,
        Add = 0x6B,
        Separator = 0x6C,
        Subtract = 0x6D,
        Decimal = 0x6E,
        Divide = 0x6F,
        F1 = 0x70,
        F2 = 0x71,
        F3 = 0x72,
        F4 = 0x73,
        F5 = 0x74,
        F6 = 0x75,
        F7 = 0x76,
        F8 = 0x77,
        F9 = 0x78,
        F10 = 0x79,
        F11 = 0x7A,
        F12 = 0x7B,
        F13 = 0x7C,
        F14 = 0x7D,
        F15 = 0x7E,
        F16 = 0x7F,
        F17 = 0x80,
        F18 = 0x81,
        F19 = 0x82,
        F20 = 0x83,
        F21 = 0x84,
        F22 = 0x85,
        F23 = 0x86,
        F24 = 0x87,
        NumLock = 0x90,
        Scroll = 0x91,
        LShift = 0xA0,
        RShift = 0xA1,
        LControl = 0xA2,
        RControl = 0xA3,
        LMenu = 0xA4,
        RMenu = 0xA5,
        BrowserBack = 0xA6,
        BrowserForward = 0xA7,
        BrowserRefresh = 0xA8,
        BrowserStop = 0xA9,
        BrowserSearch = 0xAA,
        BrowserFavorites = 0xAB,
        BrowserHome = 0xAC,
        VolumeMute = 0xAD,
        VolumeDown = 0xAE,
        VolumeUp = 0xAF,
        MediaNextTrack = 0xB0,
        MediaPrevTrack = 0xB1,
        MediaStop = 0xB2,
        MediaPlayPause = 0xB3,
        LaunchMail = 0xB4,
        LaunchMediaSelect = 0xB5,
        LaunchApp1 = 0xB6,
        LaunchApp2 = 0xB7,
        Oem1 = 0xBA,
        OemPlus = 0xBB,
        OemComma = 0xBC,
        OemMinus = 0xBD,
        OemPeriod = 0xBE,
        Oem2 = 0xBF,
        Oem3 = 0xC0,
        Oem4 = 0xDB,
        Oem5 = 0xDC,
        Oem6 = 0xDD,
        Oem7 = 0xDE,
        Oem8 = 0xDF,
        Oem102 = 0xE2,
        ProcessKey = 0xE5,
        Packet = 0xE7,
        Attn = 0xF6,
        CrSel = 0xF7,
        ExSel = 0xF8,
        ErEof = 0xF9,
        Play = 0xFA,
        Zoom = 0xFB,
        Pa1 = 0xFD,
        OemClear = 0xFE,
    };

    inline VirtualKey operator|(VirtualKey a, VirtualKey b) {
        return static_cast<VirtualKey>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef KEYEVENT
#define KEYEVENT

    enum class KeyEvent : uint32_t {
        ExtendedKey = KEYEVENTF_EXTENDEDKEY,
        KeyUp = KEYEVENTF_KEYUP,
        KeyDown = 0,
        Unicode = KEYEVENTF_UNICODE,
        ScanCode = KEYEVENTF_SCANCODE,
    };

    inline KeyEvent operator|(KeyEvent a, KeyEvent b) {
        return static_cast<KeyEvent>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
#ifndef MAPTYPE
#define MAPTYPE

    enum class MapType : uint32_t {
        VkToVsc = MAPVK_VK_TO_VSC,
        VscToVk = MAPVK_VSC_TO_VK,
        VkToChar = MAPVK_VK_TO_CHAR,
        VscToVkEx = MAPVK_VSC_TO_VK_EX,
        VkToVscEx = MAPVK_VK_TO_VSC_EX,
    };
#endif
    class keyboard {
    private:
        std::vector<HKL> layout_handles = {};
        std::vector<std::pair<HWND, int32_t>> hotkeys = {};
        sync::rwlock layout_rwlock = {};
        sync::rwlock hotkey_rwlock = {};
        uint32_t error_code = 0;

    public:
        keyboard(const keyboard &other) = delete;

        keyboard(keyboard &&other) = delete;

        keyboard &operator=(const keyboard &other) = delete;

        keyboard &operator=(keyboard &&other) = delete;

        keyboard() = default;

        ~keyboard();

        HKL load_layout(KeyboardID id = KeyboardID::ZH_CN,
                        KeyboardLayout layout = KeyboardLayout::Activate |
                                KeyboardLayout::SubstituteOk);

        bool register_hot_key(HWND window_handle,
                              int32_t id,
                              ModifiersKey mod_key,
                              VirtualKey vk);

        bool unregister_hot_key(HWND window_handle, int32_t id);

        HKL activate_layout(HKL layout_handle,
                            KeyboardLayout layout = KeyboardLayout::Activate |
                                    KeyboardLayout::SubstituteOk);

        bool unload_layout(HKL layout_handle);

        HKL get_layout(uint32_t tid);

        int32_t get_layout_list(std::vector<HKL> &layout_handle);

        bool get_layout_name(char *name);

        bool get_layout_name(wchar_t *name);

        bool get_state(uint8_t *key_state);

        bool set_state(uint8_t *key_state);

        int32_t get_type(int32_t type_flag);

        int32_t get_key_name(int32_t param, std::string &text);

        int32_t get_key_name(int32_t param, std::wstring &text);

        int16_t get_key_state(VirtualKey vk);

        uint16_t get_key_state_lparam(LPARAM lparam);

        uint16_t get_key_state_wparam(WPARAM wparam);

        int16_t get_async_key_state(VirtualKey vk);

        void send_event(VirtualKey vk,
                        uint8_t scan = 0,
                        KeyEvent kv = KeyEvent::ExtendedKey | KeyEvent::KeyDown,
                        uintptr_t extra_info = 0);

        uint32_t send_input(std::vector<INPUT> &input);

        uint8_t virtual_key_to_scan_code(VirtualKey vk,
                                         bool is_extended_key = false);

        VirtualKey scan_code_to_virtual_key(uint8_t scan_code,
                                            bool is_extended_key = false);

        uint32_t map_virtual_key(uint32_t code, MapType map_type);

        uint32_t
        map_virtual_key(uint32_t code, MapType map_type, HKL layout_handle);

        uint32_t oem_key_scan(uint16_t oem_char);

        bool vk_key_scan(char ch, ModKey6 *mod_key, VirtualKey *vk);

        bool vk_key_scan(wchar_t ch, ModKey6 *mod_key, VirtualKey *vk);

        bool vk_key_scan(char ch,
                         HKL layout_handle,
                         ModKey6 *mod_key,
                         VirtualKey *vk);

        bool vk_key_scan(wchar_t ch,
                         HKL layout_handle,
                         ModKey6 *mod_key,
                         VirtualKey *vk);

        HWND get_focus();

        HWND set_focus(HWND window_handle);

        int32_t to_ascii(VirtualKey vk,
                         uint32_t scan_code,
                         const uint8_t *key_state,
                         uint8_t *ch1,
                         uint8_t *ch2,
                         bool menu_active = false);

        int32_t to_ascii(VirtualKey vk,
                         HKL layout_handle,
                         uint32_t scan_code,
                         const uint8_t *key_state,
                         uint8_t *ch1,
                         uint8_t *ch2,
                         bool menu_active = false);

        int32_t to_unicode(VirtualKey vk,
                           uint32_t scan_code,
                           const uint8_t *key_state,
                           std::wstring &buf,
                           bool menu_active = false);

        int32_t to_unicode(VirtualKey vk,
                           HKL layout_handle,
                           uint32_t scan_code,
                           const uint8_t *key_state,
                           std::wstring &buf,
                           bool menu_active = false);

        bool is_any_input();

        bool block_input();

        bool resume_input();

        bool attach_input(uint32_t tid1, uint32_t tid2);

        bool detach_input(uint32_t tid1, uint32_t tid2);

        uint32_t wait_for_input_idle(HANDLE proc_handle,
                                     uint32_t milli_seconds);

        LRESULT default_raw_input_proc(RAWINPUT **raw_input,
                                       int32_t input,
                                       uint32_t header_size);

        uint16_t get_raw_input_code_wparam(WPARAM wparam);

        uint32_t get_raw_input_buffer(RAWINPUT *buf,
                                      uint32_t *size,
                                      uint32_t header_size);

        uint32_t get_raw_input_data(HRAWINPUT raw_input,
                                    uint32_t command,
                                    void *buf,
                                    uint32_t *size,
                                    uint32_t header_size);

        uint32_t get_raw_input_device_info(HANDLE device_handle,
                                           uint32_t command,
                                           void *buf,
                                           uint32_t *size);

        uint32_t
        get_raw_input_device_list(RAWINPUTDEVICELIST raw_input_device_list[],
                                  uint32_t *real_num);

        uint32_t
        get_registered_raw_input_devices(RAWINPUTDEVICE raw_input_devices[],
                                         uint32_t *real_num);

        RAWINPUT *next_raw_input_block(RAWINPUT *raw_input);

        bool
        register_raw_input_devices(const RAWINPUTDEVICE raw_input_devices[],
                                   uint32_t num);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // KEYBOARD_H
