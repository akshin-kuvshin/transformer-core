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

//==============================================================================
class MCGEL_API McGeOffsetCurve3d : public McGeCurve3d
{
private:

	friend class McOffsetCurve3dImpl;
	McGeOffsetCurve3d();

public:
	McGeOffsetCurve3d (
		const McGeCurve3d& baseCurve,
		const McGeVector3d& planeNormal,
		double offsetDistance);

	McGeOffsetCurve3d (const McGeOffsetCurve3d& offsetCurve);

	const McGeCurve3d*  curve             () const;
	McGeVector3d        normal            () const; 
	double              offsetDistance    () const;
	bool                paramDirection    () const;
	McGeMatrix3d        transformation    () const;

	McGeOffsetCurve3d&  setCurve          (const McGeCurve3d& baseCurve);
	McGeOffsetCurve3d&  setNormal         (const McGeVector3d& planeNormal);
	McGeOffsetCurve3d&  setOffsetDistance (double offsetDistance);

		// tries to make a NURBs approximation for the contained offset curve;
		// a negative default tolerance means to choose it automatically;
		// it's initially 1e-3, like in Acad
	bool mcs_getAsNURBs(OUT McGeNurbCurve3d*& pApproxSpline, double dTol = -1) const;

	McGeOffsetCurve3d&  operator = (const McGeOffsetCurve3d& offsetCurve);
};
//==============================================================================
