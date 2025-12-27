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

#include "IMcs.h"
#include "IContext.h"
#include "cmnmacro.h"

//----------------------------------------
enum McsNativeLineTypeEnum
{
	NLT_SYSTEM_BYOBJECT = -1,                    // Эквивалент BYOBJECT. Можно использовать при объединении системных и встроенных типов линий в одном параметре.
	NLT_BYOBJECT = 0,                            // тип линии по объекту
	//---------------------------------------------------------------------------------------------
	// PlanTracer::Ограждения
	//---------------------------------------------------------------------------------------------
	NLT_BORDER_NO_BARRIER,                       // без ограждения
	NLT_BORDER_ROCK_LESS_ONE_METER,              // каменные, железобетонные выстой менее 1м
	NLT_BORDER_ROCK_MORE_ONE_METER,              // каменные, железобетонные выстой от 1м и выше
	NLT_BORDER_BRICK_MORE_ONE_METER,             // кирпичные выстой от 1м и выше
	NLT_BORDER_METAL_FULL,                       // металлические
	NLT_BORDER_METAL_ON_ROCK_FOUNDATION,	     // металлические на каменном фундаменте
	NLT_BORDER_METAL_ON_BRICK_FOUNDATION,        // металлические на кирпичном фундаменте
	NLT_BORDER_METAL_ON_ROCK_COLUMN,             // металлические на каменных столбах
	NLT_BORDER_METAL_ON_BRICK_COLUMN,            // металлические на кирпичных столбах
	NLT_BORDER_WOOD_FULL,                        // деревянные
	NLT_BORDER_WOOD_ON_ROCK_FOUNDATION,          // деревянные на каменном фундаменте
	NLT_BORDER_WOOD_ON_BRICK_FOUNDATION,         // деревянные на кирпичном фундаменте
	NLT_BORDER_WOOD_ON_ROCK_COLUMN,              // деревянные на каменных или железобетонных столбах
	NLT_BORDER_WOOD_ON_BRICK_COLUMN,             // деревянные на кирпичных столбах
	NLT_BORDER_WICKER_FENCE,                     // плетень
	NLT_BORDER_WICKER_FENCE_BARBED_WIRE,         // плетень из колючей проволоки
	NLT_BORDER_WICKER_FENCE_WIRE_FABRIC,         // плетень из проволочной сетки
	//---------------------------------------------------------------------------------------------
	// PlanTracer::Линейные объекты
	//---------------------------------------------------------------------------------------------
	NLT_LINEOBJECT_CABLE_ELINE_HIGH_VOLTAGE,     // кабельная ЛЭП высокого напряжения
	NLT_LINEOBJECT_CABLE_ELINE_LOW_VOLTAGE,      // кабельная ЛЭП низкого напряжения
	NLT_LINEOBJECT_AIR_ELINE_HIGH_VOLTAGE,       // воздушная ЛЭП высокого напряжения
	NLT_LINEOBJECT_AIR_ELINE_LOW_VOLTAGE,        // воздушная ЛЭП низкого напряжения
	NLT_LINEOBJECT_WATER_PIPELINE_GROUND,        // водопровод наземный
	NLT_LINEOBJECT_WATER_PIPELINE_UNDERGROUND,   // водопровод подземный
	NLT_LINEOBJECT_GAS_PIPELINE_GROUND,          // газопровод наземный
	NLT_LINEOBJECT_GAS_PIPELINE_UNDERGROUND,     // газопровод подземный
	NLT_LINEOBJECT_DRAINAGE_GROUND,              // канализация наземная
	NLT_LINEOBJECT_DRAINAGE_UNDERGROUND,         // канализация подземная
	NLT_LINEOBJECT_DRAINAGE_GULLEY,              // канализация ливневая
	NLT_LINEOBJECT_HOT_WATER_PIPELINE,           // теплотрасса (прямая и обратная трубы)
	NLT_LINEOBJECT_OIL_PIPELINE,                 // нефтепровод
	NLT_LINEOBJECT_BOX,                          // короб
	NLT_LINEOBJECT_CHANNEL,                      // канал
	NLT_LINEOBJECT_TRESTLEWORK_ON_PAIR_CONCRETES,// эстакада на спаренных железобетонных опорах
	NLT_LINEOBJECT_AIR_COMMUNICATION_LINE,       // воздушная проводная линия связи
	NLT_LINEOBJECT_DOUBLE_LINE,                  // двойная линия
	NLT_LINEOBJECT_TWO_DOUBLE_LINES,             // две двойных линий
	NLT_LINEOBJECT_CASING,                       // футляр
	NLT_LINEOBJECT_DRAIN_PIPE,                   // дренажная труба
	NLT_LINEOBJECT_DRAIN_NETWORK,                // дренажная сеть
	NLT_LINEOBJECT_DRAIN_BOOT,                   // лоток (вотдосточной трубы)
	NLT_LINEOBJECT_SLOPE,                        // откос
	NLT_LINEOBJECT_WATER_PIPELINE_DRINKABLE,     // водопровод питьевой
	NLT_LINEOBJECT_WATER_PIPELINE_TECHNICAL,     // водопровод технический
	NLT_LINEOBJECT_WATER_PIPELINE_ECONOMIC,      // водопровод хозяйственный
	NLT_LINEOBJECT_DRAINAGE_DOMESTIC,            // канализация бытовая
	NLT_LINEOBJECT_DRAINAGE_PRESSURE,            // канализация напорная
	//---------------------------------------------------------------------------------------------
	// ППР::Линейные объекты
	//---------------------------------------------------------------------------------------------
	NLT_PPR_IRON_ROAD_CONSTANT,                  // железные дороги постоянные
	NLT_PPR_IRON_ROAD_RAISED,                    // железные дороги возводимые
	NLT_PPR_IRON_ROAD_TEMPORAL,                  // железные дороги временные
	NLT_PPR_IRON_ROAD_REMOVED,                   // железные дороги сносимые
	NLT_PPR_ELINE_TEMPORAL_AIR_HIGH_TOWER,       // временные ЛЭП воздушные на высоких опорах
	NLT_PPR_ELINE_TEMPORAL_GROUND,               // временные ЛЭП наземные
	NLT_PPR_ELINE_TEMPORAL_UNDERGROUND,          // временные ЛЭП подземные
	NLT_PPR_ELINE_GROUND_CONTOUR,                // контур заземления
	NLT_PPR_ELINE_CONNECT_CONDUCTOR,             // соединительные проводники
	NLT_PPR_WATER_PIPELINE_TEMPORAL_ECONOMIC,    // временная сеть хозяйственно-бытового водоснабжения
	NLT_PPR_WATER_PIPELINE_INDUSTRIAL,           // сеть производственного водоснабжения
	NLT_PPR_WATER_PIPELINE_CONSTANT,             // постоянная сеть водопровода
	NLT_PPR_WATER_PIPELINE_HOT_CONSTANT,         // постоянная сеть горячего водоснабжения
	NLT_PPR_WATER_PIPELINE_HOT_INDUSTRIAL,       // производственная сеть горячего водоснабжения
	NLT_PPR_DRAINAGE_TEMPORAL,                   // канализация временная
	NLT_PPR_DRAINAGE_INDUSTRIAL,                 // канализация производственная
	NLT_PPR_DRAINAGE_CONSTANT,                   // постоянная сеть канализации
	NLT_PPR_DRAINAGE_GULLEY,                     // канализация ливневая
	NLT_PPR_FIRE_CONTROL_TEMPORAL_NETWORK,       // временная противопожарная сеть
	NLT_PPR_BORDER_CONSTANT,                     // ограждение постоянное
	NLT_PPR_BORDER_RAISED,                       // ограждение возводимое
	NLT_PPR_BORDER_TEMPORAL,                     // ограждение временное
	NLT_PPR_BORDER_INVENTORY,                    // ограждение инвентарное
	NLT_PPR_BORDER_REMOVED,                      // ограждение сносимое
	NLT_PPR_BORDER_GROOVED,                      // ограждение шпунтовое
	NLT_PPR_TECHNICS_CRANE_ZONE_WARNING_LINE,    // линия предупреждения об ограничении зоны действия крана
	NLT_PPR_TECHNICS_CRANE_ZONE_LIMITING_LINE,   // линия ограничения зоны действия крана
	NLT_PPR_TECHNICS_MACHINE_WORKING_TRAVEL,     // рабочий ход машины
	NLT_PPR_TECHNICS_MACHINE_IDLING_TRAVEL,      // холостой ход машины
	NLT_PPR_TECHNICS_UNDERCRANE_LINES,           // пути подкрановые
	//---------------------------------------------------------------------------------------------
	// Инженерные сети
	//---------------------------------------------------------------------------------------------
	NLT_ENGINEER_TEXT_LINE,                      // линия с текстом
	NLT_ENGINEER_WIDTH_LINE,                     // линия с шириной
	NLT_ENGINEER_WIDTH_ROUND_LINE,               // линия с шириной скругленная
	//---------------------------------------------------------------------------------------------
	NLT_PPR_DRAINAGE_DITCH,                      // дренажная канава
	NLT_PPR_NEEDLE_FILTER,                       // иглофильтр
	NLT_PPR_CONCRETE_BREEDER,                    // бетоновод
	NLT_PPR_SIGNAL_FENCE,                        // сигнальное ограждение
	NLT_PPR_DISMANTLING_OBJECT,                  // объект демонтажа
	//---------------------------------------------------------------------------------------------
	NLT_MAX_INDEX,                               // добавлять новые типы до этой метки
	//---------------------------------------------------------------------------------------------
};

//----------------------------------------
__inline bool IsValidNativeLinetype(int idNLT)
{
	if (idNLT > NLT_BYOBJECT && idNLT < NLT_MAX_INDEX)
	{
		// Игнорируем типы инженерных сетей
		switch (idNLT)
		{
			case NLT_ENGINEER_TEXT_LINE:
			case NLT_ENGINEER_WIDTH_LINE:
			case NLT_ENGINEER_WIDTH_ROUND_LINE:
				return false;

			default:
				return true;
		}
	}
	return false;
}

//----------------------------------------
enum LineTypeActiveSideEnum
{
	asLeft = 0,
	asRight
};

//----------------------------------------
enum MeasureParamTypeEnum
{
	mt_Undefined = 0,		// неизвестная величина, double
	mt_Angular,				// угловая величина, double
	mt_Linear_Design,		// линейная величина, управляется масштабом оформления, double
	mt_Linear_Measure,		// линейная величина, управляется масштабом измерений, double
	mt_Bool,				// булевая величина, bool
	mt_Enum,				// индекс, задающий позицию из списка, int
	mt_Integer,				// целочисленная величина, int
	mt_Color,				// цвет, редактируется через выпадающий список ColorComboBox, int
	mt_LineWeight,			// толщина линии, редактируется через выпадающий список LineWeightComboBox, int
	mt_String,				// строка, string
	mt_TextStyle,			// текстовый стиль, редактируется через выпадающий список TextStyleComboBox, string
	mt_TextHorzAlign,		// горизонтальное выравнивание текста, редактируется через выпадающий список, int
	mt_TextVertAlign,		// вертикальное выравнивание текста, редактируется через выпадающий список, int
};

//----------------------------------------
enum LineTypeParamEnum
{
	LTPAR_UNDEFINED = 0,
	LTPAR_PPR_IRONROAD_WIDTH,						// Ж\Д : Ширина железной дороги
	LTPAR_PPR_IRONROAD_BEND_RADIUS,					// Ж\Д : радиус закругления железной дороги
	LTPAR_PPR_BORDER_STROKE_HEIGHT,					// ОГРАЖДЕНИЯ : Высота штрихов
	LTPAR_PPR_BORDER_STROKE_STEP,					// ОГРАЖДЕНИЯ : Шаг штрихов
	LTPAR_PPR_BORDER_SOLID_DASH_LINES_DISTANCE,		// ОГРАЖДЕНИЯ : Расстояние между сплошной и штриховой линиями
	LTPAR_PPR_BORDER_GROOVE_WIDTH,					// ОГРАЖДЕНИЯ : Ширина шпунта
	LTPAR_PPR_BORDER_GROOVE_LENGTH,					// ОГРАЖДЕНИЯ : Длина шпунта
	LTPAR_PPR_BORDER_GROOVE_STEP,					// ОГРАЖДЕНИЯ : Ширина шпунта
	LTPAR_PPR_UNDERCRANE_LINES_WIDTH,				// ПУТИ ПОДКРАНОВЫЕ : Ширина путей
	LTPAR_PPR_UNDERCRANE_LINES_BEND_RADIUS,			// ПУТИ ПОДКРАНОВЫЕ : радиус закругления путей
	LTPAR_PPR_UNDERCRANE_LINES_STOP_LENGTH,			// ПУТИ ПОДКРАНОВЫЕ : Длина упора
	LTPAR_PPR_UNDERCRANE_LINES_STOP_WIDTH,			// ПУТИ ПОДКРАНОВЫЕ : Ширина упора
	LTPAR_PPR_MACHINE_TRAVEL_ARROW_STEP,			// ХОД МАШИНЫ : Шаг стрелки
	LTPAR_PPR_MACHINE_TRAVEL_ARROW_LENGTH,			// ХОД МАШИНЫ : Длина стрелки
	LTPAR_PPR_MACHINE_TRAVEL_ARROW_ANGLE,			// ХОД МАШИНЫ : Угол стрелки
	LTPAR_PPR_ELINE_SOLID_DASH_LINES_DISTANCE,		// ВРЕМЕННЫЕ ЛЭП НАЗЕМНЫЕ : Расстояние между сплошной и штриховой линиями
	LTPAR_PPR_ELINE_GROUND_CONTOUR_LONG_SIZE,		// КОНТУР ЗАЗЕМЛЕНИЯ : Длина длинного штриха
	LTPAR_PPR_ELINE_GROUND_CONTOUR_SPACE_SIZE,		// КОНТУР ЗАЗЕМЛЕНИЯ : Длина промежутка
	LTPAR_PPR_ELINE_GROUND_CONTOUR_POINT_DIAM,		// КОНТУР ЗАЗЕМЛЕНИЯ : Диаметр точки
	LTPAR_PPR_ELINE_GROUND_CONTOUR_OBLIQUE_SIZE,	// КОНТУР ЗАЗЕМЛЕНИЯ : Высота наклонной черты
	LTPAR_PPR_ELINE_CONNECT_CONDUCTOR_LONG_SIZE,	// СОЕДИНИТЕЛЬНЫЕ ПРОВОДНИКИ : Длина длинного штриха
	LTPAR_PPR_ELINE_CONNECT_CONDUCTOR_SPACE_SIZE,	// СОЕДИНИТЕЛЬНЫЕ ПРОВОДНИКИ : Длина промежутка
	LTPAR_PPR_ELINE_CONNECT_CONDUCTOR_SHORT_SIZE,	// СОЕДИНИТЕЛЬНЫЕ ПРОВОДНИКИ : Длина короткого штриха
	LTPAR_PPR_ELINE_CONNECT_CONDUCTOR_OBLIQUE_SIZE,	// СОЕДИНИТЕЛЬНЫЕ ПРОВОДНИКИ : Высота наклонной черты
	LTPAR_PPR_CRANE_ZONE_WARNING_LINE_STEP,			// ЛИНИЯ ПРЕДУПРЕЖДЕНИЯ ОБ ОГРАНИЧЕНИИ ЗОНЫ ДЕЙСТВИЯ КРАНА : Шаг
	LTPAR_PPR_CRANE_ZONE_WARNING_LINE_BOUND,		// ЛИНИЯ ПРЕДУПРЕЖДЕНИЯ ОБ ОГРАНИЧЕНИИ ЗОНЫ ДЕЙСТВИЯ КРАНА : Расстояние от края линии до крайнего знака
	LTPAR_PPR_CRANE_ZONE_WARNING_LINE_SIGN_SIZE,	// ЛИНИЯ ПРЕДУПРЕЖДЕНИЯ ОБ ОГРАНИЧЕНИИ ЗОНЫ ДЕЙСТВИЯ КРАНА : Размер знака
	LTPAR_PPR_CRANE_ZONE_LIMITING_LINE_STEP,		// ЛИНИЯ ОГРАНИЧЕНИЯ ЗОНЫ ДЕЙСТВИЯ КРАНА : Шаг
	LTPAR_PPR_CRANE_ZONE_LIMITING_LINE_BOUND,		// ЛИНИЯ ОГРАНИЧЕНИЯ ЗОНЫ ДЕЙСТВИЯ КРАНА : Расстояние от края линии до крайнего знака
	LTPAR_PPR_CRANE_ZONE_LIMITING_LINE_SIGN_SIZE,	// ЛИНИЯ ОГРАНИЧЕНИЯ ЗОНЫ ДЕЙСТВИЯ КРАНА : Размер знака
	LTPAR_PPR_UNDERCRANE_LINES_DRAW_AXIS,			// ПУТИ ПОДКРАНОВЫЕ : Отображать центральную осевую линию
	LTPAR_PPR_BORDER_REMOVED_CROSS_STEP,			// ОГРАЖДЕНИЯ СНОСИМЫЕ : Шаг крестов
	LTPAR_PPR_BORDER_REMOVED_CROSS_HEIGHT,			// ОГРАЖДЕНИЯ СНОСИМЫЕ : Высота крестов
	LTPAR_ENGINEER_TEXT_LINE_TEXT,					// ЛИНИЯ С ТЕКСТОМ : Текст
	LTPAR_ENGINEER_TEXT_LINE_HEIGHT,				// ЛИНИЯ С ТЕКСТОМ : Высота текста
	LTPAR_ENGINEER_TEXT_LINE_STEP,					// ЛИНИЯ С ТЕКСТОМ : Шаг текста
	LTPAR_ENGINEER_TEXT_LINE_STYLE,					// ЛИНИЯ С ТЕКСТОМ : Текстовый стиль
	LTPAR_ENGINEER_TEXT_LINE_COLOR,					// ЛИНИЯ С ТЕКСТОМ : Цвет текста
	LTPAR_ENGINEER_TEXT_LINE_LINEWEIGHT,			// ЛИНИЯ С ТЕКСТОМ : Толщина текста
	LTPAR_ENGINEER_TEXT_LINE_ALIGNMENT,				// ЛИНИЯ С ТЕКСТОМ : Выравнивание текста
	LTPAR_ENGINEER_WIDTH_LINE_WIDTH,				// ЛИНИЯ С ШИРИНОЙ : Ширина
	LTPAR_ENGINEER_WIDTH_LINE_SHOW_AXIS,			// ЛИНИЯ С ШИРИНОЙ : Осевая линия (показывать\нет)
	LTPAR_ENGINEER_WIDTH_LINE_AXIS_ALIGN,			// ЛИНИЯ С ШИРИНОЙ : Привязка осевой линии
	LTPAR_ENGINEER_WIDTH_ROUND_LINE_WIDTH,			// ЛИНИЯ С ШИРИНОЙ СКРУГЛЕННАЯ : Ширина
	LTPAR_ENGINEER_WIDTH_ROUND_LINE_SHOW_AXIS,		// ЛИНИЯ С ШИРИНОЙ СКРУГЛЕННАЯ : Осевая линия (показывать\нет)
	LTPAR_ENGINEER_WIDTH_ROUND_LINE_AXIS_ALIGN,		// ЛИНИЯ С ШИРИНОЙ СКРУГЛЕННАЯ : Привязка осевой линии
	LTPAR_ENGINEER_WIDTH_ROUND_LINE_INTERNAL_R,		// ЛИНИЯ С ШИРИНОЙ СКРУГЛЕННАЯ : Внутренний радиус скругления
	LTPAR_PPR_NEEDLE_FILTER_STROKES_HEIGHT,			// ИГЛОФИЛЬТР : Высота штриха
	LTPAR_PPR_NEEDLE_FILTER_CIRCLE_DIAMETER,		// ИГЛОФИЛЬТР : Диаметр окружности
	LTPAR_PPR_NEEDLE_FILTER_STEP,					// ИГЛОФИЛЬТР : Шаг фильтров
	LTPAR_PPR_NEEDLE_FILTER_BOUND_SIZE,				// ИГЛОФИЛЬТР : Расстояние до крайнего фильтра
	LTPAR_PPR_NEEDLE_FILTER_LINES_DISTANCE,			// ИГЛОФИЛЬТР : Расстояние между линиями
	LTPAR_PPR_CONCRETE_BREEDER_LINES_DISTANCE,		// БЕТОНОВОД : Расстояние между линиями
	LTPAR_PPR_SIGNAL_FENCE_CIRCLE_DIAMETER,			// СИГНАЛЬНОЕ ОГРАЖДЕНИЕ : Диаметр окружности
	LTPAR_PPR_SIGNAL_FENCE_CIRCLE_STEP,				// СИГНАЛЬНОЕ ОГРАЖДЕНИЕ : Расстояние между окружностями
	LTPAR_PPR_DISMANTLING_OBJECT_CROSS_LENGTH,		// ОБЪЕКТ ДЕМОНТАЖА : Длина линий креста
	LTPAR_PPR_DISMANTLING_OBJECT_CROSS_STEP,		// ОБЪЕКТ ДЕМОНТАЖА : Шаг крестов
	LTPAR_UNDEFINEDMAX
};

enum PointTypeParamEnum;

//----------------------------------------
// Параметр встроенных типов линий\точечных обозначений
//----------------------------------------
class McNativeParam
{
public:
	__declspec(property(get = getValue, put = setValue)) MCSVariant Value;
	__declspec(property(get = getMeasureType)) MeasureParamTypeEnum typeMeasure;
	__declspec(property(get = getParamType))  int typeParam;
	__declspec(property(get = getLParamType)) LineTypeParamEnum typeLParam;
	__declspec(property(get = getPParamType)) PointTypeParamEnum typePParam;

private:
	MCSVariant m_Value;
	MeasureParamTypeEnum m_typeMeasure;
	union
	{
		int                m_typeParam;
		LineTypeParamEnum  m_typeLParam;
		PointTypeParamEnum m_typePParam;
	};

public:
	McNativeParam()
	{
		m_typeParam   = LTPAR_UNDEFINED;
		m_typeMeasure = mt_Undefined;
		m_Value = 0.0;
	}
	McNativeParam(int typeParam)
	{
		m_typeParam   = typeParam;
		m_typeMeasure = mt_Undefined;
		m_Value = 0.0;
	}
	McNativeParam(int typeParam, MeasureParamTypeEnum typeMeasure, const MCSVariant& Value)
	{
		m_typeParam   = typeParam;
		m_typeMeasure = typeMeasure;
		setValue(Value);
	}
	McNativeParam(const McNativeParam& param)
	{
		*this = param;
	}
	McNativeParam& operator = (const McNativeParam& param)
	{
		if (&param == this)
			return *this;
		m_typeParam   = param.typeParam;
		m_typeMeasure = param.typeMeasure;
		m_Value       = param.m_Value;
		return *this;
	}
	bool operator == (const McNativeParam& param) const
	{
		return typeParam == param.typeParam;
	}
	bool operator != (const McNativeParam& param) const
	{
		return typeParam != param.typeParam;
	}
	bool operator > (const McNativeParam& param) const
	{
		return typeParam > param.typeParam;
	}
	bool operator < (const McNativeParam& param) const
	{
		return typeParam < param.typeParam;
	}

	//----------------------------------------
	MeasureParamTypeEnum getMeasureType() const
	{
		return m_typeMeasure;
	}

	//----------------------------------------
	int getParamType() const
	{
		return m_typeParam;
	}
	LineTypeParamEnum getLParamType() const
	{
		return m_typeLParam;
	}
	PointTypeParamEnum getPParamType() const
	{
		return m_typePParam;
	}

	//----------------------------------------
	const MCSVariant& getValue() const
	{
		return m_Value;
	}
	const MCSVariant& setValue(const MCSVariant& Value)
	{
		switch (typeMeasure)
		{
			case mt_Undefined:
			case mt_Angular:
			case mt_Linear_Design:
			case mt_Linear_Measure:
				m_Value = (double)Value;
			break;
			
			case mt_Bool:
				m_Value = (bool)Value;
			break;
			
			case mt_Enum:
			case mt_Integer:
			case mt_Color:
			case mt_LineWeight:
			case mt_TextHorzAlign:
			case mt_TextVertAlign:
				m_Value = (int)Value;
			break;
			
			case mt_String:
			case mt_TextStyle:
				m_Value = (LPCTSTR)Value;
			break;
		}
		return m_Value;
	}

	//----------------------------------------
	double getDoubleValue() const
	{
		switch (typeMeasure)
		{
			case mt_Undefined:
			case mt_Angular:
			case mt_Linear_Design:
			case mt_Linear_Measure:
				return (double)m_Value;
		}
		return 0.0;
	}
	int getIntValue() const
	{
		switch (typeMeasure)
		{
			case mt_Enum:
			case mt_Integer:
			case mt_Color:
			case mt_LineWeight:
			case mt_TextHorzAlign:
			case mt_TextVertAlign:
				return (int)m_Value;
		}
		return 0;
	}
	bool getBoolValue() const
	{
		if (mt_Bool == typeMeasure)
			return (bool)m_Value;
		return false;
	}
	McsString getStringValue() const
	{
		switch (typeMeasure)
		{
			case mt_String:
			case mt_TextStyle:
				return (LPCTSTR)m_Value;
		}
		return _T("");
	}

	//----------------------------------------
	void setValue(double rValue)
	{
		switch (typeMeasure)
		{
			case mt_Undefined:
			case mt_Angular:
			case mt_Linear_Design:
			case mt_Linear_Measure:
				m_Value = rValue;
			break;
		}
	}
	void setValue(int nValue)
	{
		switch (typeMeasure)
		{
			case mt_Enum:
			case mt_Integer:
			case mt_Color:
			case mt_LineWeight:
			case mt_TextHorzAlign:
			case mt_TextVertAlign:
				m_Value = nValue;
			break;
		}
	}
	void setValue(bool bValue)
	{
		if (mt_Bool == typeMeasure)
			m_Value = bValue;
	}
	void setValue(LPCTSTR pszValue)
	{
		switch (typeMeasure)
		{
			case mt_String:
			case mt_TextStyle:
				if (NULL == pszValue)
					m_Value = _T("");
				else
					m_Value = pszValue;
			break;
		}
	}
};
typedef McsArray <McNativeParam, const McNativeParam&> McNativeParamArray;

//----------------------------------------
struct IMcNativeLineTypeMaker : public virtual IMcObject
{
public:
	IMCS_STD_METHOD_DEFINITION(IMcNativeLineTypeMaker, IMcObject)

	// Инициализация
	virtual HRESULT Init(IMcGeometryBuilder *p2dGeometry,
						McsNativeLineTypeEnum lineType,
						double rScale = 1.0,
						double rDScale = 1.0, 
						int nGSMarkerStart = 2048,
						LineTypeActiveSideEnum ltActiveSide = asLeft) // для ассиметричных типов
	{ return E_NOTIMPL; }

	// Черчение
	virtual bool DrawLine(const mcsPoint& pt1, const mcsPoint& pt2) { return false; }
	virtual bool DrawLine(const mcsLineSeg& linePath) { return false; }
	virtual bool DrawArc(const mcsCircArc& arcPath) { return false; }
	virtual bool DrawPolyline(const mcsPolyline& polyPath, mcsPolylineArray* pArrCutContours = NULL) { return false; }

	// Параметры (без учета масштаба)
	virtual bool GetNLParameters(McNativeParamArray& arrParams) const { return false; }
	virtual bool SetNLParameters(const McNativeParamArray& arrParams) { return false; }

	// Толщина линии (с учетом масштаба)
	virtual double GetNLThickness() const { return 0; }

	// Растояние от осевой для расчета положения привязок (с учетом масштаба)
	virtual double GetNLSnapOffset() const { return 0; }

	// Вспомогательная информация о типах линий
	virtual McsString GetNLName(McsNativeLineTypeEnum lineType) const { return _T(""); }
	virtual COLORREF  GetNLColor(McsNativeLineTypeEnum lineType) const { return 0; }
	virtual bool      IsNLAssymetrical(McsNativeLineTypeEnum lineType) const { return false; }

	// Угол для подрезки фаски между соседними участками дли типов с шириной (0 - запрет на фаску)
	virtual HRESULT SetChamferAngle(double rAngle) = 0;
	virtual double  GetChamferAngle() const = 0;
};

//----------------------------------------
IMCS_DECL_INTERFACE(IMcPathEntity,	"D88C051E-08A6-44D4-8D87-88519E6EB97F")
IMCS_DECL_INTERFACE(IMcCustomSink,	"58F2BAB0-591A-4834-846F-FC46F925EED4")

//----------------------------------------
// Интерфейс, через который IMcBaseLongObjectAssistant может получать полилинию для выполнения операции "Offset".
// Интерфейс для определения протяженного объекта
// Пример использования - маркировка трасс
//----------------------------------------
struct IMcPathEntity : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcPathEntity);
	IMCS_QI_METHOD_DEFINITION(IMcPathEntity, IMcObject);

	virtual HRESULT GetEntityPath(mcsPolyline& path) const = 0;
};

//----------------------------------------
//	Расширение штатной команды вставки
//----------------------------------------
struct IMcCustomSink : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcCustomSink);
	IMCS_QI_METHOD_DEFINITION(IMcCustomSink, IMcObject);

//	Пост-вызов по завершению каждого ActiveEnt
	virtual HRESULT OnActiveEnt(const EM_Entity& ent, bool& fHighlight) { return E_NOTIMPL; }
//	Пост-вызов по завершению каждого GetEntity, вернувшего S_OK
	virtual HRESULT OnGetEntity(const EM_Entity& ent) { return E_NOTIMPL; }

// 	Расширение опции "Offset\Отступ" в команде вставки.
// 	По умолчанию работает только от полилинии и от объектов, унаследованных от IMcNativeLongObject.
// 	arrOffsetObjTypes - ClassIDs объектов, от которых можно строить объект с отступом
// 					  - переданные классы должны поддерживать один из интерфейсов:
// 						IMcPolyline
// 						IMcNativeLongObject
// 						IMcAreaEntity
// 						IMcContourEntity
// 	sOffsetPrompt     - Приглашание пользователю в командной строке
	virtual HRESULT GetOffsetTypes(mcsGUIDArray& arrTypes) const { return E_NOTIMPL; }
	virtual HRESULT GetOffsetPrompt(McsString& sPrompt)    const { return E_NOTIMPL; }

	// Передача флагов EM_Params.dwFlags
	virtual DWORD GetSinkFlags() const { return 0; }
};

//----------------------------------------
// Ассистент базового "длинного" объекта
//----------------------------------------
struct IMcBaseLongObjectAssistant : public IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcBaseLongObjectAssistant)
	IMCS_STD_METHOD_DEFINITION(IMcBaseLongObjectAssistant, IMcObject)

	// Assist LongObject
	//----------------------------------------
	virtual HRESULT SetLongObject(IMcCdEntity* pAssistedLongObject) = 0;
	virtual IMcCdEntityPtr GetLongObject() const = 0;

	// IMcEntity redirected methods
	//----------------------------------------
	virtual HRESULT onDraw(IMcGeometryBuilder *pG) = 0;
	virtual HRESULT onTransform(IN const mcsMatrix& tfm) = 0;
	virtual HRESULT getBoundingBox(OUT mcsBoundBlock &box) const = 0;
	virtual HRESULT getCompoundBounds(mcsBoundBlocksArray& blocks) const = 0;
	virtual HRESULT onGetGripPoints(mcsPoint3dArray& gripPoints, bool bStretch) const = 0;
	virtual HRESULT onMoveGripPointsAt(const mcsIntArray& indices, const mcsVector3d& offset, bool bStretch) = 0;
	virtual HRESULT onGetGripPoints(McGripDataPtrArray& grips, double rViewUnitSize, int iGripSize, const mcsVector& vecViewDir, int iFlags) const = 0;
	virtual HRESULT onMoveGripPointsAt(const McGripDataPtrArray& grips, const mcsVector& offset, int iFlags) = 0;
	virtual HRESULT onGetOsnapPoints(McOsnapMode osnapMode, const mcsPoint3d& pickPoint, const mcsPoint3d& lastPoint, mcsPoint3dArray& snapPoints) const = 0;
	virtual HRESULT onEdit(IN const mcsPoint3d& pnt, long lFlag = 0) = 0;
	virtual HRESULT onWrite(OUT IMcsStream* pStream) const = 0;
	virtual HRESULT onRead(IN IMcsStream* pStream) = 0;
	virtual HRESULT getAsPrimitive(OUT McsEntityGeometry& primitive, OUT mcsWorkIDArray* pidsOnPrimitive = NULL) = 0;
	virtual HRESULT setAsPrimitive(IN const McsEntityGeometry& primitive, IN const mcsWorkIDArray* pidsOnPrimitive = NULL) = 0;
	virtual HRESULT getParamAtPoint(OUT McGeometryParam& param, IN const mcsPoint& pnt) const = 0;
	virtual HRESULT getPointAtParam(OUT mcsPoint& pnt, IN const McGeometryParam& param, OUT OPTIONAL McsEntityGeometry* pSimpleEnt = NULL) const = 0;
	virtual HRESULT onReactor(IMcDbObject *pObj, mcReactorsType action) = 0;
	virtual HRESULT onEvent(IMcEventType event, mcsExValueArray *pAdditionalParameters = NULL) = 0;
	virtual HRESULT onErase() = 0;
	virtual HRESULT placeObject(long lInsertType = kMcPlace_Normal, mcsExValueArray *pAdditionalParameters = NULL, IMcCustomSink* pCustomSink = NULL) = 0;
	virtual HRESULT getProperties(mcsStringArray& props) = 0;
	virtual HRESULT getProperty(const McsString& stName, MCSVariant& data) = 0;
	virtual HRESULT setProperty(const McsString& stName, const MCSVariant& data) = 0;
	virtual HRESULT getPropertyInfo(const McsString& stName, OUT McPropertyInfo& info) = 0;

	// Polyline
	//----------------------------------------
	virtual HRESULT SetPolyline(const mcsPolyline& poly) = 0;
	virtual HRESULT GetPolyline(mcsPolyline& poly) const = 0;
	virtual HRESULT GetAutoBendedPolyline(mcsPolyline& poly) const = 0;
	
	// LineType
	//----------------------------------------
	virtual HRESULT SetNativeLineType(McsNativeLineTypeEnum lineType) = 0;
	virtual McsNativeLineTypeEnum GetNativeLineType() const = 0;
	virtual McsString GetNativeLTName(McsNativeLineTypeEnum lineType) const = 0;
	
	// Active side
	//----------------------------------------
	virtual HRESULT SetActiveSide(LineTypeActiveSideEnum ltActiveSide) = 0;
	virtual LineTypeActiveSideEnum GetActiveSide() const = 0;
	
	// Custom parameters of current LineType
	//----------------------------------------
	virtual HRESULT GetNLParameters(McNativeParamArray& arrParams) const = 0;
	virtual HRESULT SetNLParameters(const McNativeParamArray& arrParams) = 0;
	virtual LineTypeParamEnum GetParamType(LPCTSTR pszSystemName) const = 0;
	virtual McsString GetParamSystemName(LineTypeParamEnum typeParam) const = 0;
	virtual McsString GetParamLocalName(LineTypeParamEnum typeParam) const = 0;
	
	// Point objects
	//----------------------------------------
	virtual HRESULT AttachPointObject(const mcsWorkID& idPointObj) = 0;
	virtual HRESULT DetachPointObject(const mcsWorkID& idPointObj) = 0;
	virtual HRESULT GetAttachedObjects(mcsWorkIDArray& idsPointObjects) const = 0;

	// Corrected by Point Objects Length
	//----------------------------------------
	virtual double GetLength() const = 0;

	// Internal Built-In Linetype Maker
	//----------------------------------------
	virtual IMcNativeLineTypeMakerPtr GetMaker() const = 0;
};

//----------------------------------------
// Базовый "длинный" объект
//----------------------------------------
struct IMcNativeLongObject : public virtual IMcCdEntity
{
public:
	IMCS_ENT_METHOD_DEFINITION(IMcNativeLongObject, IMcCdEntity, IMcDbEntity);

	//----------------------------------------
	IMcNativeLongObject() : IMcCdEntity()
	{
		IMCS_REGISTER_THIS_IID_4KINDOF;

		m__lSystemFlag = kMcCoveredEnt;

		m_pNLAssist = gpMcObjManager->createObject(IID_IMcBaseLongObjectAssistant);
		if (m_pNLAssist)
			m_pNLAssist->SetLongObject(this);
	}
	
	//----------------------------------------
	virtual ~IMcNativeLongObject()
	{
		m_pNLAssist = UNKNULL;
	}

#ifndef NOLASSIST
#define NOLASSIST(retval) if (!m_pNLAssist) return retval;
#endif

	// IMcEntity redirected methods
	//----------------------------------------
	virtual HRESULT onDraw(IMcGeometryBuilder *pG) override
	{
		NOLASSIST(E_NOTIMPL)
 		m_2dOriginalCache.RemoveAll();
 		clearContours();
 		pG->setContainer(&m_2dOriginalCache);
		return m_pNLAssist->onDraw(pG);
	}
	//----------------------------------------
	virtual HRESULT onTransform(IN const mcsMatrix& tfm) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->onTransform(tfm);
	}
	//----------------------------------------
	virtual HRESULT getBoundingBoxOCS(OUT mcsBoundBlock &box) const override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->getBoundingBox(box);
	}
	//----------------------------------------
	virtual HRESULT getCompoundBounds(mcsBoundBlocksArray& blocks) const override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->getCompoundBounds(blocks);
	}
	//----------------------------------------
	virtual HRESULT onGetGripPoints(mcsPoint3dArray& gripPoints, bool bStretch) const override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->onGetGripPoints(gripPoints, bStretch);
	}
	//----------------------------------------
	virtual HRESULT onMoveGripPointsAt(const mcsIntArray& indices, const mcsVector3d& offset, bool bStretch) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->onMoveGripPointsAt(indices, offset, bStretch);
	}
	//----------------------------------------
	virtual HRESULT onGetGripPoints(McGripDataPtrArray& grips, double rViewUnitSize, int iGripSize, const mcsVector& vecViewDir, int iFlags) const override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->onGetGripPoints(grips, rViewUnitSize, iGripSize, vecViewDir, iFlags);
	}
	//----------------------------------------
	virtual HRESULT onMoveGripPointsAt(const McGripDataPtrArray& grips, const mcsVector& offset, int iFlags) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->onMoveGripPointsAt(grips, offset, iFlags);
	}
	//----------------------------------------
	virtual HRESULT onGetOsnapPoints(McOsnapMode osnapMode, const mcsPoint3d& pickPoint, const mcsPoint3d& lastPoint, mcsPoint3dArray& snapPoints) const override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->onGetOsnapPoints(osnapMode, pickPoint, lastPoint, snapPoints);
	}
	//----------------------------------------
	virtual HRESULT onEdit(IN const mcsPoint3d& pnt, long lFlag = 0)
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->onEdit(pnt, lFlag);
	}
	//----------------------------------------
	virtual HRESULT onWrite(OUT IMcsStream* pStream) const override
	{
		NOLASSIST(E_NOTIMPL)
		HRESULT hres = pStream->putVersion(1, 1); ERRRET(hres)
		hres = m_pNLAssist->onWrite(pStream); ERRRET(hres)
		hres = pStream->writeVersionBlockEnd(); ERRRET(hres)
		return hres;
	}
	//----------------------------------------
	virtual HRESULT onRead(IN IMcsStream* pStream) override
	{
		NOLASSIST(E_NOTIMPL)
		WORD iVersion = 0, iMinor = 0;
		HRESULT hres = pStream->getVersion(iVersion, &iMinor); ERRRET(hres)
		if (iVersion > 1) {
			gpMcContext->SymbolLoadError(_T("IMcNativeLongObject"), MAKELONG(iMinor, iVersion));
			return MCS_E_MAKE_ME_PROXY;
		}
		hres = m_pNLAssist->onRead(pStream); ERRRET(hres)	
		hres = pStream->readVersionBlockEnd(); ERRRET(hres)
		return hres;
	}
	//----------------------------------------
	virtual HRESULT getAsPrimitive(OUT McsEntityGeometry& primitive, OUT mcsWorkIDArray* pidsOnPrimitive = NULL) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->getAsPrimitive(primitive, pidsOnPrimitive);
	}
	//----------------------------------------
	virtual HRESULT setAsPrimitive(IN const McsEntityGeometry& primitive, IN const mcsWorkIDArray* pidsOnPrimitive = NULL) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->setAsPrimitive(primitive, pidsOnPrimitive);
	}
	//----------------------------------------
	virtual HRESULT getParamAtPoint(OUT McGeometryParam& param, IN const mcsPoint& pnt) const override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->getParamAtPoint(param, pnt);
	}
	//----------------------------------------
	virtual HRESULT getPointAtParam(OUT mcsPoint& pnt, IN const McGeometryParam& param, OUT OPTIONAL McsEntityGeometry* pSimpleEnt = NULL) const override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->getPointAtParam(pnt, param, pSimpleEnt);
	}
	//----------------------------------------
	virtual HRESULT onReactor(IMcDbObject *pObj, mcReactorsType action) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->onReactor(pObj, action);
	}
	//----------------------------------------
	virtual HRESULT onEvent(IMcEventType event, mcsExValueArray *pAdditionalParameters = NULL) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->onEvent(event, pAdditionalParameters);
	}
	//----------------------------------------
	virtual HRESULT onErase() override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->onErase();
	}
	//----------------------------------------
	virtual HRESULT placeObject(long lInsertType = kMcPlace_Normal, mcsExValueArray *pAdditionalParameters = NULL) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->placeObject(lInsertType, pAdditionalParameters);
	}
	//----------------------------------------
	virtual HRESULT placeObject(long lInsertType, mcsExValueArray *pAdditionalParameters, IMcCustomSink* pCustomSink)
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->placeObject(lInsertType, NULL, pCustomSink);
	}
	//----------------------------------------
	virtual HRESULT getProperties(mcsStringArray& props) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->getProperties(props);
	}
	//----------------------------------------
	virtual HRESULT getProperty(const McsString& name, MCSVariant& data) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->getProperty(name, data);
	}
	//----------------------------------------
	virtual HRESULT setProperty(const McsString& name, const MCSVariant& data) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->setProperty(name, data);
	}
	//----------------------------------------
	virtual HRESULT getPropertyInfo(const McsString& systemName, OUT McPropertyInfo& info) override
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->getPropertyInfo(systemName, info);
	}

	// Assistant
	//----------------------------------------
	virtual IMcBaseLongObjectAssistantPtr GetAssistant() const { return m_pNLAssist; }
	
	// Polyline
	//----------------------------------------
	virtual HRESULT SetPolyline(const mcsPolyline& poly)
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->SetPolyline(poly);
	}
	//----------------------------------------
	virtual HRESULT GetPolyline(mcsPolyline& poly) const
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->GetPolyline(poly);
	}
	//----------------------------------------
	virtual HRESULT GetAutoBendedPolyline(mcsPolyline& poly) const
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->GetAutoBendedPolyline(poly);
	}
	
	// LineType
	//----------------------------------------
	virtual HRESULT SetNativeLineType(McsNativeLineTypeEnum lineType)
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->SetNativeLineType(lineType);
	}
	//----------------------------------------
	virtual McsNativeLineTypeEnum GetNativeLineType() const
	{
		NOLASSIST(NLT_BYOBJECT)
		return m_pNLAssist->GetNativeLineType();
	}
	//----------------------------------------
	virtual McsString GetNativeLTName(McsNativeLineTypeEnum lineType) const
	{
		NOLASSIST(L"")
		return m_pNLAssist->GetNativeLTName(lineType);
	}
	
	// Active side
	//----------------------------------------
	virtual HRESULT SetActiveSide(LineTypeActiveSideEnum ltActiveSide)
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->SetActiveSide(ltActiveSide);
	}
	//----------------------------------------
	virtual LineTypeActiveSideEnum GetActiveSide() const
	{
		NOLASSIST(asLeft)
		return m_pNLAssist->GetActiveSide();
	}
	
	// Custom parameters of current LineType
	//----------------------------------------
	virtual HRESULT GetNLParameters(McNativeParamArray& arrParams) const
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->GetNLParameters(arrParams);
	}
	//----------------------------------------
	virtual HRESULT SetNLParameters(const McNativeParamArray& arrParams)
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->SetNLParameters(arrParams);
	}
	//----------------------------------------
	virtual LineTypeParamEnum GetParamType(LPCTSTR pszSystemName) const
	{
		NOLASSIST(LTPAR_UNDEFINED)
		return m_pNLAssist->GetParamType(pszSystemName);
	}
	
	//----------------------------------------
	virtual McsString GetParamSystemName(LineTypeParamEnum typeParam) const
	{
		NOLASSIST(L"")
		return m_pNLAssist->GetParamSystemName(typeParam);
	}
	//----------------------------------------
	virtual McsString GetParamLocalName(LineTypeParamEnum typeParam) const
	{
		NOLASSIST(L"")
		return m_pNLAssist->GetParamLocalName(typeParam);
	}
	
	// Point objects
	//----------------------------------------
	virtual HRESULT AttachPointObject(const mcsWorkID& idPointObj)
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->AttachPointObject(idPointObj);
	}
	//----------------------------------------
	virtual HRESULT DetachPointObject(const mcsWorkID& idPointObj)
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->DetachPointObject(idPointObj);
	}
	//----------------------------------------
	virtual HRESULT GetAttachedObjects(mcsWorkIDArray& idsPointObjects) const
	{
		NOLASSIST(E_NOTIMPL)
		return m_pNLAssist->GetAttachedObjects(idsPointObjects);
	}

	// Corrected by Point Objects Length
	//----------------------------------------
	virtual double GetLength() const
	{
		NOLASSIST(0.0)
		return m_pNLAssist->GetLength();
	}

protected:
	IMcBaseLongObjectAssistantPtr m_pNLAssist;
};
