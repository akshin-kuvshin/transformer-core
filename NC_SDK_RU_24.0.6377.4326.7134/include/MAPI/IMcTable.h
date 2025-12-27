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
#include "McsGeometry.h"
#include "IMcObjects.h"


#define MCSRGB_DEFAULT  MCS_ENTCOLOR_BYCONTEXT                      // цвет линий брать из настроек таблицы
#define MCSRGB_INCONS   0xc0000000                                  // возвращается функцией getCellColor, если цвет нужных границ неодинаковый
#define MCSRGB_NONE     RGB(0xff,0xff,0xfe)                         // не заливать ячейку
#define MCSLWT_DEFAULT  MCS_ENTWEIGHT_BYCONTEXT                     // толщину линий брать из настроек таблицы
#define MCSLWT_NONE     (-9)                                        // нет линии
#define MCSLWT_INCONS   (-10)                                       // возвращается функцией getCellBorder, если толщина нужных границ неодинаковая


//////////////////////////////////////////////////////////////////////////
// Границы ячеек
enum McTable2BorderType
{
	kMcTableBorder_Left              = 0x0001,
	kMcTableBorder_Top               = 0x0002,
	kMcTableBorder_Right             = 0x0004,
	kMcTableBorder_Bottom            = 0x0008,
	kMcTableBorder_TopLeft           = kMcTableBorder_Top|kMcTableBorder_Left,
	kMcTableBorder_TopRight          = kMcTableBorder_Top|kMcTableBorder_Right,
	kMcTableBorder_BottomLeft        = kMcTableBorder_Bottom|kMcTableBorder_Left,
	kMcTableBorder_BottomRight       = kMcTableBorder_Bottom|kMcTableBorder_Right,
	kMcTableBorder_Horizontal        = kMcTableBorder_Top|kMcTableBorder_Bottom,
	kMcTableBorder_Vertical          = kMcTableBorder_Left|kMcTableBorder_Right,
	kMcTableBorder_ButLeft           = kMcTableBorder_Right|kMcTableBorder_Bottom|kMcTableBorder_Top,
	kMcTableBorder_ButTop            = kMcTableBorder_Left|kMcTableBorder_Bottom|kMcTableBorder_Right,
	kMcTableBorder_ButRight          = kMcTableBorder_Left|kMcTableBorder_Bottom|kMcTableBorder_Top,
	kMcTableBorder_ButBottom         = kMcTableBorder_Left|kMcTableBorder_Top|kMcTableBorder_Right,
	kMcTableBorder_All               = 0x00ff
};


//////////////////////////////////////////////////////////////////////////
// Стиль форматирования данных в ячейке
enum McTable2CellFormat
{
	kMcTable2Cell_Auto = 0,
	kMcTable2Cell_Number,				// числовой десятичный
	kMcTable2Cell_String,				// строковый
	kMcTable2Cell_Number_Scientific,	// числовой экспоненциальный
};


//////////////////////////////////////////////////////////////////////////
// Точность представления чисел в ячейке
enum McTable2CellPrecision
{
	kMcTable2Precision_Auto = -1,          // взять точность с чертежа
	kMcTable2Precision_Integer = 0,        // округлять до целых
	kMcTable2Precision_1 = 1,              // округлять до одного знака после запятой
	kMcTable2Precision_2 = 2,
	kMcTable2Precision_3 = 3,
	kMcTable2Precision_4 = 4,
	kMcTable2Precision_5 = 5,
	kMcTable2Precision_6 = 6,
	kMcTable2Precision_7 = 7,
	kMcTable2Precision_8 = 8,
	kMcTable2Precision_9 = 9,
	obsolete_kMcTable2Precision_Scientific = 10     // Вместо точности CellPrecision::Scientific нужно использовать формат CellFormat::kMcTable2Cell_Number_Scientific
};


//////////////////////////////////////////////////////////////////////////
// Типы разделов
//
// Строки таблицы группируются в разделы:
enum McTable2SectionType
{
	kMcTableSection_Header           = 0x00000000,        // верхний колонтитул (для каждой страницы)
	kMcTableSection_HeaderFirst      = 0x00010000,        // верхний колонтитул (только для первой страницы)
	kMcTableSection_HeaderMiddle     = 0x00020000,        // верхний колонтитул (для всех страниц, кроме первой и последней)
	kMcTableSection_HeaderLast       = 0x00030000,        // верхний колонтитул (только для последней страницы)
	kMcTableSection_None             = 0x00040000,        // обычные данные
	kMcTableSection_ReportHeader     = 0x00050000,        // заголовок отчёта (не выводтися, если отчёт пустой)
	kMcTableSection_ReportSource     = 0x00060000,        // шаблон отчёта
	kMcTableSection_ReportFooter     = 0x00070000,        // итог отчёта (не выводтися, если отчёт пустой)
	kMcTableSection_Footer           = 0x00080000,        // нижний колонтитул (для каждой страницы)
	kMcTableSection_FooterFirst      = 0x00090000,        // нижний колонтитул (только для первой страницы)
	kMcTableSection_FooterMiddle     = 0x000a0000,        // нижний колонтитул (для всех страниц, кроме первой и последней)
	kMcTableSection_FooterLast       = 0x000b0000,        // нижний колонтитул (только для последней страницы)
	kMcTableSection_ReportData       = 0x000c0000,        // строки отчёта
// Разделы колонтитулов, заголовка и итога отчёта содержат дополнительную невидимую строку, которая
// нужна для разделения границ ячеек между разделами таблицы.
};



//////////////////////////////////////////////////////////////////////////
// Способ разбивки на страницы
enum McTable2PageMode
{
	kMcTablePage_Single              = 0,                 // одной страницей
	kMcTablePage_ByRowCount          = 1,                 // максимальным числом строк в странице
	kMcTablePage_ByHeight            = 2,                 // максимальной высотой страницы
	kMcTablePage_Direct              = 3                  // прямым указанием разрыва страницы
};



//////////////////////////////////////////////////////////////////////////
// Вписывание текста ячейки по горизонтали
enum McTable2HorzFit
{
	kMcTableHorzFit_None             = 0,                 // Не вписывать текст. Текст может перекрывать соседние ячейки
	kMcTableHorzFit_Shrink           = 1,                 // Сжать текст по горизонтали
	kMcTableHorzFit_Wrap             = 2,                 // Переносить по словам
};



//////////////////////////////////////////////////////////////////////////
// Вписывание текста ячейки по вертикали
enum McTable2VertFit
{
	kMcTableVertFit_None             = 0,                 // Не вписывать текст. Текст может перекрывать соседние ячейки
	kMcTableVertFit_Shrink           = 1,                 // Уменьшить высоту шрифта
	kMcTableVertFit_Expand           = 2,                 // Увеличить высоту строки
	kMcTableVertFit_AddRows          = 3,                 // Добавить псевдостроки для каждой строки текста
};



//////////////////////////////////////////////////////////////////////////
// Режим вставки подтаблицы
enum McTable2InsertionMode
{
	kMcTableInsert_InSingleCell     = 0,                  // Разбить ячейку на нужное количество строк и столбцов (размеры ячейки изменятся)
	kMcTableInsert_CellByCell       = 1,                  // Занимать ячейки враво-вниз
	kMcTableInsert_Over             = 2,                  // Наклеить таблицу (размеры ячеек обеих таблиц не изменятся)
};


//////////////////////////////////////////////////////////////////////////
// Опции преобразования при экспорте в Excel, таблицы Acad, а также при при преобразовании отчетов в обычные данные.
struct McTable2ConversionOptions
{
	bool bDeleteHidden;       // Удалять скрытые строки и колонки
	bool bSaveReportTemplate; // Сохранять шаблон отчёта

	McTable2ConversionOptions()
	{
		bDeleteHidden = true;
		bSaveReportTemplate = true;
	}
};


//////////////////////////////////////////////////////////////////////////
// IMcTable2 interface
//
// Новый интерфейс к таблицам взамен IMcTable.
// Объект IMcTable2 поддерживает интерфейс IMcTable для совместимости, но в новых разработках
// лучше использовать IMcTable2. Если тут чего-то не хватает, говорите мне - добавлю.
//
// В таблице используется косвенная индексация строк. Функции с суффиксом Abs используют абсолютную
// адресацию - так, как видно в диалоге таблицы. Функции, оканчивающиеся на Drw, используют косвен-
// ную адресацию - так, как видно на чертеже. На чертеже строки могут повторяться (например, колон-
// титулы) или пропускаться (например, исходные строки отчета, строки нулевой высоты, колонтитулы).
//                                                                                         DJ
//
struct IMcTable2 : public IMcEntity
{
// Размеры таблицы.
	virtual int       getRowCountAbs() = 0;
	virtual int       getRowCountDrw() = 0;
	virtual int       getColCount() = 0;
	virtual HRESULT   setRowCountAbs(IN int iValue) = 0;
	virtual HRESULT   setColCount(IN int iValue) = 0;
	// Высота строки
	virtual double    getRowHeightAbs(IN int iRow_abs) = 0;
	virtual HRESULT   setRowHeightAbs(IN int iRow_abs, IN double rHeight) = 0;
	// Ширина столбца
	virtual double    getColWidth(IN int iCol) = 0;
	virtual HRESULT   setColWidth(IN int iCol, IN double rWidth) = 0;
	// Какой должна быть ширина столбца, чтобы текст в нём помещался без переносов.
	// Работает только в сторону увеличения от текущей ширины.
	virtual double    getSufficientColWidth(int iCol) = 0;
	// Перевод из абсолютной адресации с косвенную. Если строка не используется, вернет -1.
	// Если строка на чертеже встречается несколько раз, вернет только первое вхождение.
	virtual int       RowAbsToDrw(int iRow_abs) = 0;
	// Перевод из косвенной адресации в абсолютную.
	virtual int       RowDrwToAbs(int iRow_drw) = 0;
	// Увеличивает группу, чтобы полностью включить в нее сгруппировнные ячейки
	virtual HRESULT   getRectRectAbs(IN OUT RECT& rc_abs) = 0;
	virtual HRESULT   getRectRectDrw(IN OUT RECT& rc_drw) = 0;
	// Символьное обозначение ячейки
	virtual McsString getAddressOfCell(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   getCellOfAddress(IN McsString msAddress, OUT int& iRow_abs, OUT int& iCol) = 0;
	// Строки сверху вниз
	virtual bool      getUpToDown() = 0;
	virtual HRESULT   setUpToDown(IN bool fValue) = 0;

// Стиль ячеек по умолчанию
	virtual McsVertTextAlignEnum getVertAlign() = 0;
	virtual HRESULT   setVertAlign(IN McsVertTextAlignEnum vAlign) = 0;
	virtual McsHorizTextAlignEnum getHorzAlign() = 0;
	virtual HRESULT   setHorzAlign(IN McsHorizTextAlignEnum hAlign) = 0;
	virtual McTable2HorzFit getHorzFit() = 0;
	virtual HRESULT   setHorzFit(IN McTable2HorzFit hFit) = 0;
	virtual McTable2VertFit getVertFit() = 0;
	virtual HRESULT   setVertFit(IN McTable2VertFit vFit) = 0;
	virtual McsString getTextStyle() = 0;
	virtual HRESULT   setTextStyle(IN McsString msStyle) = 0;
	virtual double    getTextHeight() = 0;
	virtual HRESULT   setTextHeight(IN double rValue) = 0;
	virtual double    getTextScale() = 0;
	virtual HRESULT   setTextScale(IN double rValue) = 0;
	virtual double    getTextIndent() = 0;
	virtual HRESULT   setTextIndent(IN double rValue) = 0;
	virtual int       getTextWeight() = 0;
	virtual HRESULT   setTextWeight(IN int iValue) = 0;
	virtual COLORREF  getTextColor() = 0;
	virtual HRESULT   setTextColor(IN COLORREF rgbValue) = 0;

// Разбивка на страницы
	virtual McTable2PageMode getPageMode() = 0;
	virtual	int       getPageOfRow(int iRow_drw) = 0;
	// номер страницы iPage >= 1. Результат в ОСК (системе координат таблицы)
	virtual	mcsPoint  getPageOrigin(int iPage) = 0;
	// номер страницы iPage >= 1. ptOrigin - точка в МСК (мировой системе координат)
	virtual HRESULT   setPageOrigin(int iPage, const mcsPoint& ptOrigin) = 0;

	virtual	int       getPageCount() = 0;
	virtual	HRESULT   getPageBounds(int iPage, mcsBoundBlock& bb) = 0;
	virtual	HRESULT   setPageBreak(int atRow_abs) = 0;
	virtual	HRESULT   delPageBreak(int atRow_abs) = 0;
	virtual int       getPageLength() = 0;
	virtual	HRESULT   setPageLength(int iMaxRowsPerPage) = 0;
	virtual double    getPageHeight() = 0;
	virtual	HRESULT   setPageHeight(double rMaxHeight) = 0;
	virtual HRESULT   setPageSingle() = 0;
	virtual IMcFormatPtr getPageFrame(int iPage) = 0;

	// Текст в ячейке
	virtual McsString getCellText(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellText(IN int iRow_abs, IN int iCol, IN McsString msValue) = 0;
	// Формула в ячейке. Должна начинаться с "="
	virtual McsString getCellFormula(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellFormula(IN int iRow_abs, IN int iCol, IN McsString msValue) = 0;
	// Комментарий к ячейке
	virtual McsString getCellComment(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellComment(IN int iRow_abs, IN int iCol, IN McsString msValue) = 0;
	// Заменить текст на графику
	virtual HRESULT   setCellGraphics(	IN int iRow_abs, IN int iCol,
										IN const mcsGeomEntArray& graphics,
										IN OPTIONAL BOOL fShrink = TRUE,            // bShrink - вписать в высоту текста
										IN OPTIONAL BOOL bObjectStyle = FALSE) = 0; // bObjectStyle - отображать стилем объекта, а не таблицы

// Оформление ячейки. Установка значений по умолчанию предписывает использовать глобальные параметры,
// заданные в таблице. Возвращается всегда действующее значение. То есть, если установить по умолчанию,
// вернется значение из таблицы.
	// Вертикальное выравнивание текста в ячейке.
	virtual McsVertTextAlignEnum getCellVertAlign(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellVertAlign(IN int iRow_abs, IN int iCol,
	                                   IN OPTIONAL McsVertTextAlignEnum vAlign = (McsVertTextAlignEnum)3) = 0;
	// Горизонтальное выравнивание текста в ячейке.
	virtual McsHorizTextAlignEnum getCellHorzAlign(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellHorzAlign(IN int iRow_abs, IN int iCol,
		                                 IN OPTIONAL McsHorizTextAlignEnum hAlign = (McsHorizTextAlignEnum)3) = 0;
	// Горизонтальное вписывание текста
	virtual McTable2HorzFit getCellHorzFit(IN int iRow_abs, IN int iCol_abs) = 0;
	virtual HRESULT   setCellHorzFit(IN int iRow_abs, IN int iCol_abs, IN OPTIONAL McTable2HorzFit nValue = kMcTableHorzFit_None) = 0;
	// Вертикальное вписывание текста
	virtual McTable2VertFit getCellVertFit(IN int iRow_abs, IN int iCol_abs) = 0;
	virtual HRESULT   setCellVertFit(IN int iRow_abs, IN int iCol_abs, IN OPTIONAL McTable2VertFit nValue = kMcTableVertFit_None) = 0;
	// Стиль текста в ячейке
	virtual McsString getCellTextStyle(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellTextStyle(IN int iRow_abs, IN int iCol, IN OPTIONAL McsString msValue = McsString()) = 0;
	// Высота текста
	virtual double    getCellTextHeight(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellTextHeight(IN int iRow_abs, IN int iCol, IN OPTIONAL double rValue = 0) = 0;
	// Межстрочный интервал в ячейке
	virtual double    getCellLineSpacing(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellLineSpacing(IN int iRow_abs, IN int iCol, IN OPTIONAL double rValue = 1.0) = 0;
	// Масштабирование текста по горизонтали
	virtual double    getCellTextScale(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellTextScale(IN int iRow_abs, IN int iCol, IN OPTIONAL double rValue = 0) = 0;
	// Горизонтальный отступ текста
	virtual double    getCellTextIndent(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellTextIndent(IN int iRow_abs, IN int iCol, IN OPTIONAL double rValue = -1) = 0;
	// Вертикальный отступ текста
	virtual double    getCellTextVerticalIndent(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellTextVerticalIndent(IN int iRow_abs, IN int iCol, IN OPTIONAL double rValue = -1) = 0;
	// Толщина линий текста
	virtual int       getCellTextWeight(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellTextWeight(IN int iRow_abs, IN int iCol, IN OPTIONAL int iValue = MCSLWT_DEFAULT) = 0;
	// Цвет линий текста
	virtual COLORREF  getCellTextColor(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellTextColor(IN int iRow_abs, IN int iCol, IN OPTIONAL COLORREF iValue = MCSRGB_DEFAULT) = 0;
	// Текст по вертикали в градусах. Пока поддерживаются только два значения: 0 и 90
	virtual double    getCellTextAngle(IN int iRow_abs, IN int iCol) = 0;
	virtual HRESULT   setCellTextAngle(IN int iRow_abs, IN int iCol, IN double rValue) = 0;
	// Наклон текста
	virtual double    getCellTextOblique(IN int iRow_abs, IN int iCol) = 0;
	// Толщина линий по границам ячейки
	virtual int       getCellBorderAbs(IN int iRow_abs, IN int iCol_abs, IN McTable2BorderType nSide, IN OPTIONAL bool fEffecive = true) = 0;
	virtual int       getCellBorderDrw(IN int iRow_drw, IN int iCol_drw, IN McTable2BorderType nSide, IN OPTIONAL bool fEffecive = true) = 0;
	virtual HRESULT   setCellBorderAbs(IN int iRow_abs, IN int iCol_abs, IN McTable2BorderType nSide, IN OPTIONAL int ilw = MCSLWT_DEFAULT) = 0;
	// Цвет линий по границам ячейки
	virtual COLORREF  getCellColorAbs(IN int iRow_abs, IN int iCol_abs, IN McTable2BorderType nSide, IN OPTIONAL bool fEffecive = true) = 0;
	virtual COLORREF  getCellColorDrw(IN int iRow_drw, IN int iCol_drw, IN McTable2BorderType nSide, IN OPTIONAL bool fEffecive = true) = 0;
	virtual HRESULT   setCellColorAbs(IN int iRow_abs, IN int iCol_abs, IN McTable2BorderType nSide, IN OPTIONAL COLORREF rgb = MCSRGB_DEFAULT) = 0;
	// Присоединённый блок
	virtual mcsWorkID getCellBlockAbs(IN int iRow_abs, IN int iCol_abs, OUT OPTIONAL McsString* pstrName = NULL, OUT OPTIONAL McsString* pstrFile = NULL) = 0;
	virtual HRESULT   setCellBlockAbs(IN int iRow_abs, IN int iCol_abs, IN OPTIONAL LPCTSTR strBlockName = NULL, IN OPTIONAL LPCTSTR strFileName = NULL) = 0;
	virtual HRESULT   setCellBlockAbs(IN int iRow_abs, IN int iCol_abs, const mcsWorkID& id = mcsWorkID()) = 0;
	// Цвет заливки
	virtual COLORREF  getCellFillColor(IN int iRow_abs, IN int iCol_abs) = 0;
	virtual HRESULT   setCellFillColor(IN int iRow_abs, IN int iCol_abs, IN OPTIONAL COLORREF rgbValue = MCSRGB_NONE) = 0;
	// Тип данных в ячейке
	virtual McTable2CellFormat getCellType(IN int iRow_abs, IN int iCol_abs) = 0;
	virtual HRESULT   setCellType(IN int iRow_abs, IN int iCol_abs, IN McTable2CellFormat Value) = 0;
	// Точность представления чисел. Только для kMcTable2Cell_Number.
	// На вычисления не влияет - изменяет только внешний вид значения в ячейке.
	virtual McTable2CellPrecision getCellPrecision(IN int iRow_abs, IN int iCol_abs) = 0;
	virtual HRESULT   setCellPrecision(IN int iRow_abs, IN int iCol_abs, IN McTable2CellPrecision Value) = 0;
	// Подавление ведомых нулей. Только для kMcTable2Cell_Number.
	virtual bool      getCellZeros(IN int iRow_abs, IN int iCol_abs) = 0;
	virtual HRESULT   setCellZeros(IN int iRow_abs, IN int iCol_abs, IN bool fShowZeros) = 0;
	// Текст ячейки может редактироваться пользователем
	virtual BOOL      getCellEnabled(IN int iRow_abs, IN int iCol_abs) = 0;
	virtual HRESULT   setCellEnabled(IN int iRow_abs, IN int iCol_abs, IN OPTIONAL BOOL fEnable = TRUE) = 0;
	// Текст ячейки вычисляется автоматически, изменить его не получится ни из кода, ни интерактивно
	virtual BOOL      getCellReadOnly(IN int iRow_abs, IN int iCol_abs) = 0;
	// Текст в ячейке перекрывает границы ячеек и другие объекты
	virtual BOOL      getCellWipeout(IN int iRow_abs, IN int iCol_abs) = 0;
	virtual HRESULT   setCellWipeout(IN int iRow_abs, IN int iCol_abs, IN OPTIONAL BOOL fValue = TRUE) = 0;
	// Текст в ячейке размещается внизу, если строка была расширена виртуальными строками
	virtual bool      getCellPlaceBelow(IN int iRow_abs, IN int iCol_abs) = 0;
	virtual HRESULT   setCellPlaceBelow(IN int iRow_abs, IN int iCol_abs, IN OPTIONAL bool bValue = true) = 0;
	// Сбрасывает всё форматирование ячейки, текст, комментарий и формулу. Границы не меняет.
	virtual HRESULT   ResetCell(IN int iRow_abs, IN int iCol) = 0;

	// Изменение структуры
	virtual HRESULT   InsertCol(IN OPTIONAL int iTo_abs = -1, IN OPTIONAL int iCount = 1) = 0;
	virtual HRESULT   DeleteCol(IN OPTIONAL int iFrom_abs, IN OPTIONAL int iCount = 1) = 0;
	virtual HRESULT   MoveCol(IN int iFrom_abs, IN int iTo_abs, IN OPTIONAL int iCount = 1) = 0;
	virtual HRESULT   CopyCol(IN int iSource_abs, IN OPTIONAL int iTo_abs = -1, IN OPTIONAL int iCount = 1, IN OPTIONAL bool fWithContent = true) = 0;
	virtual HRESULT   CopyRow(IN int iSource_abs, IN OPTIONAL int iTo_abs = -1, IN OPTIONAL int iCount = 1, IN OPTIONAL bool fWithContent = true) = 0;
	virtual HRESULT   InsertRow(IN OPTIONAL int iTo_abs = -1, IN OPTIONAL int iCount = 1) = 0;
	virtual HRESULT   DeleteRow(IN int iFrom_abs, IN OPTIONAL int iCount = 1) = 0;
	virtual HRESULT   MoveRow(IN int iFrom_abs, IN int iTo_abs, IN OPTIONAL int iCount = 1) = 0;

	// Получение координат ячейки по точке на чертеже. Точка - в системе координат объекта.
	virtual HRESULT   getCellFromPointDrw(IN const mcsPoint& pt, OUT int& iRow_drw, OUT int& iCol_drw) = 0;
	virtual HRESULT   SplitCellsDrw(IN mcsPoint ptFrom_drw, IN mcsPoint ptTo_drw) = 0;
	virtual HRESULT   getRectBoundsDrw(IN const RECT& rc_drw, OUT mcsPoint& ptMin, OUT mcsPoint& ptMax) = 0;
	virtual int       getGSMarkerOfCell(IN int iRow_drw, IN int iCol) = 0;
	virtual HRESULT   getCellByGSMarker(IN int iGSMarker, OUT int& iRow_drw, OUT int& iCol) = 0;

	// Группировка ячеек
	virtual HRESULT   getCellRectAbs(IN int iRow_abs, IN int iCol_abs, OUT RECT& rc_abs) = 0;       	// Диапазон ячеек, включающий данную ячейку
	virtual HRESULT   getCellRectDrw(IN int iRow_drw, IN int iCol_drw, OUT RECT& rc_drw) = 0;
	virtual	HRESULT   Merge(IN RECT rc_abs) = 0;
	virtual HRESULT   Unmerge(IN RECT rc_abs) = 0;
	virtual HRESULT   Regroup(IN RECT rc_abs, IN OPTIONAL int iRows = -1, IN OPTIONAL int iCols = -1, IN OPTIONAL bool fCopyContent = false) = 0;

	// Диалоги
	virtual HRESULT   CallCellDlg(IN RECT rc_abs, IN OPTIONAL HWND hParent = NULL) = 0;
	virtual HRESULT   CallColDlg(IN int iCol, IN OPTIONAL HWND hParent = NULL) = 0;
	virtual HRESULT   CallRowDlg(IN int iRow_abs, IN OPTIONAL HWND hParent = NULL) = 0;
	virtual HRESULT   CallSplitDlg(IN RECT rc_abs, IN OPTIONAL HWND hParent = NULL) = 0;

// Чтение/запись
	// Файл. Если strFilename пустой, откроется диалог выбора файла. Тип файла определяется расширением.
	virtual HRESULT   SaveToFile(IN OPTIONAL LPCTSTR strFilename = NULL, IN OPTIONAL HWND hParent = NULL) = 0;
	virtual HRESULT   LoadFromFile(IN OPTIONAL LPCTSTR strFilename = NULL, IN OPTIONAL HWND hParent = NULL) = 0;
	// База стандартных. Если uid = 0, откроется диалог выбора элемента
	virtual HRESULT   SaveToBase(IN OPTIONAL MCSUID uid = 0, IN OPTIONAL HWND hParent = NULL) = 0;
	virtual HRESULT   LoadFromBase(IN OPTIONAL MCSUID uid = 0, IN OPTIONAL HWND hParent = NULL) = 0;
	// Excel. Если путь не указан, работает с открытым приложением. При импорте берет только селекцию текущей
	// страницы или весь используемый диапазон на странице, если селектирована одна ячейка.
	virtual HRESULT   ExportToExcel(IN OPTIONAL LPCTSTR strPath = NULL, const McTable2ConversionOptions* pOptions = NULL) = 0;
	virtual HRESULT   ImportFromExcel(IN OPTIONAL LPCTSTR strPath = NULL, IN OPTIONAL LPCTSTR strSheet = NULL) = 0;
	// Текстовый файл. Если strFilename пустой, откроется диалог выбора файла.
	virtual HRESULT   ExportToText(IN LPCTSTR strPath, IN OPTIONAL TCHAR tchDelimiter = _T(';')) = 0;
	virtual HRESULT   ImportFromText(IN LPCTSTR strPath, IN OPTIONAL TCHAR tchDelimiter = _T(';')) = 0;
	// Запрос из базы.
	virtual HRESULT   ImportFromDB(IN LPCTSTR strPath, IN LPCTSTR strQuery) = 0;
	virtual HRESULT   ImportFromSelectionSet(IN IUnknown* pSelectionSet, IN OPTIONAL HWND hParent = NULL) = 0;

// Пользовательская форма
	virtual HRESULT   FormShow(HWND hParent) = 0;
	virtual HRESULT   FormEdit(HWND hParent) = 0;

// Разделы таблицы
// Разделы колонтитулов, заголовка отчёта и итога отчёта содержат служебную (разделительную) строку.
// Это строка обеспечивает возможность назначать разные границы ячеек на колонтитул и смежый с ним
// раздел. Строка имеет неизменную нулевую высоту, на экран не выводится.
	virtual HRESULT   getSectionType(IN int iRow_abs, McTable2SectionType& stp) = 0;
	virtual HRESULT   addSection(
		IN int iRow_abs,
		IN McTable2SectionType stp,
		IN OPTIONAL int iRowCount = 1          // количество строк без учёта служебной строки колонтитула
	) = 0;
	virtual HRESULT   getSectionPos(
		IN int iRow_abs,
		OUT int& iRowFirst_abs,
		OUT int& iRowCount                     // количество строк вместе со служебной строкой
	) = 0;
	// Восстановить служебные строки после удаления, добавления, перемещения или изменения типа строк.
	virtual HRESULT   UpdateSystemRows() = 0;
	// Преобразовать отчёт в статические строки. iRow_abs - любая строка из шаблона отчёта.
	virtual HRESULT   MakeReportSectionStatic(IN int iRow_abs, const McTable2ConversionOptions* pOptions = NULL) = 0;

	// Идентификатор объекта. Определён только для строк отчёта
	virtual mcsWorkID getRowObject(IN int iRow_abs) = 0;
	// Фильтр выбора объектов. Определён только для строк отчёта
	virtual IMcSelectionSetPtr GetFilter(IN int iRow_abs) = 0;

	// Вставить таблицу
	virtual HRESULT   InsertSubtable(IN IMcTable2* pSubtable, IN int iRow_abs, IN int iCol, IN McTable2InsertionMode mode) = 0;

	// Присоединить объект. К присоединённому объекту можно обращаться в формуле,
	// используя имя msName. Ненужные объекты автоматически отсоединяются после пересчёта.
	// Внимание! После пересчёта таблицы имена объектов могут измениться.
	virtual HRESULT   AttachObject(IN const mcsWorkID& idObject, OUT McsString& msName) = 0;

	// Внедрить таблицу в формат. Если таблица не помещается, она разбивается на страницы.
	// Для каждой страницы создаётся отдельный формат.
	virtual HRESULT   setFrame(IN IMcFormat* pFrame = NULL) = 0;

	// S_FALSE - скрыта
	// S_OK - не скрыта
	// DISP_E_BADINDEX - индекс вне таблицы
	virtual HRESULT   getRowHiddenAbs(IN int iRow_abs) = 0;

	// S_FALSE - не скрыт
	// S_OK - скрыт
	// DISP_E_BADINDEX - индекс вне таблицы
	virtual HRESULT   getColHidden(IN int iCol) = 0;
	virtual HRESULT   setColHidden(IN int iCol, IN BOOL fHide) = 0;

	// Наклон текста
	virtual HRESULT   setCellTextOblique(IN int iRow_abs, IN int iCol, double rValue) = 0;

	// Описание:
	//   Возвращает значение флага, указывающего, будет ли использоваться исходное форматирование ячеек
	//   при импорте данных из другой таблицы таблицы. Если возвращаемое значение false, то будут импортированы
	//   только данные ячеек. По умолчанию возвращает false.
	virtual bool GetUseOriginFormat() = 0;
	// Описание:
	//   Задаёт значение флагу, указывающему, будет ли использоваться исходное форматирование ячеек
	//   при импорте данных из другой таблицы. Если задано значение false, то будут импортированы
	//   только данные ячеек. По умолчанию возвращает false.
	virtual void SetUseOriginFormat(bool bUseOriginFormat) = 0;

	// Сбросить все данные таблицы
	virtual HRESULT Clear() = 0;

	virtual McsString getTitle() = 0;
	virtual void setTitle(LPCTSTR st) = 0;
	virtual McsString getFile() = 0;
	virtual void setFile(LPCTSTR st) = 0;
	virtual McsString getQuery() = 0;
	virtual void setQuery(LPCTSTR st) = 0;

	// Описание:
	//   Возвращает значение, указывающее, будет ли открываться форма таблицы вместо редактора таблицы
	//   на команды redit и dedit. Если у таблицы нет формы, то метод всегда возвращает false.
	//   По умолчанию имеет значение false.
	virtual bool ShouldEditInForm() = 0;
	// Описание:
	//   Задаёт значение, указывающее, будет ли открываться форма таблицы вместо редактора таблицы
	//   на команды redit и dedit.
	virtual void SetShouldEditInForm(bool bEditInForm) = 0;
};

// Свойство для разовой блокировки масштабирования встроенных в таблицу блоков на onUpdate
#ifndef LOCK_BLOCKSCALE_PROPNAME
#define LOCK_BLOCKSCALE_PROPNAME _T("LockScaleBlocksOnUpdate")
#endif