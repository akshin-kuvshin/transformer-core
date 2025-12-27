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
#include "mckvec.h"
#include "mcvec3d.h"
#include "mcpnt3d.h"

class McGeKnotVector;

//==============================================================================
class MCGEL_API McGeSplineEnt3d : public McGeCurve3d
{
protected:
	McGeSplineEnt3d ();

public:
	// Definition of spline
	virtual int degree() const;
	virtual int order() const;
	virtual int numKnots() const;
	virtual int numControlPoints() const;
	virtual int continuityAtKnot(int idx, const McGeTol& tol = McGeContext::gTol ) const;
	virtual bool isRational() const;
	virtual McGeKnotVector knots() const;

	virtual double      startParam() const;
	virtual double      endParam() const;
	virtual McGePoint3d startPoint() const;
	virtual McGePoint3d endPoint() const;

	// Interpolation data
	virtual bool hasFitData() const;

	// Editing
	virtual double            knotAt(int idx) const;
	virtual McGeSplineEnt3d&  setKnotAt(int idx, double val);
	virtual McGePoint3d       controlPointAt(int idx) const;
	virtual McGeSplineEnt3d&  setControlPointAt(int idx, const McGePoint3d& pnt);

	McGeSplineEnt3d&  operator = (const McGeSplineEnt3d& spline);
};
//==============================================================================
