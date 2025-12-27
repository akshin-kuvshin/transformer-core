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

#include "mcent3d.h"
#include "mcponc3d.h"

class McGeCurve2d;
class McGeSurface;
class McGePoint3d;
class McGePlane;
class McGeVector3d;
class McGeLinearEnt3d;
class McGeLine3d;
class McGePointOnCurve3d;
class McGePointOnSurface;
class McGeInterval;
class McGeMatrix3d;
class McGePointOnCurve3dData;
class McGeBoundBlock3d;

//==============================================================================
class MCGEL_API McGeCurve3d : public McGeEntity3d
{
public:
		// Parametrization.
	virtual void           getInterval(McGeInterval& intrvl) const;
	virtual void           getInterval(McGeInterval& intrvl, McGePoint3d& start, McGePoint3d& end) const;
	virtual McGeCurve3d&   reverseParam();
	virtual McGeCurve3d&   setInterval();
	virtual bool           setInterval(const McGeInterval& intrvl);

		// Distance to other geometric objects.
	virtual double       distanceTo(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual double       distanceTo(const McGeCurve3d& curve, const McGeTol& tol = McGeContext::gTol) const;

		// Return the point on this object that is closest to the other object.
		// These methods return point on this curve as a simple 3d point.
	virtual McGePoint3d closestPointTo(
		const McGePoint3d& pnt, 
		const McGeTol& tol = McGeContext::gTol) const;

	virtual McGePoint3d closestPointTo(
		const McGeCurve3d& curve3d, 
		McGePoint3d& pntOnOtherCrv, 
		const McGeTol& tol = McGeContext::gTol) const;

		// Alternate signatures for above functions.  These methods return point
		// on this curve as an McGePointOnCurve3d.
  virtual void getClosestPointTo(
		const McGePoint3d& pnt, 
		McGePointOnCurve3d& pntOnCrv, 
		const McGeTol& tol = McGeContext::gTol) const;

  virtual void getClosestPointTo(
		const McGeCurve3d& curve3d, 
		McGePointOnCurve3d& pntOnThisCrv, 
		McGePointOnCurve3d& pntOnOtherCrv, 
		const McGeTol& tol = McGeContext::gTol) const;

		// Return closest points when projected in a given direction.
		// These methods return point on this curve as a simple 3d point.
	virtual McGePoint3d projClosestPointTo(
		const McGePoint3d& pnt, 
		const McGeVector3d& projectDirection, 
		const McGeTol& tol = McGeContext::gTol) const;

	virtual McGePoint3d projClosestPointTo(
		const McGeCurve3d& curve3d,
		const McGeVector3d& projectDirection,
		McGePoint3d& pntOnOtherCrv,
		const McGeTol& tol = McGeContext::gTol) const;

	  // Alternate signatures for above functions.  These methods return point
	  // on this curve as an McGePointOnCurve3d.
	virtual void getProjClosestPointTo(
		const McGePoint3d& pnt,
		const McGeVector3d& projectDirection,
		McGePointOnCurve3d& pntOnCrv,
		const McGeTol& tol = McGeContext::gTol) const;

	virtual void getProjClosestPointTo(
		const McGeCurve3d& curve3d,
		const McGeVector3d& projectDirection,
		McGePointOnCurve3d& pntOnThisCrv,
		McGePointOnCurve3d& pntOnOtherCrv,
		const McGeTol& tol = McGeContext::gTol) const;

		// Return point on curve whose normal vector passes thru input point.
		// Second parameter contains initial guess value and also 
		// contains output point.

		// Returns true or false depending on whether a normal point was found.
	virtual bool getNormalPoint(const McGePoint3d& pnt, McGePointOnCurve3d& pntOnCrv, const McGeTol& tol = McGeContext::gTol) const;

		// Return oriented bounding box of curve.
	virtual McGeBoundBlock3d  boundBlock() const;
	virtual McGeBoundBlock3d  boundBlock(const McGeInterval& range) const;

		// Return bounding box whose sides are parallel to coordinate axes.
	virtual McGeBoundBlock3d  orthoBoundBlock() const;
	virtual McGeBoundBlock3d  orthoBoundBlock(const McGeInterval& range) const;

		// Project methods.
	virtual McGeEntity3d*  project(
		const McGePlane& projectionPlane, 
		const McGeVector3d& projectDirection, 
		const McGeTol& tol = McGeContext::gTol) const;

	virtual McGeEntity3d*  orthoProject(
		const McGePlane& projectionPlane, 
		const McGeTol& tol = McGeContext::gTol) const;

		// Tests if point is on curve.
	virtual bool isOn(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isOn(const McGePoint3d& pnt, double& param, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isOn(double param, const McGeTol& tol = McGeContext::gTol) const;

		// Parameter of the point on curve.  Contract: point IS on curve
	virtual double paramOf(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol)const;

		// Return the offset of the curve.
	virtual void getTrimmedOffset(
		double distance,
		const McGeVector3d& planeNormal,
		McGePVoidArray& offsetCurveList,
		McGe::OffsetCrvExtType extensionType = McGe::kFillet,
		const McGeTol& tol = McGeContext::gTol) const;

		// Geometric inquiry methods.
	virtual bool isClosed      (const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isPlanar      (McGePlane& plane, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isLinear      (McGeLine3d& line, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isCoplanarWith(const McGeCurve3d& curve3d, McGePlane& plane, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isPeriodic    (double& period) const;

		// Length based methods.
	virtual double length(double fromParam, double toParam, double tol = McGeContext::gTol.equalPoint()) const;

	virtual double paramAtLength(
		double datumParam, 
		double length, 
		bool posParamDir = true, 
		double tol = McGeContext::gTol.equalPoint()) const;

	virtual bool area (double startParam, double endParam, double& value, const McGeTol& tol = McGeContext::gTol) const;

		// Degeneracy.
	virtual bool isDegenerate(McGe::EntityId& degenerateType, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isDegenerate(McGeEntity3d*& pConvertedEntity, const McGeTol& tol = McGeContext::gTol) const;

		// Modify methods.
	virtual void getSplitCurves(double param, McGeCurve3d*& piece1, McGeCurve3d*& piece2) const;

	int mcs_getSplitCurves(const mcsDoubleArray& paramsSortedAscent, OUT McsArray<std::shared_ptr<McGeCurve3d>>& pieces) const;

		// Explode curve into its component sub-curves.
	virtual bool explode(
		McGePVoidArray& explodedCurves, 
		McGeIntArray& newExplodedCurvesDelFlags, 
		const McGeInterval* intrvl = NULL) const;

		// Local closest points
	virtual void getLocalClosestPoints(
		const McGePoint3d& point,
		McGePointOnCurve3d& approxPnt,
		const McGeInterval* nbhd = 0,
		const McGeTol& tol = McGeContext::gTol) const;

	virtual void getLocalClosestPoints(
		const McGeCurve3d& otherCurve,
		McGePointOnCurve3d& approxPntOnThisCrv,
		McGePointOnCurve3d& approxPntOnOtherCrv,
		const McGeInterval* nbhd1 = 0,
		const McGeInterval* nbhd2 = 0,
		const McGeTol& tol = McGeContext::gTol) const;

		// Return start and end points.
	virtual bool hasStartPoint(McGePoint3d& startPnt) const;
	virtual bool hasEndPoint  (McGePoint3d& endPnt) const;

		// Evaluate methods.
	virtual McGePoint3d    evalPoint(double param) const;
	virtual McGePoint3d    evalPoint(double param, int numDeriv, McGeVector3dArray& derivArray) const;

		// Polygonize curve to within a specified tolerance.
	virtual void getSamplePoints(
		double fromParam, double toParam,
		double approxEps, 
		McGePoint3dArray& pointArray, 
		McGeDoubleArray& paramArray) const;

	virtual void getSamplePoints(int numSample, McGePoint3dArray& pointArray) const;

		// Assignment operator.
	virtual McGeCurve3d& operator =  (const McGeCurve3d& curve);

		// McGe only and non-virtual !!!
		// calculates a curvature at a given point;
	bool mcs_evalCurvature(IN double p, OUT double& curvature) const;

		// calculates the minimum possible pt-tolerance that may be used for calculations with this curve
		// NOTE: internally calls orthoBoundBlock()
		// 'valDigidts' is the number of significant digits in a result
		// NOTE: valDigidts = 16 - is the max limit for the 'double' type, don't use the val more than 13.
	void mcs_adjustTolToCurveGabarite(IN OUT McGeTol& tol, IN OPTIONAL int valDigidts = 12);

		// Searches points on this curve where curvature reaches the given value.
		// Result will be returned as an array of curve parameters.
		// Search is carried out within given interval, if it's not provided,
		// the whole curve's interval is used.
	bool mcs_findCurvePointsWithGivenCurvature(
		IN double                  curvature,
		OUT McGeDoubleArray&       params,
		IN OPTIONAL double         prmStart = UNKNOWNVALUE,
		IN OPTIONAL double         prmEnd = UNKNOWNVALUE,
		IN OPTIONAL const McGeTol& tol = McGeContext::gTol) const;

protected:
	McGeCurve3d();
};
//==============================================================================

MCGEL_API std::shared_ptr<McGeCurve3d> mcge_curve2dToCurve3d(IN const McGeCurve2d& curve);
MCGEL_API std::shared_ptr<McGeCurve2d> mcge_curve3dToCurve2d(IN const McGeCurve3d& curve);

// Оптимизированный метод поиска ближайших точек на плоских отрезках,
// Работает в 2.5 раза быстрее общего способа.
// (!) Если есть пересечение в пределах указанной точности, вернёт точный 0
// Если bCheckOnly = true, то по возможности только проверяет пересечение, но не считает его,
// в этом случае просто вернётся 0, если пересечение есть

MCGEL_API double mcge_getClosestPoints_planar_LS_LS_2d(
	const McGePoint3d& ptStart1,
	const McGePoint3d& ptEnd1,
	const McGePoint3d& ptStart2,
	const McGePoint3d& ptEnd2,
	OUT McGePoint3d&   ptOn1,
	OUT McGePoint3d&   ptOn2,
	double             dTol,
	bool               bCheckOnly = false);

