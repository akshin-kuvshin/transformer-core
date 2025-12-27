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


#include <comdef.h>
#include "McsConsts.h"
#include "IMcObjects.h"
#include "IMcStyles.h"
#include "McsTypes.h"


//////////////////////////////////////////////////////////////////////////
// поля допусков
enum McDimFieldEnum {
	// валы
	kMcDimField_a = 0,		kMcDimField_b,				kMcDimField_c,				kMcDimField_cd,
	kMcDimField_d,				kMcDimField_e,				kMcDimField_ef,				kMcDimField_f,
	kMcDimField_fg,				kMcDimField_g,				kMcDimField_h,				kMcDimField_js,
	kMcDimField_j,				kMcDimField_k,				kMcDimField_m,				kMcDimField_n,
	kMcDimField_p,				kMcDimField_r,				kMcDimField_s,			  kMcDimField_t,
	kMcDimField_u,				kMcDimField_v,				kMcDimField_x,				kMcDimField_y,
	kMcDimField_z,				kMcDimField_za,				kMcDimField_zb,				kMcDimField_zc,
	// отверстия
	kMcDimField_A,				kMcDimField_B,				kMcDimField_C,				kMcDimField_CD,
	kMcDimField_D,				kMcDimField_E,				kMcDimField_EF,				kMcDimField_F,
	kMcDimField_FG,				kMcDimField_G,				kMcDimField_H,				kMcDimField_JS,
	kMcDimField_J,				kMcDimField_K,				kMcDimField_M,				kMcDimField_N,
	kMcDimField_P,				kMcDimField_R,				kMcDimField_S,				kMcDimField_T,
	kMcDimField_U,				kMcDimField_V,				kMcDimField_X,				kMcDimField_Y,
	kMcDimField_Z,				kMcDimField_ZA,				kMcDimField_ZB,				kMcDimField_ZC,
	kMcDimField_none = -1
};


// префикс размера
enum McDimSymbolEnum {
	kMcDimSymbolNone = 0,             // отсутствует
	kMcDimSymbolRadius,               // обозначение радиуса
	kMcDimSymbolDiameter,             // обозначение диаметра
	kMcDimSymbolSquare,               // обозначение квадрата
	kMcDimSymbolMetric,               // обозначение метрической резьбы
	kMcDimSymbolLeftGradient,         // обозначение уклона влево
	kMcDimSymbolRightGradient,        // обозначение уклона вправо
	kMcDimSymbolLeftConicity,         // обозначение конусности влево
	kMcDimSymbolRightConicity,        // обозначение конусности вправо
	kMcDimSymbolSRadius,              // SR
	kMcDimSymbolSDiameter,            // S + обозначение диаметра
	kMcDimSymbolP,                    // P в кружочке
	kMcDimSymbolM                     // M в кружочке
};


// форма отображения допусков
enum McDimToleranceViewEnum {
	kMcDimTolAll = 0,
	kMcDimTolValuesOnly,
	kMcDimTolFitInLine,
	kMcDimTolFitIn2Lines,
	kMcDimTolFieldOnly,
	kMcDimTolNone
};


// скобки
enum McDimBracketEnum {
	kMcDimBracketNone = 0,
	kMcDimBracketSquare,
	kMcDimBracketRound,
	kMcDimBracketAngular
};


// тип линейного размера
// влияет на обновление ассоциативных размеров
enum McLinearDimensionType {
	kMcDimTypeSimple = 1,
	kMcDimTypeHorizontal = 2,
	kMcDimTypeVertical = 3,
	kMcDimTypeAligned = 4
};


#ifndef SZ_VALUE_UNKNOWN
	#define SZ_VALUE_UNKNOWN -1e100
#endif
#ifndef SZ_TOL_UNKNOWN
	#define SZ_TOL_UNKNOWN -1
#endif


//////////////////////////////////////////////////////////////////////////
struct IMcDimension : public IMcEntity
{
public:
	// Значение размера
	//   fActual = false  - всегда возвращает натуральное значение (с чертежа)
	//   fActual = true   - если в тексте только число или пусто, вернет это число, иначе - SZ_VALUE_UNKNOWN
	virtual double getValue(bool fActual = true) = 0;
	virtual bool setValue(double Value) = 0;
	// Верхнее отклонение
	virtual double getES() = 0;                 // SZ_VALUE_UNKNOWN
	virtual void setES(double Value) = 0;
	// Нижнее отклонение
	virtual double getEI() = 0;                 // SZ_VALUE_UNKNOWN
	virtual void setEI(double Value) = 0;
	// Квалитет
	virtual int getQuality() = 0;               // SZ_TOL_UNKNOWN
	virtual void setQuality(int Value) = 0;
	// Поле допуска
	virtual McDimFieldEnum getField() = 0;
	virtual HRESULT setField(McDimFieldEnum Value) = 0;
	virtual HRESULT setField(LPCTSTR Value) = 0;    // например, "js"
	virtual McsString getFieldAndQuality() = 0;		// например, "H12", "H12/h12"
	virtual HRESULT setFieldAndQuality(LPCTSTR Value) = 0;
	// Для обозначений допусков сопряженных поверхностей
	virtual McsString getLower() = 0;
	virtual void setLower(LPCTSTR Value) = 0;
	virtual McsString getUpper() = 0;
	virtual void setUpper(LPCTSTR Value) = 0;

	// Масштаб измерения
	virtual double getDimScale() = 0;
	virtual HRESULT setDimScale(double Value) = 0;

	// Текст перед размером
	virtual McsString getPrefix() = 0;
	virtual void setPrefix(LPCTSTR Value) = 0;
	virtual McsString getText() = 0;
	virtual bool setText(LPCTSTR Value) = 0;
	// Символ перед размером
	virtual McDimSymbolEnum getSymbol() = 0;
	virtual void setSymbol(McDimSymbolEnum Value) = 0;
	// Текст после размера
	virtual McsString getSuffix() = 0;
	virtual void setSuffix(LPCTSTR Value) = 0;
	// Текст после отклонений
	virtual McsString getPostfix() = 0;
	virtual void setPostfix(LPCTSTR Value) = 0;
	// Текст под размером
	virtual McsString getFooter() = 0;
	virtual void setFooter(LPCTSTR Value) = 0;

	// Форма записи допусков
	virtual McDimToleranceViewEnum getTolView() = 0;
	virtual void setTolView(McDimToleranceViewEnum Value) = 0;
	// Размер в скобках
	virtual McDimBracketEnum getBrackets() = 0;
	virtual void setBrackets(McDimBracketEnum Value) = 0;
//	// Текст на полке
//	virtual bool getLeader() = 0;
//	virtual void setLeader(bool Value) = 0;
	// Текст в прямоугольнике
	virtual bool getRect() = 0;
	virtual void setRect(bool Value) = 0;
	// Положение текста
	virtual mcsPoint getTextPos() = 0;
	virtual void setTextPos(const mcsPoint& Value) = 0;
	virtual void setTextPosDefault() = 0;
	virtual bool getTextPosDefault() = 0;
	// Положение размерной линии
	virtual mcsPoint getLinePos() = 0;
	virtual void setLinePos(const mcsPoint& Value) = 0;
	// Координаты и направление стрелок
	virtual HRESULT getArrowEx(int Index, OUT mcsArrow& arrow) = 0;

	// Стиль размера
	virtual IMcDimStylePtr getStyle() = 0;
	virtual HRESULT setStyle(IN IMcDimStyle* pStyle) = 0;
	virtual HRESULT setStyleName(IN OPTIONAL LPCTSTR strStyleName = NULL) = 0;

	// a.kozlov
	// перенесено в IMcDimStyle::[gs]etColorText
// 	virtual COLORREF getTextColor() = 0;
// 	virtual void setTextColor(COLORREF Value) = 0;
	
	// Ассоциативность
	virtual bool getAssociative() = 0;
	virtual HRESULT setAssociative(IN bool Value, IN OPTIONAL const McGeometryParamArray* pids = NULL) = 0;
	// Действительное значение в getText и getValue
	virtual bool getReal() = 0;
	virtual void setReal(bool Value) = 0;

	// Разрывы в размерных линиях
	virtual HRESULT addBreak(IN int iLine,              // 0, 1 - выносные, 2 - размерная
													 IN double rPosition,       // положение центра разрыва
													 IN double rWidth) = 0;     // ширина разрыва
	virtual HRESULT delBreaks() = 0;

	virtual mcsVector getNormal() = 0;
	virtual HRESULT setNormal(const mcsVector& Value) = 0;
	virtual mcsPlane getPlane() = 0;

	virtual HRESULT GetGeometry(IMcGeometryBuilder *pGB) = 0;

	virtual bool isAngular() {return false;}

	// Угол поворота текста размера
	virtual double getTextRotation() = 0;
	virtual void setTextRotation(double Value) = 0;

		// Угол поворота оси ПСК текста размера
	virtual double getHorizRotation() = 0;
		// Если указать значение по умолчанию, то угод будет вычислен по оси X
		// текущей системы координат документа (ПСК/UCS), куда вставлен размер,
		// НО только в случае, если нормаль размера совпадает с осью Z ПСК
	virtual bool setHorizRotation(double Value = UNKNOWNVALUE) = 0;

		// true, если размер относится к параметрическим зависимостям
	virtual bool isConstraintDynamic() = 0;
};


//------------------------------------------------------------------------
// Линейный размер
struct IMcLinearDimension : virtual public IMcDimension
{
public:
	virtual mcsPoint getPosition(int Index) = 0;
	virtual HRESULT setPosition(int Index, const mcsPoint& Value) = 0;
	// Направление измерений
	virtual mcsVector getDirection() = 0;
	virtual HRESULT setDirection(const mcsVector& Value) = 0;
	// Выравнивание размера
	virtual McLinearDimensionType getType() = 0;
	virtual HRESULT setType(McLinearDimensionType Value) = 0;
	// Наклон выносных линий
	virtual mcsVector getOblique() = 0;
	virtual HRESULT setOblique(const mcsVector& Value) = 0;
};


//------------------------------------------------------------------------
// Радиальный размер
struct IMcRadialDimension : virtual public IMcDimension
{
public:
	virtual mcsPoint getPosition() = 0;
	virtual HRESULT setPosition(const mcsPoint& Value) = 0;
	virtual mcsPoint getCenter() = 0;
	virtual void setCenter(const mcsPoint& Value) = 0;
	virtual double getRadius() = 0;

		// см. описание в Object ARX
	virtual double getExtArcStartAngle() = 0;
	virtual double getExtArcEndAngle() = 0;
	virtual void setExtArcStartAngle(double Value) = 0;
	virtual void setExtArcEndAngle(double Value) = 0;
};


//------------------------------------------------------------------------
// Большой радиус
struct IMcHugeRadialDimension : virtual public IMcDimension
{
public:
	// точка на дуге
	virtual mcsPoint getPosition() = 0;
	virtual HRESULT setPosition(const mcsPoint& Value) = 0;
	// центр дуги
	virtual mcsPoint getCenter() = 0;
	virtual void setCenter(const mcsPoint& Value) = 0;
	// смещенный центр дуги
	virtual mcsPoint getMeanCenter() = 0;
	virtual void setMeanCenter(const mcsPoint& Value) = 0;
	// точка излома
	virtual mcsPoint getBreakPos() = 0;
	virtual void setBreakPos(const mcsPoint& Value) = 0;

	virtual double getRadius() = 0;
	
	// вектор oX ПСК для ОСК
	virtual mcsVector getXDirection() = 0;
	virtual HRESULT setXDirection(const mcsVector& Value) = 0;
};


//------------------------------------------------------------------------
// Диаметральный размер
struct IMcDiametralDimension : virtual public IMcDimension
{
public:
	virtual mcsPoint getPosition(int Index) = 0;
	virtual HRESULT setPosition(int Index, const mcsPoint& Value) = 0;
	virtual mcsPoint getCenter() = 0;
	virtual void setCenter(const mcsPoint& Value) = 0;
	virtual double getRadius() = 0;

		// см. описание в Object ARX
	virtual double getExtArcStartAngle() = 0;
	virtual double getExtArcEndAngle() = 0;
	virtual void setExtArcStartAngle(double Value) = 0;
	virtual void setExtArcEndAngle(double Value) = 0;
};


//------------------------------------------------------------------------
// Угловой размер
struct IMcAngularDimension : virtual public IMcDimension
{
public:
	virtual mcsPoint getPosition(int Index) = 0;
	virtual HRESULT setPosition(int Index, const mcsPoint& Value) = 0;
	virtual mcsPoint getCenter() = 0;
	virtual void setCenter(const mcsPoint& Value) = 0;
	// Ординатные угловые размеры
	virtual bool getOrdinate() = 0;
	virtual void setOrdinate(bool Value) = 0;
	virtual bool isAngular() override {return true;}
	virtual bool isNeedReverse() const = 0;
};


//------------------------------------------------------------------------
// Длина дуги
struct IMcArcDimension : virtual public IMcDimension
{
public:
	virtual mcsPoint getPosition(int Index) = 0;
	virtual HRESULT setPosition(int Index, const mcsPoint& Value) = 0;
	virtual mcsPoint getCenter() = 0;
	virtual void setCenter(const mcsPoint& Value) = 0;
	virtual double getRadius() = 0;
};


//------------------------------------------------------------------------
// Размер-подобие
// Строится как смещение от измеряемого объекта (сплайна, полилинии, эллипса, окружности, дуги или отрезка).
// Измеряет длину объекта между заданными точками.
//------------------------------------------------------------------------
struct IMcOffsetDimension : virtual public IMcDimension
{
public:
	// Флаги состояния McOffsetDimension
	#define DIM_OFFSET_CREATING				0x00000001	// Вставка размера в команде.
	#define DIM_OFFSET_FAILED				0x00000002	// Не удалось построить размер по заданным точкам и значению отступа
	#define DIM_OFFSET_DIMPOINTS_SWAPPED	0x00000004	// Точки DimFrom и DimTo поменялись местами в процессе построения offset-curve
	#define DIM_OFFSET_LENGTH_FIXED			0x00000008	// Не пересчитывать длину размера в BuildDimCurves
	#define DIM_OFFSET_SYNC_DWG_TO_MC_MODE	0x00000010	// Режим синхронизации dwg->Mc. Блокирует вызов writeEnabled

//------------------------------------------------------------------------
// Основные методы
//------------------------------------------------------------------------
	// Значение смещения со знаком
	// [+] - смещение в сторону поворота против часовой стрелки от направления вектора касательной в первой выбранной точке
	// [-] - смещение в сторону поворота по     часовой стрелке от направления вектора касательной в первой выбранной точке
	virtual double offsetValue() const = 0;
	virtual HRESULT setOffsetValue(double rOffset) = 0;

	// Параметры размера на образмериваемой кривой: параметры привязки и параметры кривой начало/промежуточная точка/конец
	virtual HRESULT getDimParameters(OUT McGeometryParam& geomParamFrom, OUT McGeometryParam& geomParamTo,
									OUT double& rCurveParamFrom, OUT double& rCurveParamInter, OUT double& rCurveParamTo) const = 0;
	virtual HRESULT setDimParameters(const McGeometryParam& geomParamFrom, const McGeometryParam& geomParamTo,
									double rCurveParamFrom, double rCurveParamInter, double rCurveParamTo) = 0;

//------------------------------------------------------------------------
// Дополнительные методы для синхронизации с dwg
//------------------------------------------------------------------------
	// Список кривых, представляющих геометрию самого размера
	virtual HRESULT getDimCurveList(OUT mcsGeomEntArray& arrCurves) const = 0;
	virtual HRESULT setDimCurveList(const mcsGeomEntArray& arrCurves) = 0;

	// Векторы касательных в точках геометрии размера: начало/середина/конец
	virtual HRESULT getDimDerivs(OUT mcsVector3d& vDerivFrom, OUT mcsVector3d& vDerivMiddle, OUT mcsVector3d& vDerivTo) const = 0;
	virtual HRESULT setDimDerivs(const mcsVector3d& vDerivFrom, const mcsVector3d& vDerivMiddle, const mcsVector3d& vDerivTo) = 0;

	// Точки геометрии размера: начало/середина/конец
	virtual HRESULT getDimPoints(OUT mcsPoint3d& ptFrom, OUT mcsPoint3d& ptMiddle, OUT mcsPoint3d& ptTo) const = 0;
	virtual HRESULT setDimPoints(const mcsPoint3d& ptFrom, const mcsPoint3d& ptMiddle, const mcsPoint3d& ptTo) = 0;

	// Векторы касательных в точках на образмериваемой кривой: начало/конец
	virtual HRESULT getCurveDerivs(OUT mcsVector3d& vDerivFrom, OUT mcsVector3d& vDerivTo) const = 0;
	virtual HRESULT setCurveDerivs(const mcsVector3d& vDerivFrom, const mcsVector3d& vDerivTo) = 0;

	// Точки на образмериваемой кривой: начало/конец
	virtual HRESULT getCurvePoints(OUT mcsPoint3d& ptFrom, OUT mcsPoint3d& ptTo) const = 0;
	virtual HRESULT setCurvePoints(const mcsPoint3d& ptFrom, const mcsPoint3d& ptTo) = 0;

	// Флаги состояния OffsetDimension
	virtual DWORD offsetState() const = 0;
	virtual HRESULT setOffsetState(DWORD dwState) = 0;

	// Измеренная длина
	virtual double measuredLength() const = 0;
	virtual HRESULT setMeasuredLength(double rLength) = 0;
};


//------------------------------------------------------------------------
// Ординатный размер
struct IMcOrdinateDimension : virtual public IMcDimension
{
public:
	virtual mcsPoint getOrigin() = 0;
	virtual void setOrigin(const mcsPoint& Value) = 0;
	virtual mcsPoint getPosition() = 0;
	virtual HRESULT setPosition(const mcsPoint& Value) = 0;
	virtual mcsVector getDirection() = 0;
	virtual HRESULT setDirection(const mcsVector& Value) = 0;
};


//------------------------------------------------------------------------
// Точка начала отсчета для ординатных размеров
struct IMcOrdinateBase : public IMcEntity
{
	virtual mcsPoint getPosition() = 0;
	virtual HRESULT setPosition(const mcsPoint& Value) = 0;
	virtual double getSize() = 0;
	virtual void setSize(double Value) = 0;
};


//////////////////////////////////////////////////////////////////////////
// Получение точек привязки
struct
__declspec(uuid("{F4D6735C-7FB2-4de8-AC83-728074D58630}"))
IMcDimensionSnap : public IUnknown
{
public:
	virtual HRESULT getNearestSnap(IN OUT mcsPoint& pnt, IN OUT mcsVector& dir, OUT int& id) = 0;
	virtual HRESULT setSnap(IN int id, IN const mcsPoint& pnt, IN const mcsVector& dir) = 0;
};

typedef MComQIPtr<IMcDimensionSnap>           IMcDimensionSnapPtr;


//////////////////////////////////////////////////////////////////////////
// Вспомогательный класс для работы с допусками
struct
MECHCTL_API		// реализация в MechCtl.dll
CTechSize {
public:
	CTechSize()
		: rVal(SZ_VALUE_UNKNOWN), m_bDefault(false)
	{
		uFld.custom.rES = uFld.custom.rEI = SZ_VALUE_UNKNOWN;
		uFld.standard.nQuality = SZ_TOL_UNKNOWN;
		uFld.standard.nField = kMcDimField_none;
	}
	CTechSize(double rValue, double rES = 0, double rEI = 0)
		: rVal(rValue), m_bDefault(false)
	{
		uFld.standard.nField = kMcDimField_none;
		uFld.standard.nQuality = SZ_TOL_UNKNOWN;
		uFld.custom.rES = rES;
		uFld.custom.rEI = rEI;
	}
	CTechSize(double rValue, McDimFieldEnum field, int nQuality)
		: m_bDefault(false)
	{
		uFld.standard.nField = field;
		uFld.standard.nQuality = nQuality;
		SetValue(rValue);
	}

// basic query functions
	double         T()   const;
	double         ES()  const { return uFld.custom.rES; }               // верхнее отклонение
	double         EI()  const { return uFld.custom.rEI; }               // нижнее отклонение
	double         Min() const;                                          // минимальное значение
	double         Max() const;                                          // максимальное значение
	double         Avg() const;                                          // среднее значение
	int            Quality() const { return (uFld.standard.nQuality); }  // квалитет
	McDimFieldEnum Field() const { return uFld.standard.nField; }        // поле допуска
	void           Field(LPTSTR strFieldName) const;
	double         Value() const { return rVal; }                        // значение размера

	void           allFields(OUT mcsStringArray& Result, IN bool fHole) const;          // список полей допуска
	void           allQualities(OUT mcsStringArray& Result) const;       // список квалитетов для выбранного поля допуска

// basic edit functions
	void           SetES(double rValue);
	void           SetEI(double rValue);
	void           SetQuality(int nValue);
	bool           SetField(McDimFieldEnum nValue);
	bool           SetField(LPCTSTR strFieldName);
	void           SetValue(double rNewValue);
	void           Clear();

// operator helpers
	CTechSize  operator + (const CTechSize& op) const { CTechSize tsRes(*this); tsRes += op; return tsRes; }
	CTechSize  operator + (const double op) const { CTechSize tsRes(*this); tsRes += op; return tsRes; }
	CTechSize& operator +=(const CTechSize& op);
	CTechSize& operator +=(const double op) { rVal += op; return *this; }
	CTechSize  operator - (const CTechSize& op) const { CTechSize tsRes = -op; return (*this) + tsRes; }
	CTechSize  operator - (const double op) const { CTechSize tsRes = *this; tsRes.rVal -= op; return tsRes; }
	CTechSize& operator -=(const CTechSize& op) { CTechSize tmp = -op; return (*this) += tmp; }
	CTechSize& operator -=(const double op) { rVal -= op; return *this; }
	CTechSize  operator -() const;
	bool       operator ==(const CTechSize& op) {
		return m_bDefault == op.m_bDefault &&
			Equ(rVal, op.rVal, 1e-5) && Equ(ES(), op.ES(), 1e-5) && Equ(EI(), op.EI(), 1e-5);
	}
	bool       operator !=(const CTechSize& op) {
		return m_bDefault != op.m_bDefault ||
			!Equ(rVal, op.rVal, 1e-5) || !Equ(ES(), op.ES(), 1e-5) || !Equ(EI(), op.EI(), 1e-5);
	}
	bool       operator ==(const double op) { return op >= rVal+EI() && op <= rVal+ES(); }

// additional functions
	bool      IsStandard() const { return Quality() != SZ_TOL_UNKNOWN && Field() != kMcDimField_none; }
	McsString GetDescription(LPCTSTR lpszDevStart = _T("("),
	                         LPCTSTR strDevDelim = _T("/"),
	                         LPCTSTR strDevEnd = _T(")")) const;

// streaming
	HRESULT read(IMcsStream* pStream);
	HRESULT write(IMcsStream* pStream) const;

// GUI
	HRESULT edit(
		HWND hParent = NULL,      // родительское окно диалога
		bool bFixedType = true);  // не изменять тип размера (вал или отверстие)

	bool m_bDefault;		//свободный допуск (GetDescription пишет только номинал)

protected:
	double rVal;
	struct {
		struct { int nQuality; McDimFieldEnum nField; } standard;
		struct { double rES, rEI; } custom;
	} uFld;
#ifdef _USE_OLD_MCCVT
	friend struct McCvt;
#endif
};


//////////////////////////////////////////////////////////////////////////
// Разрыв размерной линии
struct McDimensionBreak {
	byte nLine;        // индекс размерной линии
	double rPosition;  // положение средней точки разрыва на линии
	double rWidth;     // ширина разрыва в мм без учета масштаба
};
typedef McsArray<McDimensionBreak, const McDimensionBreak&> McDimensionBreaks;


//////////////////////////////////////////////////////////////////////////
// Direct access to dimension's fields
struct
__declspec(uuid("{AA070B91-1D65-4035-8137-049A12D6C52F}"))
McDimensionData : virtual public IMcObject {
public:
	int m_iVersion;                 // версия

	//MCS_DIM {
	int m_iDimtype;                 // тип размера
	McDimSymbolEnum m_nSymbol;      // символ перед значением
	McDimToleranceViewEnum m_nTolView;  // способ записи допусков
	McDimBracketEnum m_nBrackets;   // вид скобок вокруг текста
	McsString m_csPrefix;           // текст перед размером
	McsString m_csText;             // размерный текст
	McsString m_csSuffix;           // текст после размера
	McsString m_csPostfix;          // обозначение сноски
	McsString m_csTolerance;        // квалитет и поле допуска
	McsString m_csES;               // верхнее отклонение
	McsString m_csEI;               // нижнее отклонение
	McsString m_csFooter;           // текст под размером
	// } MCS_DIM
	double m_rValue;                // действительное значение
	double m_rOblique;              // угол наклона выносных линий, рад
	double m_rTextRotation;         // угол поворота текста, рад
	double m_rHorizRotation;        // угол поворота полки текста, рад (Radial/Diametral)

	//Geometry
	mcsPoint m_pntText;             // точка вставки размерного текста
	mcsPoint m_pntLine;             // точка, через которую проходит размерная линия
	mcsPoint m_pnt[4];              // опорные точки (зависят от типа размера)
	mcsVector m_vcNormal;
	mcsVector m_vecDirection;       // направление измерения
	CTechSize m_sz;                 // величина с пределными отклонениями

	//Style
	McsString m_strDimStyleName;    // имя размерного стиля
	DWORD m_dwFlags;                // флаги свойств
		#define MCSDIM_BF_LOADED        0x00000001   // размер зачитан хотя бы раз в этой сессии
		#define MCSDIM_BF_LEADER_       0x00000002   // текст на полке
		#define MCSDIM_BF_RECT_         0x00000004   // текст в прямоугольнике
		#define MCSDIM_BF_REAL          0x00000008   // действительное значение
		#define MCSDIM_BF_ZLEAD_        0x00000010   // показывать ведущий нуль
		#define MCSDIM_BF_ZTRAIL_       0x00000020   // показывать ведомые нули
		#define MCSDIM_BF_XLINE1_       0x00000040   // показывать первую выносную линию
		#define MCSDIM_BF_XLINE2_       0x00000080   // показывать вторую выносную линию
		#define MCSDIM_BF_DLINE1_       0x00000100   // показывать первую размерную линию
		#define MCSDIM_BF_DLINE2_       0x00000200   // показывать вторую размерную линию
		#define MCSDIM_BF_TLEAD_        0x00000400   // показывать ведущий нуль в предельных отклонениях
		#define MCSDIM_BF_TTRAIL_       0x00000800   // показывать ведомый нуль в предельных отклонениях
		#define MCSDIM_BF_AUTOSCALE     0x00001000   // брать размер с привязок
		#define MCSDIM_BF_FROZEN        0x00002000   // не обновлять размер, тк он редактировался через проперти
		#define MCSDIM_BF_DDEXPORT      0x00004000   // размер экспортирован из SL через DirectDraw
		#define MCSDIM_BF_DEFTEXTPOS    0x00008000   // использовать положение текста по умолчанию
		#define MCSDIM_BF_MODIFIED      0x00010000   // объект изменен, нужно вызывать update
		#define MCSDIM_BF_ORDINATE      0x00020000   // ординатный размер
		#define MCSDIM_BF_UNITS         0x00040000   // отображать единицы измерения
		#define MCSDIM_BF_HIDELEADER_   0x00080000   // полка невидима
		#define MCSDIM_BF_INTEGRITY_CHECK 0x00100000 // #2780. Требуется проверка целостности размера при открытии документа.
		#define MCSDIM_BF_SPACE_AFTER_PREFIX 0x00200000 // #3885. Автоматический пробел после непустого префикса.
		#define MCSDIM_BF_NO_END_EXTENSION 0x00400000 // #4536. Не учитываются терминальные пробелы в суффиксе (Будем добавлять код дроби "\S;" в конец размерного текста)
													  // #4561, Поднять размер с нижним допуском. (Будем добавлять "поднимающий" пробел "\\HAx; \\HBx;" в конец размерного текста)
		#define MCSDIM_BF_SPACE_BEFORE_TOL 0x00800000 // #8311. Пробел между значением и допуском
		#define MCSDIM_BF_DUAL_SNAP_ID  0x01000000   // #9295. Коррекция привязок. Несовпадение идентификаторов id idComplex в GemetryParam.
		#define MCSDIM_BF_HEIGHT_H2_H1  0x02000000   // #11893. Установка высоты текста без восстанавливающего тега : "\\H2...\\H1"  ->  "{\\H2 ...}"
		#define MCSDIM_BF_NO_AUTO_VPDSCALE 0x04000000 // #15638. Запрет на автоматическое управление масштабом измерений размером, установленным в видовой экран.

	DWORD m_dwStyleFlags;
		#define MCSDIMSTY_BF_DIMALT     0x00000001   // показывать измерение в альтернативных единицах
		#define MCSDIMSTY_BF_DIMLIM     0x00000002   // показывать пределы измерения
		#define MCSDIMSTY_BF_SEPARRHEAD 0x00000004   // показывать различные первую и свторую стрелки (DIMSAH). стрелка лидера сюда не входит
		#define MCSDIMSTY_BF_SUPDIM1    0x00000008   // подавить первую размерную линию и стрелку
		#define MCSDIMSTY_BF_SUPDIM2    0x00000010   // подавить вторую размерную линию и стрелку
		#define MCSDIMSTY_BF_SUPEXT1    0x00000020   // подавить первую выносную линию
		#define MCSDIMSTY_BF_SUPEXT2    0x00000040   // подавить вторую выносную линию
		#define MCSDIMSTY_BF_SUPDIMOX   0x00000080   // подавить размерные линии, выходящие за выносные
		#define MCSDIMSTY_BF_TIXORIENT  0x00000100   // направление текста размера внутри выносных линий (DIMTIH): 0 -- по направлению размерной линии;   1 -- горизонтально
		#define MCSDIMSTY_BF_TIXPLACE   0x00000200   // размещение текста размера внутри выносных линий (DIMTIX):  0 -- между выносными, если есть место; 1 -- между выносными
		#define MCSDIMSTY_BF_TOFL       0x00000400   // рисовать ли размерную линию между выносныи, когда текст вне размерных линий (DIMTOFL)
		#define MCSDIMSTY_BF_TOXTXTORI  0x00000800   // направление размерного текста, находящегося не внутри выносных (DIMTOH): 0 -- вдоль размерной линии; 1 -- горизонтально
		#define MCSDIMSTY_BF_TOL        0x00001000   // показывать толерансы (допуски)
		#define MCSDIMSTY_BF_FXLON      0x00002000   // включить режим выносных линий фиксированной длины (в направлении от размерной линии к образмериваемому объекту)
		#define MCSDIMSTY_BF_DIMUPT     0x00004000   // размещение текста вручную
		#define MCSDIMSTY_BF_TXTDIR     0x00008000   // dimtxtdirection (???)
		#define MCSDIMSTY_BF_RECT       0x00010000   // включается при dimgap < 0

#define MAP_VAR(vartype, varname, dimname, def_val, metric_def_val, res1, res2) vartype varname;
#define MAP_VAR_ArrowId MAP_VAR
#define MAP_VAR_Color MAP_VAR
#define MAP_VAR_LineWeight MAP_VAR
#define MAP_VAR_StyleId MAP_VAR
#define MAP_VAR_LineTypeId MAP_VAR
#define MAP_FLG(flagname, dimname, def_val, metric_def_val, res1, res2)
#include "McDimensionDataMapVariables.h"
#undef MAP_VAR_LineTypeId
#undef MAP_VAR_StyleId
#undef MAP_VAR_LineWeight
#undef MAP_VAR_Color
#undef MAP_VAR_ArrowId
#undef MAP_VAR
#undef MAP_FLG

	bool flags(DWORD dwMask) {return (0 != (dwMask & m_dwFlags));}
	bool styleFlags(DWORD dwMask) {return (0 != (dwMask & m_dwStyleFlags));}

	McGeometryParam m_Snaps[3];     // привязки опорных точек
	McDimensionBreaks m_Breaks;     // разрывы в размерных линиях
	McsString m_csCheck;            // последнее значение размерной строки для контроля изменений
	double m_rXAng1, m_rXAng2;      // углы начала и конца дуги для радиального и диаметрального размеров

	mcsMatrix m_mx;

	bool m_bConstraintDynamic; // R/O, Gate -> Dim only

	bool m_bArrowFirstFlipped;      // флаг разворота первой стрелки
	bool m_bArrowSecondFlipped;     // флаг разворота второй стрелки

	MECHCTL_API McDimensionData();

	// Обновляет предельные отклонения после изменения номинала
	virtual void UpdateDimData() = 0;
	// Обновляет значение размера после изменения текста
	virtual void UpdateDimValue() = 0;
	// Обновляет текст размера после изменения номинала
	virtual void UpdateDimText() = 0;
	// Исправление несовпадения идентификаторов в привязках
	virtual bool FixDualSnapId() = 0;
};

typedef MComQIPtr<McDimensionData> McDimensionDataPtr;



