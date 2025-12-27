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

#include "mcpent2d.h"
#include "mccurv2d.h"

class McGeCurve2d;

//==============================================================================
class MCGEL_API McGePointOnCurve2d : public McGePointEnt2d
{
public:
	McGePointOnCurve2d();
	McGePointOnCurve2d(const McGeCurve2d& crv);
	McGePointOnCurve2d(const McGeCurve2d& crv, double param);
	McGePointOnCurve2d(const McGePointOnCurve2d& src);

	// Assignment operator.
	virtual McGePointOnCurve2d& operator = (const McGePointOnCurve2d& src);

	// Query functions.
	virtual const McGeCurve2d* curve() const;
	virtual double parameter() const;

	// Functions to evaluate a point.
	virtual McGePoint2d point() const;
	virtual McGePoint2d point(double param);
	virtual McGePoint2d point(const McGeCurve2d& crv, double param);

	// Functions to evaluate the derivatives.
	virtual McGeVector2d deriv(int order) const;
	virtual McGeVector2d deriv(int order, double param);
	virtual McGeVector2d deriv(int order, const McGeCurve2d& crv, double param);

	// Singularity
	virtual bool isSingular(const McGeTol& tol = McGeContext::gTol) const;
	virtual bool curvature(double& res);
	virtual bool curvature(double param, double& res);

	// Set functions.
	virtual McGePointOnCurve2d& setCurve(const McGeCurve2d& crv);
	virtual McGePointOnCurve2d& setParameter(double param);
};
//==============================================================================
