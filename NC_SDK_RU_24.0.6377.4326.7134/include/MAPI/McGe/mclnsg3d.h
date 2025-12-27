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

#include "mcline3d.h"
#include "mcplane.h"

class McGeLineSeg2d;

//==============================================================================
class MCGEL_API McGeLineSeg3d : public McGeLinearEnt3d
{
public:
	McGeLineSeg3d();
	McGeLineSeg3d(const McGeLineSeg3d& line);
	McGeLineSeg3d(const McGePoint3d& pnt, const McGeVector3d& vec);
	McGeLineSeg3d(const McGePoint3d& pnt1, const McGePoint3d& pnt2);

		// Bisector.
	virtual void getBisector  (McGePlane& plane) const;

		// Barycentric combination of end points.
	virtual McGePoint3d baryComb(double blendCoeff) const;

		// Definition of linear segment
	virtual McGePoint3d startPoint () const;
	virtual McGePoint3d midPoint   () const;
	virtual McGePoint3d endPoint   () const;
	virtual double      length     () const;
	virtual double      length     (double fromParam, double toParam, double tol = McGeContext::gTol.equalPoint()) const;
		
	// Set methods.
	virtual McGeLineSeg3d& set (const McGePoint3d& pnt, const McGeVector3d& vec);
	virtual McGeLineSeg3d& set (const McGePoint3d& pnt1, const McGePoint3d& pnt2);

	virtual McGeLineSeg3d& set(
		const McGeCurve3d& curve1,
		const McGeCurve3d& curve2,
		double& param1, double& param2,
		bool& success);

	virtual McGeLineSeg3d& set(
		const McGeCurve3d& curve,
		const McGePoint3d& point, double& param,
		bool& success);

		// Assignment operator.
	virtual McGeLineSeg3d& operator =   (const McGeLineSeg3d& line);
};
//==============================================================================
