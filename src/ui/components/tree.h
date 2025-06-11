/* clang-format off */
/*
 * @file tree.h
 * @date 2025-06-04
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
#ifndef TREE_H
#define TREE_H
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
#include "sync/rwlock.h"
#include "helper/convert.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
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
#ifndef TREESTYLE
#define TREESTYLE
    enum class TreeStyle : uint32_t {
        HasButtons = TVS_HASBUTTONS,
        HasLines = TVS_HASLINES,
        LinesAtRoot = TVS_LINESATROOT,
        EditLabels = TVS_EDITLABELS,
        DisableDragDrop = TVS_DISABLEDRAGDROP,
        ShowSelectAlways = TVS_SHOWSELALWAYS,
        RtlReading = TVS_RTLREADING,
        NoToolTips = TVS_NOTOOLTIPS,
        CheckBoxes = TVS_CHECKBOXES,
        TrackSelect = TVS_TRACKSELECT,
        SingleExpand = TVS_SINGLEEXPAND,
        InfoTip = TVS_INFOTIP,
        FullRowSelect = TVS_FULLROWSELECT,
        NoScroll = TVS_NOSCROLL,
        NoEvenHeight = TVS_NONEVENHEIGHT,
        NoHScroll = TVS_NOHSCROLL,
    };
    inline TreeStyle operator|(TreeStyle a, TreeStyle b) {
        return static_cast<TreeStyle>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }
#endif
#ifndef TREEEXTENDSTYLE
#define TREEEXTENDSTYLE
    enum class TreeExtendStyle : uint32_t {
        NoSingleCollapse = TVS_EX_NOSINGLECOLLAPSE,
        MultiSelect = TVS_EX_MULTISELECT,
        DoubleBuffer = TVS_EX_DOUBLEBUFFER,
        NoIndentState = TVS_EX_NOINDENTSTATE,
        RichToolTip = TVS_EX_RICHTOOLTIP,
        AutoHScroll = TVS_EX_AUTOHSCROLL,
        FadeInOutExpandOs = TVS_EX_FADEINOUTEXPANDOS,
        PartialCheckBoxes = TVS_EX_PARTIALCHECKBOXES,
        ExclusionCheckBoxes = TVS_EX_EXCLUSIONCHECKBOXES,
        DimmedCheckBoxes = TVS_EX_DIMMEDCHECKBOXES,
        DrawImageAsync = TVS_EX_DRAWIMAGEASYNC
    };
    inline TreeExtendStyle operator|(TreeExtendStyle a, TreeExtendStyle b) {
        return static_cast<TreeExtendStyle>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }
#endif
#ifndef TREEITEMSTATE
#define TREEITEMSTATE
    enum class TreeItemState : uint32_t {
        Selected = TVIS_SELECTED,
        Cut = TVIS_CUT,
        DropHilited = TVIS_DROPHILITED,
        Bold = TVIS_BOLD,
        Expanded = TVIS_EXPANDED,
        ExpandedOnce = TVIS_EXPANDEDONCE,
        ExpandPartial = TVIS_EXPANDPARTIAL,
        OverlayMask = TVIS_OVERLAYMASK,
        StateImageMask = TVIS_STATEIMAGEMASK,
        UserMask = TVIS_USERMASK,
    };
    inline TreeItemState operator|(TreeItemState a, TreeItemState b) {
        return static_cast<TreeItemState>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef TREEITEMEXSTATE
#define TREEITEMEXSTATE
    enum class TreeItemExState : uint32_t {
        Flat = TVIS_EX_FLAT,
        Disabled = TVIS_EX_DISABLED,
        All = TVIS_EX_ALL,
    };
    inline TreeItemExState operator|(TreeItemExState a, TreeItemExState b) {
        return static_cast<TreeItemExState>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }
#endif
#ifndef TREEITEMFLAG
#define TREEITEMFLAG
    enum class TreeItemFlag : uint32_t {
        Text = TVIF_TEXT,
        Image = TVIF_IMAGE,
        Param = TVIF_PARAM,
        State = TVIF_STATE,
        Handle = TVIF_HANDLE,
        SelectedImage = TVIF_SELECTEDIMAGE,
        Children = TVIF_CHILDREN,
        Integral = TVIF_INTEGRAL,
        StateEx = TVIF_STATEEX,
        ExpandedImage = TVIF_EXPANDEDIMAGE,
    };
#endif
#ifndef TREEITEMCHECKSTATE
#define TREEITEMCHECKSTATE
    enum class TreeItemCheckState : int32_t {
        Checked = 1,
        Unchecked = 0,
        Intermediate = -1,
    };
#endif
#ifndef TREEIMAGELISTTYPE
#define TREEIMAGELISTTYPE
    enum class TreeImageListType : int32_t {
        Normal = TVSIL_NORMAL,
        State = TVSIL_STATE,
    };
#endif
#ifndef TREEOPFLAG
#define TREEOPFLAG
    enum class TreeOpFlag : uint32_t {
        Root = TVGN_ROOT,
        Next = TVGN_NEXT,
        Previous = TVGN_PREVIOUS,
        Parent = TVGN_PARENT,
        Child = TVGN_CHILD,
        FirstVisible = TVGN_FIRSTVISIBLE,
        NextVisible = TVGN_NEXTVISIBLE,
        PreviousVisible = TVGN_PREVIOUSVISIBLE,
        DropHilite = TVGN_DROPHILITE,
        Caret = TVGN_CARET,
        LastVisible = TVGN_LASTVISIBLE,
        NextSelected = TVGN_NEXTSELECTED,
    };
#endif
#ifndef TREEEXPANDFLAG
#define TREEEXPANDFLAG
    enum class TreeExpandFlag : uint32_t {
        Collapse = TVE_COLLAPSE,
        Expand = TVE_EXPAND,
        Toggle = TVE_TOGGLE,
        ExpandPartial = TVE_EXPANDPARTIAL,
        CollapseReset = TVE_COLLAPSERESET,
    };
    inline TreeExpandFlag operator|(TreeExpandFlag a, TreeExpandFlag b) {
        return static_cast<TreeExpandFlag>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }
#endif
#ifndef TREEMESSAGE
#define TREEMESSAGE
    enum class TreeMessage : uint32_t {
        CreateDragImage = TVM_CREATEDRAGIMAGE,
        DeleteItem = TVM_DELETEITEM,
        EditLabel = TVM_EDITLABEL,
        EndEditLabelNow = TVM_ENDEDITLABELNOW,
        EnsureVisible = TVM_ENSUREVISIBLE,
        Expand = TVM_EXPAND,
        GetBackgroundColor = TVM_GETBKCOLOR,
        GetCount = TVM_GETCOUNT,
        GetEditControl = TVM_GETEDITCONTROL,
        GetExtendedStyle = TVM_GETEXTENDEDSTYLE,
        GetImageList = TVM_GETIMAGELIST,
        GetIndent = TVM_GETINDENT,
        GetInsertMarkColor = TVM_GETINSERTMARKCOLOR,
        GetISearchString = TVM_GETISEARCHSTRING,
        GetItem = TVM_GETITEM,
        GetItemHeight = TVM_GETITEMHEIGHT,
        GetItemPartRect = TVM_GETITEMPARTRECT,
        GetItemRect = TVM_GETITEMRECT,
        GetItemState = TVM_GETITEMSTATE,
        GetLineColor = TVM_GETLINECOLOR,
        GetNextItem = TVM_GETNEXTITEM,
        GetScrollTime = TVM_GETSCROLLTIME,
        GetSelectedCount = TVM_GETSELECTEDCOUNT,
        GetTextColor = TVM_GETTEXTCOLOR,
        GetToolTips = TVM_GETTOOLTIPS,
        GetUnicodeFormat = TVM_GETUNICODEFORMAT,
        GetVisibleCount = TVM_GETVISIBLECOUNT,
        HitTest = TVM_HITTEST,
        InsertItem = TVM_INSERTITEM,
        MapAccessIdToHTreeItem = TVM_MAPACCIDTOHTREEITEM,
        MapHTreeItemToAccessId = TVM_MAPHTREEITEMTOACCID,
        SelectItem = TVM_SELECTITEM,
        SetAutoScrollInfo = TVM_SETAUTOSCROLLINFO,
        SetBackgroundColor = TVM_SETBKCOLOR,
        SetBorder = TVM_SETBORDER,
        SetExtendedStyle = TVM_SETEXTENDEDSTYLE,
        SetHot = TVM_SETHOT,
        SetImageList = TVM_SETIMAGELIST,
        SetIndent = TVM_SETINDENT,
        SetInsertMark = TVM_SETINSERTMARK,
        SetInsertMarkColor = TVM_SETINSERTMARKCOLOR,
        SetItem = TVM_SETITEM,
        SetItemHeight = TVM_SETITEMHEIGHT,
        SetLineColor = TVM_SETLINECOLOR,
        SetScrollTime = TVM_SETSCROLLTIME,
        SetTextColor = TVM_SETTEXTCOLOR,
        SetToolTips = TVM_SETTOOLTIPS,
        SetUnicodeFormat = TVM_SETUNICODEFORMAT,
        ShowInfoTip = TVM_SHOWINFOTIP,
        SortChildren = TVM_SORTCHILDREN,
        SortChildrenCallback = TVM_SORTCHILDRENCB,
    };
#endif
#ifndef TREENOTIFY
#define TREENOTIFY
    enum class TreeNotify : uint32_t {
        Click = NM_CLICK,
        CustomDraw = NM_CUSTOMDRAW,
        DoubleClick = NM_DBLCLK,
        KillFocus = NM_KILLFOCUS,
        RightClick = NM_RCLICK,
        RightDoubleClick = NM_RDBLCLK,
        Return = NM_RETURN,
        SetCursor = NM_SETCURSOR,
        SetFocus = NM_SETFOCUS,
        AsyncDraw = TVN_ASYNCDRAW,
        BeginDrag = TVN_BEGINDRAG,
        BeginLabelEdit = TVN_BEGINLABELEDIT,
        BeginRDrag = TVN_BEGINRDRAG,
        DeleteItem = TVN_DELETEITEM,
        EndLabelEdit = TVN_ENDLABELEDIT,
        GetDispInfo = TVN_GETDISPINFO,
        GetInfoTip = TVN_GETINFOTIP,
        ItemChanged = TVN_ITEMCHANGED,
        ItemChanging = TVN_ITEMCHANGING,
        ItemExpanded = TVN_ITEMEXPANDED,
        ItemExpanding = TVN_ITEMEXPANDING,
        KeyDown = TVN_KEYDOWN,
        SelChanged = TVN_SELCHANGED,
        SelChanging = TVN_SELCHANGING,
        SetDispInfo = TVN_SETDISPINFO,
        SingleExpand = TVN_SINGLEEXPAND
    };
#endif
    class tree {
    private:
        std::vector<HWND> tree_handles = {};
        sync::rwlock tree_rwlock = {};
        uint32_t error_code = 0;

    public:
        tree(const tree &other) = delete;

        tree(tree &&other) = delete;

        tree &operator=(const tree &other) = delete;

        tree &operator=(tree &&other) = delete;

        tree();

        ~tree();

        HWND create(uintptr_t tree_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TreeStyle style = TreeStyle::HasLines |
                            TreeStyle::EditLabels | TreeStyle::HasButtons |
                            TreeStyle::LinesAtRoot | TreeStyle::InfoTip |
                            TreeStyle::ShowSelectAlways |
                            TreeStyle::SingleExpand | TreeStyle::TrackSelect,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border);

        HWND create(const char *tree_name,
                    uintptr_t tree_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TreeStyle style = TreeStyle::HasLines |
                            TreeStyle::EditLabels | TreeStyle::HasButtons |
                            TreeStyle::LinesAtRoot | TreeStyle::InfoTip |
                            TreeStyle::ShowSelectAlways |
                            TreeStyle::SingleExpand | TreeStyle::TrackSelect,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border);

        HWND create(const wchar_t *tree_name,
                    uintptr_t tree_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TreeStyle style = TreeStyle::HasLines |
                            TreeStyle::EditLabels | TreeStyle::HasButtons |
                            TreeStyle::LinesAtRoot | TreeStyle::InfoTip |
                            TreeStyle::ShowSelectAlways |
                            TreeStyle::SingleExpand | TreeStyle::TrackSelect,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border);

        bool destroy(HWND tree_handle);

        COLORREF get_background_color(HWND tree_handle);

        COLORREF set_background_color(HWND tree_handle, COLORREF color);

        COLORREF get_text_color(HWND tree_handle);

        COLORREF set_text_color(HWND tree_handle, COLORREF color);

        COLORREF get_line_color(HWND tree_handle);

        COLORREF set_line_color(HWND tree_handle, COLORREF color);

        COLORREF get_insert_mark_color(HWND tree_handle);

        COLORREF set_insert_mark_color(HWND tree_handle, COLORREF color);

        bool is_ansi_format(HWND tree_handle);

        bool is_unicode_format(HWND tree_handle);

        void set_ansi_format(HWND tree_handle);

        void set_unicode_format(HWND tree_handle);

        HWND get_tool_tips(HWND tree_handle);

        HWND set_tool_tips(HWND tree_handle, HWND tool_tips_handle);

        TreeExtendStyle get_extend_style(HWND tree_handle);

        bool set_extend_style(HWND tree_handle,
                              TreeExtendStyle style,
                              TreeExtendStyle mask);

        uint32_t get_indent(HWND tree_handle);

        void set_indent(HWND tree_handle, uint32_t indent);

        uint32_t get_scroll_time(HWND tree_handle);

        uint32_t set_scroll_time(HWND tree_handle, uint32_t milli_seconds);

        int32_t get_item_height(HWND tree_handle);

        int32_t set_item_height(HWND tree_handle, int32_t height);

        TreeItemState get_item_state(HWND tree_handle,
                                     HTREEITEM tree_item_handle,
                                     TreeItemFlag mask);

        void set_item_state(HWND tree_handle,
                            HTREEITEM tree_item_handle,
                            TreeItemState state,
                            TreeItemState mask);

        TreeItemCheckState get_check_state(HWND tree_handle,
                                           HTREEITEM tree_item_handle);

        void set_check_state(HWND tree_handle, HTREEITEM tree_item_handle);

        void set_uncheck_state(HWND tree_handle, HTREEITEM tree_item_handle);

        HIMAGELIST
        get_image_list(HWND tree_handle,
                       TreeImageListType type = TreeImageListType::Normal);

        HIMAGELIST
        set_image_list(HWND tree_handle,
                       HIMAGELIST image_list_handle,
                       TreeImageListType type = TreeImageListType::Normal);

        bool get_item(HWND tree_handle, TVITEMW *item);

        bool set_item(HWND tree_handle, TVITEMW *item);

        bool get_item_rect(HWND tree_handle,
                           HTREEITEM tree_item_handle,
                           RECT *rect,
                           bool include_text_only = false);

        bool get_item_part_rect(HWND tree_handle,
                                HTREEITEM tree_item_handle,
                                RECT *rect);

        HTREEITEM get_first_visible(HWND tree_handle);

        bool set_first_visible(HWND tree_handle, HTREEITEM tree_item_handle);

        HTREEITEM get_curr_select(HWND tree_handle);

        bool
        select(HWND tree_handle, HTREEITEM tree_item_handle, TreeOpFlag flag);

        bool select_item(HWND tree_handle, HTREEITEM tree_item_handle);

        uint32_t get_selected_count(HWND tree_handle);

        HTREEITEM get_next_selected(HWND tree_handle,
                                    HTREEITEM tree_item_handle);

        bool select_drop_target(HWND tree_handle, HTREEITEM tree_item_handle);

        HTREEITEM get_drop_hilight(HWND tree_handle);

        HTREEITEM get_child(HWND tree_handle, HTREEITEM tree_item_handle);

        HTREEITEM get_parent(HWND tree_handle, HTREEITEM tree_item_handle);

        HTREEITEM get_root(HWND tree_handle);

        HTREEITEM get_next_sibling(HWND tree_handle,
                                   HTREEITEM tree_item_handle);

        HTREEITEM get_prev_sibling(HWND tree_handle,
                                   HTREEITEM tree_item_handle);

        HTREEITEM get_next_item(HWND tree_handle,
                                HTREEITEM tree_item_handle,
                                TreeOpFlag flag);

        HTREEITEM get_next_visible(HWND tree_handle,
                                   HTREEITEM tree_item_handle);

        HTREEITEM get_prev_visible(HWND tree_handle,
                                   HTREEITEM tree_item_handle);

        HTREEITEM get_last_visible(HWND tree_handle);

        uint32_t get_count(HWND tree_handle);

        uint32_t get_visible_count(HWND tree_handle);

        HWND get_edit_control(HWND tree_handle);

        bool get_increment_search_string(
                HWND tree_handle,
                std::string &text,
                helper::CodePage code_page = helper::curr_code_page());

        bool get_increment_search_string(HWND tree_handle, std::wstring &text);

        void set_auto_scroll_info(HWND tree_handle,
                                  uint32_t pixel_per_sec,
                                  uint32_t update_time_ms);

        // std::pair<horiz, vert>
        std::pair<uint16_t, uint16_t>
        set_left_border(HWND tree_handle, uint16_t left, uint16_t top);

        // std::pair<horiz, vert>
        std::pair<uint16_t, uint16_t>
        set_top_border(HWND tree_handle, uint16_t left, uint16_t top);

        bool set_hot(HWND tree_handle, HTREEITEM tree_item_handle);

        bool set_insert_mark(HWND tree_handle,
                             HTREEITEM tree_item_handle,
                             bool insert_after = true);

        HIMAGELIST create_drag_image(HWND tree_handle,
                                     HTREEITEM tree_item_handle);

        bool delete_all_items(HWND tree_handle);

        bool delete_item(HWND tree_handle, HTREEITEM tree_item_handle);

        HWND edit_label(HWND tree_handle, HTREEITEM tree_item_handle);

        bool end_edit_label_now(HWND tree_handle, bool save = true);

        bool ensure_visible(HWND tree_handle, HTREEITEM tree_item_handle);

        bool expand(HWND tree_handle,
                    HTREEITEM tree_item_handle,
                    TreeExpandFlag flag);

        HTREEITEM hit_test(HWND tree_handle, TVHITTESTINFO *hit_test_info);

        HTREEITEM insert_item(HWND tree_handle, TVINSERTSTRUCTW *insert_struct);

        HTREEITEM map_access_id_to_tree_item_handle(HWND tree_handle,
                                                    uint32_t id);

        uint32_t map_tree_item_handle_to_access_id(HWND tree_handle,
                                                   HTREEITEM tree_item_handle);

        void show_info_tip(HWND tree_handle, HTREEITEM tree_item_handle);

        bool sort_child(HWND tree_handle,
                        HTREEITEM tree_item_handle,
                        bool recursive = true);

        bool sort_child_callback(HWND tree_handle, TVSORTCB *sort);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // TREE_H
