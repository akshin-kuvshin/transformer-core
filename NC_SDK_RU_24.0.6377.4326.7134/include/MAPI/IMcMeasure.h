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

#include "IMcObjects.h"

//===========================================================================
enum MeasureShema {
	kMcMeasureEmpty     = 0x00000000,     // ничего не измерено
	kMcMeasureProperty  = 0x00000001,     // значение свойства объекта
	kMcMeasureDistance  = 0x00000002,     // расстояние
	kMcMeasureAngle     = 0x00000004,     // угол
	kMcMeasurePerimeter = 0x00000008,     // периметр
	kMcMeasureArea      = 0x00000010,     // площадь
	kMcMeasureText      = 0x00000020,     // текстовое значение
	kMcMeasureCalc      = 0x00000040,     // вызвать калькулятор
	kMcMeasureNotes     = 0x00000080,     // вызвать записную книжку
	kMcMeasureAreaCpx   = 0x00000100,     // составная площадь
};
//===========================================================================
struct MeasureInfo
{
	MeasureShema    uShema;      // kMcMeasureEmpty если измерения отменены
	mcsWorkID       idObject;    // объект, с которого взято значение
	MCSVariant      Value;       // значение
	McsString       msProperty;  // имя свойства (только для uShema = kProperty)
	mcsPropertyType Type;        // тип свойства (только для uShema = kProperty)

	MeasureInfo()
	{
		uShema = kMcMeasureEmpty;
		Type = mcPropsNone;
	}
};

//===========================================================================
IMCS_DECL_INTERFACE(IMcMeasure, "{B25AB3EF-D84B-4706-A44A-862EA7402CB4}");

interface IMcMeasure : public IMcObject
{
public:
	virtual HRESULT setShema(IN DWORD Allowed,  // допустимые режимы
		IN MeasureShema Preffered) = 0;			// начальный режим
	virtual HRESULT setOwner(IN HWND Value) = 0;

		// Values of i3dMode:
		//   0 - measure mode will depend on the type of running up;
		//   +1 - 3d measurement mode only,
		//   -1 - 2d measurement mode only
	virtual HRESULT Execute(OUT double& Result, IN OPTIONAL LPCTSTR lpszPrompt = NULL, IN OPTIONAL int i3dMode = -1) = 0;
	virtual HRESULT ExecuteEx(OUT MeasureInfo& Info, IN OPTIONAL LPCTSTR lpszPrompt = NULL, IN OPTIONAL int i3dMode = -1) = 0;
};
//===========================================================================
