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

#ifndef __OPENDWG_AXUTILS_H__
#define __OPENDWG_AXUTILS_H__
#include "geometry.h"
#include "objectid.h"
#include "database.h"
#include "typesDb.h"
#include "nrxdbgate_impexp.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common object/entity helper functions
NRXDBGATE_EXPORT HRESULT NcAxGetShadowDisplay(NcDbObjectId& id, AcShadowDisplayType* type);
NRXDBGATE_EXPORT HRESULT NcAxPutShadowDisplay(NcDbObjectId& id, AcShadowDisplayType type);
NRXDBGATE_EXPORT HRESULT NcAxEnableShadowDisplay(NcDbObjectId& id, bool* enabled);

NRXDBGATE_EXPORT HRESULT NcAxGetMaterial(NcDbObjectId& id, BSTR* material);
NRXDBGATE_EXPORT HRESULT NcAxPutMaterial(NcDbObjectId& id, BSTR material);

NRXDBGATE_EXPORT HRESULT NcAxGetIUnknownOfObject(LPUNKNOWN* unknown, NcDbObjectId& id, LPDISPATCH application);
NRXDBGATE_EXPORT HRESULT NcAxGetIUnknownOfObject(LPUNKNOWN* unknown, NcDbObject* object, LPDISPATCH application);
#if defined(_WIN64) || defined(WIN64)
NRX::Int32 NRXDBGATE_EXPORT NcAxGetObjectId32(const NRX::IntDbId& objId);
NRX::IntDbId NRXDBGATE_EXPORT NcAxGetObjectId64(const NRX::Int32& objId);
#endif

//***************************************************************************************************************
class NRXDBGATE_EXPORT NcAxPoint2d : public NcGePoint2d
{
public:
	// constructors
	NcAxPoint2d();
	NcAxPoint2d(double x, double y);
	NcAxPoint2d(const NcGePoint2d& pt);
//FIXME:	NcAxPoint2d(const OdGePoint2d& pt);
	NcAxPoint2d(const NcGeVector2d& pt);
	NcAxPoint2d(const VARIANT* var) throw(HRESULT);
	NcAxPoint2d(const VARIANT& var) throw(HRESULT);
	NcAxPoint2d(const SAFEARRAY* safeArrayPt) throw(HRESULT);

	// equal operators
	NcAxPoint2d& operator=(const NcGePoint2d& pt);
	NcAxPoint2d& operator=(const NcGeVector2d& pt);
	NcAxPoint2d& operator=(const VARIANT* var) throw(HRESULT);
	NcAxPoint2d& operator=(const VARIANT& var) throw(HRESULT);
	NcAxPoint2d& operator=(const SAFEARRAY* safeArrayPt) throw(HRESULT);

	// type requests
	VARIANT* asVariantPtr() const throw(HRESULT);
	SAFEARRAY* asSafeArrayPtr() const throw(HRESULT);

	VARIANT& setVariant(VARIANT& var) const throw(HRESULT);
	VARIANT* setVariant(VARIANT* var) const throw(HRESULT);

	// utilities
private:
	NcAxPoint2d& fromSafeArray(const SAFEARRAY* safeArrayPt) throw(HRESULT);
};

//***************************************************************************************************************
class NRXDBGATE_EXPORT NcAxPoint3d : public NcGePoint3d
{
public:
	// constructors
	NcAxPoint3d();
	NcAxPoint3d(double x, double y, double z);
	NcAxPoint3d(const NcGePoint3d& pt);
//FIXME:	NcAxPoint3d(const OdGePoint3d& pt);
	NcAxPoint3d(const NcGeVector3d& pt);
	NcAxPoint3d(const VARIANT* var) throw(HRESULT);
	NcAxPoint3d(const VARIANT& var) throw(HRESULT);
	NcAxPoint3d(const SAFEARRAY* safeArrayPt) throw(HRESULT);

	// equal operators
	NcAxPoint3d& operator=(const NcGePoint3d& pt);
	NcAxPoint3d& operator=(const NcGeVector3d& pt);
	NcAxPoint3d& operator=(const VARIANT* var) throw(HRESULT);
	NcAxPoint3d& operator=(const VARIANT& var) throw(HRESULT);
	NcAxPoint3d& operator=(const SAFEARRAY* safeArrayPt) throw(HRESULT);

	// type requests
	VARIANT* asVariantPtr() const throw(HRESULT);
	SAFEARRAY* asSafeArrayPtr() const throw(HRESULT);

	VARIANT& setVariant(VARIANT& var) const throw(HRESULT);
	VARIANT* setVariant(VARIANT* var) const throw(HRESULT);

	// utilities
private:
	NcAxPoint3d& fromSafeArray(const SAFEARRAY* safeArrayPt) throw(HRESULT);
};

//////////////////////////////////////////////////////////////////////////
// NcAxPoint2dArray
class NRXDBGATE_EXPORT NcAxPoint2dArray : public NcGePoint2dArray {
public:
	NcAxPoint2dArray& append(const NcGePoint2d& pt) throw(HRESULT);
	NcAxPoint2dArray& append(const VARIANT* var) throw(HRESULT);
	NcAxPoint2dArray& append(const VARIANT& var) throw(HRESULT);
	NcAxPoint2dArray& append(const SAFEARRAY* safeArrayPt) throw(HRESULT);
	SAFEARRAY* asSafeArrayPtr() const throw(HRESULT);
	VARIANT& setVariant(VARIANT& var) const throw(HRESULT);
	VARIANT* setVariant(VARIANT* var) const throw(HRESULT);
private:
	NcAxPoint2dArray& fromSafeArray(const SAFEARRAY* safeArrayPt) throw(HRESULT);
};

//////////////////////////////////////////////////////////////////////////
// NcAxPoint3dArray
class NRXDBGATE_EXPORT NcAxPoint3dArray : public NcGePoint3dArray {
public:
	NcAxPoint3dArray& append(const NcGePoint3d& pt) throw(HRESULT);
	NcAxPoint3dArray& append(const VARIANT* var) throw(HRESULT);
	NcAxPoint3dArray& append(const VARIANT& var) throw(HRESULT);
	NcAxPoint3dArray& append(const SAFEARRAY* safeArrayPt) throw(HRESULT);
	SAFEARRAY* asSafeArrayPtr() const throw(HRESULT);
	VARIANT& setVariant(VARIANT& var) const throw(HRESULT);
	VARIANT* setVariant(VARIANT* var) const throw(HRESULT);
private:
	NcAxPoint3dArray& fromSafeArray(const SAFEARRAY* safeArrayPt) throw(HRESULT);
};

//***************************************************************************************************************
class NRXDBGATE_EXPORT NcAxMatrix3d : public NcGeMatrix3d
{
public:
	// constructors
	NcAxMatrix3d();
	NcAxMatrix3d(const VARIANT* var) throw(HRESULT);
	NcAxMatrix3d(const VARIANT& var) throw(HRESULT);
	NcAxMatrix3d(const SAFEARRAY* safeArrayPt) throw(HRESULT);

	// equal operators
	NcAxMatrix3d& operator=(const VARIANT* var) throw(HRESULT);
	NcAxMatrix3d& operator=(const VARIANT& var) throw(HRESULT);
	NcAxMatrix3d& operator=(const SAFEARRAY* safeArrayPt) throw(HRESULT);

	// utilities
private:
	NcAxMatrix3d& fromVariant(const VARIANT* pVar) throw(HRESULT);
	NcAxMatrix3d& fromSafeArray(const SAFEARRAY* safeArrayPt) throw(HRESULT);
};



//***************************************************************************************************************
// ---- NcAxObjectRef Class ----
//
// This class provides an abstract packaging of a reference to an NcDbObject,
// that is represented either as an NcDbObjectId or as an NcDbObject pointer.
// This packaging allows other classes to encapsulate an NcAxObjectRef instance
// instead of separate NcDbObjectId and pointer references, and to pass the
// reference around as a parameter without advance knowledge of the actual
// reference type.
//
// The following special behaviors apply to this implementation:
//
//      1. The NcAxObjectRef owns any pointers that it may encapsulate. Callers
//      should not cache any object pointers managed by an NcAxObjectRef. The
//      NcAxObjectRef destructor deletes objects it has pointers for if they
//      are not database resident.
//
//      2. The NcAxObjectRef does not manage the lifetime (i.e. does not own)
//      any NcDbObjectIds that it may encapsulate. The lifetime of the objects
//      referenced by NcDbObjectIds is not bound by the lifetime of the
//      NcAxObjectRef.
//
//      3. The NcAxObjectRef only encapsulates an NcDbObject pointer or an
//      NcDbObjectId at any given time.  Placing an NcDbObjectId into an
//      NcAxObjectRef which already encapsulates an NcDbObject pointer causes
//      the object to be deleted if it is not database resident.
//
//      3. Copy and assignment operations are prohibited, they would violate
//      the "ownership" aspect of the class.  Derived classes should override
//      copy and constructor members and declare them private.
//
//      4. Callers use the acquire() and release() methods to manage the
//      objects encapsulated by an NcAxObjectRef. There are no accessor methods
//      the encapsulated references. Callers must use the release() method to
//      obtain references to the encapsulated pointer or objectId, which
//      "detaches" the NcAxObjectRef from the references.
//***************************************************************************************************************

class NRXDBGATE_EXPORT NcAxObjectRef
{

public:
	NcAxObjectRef();
	NcAxObjectRef(NcDbObjectId objId);
	NcAxObjectRef(NcDbObject*& pObj);
	~NcAxObjectRef();

	Nano::ErrorStatus acquire(NcDbObjectId objId);
	Nano::ErrorStatus acquire(NcDbObject*& pObj);

	Nano::ErrorStatus release(NcDbObjectId& objId, NcDbObject*& pObj);

	bool isNull();
	NcDbObjectId objectId();

private:
	// Disallow copy constructor and assignment
	NcAxObjectRef(NcAxObjectRef& ref);
	NcAxObjectRef& operator=(NcAxObjectRef& ref);

	void internalRelease();
	// Object references
	NcDbObjectId m_objId;
	NcDbObject*  m_pObj;
};


//***************************************************************************************************************
// ---- Class NcAxObjectRefPtr ----
//
// This class provides "smart pointer" behavior for NcAxObjectRef instances,
// similar to the behavior provided by the NcDbObjectPointer template class for
// NcDbObjectIds. Unlike the NcDbObjectPointer class handling of non-database
// resident objects, the lifetime of the referenced object is not bound to the
// lifetime of the NcAxObjectRefPtr, only the open/closed state is managed by
// the NcAxObjectRefPtr class.
//
// The following special behaviors apply to this implementation:
//
//      1. The object references used by the NcAxObjectRefPtr class are "owned"
//      by the NcAxObjectRefPtr instance for the duration of its lifetime. When
//      constructed the NcAxObjectRefPtr releases the NcAxObjectRef of it's
//      object references.  As it is destroyed the NcAxObjectRefPtr returns the
//      ownership of these references to the NcAxObjectRef.
//
//      2. The objects managed by an NcAxObjectRefPtr are maintained in an
//      "open" state for as long as the objects are managed by the pointer
//      class. Open object references are "closed" when the NcAxObjectRefPtr
//      object is destroyed.
//
//      3. All of the caveats and usage notes mentioned for
//      NcDbObjectPointerBase in dbobjptr.h apply to this class as well.
//***************************************************************************************************************

template < class T_OBJECT >
class NcAxObjectRefPtr : public NcDbObjectPointer< T_OBJECT >
{
public:
	NcAxObjectRefPtr();
	NcAxObjectRefPtr(NcAxObjectRef* const pRef, NcDb::OpenMode mode, bool openErased = false);
	~NcAxObjectRefPtr();

private:
	// Disallow copy constructor, assignment operator
	NcAxObjectRefPtr(NcAxObjectRefPtr& pObj);
	NcAxObjectRefPtr& operator=(NcAxObjectRefPtr& pObj);

	NcAxObjectRef* const m_pRef;
};

//***************************************************************************************************************
template < class T_OBJECT > inline NcAxObjectRefPtr< T_OBJECT >::NcAxObjectRefPtr() : NcDbObjectPointer< T_OBJECT >(),
	m_pRef(NULL)
{}

//***************************************************************************************************************
template < class T_OBJECT > inline NcAxObjectRefPtr< T_OBJECT >::NcAxObjectRefPtr(NcAxObjectRef* const pRef,
                                                                                  NcDb::OpenMode mode,
                                                                                  bool openErased) : m_pRef(pRef)
{
	//_ASSERTE(NULL != pRef);
	if (NULL == pRef)
	{
		m_status = Nano::eNullObjectPointer; // VC8:Removed extra qualifier
		return;
	}

	// Acquire the reference as either an objectId or pointer
	NcDbObjectId objId = pRef->objectId();

	// If it is a non-null objectId just open it
	if (!objId.isNull())
		m_status = ncdbOpenObject(m_ptr, objId, mode, openErased);
	// If it is a null objectId we will need to acquire the
	// pointer from the NcAxObjectRef
	else
	{
		NcDbObject* pTmp = NULL;
		m_pRef->release(objId, pTmp);

		// Check for downcast of NcDbObject pointer to T_OBJECT
		// Restore object reference if this cast fails
		T_OBJECT* pTyped = T_OBJECT::cast(pTmp);
		if (NULL == pTyped)
		{
			m_ptr = NULL;
			m_pRef->acquire(pTmp);
			m_status = Nano::eNotThatKindOfClass;
		}
		else
			acquire(pTyped);
	}
}

//***************************************************************************************************************
template < class T_OBJECT > inline NcAxObjectRefPtr< T_OBJECT >::~NcAxObjectRefPtr()
{
	// If the objectid is null we need to release
	// our reference and store it on the NcAxObjectRef.
	if (NULL != m_ptr && m_ptr->objectId().isNull())
	{
		T_OBJECT* pTmp;
		release(pTmp);
		m_pRef->acquire(reinterpret_cast< NcDbObject*& >(pTmp));
	}
}

//***************************************************************************************************************
typedef NcAxObjectRefPtr< NcDbObject >  NcDbObjectRefPtr;
typedef NcAxObjectRefPtr< NcDbEntity >  NcDbEntityRefPtr;



//***************************************************************************************************************
// NcAxOleLinkManager is used to maintain the link between an NRX
// objects and their respective COM wrapper.
//***************************************************************************************************************
class OdOxOleLinkManager;
class NcAxOleLinkManager
{
public:
	NcAxOleLinkManager(OdOxOleLinkManager *native);

	// Given a pointer to a database resident object, return
	// the IUnknown of the COM wrapper. NULL is returned if
	// no wrapper is found.
	virtual IUnknown* GetIUnknown(NcDbObject* object);

	// Set the link between a database resident object and a
	// COM wrapper. If the IUnknown is NULL, then the link is removed.
	virtual NRX::Boolean SetIUnknown(NcDbObject* object, IUnknown* pUnknown);

	// Given a pointer to a database object, return
	// the IUnknown of the COM wrapper. NULL is returned if
	// no wrapper is found.
	virtual IUnknown* GetIUnknown(NcDbDatabase* pDatabase);

	// Set the link between a database object and a COM wrapper.
	// If the IUnknown is NULL, then the link is removed.
	virtual NRX::Boolean SetIUnknown(NcDbDatabase* pDatabase, IUnknown* pUnknown);

	// Given a pointer to a database object, return the
	// IDispatch of then document object. NULL is returned if
	// the database does not belong to a particular document.
	virtual IDispatch* GetDocIDispatch(NcDbDatabase* pDatabase);

	// Set the link between a database object and the IDispatch
	// of the document it belongs to. If the IDispatch is NULL, then
	// the link is removed.
	virtual NRX::Boolean SetDocIDispatch(NcDbDatabase* pDatabase, IDispatch* pDispatch);

	// Given a pointer to a database resident object and a subentID, return
	// the IUnknown of the COM wrapper. NULL is returned if
	// no wrapper is found.
	virtual IUnknown* GetIUnknown(NcDbObject* object, const NcDbSubentId& id);

	// Set the link between a database resident object, a subentID and a
	// COM wrapper. If the IUnknown is NULL, then the link is removed.
	virtual NRX::Boolean SetIUnknown(NcDbObject* object, const NcDbSubentId& id, IUnknown* pUnknown);

	OdOxOleLinkManager *native()
	{
		return m_pImpl;
	}

private:
	OdOxOleLinkManager *m_pImpl;
};

//***************************************************************************************************************
NRXDBGATE_EXPORT NcAxOleLinkManager* NcAxGetOleLinkManager();

//***************************************************************************************************************
// NcAx inline methods declaration
//***************************************************************************************************************
NRXDBGATE_EXPORT HRESULT NcAxGetOwnerId(NcDbObjectId& id, LONG_PTR* pOwnerId);

NRXDBGATE_EXPORT HRESULT NcAxErase(NcDbObjectId& id);

NRXDBGATE_EXPORT HRESULT NcAxSetXData(NcDbObjectId& id, VARIANT type, VARIANT data);
NRXDBGATE_EXPORT HRESULT NcAxGetXData(NcDbObjectId& id, BSTR bstrName, VARIANT* type, VARIANT* data);

NRXDBGATE_EXPORT HRESULT NcAxGetObjectName(NcDbObjectId& id, BSTR* name);

NRXDBGATE_EXPORT HRESULT NcAxGetHandle(NcDbObjectId& id, BSTR* handle);

NRXDBGATE_EXPORT HRESULT NcAxGetColor(NcDbObjectId& id, AcColor* color);
NRXDBGATE_EXPORT HRESULT NcAxPutColor(NcDbObjectId& id, AcColor color);

NRXDBGATE_EXPORT HRESULT NcAxGetTrueColor(NcDbObjectId& id, IAcadAcCmColor** color);
NRXDBGATE_EXPORT HRESULT NcAxPutTrueColor(NcDbObjectId& id, IAcadAcCmColor* color);

NRXDBGATE_EXPORT HRESULT NcAxGetLayer(NcDbObjectId& id, BSTR* layer);
NRXDBGATE_EXPORT HRESULT NcAxPutLayer(NcDbObjectId& id, BSTR layer);

NRXDBGATE_EXPORT HRESULT NcAxGetLinetype(NcDbObjectId& id, BSTR* pLinetype);
NRXDBGATE_EXPORT HRESULT NcAxPutLinetype(NcDbObjectId& id, BSTR linetype);

NRXDBGATE_EXPORT HRESULT NcAxGetLinetypeScale(NcDbObjectId& id, double* scale);
NRXDBGATE_EXPORT HRESULT NcAxPutLinetypeScale(NcDbObjectId& id, double scale);

NRXDBGATE_EXPORT HRESULT NcAxGetVisible(NcDbObjectId& id, VARIANT_BOOL* visible);
NRXDBGATE_EXPORT HRESULT NcAxPutVisible(NcDbObjectId& id, VARIANT_BOOL visible);

NRXDBGATE_EXPORT HRESULT NcAxGetPlotStyleName(NcDbObjectId& id, BSTR* plotStyleName);
NRXDBGATE_EXPORT HRESULT NcAxPutPlotStyleName(NcDbObjectId& id, BSTR plotStyleName);

NRXDBGATE_EXPORT HRESULT NcAxGetLineWeight(NcDbObjectId& id, ACAD_LWEIGHT* lineweight);
NRXDBGATE_EXPORT HRESULT NcAxPutLineWeight(NcDbObjectId& id, ACAD_LWEIGHT lineweight);

NRXDBGATE_EXPORT HRESULT NcAxArrayPolar(NcDbObjectId& id, LPDISPATCH dispatch, int numObjs, double fillAngle, VARIANT base,
                       VARIANT* pArrayObjs);

NRXDBGATE_EXPORT HRESULT NcAxArrayRectangular(NcDbObjectId& id, LPDISPATCH dispatch, int numRows, int numCols, int numLvls,
                             double disRows, double disCols, double disLvls, VARIANT* pArrayObjs);

NRXDBGATE_EXPORT HRESULT NcAxHighlight(NcDbObjectId& id, VARIANT_BOOL bHighlight);

NRXDBGATE_EXPORT HRESULT NcAxCopy(NcDbObjectId& id, LPDISPATCH dispatch, LPDISPATCH* pCopyObj,
                 NcDbObjectId ownerId = NcDbObjectId::kNull);

NRXDBGATE_EXPORT HRESULT NcAxMove(NcDbObjectId& id, VARIANT from, VARIANT to);

NRXDBGATE_EXPORT HRESULT NcAxRotate(NcDbObjectId& id, VARIANT base, double angle);

NRXDBGATE_EXPORT HRESULT NcAxRotate3D(NcDbObjectId& id, VARIANT point1, VARIANT point2, double angle);

NRXDBGATE_EXPORT HRESULT NcAxMirror(NcDbObjectId& id, LPDISPATCH dispatch, VARIANT point1, VARIANT point2, LPDISPATCH* pMirrorObj);

NRXDBGATE_EXPORT HRESULT NcAxMirror3D(NcDbObjectId& id, LPDISPATCH dispatch, VARIANT point1, VARIANT point2, VARIANT point3,
                     LPDISPATCH* pMirrorObj);

NRXDBGATE_EXPORT HRESULT NcAxScaleEntity(NcDbObjectId& id, VARIANT base, double scale);

NRXDBGATE_EXPORT HRESULT NcAxTransformBy(NcDbObjectId& id, VARIANT trans);

NRXDBGATE_EXPORT HRESULT NcAxUpdate(NcDbObjectId& id);

NRXDBGATE_EXPORT HRESULT NcAxGetBoundingBox(NcDbObjectId& id, VARIANT* min, VARIANT* max);

NRXDBGATE_EXPORT HRESULT NcAxIntersectWith(NcDbObjectId& id, LPDISPATCH entity, AcExtendOption option, VARIANT* points);

NRXDBGATE_EXPORT HRESULT NcAxGetHyperlinks(NcDbObjectId& id, LPDISPATCH dispatch, IAcadHyperlinks** pHyperlinks);

NRXDBGATE_EXPORT HRESULT NcAxHasExtensionDictionary(NcDbObjectId& id, VARIANT_BOOL* has_dictionary);

NRXDBGATE_EXPORT HRESULT NcAxGetExtensionDictionary(NcDbObjectId& id, LPDISPATCH dispatch, IAcadDictionary** dictionary);

NRXDBGATE_EXPORT HRESULT NcAxGetTransparency(NcDbObjectId& objId, BSTR* pTransparency);
NRXDBGATE_EXPORT HRESULT NcAxPutTransparency(NcDbObjectId& objId, BSTR transparency);

NRXDBGATE_EXPORT HRESULT NcAxGetDatabase(NcDbDatabase* database, LPDISPATCH dispatch, LPDISPATCH* pDisp);

NRXDBGATE_EXPORT HRESULT NcAxArrayPolar(NcAxObjectRef& objRef, LPDISPATCH pAppDisp, int numObjs,
                       double fillAngle, VARIANT basePoint, VARIANT* pArrayObjs);

NRXDBGATE_EXPORT HRESULT NcAxArrayRectangular(NcAxObjectRef& objRef, LPDISPATCH pAppDisp, int numRows,
                             int numCols, int numLvls, double disRows, double disCols,
                             double disLvls, VARIANT* pArrayObjs);

NRXDBGATE_EXPORT HRESULT NcAxCopy(NcAxObjectRef& objRef, LPDISPATCH pAppDisp, LPDISPATCH* pCopyObj,
                 NcDbObjectId ownerId);

NRXDBGATE_EXPORT HRESULT NcAxEnableShadowDisplay(NcAxObjectRef& objRef, bool* pEnabled);

NRXDBGATE_EXPORT HRESULT NcAxErase(NcAxObjectRef& objRef);

NRXDBGATE_EXPORT HRESULT NcAxGetBoundingBox(NcAxObjectRef& objRef, VARIANT* minPoint, VARIANT* maxPoint);

NRXDBGATE_EXPORT HRESULT NcAxGetColor(NcAxObjectRef& objRef, AcColor* pColor);

NRXDBGATE_EXPORT HRESULT NcAxGetExtensionDictionary(NcAxObjectRef& objRef, LPDISPATCH pAppDisp,
                                   IAcadDictionary** pExtDictionary);

NRXDBGATE_EXPORT HRESULT NcAxGetHandle(NcAxObjectRef& objRef, BSTR* pHandle);

NRXDBGATE_EXPORT HRESULT NcAxGetHyperlinks(NcAxObjectRef& objRef, LPDISPATCH pAppDisp,
                          IAcadHyperlinks** pHyperlinks);

NRXDBGATE_EXPORT HRESULT NcAxGetLayer(NcAxObjectRef& objRef, BSTR* pLayer);

NRXDBGATE_EXPORT HRESULT NcAxGetLinetype(NcAxObjectRef& objRef, BSTR* pLinetype);

NRXDBGATE_EXPORT HRESULT NcAxGetLinetypeScale(NcAxObjectRef& objRef, double* pLinetypeScale);

NRXDBGATE_EXPORT HRESULT NcAxGetLineWeight(NcAxObjectRef& objRef, ACAD_LWEIGHT* lineWeight);

NRXDBGATE_EXPORT HRESULT NcAxGetMaterial(NcAxObjectRef& objRef, BSTR* pMaterial);

NRXDBGATE_EXPORT HRESULT NcAxGetObjectName(NcAxObjectRef& objRef, BSTR* pName);

NRXDBGATE_EXPORT HRESULT NcAxGetOwnerId(NcAxObjectRef& objRef, NRX::IntDbId* pOwnerId);

NRXDBGATE_EXPORT HRESULT NcAxGetPlotStyleName(NcAxObjectRef& objRef, BSTR* plotStyleName);

NRXDBGATE_EXPORT HRESULT NcAxGetShadowDisplay(NcAxObjectRef& objRef, AcShadowDisplayType* pShadowDisplay);

NRXDBGATE_EXPORT HRESULT NcAxGetTransparency(NcAxObjectRef& objRef, BSTR* pTransparency);

NRXDBGATE_EXPORT HRESULT NcAxGetTrueColor(NcAxObjectRef& objRef, IAcadAcCmColor** pColor);

NRXDBGATE_EXPORT HRESULT NcAxGetVisible(NcAxObjectRef& objRef, VARIANT_BOOL* pVisible);

NRXDBGATE_EXPORT HRESULT NcAxGetXData(NcAxObjectRef& objRef, BSTR bstrName, VARIANT* type, VARIANT* data);

NRXDBGATE_EXPORT HRESULT NcAxHasExtensionDictionary(NcAxObjectRef& objRef, VARIANT_BOOL* bHasDictionary);

NRXDBGATE_EXPORT HRESULT NcAxHighlight(NcAxObjectRef& objRef, VARIANT_BOOL bHighlight);

NRXDBGATE_EXPORT HRESULT NcAxIntersectWith(NcAxObjectRef& objRef, LPDISPATCH pEntity,
                          AcExtendOption option, VARIANT* intPoints);

NRXDBGATE_EXPORT HRESULT NcAxMirror(NcAxObjectRef& objRef, LPDISPATCH pAppDisp, VARIANT point1,
                   VARIANT point2, LPDISPATCH* pMirrorObj);

NRXDBGATE_EXPORT HRESULT NcAxMirror3D(NcAxObjectRef& objRef, LPDISPATCH pAppDisp, VARIANT point1,
                     VARIANT point2, VARIANT point3, LPDISPATCH* pMirrorObj);

NRXDBGATE_EXPORT HRESULT NcAxMove(NcAxObjectRef& objRef, VARIANT fromPoint, VARIANT toPoint);

NRXDBGATE_EXPORT HRESULT NcAxPutColor(NcAxObjectRef& objRef, AcColor color);

NRXDBGATE_EXPORT HRESULT NcAxPutLayer(NcAxObjectRef& objRef, BSTR layer);

NRXDBGATE_EXPORT HRESULT NcAxPutLinetype(NcAxObjectRef& objRef, BSTR linetype);

NRXDBGATE_EXPORT HRESULT NcAxPutLinetypeScale(NcAxObjectRef& objRef, double linetypeScale);

NRXDBGATE_EXPORT HRESULT NcAxPutLineWeight(NcAxObjectRef& objRef, ACAD_LWEIGHT lineWeight);

NRXDBGATE_EXPORT HRESULT NcAxPutMaterial(NcAxObjectRef& objRef, BSTR material);

NRXDBGATE_EXPORT HRESULT NcAxPutPlotStyleName(NcAxObjectRef& objRef, BSTR plotStyleName);

NRXDBGATE_EXPORT HRESULT NcAxPutShadowDisplay(NcAxObjectRef& objRef, AcShadowDisplayType shadowDisplay);

NRXDBGATE_EXPORT HRESULT NcAxPutTransparency(NcAxObjectRef& objRef, BSTR transparency);

NRXDBGATE_EXPORT HRESULT NcAxPutTrueColor(NcAxObjectRef& objRef, IAcadAcCmColor* color);

NRXDBGATE_EXPORT HRESULT NcAxPutVisible(NcAxObjectRef& objRef, VARIANT_BOOL visible);

NRXDBGATE_EXPORT HRESULT NcAxRotate(NcAxObjectRef& objRef, VARIANT basePoint, double rotationAngle);

NRXDBGATE_EXPORT HRESULT NcAxRotate3D(NcAxObjectRef& objRef, VARIANT point1, VARIANT point2,
                     double rotationAngle);

NRXDBGATE_EXPORT HRESULT NcAxScaleEntity(NcAxObjectRef& objRef, VARIANT basePoint, double scaleFactor);

NRXDBGATE_EXPORT HRESULT NcAxSetXData(NcAxObjectRef& objRef, VARIANT type, VARIANT data);

NRXDBGATE_EXPORT HRESULT NcAxTransformBy(NcAxObjectRef& objRef, VARIANT transMatrix);

NRXDBGATE_EXPORT HRESULT NcAxUpdate(NcAxObjectRef& objRef);

#endif // __OPENDWG_AXUTILS_H__

