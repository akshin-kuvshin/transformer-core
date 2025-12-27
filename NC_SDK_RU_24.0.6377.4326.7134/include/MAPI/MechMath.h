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

#include "MCSTypes.h"
#include <math.h>

#define EQU Equ

#ifndef SIGN
#define SIGN(x) (((x) >= 0) ? 1.0 : -1.0)
#endif

#ifndef A2R
#define A2R(x) ((x)*PI/180.0)
#endif

#ifndef R2A
#define R2A(x) ((x)*180.0/PI)
#endif

//---------------------------------------------------------------------------
#ifndef DEF_PRECISION
#define DEF_PRECISION	4
#endif

//---------------------------------------------------------------------------
static const int ROUND_FACTORS_COUNT = 15;
static const double round_factors[ROUND_FACTORS_COUNT] = // 0..14 знаков после запятой
{
	1., 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10, 1e-11, 1e-12, 1e-13, 1e-14
};

//---------------------------------------------------------------------------
inline int ToleranceToPrecision(double rTolerance)
{
	for (int i = 0; i < ROUND_FACTORS_COUNT; i++)
	{
		if (round_factors[i] == rTolerance)
			return i;
	}
	return -1;
}

//---------------------------------------------------------------------------
inline double PrecisionValue(int nPrecision)
{
	if (nPrecision >= 0 && nPrecision < ROUND_FACTORS_COUNT)
		return round_factors[nPrecision];
	return 1.0;
}

//---------------------------------------------------------------------------
inline double round(double rValue, int nPrecision)
{
	if (nPrecision < 0)
		return rValue; // Некорректное значение параметра. Ничего не делаем.
	if (nPrecision > ROUND_FACTORS_COUNT-1)
		return rValue; // Нет смысла округлять double до 15-го знака и дальше. Ничего не делаем.

	// #15076. Дополнение к табличному калькулятору.
	// Особенности машинного представления вещественных чисел, когда, например, 0.005 представляется, как 0.0049999999999999
	// Для решения увеличиваем исходное число на 1E-15.

#if _MSC_VER < 1800 // до VS2013 не было библиотечной функции round
	if (rValue >= 0)
		return floor((rValue + 1E-15) / round_factors[nPrecision] + 0.5) * round_factors[nPrecision];
	else
		return ceil((rValue - 1E-15) / round_factors[nPrecision] - 0.5) * round_factors[nPrecision];
#else
	return round((rValue + SIGN(rValue)*1E-15) / round_factors[nPrecision]) * round_factors[nPrecision];
#endif
}
#if _MSC_VER < 1800 // до VS2013 не было библиотечной функции round
inline double round(double rValue)
{
	return round(rValue, 0);
}
#endif

//---------------------------------------------------------------------------
inline double ln(double operand) { return log(operand); }
inline double lg(double operand) { return log10(operand); }
inline double log(double arg, double base) { return log(arg)/log(base); }
#if _MSC_VER < 1930
inline double log2(double operand)
{
	return log(operand)/0.69314718055995;//log(2.0);
}
#endif

//---------------------------------------------------------------------------
inline bool Equ(double r1, double r2, double rTolerance = DEF_TOL)
{
	return (fabs(r2-r1) <= rTolerance) ? TRUE : FALSE;
}

//---------------------------------------------------------------------------
inline double NormalizeAngle2PI(double rA) {
  while(rA > PI2) rA -= PI2;
  while(rA < 0) rA += PI2;
  return rA;
}

//---------------------------------------------------------------------------
inline double NormalizeAnglePI(double rA) {
  while(rA > PI) rA -= PI2;
  while(rA < -PI) rA += PI2;
  return rA;
}

//---------------------------------------------------------------------------
inline double CalcDAngle(double rA1, double rA2) {
  double rAngle = NormalizeAngle2PI(rA2 - rA1);
  if(rAngle > PI)
    rAngle = fabs(PI * 2 - rAngle);
  return min(rAngle, fabs(PI - rAngle));
}

//---------------------------------------------------------------------------
inline double CalcDAngleClockwise(double rStart, double rEnd)
{
  return NormalizeAngle2PI(rEnd >= rStart ? rEnd - rStart : PI2 - (rStart - rEnd));
}
//---------------------------------------------------------------------------
