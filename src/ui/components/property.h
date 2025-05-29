//
// Created by forkernel on 2025/5/29.
//

#ifndef PROPERTY_H
#define PROPERTY_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <prsht.h>
#include <CommCtrl.h>
#include <commoncontrols.h>
#include <cstdint>
#include <string>
#include <vector>
#include "helper/convert.h"
#pragma comment(lib, "Comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
namespace YanLib::components {
#ifndef PROPERTYHEADERFLAG
#define PROPERTYHEADERFLAG
    enum class PropertyHeaderFlag : uint32_t {
        Default = PSH_DEFAULT,
        PropTitle = PSH_PROPTITLE,
        UseHIcon = PSH_USEHICON,
        UseIconId = PSH_USEICONID,
        PropSheetPage = PSH_PROPSHEETPAGE,
        WizardHasFinish = PSH_WIZARDHASFINISH,
        Wizard = PSH_WIZARD,
        UsePStartPage = PSH_USEPSTARTPAGE,
        NoApplyNow = PSH_NOAPPLYNOW,
        UseCallback = PSH_USECALLBACK,
        HasHelp = PSH_HASHELP,
        Modeless = PSH_MODELESS,
        RtlReading = PSH_RTLREADING,
        WizardContextHelp = PSH_WIZARDCONTEXTHELP,
        Wizard97 = PSH_WIZARD97,
        Watermark = PSH_WATERMARK,
        UseHbmWatermark = PSH_USEHBMWATERMARK,
        UseHplWatermark = PSH_USEHPLWATERMARK,
        StretchWatermark = PSH_STRETCHWATERMARK,
        Header = PSH_HEADER,
        UseHbmHeader = PSH_USEHBMHEADER,
        UsePageLang = PSH_USEPAGELANG,
        WizardLite = PSH_WIZARD_LITE,
        NoContextHelp = PSH_NOCONTEXTHELP,
        AeroWizard = PSH_AEROWIZARD,
        Resizable = PSH_RESIZABLE,
        HeaderBitmap = PSH_HEADERBITMAP,
        NoMargin = PSH_NOMARGIN
    };
    inline PropertyHeaderFlag operator|(PropertyHeaderFlag a,
                                        PropertyHeaderFlag b) {
        return static_cast<PropertyHeaderFlag>(static_cast<uint32_t>(a) |
                                               static_cast<uint32_t>(b));
    }
#endif
#ifndef PROPERTYPAGEFLAG
#define PROPERTYPAGEFLAG
    enum class PropertyPageFlag : uint32_t {
        Default = PSP_DEFAULT,
        DialogInDirect = PSP_DLGINDIRECT,
        UseHIcon = PSP_USEHICON,
        UseIconId = PSP_USEICONID,
        UseTitle = PSP_USETITLE,
        RtlReading = PSP_RTLREADING,
        HasHelp = PSP_HASHELP,
        UseRefParent = PSP_USEREFPARENT,
        UseCallback = PSP_USECALLBACK,
        Premature = PSP_PREMATURE,
        HideHeader = PSP_HIDEHEADER,
        UseHeaderTitle = PSP_USEHEADERTITLE,
        UseHeaderSubTitle = PSP_USEHEADERSUBTITLE,
        UseFusionContext = PSP_USEFUSIONCONTEXT,
    };
    inline PropertyPageFlag operator|(PropertyPageFlag a, PropertyPageFlag b) {
        return static_cast<PropertyPageFlag>(static_cast<uint32_t>(a) |
                                             static_cast<uint32_t>(b));
    }
#endif
#ifndef PROPERTYBUTTON
#define PROPERTYBUTTON
    enum class PropertyButton : uint32_t {
        Back = PSWIZB_BACK,
        Next = PSWIZB_NEXT,
        Finish = PSWIZB_FINISH,
        Cancel = PSWIZB_CANCEL,
        Show = PSWIZB_SHOW,
        Restore = PSWIZB_RESTORE,
        DisabledFinish = PSWIZB_DISABLEDFINISH,
    };
    inline PropertyButton operator|(PropertyButton a, PropertyButton b) {
        return static_cast<PropertyButton>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }
#endif
#ifndef PROPERTYMESSAGE
#define PROPERTYMESSAGE
    enum class PropertyMessage : uint32_t {
        AddPage = PSM_ADDPAGE,
        Apply = PSM_APPLY,
        CancelToClose = PSM_CANCELTOCLOSE,
        Changed = PSM_CHANGED,
        EnableWizButtons = PSM_ENABLEWIZBUTTONS,
        GetCurrentPageHwnd = PSM_GETCURRENTPAGEHWND,
        GetResult = PSM_GETRESULT,
        GetTabControl = PSM_GETTABCONTROL,
        HwndToIndex = PSM_HWNDTOINDEX,
        IdToIndex = PSM_IDTOINDEX,
        IndexToHwnd = PSM_INDEXTOHWND,
        IndexToId = PSM_INDEXTOID,
        IndexToPage = PSM_INDEXTOPAGE,
        InsertPage = PSM_INSERTPAGE,
        IsDialogMsg = PSM_ISDIALOGMESSAGE,
        PageToIndex = PSM_PAGETOINDEX,
        PressButton = PSM_PRESSBUTTON,
        QuerySiblings = PSM_QUERYSIBLINGS,
        RebootSystem = PSM_REBOOTSYSTEM,
        RecalcPageSizes = PSM_RECALCPAGESIZES,
        RemovePage = PSM_REMOVEPAGE,
        RestartWindows = PSM_RESTARTWINDOWS,
        SetButtonText = PSM_SETBUTTONTEXT,
        SetCurSel = PSM_SETCURSEL,
        SetCurSelId = PSM_SETCURSELID,
        SetFinishText = PSM_SETFINISHTEXT,
        SetHeaderSubtitle = PSM_SETHEADERSUBTITLE,
        SetHeaderTitle = PSM_SETHEADERTITLE,
        SetNextText = PSM_SETNEXTTEXT,
        SetTitle = PSM_SETTITLE,
        SetWizButtons = PSM_SETWIZBUTTONS,
        ShowWizButtons = PSM_SHOWWIZBUTTONS,
        Unchanged = PSM_UNCHANGED
    };
#endif
#ifndef PROPERTYNOTIFY
#define PROPERTYNOTIFY
    enum class PropertyNotify : uint32_t {
        Apply = PSN_APPLY,
        GetObj = PSN_GETOBJECT,
        Help = PSN_HELP,
        KillActive = PSN_KILLACTIVE,
        QueryCancel = PSN_QUERYCANCEL,
        QueryInitialFocus = PSN_QUERYINITIALFOCUS,
        Reset = PSN_RESET,
        SetActive = PSN_SETACTIVE,
        TranslateAccel = PSN_TRANSLATEACCELERATOR,
        WizBack = PSN_WIZBACK,
        WizFinish = PSN_WIZFINISH,
        WizNext = PSN_WIZNEXT,
    };
#endif
    class property {
    public:
        property(const property &other) = delete;

        property(property &&other) = delete;

        property &operator=(const property &other) = delete;

        property &operator=(property &&other) = delete;

        property() = default;

        ~property() = default;


        static PROPSHEETHEADERA make_header(
                const char *caption /* L"系统设置" */,
                HWND parent_window_handle,
                HINSTANCE hinstance_handle,
                std::vector<PROPSHEETPAGEA> &prop_sheet_page,
                PFNPROPSHEETCALLBACK callback = nullptr,
                PropertyHeaderFlag flag = PropertyHeaderFlag::PropSheetPage |
                        PropertyHeaderFlag::NoApplyNow,
                HICON icon_handle = nullptr,
                HBITMAP water_mark_handle = nullptr,
                HPALETTE palette_handle = nullptr,
                HBITMAP header_handle = nullptr);

        static PROPSHEETHEADERW make_header(
                const wchar_t *caption /* L"系统设置" */,
                HWND parent_window_handle,
                HINSTANCE hinstance_handle,
                std::vector<PROPSHEETPAGEW> &prop_sheet_page,
                PFNPROPSHEETCALLBACK callback = nullptr,
                PropertyHeaderFlag flag = PropertyHeaderFlag::PropSheetPage |
                        PropertyHeaderFlag::NoApplyNow,
                HICON icon_handle = nullptr,
                HBITMAP water_mark_handle = nullptr,
                HPALETTE palette_handle = nullptr,
                HBITMAP header_handle = nullptr);

        static HWND create(PROPSHEETHEADERA *header);

        static HWND create(PROPSHEETHEADERW *header);

        static PROPSHEETPAGEA
        make_page(const char *title,
                  HINSTANCE hinstance_handle,
                  const char *templates,
                  DLGPROC dialog_func,
                  LPARAM dialog_param = 0,
                  LPFNPSPCALLBACKA callback = nullptr,
                  PropertyPageFlag flag = PropertyPageFlag::UseTitle,
                  const char *header_title = nullptr,
                  const char *header_subtitle = nullptr,
                  HICON icon_handle = nullptr,
                  HBITMAP header_handle = nullptr,
                  uint32_t *ref_parent = nullptr,
                  HANDLE active_context_handle = nullptr);

        static PROPSHEETPAGEW
        make_page(const wchar_t *title,
                  HINSTANCE hinstance_handle,
                  const wchar_t *templates,
                  DLGPROC dialog_func,
                  LPARAM dialog_param = 0,
                  LPFNPSPCALLBACKW callback = nullptr,
                  PropertyPageFlag flag = PropertyPageFlag::UseTitle,
                  const wchar_t *header_title = nullptr,
                  const wchar_t *header_subtitle = nullptr,
                  HICON icon_handle = nullptr,
                  HBITMAP header_handle = nullptr,
                  uint32_t *ref_parent = nullptr,
                  HANDLE active_context_handle = nullptr);

        static HPROPSHEETPAGE create_page(PROPSHEETPAGEA *page);

        static HPROPSHEETPAGE create_page(PROPSHEETPAGEW *page);

        static bool destroy_page(HPROPSHEETPAGE page_handle);

        static bool add_page(HWND property_handle, HPROPSHEETPAGE page_handle);

        static bool insert_page(HWND property_handle,
                                int32_t index,
                                HPROPSHEETPAGE page_handle);

        static void remove_page(HWND property_handle,
                                int32_t index,
                                HPROPSHEETPAGE page_handle);

        static void change_page(HWND property_handle,
                                HPROPSHEETPAGE page_handle);

        static void unchange_page(HWND property_handle,
                                  HPROPSHEETPAGE page_handle);

        static int32_t get_page_index(HWND property_handle,
                                      HPROPSHEETPAGE page_handle);

        static int32_t get_page_index2(HWND property_handle,
                                       HPROPSHEETPAGE page_handle);

        static int32_t get_page_index(HWND property_handle, int32_t res_id);

        static bool active_curr_page(HWND property_handle,
                                     HPROPSHEETPAGE page_handle,
                                     uint32_t index);

        static bool active_curr_page(HWND property_handle, int32_t res_id);

        static HPROPSHEETPAGE get_page_handle(HWND property_handle,
                                              int32_t index);

        static HPROPSHEETPAGE get_page_handle2(HWND property_handle,
                                               int32_t index);

        static int32_t get_page_res_id(HWND property_handle, int32_t index);

        static HWND get_curr_page_handle(HWND property_handle);

        static int32_t get_result(HWND property_handle);

        static HWND get_tab_control(HWND property_handle);

        static void
        set_button_text(HWND property_handle,
                        PropertyButton button,
                        std::string &text,
                        helper::CodePage code_page = helper::CodePage::GB2312);

        static void set_button_text(HWND property_handle,
                                    PropertyButton button,
                                    std::wstring &text);

        static void set_finish_button_text(
                HWND property_handle,
                std::string &text,
                helper::CodePage code_page = helper::CodePage::GB2312);

        static void set_finish_button_text(HWND property_handle,
                                           std::wstring &text);

        static void set_next_button_text(
                HWND property_handle,
                std::string &text,
                helper::CodePage code_page = helper::CodePage::GB2312);

        static void set_next_button_text(HWND property_handle,
                                         std::wstring &text);

        static void set_header_sub_title(
                HWND property_handle,
                int32_t index,
                std::string &text,
                helper::CodePage code_page = helper::CodePage::GB2312);

        static void set_header_sub_title(HWND property_handle,
                                         int32_t index,
                                         std::wstring &text);

        static void
        set_header_title(HWND property_handle,
                         int32_t index,
                         std::string &text,
                         helper::CodePage code_page = helper::CodePage::GB2312);

        static void set_header_title(HWND property_handle,
                                     int32_t index,
                                     std::wstring &text);

        static void
        set_title(HWND property_handle,
                  PropertyHeaderFlag flag,
                  std::string &text,
                  helper::CodePage code_page = helper::CodePage::GB2312);

        static void set_title(HWND property_handle,
                              PropertyHeaderFlag flag,
                              std::wstring &text);

        static void set_wiz_buttons(HWND property_handle,
                                    PropertyButton button);

        static void enable_wiz_buttons(HWND property_handle,
                                       PropertyButton button,
                                       PropertyButton mask);

        static void show_wiz_buttons(HWND property_handle,
                                     PropertyButton button,
                                     PropertyButton mask);

        static bool apply(HWND property_handle);

        static void cancel_to_close(HWND property_handle);

        static bool is_dialog_message(HWND property_handle, MSG *message);

        static void press_button(HWND property_handle, PropertyButton button);

        static bool
        query_siblings(HWND property_handle, WPARAM wparam, LPARAM lparam);

        static void reboot_system(HWND property_handle);

        static void restart_windows(HWND property_handle);

        static bool recalc_page_sizes(HWND property_handle);
    };
} // namespace YanLib::components
#endif // PROPERTY_H
