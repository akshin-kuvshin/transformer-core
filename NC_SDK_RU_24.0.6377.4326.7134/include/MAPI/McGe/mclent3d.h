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
#include "mcvec3d.h"
#include "mcpnt3d.h"

class McGeLine3d;
class McGeCircArc3d;
class McGePlanarEnt;

//==============================================================================
class MCGEL_API McGeLinearEnt3d : public McGeCurve3d
{
public:
		// Intersection with other geometric objects.
	virtual bool intersectWith (const McGeLinearEnt3d& line, McGePoint3d& intPt, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool intersectWith (const McGePlanarEnt& plane, McGePoint3d& intPnt, const McGeTol& tol = McGeContext::gTol) const;

		// Projection-intersection with other geometric objects.
	virtual bool projIntersectWith(
		const McGeLinearEnt3d& line,
		const McGeVector3d& projDir,
		McGePoint3d& pntOnThisLine,
		McGePoint3d& pntOnOtherLine,
		const McGeTol& tol = McGeContext::gTol) const;

		// Find the overlap with other McGeLinearEnt object
	virtual bool overlap(const McGeLinearEnt3d& line, McGeLinearEnt3d*& overlap, const McGeTol& tol = McGeContext::gTol) const;

		// Containment tests.
	virtual bool isOn(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isOn(const McGePoint3d& pnt, double& param, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isOn(double param, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isOn(const McGePlane& plane,const McGeTol& tol = McGeContext::gTol) const;

		// Direction tests.
	virtual bool isParallelTo(const McGeLinearEnt3d& line, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isParallelTo  (const McGePlanarEnt& plane, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isPerpendicularTo(const McGeLinearEnt3d& line, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isPerpendicularTo(const McGePlanarEnt& plane, const McGeTol& tol = McGeContext::gTol) const;

		// Test if two lines are colinear.
	virtual bool isColinearTo(const McGeLinearEnt3d& line, const McGeTol& tol = McGeContext::gTol) const;

		// Perpendicular through a given point
	virtual void getPerpPlane(const McGePoint3d& pnt, McGePlane& plane) const;

		// Definition of line.
	virtual McGePoint3d    pointOnLine   () const;
	virtual McGeVector3d   direction     () const;
	virtual void           getLine       (McGeLine3d&) const;

		// Assignment operator.
	virtual McGeLinearEnt3d& operator =  (const McGeLinearEnt3d& line);

protected:
	McGeLinearEnt3d ();
};
//==============================================================================
