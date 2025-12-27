#ifndef _navigation_h
#define _navigation_h

#pragma once

#include "afxtempl.h"       // MFC array template classes

class CNavListCtrl;
class CNavDropSource;
class CNavDataArray;
class CNavFilterArray;
class CNavFilter;
class CNavDataArray;
class CNavPathname;

class CNcUiNavPreviewButton;

typedef enum
{
	// Open with no template flags
	ncUiOpenNoTemplateNone      =   0x0000,
	ncUiOpenNoTemplateImperail  =   0x0001,
	ncUiOpenNoTemplateMetric    =   0x0002
} NcUiOpenNoTemplateFlag;

// Tools menu items.
enum NavToolsMenuItem
{
	NAV_TOOLS_ITEM_FIND = 0x1,
	NAV_TOOLS_ITEM_LOCATE = 0x2,
	NAV_TOOLS_ITEM_FTPMODIFY = 0x4,
	NAV_TOOLS_ITEM_SIMPLESTORAGE = 0x8,
	NAV_TOOLS_ITEM_ADDCURRENT = 0x10,
	NAV_TOOLS_ITEM_ADDFAVORITES = 0x20
};

enum NavInetTransferActions
{
	NAV_INET_IGNORE_CACHE = 0x1,
	NAV_INET_STOP_ON_ERROR = 0x2,
	NAV_INET_KEEP_CACHE     = 0x4
};
// The following identifies the type of the datum.
typedef enum {
	kNavUnknown,        // Unknown data type.
	kNavShellItem,      // Standard file system item.
	kNavURL,            // General URL item.
	kNavUNC,            // UNC path item.
	kNavExtension,      // File navigation extension item (includes FTP).
	kNavWebFolders,     // 'Web Folders' item. (WEBDAV)
} NAV_DATA_TYPE;

/////////////////////////////////////////////////////////////////////////////
// File Navigation Array

template <class T>
class CNavArray : public CTypedPtrArray<CObArray, T*> {
public:
	            CNavArray ();
	virtual     ~CNavArray ();

// Data management
protected:
	virtual T       *NewData ();
public:
	T       *AddData ();
	int     GetCount ();
	T       *GetData (INT_PTR index);
	BOOL    IsIndexValid (INT_PTR index);
	void    RemoveData (INT_PTR index);
	void    RemoveAllData ();
};

/////////////////////////////////////////////////////////////////////////////
// File Navigation Array - implementation

template <class T>
CNavArray<T>::CNavArray () :
	CTypedPtrArray<CObArray, T*>()
{
}

template <class T>
CNavArray<T>::~CNavArray ()
{
	RemoveAllData();
}

//----------------
// Data management

template <class T>
T    *CNavArray<T>::AddData ()
{
	T    *d = NewData();

	ASSERT(d != NULL);
	if (d != NULL)
		Add(d);
	return d;
}

template <class T>
int  CNavArray<T>::GetCount ()
{
	const size_t nCount = GetUpperBound() + 1;
	ASSERT(nCount < 0x1000000);   // 16M sanity check
	return (int)nCount;
}

template <class T>
T    *CNavArray<T>::GetData (INT_PTR index)
{
	T    *d = NULL;

	if (IsIndexValid(index))
		d = GetAt(index);
	return d;
}

template <class T>
BOOL CNavArray<T>::IsIndexValid (INT_PTR index)
{
	return ((index >= 0) && (index <= GetUpperBound()));
}

template <class T>
T    *CNavArray<T>::NewData ()
{
	return new T;
}

template <class T>
void CNavArray<T>::RemoveData (INT_PTR index)
{
	T    *d;

	if (IsIndexValid(index)) {
		d = GetAt(index);
		RemoveAt(index);
		delete d;
	}
}

template <class T>
void CNavArray<T>::RemoveAllData ()
{
	const int  n = this->GetCount();

	for (int i = 0; i < n; i++) {
		T *d = GetAt(i);
		delete d;
	}
	RemoveAll();
	FreeExtra();
}

//////////////////////////////////////////////////////////////////////////
// CNavData
class THUNK_NATIVE_API CNavData : public CObject {
public:
	            CNavData ();
	virtual     ~CNavData ();
protected:
	NAV_DATA_TYPE m_dataType;
	LPITEMIDLIST m_id;
	CString m_text;
	CString m_textInFolder;
	CNavPathname* m_pathname;
	CString m_userName;
	CString m_password;
	CString m_extensionName;
public:
	NAV_DATA_TYPE GetDataType ();
	void    SetDataType (NAV_DATA_TYPE dataType);
	LPITEMIDLIST GetID ();
	void    SetID (LPITEMIDLIST id);
	LPCTSTR GetText ();
	void    SetText (LPCTSTR text);
	LPCTSTR GetTextInFolder ();
	void    SetTextInFolder (LPCTSTR text);
	CNavPathname* GetPathname ();
	void    SetPathname (CNavPathname* pathname);
	LPCTSTR GetUserName ();
	void    SetUserName (LPCTSTR name);
	LPCTSTR GetPassword ();
	void    SetPassword (LPCTSTR password);
	BOOL    IsRemote();
	BOOL    IsExtension();
	LPCTSTR GetExtensionName ();
	void    SetExtensionName (LPCTSTR name);
	BOOL    GetURL(CString& strURL);
protected:
	void*  m_userData;
public:
	void*   GetUserData();
	void*   SetUserData(void* data);
};

//////////////////////////////////////////////////////////////////////////
// CNavDataArray
class THUNK_NATIVE_API CNavDataArray : public CNavArray<CNavData> {
public:
	            CNavDataArray ();
virtual         ~CNavDataArray ();
};

//////////////////////////////////////////////////////////////////////////
// CNavDialog
class THUNK_NATIVE_API CNavDialog : public CNdUiDialog {
	DECLARE_DYNAMIC(CNavDialog)

public:
	CNavDialog(
	    CNavDataArray& dataArray,
	    CNavFilterArray& filterArray,
	    UINT idd=0,
	    CWnd *pParent=NULL,
	    HINSTANCE hDialogResource=NULL
	);
	virtual ~CNavDialog();
	enum { IDD = 0 };
	CNavDataArray& GetDataArray();
	CNavFilterArray& GetFilterArray();
	LPCTSTR GetDialogCaption();
	void    SetDialogCaption(LPCTSTR caption);
	LPCTSTR GetDefaultFileExtension();
	void    SetDefaultFileExtension(LPCTSTR ext);
	int     GetFilterIndex();
	void    SetFilterIndex(int index);
	int     GetDefaultFilterIndex();
	void    SetDefaultFilterIndex(int index);
	DWORD   GetInitialFilterIndex();
	int     GetForceFilterIndex();
	void    SetForceFilterIndex(int index);
	LPCTSTR GetForceInitialFolder();
	void    SetForceInitialFolder(LPCTSTR folder);
	void    SetDefaultInitialFolder(LPCTSTR folder);
	LPCTSTR GetDefaultInitialFolder();
	LPCTSTR GetInitialFileName();
	void    SetInitialFileName(LPCTSTR name);
	BOOL    GetUseRegExtensionFlags();
	void    SetUseRegExtensionFlags(BOOL bUse);
	BOOL    GetConfirmReplace();
	void    SetConfirmReplace(BOOL confirm);
	BOOL    GetAcceptAnyFileExtension();
	void    SetAcceptAnyFileExtension(BOOL any);
	BOOL    GetNoURLFileTransfer();
	void    SetNoURLFileTransfer(BOOL noTransfer);
	BOOL    GetNoURLsAllowed();
	void    SetNoURLsAllowed(BOOL noURLs);
	UINT    GetViewMode();
	void    SetViewMode(UINT viewMode);
	BOOL    GetMultiSelectAllowed();
	void    SetMultiSelectAllowed(BOOL allow);
	BOOL    GetReadOnlyAllowed();
	void    SetReadOnlyAllowed(BOOL allow);
	BOOL    GetReadOnlyHidden();
	void    SetReadOnlyHidden(BOOL hidden);
	BOOL    GetReadOnlySpecified();
	void    SetReadOnlySpecified(BOOL readOnly);
	BOOL    GetCreatingFile();
	void    SetCreatingFile(BOOL create);
	UINT    GetToolsMenuItemsPresent();
	void    SetToolsMenuItemsPresent(UINT flag);
	BOOL    GetNoFTP();
	void    SetNoFTP(BOOL noFTP);
	BOOL    GetNoExtraExtensions();
	void    SetNoExtraExtensions(BOOL noExtraExtensions);
	BOOL    GetNoExtraExtensionsInPlaces();
	void    SetNoExtraExtensionsInPlaces(BOOL noExtraExtensions);
	BOOL    GetFoldersOnly();
	void    SetFoldersOnly(BOOL foldersOnly);
	BOOL    GetNoPlacesList();
	void    SetFolderListCtrl(CNavListCtrl* folderListCtrl);
	CNavListCtrl* GetFolderListCtrl();
	UINT    GetIDD();
	void    SetOkButtonText(LPCTSTR text);
	void    GetOkButtonText(CString& strOk, BOOL bIncludeAccel = TRUE);
	void    SetOkButtonMenuExists(BOOL bExists);
	void    AddDataToHistory();
	CNavFilter* GetCurrentFileExtension(CString& strExt);
	void SetFolderComboCurSel(int i);
	int GetToolsMenuItemPosition(NavToolsMenuItem itemFlag);
	BOOL GetPersonalFolderPath(CString& strPersonal);
	BOOL NavigateToFolder(LPCTSTR sFolder);
	void GetCurrentFolderForPersistence(CString& strFolder);
	void GetSingleDataFullPath(CString& strFullPath);
	void TrimWhiteSpace(CString& strName, BOOL bAll);
	void BrowseCurrentObject();
	int InsertUserItemInPlaces(int index, LPCTSTR sFullPath, LPCTSTR sText);
	void* GetImpObject() const;
	virtual BOOL SetAllDialogsData(const CString& cValueName, CString& cValue);
	virtual BOOL SetAllDialogsData(const CString& cValueName, DWORD dwValue);
	virtual BOOL GetAllDialogsData(const CString& cValueName, CString& cValue);
	virtual BOOL GetAllDialogsData(const CString& cValueName, DWORD& data);
	virtual void LocateFile();
	virtual BOOL GetProductName(CString& strProduct);
	virtual BOOL BeginDownloadFiles(CStringArray& strURLs, CDWordArray& dwActionCodes);
	virtual DWORD GetDownloadActionCodes(CString& strURL);
	virtual void OnDialogHelp();
	virtual void OnDialogHelp(LPCTSTR pHelpTag);
protected:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void PrepareOkMenu(CMenu* pMenu);
	virtual void PrepareToolsMenu(CMenu* pMenu);
	virtual void PrepareViewsMenu(CMenu* pMenu);
	virtual void OnCancel();
	virtual void OnOK();
	virtual OkHandlerErr PreprocessData(CNavDataArray& array);
	virtual OkHandlerErr CombineDataTextWithFolderName(CNavData* data, CString& strResult);
	virtual BOOL UpdateFileExtension(CString& strName, BOOL bCanUseCurrentExtension);
	virtual BOOL OnFileNameOK();
	virtual BOOL    VerifyURLSave();
	virtual BOOL OnUrlOK();
	virtual BOOL ReportURLTransferStatus(CDWordArray& dwErrorArray, CStringArray& strURLs, CStringArray& strLocals);
	virtual BOOL GetRecentDirectory(CString& strRecent);
	virtual BOOL FindInSearchPath(LPCTSTR sBase, CString* pFullPath);
	virtual void DisplaySearchError(LPCTSTR sBase);
	virtual void GetDefaultBrowserStartURL(CString& strStartPage);
	virtual BOOL LaunchBrowserDialog(CString& strSelectedURL, LPCTSTR strDialogCaption,
	                                 LPCTSTR strOk, LPCTSTR strStartPage);
	virtual void OnURLDownloadSuccess(CString& strURL);
	virtual void OnDoLocate();
	virtual void OnDoFind();
	virtual void OnDoAddToFavorites(BOOL bOneItem);
	virtual void Refresh();
	virtual void OnFileNameChange();
	virtual void OnFileNameSelectionChange();
	virtual void OnFilterChange();
	virtual void OnFolderItemChange();
	virtual void OnFolderChange();
	virtual void UpdateUIState();
	virtual NDUI_REPLY OnNotifyControlChange(UINT controlId, LPARAM lParam);
	virtual NDUI_REPLY OnNotifyGeneric(UINT controlId, LPARAM lParam);
	virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );
	 void OnDestroy();
	 void OnContextMenu(CWnd*, CPoint);
	 BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	 void OnKickIdle();
	 void OnSysColorChange();
private:
	 LRESULT OnWmGetIShellBrowser (WPARAM wp, LPARAM lp);
	 LRESULT OnWmDeviceChange     (WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
	void* m_navImp;
};

//////////////////////////////////////////////////////////////////////////
// CNavFilter
class THUNK_NATIVE_API CNavFilter : public CStringArray {
public:
	            CNavFilter ();
	virtual     ~CNavFilter ();
private:
	BOOL    m_bFullDescription;
protected:
	CString m_description;
	INT_PTR m_tagIndex;
public:
	LPCTSTR GetDescription ();
	void    SetDescription (LPCTSTR desc);
	void    GetFullDescription (CString& desc);
	void    SetFullDescription (LPCTSTR desc);
	INT_PTR GetTagIndex ();
	void    SetTagIndex (INT_PTR tagIndex);
	int     Find (LPCTSTR str);
	int     GetCount ();
	BOOL    IsAllowed (LPCTSTR fileName);
	LPTSTR SetFrom (LPTSTR str, BOOL bUseFullDescrition = FALSE);
	BOOL    GetMultiSelectAllowed ();
	void    SetMultiSelectAllowed (BOOL bMultiSelection);
};

//////////////////////////////////////////////////////////////////////////
// CNavFilterArray
class THUNK_NATIVE_API CNavFilterArray : public CNavArray<CNavFilter> {
public:
	            CNavFilterArray ();
	virtual     ~CNavFilterArray ();
public:
	void    SetFrom (LPCTSTR str, BOOL bUseFullDescrition = FALSE);
	int     Find (LPCTSTR str);
	int     FindExact (LPCTSTR str);
};

//////////////////////////////////////////////////////////////////////////
// CNavDropSource
class CNavDropSource : public COleDropSource {
public:
	CNavDropSource();
	CNavListCtrl* m_pListCtrl;
	SCODE GiveFeedback(DROPEFFECT dropEffect);
};

//////////////////////////////////////////////////////////////////////////
// CNavListCtrl
class THUNK_NATIVE_API CNavListCtrl : public CNdUiListCtrl {
public:
	CNavListCtrl ();
public:
protected:
	 void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	 LRESULT OnHandleDrag(UINT_PTR pDataSource, LPARAM nSelectedItem);
	DECLARE_MESSAGE_MAP()
	CImageList* m_pDragImage;
	CNavDropSource m_dropSource;
};

//////////////////////////////////////////////////////////////////////////
// Nc3dDwfNavTreeNode
class Nc3dDwfNavTreeNode : public NcRxObject {
public:
	virtual const NcString&     displayName() const = 0;
	virtual const NcArray<long>& keys() const = 0;
	virtual       int           nDescendants() const = 0;
	virtual       bool          isGroup() const = 0;
	virtual const NcArray<const Nc3dDwfNavTreeNode*>& children() const = 0;
	virtual       bool          isBlock() const = 0;
	virtual       bool          addChild(const Nc3dDwfNavTreeNode* node) = 0;
	virtual       bool          removeChild(const Nc3dDwfNavTreeNode* node) = 0;
};

//////////////////////////////////////////////////////////////////////////
// CNcUiNavDialog
class THUNK_NATIVE_API CNcUiNavDialog : public CNavDialog {
	DECLARE_DYNAMIC(CNcUiNavDialog)

public:
	CNcUiNavDialog (
	    CNavDataArray& dataArray,
	    CNavFilterArray& filterArray,
	    UINT idd=0,
	    CWnd *pParent=NULL,
	    HINSTANCE hDialogResource=NULL
	);
	virtual ~CNcUiNavDialog ();
	virtual BOOL OnInitDialog ();
	virtual BOOL GetRecentDirectory(CString& strRecent);
	virtual BOOL FindInSearchPath(LPCTSTR sBase, CString* pFullPath);
	virtual void GetDefaultBrowserStartURL(CString& strStartPage);
	virtual BOOL LaunchBrowserDialog(CString& strSelectedURL, LPCTSTR strDialogCaption,
	                                 LPCTSTR strOk, LPCTSTR strStartPage);
	virtual void DisplaySearchError(LPCTSTR sBase);
	virtual void OnDoLocate();
	virtual BOOL GetProductName(CString& strProduct);
	virtual BOOL BeginDownloadFiles(CStringArray& strURLs, CDWordArray& dwActionCodes);
	virtual DWORD GetDownloadActionCodes(CString& strURL);
	virtual void OnPaintPreview(LPCTSTR strFullPath, CWnd* previewWnd);
	virtual void OnDialogHelp();
	virtual void OnDialogHelp(LPCTSTR pTag);
	BOOL GetPreviewPresent();
	void SetPreviewPresent(BOOL preview);
	BOOL GetPreviewVisible();
	void SetPreviewVisible(BOOL visible);
	BOOL GetInitialViewButtonChecked();
	void ConvertFlagsToState(int nFlags);
	NcUiOpenNoTemplateFlag GetOpenNoTemplateSelection();
	short GetUpdateThumbnailOverride();
public:
#pragma warning(push)
#pragma warning(disable: 4481)
	virtual void EnableFloatingWindows (BOOL allow); // NRX_OVERRIDE;
	virtual int IsMultiDocumentActivationEnabled(); // NRX_OVERRIDE;
	virtual int EnableMultiDocumentActivation(BOOL bEnable); // NRX_OVERRIDE;
#pragma warning(pop)
protected:
	virtual void OnFolderItemChange();
	virtual void OnFilterChange();
	virtual BOOL OnFileNameOK ();
	virtual void OnFileNameChange ();
	virtual void PrepareOkMenu(CMenu* pMenu);
	virtual void PrepareViewsMenu(CMenu* pMenu);
	virtual void PrepareToolsMenu(CMenu* pMenu);
	virtual void OnURLDownloadSuccess(CString& strURL);
	virtual BOOL GetOptionsState();
	virtual void OnCancel();
	void Do3DDwfOptionsDialog();
	void DoFbxOptionsDialog();
	void InitPreviewState();
protected:
	void OnOpenNoTemplateImperial();
	void OnOpenNoTemplateMetric();
	void OnOpenMenuPartialOpen();
	void OnOpenMenuPartialOpenReadOnly();
	void OnViewsMenuPreview();
	void OnToolsMenuOptions();
	void OnToolsMenuSecurity();
	void OnDestroy();
	void OnUpdateThumbnailCheck();
	DECLARE_MESSAGE_MAP()
private:
	short m_CmdInProgress;
	short m_nUpdateThumbnailOverride;
	BOOL m_bIsOpen;
	BOOL m_bIsSaveAs;
	BOOL m_bIsRecover;
	BOOL m_bPartialOpenAlwaysDisabled;
	BOOL m_bInitialViewButtonPresent;
	BOOL m_bInitialViewButtonChecked;
	BOOL m_bPartialOpenPresent;
	BOOL m_bOptionsPresent;
	BOOL m_bPreviewPresent;
	BOOL m_bPreviewVisible;
	BOOL m_bOpenNoTemplate;
	NcUiOpenNoTemplateFlag m_nOpenNoTemplateSelection;
	CNcUiNavPreviewButton* m_previewButton;
	BOOL m_bIsExport;
	BOOL CanPartiallyOpen(LPCTSTR szfullPath);
	static BOOL m_bOriginalMultiSelAllowed;
};

#endif // _navigation_h
