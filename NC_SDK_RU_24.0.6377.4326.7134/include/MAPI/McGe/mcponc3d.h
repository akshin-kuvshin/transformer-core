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

#include "mcpent3d.h"
#include "mccurv3d.h"

class McGeCurve3d;

//==============================================================================
class MCGEL_API McGePointOnCurve3d : public McGePointEnt3d
{
public:
	McGePointOnCurve3d();
	McGePointOnCurve3d(const McGeCurve3d& crv);
	McGePointOnCurve3d(const McGeCurve3d& crv, double param);
	McGePointOnCurve3d(const McGePointOnCurve3d& src);

		// Assignment operator.
	virtual McGePointOnCurve3d& operator = (const McGePointOnCurve3d& src);

		// Query functions.
	virtual const McGeCurve3d* curve() const;
	virtual double parameter() const;

		// Functions to evaluate a point.
	virtual McGePoint3d point() const;
	virtual McGePoint3d point(double param);
	virtual McGePoint3d point(const McGeCurve3d& crv, double param);

		// Functions to evaluate the derivatives.
	virtual McGeVector3d deriv(int order) const;
	virtual McGeVector3d deriv(int order, double param);
	virtual McGeVector3d deriv(int order, const McGeCurve3d& crv, double param);

		// Singularity
	virtual bool isSingular(const McGeTol& tol = McGeContext::gTol) const;
	virtual bool curvature(double& res);
	virtual bool curvature(double param, double& res);

		// Set functions.
	virtual McGePointOnCurve3d& setCurve(const McGeCurve3d& crv);
	virtual McGePointOnCurve3d& setParameter(double param);
};
//==============================================================================
