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

#include "mcsTypes.h"
#include "mcsGeometry.h"
#include "DynLoadMacro.h"
#include "IMcNativeGate.h"
#include <comdef.h>           // IUnknownPtr
#include "McApis.h"
#include "IMcMeasure.h"
#include "MCSPID.h"

//---------------------------------------------------------------------------
#define MC_HIGHLIGHT_COLOR  ((COLORREF)0x0000ff00)
#define MC_HIGHLIGHT_COLOR2 ((COLORREF)0x00ff0000)

//---------------------------------------------------------------------------
MECHCTL_API McsString McGetUnplottedLayerName();
#define MCS_DEF_LAYER_UNPLOTTED _T("CS_UNPLOTTED")// System

#define MCS_LAYER_UNPLOTTED McGetUnplottedLayerName()
#define MCS_LAYER_INVISIBLE _T("CS_INVISIBLE")

// Использовать СПДС-схему назначения масштаба.
// В настройках появляется параметр "Редактирование\Глобальный масштаб применять для элементов оформления".
//   Если его включить, масштаб будет работать как СПДС. Появится кнопка масштаба.
//   Если выключить, масштаб будет работать как в Механиксе.
// Параметр сохраняется в документ.
MECHCTL_API bool McSPDSLikeScale(IMcDocument* pDoc, MCS_STANDARD std);
#define MCS_SPDSLIKE_SCALE (McSPDSLikeScale(NULL, MCS_STD_CUSTOM))

//////////////////////////////////////////////////////////////////////////
IMCS_DECL_INTERFACE(IMcTextConverter,       "00000001-0007-AAAA-AAAA-050B00000000")
static const GUID CLSID_McTextConverter = { 0x7E6DFDF5, 0xCDD0, 0x43b4, { 0xAF, 0x6B, 0x4A, 0x6C, 0xBE, 0x00, 0xE6, 0x1B } };

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcTextStyle
//---------------------------------------------------------------------------
// {30136A80-81DD-43c2-8CF2-48EDE7D363F5}
static const GUID IID_IMcTextStyle = 
{ 0x30136a80, 0x81dd, 0x43c2, { 0x8c, 0xf2, 0x48, 0xed, 0xe7, 0xd3, 0x63, 0xf5 } };

class __declspec(uuid("30136A80-81DD-43c2-8CF2-48EDE7D363F5"))
IMcTextStyle : public virtual IMcObject
{
public:
	virtual LPCTSTR getName() = 0;
	virtual LPCTSTR getFontName() = 0;
	virtual bool    isTrueType() = 0;
	virtual bool    isItalic() = 0;
	virtual bool    isBold() = 0;
	virtual double  getHeight() = 0;
	virtual double  getOblique() = 0;
	virtual double  getXScaling() = 0;
	virtual int     getCharset() = 0;
	virtual int     getPitchAndFamily() = 0;
	virtual bool    isBackward() = 0;
	virtual bool    isUpsideDown() = 0;
	virtual bool    isVertical() = 0;

	virtual void setHeight(double r) = 0;
	virtual void setOblique(double r) = 0;
	virtual void setXScaling(double r) = 0;

	// Инициализация TrueType текстового стиля
	virtual void set(LPCTSTR stName, LPCTSTR stFontName, bool isItalic, bool isBold, int iCharset, int iPitchAndFamily) = 0;
	// Инициализация векторного (shx) текстового стиля
	virtual void set(LPCTSTR stName, LPCTSTR stFontName) = 0;

	virtual mcsPoint2d GetMTextBox(LPCTSTR stText, double width = 0) = 0;
	// Параметр rDirection определяет направление текста
	// На данный момент имеет значение только для 2D Инвентора (значение имеет
	// только кратность угла PI / 2), где длина текста в разных направлениях
	// может значительно отличаться
	virtual double  GetDTextLength(LPCTSTR stText, double rDirection = 0) = 0;

	virtual double  getRealOblique()
		{ return getOblique(); }
	virtual double  getRealXScaling()
		{ return getXScaling(); }

	virtual HRESULT Update() = 0;
};
typedef MComQIPtr<IMcTextStyle> IMcTextStylePtr;

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcDimStyle
//---------------------------------------------------------------------------
enum MCS_DIMSTYLE_TYPE
{
  Mcs_DimSt_Common,
  Mcs_DimSt_Linear,
  Mcs_DimSt_Angular,
  Mcs_DimSt_Radial,
  Mcs_DimSt_Diametral,
  Mcs_DimSt_Ordinate,
  Mcs_DimSt_Leader,
};
//....................................
enum McsDimVertTextAlignEnum // DIMTAD
{
	// вертикальное расположение текста размера относительно размерной линии
	kMcsDimVertTextAlign_Centered = 0, // "По центру"
	kMcsDimVertTextAlign_Above    = 1, // "Над линией"
	kMcsDimVertTextAlign_Outer    = 2, // "Снаружи"
	kMcsDimVertTextAlign_JIS      = 3, // "Согласно JIS"
	kMcsDimVertTextAlign_Below    = 4, // "Снизу"
};
//....................................
enum McsDimAltFormatting // dimaltu
{
	kMcsDimAltFmt_Scientific    = 1,
	kMcsDimAltFmt_Decimal       = 2,
	kMcsDimAltFmt_Engineering   = 3,
	kMcsDimAltFmt_ArchStack     = 4, // Architectural (stacked)
	kMcsDimAltFmt_FracStack     = 5, // Fractional (stacked)
	kMcsDimAltFmt_Architectural = 6,
	kMcsDimAltFmt_Fractional    = 7,
	kMcsDimAltFmt_MSWinDesktop  = 8, // environment settings
};
//....................................
enum McsDimArrowsTextFit // dimatfit
{
	kMcsDimArrowsTextFit_TextAndArrowsOutside  = 0, // Moves text and arrows outside extension lines.
	kMcsDimArrowsTextFit_ArrowsThenTextOutside = 1, // Moves arrows, then text, outside extension lines.
	kMcsDimArrowsTextFit_TextThenArrowsOutside = 2, // Moves text, then arrows, outside extension lines.
	kMcsDimArrowsTextFit_TextOrArrowsBestFit   = 3, // Moves text or arrows for best fit.
};
enum McsDimAngFormatting // dimaunit -- форматирование для угловых размеров
{
	kMcsDimAngFmt_DecimalDegrees        = 0, // Decimal Degrees
	kMcsDimAngFmt_DegreesMinutesSeconds = 1, // Degrees-Minutes-Seconds
	kMcsDimAngFmt_Gradians              = 2, // Gradians
	kMcsDimAngFmt_Radians               = 3, // Radians
	kMcsDimAngFmt_Surveyor              = 4, // Surveyor's Units
};
enum McsDimFracFormatting // dimfrac -- форматирование дробей для DIMLUNIT == 4 или 5
{
	kMcsDimFracFmt_HorizontalStacked = 0,
	kMcsDimFracFmt_DiagonalStacked   = 1,
	kMcsDimFracFmt_NotStacked        = 2,
};
enum McsDimTxtHorzPos // dimjust
{
	kMcsDimTxtHorzPos_AboveDimCentered   = 0, // Centered above the dimension line
	kMcsDimTxtHorzPos_By1stExt           = 1, // By the first extension line
	kMcsDimTxtHorzPos_By2ndExt           = 2, // By the second extension line
	kMcsDimTxtHorzPos_AboveDimPrll1stExt = 3, // Above the dimension line, parallel to the first extension line
	kMcsDimTxtHorzPos_AboveDimPrll2ndExt = 4, // Above the dimension line, parallel to the second extension line
};
enum McsDimFormattingNonAng { // dimlunit
	kMcsDimFormattingNonAng_Scientific   = 1, // Scientific
	kMcsDimFormattingNonAng_Decimal      = 2,
	kMcsDimFormattingNonAng_Engineering  = 3,
	kMcsDimFormattingNonAng_ArchStack    = 4, // Architectural (stacked/not ctacked) see McsDimFracFormatting
	kMcsDimFormattingNonAng_FracStack    = 5, // Fractional    (stacked/not stacked) see McsDimFracFormatting
	kMcsDimFormattingNonAng_MSWinDesktop = 6, // environment settings
};
enum McsDimTextMovement {
	kMcsDimTextMovement_TextMovesDimLine    = 0,
	kMcsDimTextMovement_TextAddsLeader      = 1,
	kMcsDimTextMovement_TextDoesntAddLeader = 2,
};
enum McsDimTextFill {
	kMcsDimTextFill_NoFill        = 0,
	kMcsDimTextFill_BGColor       = 1,
	kMcsDimTextFill_ByDIMTFILLCLR = 2,
};
enum McsArcSymbolPos
{
	kMcsArcSymbolPos_BeforeDimText = 0,
	kMcsArcSymbolPos_AboveDimText  = 1,
	kMcsArcSymbolPos_NotDisplayed  = 2,
};

// {5376E492-CA0F-45c8-8493-D1E6DB76EACE}
static const GUID IID_IMcDimStyle = 
{ 0x5376e492, 0xca0f, 0x45c8, { 0x84, 0x93, 0xd1, 0xe6, 0xdb, 0x76, 0xea, 0xce } };

class __declspec(uuid("5376E492-CA0F-45c8-8493-D1E6DB76EACE"))
IMcDimStyle : public virtual IMcObject
{
public:
	// название стиля
	virtual McsString getName() = 0;
	// Подтип размерного стиля
	virtual HRESULT setStyleType(MCS_DIMSTYLE_TYPE type) = 0;
	virtual MCS_DIMSTYLE_TYPE getStyleType() = 0;
	// Число знаков после запятой {{
	// dimadec -- точность на угловых размерах
	virtual int getPrecisionAngular() = 0;
	virtual HRESULT setPrecisionAngular(int Value) = 0;
	// dimdec -- точность на линейных размерах (точнее -- для не-угловых)
	virtual int getPrecisionLinear() = 0;
	virtual HRESULT setPrecisionLinear(int Value) = 0;
	// dimaltd -- точность для альтернативных единиц (на угловые/не угловые не разделяется)
	virtual int getPrecisionAlt() = 0;
	virtual HRESULT setPrecisionAlt(int Value) = 0;
	// dimtdec -- точность для предельных отклонений
	virtual int getPrecisionTol() = 0;
	virtual HRESULT setPrecisionTol(int Value) = 0;
	// dimalttd -- точность для предельных отклонений в альетрнативных единицах
	virtual int getPrecisionTolAlt() = 0;
	virtual HRESULT setPrecisionTolAlt(int Value) = 0;
	// если dimalt установлено в true, покажет getPrecisionAlt,
	// иначе getPrecisionAngular для угловых размеров и getPrecisionLinear для любых других
	virtual int getPrecisionActual() = 0;
	virtual HRESULT setPrecisionActual(int Value) = 0;
	// }} Число знаков после запятой

	// Тип стрелки
	virtual MCS_ARROW getArrow(int Index) = 0;                     // dimblk1, dimblk2
	// если данный метод 
	virtual HRESULT setArrow(int Index, MCS_ARROW Value) = 0;
	// вид стрелок для режима dimsah = false. для true смотреть разные стрелки по отдельности
	virtual MCS_ARROW getArrowBoth() = 0;                          // dimblk
	// установить обе стрелки в одинаковый вид. сбросить флаг разных стрелок
	virtual HRESULT setArrowBoth(MCS_ARROW Value) = 0;             // dimblk+dimsah
	// получить/установить режим разных стрелок
	virtual bool getSeparateArrowheads() = 0;                      // dimsah
	virtual HRESULT setSeparateArrowheads(bool Value) = 0;
	// стрелка для выноски
	virtual MCS_ARROW getArrowLeader() = 0;                        // dimldrblk
	virtual HRESULT setArrowLeader(MCS_ARROW Value) = 0;
	// Размер стрелки
	virtual double getArrowSize() = 0;                             // dimasz
	virtual HRESULT setArrowSize(double Value) = 0;
	// Высота текста
	virtual double getTextHeight() = 0;                            // dimtxt
	virtual HRESULT setTextHeight(double Value) = 0;
	// Множитель высоты текста (dimtxt) для предельных отклонений  // dimtfac
	virtual double getTolScale() = 0;
	virtual HRESULT setTolScale(double Value) = 0;
	// Десятичный разделитель
	virtual TCHAR getDecimalSep() = 0;                             // dimdsep
	virtual HRESULT setDecimalSep(TCHAR Value) = 0;
	// Отображение выносных линий
	virtual bool getExtensionLine(int Index) = 0;                  // dimse1, dimse2
	virtual HRESULT setExtensionLine(int Index, bool Value) = 0;
	// Отображение размерных линий
	virtual bool getDimensionLine(int Index) = 0;                  // dimsd1, dimsd2
	virtual HRESULT setDimensionLine(int Index, bool Value) = 0;
	// Минимальное расстояние между размерными полками (напр. для базовых размеров)
	virtual double getInterval() = 0;                              // dimdli
	virtual HRESULT setInterval(IN double Value) = 0;
	// Показывать ведущие и ведомые нули (в начале и в конце числа)
	virtual bool getLeadZerosLinear() = 0;                         // !(dimzin & 4)
	virtual HRESULT setLeadZerosLinear(bool Value) = 0;
	virtual bool getTrailZerosLinear() = 0;                        // !(dimzin & 8)
	virtual HRESULT setTrailZerosLinear(bool Value) = 0;
	virtual bool getLeadZerosAngular() = 0;                        // !(dimazin & 1)
	virtual HRESULT setLeadZerosAngular(bool Value) = 0;
	virtual bool getTrailZerosAngular() = 0;                       // !(dimazin & 2)
	virtual HRESULT setTrailZerosAngular(bool Value) = 0;
	virtual bool getLeadZerosAlt() = 0;                            // !(dimaltz & 4)
	virtual HRESULT setLeadZerosAlt(bool Value) = 0;
	virtual bool getTrailZerosAlt() = 0;                           // !(dimaltz & 8)
	virtual HRESULT setTrailZerosAlt(bool Value) = 0;
	virtual bool getLeadZerosLinearTol() = 0;                      // !(dimtzin & 4)
	virtual HRESULT setLeadZerosLinearTol(bool Value) = 0;
	virtual bool getTrailZerosLinearTol() = 0;                     // !(dimtzin & 8)
	virtual HRESULT setTrailZerosLinearTol(bool Value) = 0;
	virtual bool getLeadZerosAltTol() = 0;                         // !(dimalttz & 4)
	virtual HRESULT setLeadZerosAltTol(bool Value) = 0;
	virtual bool getTrailZerosAltTol() = 0;                        // !(dimalttz & 8)
	virtual HRESULT setTrailZerosAltTol(bool Value) = 0;
	// подавление нулей футов и дюймов на дюймовых форматах
	virtual bool getSuppressZeroFeet() = 0;
	virtual HRESULT setSuppressZeroFeet(bool Value) = 0;
	virtual bool getSuppressZeroInches() = 0;
	virtual HRESULT setSuppressZeroInches(bool Value) = 0;
	virtual bool getSuppressZeroFeetTol() = 0;
	virtual HRESULT setSuppressZeroFeetTol(bool Value) = 0;
	virtual bool getSuppressZeroInchesTol() = 0;
	virtual HRESULT setSuppressZeroInchesTol(bool Value) = 0;
	virtual bool getSuppressZeroFeetAlt() = 0;
	virtual HRESULT setSuppressZeroFeetAlt(bool Value) = 0;
	virtual bool getSuppressZeroInchesAlt() = 0;
	virtual HRESULT setSuppressZeroInchesAlt(bool Value) = 0;
	virtual bool getSuppressZeroFeetAltTol() = 0;
	virtual HRESULT setSuppressZeroFeetAltTol(bool Value) = 0;
	virtual bool getSuppressZeroInchesAltTol() = 0;
	virtual HRESULT setSuppressZeroInchesAltTol(bool Value) = 0;
	// Имя текстового стиля
	virtual LPCTSTR getTextStyle() = 0;                            // dimtxsty
	virtual HRESULT setTextStyle(LPCTSTR Value) = 0;
	// Вертикальное выравнивание дробей относительно текста        // dimtolj
	virtual McsDimTolVertJustifyEnum getTolVertJustify() = 0;
	virtual HRESULT setTolVertJustify(McsDimTolVertJustifyEnum Value) = 0;
	// Вертикальное выравнивание текста относительно разм. линии   // dimtad
	virtual McsDimVertTextAlignEnum getDimTextVertAlign() = 0;
	virtual HRESULT setDimTextVertAlign(McsDimVertTextAlignEnum Value) = 0;
	// убрано в пользу getMcsDimTextMovement
//	// Текст на полке
//	virtual bool getLeader() = 0;
//	virtual void setLeader(bool Value) = 0;
	// Масштаб
	virtual double getScale()
		{ return 1.0; }
	virtual void setScale(double Value)
		{ }
	// Масштаб измерений (не масштаб размера)                      // dimlfac
	virtual double  getDimScale() { return 1.0; }
	virtual HRESULT setDimScale(IN double Value) { return E_NOTIMPL; }
	virtual double  getDimScaleAlt() { return 1.0; } // масштаб измерений для альт. единиц // dimaltf
	virtual HRESULT setDimScaleAlt(IN double Value) { return E_NOTIMPL; }
	// Расстояние от текста до размерной линии                     // dimgap
	virtual double  getTextOffset() = 0;
	virtual HRESULT setTextOffset(double Value) = 0;
	// Форматирование размерного текста по правилам стиля
	virtual McsString toString(IN double Value) { return McsString().Format(_T("%g"), Value); }
	// Размещение текста вручную
	virtual bool    getDimupt() = 0;
	virtual HRESULT setDimupt(IN bool Value) = 0;
	virtual bool    getIsAlternative() = 0;
	virtual HRESULT setIsAlternative(IN bool Value) = 0;
	virtual McsString getAltPost() = 0;
	virtual HRESULT setAltPost(IN const McsString& Value) = 0;
	virtual McsString getPost() = 0;
	virtual HRESULT setPost(IN const McsString& Value) = 0;
	virtual McsDimArrowsTextFit getArrowsTextFit() = 0;
	virtual HRESULT setArrowsTextFit(IN McsDimArrowsTextFit Value) = 0;
	virtual double  getCenterMarks() = 0;
	virtual HRESULT setCenterMarks(IN double Value) = 0;
	virtual COLORREF getColorText() = 0;
	virtual HRESULT  setColorText(COLORREF Value) = 0;
	virtual COLORREF getColorLinesDim() = 0;
	virtual HRESULT  setColorLinesDim(COLORREF Value) = 0;
	virtual COLORREF getColorLinesExt() = 0;
	virtual HRESULT  setColorLinesExt(COLORREF Value) = 0;
	virtual double  getDimLinesExtend() = 0;
	virtual HRESULT setDimLinesExtend(IN double Value) = 0;
	virtual double  getExtLinesExtend() = 0;
	virtual HRESULT setExtLinesExtend(IN double Value) = 0;
	virtual double  getExtLinesOffset() = 0;
	virtual HRESULT setExtLinesOffset(IN double Value) = 0;
	virtual McsDimTxtHorzPos getDimTxtHorzPos() = 0;
	virtual HRESULT setDimTxtHorzPos(IN McsDimTxtHorzPos Value) = 0;
	virtual bool    getDisplayDimLimits() = 0;
	virtual HRESULT setDisplayDimLimits(IN bool Value) = 0;
	virtual McsDimAltFormatting getDimAltFormatting() = 0;           // dimaltu
	virtual HRESULT setDimAltFormatting(IN McsDimAltFormatting Value) = 0;
	virtual McsDimAngFormatting getDimAngFormatting() = 0;           // dimaunit
	virtual HRESULT setDimAngFormatting(IN McsDimAngFormatting Value) = 0;
	virtual McsDimFracFormatting getDimFracFormatting() = 0;
	virtual HRESULT setDimFracFormatting(IN McsDimFracFormatting Value) = 0;
	virtual McsDimFormattingNonAng getDimFormattingNonAngular() = 0; // dimlunit
	virtual HRESULT setDimFormattingNonAngular(IN McsDimFormattingNonAng Value) = 0;
	virtual int     getLineWeightDim() = 0;                          // dimlwd
	virtual HRESULT setLineWeightDim(IN int Value) = 0;
	virtual int     getLineWeightExt() = 0;                          // dimlwe
	virtual HRESULT setLineWeightExt(IN int Value) = 0;
	virtual double  getRound() = 0;                                  // dimrnd
	virtual HRESULT setRound(IN double Value) = 0;
	virtual double  getAltRound() = 0;                               // dimaltrnd
	virtual HRESULT setAltRound(IN double Value) = 0;
	virtual bool    getSuppressDimLinesOutsideExtLines() = 0;        // dimsoxd
	virtual HRESULT setSuppressDimLinesOutsideExtLines(IN bool Value) = 0;
	// Text Inside eXtension lines Orientation: false -- Aligned with dimension line; true -- Horizontal
	virtual bool    getTIXOrientation() = 0;                         // dimtih
	virtual HRESULT setTIXOrientation(IN bool Value) = 0;
	// Text Inside eXtension lines Placement: false -- Inside extension lines if there is room; true -- Inside extension lines
	virtual bool    getTIXPlacement() = 0;                           // dimtix
	virtual HRESULT setTIXPlacement(IN bool Value) = 0;
	virtual double  getTolMinus() = 0;                               // dimtm
	virtual HRESULT setTolMinus(IN double Value) = 0;
	virtual double  getTolPlus() = 0;                                // dimtp
	virtual HRESULT setTolPlus(IN double Value) = 0;
	virtual McsDimTextMovement getMcsDimTextMovement() = 0;          // dimtmove
	virtual HRESULT setMcsDimTextMovement(IN McsDimTextMovement Value) = 0;
	virtual bool    getDrawDimLineBtwExtLines() = 0;                 // dimtofl
	virtual HRESULT setDrawDimLineBtwExtLines(IN bool Value) = 0;
	// направление размерного текста вне выносных линий: false -- выровнено по размерной линии; true -- горизонтально
	virtual bool    getDimTxtOutExtOrientation() = 0;                // dimtoh
	virtual HRESULT setDimTxtOutExtOrientation(IN bool Value) = 0;
	virtual bool    getTol() = 0;                                    // dimtol
	virtual HRESULT setTol(IN bool Value) = 0;
	virtual double  getTickSize() = 0;                               // dimtsz
	virtual HRESULT setTickSize(IN double Value) = 0;
	virtual double  getDimTextVertPosition() = 0;                    // dimtvp
	virtual HRESULT setDimTextVertPosition(IN double Value) = 0;
	virtual bool    getFixedLenExtLines() = 0;                       // dimfxlon -- вкл/выкл режима fxl
	virtual HRESULT setFixedLenExtLines(IN bool Value) = 0;
	virtual double  getFixedLenExtLinesLength() = 0;                 // dimfxl
	virtual HRESULT setFixedLenExtLinesLength(IN double Value) = 0;
	virtual double  getJogAngle() = 0;                               // dimjogang
	virtual HRESULT setJogAngle(IN double Value) = 0;
	virtual McsDimTextFill getDimTextFill() = 0;                     // dimtfill
	virtual HRESULT setDimTextFill(IN McsDimTextFill Value) = 0;
	virtual COLORREF getDimTextFillColor() = 0;                      // dimtfillclr
	virtual HRESULT  setDimTextFillColor(IN COLORREF Value) = 0;
	virtual McsArcSymbolPos getArcSymbolPos() = 0;                   // dimarcsym
	virtual HRESULT setArcSymbolPos(IN McsArcSymbolPos Value) = 0;
	virtual DWORD   getLineTypeDim() = 0;                            // dimltype
	virtual HRESULT setLineTypeDim(IN DWORD Value) = 0;
	virtual DWORD   getLineTypeExt1() = 0;                           // dimltex1
	virtual HRESULT setLineTypeExt1(IN DWORD Value) = 0;
	virtual DWORD   getLineTypeExt2() = 0;                           // dimltex2
	virtual HRESULT setLineTypeExt2(IN DWORD Value) = 0;
	virtual bool    getDimTxtDirection() = 0;                        // dimtxtdirection
	virtual HRESULT setDimTxtDirection(IN bool Value) = 0;
	virtual double    getDimMzf() = 0;                               // dimmzf
	virtual HRESULT   setDimMzf(IN double Value) = 0;
	virtual McsString getDimMzs() = 0;                               // dimmzs
	virtual HRESULT   setDimMzs(IN const McsString& Value) = 0;
	virtual double    getDimAltMzf() = 0;                            // dimaltmzf
	virtual HRESULT   setDimAltMzf(IN double Value) = 0;
	virtual McsString getDimAltMzs() = 0;                            // dimaltmzs
	virtual HRESULT   setDimAltMzs(IN const McsString& Value) = 0;
};
typedef MComQIPtr<IMcDimStyle> IMcDimStylePtr;

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcLayer
//---------------------------------------------------------------------------
// {E3E8D0B7-88A3-4ad0-986C-C416D850EBE0}
static const GUID IID_IMcLayer = 
{ 0xe3e8d0b7, 0x88a3, 0x4ad0, { 0x98, 0x6c, 0xc4, 0x16, 0xd8, 0x50, 0xeb, 0xe0 } };

class __declspec(uuid("E3E8D0B7-88A3-4ad0-986C-C416D850EBE0"))
IMcLayer : public virtual IMcObject
{
public:
	virtual LPCTSTR   getName() = 0;
	virtual COLORREF  getColor() = 0;
	virtual int       getLineWeight() = 0;
	virtual bool      isFrozen() = 0;
	virtual bool      isLocked() = 0;
	virtual bool      isOff() = 0;
	virtual bool      isPlottable() = 0;
	virtual LPCTSTR   getComment() = 0;
	virtual LPCTSTR   getLinetype() = 0;

	virtual void setName(LPCTSTR stName) = 0;
	virtual void setColor(COLORREF color) = 0;
	virtual void setLineWeight(int weight) = 0;
	virtual void setFrozen(bool frozen) = 0;
	virtual void setLocked(bool locked) = 0;
	virtual void setOff(bool off) = 0;
	virtual void setPlottable(bool plottable) = 0;
	virtual void setComment(LPCTSTR st) = 0;
	virtual void setLinetype(LPCTSTR st) = 0;

	virtual HRESULT update()
		{ NOTIMPL_ALERT("IMcLayer::update"); }
};
typedef MComQIPtr<IMcLayer> IMcLayerPtr;

#define RTF_HEADER _T("{\\rtf")
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcStyleManager
//---------------------------------------------------------------------------
class IMcStyleManager
{
public:
	// Возвращает стиль с именем stName. Если stName == NULL, то возвращается 
	// стиль по умолчанию текущего проекта (для MechaniCS - GOST, для SPDS - SPDS)
	virtual IMcTextStylePtr GetTextStyle(LPCTSTR stName = NULL) = 0;
	// При byContext == false, возвращает текущий стиль среды, иначе - 
	// стиль по умолчанию текущего проекта
	virtual McsString CurrentTextStyle(bool byContext = false) = 0;
	// Возвращает набор всех стилей, присутствующих в среде
	virtual HRESULT GetTextStyles(mcsStringArray& styles) = 0;
	// Создает в среде текстовый стиль с именем stName и настройками по умолчанию текущего проекта
	// Возвращает S_FALSE, если стиль уже существует
	virtual HRESULT CreateTextStyle(IN LPCTSTR stName, OUT OPTIONAL IMcTextStyle** ppTS = NULL)
		{ NOTIMPL_ALERT("IMcStyleManager::CreateTextStyle"); }

	// Возвращает стиль с именем stName. Если stName == NULL, то возвращается 
	// стиль по умолчанию текущего проекта
	virtual IMcDimStylePtr GetDimStyle(LPCTSTR stName = NULL) = 0;
	// При byContext == false, возвращает текущий стиль среды, иначе - 
	// стиль по умолчанию текущего проекта
	virtual McsString CurrentDimStyle(bool byContext = false) = 0;
	// Возвращает набор всех стилей, присутствующих в среде
	virtual HRESULT GetDimStyles(mcsStringArray& styles) = 0;

	// Возвращает слой с именем stName.
	virtual IMcLayerPtr GetLayer(LPCTSTR stName) = 0;
	// Возвращает текущий слой среды
	virtual McsString CurrentLayer() = 0;
	// Устанавливает текущий слой среды
	virtual HRESULT SetCurrentLayer(LPCTSTR stName) = 0;
	// Возвращает набор всех слоев, присутствующих в среде
	virtual HRESULT GetLayers(mcsStringArray& layers) = 0;
	// Создает в среде слой с именем stName и настройками по умолчанию среды
	// Возвращает S_FALSE, если слой уже существует
	virtual HRESULT CreateLayer(IN LPCTSTR stName, OUT OPTIONAL IMcLayer** ppL = NULL)
		{ NOTIMPL_ALERT("IMcStyleManager::CreateLayer"); }

	virtual McsString GetDefUnplottedLayerName()
	{
		return MCS_DEF_LAYER_UNPLOTTED;
	}
	virtual McsString GetDefInvisibleLayerName()
	{
		return MCS_LAYER_INVISIBLE;
	}

	// Проверяет, является ли блок с указанным именем предопределённым или системным.
	virtual bool IsBlockPredefined(LPCTSTR lpcszBlockName) = 0;

	// Текущий масштаб
#define MC_MIN_SCALE (1e-8)
	virtual double GetCurrentScale(bool fDrawing = true) = 0;  // true for drawing scale, false for mechanical scale
	virtual HRESULT SetCurrentScale(double rScale, bool fDrawing = true)
		{ NOTIMPL_ALERT("IMcStyleManager::SetCurrentScale"); }

	// Типы линий
	virtual HRESULT GetLineTypes(OUT mcsStringArray& linetypes, IN IMcDocument* pDoc = NULL)
		{ NOTIMPL_ALERT("IMcStyleManager::GetLineTypes"); }
	// Уничтожать надо с помощью IMcStyleManager::DestroyLineTypeComboBox()
#define MC_CB_GETLBTEXT_LOCAL (WM_USER + 1)
#define MC_CB_CB_GETLBTEXTLEN_LOCAL (WM_USER + 2)
	virtual HWND CreateLineTypeComboBox(IN int x, IN int y, IN int width, IN int height, IN HWND hParent, IN int iID, IN OPTIONAL IMcDocument* pDoc = NULL, IN OPTIONAL bool useByObject = false, bool bByPlmTheme = false)
		{ NOTIMPL_ALERT2("IMcStyleManager::CreateLineTypeComboBox", NULL); }
	virtual HRESULT GetStandardLinetypeName(OUT McsString& st, IN int iLT) = 0;
	virtual HRESULT GetStandardLinetypeIndex(OUT int& iLT, IN LPCTSTR st) = 0;

	virtual void DestroyLineTypeComboBox(HWND hLineTypeComboBox) 
		{ NOTIMPL_ALERT_V("IMcStyleManager::DestroyLineTypeComboBox"); }
	virtual HRESULT InitLineTypeComboBox(HWND hLineTypeComboBox, IMcDocument* pDoc, bool useByObject, bool bByPlmTheme)
		{ NOTIMPL_ALERT("IMcStyleManager::InitLineTypeComboBox"); }

	// Возвращает цвет, соответствующий типу линии (включая специальные: BYLAYER, BYBLOCK ...)
	virtual COLORREF GetLineTypeColor(int iLineType, MCS_STANDARD std) = 0;
	// Возвращает толщину в сотых долях миллиметра, соответствующую типу линии
	// (включая специальные: BYLAYER, BYBLOCK ...)
	virtual int GetLineTypeWeight(int iLineType, MCS_STANDARD std) = 0;

	// Вызов диалога выбора цвета для текущей среды
	virtual COLORREF ShowNativeColorDialog(COLORREF color, HWND parent) = 0;

	// true - вставляемые размеры должны быть ассоциативными
	virtual bool IsDimAssociative() = 0;

	virtual LPCTSTR GetFontName()
		{ return _T("CS Standard"); }

// МАСШТАБЫ
	// Выдает список стандартных масштабов
	virtual const mcsStringArray& GetScales(bool bDrawing) = 0;
	// Приводит масштаб к бижайшему стандартному значению
	virtual HRESULT GetNearestScale(IN OUT double& Value, bool bDrawing) = 0;
	// Конвертирует текстовую строку с обозначением масштаба в число.
	// Допускается наличие префикса "М", пробелы, запись отношением или десятичной дробью
	virtual HRESULT GetScaleByName(IN const McsString& stValue, OUT double& Result, bool bDrawing) = 0;
	// Формирует строку с обозначением масштаба по переданному значению, pbUniqueValue - входит ли значение в стандартный список масштабов, выдаваемый GetScales()
	virtual HRESULT GetScaleName(IN double rValue, OUT McsString& stResult, bool bDrawing, bool* pbUniqueValue = NULL) = 0;
	virtual double GetDefaultScale(bool bDrawing){return 1.0;};
	virtual HRESULT GetModelUnits(mcsStringArray& arr, mcsDoubleArray& multipliers){return E_FAIL;};
	virtual HRESULT SelectModelUnits(const double rMultiplier){return E_FAIL;};
	virtual bool useModelUnits(){return false;};
	//чистой воды helper
	virtual McsString GetCurentModelUnits(double* rMultiplier = NULL, bool bFramed = true){return McsString();};
// Helpers
#ifdef _UNICODE
	__inline McsStringW GetRtfRaw(IN LPCWSTR st) { return GetRtfRawW(st); }
	__inline McsStringW GetRtfRawWithSymbols(IN LPCWSTR st) { return GetRtfRawW(st); }
	__inline McsStringA GetTextWithSymbols(IN LPCWSTR st) { return GetRtfRawWithSymbolsW(st); }
#else
	__inline McsStringA GetRtfRaw(IN LPCSTR st) { return GetRtfRawA(st); }
	__inline McsStringA GetRtfRawWithSymbols(IN LPCSTR st) { return GetRtfRawWithSymbolsA(st); }
	__inline McsStringA GetTextWithSymbols(IN LPCSTR st) { return GetRtfRawWithSymbolsA(st); }
#endif
	// Текст без форматирования, юникод заменяется символом '?'
	virtual McsStringA GetRtfRawA(IN LPCSTR st) = 0;
	// Юникод текст без форматирования
	virtual McsStringW GetRtfRawW(IN LPCWSTR st) = 0;
	// Текст без форматирования, юникод представлен как \U+XXXX
	virtual McsStringA GetRtfRawWithSymbolsA(IN LPCSTR st) = 0;
	virtual McsStringA GetRtfRawWithSymbolsW(IN LPCWSTR st) = 0;
	// Конвертируют текст в платформеннозависимый формат и обратно
	virtual McsString ConvertToNative(IN LPCTSTR st,
																		IN OPTIONAL double rIndexScale = 0.75,
																		IN OPTIONAL DWORD Flags = 0) = 0;
	virtual McsString ConvertFromNative(IN LPCTSTR st,
																			IN MCS_PlatformId plmFrom) = 0;
	// Разбивает текст на строки по разделителю, сохраняя форматирование
	virtual HRESULT SplitRtf(IN LPCTSTR st,
													 OUT mcsStringArray& Result,
													 IN OPTIONAL LPCTSTR stDelimiter = _T("\n")) = 0;
	// Убирает переносы строк
	virtual McsString MakeSingleLine(const McsString& st) = 0;

	// Стандарты
	virtual MCS_STANDARD getStandard() = 0;
	virtual HRESULT getAvalibleStandards(mcsIntArray& standrtds, mcsStringArray& names){return E_FAIL;};


	// Настройки приложения и стандартов.
	// Возвращает объект MSXML2::IXMLDOMElementPtr.
	// При (bApplicationSection == true) указывает на настройки для текущего приложения и стандарта, иначе на корень.
	// Сами настройки определены в data\settings.xml.
	// Например, для СПДС функция вернет узел "//Definitions/SPDS" или "//Definitions" при (bApplicationSection == false)
	virtual IUnknownPtr getXMLSettings(bool bApplicationSection = true) = 0;

	// Число отображаемых знаков после запятой
	// Для Акада - переменная "LUPREC"
	virtual int getPrecision(bool forLinear = true) = 0;

	// Для акада - переменная "LTSCALE"
	virtual double getGlobalLTScaleFactor()
		{ return 1; }

	// Для Акада - настройки оснапов
	virtual HRESULT getAutoSnapSettings(DWORD& osMode, DWORD& autoSnap)
		{ return E_NOTIMPL; }

	// Возвращает стандартные высоты текста
	virtual HRESULT getStandardTextHeights(OUT mcsStringArray& strings)
		{ return E_NOTIMPL; }
	virtual HRESULT getStandardTextHeights(OUT mcsDoubleArray& data)
		{ return E_NOTIMPL; }
	virtual bool isRtfText(LPCTSTR strText)
	{
		if( strText == NULL) return false;
		return (_tcsncmp(strText, RTF_HEADER, 5) == 0);
	}
	// Отдаёт имена стандартных типов линий по индексу: MCS_ENTLTYPE_BYLAYER, MCS_ENTLTYPE_BYBLOCK, MCS_ENTLTYPE_CONTINUOUS
	virtual McsString getStdLinetypeName(IN int iLT, IN OPTIONAL IMcDocument* pDoc = NULL)
	{
		switch(iLT)
		{
			case MCS_ENTLTYPE_BYLAYER:
				return _T("ByLayer");
			case MCS_ENTLTYPE_BYBLOCK:
				return _T("ByBlock");
			case MCS_ENTLTYPE_CONTINUOUS:
				return _T("Continious");
		}
		return _T("");
	}
	// Форматирует вещественное число в соответствии с настройками платформы.
	virtual McsString Value2String(double rValue, bool isLinear = true) = 0;

	enum TextStyleCacheMode
	{
		ktscmTextStyleCacheOff = 0,
		ktscmTextStyleCacheStart = 1,
		ktscmTextStyleCacheOn = 2,
	};
	virtual HRESULT SetTextStyleCacheMode(TextStyleCacheMode mode)
		{ return E_NOTIMPL; }

	// Переопределения параметров приложения
	virtual IUnknownPtr getXMLSettingsOverride(bool bApplicationSection = true)
		{ return UNKNULL; }

	// Получить ID визуального стиля по его имени
	virtual mcsWorkID getVisualStyleIdByName(LPCTSTR lpszVisStyleName, IN OPTIONAL IMcDocument* pDoc = NULL)
		{ return WID_NULL; }

	// Имя визуального стиля по его ID
	virtual McsString getVisualStyleName(const mcsWorkID& visStyleID)
		{ return McsString(); }
};


//////////////////////////////////////////////////////////////////////////
// Класс для работы с форматированным текстом
IMCS_DECL_INTERFACE(IMcTextRef, "{78BF28DD-2ACE-4d48-87ED-AF060C32BEC5}");
typedef McsArray<IMcTextRefPtr, IMcTextRef*> IMcTextRefPtrArray;

struct IMcTextConverter : public virtual IMcObject
{
#ifdef _UNICODE
	__inline McsStringW GetText()                                                                     { return GetTextW(); }
	__inline McsStringW GetTextRaw()                                                                  { return GetTextRawW(); }
	__inline HRESULT    SetText(LPCWSTR Value)                                                        { return SetTextW(Value); }
	__inline HRESULT    AddTextEx(IN LPCWSTR Value)                                                   { return AddTextExW(Value); }
	__inline int        Find(IN LPCWSTR str, IN OPTIONAL int nStart = 0,
											IN OPTIONAL bool fMatchCase = true, IN OPTIONAL bool fPattern = false)        { return FindW(str, nStart, fMatchCase, fPattern); }
	__inline int        Replace(IN LPCWSTR lpwzWhat, IN OPTIONAL LPCWSTR lpwzWith = L"",
											        IN OPTIONAL bool fMatchCase = true)                                   { return ReplaceW(lpwzWhat, lpwzWith, fMatchCase); }
	__inline McsStringW GetTextWithSymbols()                                                          { return GetTextRawW(); }
	__inline HRESULT    Split(OUT mcsStringArrayW& Result, IN OPTIONAL LPCWSTR lpszDelimiter = L"\n") { return SplitW(Result, lpszDelimiter); }

#else

	__inline McsStringA GetText()                                                                     { return GetTextA(); }
	__inline McsStringA GetTextRaw()                                                                  { return GetTextRawA(); }
	__inline HRESULT    SetText(LPCSTR Value)                                                         { return SetTextA(Value); }
	__inline HRESULT    AddTextEx(IN LPCSTR Value)                                                    { return AddTextExA(Value); }
	__inline int        Find(IN LPCSTR str, IN OPTIONAL int nStart = 0,
											IN OPTIONAL bool fMatchCase = true, IN OPTIONAL bool fPattern = false)        { return FindA(str, nStart, fMatchCase, fPattern); }
	__inline int        Replace(IN LPCSTR lpszWhat, IN OPTIONAL LPCSTR lpszWith = "",
											        IN OPTIONAL bool fMatchCase = true)                                   { return ReplaceA(lpszWhat, lpszWith, fMatchCase); }
	__inline McsStringA GetTextWithSymbols()                                                          { return GetTextWithSymbolsA(); }
	__inline HRESULT    Split(OUT mcsStringArrayA& Result, IN OPTIONAL LPCSTR lpszDelimiter = "\n")   { return SplitA(Result, lpszDelimiter); }
#endif

	// Получить текст в формате rtf или неформатированный, если в тексе нет поддерживаемых нами тэгов.
	virtual McsStringA GetTextA() = 0;
	virtual McsStringW GetTextW() = 0;
	// Получить текст без форматирования, но с кодами спецсимволов. Уникодной версии нет, потому что там
	// спецсимволы представлены одним символом, то есть GetTextWithSymbolsW = GetTextRawW.
	virtual McsStringA GetTextWithSymbolsA() = 0;
	// Установить текст. Можно передавать как rtf, так и простой текст
	virtual HRESULT SetTextA(IN LPCSTR Value) = 0;
	virtual HRESULT SetTextW(IN LPCWSTR Value) = 0;

	enum FractionTextSize// Размер шрифта для дробей
	{
		kftsDefault,   // Согласно глобальной настройке
		kftsBasic,     // Равный основному
		kftsOneStepLess// На одну ступень меньше
	};
	virtual HRESULT SetFractionTextSize(FractionTextSize eValue) = 0;
	virtual FractionTextSize GetFractionTextSize() = 0;

	// Получить текст без форматирования. Для ANSI-версии символы вне текущей кодовой страницы заменяются вопросами.
	virtual McsStringA GetTextRawA() = 0;
	virtual McsStringW GetTextRawW() = 0;
	// Добавить Value в текущую позицию курсора. Умеет добавлять простой текст, текст в формате rtf
	__inline HRESULT AddText(IN LPCTSTR Value) { return AddTextEx(Value); }
	virtual HRESULT AddTextExW(IN LPCWSTR Value) = 0;
	virtual HRESULT AddTextExA(IN LPCSTR Value) = 0;
	// Добавить Value (просто текст или rtf) в текущую позицию курсора как нижний индекс
	virtual HRESULT AddSubscript(IN LPCTSTR Value) = 0;
	// Добавить Value (просто текст или rtf) в текущую позицию курсора как верхний индекс
	virtual HRESULT AddSuperscript(IN LPCTSTR Value) = 0;
	// Добавляет подчёркнутый текст
	virtual HRESULT AddUnderlinedText(IN LPCTSTR Value) = 0;
	// Добавить в конец текста дробь. Upper - числитель, Lower - знаменатель.
	// Divider=FALSE - не создавать разделительную черту
	virtual HRESULT AddDivision(IN LPCTSTR Upper, IN LPCTSTR Lower, IN OPTIONAL BOOL Divider = TRUE) = 0;
	// Добавить специальный символ. То же самое, что AddTextExW, только не для строки, а для одиночного символа.
	virtual HRESULT AddSpecSymbol(IN WCHAR Value) = 0;
	// Добавить число. Округляет до 4 значащих цифр. При необходимости приводит к экспоненциальной форме
	// (с настоящей степенью, а не с буквой E), использует десятичный разделитель из размерного стиля.
	// Числа, меньшие rTol, считает нулем.
	virtual HRESULT AddNumber(IN double rNumber, IN OPTIONAL double rTol = 1e-9) = 0;
	// Устанавливает размер межстрочного интервала
	virtual HRESULT SetLineSpacing(IN double value) = 0;
	// Делает текст подчёркнутым
	virtual HRESULT SetUnderline(bool setul) = 0;
	// Убирает переносы в строке
	virtual HRESULT MakeSingleLine() = 0;

// Прочие операции
	// Разбить текст на фрагменты. Разделитель в фрагменты не включается.
	// Аналогично McsString::Split, только может возвращать rtf-текст. Текст, установленный в конвертер, теряется
	virtual HRESULT SplitA(mcsStringArrayA& Result, LPCSTR lpszDelimiter = "\n") = 0;
	virtual HRESULT SplitW(mcsStringArrayW& Result, LPCWSTR lpszDelimiter = L"\n") = 0;
	// Заменить фрагмент текста. Вернет количество сделанных замен или -1, если произошла ошибка.
	virtual int FindA(IN LPCSTR strTextToFind,
										IN OPTIONAL int nFromPos = 0,
										IN OPTIONAL bool fMatchCase = true,
										IN OPTIONAL bool fPattern = false) = 0;
	virtual int FindW(IN LPCWSTR strTextToFind,
										IN OPTIONAL int nFromPos = 0,
										IN OPTIONAL bool fMatchCase = true,
										IN OPTIONAL bool fPattern = false) = 0;
	virtual int ReplaceA(IN LPCSTR lpszWhat,                          // что заменить
											 IN OPTIONAL LPCSTR lpszWith = "",            // чем заменить
											 IN OPTIONAL bool fMatchCase = true,          // с учетом регистра
											 IN OPTIONAL bool fPattern = false) = 0;      // использовать регулярные выражения
	virtual int ReplaceW(IN LPCWSTR lpwzWhat,                         // что заменить
											 IN OPTIONAL LPCWSTR lpwzWith,                // чем заменить
											 IN OPTIONAL bool fMatchCase = true,          // с учетом регистра
											 IN OPTIONAL bool fPattern = false) = 0;      // использовать регулярные выражения
	// Селектировать следующий фрагмент текста с нужным форматированием
	// S_FALSE - не найдено
	virtual HRESULT FindFmt(IN DWORD dwEffect,                        // эффект (CFE_SUBSCRIPT, CFE_SUPERSCRIPT, CFE_AUTOBACKCOLOR, CFE_AUTOCOLOR, CFE_PROTECTED)
													IN OPTIONAL long nValue = -1,             // искомое значение
													IN OPTIONAL bool fReverse = false) = 0;   // обратное направление поиска
	// Расширить селекцию до границ указанного эффекта
	virtual HRESULT ExpandFmt(IN DWORD dwEffect) = 0;
	// Блокировать/разблокировать обновление окна.
	// EN_CHANGE не приходит, допускаются вложенные вызовы
	virtual HRESULT StartTransaction() = 0;
	virtual HRESULT EndTransaction(IN OPTIONAL BOOL fNotify = FALSE) = 0;  // fNotify - послать EN_CHANGE родителю

// Форматирование
	// Разбить текст на куски в соответствии с форматированием.
	// Учитывается стиль, высота текста, наклон, коэффициент сжатия, координаты, направление, выравнивание.
	// Если pBounds != NULL, в ней вернутся габариты текста.
	virtual HRESULT Explode(IN const mcsText& srcText,
													OUT mcsGeomEntArray& Fragments,
													OUT OPTIONAL mcsBoundBlock* pBounds) = 0;
	// Преобразовать текст rtf в текст платформы с сохранением форматирования.
	// Для Автокада вернет в формате MText, для остальных пока просто сделает GetTextRaw
	// rIndexScale - множитель высоты текста для индексов
	virtual McsString ConvertToNative(IN double rIndexScale = 0.75, IN OPTIONAL DWORD Flags = 0) = 0;
	// Преобразовать родное форматирование платформы в rtf.
	// Ошибки в форматировании по возможности пропускает, сообщая о них в InDebMon. Если были ошибки, вернет S_FALSE.
	// Например:
	// HRESULT ConvertText(IN OUT McsString& str) {
	//   IMcTextConverterPtr pText;
	//   HRESULT hr = gpMcOjManager->CreateObject(&pText, IID_IMcTextConverter);
	//   if (FAILED(hr)) return hr;
	//   pText->SetText(str);
	//   hr = pText->ConvertFromNative(gpMcContext->PlatformId());
	//   if (SUCCEEDED(hr)) str = pText->GetText();
	//   return hr;
	// }
	// plmFrom == MCS_PLM_ACAD
	//   nFlags&1    // не удалять теги MText'а
	virtual HRESULT ConvertFromNative(MCS_PlatformId plmFrom, IN OPTIONAL long nFlags = 0) = 0;

	// Преобразование в XHTML и обратно
	virtual McsStringW ToXHTML() = 0;
	virtual HRESULT FromXHTML(LPCWSTR swzHypertext) = 0;


	// Attach a rich edit control to text converter
	virtual HRESULT Attach(HWND hRichEdit) = 0;

// Работа со ссылками
	virtual IMcTextRefPtr refGetCurrent(IN OPTIONAL IMcObject* pOwner = NULL) = 0;   // обязательно вернет объект, просто если ссылки нет, он будет rtUnknown
	virtual HRESULT refGetAll(OUT IMcTextRefPtrArray& Result, IN OPTIONAL IMcObject* pOwner = NULL) = 0;

	virtual IUnknownPtr ole() = 0;
//	virtual HWND hwnd() = 0;
	virtual HRESULT Replace(IN int iFromPosition, IN int iToPosition, IN LPCWSTR lpwzWith = L"") { return E_NOTIMPL; }

	// Делает текст зачёркнутым
	virtual HRESULT SetStriked(bool bStrike) = 0;

	// Имя текстового стиля, с которым отформатирован native text
	virtual HRESULT SetNativeTextStyleName(LPCTSTR pszTextStyleName) = 0;

	// Возвращает индекс символа в тексте text по точке pnt.
	virtual int HitTest(const mcsText& text, const mcsPoint& pnt)
	{
		return -1;
	}
};

//------------------------------------------------------------------------
enum McTextRefType
{
	rtUnknown = 0x00000000,
	rtField   = 0x00000001,// ссылка на текстовое свойство
	rtObject  = 0x00000004,// внедренный объект
	rtAnchor  = 0x00000008,// гиперссылка
};

//------------------------------------------------------------------------
interface IMcTextRef : public virtual IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMcTextRef, IMcObject);

	// Удалить ссылку или конвертировать в статитческий текст
	virtual HRESULT Purge(bool bLeaveText = true) = 0;
	// Обновить текст ссылки, если stValue нулевой, то значение будет рассчитано
	virtual HRESULT Update(LPCTSTR stValue = NULL) = 0;
	// Селектировать ссылку в rich edit
	virtual HRESULT Select() = 0;

	// properties                                                 field   object   anchor
	virtual McTextRefType getType() = 0;                      //  +       +        +
	virtual DWORD getKey() = 0;                               //  +
	virtual HRESULT setKey(DWORD dwKey) = 0;                  //  +
	virtual mcsWorkID getObjectId() = 0;                      //  +
	virtual McsString getPropertyName() = 0;                  //  +
	virtual mcsPropertyType getPropertyType() = 0;            //  +
	virtual McsString getFormula() = 0;                       //  +
	virtual HRESULT setFormula(McsString msText) = 0;         //  +
	virtual McsStringW getValue() = 0;                        //  +       +        +
	virtual IMcsStreamPtr getData() = 0;                      //          +
	virtual HRESULT setData(IMcsStream* pValue) = 0;          //          +
	virtual IMcDbObjectPtr getObject() = 0;                   //          +
	virtual HRESULT EditObject(HWND hParent) = 0;             //          +
	virtual CLSID getClass() = 0;                             //          +
	// Вписывание в строку по высоте
	virtual bool getZoomed() = 0;                             //          +
	virtual HRESULT setZoomed(bool bValue) = 0;               //          +
	virtual McsVertTextAlignEnum getAlign() = 0;              //          +
	virtual HRESULT setAlign(McsVertTextAlignEnum Val) = 0;   //          +
	// Использовать собственный цвет, тип и толщину линии вместо настроек текста
	virtual bool getStyleOverride() = 0;                      //          +
	virtual HRESULT setStyleOverride(bool bValue) = 0;        //          +
	virtual McsString getURL() = 0;                           //                   +
	virtual HRESULT setURL(LPCTSTR stValue) = 0;              //                   +

	// Создаёт ссылку на текстовое свойство. idSource равен WID_NULL для типов mcPropsField и mcPropsProject.
	virtual HRESULT MakeReference(mcsPropertyType type, const mcsWorkID& idSource, LPCTSTR stSource, LPCTSTR stTarget, LPCTSTR stFormula = NULL) = 0;
	// Внедряет объект
	virtual HRESULT MakeObject(IMcEntity* pSource) = 0;
	// Внедряет произвольную графику
	virtual HRESULT MakeGeometry(const mcsGeomEntArray& Geom) = 0;
	// Создаёт гиперссылку
	virtual HRESULT MakeAnchor(LPCTSTR stUrl) = 0;

	// link <-> template functions
	virtual HRESULT ToTemplate() = 0;
	virtual HRESULT FromTemplate(LPCTSTR stProperty, IMcEntity* pDataSource = NULL) = 0;
};


//////////////////////////////////////////////////////////////////////////
// Вспомогательные функции для упрощения работы с текстовыми ссылками
namespace CxFtHelper {
	// Внедряет копию объекта pObject в текстовое свойство объекта pClient.
	//
	// Код возврата
	// S_OK                = объект внедрён
	// E_INVALIDARG        = неправильный объект pClient или pObject
	// DISP_E_UNKNOWNNAME  = ошибка в имени свойства msClientProperty
	// E_ACCESSDENIED      = свойство msClientProperty недоступно для записи
	// DISP_E_TYPEMISMATCH = свойство msClientProperty не поддерживает форматированный текст
	// E_NOINTERFACE       = класс IMcTextConverter не зарегистрирован
	// E_FAIL              = внутренняя ошибка
	HRESULT MECHCTL_API EmbedObject(IN IMcEntity* pClient,       // объект, в который внедряем
	  IN McsString msClientProperty,                             // имя свойства, в которое внедряем
		IN IMcEntity* pObject,                                     // объект, копию которого внедряем
		IN OPTIONAL BOOL fInscribe = TRUE);                        // вписать объект в высоту шрифта или оставить в исходно мразмере

	// Внедряет произвольную геометрию в текстовое свойство объекта pClient.
	//
	// Коды возврата те же, что и в EmbedObject
	// S_FALSE             = массив geometry пуст
	HRESULT MECHCTL_API EmbedGeometry(IN IMcEntity* pClient,       // объект, в который внедряем
		IN McsString msClientProperty,                             // имя свойства, в которое внедряем
		IN const mcsGeomEntArray geometry,                         // геометрия, которую внедряем
		IN OPTIONAL BOOL fInscribe = TRUE,                         // вписать геометрию в высоту шрифта или оставить в исходно мразмере
		IN OPTIONAL BOOL fKeepStyle = FALSE);                      // сохранять тип, вес и цвет линий geometry или использовать цвет текста msClientProperty

	// Внедряет динамическую ссылку на свойство объекта pServer.
	// Свойство msClientProperty в объекте pClient должно иметь gs-маркер,
	// связанный с именем свойства через getPropertyNameByGSMarker.
	//
	// Код возврата
	// S_OK                = ссылка создана
	// E_INVALIDARG        = неправильный объект pClient или pServer
	// DISP_E_UNKNOWNNAME  = ошибка в имени свойства msClientProperty или msServerProperty
	// E_ACCESSDENIED      = свойство msClientProperty недоступно для записи
	// DISP_E_TYPEMISMATCH = свойство msClientProperty не поддерживает форматированный текст
	// DISP_E_BADINDEX     = со свойством msClientProperty не связам gs-маркер
	// E_NOINTERFACE       = класс IMcTextConverter не зарегистрирован
	// E_FAIL              = внутренняя ошибка
	HRESULT MECHCTL_API EmbedProperty(IN IMcEntity* pClient,     // объект, в который внедряем
		IN McsString msClientProperty,                             // имя свойства, в которое внедряем (категория всегда mcPropsObject)
		IN IMcEntity* pServer,                                     // объект, из которого берём значение
		IN McsString msServerProperty,                             // имя свойства в pServer, из которого берём значение
		IN OPTIONAL mcsPropertyType ptType = mcPropsObject);       // категория свойства msServerProperty

	// Сериализует объект целиком, если это возможно, в противном случае сериализует только геометрию с объекта.
	//
	// Параметры:
	// IN pEmbeddedEntity - внедряемый объект. Не может быть NULL.
	// IN pHostEntity - объект, в который внедряется pEmbeddedEntity. Может быть NULL.
	// OUT msEncodedStream - результат сериализации в виде строки, закодированной в Base64.
	// OUT classId - идентификатор класса внедряемого объекта, если он был сериализован целиком, и пустой GUID в случае,
	//     если была сериализована только его геометрия.
	// OUT msClassName - имя класса внедряемого объекта, если он был сериализован целиком, и строка "Геометрия" в случае,
	//     если была сериализована только его геометрия.
	//
	// Возвращаемые значения:
	// S_OK - объект или только его геометрия успешно сериализованы.
	// E_INVALIDARG - неправильный объект pEmbeddedEntity.
	// E_FAIL - внутренняя ошибка.
	HRESULT MECHCTL_API SerializeObject(
		IN IMcEntity *pEmbeddedEntity,
		IN OPTIONAL IMcEntity *pHostEntity,
		OUT McsString &msEncodedStream,
		OUT GUID &classId,
		OUT McsString &msClassName);

	// Десериализует объект из потока, полученного вызовом функции CxFtHelper::SerializeObject().
	//
	// Параметры:
	// IN msEncodedStream - поток, закодированный в Base64 и содержащий данные объекта. Не может быть пустой строкой.
	// IN classId - идентификатор класса, с помощью которого будет создан объект. Не может быть пустым.
	// OUT entityPtr - ссылка на умный указатель, который будет указывать на воссозданный из потока объект.
	//
	// Возвращаемые значения:
	// S_OK - объект или только его геометрия успешно сериализованы.
	// E_INVALIDARG - msEncodedStream пустой или classId == IID_IUnknown или classId == GUID_NULL.
	// E_FAIL - внутренняя ошибка.
	HRESULT MECHCTL_API DeserializeObject(
		IN const McsString &msEncodedStream,
		IN const GUID &classId,
		OUT IMcEntityPtr &entityPtr);

	// Вызывает диалог редактирования формулы.
	//
	// Параметры:
	// IN OUT msFormula - формула, которую нужно изменить. Строка может быть пустой. Содержать изменённую формулу
	//     в случае, когда функция возвращает значение S_OK, в противном случае не изменяется.
	// IN hWndOwner - дескриптор окна, выступающего в качестве владельца диалога редактирования формулы.
	//
	// Возвращаемые значения:
	// S_OK - формула успешно изменена.
	// E_ABORT - формула не изменилась.
	// E_FAIL - внутренняя ошибка.
	HRESULT MECHCTL_API EditFormula(
		IN OUT McsString &msFormula,
		IN HWND hWndOwner = NULL
	);
};


/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Работа с shx шрифтами
//---------------------------------------------------------------------------

extern "C"
MCTYP_API HRESULT McGetShxTextGeometry(
	mcsGeomEntArray& ents,
	const mcsText& text,
	bool isVertical = false,
	bool isBackwards = false,
	bool isUpsideDown = false);

extern "C"
MCTYP_API double McGetShxDTextLength(
	LPCTSTR text,
	LPCTSTR textStyle,
	double height,
	double oblique,
	double xScale);

inline HRESULT DynMcGetShxTextGeometry(mcsGeomEntArray& ents, const mcsText& text, HINSTANCE hCoInst, bool isVertical = false, bool isBackwards = false, bool isUpsideDown = false)
{
	FARPROC pFunc;
	DYN_GET_PROC_ADDRESS(pFunc, _T("McTyp.dll"), "McGetShxTextGeometry", hCoInst);
	if(pFunc)
		return ((HRESULT(*)(mcsGeomEntArray&, const mcsText&, bool, bool, bool))pFunc)(ents, text, isVertical, isBackwards, isUpsideDown);
	return E_FAIL;
}

inline double DynMcGetShxDTextLength(LPCTSTR text, LPCTSTR textStyle, double height, double oblique, double xScale, HINSTANCE hCoInst)
{
	FARPROC pFunc;
	DYN_GET_PROC_ADDRESS(pFunc, _T("McTyp.dll"), "McGetShxDTextLength", hCoInst);
	if(pFunc)
		return ((double(*)(LPCTSTR, LPCTSTR, double, double, double))pFunc)(text, textStyle, height, oblique, xScale);
	return E_FAIL;
}
