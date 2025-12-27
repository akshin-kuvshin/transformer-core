#pragma once

/////////////////////////////////////////////////////////////////////////////
// CxInputTextDlg dialog

class CxInputTextDlg : public CDialog
{
// Construction
public:
	CxInputTextDlg(CWnd* pParent = NULL, LPCTSTR strHelpID = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CxInputTextDlg)
	enum { IDD = IDD_INPUT_TEXT };
	CString	m_strPromt;
	CString	m_strValue;
	//}}AFX_DATA
	CString	m_strCaption;
	CString m_strHelpID;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxInputTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CxInputTextDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CxToolBar m_tbHelp;
};
