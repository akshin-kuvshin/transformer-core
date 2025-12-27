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

class McGeCircArc2d;
class McGeLineEnt2d;
class McGePlanarEnt;

#include "mccurv2d.h"
class McGeEllipArc2d;

//==============================================================================
class MCGEL_API McGeEllipArc2d : public McGeCurve2d
{
public:
	McGeEllipArc2d();
	McGeEllipArc2d(const McGeEllipArc2d& ell);
	McGeEllipArc2d(const McGeCircArc2d& arc);
	McGeEllipArc2d(
		const McGePoint2d& cent, const McGeVector2d& majorAxis,
		const McGeVector2d& minorAxis, double majorRadius,
		double minorRadius);

	McGeEllipArc2d(
		const McGePoint2d& cent, const McGeVector2d& majorAxis,
		const McGeVector2d& minorAxis, double majorRadius,
		double minorRadius, double ang1, double ang2);

	// Intersection with other geometric objects.
	virtual bool intersectWith(
		const McGeLinearEnt2d& line, int& intn,
		McGePoint2d& p1, McGePoint2d& p2,
		const McGeTol& tol = McGeContext::gTol) const;

	// Inquiry Methods
	virtual bool isCircular(const McGeTol& tol = McGeContext::gTol) const;

	// Test if point is inside full ellipse
	virtual bool isInside(const McGePoint2d& pnt, const McGeTol& tol = McGeContext::gTol) const;

	// Definition of ellipse
	virtual McGePoint2d    center() const;
	virtual double         minorRadius() const;
	virtual double         majorRadius() const;
	virtual McGeVector2d   minorAxis() const;
	virtual McGeVector2d   majorAxis() const;
	virtual double         startAng() const;
	virtual double         endAng() const;
	virtual McGePoint2d    startPoint() const;
	virtual McGePoint2d    endPoint() const;

	virtual McGeEllipArc2d& setCenter(const McGePoint2d& cent);
	virtual McGeEllipArc2d& setMinorRadius(double rad);
	virtual McGeEllipArc2d& setMajorRadius(double rad);
	virtual McGeEllipArc2d& setAxes(const McGeVector2d& majorAxis, const McGeVector2d& minorAxis);
	virtual McGeEllipArc2d& setAngles(double startAngle, double endAngle);

	virtual McGeEllipArc2d& set(
		const McGePoint2d& cent,
		const McGeVector2d& majorAxis,
		const McGeVector2d& minorAxis,
		double majorRadius, double minorRadius);

	virtual McGeEllipArc2d& set(
		const McGePoint2d& cent,
		const McGeVector2d& majorAxis,
		const McGeVector2d& minorAxis,
		double majorRadius, double minorRadius,
		double startAngle, double endAngle);

	virtual McGeEllipArc2d& set(const McGeCircArc2d&);

	// Assignment operator.
	virtual McGeEllipArc2d& operator = (const McGeEllipArc2d& ell);

	double mcs_GetArcHeight(double fromParam, double toParam) const;
};
//==============================================================================
