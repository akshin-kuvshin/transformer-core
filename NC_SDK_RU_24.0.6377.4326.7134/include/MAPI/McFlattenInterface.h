
#pragma once

#include "3DRefKey.h"
#include "McsGeometry.h"
#include "IMcNativeGate.h"
#include "IMcs.h"

// Псевдо ID первой фичи-сечения.
// Используется для присвоения ключей FEV, появляющимся в телах при построении разреза.
// "Псевдо", потому что реально в данных самого тела о таких фичах ничего нет.
// И хранить его там банально не получится, т.е. тело может участвовать в разрезах
// в документах, куда тело попадает через внешние ссылки.
// Также в таком хранении нет смысла, поскольку основная задача - уникально идентифицировать FEV разреза
// в пределах вида. Поскольку могут иметь место последовательные разрезы, к первичному ID добавляется
// счетчик вложенности видов. Это позволяет различать FEV предыдущего разреза от последующего.
// Число выбрано так, чтобы гарантированно не пересекаться с ID фич в телах.
// Очень маловероятно, что внутри тела будет так много фич, т.к.штатно новые ID присваиваются инкрементом от 1.
//
#define DV_FTR_ID_1ST_SECTION 10000

//==================================================================================================

#ifndef OD3DENTPROJ_DEFINED
	#define OD3DENTPROJ_DEFINED
	struct Od3dEntForProj;
	typedef std::shared_ptr<Od3dEntForProj> Od3dEntForProjPtr;
#endif

typedef OdArray<Od3dEntForProjPtr>      Od3dEntForProjPtrArr;

struct IMcProjViewExDataProvider;

//==================================================================================================

struct Od3dEntForProj
{
	enum CSType
	{
		kUndefCS = 0,
		kLCS,
		kWCS,
	};

	enum GetMode
	{
		kOriginal = 0,
		kClone,
	};

protected:
	// идентифицирует объект в чертеже
	// Может быть пуст, если указан объект явно и к нему не нужно применять матрицу
	std::unique_ptr<mcsComplexWorkID> m_pCID;

	// задает тип СК объекта m_p3dEnt
	mutable CSType m_eEntCS;

	// объект для проекции
	mutable OdDbEntityPtr m_p3dEnt;

	// кэшированная матрица вставки, каждый раз при запросе получать её медленно
	mutable std::unique_ptr<OdGeMatrix3d> m_pInsTfm;

	// Интерфейс влияет на получение солидов из объектов данного класса.
	// Поле нужно инициализировать до начала построения проекций,
	// И очищать после обработки построенных проекций.
	// TODO: многопоточность, развести по потокам.
	static McsArray<IMcProjViewExDataProvider*> s_pSolidProvidersStack;

public:
	Od3dEntForProj()
	{
		m_eEntCS = kUndefCS;
	}

	// Простой 3D объект в чертеже
	Od3dEntForProj(const OdDbObjectId& id)
	{
		m_eEntCS = kWCS;
		if(!id.isNull())
		{
			mcsWorkID mcid;
			gpMcNativeGate->getMcsIdByNative(mcid, *(LONG_PTR*)&id);
			m_pCID = std::make_unique<mcsComplexWorkID>(mcid);
		}
	}

	// простой 3D объект в чертеже/в памяти
	Od3dEntForProj(OdDbEntity* p3dEnt, CSType eCS = kWCS)
	{
		m_eEntCS = eCS;

		m_p3dEnt = p3dEnt;
		if(p3dEnt)
		{
			OdDbObjectId odid = p3dEnt->objectId();
			if(!odid.isNull())
			{
				mcsWorkID mcid;
				gpMcNativeGate->getMcsIdByNative(mcid, *(LONG_PTR*)&odid);
				m_pCID = std::make_unique<mcsComplexWorkID>(mcid);
			}
		}
	}

	// 3D объект внутри блока, без модификаций
	MC_NANO_GATE_API Od3dEntForProj(const mcsComplexWorkID& cid);

	// 3D объект внутри блока, c модификациями
	// bLCS = true, если объект находится в СК документа, в котором непосредственно находится.
	MC_NANO_GATE_API Od3dEntForProj(const mcsComplexWorkID& cid, OdDbEntity* p3dEnt, CSType eCS);

	CSType cs() const {
		return m_eEntCS;
	}

	bool operator == (const Od3dEntForProj& cw) const
	{
		if(m_p3dEnt.get() != cw.m_p3dEnt.get())
			return false;

		if(!!m_pCID != !!cw.m_pCID)
			return false;
		if(m_pCID && *m_pCID != *cw.m_pCID)
			return false;

		if(m_p3dEnt.get())
		{
			if(m_pCID && m_pCID->objects().GetSize())
				if(m_eEntCS != cw.m_eEntCS)
					return false;
		}

		return true;
	}

	bool operator != (const Od3dEntForProj& cw) const {
		return !operator == (cw);
	}

	OdDbEntity* rawEntity() {
		return m_p3dEnt;
	}

	const OdDbEntity* rawEntity() const {
		return m_p3dEnt;
	}

	// Получить конечный объект, опционально с учетом матрицы вставки.
	// В случае применения матрицы будет возвращена копия объекта.
	// reqCS определяет тип СК, в которой нужно получить объект.
	// reqCS == kUndefCS, объект возвращается в неопределенной СК,
	//    использовать этот режим только для логической работы с топологией.
	// Если eOpenMode = kForWrite, будет возвращена копия, которую можно менять.
	MC_NANO_GATE_API OdDbEntityPtr get3dEnt(CSType reqCS, GetMode eOpenMode) const;

	// получить суммарную матрицу вставки, определяется полем m_odCID
	MC_NANO_GATE_API const OdGeMatrix3d& insertionTfm() const;

	MC_NANO_GATE_API const mcsComplexWorkID& cid() const;

	MC_NANO_GATE_API Od3dEntForProj& setCid(const mcsComplexWorkID& cid, bool bSetCIDOnly = false);

	MC_NANO_GATE_API bool isModelEmpty() const;

	// Получить баунд в ГСК массива проекционных элементов
	MC_NANO_GATE_API static OdGeExtents3d sGetExt3d_wcs(const Od3dEntForProjPtrArr& projEnts);

	MC_NANO_GATE_API static bool pushSolidProvider(IMcProjViewExDataProvider* pProvider);
	MC_NANO_GATE_API static bool popSolidProvider();
	MC_NANO_GATE_API static IMcProjViewExDataProvider* solidProvider();
};
//==================================================================================================

template<> inline UINT __stdcall McsHashKey(Od3dEntForProjPtr p)
{
	UINT h = McsHashKey<void*>((void*)p.get());
	return h;
}

//==================================================================================================

enum mcsProjCurveTypeEnum
{
	kMcProjCrv_Unclassified,
	kMcProjCrv_ThreadFrontArc,       // относится к резьбе; направл. проекции параллельно оси резьбы; дуга
	kMcProjCrv_ThreadAxisParallelLS, // относится к резьбе; направл. проекции перп. оси резьбы; продольная линия резьбы

	// относится к резьбе; направл. проекции перп. оси резьбы; поперечная линия резьбы;
	// обозначает глубину; но относится к случаю разреза по оси резьбы - линия должна быть пунктирной
	kMcProjCrv_ThreadAxisPerpLS_SecDash,

	// относится к резьбе; направл. проекции перп. оси резьбы; поперечная линия резьбы;
	// относится к случаю разреза по оси резьбы - линия должна быть основной
	kMcProjCrv_ThreadAxisPerpLS_SecBase,

	kMcProjCrv_FaceCurve,            // кривая-силуэт грани
	kMcProjCrv_EdgeCurve,            // кривая-проекция ребра
};

struct IMc3dThreadFeature;

//==================================================================================================

typedef std::shared_ptr<McFEVRefKeyData> McFEVRefKeyDataPtr;

struct CurveData
{
protected:

	OdGeCurve3dPtr       mspCurve;
	Od3dEntForProjPtr    mpProjEntOwner;
	McFEVRefKeyDataPtr   mpRK;
	mcsProjCurveTypeEnum mCrvType;
	IMc3dThreadFeature*  mpThread;

public:

	CurveData()
	{
		mCrvType = kMcProjCrv_Unclassified;
		mpThread = NULL;
	}

	CurveData(const CurveData& cf)
	{
		*this = cf;
	}

	void setCurve( OdGeCurve3dPtr pCurve )
	{
		mspCurve = pCurve;
	}

	void set( OdGeCurve3dPtr pCurve, Od3dEntForProjPtr pProjEnt )
	{
		mspCurve = pCurve;
		mpProjEntOwner = pProjEnt;
	}

	void setRefKey(const McFEVRefKeyData* pSourceRefKey)
	{
		mpRK = std::make_shared<McFEVRefKeyData>();
		*mpRK = *pSourceRefKey;
	}

	void setType(mcsProjCurveTypeEnum type, IMc3dThreadFeature* pThread = NULL)
	{
		mCrvType = type;
		mpThread = pThread;
	}

	mcsProjCurveTypeEnum type() const
	{
		return mCrvType;
	}

	IMc3dThreadFeature* thread() const
	{
		return mpThread;
	}

	OdGeCurve3dPtr getCurve() const
	{
		return mspCurve;
	}

	McFEVRefKeyDataPtr refKey() const
	{
		return mpRK;
	}

	Od3dEntForProjPtr owner() const
	{
		return mpProjEntOwner;
	}

	CurveData& operator = (const CurveData& cf)
	{
		if(this == &cf)
			return *this;
		mspCurve = cf.mspCurve;
		mpProjEntOwner = cf.mpProjEntOwner;
		mpRK = cf.mpRK;
		mCrvType = cf.mCrvType;
		mpThread = cf.mpThread;
		return *this;
	}
};
//==================================================================================================

typedef McsArray<CurveData> CurveDataArray;

//==================================================================================================

// Valid input entity types: OdDb3dSolid / OdDbSurface / OdDbBody / OdDbRegion
// pFaceterSettings may be omitted, default settings will be used in this case.
//
// 'bIncludeIndicesCountInFacets':
//   true = indices will contain proceeded number of indices per each facet,
//     example for triangular facets: 3 10 20 30 3 40 50 60 - encodes two triangles 10,20,30 and 40,50,60
//     example for quadrangle facets: 4 10 20 30 40 4 11 22 33 44 - encodes two quadrangles 10,20,30,40 and 11,22,33,44
//   false = inly indices will be included into 'faceIndices' array,
//     Note(!): if both triangles and quadrangles are generated for the given 3d object but
//     bIncludeIndicesCountInFacets is false, an error will be returned
//
// Valid values for 'pFaceterSettings->faceterMeshType' (see Object ARX)
//   0 = Objects are converted to an optimized mesh object type with fewer faces
//   1 = Faces are mostly quadrilateral
//   2 = Faces are mostly triangular

__inline bool dbExtConvert3dEntityToMesh(
	IN const OdDbEntity*             pDb3dEnt,
	IN OPTIONAL OdDbFaceterSettings* pFaceterSettings, // = NULL
	IN bool                          bIncludeIndicesCountInFacets, // = true
	OUT mcsPoint3dArray&             vertices,
	OUT OPTIONAL mcsVector3dArray*   pNormals, // = NULL
	OUT mcsDwordArray&               faceIndices)
{
	static FARPROC ls_proc = (FARPROC)-1;
	if(ls_proc == (FARPROC)-1)
	{
		ls_proc = NULL;
		if(HMODULE hM = GetModuleHandleA("McFlatten.dll"))
			ls_proc = GetProcAddress(hM, "convert3dEntityToMesh");
	}

	if(!ls_proc)
		return false;

	bool bres =
		( (bool(*)(const OdDbEntity*, OdDbFaceterSettings*, bool, mcsPoint3dArray&, mcsVector3dArray*, mcsDwordArray&)) ls_proc )
			(pDb3dEnt, pFaceterSettings, bIncludeIndicesCountInFacets, vertices, pNormals, faceIndices);

	return bres;
}
//==================================================================================================

struct McShellData
{
	mcsPoint3dArray  points;
	mcsVector3dArray normals;
	mcsDwordArray    indicesWithCounts;
};

typedef McsArray<McShellData> McShellDataArr;
//==================================================================================================

__inline bool dbExtConvertUnkEntityToShells(
	IN const OdDbEntity*             pDb3dEnt,
	OUT McShellDataArr&              shellsArr)
{
	static FARPROC ls_proc = (FARPROC)-1;
	if(ls_proc == (FARPROC)-1)
	{
		ls_proc = NULL;
		if(HMODULE hM = GetModuleHandleA("McFlatten.dll"))
			ls_proc = GetProcAddress(hM, "convertUnkEntityToShells");
	}

	if(!ls_proc)
		return false;

	bool bres =
		( (bool(*)(const OdDbEntity*, McShellDataArr&)) ls_proc )
			(pDb3dEnt, shellsArr);

	return bres;
}
//==================================================================================================

// An implementation expects that the given entity draws at least one shell/mesh (in its worldDraw method)
// that is further converted into a 3dSolid object

__inline bool dbExtConvertEntityGridsToSolids(const OdDbEntity* pDbEnt, OUT OdDb3dSolidPtrArray& solids)
{
	static FARPROC ls_proc = (FARPROC)-1;
	if(ls_proc == (FARPROC)-1)
	{
		ls_proc = NULL;
		if(HMODULE hM = GetModuleHandleA("McFlatten.dll"))
			ls_proc = GetProcAddress(hM, "convertEntityGridsToSolids");
	}

	if(!ls_proc)
		return false;

	bool bres = ( (bool(*)(const OdDbEntity*, OdDb3dSolidPtrArray&)) ls_proc ) (pDbEnt, solids);
	return bres;
}
//==================================================================================================

// calculates intersections between given surfaces;
// returns a number of intersections found (curves + points) or a negative value on error

__inline int dbExtIntersectSurfaces(
	IN const OdGeSurface&      surf1,
	IN const OdGeSurface&      surf2,
	OUT OdGeCurve3dPtrArray&   intersectionCurves,
	OUT OdGePoint3dArray&      intersectionPoints,
	IN OPTIONAL const OdGeTol& tol = OdGeContext::gTol)
{
	static FARPROC ls_proc = (FARPROC)-1;
	if(ls_proc == (FARPROC)-1)
	{
		ls_proc = NULL;
		if(HMODULE hM = GetModuleHandleA("McFlatten.dll"))
			ls_proc = GetProcAddress(hM, "intersectSurfaces");
	}

	if(!ls_proc)
	{
		intersectionCurves.clear();
		intersectionPoints.clear();
		return -1;
	}

	int ires = ( (int (*) (const OdGeSurface&, const OdGeSurface&, OdGeCurve3dPtrArray&, OdGePoint3dArray&, const OdGeTol&)) ls_proc ) (
		surf1, surf2, intersectionCurves, intersectionPoints, tol);

	return ires;
}
//==================================================================================================

struct IMcFlattenSrv
{
	// projPlanePt     - is a point on a plane for projections
	// projPlaneNormal - the vector is interpreted as a projection direction
	// entities3d      - 3d entities to be projected
	// visibleCurves   - result visible projected curves
	// visibleCurves   - optional result hidden projected curves
	// occludedCurves  - (deprecated, use visibleCurves instead)
	// pUsedTol        - specify a pointer if you need to know what tolerance was used during projections
	//
	// frontClipDistance, backClipDistance - are c lipping distances that are specified from the target-point,
	// positive direction is towards the eye-point,  default values mean no clipping will be used
	// (see ObjectARX for details)

	virtual OdResult calculateHiddenEdges(
		IN const OdGePoint3d&           projPlanePt_wcs,
		IN const OdGeVector3d&          projPlaneNormal_wcs,
		IN const Od3dEntForProjPtrArr&  projEnts,
		OUT CurveDataArray&             visibleCurves_wcs, // on the plane defined by projPlanePt_wcs + projPlaneNormal_wcs
		OUT OPTIONAL CurveDataArray&    hiddenCurves_wcs = *(CurveDataArray*)NULL, // on the plane defined by projPlanePt_wcs + projPlaneNormal_wcs
		OUT OPTIONAL double*            pUsedTol = NULL,
		IN OPTIONAL double              frontClipDistance = DBL_MAX,
		IN OPTIONAL double              backClipDistance = -DBL_MAX)
	{
		return eNotImplemented;
	}

	// An implementation expects that the given entity draws at least one shell/mesh (in its worldDraw method)
	// that is further converted into a 3dSolid object

	virtual OdResult convertEntityGridsToSolids(const OdDbEntity* pDbEnt, OUT OdDb3dSolidPtrArray& solids)
	{
		return eNotImplemented;
	}

	// Valid input entity types: OdDb3dSolid / OdDbSurface / OdDbBody / OdDbRegion
	// pFaceterSettings may be omitted, default settings will be used in this case.
	//
	// 'bIncludeIndicesCountInFacets':
	//   true = indices will contain proceeded number of indices per each facet,
	//     example for triangular facets: 3 10 20 30 3 40 50 60 - encodes two triangles 10,20,30 and 40,50,60
	//     example for quadrangle facets: 4 10 20 30 40 4 11 22 33 44 - encodes two quadrangles 10,20,30,40 and 11,22,33,44
	//   false = inly indices will be included into 'faceIndices' array,
	//     Note(!): if both triangles and quadrangles are generated for the given 3d object but
	//     bIncludeIndicesCountInFacets is false, an error will be returned

	virtual OdResult convert3dEntityToMesh(
		IN const OdDbEntity*             pDb3dEnt,
		IN OPTIONAL OdDbFaceterSettings* pFaceterSettings, // = NULL
		IN bool                          bIncludeIndicesCountInFacets, // = true
		OUT mcsPoint3dArray&             vertices,
		OUT OPTIONAL mcsVector3dArray*   pNormals, // = NULL
		OUT mcsDwordArray&               faceIndices)
	{
		return eNotImplemented;
	}

	// Converts the given OdGe curve into OdDb curve object
	virtual OdDbCurve* ConvertCurveToOdDb(const OdGeCurve3d& curve)
	{
		return NULL;
	}

	// Converts the given OdDb curve object into OdGe curve
	virtual OdGeCurve3d* ConvertOdDbToCurve(const OdDbCurve& curve)
	{
		return NULL;
	}

	// Projects the given 'pCurve' object into the plane(pt, vPlaneNormal)
	// The result will be returned in 'pCrvProj'
	virtual int CurvePlaneProjection( IN const OdGeCurve3d* pCurve, OUT OdGeCurve3d*& pCrvProj, const OdGePoint3d& pt, const OdGeVector3d& vPlaneNormal)
	{
		return 0;
	}
};

//==================================================================================================

extern "C" MCFLATTEN_API IMcFlattenSrv* getMcFlattenSrv();

//==================================================================================================
