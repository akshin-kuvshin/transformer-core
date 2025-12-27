#ifndef INPLACERICHEDIT_H
#define INPLACERICHEDIT_H

#include "MechCtl.h"

class CInPlaceRichEdit: public CxFtEdit
{
// Construction
public:
    CInPlaceRichEdit() {};
	CInPlaceRichEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                 int nRow, int nColumn, CString sInitText, UINT nFirstChar);
// Attributes
public:
	BOOL Create(CWnd* pOwner, LPRECT pRect, DWORD dwStyle, int id);
// Operations
public:
     void EndEdit();
 
// Overrides
     // ClassWizard generated virtual function overrides
     //{{AFX_VIRTUAL(CInPlaceEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	void UpdateWindow();
	//}}AFX_VIRTUAL
 
// Implementation
public:
     virtual ~CInPlaceRichEdit();
 
// Generated message map functions
protected:
    //{{AFX_MSG(CInPlaceRichEdit)
    afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
    afx_msg void OnSysColorChange();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    int			m_nRow;
    int			m_nColumn;
    McsString	m_sInitText;
    UINT		m_nLastChar;
    BOOL		m_bExitOnArrows;
    CRect		m_Rect;
	CBrush		m_bFrameBrush;
	int			m_nWidth;
};

#endif
