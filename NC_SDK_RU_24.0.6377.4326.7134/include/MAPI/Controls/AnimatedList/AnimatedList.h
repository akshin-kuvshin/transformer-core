/*
	Created as simple copy of DJ's AnimatedList. 
	version 2
	17.08.2011
*/
#pragma once
#include "mcClipboard.h"
#include <Windowsx.h>

// Categorized list view
// Supports both ListView and TreeView functionality
//////////////////////////////////////////////////////////////////////////

// Extra tree node states
#define TVIS_HASCHILDREN      0x00020000    // node has child nodes or/and child items
#define TVIS_HOVERED          0x00040000    // mouse is over this node
#define TVIS_DRAGGING         0x00080000    // node is being dragged
#define TVIS_HIDDEN           0x20000000

// Extra tree view hit test codes
#define TVHT_ONHEADER         (TVHT_ONITEMINDENT|TVHT_ONITEMBUTTON|TVHT_ONITEMLABEL|TVHT_ONITEMRIGHT)

// Extra list view states
#define LVIS_HIDDEN               0x0040    // list item is in collapsed node and isn't visible
#define LVIS_DRAGGING             0x0080    // list item is being dragged
#define LVIS_HOVERED              0x0100    // mouse is over the item

/*
LVM_MOVEITEMTOGROUP
  (int)WPARAM - list item index
	(HTREEITEM)LPARAM - tree node to move item into

LVM_HASGROUP
	WPARAM and LPARAM are mutually exclusive.
	(HTREEITEM)WPARAM - tree node to check it's exist (LPARAM = 0)
	(int)LPARAM - list item index for which to return handle of parent tree node (WPARAM = 0)

EN_CHANGE
  something changed
*/

#ifndef LVM_INSERTMARKHITTEST
	#define LVM_INSERTMARKHITTEST               (LVM_FIRST + 168)
	#define ListView_InsertMarkHitTest(m_hWnd, point, lvim) \
		(int)SNDMSG((m_hWnd), LVM_INSERTMARKHITTEST, (WPARAM)(LPPOINT)(point), (LPARAM)(LPLVINSERTMARK)(lvim))
	typedef struct 
	{
		UINT cbSize;
		DWORD dwFlags;
		int iItem;
		DWORD dwReserved;
	} LVINSERTMARK, * LPLVINSERTMARK;

	#define LVIM_AFTER      0x00000001 // TRUE = insert After iItem, otherwise before
#endif



//////////////////////////////////////////////////////////////////////////
// Служебная структура.
// Хранит правила формирования обозначений
struct DesignationRule {
	McsStringW swPrefix;
	McsStringW swSuffix;
	McsStringW swProperty;
	McsStringW swDefault;
	McsStringW swFixed;
};
typedef McsArray<DesignationRule, const DesignationRule&> DesignationRules;


//////////////////////////////////////////////////////////////////////////
struct MECHCTL_API CxAnimatedListSimple : public IMcWindow
{
	// IMcWindow
	virtual HWND hwnd() { return m_hWnd; }

	// CxAnimatedListSimple
	HWND m_hWnd;

	static void Register();
	static void Unregister();

	int GetItemFocus();

	BOOL Create(HWND hParent, LPRECT prc, DWORD dwStyle = WS_TABSTOP|WS_CHILD|LVS_ICON|LVS_AUTOARRANGE);
	void SubclassDlgItem(HWND hDlg, UINT idCtrl);
	void Clear() { OnItemsClear(); OnNodesClear(); }
	void InvalidateRect(LPRECT prc = NULL, BOOL fErase = TRUE);

	void ShowTooltip(UINT_PTR id, POINT pt_scr);

	HRESULT getProperties(int iItem, mcsStringArray& res);
	McsString getItemCaption(int iItem);
	bool isTitle(int iItem);   // item is a title or a cover

	// platform functions
	bool UpdatePreview(int ipItem);
	void UpdateXmlAttributes(MSXML2::IXMLDOMElement* pxItem, IMcPropertySource* pFrame);

	CxAnimatedListSimple();
	~CxAnimatedListSimple();
	
	void SetModificationByKeyboard(bool bEnable) { m_bEnableModByKBD = bEnable; }
	void SetDisableEraseAllItems(bool bDisable)  { m_bDisableEraseAllItems = bDisable; }
	void SetDisableDragging(bool bDisable)
	{
		m_bDisableDragging = bDisable; 
		if (bDisable)
			RevokeDragDrop(m_hWnd);
		else
			RegisterDragDrop(m_hWnd, &m_Target);
	}
	void SetDrawLabelAsSingleLine(bool bSingle) { m_bDrawLabelAsSingleLine = bSingle; }
	
	int SearchText(LPCTSTR pszText, mcsIntArray& idsFound);

protected:
	struct Node {
		Node* pParent;
		DWORD dwFlags;
		McsString msName;
		RECT rc;
		int iImage;
		LPARAM lParam;
		MSXML2::IXMLDOMElementPtr px;
		Node() : pParent(NULL), dwFlags(0), iImage(-1), lParam(0) { ZeroMemory(&rc, sizeof(rc)); }
		int Depth() { int iRes = 0; Node* p = pParent; while (p) { iRes++; p = p->pParent; } return iRes; }
	};

	struct Item {
		McsString msText;
		int iImage;
		DWORD dwState;
		RECT rc;
		LPARAM lParam;
		HTREEITEM hGroup;
		MSXML2::IXMLDOMElementPtr px;

		Item() : iImage(-1), dwState(0), lParam(0), hGroup(NULL) { ZeroMemory(&rc, sizeof(rc)); }
	};

	struct InsertMark {
		bool fAfter;
		int iItem;                          // list item index to insert at
		HTREEITEM hParent;                  // parent node
		HTREEITEM hAfter;                   // node after insertion point
		HTREEITEM hBefore;                  // node before insertion point
		RECT rc;                            // insertion mark bounds
		BOOL IsDropTarget(HTREEITEM hItem);
		void Clear();
		InsertMark() : fAfter(false), iItem(-1), hParent(NULL), hAfter(NULL), hBefore(NULL) {}
	};

	struct AnimationItem {
		int iItem;
		Node* pNode;
		RECT rcStart;
		RECT rcEnd;
	};

	typedef McsArray<AnimationItem, const AnimationItem&> AnimationData;

	friend struct CxListDropTarget;
	friend struct CxListItemComparator;

protected:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK EditProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	bool IsDropTarget();

	McsString getNodeCaption(Node* pNode);
	void ClientToBuffer(LPRECT prc);
	void BufferToClient(LPRECT prc);
	void ClientToBuffer(LPPOINT ppt);
	void BufferToClient(LPPOINT ppt);
	void OnPaint();
	void OnBkErase(HDC hdc);
	void PaintInRect(HDC hdc, RECT rc_cln);
	void DrawSelectionRect(HDC hdc, int dx, int dy);
	void OnScroll(int iCode, int iBar);
	void OnSize(int cx, int cy);
	void OnLButtonDown(UINT uFlags, POINT pt_cln);
	void OnNodeClicked(POINT pt_cln);
	bool OnItemClicked(POINT pt_cln, UINT uFlags);
	void OnLButtonDouble(UINT uFlags, POINT pt_cln);
	void OnMouseMove(UINT uFlags, POINT pt_cln);
	void HoverItem(POINT pt_cln);
	void CheckForDrag(POINT pt_cln, POINT pt_buf);
	void DrawSelectionFrame(UINT uFlags, POINT pt_buf);
	void OnMouseLeave();
	void SmoothPaintNode(Node* pNode, DWORD dwNewFlags);
	void OnMouseHover(UINT uFlags, POINT pt_cln);
	void OnMouseWheel(UINT uFlags, int iDelta);
	void OnLButtonUp(UINT uFlags, POINT pt_cln);
	void DraggingComplete();
	LRESULT OnGetDlgCode(LPMSG pMsg);
	BOOL OnKeyDown(UINT key);
	BOOL OnNodeCreate();
	BOOL OnChar(UINT key);
	void OnTimer(UINT uTimer);
	void CancelSearch();
	void OnSmoothScroll();
	void RenderFrame();
	void OnScrollTimer();
	void OnGetDragImage(LPSHDRAGIMAGE lp);
	void OnCreate();
	void CreateImages();
	void CreateTooltips();
	void OnKillFocus();
	void OnDestroy();
	BOOL OnUpdateView(MSXML2::IXMLDOMDocument* pxDoc, HIMAGELIST hImages);
	void RestoreSelectionState(mcsWorkIDArray& idSelection, McsStringW& swSelNode);
	void ReadTree(MSXML2::IXMLDOMDocument* pxDoc);
	void StoreSelectionState(mcsWorkIDArray& idSelection, McsStringW& swSelNode);
	void OnItemsClear();
	int OnItemInsert(LPLVITEM lpItem);
	int OnItemFind(int iFrom, LV_FINDINFO* lpfi);
	BOOL OnItemGet(LPLVITEM lpItem);
	BOOL OnItemSet(const LPLVITEM lpItem);
	BOOL OnItemDelete(int iItem);
	BOOL OnItemSetPosition(int iItem, int x, int y);
	BOOL OnItemGetPosition(int iItem, LPPOINT ppt);
	BOOL OnItemGetRect(int iItem, LPRECT prc_cln);
	BOOL OnGroupGetRect(HTREEITEM hGroup, int iType, LPRECT prc_cln);
	BOOL OnNodeGetRect(HTREEITEM hNode, LPRECT prc_cln);
	HTREEITEM OnItemGetGroup(int iItem);
	BOOL OnItemSetGroup(int iItem, HTREEITEM hGroup);
	int  OnItemHitTest(int iMode, LPLVHITTESTINFO lphti);
	int  OnInsertHitTest(POINT pt_cln, LPLVINSERTMARK lplvim);
	void BeginEditItem(int iItem);
	void BeginEditNode(HTREEITEM hNode);
	HWND CreateEditControl(bool fCenter);
	void EndEdit(BOOL fCancel = FALSE);
	void UpdateEditPos(BOOL fKeepInView = FALSE);
	BOOL OnListSetImages(HIMAGELIST hil);
	BOOL OnGetViewRect(LPRECT prc);
	void OnArrange();
	void RestoreWindowState();
	void StoreWindowState();
	void OnItemDraw(HDC hdc, int iItem, int dx, int dy);
	void DrawItemImage(HDC hdc, const CxAnimatedListSimple::Item& itm, RECT& rcItem, RECT& rcText);
	void DrawItemFrame(HDC hdc, const Item& itm, RECT& rcItem);
	void SelectItem(int iItem, BOOL fSingle = TRUE, BOOL fToggle = FALSE);
	void SelectItemEx(int iItem, DWORD dwKeys);
	bool SetItemState(int iItem, DWORD dwState, DWORD dwMask);

	void SmoothPaintItem(int iItem, DWORD dwNew, McsString msSearch);
	void EnsureItemVisible(int iItem);
	void SetItemFocus(int iItem);
	int OnItemGetNext(int iItem, DWORD dwCode);
		// dwCode values                                          simple                        +LVGN_VISIBLE          +LVGN_GROUP                    +LVGN_SELECTION
		#define LVGN_RIGHT        0x0001                       // next item                      to right from iItem   in one group                    next selected item
		#define LVGN_LEFT         0x0002                       // previous item                  to left from iItem    in one group                    last selected item
		#define LVGN_TOP          0x0003                       // above iItem                                          first item of previous group    first item in this selection group
		#define LVGN_BOTTOM       0x0004                       // beyond iItem                                         last item of next group         last item in this selection group
		#define LVGN_FIRST        0x0005                       // the very first item            first visible item    first item of the same group    first selected item
		#define LVGN_LAST         0x0006                       // the very last item             last visible item     last item of the same group     last selected item
		#define LVGN_VISIBLE      0x8000                       // only visible items             -                     -
		#define LVGN_GROUP        0x4000                       // navigation between groups      -                     -
		#define LVGN_SELECTION    0x2000                       // navigation within selection    -                     -

	void OnNodesClear();
	HTREEITEM OnNodeInsert(LPTVINSERTSTRUCT lptvis);
	BOOL OnNodeDelete(HTREEITEM hItem);
	BOOL OnNodeGet(LPTVITEM lpItem);
	BOOL OnNodeSet(LPTVITEM lpItem);
	void OnNodeDraw(HDC hdc, Node* pNode, int dx, int dy);

	void DrawNodeGlyph(HDC hdc, Node* pNode);
	void DrawNodeBackground(HDC hdc, RECT& rc, Node* pNode);
	BOOL OnNodeExpand(HTREEITEM hNode, UINT uCode);
	HTREEITEM OnNodeHitTest(LPTVHITTESTINFO lphti);
	bool OnPlaceholder(int iItem);
	bool SelectNode(HTREEITEM hNode);
	bool AutoArrange();
	bool AutoScroll(POINT pt);
	int ScrollTo(int nPos, UINT nBar = SB_VERT);
	void ArrangeRecursive(Node* pNode, int& iTop);
	bool ArrangeNode(Node* pNode, int& iTop);
	void HideItems(Node* pNode);
	void UpdateScrollBars();
	void UpdateInsertionMark(POINT ptClient);
	bool LoadRecursive(MSXML2::IXMLDOMElement* pxNode, LPTVINSERTSTRUCT lptvi, mcsIntArray* pImages);
	bool LoadItem(int iItem, MSXML2::IXMLDOMElement* pxItem, mcsIntArray* pImages);
	bool SaveItem(int iItem, MSXML2::IXMLDOMElement* pxParent);
	bool SaveNode(Node* pNode, MSXML2::IXMLDOMElement* pxParent);
	void ItemUpdateRect(int iItem);
	int  CreatePlaceholder(HTREEITEM hNode, LPCTSTR strName, UINT idCmd);
	void CreateDefaultPlaceholder(HTREEITEM hNode);
	bool UpdatePlaceholders();

	int GetNodeItemCount(Node* pNode);
	Node* GetNode(HTREEITEM hNode);
	Node* GetNextNode(HTREEITEM hNode, DWORD code);
	BOOL GetNodeRectButton(Node* pNode, LPRECT prc_cln);
	BOOL GetNodeRectLabel(Node* pNode, LPRECT prc_cln);
	BOOL GetItemRectLabel(int iItem, LPRECT prc_cln);
	void Copy();
	void Paste();
	void Cut();

	void AnimationStart();
	void AnimationFrame(int iPercent);
	void AnimationStop();
	void DragItem(POINT pt);
	void Modified();
	int InsertFile(McsString msPath, HTREEITEM hParent = NULL, int iItem = -1, bool fAfter = true, int iProgressFrom = 0, int iProgressTo = 100);
	HRESULT RemoveObject(MSXML2::IXMLDOMElement* px);
	HRESULT MarkItemText(int iItem, McsString msSample);

public:
	HWND m_hTooltip;

protected:
	bool m_fInLoading;
	bool m_fLockButtons;
	MSXML2::IXMLDOMDocument2Ptr m_pxDoc;
	McsString m_msDocPath;
	McsArray<Node*, Node*> m_Nodes;               // tree nodes
	McsArray<Item, const Item&> m_Items;          // list items
	HIMAGELIST m_hItemImages;                     // list item images
	HIMAGELIST m_hNodeImages;                     // tree images (unused)
	HIMAGELIST m_hSelectImages;                   // select item images (+ and -)
	HFONT m_hFont;                                // main font
	int m_iSpacing;                               // spacing between list items, px
	int m_iRedrawFroze;                           // WM_REDRAW counter
	RECT m_rcItems;                               // total bounds
	int m_iLastSel;                               // last selected item for keyboard selection
	McsString m_msSearch;                         // search string
	// edit labels
	HWND m_hEdit;                                 // edit control for renaming
	int m_iEditItem;
	HTREEITEM m_hEditNode;
	// Drag
	bool m_fLButtonDown;                          // left mouse button was pressed on window
	POINT m_ptDrag_buf, m_ptLast_buf;                     // drag points in buffer coordinates
	POINT m_ptLast_cln;                           // last mouse position in client coorditanes
	POINT m_ptOffset;                             // offset from mouse pointer to top left corner of dragged item
	bool m_fDragging;                             // selection frame is active
	int m_iDragged;                               // dragged item
	InsertMark m_InsertMark;                      // current drag position in node:item coordinates
	DWORD m_dwDropeffect;                         // current drop effect for OleDragDrop
	CxListDropTarget m_Target;
	bool m_fSetActive;                            // last LBUTTONDOWN changed item focus
	RECT m_rcFocus_buf;                               // semi-transparent selection rectangle (in butter coordinates)
	// Item animation
	DWORD m_dwAnimationStarted;
	AnimationData m_Animation;
	HBITMAP m_hbmBuffer;
	// Scrolling animation
	DWORD m_dwScrollStarted;
	int m_iVScrollFrom;
	int m_iVScrollTo;
	int m_iHScrollFrom;
	int m_iHScrollTo;
	int m_iVScrollBefore;                         // vertical scrollbar position just before UpdateView
	int m_iVScrollBound;                          // vertical scroll bound just before UpdateView
	McsArray<IUnknown*, IUnknown*> m_pPropSources;
	
	bool m_bEnableModByKBD;
	bool m_bDisableEraseAllItems;
	bool m_bDisableDragging;
	bool m_fInSearch;
	bool m_bDrawLabelAsSingleLine;
};


#if (_WIN32_WINNT < 0x501)
#define LVM_SETSELECTEDCOLUMN         (LVM_FIRST + 140)
#define ListView_SetSelectedColumn(m_hWnd, iCol) \
    SNDMSG((m_hWnd), LVM_SETSELECTEDCOLUMN, (WPARAM)iCol, 0)

#define LVM_SETTILEWIDTH         (LVM_FIRST + 141)
#define ListView_SetTileWidth(m_hWnd, cpWidth) \
    SNDMSG((m_hWnd), LVM_SETTILEWIDTH, (WPARAM)cpWidth, 0)

#define LV_VIEW_ICON        0x0000
#define LV_VIEW_DETAILS     0x0001
#define LV_VIEW_SMALLICON   0x0002
#define LV_VIEW_LIST        0x0003
#define LV_VIEW_TILE        0x0004
#define LV_VIEW_MAX         0x0004

#define LVM_SETVIEW         (LVM_FIRST + 142)
#define ListView_SetView(m_hWnd, iView) \
    (DWORD)SNDMSG((m_hWnd), LVM_SETVIEW, (WPARAM)(DWORD)iView, 0)

#define LVM_GETVIEW         (LVM_FIRST + 143)
#define ListView_GetView(m_hWnd) \
    (DWORD)SNDMSG((m_hWnd), LVM_GETVIEW, 0, 0)


#define LVGF_NONE           0x00000000
#define LVGF_HEADER         0x00000001
#define LVGF_FOOTER         0x00000002
#define LVGF_STATE          0x00000004
#define LVGF_ALIGN          0x00000008
#define LVGF_GROUPID        0x00000010

#define LVGS_NORMAL         0x00000000
#define LVGS_COLLAPSED      0x00000001
#define LVGS_HIDDEN         0x00000002

#define LVGA_HEADER_LEFT    0x00000001
#define LVGA_HEADER_CENTER  0x00000002
#define LVGA_HEADER_RIGHT   0x00000004  // Don't forget to validate exclusivity
#define LVGA_FOOTER_LEFT    0x00000008
#define LVGA_FOOTER_CENTER  0x00000010
#define LVGA_FOOTER_RIGHT   0x00000020  // Don't forget to validate exclusivity

typedef struct tagLVGROUP
{
    UINT    cbSize;
    UINT    mask;
    LPWSTR  pszHeader;
    int     cchHeader;

    LPWSTR  pszFooter;
    int     cchFooter;

    int     iGroupId;

    UINT    stateMask;
    UINT    state;
    UINT    uAlign;
} LVGROUP, *PLVGROUP;


#define LVM_INSERTGROUP         (LVM_FIRST + 145)
#define ListView_InsertGroup(m_hWnd, index, pgrp) \
    SNDMSG((m_hWnd), LVM_INSERTGROUP, (WPARAM)index, (LPARAM)pgrp)


#define LVM_SETGROUPINFO         (LVM_FIRST + 147)
#define ListView_SetGroupInfo(m_hWnd, iGroupId, pgrp) \
    SNDMSG((m_hWnd), LVM_SETGROUPINFO, (WPARAM)iGroupId, (LPARAM)pgrp)


#define LVM_GETGROUPINFO         (LVM_FIRST + 149)
#define ListView_GetGroupInfo(m_hWnd, iGroupId, pgrp) \
    SNDMSG((m_hWnd), LVM_GETGROUPINFO, (WPARAM)iGroupId, (LPARAM)pgrp)


#define LVM_REMOVEGROUP         (LVM_FIRST + 150)
#define ListView_RemoveGroup(m_hWnd, iGroupId) \
    SNDMSG((m_hWnd), LVM_REMOVEGROUP, (WPARAM)iGroupId, 0)

#define LVM_MOVEGROUP         (LVM_FIRST + 151)
#define ListView_MoveGroup(m_hWnd, iGroupId, toIndex) \
    SNDMSG((m_hWnd), LVM_MOVEGROUP, (WPARAM)iGroupId, (LPARAM)toIndex)

#define LVM_MOVEITEMTOGROUP            (LVM_FIRST + 154)
#define ListView_MoveItemToGroup(m_hWnd, idItemFrom, idGroupTo) \
    SNDMSG((m_hWnd), LVM_MOVEITEMTOGROUP, (WPARAM)idItemFrom, (LPARAM)idGroupTo)


#define LVGMF_NONE          0x00000000
#define LVGMF_BORDERSIZE    0x00000001
#define LVGMF_BORDERCOLOR   0x00000002
#define LVGMF_TEXTCOLOR     0x00000004

typedef struct tagLVGROUPMETRICS
{
    UINT cbSize;
    UINT mask;
    UINT Left;
    UINT Top;
    UINT Right;
    UINT Bottom;
    COLORREF crLeft;
    COLORREF crTop;
    COLORREF crRight;
    COLORREF crBottom;
    COLORREF crHeader;
    COLORREF crFooter;
} LVGROUPMETRICS, *PLVGROUPMETRICS;

#define LVM_SETGROUPMETRICS         (LVM_FIRST + 155)
#define ListView_SetGroupMetrics(m_hWnd, pGroupMetrics) \
    SNDMSG((m_hWnd), LVM_SETGROUPMETRICS, 0, (LPARAM)pGroupMetrics)

#define LVM_GETGROUPMETRICS         (LVM_FIRST + 156)
#define ListView_GetGroupMetrics(m_hWnd, pGroupMetrics) \
    SNDMSG((m_hWnd), LVM_GETGROUPMETRICS, 0, (LPARAM)pGroupMetrics)

#define LVM_ENABLEGROUPVIEW         (LVM_FIRST + 157)
#define ListView_EnableGroupView(m_hWnd, fEnable) \
    SNDMSG((m_hWnd), LVM_ENABLEGROUPVIEW, (WPARAM)fEnable, 0)

typedef int (CALLBACK *PFNLVGROUPCOMPARE)(int, int, void *);

#define LVM_SORTGROUPS         (LVM_FIRST + 158)
#define ListView_SortGroups(m_hWnd, _pfnGroupCompate, _plv) \
    SNDMSG((m_hWnd), LVM_SORTGROUPS, (WPARAM)_pfnGroupCompate, (LPARAM)_plv)

typedef struct tagLVINSERTGROUPSORTED
{
    PFNLVGROUPCOMPARE pfnGroupCompare;
    void *pvData;
    LVGROUP lvGroup;
}LVINSERTGROUPSORTED, *PLVINSERTGROUPSORTED;

#define LVM_INSERTGROUPSORTED           (LVM_FIRST + 159)
#define ListView_InsertGroupSorted(m_hWnd, structInsert) \
    SNDMSG((m_hWnd), LVM_INSERTGROUPSORTED, (WPARAM)structInsert, 0)

#define LVM_REMOVEALLGROUPS             (LVM_FIRST + 160)
#define ListView_RemoveAllGroups(m_hWnd) \
    SNDMSG((m_hWnd), LVM_REMOVEALLGROUPS, 0, 0)

#define LVM_HASGROUP                    (LVM_FIRST + 161)
#define ListView_HasGroup(m_hWnd, dwGroupId) \
    SNDMSG((m_hWnd), LVM_HASGROUP, dwGroupId, 0)

#endif //_WIN32_WINNT < 0x501


#ifndef LVM_GETFOCUSEDGROUP
	#define LVM_GETFOCUSEDGROUP             (LVM_FIRST + 93)
	#define ListView_GetFocusedGroup(m_hWnd) SNDMSG((m_hWnd), LVM_GETFOCUSEDGROUP, 0, 0)
#endif

#ifndef LVM_GETGROUPRECT
	#define LVGGR_GROUP         0 // Entire expanded group
	#define LVGGR_HEADER        1 // Header only (collapsed group)
	#define LVGGR_LABEL         2 // Label only
	#define LVGGR_SUBSETLINK    3 // subset link only
	#define LVM_GETGROUPRECT               (LVM_FIRST + 98)
	#define ListView_GetGroupRect(m_hWnd, iGroupId, type, prc) \
		SNDMSG((m_hWnd), LVM_GETGROUPRECT, (WPARAM)(iGroupId), \
		((prc) ? (((RECT*)(prc))->top = (type)), (LPARAM)(RECT*)(prc) : (LPARAM)(RECT*)NULL))
#endif
