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

#include "mcgbl.h"

#ifdef _VERBOSEHEADERS_
#pragma message("Use " __FILE__)
#endif

class OdGeTol;

class McGeTol 
{
protected:
	double equVec, equPt;

public:
	MCGEL_API McGeTol(){
		setEqualPoint(1e-9);
		setEqualVector(1e-9);
	}

	MCGEL_API McGeTol(double ptTol, double vecTol){
		setEqualPoint(ptTol);
		setEqualVector(vecTol);
	}

	MCGEL_API double  equalPoint() const {
		return equPt;
	}

	MCGEL_API double  equalVector() const {
		return equVec;
	}

	// AcGe "забил" на проверку валидности аргументов, 
	// не будем ему уподобляться
	MCGEL_API void setEqualPoint( double val ) {
		equPt = val>=0 ? val : 0;
	}

	MCGEL_API void setEqualVector( double val ) {
		equVec = val>=0 ? val : 0;
	}

	operator const OdGeTol&() const
	{
		return *(OdGeTol*)this;
	}

	operator OdGeTol&()
	{
		return *(OdGeTol*)this;
	}

#ifdef MCGE_OD_SUPPORT
	McGeTol(const OdGeTol& src) : equPt(src.equalPoint()), equVec(src.equalVector())
	{
	}
#endif//#ifdef MCGE_OD_SUPPORT
};
