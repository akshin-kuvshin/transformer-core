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
#include "mcsent3d.h"

//==============================================================================
class MCGEL_API McGePolyline3d : public McGeSplineEnt3d
{
public:
	McGePolyline3d();
	McGePolyline3d(const McGePolyline3d& src);
	McGePolyline3d(const McGePoint3dArray& points);
	McGePolyline3d(const McGeKnotVector& knots, const McGePoint3dArray& cntrlPnts);

	// Approximate curve with polyline
	McGePolyline3d(const McGeCurve3d& crv, double apprEps);

	// Interpolation data
	virtual int              numFitPoints() const;
	virtual McGePoint3d      fitPointAt(int idx) const;
	virtual McGeSplineEnt3d& setFitPointAt(int idx, const McGePoint3d& point);

	McGePolyline3d& operator = (const McGePolyline3d& pline);
};
//==============================================================================
