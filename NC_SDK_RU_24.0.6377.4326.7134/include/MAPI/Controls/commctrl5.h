//////////////////////////////////////////////////////////////////////////////////
// Файл для расширенных контроло из IE50
// Для поддержки в VC60.
// Оригиналы лежат
// "C:\Program Files\Microsoft Visual Studio .NET\Vc7\PlatformSDK\Include\CommCtrl.h"
//

#ifndef COMMCTRL5_H
#define COMMCTRL5_H

//---------------------------------------------------------------------
#if _MFC_VER < 0x0700

#define HDFT_ISSTRING       0x0000      // HD_ITEM.pvFilter points to a HD_TEXTFILTER
#define HDFT_ISNUMBER       0x0001      // HD_ITEM.pvFilter points to a INT

#define HDFT_HASNOVALUE     0x8000      // clear the filter, by setting this bit

//---------------------------------------------------------------------
#ifdef UNICODE
#define HD_TEXTFILTER HD_TEXTFILTERW
#define HDTEXTFILTER HD_TEXTFILTERW
#define LPHD_TEXTFILTER LPHD_TEXTFILTERW
#define LPHDTEXTFILTER LPHD_TEXTFILTERW
#else
#define HD_TEXTFILTER HD_TEXTFILTERA
#define HDTEXTFILTER HD_TEXTFILTERA
#define LPHD_TEXTFILTER LPHD_TEXTFILTERA
#define LPHDTEXTFILTER LPHD_TEXTFILTERA
#endif
//---------------------------------------------------------------------

typedef struct _HD_TEXTFILTERA
{
    LPSTR pszText;                      // [in] pointer to the buffer containing the filter (ANSI)
    INT cchTextMax;                     // [in] max size of buffer/edit control buffer
} HD_TEXTFILTERA, *LPHD_TEXTFILTERA;

typedef struct _HD_TEXTFILTERW
{
    LPWSTR pszText;                     // [in] pointer to the buffer contiaining the filter (UNICODE)
    INT cchTextMax;                     // [in] max size of buffer/edit control buffer
} HD_TEXTFILTERW, *LPHD_TEXTFILTERW;

#define HDI_FILTER              0x0100

#define HD_ITEMA HDITEMA
#define HD_ITEMW HDITEMW
#define HD_ITEM	 HDITEM


//---------------------------------------------------------------------
#ifdef UNICODE
#define HDITEM2	 _HD_ITEMW2
#else 
#define HDITEM2	 _HD_ITEMA2
#endif
//---------------------------------------------------------------------

typedef struct _HD_ITEMA2
{
    UINT    mask;
    int     cxy;
    LPSTR   pszText;
    HBITMAP hbm;
    int     cchTextMax;
    int     fmt;
    LPARAM  lParam;
    int     iImage;        // index of bitmap in ImageList
    int     iOrder;        // where to draw this item
	UINT    type;           // [in] filter type (defined what pvFilter is a pointer to)
	void *  pvFilter;       // [in] fillter data see above
} HDITEMA2, *LPHDITEMA2;

#define HDITEMA_V1_SIZE CCSIZEOF_STRUCT(HDITEMA, lParam)
#define HDITEMW_V1_SIZE CCSIZEOF_STRUCT(HDITEMW, lParam)

typedef struct _HD_ITEMW2
{
    UINT    mask;
    int     cxy;
    LPWSTR   pszText;
    HBITMAP hbm;
    int     cchTextMax;
    int     fmt;
    LPARAM  lParam;
    int     iImage;        // index of bitmap in ImageList
    int     iOrder;
    UINT    type;           // [in] filter type (defined what pvFilter is a pointer to)
    void *  pvFilter;       // [in] fillter data see above
} HDITEMW2, *LPHDITEMW2;

//---------------------------------------------------------------------
#ifdef UNICODE
#define HDITEM HDITEMW
#define LPHDITEM LPHDITEMW
#define HDITEM_V1_SIZE HDITEMW_V1_SIZE
#else
#define HDITEM HDITEMA
#define LPHDITEM LPHDITEMA
#define HDITEM_V1_SIZE HDITEMA_V1_SIZE
#endif
//---------------------------------------------------------------------

#define HDS_FILTERBAR           0x0100

#define HDM_SETFILTERCHANGETIMEOUT  (HDM_FIRST+22)
#define Header_SetFilterChangeTimeout(hwnd, i) \
        (int)SNDMSG((hwnd), HDM_SETFILTERCHANGETIMEOUT, 0, (LPARAM)(i))

#define HDM_EDITFILTER          (HDM_FIRST+23)
#define Header_EditFilter(hwnd, i, fDiscardChanges) \
        (int)SNDMSG((hwnd), HDM_EDITFILTER, (WPARAM)(i), MAKELPARAM(fDiscardChanges, 0))

// Clear filter takes -1 as a column value to indicate that all
// the filter should be cleared.  When this happens you will
// only receive a single filter changed notification.

#define HDM_CLEARFILTER         (HDM_FIRST+24)
#define Header_ClearFilter(hwnd, i) \
        (int)SNDMSG((hwnd), HDM_CLEARFILTER, (WPARAM)(i), 0)
#define Header_ClearAllFilters(hwnd) \
        (int)SNDMSG((hwnd), HDM_CLEARFILTER, (WPARAM)-1, 0)

#define HHT_ONFILTER            0x0010
#define HHT_ONFILTERBUTTON      0x0020

#define HDN_FILTERCHANGE        (HDN_FIRST-12)
#define HDN_FILTERBTNCLICK      (HDN_FIRST-13)

typedef struct tagNMHDFILTERBTNCLICK
{
    NMHDR hdr;
    INT iItem;
    RECT rc;
} NMHDFILTERBTNCLICK, *LPNMHDFILTERBTNCLICK;

//---------------------------------------------------------------------
#else 
#define HDITEM2 HDITEM
#endif
//---------------------------------------------------------------------

#include "shlwapi.h"
inline DWORD GetComCtlVersion()
{
	DLLGETVERSIONPROC	pfDGV = NULL;
	HINSTANCE			hInst = ::GetModuleHandle(_T("COMCTL32.DLL"));
	DWORD				dwVersion = 0;
	
	pfDGV = (DLLGETVERSIONPROC)GetProcAddress( hInst,"DllGetVersion");
	if( pfDGV ) 
	{
		DLLVERSIONINFO	dviVer;
		HRESULT			hResult = E_FAIL;
		ZeroMemory( &dviVer, sizeof( DLLVERSIONINFO ) );
		dviVer.cbSize = sizeof( DLLVERSIONINFO );		
		hResult = pfDGV( &dviVer );
		if( SUCCEEDED(hResult))
		{
			if((dviVer.dwMajorVersion<=0xFFFF) &&		
					(dviVer.dwMinorVersion<=0xFFFF))	// If Seems Valid
			{
				dwVersion = MAKELONG( dviVer.dwMajorVersion,
						dviVer.dwMinorVersion );			// Convert Version Numbers To DWORD
			}
		}
	}
	return( dwVersion );	// Return Version Information
}

#endif
//---------------------------------------------------------------------
//---------------------------------------------------------------------
