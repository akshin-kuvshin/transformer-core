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

class McGeCircArc3d;
class McGeLineEnt3d;
class McGePlanarEnt;

#include "mccurv3d.h"
class McGeEllipArc2d;

//==============================================================================
class MCGEL_API McGeEllipArc3d : public McGeCurve3d
{
public:
	McGeEllipArc3d();
	McGeEllipArc3d(const McGeEllipArc3d& ell);
	McGeEllipArc3d(const McGeCircArc3d& arc);
	McGeEllipArc3d(
		const McGePoint3d& cent, const McGeVector3d& majorAxis,
		const McGeVector3d& minorAxis, double majorRadius,
		double minorRadius);

	McGeEllipArc3d(
		const McGePoint3d& cent, const McGeVector3d& majorAxis,
		const McGeVector3d& minorAxis, double majorRadius,
		double minorRadius, double ang1, double ang2);
	                                      
		// Return the point on this object that is closest to the other object.
	virtual McGePoint3d closestPointToPlane(
		const McGePlanarEnt& plane,
		McGePoint3d& pointOnPlane,
		const McGeTol& = McGeContext::gTol) const;

		// Intersection with other geometric objects.
	virtual bool intersectWith(
		const McGeLinearEnt3d& line, int& intn,
		McGePoint3d& p1, McGePoint3d& p2,
		const McGeTol& tol = McGeContext::gTol) const;  

	virtual bool intersectWith(
		const McGePlanarEnt& plane, int& numOfIntersect,
		McGePoint3d& p1, McGePoint3d& p2,
		const McGeTol& tol = McGeContext::gTol) const;

		// Projection-intersection with other geometric objects.
	virtual bool projIntersectWith(
		const McGeLinearEnt3d& line,
		const McGeVector3d& projDir, int &numInt,
		McGePoint3d& pntOnEllipse1,
		McGePoint3d& pntOnEllipse2,
		McGePoint3d& pntOnLine1,
		McGePoint3d& pntOnLine2,
		const McGeTol& tol = McGeContext::gTol) const;

		// Plane of the ellipse
	virtual void getPlane      (McGePlane& plane) const;

		// Inquiry Methods
	virtual bool isCircular (const McGeTol& tol = McGeContext::gTol) const;

		// Test if point is inside full ellipse
	virtual bool isInside (const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;

		// Definition of ellipse
	virtual McGePoint3d    center        () const;
	virtual double         minorRadius   () const;
	virtual double         majorRadius   () const;
	virtual McGeVector3d   minorAxis     () const;
	virtual McGeVector3d   majorAxis     () const;
	virtual McGeVector3d   normal        () const; 
	virtual double         startAng      () const;
	virtual double         endAng        () const;
	virtual McGePoint3d    startPoint    () const;
	virtual McGePoint3d    endPoint      () const;

	virtual McGeEllipArc3d& setCenter     (const McGePoint3d& cent);
	virtual McGeEllipArc3d& setMinorRadius(double rad);
	virtual McGeEllipArc3d& setMajorRadius(double rad);
	virtual McGeEllipArc3d& setAxes       (const McGeVector3d& majorAxis, const McGeVector3d& minorAxis);
	virtual McGeEllipArc3d& setAngles     (double startAngle, double endAngle);

	virtual McGeEllipArc3d& set(
		const McGePoint3d& cent,
		const McGeVector3d& majorAxis,
		const McGeVector3d& minorAxis,
		double majorRadius, double minorRadius);

	virtual McGeEllipArc3d& set(
		const McGePoint3d& cent,
		const McGeVector3d& majorAxis,
		const McGeVector3d& minorAxis,
		double majorRadius, double minorRadius,
		double startAngle, double endAngle);

	virtual McGeEllipArc3d& set(const McGeCircArc3d&);

		// Assignment operator.
	virtual McGeEllipArc3d& operator = (const McGeEllipArc3d& ell);

	double mcs_GetArcHeight(double fromParam, double toParam) const;
};
//==============================================================================
