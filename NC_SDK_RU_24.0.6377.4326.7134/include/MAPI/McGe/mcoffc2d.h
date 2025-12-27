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

//==============================================================================
class MCGEL_API McGeOffsetCurve2d : public McGeCurve2d
{
private:

	friend class McOffsetCurve2dImpl;
	McGeOffsetCurve2d();

public:
	McGeOffsetCurve2d(
		const McGeCurve2d& baseCurve,
		double offsetDistance);

	McGeOffsetCurve2d(const McGeOffsetCurve2d& offsetCurve);

	const McGeCurve2d*  curve() const;
	double              offsetDistance() const;
	bool                paramDirection() const;
	McGeMatrix2d        transformation() const;

	McGeOffsetCurve2d&  setCurve(const McGeCurve2d& baseCurve);
	McGeOffsetCurve2d&  setOffsetDistance(double offsetDistance);

	McGeOffsetCurve2d&  operator = (const McGeOffsetCurve2d& offsetCurve);
};
//==============================================================================
