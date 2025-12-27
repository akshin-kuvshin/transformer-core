
#pragma once

class CInPlaceEdit
{
public:
	DECLARE_OBJ_NEWDEL;

	CInPlaceEdit(HWND hwndParent, RECT& rect, DWORD dwStyle, UINT nID,
                 int nRow, int nColumn, LPCWSTR psInitText, UINT nFirstChar);

	virtual ~CInPlaceEdit();

protected:
	static int __stdcall _WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	int OnChange();
	void EndEdit();

public:
	HWND    m_hWnd;

protected:
    int     m_nRow;
    int     m_nColumn;
    McsStringW m_sInitText;
    UINT    m_nLastChar;
    BOOL    m_bExitOnArrows;
    RECT    m_Rect;
	WNDPROC m_lpPrevWndFunc;
	UINT_PTR m_dwUserData;
};
 
