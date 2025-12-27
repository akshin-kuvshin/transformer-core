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

#define COLORREF_SPEC_VAL 0xEE010101

//=============================================================================
enum MCS_AppId;
enum MCS_ConfigurationId;

enum MCS_PlatformId
{
	MCS_PLM_UNDEFINED       =        0,
	MCS_PLM_ACAD            =   0x1000,          // Acad
	MCS_PLM_INVENTOR        =   0x2000,          // Inventor
	MCS_PLM_SPOTLIGHT       =   0x4000,          // SpotLight
	MCS_PLM_NANO            = MCS_PLM_SPOTLIGHT, // Nano2, значение MCS_PLM_SPOTLIGHT осталось так как в одной ветке исходников эти платформы никогда уже не пересекутся
	MCS_PLM_SOLIDEDGE       =   0x8000,          // SolidEdge
	MCS_PLM_INVENTOR_3D     =  0x10000,          // System value don't use it in expression
	MCS_PLM_INVENTOR_2D     =  0x20000,          // System value don't use it in expression
	MCS_PLM_ACAD_LT         =  0x40000,          // System value don't use it in expression	
	MCS_PLM_CFG_EXE         =  0x80000,          // McConfigurator
	MCS_PLM_SOLIDWORKS      = 0x100000,          // SolidWorks
	MCS_PLM_3D              = MCS_PLM_INVENTOR | MCS_PLM_SOLIDEDGE | MCS_PLM_SOLIDWORKS,
};

enum MCS_LangId
{
	MCS_LANG_ENGLISH				= 0x01,
	MCS_LANG_RUSSIAN				= 0x02,
	MCS_LANG_GERMAN					= 0x04,
	MCS_LANG_CZECH					= 0x08,
	MCS_LANG_POLISH					= 0x10,
	MCS_LANG_FRENCH					= 0x20,
	MCS_LANG_SLOVAK					= 0x40,
	MCS_LANG_BULGARIAN			= 0x80,
	MCS_LANG_HUNGARIAN			= 0x100,
	MCS_LANG_SPANISH				= 0x200,
	MCS_LANG_ITALIAN				= 0x400,
	MCS_LANG_CHINESE_SIMPL	= 0x800,
	MCS_LANG_JAPANESE				= 0x1000,
	MCS_LANG_KOREAN         = 0x2000,
	MCS_LANG_UNSUPORTED			= 0x80000000,
};


#define MCS_PLM_ALL    (MCS_PLM_INVENTOR|MCS_PLM_SOLIDEDGE|MCS_PLM_ACAD|MCS_PLM_SPOTLIGHT)
#define MCS_PLM_2D     (MCS_PLM_ACAD|MCS_PLM_SPOTLIGHT)

//=============================================================================
enum MCS_Layout
{
	MCS_LAYOUT_AUTO      = 0,
	MCS_LAYOUT_ENG       = 0x0409,
	MCS_LAYOUT_RUS       = 0x0419,
 	MCS_LAYOUT_GERMAN    = 0x0407,
	MCS_LAYOUT_CZECH     = 0x0405,
	MCS_LAYOUT_SLOVAK    = 0x041b,
	MCS_LAYOUT_BULGARIAN = 0x0402,
	MCS_LAYOUT_HUNGARIAN = 0x040e,
	MCS_LAYOUT_POLISH    = 0x0415,
	MCS_LAYOUT_FRENCH    = 0x040c,
	MCS_LAYOUT_SPANISH   = 0x040a,
	MCS_LAYOUT_ITALIAN   = 0x0410,
	MCS_LAYOUT_CHINESE_TR= 0x0804,
	MCS_LAYOUT_JAPANESE  = 0x0411,
};
//=============================================================================
// !!! Use as FLAGS !!!
enum McsMeasureTypeFilterEnum
{
  //kMcsMsrFilter_None     = 0,
  kMcsMsrFilter_Distance = 1,
//  kMcsMsrFilter_Diameter = 2,
  kMcsMsrFilter_Angle    = 4,

	kMcsMsrFilter_All      = -1,
};
//=============================================================================
//force declarations 

enum McMouseButtonEnum
{
  kMMB_Left   = 1,
  kMMB_Middle = 2,
  kMMB_Right  = 3,
};

//=============================================================================
#define MCS_CMD_MODAL                   0x00000000
#define MCS_CMD_TRANSPARENT             0x00000001
#define MCS_CMD_REDRAW                  0x00000004
#define MCS_CMD_NOMODELSPACE            0x00000020
#define MCS_CMD_NOPAPERSPACE            0x00000040
#define MCS_CMD_DEBUG                   0x01000000
#define MCS_CMD_NOCHECK                 0x02000000
#define MCS_CMD_PROPERTIES              0x00400000// ACRX_CMD_INTERRUPTIBLE equivalent
#define MCS_CMD_NO_PREFIX               0x00100000// Не устанавливать префикс автоматически
#define MCS_CMD_PLATFORM_CMD            0x80000000// Флажок для наны, означет что надо регистрировать в 2 вариантах, с префиксом и без
#define MCS_CMD_SESSION                 0x00200000// ACRX_CMD_SESSION equivalent
#define MCS_CMD_NO_UNDO                 0x00800000// На время работы команды undo отключается
#define MCS_CMD_SYS_PLM_CMD             0x04000000// Системный, команда платформы
//=============================================================================
#ifndef _XYZT_DEFINED
  #define _XYZT_DEFINED
  enum { X = 0, Y = 1, Z = 2 }; /* The coordinates of a point. */
  enum { T = 3 };               /* The translation vector of a 3D matrix */
#endif // !_XYZT_DEFINED
//=============================================================================
//Db Consts
#ifndef DBCONSTS
  #define DBCONSTS

  #define STR_VAL_IN_SCRIPT  50
  #define UNKNOWNVALUE       -0.12345
  #define MAXCOMMANDLENGTH   102400
  #define MAXEMFSIZE         61440
  #define FTREAL             1
  #define FTINT              2
  #define FTSTR              3
#endif
//=============================================================================
#ifndef PI
#define PI                   3.1415926535897932384626433832795
#endif

#ifndef PI2
#define PI2                  6.283185307179586476925286766559
#endif

#ifndef PI_2
#define PI_2                 1.5707963267948966192313216916398
#endif

#ifndef PI_3
#define PI_3                 1.0471975511965977461542144610932
#endif

#ifndef PI_4
#define PI_4                 0.78539816339744830961566084581988
#endif

#ifndef RADIAN
#define RADIAN               57.295779513082320876798154814105
#endif

#ifndef MINPOSSIBLEVALUE
#define MINPOSSIBLEVALUE	   0.0001
#endif

#define MCSUID_NULL          0.0

typedef int								M_RET;
#define	mOk								0 
#define mErr							-1
#define mCancel						-2
#define mSkip							-3
#define mUndo							-4


#ifndef DEADVTABLE
#define DEADVTABLE           0xFFEEDDCC
#endif

#ifndef UNDEFINED_IDX
#define UNDEFINED_IDX        -1
#endif

#ifndef UNDEFINED_WEIGHT
#define UNDEFINED_WEIGHT     -1
#endif

#ifndef UNDEFINED_HANDLE
#define UNDEFINED_HANDLE     -1 
#endif

#ifndef MAX_REAL 
#define MAX_REAL             1.7E+307
#endif

#ifndef REAL_DEFAULT_PRECISION
#define REAL_DEFAULT_PRECISION  0.00001
#endif

#define REAL_MAX_VALUE_DECIMAL  100000000000000. // max double digits = 14 see float h
	
#define GMC_REAL_MAX_COORD    (REAL)  (REAL_MAX_VALUE_DECIMAL * REAL_DEFAULT_PRECISION)
#define GMC_REAL_MIN_COORD    (REAL) -(REAL_MAX_VALUE_DECIMAL * REAL_DEFAULT_PRECISION)
	
#define GMC_REAL_MAX  (REAL) (INT_MAX)
#define GMC_REAL_MIN  (REAL) (INT_MIN)

#ifndef GMC_PI
#define GMC_PI				(PI)
#endif
#define GMC_PI_3			(GMC_PI/3)
#define GMC_PI_2			(GMC_PI/2)
#define GMC_2PI_3			((GMC_PI * 2)/3)
#define GMC_3PI_2			((GMC_PI * 3)/2)
#define GMC_2PI				(2*GMC_PI)
#define GMC_0					(0.)

#ifndef	GMC_RAD
	#define GMC_RAD				RADIAN
#endif
	
#define GMC_MM_IN_INCH  (25.4)

#ifndef DEF_TOL
#define DEF_TOL 0.0001
#endif

//=============================================================================
// arrows
//----------------------------------------
//аналогичный енум описан в src/OleServer/OleServer.idl
//называется ARROW_TYPE
enum MCS_ARROW
{
	MCS_ArrNone        = 0,  // "_NONE"                                 нет
	MCS_ArrArrow       = 1,  // "" (simple arrow - closed filled)       закрашенная замкнутая
	MCS_ArrDotsmall    = 2,  // "_DOTSMALL" = dot small                 малая точка
	MCS_ArrOblique     = 3,  // "_OBLIQUE" = oblique                    наклон
	MCS_ArrDatumFilled = 4,  // "_DATUMFILLED" = datum triangle filled  закрашенный треугольник
	MCS_ArrOpen        = 5,  // "_OPEN" = open                          разомкнутая
	MCS_ArrHalf        = 6,  // "_HALF" = ??
//	MCS_ArrLeg         = 7,// не использовать 7!!!!
	MCS_ArrOpen90      = 8,  // "_OPEN90" = right angle                 прямой угол
	MCS_ArrInverseHalf = 9,  // ??
	MCS_ArrClosedBlank = 10, // "_CLOSEDBLANK" = closed blank           замкнутая
	MCS_ArrDatumBlank  = 11, // "_DATUMBLANK" = datum triangle          треугольник
	MCS_ArrDotBlank    = 12, // "_DOTBLANK"= dot blank                  контурная точка
	MCS_ArrThickLine   = 13, // 
	MCS_ArrDot         = 14, // "_DOT" = dot                            точка
	MCS_ArrOrigin      = 15, // "_ORIGIN" = origin indicator            указатель начала
	MCS_ArrOrigin2     = 16, // "_ORIGIN2" = origin indicator 2         указатель начала 2
	MCS_ArrOpen30      = 17, // "_OPEN30" = open 30                     разомкнутая 30
	MCS_ArrClosed      = 18, // "_CLOSED" = closed                      замкнутая
	MCS_ArrSmall       = 19, // "_SMALL" = dot small blank              контурная малая точка
	MCS_ArrBoxFilled   = 20, // "_BOXFILLED"                            закрашенный прямоугольник
	MCS_ArrBoxBlank    = 21, // "_BOXBLANK"                             прямоугольник
	MCS_ArrIntegral    = 22, // "_INTEGRAL"                             интеграл
	MCS_ArrArchTick    = 23, // "_ARCHTICK"                             архитектурная засечка // Двойная засечка

	MCS_ArrClosedFilled = 1,
	MCS_ArrUnknown     = -1,

	// 3D стрелка, аналог Инвенторовской IIG_3dArrow.
	// Направление (dir) - направление указателя стрелки.
	// Точка pnt - начало стрелки.
	// Размер "головки" определяется автоматически.
	// rSize - задает длину стрелки. rWidth игнорируется.
	MCS_Arr3dArrow     = 1000,
};

//=============================================================================

// OsnapMode:  Specifies Object query.
//             Binary and Virtual Operations not represented.
//
enum McOsnapMode       { kMcsOsModeEnd          = 1,
                         kMcsOsModeMid          = 2,
                         kMcsOsModeCen          = 3,
                         kMcsOsModeNode         = 4,
                         kMcsOsModeQuad         = 5, 
                         kMcsOsModeIns          = 7,
                         kMcsOsModePerp         = 8,
                         kMcsOsModeTan          = 9,
                         kMcsOsModeNear         = 10 };

enum McMatchPropEnum
{
	// Dwg specific (AcDbMatchProperties::Flags)
	kMcMPropColor            = 0x00000001,
	kMcMPropLayer            = 0x00000002,
	kMcMPropLinetype         = 0x00000004,
	//kThicknessFlag = 0x8,
	kMcMPropLinetypeScale    = 0x00000010,
	kMcMPropText             = 0x00000020,
	//kDimensionFlag = 0x40,
	kMcMPropHatch            = 0x00000080,
	kMcMPropLineweight       = 0x00000100,
	//kPlotstylenameFlag = 0x200,
	//kPolylineFlag = 0x400,
	//kViewportFlag = 0x800,
	//kTableFlag = 0x1000,
	//kMaterialFlag = 0x2000,
	//kShadowDisplayFlag = 0x4000,
	//kMultileaderFlag = 0x8000,
	//kTransparencyFlag = 0x10000,
	kMcMPropPlatformAll      = 0x0001FFFF,

	// MAPI specific
	kMcMPropObject           = 0x10000000,// Все настройки объекта, кроме базовых свойств DbEntity. Включает в себя kMcMPropText, kMcMPropHatch и другие платформенные флаги, регулирующие копирование специфических свойств объекта.
	kMcMPropPlatformSettings = 0x20000000,// Текущие настройки копирования платформы плюс kMcMPropObject. Используется только для передачи в IMcDbEntity::matchProperties().
	kMcMPropGsMarker         = 0x40000000,
	kMcMPropVisibility       = 0x80000000,
	kMcMPropValues           = 0x01000000,// Это уточнение для тех объктов которые могут коприроватть и сами свойства
	kMcMPropObjectType       = 0x02000000,// Подменять тип объекта (для стандартных сменять ГОСТ)
	kMcMPropDirection        = 0x04000000,// Разворот объекта
	kMcMPropAll              = (kMcMPropPlatformAll | kMcMPropObject | kMcMPropGsMarker | kMcMPropVisibility),// Не включает kMcMPropValues, kMcMPropObjectType, kMcMPropDirection
};

//имена такие пока для совместимости
enum McViewTypes
{
	VID_NONE					=	0x010000,
	VID_FRONT					=	0x020000,
	VID_TOP						=	0x040000,
	VID_BOTTOM				=	0x080000,
	VID_RIGHT					= 0x100000,
	VID_LEFT					=	0x200000,
	VID_BACK					=	0x400000,
};

// Типы контролов в свойствах объекта и настройках
enum MCS_CTRL
{
	MC_NONE = 0,   
	MC_EDIT_INT = 1,                  //a
	MC_EDIT_DOUBLE = 2,               //a
	MC_EDIT_STRING = 3,               //a
	MC_BOOL_COMBOBOX = 4,             //a
	MC_COLOR_COMBOBOX = 5,            //a  Native Color : RGB In -- RGB Out!
	MC_LINEWEIGHT_COMBOBOX = 6,       //a
	MC_LAYER_COMBOBOX = 7,
	MC_TEXTSTYLE_COMBOBOX = 8,
	MC_OPEN_LOCAL_DB_DIALOG = 11,
	MC_OPEN_GLOBAL_DB_DIALOG = 12,
	MC_STD_FOLDER_BROWSER_DIALOG = 16,
	MC_EMPTY_CTRL_UNDERLINED = 19,
	MC_COMBOBOX_INT = 20,             //a
	MC_COMBOBOX_DOUBLE = 21,          //a
	MC_COMBOBOX_STRING = 22,          //a
//	MC_COMBOBOX_STRING_INDEX = 23, упразднено
	MC_EDIT_COMBOBOX_INT = 24,
	MC_EDIT_COMBOBOX_DOUBLE = 25,
	MC_EDIT_COMBOBOX_STRING = 26,
	MC_COMBOBOX_SCALE = 27,           // масштаб оформления
	MC_STRING_BUTTON = 28,
	MC_HIDDEN_CTRL_VOID_DATA = 29,	  // автоматически регистрируется с флагом MCS_HIDDEN_PARAM !!!!!!!
	MC_BROWSE_FOR_FOLDER = 30,
	MC_STRING_ARRAY = 31,
	MC_EDIT_STRING_ARRAY = 32,
	MC_OPEN_FILE_DIALOG = 33,         // Регистрируется как MCSVariant::kStringArray, в котором
					// 1-я строка - Имя файла по умолчанию
					// 2-я строка - Расширение файла по умолчанию
					// 3-я строка - Файловый фильтр
	MC_DIMSTYLE_COMBOBOX = 34,
	MC_HOT_KEY = 35,                  // Integer - Virtual key code ( + CTRL + SHIFT)
	MC_CMD_MODIFICATOR = 36,          // Регистрируется как MCSVariant::kIntArray, в котором
					// 1-й элемент - VK_CONTROL or 0
					// 2-й элемент - VK_SHIFT   or 0
					// В итоге 3 варианта : CTRL, SHIFT, CTRL+SHIFT
	MC_POINT2D = 37,                  // (Acad) Точка
	MC_VECTOR2D = 38,                 // (Acad) Вектор
	MC_POINT2D_ARRAY = 39,            // (Acad) Массив точек
	MC_POINT = 40,                    // (Acad) Точка
	MC_VECTOR = 41,                   // (Acad) Вектор
	MC_POINT_ARRAY = 42,              // (Acad) Массив точек
	MC_EDIT_COMBOBOX_TEXTHEIGHT = 43, // Высота текста по ГОСТ
	MC_PROFILE_TABLE = 44,            // строка - префикс выбранного профиля из таблицы, Используеися для слоя объекта
	MC_LINETYPE_COMBOBOX = 45,		// строка
	MC_HATCH_DIALOG = 46,             // строка, для работы со свойством использовать методы McHatchParamXXX,
	                                  // определённые в MCSParams.h
	MC_CUSTOM_DIALOG = 47,            // Для редактирования вызовется McPropertyInfo::pCustomDialog();
	MC_EDIT_FIXED_COMBOBOX_STRING = 48,// Поле ввода + фиксированный список предустановленных значений (+ одно пользовательское)
	MC_COMBOBOX_DIMSCALE = 49,        // масштаб измерений
	MC_EDIT_ANGLE = 50,               // MC_EDIT_DOUBLE для углов, угол в градусах
	MC_STD_OBJECT_BROWSER_DIALOG = 51,// MCSUID как int64 в шестнадцатиричном виде "0123456789ABCDEF"
	                                  // MCSVariant::kStringArray : 1-я строка - CollectionFilter::lClass, по умолчанию "0"
	MC_EDIT_DISTANCE = 52,            // MC_EDIT_DOUBLE для расстояния, расстояние в модельных попугаях
	MC_EDIT_ANGLE_DIF = 53,           // MC_EDIT_DOUBLE для разницы углов, угол в градусах
	MC_EDIT_AREA = 54,                // MC_EDIT_DOUBLE для площади, площадь в квадратных модельных попугаях
	MC_EDIT_VOLUME = 55,              // MC_EDIT_DOUBLE для объёма. Объём в кубических модельных попугаях

	MC_ARROW_COMBOBOX = 56,           // Тип стрелки. Работает через интерфейс IMcArrowsExtension.

	MC_EDIT_MASS = 57,                // MC_EDIT_DOUBLE для массы. Объём в модельных весовых попугаях
};

inline bool IsControlHasUnits(MCS_CTRL crl)
{
	switch (crl)
	{
		case MC_EDIT_ANGLE: // kmcAngular
		case MC_EDIT_ANGLE_DIF: // kmcAngularDif
		case MC_EDIT_AREA: // kmcAreal
		case MC_EDIT_DISTANCE: // kmcLinear
		case MC_EDIT_VOLUME: // kmcVolumetric
		//case MC_EDIT_MASS: //kmcMass
			return true;
	}
	return false; // kmcUndefined
}

inline bool IsControlHasValues(MCS_CTRL ctl)
{
	switch(ctl)
	{
		case MC_COMBOBOX_SCALE:
		case MC_COMBOBOX_DIMSCALE:
		case MC_TEXTSTYLE_COMBOBOX:
		case MC_DIMSTYLE_COMBOBOX:
		case MC_COMBOBOX_INT:
		case MC_COMBOBOX_DOUBLE:
		case MC_COMBOBOX_STRING:
		case MC_EDIT_COMBOBOX_INT:
		case MC_EDIT_COMBOBOX_DOUBLE:
		case MC_EDIT_COMBOBOX_STRING:
			return true;
	}
	return false;
}
inline bool IsControlHasExclusiveValues(MCS_CTRL ctl)
{
	switch(ctl)
	{
	case MC_EDIT_COMBOBOX_INT:
	case MC_EDIT_COMBOBOX_DOUBLE:
	case MC_EDIT_COMBOBOX_STRING:
		return false;
	}
	return true;
}
// Для свойств типа MC_POINT_ARRAY2D, MC_POINT_ARRAY
// Добавка к системному имени свойства для получения количества точек
#define MCPROP_COUNT_POSTFIX _T("Count")

// Для VS6.0
#ifndef LVS_EX_LABELTIP
	#define LVS_EX_LABELTIP 0x00004000
#endif

//---------------------------------------------------------
// Floating point comparison
//

#ifndef CS_FLOAT_COMPARISON
#define CS_FLOAT_COMPARISON

__inline bool FEQ (const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
{ return a-e <= b && b <= a+e; }

__inline bool FNE (const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
{ return !FEQ (a, b, e); }

__inline bool FGT (const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
{ return a-e > b; }

__inline bool FGE (const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
{ return a >= b-e; }

__inline bool FLT (const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
{ return !FGE (a, b, e); }

__inline bool FLE (const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
{ return !FGT (a, b, e); }

__inline double SIGN (const double a, double e = REAL_DEFAULT_PRECISION)
{ return FEQ (a, 0.0, e) ? 0.0 : (FGT (a, 0.0, e) ? 1.0 : -1.0); }

#endif // CS_FLOAT_COMPARISON
//=================================================================================
// Стандарты
// (Косинцев С.Г.) При изменении списка стандартов также вносить изменения в
// перечисление Standarts в файле MechaniCS\Core\Src\mapimngd\Runtime.h
enum MCS_STANDARD
{
	MCS_STD_GOST     = 0x0001,
	MCS_STD_SPDS     = 0x0002,
	MCS_STD_ISO      = 0x0004,
	MCS_STD_ISO_MECH = MCS_STD_ISO,// ISO механический
	MCS_STD_DIN      = 0x0008,
	MCS_STD_CSN      = 0x0010,
	MCS_STD_PN       = 0x0020,
	MCS_STD_JUS      = 0x0040,
	MCS_STD_GB       = 0x0080,//chinese
	MCS_STD_NF       = 0x0100,//french
	MCS_STD_IS       = 0x0200,//indian
	MCS_STD_ISO_ARCH = 0x0400,// ISO архитектурный
	MCS_STD_ANSI     = 0x0800,
	MCS_STD_CUSTOM   = 0x8000,//Вне стандартов

	MCS_STD_ALL         = 0x0FFF,
	MCS_STD_ALL_FOREIGN = 0x0FFC,
	MCS_STD_ALL_ARCH    = 0x0402,// Все архитектурные
	MCS_STD_ALL_MECH    = 0x0BFD,// Все механические
};
#define MCS_STD_ALL_BUT(STD) (MCS_STD_ALL&~(STD))
#define MCS_IS_STD_ARCH(STD) (((STD) & MCS_STD_ALL_ARCH) != 0)
#define MCS_IS_STD_MECH(STD) (((STD) & MCS_STD_ALL_MECH) != 0)

#define MCS_STANDARD_FILTER	0xFFFF
//=================================================================================
#if !defined(_NCAD_BUILD_) && !defined(_MCS_CORE_ONLY)
	#include "MCSConstsInternal.h"
#endif
//===========================================================================
