//#ifndef __OPENDWG_AFXEXT_H__
//#define __OPENDWG_AFXEXT_H__

#include "interactionDB.h"

#include <afxext.h>

#ifdef THUNK_NATIVE_API
#undef THUNK_NATIVE_API
#endif // THUNK_NATIVE_API

#ifdef NANOTHUNKUI
#define THUNK_NATIVE_API  __declspec(dllexport)
#else
#define THUNK_NATIVE_API  __declspec(dllimport)
#endif


#undef ncedGetWinNum
#undef ncedStartOverrideDropTarget
#undef ncedRevokeCustomDropTarget
#undef ncedEndOverrideDropTarget

/////////////////////////////////////////////////////////////////////////////
//Methods
THUNK_NATIVE_API void InitNcUiDLL();

THUNK_NATIVE_API HINSTANCE NcUiAppResourceInstance();

THUNK_NATIVE_API LPCTSTR NcUiContextHelpFileName();

THUNK_NATIVE_API BOOL NcUiEnableToolTips();

THUNK_NATIVE_API BOOL NcUiFindContextHelpFullPath(LPCTSTR fileName, CString& fullPath);

THUNK_NATIVE_API BOOL NcUiIsInputPending();

THUNK_NATIVE_API CWnd* NcUiMainWindow();

THUNK_NATIVE_API void NcUiRootKey(CString& root);

/////////////////////////////////////////////////////////////////////////////
// CNdUiTipWindow window
class THUNK_NATIVE_API CNdUiTipWindow : public CWnd
{
	DECLARE_DYNAMIC(CNdUiTipWindow)

public:
	CNdUiTipWindow();

public:
	virtual ~CNdUiTipWindow();

public:
	virtual BOOL Create(CWnd* owner);
	CWnd* GetControl();
	void GetTextExtent(LPCTSTR text, int& width, int& height);
	BOOL GetUseText();
	virtual void Hide();
	CWnd* Owner();
	void SetControl(CWnd* control);
	void SetUseText(BOOL useText);
	virtual void Show();

private:
	void ForwardClickMessage(UINT msg, UINT nFlags, CPoint& point, BOOL focus);

protected:
	virtual void DrawBorder(CDC& dc, CRect& rExterior, CRect& rInterior);
	virtual void DrawContent(CDC& dc, CRect& rInterior);
	void StartTimer(DWORD ms = 50);
	void StopTimer();

protected:
	static LPCTSTR    m_className; // Registered class name
	static const UINT m_timerEvent;

	BOOL              m_bUseText; // Draw as text vs. owner-draw.
	CWnd* m_control; // Related control
	CWnd* m_owner; // Owner(dialog, etc.)
	UINT              m_timerId;

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNdUiTipWindow)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNdUiTipWindow)
	afx_msg void OnActivateApp(BOOL bActive, DWORD hTask);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcDestroy();
	afx_msg void OnPaint();
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CNdUiTextTip window
class THUNK_NATIVE_API CNdUiTextTip : public CNdUiTipWindow
{
	DECLARE_DYNAMIC(CNdUiTextTip)

public:
	CNdUiTextTip();

public:
	virtual ~CNdUiTextTip();

	// Text Tip
protected:
	virtual void DrawBorder(CDC& dc, CRect& rExterior, CRect& rInterior);
	virtual void DrawContent(CDC& dc, CRect& rInterior);

public:
	virtual void Hide();
	void Update(CWnd* control, BOOL useText);
	void UpdateIfNecessary(CWnd* control, BOOL useText);

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNdUiTextTip)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNdUiTextTip)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// CNdUiBaseDialog
class THUNK_NATIVE_API CNdUiBaseDialog : public CDialog

{
	DECLARE_DYNAMIC(CNdUiBaseDialog);

public:
	CNdUiBaseDialog(UINT idd, CWnd* pParent = NULL, HINSTANCE hDialogResource = NULL);

public:
	virtual ~CNdUiBaseDialog();

protected:
	virtual NDUI_REPLY DoNdUiMessage(NDUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam);
	virtual NDUI_REPLY OnNotifyControlChange(UINT controlId, LPARAM lParam);
	virtual NDUI_REPLY OnNotifyControlValid(UINT controlId, BOOL isValid);
	virtual NDUI_REPLY OnNotifyGeneric(UINT controlId, LPARAM lParam);
	virtual NDUI_REPLY OnNotifyUpdateTip(CWnd* control);

	// Drawing Editor Interaction
private:
	HINSTANCE m_commandResourceInstance;
	BOOL      m_commandWindowWasEnabled;
	HWND      m_commandWindowWithFocus;

protected:
	//	NDUI_COMMAND_STATE m_commandState;

	void BeginEditorCommand();
	void CancelEditorCommand();
	void CompleteEditorCommand(BOOL restore_dialogs = TRUE);
	void MakeDialogsVisible(BOOL visible);


public:
	BOOL EditorCommandCancelled();

	// Context help
protected:
		CString m_contextHelpFileName;
		CString m_contextHelpFullPathName;
		CString m_contextHelpPrefix; // Must be 4 ASCII characters.

	virtual BOOL FindContextHelpFullPath(LPCTSTR fileName, CString& fullPath);

public:
	LPCTSTR GetContextHelpFileName();
	void SetContextHelpFileName(LPCTSTR file_name);
	LPCTSTR GetContextHelpFullPathName();
	void SetContextHelpFullPathName(LPCTSTR pFullPathName);
	LPCTSTR GetContextHelpPrefix();
	void SetContextHelpPrefix(LPCTSTR pPrefix);
	LPCTSTR GetContextHelpMapFileName();
	void SetContextHelpMapFileName(LPCTSTR pFileName);

	CToolTipCtrl* GetToolTipCtrl();
	/*
	private:
		BOOL m_bRunningModal;
		// Substitute font used when charset isn't supported in the default font
		CFont m_substFont;
	*/
protected:
	HINSTANCE m_hDialogResource;
	HINSTANCE m_hDialogResourceSaved;
	BOOL m_bUseTips;
	CToolTipCtrl* m_pToolTip;
	/*
		HICON m_hIcon;
		CNdUiTextTip *m_pTextTip;
		CString m_rootKey;

	//	friend class CNdUiAssist;
	//	static CNdUiAssist* m_pUIAssist;
	*/
protected:
	virtual void OnInitDialogBegin();
	virtual void OnInitDialogFinish();

public:
	virtual CWnd* AppMainWindow();
	virtual HINSTANCE AppResourceInstance();
	virtual LPCTSTR AppRootKey();
	void SetAppRootKey(LPCTSTR key);

	// Modeless dialogs should be created using one of the following
	// Create() methods(as per the MFC documentation). These are
	// provided to handle resource switching(like the new DoModal()).
	// ** Note: These methods are NOT declared virtual, yet duplicate
	// the signature of the inherited methods.
	BOOL Create(LPCTSTR lname, CWnd* parent = NULL);
	BOOL Create(UINT nIDTemplate, CWnd* parent = NULL);

	virtual void EnableFloatingWindows(BOOL allow); // INTERNAL USE ONLY
	virtual int IsMultiDocumentActivationEnabled(); // INTERNAL USE ONLY
	virtual int EnableMultiDocumentActivation(BOOL bEnable); // INTERNAL USE ONLY
	virtual BOOL DoDialogHelp(); // INTERNAL USE ONLY


	BOOL GetUseTips();
	void SetUseTips(BOOL useTips);

	HICON GetDialogIcon();
	void SetDialogIcon(HICON hIcon);

	// Data Exchange methods
public:
	BOOL DisplayData();
	virtual BOOL ExchangeData(BOOL bSaveAndValidate);
	BOOL ValidateData();

	// ClassWizard-controlled
public:
	//{{AFX_DATA(CNdUiBaseDialog)
	enum { IDD = 0 };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CNdUiBaseDialog)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);    // INTERNAL USE ONLY
	virtual INT_PTR DoModal();                      // INTERNAL USE ONLY
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	/*
	virtual void PostNcDestroy(); // INTERNAL USE ONLY
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs); // INTERNAL USE ONLY
	//}}AFX_VIRTUAL
	*/

protected:
	//{{AFX_MSG(CNdUiBaseDialog)
	/*
	afx_msg LONG OnNdUiMessage(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);// INTERNAL USE ONLY
	afx_msg BOOL OnHelpInfo(HELPINFO* lpHelpInfo);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnNdUiTimer(UINT nIDEvent);
	afx_msg BOOL OnNotify_ToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG
	*/
	DECLARE_MESSAGE_MAP()
};

//#endif // __OPENDWG_AFXEXT_H__