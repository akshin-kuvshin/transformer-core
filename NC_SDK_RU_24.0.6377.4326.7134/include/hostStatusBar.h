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
#pragma pack (push, 8)

#ifndef SB_NATIVE_API
#    ifdef SB_INTERNAL
#        define SB_NATIVE_API __declspec(dllexport)
#    else
#        define SB_NATIVE_API __declspec(dllimport)
#    endif
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// NcStatusBarItem
class SB_NATIVE_API NcStatusBarItem
{
public:
  NcStatusBarItem();
  virtual ~NcStatusBarItem();

  virtual BOOL SetIcon(HICON hIcon);
  virtual HICON GetIcon() const;

  virtual BOOL SetToolTipText(const CString& strText);
  virtual BOOL GetToolTipText(CString& strText) const;

  virtual BOOL QueryToolTipText(CString& strText) const;

  virtual void Enable(BOOL bValue);
  virtual BOOL IsEnabled();

  virtual void SetVisible(BOOL bIsVisible);
  virtual BOOL IsVisible();

  virtual void OnLButtonDown(UINT nFlags, CPoint point);
  virtual void OnRButtonDown(UINT nFlags, CPoint point);
  virtual void OnLButtonDblClk(UINT nFlags, CPoint point);

  virtual void OnDelete();

  virtual BOOL ClientToScreen(LPPOINT lpPoint);
  virtual BOOL ClientToScreen(LPRECT lpRect);

  virtual BOOL ScreenToClient(LPPOINT lpPoint);
  virtual BOOL ScreenToClient(LPRECT lpRect);

  virtual UINT DisplayContextMenu(CMenu& menu, CPoint point);

  virtual BOOL ShowTraySettingsDialog();

  virtual void SetContentChanged(BOOL bChanged) {m_bContentChanged = bChanged;}
  virtual BOOL ContentChanged() const {return m_bContentChanged;}

  virtual void SetVisibilityChanged(BOOL bChanged) {m_bVisibilityChanged = bChanged;}
  virtual BOOL VisibilityChanged() const {return m_bVisibilityChanged;}   

  int GetID() const;
  void SetID(int id);

  CString& GetActiveImageState() const;
  void SetActiveImageState(const CString& strActiveImageState);

  virtual void SetInternalData(void* pData, BOOL bForDocSwitch = FALSE);
  virtual void* GetInternalData(BOOL bForDocSwitch = TRUE) const;

protected:
  CString         m_strToolTipText;
  HICON           m_hIcon;
  BOOL            m_bEnabled;
  BOOL            m_bVisible;
  BOOL            m_bContentChanged;
  BOOL            m_bVisibilityChanged;
  int             n_nId;
  void*           m_pDocData;
};

//////////////////////////////////////////////////////////////////////////
// NcStatusBarMenuItem
class SB_NATIVE_API NcStatusBarMenuItem {
public:
  enum NcStatusBarType {
    kApplicationStatusBar  = 0,
    kDrawingStatusBar = 1
  };
  NcStatusBarMenuItem();
  virtual ~NcStatusBarMenuItem();
  virtual BOOL    CustomizeMenu       (NcStatusBarType nType,
    CMenu* pMenu,
    UINT nStartCmdId,
    UINT nEndCmdId);
  virtual BOOL    InvokeMenuCommand   (NcStatusBarType nType,
    UINT nCmdId);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcPane

#define NCSB_NOBORDERS  (1 << 0)
#define NCSB_POPOUT     (1 << 1)
#define NCSB_STRETCH    (1 << 2)
#define NCSB_NORMAL     (1 << 3)
#define NCSB_COMMAND    (1 << 4)
#define NCSB_POPUP      (1 << 5)

class SB_NATIVE_API NcPane : public NcStatusBarItem
{
public:
  NcPane();
  virtual ~NcPane();

  virtual BOOL SetIcon(HICON hIcon);
  virtual HICON GetIcon() const;

  virtual BOOL SetToolTipText(const CString& strText);
  virtual BOOL GetToolTipText(CString& strText) const;

  virtual void SetVisible(BOOL bIsVisible);
  virtual BOOL IsVisible();

  virtual BOOL SetText(const CString& text);
  virtual BOOL GetText(CString& text) const;

  virtual BOOL SetStyle(int style);
  virtual int GetStyle() const;

  virtual BOOL SetMinWidth(int width);
  virtual int GetMinWidth();

  virtual BOOL SetMaxWidth(int width);
  virtual int GetMaxWidth();

  virtual UINT DisplayPopupPaneMenu(CMenu& menu);

  virtual BOOL SetPaneName(const CString& strName);
  virtual BOOL GetPaneName(CString& strName) const;

  virtual BOOL SetRegistryKey(const CString& strRegistryKey);
  virtual BOOL GetRegistryKey(CString& strRegistryKey) const;

protected:
  CString m_strText;
  int     m_nStyle;
  int     m_cxMinWidth;
  int     m_cxMaxWidth;
  CString m_strName;
  CString m_strRegistryKey;
};

typedef void (*NcTrayItemAnimationCallbackFunc)(void*, int);
typedef void* NcTrayItemAnimationCallbackData;

class SB_NATIVE_API NcTrayItemAnimationControl
{
public:
  NcTrayItemAnimationControl();
  NcTrayItemAnimationControl(const CString& strGIFFile);
  NcTrayItemAnimationControl(HBITMAP hBitmap);
  ~NcTrayItemAnimationControl();

  void SetBitmap(HBITMAP hBitmap)
  {
    m_hBitmap = hBitmap;
  }
  void SetGIFFile(const CString& strGIFFile)
  {
    m_strGIFFile = strGIFFile;
  }
  void SetGIFResourceData(HGLOBAL hGlobal, DWORD dwSize)
  {
    m_hGifGlobal = hGlobal;
    m_dwGifSize  = dwSize;
  };
  void SetDuration(int nDurationInSeconds)
  {
    m_nDurationInSeconds = nDurationInSeconds;
  }
  void SetNewIcon(HICON hNewIcon)
  {
    m_hNewIcon = hNewIcon;
  }
  void SetCallback(NcTrayItemAnimationCallbackFunc pCallbackFunc, NcTrayItemAnimationCallbackData pCallbackData)
  {
    m_pCallbackFunc = pCallbackFunc;
    m_pCallbackData = pCallbackData;
  }

  HBITMAP GetBitmap() const
  {
    return m_hBitmap;
  };
  const CString& GetGIFFile() const
  {
    return m_strGIFFile;
  };
  void GetGIFResourceData(HGLOBAL& hGlobal, DWORD& dwSize) const
  {
    hGlobal = m_hGifGlobal;
    dwSize  = m_dwGifSize;
  };
  int GetDuration() const
  {
    return m_nDurationInSeconds;
  }
  HICON GetNewIcon() const
  {
    return m_hNewIcon;
  };
  NcTrayItemAnimationCallbackFunc GetCallbackFunc() const
  {
    return m_pCallbackFunc;
  }
  NcTrayItemAnimationCallbackData GetCallbackData() const
  {
    return m_pCallbackData;
  }

  enum
  {
    ANIMATION_ERROR_NO_CREATE,
    ANIMATION_ERROR_NO_ICONS,
    ANIMATION_KILLED,
    ANIMATION_FINISHED,
  };

protected:
  void InitDefault()
  {
    m_pCallbackFunc      = 0;
    m_pCallbackData      = 0;
    m_nDurationInSeconds = 5;
    m_hNewIcon           = 0;
  }

  HBITMAP                         m_hBitmap;
  HGLOBAL                         m_hGifGlobal;
  DWORD                           m_dwGifSize;
  CString                         m_strGIFFile;
  int                             m_nDurationInSeconds;
  HICON                           m_hNewIcon;
  NcTrayItemAnimationCallbackFunc m_pCallbackFunc;
  NcTrayItemAnimationCallbackData m_pCallbackData;
};

typedef void (*NcTrayItemBubbleWindowCallbackFunc)(void*, int);
typedef void* NcTrayItemBubbleWindowCallbackData;

class SB_NATIVE_API NcTrayItemBubbleWindowControl
{
public:
  NcTrayItemBubbleWindowControl();
  NcTrayItemBubbleWindowControl(const CString& title, const CString& text, const CString& hyper_text = _T(""),
    const CString& hyper_link = _T(""), const CString& text2 = _T(""));

  ~NcTrayItemBubbleWindowControl();

  void SetIconType(int nIconType)
  {
    m_nIconType = nIconType;
  }
  void SetTitle(const CString& strTitle)
  {
    m_strTitle = strTitle;
  }
  void SetText(const CString& strText)
  {
    m_strText = strText;
  }
  void SetHyperText(const CString& strHyperText)
  {
    m_strHyperText = strHyperText;
  }
  void SetHyperLink(const CString& strHyperLink)
  {
    m_strHyperLink = strHyperLink;
  }
  void SetText2(const CString& strText2)
  {
    m_strText2 = strText2;
  }
  void SetCallback(NcTrayItemBubbleWindowCallbackFunc pCallbackFunc,
    NcTrayItemBubbleWindowCallbackData pCallbackData = 0)
  {
    m_pCallbackFunc = pCallbackFunc;
    m_pCallbackData = pCallbackData;
  }

  int GetIconType() const
  {
    return m_nIconType;
  };
  const CString& GetTitle() const
  {
    return m_strTitle;
  }
  const CString& GetText() const
  {
    return m_strText;
  }
  const CString& GetHyperText() const
  {
    return m_strHyperText;
  }
  const CString& GetHyperLink() const
  {
    return m_strHyperLink;
  }
  const CString& GetText2() const
  {
    return m_strText2;
  }
  NcTrayItemBubbleWindowCallbackFunc GetCallbackFunc() const
  {
    return m_pCallbackFunc;
  }
  NcTrayItemBubbleWindowCallbackData GetCallbackData() const
  {
    return m_pCallbackData;
  }

  enum
  {
    BUBBLE_WINDOW_ICON_NONE,
    BUBBLE_WINDOW_ICON_INFORMATION,
    BUBBLE_WINDOW_ICON_CRITICAL,
    BUBBLE_WINDOW_ICON_WARNING,
  };

  enum
  {
    BUBBLE_WINDOW_ERROR_NO_CREATE,
    BUBBLE_WINDOW_ERROR_NO_ICONS,
    BUBBLE_WINDOW_ERROR_NO_NOTIFICATIONS,
    BUBBLE_WINDOW_CLOSE,
    BUBBLE_WINDOW_TIME_OUT,
    BUBBLE_WINDOW_HYPERLINK_CLICK,
    BUBBLE_WINDOW_DOCUMENT_DEACTIVATED
  };

protected:
  void InitDefault()
  {
    m_pCallbackFunc = 0;
    m_pCallbackData = 0;
    m_nIconType     = BUBBLE_WINDOW_ICON_INFORMATION;
  }

  int                                m_nIconType;
  CString                            m_strTitle;
  CString                            m_strText;
  CString                            m_strHyperText;
  CString                            m_strHyperLink;
  CString                            m_strText2;
  NcTrayItemBubbleWindowCallbackFunc m_pCallbackFunc;
  NcTrayItemBubbleWindowCallbackData m_pCallbackData;
};

class SB_NATIVE_API NcTrayItem : public NcStatusBarItem
{
public:
  NcTrayItem();
  virtual ~NcTrayItem();

  virtual BOOL SetIcon(HICON hIcon);
  virtual HICON GetIcon() const;

  virtual BOOL ShowBubbleWindow(NcTrayItemBubbleWindowControl* pBubbleWindowControl);
  virtual NcTrayItemBubbleWindowControl* GetBubbleWindowControl() const;

  virtual BOOL CloseAllBubbleWindows();

  BOOL PlayAnimation(NcTrayItemAnimationControl* pAnimationControl);
  void StopAnimation();
  NcTrayItemAnimationControl* GetAnimationControl() const;

protected:
  NcTrayItemAnimationControl     m_AnimationControl;
  NcTrayItemAnimationControl*    m_pAnimationControl;

  NcTrayItemBubbleWindowControl  m_BubbleWindowControl;
  NcTrayItemBubbleWindowControl* m_pBubbleWindowControl;
};

enum NcDefaultPane
{
  NCSBPANE_APP_MODEMACRO,
  NCSBPANE_APP_CURSORCOORD,
  NCSBPANE_APP_SNAP,
  NCSBPANE_APP_GRID,
  NCSBPANE_APP_ORTHO,
  NCSBPANE_APP_POLAR,
  NCSBPANE_APP_OTRACK,
  NCSBPANE_APP_LINEWEIGHT,
  NCSBPANE_APP_PAPERMODEL,
  NCSBPANE_APP_PAPER,
  NCSBPANE_APP_MODEL,
  NCSBPANE_APP_OSNAP,
  NCSBPANE_APP_FLOAT,
  NCSBPANE_APP_TABLET,
  NCSBPANE_APP_SPACER,
  NCSBPANE_APP_VPMAX_PREV,
  NCSBPANE_APP_VPMAX,
  NCSBPANE_APP_VPMAX_NEXT,
  NCSBPANE_APP_DYNINPUT,
  NCSBPANE_APP_DYNAMICUCS,
  NCSBPANE_APP_LAYOUTMODELICONS,
  NCSBPANE_APP_MODEL_ICON,
  NCSBPANE_APP_LAYOUT_ICON,
  NCSBPANE_APP_LAYOUTMORE_ICON,
  NCSBPANE_APP_ALL,
};


class NcApStatusBar
{
public:
  virtual BOOL Insert(int nIndex, NcPane* pPane, BOOL bUpdate = TRUE) = 0;
  virtual BOOL Insert(int nIndex, NcTrayItem* pTrayItem, BOOL bUpdate = TRUE) = 0;

  virtual BOOL Remove(NcPane* pPane, BOOL bUpdate = TRUE) = 0;
  virtual BOOL Remove(NcTrayItem* pTrayItem, BOOL bUpdate = TRUE) = 0;
  virtual BOOL Remove(int nIndex, BOOL bTrayItem = FALSE, BOOL bUpdate = TRUE) = 0;

  virtual BOOL RemoveAllPanes(BOOL bUpdate = TRUE) = 0;

  virtual int Add(NcPane* pPane, BOOL bUpdate = TRUE) = 0;
  virtual int Add(NcTrayItem* pTrayItem, BOOL bUpdate = TRUE) = 0;

  virtual void Update() = 0;

  virtual int GetIndex(NcPane* pPane) const = 0;
  virtual int GetIndex(NcTrayItem* pTrayItem) const = 0;
  virtual int GetIndex(int nID, BOOL bTrayItem = FALSE) const = 0;

  virtual int GetID(NcPane* pPane) const = 0;
  virtual int GetID(NcTrayItem* pTrayItem) const = 0;
  virtual int GetID(int nIndex, BOOL bTrayItem = FALSE) const = 0;

  virtual int GetPaneCount() const = 0;

  virtual NcPane* GetPane(int nIndex) = 0;

  virtual int GetTrayItemCount() const = 0;

  virtual NcTrayItem* GetTrayItem(int nIndex) = 0;

  virtual BOOL RemoveAllTrayIcons(BOOL bUpdate = TRUE) = 0;

  virtual BOOL ClientToScreen(LPPOINT lpPoint) = 0;
  virtual BOOL ClientToScreen(LPRECT lpRect) = 0;

  virtual BOOL ScreenToClient(LPPOINT lpPoint) = 0;
  virtual BOOL ScreenToClient(LPRECT lpRect) = 0;

  virtual int GetTextWidth(const CString& strText) const = 0;

  virtual UINT DisplayContextMenu(CMenu& menu, CPoint point) = 0;
  virtual UINT DisplayPopupPaneMenu(NcPane* pPane, CMenu& menu) = 0;

  virtual BOOL GetTraySettingsShowIcons() const = 0;
  virtual BOOL GetTraySettingsShowNotifications() const = 0;

  virtual void ShowStatusBarMenuIcon(BOOL bShow) = 0;

  virtual BOOL SetStatusBarMenuItem(NcPane* pPane) = 0;

  virtual void ShowCleanScreenIcon(BOOL bShow) = 0;
  virtual BOOL RemoveCleanScreenIcon() = 0;

  virtual BOOL ShowTraySettingsDialog() = 0;

  virtual NcPane* GetDefaultPane(NcDefaultPane nPane) = 0;
  virtual BOOL RemoveDefaultPane(NcDefaultPane nPane, BOOL bUpdate = TRUE) = 0;

  virtual BOOL CloseAllBubbleWindows(NcTrayItem* pTrayItem) = 0;
  
  virtual BOOL ShowBubbleWindow(NcTrayItem* pTrayItem) = 0;
  
  virtual BOOL PlayAnimation(NcTrayItem* pTrayItem) = 0;
  virtual void StopAnimation(NcTrayItem* pTrayItem) = 0; 

  virtual void updatePosition() = 0; 
};

SB_NATIVE_API NcApStatusBar* ncedGetApplicationStatusBar();
SB_NATIVE_API BOOL ncedSetStatusBarPaneID(NcPane* pPane,NcStatusBarMenuItem::NcStatusBarType nType,int nID);
SB_NATIVE_API BOOL ncedUnregisterStatusBarMenuItem(NcStatusBarMenuItem* pItem,NcStatusBarMenuItem::NcStatusBarType nType);
