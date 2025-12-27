#pragma once
#include "CxEditLt.h"
#include "CxImage.h"

class CxStatic : public CStatic 
{
public :
	CxStatic(BOOL _isWithLine = FALSE) : m_isWithLine(_isWithLine),CStatic() { }
	virtual ~CxStatic(){}
	
	BOOL IsStaticWithLine() const  { return m_isWithLine;}
 
	BOOL m_isWithLine;
protected :
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

class CArrStatic : public CxStatic
{
	public :
		CArrStatic( BOOL _isWithLine = TRUE): 
		   CxStatic(_isWithLine) { }
	private:
		CxEditLt * m_ptrCxEditLt; 
	protected :
	afx_msg void OnPaint();
	
	DECLARE_MESSAGE_MAP()
};

class MECHCTL_API CxMFCImage : public CWnd , public CxImage
{
public :
	
	CxMFCImage() : CWnd () ,CxImage() ,m_bmp(NULL) { } 
	virtual ~CxMFCImage() { if (m_bmp) DeleteObject(m_bmp); } 
	
	HBITMAP getHBMP(long BkGrnd = 0,BOOL ReDraw = FALSE,int cx = -1, int cy = -1) 
	{ 
// 		if (ReDraw)
// 		{
			DeleteObject(m_bmp);
			m_bmp = CxImage::getHBMP(BkGrnd,cx,cy);
	// 	}
		
//		if (NULL==m_bmp)
//			m_bmp = CxImage::getHBMP(BkGrnd,cx,cy);
		
		return m_bmp;
	}
	
	BOOL Create(const RECT& rect , CWnd* pParentWnd, UINT nID, DWORD dwStyle);
	afx_msg void OnPaint();
		
	DECLARE_MESSAGE_MAP()

private :
	HBITMAP m_bmp;
};


class CxRazmer :public CWnd
{
	public:
		CxRazmer() {};
	
	BOOL Create( CWnd* pParentWnd, UINT nID, DWORD dwStyle);
	
	//afx_msg void OnPaint();
	
	DECLARE_MESSAGE_MAP()
};

