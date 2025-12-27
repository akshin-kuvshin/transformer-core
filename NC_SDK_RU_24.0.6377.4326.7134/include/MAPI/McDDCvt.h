#pragma once

#include "DbArc.h"
#include "DbLine.h"
#include "DbPoint.h"
#include "DbCircle.h"
#include "DbEllipse.h"
#include "DbRay.h"
#include "DbXline.h"
#include "DbSubDMesh.h"
#include "DbPolyFaceMesh.h"
#include "DbPolygonMesh.h"
#include "DbFace.h"
#include "dbhelix.h"

#include "Ge\GeCurve2d.h"
#include "Ge\GeLineSeg2d.h"
#include "Ge\GeLineSeg3d.h"
#include "Ge\GeRay3d.h"
#include "Ge\GeCircArc2d.h"
#include "Ge\GeCircArc3d.h"
#include "Ge\GeEllipArc2d.h"
#include "Ge\GeEllipArc3d.h"
#include "Ge\GeNurbCurve2d.h"
#include "Ge\GeNurbCurve3d.h"
#include "Ge\GeCompositeCurve3d.h"
#include "Ge\GeKnotVector.h"
#include "Ge\GeCylinder.h"
#include "Ge\GeCone.h"
#include "Ge\GeSphere.h"
#include "Ge\GeTorus.h"

class OdDbPolyline;
class OdDb2dPolyline;
class OdDb3dPolyline;

class OdGePlane;
class OdGeCone;
class OdGeSphere;
class OdGeCylinder;
class OdGeTorus;
class OdGeNurbSurface;
class OdGeSurface;

class McGePoint3d;
class McGeVector3d;
class McGePlane;
class McGeLineSeg3d;
class McGeLine3d;
class McGeRay3d;
class McGeCircArc3d;
class McGeEllipArc3d;
class McGeNurbCurve3d;
class McGeCompositeCurve3d;
class McGeCurve3d;

struct mcsPlCurves;

#ifdef _DEBUG
class OdDbSafeObjectId;
#else
typedef OdDbObjectId OdDbSafeObjectId;
#endif

// AGL, copy-paste of ISNOVALID_RADIUSRATIO that is taken from:
// TD\Source\database\Entities\DbEllipse.cpp
// Teigha uses this macro for culling degenerated ellipses

#ifndef TD_ISNOVALID_RADIUSRATIO
	#define TD_ISNOVALID_RADIUSRATIO(ratio) ( ratio > 1.0000000001 || ratio < 1.0e-6 )
#endif

// ================================================ 3D related
// #include "ge\GeCone.h"
// #include "ge\GeCylinder.h"
// #include "ge\GeTorus.h"
// #include "Ge\GeCurveCurveInt3d.h"
// #include "Ge\GePosition3d.h"
// #include "ge\GeExternalBoundedSurface.h"
// #include "Ge\GeExternalCurve3d.h"
// #include "Ge\GeExternalSurface.h"
// ================================================ end 3D related

#ifndef MCCVT_API
	#ifdef MCCVT_DLL
		#define MCCVT_API __declspec(dllexport) 
	#else
		#define MCCVT_API __declspec(dllimport) 
		#ifdef LMPROJECT
			#pragma comment(lib, "PTCvt.lib")
		#else
			#pragma comment(lib, "mcDDCvt.lib")
		#endif
	#endif
#endif

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// McCvt
//---------------------------------------------------------------------------
namespace McCvt
{
	extern MCCVT_API mcsTol splfyTol;

	using namespace std;

	MCCVT_API HRESULT ConvertPlane(const OdGePlane*, mcsPlane& plane);
	MCCVT_API HRESULT ConvertPlane(const mcsPlane& plane, OUT OdGePlane&);
	MCCVT_API HRESULT ConvertCone(const OdGeCone*, mcsCone& cone, int iInnerFace = 0);
	MCCVT_API HRESULT ConvertCone(const mcsCone& cone, OUT OdGeCone&);
	MCCVT_API HRESULT ConvertCylinger(const OdGeCylinder*, mcsCylinder& cyl);
	MCCVT_API HRESULT ConvertCylinger(const mcsCylinder& cyl, OUT OdGeCylinder&);
	MCCVT_API HRESULT ConvertSphere(const OdGeSphere*, mcsSphere& sphere, int iInnerFace = 0);
	MCCVT_API HRESULT ConvertSphere(const mcsSphere& sphere, OUT OdGeSphere&);
	MCCVT_API HRESULT ConvertTorus(const OdGeTorus*, mcsTorus& tor, int iInnerFace = 0);
	MCCVT_API HRESULT ConvertTorus(const mcsTorus& tor, OUT OdGeTorus&);
	MCCVT_API HRESULT ConvertNurbSurf(const OdGeNurbSurface*, mcsNurbSurf& ns);
	MCCVT_API HRESULT ConvertNurbSurf(IN const mcsNurbSurf& nurbSurf, OUT OdGeNurbSurface& pOdGeSurfGeom);

	MC_NANO_GATE_API HRESULT ConvertGeSurface(IN const OdGeSurface* pSurf, OUT McsEntityGeometry& geometry, int iInnerFace = 0);
	MC_NANO_GATE_API HRESULT ConvertGeSurface(IN const McsEntityGeometry& mcSurfGeom, OUT OdGeSurfacePtr& pOdGeSurfGeom);

	MCCVT_API HRESULT ConvertMesh(IN const mcsMesh& mesh, OUT OdDbSubDMesh* pMesh);
	MCCVT_API HRESULT ConvertMesh(IN const OdDbSubDMesh* pDbMesh, OUT mcsMesh& mesh);

	MCCVT_API HRESULT ConvertMesh(IN const OdDbPolyFaceMesh* pDbMesh, OUT mcsMesh& mesh);
	MCCVT_API HRESULT ConvertMesh(IN const OdDbPolygonMesh* pDbMesh, OUT mcsMesh& mesh);
	MCCVT_API HRESULT ConvertMesh(IN const OdDbFace* pFace, OUT mcsMesh& mesh);

	MCCVT_API HRESULT ConvertLine3d(IN const OdGeLine3d& inCurve, OUT mcsLine3d& outCurve);
	MCCVT_API HRESULT ConvertLine3d(IN const mcsLine3d& inCurve, OUT OdGeLine3d& outCurve);
	MCCVT_API HRESULT ConvertRay(IN const OdGeRay3d& inCurve, OUT mcsRay& outCurve);
	MCCVT_API HRESULT ConvertRay(IN const mcsRay& inCurve, OUT OdGeRay3d& outCurve);
	MCCVT_API HRESULT ConvertNurbCurve(const mcsSpline&, OUT OdGeNurbCurve3d& odNurb);
	MCCVT_API HRESULT ConvertNurbCurve2d(const mcsSpline& tNurb, OUT OdGeNurbCurve2d& odNurb);
	MCCVT_API HRESULT ConvertPtsArr(const OdGePoint3dArray& odArr, OUT mcsGePoints3dArr& tArr);
	MCCVT_API HRESULT ConvertPtsArr(const mcsGePoints3dArr& tArr, OUT OdGePoint3dArray& odArr);
	MCCVT_API HRESULT ConvertVecsArr(const OdGeVector3dArray& odArr, OUT mcsGeVectors3dArr& tArr);
	MCCVT_API HRESULT ConvertVecsArr(const mcsGeVectors3dArr& tArr, OUT OdGeVector3dArray& odArr);
	MCCVT_API HRESULT ConvertDblArr(const OdGeDoubleArray& odArr, OUT mcsGeDoubleArr& tArr);
	MCCVT_API HRESULT ConvertDblArr(const mcsGeDoubleArr& tArr, OUT OdGeDoubleArray& odArr);
	MCCVT_API HRESULT ConvertKnotVector(const OdGeKnotVector& odKV, OUT mcsKnotVector& tKV);
	MCCVT_API HRESULT ConvertKnotVector(const mcsKnotVector& tKV, OUT OdGeKnotVector& odKV);
	MCCVT_API HRESULT ConvertCurve(IN const OdGeCurve3d* pCurve, OUT mcsCurve*& pMcsCurve, bool fTrySimplifyNurb = true, const mcsTol& splineSimplificationTol = splfyTol);
	MCCVT_API HRESULT ConvertCurve(IN const mcsCurve* pMcsCurve, OUT OdGeCurve3d*& pCurve);
	MCCVT_API HRESULT ConvertLineSeg(IN const OdGeLineSeg3d& inCurve, OUT mcsLineSeg& outCurve);
	MCCVT_API HRESULT ConvertLineSeg(IN const mcsLineSeg& inCurve, OUT OdGeLineSeg3d& outCurve);
	MCCVT_API HRESULT ConvertCircArc(IN const OdGeCircArc3d& inCurve, OUT mcsCircArc& outCurve);
	MCCVT_API HRESULT ConvertCircArc(IN const mcsCircArc& inCurve, OUT OdGeCircArc3d& outCurve);
	MCCVT_API HRESULT ConvertEllipArc(IN const OdGeEllipArc3d& inCurve, OUT mcsEllipArc& outCurve);
	MCCVT_API HRESULT ConvertEllipArc(IN const mcsEllipArc& inCurve, OUT OdGeEllipArc3d& outCurve);
	MCCVT_API HRESULT ConvertNurbs(IN const OdGeNurbCurve3d& inCurve, OUT mcsCurve*& pOutCurve, bool fTrySimplify = false, const mcsTol& splineSimplificationTol = splfyTol);
	MCCVT_API HRESULT ConvertNurbs(IN const mcsSpline& inCurve, OUT OdGeNurbCurve3d*& pOutCurve);
	MCCVT_API HRESULT ConvertCompositeCurve(IN const OdGeCompositeCurve3d& odgeCurve, OUT mcsCompositeCurve3d& mcgeCurve);
	MCCVT_API HRESULT ConvertCompositeCurve(IN const mcsCompositeCurve3d& mcgeCurve, OUT OdGeCompositeCurve3d& odgeCurve);
	MC_NANO_GATE_API HRESULT ConvertCompositeCurve(IN const OdGeCompositeCurve3d& odgeCurve, OUT mcsPolyline& mcPolyine);

	// McGe/OdGe -> OdDb .............................................................................

	MCCVT_API HRESULT ConvertLineSeg(IN const McGeLineSeg3d& aLineIn, OUT OdDbLine* pLineOut);
	MCCVT_API HRESULT ConvertLineSeg(IN const OdGeLineSeg3d& aLineIn, OUT OdDbLine* pLineOut);
	MCCVT_API HRESULT ConvertPoint(IN const McGePoint3d& aPointIn, OUT OdDbPoint* pPointOut, IN OPTIONAL OdDbDatabase* pDb = NULL);
	MCCVT_API HRESULT ConvertPoint(IN const OdGePoint3d& aPointIn, OUT OdDbPoint* pPointOut, IN OPTIONAL OdDbDatabase* pDb = NULL);
	MCCVT_API HRESULT ConvertArc(IN const McGeCircArc3d& arc, OUT OdDbArc* pArc);
	MCCVT_API HRESULT ConvertArc(IN const OdGeCircArc3d& arc, OUT OdDbArc* pArc);
	MCCVT_API HRESULT ConvertCircArc(IN const McGeCircArc3d& aArcIn, OUT OdDbCircle* pArcOut);
	MCCVT_API HRESULT ConvertCircArc(IN const OdGeCircArc3d& aArcIn, OUT OdDbCircle* pArcOut);
	MCCVT_API HRESULT ConvertEllipArc(IN const McGeEllipArc3d& aArcIn, OUT OdDbEllipse* pArcOut);
	MCCVT_API HRESULT ConvertEllipArc(IN const OdGeEllipArc3d& aArcIn, OUT OdDbEllipse* pArcOut);
	MCCVT_API HRESULT ConvertRay(IN const McGeRay3d& aRayIn, OUT OdDbRay* pRayOut);
	MCCVT_API HRESULT ConvertRay(IN const OdGeRay3d& aRayIn, OUT OdDbRay* pRayOut);
	MCCVT_API HRESULT ConvertXLine(IN const McGeLine3d& aXLineIn, OUT OdDbXline* pXLineOut);
	MCCVT_API HRESULT ConvertXLine(IN const OdGeLine3d& aXLineIn, OUT OdDbXline* pXLineOut);
	MCCVT_API HRESULT ConvertSpline(IN const McGeNurbCurve3d& spline, OUT OdDbSpline* pS);
	MCCVT_API HRESULT ConvertSpline(IN const OdGeNurbCurve3d& spline, OUT OdDbSpline* pS);

	// NOTE: polylines aren't converted
	MCCVT_API HRESULT ConvertCurve(IN const McGeCurve3d& geCurveIn, OUT OdDbCurvePtr& pDbCurveOut);
	MCCVT_API HRESULT ConvertCurve(IN const OdGeCurve3d& geCurveIn, OUT OdDbCurvePtr& pDbCurveOut);

	// supports mcsPolyline -> OdDbPolyline conversion
	MC_NANO_GATE_API HRESULT ConvertCurveEx(IN const McGeCurve3d& geCurveIn, OUT OdDbCurvePtr& pDbCurveOut);

	MC_NANO_GATE_API HRESULT ConvertGeom(
		OdDbEntityPtr*           ppEnt,
		const McsEntityGeometry& ent,
		MCS_STANDARD             std,
		const OdDbEntity*        pContext = NULL,
		OdDbDatabase*            pDb = NULL,
		IMcGeometry*             pMcContext = NULL);

	// OdDb -> McGe/OdGe .............................................................................

	MCCVT_API HRESULT ConvertLineSeg(IN const OdDbLine* pLineIn, OUT McGeLineSeg3d& aLineOut);
	MCCVT_API HRESULT ConvertLineSeg(IN const OdDbLine* pLineIn, OUT OdGeLineSeg3d& aLineOut);
	MCCVT_API HRESULT ConvertArc(IN const OdDbArc* pArcIn, OUT McGeCircArc3d& aArcOut);
	MCCVT_API HRESULT ConvertArc(IN const OdDbArc* pArcIn, OUT OdGeCircArc3d& aArcOut);
	MCCVT_API HRESULT ConvertCircArc(IN const OdDbCircle* pArcIn, OUT McGeCircArc3d& aArcOut);
	MCCVT_API HRESULT ConvertCircArc(IN const OdDbCircle* pArcIn, OUT OdGeCircArc3d& aArcOut);
	MCCVT_API HRESULT ConvertEllipArc(IN const OdDbEllipse* pArcIn, OUT McGeEllipArc3d& aArcOut);
	MCCVT_API HRESULT ConvertEllipArc(IN const OdDbEllipse* pArcIn, OUT OdGeEllipArc3d& aArcOut);
	MCCVT_API HRESULT ConvertPoint(IN const OdDbPoint* pPointIn, OUT McGePoint3d& aPointOut);
	MCCVT_API HRESULT ConvertPoint(IN const OdDbPoint* pPointIn, OUT OdGePoint3d& aPointOut);
	MCCVT_API HRESULT ConvertRay(IN const OdDbRay* pRayIn, OUT McGeRay3d& aRayOut);
	MCCVT_API HRESULT ConvertRay(IN const OdDbRay* pRayIn, OUT OdGeRay3d& aRayOut);
	MCCVT_API HRESULT ConvertXLine(IN const OdDbXline* pXLineIn, OUT McGeLine3d& aXLineOut);
	MCCVT_API HRESULT ConvertXLine(IN const OdDbXline* pXLineIn, OUT OdGeLine3d& aXLineOut);
	MCCVT_API HRESULT ConvertSpline(IN const OdDbSpline* pS, OUT McGeNurbCurve3d& aSpline);
	MCCVT_API HRESULT ConvertSpline(IN const OdDbSpline* pS, OUT OdGeNurbCurve3d& aSpline);

	// NOTE: polylines aren't converted
	MCCVT_API HRESULT ConvertCurve(IN const OdDbCurve& dbCurveIn, OUT OdSharedPtr<McGeCurve3d>& pGeCurveOut);
	MCCVT_API HRESULT ConvertCurve(IN const OdDbCurve& dbCurveIn, OUT OdGeCurve3dPtr& pGeCurveOut);

	// supports OdDbPolyline/OdDb2dPolyline/OdDb3dPolyline -> mcsPolyline conversion
	MC_NANO_GATE_API HRESULT ConvertCurveEx(IN const OdDbCurve& dbCurveIn, OUT OdSharedPtr<McGeCurve3d>& pGeCurveOut);

	// supports OdDbPolyline/OdDb2dPolyline/OdDb3dPolyline -> mcsPolyline conversion
	// Composite curves are converted to mcsPolyline
	MC_NANO_GATE_API HRESULT ConvertCurveEx(IN const OdGeCurve3d& odgeCurveIn, OUT OdSharedPtr<McGeCurve3d>& pGeCurveOut);

	// polylines .....................................................................................

	MC_NANO_GATE_API HRESULT ConvertPolyline(OdDbPolyline* pPoly, const mcsPolyline& poly);
	MC_NANO_GATE_API HRESULT Convert2dPolyline(OdDb2dPolyline* pPoly, const mcsPolyline& poly);
	MC_NANO_GATE_API HRESULT Convert3dPolyline(OdDb3dPolyline* pPoly, const mcsPolyline& poly);
	MC_NANO_GATE_API HRESULT ConvertPolyline(mcsPolyline& polyline, const OdDbPolyline* pPolyline);
	MC_NANO_GATE_API HRESULT Convert2dPolyline(mcsPolyline& polyline, const OdDb2dPolyline* pPolyline);
	MC_NANO_GATE_API HRESULT Convert3dPolyline(mcsPolyline& polyline, const OdDb3dPolyline* pPolyline);

	MCCVT_API bool symplifyCurve(
		const mcsCurve*  pMcCurve,
		OUT mcsCurve*&   pSimplifiedCurve,
		IN const mcsTol& splineSimplificationTol);

	MC_NANO_GATE_API OdCmEntityColor  ConvertEntColor(COLORREF color);
	MC_NANO_GATE_API OdDb::LineWeight ConvertLineWeight(int weight);
	MC_NANO_GATE_API OdDbSafeObjectId ConvertLinetype(DWORD iLT, OdDbDatabase* pDb);

	MC_NANO_GATE_API HRESULT CreateRegion(OdDbRegionPtr& pR, const mcsPlCurves& contour, const mcsVector* pvNormal = NULL);
}; // namespace McCvt

MC_NANO_GATE_API OdResult mcsGetOdCurvePlane(const OdDbCurve* pCrv, OUT OdGePlane& plane, OUT OdDb::Planarity& planarity);

//#endif//#ifndef MFC_DEBUG
