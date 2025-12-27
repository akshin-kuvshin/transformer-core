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

#include "mclent2d.h"

//==============================================================================
class MCGEL_API McGeLine2d : public McGeLinearEnt2d
{
public:
	McGeLine2d();
	McGeLine2d(const McGeLine2d& line);
	McGeLine2d(const McGePoint2d& pnt, const McGeVector2d& vec);
	McGeLine2d(const McGePoint2d& pnt1, const McGePoint2d& pnt2);

	// The x-axis, y-axis, and z-axis lines.
	static const McGeLine2d kXAxis;
	static const McGeLine2d kYAxis;
	static const McGeLine2d kZAxis;

	// Set methods.
	virtual McGeLine2d& set(const McGePoint2d& pnt, const McGeVector2d& vec);
	virtual McGeLine2d& set(const McGePoint2d& pnt1, const McGePoint2d& pnt2);

	// Assignment operator.
	virtual McGeLine2d& operator = (const McGeLine2d& line);
};
//==============================================================================
