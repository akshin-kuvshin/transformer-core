#pragma once

#include "CxTreeListCtrl.h"

//==============================================================================
class MECHCTL_API CIPEditCtrlWithFuncs : public CInPlaceEditCtrl
{
public:
	CIPEditCtrlWithFuncs(BOOL bResizing = FALSE, BOOL bTreeIsParent = TRUE);
	~CIPEditCtrlWithFuncs() {};

	// CInPlaceEditCtrl
	virtual BOOL CreateOneTime(CWnd* parent, UINT nCtrlId);
	virtual BOOL EditBegin(CRect& rc, TLNM_ITEM& item, UINT nChar);
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPEditCtrlWithFuncs)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

protected:

	CMenu m_menuPopup;
	//HMENU hMenuPopupExpressions;

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//{{AFX_MSG(CIPEditCtrlWithFuncs)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};
//==============================================================================
