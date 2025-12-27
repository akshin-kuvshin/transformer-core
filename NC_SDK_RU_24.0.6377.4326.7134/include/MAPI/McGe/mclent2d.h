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
#include "mcvec2d.h"
#include "mcpnt2d.h"

class McGeLine2d;
class McGeCircArc2d;
class McGePlanarEnt;

//==============================================================================
class MCGEL_API McGeLinearEnt2d : public McGeCurve2d
{
public:
	// Intersection with other geometric objects.
	virtual bool intersectWith(const McGeLinearEnt2d& line, McGePoint2d& intPt, const McGeTol& tol = McGeContext::gTol) const;

	// Find the overlap with other McGeLinearEnt object
	virtual bool overlap(const McGeLinearEnt2d& line, McGeLinearEnt2d*& overlap, const McGeTol& tol = McGeContext::gTol) const;

	// Containment tests.
	virtual bool isOn(const McGePoint2d& pnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isOn(const McGePoint2d& pnt, double& param, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isOn(double param, const McGeTol& tol = McGeContext::gTol) const;

	// Direction tests.
	virtual bool isParallelTo(const McGeLinearEnt2d& line, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isPerpendicularTo(const McGeLinearEnt2d& line, const McGeTol& tol = McGeContext::gTol) const;

	// Test if two lines are colinear.
	virtual bool isColinearTo(const McGeLinearEnt2d& line, const McGeTol& tol = McGeContext::gTol) const;
	virtual McGeEntity2d& transformBy(const McGeMatrix2d& xfm);

	// Definition of line.
	virtual McGePoint2d    pointOnLine() const;
	virtual McGeVector2d   direction() const;
	virtual void           getLine(McGeLine2d&) const;

	// Assignment operator.
	virtual McGeLinearEnt2d& operator =  (const McGeLinearEnt2d& line);

protected:
	McGeLinearEnt2d();
};
//==============================================================================
