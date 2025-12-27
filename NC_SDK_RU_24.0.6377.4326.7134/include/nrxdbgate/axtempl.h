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

#ifndef __OPENDWG_AXTEMPL_H__
#define __OPENDWG_AXTEMPL_H__
#include "nrxdbgate_impexp.h"



// The following #defies may be used in place of VARIANT_TRUE and
// VARIANT_FALSE to avoid Microsoft compiler warnings C4310
#define NCAX_VARIANT_TRUE   (VARIANT_BOOL)-1
#define NCAX_VARIANT_FALSE  (VARIANT_BOOL)0

typedef CALPOLESTR  OPMLPOLESTR;
typedef CADWORD     OPMDWORD;

#ifdef OPMPROP_ENTRY
	#undef OPMPROP_ENTRY
#endif

#define OPMPROP_ENTRY(nDesID, dpid, ctid, ctNameID, elementsID, predefID, vals, grp, editable, other, clsid, ellipsesTxt) \
	{ nDesID, dpid, ctid, ctNameID, elementsID, predefID, vals, grp, editable, &other, &clsid, &IID_IDispatch, \
	  OLESTR(ellipsesTxt) },

template < class T >
class CProxy_AcadObjectEvents :
	public IConnectionPointImpl< T, &__uuidof(IAcadObjectEvents), CComDynamicUnkArray >
{
public:

	void Fire_Modified()
	{
		T* pT = static_cast< T* >(this);
		CComPtr< IAcadObject > pAcadObject;
		pT->QueryInterface(__uuidof(IAcadObject), (void**)&pAcadObject);
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IAcadObjectEvents* pAcadObjectEvents = reinterpret_cast< IAcadObjectEvents* >(*pp);
				//_ASSERTE(pAcadObjectEvents != NULL);
				pAcadObjectEvents->Modified(pAcadObject);
			}
			pp++;
		}
		pT->Unlock();
	}
};

template < class T >
class CProxy_PropertyNotifySink : public IConnectionPointImpl< T, &IID_IPropertyNotifySink, CComDynamicUnkArray >
{
public:

	void Fire_OnChanged()
	{
		Fire_OnChanged(DISPID_UNKNOWN);
	}

	void Fire_OnChanged(DISPID dispId)
	{
		T* pT = static_cast< T* >(this);
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			IPropertyNotifySink* pNotifySink = reinterpret_cast< IPropertyNotifySink* >(*pp);
			if (pNotifySink)
				pNotifySink->OnChanged(dispId);
			pp++;
		}
		pT->Unlock();
	}
};
// IAcadBaseObject and IRetrieveApplication already defined in odaxwrap.h
	DEFINE_GUID(IID_IAcadBaseObject, 0xc9e0781d, 0xba3d, 0x4224, 0x9f, 0xa4, 0x58, 0xec, 0xea, 0x2b, 0xc5, 0x59);

	/* Definition of interface: IAcadBaseObject */
#undef INTERFACE
#define INTERFACE  IAcadBaseObject

interface DECLSPEC_UUID("C9E0781D-BA3D-4224-9FA4-58ECEA2BC559")
IAcadBaseObject : public IUnknown
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// IAcadBaseObject methods
	STDMETHOD(SetObjectId)(THIS_ NcDbObjectId& objId, NcDbObjectId ownerId = NcDbObjectId::kNull,
		                      NCHAR* keyName = NULL) PURE;
	STDMETHOD(GetObjectId)(THIS_ NcDbObjectId* objId) PURE;
	STDMETHOD(Clone)(THIS_ NcDbObjectId ownerId, LPUNKNOWN* pUnkClone) PURE;
	STDMETHOD(GetClassID)(THIS_ CLSID& clsid) PURE;
	STDMETHOD(NullObjectId)(THIS) PURE;
	STDMETHOD(OnModified)(THIS) PURE;
};
// {ADAAAEC4-C7FE-11d5-8D60-0010830243CE}
DEFINE_GUID(IID_IAcadBaseObject2,
	0xadaaaec4, 0xc7fe, 0x11d5, 0x8d, 0x60, 0x0, 0x10, 0x83, 0x2, 0x43, 0xce);

/* Definition of interface: IAcadBaseObject2 */

interface DECLSPEC_UUID("ADAAAEC4-C7FE-11d5-8D60-0010830243CE") 
IAcadBaseObject2 : public IUnknown       
{
	/* IUnknown methods */
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	/* IAcadBaseObject2 methods */
	STDMETHOD(ForceDbResident)(THIS_ VARIANT_BOOL* forceDbResident) PURE;
	STDMETHOD(AddToDb)(THIS_ NcDbObjectId& objId, 
		NcDbObjectId ownerId = NcDbObjectId::kNull,
		NCHAR* keyName = NULL) PURE;
	STDMETHOD(CreateObject)(THIS_ NcDbObjectId ownerId = NcDbObjectId::kNull,
		NCHAR* keyName = NULL) PURE;
	STDMETHOD(ObjectExists)(THIS_ VARIANT_BOOL* objectExists) PURE;
	STDMETHOD(SetObject)(THIS_ NcDbObject*& pObj) PURE;
	STDMETHOD(GetObject)(THIS_ NcDbObject*& pObj) PURE;
	STDMETHOD(OnModified)(THIS_ DISPID = DISPID_UNKNOWN) PURE;
};

typedef IAcadBaseObject2* LPACADBASEOBJECT2;
_COM_SMARTPTR_TYPEDEF(IAcadBaseObject, __uuidof(IAcadBaseObject));


/* Definition of interface: IAcadBaseSubEntity */
DEFINE_GUID(IID_IAcadBaseSubEntity, 0xb374d885, 0xeece, 0x4138, 0x8c, 0x82, 0x3f, 0xb2, 0xc, 0x53, 0x87, 0x88);

#undef INTERFACE
#define INTERFACE IAcadBaseSubEntity

interface DECLSPEC_UUID("B374D885-EECE-4138-8C82-3FB20C538788") 
IAcadBaseSubEntity : public IUnknown
{
	/* IUnknown methods */
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	/* IAcadBaseSubEntity methods */
	STDMETHOD(OnModified)() PURE;
	STDMETHOD(SetFullSubEntPath)(THIS_ NcDbFullSubentPath& subentPath) PURE; 
	STDMETHOD(GetFullSubEntPath)(THIS_ NcDbFullSubentPath* subentPath) PURE;
	STDMETHOD(GetClassID)(THIS_ CLSID& clsid) PURE;
};

typedef IAcadBaseSubEntity* LPACADSUBENTITY;

// Definition of interface: IRetrieveApplication

#ifndef _ODAXWRAP_H_INCLUDED_
interface __declspec(uuid("765B4640-664A-11cf-93F3-0800099EB3B7")) 
IRetrieveApplication : public IUnknown
{
	// IRetrieveApplication methods
	virtual HRESULT STDMETHODCALLTYPE SetApplicationObject(LPDISPATCH pAppDisp) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetApplicationObject(LPDISPATCH* pAppDisp) = 0;
};

typedef IRetrieveApplication* LPRETRIEVEAPPLICATION;

_COM_SMARTPTR_TYPEDEF(IRetrieveApplication, __uuidof(IRetrieveApplication));
#endif //_ODAXWRAP_H_INCLUDED_

class ATL_NO_VTABLE IRetrieveApplicationImpl : public IRetrieveApplication
{
public:
	IRetrieveApplicationImpl()
	{
		m_App = NULL;
	}

	virtual ~IRetrieveApplicationImpl()
	{
		if (m_App != NULL)
			m_App->Release();
	}

	STDMETHOD(SetApplicationObject)(LPDISPATCH pApp)
	{
		if (m_App != NULL)
			return E_FAIL;

		m_App = pApp;

		// only addref if there is a valid pointer
		if (m_App != NULL)
			m_App->AddRef();

		return S_OK;
	}

	// not exported via
	STDMETHOD(GetApplicationObject)(LPDISPATCH* pApp)
	{
		*pApp = m_App;
		if (m_App == NULL)
			return E_FAIL;

		m_App->AddRef();
		return S_OK;
	}

protected:
	LPDISPATCH m_App;
};

template < class T, const CLSID* pclsid >
class ATL_NO_VTABLE IAcadBaseObjectImpl : public IAcadBaseObject, public IConnectionPointContainerImpl< T >,
	public CProxy_AcadObjectEvents< T >, public CProxy_PropertyNotifySink< T >
{
public:
	IAcadBaseObjectImpl() {}

	virtual ~IAcadBaseObjectImpl()
	{
		if (!m_objId.isValid())
			return;

		NcDbObjectPointer< NcDbObject > pObject(m_objId, NcDb::kForRead, NRX::kTrue);
		if (pObject.openStatus() != Nano::eOk)
		{
			NcDbObject* pTemp;
			if (Nano::eOk != ncdbOpenObject(pTemp, m_objId, NcDb::kForNotify, NRX::kTrue))
			{
				return;
			}
			pObject.acquire(pTemp);
		}

		NcAxOleLinkManager* pOleLinkManager = NcAxGetOleLinkManager();
		//_ASSERTE(pOleLinkManager != NULL);
		if (pOleLinkManager != NULL)
			pOleLinkManager->SetIUnknown(pObject.object(), NULL);
	}

	// Implement to create a new object to the specified owner. Return
	// the new object id to the caller.
	virtual HRESULT CreateNewObject(NcDbObjectId& objId, NcDbObjectId& ownerId, NCHAR* keyName) = 0;

	// IAcadBaseObject
	STDMETHOD(SetObjectId)(NcDbObjectId& objId, NcDbObjectId ownerId = NcDbObjectId::kNull, NCHAR* keyName = NULL)
	{
		if (!m_objId.isNull())
			return E_FAIL;

		if (objId == NcDbObjectId::kNull)
		{
			HRESULT hr;
			if (FAILED(hr = CreateNewObject(objId, ownerId, keyName)))
				return hr;
		}

		m_objId = objId;
		//_ASSERTE(m_objId != NcDbObjectId::kNull);
		ObjectIdModified();
		return S_OK;
	}

	STDMETHOD(GetObjectId)(NcDbObjectId* objId)
	{
		*objId = m_objId;
		return S_OK;
	}

	STDMETHOD(Clone)(NcDbObjectId /*ownerId*/, LPUNKNOWN* /*pUnkClone*/)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetClassID)(CLSID& clsid)
	{
		clsid = *pclsid;
		return S_OK;
	}

	STDMETHOD(NullObjectId) (void)
	{
		m_objId = NcDbObjectId::kNull;
		ObjectIdModified();
		return S_OK;
	}

	STDMETHOD(OnModified) (void)
	{
		Fire_Modified();
		Fire_OnChanged();
		return S_OK;
	}

	// IConnectionPointContainerImpl
	BEGIN_CONNECTION_POINT_MAP(T)
	CONNECTION_POINT_ENTRY(__uuidof(IAcadObjectEvents))
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	END_CONNECTION_POINT_MAP()

protected:
	NcDbObjectId m_objId;

	// Notify derived classes (e.g. IAcadBaseObject2Impl) that
	// objectId has been modified
	virtual void ObjectIdModified() {};
};

template < class T, const CLSID* pclsid >
	class ATL_NO_VTABLE IAcadBaseObject2Impl : public IAcadBaseObject2,
		public IAcadBaseObjectImpl< T, pclsid >
{
public:
	IAcadBaseObject2Impl() {};

	virtual ~IAcadBaseObject2Impl() {};

	// IAcadBaseObject2

	// Attaches the wrapper instance to an object via an NcDbObject pointer.
	STDMETHOD(SetObject) (NcDbObject* &pObj)
	{
		if (pObj->objectId().isNull())
		{
			NullObjectId();
			m_objRef.acquire(pObj);
			return S_OK;
		}
		else
		{
			NcDbObjectId tmpId = pObj->objectId();
			return SetObjectId(tmpId);
		}
	}

	// Releases a wrapper instance from an object only if the wrapper is to
	// a non-database resident object
	STDMETHOD(GetObject)(NcDbObject* &pObj)
	{
		pObj = NULL;
		if (!m_objRef.objectId().isNull())
			return E_FAIL;

		NcDbObjectId tmpId;
		m_objRef.release(tmpId, pObj);
		//_ASSERTE(m_objId.isNull());
		//_ASSERTE(tmpId.isNull());
		return S_OK;
	}

	// Objects which support non-database resident instances should override
	// this method to return FALSE.
	STDMETHOD(ForceDbResident)(VARIANT_BOOL* forceDbResident)
	{
		if (NULL == forceDbResident)
			return E_POINTER;

		*forceDbResident = NCAX_VARIANT_TRUE;
		return S_OK;
	}

	// Objects which support non-database resident wrappers must implement this
	// method to allow non-database resident objects to be added to a database.
	STDMETHOD(AddToDb)(NcDbObjectId& objId, NcDbObjectId ownerId = NcDbObjectId::kNull, NCHAR* keyName = NULL)
	{
		return E_NOTIMPL;
	}

	// Objects which support non-database resident wrappers must implement this
	// method to allow non-database resident objects to be created.
	STDMETHOD(CreateObject)(NcDbObjectId ownerId = NcDbObjectId::kNull, NCHAR* keyName = NULL)
	{
		// Example implementation:
		//   releaseObject();
		//   NcDbLine *pLine = new NcDbLine();
		//   SetObject(pLine);
		// ...
		return E_NOTIMPL;
	}

	// Wrappers for non-database resident objects may have a reference to a
	// non-database resident object. This method allows callers to determine
	// if any object is actually being wrapped
	STDMETHOD(ObjectExists)(VARIANT_BOOL* objectExists)
	{
		if (NULL == objectExists)
			return E_POINTER;

		*objectExists = m_objRef.isNull() ? NCAX_VARIANT_FALSE : NCAX_VARIANT_TRUE;
		return S_OK;
	}

	STDMETHOD(OnModified)(DISPID dispId = DISPID_UNKNOWN)
	{
		Fire_Modified();
		Fire_OnChanged(dispId);
		return S_OK;
		//return E_NOTIMPL;
	}

protected:
	NcAxObjectRef m_objRef;

	// IAcadBaseObject override.
	// Capture the modified id in our object reference.
	virtual void ObjectIdModified()
	{
		releaseReference();
		m_objRef.acquire(m_objId);
	}

	// Derived classes which support non-database residency should call this
	// method from each of their "set" methods to notify connected listeners
	// that the property has changed. This is not necessary for
	// database-resident objects because AutoCAD's object and database reactors
	// fire the notification automatically.
	void Fire_Notification(DISPID dispId = DISPID_UNKNOWN)
	{
		if (m_objRef.objectId().isNull())
		{
			Fire_Modified();
			Fire_OnChanged(dispId);
		}
		//return E_NOTIMPL;
	}

	// Release the enclosed object reference, deleting the encapsulated
	// database object if it is not database resident
	STDMETHOD(releaseReference) ()
	{
		NcDbObjectId tmpId;
		NcDbObject*  pTmp = NULL;
		m_objRef.release(tmpId, pTmp);
		if (NULL != pTmp && pTmp->objectId().isNull())
			delete pTmp;
		return S_OK;
	}
};

template < class C, const CLSID* pclsid, class T, const IID* piid, const GUID* plibid,
           WORD wMajor = 1, WORD wMinor = 0, class tihclass = CComTypeInfoHolder >
class ATL_NO_VTABLE IAcadObjectDispatchImpl : public IDispatchImpl< T, piid, plibid, wMajor, wMinor, tihclass >,
	public IAcadBaseObject2Impl< C, pclsid >, public IRetrieveApplicationImpl
{
public:

	IAcadObjectDispatchImpl()
	{
		// ATL doesn't support multiple LCID's at the same time
		// Whatever LCID is queried for first is the one that is used.
		//_tih.EnsureTI(ncrxProductLCID());
	}

	virtual ~IAcadObjectDispatchImpl() {}

	STDMETHOD(get_Application)(LPDISPATCH* pVal)
	{
		return GetApplicationObject(pVal);
	}

	STDMETHOD(get_ObjectID)(LONG_PTR* pVal)
	{
		//*pVal = (long) m_objRef.objectId().asOldId();
		*pVal = m_objId.asOldId();
		return S_OK;
	}

	STDMETHOD(get_OwnerID)(LONG_PTR* pVal)
	{
		//return NcAxGetOwnerId(m_objRef, pVal);
		return NcAxGetOwnerId(m_objId, pVal);
	}

	STDMETHOD(Delete)()
	{
		//return NcAxErase(m_objRef);
		return NcAxErase(m_objId);
	}

	STDMETHOD(SetXData)(VARIANT type, VARIANT data)
	{
		//return NcAxSetXData(m_objRef, type, data);
		return NcAxSetXData(m_objId, type, data);
	}

	STDMETHOD(GetXData)(BSTR bstrName, VARIANT* type, VARIANT* data)
	{
		//return NcAxGetXData(m_objRef, bstrName, type, data);
		return NcAxGetXData(m_objId, bstrName, type, data);
	}

	STDMETHOD(get_ObjectName)(BSTR* pVal)
	{
		//return NcAxGetObjectName(m_objRef, pVal);
		return NcAxGetObjectName(m_objId, pVal);
	}

	STDMETHOD(get_Handle)(BSTR* pVal)
	{
		//return NcAxGetHandle(m_objRef, pVal);
		return NcAxGetHandle(m_objId, pVal);
	}

	STDMETHOD(get_HasExtensionDictionary)(VARIANT_BOOL* bHasDictionary)
	{
		//return NcAxHasExtensionDictionary(m_objRef, bHasDictionary);
		return NcAxHasExtensionDictionary(m_objId, bHasDictionary);
	}

	STDMETHOD(GetExtensionDictionary)(IAcadDictionary** pExtDictionary)
	{
		//return NcAxGetExtensionDictionary(m_objRef, m_App, pExtDictionary);
		return NcAxGetExtensionDictionary(m_objId, m_App, pExtDictionary);
	}

	STDMETHOD(get_Database)(IAcadDatabase** pDatabase)
	{
		//if(m_objRef.objectId() == NcDbObjectId::kNull || m_objRef.objectId().database() == NULL)
		if (m_objId == NcDbObjectId::kNull || m_objId.database() == NULL)
		{
			//return RaiseArxException(*piid, 0, Nano::eNoDatabase);
			return S_FALSE;
		}

		CComPtr< IDispatch > pDispatch;
		//HRESULT hr = NcAxGetDatabase(m_objRef.objectId().database(), m_App, &pDispatch);
		HRESULT              hr = NcAxGetDatabase(m_objId.database(), m_App, &pDispatch);

		if (SUCCEEDED(hr))
		{
			hr = pDispatch->QueryInterface(__uuidof(IAcadDatabase), reinterpret_cast< LPVOID* >(pDatabase));
		}

		return hr;
	}

	STDMETHOD(get_Document)(LPDISPATCH* pDocument)
	{
		//if(m_objRef.objectId() == NcDbObjectId::kNull || m_objRef.objectId().database() == NULL)
		/*if(m_objId == NcDbObjectId::kNull || m_objId.database() == NULL)
		{
		  //return RaiseArxException(*piid, 0, Nano::eNoDatabase);
		  return S_FALSE;
		}

		NcAxOleLinkManager* pOleLinkManager = NcAxGetOleLinkManager();
		//_ASSERTE(pOleLinkManager != NULL);
		  if (pOleLinkManager == NULL)
		  return S_FALSE;

		//*pDocument = pOleLinkManager->GetDocIDispatch(m_objRef.objectId().database());
		*pDocument = pOleLinkManager->GetDocIDispatch(m_objId.database());
		if(*pDocument == NULL)
		{
		  //return RaiseArxException(*piid, 0, Nano::eNoDocument);
		  return S_FALSE;
		}
		  (*pDocument)->AddRef();

		return S_OK;*/
		return E_NOTIMPL;
	}

	//
	// Provided for backwards compatibility; for future coding
	// use call Delete() instead of Erase()
	//
	STDMETHOD(Erase) ()
	{
		return Delete();
	}

};

template < class C, const CLSID* pclsid, class T, const IID* piid, const GUID* plibid,
           WORD wMajor = 1, WORD wMinor = 0, class tihclass = CComTypeInfoHolder >
class ATL_NO_VTABLE IAcadEntityDispatchImpl : public IAcadObjectDispatchImpl< C, pclsid, T, piid, plibid, wMajor, wMinor,
	                                                                          tihclass >
{
public:

	STDMETHODIMP get_color(AcColor* pVal)
	{
		//return NcAxGetColor(m_objRef, pVal);
		return NcAxGetColor(m_objId, pVal);
	}

	STDMETHODIMP put_color(AcColor newVal)
	{
		//return NcAxPutColor(m_objRef, newVal);
		return NcAxPutColor(m_objId, newVal);
	}

	STDMETHODIMP get_TrueColor(IAcadAcCmColor** pColor)
	{
		//return NcAxGetTrueColor(m_objRef, pColor);
		return NcAxGetTrueColor(m_objId, pColor);
	}

	STDMETHODIMP put_TrueColor(IAcadAcCmColor* color)
	{
		//return NcAxPutTrueColor(m_objRef, color);
		return NcAxPutTrueColor(m_objId, color);
	}

	STDMETHODIMP get_Layer(BSTR* pVal)
	{
		//return NcAxGetLayer(m_objRef, pVal);
		return NcAxGetLayer(m_objId, pVal);
	}

	STDMETHODIMP put_Layer(BSTR newVal)
	{
		//return NcAxPutLayer(m_objRef, newVal);
		return NcAxPutLayer(m_objId, newVal);
	}

	STDMETHODIMP get_Linetype(BSTR* pVal)
	{
		//return NcAxGetLinetype(m_objRef, pVal);
		return NcAxGetLinetype(m_objId, pVal);
	}

	STDMETHODIMP put_Linetype(BSTR newVal)
	{
		//return NcAxPutLinetype(m_objRef, newVal);
		return NcAxPutLinetype(m_objId, newVal);
	}

	STDMETHODIMP get_Material(BSTR* pVal)
	{
		//return NcAxGetMaterial(m_objRef, pVal);
		return E_NOTIMPL;
	}

	STDMETHODIMP put_Material(BSTR newVal)
	{
		//return NcAxPutMaterial(m_objRef, newVal);
		return E_NOTIMPL;
	}

	STDMETHODIMP get_LinetypeScale(double* pVal)
	{
		//return NcAxGetLinetypeScale(m_objRef, pVal);
		return NcAxGetLinetypeScale(m_objId, pVal);
	}

	STDMETHODIMP put_LinetypeScale(double newVal)
	{
		//return NcAxPutLinetypeScale(m_objRef, newVal);
		return NcAxPutLinetypeScale(m_objId, newVal);
	}

	STDMETHODIMP get_Visible(VARIANT_BOOL* pVal)
	{
		//return NcAxGetVisible(m_objRef, pVal);
		return NcAxGetVisible(m_objId, pVal);
	}

	STDMETHODIMP put_Visible(VARIANT_BOOL newVal)
	{
		//return NcAxPutVisible(m_objRef, newVal);
		return NcAxPutVisible(m_objId, newVal);
	}

	STDMETHODIMP ArrayPolar(int numObjs, double fillAngle, VARIANT basePoint, VARIANT* pArrayObjs)
	{
		//return NcAxArrayPolar(m_objRef, m_App, numObjs, fillAngle, basePoint, pArrayObjs);
		return NcAxArrayPolar(m_objId, m_App, numObjs, fillAngle, basePoint, pArrayObjs);
	}

	STDMETHODIMP ArrayRectangular(int numRows, int numCols, int numLvls, double disRows, double disCols, double disLvls,
	                              VARIANT* pArrayObjs)
	{
		//return NcAxArrayRectangular(m_objRef, m_App, numRows, numCols, numLvls, disRows, disCols, disLvls, pArrayObjs);
		return NcAxArrayRectangular(m_objId, m_App, numRows, numCols, numLvls, disRows, disCols, disLvls, pArrayObjs);
	}

	STDMETHODIMP Highlight(VARIANT_BOOL bFlag)
	{
		//return NcAxHighlight(m_objRef, bFlag);
		return NcAxHighlight(m_objId, bFlag);
	}

	STDMETHODIMP Copy(LPDISPATCH* pCopyObj)
	{
		//return NcAxCopy(m_objRef, m_App, pCopyObj);
		return NcAxCopy(m_objId, m_App, pCopyObj);
	}

	STDMETHODIMP Move(VARIANT fromPoint, VARIANT toPoint)
	{
		//return NcAxMove(m_objRef, fromPoint, toPoint);
		return NcAxMove(m_objId, fromPoint, toPoint);
	}

	STDMETHODIMP Rotate(VARIANT basePoint, double rotationAngle)
	{
		//return NcAxRotate(m_objRef, basePoint, rotationAngle);
		return NcAxRotate(m_objId, basePoint, rotationAngle);
	}

	STDMETHODIMP Rotate3D(VARIANT point1, VARIANT point2, double rotationAngle)
	{
		//return NcAxRotate3D(m_objRef, point1, point2, rotationAngle);
		return NcAxRotate3D(m_objId, point1, point2, rotationAngle);
	}

	STDMETHODIMP Mirror(VARIANT point1, VARIANT point2, LPDISPATCH* pMirrorObj)
	{
		//return NcAxMirror(m_objRef, m_App, point1, point2, pMirrorObj);
		return NcAxMirror(m_objId, m_App, point1, point2, pMirrorObj);
	}

	STDMETHODIMP Mirror3D(VARIANT point1, VARIANT point2, VARIANT point3, LPDISPATCH* pMirrorObj)
	{
		//return NcAxMirror3D(m_objRef, m_App, point1, point2, point3, pMirrorObj);
		return NcAxMirror3D(m_objId, m_App, point1, point2, point3, pMirrorObj);
	}

	STDMETHODIMP ScaleEntity(VARIANT basePoint, double scaleFactor)
	{
		//return NcAxScaleEntity(m_objRef, basePoint, scaleFactor);
		return NcAxScaleEntity(m_objId, basePoint, scaleFactor);
	}

	STDMETHODIMP TransformBy(VARIANT transMatrix)
	{
		//return NcAxTransformBy(m_objRef, transMatrix);
		return NcAxTransformBy(m_objId, transMatrix);
	}

	STDMETHODIMP Update()
	{
		//return NcAxUpdate(m_objRef);
		return NcAxUpdate(m_objId);
	}

	STDMETHODIMP GetBoundingBox(VARIANT* minPoint, VARIANT* maxPoint)
	{
		//return NcAxGetBoundingBox(m_objRef, minPoint, maxPoint);
		return NcAxGetBoundingBox(m_objId, minPoint, maxPoint);
	}

	STDMETHODIMP IntersectWith(LPDISPATCH pEntity, AcExtendOption option, VARIANT* intPoints)
	{
		//return NcAxIntersectWith(m_objRef, pEntity, option, intPoints);
		return NcAxIntersectWith(m_objId, pEntity, option, intPoints);
	}

	STDMETHODIMP get_PlotStyleName(BSTR* plotStyleName)
	{
		return NcAxGetPlotStyleName(m_objId, plotStyleName);
		//return NcAxGetPlotStyleName(m_objRef, plotStyleName);
	}

	STDMETHODIMP put_PlotStyleName(BSTR plotStyleName)
	{
		//return NcAxPutPlotStyleName(m_objRef, plotStyleName);
		return NcAxPutPlotStyleName(m_objId, plotStyleName);
	}

	STDMETHODIMP get_Lineweight(ACAD_LWEIGHT* lineweight)
	{
		//return NcAxGetLineWeight(m_objRef, lineweight);
		return NcAxGetLineWeight(m_objId, lineweight);
	}

	STDMETHODIMP put_Lineweight(ACAD_LWEIGHT lineweight)
	{
		//return NcAxPutLineWeight(m_objRef, lineweight);
		return NcAxPutLineWeight(m_objId, lineweight);
	}

	STDMETHODIMP get_Hyperlinks(IAcadHyperlinks** pHyperlinks)
	{
		//return NcAxGetHyperlinks(m_objRef, m_App, pHyperlinks);
		return NcAxGetHyperlinks(m_objId, m_App, pHyperlinks);
	}

	//
	// Provided for backwards compatibility; for future coding
	// use call ObjectName() instead of EntityName()
	//
	STDMETHOD(get_EntityName)(BSTR* pVal)
	{
		//return NcAxGetObjectName(m_objRef, pVal);
		return NcAxGetObjectName(m_objId, pVal);
	}

	//
	// Provided for backwards compatibility; for future coding
	// use QueryInterface() to determine object type. In VB,
	// the TypeOf function can be used.
	//
	STDMETHOD(get_EntityType)(long* /*entType*/)
	{
		return E_NOTIMPL;
	}
};

// IAcadBaseSubEntity
template <class C, const CLSID* pclsid, class T, const IID* piid,
	const GUID* plibid,
	WORD wMajor = 1, WORD wMinor = 0, class tihclass = CComTypeInfoHolder>
class ATL_NO_VTABLE IAcadBaseSubEntityImpl : 
	public IDispatchImpl<T, piid, plibid, wMajor, wMinor, tihclass>,
	public IAcadBaseSubEntity,
	public IRetrieveApplicationImpl,
	public IConnectionPointContainerImpl<C>,
	public CProxy_AcadObjectEvents<C>,
	public CProxy_PropertyNotifySink<C>
{
public:
	IAcadBaseSubEntityImpl()
	{
	}
	//
	// TODO: MGraf - Addressing the link manager to follow.
	// I expect this mechanism to fall apart with the mutliple select situation,
	// but I'm moving forward with implementation for now.
	virtual ~IAcadBaseSubEntityImpl()
	{
		// unregister ourself with the link manager (mimic IAcadBaseObjectImpl)
		if (!m_objId.isValid())
			return;

		NcDbObjectPointer<NcDbObject> pObject(m_objId, NcDb::kForRead, NRX::kTrue);
		if (pObject.openStatus() != Nano::eOk)
		{
			NcDbObject* pTemp;
			if (Nano::eOk != ncdbOpenObject(pTemp, m_objId, NcDb::kForNotify, NRX::kTrue))
			{
				return; 
			}
			pObject.acquire(pTemp);
		}
	}

	STDMETHOD(OnModified)()
	{
		Fire_Modified();
		Fire_OnChanged();
		return S_OK;
	}

	STDMETHOD(SetFullSubEntPath)(NcDbFullSubentPath& subentPath)
	{
		m_subentPath = subentPath;
		NcDbObjectIdArray objectIds = m_subentPath.objectIds();
		if (0 != objectIds.length())
			m_objId = objectIds[objectIds.length() - 1];
		return S_OK;
	}

	STDMETHOD(GetFullSubEntPath)(NcDbFullSubentPath* subentPath)
	{
		*subentPath = m_subentPath;
		return S_OK;
	}

	STDMETHOD(GetClassID)(CLSID& clsid) 
	{
		clsid = *pclsid;
		return S_OK;
	}

	STDMETHOD(get_ObjectName)(BSTR *pVal)
	{
		return NcAxGetObjectName(m_objId, pVal);
	}
	STDMETHODIMP get_Color(IAcadAcCmColor** pColor)
	{
		return NcAxGetTrueColor(m_objId, pColor);
	}
	STDMETHODIMP get_Layer(BSTR * pVal)
	{
		return NcAxGetLayer(m_objId, pVal);
	}
	STDMETHODIMP get_Linetype(BSTR * pVal)
	{
		return NcAxGetLinetype(m_objId, pVal);
	}
	STDMETHODIMP get_LinetypeScale(double * pVal)
	{
		return NcAxGetLinetypeScale(m_objId, pVal);
	}
	STDMETHODIMP get_PlotStyleName(BSTR* plotStyleName)
	{
		return NcAxGetPlotStyleName(m_objId, plotStyleName);
	}
	STDMETHODIMP get_Lineweight(ACAD_LWEIGHT* lineweight)
	{
		return NcAxGetLineWeight(m_objId, lineweight);
	}
	STDMETHODIMP get_Hyperlinks(IAcadHyperlinks** pHyperlinks)
	{
		return NcAxGetHyperlinks(m_objId, m_App, pHyperlinks);
	}

	// IConnectionPointContainerImpl
	BEGIN_CONNECTION_POINT_MAP(C)
		CONNECTION_POINT_ENTRY(__uuidof(IAcadObjectEvents))
		CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	END_CONNECTION_POINT_MAP()

protected:
	STDMETHODIMP parentObjectId(NcDbObjectId &objID)
	{
		NcDbObjectIdArray objectIds = m_subentPath.objectIds();
		if (0 != objectIds.length()) {
			objID = objectIds[objectIds.length() - 1];
			return S_OK;
		}
		return E_FAIL;
	}
	NcDbFullSubentPath m_subentPath;
	NcDbObjectId m_objId;
};


template<class T>
class ATL_NO_VTABLE IOPMPropertyExtensionImpl : public ICategorizeProperties,
                                                public IPerPropertyBrowsing,
                                                public IOPMPropertyExtension
{
public:
	typedef IOPMPropertyExtensionImpl<T> t_basePropertyExtensionImpl;
	IOPMPropertyExtensionImpl()
	{
	}

	virtual ~IOPMPropertyExtensionImpl()
	{
	}

	virtual HINSTANCE GetResourceInstance() = 0;

	// ICategorizeProperties methods
	STDMETHODIMP MapPropertyToCategory(DISPID dispid, PROPCAT* ppropcat)
	{
		return NcOpmMapPropertyToCategory(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispid, ppropcat);
	}
	STDMETHODIMP GetCategoryName(PROPCAT propcat, LCID lcid, BSTR* pbstrName)
	{
		return NcOpmGetCategoryName(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), T::GetOPMPropertyMap(), propcat, lcid, pbstrName);
	}

	// IPerPropertyBrowsing methods
	STDMETHODIMP GetDisplayString(DISPID dispID, BSTR *pBstr)
	{
		return NcOpmGetDisplayString(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispID, pBstr);
	}

	STDMETHODIMP MapPropertyToPage(DISPID dispID, CLSID *pClsid)
	{
		return NcOpmMapPropertyToPage(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispID, pClsid);
	}

	STDMETHODIMP GetPredefinedStrings(DISPID dispID, CALPOLESTR *pCaStringsOut, CADWORD *pCaCookiesOut)
	{
		return NcOpmGetPredefinedStrings(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), T::GetOPMPropertyMap(), dispID, pCaStringsOut, pCaCookiesOut);
	}

	STDMETHODIMP GetPredefinedValue(DISPID dispID, DWORD dwCookie, VARIANT *pVarOut)
	{
		return NcOpmGetPredefinedValue(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispID, dwCookie, pVarOut);
	}

	// IOPMPropertyExtension methods
	STDMETHODIMP GetDisplayName(DISPID dispID, BSTR *pBstr)
	{
		return NcOpmGetDisplayName(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), T::GetOPMPropertyMap(), dispID, pBstr);
	}

	STDMETHODIMP Editable(/* [in] */ DISPID dispID, /* [out] */ BOOL __RPC_FAR *bEditable)
	{
		return NcOpmEditable(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispID, bEditable);
	}

	STDMETHODIMP ShowProperty(/* [in] */ DISPID dispID, /* [out] */ BOOL *pShow)
	{
		return NcOpmShowProperty(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispID, pShow);
	}
};

template < class T >
class ATL_NO_VTABLE IOPMPropertyExtensionImpl2 : public IPerPropertyBrowsing, public IOPMPropertyExtension
{
public:
	IOPMPropertyExtensionImpl2() {}

	virtual ~IOPMPropertyExtensionImpl2() {}

	virtual HINSTANCE GetResourceInstance() = 0;

	// IPerPropertyBrowsing methods
	STDMETHODIMP GetDisplayString(DISPID dispID, BSTR* pBstr)
	{
		return NcOpmGetDisplayString(reinterpret_cast< IUnknown* >(this), T::GetOPMPropertyMap(), dispID, pBstr);
	}

	STDMETHODIMP MapPropertyToPage(DISPID dispID, CLSID* pClsid)
	{
		return NcOpmMapPropertyToPage(reinterpret_cast< IUnknown* >(this), T::GetOPMPropertyMap(), dispID, pClsid);
	}

	STDMETHODIMP GetPredefinedStrings(DISPID dispID, CALPOLESTR* pCaStringsOut, CADWORD* pCaCookiesOut)
	{
		return NcOpmGetPredefinedStrings(reinterpret_cast< IUnknown* >(this), GetResourceInstance(),
		                                 T::GetOPMPropertyMap(), dispID, pCaStringsOut, pCaCookiesOut);
	}

	STDMETHODIMP GetPredefinedValue(DISPID dispID, DWORD dwCookie, VARIANT* pVarOut)
	{
		return NcOpmGetPredefinedValue(reinterpret_cast< IUnknown* >(this), T::GetOPMPropertyMap(), dispID, dwCookie,
		                               pVarOut);
	}

	// IOPMPropertyExtension methods
	STDMETHODIMP GetDisplayName(DISPID dispID, BSTR* pBstr)
	{
		return NcOpmGetDisplayName(reinterpret_cast< IUnknown* >(this), GetResourceInstance(), T::GetOPMPropertyMap(),
		                           dispID, pBstr);
	}

	STDMETHODIMP Editable(
	        /* [in] */ DISPID dispID,
	        /* [out] */ BOOL __RPC_FAR* bEditable)
	{
		return NcOpmEditable(reinterpret_cast< IUnknown* >(this), T::GetOPMPropertyMap(), dispID, bEditable);
	}

	STDMETHODIMP ShowProperty(
	        /* [in] */ DISPID dispID,
	        /* [out] */ BOOL* pShow)
	{
		return NcOpmShowProperty(reinterpret_cast< IUnknown* >(this), T::GetOPMPropertyMap(), dispID, pShow);
	}
};

DEFINE_GUID(IID_IAcPiCategorizeProperties, 0x8590b992, 0xd9a1, 0x48d1, 0x89, 0x9a, 0x35, 0x8d, 0x77, 0xe1, 0x51, 0x2a);

interface DECLSPEC_UUID("8590b992-d9a1-48d1-899a-358d77e1512a")
IAcPiCategorizeProperties : public IUnknown
{
public:
	/* IUnknown methods */
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	/* IAcPiCategorizeProperties methods */
	STDMETHOD(MapPropertyToCategory)(THIS_ DISPID dispID, int *pCatID) PURE;
	STDMETHOD(GetCategoryName)(THIS_ int CatID, LCID lCid, BSTR *pCategoryName) PURE;
	STDMETHOD(GetCategoryDescription)(THIS_ int CatID, LCID lCid, BSTR *pCategoryDescription) PURE;
	STDMETHOD(GetCategoryWeight)(THIS_ int CatID, long *pCategoryWeight) PURE;
	STDMETHOD(GetParentCategory)(THIS_ int CatID, int *pParentCatID) PURE;
	STDMETHOD(GetUniqueID)(THIS_ BSTR *pVal) PURE;
	STDMETHOD(GetCommandButtons)(THIS_ int CatID, VARIANT *pCatCmdBtns) PURE;
};

#define ICategorizeProperties2Impl  IAcPiCategorizePropertiesImpl

template < class T >
class ATL_NO_VTABLE IAcPiCategorizePropertiesImpl : public IAcPiCategorizeProperties
{
public:
	CATEGORY_VECTOR  m_CategoryVector;
	CATCMDBTN_VECTOR m_CatCmdBtnVector;

	CATEGORY_VECTOR& GetCategoryVector()
	{
		return m_CategoryVector;
	}

	CATCMDBTN_VECTOR& GetCmdBtnVector()
	{
		return m_CatCmdBtnVector;
	}

	bool IsDefaultCategoryEntry(CATEGORY_ENTRY in)
	{
		if (in.m_CatID != -1)
			return false;

		if (in.m_nWeight != -1)
			return false;

		if (in.m_ParentCatID != -1)
			return false;

		if (in.m_nDescId != 0)
			return false;

		if (in.m_nNameId != 0)
			return false;

		return true;
	}

	bool IsDefaultCmdBtnEntry(CATCMDBTN_ENTRY in)
	{
		if (in.m_CatID != -1)
			return false;

		if (in.m_lpEnBtnBmpRes != NULL)
			return false;

		if (in.m_nEnBtnBmpType != PICTYPE_UNINITIALIZED)
			return false;

		if (in.m_lpDisBtnBmpRes != NULL)
			return false;

		if (in.m_nDisBtnBmpType != PICTYPE_UNINITIALIZED)
			return false;

		if (in.m_nStyle != NULL)
			return false;

		if (in.m_pfnBtnProc != NULL)
			return false;

		if (in.m_nBtnNameId != 0)
			return false;

		return true;
	}

	IAcPiCategorizePropertiesImpl()
	{
		m_CatCmdBtnVector.clear();
		m_CategoryVector.clear();
		int i = 0;
		while (!IsDefaultCmdBtnEntry(T::GetCmdBtnArray()[i]))
		{
			m_CatCmdBtnVector.push_back(T::GetCmdBtnArray()[i]);
			i++;
		}

		i = 0;
		while (!IsDefaultCategoryEntry(T::GetCatArray()[i]))
		{
			m_CategoryVector.push_back(T::GetCatArray()[i]);
			i++;
		}
	}

	virtual ~IAcPiCategorizePropertiesImpl() {}

	virtual HINSTANCE GetResourceInstance() = 0;

	// IAcPiCategorizeProperties methods
	STDMETHODIMP MapPropertyToCategory(DISPID dispid, PROPCAT* ppropcat)
	{
		return NcOpmMapPropertyToCategory(reinterpret_cast< IUnknown* >(this), T::GetOPMPropertyMap(), dispid, ppropcat);
	}

	STDMETHODIMP GetCategoryName(PROPCAT propcat, LCID lcid, BSTR* pbstrName)
	{
		HRESULT hr;
		hr = NcOpmGetCategoryName(reinterpret_cast< IUnknown* >(this), GetResourceInstance(), T::GetOPMPropertyMap(),
		                          propcat, lcid, pbstrName);
		if (hr == S_FALSE)
		{
			hr = NcOpmGetCategoryName(reinterpret_cast< IUnknown* >(this), GetResourceInstance(), GetCategoryVector(),
			                          propcat, lcid, pbstrName);
		}
		return hr;
	}

	STDMETHODIMP GetCategoryDescription(PROPCAT propcat, LCID lcid, BSTR* pbstrDesc)
	{
		return NcOpmGetCategoryDescription(reinterpret_cast< IUnknown* >(this), GetResourceInstance(),
		                                   GetCategoryVector(), propcat, lcid, pbstrDesc);
	}

	STDMETHODIMP GetCategoryWeight(PROPCAT CatID, long* pCategoryWeight)
	{
		return NcOpmGetCategoryWeight(reinterpret_cast< IUnknown* >(this), GetCategoryVector(), CatID, pCategoryWeight);
	}

	STDMETHODIMP GetParentCategory(PROPCAT CatID, PROPCAT* pParentCatID)
	{
		return NcOpmGetParentCategory(reinterpret_cast< IUnknown* >(this), GetCategoryVector(), CatID, pParentCatID);
	}

	STDMETHODIMP GetCommandButtons(PROPCAT CatID, VARIANT* pCatCmdBtns)
	{
		return NcOpmGetCategoryCommandButtons(reinterpret_cast< IUnknown* >(this), GetResourceInstance(),
		                                      GetCmdBtnVector(), CatID, pCatCmdBtns);
	}
};

DEFINE_GUID(IID_IOPMPropertyDialog, 0x8B384029, 0xACB0, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);
interface DECLSPEC_UUID("8B384029-ACB0-11D1-A2B4-080009DC639A") IOPMPropertyDialog : public IUnknown
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IOPMPropertyDialog methods ***
	STDMETHOD(DoModal)(THIS_ BSTR* propValueString, NcDbObjectIdArray* ObjectIdArray) PURE;
};

template<class T>
class ATL_NO_VTABLE IAcPiPropCommandButtonsImpl : public IAcPiPropCommandButtons
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

	IAcPiPropCommandButtonsImpl()
	{
		m_CmdBtnVector.clear();
		int i=0;
		while (!IsDefaultCmdBtnEntry(T::GetPropCmdBtnArray()[i]))
		{
			m_CmdBtnVector.push_back(T::GetPropCmdBtnArray()[i]);
			i++;
		}
	}
	virtual ~IAcPiPropCommandButtonsImpl() {}

	virtual HINSTANCE GetResourceInstance() = 0;

	// IAcPiPropCommandButtons methods
	STDMETHODIMP GetButtons(VARIANT *pCmdBtns)
	{
		return NcOpmGetCommandButtons(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), GetCmdBtnVector(), pCmdBtns);
	}
};

#define IPerPropertyDisplay IAcPiPropertyDisplay
#define IID_IPerPropertyDisplay IID_IAcPiPropertyDisplay

DEFINE_GUID(IID_IAcPiPropertyDisplay, 0x6A0D7861, 0x8773, 0x4D56, 0xAC, 0x16, 0x95, 0xAF, 0xF3, 0x05, 0x1E, 0xBD);

interface DECLSPEC_UUID("6A0D7861-8773-4D56-AC16-95AFF3051EBD")
IAcPiPropertyDisplay : public IUnknown
{
public:
	/* IUnknown methods */
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	/* IAcPiPropertyDisplay methods */
	STDMETHOD(GetCustomPropertyCtrl)(THIS_ VARIANT Id, LCID lcid, BSTR *pProgId) PURE;
	STDMETHOD(GetPropertyIcon)(THIS_ VARIANT Id, IUnknown **pIcon) PURE;
	STDMETHOD(GetPropTextColor)(THIS_ VARIANT Id, OLE_COLOR *pTextColor) PURE;
	STDMETHOD(IsFullView)(THIS_ VARIANT Id, VARIANT_BOOL *pbVisible,
	                      DWORD *pIntegralHeight) PURE;
	STDMETHOD(GetPropertyWeight)(THIS_ VARIANT Id, long *pPropertyWeight) PURE;

};

#define IPerPropertyDisplayImpl IAcPiPropertyDisplayImpl

template<class T>
class ATL_NO_VTABLE IAcPiPropertyDisplayImpl :
	public IAcPiPropertyDisplay
{
public:
	PROP_DISP_VECTOR m_PropDispVector;

	PROP_DISP_VECTOR & GetPerPropDisplayVector()
	{
		return m_PropDispVector;
	}
	bool IsDefaultPerPropDispEntry(PER_PROP_DISP_ENTRY in)
	{
		if(in.m_bFullView != false)
			return false;

		if(in.m_ProgID != NULL)
			return false;

		if(in.m_dispid != -1)
			return false;

		if(in.m_dwIntegralHeight != -1)
			return false;

		if(in.m_lpEllipsisBmpRes != NULL)
			return false;

		if(in.m_nEllipsisBmpType != PICTYPE_UNINITIALIZED)
			return false;

		if(in.m_lpLeftIconRes != NULL)
			return false;

		if(in.m_nLeftIconType != PICTYPE_UNINITIALIZED)
			return false;

		if(in.m_nWeight != -1)
			return false;

		if(in.m_TextColor != 0x80000008)
			return false;

		return true;
	}

	IAcPiPropertyDisplayImpl()
	{
		m_PropDispVector.clear();
		int i=0;
		while(!IsDefaultPerPropDispEntry(T::GetPerPropDisplayArray()[i]))
		{
			m_PropDispVector.push_back(T::GetPerPropDisplayArray()[i]);
			i++;
		}
	}

	virtual ~IAcPiPropertyDisplayImpl()
	{
	}

	virtual HINSTANCE GetResourceInstance() = 0;

	// IAcPiPropertyDisplay methods
	STDMETHODIMP GetCustomPropertyCtrl(VARIANT Id, LCID lcid, BSTR *psProgId)
	{
		return NcOpmGetCustomPropertyCtrl(reinterpret_cast<IUnknown*>(this), GetPerPropDisplayVector(), Id, lcid, psProgId);
	}

	STDMETHODIMP GetPropertyIcon(VARIANT Id, IUnknown **ppIcon)
	{
		return NcOpmGetPropertyIcon(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), GetPerPropDisplayVector(), Id, ppIcon);
	}

	STDMETHODIMP GetPropTextColor(VARIANT Id, OLE_COLOR *pTextColor)
	{
		return NcOpmGetPropTextColor(reinterpret_cast<IUnknown*>(this), GetPerPropDisplayVector(), Id, pTextColor);
	}

	STDMETHODIMP IsFullView(VARIANT Id, VARIANT_BOOL *pbVisible, DWORD *pIntegralHeight)
	{
		return NcOpmIsPropFullView(reinterpret_cast<IUnknown*>(this), GetPerPropDisplayVector(), Id, pbVisible, pIntegralHeight);
	}

	STDMETHODIMP GetPropertyWeight(VARIANT Id, long *pPropertyWeight)
	{
		return NcOpmGetPropertyWeight(reinterpret_cast<IUnknown*>(this), GetPerPropDisplayVector(), Id, pPropertyWeight);
	}
};

#endif // __OPENDWG_AXTEMPL_H__
