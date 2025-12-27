///////////////////////////////////////////////////////////////////////////////
// 
// CxTreeCtrl - Multiple selection tree control for MFC

#ifndef __TREECTRLEX_H
#define __TREECTRLEX_H

#include "mcsTempl.h"
#define TVGN_EX_ALL			0x000F

#define TVN_DROP	        (TVN_FIRST-77)
#define TVN_CANDROP	        (TVN_FIRST-76)
#define TVN_TRANSFER		(TVN_FIRST-75)
#define TVN_DROPPED			(TVN_FIRST-74)

#ifndef TVN_ITEMCHANGINGA 

#define TVN_ITEMCHANGINGA (TVN_FIRST-16)
#define TVN_ITEMCHANGINGW (TVN_FIRST-17) 

typedef struct tagNMTVITEMCHANGE 
{ 
	NMHDR hdr; 
	UINT uChanged; 
	HTREEITEM hItem; 
	UINT uStateNew; 
	UINT uStateOld; 
	LPARAM lParam; 
} NMTVITEMCHANGE; 

#endif 

/////////////////////////////////////////////////////////////////////////////
// CxTreeCtrl window

typedef McsArray<HTREEITEM, HTREEITEM> mcsHtreeitemArray;
class MECHCTL_API CxTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CxTreeCtrl)

// Construction
public:
	CxTreeCtrl();
	BOOL Create(DWORD dwStyle, DWORD dwExStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Attributes
public:
	UINT GetSelectedCount() const;
	HRESULT GetSelectedItems(mcsHtreeitemArray& items) const;
	HTREEITEM GetNextItem(HTREEITEM hItem, UINT nCode);
	HTREEITEM GetFirstSelectedItem();
	HTREEITEM GetNextSelectedItem(HTREEITEM hItem);
	HTREEITEM GetPrevSelectedItem(HTREEITEM hItem);
	HTREEITEM ItemFromData(DWORD dwData, HTREEITEM hStartAtItem=NULL) const;

	BOOL SelectItemEx(HTREEITEM hItem, BOOL bSelect=TRUE);

	BOOL SelectItems(HTREEITEM hFromItem, HTREEITEM hToItem);
	void ClearSelection(BOOL bMultiOnly=FALSE);
	HTREEITEM TransferItem(HTREEITEM hitem, HTREEITEM newParent);
	
	BOOL IsChildNodeOf(HTREEITEM hitemChild, HTREEITEM hitemSuspectedParent);

protected:
	void SelectMultiple( HTREEITEM hClickedItem, UINT nFlags, CPoint point );	

private:
	BOOL		m_bSelectPending;
	CPoint		m_ptClick;
	HTREEITEM	m_hClickedItem;
	HTREEITEM	m_hEditLabelPendingItem;
	HTREEITEM	m_hFirstSelectedItem;
	BOOL		m_bSelectionComplete;
	BOOL		m_bEditLabelPending;
	UINT_PTR	m_idTimer;

	BOOL		m_bDragging;
	CImageList  *m_pimagelist;
	HTREEITEM   m_hitemDrop;

	HTREEITEM	m_unlockItem;
	HTREEITEM	m_AntiDeadLockItem;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CxTreeCtrl() {}

	// Generated message map functions
protected:
	//{{AFX_MSG(CxTreeCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnItemChanging(NMHDR* pNMHDR, LRESULT* pResult);

#ifdef WIN64
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif

	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


HTREEITEM GetTreeItemFromData(CTreeCtrl& treeCtrl, DWORD dwData, HTREEITEM hStartAtItem=NULL);

#endif
