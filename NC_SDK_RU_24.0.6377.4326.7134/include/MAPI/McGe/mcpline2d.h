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
#include "mckvec.h"
#include "mcvec2d.h"
#include "mcpnt2d.h"
#include "mcsent2d.h"

//==============================================================================
class MCGEL_API McGePolyline2d : public McGeSplineEnt2d
{
public:
	McGePolyline2d();
	McGePolyline2d(const McGePolyline2d& src);
	McGePolyline2d(const McGePoint2dArray& points);
	McGePolyline2d(const McGeKnotVector& knots, const McGePoint2dArray& cntrlPnts);

	// Approximate curve with polyline
	McGePolyline2d(const McGeCurve2d& crv, double apprEps);

	// Interpolation data
	virtual int              numFitPoints() const;
	virtual McGePoint2d      fitPointAt(int idx) const;
	virtual McGeSplineEnt2d& setFitPointAt(int idx, const McGePoint2d& point);

	McGePolyline2d& operator = (const McGePolyline2d& pline);
};
//==============================================================================
