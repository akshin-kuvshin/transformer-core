
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CxEditLt window

#define ARROW_SIZE		6

#define EDIT_EM_MENU	13333

enum EDIT_BUTTONTYPE
{
	EDIT_BN_NONE,
	EDIT_BN_ARROWDOWN,
	EDIT_BN_ARROWRIGHT,
	EDIT_BN_POINTS,
	EDIT_BN_CHECK,
	EDIT_BN_IMAGE = 0x80000000 // EDIT_BN_IMAGE|iIcon    (iIcon - number of icon in global imagelist)
};

class MECHCTL_API CxEditLt : public CEdit
{
// Construction
public:
	CxEditLt();
	virtual ~CxEditLt();

	BOOL Create(const CRect &rc, CWnd* pParentWnd, UINT nID);

	void GetButtonRect(CRect &rc);

	void EnableButton(BOOL bEnable = TRUE);

	//
	void SetEdit(BOOL bEditing = TRUE);
	BOOL IsEditing();

	//
	BOOL SetButtonType(EDIT_BUTTONTYPE bnType, UINT idCommand = 0, CMenu *pMenu = NULL);
	afx_msg void OnPaint();

protected:

	BOOL			m_bButtonEnabledAlways;
	BOOL			m_bValueIsNull;

protected:
	void DrawButton(BOOL bPressed = FALSE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxEditLt)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CxEditLt)
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg void OnEnable(BOOL bEnable);
	
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);

#if _MFC_VER >= 0x0800
	afx_msg LRESULT OnNcHitTest(CPoint point);
#else
	afx_msg UINT OnNcHitTest(CPoint point);
#endif

#ifdef WIN64
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL				m_bButtonDown;
	UINT				m_btnCommand;
	UINT_PTR		m_nBtnTimer;
	EDIT_BUTTONTYPE		m_btnType;

	BOOL				m_bEditing;
	
	CMenu*				m_pMenu;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

