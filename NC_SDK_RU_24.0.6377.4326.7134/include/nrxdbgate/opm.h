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

#ifndef __OPENDWG_OPM_H__
#define __OPENDWG_OPM_H__
#if !defined(HOST_IN_QT)
#include "nrxdbgate_impexp.h"
#include "hostOPM.h"
#include "category.h"

struct NCAD_OPMPROPMAP_ENTRY     //Full copy of ODA_OPMPROPMAP_ENTRY
{
  UINT nDescID;                  //Alternate property name
  DISPID dispid;                 //ID of the property
  PROPCAT  catid;                //categoryID
  UINT nCatNameID;               //category Name
  UINT nElementStrID;            //expanded property name list (for pts, ex.)
  UINT nPredefinedStrID;         //IPerPropertyBrowsing enumeration strings
  LPCWSTR    predefinedValues;    //IPerPropertyBrowsing enumeration values
  unsigned short grouping;       //expanded property name grouping
  bool      editable;            //show property override
  const CLSID* pclsidOther;      //CLSID for Other.. combo item dlg (not used)
  const CLSID* pclsidPropPage;   //IPerPropertyBrowsing dialog CLSID
  const IID* piidDispatch;       //dispatch pointer for property
  LPCOLESTR szEllipsesTxt;       //IPerPropertyBrowsing display string
};

struct PER_PROP_DISP_ENTRY;
typedef std::vector<PER_PROP_DISP_ENTRY> PROP_DISP_VECTOR;
struct CATEGORY_ENTRY;
typedef std::vector<CATEGORY_ENTRY> CATEGORY_VECTOR;
struct CATCMDBTN_ENTRY;
typedef std::vector<CATCMDBTN_ENTRY>  CATCMDBTN_VECTOR;
struct CMDBTN_ENTRY;
typedef std::vector<CMDBTN_ENTRY> CMDBTN_VECTOR;


#ifdef BEGIN_OPMPROP_MAP
#undef BEGIN_OPMPROP_MAP
#endif

#ifdef OPMPROP_ENTRY
#undef OPMPROP_ENTRY
#endif

#ifdef OPMPROP_CAT_ENTRY
#undef OPMPROP_CAT_ENTRY
#endif

#ifdef OPMPROP_DESC_ENTRY
#undef OPMPROP_DESC_ENTRY
#endif

#ifdef OPMPROP_PREDEFINED_ENTRY
#undef OPMPROP_PREDEFINED_ENTRY
#endif

#ifdef OPMPROP_ELEMENT_ENTRY
#undef OPMPROP_ELEMENT_ENTRY
#endif

#ifdef OPMPROP_PAGE
#undef OPMPROP_PAGE
#endif

#ifdef END_OPMPROP_MAP
#undef END_OPMPROP_MAP
#endif

#define BEGIN_OPMPROP_MAP()                                 \
	static NCAD_OPMPROPMAP_ENTRY* GetOPMPropertyMap()               \
	{                                                               \
		static NCAD_OPMPROPMAP_ENTRY pPropMap[] =                   \
		{

// DescriptionID, dispID, catagoryID, catagoryNameID, elements string list ID (semi-colon separator), predefined strings ID (semi-colon separator), predefined values, grouping, editable property, other, proppage
#define OPMPROP_ENTRY(nDesID, dpid, ctid, ctNameID, elementsID, predefID, vals, grp, editable, other, clsid, ellipsesTxt)      \
		{nDesID, dpid, ctid, ctNameID, elementsID, predefID, vals, grp, editable, &other, &clsid, &IID_IDispatch, OLESTR(ellipsesTxt)},

#define OPMPROP_CAT_ENTRY(nDesID, dpid, ctid, ctNameID)      \
		{nDesID, dpid, ctid, ctNameID, 0, 0, _NCRX_T(""), 0, 1, &IID_NULL, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_DESC_ENTRY(nDesID, dpid)      \
		{nDesID, dpid, -2, 0, 0, 0, _NCRX_T(""), 0, 1, &IID_NULL, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_PREDEFINED_ENTRY(nDesID, dpid, predefID, values, other)      \
		{nDesID, dpid, -2, 0, 0, predefID, values, 0, 1, &other, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_ELEMENT_ENTRY(dpid, ctid, ctNameID, elementsID, grouping)      \
		{0, dpid, ctid, ctNameID, elementsID, 0, _NCRX_T(""), grouping, 1, &IID_NULL, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_PAGE(nDesID, dpid, ctid, ctNameID, clsid)      \
		{nDesID, dpid, ctid, ctNameID, 0, 0, _NCRX_T(""), 0, 1, &IID_NULL, &clsid, &IID_IDispatch, OLESTR("")},

#define END_OPMPROP_MAP()                                           \
			{0, 0, 0, 0, 0, 0, NULL, 0, 0, NULL, NULL, &IID_NULL, NULL}            \
		};                                                          \
		return pPropMap;                                            \
	}

#define BEGIN_PERPROPDISPLAY_MAP()                                                            \
    static PER_PROP_DISP_ENTRY* GetPerPropDisplayArray()                                    \
    {                                                                                        \
        static PER_PROP_DISP_ENTRY pPerPropDisplayArray[] =                                 \
        {
                                                                                            
#define PROP_DISP_ENTRY(dispid, progid, lpLeftIconRes, lpLeftIconType,                        \
    lpEllipsisBmpRes, lpEllipsisBmpType, textcolor,                                          \
    bFullView, dwIntegralHeight, nWeight)                                                    \
        {dispid, progid, lpLeftIconRes, lpLeftIconType, lpEllipsisBmpRes,                    \
        lpEllipsisBmpType, textcolor, bFullView,                                             \
        dwIntegralHeight, nWeight},                                                            \
                                                                                            
#define END_PERPROPDISPLAY_MAP()                                                            \
        {-1, NULL, NULL, PICTYPE_UNINITIALIZED, NULL, PICTYPE_UNINITIALIZED, 0x80000008, false, -1, -1}                    \
        };                                                                                    \
        return pPerPropDisplayArray;                                                        \
    }

#define BEGIN_CAT_MAP() \
	static CATEGORY_ENTRY * GetCatArray() \
	{ \
		static CATEGORY_ENTRY pCatArray[] = {


#define CATEGORY_MAP_ENTRY(nId, NameId, DescId, nParentId, nWeight) \
			{ nId, NameId, DescId, nParentId, nWeight },

#define END_CAT_MAP() \
			{ -1, 0, 0, -1, -1 } \
		}; \
		return pCatArray; \
	}



#define BEGIN_CATCMDBTN_MAP() \
	static CATCMDBTN_ENTRY * GetCmdBtnArray() \
	{ \
		static CATCMDBTN_ENTRY pCatCmdBtnArray[] = {


#define CATCMDBTN_MAP_ENTRY(nId, NameId, lpEnBtnBmpRes, lpEnBtnBmpType, lpDisBtnBmpRes, lpDisBtnBmpType, nStyle, \
	                        pfnBtnProc) \
			{ nId, NameId, lpEnBtnBmpRes, lpEnBtnBmpType, lpDisBtnBmpRes, lpDisBtnBmpType, nStyle, pfnBtnProc },

#define END_CATCMDBTN_MAP() \
			{ -1, 0, NULL, PICTYPE_UNINITIALIZED, NULL, PICTYPE_UNINITIALIZED, NULL, NULL } \
		}; \
		return pCatCmdBtnArray; \
	}

// ICategorizeProperties methods
//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmMapPropertyToCategory(IUnknown* pUnk, NCAD_OPMPROPMAP_ENTRY* pMap, DISPID dispid, PROPCAT* ppropcat);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetCategoryName(IUnknown* pUnk, HINSTANCE hResInstance, NCAD_OPMPROPMAP_ENTRY* pMap, PROPCAT propcat,
                                              LCID lcid, BSTR* pbstrName);
// IAcPiCategorizeProperties methods
//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetCategoryName(IUnknown* pUnk, HINSTANCE hResInstance, CATEGORY_VECTOR& arr, PROPCAT propcat,
                                              LCID lcid, BSTR* pbstrName);

NRXDBGATE_EXPORT void ReportNotImplementedAPI(PCWSTR szDesc);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetCategoryCommandButtons(IUnknown *pUnk, HINSTANCE hResInstance, CATCMDBTN_VECTOR & arr, PROPCAT propcat, VARIANT *pCatCmdBtns);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetParentCategory(IUnknown* pUnk, CATEGORY_VECTOR& arr, PROPCAT propcat, PROPCAT* pParentCatID);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetCategoryWeight(IUnknown* pUnk, CATEGORY_VECTOR& arr, PROPCAT propcat, long* pCategoryWeight);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetCategoryDescription(IUnknown* pUnk, HINSTANCE hResInstance, CATEGORY_VECTOR& arr, PROPCAT propcat,
                                                     LCID lcid, BSTR* pbstrDesc);


// IPerPropertyBrowsing methods
//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetDisplayString(IUnknown* pUnk, NCAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BSTR* pBstr);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmMapPropertyToPage(IUnknown* pUnk, NCAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, CLSID* pClsid);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetPredefinedStrings(IUnknown* pUnk, HINSTANCE hResInstance, NCAD_OPMPROPMAP_ENTRY* pMap,
                                                   DISPID dispID, CALPOLESTR* pCaStringsOut, CADWORD* pCaCookiesOut);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetPredefinedValue(IUnknown* pUnk, NCAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, DWORD dwCookie,
                                                 VARIANT* pVarOut);

// IOPMPropertyExtension methods
//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetDisplayName(IUnknown* pUnk, HINSTANCE hResInstance, NCAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID,
                                             BSTR* pBstr);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmEditable(IUnknown* pUnk, NCAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BOOL __RPC_FAR* bEditable);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmShowProperty(IUnknown* pUnk, NCAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BOOL* pShow);

// IAcPiPropertyDisplay methods
//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetPropertyWeight(IUnknown* pUnk, PROP_DISP_VECTOR& arr, VARIANT Id, long* pPropertyWeight);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmIsPropFullView(IUnknown* pUnk, PROP_DISP_VECTOR& arr, VARIANT Id, VARIANT_BOOL* pbVisible,
                                             DWORD* pIntegralHeight);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetPropTextColor(IUnknown* pUnk, PROP_DISP_VECTOR& arr, VARIANT Id, OLE_COLOR* pTextColor);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetPropertyIcon(IUnknown* pUnk, HINSTANCE hResInstance, PROP_DISP_VECTOR& arr, VARIANT Id,
                                              IUnknown** ppIcon);

//**********************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcOpmGetCustomPropertyCtrl(IUnknown* pUnk, PROP_DISP_VECTOR& arr, VARIANT Id, LCID lcid, BSTR* psProdId);

// IAcPiPropCommandButtons methods
NRXDBGATE_EXPORT HRESULT NcOpmGetCommandButtons(IUnknown *pUnk, HINSTANCE hResInstance, CMDBTN_VECTOR & arr, VARIANT *pCmdBtns);


#endif // HOST_IN_QT
#endif // __OPENDWG_OPM_H__
