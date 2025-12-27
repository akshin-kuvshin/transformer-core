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

#include "mcstypes.h"

//=============================================================================
IMCS_DECL_INTERFACE(mtMemImage24, "1F000001-0002-FEDA-1979-200502021024");
IMCS_DECL_INTERFACE(mtDIB,        "1F000002-0002-FEDA-1979-200502021024");

struct mtDIB : public virtual IMcObject
{
  HBITMAP    m_hBmp;
  BITMAPINFO m_BI;
  DWORD      m_W,m_H;
  DWORD      m_dwBPL; // bytes per line
  DWORD      m_dwLineRem; // bytes of reminder for each line
  LPBYTE     m_pData;

  DECLARE_OBJ_NEWDEL;
  IMCS_STD_METHOD_DEFINITION(mtDIB, IMcObject);
  MT_API mtDIB();
  MT_API virtual ~mtDIB();
  MT_API void     Reset(bool fDeleteBitmap=true);
  MT_API HRESULT  Create(HWND hWndCtrl);
  MT_API HRESULT  Create(DWORD w, DWORD h);
  MT_API HRESULT  CopyData(const mtMemImage24& imageFrom);
  MT_API HRESULT  GetCopy(OUT mtDIBPtr& pCopiedDIB);
  MT_API HRESULT  GetCompressed(IN UINT k, OUT mtDIBPtr& pComprDIB);
	MT_API COLORREF GetPixel(UINT row, UINT col);
	MT_API HRESULT  SetPixel(UINT row, UINT col, COLORREF color);
};
//=============================================================================
struct mtMemImage24 : public virtual IMcObject
{
  DWORD  m_W, m_H;
  DWORD  m_dwBPL;
  DWORD  m_size;
  LPBYTE m_pData;
  bool   m_fNeedDestroy;

  DECLARE_OBJ_NEWDEL;
  IMCS_STD_METHOD_DEFINITION(mtMemImage24,IMcObject);
  MT_API mtMemImage24();
  MT_API virtual ~mtMemImage24();

  MT_API void Reset();
  MT_API HRESULT Create(const mtDIB& dib);
  MT_API HRESULT Create(DWORD w, DWORD h);
  MT_API HRESULT LinkToBuffer(LPBYTE pData,DWORD w, DWORD h); // link existing buffer
  MT_API HRESULT CopyData(const mtDIB& dibFrom);
  MT_API HRESULT GetCopy(OUT mtMemImage24Ptr& pCopy);
  MT_API HRESULT AlphaBlend
		(const mtMemImage24& img,
		DWORD iDestLeft, DWORD iDestTop, DWORD w, DWORD h,
		DWORD iInputLeft, DWORD iInputTop,
		double kThis,double kInput);
  MT_API HRESULT SetPixel(int row, int col, COLORREF color);
};
//=============================================================================
