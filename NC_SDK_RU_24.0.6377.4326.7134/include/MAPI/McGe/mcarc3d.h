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

#include "mccurv3d.h"
#include "mcplane.h"

class McGeLine3d;
class McGeCircArc2d;
class McGePlanarEnt;

//==============================================================================
class MCGEL_API McGeCircArc3d : public McGeCurve3d
{
public:
	McGeCircArc3d();
	McGeCircArc3d(const McGeCircArc3d& arc);
	McGeCircArc3d(const McGePoint3d& cent, const McGeVector3d& nrm, double radius);
	McGeCircArc3d(const McGePoint3d& startPoint, const McGePoint3d& pnt, const McGePoint3d& endPoint);
	McGeCircArc3d(
		const McGePoint3d& cent, 
		const McGeVector3d& nrm, 
		const McGeVector3d& refVec, 
		double radius,
		double startAngle, 
		double endAngle);
	                                        
		// Return the point on this object that is closest to the other object.
	virtual McGePoint3d closestPointToPlane (
		const McGePlanarEnt& plane,
		McGePoint3d& pointOnPlane,
		const McGeTol& tol = McGeContext::gTol) const;

		// Intersection with other geometric objects.
	virtual bool intersectWith(
		const McGeLinearEnt3d& line, int& intn,
		McGePoint3d& p1, McGePoint3d& p2,
		const McGeTol& tol = McGeContext::gTol) const;

	virtual bool intersectWith(
		const McGeCircArc3d& arc, int& intn,
		McGePoint3d& p1, McGePoint3d& p2,
		const McGeTol& tol = McGeContext::gTol) const;

	virtual bool intersectWith(
		const McGePlanarEnt& plane, int& numOfIntersect,
		McGePoint3d& p1, McGePoint3d& p2,
		const McGeTol& tol = McGeContext::gTol) const;

		// Projection-intersection with other geometric objects.
	virtual bool projIntersectWith(
		const McGeLinearEnt3d& line,
		const McGeVector3d& projDir, int& numInt,
		McGePoint3d& pntOnArc1,
		McGePoint3d& pntOnArc2,
		McGePoint3d& pntOnLine1,
		McGePoint3d& pntOnLine2,
		const McGeTol& tol = McGeContext::gTol) const;

		// Tangent to the circular arc.
	virtual bool tangent(const McGePoint3d& pnt, McGeLine3d& line, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool tangent(const McGePoint3d& pnt, McGeLine3d& line, const McGeTol& tol, McGeError& error) const;

		// Possible error conditions:  kArg1TooBig, kArg1InsideThis, 
		// kArg1OnThis, kThisIsInfiniteLine

		// Plane of the arc
	virtual void getPlane(McGePlane& plane) const;

		// Test if point is inside circle.
	virtual bool isInside(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;

		// Definition of circular arc
	virtual McGePoint3d    center    () const;
	virtual McGeVector3d   normal    () const;
	virtual McGeVector3d   refVec    () const;
	virtual double         radius    () const;
	virtual double         startAng  () const;
	virtual double         endAng    () const;
	virtual McGePoint3d    startPoint() const;
	virtual McGePoint3d    endPoint  () const;

	virtual McGeCircArc3d& setCenter   (const McGePoint3d&);
	virtual McGeCircArc3d& setAxes     (const McGeVector3d& normal, const McGeVector3d& refVec);
	virtual McGeCircArc3d& setRadius   (double);
	virtual McGeCircArc3d& setAngles   (double startAngle, double endAngle);

	virtual McGeCircArc3d& set(const McGePoint3d& cent, const McGeVector3d& nrm, double radius);

	virtual McGeCircArc3d& set(
		const McGePoint3d& cent,
		const McGeVector3d& nrm,
		const McGeVector3d& refVec, double radius,
		double startAngle, double endAngle);

	virtual McGeCircArc3d& set(const McGePoint3d& startPoint, const McGePoint3d& pnt, const McGePoint3d& endPoint);
	virtual McGeCircArc3d& set(const McGePoint3d& startPoint, const McGePoint3d& pnt, const McGePoint3d& endPoint, McGeError& error);

		// Possible errors:  kEqualArg1Arg2, kEqualArg1Arg3, kEqualArg2Arg3, 
		// kLinearlyDependentArg1Arg2Arg3.
		// Degenerate results: none.
		// On error, the object is unchanged.
	virtual McGeCircArc3d& set(
		const McGeCurve3d& curve1,
		const McGeCurve3d& curve2,
		double radius, double& param1, double& param2,
		bool& success);

		// On success, this arc becomes the fillet of the given radius between the two curves,
		// whose points of tangency are nearest param1 and param2 respectively.
	virtual McGeCircArc3d& set(
		const McGeCurve3d& curve1,
		const McGeCurve3d& curve2,
		const McGeCurve3d& curve3,
		double& param1, double& param2, double& param3,
		bool& success);

		// Assignment operator.
	virtual McGeCircArc3d& operator = (const McGeCircArc3d& arc);

	static McGeCircArc3d& mcs_sMakeArcWithBulge(
		const McGePoint3d&  ptStart,
		const McGePoint3d&  ptEnd,
		const McGeVector3d& vNormal,
		double              rBulge,
		OUT McGeCircArc3d&  arc,
		const McGeTol&      tol);
};
//==============================================================================

MCGEL_API double mcge_getCircArcHeight(double radius, const McGePoint3d& sp, const McGePoint3d& ep, double dAngle);
