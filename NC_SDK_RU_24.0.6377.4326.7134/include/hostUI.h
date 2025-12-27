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

#pragma once

#include <afxcontrolbars.h> // MFC support for ribbons and control bars
#include <vector>
#include <map>

#define WM_HOST_KEEP_FOCUS (WM_USER + 0x6D01)

#define MOVEX               0x00001
#define MOVEY               0x00002
#define MOVEXY              0x00003
#define ELASTICX            0x00010
#define ELASTICY            0x00020
#define ELASTICXY           0x00030

#pragma pack (push, 8)
typedef struct _dlgControlTag {
    DWORD       id;
    DWORD       flags;
    DWORD       pct;
} DLGCTLINFO, *PDLGCTLINFO;
#pragma pack (pop)

#ifndef HOST_PALETTE_API
#    ifdef HOST_PALETTE_INTERNAL
#        define HOST_PALETTE_API __declspec(dllexport)
#    else
#        define HOST_PALETTE_API __declspec(dllimport)
#    endif
#endif


class __pos_holder {
public:
  virtual void  SetControlProperty (const PDLGCTLINFO lp,DWORD dwElements){
#ifdef _CSDEBUG_H_
    mAssert(lp);
#endif
    for (DWORD i=0; i < dwElements; i++){
      m_info.push_back(lp[i]);
    }
  }  
  virtual std::vector<DLGCTLINFO>* GetControlProperty(){
    return &m_info;
  }  
protected:
  std::vector<DLGCTLINFO> m_info;
};

// Palette Set Styles
#define PSS_AUTO_ROLLUP                  0x00000002 
#define PSS_PROPERTIES_MENU              0x00000004 
#define PSS_CLOSE_BUTTON                 0x00000008 
#define PSS_EDIT_NAME                    0x00000010 
#define PSS_SNAP                         0x00000020 
#define PSS_SINGLE_PALETTE_TAB           0x00000040 
#define PSS_USE_SINGLE_PALETTE_TAB_NAME  0x00000080 
#define PSS_SINGLE_ROW_HORZ_DOCK         0x00000200 
#define PSS_NOTIFY                       0x00000400 


class hostUiDialogData;
class CMFCAutoHideBar;
class HOST_PALETTE_API hostUiDialog : public CDialog, public __pos_holder {
    DECLARE_DYNAMIC(hostUiDialog);
public:
  hostUiDialog(UINT idd,CWnd *pParent=NULL,HINSTANCE hDialogResource=NULL);
  BOOL  OnInitDialog();
  virtual INT_PTR DoModal();

  virtual ~hostUiDialog();

  void    SetDialogMaxExtents (int width, int height);
  void    SetDialogMinExtents (int width, int height);

  BOOL    SetDialogData (LPCWSTR valueName, LPCWSTR data);
  BOOL    SetDialogData (LPCWSTR valueName, DWORD data);
  BOOL    GetDialogData (LPCWSTR valueName, CString& data);
  BOOL    GetDialogData (LPCWSTR valueName, DWORD& data);
  BOOL    GetDialogKey (CString& strKey);


  void    BeginEditorCommand ();
  void    CancelEditorCommand ();
  void    CompleteEditorCommand (BOOL restoreDialogs=TRUE);
  void    MakeDialogsVisible (BOOL visible);
  void    SetHelpString(LPCWSTR lpHelp);
  BOOL    GetDialogName(CString& name);
  void    SetDialogName(LPCTSTR name);

  BOOL MoveControlX (UINT id, LONG lMovePct);
  BOOL MoveControlXY (UINT id, LONG lMoveXPct, LONG lMoveYPct);
  BOOL MoveControlY (UINT id, LONG lMovePct);
  BOOL StretchControlX (UINT id, LONG lStretchPct);
  BOOL StretchControlXY (UINT id, LONG lStretchXPct, LONG lStretchYPct);
  BOOL StretchControlY (UINT id, LONG lStretchPct);



protected:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  DECLARE_MESSAGE_MAP()
  //{{AFX_MSG(hostUiDialog)
  //}}AFX_MSG

private:
  hostUiDialogData*  m_pData;
  CString            m_helpString;
  bool               m_modal;
public:
  using CWnd::operator new;
  using CWnd::operator delete;
};
#define HostUIDialog hostUiDialog


class hostUiPaletteSet;

class HOST_PALETTE_API hostUiPalette : public CWnd
{
    DECLARE_DYNAMIC(hostUiPalette)

public:
    hostUiPalette();
    virtual ~hostUiPalette();

    // Creates the palette window
    BOOL Create(DWORD dwStyle, LPCTSTR pszName, hostUiPaletteSet* pParent,
                DWORD dwPaletteStyle = 0);

    virtual BOOL Create(hostUiPaletteSet* pParent);

    DWORD GetPaletteStyle();
    void  SetPaletteStyle(DWORD dwStyle);

    BOOL EditNameStyle() { return m_dwStyle & PSS_EDIT_NAME; }

    virtual BOOL Load(IUnknown* pUnk);
    virtual BOOL Save(IUnknown* pUnk);

    hostUiPaletteSet* GetPaletteSet() { return m_pParent; };
    void SetPaletteSet(hostUiPaletteSet* pSet);

    virtual void OnSetActive();
    virtual BOOL OnKillActive();

    CString GetName();
    void SetName(LPCWSTR strName);

    virtual BOOL GetMinimumSize(CSize& size);
    virtual BOOL GetMaximumSize(CSize& size);

    virtual bool CanFrameworkTakeFocus();

protected:
    afx_msg LRESULT OnKeepFocus(WPARAM, LPARAM);

    DECLARE_MESSAGE_MAP()

private:
    CString                 m_sName;
    hostUiPaletteSet *      m_pParent;
    DWORD                   m_dwStyle;
public:
  using CWnd::operator new;
  using CWnd::operator delete;
};

class hostUiPalette;

#define HSTUI_HT_CAPTION                             1 
#define HSTUI_HT_OPTION_BUTTON                       2 
#define HSTUI_HT_ROLLUP_BUTTON                       3 
#define HSTUI_HT_CLOSE_BUTTON                        4 
#define HSTUI_HT_GRIP                                5 
#define HSTUI_HT_TABS                                6 
#define HSTUI_HT_PALETTE                             7 
#define HSTUI_HT_TAB_OVERFLOW                        8 
#define HSTUI_HT_PALETTESET                          9 

class CCSTabWnd;
class uiSmartMenu;
class HOST_PALETTE_API hostUiPaletteSet : public CDockablePane
{
    friend class hostUiPalette;
    friend class CNdUiPaletteSet;
    
    DECLARE_DYNCREATE(hostUiPaletteSet);

public:
    hostUiPaletteSet(int nStyle = 0);
    virtual ~hostUiPaletteSet();

    BOOL Create(LPCTSTR strTitle, DWORD dwStyle, const RECT &rect,
                CWnd *pwndParent,
                DWORD dwPaletteSetStyle = PSS_PROPERTIES_MENU | PSS_AUTO_ROLLUP | PSS_CLOSE_BUTTON | PSS_SNAP);

    DWORD GetPaletteSetStyle();
    void  SetPaletteSetStyle(DWORD dwStyle);

    CString GetName();
    BOOL SetName(LPCWSTR pszName);

    hostUiPalette* GetActivePalette();
    int GetActivePaletteTabIndex();
    BOOL SetActivePalette (hostUiPalette* pPalette);
    BOOL SetActivePalette (int nPaletteIndex);

    int AddPalette(hostUiPalette* pPalette);
    int InsertPalette(int iIndex, hostUiPalette* pPalette);
    BOOL RemovePalette(hostUiPalette* pPalette);
    BOOL RemovePalette(int nPaletteIndex);
    int GetPaletteCount();
    hostUiPalette * GetPalette(int nIndex);
    int GetTabIndex(hostUiPalette* pPalette);

    void GetFullRect(CRect & rect);
    BOOL GetNonClientSize(CSize& size);

    virtual BOOL Load(IUnknown* pUnk);
    virtual BOOL Save(IUnknown* pUnk);

    void UpdateTabs();
    void EnableDocking(DWORD dwDockStyle);

    typedef enum {
        kLeft = 0,
        kRight
    } hostUiTitleBarLocation ;

    void SetToolID (CLSID* pCLSID);
    CLSID* GetToolID () { return &m_ID; }
    void Show(BOOL fShow);

    BOOL SetAutoRollup(BOOL bSet = TRUE);
    BOOL GetAutoRollup();

    virtual BOOL IsVisible() const;
    virtual void AdjustLayout();

    void DockControlBar (UINT nOrientation, RECT *pRect);
    void RestoreControlBar (UINT nPreferredOrientation = AFX_IDW_DOCKBAR_LEFT,
                            CRect *pSizeFloating = NULL);

    virtual bool CanFrameworkTakeFocus();
    void SetAllowDockingMenuItemState(bool bState) { m_bADMenuState = bState; }
    bool AllowDockingMenuItemState() { return m_bADMenuState; }

    BOOL HitTest(CPoint pt, UINT& nFlag, DWORD& dwData);
    virtual BOOL AddContextMenuItems(CMenu * pMenu, int nHitFlag, int nRightClkTab = 0);
    virtual void GetMinimumSize(CSize& size);
    virtual void GetMaximumSize(CSize& size);
    virtual void PaletteAdded(hostUiPalette* pPalette) { return; }
    virtual void PaletteRemoved(hostUiPalette* pPalette) { return; }
    virtual void PaletteActivated(hostUiPalette* pActivated, hostUiPalette* pDeactivated) { return; }
    virtual void AutoRollupChanged(BOOL bAutoRollupIsOn) { return; }
    void GetAdjustedClientRect(CRect & rect);
    virtual void GetMinSize(CSize& size) const;
    virtual bool OnClosing ();
    virtual void ShowPane(BOOL bShow, BOOL bDelay, BOOL bActivate/* = TRUE*/);
    //{{AFX_VIRTUAL(hostUiPaletteSet)
public:
    virtual BOOL PreTranslateMessage(MSG * msg);
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL

    virtual int  GetTopReservedHeight();
    virtual int  GetBottomReservedHeight();

    int GetOpacity() const;
    BOOL SetOpacity(int nOpacity);
    void BringToTop();

protected:
    //{{AFX_MSG(hostUiPaletteSet)
    afx_msg void    OnSize(UINT nType, int cx, int cy);
    virtual void    OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
    afx_msg void    OnPaint();
    afx_msg int     OnCreate(LPCREATESTRUCT lpCs);
    afx_msg void    OnDestroy();
    afx_msg void    OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg LRESULT OnKeepFocus(WPARAM, LPARAM);
    afx_msg void    OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void    OnLButtonDblClk(UINT nFlags, CPoint point);
    //}}AFX_MSG
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()


protected: //BasePane

    virtual BOOL IsResizable() const;
    virtual void OnPressCloseButton();
    virtual void PostNcDestroy();
    virtual BOOL CanBeDocked(CBasePane* /*pDockBar*/) const;
    virtual BOOL CanBeAttached() const;
    virtual BOOL CanBeTabbedDocument() const;
    virtual void OnAfterFloat();
    virtual BOOL OnShowControlBarMenu(CPoint point);
    virtual void OnBeforeChangeParent(CWnd* pWndNewParent, BOOL bDelay = FALSE);
    virtual void RecalcLayout();


    virtual BOOL LoadState(LPCWSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);
    virtual BOOL SaveState(LPCWSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);
    virtual void SetDragMode(BOOL bOnOff);
    virtual BOOL OnBeforeShowPaneMenu(CMenu& menu);
		virtual CMFCAutoHideBar* SetAutoHideMode(BOOL bMode, DWORD dwAlignment, CMFCAutoHideBar* pCurrAutoHideBar = NULL, BOOL bUseTimer = TRUE);
    
private:
    BOOL                    TryCloseChilds();
    int                     AddPaletteInt(hostUiPalette* pPalette,int nIndex);
    std::vector<hostUiPalette*> m_palettes;
    int                     m_nActive;
    CCSTabWnd*              m_tabWnd;
    int                     m_nStyle;
    hostUiTitleBarLocation  m_barlocation;
    CLSID                   m_ID;
    bool                    m_bADMenuState;
    std::map<int,std::map<int,uiSmartMenu*> > m_ctxMenus;
    CString                 m_sPreWindowsName;
    UINT                    m_startPreferredOrientation;
    CRect                   m_startSizeFloating;
    BOOL                    m_stateLoaded;

public:
    using CWnd::operator new;
    using CWnd::operator delete;
    friend CCSTabWnd;
    void onFrameInit(bool forseVisible);
};

class HOST_PALETTE_API hostUiQtPaletteSet: public hostUiPaletteSet
{
public:
    virtual BOOL PreTranslateMessage(MSG* msg) { return FALSE; }
};

////Command UI
#define HST_CMD_CHECKED 2
#define HST_CMD_ENABLED 1
class hostUpdateCmdUIClient{
public:
  virtual DWORD getState() = NULL;
};
//see NRX func ncedAddRemoveCmdUIClient(hostUpdateCmdUIClient*,bool fadd) see ui.h