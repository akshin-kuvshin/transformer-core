//
// Копирайт (С) 2019, ООО «Нанософт разработка». Все права защищены.
// 
// Данное программное обеспечение, все исключительные права на него, его
// документация и сопроводительные материалы принадлежат ООО «Нанософт разработка».
// Данное программное обеспечение может использоваться при разработке и входить
// в состав разработанных программных продуктов при соблюдении условий
// использования, оговоренных в «Лицензионном договоре присоединения
// на использование программы для ЭВМ «Платформа nanoCAD»».
// 
// Данное программное обеспечение защищено в соответствии с законодательством
// Российской Федерации об интеллектуальной собственности и международными
// правовыми актами.
// 
// Используя данное программное обеспечение,  его документацию и
// сопроводительные материалы вы соглашаетесь с условиями использования,
// указанными выше. 
//

#ifndef __nanothunk_ui_h__
#define __nanothunk_ui_h__


#ifdef THUNK_NATIVE_API
	#undef THUNK_NATIVE_API
#endif // THUNK_NATIVE_API

#ifdef NANOTHUNKUI
	#define THUNK_NATIVE_API  __declspec(dllexport)
#else
	#define THUNK_NATIVE_API  __declspec(dllimport)
#endif

#ifdef CDialog
	#undef CDialog
#endif

#define CNcUiFileDialog  CFileDialog

class CElasticData;
class CNdUiComboBox;
class CNcUiTabMainDialog;
class CNcUiTabChildDialog;

#define MOVEX      0x00001
#define MOVEY      0x00002
#define MOVEXY     0x00003
#define ELASTICX   0x00010
#define ELASTICY   0x00020
#define ELASTICXY  0x00030

#ifndef WM_NCAD_KEEPFOCUS
	#ifndef WM_USER
		#define WM_NCAD_KEEPFOCUS  (0x0400 + 0x6D01)
	#else
		#define WM_NCAD_KEEPFOCUS  (WM_USER + 0x6D01)
	#endif
#endif



/*
#pragma pack (push, 8)
typedef struct _dlgControlTag {
DWORD    id;
DWORD    flags;
DWORD    pct;
} DLGCTLINFO, *PDLGCTLINFO;
#pragma pack (pop)
*/

class CPaletteSetTooltip;
class AFILE;

class CNdUiTab;
class CNdUiTabMainDialog;
class CNdUiTheme;
class CNdUiWorksheetDraw;
class CNdUiPaletteSet;
class CNdUiDropTarget;
class CNdUiVolumeDescriptor;
class CNdUiPathname;
class CNdUiTrackButtonDraw;
class CNdUiGroupCtrl;
class CNdUiSearchBoxEditor;
class CNdUiSearchBoxSearchButton;
class CNdUiSearchBoxClearButton;

class CNcFdUiImpFieldDialog;
class CNcFdUiFieldDialogHook;
class CNcFdUiFieldOptionDialog;
class CNcFdUiFormatList;

class CNdToolTipCtrl;
class NdImpMenuBar;
class NdToolTip;
class NdWthToolTip;


typedef CTypedPtrArray<CPtrArray, CNcFdUiFieldDialogHook*>  NcFdUiFieldDialogHookArray;

#define NCUI_MAX_TRUECOLOR_COMBOBOX_MRU   16
#define NCUI_TRUECOLOR_COMBOBOX_TABLE_SIZE  NCUI_MAX_TRUECOLOR_COMBOBOX_MRU + 9

#define CNcUiListBox CNdUiListBox
#define CNcUiListCtrl CNdUiListCtrl
#define CNcUiHeaderCtrl CNdUiHeaderCtrl

enum path_category {
	DRIVE_TYPE,
	UNC_TYPE,
	ROOT_TYPE,
	RELATIVE_TYPE
};

typedef enum {
	PATH_NOERR = 0,
	PATH_INVALID,
	PATH_BADOP,
	PATH_REFUSED,
	PATH_ERR
} PathErr;

typedef enum {
	NO_PATH = 0,
	NEW_PATH,
	WC_PATH,
	FILE_PATH,
	DIR_PATH,
	DEV_PATH,
} path_type;

enum FS_TYPE {
	NOFS,
	UKFS,
	NTFS,
	FAT,
	VFAT,
	HPFS,
	CDFS,
	HFS,
	UFS
};

typedef void (*NdUiBmpBtnFcnPtr)(CWnd*);

typedef struct NdUiGroupCtrlData
{
	NdUiGroupCtrlData() : nWndIndex(0), title(/*MSG0*/""), pWnd(NULL), dwBtnCookie(-1) {};
	int nWndIndex;
	CString title;
	CWnd* pWnd;
	DWORD dwBtnCookie;
} groupData;

typedef struct tagNDUI_DRAGDATA
{
	CWnd           *mpWnd;
	COleDataObject *mpDataObject;
	DWORD           mdwKeyState;
	POINTL          mPoint;
	DROPEFFECT      mDropEffect;
	DROPEFFECT      mDropList;
} NDUI_DRAGDATA,*PNDUI_DRAGDATA;

typedef NcArray<groupData> NDUIGROUPCTRLDATALIST;
typedef struct NdUiBmpBtnData
{
	NdUiBmpBtnData() : pBmp(NULL), fcnPtr(NULL),
		tooltip(/*MSG0*/""), dwCookie(0) {};
	CBitmap* pBmp;
	NdUiBmpBtnFcnPtr fcnPtr;
	CString tooltip;
	DWORD dwCookie;
} bmpBtnData;
typedef NcArray<bmpBtnData> NDUIHEADERBTNLIST;

enum OkHandlerErr
{
	NAV_OKHANDLER_SUCCESS = 0,
	NAV_OKHANDLER_NONFILESYSTEM,
	NAV_OKHANDLER_FAILURE,
	NAV_OKHANDLER_TOOLONG
};

typedef enum {

	kUnknownElements = -1,

	kPaletteFontCaption,
	kPaletteFontTab,
	kPaletteFontToolTip,
	kPaletteFont,
	kWorksheetFont,
	kWorksheetFontCaption,
	kInspectorItemFont,
	kInspectorRootFont,

	kPaletteBackground,
	kPaletteCaptionBackground,
	kPaletteCaptionInactive,
	kPaletteCaptionText,
	kPaletteCaptionInactiveText,
	kPaletteTabText,
	kPaletteTabBackground,
	kPaletteBorder,
	kPaletteTabShadow,
	kPaletteTabHighlight,
	kPaletteTabTextHilite,
	kPaletteTabSelectHilite,
	kPaletteToolTip,
	kPaletteToolTipText,
	kPaletteButtonText,
	kPaletteButtonTextDisabled,
	kPaletteButtonBorder,
	kPaletteItemText,
	kPaletteScrollBackground,
	kPaletteScrollThumb,
	kPaletteScrollArrow,

	kWorksheetBackground,
	kWorksheetCaptionBackground,
	kWorksheetCaptionText,
	kWorksheet3DBtnShadow,
	kWorksheetButtonText,
	kWorksheetButtonTextDisabled,
	kWorksheetScrollBackground,
	kWorksheetScrollThumb,
	kWorksheetBorder,
	kWorksheetGripHighlight,

	kInspector,
	kInspectorTop,
	kInspectorCat,
	kInspectorItem,
	kInspectorBorder,
	kInspectorBorderItem,
	kInspectorTextTop,
	kInspectorTextCat,
	kInspectorTextItem,
	kInspectorFGHighlight,
	kInspectorBGHighlight,
	kInspector3dShadow,
	kInspectorControl,
	kInspectorCatChevron1,
	kInspectorCatChevron2,
	kInspectorSubChevron,

	kPanelBackground,
	kPanelSashBackground,
	kPanelBorder,
	kControlBorder,
	kControlBackground,
	kDisabledControlBorder,
	kControlSupport,

	kPaletteFrameInnerBorder,
	kPaletteFrameOuterBorder,
	kPaletteFrameBackground,
	kPaletteFrameShadow,
	kInspectorTopGradient1,
	kInspectorTopGradient2,
	kPaletteScrollBackgroundBorder,
	kPaletteScrollBackgroundGradient1,
	kPaletteScrollBackgroundGradient2,
	kPaletteScrollSliderInactive,
	kPaletteScrollSliderActiveOuterBorder,
	kPaletteScrollSliderActiveOuterGradient1,
	kPaletteScrollSliderActiveOuterGradient2,
	kPaletteScrollSliderActiveOuterGradient3,
	kPaletteScrollSliderActiveOuterGradient4,
	kPaletteScrollSliderActiveInnerGradient1,
	kPaletteScrollSliderActiveInnerGradient2,
	kInspectorClosedOuterBorder,
	kInspectorOpenOuterBorder,
	kInspectorInnerBorder,

	kAnchorBarOuterBorder,
	kAnchorBarEmbossRightBottom,
	kAnchorBarEmbossLeftTop,
	kAnchorBarInnerHighlight,
	kAnchorBarGradient1,
	kAnchorBarGradient2,
	kAnchorBarActiveTitleBackground,
	kAnchorBarCaptionText,

	kGrabBarDotDark,
	kGrabBarDotLight,
	kControlBarTitleBackground,

	kAppFrameBorder,
	kAppFrameOuterBorder,

} NdUiThemeElement;

typedef bool (CALLBACK *LPFNADMENUCALLBACK)(unsigned int nItemId);

#define NCEDSYMUTIL_SERVICES_CURRENT_VERSION 100

class THUNK_NATIVE_API CNdUiDialog : public CNdUiBaseDialog
{
	DECLARE_DYNAMIC(CNdUiDialog)

public:
	CNdUiDialog(CWnd* pParent = NULL);   // standard constructor
	CNdUiDialog(UINT idd, CWnd* pParent = NULL, HINSTANCE hDialogResource = NULL);
	virtual ~CNdUiDialog();

protected:
	virtual void OnInitDialogBegin ();
	virtual void OnInitDialogFinish ();

public:
	BOOL    AddControl (CWnd *pControl);
	BOOL    AutoLoadControl (CWnd *pControl);
	BOOL    ForceControlRepaint (CWnd *pControl, BOOL bForce);
	BOOL    ForceControlResize (CWnd *pControl, LPRECT prect);
	BOOL    GetColumnSizes (CListCtrl *pList);
	CSize   *GetCurrentDelta ();
	void    GetDialogHelpTag (CString& tag);
	void    GetElasticMinMaxInfo (MINMAXINFO& mmi);
	LPVOID  GetElasticPointer ();
	BOOL    GetPixelData (CRect& r);
	void    LockDialogHeight ();
	void    LockDialogWidth ();
	BOOL    ReloadControl (CWnd *pControl, LPCTSTR lpResString);
	BOOL    RemoveControl (CWnd *pControl);
	BOOL    SaveColumnSizes (CListCtrl *pList);
	void    SetDialogMaxExtents (int width, int height);
	void    SetDialogMinExtents (int width, int height);
	void    SetDialogHelpTag (LPCTSTR tag);
	void    SetElasticSize (CSize& size, BOOL bRefreshDialog);
	void    SetPersistency (BOOL bFlag);
	void    SetRootKey (LPCTSTR key);
	void    SetTabSize (LPARAM lParam, BOOL bRefreshDialog);
	BOOL    StorePixelData ();

	BOOL MoveControlX(UINT id, LONG lMovePct);
	BOOL MoveControlXY(UINT id, LONG lMoveXPct, LONG lMoveYPct);
	BOOL MoveControlY(UINT id, LONG lMovePct);
	BOOL StretchControlX(UINT id, LONG lStretchPct);
	BOOL StretchControlXY(UINT id, LONG lStretchXPct, LONG lStretchYPct);
	BOOL StretchControlY(UINT id, LONG lStretchPct);

	//////////////////////////////////////////////////////////////////////////
	// DLGCTLINFO struct flags
	// MOVEX      0x00001
	// MOVEY      0x00002
	// MOVEXY     0x00003
	// ELASTICX   0x00010
	// ELASTICY   0x00020
	// ELASTICXY     0x00030
	BOOL SetControlProperty(PDLGCTLINFO lp, DWORD numElements);

	//////////////////////////////////////////////////////////////////////////
	// Registry section names
	BOOL GetDialogName(CString& name);
	void SetDialogName(LPCTSTR name);

	// Registry path
	// HKCU\Software\Nanosoft\nanoCAD\Dialogs\<DialogClass>
	BOOL GetDialogKey(CString& strKey);

	//////////////////////////////////////////////////////////////////////////
	// Load/Save data from registry
	// HKCU\Software\GeoniCS\NanoCAD\Dialogs\<DialogClass>
	BOOL SetDialogData(const CString& strValueName, const CString& strValue);
	BOOL SetDialogData(const CString& strValueName, DWORD dwValue);
	BOOL GetDialogData(const CString& strValueName, CString& strValue);
	BOOL GetDialogData(const CString& strValueName, DWORD& dwValue);

	virtual void OnOK();

private:
	CElasticData* m_pElasticData;
	BOOL m_bShowFirstTime;

	// ClassWizard-controlled
public:
	//{{AFX_DATA(CNdUiDialog)
	enum { IDD = 0 };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CNdUiDialog)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	virtual void OnDialogHelp();

protected:
	//{{AFX_MSG(CNdUiDialog)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

protected:
	CString   m_strDialogName;
};

class THUNK_NATIVE_API CNcUiDialog : public CNdUiDialog
{
	DECLARE_DYNAMIC(CNcUiDialog)

public:
	CNcUiDialog(CWnd* pParent = NULL);   // standard constructor
	CNcUiDialog(UINT idd, CWnd* pParent = NULL, HINSTANCE hDialogResource = NULL);
	virtual ~CNcUiDialog(){};

protected:
	//virtual BOOL    FindContextHelpFullPath (LPCTSTR fileName, CString& fullPath);

public:
	virtual CWnd    *AppMainWindow ();
	virtual HINSTANCE AppResourceInstance ();
	virtual LPCTSTR AppRootKey ();
	virtual void    EnableFloatingWindows (BOOL allow);
	virtual int EnableMultiDocumentActivation(BOOL bEnable);
	virtual int IsMultiDocumentActivationEnabled();

	virtual void OnDialogHelp();

	virtual BOOL OnInitDialog();

// ClassWizard-controlled
public:
	//{{AFX_DATA(CNcUiDialog)
	enum { IDD = 0 };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CNcUiDialog)
protected:
	//virtual void OnOK();
	//virtual void OnCancel();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNcUiDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdUiTab
class THUNK_NATIVE_API CNdUiTab : public CTabCtrl
{
	friend class CNcUiTabMainDialog;
	friend class CNdUiTabChildDialog;

	DECLARE_DYNAMIC(CNdUiTab);

public:
	         CNdUiTab ();
	virtual ~CNdUiTab ();

private:
	BOOL    m_bDirty;
	HWND    m_hwndFocus;
	int     m_iActiveTab;
	UINT    m_uApplyButtonID;

	BOOL    BringTabToFront(int iPos);
	void    PositionTabDialog (CNdUiTabChildDialog *pDialog);

public:
	BOOL    AddTab (int iPos, CString const& sTabname,
	                UINT uTemplateID, CNdUiTabChildDialog *pDialog);
	BOOL    AddTab (int iPos, UINT uTabStringID,
	                UINT uTemplateID, CNdUiTabChildDialog *pDialog);
	BOOL    DeleteItem (int iPos);
	BOOL    DestroyTab (int iPos, BOOL bUpdateData=FALSE);
	int     GetActiveTab ();
	CNdUiTabMainDialog *GetMainDialog ();
	int     GetTabIndex (CNdUiTabChildDialog *pDialog);
	CNdUiTabChildDialog *GetDialogPointer (int iPos);
	BOOL    IsDirty ();
	BOOL    RemoveTab (int iPos);
	int     SetActiveTab (int iPos);
	void    SetApplyButtonID (UINT uID);
	void    SetChildFocus ();
	void    SetDirty (BOOL bDirty=TRUE);
	void    SetValidationInfo (CDataExchange* pDX);

public:
	BOOL    DisplayData ();
	BOOL    ExchangeData (BOOL bSaveAndValidate);
	BOOL    ValidateData ();

public:
	protected:
	virtual void PreSubclassWindow();

protected:
	BOOL OnSelChange(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL OnSelChanging(NMHDR* pNMHDR, LRESULT* pResult);
	void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

class THUNK_NATIVE_API CNcUiTab : public CNdUiTab
{
	DECLARE_DYNAMIC(CNcUiTab)

public:
	CNcUiTab();
	virtual ~CNcUiTab();

protected:
	DECLARE_MESSAGE_MAP()
};

class THUNK_NATIVE_API CNdUiTabExtensionManager
{
public:
	CNdUiTabExtensionManager();
	virtual ~CNdUiTabExtensionManager();

public:
	int             AddExtendedTabs();
	virtual BOOL    AddTab(HINSTANCE hInstRes, UINT uTemplateID, LPCTSTR pszTabName, CNdUiTabChildDialog *pDialog);
	virtual LPCTSTR GetDialogName();
	void            Initialize(CNdUiTab *pTabCtrl, CNdUiTabMainDialog *pDlg);
	CNdUiTab*       GetTabControl() const;

private:
	BOOL            AddApplicationTabs(LPCTSTR pszAppName);

	CString             m_dlgName;
	CNcUiTabMainDialog* m_pDlg;
	CNdUiTab*           m_pTabCtrl;
};



//////////////////////////////////////////////////////////////////////////
// CNdUiTabMainDialog
class THUNK_NATIVE_API CNdUiTabMainDialog : public CNdUiDialog {
	friend class CNdUiTab;
	DECLARE_DYNAMIC(CNdUiTabMainDialog);
public:
	CNdUiTabMainDialog (
		UINT idd,
		CWnd *pParent=NULL,
		HINSTANCE hDialogResource=NULL
	);
private:
	int m_idDefaultButton;
	CNdUiTab *m_pTab;
	CString m_strTabIndex;
	BOOL    TranslateTabKey ();
protected:
	void    SetNcadTabPointer (CNdUiTab *pNcadTab);
public:
	int     AddExtendedTabs ();
	int     GetDefaultButton ();
	CNdUiTab *GetTabControl ();
	void    SetDefaultButton (int nIdDefaultButton);
	void    UpdateDefaultButton (HWND hFocusBefore, HWND hFocusAfter);
	void    SetInitialTabIndex(LPCTSTR strTabIndex) {m_strTabIndex = strTabIndex;}
	LPCTSTR GetInitialTabIndex() {return m_strTabIndex;}
	int     GetInitialRequestedTabIndex();
protected:
	virtual void    OnInitDialogBegin ();
	virtual void    OnInitDialogFinish ();
protected:
	CNdUiTabExtensionManager m_xtabManager;
public:
	virtual BOOL    AddApplicationTabs (LPCTSTR pszAppName);
	CNdUiTabExtensionManager *GetXtabPointer ();
public:
	BOOL    AddTab (
	                int iPos, LPCTSTR tabName,
	                UINT uTemplateID, CNdUiTabChildDialog *pDialog
	               );
	BOOL    AddTab (
	                int iPos, UINT uTabStringID,
	                UINT uTemplateID, CNdUiTabChildDialog *pDialog
	               );
	int     GetTabIndex (CNdUiTabChildDialog *pDialog);
	BOOL    RemoveTab (int iPos);
public:
	enum { IDD = 0 };
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual void OnOK();
	void RaiseApplyEvent();
protected:
	 void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiTabMainDialog
class THUNK_NATIVE_API CNcUiTabMainDialog : public CNdUiTabMainDialog {
	DECLARE_DYNAMIC(CNcUiTabMainDialog);
public:
	              CNcUiTabMainDialog (
	                UINT idd,
	                CWnd *pParent=NULL,
	                HINSTANCE hDialogResource=NULL
	            );
	virtual         ~CNcUiTabMainDialog ();
public:
	virtual CWnd    *AppMainWindow ();
virtual HINSTANCE AppResourceInstance ();
virtual LPCTSTR AppRootKey ();
virtual void    EnableFloatingWindows (BOOL allow);
virtual void    OnDialogHelp();
virtual int IsMultiDocumentActivationEnabled();
virtual int EnableMultiDocumentActivation(BOOL bEnable);
public:
	virtual BOOL    AddApplicationTabs (LPCTSTR pszAppName);
public:
	enum { IDD = 0 };
	protected:
	virtual void OnOK();
	virtual void OnCancel();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	DECLARE_MESSAGE_MAP()
};


// data styles
#define NC_ES_STRING   0x01
#define NC_ES_SYMBOL   0x02
#define NC_ES_NUMERIC  0x04
#define NC_ES_ANGLE    0x08

// behavior styles
#define NC_ES_VAL_ONKILLFOCUS     0x10
#define NC_ES_CONV_ONKILLFOCUS    0x20
#define NC_ES_SHOW_ERRMSG         0x40
#define NC_ES_ERRMSG_ALLOWIGNORE  0x80

// validation styles
#define NC_ES_NOZERO      0x100
#define NC_ES_NOBLANK     0x200
#define NC_ES_NONEGATIVE  0x400
#define NC_ES_INRANGE     0x800

typedef enum
{
	kNcUiError_None,     // No error; OK.
	kNcUiError_Blank,    // Data is blank
	kNcUiError_Symbol,   // Detected illegal symbol syntax
	kNcUiError_Numeric,  // Detected non-numeric data
	kNcUiError_Angle,    // Data does not represent an angle
	kNcUiError_Zero,     // Data is zero
	kNcUiError_Negative, // Data is negative
	kNcUiError_Range     // Data is out of range
} NCUI_ERROR_CODE;

#define NCUI_MAX_COMBOBOX_MRU            6
#define NCUI_MAX_TRUECOLOR_COMBOBOX_MRU  16

typedef enum
{
	kNcUiMRUCargo_Last    = -106, // Make sure this is the last entry
	kNcUiMRUCargo_Option2 = -105,
	kNcUiMRUCargo_Option1 = -104,
	kNcUiMRUCargo_Other2  = -103,
	kNcUiMRUCargo_Other1  = -102,
	kNcUiMRUCargo_None    = -101
} NCUI_MRU_CARGO;

//////////////////////////////////////////////////////////////////////////
//
class THUNK_NATIVE_API CNdUiDrawTipText
{
public:
	CNdUiDrawTipText(CDC& dc, CRect& rect, CString& text);

public:
	CDC&     m_dc;
	CRect&   m_rect;
	CString& m_text;
};

//////////////////////////////////////////////////////////////////////////
// CNcUiEdit
//////////////////////////////////////////////////////////////////////////
#define CNdUiEdit  CNcUiEdit

class THUNK_NATIVE_API CNcUiEdit : public CEdit
{
	DECLARE_DYNAMIC(CNcUiEdit)

public:
	CNcUiEdit();
	virtual ~CNcUiEdit();

	virtual void SetStyleMask(DWORD dwStyleMask);  // define behavior
	DWORD GetStyleMask();    // fetch the style
	BOOL IsStyleMaskSet(DWORD dwStyleMask); // verify styles

	// range value
	void SetRange(double dMin, double dMax);

	// data style conversion
	void Convert();
	BOOL ConvertData(CString& strValue);

	// data validation
	BOOL Validate();
	NCUI_ERROR_CODE ValidateData(const CString& strValue);

	BOOL HasChanged();   // detect user changes
	void SetDirty();

	CWnd *GetNdUiParent ();
	virtual void GetContentExtent (LPCTSTR text, int& width, int& height);
	void GetTextExtent (LPCTSTR text, int& width, int& height);
	void SetNdUiParent (CWnd *w);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnChange();
	afx_msg BOOL OnKillFocus();

	DWORD m_dwStyleMask;   // style bits (application-defined)

	CWnd* m_nduiParent;

public:
	BOOL   m_bChanged;    // value changed flag
	double m_dMinValue;  // min value for range checking
	double m_dMaxValue;  // max value for range checking
	BOOL   m_bTouch;      // flag to detect changes in text
};


//////////////////////////////////////////////////////////////////////////
// CNcUiNumericEdit
//////////////////////////////////////////////////////////////////////////
class THUNK_NATIVE_API CNcUiNumericEdit : public CNcUiEdit
{
	DECLARE_DYNAMIC(CNcUiNumericEdit)

public:
	CNcUiNumericEdit();
	virtual ~CNcUiNumericEdit();

	virtual void SetStyleMask(DWORD dwStyleMask);

protected:
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////////////////////////////////////////
// CNcUiAngleEdit
//////////////////////////////////////////////////////////////////////////
class THUNK_NATIVE_API CNcUiAngleEdit : public CNcUiEdit
{
	DECLARE_DYNAMIC(CNcUiAngleEdit)

public:
	CNcUiAngleEdit();
	virtual ~CNcUiAngleEdit();

	virtual void SetStyleMask(DWORD dwStyleMask);

protected:
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////////////////////////////////////////
// CNcUiSymbolEdit
//////////////////////////////////////////////////////////////////////////
class THUNK_NATIVE_API CNcUiSymbolEdit : public CNcUiEdit
{
	DECLARE_DYNAMIC(CNcUiSymbolEdit)

public:
	CNcUiSymbolEdit();
	virtual ~CNcUiSymbolEdit();

	virtual void SetStyleMask(DWORD dwStyleMask);

protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiStringEdit
//////////////////////////////////////////////////////////////////////////
class THUNK_NATIVE_API CNcUiStringEdit : public CNcUiEdit
{
	DECLARE_DYNAMIC(CNcUiStringEdit)

public:
	CNcUiStringEdit();
	virtual ~CNcUiStringEdit();

	virtual void SetStyleMask(DWORD dwStyleMask);

protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
//
class THUNK_NATIVE_API CNdUiListBox : public CListBox
{
	DECLARE_DYNAMIC(CNdUiListBox);

public:
	CNdUiListBox();
	virtual ~CNdUiListBox();

	// Misc.
protected:
	CPoint m_lastMousePoint;
	int    m_tipItem;
	CRect  m_tipRect;

public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual void GetContentExtent(int item, LPCTSTR text, int& width, int& height);
	int GetItemAtPoint(CPoint& p);
	void GetTextExtent(LPCTSTR text, int& width, int& height);
	BOOL IsOwnerDraw();

	// NdUi message handlers
protected:
	CWnd* m_nduiParent;

	virtual NDUI_REPLY DoNdUiMessage(NDUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam);
	virtual void OnDrawTip(CDC& dc);
	virtual BOOL OnDrawTipText(CNdUiDrawTipText& dtt);
	virtual NDUI_REPLY OnGetTipSupport(CPoint& p);
	virtual BOOL OnGetTipRect(CRect& r);
	virtual BOOL OnGetTipText(CString& text);
	virtual BOOL OnHitTipRect(CPoint& p);
public:
	CWnd* GetNdUiParent();
	void SetNdUiParent(CWnd* w);

	// Subclassed ComboLBox support
protected:
	BOOL           m_bComboBoxDraw;
	CNdUiComboBox* m_pComboBox;

public:
	CNdUiComboBox* GetComboBox();
	void SetComboBox(CNdUiComboBox* control);
	BOOL GetComboBoxDraw();
	void SetComboBoxDraw(BOOL comboBoxDraw);

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNdUiListBox)
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNdUiListBox)
	afx_msg LRESULT OnNdUiMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CNdUiComboBox window
class THUNK_NATIVE_API CNdUiComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CNdUiComboBox)

public:
	CNdUiComboBox();
	virtual ~CNdUiComboBox();

	// Fixed MFC Routines
public:
	// Use GetLBString() to circumvent GetLBText() errors.
	void GetLBString(int nIndex, CString& rString);

	// Misc.
protected:
	CPoint  m_lastMousePoint;
	CRect   m_tipRect;
	CString m_sToolTipText;

public:
	static bool IsVistaTheme();
	static bool IsInEdit(UINT nItemState);

	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual BOOL OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	virtual void GetContentExtent(LPCTSTR text, int& width, int& height);
	void GetTextExtent(LPCTSTR text, int& width, int& height);
	BOOL IsOwnerDraw();
	BOOL IsStatic();

	// NdUi message handlers
protected:
	CWnd* m_nduiParent;

	virtual NDUI_REPLY DoNdUiMessage(NDUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam);
	virtual void OnDrawTip(CDC& dc);
	virtual BOOL OnDrawTipText(CNdUiDrawTipText& dtt);
	virtual NDUI_REPLY OnGetTipSupport(CPoint& p);
	virtual BOOL OnGetTipRect(CRect& r);
	virtual BOOL OnGetTipText(CString& text);
	virtual BOOL OnHitTipRect(CPoint& p);
public:
	CWnd* GetNdUiParent();
	void SetNdUiParent(CWnd* w);

	CString GetToolTipText(void) const;
	BOOL SetToolTipText(const CString& sText);

	// Subclassed controls
protected:
	BOOL          m_bAutoDeleteEBox     : 1; // set to automatically delete
	BOOL          m_bAutoDeleteLBox     : 1; //  the edit or listbox controls
	BOOL          m_bSubclassedControls : 1; // set when all children are found
	CNdUiEdit*    m_pComboEBox;              // the child edit control (if any)
	CNdUiListBox* m_pComboLBox;              // the list box

public:
	CNdUiEdit* GetEditBox();
	void SetEditBox(CNdUiEdit* control, BOOL autoDelete);
	CNdUiListBox* GetListBox();
	void SetListBox(CNdUiListBox* control, BOOL autoDelete);

	// Validation style for subclassed EditBox
public:
	DWORD GetStyleMask();
	BOOL IsStyleMaskSet(DWORD mask);
	void SetStyleMask(DWORD mask);

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNdUiComboBox)
	//}}AFX_VIRTUAL

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CNdUiComboBox)
	afx_msg void OnPaint();
	afx_msg LRESULT OnNdUiMessage(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnGetToolTipText(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CNcUiComboBox window
class THUNK_NATIVE_API CNcUiComboBox : public CNdUiComboBox
{
	DECLARE_DYNAMIC(CNcUiComboBox);

public:
	CNcUiComboBox();
	virtual ~CNcUiComboBox();

	// Subclassed EditBox and Validation
public:
	CNcUiEdit* NcUiEditBox();
	BOOL Validate();
	NCUI_ERROR_CODE ValidateData(CString& x);
	void Convert();
	BOOL ConvertData(CString& x);
	void SetRange(double vMin, double vMax);

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNcUiComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNcUiComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////
// MRU ComboBox
class THUNK_NATIVE_API CNcUiMRUComboBox : public CNcUiComboBox
{
public:
	CNcUiMRUComboBox();
	virtual ~CNcUiMRUComboBox();

	// Misc.
	virtual void GetContentExtent(LPCTSTR text, int& width, int& height);
	virtual BOOL GetItemColors(DRAWITEMSTRUCT& dis, COLORREF& fgColor, COLORREF& bgColor, COLORREF& fillColor);

	// NdUi message handler
protected:
	virtual BOOL OnGetTipRect(CRect& r);

	// MRU control
protected:
	BOOL        m_bIsDynamicCreation : 1;   // TRUE if Create() is used, else FALSE.
	BOOL        m_bUseOption1        : 1;
	BOOL        m_bUseOption2        : 1;
	BOOL        m_bUseOther1         : 1;
	BOOL        m_bUseOther2         : 1;
	BOOL        m_bOther1Selected    : 1;
	BOOL        m_bOther2Selected    : 1;
	int         m_cargoOption1;
	int         m_cargoOption2;
	LOGPALETTE* m_logPalette;
	HPALETTE    m_hPalette;
	CPalette*   m_pOldPalette;
	int         m_itemHeight;
	int         m_lastSelection;
	int         m_mruCargo[NCUI_MAX_COMBOBOX_MRU];
	int         m_mruLen;
	CString     m_mruName[NCUI_MAX_COMBOBOX_MRU];

	virtual int CalcItemHeight();

	// The methods below are subfunctions to support the virtual DrawItem(..)
	// method which is called via message handler OnDrawItem(..).  Derived
	// classes may override the DrawItem(..) method and use these subfunctions
	// to customize the way DrawItemImage(..) is called. For example, the linetype
	// control does not use the cargo value as an index, thus it must replace
	// the cargo parameter of DrawItemImage(..) to instead pass the index of the
	// selection being drawn, then it's derived DrawItemImage(..) must resolve
	// that index to the object id of the linetype
	virtual void DrawItemImage(CDC& dc, CRect& r, INT_PTR cargo);
	void DrawItemImageFromCargo(CDC* dc, CRect& r, int i);
	void DrawTextAndFocusRect(LPDRAWITEMSTRUCT lpDrawItemStruct, CDC* dc, CRect& rItem, int i, COLORREF& fgColor,
	                          COLORREF& bgColor);
	void CreateAndSelectPalette(LPDRAWITEMSTRUCT lpDrawItemStruct, CDC* dc);
	void SetupForImageDraw(LPDRAWITEMSTRUCT lpDrawItemStruct, CDC* dc, CRect& rItem, CRect& rImage, COLORREF& fgColor,
	                       COLORREF& bgColor);
	void ResetAndRestorePalette(CDC* dc, int savedState);
	// end DrawItem(..) supporting methods

	BOOL FindCargoInMRU(int cargo);
	int GenerateCargoFromMRU(int seed);
	virtual BOOL GetOptionName(BOOL isOption2, CString& name);
	virtual BOOL GetOtherName(BOOL isOther2, CString& name);
	virtual void OnAddItems();
	virtual void OnComboBoxInit();
	virtual BOOL OnSelectOther(BOOL isOther2, int curSel, int& newSel);
	void SelectOther(BOOL isOther2);

public:
	int AddItemToList(LPCTSTR name, INT_PTR cargo);
	int AddItemToMRU(LPCTSTR name, int cargo); // Returns item index (or -1).
	void AddItems();
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual int ExtraWidth();
	int FindItemByCargo(INT_PTR cargo);  // Get corresponding item index.
	int GetCargoOption1();
	int GetCargoOption2();
	INT_PTR GetCurrentItemCargo();    // Get current item's cargo (or -1).
	INT_PTR GetItemCargo(int item);   // Get item's cargo (or -1).
	LOGPALETTE* GetLogPalette();
	HPALETTE GetPalette();
	BOOL GetUseOption1();
	BOOL GetUseOption2();
	BOOL GetUseOther1();
	BOOL GetUseOther2();
	virtual int ImageWidth();
	int InsertItemInList(int index, LPCTSTR name, INT_PTR cargo);
	int ItemHeight();
	void RecalcHeight();
	void RemoveItemFromMRU(int cargo);
	void SetCargoOption1(int cargo);
	void SetCargoOption2(int cargo);
	void SetLastSelection(int sel);
	void SetLogPalette(LOGPALETTE* logPalette);
	void SetPalette(HPALETTE hPalette);
	void SetUseOption1(BOOL use);
	void SetUseOption2(BOOL use);
	void SetUseOther1(BOOL use);
	void SetUseOther2(BOOL use);

	// Aliases for OptionX and OtherX
public:
	BOOL GetUseByBlock();
	BOOL GetUseByLayer();
	BOOL GetUseOther();
	BOOL GetUseWindows();
	void SetUseByBlock(BOOL use);
	void SetUseByLayer(BOOL use);
	void SetUseOther(BOOL use);
	void SetUseWindows(BOOL use);

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNcUiMRUComboBox)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNcUiMRUComboBox)
	afx_msg BOOL OnCloseUp();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnDropDown();
	afx_msg BOOL OnSelEndOk();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiLineWeithComboBox
//////////////////////////////////////////////////////////////////////////

// ComboBox control in the dialog should have styles
// CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS
// and should not have style CBS_SORT

class THUNK_NATIVE_API CNcUiLineWeightComboBox : public CNcUiMRUComboBox
{
	DECLARE_DYNAMIC(CNcUiLineWeightComboBox)
public:
	CNcUiLineWeightComboBox();
	virtual ~CNcUiLineWeightComboBox();

	// MRU control
	// protected:
	virtual void DrawItemImage(CDC& dc, CRect& r, INT_PTR cargo);
	virtual int  ImageWidth();
	virtual void OnAddItems();

public:
	// lw AutoCAD lineweight, ranging from NcDb::kLnWt000 to NcDb::kLnWt211
	int FindItemByLineWeight(int lw);  // Get corresponding item index.
	int GetItemLineWeight(int item);   // Get item's LW (or -1).

	int GetCurrentItemLineWeight(); // Get current item's LW (or -1).
	int GetCurrentLayerLineWeight();

	double GetLineWeightScale();
	void SetLineWeightScale(double scale);

	void SetUseDefault(BOOL use);
	//virtual int ImageWidth();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// LineWeight control
protected:
	double m_lineWeightScale;

private:
	BOOL m_bUseDefault;

	// List of displayed lineweights
	void* m_plineweights;
	//lineweight::list m_lineweights;
};

class THUNK_NATIVE_API CNcUiColorComboBox : public CNcUiMRUComboBox
{
public:
	CNcUiColorComboBox();
	virtual ~CNcUiColorComboBox();

	// MRU control
protected:
	virtual void DrawItemImage(CDC& dc, CRect& r, INT_PTR cargo);
	virtual void OnAddItems();
	virtual BOOL OnSelectOther(BOOL isOther2, int curSel, int& newSel);

	// Color control
protected:
	int m_blockColorIndex;

	virtual BOOL GetOtherColorIndex(int defaultColorIndex, int layerColorIndex, BOOL enableMetaColors, int& colorIndex);
	virtual BOOL GetWindowsColor(COLORREF& color);
	virtual BOOL GetOtherName(BOOL isOther2, CString& name);

	void RGBFill(CDC& dc, CRect& rFill);
public:
	int AddColorToMRU(int colorIndex);  // Returns item index (or -1).
	int FindItemByColorIndex(int colorIndex); // Get corresponding item index.
	int GetBlockColorIndex();
	virtual COLORREF GetColorFromIndex(int colorIndex); // Returns corresponding color.
	virtual int GetColorIndex(COLORREF color);  // Returns color index (or -1).
	int GetCurrentItemColorIndex();  // Get current item's color index (or -1).
	virtual int GetCurrentLayerColorIndex();
	int GetItemColorIndex(int item);    // Get item's color index (or -1).
	virtual COLORREF LookupColor(int colorIndex, LOGPALETTE* logPalette); // Returns corresponding raw color.
	void SetBlockColorIndex(int colorIndex);

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNcUiColorComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNcUiColorComboBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

/////////////////////////////////////////////////////////////////////////////
// CNcUiAngleComboBox window
//
// ComboBox with the persistent CNcUiAngleEdit control for the Edit box

class THUNK_NATIVE_API CNcUiAngleComboBox : public CNcUiComboBox {
	DECLARE_DYNAMIC(CNcUiAngleComboBox);

public:
	CNcUiAngleComboBox ();
	virtual ~CNcUiAngleComboBox ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNcUiAngleComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNcUiAngleComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CNcUiNumericComboBox window
//
// ComboBox with the persistent CNcUiNumericEdit control for the Edit box

class THUNK_NATIVE_API CNcUiNumericComboBox : public CNcUiComboBox {
	DECLARE_DYNAMIC(CNcUiNumericComboBox);

public:
	CNcUiNumericComboBox ();
	virtual ~CNcUiNumericComboBox ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNcUiNumericComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNcUiNumericComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CNcUiStringComboBox window
//
// ComboBox with the persistent CNcUiStringEdit control for the Edit box

class THUNK_NATIVE_API CNcUiStringComboBox : public CNcUiComboBox {
	DECLARE_DYNAMIC(CNcUiStringComboBox);

public:
	            CNcUiStringComboBox ();
	virtual         ~CNcUiStringComboBox ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNcUiStringComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNcUiStringComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CNcUiSymbolComboBox window
//
// ComboBox with the persistent CNcUiSymbolEdit control for the Edit box

class THUNK_NATIVE_API CNcUiSymbolComboBox : public CNcUiComboBox {
	DECLARE_DYNAMIC(CNcUiSymbolComboBox);

public:
	            CNcUiSymbolComboBox ();
	virtual         ~CNcUiSymbolComboBox ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNcUiSymbolComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNcUiSymbolComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiLTypeRecord
class CNcUiLTypeRecord : public CObject {
public:
	CString & ltypeName();
	void setLTypeName(CString sName);
	NcDbObjectId objectId();
	void setObjectId(NcDbObjectId id);
	BOOL isDependent();
	void setIsDependent(BOOL bValue);

private:
	CString m_strLTypeName;
	NcDbObjectId m_idObjectId;
	BOOL m_bIsDependent;
};

//////////////////////////////////////////////////////////////////////////
// Inlines for CNcUiLTypeRecord
inline CString & CNcUiLTypeRecord::ltypeName()
{
	return m_strLTypeName;
}

inline void CNcUiLTypeRecord::setLTypeName(CString sName)
{
	m_strLTypeName = sName;
}

inline NcDbObjectId CNcUiLTypeRecord::objectId()
{
	return m_idObjectId;
}

inline void CNcUiLTypeRecord::setObjectId(NcDbObjectId id)
{
	m_idObjectId = id;
}

inline BOOL CNcUiLTypeRecord::isDependent()
{
	return m_bIsDependent;
}

inline void CNcUiLTypeRecord::setIsDependent(BOOL bValue)
{
	m_bIsDependent = bValue;
}
//////////////////////////////////////////////////////////////////////////
//
class THUNK_NATIVE_API CNdUiOwnerDrawButton : public CButton
{
	friend class CNdUiODButtonThemeModReactor;  // INTERNAL USE ONLY

	DECLARE_DYNAMIC(CNdUiOwnerDrawButton)

public:
	CNdUiOwnerDrawButton();
	virtual ~CNdUiOwnerDrawButton();

protected:
	CPoint m_lastMousePoint;
	CRect  m_tipRect;

	//    CNdUiTheme *m_pTheme;  // INTERNAL USE ONLY

	// NdUi message handler
protected:
	CWnd* m_nduiParent;

	virtual NDUI_REPLY DoNdUiMessage(NDUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam);

	virtual void OnDrawTip(CDC& dc);
	virtual BOOL OnDrawTipText(CNdUiDrawTipText& dtt);
	virtual NDUI_REPLY OnGetTipSupport(CPoint& p);
	virtual BOOL OnGetTipRect(CRect& r);
	virtual BOOL OnGetTipText(CString& text);
	virtual BOOL OnHitTipRect(CPoint& p);
public:
	CWnd* GetNdUiParent();
	void SetNdUiParent(CWnd* w);

	virtual void SetTracking(BOOL b)
	{
		m_bIsTrackButton = b;
	};

	//virtual CNdUiTheme* SetTheme(CNdUiTheme* pTheme);  // INTERNAL USE ONLY

	//Owner Draw routines
protected:
	static const UINT_PTR m_timerEvent;
	BOOL                  m_bEnableDragDrop  : 1;
	BOOL                  m_bEnableFastDraw  : 1;
	BOOL                  m_bEnablePointedAt : 1;
	BOOL                  m_bIsPointedAt     : 1;
	BOOL                  m_bIsStatic        : 1;
	BOOL                  m_bIsToolButton    : 1;
	BOOL                  m_bIsTrackButton   : 1;
	UINT_PTR              m_timerId;

	// members added for XP look and feel
	int  m_nPartId;
	int  m_nStateId;
	UINT m_uEdge;
	BOOL m_bMouseHover;

	virtual void DrawBorder(CDC* pDC, CRect& r, COLORREF cr);
	virtual void DrawHotBorder();
	virtual void DrawButton(CDC& dc, int w, int h, BOOL isDefault, BOOL isDisabled, BOOL isSelected, BOOL isFocused);
	virtual void DrawPushButtonBorder(CDC& dc, CRect& rButton, BOOL isDefault, BOOL isSelected);
	virtual void DrawToolButtonBorder(CDC& dc, CRect& rButton, BOOL isSelected, BOOL isFocused);
	void DrawTransparentBitmap(CDC& dc, CBitmap& bmp, int x, int y, int w, int h, BOOL isDisabled);
	void DrawContentText(CDC& dc, CString sText, CRect& rcText, BOOL isDisabled);
	BOOL GetIsPointedAt();
	void SetIsPointedAt(BOOL isPointedAt);
	virtual BOOL OnAutoLoad();
	virtual void OnDragDrop(HDROP hDropInfo);
	virtual void OnPointedAt(BOOL isPointedAt);
	virtual BOOL OnReload(LPCTSTR strResId);
	void StartTimer(DWORD ms = 50);
	void StopTimer();

	//virtual void ThemeModified(NdUiThemeElement element);  // INTERNAL USE ONLY

public:
	BOOL AutoLoad();
	BOOL GetEnableDragDrop();
	void SetEnableDragDrop(BOOL allow);
	BOOL GetEnableFastDraw();
	void SetEnableFastDraw(BOOL allow);
	BOOL GetEnablePointedAt();
	void SetEnablePointedAt(BOOL allow);
	BOOL GetIsStatic();
	void SetIsStatic(BOOL isStatic);
	BOOL GetIsToolButton();
	void SetIsToolButton(BOOL isToolButton);
	BOOL Reload(LPCTSTR strResId);

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNdUiOwnerDrawButton)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNdUiOwnerDrawButton)
	afx_msg LRESULT OnNdUiMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
	afx_msg void OnNcDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	HANDLE GetVisualStylesTheme()
	{
		return m_hVS;
	}
private:
	CNdUiODButtonThemeModReactor* m_pThemeModReactor;  // INTERNAL USE ONLY
	HANDLE                        m_hVS;      // INTERNAL USE ONLY
};

//////////////////////////////////////////////////////////////////////////
// CNcUiOwnerDrawButton
class THUNK_NATIVE_API CNcUiOwnerDrawButton : public CNdUiOwnerDrawButton
{
	DECLARE_DYNAMIC(CNcUiOwnerDrawButton)

public:
	CNcUiOwnerDrawButton();
	virtual ~CNcUiOwnerDrawButton();

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNcUiOwnerDrawButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNcUiOwnerDrawButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CNdUiBitmapButton
class THUNK_NATIVE_API CNdUiBitmapButton : public CNdUiOwnerDrawButton
{
	DECLARE_DYNAMIC(CNdUiBitmapButton)

public:
	CNdUiBitmapButton();
	virtual ~CNdUiBitmapButton();

	BOOL GetAutoSizeToBitmap();
	void SetAutoSizeToBitmap(BOOL autoSizeToBitmap);
	void SizeToBitmap();
	void SetBitmapOffsets(int nBorderOffset, int nFocusRectOffset);
	BOOL LoadBitmap(LPCTSTR strResId);

protected:
	// Owner Draw routines
	virtual void DrawButton(CDC& dc, int w, int h, BOOL isDefault, BOOL isDisabled, BOOL isSelected, BOOL isFocused);
	virtual BOOL OnAutoLoad();
	virtual BOOL OnReload(LPCTSTR strResId);

	// Bitmap Button routines
	virtual BOOL OnLoadBitmap(LPCTSTR strResId);
	BOOL LoadBitmapResource(LPCTSTR strResId, CBitmap& bmp, HINSTANCE hInst);
	void CalcBitmapSize();

	BOOL    m_bAutoSizeToBitmap;
	CBitmap m_bmp;
	CString m_bmpResId;
	int     m_bmpHeight;
	int     m_bmpWidth;
	int     m_bmpX;
	int     m_bmpY;
	int     m_focusRectOffset;

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNdUiBitmapButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNdUiBitmapButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiBitmapButton
class THUNK_NATIVE_API CNcUiBitmapButton : public CNdUiBitmapButton
{
	DECLARE_DYNAMIC(CNcUiBitmapButton)

public:
	CNcUiBitmapButton();
	virtual ~CNcUiBitmapButton();

	// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CNcUiBitmapButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNcUiBitmapButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#define NDUI_DOCK_POSITION_TOOL_KEY      NDUI_XML_DOCK_TOOL_INFO
#define NDUI_DOCK_STARTUP_TOOL_KEY       NDUI_XML_DOCK_STARTUP_INFO
#define NDUI_XML_ROOT                    _T("AdUiTools")
#define NDUI_XML_DOCK_TOOL_INFO          _T("ToolsInfo")
#define NDUI_XML_DOCK_TOOL               _T("Tool")
#define NDUI_XML_DOCK_TOOL_CLSID         _T("CLSID")
#define NDUI_XML_DOCK_STARTUP_INFO       _T("StartupInfo")
#define NDUI_XML_DOCK_STARTUP_TOOL_NAME  _T("ToolName")
#define NDUI_XML_DOCK_STARTUP_CMD_NAME   _T("Command")

#define ID_NDUI_ALLOWDOCK  0x1001
#define ID_NDUI_HIDEBAR    0x1002

#define NDUI_DOCK_CS_DESTROY_ON_CLOSE  0x01 // closing the floating window closes the control bar
#define NDUI_DOCK_CS_STDMOUSECLICKS    0x02 // standard mouse handling for the menu

#define NDUI_DOCK_NF_SIZECHANGED   0x01
#define NDUI_DOCK_NF_STATECHANGED  0x02
#define NDUI_DOCK_NF_FRAMECHANGED  0x02

//////////////////////////////////////////////////////////////////////////
// CNdUiDockControlBar
class THUNK_NATIVE_API CNdUiDockControlBar : public CControlBar
{
	friend class CNdUiDockFrame;
	friend class CNdUiPaletteSetDockFrame;
	friend class CNdUiDockDragContext;
	friend class CNdUiDockBar;
	friend class CNdUiDockBarMutator;
	friend class CNdUiDockControlBarThemeModReactor; // INTERNAL USE ONLY

// Attributes
private:
	static CObArray*  m_paBars;      // array of dynamically allocated bars
	CSize             m_FloatSize;      // size when docked
	CSize             m_HorzDockSize;      // size when docked horizontal
	CSize             m_VertDockSize;      // size when docked vertical
	CPoint            m_FloatingPosition;     // floating position
	bool              m_bAllowDockingMenuItemState; // allow docking menu item state
	int               m_Style;       // style flags
	CSize             m_PrevSize;
	BOOL              m_bPrevFloating;
	CNdUiBitmapButton m_closeBtn;
	CNdUiBitmapButton m_pinBtn;
	CLSID             m_ID;
	bool              m_bShowCloseButton;     // Show and draw close button on docked bar

	static int        m_nLastBarID;
	static bool       m_bToolsRestartMode;   // Boolean variable to signal start/end of
	// restarting of tools (usually set/cleared
	// by the the application during startup.

	// variables which reflect persisted dock/float rect for the controlbar
	// across application sessions
	CRect m_PersistedDockRect;
	CRect m_PersistedFloatRect;

private:
	void SetDockFlag(DWORD dwStyle);
	void Resized(int cx, int cy, BOOL bFloating, int flags);
	LRESULT AddMenuItems(WPARAM wParam, LPARAM lParam);
	static void RemoveBars();
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	void PaintBar(CDC* pDC);
	void Draw3DRect(CDC* pDC, LPRECT lpRect, CPen* pPenGray);
	LRESULT WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
	void LoadDefaultLocation(UINT nOrientation, RECT* pSizeFloating);

public:
	CNdUiDockControlBar(int nStyle = NDUI_DOCK_CS_STDMOUSECLICKS);

	BOOL Create(CWnd* pParent, LPCTSTR lpszTitle, UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
	            const RECT& rect = CFrameWnd::rectDefault);
	BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
	            UINT nID, CCreateContext* pContext = NULL);

	void EnableDocking(DWORD dwDockStyle);
	void TileInRow();
	BOOL IsFloating();

	void DockControlBar(UINT nOrientation, RECT* pRect);
	void RestoreControlBar(UINT nPreferredOrientation = AFX_IDW_DOCKBAR_LEFT, CRect* pSizeFloating = NULL);

	void InitFloatingPosition(CRect* pSizeFloating);
	void GetFloatingRect(CRect* pFloatingPos);

	// access methods which returns the cached dock/float
	// rect which would have persisted in the fixed profile
	// across autocad sessions.
	void GetPersistedDockingRect(CRect* pDockRect);
	void GetPersistedFloatingRect(CRect* pFloatRect);

	// Get/Set methods to signal begining and end of
	// restarting of tools. Set and cleared by the
	// application to position controlbars inside
	// one of the four dockbars during the application
	// startup.
	static void SetToolsRestartMode(bool bMode);
	static bool GetToolsRestartMode();

	void SetAllowDockingMenuItemState(bool bState)
	{
		m_bAllowDockingMenuItemState = bState;
	}
	bool AllowDockingMenuItemState()
	{
		return m_bAllowDockingMenuItemState;
	}

	void SetToolID(CLSID* pCLSID);
	CLSID* GetToolID()
	{
		return &m_ID;
	}
	DWORD GetDockStyle()
	{
		return m_dwDockStyle;
	}

	// Called in response to the application's query to take the focus back.
	// Default implementation returns false, keeping the focus in the tool window.
	virtual bool CanFrameworkTakeFocus()
	{
		return false;
	}

	// Loads the data from xml file
	virtual BOOL Load(IUnknown* pUnk);
	// Saves the data to xml file
	virtual BOOL Save(IUnknown* pUnk);

	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	bool Anchored();
	bool Anchored(bool bHiddenReturnsLastState);

	bool AdjustVertDockedBarHeight(int nHeight);
	static bool ShowPalettes();
	static bool HidePalettes();

	// Returns the the current theme being used
	//CNdUiTheme* GetTheme();        // INTERNAL USE ONLY

	// Sets the the current theme to be used
	//CNdUiTheme* SetTheme(CNdUiTheme* pTheme);  // INTERNAL USE ONLY

	// Theme modified callback
	//void ThemeModified(NdUiThemeElement element); // INTERNAL USE ONLY

	// Returns the title bar width/height
	LONG GetTitleBarSize();

#ifdef _DEBUG
	void AssertValid() const;
#endif

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNdUiDockControlBar)
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	virtual ~CNdUiDockControlBar();

protected:
	enum
	{
		btnWidth   = 12,
		btnHeight  = 12,
		idCloseBtn = 10001,
		idPinBtn   = 10002
	};

protected:
	// windows message handlers
	//{{AFX_MSG(CNdUiDockControlBar)
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAllowDock();
	afx_msg void OnAnchor();
	afx_msg void OnAnchorLeft();
	afx_msg void OnAnchorRight();
	afx_msg void OnHideBar();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG


protected:
	void GetUsedRect(CRect& rect);
	void ShowCloseButton(bool bShow)
	{
		m_bShowCloseButton = bShow;
	};
	bool CloseButtonVisible()
	{
		return m_bShowCloseButton;
	};
	void RepositionOrHideButtons();
	static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

	// Overridable functions
	virtual void PaintControlBar(CDC* pDC);
	virtual BOOL CreateControlBar(LPCREATESTRUCT lpCreateStruct);
	virtual void SizeChanged(CRect* lpRect, BOOL bFloating, int flags) {}
	virtual bool OnClosing();
	virtual void GetFloatingMinSize(long* pnMinWidth, long* pnMinHeight);
	virtual BOOL AddCustomMenuItems(LPARAM hMenu);
	virtual void OnUserSizing(UINT nSide, LPRECT pRect) {};

	DECLARE_DYNAMIC(CNdUiDockControlBar)
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////////////////////////////////////////
// CNcUiDockControlBar
class THUNK_NATIVE_API CNcUiDockControlBar : public CNdUiDockControlBar
{
public:
	CNcUiDockControlBar() {}

protected:
	virtual bool CanFrameworkTakeFocus()
	{
		return false;
	}
};

THUNK_NATIVE_API CRuntimeClass* NdUiGetRegisteredPaletteSetFloatingFrameClass(void);
THUNK_NATIVE_API CRuntimeClass* NdUiSetFloatingFrameClass(CRuntimeClass* pNewClass);

// AutoGen:

//////////////////////////////////////////////////////////////////////////
// NcEditorReactor3
class NcEditorReactor3 : public NcEditorReactor2 {
public:
	NCRX_DECLARE_MEMBERS(NcEditorReactor3);
	virtual void fullRegenEnded(NcDbDatabase*  pDb,
	                            const NcDbIntArray & regenedViewports) {}
	virtual void curDocOpenUpgraded(NcDbDatabase* pDb,
	                                const CNdUiPathname& filename)
	{}
	virtual void curDocOpenDowngraded(NcDbDatabase* pDb,
	                                  const CNdUiPathname& filename)
	{}
};

//////////////////////////////////////////////////////////////////////////
// CNcFdUiFieldDialog
class THUNK_NATIVE_API CNcFdUiFieldDialog : public CNdUiDialog {
	friend CNcFdUiImpFieldDialog;
	DECLARE_DYNAMIC(CNcFdUiFieldDialog)
public:
	CNcFdUiFieldDialog(CWnd* pParent = NULL);
	virtual ~CNcFdUiFieldDialog();
	INT_PTR         DoModal                 (NcDbField*& pField,
	                                         BOOL bEdit,
	                                         NcDbDatabase* pDb);
	NcDbField   *   GetFieldToEdit          (void) const;
	BOOL            SetFieldCodeReadOnly    (BOOL bReadOnly = TRUE);
	CString         GetFieldCode            (void) const;
	BOOL            SetFieldCode            (LPCTSTR pszExpr);
	BOOL            IsFieldCodeDirty        (void);
	CEdit       *   GetFieldCodeEditCtrl    (void);
	BOOL            GetCurrentField         (UINT* pFieldId,
	                                         UINT* pCatId) const;
	BOOL            SelectField             (UINT uFieldId,
	                                         UINT uCatId);
	CNcFdUiFieldOptionDialog* GetOptionDialog(void) const;
public:
	void            BeginEditorCommand      (void);
	void            CompleteEditorCommand   (BOOL restoreDialogs = TRUE);
	void            CancelEditorCommand     (void);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL    OnInitDialog            (void);
	virtual void    OnOK                    (void);
	virtual void    OnCancel                (void);
	 void    OnCbnSelChangeCategoryList(void);
	 void    OnLbnSelChangeFieldNameList(void);
	 void    OnEnChangeFieldCode     (void);
	 void    OnDialogHelp            (void);
	 LRESULT OnFormatChanged         (WPARAM wParam,
	                                  LPARAM lParam);
	 LRESULT OnBeginFormatExDialog   (WPARAM wParam,
	                                  LPARAM lParam);
	 LRESULT OnEndFormatExDialog     (WPARAM wParam,
	                                  LPARAM lParam);
private:
	friend class NcFdUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNcFdUiFieldDialogHook
class THUNK_NATIVE_API CNcFdUiFieldDialogHook : public CObject {
public:
	CNcFdUiFieldDialogHook(void);
	~CNcFdUiFieldDialogHook(void);
	virtual BOOL    CreateInstance          (CNcFdUiFieldDialogHook*& pHook);
	virtual int     GetEvaluatorIds         (CStringArray& evalIds);
	virtual BOOL    BeginFieldDialog        (CNcFdUiFieldDialog* pFieldDlg,
	                                         NcDbDatabase* pDb,
	                                         int nContext);
	virtual BOOL    EndFieldDialog          (int nRet);
	virtual BOOL    SetFieldToEdit          (NcDbField* pField);
	NcDbDatabase *  GetDatabase             (void) const;
	virtual BOOL    GetCategoryNames        (UINT uMinUnusedCatId,
	                                         CStringArray& catNames,
	                                         CUIntArray& catIds);
	virtual BOOL    GetFieldNames           (UINT uCatId,
	                                         UINT uMinUnusedFieldId,
	                                         CStringArray& fieldNames,
	                                         CUIntArray& fieldIds,
	                                         BOOL& bSort);
	virtual BOOL    GetOptionDialog         (UINT uFieldId,
	                                         CNcFdUiFieldOptionDialog*& pOptionDlg);
	virtual CString GetPreview              (LPCTSTR pszFormatType,
	                                         LPCTSTR pszFormat);
	virtual BOOL    UpdateFieldCode         (void);
	virtual BOOL    OnFieldSelected         (UINT uFieldId);
	virtual BOOL    CreateField             (UINT uFieldId,
	                                         NcDbField*& pField);
private:
	friend class NcFdUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNcFdUiFormatList
class THUNK_NATIVE_API CNcFdUiFormatList : public CNdUiListBox {
	DECLARE_DYNAMIC(CNcFdUiFormatList)
public:
	CNcFdUiFormatList(void);
	virtual ~CNcFdUiFormatList(void);
	void            SetRootKey              (LPCTSTR pszKey);
	void            SetPersistency            (BOOL bPersist);
	CString            GetFormatType            (void) const;
	BOOL            SetFormatType            (LPCTSTR pszFormatType);
	int                GetCurrentFormat        (CString& sDisplayName,
	                                            CString& sFormatString) const;
	BOOL            SetCurrentFormat        (LPCTSTR pszDisplayName,
	                                         LPCTSTR pszFormatString);
	BOOL            Refresh                    (void);
protected:
	 int     OnCreate                (LPCREATESTRUCT lpCreateStruct);
	 void     OnDestroy                (void);
	DECLARE_MESSAGE_MAP()
private:
	friend class NcFdUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNcFdUiFieldFormatList
class THUNK_NATIVE_API CNcFdUiFieldFormatList : public CNcFdUiFormatList {
	DECLARE_DYNAMIC(CNcFdUiFieldFormatList)
};

//////////////////////////////////////////////////////////////////////////
// CNcFdUiFieldManager
class THUNK_NATIVE_API CNcFdUiFieldManager : public CObject {
public:
	CNcFdUiFieldManager(void);
	~CNcFdUiFieldManager(void);
	BOOL            RegisterFieldDialogHook    (CNcFdUiFieldDialogHook* pDlgHook);
	BOOL            UnregisterFieldDialogHook(const CNcFdUiFieldDialogHook* pDlgHook);
	int                GetRegisteredDialogHooks(NcFdUiFieldDialogHookArray& hooks);
private:
	friend class NcFdUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNcFdUiFieldOptionDialog
class THUNK_NATIVE_API CNcFdUiFieldOptionDialog : public CNdUiDialog {
	friend CNcFdUiFieldDialog;
	friend CNcFdUiImpFieldDialog;
	DECLARE_DYNAMIC(CNcFdUiFieldOptionDialog)
public:
	CNcFdUiFieldOptionDialog(CNcFdUiFieldDialogHook* pDialogHook, CNcFdUiFieldDialog* pFieldDlg,
	                         UINT nIDTemplate, HINSTANCE hDialogResource = NULL);
	virtual ~CNcFdUiFieldOptionDialog();
	CNcFdUiFieldDialogHook* GetFieldDialogHook(void) const;
	CNcFdUiFieldDialog* GetFieldDialog      (void) const;
	virtual BOOL    Create                  (CWnd* pParent);
public:
	virtual BOOL    Create                  (LPCTSTR lpszTemplateName,
	                                         CWnd* pParent = NULL);
	virtual BOOL    Create                  (UINT nIDTemplate,
	                                         CWnd* pParent = NULL);
protected:
	virtual BOOL    OnSetActive             (void);
	virtual BOOL    OnKillActive            (void);
	virtual BOOL    OnFieldSelected         (UINT uNewFieldId);
protected:
	virtual void    OnOK                    (void);
	virtual void    OnCancel                (void);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	 LRESULT OnFormatChanged         (WPARAM wParam,
	                                  LPARAM lParam);
	 LRESULT OnBeginFormatExDialog   (WPARAM wParam,
	                                  LPARAM lParam);
	 LRESULT OnEndFormatExDialog     (WPARAM wParam,
	                                  LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	friend class NcFdUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNcFdUiFormatDialog
class THUNK_NATIVE_API CNcFdUiFormatDialog : public CNdUiDialog {
	DECLARE_DYNAMIC(CNcFdUiFormatDialog)
public:
	CNcFdUiFormatDialog(CWnd* pParent, BOOL bNew);
	virtual ~CNcFdUiFormatDialog();
	virtual BOOL     Create                    (CWnd* pParent);
	CNcFdUiFormatList* GetFormatList    (void);
	CString            GetFormatType            (void) const;
	BOOL            SetFormatType            (LPCTSTR pszFormatType);
	int                GetCurrentFormat        (CString& sDisplayName,
	                                            CString& sFormatString,
	                                            CString& sVersion) const;
	BOOL            SetCurrentFormat        (LPCTSTR pszDisplayName,
	                                         LPCTSTR pszFormatString);
	BOOL            SetFormatPreviewReadOnly(BOOL bReadOnly = TRUE);
	BOOL            SetFormatPreviewLabel    (LPCTSTR pszText);
	BOOL            SetFormatPreviewText    (LPCTSTR pszPreviewText,
	                                         const NcValue& fieldValue);
	BOOL            SetDialogStyle          (int nStyle);
protected:
	virtual void    DoDataExchange          (CDataExchange* pDX);
	 void    OnDestroy               (void);
	 void    OnLbnSelChangeFormatList(void);
	 void     OnEnChangePreview        (void);
	 void    OnBnClickedFilenameOnly (void);
	 void    OnBnClickedPathOnly     (void);
	 void    OnBnClickedPathAndFilename(void);
	 void    OnBnClickedIncludeExtension(void);
	 void    OnBnClickedFormatEx     (void);
	 void    OnCbnSelChangePrecision (void);
	 void    OnCbnSelChangeDecimalSeparator(void);
	 void    OnCbnSelChangeListSeparator(void);
	 void    OnCbnEditChangeListSeparator(void);
	 void    OnBnClickedPointX       (void);
	 void    OnBnClickedPointY       (void);
	 void    OnBnClickedPointZ       (void);
	 void    OnBnClickedAppendSymbol (void);
	 void    OnCbnSelChangeCurrencySymbol(void);
	 void    OnLbnSelChangeNegativeNumberList(void);
	DECLARE_MESSAGE_MAP()
private:
	friend class NcFdUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiBitmapStatic
class THUNK_NATIVE_API CNdUiBitmapStatic : public CNdUiBitmapButton {
	DECLARE_DYNAMIC(CNdUiBitmapStatic)
public:
	            CNdUiBitmapStatic ();
	virtual         ~CNdUiBitmapStatic ();
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiBitmapStatic
class THUNK_NATIVE_API CNcUiBitmapStatic : public CNdUiBitmapStatic {
	DECLARE_DYNAMIC(CNcUiBitmapStatic)
public:
	            CNcUiBitmapStatic ();
	virtual         ~CNcUiBitmapStatic ();
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdUiDropSite
class THUNK_NATIVE_API CNdUiDropSite : public CNdUiBitmapStatic {
	DECLARE_DYNAMIC(CNdUiDropSite)
public:
	            CNdUiDropSite ();
	virtual         ~CNdUiDropSite ();
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiDropSite
class THUNK_NATIVE_API CNcUiDropSite : public CNdUiDropSite {
	DECLARE_DYNAMIC(CNcUiDropSite)
public:
	            CNcUiDropSite ();
	virtual         ~CNcUiDropSite ();
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiPickButton
class THUNK_NATIVE_API CNcUiPickButton : public CNdUiBitmapButton {
	DECLARE_DYNAMIC(CNcUiPickButton)
public:
	            CNcUiPickButton ();
	virtual         ~CNcUiPickButton ();
protected:
	virtual BOOL    OnLoadBitmap (LPCTSTR strResId);
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiSelectButton
class THUNK_NATIVE_API CNcUiSelectButton : public CNcUiPickButton {
	DECLARE_DYNAMIC(CNcUiSelectButton)
public:
	            CNcUiSelectButton ();
	virtual         ~CNcUiSelectButton ();
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdUiToolButton
class THUNK_NATIVE_API CNdUiToolButton : public CNdUiBitmapButton {
	DECLARE_DYNAMIC(CNdUiToolButton)
public:
	            CNdUiToolButton ();
	virtual         ~CNdUiToolButton ();
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiToolButton
class THUNK_NATIVE_API CNcUiToolButton : public CNdUiToolButton {
	DECLARE_DYNAMIC(CNcUiToolButton)
public:
	            CNcUiToolButton ();
	virtual         ~CNcUiToolButton ();
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiMRUListBox
class THUNK_NATIVE_API CNcUiMRUListBox : public CNcUiListBox {
public:
	CNcUiMRUListBox ();
	virtual ~CNcUiMRUListBox ();
public:
	virtual void    GetContentExtent (
                    int item, LPCTSTR text, int& width, int& height
                );
protected:
	virtual BOOL    OnGetTipRect (CRect& r);
protected:
	int     ExtraWidth ();
	CNcUiMRUComboBox *MRUComboBox ();
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiLineTypeComboBox
class THUNK_NATIVE_API CNcUiLineTypeComboBox : public CNcUiMRUComboBox {
public:
	CNcUiLineTypeComboBox ();
	virtual ~CNcUiLineTypeComboBox ();

	// Get/Set NcDbObjectId of current selection
	NcDbObjectId getOIDSel(int sel);
	NcDbObjectId getOIDCurSel();
	void setCurSelByOID(const NcDbObjectId& oidCurSel);
	bool isOtherSelected();
	void forceSelectOther (BOOL isOther2);
	int  getLastSelection();
	bool getDbReload();
	void setDbReload(bool bReload);
	void emptyLTypeLocalList();
protected:
	virtual void DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);
	virtual int  ImageWidth();
	virtual void OnComboBoxInit ();
	virtual void OnAddItems();
	virtual BOOL GetOtherName(BOOL isOther2, CString& name);
	virtual BOOL OnSelectOther (BOOL isOther2, int curSel, int& newSel);

	INT_PTR  GetItemCargo (int item);// Cargo for this class is just the
	// combobox item index.  That needs to
	// be resolved to the item data pointer
	// which is actually a CNcUiLTypeRecord
	// pointer, not an integer
	int  FindItemByCargo (NcDbObjectId cargo);
	void LoadContentsFromDatabase();
	void ShowLTypes(bool bForceReloadDB = false);
	int AddLTypeToControl(CNcUiLTypeRecord * pLTypeRecord);
	CNcUiLTypeRecord* CreateLTRecord(CString& cstrLTName, NcDbObjectId& oidLT);
	
	// Get/Set current DB pointer
	NcDbDatabase* getLTLocalMapDB();
	void setLTLocalMapDB(NcDbDatabase* pDb);

	// Member data
	CObList m_LTypeLocalList;
	NcDbDatabase* m_pLTLocalMapDB;
	bool m_bDbReload;

protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// Inlines for CNcUiLineTypeComboBox

// Test for and set whether to reload from the db or not
inline bool CNcUiLineTypeComboBox::getDbReload()
{
	return m_bDbReload;
}

inline void CNcUiLineTypeComboBox::setDbReload(bool bReload)
{
	m_bDbReload = bReload;
}

// Test for the "Other" selection of the linetype combo
inline void CNcUiLineTypeComboBox::forceSelectOther (BOOL isOther2)
{
	SelectOther(isOther2);
}

inline int CNcUiLineTypeComboBox::getLastSelection()
{
	return m_lastSelection;
}

inline bool CNcUiLineTypeComboBox::isOtherSelected()
{
	CString otherName;
	CString curSelName;
	GetOtherName (false, otherName);
	GetLBText(GetCurSel(), curSelName);
	return curSelName == otherName;
}

// Get/Set NcDbObjectId of given selection
inline NcDbObjectId CNcUiLineTypeComboBox::getOIDSel(int sel)
{
	NcDbObjectId oidLT;
	CNcUiLTypeRecord* pLTRec = (CNcUiLTypeRecord*)(GetItemDataPtr(sel));
	if (NULL != pLTRec)
		oidLT = pLTRec->objectId();
	return oidLT;
}

// Get/Set NcDbObjectId of current selection
inline NcDbObjectId CNcUiLineTypeComboBox::getOIDCurSel()
{
	return getOIDSel(GetCurSel());
}

inline void CNcUiLineTypeComboBox::setCurSelByOID(const NcDbObjectId& oidCurSel)
{
	int i = FindItemByCargo(oidCurSel);
	SetCurSel(i >= 0 ? i : m_lastSelection);
	if (i >= 0)
		m_lastSelection = i;
}

//////////////////////////////////////////////////////////////////////////
// CNcUiTrueColorComboBox
class THUNK_NATIVE_API CNcUiTrueColorComboBox : public CNcUiMRUComboBox {
public:
	enum ColorTableIndex {
		kCargoOption1           =  0,
		kCargoOption2           =  1,
		kCargoStockItem1        =  2,
		kCargoStockItem2        =  3,
		kCargoStockItem3        =  4,
		kCargoStockItem4        =  5,
		kCargoStockItem5        =  6,
		kCargoStockItem6        =  7,
		kCargoStockItem7        =  8,
		kIndexOfFirstMRUItem    =  9,
		kCargoOther1            = -1,
		kCargoOther2            = -2,
		kLastIndex              = NCUI_TRUECOLOR_COMBOBOX_TABLE_SIZE-1
	};
	                    CNcUiTrueColorComboBox      ();
	virtual                 ~CNcUiTrueColorComboBox     ();
	void                    AddItems                    ();
	int                     AddItemToList               (LPCTSTR name, int index, INT_PTR cargo);
	int                     AddItemToMRU                (LPCTSTR name, int cargo);
	int                     AddColorToMRU               (const NcCmColor& color);
	int                     FindItemByColor             (const NcCmColor& color);
	void                    GetCurrentItemColor         (NcCmColor& color);
	DWORD                   getColorByCargo             (int cargo);
	const NcCmColor&        GetBlockColor               ();
	void                    SetBlockColor               (const NcCmColor& color);
	virtual COLORREF        GetColorFromIndex           (int colorIndex);
	DWORD                   getColorData                (NcCmColor color);
	int                     GetColorIndex               (COLORREF color);
	void                    SetSupportColorBook         (BOOL newVal);
	BOOL                    GetSupportColorBook         ();
protected:
	int                     m_cargoOther1;
	int                     m_cargoOther2;
	NcCmColor               m_blockColor;
	virtual void            DrawItemImage               (CDC& dc, CRect& r, INT_PTR cargo);
	virtual void            OnAddItems                  ();
	virtual BOOL            OnSelectOther               (BOOL isOther2,int curSel,int& newSel);
	BOOL                    GetOtherColor               (NcCmColor& defaultColor,
	                                                     const NcCmColor& layerColor,
	                                                     BOOL enableMetaColors);
	BOOL                    GetWindowsColor             (NcCmColor& color);
	virtual BOOL            GetOtherName                (BOOL isOther2, CString& name);
	
	NcCmColor *             m_AcCmColorTable[NCUI_TRUECOLOR_COMBOBOX_TABLE_SIZE];
	int                     m_nextAcCmColorTableIndex;
	void                    initAcCmColorTable          (void);
	void                    RGBFill                     (CDC& dc, CRect& rFill);
	bool                    GetCurrentLayerColor        (NcCmColor& color);
	virtual COLORREF        LookupColor                 (int colorIndex, LOGPALETTE *logPalette);
	void            OnDrawItem                  (int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiArrowHeadComboBox
class THUNK_NATIVE_API CNcUiArrowHeadComboBox : public CNcUiMRUComboBox {
public:
	            CNcUiArrowHeadComboBox ();
	virtual         ~CNcUiArrowHeadComboBox ();

	int     AddArrowHeadToMRU (LPCTSTR name);
  
	BOOL    GetUseOrigin2 ();
	void    SetUseOrigin2 (BOOL use);

protected:
	virtual void    DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);
	virtual int     CalcItemHeight ();
	virtual BOOL    GetOtherName (BOOL isOther2, CString& name);
	virtual void    OnAddItems ();
	virtual void    OnComboBoxInit ();
	virtual bool    LoadImages();

private:
	CBitmap m_arrowBitmap;
	int     m_arrowCount;
	int     m_arrowSize;
	BOOL    m_bUseOrigin2;

protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiPlotStyleTablesComboBox
class THUNK_NATIVE_API CNcUiPlotStyleTablesComboBox : public CNcUiMRUComboBox {
public:
	CNcUiPlotStyleTablesComboBox ();
	CNcUiPlotStyleTablesComboBox (BOOL bInitialize);
	virtual         ~CNcUiPlotStyleTablesComboBox ();
	void    SetFileType(bool currentDrawing, bool named);
	int     AddMissingStyleTable(LPCTSTR fullFileName, bool bMissing = true);
	bool    IsMissing(int index);
	virtual int     ImageWidth ();
	void GetLBText(int nIndex, CString& rString) const;
	int     AddItemToList (LPCTSTR name,    INT_PTR cargo);
protected:
	virtual void    DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);
	virtual int     CalcItemHeight ();
	virtual void    OnAddItems ();
	virtual void    OnComboBoxInit ();
private:
	CBitmap m_plotStyleTablesBitmap;
	int     m_plotStyleTableBitmapSize;
	BOOL    m_bImageDisplayed;
	bool    m_bCurrentDrawing;
	bool    m_bNamed;
	BOOL    m_bInitialize;
public:
	virtual BOOL OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);
protected:
	BOOL OnDropDown();
	DECLARE_MESSAGE_MAP()
private:
	BOOL AdjustDropDownListWidth(void);
};

//////////////////////////////////////////////////////////////////////////
// CNcUiPlotStyleNamesComboBox
class THUNK_NATIVE_API CNcUiPlotStyleNamesComboBox : public CNcUiMRUComboBox {
public:
    CNcUiPlotStyleNamesComboBox ();
    virtual         ~CNcUiPlotStyleNamesComboBox ();
    virtual int     ImageWidth ();
    void            OtherRunsSelectPlotStyle() {m_whatOtherDoes = 0; }
    void            OtherRunsCurrentPlotStyle() {m_whatOtherDoes = 1; }
    void            OtherRunsDefault() {m_whatOtherDoes = -1;}
    void            SetAllowByLayerByBlock(BOOL bAllow) {m_bAllowByLayerByBlock = bAllow;}
    void            SetColorDependentMode();
    void            SetNamedMode();
protected:
    virtual void    OnAddItems ();
    virtual BOOL    OnSelectOther (BOOL isOther2, int curSel, int& newSel);
    virtual void    OnComboBoxInit ();
private:
    int m_whatOtherDoes;
    BOOL m_bColorDependentMode;
    BOOL m_bAllowByLayerByBlock;
    BOOL m_bLastByBlock;
    BOOL m_bLastByLayer;
    BOOL m_bLastUseOther;
public:
protected:
    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiPredefBlockComboBox
class THUNK_NATIVE_API CNcUiPredefBlockComboBox : public CNcUiMRUComboBox {
public:
	            CNcUiPredefBlockComboBox ();
	virtual         ~CNcUiPredefBlockComboBox ();
protected:
	virtual void    DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);
	virtual int     CalcItemHeight ();
	virtual BOOL    GetOtherName (BOOL isOther2, CString& name);
	virtual void    OnAddItems ();
	virtual void    OnComboBoxInit ();
private:
	CBitmap m_blockBitmap;
	int     m_blockCount;
	int     m_blockSize;
public:
	int     AddPredefBlockToMRU (LPCTSTR name);
public:
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdUiDialogBar
class THUNK_NATIVE_API CNdUiDialogBar : public CDialogBar {
	DECLARE_DYNAMIC(CNdUiDialogBar);
public:
	            CNdUiDialogBar ();
	virtual         ~CNdUiDialogBar ();
protected:
	virtual NDUI_REPLY DoNdUiMessage (
                    NDUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
	virtual NDUI_REPLY OnNotifyControlChange (UINT controlId, LPARAM lParam);
	virtual NDUI_REPLY OnNotifyControlValid (UINT controlId, BOOL isValid);
	virtual NDUI_REPLY OnNotifyGeneric (UINT controlId, LPARAM lParam);
	virtual NDUI_REPLY OnNotifyUpdateTip (CWnd *control);
protected:
	    BOOL    m_bUseTips;
	    CNdUiTextTip *m_pTextTip;
	    CToolTipCtrl *m_pToolTip;
	    CString m_rootKey;
public:
	virtual CWnd    *AppMainWindow ();
	virtual HINSTANCE AppResourceInstance ();
	virtual LPCTSTR AppRootKey ();
	        BOOL    GetUseTips ();
	        void    SetUseTips (BOOL useTips);
public:
	enum { IDD = 0 };
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void PostNcDestroy();
protected:
	 LRESULT OnNdUiMessage (WPARAM wParam, LPARAM lParam);
	 int OnCreate(LPCREATESTRUCT lpcs);
	 HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	 BOOL OnNotify_ToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiDialogBar
class THUNK_NATIVE_API CNcUiDialogBar : public CNdUiDialogBar {
	DECLARE_DYNAMIC(CNcUiDialogBar);
public:
	            CNcUiDialogBar ();
	virtual         ~CNcUiDialogBar ();
public:
	virtual CWnd    *AppMainWindow ();
	virtual HINSTANCE AppResourceInstance ();
	virtual LPCTSTR AppRootKey ();
public:
	enum { IDD = 0 };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdUiDialogWorksheet
class THUNK_NATIVE_API CNdUiDialogWorksheet : public CNdUiDialog {
	friend class CNdUiWorksheetThemeModReactor;
	DECLARE_DYNAMIC(CNdUiDialogWorksheet);
public:
	virtual ~CNdUiDialogWorksheet();
	CNdUiDialogWorksheet() {};
	CNdUiTheme * GetTheme() const;
	CNdUiTheme * SetTheme(CNdUiTheme *pTheme);
	static CNdUiWorksheetDraw * SetDefaultDraw(CNdUiWorksheetDraw * pDraw);
	void SetDraw(const CNdUiWorksheetDraw * pDraw);
	virtual void ThemeModified(NdUiThemeElement element);
	public:
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
	                      int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU nIDorHMenu,
	                      LPVOID lpParam = NULL);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
	                      const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
	virtual BOOL DestroyWindow();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	protected:
	virtual void PostNcDestroy();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	HICON m_hIcon;
	CNdUiDialogWorksheet(UINT ID, CWnd* pParent = NULL, HINSTANCE hResInst = NULL);
	CNdUiDialogWorksheet(UINT ID, const CNdUiWorksheetDraw & draw, CWnd* pParent = NULL, HINSTANCE hResInst = NULL);
	 void OnDestroy();
	 void OnClose();
	 void OnPaint();
	 HCURSOR OnQueryDragIcon();
	 void OnSize(UINT nType, int cx, int cy);
	 HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	 BOOL OnEraseBkgnd(CDC *pDC);
	 void OnIconEraseBkgnd(CDC* pDC);
	 void OnSetFocus(CWnd* pOldWnd);
	 void OnKillFocus(CWnd* pNewWnd);
	 void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	 void OnStyleChanging(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	 void OnSizing(UINT nSide, LPRECT lpRect);
	 void OnMoving(UINT nSide, LPRECT lpRect);
	 void OnMouseMove(UINT nHitTest,CPoint point);
	 void OnLButtonDblClk(UINT nFlags, CPoint point);
	 void OnLButtonDown(UINT nFlags, CPoint point);
	 void OnLButtonUp(UINT nFlags, CPoint point);
	 void OnMButtonDblClk(UINT nFlags, CPoint point);
	 void OnMButtonDown(UINT nFlags, CPoint point);
	 void OnMButtonUp(UINT nFlags, CPoint point);
	 void OnRButtonDblClk(UINT nFlags, CPoint point);
	 void OnRButtonDown(UINT nFlags, CPoint point);
	 void OnRButtonUp(UINT nFlags, CPoint point);
	 void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	 void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	 void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	 BOOL OnNcActivate(BOOL bActive);
	 void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	 BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	 void OnNcDestroy();
#if _MSC_VER<1400
	 UINT OnNcHitTest(CPoint point);
#else
	 LRESULT OnNcHitTest(CPoint point);
#endif
	 void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	 void OnNcLButtonDown(UINT nHitTest, CPoint point);
	 void OnNcLButtonUp(UINT nHitTest, CPoint point);
	 void OnNcMButtonDblClk(UINT nHitTest, CPoint point);
	 void OnNcMButtonDown(UINT nHitTest, CPoint point);
	 void OnNcMButtonUp(UINT nHitTest, CPoint point);
	 void OnNcMouseMove(UINT nHitTest, CPoint point);
	 void OnNcPaint();
	 void OnNcRButtonDblClk(UINT nHitTest, CPoint point);
	 void OnNcRButtonDown(UINT nHitTest, CPoint point);
	 void OnNcRButtonUp(UINT nHitTest, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	static CNdUiWorksheetDraw * s_pDefaultDraw;
	static CNdUiWorksheetDraw   s_PlatformDefaultDraw;
	CNdUiWorksheetDraw * m_pDraw;
};

//////////////////////////////////////////////////////////////////////////
// CNcUiDialogWorksheet
class THUNK_NATIVE_API CNcUiDialogWorksheet : public CNdUiDialogWorksheet {
	DECLARE_DYNAMIC(CNcUiDialogWorksheet);
public:
	CNcUiDialogWorksheet(UINT ID, CWnd* pParent = NULL, HINSTANCE hResInst=NULL);
	~CNcUiDialogWorksheet();
	enum { IDD = 0 };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	virtual BOOL OnInitDialog();
	 void OnSysCommand(UINT nID, LPARAM lParam);
	 void OnPaint();
	 void OnNcPaint();
	 BOOL OnNcActivate(BOOL bActive);
	 HCURSOR OnQueryDragIcon();
	 void OnSize(UINT nType, int cx, int cy);
	 HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	 BOOL OnEraseBkgnd(CDC *pDC);
	 void OnNcLButtonDown( UINT nHitTest, CPoint point );
	 void OnNcLButtonUp( UINT nHitTest, CPoint point );
	 void OnNcMouseMove(UINT nHitTest,CPoint point);
	 void OnMouseMove(UINT nHitTest,CPoint point);
	 void OnLButtonUp(UINT nFlags, CPoint point);
#if _MSC_VER<1400
	 UINT OnNcHitTest(CPoint point);
#else
	 LRESULT OnNcHitTest(CPoint point);
#endif
	 void OnLButtonDown(UINT nFlags, CPoint point);
	 void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	 void OnSysColorChange();
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdUiDockFrame
class THUNK_NATIVE_API CNdUiDockFrame : public CMiniDockFrameWnd {
	DECLARE_DYNCREATE (CNdUiDockFrame)
public:
	CNdUiDockFrame ();
public:
	enum ContainedBarType { Unknown, Standard, AdskBar } ;
	enum ContainedBarType GetContainedBarType ();
protected:
	enum ContainedBarType m_nContainedBarType;
	bool m_bZOrderChanged;
	bool CanFrameworkTakeFocus ();
	void ForceChildRepaint ();
public:
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	 int OnCreate(LPCREATESTRUCT lpCreateStruct);
	 void OnSize(UINT nType, int cx, int cy);
	 void OnClose();
	 void OnNcLButtonDown(UINT nHitTest, CPoint pt);
#if _MSC_VER<1400
	 UINT OnNcHitTest(CPoint point);
#else
	 LRESULT OnNcHitTest(CPoint point);
#endif
	 int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	 void OnWindowPosChanging (WINDOWPOS* lpwndpos);
	 void OnPaint ();
	 void OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI);
	 void OnSizing (UINT nSide, LPRECT pRect);
	bool CanAutoCADTakeFocus ();
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiDockFrame
class THUNK_NATIVE_API CNcUiDockFrame : public CNdUiDockFrame {
	DECLARE_DYNCREATE(CNcUiDockFrame);
public:
	            CNcUiDockFrame ();
	virtual         ~CNcUiDockFrame ();
public:
protected:
	 LRESULT OnACADKeepFocus (WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdUiPaletteSetDockFrame
class THUNK_NATIVE_API CNdUiPaletteSetDockFrame : public CMiniDockFrameWnd {
	friend class CNdUiDockDragContext;
	friend class CNdUiDockBarMutator;
	friend class CNdUiAnchorBar;
	DECLARE_DYNCREATE (CNdUiPaletteSetDockFrame)
public:
	CNdUiPaletteSetDockFrame ();
	virtual ~CNdUiPaletteSetDockFrame ();
	virtual BOOL Create(CWnd* pParent, DWORD dwBarStyle);
	static bool HidePalettes();
	static bool ShowPalettes();
public:
	    enum ContainedBarType { Unknown, Standard, AdskBar } ;
	    enum ContainedBarType GetContainedBarType ();
	    void SetAutoRollup(BOOL bSet);
	    virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	typedef enum {
		kLeft = 0,
		kRight
	} NdUiTitleBarLocation ;
	CNdUiPaletteSetDockFrame::NdUiTitleBarLocation TitleBarLocation();
	void SetTitleBarLocation(CNdUiPaletteSetDockFrame::NdUiTitleBarLocation);
protected:
	enum ContainedBarType m_nContainedBarType;
	bool m_bZOrderChanged;
	bool CanFrameworkTakeFocus ();
	void ForceChildRepaint ();
public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL PreTranslateMessage(MSG * msg);
	 int     OnCreate(LPCREATESTRUCT lpCreateStruct);
	 void    OnDestroy();
	 void    OnSize(UINT nType, int cx, int cy);
	 void    OnClose();
	 void    OnLButtonDown(UINT nHitTest, CPoint pt);
	 void    OnNcLButtonDown(UINT nHitTest, CPoint pt);
	 void    OnNcRButtonDown(UINT nHitTest, CPoint pt);
	 void    OnNcRButtonUp(UINT nHitTest, CPoint pt);
	 void    OnNcLButtonUp(UINT nHitTest, CPoint pt);
#if _MSC_VER<1400
	 UINT OnNcHitTest(CPoint point);
#else
	 LRESULT OnNcHitTest(CPoint point);
#endif
	 void    OnMouseMove(UINT nHitTest, CPoint pt);
	 void    OnNcMouseMove(UINT nHitTest, CPoint pt);
	 int     OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	 void    OnWindowPosChanging (WINDOWPOS* lpwndpos);
	 void    OnPaint ();
	 void    OnNcPaint ();
	 LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);
	 LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
	 void    OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized );
	 BOOL    OnNcActivate(BOOL bActive);
	 void    OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI);
	 void    OnSizing (UINT nSide, LPRECT pRect);
	 void    OnShowWindow( BOOL bShow, UINT nStatus );
	 BOOL    OnSetCursor(CWnd *pwnd, UINT nHitTest, UINT msg);
	 void    OnSetFocus(CWnd * pOldWnd);
	 void    OnTimer(UINT_PTR nIdEvent);
	 void    OnContextMenu(CWnd* pWnd, CPoint pos);
	 BOOL    OnEraseBkgnd(CDC* pDC);
	 LRESULT OnEnterSizeMove(WPARAM, LPARAM);
	 LRESULT OnExitSizeMove(WPARAM, LPARAM);
	 void    OnSettingChange( UINT uFlags, LPCTSTR lpszSection );
	virtual LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
	virtual LRESULT  OnDragScroll(WPARAM wParam, LPARAM lParam);
	bool CanAutoCADTakeFocus ();
	BOOL HitTest(CPoint pt, UINT& nFlag, DWORD& dwData);
	CNdUiPaletteSet* GetPaletteSet();
	DECLARE_MESSAGE_MAP()
private:
	enum NdUiSkBtnItems {
		kBtnUnknown     = -1,
		kBtnPushPin     = 0,
		kBtnOptionMenu  = 1,
		kBtnClose       = 2,
		kBtnIcon        = 3,
	};
	enum NdUiSkIds {
		kRollupTimerId = 0x3011,
		kRolloutTimerId = 0x3012,
		kCursorCheckTimerId = 0x3013
	};
	enum NdUiSkUiFlags {
		kImgListUnpinnedLeft        = 0,
		kImgListUnpinnedRight       = 1,
		kImgListPinnedLeft          = 2,
		kImgListPinnedRight         = 3,
		kImgListOptionMenuLeft      = 4,
		kImgListOptionMenuRight     = 5,
		kImgListClose               = 6,
		kImgList_Count              = 7,
	};
	void ncPaint(UINT nPtFlags);
	void windowToNonClient(CRect & rect);
	void nonclientToWindow(CRect & rect);
	void getRegion(CRgn & rgn);
	void getBorderRects(CRect & rectTop, CRect & rectBottom, CRect & rectSide);
	int getMetrics(UINT nItem);
	void getWndCaptionRect(CRect & rect);
	void getWndStatusRect(CRect & rect);
	void getWndSizerRect(CRect & rect);
	void getButtonItemRect(NdUiSkBtnItems eBtn, CRect & rect);
	void GetNonClientSize(CSize& size);
	int  GetTopGrabbableHeight();
	void SnapToRect(CRect & rect, WINDOWPOS * pWndpos,
	                int nPaletteWidth, int nPaletteHeight,
	                bool bSnapInside, bool bSnapOutside);
	void InitFonts();
	BOOL isImgListItemValid(int nItem);
	void OnOptionsMenu();
	void OnSystemMenu(CPoint pos);
	void buttonBlt(CDC *pDC,int nImage, CRect &rcBtn);
	bool btnPress(NdUiSkBtnItems eBtn, LPPOINT pt);
	void btnPressOptionMenu();
	void btnPressPushPin();
	void btnPressClose();
	void setWindowRgn();
	void    doDrawCaption(CDC *pDC);
	void    doDrawStatus(CDC *pDC);
	void    doDrawSizer(CDC *pDC);
	void    doDrawBorder(CDC* pDC);
	void    doDrawButton(CDC *pDC, NdUiSkBtnItems btnItem, BOOL bErase = false);
	void        displayTip(LPPOINT pt);
	void        SetRollupDelay();
	DWORD       GetRollupDelay() {
		return m_bDelayRolledOut ? m_nHoldopenDelay : m_nRollupDelay; }
	void        SetRolloutDelay();
	DWORD       GetRolloutDelay() { return m_nRolloutDelay; }
	void        RollOut(CPoint * pPt, bool bDelay = false);
	void        rollupDlg(BOOL bRollup = TRUE);
	void        SetRolloutTimer();
	void        SetRollupTimer();
	BOOL RolledUp() { return (! m_rectSize.IsRectEmpty()); }
	CRect m_rectSize;
	CSize m_sizeShadow;
	CRect m_rectCaptionText;
	CImageList m_imgListGui;
	CImageList m_imgListIcon;
	DWORD m_dwUiTransientFlags;
	bool  m_bRolloutTimerSet;
	bool  m_bRollupTimerSet;
	static DWORD m_nRollupDelay;
	static DWORD m_nRolloutDelay;
	static DWORD m_nHoldopenDelay;
	CPaletteSetTooltip* m_pToolTip;
	BOOL  m_bAllowSnapping;
	CNdUiDropTarget* m_pDropTarget;
	NdUiTitleBarLocation m_orphanTitleBarLoc;
	bool m_bUserEnteredAutoHideMode;
	CRect m_rectWorkArea;
	bool m_bDelayRolledOut;
};

//////////////////////////////////////////////////////////////////////////
// CNcUiPaletteSetDockFrame
class THUNK_NATIVE_API CNcUiPaletteSetDockFrame : public CNdUiPaletteSetDockFrame {
	DECLARE_DYNCREATE(CNcUiPaletteSetDockFrame);
public:
	            CNcUiPaletteSetDockFrame ();
	virtual         ~CNcUiPaletteSetDockFrame ();
public:
protected:
	 LRESULT OnACADKeepFocus (WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdUiPathname
class THUNK_NATIVE_API CNdUiPathname {
	friend void GetDisplayNameHelper(
	                                 const CNdUiPathname* const pPathName,
	                                 CString& strResult,
	                                 int maxchars );
	friend CNdUiVolumeDescriptor* NewVolDescriptorHelper(
	                                                     const CNdUiPathname* const pPathName,
	                                                     const CString& vol_name);
	friend bool IsPathValid(
	                        CNdUiPathname* pPathName,
	                        const CNdUiPathname* rel_path,
	                        const CString* work);
	friend void HandleSpecialPath(
	                              CNdUiPathname* pPathName,
	                              const CNdUiPathname* rel_path,
	                              CString* work,
	                              int index,
	                              const BOOL wildcard_ok);
	friend bool IsValidOnColon(const CString* work);
	friend void SetupVolForRoottypePath(
	                              CNdUiPathname* pPathName,
	                              LPCTSTR pPathStr);
	friend CString GetDriveForRoottypePath(const CNdUiVolumeDescriptor* const);
	friend BOOL WasAbsoluteHelper(path_category pc);

public:
	CNdUiPathname(void);
	CNdUiPathname(const CNdUiPathname&);
	~CNdUiPathname(void);
	void Empty(void);
	virtual PathErr Parse( LPCTSTR, const BOOL wildcard_ok = FALSE );
	PathErr ParseRelative( LPCTSTR name,
	                      const CNdUiPathname* relpath,
	                      const BOOL wildcard_ok = FALSE );
	BOOL ParseAndOSFind( LPCTSTR );
	const CNdUiPathname& CNdUiPathname::operator=(const CNdUiPathname& pathSrc);
	const CNdUiPathname& CNdUiPathname::operator=(const CNdUiPathname* pathSrc);
	BOOL CNdUiPathname::GetUniqueName(
	                       CNdUiPathname&,
	                       BOOL alwaysMangle = FALSE ) const;
	void GetFilename(CString&) const;
	void GetExtension(CString&) const;
	void GetBasename(CString&) const;
	void GetParent(CNdUiPathname& ) const;
	PathErr Trim(void);
	PathErr TrimSlash(void);
	PathErr TrimComponent(void);
	PathErr Append( LPCTSTR );
	PathErr AppendSlash(void);
	PathErr AppendComponent( LPCTSTR );
	PathErr AddExtensionAlways( LPCTSTR );
	PathErr AddExtensionIfNoMatch( LPCTSTR );
	PathErr ReplaceExtensionAlways( LPCTSTR );
	PathErr ReplaceExtensionIfNoMatch( LPCTSTR );
	void RemoveExtensionAlways(void);
	void RemoveExtensionIfMatch( LPCTSTR );
	void BaseToLower( void );
	void BaseToUpper( void );
	void RemoveSpaces( void );
	void GetDisplayName( CString& strResult, int maxchars ) const;
	LPCTSTR GetPathString(void) const;
	LPCTSTR GetRelativePathString(void) const;
	BOOL GetFullPath( CString& ) const;
	BOOL GetFullPath( LPTSTR) const;
	BOOL GetFullPath( LPTSTR, size_t strBuffLen ) const;
	void GetFullUNCPath(CString&) const;
	BOOL IsPath(void) const;
	BOOL IsEmpty(void) const;
	path_type GetPathType(void) const;
	const CNdUiVolumeDescriptor* GetVolumeDescriptor(void) const;
	BOOL PathMatch( const CNdUiPathname* ) const;
	BOOL PathMatch( LPCTSTR ) const;
	BOOL Exists(void);
	BOOL VerifyExtension( LPCTSTR extlist ) const;
	BOOL HadPrefix(void) const;
	BOOL WasAbsolute(void) const;
	BOOL WasRoot(void) const;
	BOOL Open(FILE** fdp, const NCHAR *openmode);
	BOOL Open(CFile& fp, UINT openflags);
	BOOL OpenReadOnly(HANDLE &rFileHandle);
	BOOL OpenWriteOnly(HANDLE &rFileHandle);
	BOOL Rename(const NCHAR *newname);
	BOOL Remove(void);
protected:
	path_type                       m_this_type;
	const CNdUiVolumeDescriptor*        m_pvolume;
	CString*                        m_pathbuffer;
	CString*                        m_relpath;
	path_category                   m_path_cat;
	NCHAR                           m_separator;
	BOOL                            m_had_prefix;
	const CNdUiVolumeDescriptor* FindVolumeDescriptor(const CString& vol_name) const;
	const CNdUiVolumeDescriptor* NewVolDescriptor( const CString& vol_name) const;
	FS_TYPE GetFileSystem(CString& vol_name) const;
	BOOL IsDeviceName(const CString& str) const;
	static void Unquote( CString& );
	NCHAR GetSeparator(void) const;
	virtual void AssignCopy( const CNdUiPathname& );
	static NCHAR GetLastCharacter( const CString& );
private:
	void GetFirstExtInList( LPCTSTR, CString&) const;
	void lstrncpy_x( LPTSTR dest, LPCTSTR src, int nchars) const;
	void StripSpaces(CString& work);
	void GetAttributes(const CString* path,
	                   const CString* relpath,
	                   path_type* this_type);
};

//////////////////////////////////////////////////////////////////////////
// CNcUiPathname
class THUNK_NATIVE_API CNcUiPathname : public CNdUiPathname {
public:
	CNcUiPathname(void);
	CNcUiPathname(const CNcUiPathname&);
	~CNcUiPathname(void);
	virtual PathErr Parse( LPCTSTR, const BOOL wildcard_ok = FALSE );
	int Status(void);
	BOOL Open(AFILE** fdp, const TCHAR *openmode);
	const CNcUiPathname& CNcUiPathname::operator=(const CNcUiPathname& pathSrc);
	const CNcUiPathname& CNcUiPathname::operator=(const CNcUiPathname* pathSrc);
protected:
	virtual void AssignCopy( const CNcUiPathname& );
};

//////////////////////////////////////////////////////////////////////////
// CNcUiString
class CNcUiString : public CString {
public:
	THUNK_NATIVE_API CNcUiString ();
	THUNK_NATIVE_API CNcUiString (const CString& stringSrc);
	THUNK_NATIVE_API CNcUiString (NCHAR ch, int nRepeat = 1);
	THUNK_NATIVE_API CNcUiString (LPCTSTR psz);
	THUNK_NATIVE_API CNcUiString (LPCTSTR pch, int nLength);
	THUNK_NATIVE_API CNcUiString (UINT nStringResourceID);
public:
	THUNK_NATIVE_API BOOL    IsTab (int nIndex)          const;
	THUNK_NATIVE_API BOOL    IsWhiteSpace (int nIndex)   const;
	THUNK_NATIVE_API BOOL    IsAlphabetic (int nIndex)   const;
	THUNK_NATIVE_API BOOL    IsAlphanumeric (int nIndex) const;
	THUNK_NATIVE_API BOOL    IsBlank (int nIndex)        const;
	THUNK_NATIVE_API BOOL    IsPunctuation (int nIndex)  const;
	THUNK_NATIVE_API BOOL    IsUppercase (int nIndex)    const;
	THUNK_NATIVE_API BOOL    IsLowercase (int nIndex)    const;
	THUNK_NATIVE_API BOOL    IsNumeric (int nIndex)      const;
	THUNK_NATIVE_API BOOL    IsHexNumeric (int nIndex)   const;
public:
	THUNK_NATIVE_API void    MakeCharUpper (int nIndex);
	THUNK_NATIVE_API void    MakeCharLower (int nIndex);
	THUNK_NATIVE_API void    GetCurrentWorkingDirectory ();
	THUNK_NATIVE_API void    ReplaceCharWithChar (NCHAR chFrom, NCHAR chTo);
	THUNK_NATIVE_API void    StripMnemonic ();
	THUNK_NATIVE_API void    StripDiesel ();
	THUNK_NATIVE_API void    ConvertMenuExecString ();
	THUNK_NATIVE_API void    ConvertFromMenuExecString ();
	THUNK_NATIVE_API void    FixFileName ();
	THUNK_NATIVE_API void    WrapLine (CNcUiString& strRest, int nWrapAt);
	THUNK_NATIVE_API void    WrapLine (CStringList& strListWrapped, int nWrapAt);
	THUNK_NATIVE_API void    ExpandTabs (int nTabSize = 8);
public:
	THUNK_NATIVE_API void    StripTrailingBlanks  ();
	THUNK_NATIVE_API void    StripPrecedingBlanks ();
	THUNK_NATIVE_API void    StripTrailingCharacters  (NCHAR cChar);
	THUNK_NATIVE_API void    StripPrecedingCharacters (NCHAR cChar);
public:
	THUNK_NATIVE_API void    ShortenString (
	            CDC *pDC,
	            CString OriginalString,
	            UINT width
	        );
	THUNK_NATIVE_API CString CreateEllipsedString (
	            CDC *pDC,
	            CString OriginalString,
	            UINT width
	        );
};

//////////////////////////////////////////////////////////////////////////
// CNcUiStringExp
class CNcUiStringExp : public CNcUiString {
public:
	    THUNK_NATIVE_API CNcUiStringExp ();
	    THUNK_NATIVE_API CNcUiStringExp (const CString& stringSrc);
	    THUNK_NATIVE_API CNcUiStringExp (NCHAR ch, int nRepeat = 1);
	    THUNK_NATIVE_API CNcUiStringExp (LPCTSTR psz);
	    THUNK_NATIVE_API CNcUiStringExp (LPCTSTR pch, int nLength);
	    THUNK_NATIVE_API CNcUiStringExp (UINT nStringResourceID);
public:
	    THUNK_NATIVE_API virtual BOOL LoadString(UINT nID);
	    THUNK_NATIVE_API void    ReplaceProductMacroStrings();
};

//////////////////////////////////////////////////////////////////////////
// NdMenuBar
class THUNK_NATIVE_API NdMenuBar {
	friend class NdApplicationFrame;
public:
	virtual ~NdMenuBar();
	bool GetMenuItemHelpString(UINT nItemID, const wchar_t **wszHelpString);
	bool RemoveMenuItem(HMENU hMenu, UINT nMenuItemId);
	bool AddMenuItem(HMENU hMenu, UINT nPos, const MENUITEMINFO& menuItem,
	                 LPFNADMENUCALLBACK pfnCallback, const wchar_t *wszHelpString);
	bool SetMenuHandle(HMENU hMenu);
	void UpdateMenu();
	HMENU GetMenuHandle();
	bool TrackingPopup();
	void SetChildWindowMenuPopup(bool bShow);
	bool GetChildWindowMenuPopup(void);
private:
	NdMenuBar();
};

//////////////////////////////////////////////////////////////////////////
// CNdUiThemeModifiedReactor
class CNdUiThemeModifiedReactor {
public:
	virtual void ThemeModified(const CNdUiTheme * pTheme, NdUiThemeElement element) = 0;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiODButtonThemeModReactor
class CNdUiODButtonThemeModReactor : public CNdUiThemeModifiedReactor {
public:
	CNdUiODButtonThemeModReactor(CNdUiOwnerDrawButton* pBtn);
	virtual void ThemeModified(const CNdUiTheme * pTheme, NdUiThemeElement element);
private:
	CNdUiOwnerDrawButton * m_pBtn;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiTrackButton
class THUNK_NATIVE_API CNdUiTrackButton : public CNdUiOwnerDrawButton {
	DECLARE_DYNAMIC(CNdUiTrackButton)
public:
	            CNdUiTrackButton();
	            CNdUiTrackButton(const CNdUiTrackButtonDraw & pDraw);
	virtual     ~CNdUiTrackButton();
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual CNdUiTheme * GetTheme() const;
	virtual CNdUiTheme * SetTheme(CNdUiTheme *pTheme);
	static  CNdUiTrackButtonDraw * SetDefaultDraw(CNdUiTrackButtonDraw * pDraw);
	        CNdUiTrackButtonDraw * SetDraw(CNdUiTrackButtonDraw * pDraw);
	virtual void    SetTracking(BOOL b);
protected:
	virtual void    DrawButton(
                    CDC& dc, int w, int h,
                    BOOL isDefault,
                    BOOL isDisabled,
                    BOOL isSelected,
                    BOOL isFocused
                );
	virtual void    DrawBorder(CDC *pDC,CRect &r,COLORREF cr);
	virtual void    DrawHotBorder();
	virtual void    DrawPushButtonBorder (CDC& dc, CRect& rButton, BOOL isDefault, BOOL isSelected);
	virtual void    DrawToolButtonBorder (CDC& dc, CRect& rButton, BOOL isSelected, BOOL isFocused);
	virtual NDUI_REPLY OnGetTipSupport (CPoint& p);
	 void OnNcPaint();
	 void OnPaint();
	DECLARE_MESSAGE_MAP()
	virtual void releaseDraw();
private:
	static CNdUiTrackButtonDraw * s_pDefaultDraw;
	CNdUiTrackButtonDraw * m_pDraw;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiBitmapTextButton
class THUNK_NATIVE_API CNdUiBitmapTextButton : public CNdUiBitmapButton {
	DECLARE_DYNAMIC(CNdUiBitmapTextButton)
public:
	enum ButtonType
	{
		kBitmap = 0x1,
		kText = 0x2,
	};
	enum BitmapLocation
	{
		kLeft = 0x1,
		kTop = 0x2,
		kRight = 0x4,
		kBottom = 0x8,
	};
	enum ButtonStyle
	{
		kButtonStyleNone  = 0,
		kButtonStyleFlat  = 0x1,
		kButtonStyleCheck = 0x2,
		kButtonHCenter     = 0x00000300,
		kButtonVCenter    = 0x00000C00,
	};
public:
	CNdUiBitmapTextButton();
	virtual ~CNdUiBitmapTextButton();
protected:
	virtual void DrawButton(
	    CDC& dc, int w, int h,
	    BOOL isDefault,
	    BOOL isDisabled,
	    BOOL isSelected,
	    BOOL isFocused
	    );
	virtual BOOL OnAutoLoad ();
	virtual BOOL OnReload (LPCTSTR strResId);
	virtual BOOL OnLoadBitmap (LPCTSTR strResId);
public:
	BOOL                GetAutoSizeToContent ();
	void                SetAutoSizeToContent (BOOL autoSizeToContent);
	void                SizeToContent ();
	void                SetContentOffsets(int nBorderOffset,
	                                      int nFocusRectOffset);
	UINT                GetButtonType();
	UINT                GetBitmapLocation();
	UINT                SetButtonType(UINT btnType);
	UINT                SetBitmapLocation(UINT imgPos);
	ButtonStyle            GetBitmapTextButtonStyle() const;
	void                SetBitmapTextButtonStyle(ButtonStyle nBtnStyle);
	DECLARE_MESSAGE_MAP()
public:
	BOOL                GetAutoSizeToBitmap ();
	void                SetAutoSizeToBitmap (BOOL autoSizeToBitmap);
	void                SizeToBitmap ();
	void                SetBitmapOffsets(int nBorderOffset, int nFocusRectOffset);
	void                SetBkColor(COLORREF);
	void                SetBorderColor(COLORREF);
	void                SetCheck(int nCheck);
	int                    GetCheck();
	HICON                SetIcon(HICON hIcon, BOOL bRedraw = TRUE);
	HICON                GetIcon() const;
	HBITMAP                SetBitmap(HBITMAP hBitmap, BOOL bRedraw = TRUE);
	HBITMAP                GetBitmap() const;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiCoupledGroupCtrl
class THUNK_NATIVE_API CNdUiCoupledGroupCtrl : public CWnd {
	DECLARE_DYNAMIC(CNdUiCoupledGroupCtrl);
public:
	CNdUiCoupledGroupCtrl();
	virtual ~CNdUiCoupledGroupCtrl();
public:
public:
	virtual void AddCouple(CNdUiGroupCtrl * pNdUiTopWnd,
	                       CNdUiGroupCtrl * pNdUiBottomWnd);
	virtual void AddCouple(CWnd* pWndTop, CWnd* pWndBottom);
	virtual void AddCouple(CNdUiGroupCtrl* pNdUiTopWnd, CWnd* pWndBottom);
	virtual void AddCouple(CWnd* pWndTop, CNdUiGroupCtrl* pNdUiBottomWnd);
	virtual void MinMaxOneChild(CWnd* pWnd, bool bMinimized);
	double GetTopToWholeRatio() const { return m_topToWholeRatio; }
	void SetTopToWholeRatio(double topToWholeRatio);
	void SetSplitterEnabled(bool bSplitterEnabled) {
		m_bSplitterEnabled = bSplitterEnabled;
	}
	bool GetSplitterEnabled() {
		return m_bSplitterEnabled;
	}
	void SetTheme(CNdUiTheme* pTheme);
protected:
	 void OnSize(UINT nType, int cx, int cy);
	 void OnPaint();
	 void OnMouseMove( UINT nFlags, CPoint );
	 void OnLButtonDown( UINT nFlags, CPoint );
	 void OnLButtonUp( UINT nFlags, CPoint );
	 HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
protected:
	void ResizeChildren( int cx, int cy );
	bool ValidateCtrls();
	bool IsAnyCtrlMinimizedOrIconic();
protected:
	COLORREF m_crNCBackground;
	COLORREF m_crSplitter;
	CBrush   m_bkBrush;
protected:
	CNdUiGroupCtrl* m_pNdUiTopWnd;
	CNdUiGroupCtrl* m_pNdUiBottomWnd;
	CWnd*           m_pTopWnd;
	CWnd*           m_pBottomWnd;
	double          m_topToWholeRatio;
	bool            m_bDragging;
	bool            m_bSplitterEnabled;
	CPoint          m_ptLast;
	CRect           m_rtSpace;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiDockControlBarThemeModReactor
class CNdUiDockControlBarThemeModReactor : public CNdUiThemeModifiedReactor {
public:
	CNdUiDockControlBarThemeModReactor(CNdUiDockControlBar* pDockControlBar);
	virtual void ThemeModified(const CNdUiTheme * pTheme, NdUiThemeElement element);
	void SetDockControlBar(CNdUiDockControlBar* pDockControlBar);
private:
	CNdUiDockControlBar * m_pDockControlBar;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiDropTarget
class CNdUiDropTarget : public COleDropTarget {
public:
	CNdUiDropTarget();
	CNdUiDropTarget(int nId);
	~CNdUiDropTarget();
	BOOL            SetTargetWindowForMessages(CWnd* pWnd);
protected:
	virtual DROPEFFECT     OnDragEnter            (CWnd* pWnd,
	                                               COleDataObject* pDataObject,
	                                               DWORD dwKeyState,
	                                               CPoint point);
	virtual DROPEFFECT     OnDragOver            (CWnd* pWnd,
	                                              COleDataObject* pDataObject,
	                                              DWORD dwKeyState,
	                                              CPoint point);
	virtual BOOL        OnDrop                (CWnd* pWnd,
	                                           COleDataObject* pDataObject,
	                                           DROPEFFECT     dropEffect,
	                                           CPoint point);
	virtual DROPEFFECT     OnDropEx            (CWnd* pWnd,
	                                            COleDataObject* pDataObject,
	                                            DROPEFFECT dropDefault,
	                                            DROPEFFECT dropList,
	                                            CPoint point);
	virtual void        OnDragLeave            (CWnd* pWnd);
	virtual DROPEFFECT  OnDragScroll        (CWnd* pWnd,
	                                         DWORD dwKeyState,
	                                         CPoint point);
protected:
	DWORD        mdwKeyState;
	int                 mnId;
	CWnd            *   mpTargetWnd;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiSearchBox
class THUNK_NATIVE_API CNdUiSearchBox : public CNdUiEdit {
	DECLARE_DYNAMIC(CNdUiSearchBox)
public:
	            CNdUiSearchBox ();
	virtual         ~CNdUiSearchBox ();
virtual BOOL    Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
virtual void    PreSubclassWindow();
        void    SetDefaultText(LPCTSTR pszText);
        void    SetNotification(LPCTSTR pszText);
        void    ClearEditor();
        bool    IsEditEmpty();
public:
	virtual void    EditChanged();
	virtual void    ClearButtonClicked();
	virtual void    SearchButtonClicked();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	 void OnClearButton();
	 void OnSearchButton();
	 void SetEditFocus();
	 void KillEditFocus();
	 void OnEditChange();
	 void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
private:
	BOOL    CreateControls();
	BOOL    DestroyControls();
	void    UpdateSearchBox();
	void    UpdateButton();
	void    GetControlRect(CRect &editRect, CRect &buttonRect);
private:
	bool                    m_bIsControlsCreated;
	CNdUiSearchBoxEditor*    m_pEditor;
	CNdUiSearchBoxSearchButton*      m_pBtnSearch;
	CNdUiSearchBoxClearButton*   m_pBtnClear;
	CString                 m_strNotification;
	CString                 m_strDefaultText;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiGroupCtrl
class THUNK_NATIVE_API CNdUiGroupCtrl : public CStatic {
	DECLARE_DYNAMIC(CNdUiGroupCtrl);
public:
	CNdUiGroupCtrl( );
	virtual ~CNdUiGroupCtrl();
	virtual bool AddWnd(CWnd* pWnd, LPCTSTR pszTitle, CBitmap* pBMP = NULL);
	virtual bool AddWnd(CWnd* pWnd, LPCTSTR pszTitle, LPCTSTR pszResName);
	virtual bool ShowWnd(CWnd* pWnd);
	virtual bool AddBmpBtnToHeader(LPCTSTR pszResName,
	                               NdUiBmpBtnFcnPtr fcnPtr,
	                               DWORD& dwCookie,
	                               LPCTSTR pszToolTip);
	virtual bool AddBmpBtnToHeader(CBitmap* pBmp,
	                               NdUiBmpBtnFcnPtr fcnPtr,
	                               DWORD& dwCookie,
	                               LPCTSTR pszToolTip);
	virtual bool RemoveBmpBtnFromHeader(DWORD dwCookie);
	virtual void ModGroupStyle(DWORD styleRemove, DWORD styleAdd);
	virtual void SetTheme(CNdUiTheme* pTheme);
	virtual void SetFont(CFont* pFont);
	virtual void SetFont(CFont* pFont, BOOL bRedraw);
	virtual void SetMinimized(bool bMinimized);
	bool GetMinimized() const;
	void SetTitle(LPCTSTR pszTitle) { m_csTitle = pszTitle; }
	CString GetTitle() { return m_csTitle; }
	void SetHeaderHeight(int nHeight) { m_nHeaderHeight = nHeight; }
	int GetHeaderHeight() { return m_nHeaderHeight; }
	void SetStyle(DWORD nStyle) { m_nStyle = nStyle; }
	DWORD GetStyle() { return m_nStyle; }
	void SetSelIndex(int nSelIndex);
	int GetSelIndex();
	void SetHideGroupHeader(bool bHide) {
		m_bHideGroupHeader = bHide;
	}
	bool GetHideGroupHeader() {
		return m_bHideGroupHeader;
	}
	void SetActive(bool bActive);
	bool GetActive() { return m_bActive; }
protected:
	virtual void DrawGroupContent(CDC* pDC);
	virtual void DrawGroupHeader(CDC* pDC);
	virtual void DeselectGroupHeader() {
		CDC* pDC = GetWindowDC();
		DrawGroupHeader(pDC);
		ReleaseDC(pDC);
	}
	void OnChevronClicked();
	void DrawHeaderBorder(CDC   *pDC, CRect &rect);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	static CNdToolTipCtrl* GetToolTipControl();
protected:
	 void OnNcPaint();
	 void OnPaint();
	 void OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS * );
	 int OnCreate( LPCREATESTRUCT lpCreateStruct );
	 void OnSize( UINT nType, int cx, int cy );
	 void OnNcLButtonDown( UINT nHitTest, CPoint );
	 void OnNcLButtonDblClk( UINT nHitTest, CPoint );
#if _MSC_VER<1400
	 UINT OnNcHitTest(CPoint point);
#else
	 LRESULT OnNcHitTest(CPoint point);
#endif
	 void OnSetFocus( CWnd * pOldWnd );
	 void OnKillFocus( CWnd * pNewWnd );
	 BOOL OnEraseBkgnd(CDC*) { return TRUE;};
	 HBRUSH OnCtlColor(CDC*, CWnd*, UINT);
	DECLARE_MESSAGE_MAP()
protected:
	COLORREF m_crNCBackground;
	COLORREF m_crGroupBorder;
	COLORREF m_crHeaderActive;
	COLORREF m_crHeaderInactive;
	COLORREF m_crTitleText;
	COLORREF m_crButtonBorderNormal;
	COLORREF m_crButtonFillNormal;
	COLORREF m_crButtonFillSelected;
	COLORREF m_crButtonBorderSelected1;
	COLORREF m_crButtonBorderSelected2;
	CBrush   m_bgBrush;
protected:
	CString         m_csTitle;
	bool            m_bMinimized;
	bool            m_bActive;
	bool            m_bHideGroupHeader;
	int             m_nHeaderHeight;
	int             m_nRestoreHeight;
	int             m_nSelIndex;
	DWORD           m_nStyle;
	DWORD           m_dwBtnId;
	NDUIHEADERBTNLIST       m_bmpBtnList;
	NDUIGROUPCTRLDATALIST   m_groupList;
	CToolTipCtrl            m_ToolTip;
	static LOGFONT& font();
private:
	static LOGFONT          m_lf;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiHeaderCtrl
class THUNK_NATIVE_API CNdUiHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CNdUiHeaderCtrl)
public:
	CNdUiHeaderCtrl ();
	virtual ~CNdUiHeaderCtrl ();
protected:
	CPoint  m_lastMousePoint;
	int     m_tipItem;
	CRect   m_tipRect;
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual void GetContentExtent(int item, LPCTSTR text, int& width, int& height);
	int     GetItemAtPoint (CPoint& p);
	BOOL    GetItemRect (int idx, CRect& rItem);
	BOOL    GetText (int idx, CString& text);
	void    GetTextExtent (LPCTSTR text, int& width, int& height);
	BOOL    IsOwnerDraw (int idx);
protected:
	CWnd*		m_nduiParent;
	virtual NDUI_REPLY DoNdUiMessage (NDUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam);
	virtual void    OnDrawTip (CDC& dc);
	virtual BOOL    OnDrawTipText (CNdUiDrawTipText& dtt);
	virtual NDUI_REPLY OnGetTipSupport (CPoint& p);
	virtual BOOL    OnGetTipRect (CRect& r);
	virtual BOOL    OnGetTipText (CString& text);
	virtual BOOL    OnHitTipRect (CPoint& p);
public:
	CWnd*		GetNdUiParent ();
	void		SetNdUiParent (CWnd *w);
public:
protected:
	LRESULT OnNdUiMessage (WPARAM wParam, LPARAM lParam);
	void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdUiListCtrl
class THUNK_NATIVE_API CNdUiListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CNdUiListCtrl);
public:
	CNdUiListCtrl ();
	virtual ~CNdUiListCtrl ();
protected:
	CPoint  m_lastMousePoint;
	int     m_tipIndex;
	int     m_tipItem;
	CRect   m_tipRect;
public:
	CNdUiHeaderCtrl m_headerCtrl;
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	int     ColumnCount ();
	virtual void GetContentExtent (int item, int index, LPCTSTR text, int& width, int& height);
	BOOL    GetItemAtPoint (CPoint& p, int& item, int& index);
	BOOL    GetSubItemRect (int item, int index, CRect& rect);
	void    GetTextExtent (LPCTSTR text, int& width, int& height);
	BOOL    IsOwnerDraw ();
protected:
	CWnd*		m_nduiParent;
	virtual NDUI_REPLY DoNdUiMessage (NDUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam);
	virtual void    OnDrawTip (CDC& dc);
	virtual BOOL    OnDrawTipText (CNdUiDrawTipText& dtt);
	virtual NDUI_REPLY OnGetTipSupport (CPoint& p);
	virtual BOOL    OnGetTipRect (CRect& r);
	virtual BOOL    OnGetTipText (CString& text);
	virtual BOOL    OnHitTipRect (CPoint& p);
public:
	CWnd*	GetNdUiParent ();
	void  SetNdUiParent (CWnd *w);
public:
	protected:
	virtual void PreSubclassWindow();
protected:
	LRESULT OnNdUiMessage (WPARAM wParam, LPARAM lParam);
	void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdUiRegistryAccess
class THUNK_NATIVE_API CNdUiRegistryAccess {
public:
	CNdUiRegistryAccess();
	CNdUiRegistryAccess(HKEY hKey,const CString& sSubkey);
	virtual ~CNdUiRegistryAccess();
	operator HKEY() const;
	virtual BOOL Open(HKEY hKey,const CString &sSubkey);
	virtual void Close();
	BOOL IsOpen();
	BOOL EnumKeyNames(DWORD dwEntryIndex,CString& sKeyName);
	BOOL EnumValueNames(DWORD dwEntryIndex,CString& sValueName,LPDWORD lpdwType = NULL);
	DWORD   ValueType(const CString& sValueName,LPDWORD lpdwSize = NULL);
	CString GetString(const CString& sValueName);
	DWORD   GetDWord(const CString&  sValueName);
protected:
	void CommonConstruction();
	HKEY    m_hKey;
	CString m_sSubkey;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiRegistryWriteAccess
class THUNK_NATIVE_API CNdUiRegistryWriteAccess: public CNdUiRegistryAccess {
public:
	CNdUiRegistryWriteAccess();
	CNdUiRegistryWriteAccess(HKEY hKey,const CString& sSubkey);
	virtual ~CNdUiRegistryWriteAccess();
	virtual BOOL Open(HKEY hKey,const CString& sSubkey);
	BOOL    SetString(const CString& sValueName,const CString& sValue);
	BOOL    SetDWord(const CString&  sValueName,DWORD dwValue);
};

//////////////////////////////////////////////////////////////////////////
// CNdUiRegistryDeleteAccess
class THUNK_NATIVE_API CNdUiRegistryDeleteAccess: public CNdUiRegistryWriteAccess {
public:
	CNdUiRegistryDeleteAccess();
	CNdUiRegistryDeleteAccess(HKEY hKey,const CString& sSubkey);
	virtual ~CNdUiRegistryDeleteAccess();
	BOOL    DeleteValue(const CString& sValueName);
	BOOL    DeleteAllValues();
	BOOL    DeleteKey(const CString&  sKeyName);
	BOOL    DeleteKeyAndSubkeys(const CString&  sKeyName);
	BOOL    DeleteAllKeys();
};

//////////////////////////////////////////////////////////////////////////
// CNdUiTabChildDialog
class THUNK_NATIVE_API CNdUiTabChildDialog : public CNdUiDialog {
	friend class CNdUiTab;
	DECLARE_DYNAMIC(CNdUiTabChildDialog);
public:
	CNdUiTabChildDialog (
	    CWnd *pParent=NULL,
	    HINSTANCE hDialogResource=NULL
	);
private:
	BOOL    m_bDirty;
	HWND    m_hWndFocus;
	CNdUiTab *m_pNcadTab;
	BOOL    TranslateTabKey ();
public:
//!!!private:
	void    SetNcadTabPointer (CNdUiTab *pNcadTab);
public:
	CNdUiTab *GetNcadTabPointer ();
	CNcUiTabMainDialog *GetMainDialog ();
	int     GetTabIndex ();
	BOOL    IsDirty ();
	virtual void    OnTabActivation (BOOL bActivate);
	virtual BOOL    OnTabChanging ();
	void    SetNcadTabChildFocus (HWND hWndFocus);
	void    SetDirty (BOOL bDirty=TRUE);
	void    SetValidationInfo (CDataExchange *pDX);
protected:
	virtual void    OnInitDialogBegin ();
	virtual void    OnInitDialogFinish ();
public:
	enum { IDD = 0 };
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnMainDialogCancel();
	virtual void OnMainDialogOK();
	virtual BOOL OnMainDialogHelp();
	virtual void OnMainDialogApply();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual void OnOK();
public:
//!!!protected:
	void OnSize(UINT nType, int cx, int cy);
protected:
	LRESULT OnResizePage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcUiTabChildDialog
class THUNK_NATIVE_API CNcUiTabChildDialog : public CNdUiTabChildDialog {
	DECLARE_DYNAMIC(CNcUiTabChildDialog);
public:
	            CNcUiTabChildDialog (
	                CWnd *pParent=NULL,
	                HINSTANCE hDialogResource=NULL
	            );
	virtual         ~CNcUiTabChildDialog ();
public:
	virtual CWnd    *AppMainWindow ();
	virtual HINSTANCE AppResourceInstance ();
	virtual LPCTSTR AppRootKey ();
	virtual void    EnableFloatingWindows (BOOL allow);
	virtual BOOL OnMainDialogHelp();
	virtual void    OnDialogHelp();
public:
	enum { IDD = 0 };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	DECLARE_MESSAGE_MAP()
};

// !!! OLD
//
//class THUNK_NATIVE_API CNcUiTabChildDialog : public CNcUiDialog
//{
//    DECLARE_DYNAMIC(CNcUiTabChildDialog)
//
//    friend class CNcUiTab;
//
//public:
	//    CNcUiTabChildDialog(CWnd* pParent = NULL, HINSTANCE hDialogResource = NULL);
//    virtual ~CNcUiTabChildDialog();
//
//    virtual BOOL OnInitDialog();
//
//    void SetNcadTabPointer(CNcUiTab* pTab);
//    CNcUiTab* GetNcadTabPointer();
//    CNcUiTabMainDialog* GetMainDialog();
//    int GetTabIndex();
//
//    virtual void OnTabActivation(BOOL bActivate);
//    virtual BOOL OnTabChanging();
//
//    virtual void OnMainDialogCancel();
//    virtual void OnMainDialogOK();
//    //virtual BOOL OnMainDialogHelp();
//    virtual void OnMainDialogApply();
//
//    void SetDirty(BOOL bDirty=TRUE);
//    BOOL IsDirty();
//
//protected:
	//    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
//    virtual void OnCancel();
//    virtual void OnOK();
//    virtual BOOL PreTranslateMessage(MSG* pMsg);
//
//    DECLARE_MESSAGE_MAP()
//
//private:
	//    BOOL      m_bDirty;
//    CNcUiTab* m_pTab;
//    HWND      m_hWndFocus;
//};

//////////////////////////////////////////////////////////////////////////
// CNdUiBalloonTip
class THUNK_NATIVE_API CNdUiBalloonTip : public CNdUiTipWindow {
	DECLARE_DYNAMIC(CNdUiBalloonTip)
public:
	            CNdUiBalloonTip ();
	virtual         ~CNdUiBalloonTip ();
protected:
	    CPoint  m_initialCursorPos;
	virtual void    DrawBorder (CDC& dc, CRect& rExterior, CRect& rInterior);
virtual void    DrawContent (CDC& dc, CRect& rInterior);
public:
	virtual void    Hide ();
	virtual void    Show ();
public:
protected:
	 void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNdToolTipCtrl
class THUNK_NATIVE_API CNdToolTipCtrl : public CToolTipCtrl {
	DECLARE_MESSAGE_MAP()
public:
	CNdToolTipCtrl();
	virtual ~CNdToolTipCtrl() {}
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	 int OnCreate(LPCREATESTRUCT lpCreateStruct);
	 void OnDestroy();
	static void SetToolTipsFlag(BOOL bToolTipsFlag);
	static void SetDeaultDelayTime(int nDelay);
protected:
	virtual NdToolTip * CreateAdToolTipInstance();
	NdToolTip* m_pToolTip;
	BOOL m_bActivate;
	UINT m_nDelayTime;
private:
	static BOOL m_bToolTipHasCreated;
	static BOOL m_bToolTipsFlag;
	static UINT m_nDefaultDealyTime;
};

//////////////////////////////////////////////////////////////////////////
// CNdWthToolTipCtrl
class THUNK_NATIVE_API CNdWthToolTipCtrl : public CNdToolTipCtrl {
	DECLARE_MESSAGE_MAP()
public:
	NdWthToolTip* GetWthToolTip();
protected:
	virtual NdToolTip * CreateAdToolTipInstance();
};

//////////////////////////////////////////////////////////////////////////
// CNdUiTheme
class THUNK_NATIVE_API CNdUiTheme {
	friend class CNdUiThemeManager;
public:
	COLORREF GetColor (NdUiThemeElement nDisplayElement) const;
	BOOL SetColor(NdUiThemeElement nDisplayElement, COLORREF crColor);
	BOOL SetFont(NdUiThemeElement nDisplayElement,LOGFONT *plf=NULL);
	BOOL GetFont(NdUiThemeElement nDisplayElement,LOGFONT *plf) const;
	BOOL GetFont(NdUiThemeElement nDisplayElement,CFont *& pFont) const;
	BOOL GetData(int nElement, DWORD& dwData) const;
	void SetData(int nElement, const DWORD& dwData);
	BOOL GetData(int nElement, CString& sData) const;
	void SetData(int nElement, const CString& sData);
	void* GetDataPtr(int nElement) const;
	void SetDataPtr(int nElement, void* pData);
	BOOL RegisterReactor(CNdUiThemeModifiedReactor * pReactor);
	BOOL UnregisterReactor(CNdUiThemeModifiedReactor * pReactor);
	void SuspendModifiedNotifications() { m_nModNotificationsSuspended++; }
	void ResumeModifiedNotifications();
	void SendModifiedNotification() const;
	bool UsesActiveThemeColors(){return m_bUsesActiveThemeColors;}
	void IncrementRefCount() { m_nRefCount++; }
	CNdUiTheme& operator=(const CNdUiTheme *pTheme);
private:
	CNdUiTheme();
	virtual ~CNdUiTheme();
	void InitWithActiveThemeColors();
	void SendThemeModifiedNotifications(NdUiThemeElement nElement) const;
	void CheckXP();
	COLORREF GetActiveThemeColor(NdUiThemeElement nElement) const;
	BOOL UsesXP() { return m_bUsesXPThemes; };
	void DecrementRefCount() { m_nRefCount--; }
	int RefCount() { return m_nRefCount; }
	int    m_nRefCount;
	bool   m_bUsesActiveThemeColors;
	CTypedPtrArray<CPtrArray, CNdUiThemeModifiedReactor*> m_arrayModReactors;
	int m_nModNotificationsSuspended;
	CMap<int, int, DWORD, DWORD> m_mapDwordValues;
	CMap<int, int, CString, CString> m_mapStringValues;
	CMap<int, int, void*, void*> m_mapPointerValues;
	LOGFONT             m_lfWorksheet;
	LOGFONT             m_lfWorksheetCaption;
	LOGFONT             m_lfPaletteCaption;
	LOGFONT             m_lfInspectorItem;
	LOGFONT             m_lfInspectorRoot;
	LOGFONT             m_lfPaletteTab;
	LOGFONT             m_lfPalette;
	LOGFONT             m_lfPaletteToolTip;
	COLORREF            m_crPaletteBkgnd;
	COLORREF            m_crPaletteCaptionBkgnd;
	COLORREF            m_crPaletteCaptionInactive;
	COLORREF            m_crPaletteCaptionText;
	COLORREF            m_crPaletteCaptionInactiveText;
	COLORREF            m_crPaletteItemText;
	COLORREF            m_crPaletteTabText;
	COLORREF            m_crPaletteTabBackground;
	COLORREF            m_crPaletteBorder;
	COLORREF            m_crPaletteTabShadow;
	COLORREF            m_crPaletteTabHighlight;
	COLORREF            m_crPaletteTabSelectHilite;
	COLORREF            m_crPaletteTabTextHilite;
	COLORREF            m_crPaletteScrollBackground;
	COLORREF            m_crPaletteScrollThumb;
	COLORREF            m_crPaletteScrollArrow;
	COLORREF            m_crPaletteButtonBorder;
	COLORREF            m_crPaletteButtonText;
	COLORREF            m_crPaletteButtonTextDisabled;
	COLORREF            m_crPaletteToolTip;
	COLORREF            m_crPaletteToolTipText;
	COLORREF            m_crWorksheetBkgnd;
	COLORREF            m_crWorksheetCaptionBkgnd;
	COLORREF            m_crWorksheetCaptionText;
	COLORREF            m_crWorksheetBtnShadow;
	COLORREF            m_crWorksheetBtnText;
	COLORREF            m_crWorksheetBtnTextDisabled;
	COLORREF            m_crWorksheetScroll;
	COLORREF            m_crWorksheetScrollThumb;
	COLORREF            m_crWorksheetBorder;
	COLORREF            m_crWorksheetGripHighlight;
	COLORREF            m_crInspector;
	COLORREF            m_crInspectorTop;
	COLORREF            m_crInspectorCat;
	COLORREF            m_crInspectorItem;
	COLORREF            m_crInspectorBorder;
	COLORREF            m_crInspectorBorderItem;
	COLORREF            m_crInspectorTextTop;
	COLORREF            m_crInspectorTextCat;
	COLORREF            m_crInspectorTextItem;
	COLORREF            m_crInspectorFGHighlight;
	COLORREF            m_crInspectorBGHighlight;
	COLORREF            m_crInspector3dShadow;
	COLORREF            m_crInspectorControl;
	COLORREF            m_crInspectorCatChevron1;
	COLORREF            m_crInspectorCatChevron2;
	COLORREF            m_crInspectorSubChevron;
	COLORREF            m_crPanelBackground;
	COLORREF            m_crPanelSashBackground;
	COLORREF            m_crPanelBorder;
	COLORREF            m_crControlBorder;
	COLORREF            m_crControlBackground;
	COLORREF            m_crDisabledControlBorder;
	COLORREF            m_crControlSupport;
	COLORREF            m_crPaletteFrameInnerBorder;
	COLORREF            m_crPaletteFrameOuterBorder;
	COLORREF            m_crPaletteFrameBackground;
	COLORREF            m_crPaletteFrameShadow;
	COLORREF            m_crInspectorTopGradient1;
	COLORREF            m_crInspectorTopGradient2;
	COLORREF            m_crPaletteScrollBackgroundBorder;
	COLORREF            m_crPaletteScrollBackgroundGradient1;
	COLORREF            m_crPaletteScrollBackgroundGradient2;
	COLORREF            m_crPaletteScrollSliderInactive;
	COLORREF            m_crPaletteScrollSliderActiveOuterBorder;
	COLORREF            m_crPaletteScrollSliderActiveOuterGradient1;
	COLORREF            m_crPaletteScrollSliderActiveOuterGradient2;
	COLORREF            m_crPaletteScrollSliderActiveOuterGradient3;
	COLORREF            m_crPaletteScrollSliderActiveOuterGradient4;
	COLORREF            m_crPaletteScrollSliderActiveInnerGradient1;
	COLORREF            m_crPaletteScrollSliderActiveInnerGradient2;
	COLORREF            m_crInspectorClosedOuterBorder;
	COLORREF            m_crInspectorOpenOuterBorder;
	COLORREF            m_crInspectorInnerBorder;
	COLORREF            m_crAnchorBarOuterBorder;
	COLORREF            m_crAnchorBarEmbossRightBottom;
	COLORREF            m_crAnchorBarEmbossLeftTop;
	COLORREF            m_crAnchorBarInnerHighlight;
	COLORREF            m_crAnchorBarGradient1;
	COLORREF            m_crAnchorBarGradient2;
	COLORREF            m_crAnchorBarActiveTitleBackground;
	COLORREF            m_crAnchorBarCaptionText;
	COLORREF            m_crGrabBarDotDark;
	COLORREF            m_crGrabBarDotLight;
	COLORREF            m_crControlBarTitleBackground;
	COLORREF            m_crAppFrameBorder;
	COLORREF            m_crAppFrameOuterBorder;
	BOOL                m_bUsesXPThemes;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiThemeMgrReactor
class CNdUiThemeMgrReactor {
public:
	CNdUiThemeMgrReactor();
	virtual void ThemeAdded(const CString & strThemeName) = 0;
	virtual void ThemeRemoved(const CString & strThemeName) = 0;
	virtual void SystemColorChanged() = 0;
	~CNdUiThemeMgrReactor();
};

//////////////////////////////////////////////////////////////////////////
// CNdUiThemeManager
class CNdUiThemeManager {
	friend class CNdUiThemeMgrReactor;
public:
	CNdUiThemeManager();
	~CNdUiThemeManager();
	CNdUiTheme * GetTheme(const NCHAR *pThemeName);
	BOOL ReleaseTheme(CNdUiTheme * pTheme);
	BOOL HasTheme(const NCHAR *pThemeName) const;
	void SystemColorChanged();
private:
	int  RemoveTheme(const NCHAR *pThemeName);
	void Cleanup();
	int  GetThemeIndex(const NCHAR *pThemeName) const;
	int  GetThemeIndex(const CNdUiTheme *pTheme) const;
	BOOL RegisterThemeMgrReactor(CNdUiThemeMgrReactor * pReactor);
	BOOL UnregisterThemeMgrReactor(CNdUiThemeMgrReactor * pReactor);
	void NotifyThemeAddedReactors(const CString & strThemeName);
	void NotifySysColorReactors();
	CObArray        m_list;
	CTypedPtrArray<CPtrArray, CNdUiThemeMgrReactor*> m_arrayThemeMgrReactors;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiVolumeDescriptor
class THUNK_NATIVE_API CNdUiVolumeDescriptor {

	friend class CNdUiPathname;
public:
	CNdUiVolumeDescriptor();
	CNdUiVolumeDescriptor(const CString&);
	virtual ~CNdUiVolumeDescriptor();
	virtual BOOL CheckReadOnly() const;
	virtual BOOL ValidateFilename(const CString*,
	                              const BOOL wildcard_ok = false ) const =0;
	virtual BOOL ValidateSegment(const CString*,
	                             const BOOL wildcard_ok = false ) const =0;
	virtual BOOL IsCaseSensitive(void) const;
	virtual BOOL PreservesCase(void) const;
	virtual BOOL AllowsCaseSensitiveLookup(void) const;
	virtual void VolCase( CString& ) const;
	virtual BOOL VolMatch( const NCHAR * a, const CString* b ) const;
	virtual BOOL VolMatch( const CString* a, const CString* b) const;
	virtual const CString* GetLocalName() const;
	virtual LONG GetVolFreeSpace() const;
	virtual BOOL WillFit(DWORD) const;
	virtual BOOL VolumeValid() const;
#ifdef _DEBUG
	virtual void debug_dump(FILE*) const;
#endif
	BOOL IsRemote() const;
	BOOL IsRemovable() const;
protected:
	void GetConnectionName( void );
	int Find(const CString& str, UINT ch) const;
	int IsControl(int c) const;
	FS_TYPE m_vol_fs_type;
	typedef unsigned flagbits;
	flagbits m_d_fixed:    1;
	flagbits m_d_removable: 1;
	flagbits m_d_cdrom: 1;
	flagbits m_d_remote: 1;
	flagbits m_d_ramdisk: 1;
	flagbits m_d_readonly: 1;
	flagbits m_d_caseSensitive: 1;
	CString* m_vol_localname;
	int    m_max_component_size;
	int    m_max_path_length;
	NCHAR    m_vol_slash;
	BOOL     mbUnused;
	DWORD    m_vol_serial;
	DWORD    m_fsflags;
	CString* m_vol_label;
	CString* m_connection_name;
	const NCHAR * m_doubleslash;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiNTFSVolumeDescriptor
class THUNK_NATIVE_API CNdUiNTFSVolumeDescriptor : public CNdUiVolumeDescriptor {
	public:
		CNdUiNTFSVolumeDescriptor(const CString&);
		~CNdUiNTFSVolumeDescriptor(){};
		BOOL ValidateFilename( const CString*,
		                       const BOOL wildcard_ok = false ) const;
		BOOL ValidateSegment( const CString*,
		                      const BOOL wildcard_ok = false ) const;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiVFATVolumeDescriptor
class THUNK_NATIVE_API CNdUiVFATVolumeDescriptor : public CNdUiVolumeDescriptor {
public:
	CNdUiVFATVolumeDescriptor(const CString&);
	~CNdUiVFATVolumeDescriptor(){};
	BOOL ValidateFilename(const CString*,
	                      const BOOL wildcard_ok = false ) const;
	BOOL ValidateSegment(const CString*,
	                     const BOOL wildcard_ok = false ) const;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiHPFSVolumeDescriptor
class THUNK_NATIVE_API CNdUiHPFSVolumeDescriptor : public CNdUiVolumeDescriptor {
public:
	CNdUiHPFSVolumeDescriptor(const CString&);
	~CNdUiHPFSVolumeDescriptor(){};
	BOOL ValidateFilename( const CString*,
	                      const BOOL wildcard_ok = false ) const;
	BOOL ValidateSegment( const CString*,
	                     const BOOL wildcard_ok = false ) const;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiCDFSVolumeDescriptor
class THUNK_NATIVE_API CNdUiCDFSVolumeDescriptor : public CNdUiVolumeDescriptor {
public:
	CNdUiCDFSVolumeDescriptor(const CString&);
	~CNdUiCDFSVolumeDescriptor(){};
	BOOL ValidateFilename( const CString*,
	                      const BOOL wildcard_ok = false ) const;
	BOOL ValidateSegment( const CString*,
	                     const BOOL wildcard_ok = false ) const;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiFATVolumeDescriptor
class THUNK_NATIVE_API CNdUiFATVolumeDescriptor : public CNdUiVolumeDescriptor {
public:
	CNdUiFATVolumeDescriptor(const CString&);
	~CNdUiFATVolumeDescriptor(){};
	BOOL ValidateFilename( const CString*,
	                      const BOOL wildcard_ok = false ) const;
	BOOL ValidateSegment( const CString*,
	                     const BOOL wildcard_ok = false ) const;
protected:
	int m_segc;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiUFSVolumeDescriptor
class THUNK_NATIVE_API CNdUiUFSVolumeDescriptor : public CNdUiVolumeDescriptor {
public:
	CNdUiUFSVolumeDescriptor(const CString&);
	~CNdUiUFSVolumeDescriptor(){};
	BOOL ValidateFilename( const CString*,
	                      const BOOL wildcard_ok = false ) const;
	BOOL ValidateSegment( const CString*,
	                     const BOOL wildcard_ok = false ) const;
};

//////////////////////////////////////////////////////////////////////////
// CNdUiNOFSVolumeDescriptor
class THUNK_NATIVE_API CNdUiNOFSVolumeDescriptor : public CNdUiVolumeDescriptor {
public:
	CNdUiNOFSVolumeDescriptor(const CString&);
	~CNdUiNOFSVolumeDescriptor(){};
	BOOL ValidateFilename( const CString*,
	                      const BOOL wildcard_ok = false ) const;
	BOOL ValidateSegment( const CString*,
	                     const BOOL wildcard_ok = false ) const;
};
// AutoGen.

//////////////////////////////////////////////////////////////////////////
// CNcFdUiFieldFormatDialog
class THUNK_NATIVE_API CNcFdUiFieldFormatDialog : public CNcFdUiFormatDialog {
	DECLARE_DYNAMIC(CNcFdUiFieldFormatDialog)
	//CNcFdUiFieldFormatDialog(CWnd* pParent, BOOL bNew );
};


//////////////////////////////////////////////////////////////////////////
// CNdUiFileDialog
class THUNK_NATIVE_API CNdUiFileDialog : public CFileDialog {
	DECLARE_DYNAMIC(CNdUiFileDialog);
public:
	CNdUiFileDialog (
	    BOOL bOpenFileDialog,
	    LPCTSTR lpszDefExt=NULL,
	    LPCTSTR lpszFileName=NULL,
	    DWORD dwFlags=OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	    LPCTSTR lpszFilter=NULL,
	    CWnd *pParentWnd=NULL,
	    HINSTANCE hDialogResource=NULL
	);
	virtual         ~CNdUiFileDialog ();
protected:
	virtual NDUI_REPLY DoNdUiMessage (
                    NDUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
	virtual NDUI_REPLY OnNotifyControlChange (UINT controlId, LPARAM lParam);
	virtual NDUI_REPLY OnNotifyControlValid (UINT controlId, BOOL isValid);
	virtual NDUI_REPLY OnNotifyGeneric (UINT controlId, LPARAM lParam);
	virtual NDUI_REPLY OnNotifyUpdateTip (CWnd *control);
private:
	HINSTANCE m_commandResourceInstance;
	BOOL    m_commandWindowWasEnabled;
	HWND    m_commandWindowWithFocus;
protected:
	NDUI_COMMAND_STATE m_commandState;
	void    BeginEditorCommand ();
	void    CancelEditorCommand ();
	void    CompleteEditorCommand (BOOL restoreDialogs=TRUE);
	void    MakeDialogsVisible (BOOL visible);
public:
	BOOL    EditorCommandCancelled ();
protected:
	CString m_contextHelpFileName;
	CString m_contextHelpFullPathName;
	CString m_contextHelpPrefix;
	virtual BOOL    FindContextHelpFullPath (LPCTSTR fileName, CString& fullPath);
public:
	LPCTSTR GetContextHelpFileName ();
	void    SetContextHelpFileName (LPCTSTR pFileName);
	LPCTSTR GetContextHelpFullPathName ();
	void    SetContextHelpFullPathName (LPCTSTR pFullPathName);
	LPCTSTR GetContextHelpPrefix ();
	void    SetContextHelpPrefix (LPCTSTR pPrefix);
	void    SetDialogName (LPCTSTR name);
	void    SetDialogHelpTag (LPCTSTR tag) {m_dlgHelpTag = tag;}
	void    GetDialogName (CString& name) {name = m_dlgName;}
	void    GetDialogHelpTag (CString& tag) {tag = m_dlgHelpTag;}
private:
	HINSTANCE m_hDialogResourceSaved;
	CString m_dlgHelpTag;
	CString m_dlgName;
protected:
	int    m_bUseTips;
	HINSTANCE m_hDialogResource;
	HICON   m_hIcon;
	CNdUiTextTip *m_pTextTip;
	CToolTipCtrl *m_pToolTip;
	CString m_rootKey;
	CWnd* m_pParent;
	virtual void    OnInitDialogBegin ();
	virtual void    OnInitDialogFinish ();
public:
	virtual CWnd    *AppMainWindow ();
	virtual HINSTANCE AppResourceInstance ();
	virtual LPCTSTR AppRootKey ();
	virtual void    EnableFloatingWindows (BOOL allow);
	int    GetUseTips ();
	void    SetUseTips (int useTips);
	HICON   GetDialogIcon();
	void    SetDialogIcon(HICON hIcon);
	virtual void OnDialogHelp();
	virtual BOOL DoDialogHelp();
public:
	enum { IDD = 0 };
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual INT_PTR DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnInitDialog();
	LRESULT OnNdUiMessage (WPARAM wParam, LPARAM lParam);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnHelpInfo(HELPINFO* lpHelpInfo);
	BOOL OnNotify_ToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};

class THUNK_NATIVE_API CNdUiPalette : public hostUiPalette
{
	DECLARE_DYNAMIC(CNdUiPalette)

public:
	CNdUiPalette();
	virtual ~CNdUiPalette();

	CNdUiPaletteSet* GetPaletteSet();
	void SetPaletteSet(CNdUiPaletteSet* pSet);

	DECLARE_MESSAGE_MAP()
};


class THUNK_NATIVE_API CNdUiPaletteSet : public hostUiPaletteSet
{
	DECLARE_DYNCREATE(CNdUiPaletteSet);

public:
	CNdUiPaletteSet ();
public:
	static void ApplyGlobalOpacities(BOOL bApply);
	BOOL AutoRollupStyle();
	BOOL CloseButtonStyle();
	BOOL EditNameStyle();
	static int GetGlobalOpacity();
	static int GetGlobalRolloverOpacity ();
	static UINT GetGlobalTransparency();
	int GetOpacity() const;
	int GetRolloverOpacity() const;
	CNdUiTheme* GetTheme();
	CFont*  GetWindowFont();
	static BOOL IsGlobalOpacitiesApplied();
	virtual BOOL NameEditValidation(CEdit* pEdit);
	void OnTogglePin();
	BOOL PropertiesMenuStyle();
	BOOL RolledUp();
	void RollOut(bool bDelay = false);
	void RollUp();
	bool SetAllowTransparency(CString key, bool bDefault);
	static BOOL SetGlobalOpacity(int nOpacity);
	static BOOL SetGlobalRolloverOpacity(int nOpacity);
	static bool SetGlobalTransparency(UINT flag);
	BOOL SetOpacity(int nOpacity);
	BOOL SetRolloverOpacity(int nOpacity);
	CNdUiTheme* SetTheme(CNdUiTheme* pTheme);
	
	// NdUiTitleBarLocation
	typedef enum {
		kLeft = 0,
		kRight
	} NdUiTitleBarLocation ;

	void SetTitleBarLocation(NdUiTitleBarLocation loc);
	BOOL SinglePaletteTabStyle();
	BOOL SnapStyle();
	NdUiTitleBarLocation TitleBarLocation();
	virtual void TitleBarLocationUpdated(NdUiTitleBarLocation newLoc);
	BOOL UseSinglePaletteTabNameStyle();
	CString GetName();
	BOOL SetName(LPCTSTR pszName);

	DWORD GetPaletteSetStyle();
	void  SetPaletteSetStyle(DWORD dwStyle);

	CNdUiPalette* GetPalette(int nIndex);
	CNdUiPalette* GetActivePalette();

	virtual void PaletteAdded(CNdUiPalette* pPalette) {return;}
	virtual void PaletteRemoved(CNdUiPalette* pPalette) { return; }
	virtual void PaletteActivated(CNdUiPalette* pActivated, CNdUiPalette* pDeactivated) { return; }

	virtual void PaletteAdded(hostUiPalette* pPalette)   {
		PaletteAdded((CNdUiPalette*)dynamic_cast<CNdUiPalette*>(pPalette));
	}
	virtual void PaletteRemoved(hostUiPalette* pPalette)  {
		PaletteRemoved((CNdUiPalette*)dynamic_cast<CNdUiPalette*>(pPalette));
	}
	virtual void PaletteActivated(hostUiPalette* pActivated, hostUiPalette* pDeactivated)  {
		PaletteActivated((CNdUiPalette*)dynamic_cast<CNdUiPalette*>(pActivated), (CNdUiPalette*)dynamic_cast<CNdUiPalette*>(pDeactivated));
	}

};

//int  NdUiAlertDialog (
//    LPCTSTR captionText,
//    LPCTSTR msg0Text,
//    LPCTSTR button0Text,
//    LPCTSTR button1Text,
//    UINT defButton = 0
//);
void THUNK_NATIVE_API InitNdUiDLL();

void THUNK_NATIVE_API NdUiEnableDockControlBars(BOOL bEnable, CStringArray* pToolIds = NULL);

BOOL THUNK_NATIVE_API NdUiFindContextHelpFullPath (
    LPCTSTR fileName, CString& fullPath
);

HWND THUNK_NATIVE_API NdUiGetSafeParentHwnd();
THUNK_NATIVE_API CWnd* NdUiGetSafeParentWnd();
void THUNK_NATIVE_API NdUiHideBalloonTip (CWnd*control);
const UINT THUNK_NATIVE_API NdUiMessage ();
NDUI_NOTIFY THUNK_NATIVE_API NdUiNotification (WPARAM wp);
NDUI_REPLY THUNK_NATIVE_API NdUiNotify (CWnd* w, UINT id, NDUI_NOTIFY n, DWORD_PTR lParam);
UINT THUNK_NATIVE_API NdUiNotifyId (WPARAM wp);
BOOL THUNK_NATIVE_API NdUiPostNotify (CWnd* w, UINT id, NDUI_NOTIFY n, DWORD_PTR lParam);

bool THUNK_NATIVE_API NdUiRegisterDockingTool (LPCTSTR lpszToolName, LPCTSTR lpszCommand, UINT nToolbarID);

THUNK_NATIVE_API void NdUiRegisterFloatingFrameClassAddress(CRuntimeClass** pClass);
THUNK_NATIVE_API void NdUiRegisterPaletteSetFloatingFrameClass(CRuntimeClass* pClass);
bool THUNK_NATIVE_API NdUiRegisterTool (LPCTSTR lpszToolName, LPCTSTR lpszCommand, CLSID* pID);
BOOL THUNK_NATIVE_API NdUiShowBalloonTip (CWnd*owner, CWnd*control, LPCTSTR text, BOOL beep);

void THUNK_NATIVE_API NdUiShowDockControlBars (bool bShow);
void THUNK_NATIVE_API NdUiSubstituteShellFont (CWnd& dlg, CFont& font);
//bool THUNK_NATIVE_API CanStealFocusFromDockedWindow (); for internal use

THUNK_NATIVE_API int NcFdUiInvokeFieldDialog(NcDbField*& pNewField,
                                             BOOL bEdit,
                                             NcDbDatabase* pDb,
                                             CWnd* pParent = NULL);
THUNK_NATIVE_API CNcFdUiFieldManager* NcFdUiGetFieldManager(void);

int THUNK_NATIVE_API NdUiAlertDialog (
	LPCTSTR captionText,
	LPCTSTR msg0Text,
	LPCTSTR button0Text,
	LPCTSTR button1Text,
	UINT defButton = 0
);

THUNK_NATIVE_API void ncedAddRemoveCmdUIClient(LPCWSTR cmdname, hostUpdateCmdUIClient*,bool fadd);

#endif // __nanothunk_ui_h__
