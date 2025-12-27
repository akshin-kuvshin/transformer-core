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

#ifndef HOST_OPM_API
#    ifdef HOST_OPM_INTERNAL
#        define HOST_OPM_API __declspec(dllexport)
#    else
#        define HOST_OPM_API __declspec(dllimport)
#    endif
#endif

#include "hostOPMdef.h"
#include "OdaX.h"


//*************************************************************************************************
// Property map methods
//*************************************************************************************************
HOST_OPM_API HRESULT OpmGetCategoryName(IUnknown* pUnk, HINSTANCE hResInstance, CATEGORY_VECTOR & arr, PROPCAT propcat, LCID lcid, BSTR* pbstrName);
HOST_OPM_API HRESULT OpmGetParentCategory(IUnknown *pUnk, CATEGORY_VECTOR & arr, PROPCAT propcat, PROPCAT *pParentCatID);
HOST_OPM_API HRESULT OpmGetCategoryWeight(IUnknown *pUnk, CATEGORY_VECTOR & arr, PROPCAT propcat, long *pCategoryWeight);
HOST_OPM_API HRESULT OpmGetCategoryDescription(IUnknown *pUnk, HINSTANCE hResInstance, CATEGORY_VECTOR & arr, PROPCAT propcat, LCID lcid, BSTR* pbstrDesc);
HOST_OPM_API HRESULT OpmGetPropertyWeight(IUnknown *pUnk, PROP_DISP_VECTOR & arr, VARIANT Id, long *pPropertyWeight);
HOST_OPM_API HRESULT OpmIsPropFullView(IUnknown *pUnk, PROP_DISP_VECTOR & arr, VARIANT Id, VARIANT_BOOL *pbVisible, DWORD *pIntegralHeight);
HOST_OPM_API HRESULT OpmGetPropTextColor(IUnknown *pUnk, PROP_DISP_VECTOR & arr, VARIANT Id, OLE_COLOR *pTextColor);
HOST_OPM_API HRESULT OpmGetPropertyIcon(IUnknown *pUnk, HINSTANCE hResInstance, PROP_DISP_VECTOR & arr, VARIANT Id, IUnknown **ppIcon);
HOST_OPM_API HRESULT OpmGetCustomPropertyCtrl(IUnknown *pUnk, PROP_DISP_VECTOR & arr, VARIANT Id, LCID lcid, BSTR *psProdId);

// IAcPiPropCommandButtons methods
HOST_OPM_API HRESULT OpmGetCommandButtons(IUnknown *pUnk, HINSTANCE hResInstance, CMDBTN_VECTOR & arr, VARIANT *pCmdBtns);


//*************************************************************************************************
// IOPMPropertyExpanderHostImpl: default implementation of interfaces:
// - IOPMPropertyExpander
//*************************************************************************************************
template<class T>
class ATL_NO_VTABLE IOPMPropertyExpanderHostImpl : public IOPMPropertyExpander
{
  public:
    typedef IOPMPropertyExpanderHostImpl<T> t_basePropertyExpanderHostImpl;
    IOPMPropertyExpanderHostImpl()
    {
    }

    virtual ~IOPMPropertyExpanderHostImpl()
    {
    }

    // IOPMPropertyExpander
    STDMETHODIMP GetElementValue(/* [in] */ DISPID dispID, /* [in] */ DWORD dwCookie, /* [out] */ VARIANT *pVarOut)
    {
      return E_FAIL;
    }

    STDMETHODIMP SetElementValue(/* [in] */ DISPID dispID, /* [in] */ DWORD dwCookie, /* [in] */ VARIANT VarIn)
    {
      return E_FAIL;
    }

    STDMETHODIMP GetElementStrings(/* [in] */  DISPID dispID, /* [out] */ CALPOLESTR *pCaStringsOut, /* [out] */ CADWORD *pCaCookiesOut)
    {
      for (ODA_OPMPROPMAP_ENTRY* pMap = T::GetOPMPropertyMap(); !PropertyMapEnd(*pMap); pMap++)
      {
        if (dispID == pMap->dispid && pMap->nElementStrID)
        {
          CString strElements;
          if (!strElements.LoadString(This_GetInstanceHandle(), pMap->nElementStrID))
            return FALSE;
          int count = 0;
          int curPos;
          for (curPos = 0; curPos < strElements.GetLength(); count++) 
            CString str = strElements.Tokenize(_T(";"), curPos);
          CXArray<CADWORD, DWORD> Cookies(count);
          CXArray<CALPOLESTR, LPOLESTR, OLESTR_SYSALLOC> Strings(count);
          curPos = 0;
          for (int i = 0; i < count; i++)
          {
            Cookies[i] = i;
            Strings[i] = CT2W(strElements.Tokenize(_T(";"), curPos));
          }
          Cookies.Detach(pCaCookiesOut);
          Strings.Detach(pCaStringsOut);
          return S_OK;
        }
      }
      return E_FAIL;
    }

    STDMETHODIMP GetElementGrouping(/* [in] */ DISPID dispID, /* [out] */ short *groupingNumber)
    {
      return E_FAIL;
    }

    STDMETHODIMP GetGroupCount(/* [in] */ DISPID dispID, /* [out] */ long *nGroupCnt)
    {
      return E_FAIL;
    }
};


//*************************************************************************************************
// IOPMPropertyExpanderExHostImpl: default implementation of interfaces:
// - IOPMPropertyExpanderEx
//*************************************************************************************************
template<class T>
class ATL_NO_VTABLE IOPMPropertyExpanderExHostImpl : public IOPMPropertyExpanderEx
{
  public:
    typedef IOPMPropertyExpanderExHostImpl<T> t_basePropertyExpanderExHostImpl;
    IOPMPropertyExpanderExHostImpl()
    {
    }

    virtual ~IOPMPropertyExpanderExHostImpl()
    {
    }

    // IOPMPropertyExpander
    STDMETHODIMP GetElementValue(/* [in] */ DISPID dispID, /* [in] */ DWORD dwCookie, /* [out] */ VARIANT *pVarOut)
    {
      return E_FAIL;
    }

    STDMETHODIMP SetElementValue(/* [in] */ DISPID dispID, /* [in] */ DWORD dwCookie, /* [in] */ VARIANT VarIn)
    {
      return E_FAIL;
    }

    STDMETHODIMP GetElementStrings(/* [in] */  DISPID dispID, /* [out] */ CALPOLESTR *pCaStringsOut, /* [out] */ CADWORD *pCaCookiesOut)
    {
      for (ODA_OPMPROPMAP_ENTRY* pMap = T::GetOPMPropertyMap(); !PropertyMapEnd(*pMap); pMap++)
      {
        if (dispID == pMap->dispid && pMap->nElementStrID)
        {
          CString strElements;
          if (!strElements.LoadString(This_GetInstanceHandle(), pMap->nElementStrID))
            return FALSE;
          int count = 0;
          for (int curPos= 0; curPos < strElements.GetLength(); count++) 
            CString str = strElements.Tokenize(_T(";"), curPos);
          CXArray<CADWORD, DWORD> Cookies(count);
          CXArray<CALPOLESTR, LPOLESTR, OLESTR_SYSALLOC> Strings(count);
          curPos = 0;
          for (int i = 0; i < count; i++)
          {
            Cookies[i] = i;
            Strings[i] = CT2W(strElements.Tokenize(_T(";"), curPos));
          }
          Cookies.Detach(pCaCookiesOut);
          Strings.Detach(pCaStringsOut);
          return S_OK;
        }
      }
      return E_FAIL;
    }

    STDMETHODIMP GetElementGrouping(/* [in] */ DISPID dispID, /* [out] */ short *groupingNumber)
    {
      return E_FAIL;
    }

    STDMETHODIMP GetGroupCount(/* [in] */ DISPID dispID, /* [out] */ long *nGroupCnt)
    {
      return E_FAIL;
    }

    STDMETHODIMP GetElementBitmap(/*[in]*/DISPID dispID, /*[in]*/DWORD dwCookie, /*[out]*/IPicture** pPicture)
    {
      return E_FAIL;
    }
    STDMETHODIMP ButtonProc(/*[in]*/DISPID dispID, /*[in]*/DWORD dwCookie)
    {
      return E_FAIL;
    }
};



//*************************************************************************************************
// IAcPiPropCommandButtonsHostImpl: default implementation of interfaces:
// - IAcPiPropCommandButtons
//*************************************************************************************************
template<class T>
class ATL_NO_VTABLE IAcPiPropCommandButtonsHostImpl : public IAcPiPropCommandButtons
{
  public:
    CMDBTN_VECTOR m_CmdBtnVector;

    CMDBTN_VECTOR & GetCmdBtnVector() { return m_CmdBtnVector; }

    bool IsDefaultCmdBtnEntry(CMDBTN_ENTRY in)
    {
      if (in.m_lpEnBtnBmpRes != NULL)
        return false;
      if (in.m_nEnBtnBmpType != PICTYPE_UNINITIALIZED)
        return false;
      if (in.m_lpDisBtnBmpRes != NULL)
        return false;
      if (in.m_nDisBtnBmpType != PICTYPE_UNINITIALIZED)
        return false;
      if (in.m_pfnBtnProc != NULL)
       return false;
      if (in.m_nBtnNameId != NULL)
        return false;
      if (in.m_nStyle != NULL)
        return false;
      return true;
    }

    IAcPiPropCommandButtonsHostImpl()
    {
      m_CmdBtnVector.clear();
      int i=0;
      while (!IsDefaultCmdBtnEntry(T::GetPropCmdBtnArray()[i]))
      {
        m_CmdBtnVector.push_back(T::GetPropCmdBtnArray()[i]);
        i++;
      }
    }
    virtual ~IAcPiPropCommandButtonsHostImpl() {}

    virtual HINSTANCE GetResourceInstance() = 0;

    // IAcPiPropCommandButtons methods
    STDMETHODIMP GetButtons(VARIANT *pCmdBtns)
    {
      return OpmGetCommandButtons(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), GetCmdBtnVector(), pCmdBtns);
    }
};
#if !defined(__NCHEADERS_H__) && !defined(__NCDBHEADERS_H__)
// Updates sPropName property or all properties if sPropName=NULL
// Note: sPropName is a full property name (for example "General.Color") 
HOST_OPM_API bool UpdateProperties(LPCWSTR sPropName = NULL);
HOST_OPM_API bool OpmUpdateProperties(LPCWSTR sPropName = NULL);
// Reset and gather new list of properties if fFullRefresh=true, otherwise update values only
HOST_OPM_API bool RefreshProperties(bool fFullRefresh = true);
HOST_OPM_API bool OpmRefreshProperties(bool fFullRefresh = true);
#endif