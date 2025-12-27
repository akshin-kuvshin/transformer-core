#pragma once
#include "MCSTypes.h"

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Units
//---------------------------------------------------------------------------
struct McUnits
{
	enum Name
	{
		kDefault      = 255,// По умолчанию, согласно настроек среды
		kUndefined    = 0,// Безразмерная величина

		// Linear
		kInches       = 1,
		kFeet         = 2,
		kMiles        = 3,
		kMillimeters  = 4,
		kCentimeters  = 5,
		kMeters       = 6,
		kKilometers   = 7,
		kMicroinches  = 8,
		kMils         = 9,
		kYards        = 10,
		kAngstroms    = 11,
		kNanometers   = 12,
		kMicrons      = 13,
		kDecimeters   = 14,
		kDekameters   = 15,
		kHectometers  = 16,
		kGigameters   = 17,
		kAstronomical = 18,
		kLightYears   = 19,
		kParsecs      = 20,

		// Angular
		kRadians      = 30,
		kDegrees      = 31,
		kMinutes      = 32,
		kSeconds      = 33,
		kGradians     = 34,

		// Mass
		kMilligrams   = 40,
		kGrams        = 41,
		kKilograms    = 42,
		kCentners     = 43,
		kTons         = 44,

		// End of fixed part
		kLinearSmall = 254,// Настраиваемая пользовательская величина для небольших величин. Например, для задания размеров элементов оформления, высоты текста и т.п. Использовать только при пользовательском вводе\выводе, сохранять нельзя.
		kLinearMiddle = 253,// Настраиваемая пользовательская величина для средних величин. Например, длина коридора, высота потолка и т.п. Использовать только при пользовательском вводе\выводе, сохранять нельзя.
		kLinearLarge = 252,// Настраиваемая пользовательская величина для больших величин. Например, протяжённость дороги и т.п. Использовать только при пользовательском вводе\выводе, сохранять нельзя.

	};
	enum LinearMode// "LUNITS" dwg variable
	{
		klmDefault       = -1,
		klmScientific    = 1,
		klmDecimal       = 2,
		klmEngineering   = 3,
		klmArchitectural = 4,
		klmFractional    = 5,
	};
	enum AngularMode// "AUNITS" dwg variable
	{
		kamDefault        = -1,
		kamDecimalDegrees = 0,
		kamDegMinSec      = 1,
		kamGradians       = 2,
		kamRadians        = 3,
		kamSurveyors      = 4,
	};
	enum DisplayFormat// "UNITMODE" dwg variable
	{
		kdfDefault       = -1,
		kdfUsingSpaces   = 0,// Displays fractional, feet-and-inches, and surveyor's angles in “report” format using spaces as delimiters
		kdfWithoutSpaces = 1,// Displays fractional, feet-and-inches, and surveyor's angles in “input” format without including spaces and, in some cases, substituting dashes for spaces
	};
	enum LinearSuppressZero// "DIMZIN" dwg variable
	{
		klszDefault          = -1,
		klszSuppFeetSuppInch = 0,// Suppresses zero feet and precisely zero inches
		klszInclFeetInclInch = 1,// Includes zero feet and precisely zero inches
		klszInclFeetSuppInch = 2,// Includes zero feet and suppresses zero inches
		klszSuppFeetInclInch = 3,// Includes zero inches and suppresses zero feet
		klszNoSuppress       = 0,// Do not suppress zeros in decimal dimensions
		klszSuppLead         = 4,// Suppresses leading zeros in decimal dimensions (for example, 0.5000 becomes .5000)
		klszSuppTrail        = 8,// Suppresses trailing zeros in decimal dimensions (for example, 12.5000 becomes 12.5)
		klszSuppLeadAndTrail = 12,// Suppresses both leading and trailing zeros (for example, 0.5000 becomes .5)
	};
	enum AngularSuppressZero// "DIMAZIN" dwg variable
	{
		kaszDefault          = -1,
		kaszDisplayAll       = 0,// Displays all leading and trailing zeros
		kaszSuppLead         = 1,// Suppresses leading zeros in decimal dimensions (for example, 0.5000 becomes .5000)
		kaszSuppTrail        = 2,// Suppresses trailing zeros in decimal dimensions (for example, 12.5000 becomes 12.5)
		kaszSuppLeadAndTrail = 3,// Suppresses leading and trailing zeros (for example, 0.5000 becomes .5)
	};
	enum MeasureCategory
	{
		kmcUndefined  = -1,// Безразмерная величина
		kmcLinear     = 0,// Линейная величина
		kmcAreal      = 1,// Площадная величина
		kmcVolumetric = 2,// Объёмная величина
		kmcAngular    = 3,// Угловая величина
		kmcAngularDif = 5,// Угловая величина как разница углов (без учёта базового угла и направления)
		kmcMass       = 6,// Масса
	};
};
#define UNIT_COMBO_CATEGORY(units) ((McUnits::MeasureCategory)(((units) & 0xff000000) >> 24))
#define UNIT_COMBO_NAME(units)     ((McUnits::Name)(((units) & 0x000000ff)))
#define UNIT_COMBO_MAKE(MeasureCategory, Name) ((((DWORD32)MeasureCategory) << 24) | (DWORD32)(Name))
#define MC_DEF_BASE_ANGLE -777.7777// Магическое число, базовый угол по умолчанию

struct IMcUnitConverter;
IMCS_DECL_INTERFACE(IMcUnitConverter, "8C9BDE8A-BDC8-4f51-BFD2-54D7EEEEFA13")

struct IMcUnitConverter : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcUnitConverter);
	IMCS_STD_METHOD_DEFINITION(IMcUnitConverter, IMcObject);
	//
	virtual double GetUnitFactor(IN McUnits::MeasureCategory aCategory, IN McUnits::Name aFrom, IN OPTIONAL McUnits::Name aTo = McUnits::kDefault) = 0;

	virtual McsString GetUnitString(IN McUnits::MeasureCategory aCategory, IN OPTIONAL McUnits::Name aFrom = McUnits::kDefault, IN OPTIONAL bool aForControls = true) = 0;

	virtual bool HasValidUnitString(McUnits::MeasureCategory aCategory, IN LPCTSTR stValue) = 0;

	virtual bool Ang2Str(
		double rValue,
		OUT McsString& stValue,
		double rBaseAngle = MC_DEF_BASE_ANGLE, // Базовый угол относительно оси Х, MC_DEF_BASE_ANGLE - взять из документа
		int iDirection = -1, // Направление: 0 - против часовой стрелки, 1 - по часовой стрелке, -1 - взять из документа
		McUnits::AngularMode mode = McUnits::kamDefault,
		McUnits::Name inputUnit = McUnits::kDegrees,
		int iPrecision = -1,
		McUnits::AngularSuppressZero dimzin = McUnits::kaszDefault,
		McUnits::DisplayFormat dispformat = McUnits::kdfDefault) = 0;

	virtual bool Lin2Str(
		double rValue,
		OUT McsString& stValue,
		McUnits::Name inputUnit = McUnits::kDefault,
		McUnits::Name outputUnit = McUnits::kDefault,
		McUnits::LinearMode mode = McUnits::klmDefault,
		int iPrecision = -1,
		McUnits::LinearSuppressZero dimzin = McUnits::klszDefault,
		McUnits::DisplayFormat dispformat = McUnits::kdfDefault) = 0;

	virtual bool Area2Str(
		double rValue,
		OUT McsString& stValue,
		McUnits::Name inputUnit = McUnits::kDefault,
		McUnits::Name outputUnit = McUnits::kDefault,
		McUnits::LinearMode mode = McUnits::klmDefault,
		int iPrecision = -1,
		McUnits::LinearSuppressZero dimzin = McUnits::klszDefault,
		McUnits::DisplayFormat dispformat = McUnits::kdfDefault) = 0;

	virtual bool Volume2Str(
		double rValue,
		OUT McsString& stValue,
		McUnits::Name inputUnit = McUnits::kDefault,
		McUnits::Name outputUnit = McUnits::kDefault,
		McUnits::LinearMode mode = McUnits::klmDefault,
		int iPrecision = -1,
		McUnits::LinearSuppressZero dimzin = McUnits::klszDefault,
		McUnits::DisplayFormat dispformat = McUnits::kdfDefault) = 0;
	
	virtual bool Str2Ang(
		LPCTSTR stValue,
		OUT double& rValue,
		double rBaseAngle = MC_DEF_BASE_ANGLE, // Базовый угол относительно оси Х, MC_DEF_BASE_ANGLE - взять из документа
		int iDirection = -1, // Направление: 0 - против часовой стрелки, 1 - по часовой стрелке, -1 - взять из документа
		McUnits::Name unit = McUnits::kDegrees,
		McUnits::Name defunit = McUnits::kDefault) = 0;
	
	virtual bool Str2Lin(LPCTSTR stValue, OUT double& rValue, McUnits::Name unit = McUnits::kDefault, McUnits::Name defunit = McUnits::kDefault) = 0;
	virtual bool Str2Area(LPCTSTR stValue, OUT double& rValue, McUnits::Name unit = McUnits::kDefault, McUnits::Name defunit = McUnits::kDefault) = 0;
	virtual bool Str2Volume(LPCTSTR stValue, OUT double& rValue, McUnits::Name unit = McUnits::kDefault, McUnits::Name defunit = McUnits::kDefault) = 0;

	virtual bool GetDefaultMeasureUnitName(IN McUnits::MeasureCategory aGroupID, IN McUnits::Name aID, OUT McsString& stValue) = 0;
	virtual bool FindMeasureUnitByDefaultName(IN LPCTSTR pMatchString, OUT McUnits::MeasureCategory& aGroupID, OUT McUnits::Name& aID) = 0;
};

//---------------------------------------------------------------------------
// константы для запросов дефолтов из документа
#define MCUNITS_GETDEFAULT_LINEARUNIT       0x1
#define MCUNITS_GETDEFAULT_LINEARMODE       0x2
#define MCUNITS_GETDEFAULT_LINEARPRECISION  0x4
#define MCUNITS_GETDEFAULT_LINEARSUPPMODE   0x8
#define MCUNITS_GETDEFAULT_DISPLAYFORMAT    0x10
#define MCUNITS_GETDEFAULT_LINEAR           0x1f

#define MCUNITS_GETDEFAULT_ANGULARUNIT      0x20 // Implies angularMode
#define MCUNITS_GETDEFAULT_ANGULARMODE      0x40
#define MCUNITS_GETDEFAULT_ANGULARPRECISION 0x80
#define MCUNITS_GETDEFAULT_ANGULARSUPPMODE  0x100
#define MCUNITS_GETDEFAULT_BASEANGLE        0x200
#define MCUNITS_GETDEFAULT_DIRECTION        0x400
#define MCUNITS_GETDEFAULT_ANGLE            0x7f0

#define MCUNITS_GETDEFAULT_ALL              0xffffff
#define MCUNITS_GETDEFAULT_UNIT				0x21

class MeasureParams {
public:
	MeasureParams()
	{
		LinearUnit = McUnits::kUndefined;
		AngularUnit = McUnits::kUndefined;
		LinearPrecision = -1;
		AngularPrecision = -1;
		BaseAngle = MC_DEF_BASE_ANGLE;
		LinearMode = McUnits::klmDefault;
		AngularMode = McUnits::kamDefault;
		LinearSuppressZero = McUnits::klszDefault;
		AngularSuppressZero = McUnits::kaszDefault;
		DisplayFormat = McUnits::kdfDefault;
		AngleDirection = 0;
	};

	McUnits::Name LinearUnit;
	McUnits::Name AngularUnit;
	int LinearPrecision;
	int AngularPrecision;
	McUnits::LinearMode LinearMode;
	McUnits::AngularMode AngularMode;
	McUnits::LinearSuppressZero LinearSuppressZero;
	McUnits::AngularSuppressZero AngularSuppressZero;
	McUnits::DisplayFormat DisplayFormat;
	double BaseAngle;
	int AngleDirection;
};

//
// Предупреждение. Эти функции устарели, и их использование не рекомендуется.
// Взамен следует использовать конструкцию
// ---
// 	IMcUnitConverterPtr _pUnitConverter = gpMcObjManager->createObject(IID_IMcUnitConverter);
//	if (null == _pUnitConverter)
//		throw(...);
//	_pUnitConverter->...
// ---
// 
IMcUnitConverter* GetUnitConverter();
extern "C" MCTYP_API double McGetUnitFactor(IN McUnits::MeasureCategory aCategory, IN McUnits::Name aFrom, IN OPTIONAL McUnits::Name aTo = McUnits::kDefault);
MCTYP_API McsString McGetUnitString(IN McUnits::MeasureCategory aCategory, IN OPTIONAL McUnits::Name aFrom = McUnits::kDefault, IN OPTIONAL bool aForControls = true);
extern "C" MCTYP_API bool McHasValidUnitString(McUnits::MeasureCategory aCategory, IN LPCTSTR stValue);
extern "C" MCTYP_API bool McAng2Str(
									double rValue,
									OUT McsString& stValue,
									double rBaseAngle = MC_DEF_BASE_ANGLE, // Базовый угол относительно оси Х, MC_DEF_BASE_ANGLE - взять из документа
									int iDirection = -1, // Направление: 0 - против часовой стрелки, 1 - по часовой стрелке, -1 - взять из документа
									McUnits::AngularMode mode = McUnits::kamDefault,
									McUnits::Name inputUnit = McUnits::kDegrees,
									int iPrecision = -1,
									McUnits::AngularSuppressZero dimzin = McUnits::kaszDefault,
									McUnits::DisplayFormat dispformat = McUnits::kdfDefault);
extern "C" MCTYP_API bool McLin2Str(
									double rValue,
									OUT McsString& stValue,
									McUnits::Name inputUnit = McUnits::kDefault,
									McUnits::Name outputUnit = McUnits::kDefault,
									McUnits::LinearMode mode = McUnits::klmDefault,
									int iPrecision = -1,
									McUnits::LinearSuppressZero dimzin = McUnits::klszDefault,
									McUnits::DisplayFormat dispformat = McUnits::kdfDefault);
extern "C" MCTYP_API bool McArea2Str(
									 double rValue,
									 OUT McsString& stValue,
									 McUnits::Name inputUnit = McUnits::kDefault,
									 McUnits::Name outputUnit = McUnits::kDefault,
									 McUnits::LinearMode mode = McUnits::klmDefault,
									 int iPrecision = -1,
									 McUnits::LinearSuppressZero dimzin = McUnits::klszDefault,
									 McUnits::DisplayFormat dispformat = McUnits::kdfDefault);
extern "C" MCTYP_API bool McVolume2Str(
									   double rValue,
									   OUT McsString& stValue,
									   McUnits::Name inputUnit = McUnits::kDefault,
									   McUnits::Name outputUnit = McUnits::kDefault,
									   McUnits::LinearMode mode = McUnits::klmDefault,
									   int iPrecision = -1,
									   McUnits::LinearSuppressZero dimzin = McUnits::klszDefault,
									   McUnits::DisplayFormat dispformat = McUnits::kdfDefault);

extern "C" MCTYP_API bool McMass2Str(
	double rValue,
	OUT McsString& stValue,
	McUnits::Name inputUnit = McUnits::kDefault,
	McUnits::Name outputUnit = McUnits::kDefault,
	McUnits::LinearMode mode = McUnits::klmDefault,
	int iPrecision = -1,
	McUnits::LinearSuppressZero dimzin = McUnits::klszDefault,
	McUnits::DisplayFormat dispformat = McUnits::kdfDefault);
//////////////////
//---------------------------------------------------------------------------
// stValue - произвольная строка, содержащая введённую величину
// rValue - возвращаемая величина
// unit - единицы, в которых возвращается величина
// defunit - единицы, в которых исчисляется stValue в том случае, когда явно единицы не указаны
extern "C" MCTYP_API bool McStr2Ang(
									LPCTSTR stValue,
									OUT double& rValue,
									double rBaseAngle = MC_DEF_BASE_ANGLE, // Базовый угол относительно оси Х, MC_DEF_BASE_ANGLE - взять из документа
									int iDirection = -1, // Направление: 0 - против часовой стрелки, 1 - по часовой стрелке, -1 - взять из документа
									McUnits::Name unit = McUnits::kDegrees,
									McUnits::Name defunit = McUnits::kDefault);
extern "C" MCTYP_API bool McStr2Lin(LPCTSTR stValue, OUT double& rValue, McUnits::Name unit = McUnits::kDefault, McUnits::Name defunit = McUnits::kDefault);
extern "C" MCTYP_API bool McStr2Area(LPCTSTR stValue, OUT double& rValue, McUnits::Name unit = McUnits::kDefault, McUnits::Name defunit = McUnits::kDefault);
extern "C" MCTYP_API bool McStr2Volume(LPCTSTR stValue, OUT double& rValue, McUnits::Name unit = McUnits::kDefault, McUnits::Name defunit = McUnits::kDefault);
extern "C" MCTYP_API bool McStr2Mass(LPCTSTR stValue, OUT double& rValue, McUnits::Name unit = McUnits::kDefault, McUnits::Name defunit = McUnits::kDefault);

extern "C" MCTYP_API bool McGetDefaultMeasureUnitName(IN McUnits::MeasureCategory aGroupID, IN McUnits::Name aID, OUT McsString& stValue);
extern "C" MCTYP_API bool McFindMeasureUnitByDefaultName(IN LPCTSTR pMatchString, OUT McUnits::MeasureCategory& aGroupID, OUT McUnits::Name& aID);
