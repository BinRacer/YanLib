//
// Created by forkernel on 2025/5/27.
//

#ifndef LISTVIEW_H
#define LISTVIEW_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <cstdint>
#include <string>
#include <vector>
#include "helper/convert.h"
#pragma comment(lib, "Comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
namespace YanLib::components {
#ifndef WINDOWSTYLE
#define WINDOWSTYLE

    enum class WindowStyle : uint32_t {
        Overlapped = WS_OVERLAPPED,
        Popup = WS_POPUP,
        Child = WS_CHILD,
        Minimize = WS_MINIMIZE,
        Visible = WS_VISIBLE,
        Disabled = WS_DISABLED,
        ClipSiblings = WS_CLIPSIBLINGS,
        ClipChildren = WS_CLIPCHILDREN,
        Maximize = WS_MAXIMIZE,
        Caption = WS_CAPTION,
        Border = WS_BORDER,
        DialogFrame = WS_DLGFRAME,
        VScroll = WS_VSCROLL,
        HScroll = WS_HSCROLL,
        SysMenu = WS_SYSMENU,
        ThickFrame = WS_THICKFRAME,
        Group = WS_GROUP,
        TabStop = WS_TABSTOP,
        MinimizeBox = WS_MINIMIZEBOX,
        MaximizeBox = WS_MAXIMIZEBOX,
        Tiled = WS_TILED,
        Iconic = WS_ICONIC,
        SizeBox = WS_SIZEBOX,
        TiledWindow = WS_TILEDWINDOW,
        OverlappedWindow = WS_OVERLAPPEDWINDOW,
        PopupWindow = WS_POPUPWINDOW,
        ChildWindow = WS_CHILDWINDOW,
    };

    inline WindowStyle operator|(WindowStyle a, WindowStyle b) {
        return static_cast<WindowStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef LISTVIEWSTYLE
#define LISTVIEWSTYLE
    enum class ListViewStyle : uint32_t {
        Icon = LVS_ICON,
        Report = LVS_REPORT,
        SmallIcon = LVS_SMALLICON,
        List = LVS_LIST,
        TypeMask = LVS_TYPEMASK,
        SingleSel = LVS_SINGLESEL,
        ShowSelAlways = LVS_SHOWSELALWAYS,
        SortAscending = LVS_SORTASCENDING,
        SortDescending = LVS_SORTDESCENDING,
        ShareImageLists = LVS_SHAREIMAGELISTS,
        NoLabelWrap = LVS_NOLABELWRAP,
        AutoArrange = LVS_AUTOARRANGE,
        EditLabels = LVS_EDITLABELS,
        OwnerData = LVS_OWNERDATA,
        NoScroll = LVS_NOSCROLL,
        TypeStyleMask = LVS_TYPESTYLEMASK,
        AlignTop = LVS_ALIGNTOP,
        AlignLeft = LVS_ALIGNLEFT,
        AlignMask = LVS_ALIGNMASK,
        OwnerDrawFixed = LVS_OWNERDRAWFIXED,
        NoColumnHeader = LVS_NOCOLUMNHEADER,
        NoSortHeader = LVS_NOSORTHEADER
    };
    inline ListViewStyle operator|(ListViewStyle a, ListViewStyle b) {
        return static_cast<ListViewStyle>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef LISTVIEWEXTENDSTYLE
#define LISTVIEWEXTENDSTYLE
    enum class ListViewExtendStyle : uint32_t {
        GridLines = LVS_EX_GRIDLINES,
        SubItemImages = LVS_EX_SUBITEMIMAGES,
        CheckBoxes = LVS_EX_CHECKBOXES,
        TrackSelect = LVS_EX_TRACKSELECT,
        HeaderDragDrop = LVS_EX_HEADERDRAGDROP,
        FullRowSelect = LVS_EX_FULLROWSELECT,
        OneClickActivate = LVS_EX_ONECLICKACTIVATE,
        TwoClickActivate = LVS_EX_TWOCLICKACTIVATE,
        FlatScrollBar = LVS_EX_FLATSB,
        Regional = LVS_EX_REGIONAL,
        InfoTip = LVS_EX_INFOTIP,
        UnderlineHot = LVS_EX_UNDERLINEHOT,
        UnderlineCold = LVS_EX_UNDERLINECOLD,
        MultiWorkAreas = LVS_EX_MULTIWORKAREAS,
        LabelTip = LVS_EX_LABELTIP,
        BorderSelect = LVS_EX_BORDERSELECT,
        DoubleBuffer = LVS_EX_DOUBLEBUFFER,
        HideLabels = LVS_EX_HIDELABELS,
        SingleRow = LVS_EX_SINGLEROW,
        SnapToGrid = LVS_EX_SNAPTOGRID,
        SimpleSelect = LVS_EX_SIMPLESELECT,
        JustifyColumns = LVS_EX_JUSTIFYCOLUMNS,
        TransparentBackground = LVS_EX_TRANSPARENTBKGND,
        TransparentShadowText = LVS_EX_TRANSPARENTSHADOWTEXT,
        AutoAutoArrange = LVS_EX_AUTOAUTOARRANGE,
        HeaderInAllViews = LVS_EX_HEADERINALLVIEWS,
        AutoCheckSelect = LVS_EX_AUTOCHECKSELECT,
        AutoSizeColumns = LVS_EX_AUTOSIZECOLUMNS,
        ColumnSnapPoints = LVS_EX_COLUMNSNAPPOINTS,
        ColumnOverflow = LVS_EX_COLUMNOVERFLOW
    };
    inline ListViewExtendStyle operator|(ListViewExtendStyle a,
                                         ListViewExtendStyle b) {
        return static_cast<ListViewExtendStyle>(static_cast<uint32_t>(a) |
                                                static_cast<uint32_t>(b));
    }
#endif
#ifndef LVALIGNSTYLE
#define LVALIGNSTYLE
    enum class LVAlignStyle : uint32_t {
        Default = LVA_DEFAULT,
        Left = LVA_ALIGNLEFT,
        Top = LVA_ALIGNTOP,
        SnapToGrid = LVA_SNAPTOGRID,
    };
#endif
#ifndef LVITEMSTATE
#define LVITEMSTATE
    enum class LVItemState : uint32_t {
        Focused = LVIS_FOCUSED,
        Selected = LVIS_SELECTED,
        Cut = LVIS_CUT,
        DropHilited = LVIS_DROPHILITED,
        Glow = LVIS_GLOW,
        Activating = LVIS_ACTIVATING,
        OverlayMask = LVIS_OVERLAYMASK,
        StateImageMask = LVIS_STATEIMAGEMASK,
    };
    inline LVItemState operator|(LVItemState a, LVItemState b) {
        return static_cast<LVItemState>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef GROUPRECTTYPE
#define GROUPRECTTYPE
    enum class GroupRectType : uint32_t {
        Group = LVGGR_GROUP,
        Header = LVGGR_HEADER,
        Label = LVGGR_LABEL,
        SubSetLink = LVGGR_SUBSETLINK,
    };
#endif
#ifndef GROUPSTATE
#define GROUPSTATE
    enum class GroupState : uint32_t {
        Normal = LVGS_NORMAL,
        Collapsed = LVGS_COLLAPSED,
        Hidden = LVGS_HIDDEN,
        NoHeader = LVGS_NOHEADER,
        Collapsible = LVGS_COLLAPSIBLE,
        Focused = LVGS_FOCUSED,
        Selected = LVGS_SELECTED,
        Subseted = LVGS_SUBSETED,
        SubsetLinkFocused = LVGS_SUBSETLINKFOCUSED,
    };
    inline GroupState operator|(GroupState a, GroupState b) {
        return static_cast<GroupState>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef LVILSTYLE
#define LVILSTYLE
    enum class LVILStyle : int32_t {
        Normal = LVSIL_NORMAL,
        Small = LVSIL_SMALL,
        State = LVSIL_STATE,
        GroupHeader = LVSIL_GROUPHEADER,
    };
#endif
#ifndef LVICFLAG
#define LVICFLAG
    enum class LVICFlag : uint32_t {
        NoInvalidateAll = LVSICF_NOINVALIDATEALL,
        NoScroll = LVSICF_NOSCROLL,
    };
    inline LVICFlag operator|(LVICFlag a, LVICFlag b) {
        return static_cast<LVICFlag>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
#ifndef LVIRCODE
#define LVIRCODE
    enum class LVIRCode : int32_t {
        Bounds = LVIR_BOUNDS,
        Icon = LVIR_ICON,
        Label = LVIR_LABEL,
        SelectBounds = LVIR_SELECTBOUNDS,
    };
#endif
#ifndef LVNIFLAG
#define LVNIFLAG
    enum class LVNIFlag : uint32_t {
        All = LVNI_ALL,
        Focused = LVNI_FOCUSED,
        Selected = LVNI_SELECTED,
        Cut = LVNI_CUT,
        DropHilited = LVNI_DROPHILITED,
        StateMask = LVNI_STATEMASK,
        VisibleOrder = LVNI_VISIBLEORDER,
        Previous = LVNI_PREVIOUS,
        VisibleOnly = LVNI_VISIBLEONLY,
        SameGroupOnly = LVNI_SAMEGROUPONLY,
        Above = LVNI_ABOVE,
        Below = LVNI_BELOW,
        ToLeft = LVNI_TOLEFT,
        ToRight = LVNI_TORIGHT,
        DirectionMask = LVNI_DIRECTIONMASK,
    };
    inline LVNIFlag operator|(LVNIFlag a, LVNIFlag b) {
        return static_cast<LVNIFlag>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
    class listview {
    private:
        uint32_t error_code = 0;

    public:
        listview(const listview &other) = delete;

        listview(listview &&other) = delete;

        listview &operator=(const listview &other) = delete;

        listview &operator=(listview &&other) = delete;

        listview() = default;

        ~listview() = default;

        HWND create(uintptr_t listview_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ListViewStyle style = ListViewStyle::Report |
                            ListViewStyle::EditLabels,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND edit_label(HWND listview_handle, int32_t index);

        void cancel_edit_label(HWND listview_handle);

        bool delete_item(HWND listview_handle, int32_t index);

        bool delete_column(HWND listview_handle, int32_t column_index);

        bool delete_all_items(HWND listview_handle);

        HIMAGELIST
        create_drag_image(HWND listview_handle, POINT *left_top, int32_t index);

        // std::pair<width, height>
        std::pair<uint32_t, uint32_t>
        approximate_view_rect(HWND listview_handle,
                              int32_t width = -1,
                              int32_t height = -1,
                              int32_t count = -1);

        bool arrange(HWND listview_handle,
                     LVAlignStyle style = LVAlignStyle::Default);

        int32_t enable_group_view(HWND listview_handle);

        int32_t disable_group_view(HWND listview_handle);

        bool is_group_view_enabled(HWND listview_handle);

        bool ensure_visible(HWND listview_handle,
                            int32_t index,
                            bool entire_visible = false);

        int32_t find_item(HWND listview_handle,
                          const LVFINDINFOW *find_info,
                          int32_t index = -1);

        COLORREF get_background_color(HWND listview_handle);

        bool set_background_color(HWND listview_handle, COLORREF color);

        bool get_background_image(HWND listview_handle, LVBKIMAGEW *image);

        bool set_background_image(HWND listview_handle, LVBKIMAGEW *image);

        LVItemState get_callback_mask(HWND listview_handle);

        bool set_callback_mask(HWND listview_handle, LVItemState mask);

        bool is_checked(HWND listview_handle, uint32_t index);

        void set_check(HWND listview_handle, uint32_t index);

        void unset_check(HWND listview_handle, uint32_t index);

        bool get_column(HWND listview_handle,
                        LVCOLUMNW *column,
                        int32_t column_index);

        bool set_column(HWND listview_handle,
                        LVCOLUMNW *column,
                        int32_t column_index);

        bool get_column_order(HWND listview_handle,
                              std::vector<int32_t> &order);

        void set_column_order(HWND listview_handle,
                              std::vector<int32_t> &order);

        int32_t get_column_width(HWND listview_handle, int32_t column_index);

        bool set_column_width(HWND listview_handle,
                              int32_t column_index,
                              int32_t width = LVSCW_AUTOSIZE_USEHEADER);

        int32_t get_count_per_page(HWND listview_handle);

        HWND get_edit_control(HWND listview_handle);

        bool
        get_empty_text(HWND listview_handle,
                       std::string &text,
                       helper::CodePage code_page = helper::CodePage::GB2312);

        bool get_empty_text(HWND listview_handle, std::wstring &text);

        ListViewExtendStyle get_extended_style(HWND listview_handle);

        void set_extended_style(HWND listview_handle,
                                ListViewExtendStyle style);

        void set_extended_style(HWND listview_handle,
                                ListViewExtendStyle style,
                                ListViewExtendStyle mask /* 0 */);

        int32_t get_focused_group(HWND listview_handle);

        void get_footer_info(HWND listview_handle, LVFOOTERINFO *footer_info);

        bool get_footer_item(HWND listview_handle,
                             LVFOOTERITEM *footer_item,
                             uint32_t index);

        bool
        get_footer_item_rect(HWND listview_handle, RECT *rect, uint32_t index);

        bool get_footer_rect(HWND listview_handle, RECT *rect);

        int32_t get_group_count(HWND listview_handle);

        HIMAGELIST get_group_header_image_list(HWND listview_handle);

        HIMAGELIST set_group_header_image_list(HWND listview_handle,
                                               HIMAGELIST image_list_handle);

        int32_t
        get_group_info(HWND listview_handle, LVGROUP *group, int32_t index);

        int32_t
        set_group_info(HWND listview_handle, LVGROUP *group, int32_t index);

        bool get_group_info_by_index(HWND listview_handle,
                                     LVGROUP *group,
                                     int32_t index);

        void get_group_metrics(HWND listview_handle,
                               LVGROUPMETRICS *group_metrics);

        void set_group_metrics(HWND listview_handle,
                               LVGROUPMETRICS *group_metrics);

        bool get_group_rect(HWND listview_handle,
                            RECT *rect,
                            int32_t index,
                            GroupRectType type = GroupRectType::Group);

        GroupState get_group_state(HWND listview_handle,
                                   uint32_t index,
                                   GroupState mask = GroupState::Normal);
        bool set_group_state(HWND listview_handle,
                             GroupState state,
                             uint32_t index,
                             GroupState mask = GroupState::Normal);

        HWND get_header(HWND listview_handle);

        HCURSOR get_hot_cursor(HWND listview_handle);

        HCURSOR set_hot_cursor(HWND listview_handle, HCURSOR cursor_handle);

        int32_t get_hot_item(HWND listview_handle);

        int32_t set_hot_item(HWND listview_handle, int32_t index);

        uint32_t get_hover_time(HWND listview_handle);

        void set_hover_time(HWND listview_handle, uint32_t milli_seconds);

        HIMAGELIST get_image_list(HWND listview_handle, LVILStyle style);

        HIMAGELIST set_image_list(HWND listview_handle,
                                  HIMAGELIST image_list_handle,
                                  LVILStyle style);

        bool get_insert_mark(HWND listview_handle, LVINSERTMARK *insert_mark);

        bool set_insert_mark(HWND listview_handle, LVINSERTMARK *insert_mark);

        COLORREF get_insert_mark_color(HWND listview_handle);

        COLORREF set_insert_mark_color(HWND listview_handle, COLORREF color);

        bool get_insert_mark_rect(HWND listview_handle, RECT *rect);

        int32_t get_increment_search_string(
                HWND listview_handle,
                std::string &text,
                helper::CodePage code_page = helper::CodePage::GB2312);

        int32_t get_increment_search_string(HWND listview_handle,
                                            std::wstring &text);

        bool get_item(HWND listview_handle, LVITEMW *item);

        bool set_item(HWND listview_handle, LVITEMW *item);

        int32_t get_item_count(HWND listview_handle);

        void set_item_count(HWND listview_handle, int32_t count);

        void set_item_count(HWND listview_handle, int32_t count, LVICFlag flag);

        bool get_item_index_rect(HWND listview_handle,
                                 LVITEMINDEX *item_index,
                                 int32_t index,
                                 LVIRCode code,
                                 RECT *rect);

        bool get_item_pos(HWND listview_handle, POINT *point, int32_t index);

        bool set_item_pos(HWND listview_handle, POINT point, int32_t index);

        void set_item_pos32(HWND listview_handle, POINT point, int32_t index);

        bool get_item_rect(HWND listview_handle,
                           RECT *rect,
                           int32_t index,
                           LVIRCode code);

        // std::pair<horizontal, vertical>
        std::pair<uint32_t, uint32_t> get_item_spacing(HWND listview_handle,
                                                       bool small_icon = false);

        LVItemState
        get_item_state(HWND listview_handle, int32_t index, LVItemState mask);

        void set_item_state(HWND listview_handle,
                            LVItemState state,
                            int32_t index,
                            LVItemState mask);

        void
        get_item_text(HWND listview_handle,
                      std::string &text,
                      int32_t item_index,
                      int32_t sub_item_index,
                      helper::CodePage code_page = helper::CodePage::GB2312);

        void get_item_text(HWND listview_handle,
                           std::wstring &text,
                           int32_t item_index,
                           int32_t sub_item_index);

        void
        set_item_text(HWND listview_handle,
                      std::string &text,
                      int32_t item_index,
                      int32_t sub_item_index,
                      helper::CodePage code_page = helper::CodePage::GB2312);

        void set_item_text(HWND listview_handle,
                           std::wstring &text,
                           int32_t item_index,
                           int32_t sub_item_index);

        int32_t get_next_item(HWND listview_handle,
                              int32_t index,
                              LVNIFlag flag = LVNIFlag::All);

        bool get_next_item_index(HWND listview_handle,
                                 LVITEMINDEX *item_index,
                                 LVNIFlag flag = LVNIFlag::All);

        void get_number_of_work_areas(HWND listview_handle,
                                      uint32_t *num_work_areas);

        bool get_origin(HWND listview_handle, POINT *point);

        COLORREF get_outline_color(HWND listview_handle);

        COLORREF set_outline_color(HWND listview_handle, COLORREF color);

        uint32_t get_selected_column(HWND listview_handle);

        void set_selected_column(HWND listview_handle, uint32_t column);

        uint32_t get_selected_count(HWND listview_handle);

        int32_t get_selection_mark(HWND listview_handle);

        int32_t set_selection_mark(HWND listview_handle, int32_t mark);

        int32_t
        get_string_width(HWND listview_handle,
                         std::string &text,
                         helper::CodePage code_page = helper::CodePage::GB2312);

        int32_t get_string_width(HWND listview_handle, std::wstring &text);

        bool get_sub_item_rect(HWND listview_handle,
                               RECT *rect,
                               int32_t item_index,
                               int32_t sub_item_index,
                               LVIRCode code);

        COLORREF get_text_background_color(HWND listview_handle);

        bool set_text_background_color(HWND listview_handle, COLORREF color);

        COLORREF get_text_color(HWND listview_handle);

        bool set_text_color(HWND listview_handle, COLORREF color);


        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::components
#endif // LISTVIEW_H
