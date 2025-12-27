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

#include "mcgblabb.h"

class McGeTol;
class McGeVector2d;
class McGeVector3d;
class McGePoint3d;
class McGePoint2d;

//==============================================================================

typedef McsArray<McGeVector3d, const McGeVector3d&>	McGeVector3dArray;
typedef McsArray<McGeVector2d, const McGeVector2d&>	McGeVector2dArray;
typedef McsArray<McGePoint3d, const McGePoint3d&>	McGePoint3dArray;
typedef McsArray<McGePoint2d, const McGePoint2d&>	McGePoint2dArray;
typedef McsArray<double, double> McGeDoubleArray;
typedef McsArray<int, int> McGeIntArray;
typedef McsArray<void*, void*> McGePVoidArray;

//==============================================================================

struct McGeContext
{
		// System wide default tolerance.
	MCGEL_API static McGeTol gTol;

		// tolerance for parametric 3D functionality
	MCGEL_API static McGeTol g3dTol;

	MCGEL_API static void (*gErrorFunc)();

		// Function to calculate a vector which is orthogonal to the given vector.
	MCGEL_API static void (*gOrthoVector)(const McGeVector3d&,McGeVector3d&);
};
//==============================================================================

template <class PointType>
bool addDistinctPoint(IN OUT McsArray<PointType>& pointsArr, const PointType& pt, const McGeTol& tol = McGeContext::gTol)
{
	for(int i = 0; i < pointsArr.GetSize(); ++i) {
		if(pointsArr[i].isEqualTo(pt, tol))
			return false;
	}
	pointsArr += pt;
	return true;
}
//==============================================================================

__inline double mcge_max_abs_3(double d1, double d2, double d3)
{
	double ad1 = fabs(d1);
	double ad2 = fabs(d2);
	double ad3 = fabs(d3);

	return max(ad1, max(ad2, ad3));
}
//==============================================================================

__inline double mcge_max_abs_2(double d1, double d2)
{
	double ad1 = fabs(d1);
	double ad2 = fabs(d2);

	return max(ad1, ad2);
}
//==============================================================================

MCGEL_API double EFF_TOL(double d, double tol_arg);
MCGEL_API double EFF_TOL2(double d1, double d2, double tol_arg, int nSignificantDecimalDigits = -1);
