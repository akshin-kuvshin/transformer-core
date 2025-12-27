#ifndef HIDDENLINES_H
#define HIDDENLINES_H
#include "nrxdbgate_impexp.h"

#define NsdkHlrApiServiceName _T("NSDK_HLR_API_SERVICES")

enum NsdkHlrControl {
	kProject            =0x0001,
	kShowAll            =0x0002,
	kEntity             =0x0004,
	kBlock              =0x0008,
	kSubentity          =0x0010,
	kHideTangents       =0x0020,
	kCleanup            =0x0040,
	kIsolines           =0x0080,
	kUnite              =0x0100,
	kReuse              =0x0200,
	kProgress           =0x0400,
	kHandlePoints       =0x0800,
	kProcessAll         =0x1000,
	kHonorInternals     =0x2000,
	kMeshSilhouettes    =0x4000,
	kSingleCacheVp      =0x8000
} ;

//////////////////////////////////////////////////////////////////////////
// NsdkHiddenLineBase
class NRXDBGATE_EXPORT NsdkHiddenLineBase: public NcRxObject {
protected:
	std::map<NcDbEntity*, NcDbVoidPtrArray*> m_entityBodies ;
public:
	NCRX_DECLARE_MEMBERS (NsdkHiddenLineBase) ;
	virtual Nano::ErrorStatus prepare (NcDbEntity*pEnt, NcDbVoidPtrArray &bodies, int control, const NcDbViewport*pVp) ;
	virtual Nano::ErrorStatus getBody (void*pBodyData, int control) ;
	static Nano::ErrorStatus saveData (NcDbEntity*pEnt, void*pBodyData) ;
	static NRX::Boolean retrieveData (NcDbEntity*pEnt, NcDbVoidPtrArray &bodies, const NcDbViewport*pVp =NULL) ;
	static void clear () ;
	static void clear (NcDbEntity*pEnt) ;
	static void clear (NcDbEntity*pEnt, NcDbViewport*pVp) ;
};

//////////////////////////////////////////////////////////////////////////
// NsdkHlrData
class NRXDBGATE_EXPORT NsdkHlrData {
public:
	enum Visibility {
		kVisible,
		kHidden,
		kOccluded,
		kInternallyHidden,
		kUndefined
	} ;
protected:
	NcDbEntity*m_pEntity ;
	NcDbObjectIdArray m_objectIds ;
	NcDbSubentId m_subentId ;
	Visibility m_visibility ;
	Visibility m_hlrVisibility ;
	NcDbEntity*m_pResultEntity ;
public:
	NsdkHlrData () : m_pEntity (NULL), m_visibility(kUndefined), m_hlrVisibility(kUndefined), m_pResultEntity(NULL) {}
	virtual ~NsdkHlrData () {
		if ( m_pResultEntity && m_pResultEntity->objectId () == NcDbObjectId::kNull )
			delete m_pResultEntity ;
	}
	void setEntity (NcDbEntity*pEnt)
	    { if ( pEnt != NULL ) m_pEntity =pEnt ;    }
	void setObjectIds (NcDbObjectIdArray id)
	    { m_objectIds =id ; }
	void setResultEntity (NcDbEntity*pResultEnt)
	    { m_pResultEntity =pResultEnt ; }
	void setVisibility (Visibility visibility)
	    { m_visibility =visibility ; }
	void setHlrVisibility (Visibility visibility)
	    { m_hlrVisibility =visibility ; }
	void setSubentId (NcDbSubentId subentId)
	    { m_subentId =subentId ; }
	NcDbEntity*getEntity ()
	    { return (m_pEntity) ; }
	NcDbObjectIdArray &getObjectIds ()
	    { return (m_objectIds) ; }
	NcDbEntity*getResultEntity ()
	    { return (m_pResultEntity) ; }
	Visibility getVisibility ()
	    { return (m_visibility) ; }
	Visibility getHlrVisibility ()
	    { return (m_hlrVisibility) ; }
	NcDbSubentId getSubentId ()
	    { return (m_subentId) ; }
};

//////////////////////////////////////////////////////////////////////////
// NsdkHlrCollector
template class NRXDBGATE_EXPORT NcArray<NsdkHlrData*>;
template class NRXDBGATE_EXPORT NcArray<NcDbEntity*>;
class NRXDBGATE_EXPORT NsdkHlrCollector {
protected:
	NcArray<NcDbEntity*> mEntities ;
	bool mbDeleteInDestructor ;
	NcDbObjectIdArray mEntityIds ;
public:
	NcArray<NsdkHlrData*> mOutputData ;
public:
	NsdkHlrCollector () : mbDeleteInDestructor(false) {}
	NsdkHlrCollector (NcDbObjectIdArray &ids) ;
	NsdkHlrCollector (NcArray<NcDbEntity*> &entities, bool deleteInDestructor =false) ;
	NsdkHlrCollector (NsdkHlrCollector &collector) ;
	virtual ~NsdkHlrCollector () ;
	bool getDeleteState ()
	    { return (mbDeleteInDestructor) ; }
	void setDeleteState (bool bFlag)
	    { mbDeleteInDestructor =bFlag ; }
	NcArray<NcDbEntity*> &getInputEntities ()
	    { return (mEntities) ; }
	NcDbObjectIdArray &getInputEntityIds ()
	    { return (mEntityIds) ; }
	void addEntity (NcDbEntity*pEnt) ;
	void addEntities (NcArray<NcDbEntity*> &pEnts) ;
	void addEntity (NcDbObjectId id) ;
	void addEntities (NcDbObjectIdArray &ids) ;
	void removeEntity (NcDbEntity*pEnt) ;
	void removeEntities (NcArray<NcDbEntity*> &pEnts) ;
	void removeEntity (NcDbObjectId id) ;
	void removeEntities (NcDbObjectIdArray &ids) ;
	void clear () ;
protected:
	virtual int initialize (NcArray<NcDbEntity*> &collection) ;
	virtual void close (NcArray<NcDbEntity*> &collection) ;
	friend class NsdkHlrEngine ;
};

typedef void (*_AbortCallbackFct) (bool *abort) ;
typedef void (*_ProgressCallbackFct) (int percent_completed) ;

//////////////////////////////////////////////////////////////////////////
// NsdkHlrEngine
class NRXDBGATE_EXPORT NsdkHlrEngine {
protected:
	NcDbViewport*mpViewport ;
	int mnControl ;
	_AbortCallbackFct mpAbortCallbackFct ;
	_ProgressCallbackFct mpAcisConvertionProgressCallbackFct ;
	_ProgressCallbackFct mpAhlProgressCallbackFct ;
	_ProgressCallbackFct mpNcadConvertionProgressCallbackFct ;
public:
	NsdkHlrEngine (int ctrl =kShowAll | kEntity | kBlock | kSubentity | kReuse) ;
	NsdkHlrEngine (NcDbObjectId id, int ctrl =kShowAll | kEntity | kBlock | kSubentity | kReuse) ;
	NsdkHlrEngine (NcDbViewport*pViewport, int ctrl =kShowAll | kEntity | kBlock | kSubentity | kReuse) ;
	NsdkHlrEngine (NcGePoint3d &viewTarget, NcGeVector3d &viewDirection, int ctrl =kShowAll | kEntity | kBlock | kSubentity | kReuse) ;
	virtual ~NsdkHlrEngine () ;
	Nano::ErrorStatus run (NsdkHlrCollector &collector) ;
	void setAbortCallback (_AbortCallbackFct fct) ;
	void setAcisConversionProgressCallBack (_ProgressCallbackFct fct) ;
	void setAhlProgressCallBack (_ProgressCallbackFct fct) ;
	void setNcadConversionProgressCallBack (_ProgressCallbackFct fct) ;
	static void cleanHlrCache () ;
	static void cleanHlrCache (NcDbEntity*pEnt, NcDbViewport*pVp =NULL) ;
	static void cleanHlrCache (NcDbEntity*pEnt, NcGePoint3d viewTarget, NcGeVector3d viewDir) ;
};
#endif // HIDDENLINES_H
