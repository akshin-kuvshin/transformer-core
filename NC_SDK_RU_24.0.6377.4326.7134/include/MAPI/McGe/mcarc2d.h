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

#include "mccurv2d.h"
#include "mcplane.h"

class McGeLine2d;
class McGeCircArc2d;
class McGePlanarEnt;

//==============================================================================
class MCGEL_API McGeCircArc2d : public McGeCurve2d
{
public:
	McGeCircArc2d();
	McGeCircArc2d(const McGeCircArc2d& arc);
	McGeCircArc2d(const McGePoint2d& cent, double radius);
	McGeCircArc2d(const McGePoint2d& startPoint, const McGePoint2d& pnt, const McGePoint2d& endPoint);
	McGeCircArc2d(
		const McGePoint2d& cent,
		const McGeVector2d& refVec,
		double radius,
		double startAngle,
		double endAngle);

	// Intersection with other geometric objects.
	virtual bool intersectWith(
		const McGeLinearEnt2d& line, int& intn,
		McGePoint2d& p1, McGePoint2d& p2,
		const McGeTol& tol = McGeContext::gTol) const;

	virtual bool intersectWith(
		const McGeCircArc2d& arc, int& intn,
		McGePoint2d& p1, McGePoint2d& p2,
		const McGeTol& tol = McGeContext::gTol) const;

	// Tangent to the circular arc.
	virtual bool tangent(const McGePoint2d& pnt, McGeLine2d& line, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool tangent(const McGePoint2d& pnt, McGeLine2d& line, const McGeTol& tol, McGeError& error) const;

	// Possible error conditions:  kArg1TooBig, kArg1InsideThis, 
	// kArg1OnThis, kThisIsInfiniteLine

	// Test if point is inside circle.
	virtual bool isInside(const McGePoint2d& pnt, const McGeTol& tol = McGeContext::gTol) const;

	// Definition of circular arc
	virtual McGePoint2d    center() const;
	virtual McGeVector2d   refVec() const;
	virtual double         radius() const;
	virtual double         startAng() const;
	virtual double         endAng() const;
	virtual McGePoint2d    startPoint() const;
	virtual McGePoint2d    endPoint() const;

	virtual McGeCircArc2d& setCenter(const McGePoint2d&);
	virtual McGeCircArc2d& setRefVec(const McGeVector2d& refVec);
	virtual McGeCircArc2d& setRadius(double);
	virtual McGeCircArc2d& setAngles(double startAngle, double endAngle);

	virtual McGeCircArc2d& set(const McGePoint2d& cent, double radius);

	virtual McGeCircArc2d& set(
		const McGePoint2d& cent,
		const McGeVector2d& refVec, double radius,
		double startAngle, double endAngle);

	virtual McGeCircArc2d& set(const McGePoint2d& startPoint, const McGePoint2d& pnt, const McGePoint2d& endPoint);
	virtual McGeCircArc2d& set(const McGePoint2d& startPoint, const McGePoint2d& pnt, const McGePoint2d& endPoint, McGeError& error);

	// Possible errors:  kEqualArg1Arg2, kEqualArg1Arg3, kEqualArg2Arg3, 
	// kLinearlyDependentArg1Arg2Arg3.
	// Degenerate results: none.
	// On error, the object is unchanged.
	virtual McGeCircArc2d& set(
		const McGeCurve2d& curve1,
		const McGeCurve2d& curve2,
		double radius, double& param1, double& param2,
		bool& success);

	// On success, this arc becomes the fillet of the given radius between the two curves,
	// whose points of tangency are nearest param1 and param2 respectively.
	virtual McGeCircArc2d& set(
		const McGeCurve2d& curve1,
		const McGeCurve2d& curve2,
		const McGeCurve2d& curve3,
		double& param1, double& param2, double& param3,
		bool& success);

	// Assignment operator.
	virtual McGeCircArc2d& operator = (const McGeCircArc2d& arc);
};
//==============================================================================

MCGEL_API double mcge_getCircArcHeight(double radius, const McGePoint2d& sp, const McGePoint2d& ep, double dAngle);
