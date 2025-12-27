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

#include "comdef.h"
#include <vector>
#include "OdaX.h"
struct PER_PROP_DISP_ENTRY
{
  DISPID    m_dispid;
  const TCHAR * m_ProgID;
  const TCHAR * m_lpLeftIconRes;
  UINT      m_nLeftIconType;
  const TCHAR * m_lpEllipsisBmpRes;
  UINT      m_nEllipsisBmpType;
  COLORREF  m_TextColor;
  bool      m_bFullView;
  DWORD     m_dwIntegralHeight;
  long      m_nWeight;
};
#ifndef _ODAXWRAP_H_INCLUDED_
typedef int PROPCAT;
#endif //_ODAXWRAP_H_INCLUDED_
struct CATEGORY_ENTRY
{
  PROPCAT   m_CatID;
  UINT      m_nNameId;
  UINT      m_nDescId;
  PROPCAT   m_ParentCatID;
  long      m_nWeight;
};


typedef std::vector<PER_PROP_DISP_ENTRY> PROP_DISP_VECTOR;
typedef std::vector<CATEGORY_ENTRY> CATEGORY_VECTOR;

//*************************************************************************************************
// IOPMPropertyExpanderEx : nCAD extension of IOPMPropertyExpander
//*************************************************************************************************
DEFINE_GUID(IID_IOPMPropertyExpanderEx, 0x46B849A6, 0x0ED1, 0x4afa, 0xA7, 0x44, 0x34, 0x76, 0x30, 0xDD, 0x54, 0x07);

interface DECLSPEC_UUID("46B849A6-0ED1-4afa-A744-347630DD5407") IOPMPropertyExpanderEx : public IOPMPropertyExpander
{
  BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IOPMPropertyExpanderEx methods ***
    STDMETHOD(GetElementBitmap)(/*[in]*/DISPID dispID, /*[in]*/DWORD dwCookie, /*[out]*/IPicture** pPicture) PURE;
    STDMETHOD(ButtonProc)(/*[in]*/DISPID dispID, /*[in]*/DWORD dwCookie) PURE;
};
_COM_SMARTPTR_TYPEDEF(IOPMPropertyExpanderEx, __uuidof(IOPMPropertyExpanderEx));


//*************************************************************************************************
// IOPMPropertyFocusNotify : property focus changed notification interface 
//*************************************************************************************************
DEFINE_GUID(IID_IOPMPropertyFocusNotify, 0xB75ABA33, 0xA39F, 0x4acb, 0x8C, 0xAE, 0x2B, 0xF2, 0x01, 0x4C, 0x4F, 0x85);

interface DECLSPEC_UUID("B75ABA33-A39F-4acb-8CAE-2BF2014C4F85") IOPMPropertyFocusNotify : public IUnknown
{
  BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IOPMPropertyExpanderEx methods ***
    STDMETHOD(FocusChanged)(DISPID dispID, BOOL bFocus, int iGroupIndex = -1) PURE;
};
_COM_SMARTPTR_TYPEDEF(IOPMPropertyFocusNotify, __uuidof(IOPMPropertyFocusNotify));


//*************************************************************************************************
// IOPMPropertyNumeric : numeric property interface 
//*************************************************************************************************
DEFINE_GUID(IID_IOPMPropertyNumeric, 0xA4BB05E6, 0x95EA, 0x4575, 0x87, 0x7C, 0x92, 0xFE, 0x9A, 0x3F, 0x20, 0xE8);

interface DECLSPEC_UUID("A4BB05E6-95EA-4575-877C-92FE9A3F20E8") IOPMPropertyNumeric : public IUnknown
{
  BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IOPMPropertyNumeric methods ***
    STDMETHOD(MinValue)(DISPID dispID, int* pMinValue) PURE;
    STDMETHOD(MaxValue)(DISPID dispID, int* pMaxValue) PURE;
};
_COM_SMARTPTR_TYPEDEF(IOPMPropertyNumeric, __uuidof(IOPMPropertyNumeric));



//*************************************************************************************************
// IAcPiCommandButtons : 
//*************************************************************************************************
DEFINE_GUID(IID_IAcPiPropCommandButtons, 0xa6cd83fa, 0x32a5, 0x4c1e, 0x9f, 0x2e, 0x48, 0x7a, 0x61, 0x2f, 0x4a, 0x77);

interface DECLSPEC_UUID("A6CD83FA-32A5-4c1e-9F2E-487A612F4A77") IAcPiPropCommandButtons : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
  
    /* IAcPiPropCommandButtons methods */
    STDMETHOD(GetButtons)(VARIANT *pButtons) PURE;
};


//*************************************************************************************************
// IAcPiCommandButton : 
//*************************************************************************************************
DEFINE_GUID(IID_IAcPiCommandButton, 0xa5eab6fd, 0xeb1a, 0x43d5, 0xbc, 0xe0, 0x2d, 0xa8, 0xc4, 0x0f, 0x21, 0xba);

interface DECLSPEC_UUID("A5EAB6FD-EB1A-43d5-BCE0-2DA8C40F21BA") IAcPiCommandButton : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IAcPiCommandButton methods */
    STDMETHOD(GetName)(LCID lcid, BSTR *name) PURE;
    STDMETHOD(get_EnabledPicture)(IUnknown **pPicture) PURE;
    STDMETHOD(get_DisabledPicture)(IUnknown **pPicture) PURE;
    STDMETHOD(get_Enabled)(VARIANT_BOOL *bEnabled) PURE;
    STDMETHOD(put_Enabled)(VARIANT_BOOL bEnabled) PURE;
    STDMETHOD(get_Checked)(VARIANT_BOOL *bChecked) PURE;
    STDMETHOD(put_Checked)(VARIANT_BOOL bChecked) PURE;
    STDMETHOD(get_ButtonStyle)(long *style) PURE;
    STDMETHOD(Execute)(VARIANT Objects) PURE;
};

//*************************************************************************************************
// CMDBTN_ENTRY : 
//*************************************************************************************************
typedef BOOL (*BUTTONPROC)(IAcPiCommandButton* pButton, VARIANT Objects);
struct CMDBTN_ENTRY
{
  UINT          m_nBtnNameId;
  const TCHAR * m_lpEnBtnBmpRes;
  UINT          m_nEnBtnBmpType;
  const TCHAR * m_lpDisBtnBmpRes;
  UINT          m_nDisBtnBmpType;
  long          m_nStyle;
  BUTTONPROC    m_pfnBtnProc;
};

#define BEGIN_CMDBTN_MAP() \
  static CMDBTN_ENTRY * GetPropCmdBtnArray() \
  { \
    static CMDBTN_ENTRY pCmdBtnArray[] = \
    { \

#define CMDBTN_MAP_ENTRY(NameId, lpEnBtnBmpRes, lpEnBtnBmpType, lpDisBtnBmpRes, lpDisBtnBmpType, nStyle, pfnBtnProc) \
      { NameId, lpEnBtnBmpRes, lpEnBtnBmpType, lpDisBtnBmpRes, lpDisBtnBmpType, nStyle, pfnBtnProc },                      

#define END_CMDBTN_MAP() \
      { 0, NULL, PICTYPE_UNINITIALIZED, NULL, PICTYPE_UNINITIALIZED, NULL, NULL } \
    }; \
    return pCmdBtnArray; \
  }

typedef std::vector<CMDBTN_ENTRY> CMDBTN_VECTOR;

struct CATCMDBTN_ENTRY
{
  PROPCAT      m_CatID;
  UINT         m_nBtnNameId;
  const TCHAR* m_lpEnBtnBmpRes;
  UINT         m_nEnBtnBmpType;
  const TCHAR* m_lpDisBtnBmpRes;
  UINT         m_nDisBtnBmpType;
  long         m_nStyle;
  BUTTONPROC   m_pfnBtnProc;
};

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

typedef std::vector<CATCMDBTN_ENTRY>  CATCMDBTN_VECTOR;

//*************************************************************************************************
// IDynamicPropertyNotify : 
//*************************************************************************************************
interface IDynamicProperty;
DEFINE_GUID(IID_IDynamicPropertyNotify, 0x8B384028, 0xACA8, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACA8-11d1-A2B4-080009DC639A") IDynamicPropertyNotify : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDynamicPropertyNotify methods */

    // Call this when your property changes
    STDMETHOD(OnChanged)(THIS_ /*[in]*/IDynamicProperty* pDynamicProperty) PURE;
    // Call to get the current selection set OPM is working with, returns a SAFEARRAY 
    // of LONGs representing the objectIDs of the set, be sure to call VariantClear to cleanup
    STDMETHOD(GetCurrentSelectionSet)(THIS_ /*[out*/VARIANT* pSelection) PURE;
};
typedef IDynamicPropertyNotify FAR* LPDYNAMICPROPERTYNOTIFY;


//*************************************************************************************************
// IDynamicPropertyNotify2 : 
//*************************************************************************************************
interface IDynamicProperty2;
DEFINE_GUID(IID_IDynamicPropertyNotify2, 0x975112b5, 0x5403, 0x4197, 0xaf, 0xb8, 0x90, 0xc6, 0xca, 0x73, 0xb9, 0xe1);

interface DECLSPEC_UUID("975112B5-5403-4197-AFB8-90C6CA73B9E1") IDynamicPropertyNotify2 : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDynamicPropertyNotify2 methods */

    // Call this when your property changes.
    // Either IDynamicProperty or IDynamicProperty2 will be queried from the IUnknown pointer supplied.
    STDMETHOD(OnChanged)(THIS_ /*[in]*/IUnknown* pDynamicProperty) PURE;
    // Call to get the current selection set OPM is working with, returns a SAFEARRAY 
    // of IUnknowns representing the objects of the set, be sure to call VariantClear to cleanup
    STDMETHOD(GetCurrentSelectionSet)(THIS_ /*[out*/VARIANT* pSelection) PURE;
};
typedef IDynamicPropertyNotify2 FAR* LPDYNAMICPROPERTYNOTIFY2;

const int DISPID_DYNAMIC = -23; //majic DISPID

//*************************************************************************************************
// IDynamicProperty : Implement this class to create dynamic properties for the OPM
// it defines the base set of property attributes as well as the name/type/data tuples. 
//*************************************************************************************************
DEFINE_GUID(IID_IDynamicProperty, 0x8B384028, 0xACA9, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACA9-11d1-A2B4-080009DC639A") IDynamicProperty : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDynamicProperty methods */
    //Unique property ID
    STDMETHOD(GetGUID)(THIS_ /*[out]*/GUID* propGUID) PURE;
    // Property display name
    STDMETHOD(GetDisplayName)(THIS_ /*[out]*/BSTR* bstrName) PURE;
    // Show/Hide property in the OPM, for this object instance 
    STDMETHOD(IsPropertyEnabled)(THIS_ /*[in]*/LONG_PTR objectID, /*[out]*/BOOL* pbEnabled) PURE;
    // Is property showing but disabled
    STDMETHOD(IsPropertyReadOnly)(THIS_ /*[out]*/BOOL* pbReadonly) PURE;
    // Get the property description string
    STDMETHOD(GetDescription)(THIS_ /*[out]*/BSTR* bstrName) PURE;
    
    /* Basic property value information. OPM will typically display these in an edit field */
    // optional: meta data representing property type name (ex. ACAD_ANGLE)
    STDMETHOD(GetCurrentValueName)(THIS_ /*[out]*/BSTR* pbstrName) PURE;
    // What is the property type (ex. VT_R8)
    STDMETHOD(GetCurrentValueType)(THIS_ /*[out]*/VARTYPE* pVarType) PURE;
    // Get the property value, passes the specific object we need the property value for
    STDMETHOD(GetCurrentValueData)(THIS_ /*in*/LONG_PTR objectID, /*[out]*/VARIANT* pvarData) PURE;
    // Set the property value, passes the specific object we want to set the property value for
    STDMETHOD(SetCurrentValueData)(THIS_ /*[in]*/LONG_PTR objectID, /*[in]*/const VARIANT varData) PURE;

    /* Notifications */
    // OPM passes its implementation of IDynamicPropertyNotify, you
    // cache it and call it to inform OPM your property has changed
    STDMETHOD(Connect)(THIS_ /*[in]*/IDynamicPropertyNotify* pSink) PURE;
    STDMETHOD(Disconnect)(THIS_ ) PURE;
};
typedef IDynamicProperty FAR* LPDYNAMICPROPERTY;


//*************************************************************************************************
// IDynamicPropertyEx : Implement functionality of IDynamicProperty and Invalidate() method
//*************************************************************************************************
DEFINE_GUID(IID_IDynamicPropertyEx, 0xC75D1B7A, 0x227A, 0x4821, 0xA7, 0xD5, 0x59, 0xEA, 0x0A, 0x68, 0x44, 0xB9);

interface DECLSPEC_UUID("C75D1B7A-227A-4821-A7D5-59EA0A6844B9") IDynamicPropertyEx : public IDynamicProperty
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDynamicPropertyEx methods */
    // When called property control should be updated
    STDMETHOD(Invalidate)() PURE;
};
typedef IDynamicPropertyEx FAR* LPDYNAMICPROPERTYEX;



//*************************************************************************************************
// IDynamicProperty2 : Implement this class to create dynamic properties for the PropertyPalette
// it defines the base set of property attributes as well as the name/type/data tuples. 
//*************************************************************************************************
DEFINE_GUID(IID_IDynamicProperty2, 0x9caf41c2, 0xca86, 0x4ffb, 0xb0, 0x5a, 0xac, 0x43, 0xc4, 0x24, 0xd0, 0x76);

interface DECLSPEC_UUID("9CAF41C2-CA86-4ffb-B05A-AC43C424D076") IDynamicProperty2 : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDynamicProperty2 methods */
    //Unique property ID
    STDMETHOD(GetGUID)(THIS_ /*[out]*/GUID* propGUID) PURE;
    // Property display name
    STDMETHOD(GetDisplayName)(THIS_ /*[out]*/BSTR* bstrName) PURE;
    // Show/Hide property in the OPM, for this object instance 
    STDMETHOD(IsPropertyEnabled)(THIS_ /*[in]*/IUnknown *pUnk, /*[out]*/BOOL* pbEnabled) PURE;
    // Is property showing but disabled
    STDMETHOD(IsPropertyReadOnly)(THIS_ /*[out]*/BOOL* pbReadonly) PURE;
    // Get the property description string
    STDMETHOD(GetDescription)(THIS_ /*[out]*/BSTR* bstrName) PURE;
    
    /* Basic property value information. OPM will typically display these in an edit field */
    // optional: meta data representing property type name, ex. ACAD_ANGLE
    STDMETHOD(GetCurrentValueName)(THIS_ /*[out]*/BSTR* pbstrName) PURE;
    // What is the property type, ex. VT_R8
    STDMETHOD(GetCurrentValueType)(THIS_ /*[out]*/VARTYPE* pVarType) PURE;
    // Get the property value, passes the specific object we need the property value for.
    STDMETHOD(GetCurrentValueData)(THIS_ /*in*/IUnknown *pUnk, /*[out]*/VARIANT* pvarData) PURE;
    // Set the property value, passes the specific object we want to set the property value for
    STDMETHOD(SetCurrentValueData)(THIS_ /*[in]*/IUnknown *pUnk, /*[in]*/const VARIANT varData) PURE;

    /* Notifications */
    // OPM passes its implementation of IDynamicPropertyNotify, you
    // cache it and call it to inform OPM your property has changed
    STDMETHOD(Connect)(THIS_ /*[in]*/IDynamicPropertyNotify2* pSink) PURE;
    STDMETHOD(Disconnect)(THIS_ ) PURE;
};
typedef IDynamicProperty2 FAR* LPDYNAMICPROPERTY2;


//*************************************************************************************************
// IDynamicEnumProperty : components can implement this interface to create an enumerated property
// which will usually be displayed as a drop-down list in the OPM
//*************************************************************************************************
DEFINE_GUID(IID_IDynamicEnumProperty, 0x8B384028, 0xACB1, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACB1-11d1-A2B4-080009DC639A") IDynamicEnumProperty : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDynamicEnumProperty methods */    
    // total number of values this property can have, or currently has
    STDMETHOD(GetNumPropertyValues)(THIS_ /*[out]*/LONG* numValues) PURE;
    // called for each property value, 0-based indexed to GetNumPropertyValues()
    STDMETHOD(GetPropValueName)(THIS_ /*in*/LONG index, /*[out]*/BSTR* valueName) PURE;
    // called for each property value, 0-based indexed to GetNumPropertyValues()
    STDMETHOD(GetPropValueData)(THIS_ /*in*/LONG index, /*[out]*/VARIANT* valueData) PURE;
};
typedef IDynamicEnumProperty FAR* LPDYNAMICENUMPROPERTY;

//*************************************************************************************************
// IDynamicDialogProperty : components can implement this interface to support ellipsis
// button properties
//*************************************************************************************************
typedef BOOL (*OPMDIALOGPROC)(void);
DEFINE_GUID(IID_IDynamicDialogProperty, 0x8B384028, 0xACB2, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACB2-11d1-A2B4-080009DC639A") IDynamicDialogProperty : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDynamicDialogProperty methods */ 
    // If implemented, OPM will call the function passed back here
    STDMETHOD(GetCustomDialogProc)(THIS_ /*[out]*/OPMDIALOGPROC* pDialogProc) PURE;
    // Or, pass us the name of the VBA macro to run to edit this property
    STDMETHOD(GetMacroName)(THIS_ /*[out]*/BSTR* bstrName) PURE;
};
typedef IDynamicDialogProperty FAR* LPDYNAMICDIALOGPROPERTY;

//*************************************************************************************************
// IPropertyManager : Use this to add your property classes for a given command or type of entity
//*************************************************************************************************
DEFINE_GUID(IID_IPropertyManager, 0x8B384028, 0xACA9, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACA9-11d1-A2B4-080009DC639A") IPropertyManager : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IPropertyManager methods */
    STDMETHOD(AddProperty)(THIS_ IDynamicProperty FAR* pProperty) PURE;
    STDMETHOD(RemoveProperty)(THIS_ IDynamicProperty FAR* pProperty) PURE;
    STDMETHOD(GetDynamicProperty)(THIS_ /*[in]*/LONG index, /*[out]*/IDynamicProperty ** pProperty) PURE;
    STDMETHOD(GetDynamicPropertyByName)(THIS_ /*[in]*/BSTR propName, /*[out]*/IDynamicProperty ** pProperty) PURE;
    STDMETHOD(GetDynamicPropertyCount)(THIS_ /*[out]*/LONG* count) PURE;
    
    // For COM Wrappers to generate dynamic property typeinfo
    STDMETHOD(GetDynamicClassInfo)(THIS_ /*[in]*/IUnknown* pObj, /*[out]*/ITypeInfo** pptiDynamic, /*[out]*/DWORD* dwCookie) PURE;
};
typedef IPropertyManager FAR* LPPROPERTYMANAGER;


//*************************************************************************************************
// IPropertyManager2: Use this to add your property classes for a given type of IUnknown object. 
// You can get this interface using CreateOPMIUnknownProtocol(ppUnk)->GetPropertyManager2().
//*************************************************************************************************
DEFINE_GUID(IID_IPropertyManager2, 0xfabc1c70, 0x1044, 0x4aa0, 0xbf, 0x8d, 0x91, 0xff, 0xf9, 0x5, 0x27, 0x15);

interface DECLSPEC_UUID("FABC1C70-1044-4aa0-BF8D-91FFF9052715") IPropertyManager2 : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IPropertyManager2 methods */
    STDMETHOD(AddProperty)(THIS_ IUnknown FAR* pDynPropObj) PURE;
    STDMETHOD(RemoveProperty)(THIS_ IUnknown FAR* pDynPropObj) PURE;
    STDMETHOD(GetDynamicProperty)(THIS_ /*[in]*/LONG index, /*[out]*/IUnknown ** pDynPropObj) PURE;
    STDMETHOD(GetDynamicPropertyByName)(THIS_ /*[in]*/BSTR propName, /*[out]*/IUnknown ** pDynPropObj) PURE;
    STDMETHOD(GetDynamicPropertyCountEx)(THIS_ /*[out]*/LONG* count) PURE;
    
    // For COM Wrappers to generate dynamic property typeinfo
    STDMETHOD(GetDynamicClassInfo)(THIS_ /*[in]*/IUnknown* pObj, /*[out]*/ITypeInfo** pptiDynamic, /*[out]*/DWORD* dwCookie) PURE;
};
typedef IPropertyManager2 FAR* LPPROPERTYMANAGER2;



//*************************************************************************************************
// IPropertySource : 
//*************************************************************************************************
DEFINE_GUID(IID_IPropertySource, 0x61d0a8e3, 0xc792, 0x4956, 0x8e, 0x96, 0x59, 0x43, 0x15, 0xb9, 0x59, 0x2);

interface DECLSPEC_UUID("61D0A8E3-C792-4956-8E96-594315B95902") IPropertySource : public IUnknown
{
  BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IPropertySource methods */
    STDMETHOD(get_Name)(THIS_ /*[out, retval]*/BSTR* pName) PURE;
    STDMETHOD(GetProperties)(THIS_ /*[in]*/IUnknown* pObject, /*[out, retval]*/VARIANT *pPropertyArray) PURE;
};
typedef IPropertySource FAR* LPPROPERTYSOURCE;
