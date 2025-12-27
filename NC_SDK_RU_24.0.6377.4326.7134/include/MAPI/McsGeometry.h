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

#ifdef _VERBOSEHEADERS_
	#pragma message("Use " __FILE__)
#endif

#define MCSGEOM_INCLUDED

#include <math.h>
#include <float.h>

#include "McsTypes.h"
#include "McsTempl.h"
#include "mcsutils.h"

#include "McAPIs.h"

#include "McGe\mcsBoundBlock.h"

#ifndef MCGELDLL

	#ifndef MCTYP_DLL
	 #pragma comment(lib,"mctyp.lib")
	#endif

#else

	#undef MCTYP_API
	#define MCTYP_API

#endif // MCGELDLL

struct McsEntityGeometry;

//==============================================================================
// means that default color for specified linetype will be set
#define MCS_ENTCOLOR_BYLINETYPE  0xFF000000
#define MCS_ENTCOLOR_BYLAYER     0xFE000000
#define MCS_ENTCOLOR_BYBLOCK     0xFD000000
#define MCS_ENTCOLOR_BYCONTEXT   0xFC000000
#define MCS_ENTCOLOR_FOREGROUND  0xFB000000 // Цвет фона документа
#define MCS_ENTCOLOR_NONE        0xFA000000 // Отсутствие цвета, заливки
#define MCS_ENTCOLOR_BYDEFAULT   MCS_ENTCOLOR_NONE
/*
Reserved values. Not use!!! Now used in Tables only (#4311).
#define MCS_ENTCOLOR_BY_PARAM_LINETYPE9		0xF9000000
#define MCS_ENTCOLOR_BY_PARAM_LINETYPE8		0xF8000000
#define MCS_ENTCOLOR_BY_PARAM_LINETYPE7		0xF7000000
#define MCS_ENTCOLOR_BY_PARAM_LINETYPE6		0xF6000000
#define MCS_ENTCOLOR_BY_PARAM_LINETYPE5		0xF5000000
#define MCS_ENTCOLOR_BY_PARAM_LINETYPE4		0xF4000000
#define MCS_ENTCOLOR_BY_PARAM_LINETYPE3		0xF3000000
#define MCS_ENTCOLOR_BY_PARAM_LINETYPE2		0xF2000000
#define MCS_ENTCOLOR_BY_PARAM_LINETYPE1		0xF1000000
*/
#define MCS_ENTCOLOR_TRUE_COLOR  0xF0000000 // Изначально TrueColor цвет, а не индексный.
typedef COLORREF mcsColor;
typedef McsArray<mcsColor, mcsColor> mcsColorsArray;

#define MCS_ENTWEIGHT_BYLINETYPE  -3
#define MCS_ENTWEIGHT_BYLAYER     -1
#define MCS_ENTWEIGHT_BYBLOCK     -2
#define MCS_ENTWEIGHT_BYCONTEXT   -4
#define MCS_ENTWEIGHT_BYDEFAULT   -5
/*
Reserved values. Not use!!! Now used in Tables only (#4311).
#define MCS_ENTWEIGHT_BY_PARAM_LINETYPE9	-19
#define MCS_ENTWEIGHT_BY_PARAM_LINETYPE8	-18
#define MCS_ENTWEIGHT_BY_PARAM_LINETYPE7	-17
#define MCS_ENTWEIGHT_BY_PARAM_LINETYPE6	-16
#define MCS_ENTWEIGHT_BY_PARAM_LINETYPE5	-15
#define MCS_ENTWEIGHT_BY_PARAM_LINETYPE4	-14
#define MCS_ENTWEIGHT_BY_PARAM_LINETYPE3	-13
#define MCS_ENTWEIGHT_BY_PARAM_LINETYPE2	-12
#define MCS_ENTWEIGHT_BY_PARAM_LINETYPE1	-11
*/
#define MCS_ENTLTYPE_BYCONTEXT   0
#define MCS_ENTLTYPE_BYLAYER     -1
#define MCS_ENTLTYPE_BYBLOCK     -2
#define MCS_ENTLTYPE_CONTINUOUS  -3 // Используется только в IMcStyleManager::getStdLinetypeName(). Ни в getXXX, ни в setXXX применять нельзя.

typedef int mcsLinetype;
typedef McsArray<mcsLinetype, mcsLinetype> mcsLinetypesArray;

#define MCSTEXT_DEFOBLIQUE -10

//==============================================================================
// enum used in universal entity monitor so some values have not means
enum EntityGeometryTypeEnum
{
	kMcsNull            = 0x00000000,

	kMcsPoint           = 0x00000001,
	kMcsVertex          = 0x00000002,

	kMcsLine            = 0x00000100,
	kMcsCircArc         = 0x00000200,
	kMcsEllipticArc     = 0x00000400,
	kMcsSpline          = 0x00000800,
	kMcsPolyline        = 0x00001000,
	kMcsXLine           = 0x00002000,
	kMcsRay             = 0x00004000,
	kMcsOfsCrv          = 0x00008000,
	kMcsLinear          = kMcsLine | kMcsXLine | kMcsRay,

	kMcsPlaneSegment    = 0x00010000,
	kMcsCylinderSegment = 0x00020000,
	kMcsConeSegment     = 0x00040000,
	kMcsTorusSegment    = 0x00080000,
	kMcsSphereSegment   = 0x00100000,
	kMcsTriangleSegment = 0x00200000,
	kMcsBSplineSegment  = 0x00400000,

	kMcsComponent       = 0x01000000, // compatible only with <kMcsPoint>
	kMcsText            = 0x02000000,
	kMcsHatch           = 0x04000000,
	kMcsArrow           = 0x08000000,
	kMcs3dImageRef      = 0x10000000, // Facets/Strokes 3d-preview

	kMcsDimArrow        = 0x00000010,
	kMcsRepeatedShape   = 0x00000020,
	kMcsObjGeomRef      = 0x00000040,
	kMcsMesh            = 0x00000080,

	// composed values
	kMcsCurveEntities =
		kMcsLine | kMcsXLine | kMcsRay |
		kMcsCircArc | kMcsEllipticArc | kMcsSpline | kMcsPolyline | kMcsOfsCrv,

	kMcsSurfaceEntities =
		kMcsPlaneSegment | kMcsCylinderSegment | kMcsConeSegment | kMcsTorusSegment |
		kMcsSphereSegment | kMcsTriangleSegment | kMcsBSplineSegment,

	kMcsAllEntities = kMcsPoint | kMcsVertex | kMcsCurveEntities | kMcsSurfaceEntities
};
//====================================================================================

#pragma warning(disable: 4275) // An exported class was derived from a class that was not exported.
#pragma warning(disable: 4251) // A base class or structure must be declared with the __declspec(dllexport) keyword if a function in a derived class is to be exported.

#ifdef NOACGE
	#ifdef MCGEL
		#include "McGeometry.h"
	#elif defined(DDGEL)
		#include "OdGeometry.h"
	#endif

#ifndef ACGATE

#define AcGeEntity3d              USE_mcsEntity_INSTEAD
#define AcGeEntity2d              USE_mcsEntity2d_INSTEAD
#define AcGePoint3d               USE_mcsPoint_INSTEAD
#define AcGePoint2d               USE_mcsPoint2d_INSTEAD
#define AcGePointEnt3d            USE_mcsPointEnt_INSTEAD
#define AcGePointEnt2d            USE_mcsPointEnt2d_INSTEAD
#define AcGeVector3d              USE_mcsVector_INSTEAD
#define AcGeVector2d              USE_mcsVector2d_INSTEAD
#define AcGeMatrix3d              USE_mcsMatrix_INSTEAD
#define AcGeMatrix2d              USE_mcsMatrix2d_INSTEAD
#define AcGeLine3d                USE_mcsLine_INSTEAD
#define AcGeLine2d                USE_mcsLine2d_INSTEAD
#define AcGeLinearEnt3d           USE_mcsLinearEntity_INSTEAD
#define AcGeLinearEnt2d           USE_mcsLinearEntity2d_INSTEAD
#define AcGeLineSeg3d             USE_mcsLineSeg_INSTEAD
#define AcGeLineSeg2d             USE_mcsLineSeg2d_INSTEAD
#define AcGeRay3d                 USE_mcsRay_INSTEAD
#define AcGeRay2d                 USE_mcsRay2d_INSTEAD
#define AcGeCurve3d               USE_mcsCurve_INSTEAD
#define AcGeCurve2d               USE_mcsCurve2d_INSTEAD
#define AcGeNurbCurve3d           USE_mcsNurbCurve_INSTEAD
#define AcGeNurbCurve2d           USE_mcsNurbCurve2d_INSTEAD
#define AcGeSplineEnt2d           USE_mcsSplineEnt2d_INSTEAD
#define AcGeSplineEnt3d           USE_mcsSplineEnt3d_INSTEAD
#define AcGeCircArc3d             USE_mcsCircArc_INSTEAD
#define AcGeCircArc2d             USE_mcsCircArc2d_INSTEAD
#define AcGeEllipArc3d            USE_mcsEllipArc_INSTEAD
#define AcGeEllipArc2d            USE_mcsEllipArc2d_INSTEAD
#define AcGeBoundBlock3d          USE_mcsBounds_INSTEAD
#define AcGeBoundBlock2d          USE_mcsBounds2d_INSTEAD
#define AcGePointOnCurve3d        USE_mcsPointOnCurve_INSTEAD
#define AcGePointOnCurve2d        USE_mcsPointOnCurve2d_INSTEAD
#define AcGePointOnSurface        USE_mcsPointOnSurf_INSTEAD
#define AcGeCurveCurveInt3d       USE_mcsCurveCurveInt_INSTEAD
#define AcGeCurveCurveInt2d       USE_mcsCurveCurveInt2d_INSTEAD
#define AcGeCompositeCurve3d      USE_mcsCompositeCurve_INSTEAD
#define AcGeCompositeCurve2d      USE_mcsCompositeCurve2d_INSTEAD
#define AcGeOffsetCurve3d         USE_mcsOffsetCurve_INSTEAD
#define AcGeOffsetCurve2d         USE_mcsOffsetCurve2d_INSTEAD
#define AcGe                      USE_mcsGe_INSTEAD
#define AcGeError                 USE_mcsGeError_INSTEAD
#define AcGePlane                 USE_mcsPlane_INSTEAD
#define AcGeBoundedPlane          USE_mcsBoundedPlane_INSTEAD
#define AcGePlanarEnt             UCS_mcsPlanarEnt_INSTEAD
#define AcGeNurbSurface           USE_mcsNurbSurf_INSTEAD
#define AcGeTol                   USE_mcsTol_INSTEAD
#define AcGeInterval              USE_mcsInterval_INSTEAD
#define AcGeContext               USE_mcsGeContext_INSTEAD
#define Adesk                     USE_CSOmsk_INSTEAD
#define AcGePoint3dArray          USE_mcsGePoints3dArr_INSTEAD
#define AcGeVector3dArray         USE_mcsGeVectors3dArr_INSTEAD
#define AcGePoint2dArray          USE_mcsGePoints2dArr_INSTEAD
#define AcGeVector2dArray         USE_mcsGeVectors2dArr_INSTEAD
#define AcGeVoidPointerArray      USE_mcsGeVoidPtrArr_INSTEAD
#define AcGeDoubleArray           USE_mcsGeDoubleArr_INSTEAD
#define AcGeIntArray              USE_mcsGeIntArr_INSTEAD
#define AcGeAugPolyline3d         USE_mcsAugPolyline3d_INSTEAD
#define AcGePosition3d            USE_mcsPosition3d_INSTEAD
#define AcGeKnotVector            USE_mcsKnotVector_INSTEAD

#define AcGeSurface               USE_mcsSurface_INSTEAD
#define AcGeSphere                USE_mcsGeSphere_INSTEAD
#define AcGeCone                  USE_mcsGeCone_INSTEAD
#define AcGeCylinder              USE_mcsGeCylinder_INSTEAD
#define AcGeGeTorus               UCS_mcsGeTorus_INSTEAD

#endif // ACGATE

#else // NOACGE

	// geometry primitives from ACGE library
	#define mcsEntity          AcGeEntity3d
#define mcsEntity3d          AcGeEntity3d
#define mcsEntity2d          AcGeEntity2d
	#define mcsPoint           AcGePoint3d
#define mcsPoint3d           AcGePoint3d
#define mcsPoint2d           AcGePoint2d
	#define mcsPointEnt        AcGePointEnt3d
#define mcsPointEnt3d        AcGePointEnt3d
#define mcsPointEnt2d        AcGePointEnt2d
	#define mcsVector          AcGeVector3d
#define mcsVector2d          AcGeVector2d
#define mcsVector3d          AcGeVector3d
	#define mcsMatrix2d        AcGeMatrix2d
#define mcsMatrix3d          AcGeMatrix3d
	#define mcsLine            AcGeLine3d
#define mcsLine3d            AcGeLine3d
#define mcsLine2d            AcGeLine2d
	#define mcsRay             AcGeRay3d
#define mcsRay3d             AcGeRay3d
#define mcsRay2d             AcGeRay2d
	#define mcsLinearEntity    AcGeLinearEnt3d
#define mcsLinearEntity3d    AcGeLinearEnt3d
#define mcsLinearEntity2d    AcGeLinearEnt2d
	#define mcsLineSeg         AcGeLineSeg3d
#define mcsLineSeg3d         AcGeLineSeg3d
#define mcsLineSeg2d         AcGeLineSeg2d
	#define mcsCurve           AcGeCurve3d
#define mcsCurve3d           AcGeCurve3d
#define mcsCurve2d           AcGeCurve2d
	#define mcsNurbCurve       AcGeNurbCurve3d
#define mcsNurbCurve3d       AcGeNurbCurve3d
#define mcsNurbCurve2d       AcGeNurbCurve2d
	#define mcsCircArc         AcGeCircArc3d
#define mcsCircArc3d         AcGeCircArc3d
#define mcsCircArc2d         AcGeCircArc2d
	#define mcsEllipArc        AcGeEllipArc3d
#define mcsEllipArc3d        AcGeEllipArc3d
#define mcsEllipArc2d        AcGeEllipArc2d
	#define mcsNurbCurve       AcGeNurbCurve3d
	#define mcsSpline          AcGeNurbCurve3d
#define mcsSpline3d          AcGeNurbCurve3d
#define mcsSpline2d          AcGeNurbCurve2d
	#define mcsSplineEnt       AcGeSplineEnt3d
#define mcsSplineEnt3d       AcGeSplineEnt3d
#define mcsSplineEnt2d       AcGeSplineEnt2d
	#define mcsBounds          AcGeBoundBlock3d
#define mcsBounds3d          AcGeBoundBlock3d
#define mcsBounds2d          AcGeBoundBlock2d
	#define mcsPointOnCurve    AcGePointOnCurve3d
#define mcsPointOnCurve3d    AcGePointOnCurve3d
#define mcsPointOnCurve2d    AcGePointOnCurve2d
#define mcsPointOnSurf       AcGePointOnSurface
	#define mcsCurveCurveInt   AcGeCurveCurveInt3d
#define mcsCurveCurveInt3d   AcGeCurveCurveInt3d
#define mcsCurveCurveInt2d   AcGeCurveCurveInt2d
	#define mcsPointOnCurve    AcGePointOnCurve3d
	#define mcsCompositeCurve  AcGeCompositeCurve3d
#define mcsCompositeCurve3d  AcGeCompositeCurve3d
#define mcsCompositeCurve2d  AcGeCompositeCurve2d
	#define mcsOffsetCurve     AcGeOffsetCurve3d
#define mcsOffsetCurve3d     AcGeOffsetCurve3d
#define mcsOffsetCurve2d     AcGeOffsetCurve2d
	#define mcsAugPolyline     AcGeAugPolyline3d
#define mcsAugPolyline3d     AcGeOffsetCurve3d
	#define mcsPosition        AcGePosition3d
#define mcsPosition3d        AcGePosition3d
#define mcsKnotVector        AcGeKnotVector

#define mcsSurface           AcGeSurface
#define mcsGeSphere          AcGeSphere
#define mcsGeCone            AcGeCone
#define mcsGeCylinder        AcGeCylinder
#define mcsGeTorus           AcGeTorus

#define mcsGe                AcGe
#define mcsGeError           AcGeError
#define CSOmsk               Adesk
#define mcsPlane             AcGePlane
#define mcsBoundedPlane      AcGeBoundedPlane
#define mcsPlanarEnt         AcGePlanarEnt
#define mcsNurbSurf          AcGeNurbSurface
#define mcsTol               AcGeTol
#define mcsInterval          AcGeInterval
#define mcsGeContext         AcGeContext
#define mcsOffsetCrvExtType  AcGe::OffsetCrvExtType
#define mcsTrue              Adesk::kTrue
#define mcsFalse             Adesk::kFalse
#define mcsBoolean           Adesk::Boolean

#define mcsGePoints3dArr     AcGePoint3dArray
#define mcsGeVectors3dArr    AcGeVector3dArray
#define mcsGePoints2dArr     AcGePoint2dArray
#define mcsGeVectors2dArr    AcGeVector2dArray
#define mcsGeVoidPtrArr      AcGeVoidPointerArray
#define mcsGeDoubleArr       AcGeDoubleArray
#define mcsGeIntArr          AcGeIntArray

#include "geent2d.h"
#include "geent3d.h"
#include "gepnt2d.h"
#include "gepnt3d.h"
#include "gemat2d.h"
#include "gemat3d.h"
#include "gevec2d.h"
#include "gevec3d.h"
#include "gecurv2d.h"
#include "gecurv3d.h"
#include "gelnsg2d.h"
#include "gelnsg3d.h"
#include "geline2d.h"
#include "geline3d.h"
#include "geray3d.h"
#include "gearc2d.h"
#include "gearc3d.h"
#include "geplin2d.h"
#include "geplin3d.h"
#include "genurb2d.h"
#include "genurb3d.h"
#include "geell2d.h"
#include "geell3d.h"
#include "geblok2d.h"
#include "geblok3d.h"
#include "gept2dar.h"
#include "gept3dar.h"
#include "gecint2d.h"
#include "gecint3d.h"
#include "geplane.h"
#include "geintrvl.h"
#include "genurbsf.h"
#include "gecomp2d.h"
#include "gecomp3d.h"
#include "geoffc3d.h"
#include "geapln3d.h"
#include "gepos3d.h"
#include "gekvec.h"
#include "gesurf.h"
#include "gesphere.h"
#include "gecone.h"
#include "gecylinder.h"
#include "getorus.h"

#endif //	!defined(NOACGE)

extern MCTYP_API mcsTol gDefTol; // initialized by DEF_TOL

//==================================================================================================

typedef McsArray <mcsPoint, const mcsPoint&>       mcsPoint3dArray;
typedef McsArray <mcsVector, const mcsVector&>     mcsVector3dArray;
typedef McsArray <mcsLineSeg, const mcsLineSeg&>   mcsLineSegArray;
typedef McsArray<mcsCurve*, mcsCurve*>             mcsCurvesArray;
typedef McsArray<const mcsCurve*, const mcsCurve*> mcsConstCurvesArray;

#ifndef CCI_POINT_ARR_DEFINED
	#define CCI_POINT_ARR_DEFINED
	struct cci_point;
	typedef McsArray<cci_point> cci_point_arr;
#endif

typedef bool (* SurfGeomCurveIntersectionProc)(const McsEntityGeometry&, const mcsCurve&, cci_point_arr&, mcsVector3dArray*, const mcsTol&);
extern "C" MCGEL_API SurfGeomCurveIntersectionProc pExternalSurfCurveIntersectionProc;

enum McGeomOverlapStatusEnum;
typedef bool (* SurfSurfCheckOverlappingProc)(const McsEntityGeometry&, const McsEntityGeometry&, OUT McGeomOverlapStatusEnum&, const mcsTol&);
extern "C" MCGEL_API SurfSurfCheckOverlappingProc pExternalSurfSurfCheckOverlapping;

//==================================================================================================

class CxImage;

enum EntityGeometryTypeEnum;
typedef McsArray<EntityGeometryTypeEnum, EntityGeometryTypeEnum> mcsGeomTypeArray;

//==============================================================================
template <class GeomEntArrType>
void transformGeomArrBy(GeomEntArrType& geArr, const mcsMatrix3d& tfm)
{
	int i, n = geArr.GetSize();
	for(i=0; i<n; i++)
		geArr[i].transformBy(tfm);
}
//==============================================================================
template <class GeomEntArrType>
bool isEqualToGeomArr
(const GeomEntArrType& geArr1,
 const GeomEntArrType& geArr2,
 const mcsTol&         tol = mcsGeContext::gTol)
{
	if(&geArr1 == &geArr2)
		return true;

	int i, n = geArr1.GetSize(), n2 = geArr2.GetSize();
	if(n != n2)
		return false;

	for(i=0; i<n; i++){
		if(!geArr1[i].isEqualTo(geArr2[i], tol))
			return false;
	}
	return true;
}
//==============================================================================

#ifndef MCGELDLL

struct mcsText;
typedef HRESULT (__cdecl* GetFragmentBoundsProc)(const mcsText* self, int iStart, int iEnd, mcsBoundBlocksArray& bounds);
extern "C" MCTYP_API GetFragmentBoundsProc mcsTextGetFragmentBoundsImpl;
typedef void (__cdecl* mcsTextPrepareProc)(mcsText&, mcsBoundBlock*);
extern "C" MCTYP_API mcsTextPrepareProc gpMcTxtPrep;
typedef int (__cdecl* mcsTextHitTestProc)(const mcsText& text, const mcsPoint& pnt);
extern "C" MCTYP_API mcsTextHitTestProc gpMcTextHitTest;
#define DECL_PROPERTY(class,name) class m_##name; _declspec(property(get=get_##name,put=set_##name)) class name

class mcsImpPline3d;

#include "mechmath.h"

//==============================================================================
class mcsGeomEntArray : public McsArray<McsEntityGeometry,const McsEntityGeometry&>
{
protected:
	bool m_bAddContentsToExternalStorage;

public:
  DECLARE_OBJ_NEWDEL;

	mcsGeomEntArray()
	{
		m_bAddContentsToExternalStorage = false;
	}

	MCTYP_API bool isEqualTo(const mcsGeomEntArray& cw, const mcsTol& tol = mcsGeContext::gTol, IN OPTIONAL bool fCmpGeomOnly = false) const;
	MCTYP_API bool transformBy(const mcsMatrix& tfm);

	MCTYP_API bool init(int nNewSize, EntityGeometryTypeEnum elementsType);

	MCTYP_API void setVisible(bool fVisible);
	MCTYP_API void setTransparency(int iTransparency); // 0..100, 0 = opaque/visible, 100 = completely transparent/invisible
	MCTYP_API void setColor(COLORREF newColor);
	MCTYP_API void setLineWeight(int iLineWeight);
	MCTYP_API void setLineType(int lt);

	MCTYP_API mcsBoundBlock getBoundBlock(bool bIncludeAxis=false) const;
	MCTYP_API mcsBoundBlock getOrthoBoundBlock() const;

	MCTYP_API bool areEquAs3dNodes(IN const mcsGeomEntArray& cw, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol, IN OPTIONAL bool fCmpGeomOnly = false) const;

	//................................................................
	// returns <0 if not found
	MCTYP_API int getNearestEnt(const mcsPoint& pickPoint, OUT OPTIONAL double* pDistance=NULL) const;

	// Матрица проекции должна быть задана для плоскости XY, т.к. после проекции Z игнорируется.
	// (!) Матрица должна быть обратима.
	MCTYP_API int getNearestEnt(const mcsPoint& pickPoint, IN OPTIONAL const mcsMatrix* pXyProjTfm) const;

	MCTYP_API bool getNearestEnt(McsEntityGeometry& simpleEnt,  const mcsPoint& pickPoint) const;

	MCTYP_API int getNearestEntAmongClosest(const mcsPoint& pickPoint, double dMaxDist, OUT OPTIONAL double* pDistance) const;

	// Матрица проекции должна быть задана для плоскости XY, т.к. после проекции Z игнорируется.
	// (!) Матрица должна быть обратима.
	MCTYP_API int getNearestEntAmongClosest(
		const mcsPoint&              pickPoint,
		IN OPTIONAL const mcsMatrix* pXyProjTfm,
		double                       dMaxDist,
		OUT OPTIONAL double*         pDistance) const;

	MCTYP_API void clearExProperties();

	MCTYP_API int findByGSMarker(__int64 iGSMarker);

	void setAddContentsFlag(bool bAdd) {
		m_bAddContentsToExternalStorage = bAdd;
	}

	bool doAddContents() const {
		return m_bAddContentsToExternalStorage;
	}
};

//==============================================================================

#define MC_DEF_PL_WIDTH 0.

//==============================================================================

enum McPolylineWidthTypeEnum
{
	kMcPolyWidthData_unk    = -1, // не возвращается как результат
	kMcPolyNoWidthData      =  0, // данные ширины не заданы
	kMcPolyVtxConstantWidth =  1, // данные ширины заданы на вершинах, и ширина не меняется
	kMcPolyVtxVariableWidth =  2, // на вершинах заданы переменные данные ширины
	kMcPolyConstantWidth    =  3, // на вершинах нет данных ширины, задана ширина на всю полилинию
};
//==============================================================================

struct MCTYP_API mcsPline3dVertex
{
	double    rWidths[2];
	double    bulge; // не 0 для круговой дуги
	mcsPoint  pnt;
	mcsVector normal; // для NURB-сегмента нормаль нулевая, по правилам должна определяться через pNurb->isPlanar
	__int64   dataI64; // для сохраняемых данных

	// не сохраняется в стрим
	// признак того, что вершина была добавлена автоматически при формировании полилинии,
	// и может быть удалена, если будет продублирована явным добавлением
	bool      _fAutoAdded;

	// пользовательские данные, не пишутся в стрим
	DWORD_PTR data;  // целое, с возможностью хранения указателей
	double    rdata; // вещественное число

	// Ellipse и NURB нужно устанавливать в объект либо через конструктор, либо методами setEllipse, setNurb

	// ellipse data
	// AGL, 21.01.2011, в старом варианте не сохранялись нормаль, центр и угол раствора элиптической дуги,
	// что было невозможно в 100% случаев восстановить по ранее сохраняемым данным;
	// Такой результат определён массированным тестом в MCGEL ( ExpTests.cpp\MiscTest_26() )
protected:
	mcsEllipArc*  mpEA;

		// AGL, 16.06.2011
	mcsNurbCurve* mpNurb; // сплайновый участок - NURB
	__int64       _internalData; // used by the implementation of the polyline class

public:
		// сохранять гладкость касательной у сплайна в начале и конце соотв.
		// если идут подряд два не склеенных сплайна, то касательная в начале последующего 
		// зависит от ксательной в конце предыдущего сплайна, (а вообще нужно сращивать такие сплайны при добавлении)
	bool          fNurbTanBefore, fNurbTanAfter; 

	DECLARE_OBJ_NEWDEL;

	mcsPline3dVertex();
	mcsPline3dVertex( const mcsPoint2d& pt, double blg, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH );
	mcsPline3dVertex( const mcsPoint3d& pt, double blg, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, mcsVector3d normal = mcsVector3d::kZAxis  );
	~mcsPline3dVertex();

	// AGL, 21.01.2011
	mcsPline3dVertex(const mcsEllipArc& elliseSegment, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH);
	void setEllipse(const mcsEllipArc* pElliseSegment);

	// AGL, 16.06.2011
	mcsPline3dVertex(const mcsNurbCurve& splineSegment, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, bool fKeepTanAtNURBsStart = false, bool fKeepTanAtNURBsEnd = false);
	void setNurb(const mcsNurbCurve* pNurbSegment, bool fKeepTanAtNURBsStart = false, bool fKeepTanAtNURBsEnd = false);

	mcsPline3dVertex( const mcsPline3dVertex* pSrc );
	mcsPline3dVertex( const mcsPline3dVertex& src );
	bool isZeroBulge( ) const; // не зависит от точности, просто является ли bulge допустимым
	bool isValidBulge( const mcsTol& tol = mcsGeContext::gTol ) const; // корректность значения bulge при точности tol
	bool isPoint() const;
	void convertToPoint(bool fSetAutoadded = false);
	mcsPoint endPt() const;

	McPolylineWidthTypeEnum widthType() const;

	mcsPline3dVertex& transformBy(
		const mcsMatrix3d& tfm,
		bool               fInvert, // если tdm.det() < 0 должно быть true
		double             scale);  // = tfm.scale()

	bool convertCA2EA(const mcsPline3dVertex& nextVrt);

	mcsCurve* heldCurve();
	const mcsCurve* heldCurve() const;

	mcsEllipArc* pEllipse() 
		{return mpEA;}
	const mcsEllipArc* pEllipse() const
		{return mpEA;}
	mcsNurbCurve* pNURB() 
		{return mpNurb;}
	const mcsNurbCurve* pNURB() const
		{return mpNurb;}

	mcsPline3dVertex& operator = (const mcsPline3dVertex& scrVrt);

	friend class mcsPline3d;
	friend class mcsImpPline3d;
};

typedef McsArray<mcsPline3dVertex, const mcsPline3dVertex&> mcsPline3dVertices;
//==============================================================================
// точность по умолчанию для полилиний
extern MCTYP_API const mcsTol gDefPolTol;
//==============================================================================
class mcsPolylineArray;
struct mcsPline3dOffsetData;
//==============================================================================
//#pragma warning(default: 4800) // forcing value to bool 'true' or 'false' // для отлова неявного превращения double -> bool
//==============================================================================

#ifdef MCGEL
	#define PLINE_OVERRIDE override
#else
	#define PLINE_OVERRIDE
#endif

//==============================================================================
class MCTYP_API mcsPline3d : public mcsCompositeCurve3d
{
public:
		// (!) порядок и значение не менять, пишется в стрим
		enum SegType
		{
			kLine,
			kArc,
			kEllipse,
			kNurb,
			kCoincident, // вырожденный в точку сегмент
			kEmpty
		};

public:

	mcsPline3d();
	mcsPline3d(const mcsPline3d&);

		// adds num_verts point-vertices
	mcsPline3d(unsigned int num_verts);

		// init pline by given fit-points, and given normal
	mcsPline3d(const mcsPoint3dArray& fitPoints, const mcsVector& vNormal = mcsVector::kZAxis);
	mcsPline3d(const mcsPoint* pFitPoints,int nFitPoints, const mcsVector& vNormal = mcsVector::kZAxis);

		// init pline by given fit-points with bulges, and given normal;
		// minmal dimension of fitPoints and bulges will be taken
	mcsPline3d(const mcsPoint3dArray& fitPoints, const mcsDoubleArray& bulges, const mcsVector& vNormal = mcsVector::kZAxis);

	virtual ~mcsPline3d();

	virtual mcsGe::EntityId type() const PLINE_OVERRIDE;
	virtual mcsBoolean   isKindOf (mcsGe::EntityId entType) const PLINE_OVERRIDE;

	void set(unsigned int num_verts);
	void set(const mcsPoint3dArray& fitPoints, const mcsVector& vNormal = mcsVector::kZAxis);
	void set(const mcsPoint3dArray& fitPoints, const mcsDoubleArray& bulges, const mcsVector& vNormal = mcsVector::kZAxis);
	void set(const mcsPoint* pFitPoints, int nFitPoints, const mcsVector& vNormal = mcsVector::kZAxis);

	bool addVertex    (const mcsPoint2d& pt, double bulge = 0., double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, const mcsTol& tol = gDefPolTol);
	bool addVertex    (const mcsPoint3d& pt, double bulge = 0., double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, mcsVector3d normal = mcsVector3d::kZAxis, const mcsTol& tol = gDefPolTol);
	bool addVertex    (const mcsPline3dVertex &vrt, bool fAutoLinkNurbs = false, const mcsTol& tol = gDefPolTol);

		// AGL, 20.06.2014, следующие методы автоматически подбирают сторону добавления сегмента, а также
		// выполняют автореверс кривой, если это нужно для стыковки. При этом, если добавлемый сегмент реверсируется,
		// то параметры ширины, сглаживания в начале/конце добавляемой кривой применяются к уже реверсивной кривой.
		// То есть startWidth, к примеру, будет применён к концу кривой, если для стыковки надо изменить её напрвление.
	bool addSegment   (const mcsLineSeg &line, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, const mcsTol& tol = gDefPolTol);
	bool addSegment   (const mcsCircArc &arc, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, const mcsTol& tol = gDefPolTol);
	bool addSegment   (const mcsEllipArc &arc, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, const mcsTol& tol = gDefPolTol);
	bool addSegment   (const mcsNurbCurve &nurb, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, bool fKeepTanAtNURBsStart = true, bool fKeepTanAtNURBsEnd = true, bool fAutoLinkNurbs = false, const mcsTol& tol = gDefPolTol);
	bool addGeometry  (const McsEntityGeometry &geom, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, bool fKeepTanAtNURBsStart = true, bool fKeepTanAtNURBsEnd = true, bool fAutoLinkNurbs = false, const mcsTol& tol = gDefPolTol);
	bool addCurve     (const mcsCurve &curve, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, bool fKeepTanAtNURBsStart = true, bool fKeepTanAtNURBsEnd = true, bool fAutoLinkNurbs = true, const mcsTol& tol = gDefPolTol);
	bool addPolyline  (const mcsPline3d& polyline, const mcsTol& tol = gDefPolTol);

	bool addVertexAt  (unsigned int index, const mcsPoint2d& pt, double bulge = 0., double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, const mcsTol& tol = gDefPolTol);
	bool addVertexAt  (unsigned int index, const mcsPoint3d& pt, double bulge = 0., double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, mcsVector3d normal = mcsVector3d::kZAxis, const mcsTol& tol = gDefPolTol);
	bool addVertexAt  (unsigned int index, const mcsPline3dVertex &vrt, bool fAutoLinkNurbs = false, const mcsTol& tol = gDefPolTol);
	bool addSegmentAt (unsigned int index, const mcsLineSeg &line, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, const mcsTol& tol = gDefPolTol);
	bool addSegmentAt (unsigned int index, const mcsCircArc &arc, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, const mcsTol& tol = gDefPolTol);
	bool addSegmentAt (unsigned int index, const mcsEllipArc &arc, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, const mcsTol& tol = gDefPolTol);
	bool addSegmentAt (unsigned int index, const mcsNurbCurve &nurb, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, bool fKeepTanAtNURBsStart = true, bool fKeepTanAtNURBsEnd = true, bool fAutoLinkNurbs = false, const mcsTol& tol = gDefPolTol);
	bool addGeometryAt(unsigned int index, const McsEntityGeometry &geom, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, bool fKeepTanAtNURBsStart = true, bool fKeepTanAtNURBsEnd = true, bool fAutoLinkNurbs = false, const mcsTol& tol = gDefPolTol);
	bool addCurveAt   (unsigned int index, const mcsCurve &curve, double startWidth = MC_DEF_PL_WIDTH, double endWidth = MC_DEF_PL_WIDTH, bool fKeepTanAtNURBsStart = true, bool fKeepTanAtNURBsEnd = true, bool fAutoLinkNurbs = false, const mcsTol& tol = gDefPolTol);
	bool addPolylineAt(unsigned int index, const mcsPline3d& polyline, const mcsTol& tol = mcsGeContext::gTol);

	bool setPointAt (unsigned int index, const mcsPoint2d& pt);
	bool getPointAt (unsigned int index, mcsPoint2d& pt) const;

	bool setPointAt (unsigned int index, const mcsPoint3d& pt);
	bool getPointAt (unsigned int index, mcsPoint3d& pt) const;

	bool setBulgeAt (unsigned int index, double bulge );

		// 15.02.2015, vContextNormal решает ту же проблему, но для любой плоскости,
		// bool убран, т.к. значение false нигде не использовалось;
		// Если вектор нормали дугового сегмента точно ориентирован в обратную сторону относительно vContextNormal,
		// возвращаеммая кривизна будет инвертирована
		//
		// учитывайте нормаль, знак bulge зависит от нормали дуги
		// bStoreIfZAxis - введен неккоректный по сути, смысл в том, что если дуга лежит в плоскости ОХУ,
		// то знак bulge будет выдаваться по отношению к нормали ZAXIS, а не текущей нормали дуги
	//bool getBulgeAt (unsigned int index, double& bulge, bool bStoreIfZAxis = true ) const;
	bool getBulgeAt (unsigned int index, double& bulge, const mcsVector& vContextNormal = mcsVector::kZAxis ) const;

	bool setNormalAt (unsigned int index, const mcsVector3d& nrm);
	bool getNormalAt (unsigned int index, mcsVector3d& nrm) const;

	bool setVertexAt (unsigned int index, const mcsPline3dVertex &vrt); // даёт возможность изменить тип сегмента с началом в этой вершине
	bool getVertexAt (unsigned int index, mcsPline3dVertex &vrt) const;

	bool getVertexAt (unsigned int index, mcsPoint3d& pt, double &bulge, double& startWidth, double& endWidth, mcsVector3d &nrm) const;
	bool getVertices (OUT mcsPline3dVertices& vrt) const;

	mcsPoint3d getPointAt(unsigned int index) const;
	mcsPoint3d getLastPoint() const;
	mcsPoint3d getFirstPoint() const;

	bool removeVertexAt (unsigned int index);
	bool removeLastSegment();
	void reset (bool reuse = false, unsigned int numVerts = 0);

		// если полилиния была не закрыта и вызов выполняется как setClosed(true, true), тогда
		// полииния будет закрыта сплайном касательные которого на концах будут созвпадать с 
		// касательными на концах незакрытой полилинии
	void setClosed( bool fClosed, bool fCloseByNURB = false );

	bool setConstantWidth( double width );
	void setThickness( double thickness );
	bool setWidthsAt(unsigned int index, double startWidth, double endWidth);

	bool getLineSegAt(unsigned int index, mcsLineSeg& line, const mcsTol& tol = gDefPolTol) const;
	bool getArcSegAt( unsigned int index, mcsCircArc& arc, const mcsTol& tol = gDefPolTol) const;
	bool getEllipsSegAt( unsigned int index, mcsEllipArc& arc, const mcsTol& tol = gDefPolTol) const;
	bool getNurbSegAt( unsigned int index, mcsNurbCurve& nurb, bool fAcceptAutoTangents = true, const mcsTol& tol = gDefPolTol) const;
	const mcsCurve* getSegAt(unsigned int index, bool fAcceptNURBAutoTangents = true) const; // указатель на внутреннюю кривую, НЕ копия, удалять НЕ надо

		// getArea - attention: negative value according to pline direct!
	bool getArea( double& area, const mcsTol& tol = gDefPolTol) const;
	bool getWidthsAt( unsigned int index,double& startWidth, double& endWidth ) const;
	bool getConstantWidth(double& constWidth) const;

	bool hasWidth() const; // = AcDbPolyline::hasWidth
	McPolylineWidthTypeEnum widthType() const; // тип ширины на полилинии

	// получить толщину полилинии в указанной параметрической точке
	// eWidthType - используется для оптимизации проверки наличия данных ширины на вершинах
	double widthAtParam(double param, McPolylineWidthTypeEnum eWidthType = kMcPolyWidthData_unk) const;
	double widthAtSegParam(int iSeg, double paramOnSeg) const;

		// simple user Run-Time data (not saved to stream)
	void      setUserData( DWORD_PTR userData ) {setObjectData(userData);}
	DWORD_PTR getUserData() const {return getObjectData();}
	void      setObjectData( DWORD_PTR userData );
	DWORD_PTR getObjectData() const;

		// run-time data per vertex (not saved to stream)
	bool      setVertexData(unsigned int index, DWORD_PTR dwpData, DWORD_PTR dwMask = -1);
	DWORD_PTR getVertexData(unsigned int index) const;
	void      resetVertexData(DWORD_PTR dwMask = 0);

		// run-time data per vertex (not saved to stream)
	bool      setRVertexData(unsigned int index, double rData);
	double    getRVertexData(unsigned int index) const;

		// 13.01.12, persistent data for vertices (savable to stream)
		// saveble data for vertices
	bool    setVertexPersistentData(unsigned int idxVert, __int64 i64data);
		// return -1, if invalid vertex specified
	__int64 getVertexPersistentData(unsigned int idxVert) const;

	bool makeFilletAtVertex(int idxVert, double r);

	// создать фаску в указанной вершине
	// dist1 - для сегмента до вершины, dist2 (если > 0) - для сегмента после вершины
	bool makeChamferAtVertex(int idxVert, double dist1, double dist2 = -1);

		// оптимизация, уменьшает кол-во сегментов, с сохр. формы в пределах данной точности.
		// pIdx2SrcIdx: maps the index of the result polyline to the index of
		// the segment on the polyline before the call;
		// the map will be empty it nothing is done during the optimization
	bool optimize(bool fLinkSequentialNURBs = true, const mcsTol& tol = gDefPolTol, IN OPTIONAL mcsMapInt2IntEx* pIdx2SrcIdx = NULL);
	bool isOk(const mcsTol& tol = gDefPolTol) const;

	bool save(IMcsStream*) const;
	bool load(IMcsStream*);

	//............................................................................
	// Rx methods

		// Если bTwoEndingGripsForOpenCase == true, 
		// для незамкнутой логически полилинии вернёт грип точку в начале полилинии и в грип-точку в конце.
		// Даже если они совпадают физически. Это позволит растаскивать совпадающие концы полилинии.
	bool getGripPoints(
		OUT mcsPoint3dArray& gripPoints,
		IN OPTIONAL bool     bTwoEndingGripsForOpenCase = false) const;

		// При перемещении грип-точек параметр bTwoEndingGripsForOpenCase должен быть таким же, какой был передан
		// в вызове getGripPoints
	bool moveGripPointsAt(
		const mcsIntArray& gripIndices,
		const mcsVector&   offset,
		IN OPTIONAL bool   fStretchMode = false,
		IN OPTIONAL bool   bTwoEndingGripsForOpenCase = false);

	bool hasBulges() const;
	bool hasEllipses() const;
	bool hasSplines() const;
	bool isOnlyLines () const;

	int  numVerts () const;
	int  numSegs() const;

	bool onSegAt (unsigned int index, const mcsPoint2d& pt2d, double& param, const mcsTol& tol = gDefPolTol) const;
	bool onSegAt (unsigned int index, const mcsPoint3d& pt3d, double& param, const mcsTol& tol = gDefPolTol) const;
	double thickness () const;
	SegType segType (unsigned int index, const mcsTol& tol = gDefPolTol) const;
	bool isValid(unsigned int idx) const;

	bool getFirstDeriv(const mcsPoint3d& pt3d, mcsVector3d& firstDeriv, const mcsTol& tol = gDefPolTol) const;
	bool getFirstDeriv(double param, mcsVector3d& firstDeriv, const mcsTol& tol = gDefPolTol) const;

		// dist - длина от точки, которая задаётся параметром param, "+" по направлению, "-" в обратном направлении
	bool getParamAtDist(double dist, double& param, const mcsTol& tol = gDefPolTol) const;
		// param = paramOf(pt3d)
	bool getParamAtPoint(const mcsPoint3d& pt3d, double& param, const mcsTol& tol = gDefPolTol) const;
		// pt3d = evalPoint(param)
	bool getPointAtDist(double param, mcsPoint3d& pt3d, const mcsTol& tol = gDefPolTol) const;
		// pt3d = evalPoint(param)
	bool getPointAtParam(double param, mcsPoint3d& pt3d, const mcsTol& tol = gDefPolTol) const;
		// dist = param
	bool getDistAtParam(double param, double& dist, const mcsTol& tol = gDefPolTol) const;
		// param = paramOf(pt3d)
	bool getDistAtPoint(const mcsPoint3d& pt3d, double& param, const mcsTol& tol = gDefPolTol) const;

#ifndef NOACGE
	bool intersectWith( const mcsCurve& curve, mcsGePoints3dArr &intArr, const mcsTol& tol = gDefPolTol) const;
#endif
	bool intersectWith( const mcsCurve& curve, mcsGePoints3dArr &intArr, const mcsTol& tol = gDefPolTol) const;

#ifdef MCGEL
	virtual bool mcs_intersectWithPlanarEnt (const McGePlanarEnt& plane, OUT McGePoint3dArray& points, const McGeTol& tol = McGeContext::gTol) const;
#endif

		// Definition of curve
		// Note: some methods derived from AcGeCompositeCurve3d are DISABLED for you!

		// Methods from mcsCurve

		// Parametrization.
	virtual void      getInterval(mcsInterval& intrvl) const PLINE_OVERRIDE;
	virtual void      getInterval(mcsInterval& intrvl, mcsPoint3d& start, mcsPoint3d& end) const PLINE_OVERRIDE;
	virtual mcsCurve& reverseParam() PLINE_OVERRIDE;
	virtual mcsCurve& setInterval() PLINE_OVERRIDE;
	virtual bool      setInterval(const mcsInterval& intrvl) PLINE_OVERRIDE;

		// Distance to other geometric objects.
	virtual double distanceTo( const mcsPoint3d& pnt, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;
	virtual double distanceTo( const mcsCurve& curve, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

		// Return the point on this object that is closest to the other object.
		// These methods return point on this curve as a simple 3d point.
	virtual mcsPoint3d closestPointTo(const mcsPoint3d& pnt, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

	virtual mcsPoint3d closestPointTo(
		const mcsCurve& curve3d, mcsPoint3d& pntOnOtherCrv,
		const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

		// Return the index of segment that is closest to the point.
	int getNearestSegment(OUT McsEntityGeometry& nearestSegGeom, const mcsPoint& pickPoint, const mcsTol& tol = gDefPolTol) const;
	int getNearestSegment(const mcsPoint& pickPoint, const mcsTol& tol = gDefPolTol) const;
	int getNearestSegment(const mcsPoint& pickPoint, IN OPTIONAL const mcsMatrix* pXyProjTfm, IN OPTIONAL const mcsTol& tol = gDefPolTol) const;

		// Alternate signatures for above functions.  These methods return point
		// on this curve as an mcsPointOnCurve3d.
	virtual void getClosestPointTo(const mcsPoint3d& pnt, mcsPointOnCurve3d& pntOnCrv, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

	virtual void getClosestPointTo(
		const mcsCurve& curve3d,
		mcsPointOnCurve3d& pntOnThisCrv,
		mcsPointOnCurve3d& pntOnOtherCrv,
		const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

		// Return closest points when projected in a given direction.
		// These methods return point on this curve as a simple 3d point.
	virtual mcsPoint3d projClosestPointTo(
		const mcsPoint3d& pnt,
		const mcsVector3d& projectDirection,
		const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

	virtual mcsPoint3d projClosestPointTo(
		const mcsCurve& curve3d,
		const mcsVector3d& projectDirection,
		mcsPoint3d& pntOnOtherCrv,
		const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

		// Alternate signatures for above functions.  These methods return point
		// on this curve as an mcsPointOnCurve3d.
	virtual void getProjClosestPointTo(
		const mcsPoint3d& pnt,
		const mcsVector3d& projectDirection,
		mcsPointOnCurve3d& pntOnCrv,
		const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

	virtual void getProjClosestPointTo(const mcsCurve& curve3d,
		const mcsVector3d& projectDirection,
		mcsPointOnCurve3d& pntOnThisCrv,
		mcsPointOnCurve3d& pntOnOtherCrv,
		const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

		// Return point on curve whose normal vector passes thru input point.
		// Second parameter contains initial guess value and also
		// contains output point.

		// Returns true or false depending on whether a normal point was found.
	virtual bool getNormalPoint(const mcsPoint3d& pnt, mcsPointOnCurve3d& pntOnCrv, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

		// 22.05.2006, AGL: "mcs_" prefix added because usage of these methods under
		// OdGe library is ambiguous. In OdGe version there are "virtual"
		// keywords before these methods.

		// Returns oriented bounding box of curve.
	virtual mcsBounds  boundBlock() const PLINE_OVERRIDE;
	virtual mcsBounds  boundBlock( const mcsInterval& range ) const PLINE_OVERRIDE;
	virtual mcsBounds  orthoBoundBlock() const PLINE_OVERRIDE;
	virtual mcsBounds  orthoBoundBlock( const mcsInterval& range ) const PLINE_OVERRIDE;

	mcsBoundBlock  mcs_boundBlock() const;
	mcsBoundBlock  mcs_boundBlock( const mcsInterval& range ) const;
	mcsBoundBlock  mcs_boundBlock( const mcsInterval& range, bool bOrtho ) const;

		// Return bounding box whose sides are parallel to coordinate axes.
	mcsBoundBlock  mcs_orthoBoundBlock() const;
	mcsBoundBlock  mcs_orthoBoundBlock( const mcsInterval& range ) const;

		// Project methods.
	virtual mcsEntity3d*  project(
		const mcsPlane& projectionPlane,
		const mcsVector3d& projectDirection,
		const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

	virtual mcsEntity3d*  orthoProject(const mcsPlane& projectionPlane, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

		// Tests if point is on curve.
	virtual bool isOn(const mcsPoint3d& pnt,const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;
	virtual bool isOn(const mcsPoint3d& pnt, double& param, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;
	virtual bool isOn(double param, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;
	bool isOn(const mcsPoint3d& pnt, int& idx, const mcsTol& tol = gDefPolTol) const;

		// Tests if point is inside curve.
	bool isIn(const mcsPoint3d& pnt, const mcsTol& tol = gDefPolTol) const;

		// Parameter of the point on curve.  Contract: point IS on curve
	virtual double paramOf(const mcsPoint3d& pnt, const mcsTol& tol = gDefPolTol)const PLINE_OVERRIDE;

		// Return the offset of the curve.
		// distance may be positive and negative value
	virtual void getTrimmedOffset(
		double distance,
		const mcsVector3d& planeNormal,
		mcsPVoidArray& offsetCurveList,
		mcsOffsetCrvExtType extensionType = mcsGe::kFillet,
		const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

	mcsBoolean getTrimmedOffset(
		double distance,
		mcsPolylineArray& offsetPlines,
		mcsOffsetCrvExtType extensionType = mcsGe::kExtend,
		const mcsVector3d& planeNormal = mcsVector3d::kZAxis, // most cases for 2D
		const mcsTol& tol = gDefPolTol) const;

#ifdef MCGEL
	mcsBoolean mcs_getTrimmedOffsetEx(mcsPline3dOffsetData& offd) const;
#endif

	// RMCS 14594
	// The call to mcsPline3d::getOffsetCurve by default optimizes input curves by joining segments
	// in case when one of them lays on a continuation of the neighboring segment;
	// This call switches this logic off, but only for the next call only;
	// Returning value is the reference to the static variable of the 'bool ' type which
	// holds the current state of the switch
	static bool& disableOffsetInputOptimizationOnNextCall();

		// Geometric inquiry methods.

		// этот метод тупо возвращает внутренний флажок замкнутости,
		// т.е. фактически от геометрии он не зависит.
	bool isClosedLogically() const;

		// а этот метод взовращает сводный статус замкнутости.
		// Т.е. если замкнута логически, то вернет, что замкнута, а если не замкнута
		// логически, то проверит концевые точки на совпадение с заданной точностью
	virtual bool isClosed      (const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

	virtual bool isPlanar      (mcsPlane& plane, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;
	bool isPlanar      (const mcsTol& tol = gDefPolTol) const;
	virtual bool isLinear      (mcsLine& line, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;
	virtual bool isCoplanarWith(const mcsCurve& curve3d, mcsPlane& plane, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;
	virtual bool isPeriodic    (double& period) const PLINE_OVERRIDE;
	bool isClockWise   (OUT mcsVector3d &nrm, const mcsTol& tol = gDefPolTol) const;

		// Length based methods.
	virtual double  length(double fromParam, double toParam, double tol = gDefPolTol.equalPoint()) const PLINE_OVERRIDE;
	double  length() const; // просто вся длина от начала и до конца
	virtual double  paramAtLength(double datumParam, double length, mcsBoolean posParamDir = true, double tol = gDefPolTol.equalPoint()) const PLINE_OVERRIDE;

		// getArea - attention: negative value according to pline direct!
	virtual bool area (double startParam, double endParam, double& value, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

		// Degeneracy.
	virtual bool isDegenerate(mcsGe::EntityId& degenerateType, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;
	virtual bool isDegenerate(mcsEntity3d*& pConvertedEntity, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

	virtual double  globalToLocalParam( double param, int& idxSeg) const PLINE_OVERRIDE;
	void    globalToLocalParam( double* params, int* idxSeg, int num) const;
	virtual double  localToGlobalParam ( double param, int idxSeg ) const PLINE_OVERRIDE;

		// curveList = mcsCurve* array
	virtual void getCurveList(mcsGeVoidPtrArr& curveList) const PLINE_OVERRIDE;

		// curveList = mcsCurve* array
		// вызов эквивалентен setCurveList(curveList, isOwnerOfCurves), 
		// где второй аргумент - массив нулей той же размерности, что и у массива curveList
	virtual mcsCompositeCurve3d& setCurveList(const mcsGeVoidPtrArr& curveList) PLINE_OVERRIDE;

		// curveList = mcsCurve* array
	virtual mcsCompositeCurve3d& setCurveList(const mcsGeVoidPtrArr& curveList, const mcsGeIntArr& isOwnerOfCurves) PLINE_OVERRIDE;

		// Modify methods.
	virtual void getSplitCurves(double param, mcsCurve*& piece1, mcsCurve*& piece2) const PLINE_OVERRIDE;

		// Explode curve into its component sub-curves.
	virtual mcsBoolean explode (
		OUT mcsPVoidArray& explodedCurves, // mcsCurve* array
		OUT mcsIntArray& newExplodedCurves,
		IN OPTIONAL const mcsInterval* intrvl = NULL ) const PLINE_OVERRIDE;

	mcsBoolean explode(mcsGeomEntArray &arr) const;

	virtual void getLocalClosestPoints(
		const mcsPoint3d& point,
		mcsPointOnCurve3d& approxPnt,
		const mcsInterval* nbhd = 0,
		const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

	virtual void getLocalClosestPoints(
		const mcsCurve& otherCurve,
		mcsPointOnCurve3d& approxPntOnThisCrv,
		mcsPointOnCurve3d& approxPntOnOtherCrv,
		const mcsInterval* nbhd1 = 0,
		const mcsInterval* nbhd2 = 0,
		const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;

		// Return start and end points.
	virtual bool hasStartPoint(mcsPoint3d& startPnt) const PLINE_OVERRIDE;
	virtual bool hasEndPoint  (mcsPoint3d& endPnt) const PLINE_OVERRIDE;

		// Evaluate methods.
	virtual mcsPoint3d    evalPoint(double param) const PLINE_OVERRIDE;
	virtual mcsPoint3d    evalPoint(double param, int numDeriv, mcsVector3dArray& derivArray) const PLINE_OVERRIDE;

#ifndef NOACGE
	mcsPoint3d    evalPoint(double param, int numDeriv, mcsGeVectors3dArr& derivArray) const;
#endif

		// Polygonize curve to within a specified tolerance.
	virtual void getSamplePoints(int numSample, mcsPoint3dArray& pointArray) const PLINE_OVERRIDE;

	virtual void getSamplePoints(
		double fromParam,
		double toParam,
		double approxEps,
		mcsPoint3dArray&  pointArray,
		mcsDoubleArray& paramArray) const PLINE_OVERRIDE;

		// разбивает полилинию на отрезки с заданной точностью
	bool approxByLineSegs(double approxEps, OUT mcsPline3d& approxPolyline);

#ifndef NOACGE
	mcsBoolean explode(
		mcsGeVoidPtrArr& explodedCurves,
		mcsGeIntArr& newExplodedCurves,
		const mcsInterval* intrvl = NULL ) const;

	void getTrimmedOffset(
		double distance,
		const mcsVector3d& planeNormal,
		mcsGeVoidPtrArr& offsetCurveList,
		mcsGe::OffsetCrvExtType extensionType = mcsGe::kFillet,
		const mcsTol& tol = gDefPolTol) const;

	void getSamplePoints(
		double fromParam, double toParam,
		double approxEps, mcsGePoints3dArr& pointArray, mcsGeDoubleArr& paramArray) const;

	void getSamplePoints(int numSample, mcsGePoints3dArr& pointArray) const;
#endif

		// Assignment operator.
	mcsPline3d& operator = (const mcsPline3d& pline);

		// Derived from AcGeEntity3d

		// Make a copy of the entity.
	virtual mcsEntity3d*    copy        () const PLINE_OVERRIDE;
	virtual mcsEntity3d&    operator =  (const mcsEntity3d& entity) PLINE_OVERRIDE;
	virtual mcsCurve&       operator =  (const mcsCurve& curve) PLINE_OVERRIDE;

		// Equivalence
	virtual mcsBoolean   operator == (const mcsEntity3d& entity) const PLINE_OVERRIDE;
	virtual mcsBoolean   operator != (const mcsEntity3d& entity) const PLINE_OVERRIDE;
	virtual mcsBoolean   isEqualTo   (const mcsEntity3d& ent, const mcsTol& tol = gDefPolTol) const PLINE_OVERRIDE;
	bool operator == (const mcsPline3d&) const;
	bool operator != (const mcsPline3d& cw) const {return !(*this==cw);}

		// Matrix multiplication - transformation
		// (!) If scaling present, then stored parametrization will be broken,
		// you must reevaluate all parameters you need, because the parameter of point on polyline is
		// length from start of curve
	virtual mcsEntity3d& transformBy( const mcsMatrix3d& xfm ) PLINE_OVERRIDE;
	virtual mcsEntity3d& translateBy (const mcsVector3d& translateVec) PLINE_OVERRIDE;
	virtual mcsEntity3d& rotateBy    (double angle, const mcsVector3d& vec, const mcsPoint3d& wrtPoint = mcsPoint3d::kOrigin) PLINE_OVERRIDE;
	virtual mcsEntity3d& mirror  (const mcsPlane& plane) PLINE_OVERRIDE;
	virtual mcsEntity3d& scaleBy (double scaleFactor, const mcsPoint3d& wrtPoint = mcsPoint3d::kOrigin) PLINE_OVERRIDE;

		// compatibility for old polyline
	double   getBulgeAt(const int iIndex, const mcsVector& vContextNormal = mcsVector::kZAxis) const
	{
		double r;
		getBulgeAt(iIndex, r, vContextNormal);
		return r;
	}

	mcsPoint fitPointAt(int idx) const {mcsPoint V; getPointAt(idx,V); return V;}
	void     setFitPointAt(int idx,const mcsPoint& V) {setPointAt(idx,V);}
	int      numFitPoints() const {return numVerts();};

	bool mcsPolyline::intersectBy(const McsEntityGeometry& otherEnt,OUT mcsPoint3dArray& crossPoints, const mcsTol& tol = gDefPolTol) const;

	bool saveToXML(IUnknown* pxuPolylineNode) const;
	bool loadFromXML(IUnknown* pxuPolylineNode);

		// запись в бинарный файл, можно использовать для отладочного просмотра графики полилинии,
		// нпаример через диалог Router!VisPolylineTest
	bool saveToFile(LPCTSTR lpszPath) const;
	bool loadFromFile(LPCTSTR lpszPath);

	// Хэлпер, создаёт полилинию-прямоугольник в XY, ориентированную против часовой стрелки относительно oZ.
	// Стороны прямоугольника выравниваются параллельно осям oX, oY.
	// L->R направление сонаправлено с осью oX.
	// B->T направление сонаправлено с осью oY.
	// Z-координаты точек игнорируются
	void createRect(const mcsPoint& bottomLeft_2d, const mcsPoint& topRighit_2d);

	// метод проверяет, является ли полилиния полной окружностью в пределах данной точности,
	// и отдаёт эту самую окружность
	bool isFullCA(OUT mcsCircArc& circArc, const mcsTol& tol = gDefPolTol) const;

	// метод проверяет, является ли полилиния полным эллипсом в пределах данной точности,
	// и отдаёт этот самый эллипс
	bool isFullEA(OUT mcsEllipArc& ellipArc, const mcsTol& tol = gDefPolTol) const;

protected:
#ifdef _MCEYE
public:
#endif
	friend class mcsImpPline3d;
	mcsImpPline3d  *m_pImpPline;
};
//==============================================================================
// Метод используется в командах построения протяженных объектов а-ля платформенная полилиния AcDbPolyline
// для включения опции "Замкнуть" в список доступных в команде опций.
// И вызывается при формировании списка опций команды перед запросом очередной точки полилинии.
// ---
// Такой способ построения предусматривает создание линейных и дуговых участков.	
// ---
// Метод возвращает true, если в результате закрытия получится замкнутый контур.
// При этом на момент вызова полилиния должна содержать как минимум два линейных участков или один дуговой,
// а также собственно сам последний сегмент, который может быть любым.
__inline bool IsEnabledCommandOption_ClosePolyline(const mcsPolyline& poly)
{
	int nSegCount = poly.numSegs();
	if (nSegCount < 2)
		return false;
	mcsPolyline::SegType st1 = poly.segType(0);
	int nUnEmptySegCount = 0;
	for (int i = 0; i < nSegCount; i++)
	{
		mcsPolyline::SegType st = (0 == i) ? st1 : poly.segType(i);
		if (mcsPolyline::kLine == st || mcsPolyline::kArc == st)
		{
			nUnEmptySegCount++;
			if (nUnEmptySegCount > 2)
				return true;
		}
	}
	if (mcsPolyline::kArc == st1 || (2 == nUnEmptySegCount && nSegCount > 2))
		return true;
	return false;
}
//==============================================================================
#ifndef mcsPolyline
	#define mcsPolyline mcsPline3d
#endif
//==============================================================================
class mcsPolylineArray :public McsArray <mcsPolyline, const mcsPolyline&>
{
public:
	void transformBy(const mcsMatrix& tfm);
	mcsBoundBlock mcs_orthoBoundBlock() const;
	mcsBoundBlock mcs_boundBlock() const;
	double distanceTo(const mcsPoint& pnt, int* piIndex = NULL, const mcsTol& tol = gDefPolTol) const;
};
//==============================================================================
#ifdef MCGEL
struct mcsPline3dOffsetData : McGeCurve3dOffsetData
{
	enum Flags
	{
		fFillAssocMap = 0x01, // enabled by default
	};
	IN DWORD dwFlags;

	// out members
	OUT mcsPolylineArray offsetPlines; // is used instead of McGeCurve3dOffsetData::offsetCurves

	MCTYP_API void Clear();
	MCTYP_API void ClearOut();

	MCTYP_API mcsPline3dOffsetData(
		double distance = 0,
		mcsOffsetCrvExtType extensionType = mcsGe::kExtend,
		const mcsVector3d& planeNormal = mcsVector3d::kZAxis,
		const mcsTol& tolerance = gDefPolTol);

	MCTYP_API mcsPline3dOffsetData(const McGeCurve3dOffsetData& baseOffd);

	MCTYP_API mcsPline3dOffsetData(const mcsPline3dOffsetData& offd);
	MCTYP_API mcsPline3dOffsetData& operator=(const mcsPline3dOffsetData& offd);

protected:
	void _ClearBaseResContour();
};
#endif
//==============================================================================
__inline void mcsPolylineArray::transformBy(const mcsMatrix& tfm){
	for(int i=m_nSize-1; i>=0; i--) {
		m_pData[i].transformBy(tfm);
	}
};
//==============================================================================
__inline mcsBoundBlock mcsPolylineArray::mcs_orthoBoundBlock() const
{
	mcsBoundBlock bound(true);
	for(int i = m_nSize - 1; i >= 0; i--)
		bound.mergeWith(m_pData[i].mcs_orthoBoundBlock());
	return bound;
}
//==============================================================================
__inline mcsBoundBlock mcsPolylineArray::mcs_boundBlock() const
{
	mcsBoundBlock bound;
	for(int i = m_nSize - 1; i >= 0; i--)
		bound.mergeWith(m_pData[i].mcs_boundBlock());
	return bound;
}
//==============================================================================
__inline double mcsPolylineArray::distanceTo(const mcsPoint& pnt, int* piIndex, const mcsTol& tol) const
{
	if(piIndex)
		*piIndex = -1;
	double rMin = MAX_REAL, r;
	for(int i = m_nSize - 1; i >= 0; i--)
	{
		r = m_pData[i].distanceTo(pnt, tol);
		if(r < rMin)
		{
			rMin = r;
			if(piIndex)
				*piIndex = i;
		}
	}
	return rMin;
}
//==============================================================================

#endif // MCGELDLL

struct mcsSphereImpl;
struct mcsCylImpl;
struct mcsConeImpl;
struct mcsTorusImpl;

class McGeCone;
class McGeCylinder;
class McGeTorus;
class McGeSphere;

struct mcsSphere
{
private:
#ifdef _MCEYE
public:
#endif
	mcsSphereImpl* m_pImpl;

public:
	MCGEL_API mcsSphere();
	MCGEL_API mcsSphere(const mcsSphere& t);
	MCGEL_API mcsSphere(const mcsGeSphere& sphere);

	MCGEL_API ~mcsSphere();

	MCGEL_API const McGeSphere& asMcsGeSphere() const;

	DECLARE_OBJ_NEWDEL;

	MCGEL_API mcsPoint      center() const;
	MCGEL_API double        radius() const;

	MCGEL_API bool getData(OUT OPTIONAL mcsPoint* pCenter, OUT OPTIONAL double* pRadius) const;
	MCGEL_API bool setData(IN const mcsPoint& center, IN double radius);
	MCGEL_API mcsSphere& set(const mcsGeSphere& sphere);

	MCGEL_API bool isInner() const;
	MCGEL_API void setInner(bool bInnerSurf);

	MCGEL_API void          transformBy(const mcsMatrix& tfm);
	MCGEL_API bool          isEqualTo(const mcsSphere& t, const mcsTol& tol = mcsGeContext::gTol) const;
	MCGEL_API mcsSphere&    operator = (const mcsSphere&);
	MCGEL_API mcsSphere&    operator = (const mcsGeSphere& sphere);
	MCGEL_API double        distanceTo(const mcsPoint& pt) const; // negative, if inside
	MCGEL_API double        distanceTo(const mcsPlane& plane) const; // negative, if plane crosses sphere

	MCGEL_API bool isArgInside(const mcsSphere& s) const;
	MCGEL_API bool isArgOutside(const mcsSphere& s) const;

	MCGEL_API bool intersectBy(IN const mcsLinearEntity& axis, OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;

	MCGEL_API bool intersectBy(
		const mcsLinearEntity&         axis,
		OUT mcsPoint3dArray&           crossPoints,
		OUT OPTIONAL mcsVector3dArray* pNormals, // = NULL,
		IN OPTIONAL const mcsTol&      tol = mcsGeContext::gTol) const;

	MCGEL_API mcsBoundBlock getBoundBlock() const;

	MCTYP_API bool          save(IMcsStream*) const;
	MCTYP_API bool          load(IMcsStream*);
};
typedef McsArray<mcsSphere, const mcsSphere&> mcsSpheresArray;

//==============================================================================
struct mcsCylinder
{
private:
#ifdef _MCEYE
public:
#endif
	mcsCylImpl* m_pImpl;

public:
	MCGEL_API mcsCylinder();
	MCGEL_API mcsCylinder(const mcsCylinder& t);
	MCGEL_API mcsCylinder(const mcsGeCylinder& cylinder);

	MCGEL_API ~mcsCylinder();

	MCGEL_API const McGeCylinder& asMcsGeCylinder() const;

	DECLARE_OBJ_NEWDEL;

	MCGEL_API mcsPoint      basept() const;
	MCGEL_API mcsVector     axis() const;
	MCGEL_API double        radius() const;
	MCGEL_API double        length() const;

	MCGEL_API bool getData(
		OUT OPTIONAL mcsPoint*  pBasePt,
		OUT OPTIONAL mcsVector* pDirAxis,
		OUT OPTIONAL double*    pRadius,
		OUT OPTIONAL double*    pLength) const;

	MCGEL_API bool setData(
		IN const mcsPoint&  BasePt,
		IN const mcsVector& DirAxis,
		IN double           Radius,
		IN double           Length);

	MCGEL_API mcsCylinder& set(const mcsGeCylinder& cylinder);

	MCGEL_API bool isInner() const;
	MCGEL_API void setInner(bool bInnerSurf);

	MCGEL_API mcsCylinder&  transformBy(const mcsMatrix& tfm);
	MCGEL_API void          reverseAxis();
	MCGEL_API bool          isEqualTo(const mcsCylinder& t, const mcsTol& tol = mcsGeContext::gTol) const;
	MCGEL_API mcsCylinder&  operator = (const mcsCylinder&);
	MCGEL_API mcsCylinder&  operator = (const mcsGeCylinder&);

	MCGEL_API bool intersectBy(const mcsLinearEntity& axis,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;

	MCGEL_API bool intersectBy(
		const mcsLinearEntity&         axis,
		OUT mcsPoint3dArray&           crossPoints,
		OUT OPTIONAL mcsVector3dArray* pNormals, // = NULL,
		IN OPTIONAL const mcsTol&      tol = mcsGeContext::gTol) const;

	MCGEL_API mcsBoundBlock getBoundBlock() const;

	MCTYP_API bool          save(IMcsStream*) const;
	MCTYP_API bool          load(IMcsStream*);
};
typedef McsArray<mcsCylinder, const mcsCylinder&> mcsCylindersArray;
//==============================================================================
struct mcsCone
{
private:
#ifdef _MCEYE
public:
#endif
	mcsConeImpl* m_pImpl;

public:
	MCGEL_API mcsCone();
	MCGEL_API mcsCone(const mcsCone& t);
	MCGEL_API mcsCone(const mcsGeCone& cone);

	MCGEL_API ~mcsCone();

	MCGEL_API const McGeCone& asMcsGeCone() const;

	DECLARE_OBJ_NEWDEL;

	MCGEL_API mcsPoint      basept() const;
	MCGEL_API mcsVector     axis() const;
	MCGEL_API double        startR() const;
	MCGEL_API double        endR() const;
	MCGEL_API double        height() const;
	MCGEL_API double        halfAng() const;

	MCGEL_API bool getData(
		OUT OPTIONAL mcsPoint*  pBasePt,
		OUT OPTIONAL mcsVector* pDirAxis,
		OUT OPTIONAL double*    pRStart,
		OUT OPTIONAL double*    pREnd,
		OUT OPTIONAL double*    pH) const;

	MCGEL_API mcsPoint apex() const;

	MCGEL_API bool setData(
		IN const mcsPoint&  BasePt,
		IN const mcsVector& DirAxis,
		IN double           RStart,
		IN double           REnd,
		IN double           H);

	MCGEL_API mcsCone& set(const mcsGeCone& cone);

	MCGEL_API bool setData(
		IN const mcsPoint&  BasePt,
		IN const mcsVector& DirAxis,
		IN double           RStart,
		IN double           halfAng);

	MCGEL_API bool isInner() const;
	MCGEL_API void setInner(bool bInnerSurf);

	MCGEL_API void          transformBy(const mcsMatrix& tfm);
	MCGEL_API void          reverseAxis();
	MCGEL_API bool          isEqualTo(const mcsCone& t, const mcsTol& tol = mcsGeContext::gTol) const;
	MCGEL_API mcsCone&      operator = (const mcsCone&);
	MCGEL_API mcsCone&      operator = (const mcsGeCone&);

	MCGEL_API bool          intersectBy(const mcsLinearEntity& axis,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;

	MCGEL_API bool intersectBy(
		const mcsLinearEntity&         axis,
		OUT mcsPoint3dArray&           crossPoints,
		OUT OPTIONAL mcsVector3dArray* pNormals, // = NULL,
		IN OPTIONAL const mcsTol&      tol = mcsGeContext::gTol) const;

	MCGEL_API mcsBoundBlock getBoundBlock() const;

	MCTYP_API bool          save(IMcsStream*) const;
	MCTYP_API bool          load(IMcsStream*);
};
typedef McsArray<mcsCone, const mcsCone&> mcsConesArray;

//==============================================================================
struct mcsTorus
{
private:
#ifdef _MCEYE
public:
#endif
	mcsTorusImpl* m_pImpl;

public:
	MCGEL_API mcsTorus();
	MCGEL_API mcsTorus(const mcsTorus& t);
	MCGEL_API mcsTorus(const mcsGeTorus& torus);

	MCGEL_API ~mcsTorus();

	MCGEL_API const McGeTorus& asMcsGeTorus() const;

	DECLARE_OBJ_NEWDEL;

	MCGEL_API const  mcsCircArc& path() const;
	MCGEL_API double        minR() const;
	MCGEL_API double        maxR() const;
	MCGEL_API mcsPoint      center() const;
	MCGEL_API mcsVector     axis() const;

	MCGEL_API bool getData(
		OUT OPTIONAL mcsCircArc* pPathAxis,
		OUT OPTIONAL double*     pPathRadius) const;

	MCGEL_API bool setData(
		IN const mcsCircArc& PathAxis,
		IN double            PathRadius);

	MCGEL_API mcsTorus& set(const mcsGeTorus& torus);

	MCGEL_API bool isInner() const;
	MCGEL_API void setInner(bool bInnerSurf);

	MCGEL_API void          transformBy(const mcsMatrix& tfm);
	MCGEL_API void          reverseAxis();
	MCGEL_API bool          isEqualTo(const mcsTorus& t, const mcsTol& tol = mcsGeContext::gTol) const;
	MCGEL_API mcsTorus&     operator = (const mcsTorus&);
	MCGEL_API mcsTorus&     operator = (const mcsGeTorus& torus);

	MCGEL_API bool intersectBy(const mcsLinearEntity& axis,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;

	MCGEL_API bool intersectBy(
		const mcsLinearEntity&         axis,
		OUT mcsPoint3dArray&           crossPoints,
		OUT OPTIONAL mcsVector3dArray* pNormals, // = NULL,
		IN OPTIONAL const mcsTol&      tol = mcsGeContext::gTol) const;

	MCGEL_API mcsBoundBlock getBoundBlock() const;

	MCTYP_API bool          save(IMcsStream*) const;
	MCTYP_API bool          load(IMcsStream*);
};
typedef McsArray<mcsTorus, const mcsTorus&> mcsTorusesArray;

//==============================================================================
struct mcsTriangle
{
	mcsPoint pt[3];

	mcsTriangle(const mcsPoint& p1, const mcsPoint& p2, const mcsPoint& p3) {
		set(p1, p2, p3);
	}

	mcsTriangle() {
	}

	~mcsTriangle(){
	}

	void set(const mcsPoint& p1, const mcsPoint& p2, const mcsPoint& p3) {
		pt[0] = p1;
		pt[1] = p2;
		pt[2] = p3;
	}

	mcsTriangle(const mcsTriangle& cf) {
		*this = cf;
	}

	mcsTriangle& operator=(const mcsTriangle& cf)
	{
		if(this == &cf)
			return *this;

		pt[0] = cf.pt[0];
		pt[1] = cf.pt[1];
		pt[2] = cf.pt[2];
		return *this;
	}

	DECLARE_OBJ_NEWDEL;

	void transformBy(const mcsMatrix& tfm)
	{
		pt[0].transformBy(tfm);
		pt[1].transformBy(tfm);
		pt[2].transformBy(tfm);
	}

	MCGEL_API bool isEqualTo(const mcsTriangle& t, const mcsTol& tol = mcsGeContext::gTol) const;

	// ((pt[1] - pt[0]).crossProduct(pt[2] - pt[1])).normal()
	MCGEL_API mcsVector normal() const;

	// проверяет, лежит ли проекция точки на плоскость треугольника в пределах его границ
	MCGEL_API bool isProjInBounds(const mcsPoint& pt, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;

	MCGEL_API bool intersectBy(const mcsLinearEntity& axis,OUT mcsPoint& crossPoint, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCGEL_API mcsBoundBlock getBoundBlock() const;

	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);
};
typedef McsArray<mcsTriangle, const mcsTriangle&> mcsTrianglesArray;
//==================================================================================================

#ifndef MCGELDLL

enum McsHorizTextAlignEnum
{
  kTextHorizAlign_Left   = 0,
  kTextHorizAlign_Center = 1,
  kTextHorizAlign_Right  = 2
};
//==================================================================================================

enum McsVertTextAlignEnum
{
  kTextVertAlign_Top    = 0,
  kTextVertAlign_Center = 1,
  kTextVertAlign_Bottom = 2
};
//==================================================================================================

// В размерных стилях используется следующий порядок, нежели McsVertTextAlignEnum.
// Однако в старые форматы стрима писалось McsVertTextAlignEnum.
enum McsDimTolVertJustifyEnum
{
	kMcsDimTolVertJustify_Bottom = 0,
	kMcsDimTolVertJustify_Middle = 1,
	kMcsDimTolVertJustify_Top    = 2,
};
//==================================================================================================

inline McsDimTolVertJustifyEnum cvtVertAlign(IN McsVertTextAlignEnum eVert) { return (McsDimTolVertJustifyEnum) (2-int(eVert)); }
inline McsVertTextAlignEnum cvtVertAlign(IN McsDimTolVertJustifyEnum eVert) { return (McsVertTextAlignEnum) (2-int(eVert)); }

//==============================================================================
struct mcsText
{
	DECL_PROPERTY(McsString,             text);
	DECL_PROPERTY(McsString,             textStyle);    // If empty - default textstyle by context
	DECL_PROPERTY(mcsPoint,              origin);       // Text location
	DECL_PROPERTY(mcsVector,             direction);    // Text direction
	DECL_PROPERTY(McsHorizTextAlignEnum, horizAlign);   // Horizontal alignment
	DECL_PROPERTY(McsVertTextAlignEnum,  vertAlign);    // Vertical alignment
	DECL_PROPERTY(double,                width);        // Used during word wrap. If 0 - no word wrap
	DECL_PROPERTY(double,                height);       // If 0 - by textStyle
	DECL_PROPERTY(double,                oblique);      // Oblique in radians. If MCSTEXT_DEFOBLIQUE - by textStyle. Ignored in MText
	DECL_PROPERTY(double,                xScale);       // If 0 - by textStyle. Ignored in MText
	DECL_PROPERTY(double,                lineSpacing);  // Line spacing
	DECL_PROPERTY(bool,                  isWordWrap);
	DECL_PROPERTY(double,                hostScale);    // Text's host scale

	DWORD                                m_Flags;
	#define    MCSTEXT_DEPRECATED        0x80000000     // Text parameters has changed
	// Более не используется. Теперь работаем через свойство геометрии kMcGeomExPropUseOwnStyle
	//#define    MCSTEXT_STYLE_OVERRIDE    0x40000000     // Use style settings (color, line weight and type) directly from exploded
	#define    MCSTEXT_MASK_BACKGROUND   0x20000000     // Fill text boundaries with background color
	#define    MCSTEXT_ALIGNED_TO_CAMERA 0x10000000     // Draws the text in a plane that's parallel to the camera

	mcsGeomEntArray exploded;
	mcsPoint        boundBase;
	double          boundX;
	double          boundY;

	DECLARE_OBJ_NEWDEL;

	MCTYP_API mcsText();
	MCTYP_API ~mcsText();

	MCTYP_API mcsText(
		LPCTSTR _text,
		const mcsPoint& _origin,
		const mcsVector& _direction,
		const McsHorizTextAlignEnum _horizAlign = kTextHorizAlign_Left,
		const McsVertTextAlignEnum _vertAlign = kTextVertAlign_Bottom,
		LPCTSTR _textStyle = NULL,
		const double _height = 0,
		const double _width = 0);

	MCTYP_API mcsText(
		LPCTSTR _text,
		const mcsPoint& _origin,
		const mcsVector& _direction,
		LPCTSTR _textStyle = NULL,
		const double _height = 0,
		const double _oblique = MCSTEXT_DEFOBLIQUE,
		const double _xScale = 0);

	MCTYP_API bool operator ==(const mcsText& trg) const;
	MCTYP_API bool isEqualTo(const mcsText& cw, const mcsTol& tol = mcsGeContext::gTol) const;

	bool operator != (const mcsText& trg) const
		{ return !operator == (trg); }

	MCTYP_API void transformBy(const mcsMatrix& tfm);
	MCTYP_API mcsBoundBlock getBoundBlock(bool isOrtho = false) const;
	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);
	MCTYP_API McsString textRaw() const;  // текст без rtf-форматирования
	MCTYP_API void Prepare(mcsBoundBlock* pBound); // разбивает текст на примитивы и складывает в exploded
	MCTYP_API bool GetContour(mcsPolyline& contour, double rOffset) const; // контур маскировки\перекрытия
	MCTYP_API bool GetContour(mcsPoint *pRectangle, double rOffset) const;// контур маскировки\перекрытия, pRectangle - указатель на массив из четырёх точек
	MCTYP_API bool GetFragmentBounds(int iStart, int iEnd, mcsBoundBlocksArray& bounds) const; // Габариты фрагмента от iStart символа до iEnd в простом тексте. Например для подсветки фрагмента.
	MCTYP_API int HitTest(const mcsPoint& pnt) const;// Номер символа по точке.

	bool getMaskBackground() const
		{ return 0 != (m_Flags & MCSTEXT_MASK_BACKGROUND); }

	void setMaskBackground	(bool b)
	{
		if(b)
			m_Flags |= MCSTEXT_MASK_BACKGROUND;
		else
			m_Flags &= !MCSTEXT_MASK_BACKGROUND;
		m_Flags |= MCSTEXT_DEPRECATED;
	}

	bool getAlignedToCamera() const
	{
		return 0 != (m_Flags & MCSTEXT_ALIGNED_TO_CAMERA);
	}

	void setAlignedToCamera(bool b)
	{
		if (b)
			m_Flags |= MCSTEXT_ALIGNED_TO_CAMERA;
		else
			m_Flags &= !MCSTEXT_ALIGNED_TO_CAMERA;
		m_Flags |= MCSTEXT_DEPRECATED;
	}

	// Inline property helpers
	const McsString&            get_text() const                            { return m_text; }
#ifdef WIN64
	const TCHAR                 get_text(int Index) const                   { return m_text[Index]; }
#endif
	const TCHAR                 get_text(INT_PTR Index) const               { return m_text[Index]; }
	void                        set_text(LPCTSTR Value)                     { if ((m_Flags&MCSTEXT_DEPRECATED) || m_text != Value) { m_text = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	void                        set_text(TCHAR Value)                       { if (m_text.GetLength() != 1 || m_text[0] != Value) { m_text = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const McsString&            get_textStyle() const                       { return m_textStyle; }
	void                        set_textStyle(LPCTSTR Value)                { if ((m_Flags&MCSTEXT_DEPRECATED) || m_textStyle != Value) { m_textStyle = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const mcsPoint&             get_origin() const                          { return m_origin; }
	void                        set_origin(const mcsPoint& Value)           { if ((m_Flags&MCSTEXT_DEPRECATED) || m_origin != Value) { m_origin = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const mcsVector&            get_direction() const                       { return m_direction; }
	void                        set_direction(const mcsVector& Value)       { if ((m_Flags&MCSTEXT_DEPRECATED) || m_direction != Value) { m_direction = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const McsHorizTextAlignEnum get_horizAlign() const                      { return m_horizAlign; }
	void                        set_horizAlign(McsHorizTextAlignEnum Value) { if ((m_Flags&MCSTEXT_DEPRECATED) || m_horizAlign != Value) { m_horizAlign = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const McsVertTextAlignEnum  get_vertAlign() const                       { return m_vertAlign; }
	void                        set_vertAlign(McsVertTextAlignEnum Value)   { if ((m_Flags&MCSTEXT_DEPRECATED) || m_vertAlign != Value) { m_vertAlign = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const double&               get_width() const                           { return m_width; }
	void                        set_width(const double Value)               { if (!EQU(Value,m_width)) { m_width = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const double&               get_height() const                          { return m_height; }
	void                        set_height(const double Value)              { if (!EQU(Value,m_height)) { m_height = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const double&               get_oblique() const                         { return m_oblique; }
	void                        set_oblique(const double Value)             { if (!EQU(Value,m_oblique)) { m_oblique = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const double&               get_xScale() const                          { return m_xScale; }
	void                        set_xScale(const double Value)              { if (!EQU(Value,m_xScale)) { m_xScale = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const double&               get_lineSpacing() const                     { return m_lineSpacing; }
	void                        set_lineSpacing(const double Value)         { if(!EQU(Value, m_lineSpacing)) { m_lineSpacing = Value; m_Flags |= MCSTEXT_DEPRECATED; } }
	const bool                  get_isWordWrap() const                      { return m_isWordWrap; }
	void                        set_isWordWrap(bool Value)                  { if (Value != m_isWordWrap) { m_isWordWrap = Value; m_Flags|=MCSTEXT_DEPRECATED; } }
	const double&               get_hostScale() const                       { return m_hostScale; }
	void                        set_hostScale(const double Value)           { if(!EQU(Value, m_hostScale)) { m_hostScale = Value; m_Flags |= MCSTEXT_DEPRECATED; } }
};
typedef McsArray<mcsText, const mcsText&> mcsTextsArray;

//==============================================================================
struct mcsHatch
{
	enum Style
	{
		kNormal           = 0,
		kOuter            = 1,
		kIgnore           = 2
	};
	enum PatternType
	{
		kUserDefined      = 0,// линиями (angle, spacing, patternDouble)
		kPreDefined       = 1,// по шаблону (patternName, angle, patternScale)
		kCustomDefined    = 2
	};
	enum ObjectType
	{
		kHatchObject      = 0,
		kGradientObject   = 1,
		kWipeoutObject    = 2,
	};
	enum LoopType
	{
		kDefault             = 0x0000,
		kExternal            = 0x0001,
		kPolyline            = 0x0002,
		kDerived             = 0x0004,
		kTextbox             = 0x0008,
		kOutermost           = 0x0010,
		kNotClosed           = 0x0020,
		kSelfIntersecting    = 0x0040,
		kTextIsland          = 0x0080,
		kDuplicate           = 0x0100,
		kIsAnnotative        = 0x0200,
		kDoesNotSupportScale = 0x0400,
		kForceAnnoAllVisible = 0x0800,
		kOrientToPaper       = 0x1000,
		kIsAnnotativeBlock   = 0x2000,

		// System. Mcs only.
		kComposite           = 0x80000,
	};
	enum GradientPatternType
	{
		kPreDefinedGradient  = 0,
		kUserDefinedGradient = 1
	};
	typedef mcsWorkIDArray mcsHatchAssocContour;
	typedef McsArray<mcsHatchAssocContour, const mcsHatchAssocContour&> mcsHatchAssocContours;

	mcsPolylineArray contours;
	mcsHatchAssocContours assocContours;// Must be the same size as contours, otherwise ignored.
	double           angle;
	double           spacing;// Pattern space. Only for kUserDefined hatch. 0 - for solid hatch.
	Style            hatchStyle;
	PatternType      patternType;
	McsString        patternName;// Only for kPreDefined and kCustomDefined hatches.
	double           patternScale;
	COLORREF         backgroundColor;
	bool             patternDouble;// Only for kUserDefined hatch. Double patterns apply a second set
	                               // of hatch lines at 90 degrees to the original hatch lines.
	bool             bAutoOrigin;// Начало отсчёта штриховки рассчитывается автоматически на основе баунда
	mcsPoint2d       pntOrigin;// Начало отчсёта штриховки
	bool isAssociative;
	ObjectType objectType;
	GradientPatternType gradientType;
	McsString gradientName;
	double gradientAngle;
	COLORREF gradientColor1;
	COLORREF gradientColor2;
	double gradientColorInterpolation1;
	double gradientColorInterpolation2;
	bool isGradientOneColorMode;
	double shadeTintValue;
	double gradientShift;

	DECLARE_OBJ_NEWDEL;

	MCTYP_API mcsHatch();
	MCTYP_API ~mcsHatch();

	//Constructs simple user defined hatch
	MCTYP_API mcsHatch(const mcsPolyline& _contour, const double _angle, const double _spacing, const bool _patternDouble = false);

	//Full
	MCTYP_API mcsHatch(
		const mcsPolylineArray& _contours,
		LPCTSTR _patternName,
		const double _angle,
		const double _spacing,
		const bool _patternDouble = false,
		const Style _hatchStyle = kNormal,
		const PatternType _patternType = kUserDefined,
		const double _patternScale = 1);

	bool isSolid() const
	{
		if(patternType == kUserDefined && spacing < DEF_TOL || patternType == kPreDefined && 0 == _tcsicmp(patternName, _T("SOLID")))
			return true;
		return false;
	}

	MCTYP_API mcsPoint2d getOrigin() const;

	MCTYP_API bool operator == (const mcsHatch& trg) const;
	MCTYP_API bool isEqualTo(const mcsHatch& cw, const mcsTol& tol = mcsGeContext::gTol) const;

	bool operator != (const mcsHatch& trg) const
		{ return !operator == (trg); }

	MCTYP_API void transformBy(const mcsMatrix& tfm);

	MCTYP_API mcsBoundBlock getBoundBlock(bool isOrtho = false) const;

	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);
};
typedef McsArray<mcsHatch, const mcsHatch&> mcsHatchesArray;

//==============================================================================
struct mcsArrow
{
	mcsPoint  pnt;
	mcsVector dir;
	mcsVector normal;
	MCS_ARROW eType;
	double    rSize;
	double    rWidth;

	DECLARE_OBJ_NEWDEL;

	MCTYP_API mcsArrow();
	MCTYP_API ~mcsArrow();
	MCTYP_API mcsArrow(const mcsPoint& _pnt, const mcsVector& _dir, MCS_ARROW _eType, double _rSize, double _rWidth = 0);
	MCTYP_API mcsArrow(const mcsPoint& _pnt, const mcsVector& _dir, const mcsVector& _normal, MCS_ARROW _eType, double _rSize, double _rWidth = 0);

	MCTYP_API bool operator == (const mcsArrow& t) const;
	MCTYP_API bool isEqualTo(const mcsArrow& cw, const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API mcsArrow& operator =(const mcsArrow& src);

	bool operator != (const mcsArrow& trg) const
		{ return !operator == (trg); }

	MCTYP_API void          transformBy(const mcsMatrix& tfm);
	MCTYP_API mcsBoundBlock getBoundBlock(bool isOrtho = false) const;
	MCTYP_API bool          intersectBy(const mcsLinearEntity& axis, OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API bool          intersectBy(const McsEntityGeometry& otherEnt,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API bool          asLineSeg(OUT mcsLineSeg& ls) const;

	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);
};
typedef McsArray<mcsArrow, const mcsArrow&> mcsArrowsArray;

//==============================================================================
// represents dimension arrows for linear and angular dimensions
struct mcsDimArrow
{
	mcsLineSeg m_ls;
	mcsCircArc m_ca;
	mcsVector  m_normal; // only for linear type
	bool       m_fLinear;
	bool       m_fEnd1, m_fEnd2;
	McsString  m_text;
	COLORREF   m_textColor; // color for dim text, by def may be black or white, or black/white
	byte       m_textHeight; // in pixels, 0 - default

	//.........................................................
	DECLARE_OBJ_NEWDEL;

	MCTYP_API mcsDimArrow();
	MCTYP_API ~mcsDimArrow();

	MCTYP_API void setLinear(
		const mcsLineSeg& ls,
		bool fEnd1,
		bool fEnd2,
		IN OPTIONAL LPCTSTR text = NULL,
		IN OPTIONAL const mcsVector& normal = mcsVector::kZAxis,
		IN OPTIONAL COLORREF textColor = COLORREF_SPEC_VAL,
		IN OPTIONAL byte textHeight = 0);

	MCTYP_API void setAngular(
		const mcsCircArc& ca,
		bool fEnd1,
		bool fEnd2,
		IN OPTIONAL LPCTSTR text = NULL,
		IN OPTIONAL COLORREF textColor = COLORREF_SPEC_VAL,
		IN OPTIONAL byte textHeight = 0);

	MCTYP_API mcsDimArrow& operator = (const mcsDimArrow& cf);
	MCTYP_API bool operator == (const mcsDimArrow& cw) const;
	MCTYP_API bool operator != (const mcsDimArrow& cw) const;
	MCTYP_API bool isEqualTo(const mcsDimArrow& cw, const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API void transformBy(const mcsMatrix& tfm);

	MCTYP_API mcsBoundBlock getBoundBlock(bool isOrtho = false) const;

	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);
};

typedef McsArray<mcsDimArrow, const mcsDimArrow&> mcsDimArrowsArray;

//==============================================================================

struct mcsObjGeomRef
{
public:
	mcsWorkID idObject;
	mcsMatrix tfm;

protected:
	enum ObjGeomRefFlags
	{
		kDefault       = 0x0000,
		kHardReference = 0x0001,
		kNotSnapable   = 0x0002,
	};

	LONG m_lFlags;

	// Для временной прорисовки объекта вне контейнера (для редактирования за ручки),
	// должен реализовывать IMcDbEntity, тут хранится базовый указатель для возможности сборки MapiBaseTypes
	IMcObjectPtr m_pTmpObj;

public:
	MCTYP_API mcsObjGeomRef();
	MCTYP_API mcsObjGeomRef(const mcsObjGeomRef&);
	MCTYP_API ~mcsObjGeomRef();

	MCTYP_API void setTmpObj(IMcDbEntity* pTmpDBE);
	MCTYP_API IMcDbEntityPtr getTmpObj() const;

	// возвращает объект, из которого отдаётся геометрия (с учетом getTmpObj())
	MCTYP_API IMcDbEntityPtr getObject() const;

	void setHard(bool isHard)
	{
		if(isHard)
			m_lFlags |= kHardReference;
		else
			m_lFlags &= ~kHardReference;
	}

	bool isHard() const
		{ return ((m_lFlags & kHardReference) != 0); }

	void setSnapable(bool isSnapable)
	{
		if(isSnapable)
			m_lFlags &= ~kNotSnapable;
		else
			m_lFlags |= kNotSnapable;
	}

	bool isSnapable() const
		{ return ((m_lFlags & kNotSnapable) == 0); }

	bool operator == (const mcsObjGeomRef& cw) const { return isEqualTo(cw); }
	bool operator != (const mcsObjGeomRef& cw) const  { return !isEqualTo(cw); }

	MCTYP_API void transformBy(const mcsMatrix& tfm);
	MCTYP_API bool isEqualTo(const mcsObjGeomRef& cw, const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API mcsBoundBlock getBoundBlock(bool fOrtho = false) const;
	MCTYP_API double distanceTo(const mcsPoint& pnt, mcsPoint* pNearest = NULL) const;
	MCTYP_API bool getOsnapPoints(McOsnapMode osnapMode, const mcsPoint3d& pickPoint, const mcsPoint3d& lastPoint, mcsPoint3dArray& snapPoints, double rAperture = 0) const;

	MCTYP_API bool intersectBy(const McsEntityGeometry& otherEnt, OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API bool intersectBy(const mcsCurve& curve, OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;

	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);

	MCTYP_API bool getGeometry(OUT mcsGeomEntArray&) const;

	enum TfmMatrixType
	{
		kTfmSrcObj  = 0x0001, // собственная матрицы src-объекта
		kTfmGeomRef = 0x0002, // матрица геометрической ссылки - mcsObjGeomRef::tfm
	};

	// Метод отдаёт геометрию с учетом указанных в dwRequiredTfmsMask матриц трансформации,
	// допустимы значения из множества mcsObjGeomRef::TfmMatrixType
	// вызов getGeometry соответствует маске dwRequiredTfmsMask = kTfmSrcObj | kTfmGeomRef
	MCTYP_API bool getGeometryEx(OUT mcsGeomEntArray&, DWORD dwRequiredTfmsMask) const;
};
//==============================================================================
struct mcOfsCrvHolder
{
	mcsOffsetCurve* pOfsCrv; // is always non-null(!), the curve it points to is the member 'pOriCrv'
protected:
	mcsCurve*       pOriCrv; // the curve 'pOfsCrv' keeps pointer to
public:
	//............................................................................

	DECLARE_OBJ_NEWDEL;

	mcOfsCrvHolder()
	{
		pOfsCrv = new mcsOffsetCurve(mcsLine::kXAxis, mcsVector::kZAxis, 0); // ptr mustn't be null
		pOriCrv = NULL;
	}
	//............................................................................
	mcOfsCrvHolder(const mcsOffsetCurve& OC)
	{
		pOfsCrv = NULL; pOriCrv = NULL;
		*this = OC;
	}
	//............................................................................
	mcOfsCrvHolder& operator = (const mcOfsCrvHolder& och)
	{
		if(this != &och)
			*this = *och.pOfsCrv;
		return *this;
	}
	//............................................................................
	mcOfsCrvHolder& operator = (const mcsOffsetCurve& OC)
	{
		if(pOfsCrv == &OC)
			return *this;

		setNull();

		// create new offset curve, with the same params as 'OC',
		// that refers to the copy of curve in the given 'OC'

		double dist = OC.offsetDistance();
		mcsMatrix3d tfm = OC.transformation();
		bool bReversed = !OC.paramDirection();
		mcsVector vNormal = OC.normal();
		mcsInterval ivl;
		OC.getInterval(ivl);

		pOriCrv = (mcsCurve*)OC.curve()->copy();
		pOfsCrv = new mcsOffsetCurve(*pOriCrv, vNormal, dist);
		if(bReversed)
			pOfsCrv->reverseParam();
		pOfsCrv->setInterval(ivl);
		pOfsCrv->transformBy(tfm);

		return *this;
	}
	//............................................................................
	~mcOfsCrvHolder()
	{
		setNull();
	}
	//............................................................................
	void setNull()
	{
		if(pOfsCrv) // 1'st del the ofs curve, then the curve it refers to
			delete pOfsCrv;
		pOfsCrv = NULL;
		if(pOriCrv)
			delete pOriCrv;
		pOriCrv = NULL;
	}
	//............................................................................
	MCTYP_API bool save(IMcsStream* pS) const;
	MCTYP_API bool load(IMcsStream* pS);
};
//==============================================================================
struct mcsRepeatedShape;
struct mcsMesh;

#pragma pack(push,1) // byte alignment
// following union is needed to detect necessary memory size to store all types
// of geometric entities
union __union_sz_McsEntityGeometry
{
	byte sz_point[sizeof(mcsPoint)];
	byte sz_line[sizeof(mcsLineSeg)];
	byte sz_xline[sizeof(mcsLine)];
	byte sz_ray[sizeof(mcsRay)];
	byte sz_circarc[sizeof(mcsCircArc)];
	byte sz_elliparc[sizeof(mcsEllipArc)];
	byte sz_spline[sizeof(mcsNurbCurve)];
	byte sz_ofscrv[sizeof(mcOfsCrvHolder)];
	byte sz_polyline[sizeof(mcsPolyline)];
	byte sz_plane[sizeof(mcsPlane)];
	byte sz_nurbsurf[sizeof(mcsNurbSurf)];
	byte sz_cylinder[sizeof(mcsCylinder)];
	byte sz_triangle[sizeof(mcsTriangle*)];
	byte sz_cone[sizeof(mcsCone)];
	byte sz_torus[sizeof(mcsTorus)];
	byte sz_sphere[sizeof(mcsSphere)];
	byte sz_text[sizeof(mcsText*)];
	byte sz_hatch[sizeof(mcsHatch*)];
	byte sz_arrow[sizeof(mcsArrow*)];
	byte sz_dimarrow[sizeof(mcsDimArrow*)];
	byte sz_rptshape[sizeof(mcsRepeatedShape*)];
	byte sz_objgeomref[sizeof(mcsObjGeomRef*)];
	byte sz_mesh[sizeof(mcsMesh*)];
};

//==============================================================================
// сохраняться будет байтовое представление,
// так что не выходите за рамки -128 .. +127 при добавлении нового типа;
// значения менять нельзя !
enum McGeomExtendedPropTypeEnum
{
	kMcGEPT_Undef  =  0,
	kMcGEPT_Int    =  1,
	kMcGEPT_Double =  2,
	kMcGEPT_String =  3,
	kMcGEPT_Int64  =  4,
	kMcGEPT_WorkID =  5,
	kMcGEPT_Point  =  6,
};
//==============================================================================
// в старом эквиваленте (V7-) код свойства кодировался числом;
// теперь число сохранилось, но в нижнем байте, а второй байт определяет тип свойства;
// такой способ позволяет добавлять новые свойства без изменнения процедур
// сохранения/записи, но не позволяет добавлять в пределах минорной версии новый тип
enum EMcGeomExtendedProperties
{
	kMcGeomExPropUndefined        = -1,
	kMcGeomExPropGSMarker         =  0 | (kMcGEPT_Int    << 8), // Default -1
	kMcGeomExPropLayer            =  1 | (kMcGEPT_String << 8), // Default NULL
	kMcGeomExPropLinetypeScale    =  2 | (kMcGEPT_Double << 8), // Default 0
	kMcGeomExPropVisibility       =  3 | (kMcGEPT_Int    << 8), // Default 100
	kMcGeomExPropSystemColor      =  4 | (kMcGEPT_Int    << 8), // Default MCS_ENTCOLOR_BYCONTEXT
	kMcGeomExPropSystemLineWeight =  5 | (kMcGEPT_Int    << 8), // Default MCS_ENTWEIGHT_BYCONTEXT
	kMcGeomExPropSystemLinetype   =  6 | (kMcGEPT_Int    << 8), // Default 0
	kMcGeomExPropPolylineSegment  =  7 | (kMcGEPT_Int    << 8), // System, only for cutting. Default -1 а так же Custom там где надо(контура перекрытия, маркеры)
	kMcGeomExPropConstSize        =  8 | (kMcGEPT_Int    << 8), // Default 0, used for interactive graphics in 3D to ensure object will have constant size on screen
	kMcGeomExPropLinetype         =  9 | (kMcGEPT_String << 8), // Default NULL
	kMcGeomExPropBurnThrough      = 10 | (kMcGEPT_Int    << 8), // Default 0, if !=0 then entity will not participate in z-buffer clipping, i.e. will be always visible
	kMcGeomExPropRepShapeOffset   = 11 | (kMcGEPT_Double << 8), // Default 0, system, used only in mcsRepeatedShape::path
	kMcGeomExProp_SubEntID        = 12 | (kMcGEPT_WorkID << 8), // System, Default Null, used for drawing surface entities from object bodies, not for save
	kMcGeomExPropHighlightMode    = 13 | (kMcGEPT_Int    << 8), // Default 0, use EMcGeomExPropHighlightMode flags
	kMcGeomExPropPlottable        = 14 | (kMcGEPT_Int    << 8), // Default 1, если ноль, то элемент не выводится на печать
	kMcGeomExPropCutMode          = 15 | (kMcGEPT_Int    << 8), // Default 1, если ноль, то не участвует в процессе резки и виден всегда, даже если полностью перекрыт контуром подавления
	kMcGeomExPropFragmentStart    = 16 | (kMcGEPT_Int    << 8), // Default -1, индекс символа, с которого начинается данный фрагмент в полной строке. Устанавливается на тексты в массиве mcsText::exploded. Используется в редактировании по месту.
	kMcGeomExPropUseOwnStyle      = 17 | (kMcGEPT_Int    << 8), // Default 0, если 1, то геометрия всегда будет отображаться со своим цветом, весом и типом линии, даже если является частью текста или иного составного объекта.
	kMcGeomExPropScalingPt        = 18 | (kMcGEPT_Point  << 8), // Default UNKNOWNPOINT, если задано, это координаты точки масштабирования для примитивов пиксельного размера
};

//==============================================================================
enum EMcGeomExPropHighlightMode
{
	kMcGeomHighlightModeDefault = 0x0000,
	kMcGeomHighlightModeLock    = 0x0001,// Do not change geometry properties, when highlighted.
	kMcGeomHighlightModeMark    = 0x0002,// Highlight always.
};

struct mcsComplexWorkID;

//==============================================================================
// ВНИМАНИЕ: эту структуру использовать нельзя,
// пользуйтесь McGeomExtendedPropArray
struct McGeomExtendedProp
{
	EMcGeomExtendedProperties type;
	union
	{
		int         iVal;
		double      rVal;
		__int64     i64Val;
		McsString*  pst;
		mcsComplexWorkID* pID;
		mcsPoint*   pPt;
	};
	//............................................................................
	DECLARE_OBJ_NEWDEL;

	// в версии V8+ отдельные свойства пишутся через <McGeomExtendedPropArray>
  //MCTYP_API HRESULT write(IMcsStream* pStream) const;
private:
	friend class McGeomExtendedPropArray;
	MCTYP_API HRESULT read(IMcsStream* pStream); // метод используется только для чтения старых данных, поэтому нет метода 'write'

	//............................................................................
public:
	MCTYP_API McGeomExtendedProp();
	MCTYP_API McGeomExtendedProp(const McGeomExtendedProp& src);
	MCTYP_API McGeomExtendedProp(EMcGeomExtendedProperties _type, int value);
	MCTYP_API McGeomExtendedProp(EMcGeomExtendedProperties _type, double value);
	MCTYP_API McGeomExtendedProp(EMcGeomExtendedProperties _type, LPCTSTR value);
	MCTYP_API McGeomExtendedProp(EMcGeomExtendedProperties _type, const mcsPoint& pt);
	MCTYP_API McGeomExtendedProp(EMcGeomExtendedProperties _type, const mcsComplexWorkID& value);

	MCTYP_API ~McGeomExtendedProp();

	MCTYP_API void set(EMcGeomExtendedProperties _type, LPCTSTR st);
	MCTYP_API void set(EMcGeomExtendedProperties _type, const mcsComplexWorkID& id);
	MCTYP_API void set(EMcGeomExtendedProperties _type, const mcsPoint& pt);

	MCTYP_API bool operator !=(const McGeomExtendedProp& cw) const;
	MCTYP_API bool operator ==(const McGeomExtendedProp& cw) const;

	MCTYP_API McGeomExtendedProp& operator =(const McGeomExtendedProp& src);
	MCTYP_API void Clear();
};
//==============================================================================
class McGeomExtendedPropArray : public McsArray<McGeomExtendedProp, const McGeomExtendedProp&>
{
public:
	DECLARE_OBJ_NEWDEL;

	bool propertyExists(EMcGeomExtendedProperties type) const {
		return (-1 != findProperty(type));
	}

	MCTYP_API HRESULT write(IMcsStream* pStream) const;
	MCTYP_API HRESULT read(IMcsStream* pStream);

	MCTYP_API void  matchProperties(const McGeomExtendedPropArray& src, McMatchPropEnum props);

	MCTYP_API void    setIProperty(EMcGeomExtendedProperties type, int value);
	MCTYP_API void    setRProperty(EMcGeomExtendedProperties type, double value);
	MCTYP_API void    setSProperty(EMcGeomExtendedProperties type, LPCTSTR value);
	MCTYP_API void    setIDProperty(EMcGeomExtendedProperties type, const mcsComplexWorkID& value);
	MCTYP_API void    setPtProperty(EMcGeomExtendedProperties type, const mcsPoint& value);

	MCTYP_API int       getIProperty(EMcGeomExtendedProperties type) const;
	MCTYP_API double    getRProperty(EMcGeomExtendedProperties type) const;
	MCTYP_API LPCTSTR   getSProperty(EMcGeomExtendedProperties type) const;
	MCTYP_API mcsComplexWorkID getIDProperty(EMcGeomExtendedProperties type) const;
	MCTYP_API mcsPoint  getPtProperty(EMcGeomExtendedProperties type) const;

	MCTYP_API bool operator == (const McGeomExtendedPropArray& src) const;

	bool operator != (const McGeomExtendedPropArray& src) const
		{ return !(*this == src); }

	MCTYP_API int findProperty(EMcGeomExtendedProperties type) const;
};

//==============================================================================
struct McsEntityGeometry
{
	byte                   _ent_storage[sizeof(__union_sz_McsEntityGeometry)];
	EntityGeometryTypeEnum _entType;
	McGeomExtendedPropArray exProps;

public:
	COLORREF               color;
	int                    iLineType; //GOST TYPE INDEX 1-9
	int                    iLineWeight; //one of enum AcadLineWeight or AcDb::LineWeight

	void clearExProperties()
		{ exProps.RemoveAll(); }
	bool propertyExists(EMcGeomExtendedProperties type) const
		{ return exProps.propertyExists(type); }
	void setIProperty(EMcGeomExtendedProperties type, int value)
		{ exProps.setIProperty(type, value); }
	void setRProperty(EMcGeomExtendedProperties type, double value)
		{ exProps.setRProperty(type, value); }
	void setSProperty(EMcGeomExtendedProperties type, LPCTSTR value)
		{ exProps.setSProperty(type, value); }
	void setIDProperty(EMcGeomExtendedProperties type, const mcsComplexWorkID& value)
		{ exProps.setIDProperty(type, value); }
	void setPtProperty(EMcGeomExtendedProperties type, const mcsPoint& value)
		{ exProps.setPtProperty(type, value); }
	int getIProperty(EMcGeomExtendedProperties type) const
		{ return exProps.getIProperty(type); }
	double getRProperty(EMcGeomExtendedProperties type) const
		{ return exProps.getRProperty(type); }
	LPCTSTR getSProperty(EMcGeomExtendedProperties type) const
		{ return exProps.getSProperty(type); }
	MCTYP_API mcsComplexWorkID getIDProperty(EMcGeomExtendedProperties type) const;
	MCTYP_API mcsPoint getPtProperty(EMcGeomExtendedProperties type) const;

	bool isVisible() const
		{ return 0!=exProps.getIProperty(kMcGeomExPropVisibility);}

	void setVisible(bool fVisible)
		{ exProps.setIProperty(kMcGeomExPropVisibility, fVisible ? 100 : 0);}

	MCTYP_API void setLinetype(LPCTSTR stLT);
	MCTYP_API void setLinetype(int iLT);

	DECLARE_OBJ_NEWDEL;

	MCTYP_API McsEntityGeometry();

	// helper constructors
	MCTYP_API McsEntityGeometry(const mcsPoint&);
	MCTYP_API McsEntityGeometry(const mcsLineSeg&);
	MCTYP_API McsEntityGeometry(const mcsLine&);
	MCTYP_API McsEntityGeometry(const mcsRay&);
	MCTYP_API McsEntityGeometry(const mcsCircArc&);
	MCTYP_API McsEntityGeometry(const mcsEllipArc&);
	MCTYP_API McsEntityGeometry(const mcsNurbCurve&);
	MCTYP_API McsEntityGeometry(const mcsOffsetCurve&);
	MCTYP_API McsEntityGeometry(const mcsCurve&);
	MCTYP_API McsEntityGeometry(const mcsPolyline&);
	MCTYP_API McsEntityGeometry(const mcsPlane&);
	MCTYP_API McsEntityGeometry(const mcsTriangle&);
	MCTYP_API McsEntityGeometry(const mcsCylinder&);
	MCTYP_API McsEntityGeometry(const mcsCone&);
	MCTYP_API McsEntityGeometry(const mcsTorus&);
	MCTYP_API McsEntityGeometry(const mcsSphere&);
	MCTYP_API McsEntityGeometry(const mcsNurbSurf&);
	MCTYP_API McsEntityGeometry(const mcsText&);
	MCTYP_API McsEntityGeometry(const mcsHatch&);
	MCTYP_API McsEntityGeometry(const mcsArrow&);
	MCTYP_API McsEntityGeometry(const mcsDimArrow&);
	MCTYP_API McsEntityGeometry(const mcsRepeatedShape&);
	MCTYP_API McsEntityGeometry(const mcsObjGeomRef&);
	MCTYP_API McsEntityGeometry(const mcsMesh&);
	MCTYP_API McsEntityGeometry(Mc3dImage* p3dImg);

	MCTYP_API McsEntityGeometry(const McsEntityGeometry&);
	MCTYP_API ~McsEntityGeometry();

	MCTYP_API EntityGeometryTypeEnum geometryType() const;

	__inline bool isNull() const {
		return _entType == kMcsNull;
	}

	MCTYP_API mcsPoint&    point();                           ;;;       MCTYP_API const mcsPoint&    point() const;
	MCTYP_API mcsLineSeg&  line();                            ;;;       MCTYP_API const mcsLineSeg&  line() const;
	MCTYP_API mcsLine&     xline();                           ;;;       MCTYP_API const mcsLine&     xline() const;
	MCTYP_API mcsRay&      ray();                             ;;;       MCTYP_API const mcsRay&      ray() const;
	MCTYP_API mcsLinearEntity& lineEnt();                     ;;;       MCTYP_API const mcsLinearEntity& lineEnt() const;
	MCTYP_API mcsCircArc&  circarc();                         ;;;       MCTYP_API const mcsCircArc&  circarc() const;
	MCTYP_API mcsEllipArc& elliparc();                        ;;;       MCTYP_API const mcsEllipArc& elliparc() const;
	MCTYP_API mcsNurbCurve& spline();                         ;;;       MCTYP_API const mcsNurbCurve& spline() const;
	MCTYP_API mcsOffsetCurve& ofscrv();                       ;;;       MCTYP_API const mcsOffsetCurve& ofscrv() const;
	MCTYP_API mcsPolyline& polyline();                        ;;;       MCTYP_API const mcsPolyline& polyline() const;
	MCTYP_API mcsPlane&    plane();                           ;;;       MCTYP_API const mcsPlane&    plane() const;
	MCTYP_API mcsCylinder& cylinder();                        ;;;       MCTYP_API const mcsCylinder& cylinder() const;
	MCTYP_API mcsTriangle& triangle();                        ;;;       MCTYP_API const mcsTriangle& triangle() const;
	MCTYP_API mcsCone&     cone();                            ;;;       MCTYP_API const mcsCone&     cone() const;
	MCTYP_API mcsTorus&    torus();                           ;;;       MCTYP_API const mcsTorus&    torus() const;
	MCTYP_API mcsSphere&   sphere();                          ;;;       MCTYP_API const mcsSphere&   sphere() const;
	MCTYP_API mcsNurbSurf& nurbSurf();                        ;;;       MCTYP_API const mcsNurbSurf& nurbSurf() const;
	MCTYP_API mcsText&     text();                            ;;;       MCTYP_API const mcsText&     text() const;
	MCTYP_API mcsHatch&    hatch();                           ;;;       MCTYP_API const mcsHatch&    hatch() const;
	MCTYP_API mcsArrow&    arrow();                           ;;;       MCTYP_API const mcsArrow&    arrow() const;
	MCTYP_API mcsDimArrow& dimArrow();                        ;;;       MCTYP_API const mcsDimArrow& dimArrow() const;
	MCTYP_API mcsRepeatedShape& rptShape();                   ;;;       MCTYP_API const mcsRepeatedShape& rptShape() const;
	MCTYP_API mcsObjGeomRef& objGRef();                       ;;;       MCTYP_API const mcsObjGeomRef& objGRef() const;
	MCTYP_API mcsMesh&     mesh();                            ;;;       MCTYP_API const mcsMesh&     mesh() const;
	MCTYP_API Mc3dImagePtr image3d() const;

	MCTYP_API void setGeometryType(EntityGeometryTypeEnum newType);

	MCTYP_API McsEntityGeometry& setNull();
	MCTYP_API McsEntityGeometry& set(const mcsPoint&);        ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsPoint&);
	MCTYP_API McsEntityGeometry& set(const mcsLineSeg&);      ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsLineSeg&);
	MCTYP_API McsEntityGeometry& set(const mcsLine&);         ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsLine&);
	MCTYP_API McsEntityGeometry& set(const mcsRay&);          ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsRay&);
	MCTYP_API McsEntityGeometry& set(const mcsCircArc&);      ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsCircArc&);
	MCTYP_API McsEntityGeometry& set(const mcsEllipArc&);     ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsEllipArc&);
	MCTYP_API McsEntityGeometry& set(const mcsNurbCurve&);    ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsNurbCurve&);
	MCTYP_API McsEntityGeometry& set(const mcsOffsetCurve&);  ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsOffsetCurve&);
	MCTYP_API McsEntityGeometry& set(const mcsCurve&);        ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsCurve&);
	MCTYP_API McsEntityGeometry& set(const mcsPolyline&);     ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsPolyline&);
	MCTYP_API McsEntityGeometry& set(const mcsPlane&);        ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsPlane&);
	MCTYP_API McsEntityGeometry& set(const mcsTriangle&);     ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsTriangle&);
	MCTYP_API McsEntityGeometry& set(const mcsCylinder&);     ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsCylinder&);
	MCTYP_API McsEntityGeometry& set(const mcsCone&);         ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsCone&);
	MCTYP_API McsEntityGeometry& set(const mcsTorus&);        ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsTorus&);
	MCTYP_API McsEntityGeometry& set(const mcsSphere&);       ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsSphere&);
	MCTYP_API McsEntityGeometry& set(const mcsNurbSurf&);     ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsNurbSurf&);
	MCTYP_API McsEntityGeometry& set(const mcsText&);         ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsText&);
	MCTYP_API McsEntityGeometry& set(const mcsHatch&);        ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsHatch&);
	MCTYP_API McsEntityGeometry& set(const mcsArrow&);        ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsArrow&);
	MCTYP_API McsEntityGeometry& set(const mcsDimArrow&);     ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsDimArrow&);
	MCTYP_API McsEntityGeometry& set(const mcsRepeatedShape&);;;;       MCTYP_API McsEntityGeometry& operator = (const mcsRepeatedShape&);
	MCTYP_API McsEntityGeometry& set(const mcsObjGeomRef&);   ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsObjGeomRef&);
	MCTYP_API McsEntityGeometry& set(const mcsMesh&);         ;;;       MCTYP_API McsEntityGeometry& operator = (const mcsMesh&);
	MCTYP_API McsEntityGeometry& set(Mc3dImage*);             ;;;       MCTYP_API McsEntityGeometry& operator = (Mc3dImage*);

	MCTYP_API McsEntityGeometry& operator = (const McsEntityGeometry&);

	MCTYP_API bool operator == (const McsEntityGeometry&) const;

	bool operator != (const McsEntityGeometry& cw) const {
		return !operator == (cw);
	}

		// если fCmpGeomOnly = true, то будет сравнивать только геометрию, игнорирую различия в цветах, типе и свойствах
	MCTYP_API bool isEqualToAs3dNode(const McsEntityGeometry& otherGeom, const mcsTol& tol = mcsGeContext::gTol, IN OPTIONAL bool fCmpGeomOnly = false) const;

		// если fCmpGeomOnly = true, то будет сравнивать только геометрию, игнорирую различия в цветах, типе и свойствах
	MCTYP_API bool isEqualTo(const McsEntityGeometry& otherGeom, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol, IN OPTIONAL bool fCmpGeomOnly = false) const;

	MCTYP_API void setPropertiesFrom(const McsEntityGeometry&, McMatchPropEnum props = kMcMPropAll);

	MCTYP_API mcsVector     getDirVector() const;
	MCTYP_API bool          transformBy(const mcsMatrix& tfm);
	MCTYP_API bool          intersectBy(const mcsLinearEntity& axis,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API bool          intersectBy(const mcsLinearEntity& axis,OUT mcsPoint3dArray& crossPoints, OUT OPTIONAL mcsVector3dArray* pSurfNormals, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API bool          intersectBy(const McsEntityGeometry& otherEnt,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API mcsBoundBlock getBoundBlock() const;
	MCTYP_API mcsBoundBlock getOrthoBoundBlock() const;

	MCTYP_API const mcsEntity3d*     asGeEnt3d() const;
	MCTYP_API const mcsPoint*        asPoint() const;
	MCTYP_API const mcsLinearEntity* asLinearEnt() const;
	MCTYP_API const mcsCurve*        asCurve() const;
	MCTYP_API const mcsSurface*      asSurface() const;

	mcsEntity3d*     asGeEnt3d()    { return (mcsEntity3d*)     ((const McsEntityGeometry*)this)->asGeEnt3d(); }
	mcsPoint*        asPoint()      { return (mcsPoint*)        ((const McsEntityGeometry*)this)->asPoint(); }
	mcsLinearEntity* asLinearEnt()  { return (mcsLinearEntity*) ((const McsEntityGeometry*)this)->asLinearEnt(); }
	mcsCurve*        asCurve()      { return (mcsCurve*)        ((const McsEntityGeometry*)this)->asCurve(); }
	mcsSurface*      asSurface()    { return (mcsSurface*)      ((const McsEntityGeometry*)this)->asSurface(); }

	// if normal is not perpendicular to ptEnd-ptStart line, then method will try
	// automatically recalculate given normal
	MCTYP_API static mcsCircArc& sMakeArcWithBulge(
		const mcsPoint& ptStart,
		const mcsPoint& ptEnd,
		const mcsVector& normal,
		double rBulge,
		OUT mcsCircArc& arc,
		const mcsTol& = mcsGeContext::gTol);

	// returns number of read bytes
	MCTYP_API bool save(IMcsStream* pStreamTo) const;
	MCTYP_API bool load(IMcsStream* pStreamFrom);

	MCTYP_API bool getOsnapPoints(
		McOsnapMode             osnapMode,
		const mcsPoint3d&       pickPoint,
		const mcsPoint3d&       lastPoint,
		IN OUT mcsPoint3dArray& snapPoints) const;

	MCTYP_API bool getOsnapPoints(
		McOsnapMode                  osnapMode,
		const mcsPoint3d&            pickPoint,
		const mcsPoint3d&            lastPoint,
		IN OUT mcsPoint3dArray&      snapPoints,
		IN OPTIONAL const mcsMatrix* pXyProjTfm) const;

private:
	MCTYP_API void _DestructContents();
	MCTYP_API void _SetContentsType(EntityGeometryTypeEnum newType);
	MCTYP_API void _initDefault();

	friend class mcsGeomEntArray;
};
#pragma pack(pop)

//==============================================================================
struct mcsRepeatedShape
{
	McsEntityGeometry path;// Путь
	double            rLineLength;// Длина линии
	double            rSpaceLength;// Длина пробела
	double            rGeometryPos;// Положение массива геометрии относительно начала сегмента. rGeometryPos < rLineLength + rSpaceLength
	mcsGeomEntArray   geometry;

	DECLARE_OBJ_NEWDEL;

	mcsRepeatedShape()
	{
		rLineLength = 0;
		rSpaceLength = 0;
		rGeometryPos = 0;
	}

	MCTYP_API bool operator ==(const mcsRepeatedShape& cmpWith) const;
	MCTYP_API void transformBy(const mcsMatrix& tfm);
	MCTYP_API bool isEqualTo(const mcsRepeatedShape& cw, const mcsTol& tol = mcsGeContext::gTol) const;

	bool operator != (const mcsRepeatedShape& trg) const
		{ return !operator == (trg); }

	MCTYP_API mcsBoundBlock getBoundBlock(bool isOrtho = false) const;
	MCTYP_API bool          intersectBy(const mcsLinearEntity& axis,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API bool          intersectBy(const mcsCircArc& ca,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API bool          intersectBy(const mcsEllipArc& ea,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API bool          intersectBy(const mcsSpline& spline,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;
	MCTYP_API bool          intersectBy(const McsEntityGeometry& otherEnt,OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol) const;

	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);
};

#endif // MCGELDLL
//==================================================================================================

/*
mesh 4x3
vertices, nr*nc = 4*3 = 12:
    c0  c1  c2
r0   0---1---2
     |   |   |
r1   3---4---5
     |   |   |
r2   6---7---8
     |   |   |
r3   9--10--11
*/

struct mcsMeshVertsData
{
protected:
	int               m_nc, m_nr;
	mcsVector3dArray* m_pNormals; // NULL = auto
	mcsColorsArray*   m_pColors;  // MAPI colors, NULL = by context

public:
	DECLARE_OBJ_NEWDEL;

	MCGEL_API ~mcsMeshVertsData();
	MCGEL_API mcsMeshVertsData(int nRows, int nCols);
	MCGEL_API mcsMeshVertsData(const mcsMeshVertsData& cf);
	MCGEL_API mcsMeshVertsData& operator =(const mcsMeshVertsData&);

	bool isEmpty() const { return !m_pNormals && !m_pColors; }
	int  totalCount() const { return m_nc * m_nr; }

	MCGEL_API void clear();
	MCGEL_API void purgeColors();
	MCGEL_API void purgeNormals();

	MCGEL_API mcsColorsArray&   allocColors(bool bForLoad = false);
	MCGEL_API mcsVector3dArray& allocNormals(bool bForLoad = false);

	MCGEL_API bool isEqualTo(
		const mcsMeshVertsData& cw,
		bool                    fCmpGeomOnly = false,
		const mcsTol&           tol = mcsGeContext::gTol) const;

	MCGEL_API void transformBy(const mcsMatrix& tfm);

	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);

protected:

	MCTYP_API bool _save_v1(IMcsStream*) const;
	MCTYP_API bool _load_v1(IMcsStream*);

	friend struct mcsMesh;
};
//==============================================================================
enum mcsMeshEdgeSetDirEnum
{
	kRow = 0,
	kCol = 1
};

/*
mesh 4x3
edges, ((nr-1)*nc + nr*(nc-1)) = 3*3 + 4*2 = 17:
    c0    c1    c2
r0   +--0--+--1--+
     |     |     |
     8    11    14
     |     |     |
r1   +--2--+--3--+
     |     |     |
     9    12    15
     |     |     |
r2   +--4--+--5--+
     |     |     |
    10    13    16
     |     |     |
r3   +--6--+--7--+
*/

struct mcsMeshEdgesData
{
protected:
	int                  m_nc, m_nr;
	mcsLinetypesArray*   m_pLineTypes;   // NULL = by context
	mcsIntArray*         m_pGsMarkers;    // NULL = no edges detailing in mesh for selection
	mcsBoolArray*        m_pVisibilities; // NULL = all grid-edges are visible
	mcsColorsArray*      m_pColors;       // MAPI colors, NULL = by context

public:
	DECLARE_OBJ_NEWDEL;

	MCGEL_API ~mcsMeshEdgesData();
	MCGEL_API mcsMeshEdgesData(int nRows, int nCols);
	MCGEL_API mcsMeshEdgesData(const mcsMeshEdgesData& cf);
	MCGEL_API mcsMeshEdgesData& operator =(const mcsMeshEdgesData&);

	bool isEmpty() const { return !m_pLineTypes && !m_pGsMarkers && !m_pVisibilities && !m_pColors; }
	int  totalCount() const { return (m_nr - 1) * m_nc + m_nr * (m_nc - 1); }

	MCGEL_API void clear();
	MCGEL_API void purgeLineTypes();
	MCGEL_API void purgeGsMarkers();
	MCGEL_API void purgeVisibilities();
	MCGEL_API void purgeColors();

	MCGEL_API mcsLinetypesArray& allocLineTypes(bool bForLoad = false);
	MCGEL_API mcsIntArray&       allocGsMarkers(bool bForLoad = false);
	MCGEL_API mcsBoolArray&      allocVisibilities(bool bForLoad = false);
	MCGEL_API mcsColorsArray&    allocColors(bool bForLoad = false);

	MCGEL_API bool isEqualTo(
		const mcsMeshEdgesData& cw,
		bool                    fCmpGeomOnly = false,
		const mcsTol&           tol = mcsGeContext::gTol) const;

	MCGEL_API void transformBy(const mcsMatrix& tfm);

	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);

protected:

	MCTYP_API bool _save_v1(IMcsStream*) const;
	MCTYP_API bool _load_v1(IMcsStream*);

	friend struct mcsMesh;
};
//==============================================================================
/*
mesh 4x3
faces, ((nr-1) * (nc-1)) = 3*2 = 6:
    c0  c1  c2
r0   +---+---+
     | 0 | 1 |
r1   +---+---+
     | 2 | 3 |
r2   +---+---+
     | 4 | 5 |
r3   +---+---+
*/

struct mcsMeshFacesData
{
protected:
	int                 m_nc, m_nr;
	mcsVector3dArray*   m_pNormals;        // NULL = Auto
	mcsBoolArray*       m_pVisibilities;   // NULL = all grid-edges are visible
	mcsByteArray*       m_pTransparencies; // byte per face, 0 (opaque) ... 255 (transparent)
	mcsIntArray*        m_pGsMarkers;      // NULL = no faces detailing in mesh for selection
	mcsColorsArray*     m_pColors;         // MAPI colors, NULL = by context

public:
	DECLARE_OBJ_NEWDEL;

	MCGEL_API ~mcsMeshFacesData();
	MCGEL_API mcsMeshFacesData(int nRows, int nCols);
	MCGEL_API mcsMeshFacesData(const mcsMeshFacesData& cf);
	MCGEL_API mcsMeshFacesData& operator =(const mcsMeshFacesData&);

	bool isEmpty() const { return !m_pNormals && !m_pVisibilities && !m_pTransparencies && !m_pGsMarkers && !m_pColors; }
	int  totalCount() const { return (m_nr - 1) * (m_nc - 1); }

	MCGEL_API void clear();
	MCGEL_API void purgeNormals();
	MCGEL_API void purgeGsMarkers();
	MCGEL_API void purgeVisibilities();
	MCGEL_API void purgeTransparencies();
	MCGEL_API void purgeColors();

	MCGEL_API mcsVector3dArray& allocNormals(bool bForLoad = false);
	MCGEL_API mcsIntArray&      allocGsMarkers(bool bForLoad = false);
	MCGEL_API mcsBoolArray&     allocVisibilities(bool bForLoad = false);
	MCGEL_API mcsByteArray&     allocTransparencies(bool bForLoad = false);
	MCGEL_API mcsColorsArray&   allocColors(bool bForLoad = false);

	MCGEL_API bool isEqualTo(
		const mcsMeshFacesData& cw,
		bool                    fCmpGeomOnly = false,
		const mcsTol&           tol = mcsGeContext::gTol) const;

	MCGEL_API void transformBy(const mcsMatrix& tfm);

	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);

protected:

	MCTYP_API bool _save_v1(IMcsStream*) const;
	MCTYP_API bool _load_v1(IMcsStream*);

	friend struct mcsMesh;
};
//==============================================================================

enum ShellInternalEdgesHideMethod
{
	kMcHideEdgesNone = 0,
	kMcHideEdgesByCounting, // скрывает все рёбра, которые используются в сетке более двух раз
	kMcHideEdgesByNormals, // скрывает ребра, у которых на стыке нормали соседних граней образуют угол больше некоторого порогового значения
	kMcHideEdgesAll, // скрывает все рёбра
};
//==============================================================================

// Функция генерирует массив видимостей рёбер сетки на основе данных о нормалях её полигонов.
// Нормали полигонов вычисляются на основе вершин полигонов. (TODO: учитывать данные нормалей на входе)
MCGEL_API
bool mcGenerateEdgeVisibilitiesByNormals(
	IN OUT mcsPoint3dArray& points,  // "OUT" if bOptimizePoints is true
	IN OUT mcsIntArray&     indices, // "OUT" if bOptimizePoints is true
	OUT mcsByteArray&       edgeVisibilities,
	bool                    bOptimizePoints = false);

// То же, что и функция выше, но без оптимизации данных вершин.
MCGEL_API
bool mcGenerateEdgeVisibilitiesByNormals_noVtxOpt(
	IN const mcsPoint3dArray& points,
	IN const mcsIntArray&     indices,
	OUT mcsByteArray&         edgeVisibilities);

// Функция генерирует массив видимостей рёбер сетки на основе данных о количестве раз, которое ребро используется в сетке.
MCGEL_API
bool mcGenerateEdgeVisibilitiesByCount(
	IN const mcsPoint3dArray& points,
	IN const mcsIntArray&     indices,
	OUT mcsByteArray&         edgeVisibilities);

//==============================================================================

struct mcsMesh
{
protected:
	int               m_nc, m_nr;
	mcsPoint3dArray   m_points;

		// data for the shell-type
		// size of pShellNormals must be equal to the size of points
		// sizeof of pShellIndices must be multiple of 3 and must contain integers that are indices in
		// the <points> member;
		// each triple of indices defines vertices for the triangular piece of a shell

	mcsVector3dArray* m_pShellNormals;
	mcsIntArray*      m_pShellIndices;
	mcsByteArray*     m_pShellEdgeVisibilities;
	ShellInternalEdgesHideMethod m_shellEdgesHideMethod;

	mcsMeshVertsData* m_pVD;
	mcsMeshEdgesData* m_pED;
	mcsMeshFacesData* m_pFD;

public:
	DECLARE_OBJ_NEWDEL;

	MCGEL_API mcsMesh();
	MCGEL_API mcsMesh(const mcsMesh&);
	MCGEL_API mcsMesh(int nRows, int nCols);
	MCGEL_API ~mcsMesh();

	MCGEL_API bool init(int nRows, int nCols);
	MCGEL_API mcsMesh& operator = (const mcsMesh&);

	// {{ shell-type support

	MCGEL_API bool initForShell(
		const mcsPoint3dArray&  vertices,
		const mcsVector3dArray& normals,
		const mcsDwordArray& facesIndices);

	MCGEL_API bool initForShell(
		int nVertices, const mcsPoint*  pVertices,
		int nNormals,  const mcsVector* pNormals,
		int nIndices,  const DWORD*     pIndices);

	bool isShell() const { return NULL != m_pShellIndices; }

		// call the following methods only if object is of the shell-type
	const mcsPoint3dArray&  shellVertices() const { return m_points; }
	const mcsVector3dArray& shellNormals() const { return *m_pShellNormals; }
	const mcsIntArray&      shellIndices() const { return *m_pShellIndices; }
	const mcsByteArray&     shellEdgeVisibilities() const { return *m_pShellEdgeVisibilities; }

	MCGEL_API bool hideShellInternalEdges(ShellInternalEdgesHideMethod hideMethod);
	MCGEL_API void showShellInternalEdges();

protected:

	MCGEL_API mcsVector3dArray& allocNormalsForShell(int nNormals = 0);
	MCGEL_API mcsIntArray&      allocIndicesForShell(int nIndices = 0);
	MCGEL_API mcsByteArray&     allocEdgeVisibilitiesForShell(int nEdges = 0);

	MCTYP_API bool hideShellInternalEdgesByCounting();
	MCTYP_API bool hideShellInternalEdgesByNormals();
	MCTYP_API bool hideAllShellInternalEdges();
	MCTYP_API int  getNumShellEdges() const;

public:
	// }} shell-type support

	int            numRows() const { return m_nr; }
	int            numCols() const { return m_nc; }

	bool           hasVertsData() const { return !!m_pVD; }
	bool           hasEdgesData() const { return !!m_pED; }
	bool           hasFacesData() const { return !!m_pFD; }

	bool           hasVertNormals() const { return m_pVD && m_pVD->m_pNormals; }
	bool           hasVertColors() const { return m_pVD && m_pVD->m_pColors; }

	bool           hasEdgeLinetypes() const { return m_pED && m_pED->m_pLineTypes; }
	bool           hasEdgeVisibilities() const { return m_pED && m_pED->m_pVisibilities; }
	bool           hasEdgeGsMarkers() const { return m_pED && m_pED->m_pGsMarkers; }
	bool           hasEdgeColors() const { return m_pED && m_pED->m_pColors; }

	bool           hasFaceNormals() const { return m_pFD && m_pFD->m_pNormals; }
	bool           hasFaceVisibilities() const { return m_pFD && m_pFD->m_pVisibilities; }
	bool           hasFaceTransparencies() const { return m_pFD && m_pFD->m_pTransparencies; }
	bool           hasFaceGsMarkers() const { return m_pFD && m_pFD->m_pGsMarkers; }
	bool           hasFaceColors() const { return m_pFD && m_pFD->m_pColors; }

	MCGEL_API void clear();

	// resets V/E/F to be default
	MCGEL_API void purgeVertsData();
	MCGEL_API void purgeEdgesData();
	MCGEL_API void purgeFacesData();

	MCGEL_API void purgeVertNormals();
	MCGEL_API void purgeVertColors();

	MCGEL_API void purgeEdgeLinetypes();
	MCGEL_API void purgeEdgeVisibilities();
	MCGEL_API void purgeEdgeGsMarkers();
	MCGEL_API void purgeEdgeColors();

	MCGEL_API void purgeFaceNormals();
	MCGEL_API void purgeFaceVisibilities();
	MCGEL_API void purgeFaceTransparencies();
	MCGEL_API void purgeFaceGsMarkers();
	MCGEL_API void purgeFaceColors();

	MCGEL_API bool isEqualTo(
		const mcsMesh& cw,
		bool           fCmpGeomOnly = false,
		const mcsTol&  tol = mcsGeContext::gTol) const;

	MCGEL_API void transformBy(const mcsMatrix& tfm);
	MCGEL_API mcsBoundBlock getBoundBlock(bool fOrtho = false) const;

	MCTYP_API bool save(IMcsStream*) const;
	MCTYP_API bool load(IMcsStream*);

protected:

	MCTYP_API bool _save_v1(IMcsStream*) const;
	MCTYP_API bool _load_v1(IMcsStream* pS, WORD vMinor);

public:

	MCTYP_API Mc3dImagePtr getAsImage() const;
	MCTYP_API HRESULT      setFromImage(Mc3dImage* pFrom);

	MCGEL_API long calcShellSize() const;


	//............................................................................
	// basic grid coordinates control (vertices)

	// num of verts = numRows * numCols; see numeration at mcsMeshVerticesData definition
	// num of edges = (numRows - 1) * numCols + numRows * (numCols - 1); see numeration at mcsMeshEdgesData definition
	// num of faces = (numRows - 1) * (numCols - 1); see numeration at mcsMeshFacesData definition

	MCGEL_API mcsPoint&        pointAt (int iRow, int iCol);
	MCGEL_API const mcsPoint&  pointAt (int iRow, int iCol) const;
	MCGEL_API mcsPoint*        operator [] (int iRow);       // valid range: 0..nRows-1
	MCGEL_API const mcsPoint*  operator [] (int iRow) const; // valid range: 0..nRows-1

	mcsPoint*                  pointsData () { return m_points.GetData(); }
	const mcsPoint*            pointsData () const { return m_points.GetData(); }

	//............................................................................
	// vertices addon control

	MCGEL_API mcsVector&       vertexNormalAt(int iRow, int iCol);
	MCGEL_API const mcsVector& vertexNormalAt(int iRow, int iCol) const;

	MCGEL_API mcsColor&        vertexColorAt(int iRow, int iCol);
	MCGEL_API const mcsColor&  vertexColorAt(int iRow, int iCol) const;

	MCGEL_API mcsVector*       vertNormals();       // valid range: 0..(nRows*nCols)-1
	MCGEL_API const mcsVector* vertNormals() const; // valid range: 0..(nRows*nCols)-1
	MCGEL_API mcsVector*       vertNormalsAtRow(int iRow);       // valid range: 0..nCols-1
	MCGEL_API const mcsVector* vertNormalsAtRow(int iRow) const; // valid range: 0..nCols-1

	MCGEL_API mcsColor*        vertColors();       // valid range: 0..(nRows*nCols)-1
	MCGEL_API const mcsColor*  vertColors() const; // valid range: 0..(nRows*nCols)-1
	MCGEL_API mcsColor*        vertColorsAtRow(int iRow);       // valid range: 0..nCols-1
	MCGEL_API const mcsColor*  vertColorsAtRow(int iRow) const;  // valid range: 0..nCols-1

	//............................................................................
	// edges addon control

	// eDir   - defines edges set - row of edges or column of edges,
	// idxDir - defines index of row or column depends on eDir value

	MCGEL_API mcsLinetype&       edgeLinetypeAt(mcsMeshEdgeSetDirEnum eDir, int idxDir, int idxInDir);
	MCGEL_API const mcsLinetype& edgeLinetypeAt(mcsMeshEdgeSetDirEnum eDir, int idxDir, int idxInDir) const;

	MCGEL_API int&               edgeGsMarkerAt(mcsMeshEdgeSetDirEnum eDir, int idxDir, int idxInDir);
	MCGEL_API const int&         edgeGsMarkerAt(mcsMeshEdgeSetDirEnum eDir, int idxDir, int idxInDir) const;

	MCGEL_API bool&              edgeVisibilityAt(mcsMeshEdgeSetDirEnum eDir, int idxDir, int idxInDir);
	MCGEL_API const bool&        edgeVisibilityAt(mcsMeshEdgeSetDirEnum eDir, int idxDir, int idxInDir) const;

	MCGEL_API mcsColor&          edgeColorAt(mcsMeshEdgeSetDirEnum eDir, int idxDir, int idxInDir);
	MCGEL_API const mcsColor&    edgeColorAt(mcsMeshEdgeSetDirEnum eDir, int idxDir, int idxInDir) const;

	MCGEL_API mcsLinetype*       edgeLinetypes();       // valid range: 0 .. (nCols-1)*nRows + nCols*(nRows-1) - 1
	MCGEL_API const mcsLinetype* edgeLinetypes() const; // valid range: 0 .. (nCols-1)*nRows + nCols*(nRows-1) - 1
	MCGEL_API mcsLinetype*       edgeLinetypesAtDir(mcsMeshEdgeSetDirEnum eDir, int idxDir);       // valid range: 0 .. nRows|nCols-1
	MCGEL_API const mcsLinetype* edgeLinetypesAtDir(mcsMeshEdgeSetDirEnum eDir, int idxDir) const; // valid range: 0 .. nRows|nCols-1

	MCGEL_API int*               edgeGsMarkers();       // valid range: 0 .. (nCols-1)*nRows + nCols*(nRows-1) - 1
	MCGEL_API const int*         edgeGsMarkers() const; // valid range: 0 .. (nCols-1)*nRows + nCols*(nRows-1) - 1
	MCGEL_API int*               edgeGsMarkersAtDir(mcsMeshEdgeSetDirEnum eDir, int idxDir);       // valid range: 0 .. nRows|nCols-1
	MCGEL_API const int*         edgeGsMarkersAtDir(mcsMeshEdgeSetDirEnum eDir, int idxDir) const; // valid range: 0 .. nRows|nCols-1

	MCGEL_API bool*              edgeVisibilities();       // valid range: 0 .. (nCols-1)*nRows + nCols*(nRows-1) - 1
	MCGEL_API const bool*        edgeVisibilities() const; // valid range: 0 .. (nCols-1)*nRows + nCols*(nRows-1) - 1
	MCGEL_API bool*              edgeVisibilitiesAtDir(mcsMeshEdgeSetDirEnum eDir, int idxDir);       // valid range: 0 .. nRows|nCols-1
	MCGEL_API const bool*        edgeVisibilitiesAtDir(mcsMeshEdgeSetDirEnum eDir, int idxDir) const; // valid range: 0 .. nRows|nCols-1

	MCGEL_API mcsColor*          edgeColors();       // valid range: 0 .. (nCols-1)*nRows + nCols*(nRows-1) - 1
	MCGEL_API const mcsColor*    edgeColors() const; // valid range: 0 .. (nCols-1)*nRows + nCols*(nRows-1) - 1
	MCGEL_API mcsColor*          edgeColorsAtDir(mcsMeshEdgeSetDirEnum eDir, int idxDir);       // valid range: 0 .. nRows|nCols-1
	MCGEL_API const mcsColor*    edgeColorsAtDir(mcsMeshEdgeSetDirEnum eDir, int idxDir) const; // valid range: 0 .. nRows|nCols-1

	//............................................................................
	// faces addon control

	MCGEL_API mcsVector&         faceNormalAt(int iRow, int iCol);
	MCGEL_API const mcsVector&   faceNormalAt(int iRow, int iCol) const;

	MCGEL_API int&               faceGsMarkerAt(int iRow, int iCol);
	MCGEL_API const int&         faceGsMarkerAt(int iRow, int iCol) const;

	MCGEL_API bool&              faceVisibilityAt(int iRow, int iCol);
	MCGEL_API const bool&        faceVisibilityAt(int iRow, int iCol) const;

	MCGEL_API byte&              faceTransparencyAt(int iRow, int iCol); // 0 - opaque, 255 - fully transparent
	MCGEL_API const byte&        faceTransparencyAt(int iRow, int iCol) const;

	MCGEL_API mcsColor&          faceColorAt(int iRow, int iCol);
	MCGEL_API const mcsColor&    faceColorAt(int iRow, int iCol) const;

	MCGEL_API mcsVector*         faceNormals();       // valid range: 0 .. (nRows-1)*(nCols-1)
	MCGEL_API const mcsVector*   faceNormals() const; // valid range: 0 .. (nRows-1)*(nCols-1)
	MCGEL_API mcsVector*         faceNormalsAtRow(int iRow);       // valid range: 0 .. nCols-1
	MCGEL_API const mcsVector*   faceNormalsAtRow(int iRow) const; // valid range: 0 .. nCols-1

	MCGEL_API int*               faceGsMarkers();       // valid range: 0 .. (nRows-1)*(nCols-1)
	MCGEL_API const int*         faceGsMarkers() const; // valid range: 0 .. (nRows-1)*(nCols-1)
	MCGEL_API int*               faceGsMarkersAtRow(int iRow);       // valid range: 0 .. nCols-1
	MCGEL_API const int*         faceGsMarkersAtRow(int iRow) const; // valid range: 0 .. nCols-1

	MCGEL_API bool*              faceVisibilities();       // valid range: 0 .. (nRows-1)*(nCols-1)
	MCGEL_API const bool*        faceVisibilities() const; // valid range: 0 .. (nRows-1)*(nCols-1)
	MCGEL_API bool*              faceVisibilitiesAtRow(int iRow);       // valid range: 0 .. nCols-1
	MCGEL_API const bool*        faceVisibilitiesAtRow(int iRow) const; // valid range: 0 .. nCols-1

	MCGEL_API byte*              faceTransparencies();       // valid range: 0 .. (nRows-1)*(nCols-1)
	MCGEL_API const byte*        faceTransparencies() const; // valid range: 0 .. (nRows-1)*(nCols-1)
	MCGEL_API byte*              faceTransparenciesAtRow(int iRow);       // valid range: 0 .. nCols-1
	MCGEL_API const byte*        faceTransparenciesAtRow(int iRow) const; // valid range: 0 .. nCols-1

	MCGEL_API mcsColor*          faceColors();       // valid range: 0 .. (nRows-1)*(nCols-1)
	MCGEL_API const mcsColor*    faceColors() const; // valid range: 0 .. (nRows-1)*(nCols-1)
	MCGEL_API mcsColor*          faceColorsAtRow(int iRow);       // valid range: 0 .. nCols-1
	MCGEL_API const mcsColor*    faceColorsAtRow(int iRow) const; // valid range: 0 .. nCols-1

protected:

	MCGEL_API mcsMeshVertsData&  vd();
	MCGEL_API mcsVector3dArray&  vd_n();
	MCGEL_API mcsColorsArray&    vd_c();
	MCGEL_API const mcsVector3dArray&  vd_n() const;
	MCGEL_API const mcsColorsArray& vd_c() const;

	MCGEL_API mcsMeshEdgesData&  ed();
	MCGEL_API mcsLinetypesArray& ed_lt();
	MCGEL_API mcsIntArray&       ed_gs();
	MCGEL_API mcsBoolArray&      ed_v();
	MCGEL_API mcsColorsArray&    ed_c();
	MCGEL_API const mcsLinetypesArray& ed_lt() const;
	MCGEL_API const mcsIntArray&       ed_gs() const;
	MCGEL_API const mcsBoolArray&      ed_v() const;
	MCGEL_API const mcsColorsArray&    ed_c() const;

	MCGEL_API mcsMeshFacesData&  fd();
	MCGEL_API mcsVector3dArray&  fd_n();
	MCGEL_API mcsIntArray&       fd_gs();
	MCGEL_API mcsBoolArray&      fd_v();
	MCGEL_API mcsByteArray&      fd_t();
	MCGEL_API mcsColorsArray&    fd_c();
	MCGEL_API const mcsVector3dArray&  fd_n() const;
	MCGEL_API const mcsIntArray&       fd_gs() const;
	MCGEL_API const mcsBoolArray&      fd_v() const;
	MCGEL_API const mcsByteArray&      fd_t() const;
	MCGEL_API const mcsColorsArray&    fd_c() const;
};
//==================================================================================================

MCTYP_API mcsBoundBlock getBoundBlock(const mcsLinearEntity& lnEnt, bool isOrtho = false);
MCTYP_API mcsBoundBlock getBoundBlock(const mcsCircArc& carc, bool isOrtho = false);
MCTYP_API mcsBoundBlock getBoundBlock(const mcsEllipArc& earc, bool isOrtho = false);
MCTYP_API mcsBoundBlock getBoundBlock(const mcsNurbCurve& spline, bool isOrtho = false);
MCTYP_API mcsBoundBlock getBoundBlock(const mcsOffsetCurve& ofscrv, bool isOrtho = false);

//==================================================================================================

#ifndef MCGELDLL

//....................................................................................
// SAVE|LOAD to|from stream for simple geometry primitives

MCTYP_API bool savePoint2MS(IMcsStream* pStreamTo, const mcsPoint&);
MCTYP_API bool saveLineSeg2MS(IMcsStream* pStreamTo, const mcsLineSeg&);
MCTYP_API bool saveLine2MS(IMcsStream* pStreamTo, const mcsLine&);
MCTYP_API bool saveRay2MS(IMcsStream* pStreamTo, const mcsRay&);
MCTYP_API bool saveCircArc2MS(IMcsStream* pStreamTo, const mcsCircArc&);
MCTYP_API bool saveEllipArc2MS(IMcsStream* pStreamTo, const mcsEllipArc&);
MCTYP_API bool savePlane2MS(IMcsStream* pStreamTo, const mcsPlane&);
MCTYP_API bool saveSpline2MS(IMcsStream* pStreamTo, const mcsNurbCurve&);
MCTYP_API bool saveNurbSurf2MS(IMcsStream* pStreamTo, const mcsNurbSurf&);
MCTYP_API bool saveCrv2MS(IMcsStream* pStreamTo, const mcsCurve&);

MCTYP_API bool loadPointFromMS(IMcsStream* pStreamFrom, OUT mcsPoint&);
MCTYP_API bool loadLineSegFromMS(IMcsStream* pStreamFrom, OUT mcsLineSeg&);
MCTYP_API bool loadLineFromMS(IMcsStream* pStreamFrom, OUT mcsLine&);
MCTYP_API bool loadRayFromMS(IMcsStream* pStreamFrom, OUT mcsRay&);
MCTYP_API bool loadCircArcFromMS(IMcsStream* pStreamFrom, OUT mcsCircArc&);
MCTYP_API bool loadEllipArcFromMS(IMcsStream* pStreamFrom, OUT mcsEllipArc&);
MCTYP_API bool loadPlaneFromMS(IMcsStream* pStreamFrom, OUT mcsPlane&);
MCTYP_API bool loadSplineFromMS(IMcsStream* pStreamFrom, OUT mcsNurbCurve&);
MCTYP_API bool loadNurbSurfFromMS(IMcsStream* pStreamFrom, OUT mcsNurbSurf&);
MCTYP_API bool loadCrvFromMS(IMcsStream* pStreamTo, OUT mcsCurve*&);

MCTYP_API bool intersectByEnt(const mcsLinearEntity& lnEnt, const McsEntityGeometry& otherEnt, OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol);
MCTYP_API bool intersectByEnt(const mcsCircArc& sarc, const McsEntityGeometry& otherEnt, OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol);
MCTYP_API bool intersectByEnt(const mcsEllipArc& earc, const McsEntityGeometry& otherEnt, OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol);

MCTYP_API bool intersectCurveCurve(const mcsCurve& C1, const mcsCurve& C2, OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol);
MCTYP_API bool intersectByEnt(const mcsNurbCurve& spline, const McsEntityGeometry& otherEnt, OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol);
MCTYP_API bool intersectArrowByCurve(const mcsArrow& arrow, const mcsCurve& otherCrv, OUT mcsPoint3dArray& crossPoints, IN OPTIONAL const mcsTol& tol = mcsGeContext::gTol);

	// сравнивает геометрию двух кривых с заданной точностью, тип может различаться
MCTYP_API bool areEqualCurves3d(const mcsCurve&,const mcsCurve&, const mcsTol& tol = mcsGeContext::gTol, bool bAlsoCheckReversedCase = false, int nPointsToCompare = -1);

	// сравнивает геометрическое положение двух плоскостей с заданной точностью,
	// координатные системы на плоскостях могут различаться
MCTYP_API bool areEqualPlanes(const mcsPlane&,const mcsPlane&, const mcsTol& tol = mcsGeContext::gTol);

	// сравнивает геометрическое положение двух осей с заданной точностью,
	// опорная точка и шак единичного вектора могут различаться
MCTYP_API bool areEqualLines(const mcsLine&,const mcsLine&, const mcsTol& tol = mcsGeContext::gTol);

// чем больше число, тем меньше совпадение геометрии сравниваемых элементов
enum McGeomOverlapStatusEnum
{
	kMcGeomOvl_Equal                  = -5,
	kMcGeomOvl_Overlapped             = -4,
	kMcGeomOvl_OverlappedReversed     = -3,
	kMcGeomOvl_BaseOverlapped         = -2,
	kMcGeomOvl_BaseOverlappedReversed = -1,
	kMcGeomOvl_NotOverlapped          =  0,
};

	// функция проверяет факт перекрытия кривых, если таковой будет обнаружен,
	// вернёт кусок перекрывающейся кривой,
	// Если же перекрытие полностью совпадает с кривой c1, перекрытие не возвращается, только факт его наличия (для оптимизации)
	// (!) причем этот кусок будет вырезан из кривой c1

	// возврат 0 - не перекрываются
	// >0 - перекрываются и сонаправлены
	// <0 - перекрываются и направлены в разные стороны

MCTYP_API int areCurvesOverlapped(
	const mcsCurve&                       c1,
	const mcsCurve&                       c2,
	const mcsTol&                         tol,
	OUT McsEntityGeometry&                overlapGeom,
	OUT OPTIONAL McGeomOverlapStatusEnum* pOvlStatus);


	// Функция проверяет тип перекрытия поверхностей.
	// Если перекрытие полностью совпадает с поверхностью s1, перекрытие не возвращается, только факт его наличия (для оптимизации)
	// Если точного совпадения нет, то вернёт кусок перекрывающейся поверхности,
	// (!) причем этот кусок будет вырезан из поверхности s1

MCTYP_API McGeomOverlapStatusEnum getSurfacesOverlappingStatus(
	const McsEntityGeometry& s1,
	const McsEntityGeometry& s2,
	const mcsTol&            tol,
	OUT McsEntityGeometry&   overlapGeom);

//====================================================================================

#define MC_GSMARKER_PTHIGHLIGHT -3

//====================================================================================
//---------------------------------------------------------------------------
// IMcGeometryBuilder helper class for geometry constructions
//---------------------------------------------------------------------------
// Во время построения 2D геометрии нормаль и 'z' координаты игнорируются
// (кроме случая с дугами, описанного ниже)
struct IMcGeometryBuilder : public virtual IMcObject
{
public:
	IMCS_STD_METHOD_DEFINITION(IMcGeometryBuilder, IMcObject)

	virtual bool setContainer(mcsGeomEntArray* pContainer) = 0;
	virtual mcsGeomEntArray* getContainer() = 0;

	virtual bool is3D() {return false;}
	virtual void setIs3D(bool fCacheIs3D) {}

	// Если кроме этого контейнера у объекта при рисовании используется еще какой-то (как у 3D-солидов),
	// то метод позволяет указать, добавлять ли графику this-контейнера ко внешнему.
	MECHCTL_API virtual void setAddGraphicsToExtStorage(bool bAdd);
	MECHCTL_API virtual bool doAddGraphicsToExtStorage();

	virtual void setContext(IMcDbEntity* pDbEntity) = 0;

	// viewport type, for pseudo 3d objects drawing
	virtual int	 getViewType() {return VID_NONE;}
	virtual void setViewType(int iVT) {}

	virtual bool clear() = 0; //Clear container

	virtual bool setLinetype(int lt) = 0;             // Default: MCS_LINETYPE2

	// Использовать ТОЛЬКО в случае, если недостаточно варианта с числовым идентификатором типа: setLinetype(int lt)
	virtual bool setStrLinetype(LPCTSTR type) = 0;    // Default: MCS_LINETYPE2 - числовой вариант
	virtual bool setColor(COLORREF color) = 0;        // Default: MCS_ENTCOLOR_BYLINETYPE, i.e. by line type
	virtual bool setLineweght(int lw) = 0;            // Default: MCS_ENTWEIGHT_BYLINETYPE, i.e. by line type
	virtual bool setTextStyle(LPCTSTR style) = 0;     // Default: by context ("" or NULL)
	virtual bool setTextHeight(double height) = 0;    // Default: by text style (0)
	virtual bool setTextOblique(double oblique) = 0;  // Default: by text style (MCSTEXT_DEFOBLIQUE)
	virtual bool setTextXScaling(double xScaling) = 0;// Default: by text style (0)
	virtual bool setTextLineSpacing(double r) = 0;// Default: 1

	// Использовать ТОЛЬКО в случае, если геометрия объекта располагается на разных слоях
	virtual bool setLayer(LPCTSTR layer) = 0;         // Default: by object ("" or NULL)

	// Использовать ТОЛЬКО в случае, если масштаб типа линии отличается от масштаба объекта
	// в момент вставки и/или должен быть зафиксирован, а не зависеть от свойств объекта
	virtual bool setLinetypeScale(double scale) = 0;  // Default: by object scale (0)

	virtual bool setPlottable(bool bValue) = 0;

	// Масштаб примитива. Если не назначен, то используется масштаб объекта, заданного через IMcGeometryBuilder::setContext(). Задаёт mcsText::hostScale.
	virtual bool setScale(double rScale) = 0;

	virtual int       getLinetype() = 0; // Если установлено строковое значение, то вернёт 0
	virtual LPCTSTR   getStrLinetype() = 0; // Если предварительно не установлено строковой значение, то вернёт NULL
	virtual COLORREF  getColor() = 0;
	virtual int       getLineweght() = 0;
	virtual LPCTSTR   getTextStyle() = 0;
	virtual double    getTextHeight() = 0;
	virtual double    getTextOblique() = 0;
	virtual double    getTextXScaling() = 0;
	virtual double    getTextLineSpacing() = 0;
	virtual LPCTSTR   getLayer() = 0;
	virtual double    getLinetypeScale() = 0;
	virtual bool      getPlottable() = 0;
	virtual double    getScale() = 0;

	// rDirection - see IMcTextStyle::GetDTextLength()
	virtual double  getTextLength(LPCTSTR text, double rDirection = 0) = 0;   // Return DText length
	virtual void    getMTextBox(mcsBoundBlock& bound, const mcsText& text) = 0;

	virtual void    getMTextBox(
		mcsBoundBlock&        bound,
		const mcsPoint&       origin,
		const mcsVector&      direction,
		LPCTSTR               text,
		McsHorizTextAlignEnum horzAlign = kTextHorizAlign_Left,
		McsVertTextAlignEnum  vertAlign = kTextVertAlign_Bottom,
		double                width = 0) = 0;

	// Точка не выводится на печать
	virtual bool point(const mcsPoint& pnt, int iGSMarker = -1) = 0;

	// Точка выводится на печать
	virtual bool vertex(const mcsPoint& pnt, int iGSMarker = -1) = 0;
	virtual bool arc(const mcsCircArc& arc, int iGSMarker = -1) = 0;

	virtual bool arc(
		const mcsPoint&  start,
		const mcsPoint&  end,
		double           bulge,
		const mcsVector& normal = mcsVector::kZAxis, // в 2D игнорируется
		int              iGSMarker = -1) = 0;

	// При построении 2D геометрии нормаль может принимать только
	// значения (mcsVector::kZAxis) или (-mcsVector::kZAxis).
	// Направление дуги всегда против часовой стрелки
	virtual bool arc(
		const mcsPoint&  center,
		double           radius,
		double           startAng,
		double           endAng,
		const mcsVector& normal = mcsVector::kZAxis,
		int              iGSMarker = -1) = 0;

	// При построении 2D геометрии нормаль может принимать только
	// значения (mcsVector::kZAxis) или (-mcsVector::kZAxis).
	// Направление дуги всегда против часовой стрелки
	virtual bool arc(
		const mcsPoint&   center,
		double            radius,
		const mcsVector& refVector,
		double            angle,
		const mcsVector&  normal = mcsVector::kZAxis,
		int               iGSMarker = -1) = 0;

	virtual bool ellipse(
		const mcsPoint&  center,
		const mcsVector& majorAxis,
		const mcsVector& minorAxis,
		double           majorRadius,
		double           minorRadius,
		double           startAngle = 0,
		double           endAngle = PI * 2,
		int              iGSMarker = -1) = 0;

	virtual bool ellipse(const mcsEllipArc& ell, int iGSMarker = -1) = 0;

	virtual bool circle(const mcsPoint& center, double radius, const mcsVector& normal = mcsVector::kZAxis, int iGSMarker = -1) = 0;

	virtual bool line(const mcsLineSeg& line, int iGSMarker = -1) = 0;
	virtual bool line(const mcsPoint& start, const mcsPoint& end, double globalWidth = 0, int iGSMarker = -1) = 0;

	virtual bool polyline(const mcsPolyline& pline, int iGSMarker = -1) = 0;
	virtual bool polyline(const mcsPoint* points, int count, double globalWidth = 0, int iGSMarker = -1) = 0;

	virtual bool polyline(
		const mcsPoint3dArray& points,
		const mcsDoubleArray&  bulges,
		double                 globalWidth = 0,
		int                    iGSMarker = -1) = 0; // bulges must be empty or have the same length as points array

	virtual bool text(const mcsText& text, OUT mcsPolyline* pContour = NULL, int iGSMarker = -1) = 0;

	virtual bool dtext(
		const mcsPoint&       origin,
		const mcsVector&      direction,
		LPCTSTR               text,
		OUT mcsPolyline*      pContour = NULL,
		int                   iGSMarker = -1,
		McsHorizTextAlignEnum horzAlign = kTextHorizAlign_Left,
		McsVertTextAlignEnum  vertAlign = kTextVertAlign_Bottom,
		bool                  bMaskBackground = false) = 0;

	virtual bool dtext(
		const mcsPoint&       origin,
		double                angle,
		LPCTSTR               text,
		OUT mcsPolyline*      pContour = NULL,
		int                   iGSMarker = -1,
		McsHorizTextAlignEnum horzAlign = kTextHorizAlign_Left,
		McsVertTextAlignEnum  vertAlign = kTextVertAlign_Bottom,
		bool                  bMaskBackground = false) = 0;

	virtual bool mtext(
		const mcsPoint&       origin,
		const mcsVector&      direction,
		LPCTSTR               text,
		McsHorizTextAlignEnum horzAlign = kTextHorizAlign_Left,
		McsVertTextAlignEnum  vertAlign = kTextVertAlign_Bottom,
		double                width = 0,
		OUT mcsPolyline*      pContour = NULL,
		int                   iGSMarker = -1,
		bool                  bMaskBackground = false) = 0;

	virtual bool hatch(
		const mcsPolyline& contour,
		double             angle = 0,
		double             spacing = 0,
		bool               patternDouble = false,
		int                iGSMarker = -1,
		COLORREF           backgroundColor = MCS_ENTCOLOR_BYDEFAULT) = 0; // Creates user defined hatch

	virtual bool hatch(
		const mcsPolylineArray& contours,
		double                  angle = 0,
		double                  spacing = 0,
		bool                    patternDouble = false,
		int                     iGSMarker = -1,
		COLORREF                backgroundColor = MCS_ENTCOLOR_BYDEFAULT) = 0; // Creates user defined hatch

	virtual bool phatch(
		const mcsPolyline&    contour,
		LPCTSTR               patternName,
		double                angle = 0,
		double                patternScale = 1,
		mcsHatch::PatternType patternType = mcsHatch::kPreDefined,
		int                   iGSMarker = -1,
		COLORREF              backgroundColor = MCS_ENTCOLOR_BYDEFAULT,
		double                spacing = 0) = 0; // Creates predefined or user defined hatch

	virtual bool phatch(
		const mcsPolylineArray& contours,
		LPCTSTR                 patternName,
		double                  angle = 0,
		double                  patternScale = 1,
		mcsHatch::PatternType   patternType = mcsHatch::kPreDefined,
		int                     iGSMarker = -1,
		COLORREF                backgroundColor = MCS_ENTCOLOR_BYDEFAULT,
		double                  spacing = 0) = 0; // Creates predefined or user defined hatch

	virtual bool leader(
		const mcsPoint& start,
		const mcsPoint& end,
		const mcsVector& vormal,
		MCS_ARROW       type,
		double          size,
		double          width = 0,
		int             iGSMarker = -1,
		mcsCurve*       pCurve = NULL) = 0;// Line with arrow
	bool leader(
		const mcsPoint& start,
		const mcsPoint& end,
		MCS_ARROW       type,
		double          size,
		double          width = 0,
		int             iGSMarker = -1,
		mcsCurve* pCurve = NULL)
	{
		return leader(start, end, mcsVector::kZAxis, type, size, width, iGSMarker, pCurve);
	}

	virtual bool arrow(
		const mcsPoint&  start,
		const mcsVector& direction,
		const mcsVector& normal,
		MCS_ARROW        type,
		double           size,
		double           width = 0,
		int              iGSMarker = -1) = 0;
	bool arrow(
		const mcsPoint& start,
		const mcsVector& direction,
		MCS_ARROW        type,
		double           size,
		double           width = 0,
		int              iGSMarker = -1)
	{
		return arrow(start, direction, mcsVector::kZAxis, type, size, width, iGSMarker);
	}

	virtual bool sphere(const mcsPoint& center, double radius, int iGSMarker = -1) = 0;

	virtual bool cylinder(
		const mcsPoint&  base,
		const mcsVector& dir,
		double           radius,
		double           length,
		int              iGSMarker = -1) = 0;

	virtual bool cone(
		const mcsPoint&  base,
		const mcsVector& dir,
		double           startRadius,
		double           endRadius,
		double           length,
		int              iGSMarker = -1) = 0;

	virtual bool coneA(
		const mcsPoint&  base,
		const mcsVector& dir,
		double           startRadius,
		double           halfAng,
		int              iGSMarker = -1) = 0;

	virtual bool torus(const mcsCircArc& path, double pathRadius, int iGSMarker = -1) = 0;

	virtual bool triangle(
		const mcsPoint& pnt1,
		const mcsPoint& pnt2,
		const mcsPoint& pnt3,
		int             iGSMarker = -1) = 0;

	virtual bool repshape(
		const McsEntityGeometry& path,
		const mcsGeomEntArray&   shape,
		double                   rLineLength,
		double                   rSpaceLength,
		double                   rGeometryPos,
		bool                     isUniformShape = true,
		int                      iGSMarker = -1) = 0;

	virtual bool geometry(const McsEntityGeometry& geometry, int iGSMarker = -1) = 0;

	// Прорисовка 3D-изображения
	// Если изображение не детализированное, то будет использоваться указанный маркер 'iGSMarker',
	// если детализированное, то предполагается, что в одном наборе графики будет одно изображение,
	// и автоматически присваиваются маркеры по следующему правилу:
	//    int gsm = MCMOD_IDX_2_GSM(seType,  i + 1);
	// seType - это одно из значений: kMcModSubentType_Face или kMcModSubentType_Edge.
	// i - это индекс детализированной части в контейнере геометрии this-строителя
	//
	virtual bool image3d(
		const CxImage& img3d,
		COLORREF       clrFaces = MCS_ENTLTYPE_BYCONTEXT,
		COLORREF       clrEdges = MCS_ENTLTYPE_BYCONTEXT,
		int            iGSMarker = -1) = 0;
};

#endif // MCGELDLL

//==============================================================================
class FPoint;
typedef const FPoint* PCTFPNT;
typedef FPoint*       PFPNT;

class FPoint
{
public:
	REAL fx, fy;

public:

	__inline FPoint() : fx(0.0), fy(0.0) { }

	__inline FPoint(const FPoint& fp) : fx(fp.fx), fy(fp.fy) { }

	__inline FPoint(PCTFPNT pSrc) : fx(pSrc->fx), fy(pSrc->fy) { }

	__inline FPoint(REAL rX, REAL rY) : fx(rX), fy(rY) { }

	__inline FPoint(const mcsPoint& pnt) : fx(pnt.x), fy(pnt.y) { }

	__inline void set(REAL rX, REAL rY) {
		this->fx = rX;
		this->fy = rY;
	}

	__inline FPoint& operator=(const FPoint& pntSrc) {
		fx = pntSrc.fx;
		fy = pntSrc.fy;
		return *this;
	}

	__inline FPoint& operator-=(const FPoint& fp) {
		fx -= fp.fx;
		fy -= fp.fy;
		return *this;
	}

	__inline FPoint& operator+=(const FPoint& fp) {
		fx += fp.fx;
		fy += fp.fy;
		return *this;
	}

	__inline FPoint& operator-=(REAL r) {
		fx -= r;
		fy -= r;
		return *this;
	}

	__inline FPoint& operator+=(REAL r) {
		fx += r;
		fy += r;
		return *this;
	}

	__inline FPoint& operator*=(REAL r) {
		fx *= r;
		fy *= r;
		return *this;
	}

	__inline FPoint& operator/=(REAL r) {
		if (FEQ(r, 0.0)) {
			fx /= r;
			fy /= r;
		}
		return *this;
	}

	__inline bool operator == (const FPoint& fp) const {
		return !!isEqual(&fp);
	}

	__inline bool operator != (const FPoint& fp) const {
		return !isEqual(&fp);
	}

	__inline bool isValid() const {
		return fx >= GMC_REAL_MIN_COORD && fx <= GMC_REAL_MAX_COORD && fy >= GMC_REAL_MIN_COORD && fy <= GMC_REAL_MAX_COORD;
	}

	__inline bool isEqual(PCTFPNT pPnt, REAL rDelta = REAL_DEFAULT_PRECISION) const {
		return checkLength(pPnt, rDelta) <= 0.0;
	}

	__inline REAL checkLength(PCTFPNT pPnt, REAL rLength) const {
		REAL dx = fx - pPnt->fx;
		REAL dy = fy - pPnt->fy;
		return (dx * dx + dy * dy - rLength * rLength);
	}

	__inline operator PCTFPNT() const {
		return this;
	}

	__inline operator PFPNT() {
		return this;
	}

	void transformBy(const mcsMatrix &tfm);
};

//====================================================================================
inline bool Equ(const mcsPoint& pnt1, const mcsPoint& pnt2, double rPV_TOLERANCE = DEF_TOL)
{
	return Equ(pnt1.x, pnt2.x, rPV_TOLERANCE) &&
         Equ(pnt1.y, pnt2.y, rPV_TOLERANCE) &&
         Equ(pnt1.z, pnt2.z, rPV_TOLERANCE);
}
//====================================================================================
inline mcsPoint& round(mcsPoint& pntVal, int nPrecision = DEF_PRECISION) // DEF_PRECISION => DEF_TOL
{
	pntVal[X] = round(pntVal[X], nPrecision);
	pntVal[Y] = round(pntVal[Y], nPrecision);
	pntVal[Z] = round(pntVal[Z], nPrecision);
	return pntVal;
}
//====================================================================================
inline mcsVector& round(mcsVector& vecVal, int nPrecision = DEF_PRECISION) // DEF_PRECISION => DEF_TOL
{
	vecVal[X] = round(vecVal[X], nPrecision);
	vecVal[Y] = round(vecVal[Y], nPrecision);
	vecVal[Z] = round(vecVal[Z], nPrecision);
	return vecVal;
}
//====================================================================================
inline double CalcAngle(const mcsPoint& pnt1, const mcsPoint& pnt2) {
	return atan2(pnt2[Y] - pnt1[Y], pnt2[X] - pnt1[X]);
}
//====================================================================================
inline double CalcLen(const mcsPoint& pnt1, const mcsPoint& pnt2) {
	double dx = pnt2[X] - pnt1[X];
	double dy = pnt2[Y] - pnt1[Y];
	return sqrt(dx*dx + dy*dy);
}
//====================================================================================
inline void GetNextPoint(mcsPoint& pntRet, const mcsPoint& pntStart, double rAngle, double rLen)
{
	pntRet[X] = cos(rAngle)*rLen + pntStart[X];
	pntRet[Y] = sin(rAngle)*rLen + pntStart[Y];
}
//====================================================================================
inline mcsPoint GetNextPoint(const mcsPoint& pntStart, double rAngle, double rLen)
{
	mcsPoint pntRet;
	pntRet[X] = cos(rAngle)*rLen + pntStart[X];
	pntRet[Y] = sin(rAngle)*rLen + pntStart[Y];
	return pntRet;
}
//====================================================================================
inline int GetNearestPoint(const mcsPoint& pnt, const mcsPoint* pnts, int iNumPoints)
{
	double rMin = CalcLen(pnt, pnts[0]);
	int iMin = 0;
	for(int i=1; i<iNumPoints; i++) {
		double r = CalcLen(pnt, pnts[i]);
		if (r < rMin) {
			iMin = i;
			rMin = r;
		}
	}
	return iMin;
}
//====================================================================================
inline void MidPoint(mcsPoint& pntMid, const mcsPoint& pntStart, const mcsPoint& pntEnd)
  {pntMid = (pntStart + pntEnd.asVector())*0.5;}
//====================================================================================
inline mcsPoint MidPoint(const mcsPoint& pntStart, const mcsPoint& pntEnd)
  {return (pntStart + pntEnd.asVector())*0.5;}
//====================================================================================
inline void CalcLineKfs(const mcsPoint& p1, const mcsPoint& p2, REAL& rkA, REAL& rkB, REAL& rkC) {
	rkA = p2.y - p1.y;
	rkB = p1.x - p2.x;
	rkC = -(p1.y * rkB + p1.x * rkA);
}
//====================================================================================
inline bool CrossLines(mcsPoint& pntCross, const mcsPoint& p1start, const mcsPoint& p1end, const mcsPoint& p2start, const mcsPoint& p2end)
{
	REAL rkA1, rkB1, rkC1, rkA2, rkB2, rkC2;
	CalcLineKfs (p1start, p1end, rkA1, rkB1, rkC1);
	CalcLineKfs (p2start, p2end, rkA2, rkB2, rkC2);

	REAL rBottom = rkA1 * rkB2 - rkA2 * rkB1;
	if (Equ(rBottom, 0.0)) return FALSE;
	pntCross.x = (rkB1 * rkC2 - rkB2 * rkC1) / rBottom;
	pntCross.y = (rkC1 * rkA2 - rkC2 * rkA1) / rBottom;
	return true;
}
//====================================================================================
inline mcsPoint GetPointOnLine(const mcsPoint& pntStart, const mcsPoint& pntEnd, const mcsPoint& pnt)
{
	REAL a = CalcAngle(pntStart, pntEnd);
	mcsPoint pnt2 = GetNextPoint(pnt, a+PI/2.0, 1.0);
	mcsPoint pntCross;
	CrossLines(pntCross, pntStart, pntEnd, pnt, pnt2);
	return pntCross;
}
//====================================================================================
inline double CalcAngle(const mcsPoint2d& pnt1, const mcsPoint2d& pnt2) {
	return atan2(pnt2[Y] - pnt1[Y], pnt2[X] - pnt1[X]);
}
//====================================================================================
inline double CalcLen(const mcsPoint2d& pnt1, const mcsPoint2d& pnt2) {
	double dx = pnt2[X] - pnt1[X];
	double dy = pnt2[Y] - pnt1[Y];
	return sqrt(dx*dx + dy*dy);
}
//====================================================================================
inline mcsPoint2d GetNextPoint(const mcsPoint2d& pntStart, double rAngle, double rLen)
{
	mcsPoint2d pntRet;
	pntRet[X] = cos(rAngle)*rLen + pntStart[X];
	pntRet[Y] = sin(rAngle)*rLen + pntStart[Y];
	return pntRet;
}
//====================================================================================
inline mcsPoint2d MidPoint(const mcsPoint2d& pntStart, const mcsPoint2d& pntEnd)
{
	return mcsPoint2d((pntStart[X] + pntEnd[X])/2.0, (pntStart[Y] + pntEnd[Y])/2.0);
}
//====================================================================================
inline void Swap(mcsPoint2d& pnt1, mcsPoint2d& pnt2) {
	mcsPoint2d pntTmp = pnt1;
	pnt1 = pnt2;
	pnt2 = pntTmp;
}
//====================================================================================
inline void Swap(mcsPoint& pnt1, mcsPoint& pnt2)
{
	mcsPoint pntTmp = pnt1;
	pnt1 = pnt2;
	pnt2 = pntTmp;
}
//====================================================================================
// Угол хорды по длине дуги и радиусу
inline double ChordToAngle(double radius, double chordLength)
{
	return acos(1 - chordLength*chordLength/2/radius/radius);
}
//====================================================================================
// Длина хорды по длине дуги и радиусу
inline double ChordToArc(double radius, double chordLength)
{
	return radius*ChordToAngle(radius, chordLength);
}
//====================================================================================
// Длина дуги по длине хорды и радиусу
inline double ArcToChord(double radius, double chordLength)
{
	return radius*sqrt(2*(1 - cos(chordLength/radius)));
}
//====================================================================================
// Найти угол по длине дуги и радиусу
inline double ArcToAngle(double radius, double arcLength)
{
	return arcLength/radius;
}
//====================================================================================
// Найти длину дуги по радиусу и углу
inline double AngleToArc(double radius, double angle)
{
	return radius/angle;
}
//====================================================================================
//[12/6/2002]
inline mcsMatrix3d getRotation(const mcsPoint& origin, const mcsVector& newXaxis)
//Матрица поворота к.с.
//угол и направление поворота такие, что в новой к.с. ОХ совмещен с newXaxis
{
	mcsVector zOrt, yOrt;
	if (Equ(newXaxis[Z], 0)) { //поворот на плоскости
		zOrt.set(0, 0, 1);
		yOrt.set(-newXaxis[Y], newXaxis[X], 0);
	} else { //поворот в пространстве
		zOrt = (newXaxis.isParallelTo(mcsVector::kXAxis)) ?
						mcsVector::kZAxis :
						newXaxis.crossProduct(mcsVector::kXAxis);
		yOrt = newXaxis.crossProduct(zOrt);
	}
	mcsMatrix3d res;
	res.setCoordSystem(origin, newXaxis.normal(), yOrt.normal(), zOrt.normal());
	return res;
}
//====================================================================================
inline mcsPoint2d ToPoint2d(const mcsPoint& pnt) {
  return mcsPoint2d(pnt.x, pnt.y);
}
//====================================================================================
inline mcsPoint ToPoint3d(const mcsPoint2d& pnt) {
  return mcsPoint(pnt.x, pnt.y, 0.0);
}
//====================================================================================
inline void GetLineCoefs(const mcsPoint& p1, const mcsPoint& p2, double& a, double& b, double& c)
{
  a = p1.y - p2.y;
  b = p2.x - p1.x;
  c = p1.x * p2.y - p2.x * p1.y;
}
//====================================================================================
inline bool GetLineIntersect(mcsPoint &pnt, const double a1, const double b1, const double c1, const double a2, const double b2, const double c2)
{
	if(EQU(a1 * b2, b1 * a2))
		return false;
	pnt.x = (c2 * b1 - c1 * b2) / (a1 * b2 - a2 * b1);
	pnt.y = (a1 * c2 - a2 * c1) / (b1 * a2 - b2 * a1);
	pnt.z = 0;
	return true;
}
//====================================================================================
inline void GetAnglePoint(mcsPoint& pnt, const mcsPoint& pntStart, double rAngle, double rDist)
{
	pnt.x = cos(rAngle) * rDist + pntStart.x;
	pnt.y = sin(rAngle) * rDist + pntStart.y;
	pnt.z = 0;
}
//====================================================================================
inline mcsPoint GetAnglePoint(const mcsPoint& pntStart, double rAngle, double rDist)
{
  mcsPoint pnt(cos(rAngle) * rDist + pntStart.x, sin(rAngle) * rDist + pntStart.y, 0.0);
  return pnt;
}
//====================================================================================
MCTYP_API HRESULT mcsMakeArcData
(IN const mcsPoint& pt1,
 IN const mcsPoint& pt2,
 IN const mcsPoint& pt3,
 IN const double FiletRadiusAtPt2,
 OUT mcsCircArc& arc);
//====================================================================================
MCTYP_API int CheckPointDisposition(const mcsPoint& pntStart, const mcsPoint& pntEnd, const mcsPoint& pntCheck, double rTol = DEF_TOL);
//====================================================================================

	// Функция находит на многогранной сети из треугольников точку, ближайшую к данной.
MCGEL_API mcsPoint mcsGetClosestPointToTrianglesShell(
	const mcsPoint& pt,        // точка, к которой искать ближайшую
	const mcsPoint* pPts,      // точки, вершины фасетов
	int             npts,      // кол-во точек по указателю pPts
	const int*      pIndices,  // могту быть отрицатльеными у shell() из DWG, просто игнорировать знак
	int             nIndices,  // должно быть кратно 3
	bool            bFacetIndicesHasPreceedingCount // если = true, каждой тройке индексов для фасета предшествует кол-во индексов (=3)
);

	// функция определяет отклонение сетки (shell) от поверхности
MCTYP_API HRESULT mcsDetectShellTolerance(
	OUT double&      surfDev,   // результат
	const mcsPoint*  pPts,      // точки, вершины фасетов
	int              npts,      // кол-во точек по указателю pPts
	const int*       pIndices,  // могту быть отрицатльеными у shell() из DWG, просто игнорировать знак
	int              nIndices,  // должно быть кратно 3
	bool             bFacetIndicesHasPreceedingCount, // если = true, каждой тройке индексов для фасета предшествует кол-во индексов (=3)
	IN OPTIONAL const McsEntityGeometry* pSurfGeom); // геометрия аналитической поверхности, для которой построена сетка NULL

	// Отсечь часть сетки плоскостью.
	// Есдт usePositiveSide == true, от сетки будет отрезана часть,
	// которая находится на "-" стороне плоскости
MCGEL_API bool mcsCutShellDataByPlane(
	IN OUT mcsPoint3dArray&  vertices,
	IN OUT mcsVector3dArray& normals,
	IN bool                  bIndicesContainCount, // true, если индексы содержат префиксы кол-ва вершин в фасете
	IN OUT mcsIntArray&      indices,
	IN const mcsPlane&       sectionPlane,
	IN bool                  usePositiveSide);

	// Функция-хелпер для обрезки кривой по указанным параметрам
MCGEL_API bool mcsTrimCurveByParams(
	IN const mcsCurve* pCurv,
	IN double          stParam,
	IN double          endParam,
	OUT std::shared_ptr<mcsCurve>& pTrimmedCurve);

	// Возвращает ближайшую к 'pnt' точку на примитиве.
	// Если bRough = true, вернёт грубый (но быстрый) результат.
MCTYP_API bool MCSGeomGetNearestPoint(mcsPoint& pntRet, const McsEntityGeometry& ent, const mcsPoint& pnt, bool bRough = false);
MCTYP_API void MCSGeomGetNearestPointArr(mcsPoint& pntRet, const mcsGeomEntArray& ents, const mcsPoint& pnt, bool bRough = false);

	// Returns unique param corresponding point on ent (point corresponding unique param)
MCTYP_API bool MCSGeomGetPointAtParam(const McsEntityGeometry& ent, double rParam, OUT mcsPoint& pnt);
MCTYP_API bool MCSGeomGetParamAtPoint(const McsEntityGeometry& ent, OUT double& rParam, const mcsPoint& pnt);

// Матрица проекции должна быть задана для плоскости XY, т.к. после проекции Z игнорируется.
// (!) Матрица должна быть обратима.
MCTYP_API bool MCSGeomGetParamAtPoint(const McsEntityGeometry& ent, OUT double& rParam, const mcsPoint& pnt, IN OPTIONAL const mcsMatrix* pXyProjTfm);

	// Return true if ent can determine unique param for all it`s points
MCTYP_API bool MCSGeomCanConnectTo(const McsEntityGeometry& ent);

	// Constructs mcsCircArc by two points and bulge
MCTYP_API void MCSGeomMakeArc(mcsCircArc& arc, const mcsPoint& pntStart, const mcsPoint& pntEnd, double rBulge);

	// Return index of nearest to pntBase pline segment
MCTYP_API int MCSGeomGetNearestSegment(const mcsPolyline& pline, const mcsPoint& pntBase);
// Проверка равенства точек с учетом проекции.
// pXyProjTfm - матрица проекции в XY
// ptPick     - спроецированная точка (Z игнорируется), с которой выполняется сравнение
MCTYP_API bool areProjPointsEqual(
	const mcsPoint&              ptStuff,
	const mcsPoint&              ptPick,
	IN OPTIONAL const mcsMatrix* pXyProjTfm,
	double                       dtol);

//====================================================================================

//=============================================================================
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//Класс с менее широкой функциональностю чем вариант, но более удобный
#ifndef VALTYPES
#define VALTYPES
//аналогичный енум описан в src/OleServer/OleServer.idl
//называется ExValueTypes
typedef enum {MCSUNDEF = 0x0,
							MCSPNT = 0x1,
							MCSVEC = 0x2,
							MCSNUM = 0x4,
							MCSSTR = 0x10,
							MCSPLANE = 0x20,
							MCSCYLINDER = 0x40,
							MCS_VARINSTR = 0x80,
							MCS_STRCOMMAND = 0x100,
							MCS_SUBOBJECT_SWITCH = 0x200} ValTypes;
#endif

struct ParserVal
{
	mcsPoint3d         m_pnt;
	mcsVector3d        m_vec;
	double             m_num;
	ValTypes           m_ValType;
  McsString          m_str;

public:
  DECLARE_OBJ_NEWDEL;

  ParserVal(){
		m_ValType = MCSNUM;
		m_num = UNKNOWNVALUE;
	}

	ParserVal(const ParserVal &src){
		*this = src;
	}

	~ParserVal(){
	}

  void setStr(LPCTSTR str){
    m_str = str;
		m_ValType = MCSSTR;
  }

	LPCTSTR getStr() const{
		return m_str;
	}

	bool isUnknownValue(){
		if(m_ValType == MCSNUM && m_num == UNKNOWNVALUE){
			return true;
		}
		return false;
	}

  ParserVal& operator=(const ParserVal& src){
    if(this == &src) return *this;

    m_ValType = src.m_ValType;
    m_pnt = src.m_pnt;
    m_vec = src.m_vec;
    m_num = src.m_num;

    m_str = src.m_str;
    return *this;
  }

  // AGL
  bool transformBy(const mcsMatrix& tfm)
  {
    switch(m_ValType) {
      case MCSPNT: m_pnt.transformBy(tfm); return true;
      case MCSVEC: m_vec.transformBy(tfm); return true;

      case MCSPLANE:
        m_pnt.transformBy(tfm);
        m_vec.transformBy(tfm);
        return true;

      case MCSCYLINDER:
        MCSASSERTE("MCSCYLINDER: E_NOTIMPL");
        return false;

      default:
        MCSASSERTE("Can't transform non-geometric value");
        return false;
    }
    return false;
  }
};

//====================================================================================
#define PV_TOLERANCE 0.001
#define PV_NUM_TOLERANCE 0.0001

typedef enum {
	PV_ERR_ADD_WRONGTYPE = 1,
	PV_ERR_CMP1_WRONGTYPE,
	PV_ERR_CMP2_WRONGTYPE,
	PV_ERR_CMP3_WRONGTYPE,
	PV_ERR_CMP4_WRONGTYPE,
	PV_ERR_SUB_WRONGTYPE,
	PV_ERR_UNSUB_WRONGTYPE,
	PV_ERR_MUL_WRONGTYPE,
	PV_ERR_DIV_WRONGTYPE,
	PV_ERR_POW_WRONGTYPE,
	PV_ERR_DIV_BY_ZERO,
	PV_ERR_POW_ERR1,
	PV_ERR_POW_ERR2,
} pvErrorsType;

MCTYP_API void errorInParserVal(int iErrNum, int iType);
extern MCTYP_API mcsTol gPvTol;

//====================================================================================
__inline bool operator==( const ParserVal& v1, const ParserVal& v2 )
{
  if(v1.m_ValType!=v2.m_ValType) return false;

  switch(v1.m_ValType)
	{
	  case MCSPNT:
				return v1.m_pnt.isEqualTo(v2.m_pnt, gPvTol);

	  case MCSVEC:
				return v1.m_vec.isEqualTo(v2.m_vec, gPvTol);

	  case MCSNUM:
				return Equ(v1.m_num,v2.m_num,PV_NUM_TOLERANCE);

	  case MCSSTR:
			  return !lstrcmp(v1.getStr(),v2.getStr());

	  case MCSPLANE:
			  if(! (v1.m_vec.isEqualTo(v2.m_vec, gPvTol))) return false;
        return v1.m_pnt.isEqualTo(v2.m_pnt, gPvTol);
	}
	return false;
}

//====================================================================================
__inline bool operator!=( const ParserVal& v1, const ParserVal& v2 )
  {return !(v1==v2);}

#define SUB_OBJ_START TEXT("SetPrefix")

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//====================================================================================
//Класс с менее широкой функциональностю чем вариант, но более удобный
#define kMcsExv_CustomVal 0x1
struct exValue 
{
  DECLARE_OBJ_NEWDEL;

	exValue()
    {lFlag = 0;}
	exValue(LPCTSTR name, const double val){
		lFlag = 0;
		setName(name); setValue(val);
	}
	exValue(LPCTSTR name, LPCTSTR val){
		lFlag = 0;
		setName(name); setValue(val);
	}
	exValue(LPCTSTR name, const mcsPoint& val){
		lFlag = 0;
		setName(name); setValue(val);
	}
	exValue(LPCTSTR name, const mcsVector& val){
		lFlag = 0;
		setName(name); setValue(val);
	}
	exValue(LPCTSTR name, const mcsPoint& pnt, const mcsVector& vec){
		lFlag = 0;
		setName(name); setValue(pnt, vec);
	}
	exValue(LPCTSTR name, const ParserVal& v){
		lFlag = 0;
		setName(name); val = v;
	}

	exValue(const exValue& src){
		*this = src;
	}

	bool equName(const exValue& var) const{
    return strParName==var.strParName;
	}


	exValue& operator=(const exValue& src){
		if(this == &src) return *this;
		val = src.val;
		strParName = src.strParName;
		lFlag = src.lFlag;
		return *this;
	}


	void transform(const mcsMatrix3d& tfm){
		if(val.m_ValType & (MCSVEC |MCSPNT| MCSPLANE)){
			val.m_pnt.transformBy(tfm);
			val.m_vec.transformBy(tfm);
		}
	};

	void setName(LPCTSTR name){
    MCSASSERT(name);
		strParName = name;
	}
	void setValue(const double rValue){
		val.m_ValType = MCSNUM;
		val.m_num = rValue;
	}
	void setValue(const mcsPoint& pnt){
		val.m_ValType = MCSPNT;
		val.m_pnt = pnt;
	}
	void setValue(const mcsVector& vec){
		val.m_ValType = MCSVEC;
		val.m_vec = vec;
	}
	void setValue(LPCTSTR str){
		val.m_ValType = MCSSTR;
		val.setStr(str);
	}
	void setAsDouble(LPCTSTR str){
		McsString st = str; 
		val.m_ValType = MCSNUM;
		val.m_num = st.asDouble();
	}
	
	void setValue(const mcsPoint& pnt, const mcsVector& vec){
		val.m_ValType = MCSPLANE;
		val.m_vec = vec;
		val.m_pnt = pnt;
	}

  ParserVal val;
	long lFlag;
	McsString strParName;
};

__inline bool operator==(const exValue& op1, const exValue& op2){
	if(op1.equName(op2) && op1.val == op2.val && op1.lFlag == op2.lFlag) return true;
	return false;
}

__inline bool operator!=(const exValue& op1, const exValue& op2){
	return ! (op1 == op2);
}
//==================================================================================================

class mcsExValueArray : public McsArray<exValue, const exValue&>
{
protected:
	mutable McsString m_strFmtPrefix;

public:
	DECLARE_OBJ_NEWDEL;

	//------------------------------------------------------------------------------------------------

	bool findByName(OUT int& iIndex,IN LPCTSTR name) const
	{
		MCSASSERT(name);
		McsString strName = name;//ускорение поиска, сравнение McsString идет быстрее
		iIndex = -1;
		for (int i = m_nSize - 1; i >= 0; i--)
		{
			if(m_pData[i].strParName == strName)
			{
				iIndex = i;
				return true;
			}
		}
		return false;
	}
	//------------------------------------------------------------------------------------------------

	bool GetAt(IN LPCTSTR valName,OUT exValue& val) const 
	{
		if(!IsInvalidPtr(valName))
		{
			McsString strName = valName;//ускорение поиска, сравнение McsString идет быстрее
			for (int i = m_nSize - 1; i >= 0; i--)
			{
				if(m_pData[i].strParName == strName)
				{
					val = m_pData[i];
					return true;
				}
			}
		}

		val.strParName.Empty();
		val.val.m_ValType = (ValTypes)0; 
		return false;
	}
	//------------------------------------------------------------------------------------------------

	MCTYP_API const exValue& operator[](LPCTSTR name) const;
	//------------------------------------------------------------------------------------------------

	const exValue& operator[](int nIndex) const
	{
		return m_pData[nIndex]; 
	}
	//------------------------------------------------------------------------------------------------

	exValue& operator[](int nIndex)
	{
		return ElementAt(nIndex); 
	}
	//------------------------------------------------------------------------------------------------

	bool SetAt(IN LPCTSTR valName,const exValue& val)
	{
		int iIndex = -1;
		if(findByName(iIndex, valName)){
			m_pData[iIndex] = val;
			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------------------------------

	bool SetAt(IN LPCTSTR valName, const double rValue)
	{
		int iIndex = -1;
		if(findByName(iIndex, valName))
		{
			m_pData[iIndex].val.m_num = rValue;
			m_pData[iIndex].val.m_ValType = MCSNUM;
			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------------------------------

	bool setValue(IN LPCTSTR valName, const mcsPoint& pnt)
	{
		int iIndex = -1;
		if(findByName(iIndex, valName)){
			m_pData[iIndex].val.m_pnt = pnt;
			m_pData[iIndex].val.m_ValType = MCSPNT;
			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------------------------------

	bool setValue(IN LPCTSTR valName, const mcsVector& vec)
	{
		int iIndex = -1;
		if(findByName(iIndex, valName))
		{
			m_pData[iIndex].val.m_vec = vec;
			m_pData[iIndex].val.m_ValType = MCSVEC;
			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------------------------------

	bool setValue(IN LPCTSTR valName, LPCTSTR str)
	{
		int iIndex = -1;
		if(findByName(iIndex, valName))
		{
			m_pData[iIndex].val.setStr(str);
			m_pData[iIndex].val.m_ValType = MCSSTR;
			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------------------------------

	bool AddDistinctByName(const exValue& val, bool bRewrite)
	{
		int iIndex = -1;
		if(findByName(iIndex, val.strParName))
		{
			if(bRewrite)
			{
				m_pData[iIndex] = val;
				return true;
			}
			return false;
		}

		Add(val);
		return true;
	}
	//------------------------------------------------------------------------------------------------

	bool AddDistinctByName(const mcsExValueArray& arr, bool bRewrite)
	{
		int nE = arr.GetSize();
		bool bres = false;
		for(int i=0; i<nE; i++) {
			bres |= AddDistinctByName(arr[i], bRewrite);
		}

		return bres;
	}
	//------------------------------------------------------------------------------------------------

	bool MECHCTL_API setFromStr(LPCTSTR strParams);
	bool getNamesByType(OUT mcsStringArray& names, IN DWORD dwTypesMask)
	{
		names.SetSize(0,20); // speed up, and pre-clean out parameter! 
		if(dwTypesMask==0) return false;

		for (int i = m_nSize - 1; i >= 0; i--)
		{
			if(m_pData[i].val.m_ValType & dwTypesMask)
				names.Add(m_pData[i].strParName);
		}

		if(names.GetSize())
			return true;
		return false;
	}
	//------------------------------------------------------------------------------------------------

	bool extractByType(OUT mcsExValueArray& vars, IN DWORD dwTypesMask, IN OPTIONAL bool fRemoveFromThis = false)
	{
		vars.SetSize(0,20); // speed up, and pre-clean out parameter! 
		if(dwTypesMask == 0)
			return false;

		for (int i = 0; i < m_nSize; i++)
		{
			if(m_pData[i].val.m_ValType & dwTypesMask)
			{
				vars.Add(m_pData[i]);
				if(fRemoveFromThis)
					RemoveAt(i--);
			}
		}
    
		if(vars.GetSize())
			return true;
		return false;
	}
	//------------------------------------------------------------------------------------------------

	bool extractByName(OUT mcsExValueArray& vars, IN const mcsStringArray& src)
	{
		for(int i = 0; i < src.GetSize(); i++)
		{
			for (int j = m_nSize - 1; j >= 0; j--)
			{
				if(m_pData[j].strParName == src[i])
				{
					vars.Add(m_pData[j]);
					break;
				}
			}
		}

		if(vars.GetSize())
			return true;
		return false;
	}
	//------------------------------------------------------------------------------------------------

	bool extractByFlag(OUT mcsExValueArray& vars, short lExist, short lNotExist = 0)
	{
		vars.SetSize(0,20); // speed up, and pre-clean out parameter! 
		for(int j = m_nSize - 1; j >= 0; j--)
		{
			if( (lExist == 0 || (m_pData[j].lFlag & lExist)) &&
				 (lNotExist == 0 || !(m_pData[j].lFlag & lNotExist)) )
			{
				vars.Add(m_pData[j]);
			}
		}

		if(vars.GetSize())
			return true;
		return false;
	}
	//------------------------------------------------------------------------------------------------

	// diff will contain different elements from set2
	bool getDifference(OUT mcsExValueArray& diff, IN const mcsExValueArray& set2)
	{
		diff.SetSize(0,10); // speed up, and pre-clean out parameter! 

		// mask array for secondary array values, if true then val is processed
		mcsByteArray secUsageMask; 
		secUsageMask.SetSize(set2.m_nSize);
		memset(secUsageMask.GetData(), 0, secUsageMask.GetSize());

		for (int t = 0; t < m_nSize; t++) // t - idx in this
		{
			for (int s = 0; s < set2.m_nSize; s++)  // s - idx in set2
			{
				if(secUsageMask[s])
					continue;

				if(m_pData[t].equName(set2.m_pData[s]))
				{
					secUsageMask[s] = 1;
					if(m_pData[t].val != set2.m_pData[s].val)
						diff.Add(m_pData[t]);

					break;
				}
			}
		}

		if(diff.GetSize())
			return true;
		return false;
	}
	//------------------------------------------------------------------------------------------------
  
	//return difference для значений которые есть в обоих массивах
	bool compare(OUT mcsStringArray& diff, IN const mcsExValueArray& src, int *iDiffType = NULL)
	{
		diff.SetSize(0,10); // speed up, and pre-clean out parameter! 
		if(iDiffType)
			*iDiffType = 0;

		// AGL (optimization)
		// mask array for primary array values, if !0 then val is compared
		mcsByteArray priUsageMask; 
		priUsageMask.SetSize(m_nSize);
		memset(priUsageMask.GetData(), 0, priUsageMask.GetSize());

		for (int s = 0; s < src.m_nSize; s++) // s - idx in src
		{
			for (int t = 0; t < m_nSize; t++) // t - idx in this
			{
				if(priUsageMask[t])
					continue; // value already compared

				if(src.m_pData[s].equName(m_pData[t]))
				{
					priUsageMask[t] = 1; // AGL: found corresponding values
					if(src.m_pData[s].val != m_pData[t].val)
					{
						diff.Add(m_pData[t].strParName);
						if(iDiffType)
							*iDiffType |= m_pData[t].val.m_ValType;
					}
					break;
				}
			}
		}
		return true;
	}
	//------------------------------------------------------------------------------------------------

	void transformBy(const mcsMatrix3d& tfm)
	{
		for (int i = m_nSize - 1; i >= 0; i--)
			m_pData[i].transform(tfm);
	}
	//------------------------------------------------------------------------------------------------

	//Формирует строковое представление val и делает strcat в strBufResult
	void formatString(IN OUT McsString& strBufResult, IN const exValue& valToFormat) const
	{
		McsString temp;
		if(!lstrcmp(valToFormat.strParName, SUB_OBJ_START))
			m_strFmtPrefix = valToFormat.val.getStr();

		switch(valToFormat.val.m_ValType)
		{
			case MCS_VARINSTR:
				strBufResult+= valToFormat.val.getStr();
				break;

			case MCSSTR:
				temp.FormatD(TEXT("%s%s=\"%s\";"), (LPCTSTR)m_strFmtPrefix, (LPCTSTR)valToFormat.strParName, valToFormat.val.getStr());
				strBufResult+= temp;
				break;

			case MCSNUM:
				temp.FormatD(TEXT("%s=%.15g;"), (LPCTSTR)valToFormat.strParName, valToFormat.val.m_num);
				strBufResult+= temp;
				break;

			case MCSVEC:
				temp.FormatD(TEXT("%s = Vector(%.8g, %.8g, %.8g);"), (LPCTSTR)valToFormat.strParName,  valToFormat.val.m_vec[X], valToFormat.val.m_vec[Y], valToFormat.val.m_vec[Z]);
				strBufResult+= temp;
				break;

			case MCSPNT:
				temp.FormatD(TEXT("%s = Point(%.8g,%.8g,%.8g);"), (LPCTSTR)valToFormat.strParName, valToFormat.val.m_pnt[X], valToFormat.val.m_pnt[Y], valToFormat.val.m_pnt[Z]);
				strBufResult+= temp;
				break;

			case MCSPLANE:
				temp.FormatD(
					TEXT("%s = Plane(Point(%.8g,%.8g,%.8g), Vector(%.8g, %.8g, %.8g));"), 
					(LPCTSTR)valToFormat.strParName, 
					valToFormat.val.m_pnt[X], valToFormat.val.m_pnt[Y], valToFormat.val.m_pnt[Z], 
					valToFormat.val.m_vec[X], valToFormat.val.m_vec[Y], valToFormat.val.m_vec[Z]);

				strBufResult += temp;
				break;

			default:
				break;
		}
	}
	//------------------------------------------------------------------------------------------------

	McsString asString() const
	{
		m_strFmtPrefix.Empty();

		McsString str;
		for(int i = m_nSize - 1; i >= 0; i--)
			formatString(str, m_pData[i]);

		return str;
	}
	//------------------------------------------------------------------------------------------------

	MCTYP_API McsString getDbgString(LPCTSTR pfx = _T("")) const;
};

//====================================================================================
//////////////////////////////////////////////////////////////////////
//Переопределение операций +,-,*,/ для типа ParserVal
//участвующего в вычислениях
//////////////////////////////////////////////////////////////////////
__inline ParserVal operator+( const ParserVal& v1, const ParserVal& v2 )
{
	ParserVal result;
	switch(v1.m_ValType)
	{
		case MCSPNT:
				switch(v2.m_ValType)
				{
					case MCSVEC:
						result.m_pnt=v1.m_pnt+v2.m_vec;
						result.m_ValType=MCSPNT;
						break;

					default:
						result.m_pnt=v1.m_pnt;
						result.m_ValType=MCSPNT;
						errorInParserVal(PV_ERR_ADD_WRONGTYPE, MCSPNT);
						break;
				}
			break;

		case MCSPLANE:
			switch(v2.m_ValType)
			{
				case MCSVEC:
					result.m_pnt=v1.m_pnt+v2.m_vec;
					result.m_vec = v1.m_vec;
					result.m_ValType=MCSPLANE;
					break;

				case MCSNUM:
					result.m_pnt = v1.m_pnt + v1.m_vec*v2.m_num;
					result.m_vec = v1.m_vec;
					result.m_ValType=MCSPLANE;
					break;

				default:
					result.m_pnt=v1.m_pnt;
					result.m_vec = v1.m_vec;
					result.m_ValType=MCSPLANE;
					errorInParserVal(PV_ERR_ADD_WRONGTYPE, MCSPLANE);
					break;
			}
			break;

		case MCSVEC:
				switch(v2.m_ValType)
				{
					case MCSPNT:
						result.m_pnt=v2.m_pnt+v1.m_vec;
						result.m_ValType=MCSPNT;
						break;

					case MCSVEC:
						result.m_vec=v1.m_vec+v2.m_vec;
						result.m_ValType=MCSVEC;
						break;

					default:
						result.m_vec=v1.m_vec;
						result.m_ValType=MCSVEC;
						errorInParserVal(PV_ERR_ADD_WRONGTYPE, MCSVEC);
						break;
				}
			break;

		case MCSNUM:
				switch(v2.m_ValType)
				{
					case MCSNUM:
						result.m_num=v1.m_num+v2.m_num;
						result.m_ValType=MCSNUM;
						break;

					default:
						result.m_num=v1.m_num;
						result.m_ValType=MCSNUM;
						errorInParserVal(PV_ERR_ADD_WRONGTYPE, MCSNUM);
						break;
				}
			break;

		case MCSSTR:
			switch(v2.m_ValType)
			{
				case MCSSTR:
					result.setStr(McsString(v1.getStr()) + McsString(v2.getStr()));
					result.m_ValType=MCSSTR;
					break;

				case MCSNUM:{
						McsString str; str.Format(TEXT("%s%.15g"), v1.getStr(), round(v2.m_num, 3));
						result.setStr(str);
						result.m_ValType=MCSSTR;
					}
					break;

				default:
					errorInParserVal(PV_ERR_ADD_WRONGTYPE, MCSSTR);
					break;
			}
			break;

		default:
			result.m_num=UNKNOWNVALUE;
			result.m_ValType=MCSNUM;
			break;
	}
	return result;
};

//====================================================================================
__inline bool operator>=( const ParserVal& v1, const ParserVal& v2 )
{
	switch(v1.m_ValType)
	{
		case MCSPNT:
			errorInParserVal(PV_ERR_CMP1_WRONGTYPE, MCSPNT);
			return false;
			break;

		case MCSPLANE:
			errorInParserVal(PV_ERR_CMP1_WRONGTYPE, MCSPLANE);
			return false;
			break;

		case MCSVEC:
				switch(v2.m_ValType)
				{
					case MCSVEC:
						if(v1.m_vec.length() >= v2.m_vec.length() || Equ(v1.m_vec.length(), v2.m_vec.length(), PV_NUM_TOLERANCE)) return true;
						else return false;

					default:
						errorInParserVal(PV_ERR_CMP1_WRONGTYPE, MCSVEC);
						return 0;
				}
			break;

		case MCSNUM:
				switch(v2.m_ValType)
				{
					case MCSNUM:
						if((v1.m_num >= v2.m_num) || Equ(v1.m_num, v2.m_num, PV_NUM_TOLERANCE)) return true;
						else return false;

					default:
						errorInParserVal(PV_ERR_CMP1_WRONGTYPE, MCSNUM);
						return false;
				}
			break;

		case MCSSTR:
			errorInParserVal(PV_ERR_CMP1_WRONGTYPE, MCSSTR);
			return false;
			break;
	}
	return false;
};

//====================================================================================
__inline bool operator<=( const ParserVal& v1, const ParserVal& v2 )
{
	switch(v1.m_ValType)
	{
		case MCSPNT:
			errorInParserVal(PV_ERR_CMP2_WRONGTYPE, MCSPNT);
			return false;
			break;

		case MCSPLANE:
			errorInParserVal(PV_ERR_CMP2_WRONGTYPE, MCSPLANE);
			return false;
			break;

		case MCSVEC:
				switch(v2.m_ValType)
				{
					case MCSVEC:
						if(v1.m_vec.length() <= v2.m_vec.length() || Equ(v1.m_vec.length(), v2.m_vec.length(), PV_TOLERANCE)) return true;
						else return false;

					default: errorInParserVal(PV_ERR_CMP2_WRONGTYPE, MCSVEC); return false;
				}
			break;

		case MCSNUM:
				switch(v2.m_ValType)
				{
					case MCSNUM:
						if((v1.m_num <= v2.m_num) || Equ(v1.m_num, v2.m_num,PV_NUM_TOLERANCE)) return true;
						else return false;

					default: errorInParserVal(PV_ERR_CMP2_WRONGTYPE, MCSNUM);	return false;
				}
			break;
		case MCSSTR: errorInParserVal(PV_ERR_CMP2_WRONGTYPE, MCSSTR);	break;
	}

	return false;
};

//====================================================================================
__inline bool  operator>( const ParserVal& v1, const ParserVal& v2 )
{
	switch(v1.m_ValType)
	{
		case MCSPNT:	errorInParserVal(PV_ERR_CMP3_WRONGTYPE, MCSPNT);		return false;
			break;

		case MCSPLANE:	errorInParserVal(PV_ERR_CMP3_WRONGTYPE, MCSPLANE);		return false;
			break;

		case MCSVEC:
				switch(v2.m_ValType)
				{
					case MCSVEC:
						if(v1.m_vec.length() > v2.m_vec.length()) return true;
						else return false;

					default:
						errorInParserVal(PV_ERR_CMP3_WRONGTYPE, MCSVEC);		return false;
				}
			break;

		case MCSNUM:
				switch(v2.m_ValType)
				{
					case MCSNUM:
						if(v1.m_num > v2.m_num) return true;
						else return false;

					default:
						errorInParserVal(PV_ERR_CMP3_WRONGTYPE, MCSNUM);		return false;
				}
			break;

		case MCSSTR:
			errorInParserVal(PV_ERR_CMP3_WRONGTYPE, MCSSTR);		return false;
			break;
	}
	return false;
};

//====================================================================================
__inline bool operator<( const ParserVal& v1, const ParserVal& v2 )
{
	switch(v1.m_ValType)
	{
		case MCSPNT:	errorInParserVal(PV_ERR_CMP4_WRONGTYPE, MCSPNT);		return false;
			break;

		case MCSPLANE:	errorInParserVal(PV_ERR_CMP4_WRONGTYPE, MCSPLANE);		return false;
			break;

		case MCSVEC:
				switch(v2.m_ValType)
				{
					case MCSVEC:
						if(v1.m_vec.length() < v2.m_vec.length()) return true;
						else return false;
					default:
						errorInParserVal(PV_ERR_CMP4_WRONGTYPE, MCSVEC);		return false;
				}
			break;

		case MCSNUM:
				switch(v2.m_ValType)
				{
					case MCSNUM:
						if(v1.m_num < v2.m_num) return true;
						else return false;

					default:
						errorInParserVal(PV_ERR_CMP4_WRONGTYPE, MCSNUM);		return false;
				}
			break;

		case MCSSTR:
			errorInParserVal(PV_ERR_CMP4_WRONGTYPE, MCSSTR);		return false;
			break;
	}
	return false;
};

//====================================================================================
__inline ParserVal operator-(const ParserVal& v1, const ParserVal& v2)
{
	ParserVal result;
	switch(v1.m_ValType)
	{
		case MCSPNT:
				switch(v2.m_ValType)
				{
					case MCSPNT:
						result.m_vec=v1.m_pnt-v2.m_pnt;
						result.m_ValType=MCSVEC;
						break;

					case MCSVEC:
						result.m_pnt=v1.m_pnt-v2.m_vec;
						result.m_ValType=MCSPNT;
						break;

					case MCSPLANE:{
							mcsPlane plane(v2.m_pnt, v2.m_vec);
							result.m_num = -plane.signedDistanceTo(v1.m_pnt);
							result.m_ValType=MCSNUM;
						}
						break;

					default:
						errorInParserVal(PV_ERR_SUB_WRONGTYPE, MCSPNT);
						result.m_pnt=v1.m_pnt;
						result.m_ValType=MCSPNT;
						break;
				}
			break;

		case MCSPLANE:
			switch(v2.m_ValType)
			{
				case MCSPNT:{
						mcsPlane plane(v1.m_pnt, v1.m_vec);
						result.m_num = plane.signedDistanceTo(v2.m_pnt);
						result.m_ValType=MCSNUM;
					}
					break;

				case MCSVEC:
					result.m_pnt=v1.m_pnt-v2.m_vec;
					result.m_vec=v1.m_vec;
					result.m_ValType=MCSPLANE;
					break;

				case MCSNUM:
					result.m_pnt=v1.m_pnt-v1.m_vec*v2.m_num;
					result.m_vec=v1.m_vec;
					result.m_ValType=MCSPLANE;
					break;

				case MCSPLANE:{
						mcsPlane plane(v1.m_pnt, v1.m_vec);
						result.m_num = plane.signedDistanceTo(v2.m_pnt);
						result.m_ValType=MCSNUM;
					}
					break;

				default:
					errorInParserVal(PV_ERR_SUB_WRONGTYPE, MCSPLANE);
					result = v1;
					result.m_ValType = MCSPLANE;
					break;
			}
			break;

		case MCSVEC:
				switch(v2.m_ValType)
				{
					case MCSPNT:
						result.m_pnt=v2.m_pnt-v1.m_vec;
						result.m_ValType=MCSPNT;
						break;

					case MCSVEC:
						result.m_vec=v1.m_vec-v2.m_vec;
						result.m_ValType=MCSVEC;
						break;

					default:
						errorInParserVal(PV_ERR_SUB_WRONGTYPE, MCSVEC);
						result.m_vec=v1.m_vec;
						result.m_ValType=MCSVEC;
						break;
				}
				break;

		case MCSNUM:
				switch(v2.m_ValType)
				{
					case MCSNUM:
						result.m_num=v1.m_num-v2.m_num;
						result.m_ValType=MCSNUM;
						break;

					default:
						errorInParserVal(PV_ERR_SUB_WRONGTYPE, MCSNUM);
						result.m_num=v1.m_num;
						result.m_ValType=MCSNUM;
						break;
				}
				break;
	}
	return result;
};

//====================================================================================
__inline ParserVal operator-(const ParserVal& v1)
{
	ParserVal result;
	switch(v1.m_ValType)
	{
		case MCSVEC:
			result.m_vec=-v1.m_vec;
			result.m_ValType=MCSVEC;
			break;

		case MCSPLANE:
			result.m_vec = -v1.m_vec;
			result.m_pnt = v1.m_pnt;
			result.m_ValType=MCSPLANE;
			break;

		case MCSNUM:
			result.m_num=-v1.m_num;
			result.m_ValType=MCSNUM;
			break;

		case MCSPNT:
			result = v1;
			break;

		default:
			errorInParserVal(PV_ERR_UNSUB_WRONGTYPE, MCSVEC);
			result.m_pnt=v1.m_pnt;
			result.m_ValType=MCSPNT;
			break;
	}
	return result;
};

//====================================================================================
__inline ParserVal operator*(const ParserVal& v1, const ParserVal& v2)
{
	ParserVal result;
	switch(v1.m_ValType)
	{
		case MCSVEC:
			switch(v2.m_ValType)
			{
				case MCSNUM:
					result.m_vec=v1.m_vec*v2.m_num;
					result.m_ValType=MCSVEC;
					break;

				case MCSVEC:
					result.m_vec[X]=v1.m_vec[X]*v2.m_vec[X];
					result.m_vec[Y]=v1.m_vec[Y]*v2.m_vec[Y];
					result.m_vec[Z]=v1.m_vec[Z]*v2.m_vec[Z];
					result.m_ValType=MCSVEC;
					break;

				default:
					errorInParserVal(PV_ERR_MUL_WRONGTYPE, MCSVEC);
					result.m_vec=v1.m_vec;
					result.m_ValType=MCSVEC;
					break;
			}
		break;

	case MCSNUM:
			switch(v2.m_ValType)
			{
				case MCSNUM:
					result.m_num=v1.m_num*v2.m_num;
					result.m_ValType=MCSNUM;
					break;

				case MCSVEC:
					result.m_vec=v2.m_vec*v1.m_num;
					result.m_ValType=MCSVEC;
					break;

				default:
					errorInParserVal(PV_ERR_MUL_WRONGTYPE, MCSNUM);
					result.m_num=v1.m_num;
					result.m_ValType=MCSNUM;
					break;
			}
		break;

	default:
		errorInParserVal(PV_ERR_MUL_WRONGTYPE, 10000);
		result.m_num = UNKNOWNVALUE;
		result.m_ValType=MCSNUM;
		break;
	}
	return result;
};

//====================================================================================
__inline ParserVal operator/(const ParserVal& v1, ParserVal& v2)
{
	ParserVal result;
	switch(v1.m_ValType)
	{
		case MCSVEC:
				switch(v2.m_ValType)
				{
				case MCSNUM:
					if(v2.m_num == 0){
						errorInParserVal(PV_ERR_DIV_BY_ZERO, MCSVEC);
						v2.m_num = 1;
					}
					result.m_vec=v1.m_vec/v2.m_num;				
					result.m_ValType=MCSVEC;
					break;

				default:
					errorInParserVal(PV_ERR_DIV_WRONGTYPE, MCSVEC);
					result.m_vec=v1.m_vec;
					result.m_ValType=MCSVEC;
					break;
				}
			break;

		case MCSNUM:
				switch(v2.m_ValType)
				{
				case MCSNUM:
					if(v2.m_num == 0){
						errorInParserVal(PV_ERR_DIV_BY_ZERO, MCSNUM);
						v2.m_num = 1;
					}
					result.m_num=v1.m_num/v2.m_num;
					result.m_ValType=MCSNUM;
					break;

				default:
					errorInParserVal(PV_ERR_DIV_WRONGTYPE, MCSNUM);
					result.m_num=v1.m_num;
					result.m_ValType=MCSNUM;
					break;
				}
			break;

		default:
			errorInParserVal(PV_ERR_DIV_WRONGTYPE, 100000);
			result = v1;
			break;
	}
	return result;
};

//====================================================================================
__inline ParserVal operator^(const ParserVal& v1, const ParserVal& v2)
{
	ParserVal result;
	switch(v1.m_ValType)
	{
		case MCSNUM:
				switch(v2.m_ValType)
				{
					case MCSNUM:
						if((v1.m_num == 0 && v2.m_num < 0)){
							errorInParserVal(PV_ERR_POW_ERR1, 100000);
							result.m_num = 1;
						} else if(v1.m_num < 0 && v2.m_num < 1 && (((int)v2.m_num) % 2 == 0)){
							errorInParserVal(PV_ERR_POW_ERR2, 100000);
							result.m_num=pow(fabs(v1.m_num),v2.m_num);
						} else {
							result.m_num=pow(v1.m_num,v2.m_num);
						}
						result.m_ValType=MCSNUM;
						break;

					default:
						errorInParserVal(PV_ERR_POW_WRONGTYPE, MCSNUM);
						result.m_num=v1.m_num;
						result.m_ValType=MCSNUM;
						break;
				}
			break;

		default:
			errorInParserVal(PV_ERR_POW_WRONGTYPE, 100000);
			result.m_num=1;
			result.m_ValType=MCSNUM;
			break;
	}
	return result;
};
//====================================================================================

#if !defined(_NCAD_BUILD_) && !defined(_MCS_CORE_ONLY)
	#include "McsGeometryInternal.h"
#endif

//=============================================================================

