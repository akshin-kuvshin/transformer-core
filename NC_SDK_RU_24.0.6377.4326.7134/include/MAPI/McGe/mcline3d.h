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

#include "mclent3d.h"

//==============================================================================
class MCGEL_API McGeLine3d : public McGeLinearEnt3d
{
public:
	McGeLine3d();
	McGeLine3d(const McGeLine3d& line);
	McGeLine3d(const McGePoint3d& pnt, const McGeVector3d& vec);
	McGeLine3d(const McGePoint3d& pnt1, const McGePoint3d& pnt2);

		// The x-axis, y-axis, and z-axis lines.
	static const McGeLine3d kXAxis;
	static const McGeLine3d kYAxis;
	static const McGeLine3d kZAxis;

		// Set methods.
	virtual McGeLine3d& set(const McGePoint3d& pnt, const McGeVector3d& vec);
	virtual McGeLine3d& set(const McGePoint3d& pnt1, const McGePoint3d& pnt2);

		// Assignment operator.
	virtual McGeLine3d& operator = (const McGeLine3d& line);
};
//==============================================================================
