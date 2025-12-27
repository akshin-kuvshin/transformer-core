#pragma once

#include "3DCore.h"
#include "IMcCutter.h"

IMCS_DECL_INTERFACE(McProfileContourData,"1111000B-3D3D-AAAA-AAAA-050B00000000")

//==============================================================================
enum McProfCntPtTypeEnum
{
	kMcProfCntPt_Unk    = 0,
	kMcProfCntPt_Close  = 1, // кривая замкнута и используется полностью
	kMcProfCntPt_Vertex = 2, // узловая вершина
	kMcProfCntPt_CCI    = 3, // точка пересечения
};
//==============================================================================
struct McProfCntPtData
{
	McProfCntPtTypeEnum mPtType;    // тип точки контура
	mcsWorkID           mIdGeomCrv; // ID исходного объекта-кривой, часть которой нужно взять для сегмента контура
	int                 mIdxSubCrv; // индекс подсегмента кривой, имеет смысл для полилинии, для остальных = 0
	McGe::EntityId      mGeomType1;

	bool                mfCodirect; // сонаправлен ли сегмент с исходной кривой

	// Для CA/EA хранит признак того, что использована меньшая часть дуги.
	// Логика такая: при разбиении CA/EA на две дуги, одна из них всегда короче другой
	// (случаи равенства оставим работать по-старому, через mfCodirect).
	// При восстановлении дуги из геометрии будем использовать этот признак, независимо
	// от выпуклости дуг.
	bool                mfCAEASmallerPart;

	// если тип вершины kMcProfCntPt_Vertex, то смысл таков:
	// -1: end, 0: start, 1, 2...: polyline middle vertex
	// если тип kMcProfCntPt_CCI, тогда это индекс точки пересечения
	// подсегментов кривых mIdGeomCrv::mIdxSubCrv и mIdGeomOtherCrv::mIdxOtherSubCrv
	int                 mIdxVtxOrIntPt;

	// Если тип точки = перечечение.
	// Нужно посчитать все пересечения кривой mIdGeomCrv с кривой mIdGeomOtherCrv,
	// отсортировать их в порядке увеличения параметра точек пересечения на первой кривой,
	// и взять точку с индексом mIdxVtxOrIntPt
	mcsWorkID           mIdGeomOtherCrv;
	McGe::EntityId      mGeomType2;
	int                 mIdxOtherSubCrv; // индекс подсегмента второй кривой

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MCTYP_API McProfCntPtData();

	MCTYP_API void reset();
	MCTYP_API bool isNull() const;
	MCTYP_API HRESULT save(IMcsStream* pS) const;
	MCTYP_API HRESULT load(IMcsStream* pS);

	MCTYP_API bool operator == (const McProfCntPtData& cw) const;
	MCTYP_API bool operator != (const McProfCntPtData& cw) const;
};


//==============================================================================
enum CrvOverlapEnum
{
	kCrvOverlap_ExactCounterdirect = -2, // совпадает и противонаправлена, концы тоже совпадают
	kCrvOverlap_Counterdirect      = -1, // совпадает и противонаправлена
	kCrvOverlap_None               =  0, // не совпадает
	kCrvOverlap_Codirect           =  1, // совпадает и сонаправлена
	kCrvOverlap_ExactCodirect      =  2, // совпадает и сонаправлена, концы тоже совпадают
};
//==============================================================================
typedef McsArray<McProfCntPtData, const McProfCntPtData&> McProfCntPtDataArray;
//==============================================================================
struct CrvMatchRes
{
	const mcsCurve* pStuffCurve;
	const mcsCurve* pStuffSubCurve;
	mcsWorkID       idStuffCurve;
	int             idxSubCurve;
	bool            fCodirect;

	CrvMatchRes();
	MCTYP_API void reset();
	MCTYP_API bool isNull() const;
};
//==============================================================================
struct McWIDPair
{
	// правило для значений:
	// mWID1 < mWID2 ||
	// mWID1 == mWID2 && mIdxSub1 <= mIdxSub2
	mcsWorkID mWID1, mWID2;
	int       mIdxSub1, mIdxSub2;

	MCTYP_API McWIDPair();
	MCTYP_API McWIDPair(const mcsWorkID& idCurve1, int idxSubCrv1, const mcsWorkID& idCurve2, int idxSubCrv2);
	MCTYP_API bool operator== (const McWIDPair& cw) const;
};
//==============================================================================
template <> __inline UINT __stdcall McsHashKey <const McWIDPair&> (const McWIDPair& key)
{
	// это не работает
	//UINT hash = (UINT)(key.mWID1.ID.Data1 ^ key.mWID2.ID.Data1);

	UINT h1 = McsHashKey <const mcsWorkID&> (key.mWID1);
	UINT h2 = McsHashKey <const mcsWorkID&> (key.mWID2) ^ (-1);
	UINT h3 = McsHashKey <__int64> (key.mIdxSub1);
	UINT h4 = McsHashKey <__int64> (key.mIdxSub2) ^ (-1);
	UINT hash = h1 ^ h2 ^ h3 ^ h4;

	return hash;
};
//==============================================================================
typedef McsMap<McWIDPair, const McWIDPair&, mcsPoint3dArray, const mcsPoint3dArray> mcsMapWIDPair2PtsArr;
//==============================================================================

// McProfileContourData обеспечиает хранение структуры контура профиля.
// После получения конутра определяет, из каких кусочков исходной геометрии (ИГ) состоит контур.
// Опорными являются концы кривых ИГ, вершины полилиний в ИГ, точки пересечения элементов ИГ.
// Эти даныне позволяют логически регенерировать контур после изменения формы ИГ.

struct McProfileContourData : public IMcProfileContourData
{
	IMCS_STD_METHOD_DEFINITION(McProfileContourData, IMcProfileContourData);

	McProfCntPtDataArray mVertices;
	int                  miClosed; // <0 - not, >0 - yes, 0 - undef

	// ассоциированный с данными контур;
	// restoreContour обновляет его, либо сбрасывает в случае ошибки;
	// storeContour перезаписывает его, даже если не удаётся сохранить структуру;
	mcsPolyline          mContour;

	// temp data
	mutable mcsMapWIDPair2PtsArr m__crossPoints;
	mutable const mapWID2MEG*    m__pGeomStuff2d;

	MCTYP_API McProfileContourData();

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	// IMcProfileContourData interface members

	MCTYP_API virtual bool    storeContour(const mapWID2MEG& geStuff2d, const mcsPolyline& srcContour, const mcsTol& tol = gp3dSite->tol()) override;
	MCTYP_API virtual bool    restoreContour(const mapWID2MEG& geStuff2d, const mcsTol& tol = gp3dSite->tol()) override;
	MCTYP_API virtual HRESULT save(IMcsStream* pStream) const override;
	MCTYP_API virtual HRESULT load(IMcsStream* pStream, const mcsTol& tol = gp3dSite->tol()) override;
	MCTYP_API virtual void    getContour(OUT mcsPolyline& contour) const override;

	MCTYP_API virtual HRESULT asListProfileEntities(
		const mapWID2MEG&               IDs2GeomMap,
		OUT McsArray<McsProfileEntity>& aEntities,
		OUT McsArray<McsCrossPoint>&    aPoints) const override;

		// выдаёт последовательность проекций, каждая из которых полностью использована в контуре,
		// все проекции лежат на одной базовой геом. кривой (т.е., напр., являются частью одной окржуности/эллипса)
	MCTYP_API virtual bool getClosedHomogeneousProjLoop(
		IN OUT McClosedHomogeneousProjLoopsData& loopData,
		OUT McsEntityGeometry&                   loopGeom_wcs) const override;

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	MCTYP_API void reset();

	MCTYP_API bool _linkNurbs(int idxSegToLinkWithPrev);

	MCTYP_API bool isEqualContour(const McProfileContourData& cw, const mcsTol& tol = gp3dSite->tol()) const;
	MCTYP_API bool isEqualStruct(const McProfileContourData& cw) const;

	// если было определено, что данный контур есть полная окружность, то пытается
	// создать для неё правило построения на основе всех доступных дуг и окружностей эскиза
	MCTYP_API bool _storeFullCAContour(const mapWID2MEG& geStuff2d, const mcsCircArc& srcCA, const mcsTol& tol = gp3dSite->tol());

	// если было определено, что данный контур есть полный эллипс, то пытается
	// создать для неё правило построения на основе всех доступных эллиптических дуг и эллипсов эскиза
	MCTYP_API bool _storeFullEAContour(const mapWID2MEG& geStuff2d, const mcsEllipArc& srcEA, const mcsTol& tol = gp3dSite->tol());

	// определяет кол-во точек пересечения (не контакта) между указанынми кривыми
	MCTYP_API int  _getStuffCrossPointsCount(const mcsWorkID& wid1, int idxSubCrv1, const mcsWorkID& wid2, int idxSubCrv2, const mcsTol& tol = gp3dSite->tol()) const;

	// выдаёт точку пересечения между указанными кривыми по индексу.
	// точки пересечения отсортированы в порядке увеличения параметра точек на первой кривой,
	// поэтому индекс имеет перманентный смысл по тоношению к изменчивой геометрии обоих кривых
	MCTYP_API bool _getStuffCrossPoint(const mcsWorkID& wid1, int idxSubCrv1, const mcsWorkID& wid2, int idxSubCrv2, int idxPoint, OUT mcsPoint&, const mcsTol& tol = gp3dSite->tol()) const;

	// определяет положение начальной точки указанного сегмента в контуре.
	// если fStart==false, то будет идентифицировать конец кривой
	MCTYP_API bool _identifyVertex(bool fStart, const mcsCurve* pSeg, OUT McProfCntPtData& vtxData, const mcsTol& tol = gp3dSite->tol());

	// находим WID исходной кривой, с которой есть хотя бы частичное совпадение
	MCTYP_API bool _identifyStuffCurve(
		const mcsCurve*      pSeg,
		OUT CrvMatchRes&     crvIdentRes, 
		const mcsTol& tol = gp3dSite->tol());

	// проверяет, явлется ли данный контур полностью замкнутой окружностью;
	// это нужно т.к. полилиния не может хранить окружность в виде одного сегмента,
	// в результате чего нет возможность получить правило построения контура по узловым
	// точкам, как это делается для всех других типов контуров
	MCTYP_API bool _isAFullCircle(const mcsPolyline&, OUT mcsCircArc& CA, const mcsTol& tol = gp3dSite->tol());
	MCTYP_API bool _isAFullEllipse(const mcsPolyline&, OUT mcsEllipArc& EA, const mcsTol& tol = gp3dSite->tol());

	// определяем, имеет ли кривая pCurveToCheck какую-то часть, совпадающую с кривой pStuffCurve
	MCTYP_API static CrvOverlapEnum _sIsCurvePartOfStuffCurve(const mcsCurve* pCurveToCheck, const mcsCurve* pStuffCurve, const mcsTol& tol = gp3dSite->tol());
};
//==============================================================================
MCTYP_API bool _areEqualPolylines4Profile(const mcsPolyline& pl1, const mcsPolyline& pl2, const mcsTol& tol = gp3dSite->tol());
MCTYP_API bool _joinSimilarPolylineSegments(IN const mcsPolyline& pl, OUT mcsPolyline& optimizedPolyline, const mcsTol& tol = gp3dSite->tol());
//==============================================================================
