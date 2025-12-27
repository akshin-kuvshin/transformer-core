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

#include "mcline2d.h"
#include "mcplane.h"

class McGeLineSeg2d;

//==============================================================================
class MCGEL_API McGeLineSeg2d : public McGeLinearEnt2d
{
public:
	McGeLineSeg2d();
	McGeLineSeg2d(const McGeLineSeg2d& line);
	McGeLineSeg2d(const McGePoint2d& pnt, const McGeVector2d& vec);
	McGeLineSeg2d(const McGePoint2d& pnt1, const McGePoint2d& pnt2);

	// Barycentric combination of end points.
	virtual McGePoint2d baryComb(double blendCoeff) const;

	// Definition of linear segment
	virtual McGePoint2d startPoint() const;
	virtual McGePoint2d midPoint() const;
	virtual McGePoint2d endPoint() const;
	virtual double      length() const;
	virtual double      length(double fromParam, double toParam, double tol = McGeContext::gTol.equalPoint()) const;

	// Set methods.
	virtual McGeLineSeg2d& set(const McGePoint2d& pnt, const McGeVector2d& vec);
	virtual McGeLineSeg2d& set(const McGePoint2d& pnt1, const McGePoint2d& pnt2);

	virtual McGeLineSeg2d& set(
		const McGeCurve2d& curve1,
		const McGeCurve2d& curve2,
		double& param1, double& param2,
		bool& success);

	virtual McGeLineSeg2d& set(
		const McGeCurve2d& curve,
		const McGePoint2d& point, double& param,
		bool& success);

	// Assignment operator.
	virtual McGeLineSeg2d& operator =   (const McGeLineSeg2d& line);
};
//==============================================================================
