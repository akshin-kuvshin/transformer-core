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

#include "mcent2d.h"
#include "mcponc2d.h"

class McGeCurve2d;
class McGeSurface;
class McGePoint2d;
class McGePlane;
class McGeVector2d;
class McGeLinearEnt2d;
class McGeLine2d;
class McGePointOnCurve2d;
class McGePointOnSurface;
class McGeInterval;
class McGeMatrix2d;
class McGePointOnCurve2dData;
class McGeBoundBlock3d;

//==============================================================================
class MCGEL_API McGeCurve2d : public McGeEntity2d
{
public:
	// Parametrization.
	virtual void           getInterval(McGeInterval& intrvl) const;
	virtual void           getInterval(McGeInterval& intrvl, McGePoint2d& start, McGePoint2d& end) const;
	virtual McGeCurve2d&   reverseParam();
	virtual McGeCurve2d&   setInterval();
	virtual bool           setInterval(const McGeInterval& intrvl);

	// Distance to other geometric objects.
	virtual double       distanceTo(const McGePoint2d& pnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual double       distanceTo(const McGeCurve2d& curve, const McGeTol& tol = McGeContext::gTol) const;

	// Return the point on this object that is closest to the other object.
	// These methods return point on this curve as a simple 2d point.
	virtual McGePoint2d closestPointTo(
		const McGePoint2d& pnt,
		const McGeTol& tol = McGeContext::gTol) const;

	virtual McGePoint2d closestPointTo(
		const McGeCurve2d& curve2d,
		McGePoint2d& pntOnOtherCrv,
		const McGeTol& tol = McGeContext::gTol) const;

	// Alternate signatures for above functions.  These methods return point
	// on this curve as an McGePointOnCurve2d.
	virtual void getClosestPointTo(
		const McGePoint2d& pnt,
		McGePointOnCurve2d& pntOnCrv,
		const McGeTol& tol = McGeContext::gTol) const;

	virtual void getClosestPointTo(
		const McGeCurve2d& curve2d,
		McGePointOnCurve2d& pntOnThisCrv,
		McGePointOnCurve2d& pntOnOtherCrv,
		const McGeTol& tol = McGeContext::gTol) const;

	// Return point on curve whose normal vector passes thru input point.
	// Second parameter contains initial guess value and also 
	// contains output point.

	// Returns true or false depending on whether a normal point was found.
	virtual bool getNormalPoint(const McGePoint2d& pnt, McGePointOnCurve2d& pntOnCrv, const McGeTol& tol = McGeContext::gTol) const;

	// Return oriented bounding box of curve.
	virtual McGeBoundBlock2d  boundBlock() const;
	virtual McGeBoundBlock2d  boundBlock(const McGeInterval& range) const;

	// Return bounding box whose sides are parallel to coordinate axes.
	virtual McGeBoundBlock2d  orthoBoundBlock() const;
	virtual McGeBoundBlock2d  orthoBoundBlock(const McGeInterval& range) const;

	// Tests if point is on curve.
	virtual bool isOn(const McGePoint2d& pnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isOn(const McGePoint2d& pnt, double& param, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isOn(double param, const McGeTol& tol = McGeContext::gTol) const;

	// Parameter of the point on curve.  Contract: point IS on curve
	virtual double paramOf(const McGePoint2d& pnt, const McGeTol& tol = McGeContext::gTol)const;

	// Return the offset of the curve.
	virtual void getTrimmedOffset(
		double distance,
		McGePVoidArray& offsetCurveList,
		McGe::OffsetCrvExtType extensionType = McGe::kFillet,
		const McGeTol& tol = McGeContext::gTol) const;

	// Geometric inquiry methods.
	virtual bool isClosed(const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isLinear(McGeLine2d& line, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isPeriodic(double& period) const;

	// Length based methods.
	virtual double length(double fromParam, double toParam, double tol = McGeContext::gTol.equalPoint()) const;

	virtual double paramAtLength(
		double datumParam,
		double length,
		bool posParamDir = true,
		double tol = McGeContext::gTol.equalPoint()) const;

	virtual bool area(double startParam, double endParam, double& value, const McGeTol& tol = McGeContext::gTol) const;

	// Degeneracy.
	virtual bool isDegenerate(McGe::EntityId& degenerateType, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isDegenerate(McGeEntity2d*& pConvertedEntity, const McGeTol& tol = McGeContext::gTol) const;

	// Modify methods.
	virtual void getSplitCurves(double param, McGeCurve2d*& piece1, McGeCurve2d*& piece2) const;

	// Explode curve into its component sub-curves.
	virtual bool explode(
		McGePVoidArray& explodedCurves,
		McGeIntArray& newExplodedCurvesDelFlags,
		const McGeInterval* intrvl = NULL) const;

	// Local closest points
	virtual void getLocalClosestPoints(
		const McGePoint2d& point,
		McGePointOnCurve2d& approxPnt,
		const McGeInterval* nbhd = 0,
		const McGeTol& tol = McGeContext::gTol) const;

	virtual void getLocalClosestPoints(
		const McGeCurve2d& otherCurve,
		McGePointOnCurve2d& approxPntOnThisCrv,
		McGePointOnCurve2d& approxPntOnOtherCrv,
		const McGeInterval* nbhd1 = 0,
		const McGeInterval* nbhd2 = 0,
		const McGeTol& tol = McGeContext::gTol) const;

	// Return start and end points.
	virtual bool hasStartPoint(McGePoint2d& startPnt) const;
	virtual bool hasEndPoint(McGePoint2d& endPnt) const;

	// Evaluate methods.
	virtual McGePoint2d    evalPoint(double param) const;
	virtual McGePoint2d    evalPoint(double param, int numDeriv, McGeVector2dArray& derivArray) const;

	// Polygonize curve to within a specified tolerance.
	virtual void getSamplePoints(
		double fromParam, double toParam,
		double approxEps,
		McGePoint2dArray& pointArray,
		McGeDoubleArray& paramArray) const;

	virtual void getSamplePoints(int numSample, McGePoint2dArray& pointArray) const;

	// Assignment operator.
	virtual McGeCurve2d& operator =  (const McGeCurve2d& curve);

	// McGe only and non-virtual !!!
	// calculates a curvature at a given point;
	bool mcs_evalCurvature(IN double p, OUT double& curvature) const;

	// calculates the minimum possible pt-tolerance that may be used for calculations with this curve
	// NOTE: internally calls orthoBoundBlock()
	// 'valDigidts' is the number of significant digits in a result
	// NOTE: valDigidts = 16 - is the max limit for the 'double' type, don't use the val more than 13.
	void mcs_adjustTolToCurveGabarite(IN OUT McGeTol& tol, IN OPTIONAL int valDigidts = 12);

protected:
	McGeCurve2d();
};
//==============================================================================

