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
#include <atltime.h>


//////////////////////////////////////////////////////////////////////////
typedef McsArray<IMcFormatPtr, IMcFormat*> mcsFormatArray;


//////////////////////////////////////////////////////////////////////////
// Формат
interface IMcFormat : public IMcEntity
{
	// СВОЙСТВА
	// Шаблон. Идентификатор объекта с классом FORMAT_CLASS или TITLE_CLASS в базе стандартных элементов.
	// В шаблоне FORMAT_CLASS содержится тип рамки (стандартная с указанием стандарта или произвольная с
	// определением геометрии), тип, положение и выравнивание надписей. Стандартные умеют масштабироваться,
	// пользовательские имеют один фиксированный размер. В шаблоне TITLE_CLASS для каждого типоразмера
	// сохраняется своя геометрия и штампы.
	virtual MCSUID getTemplate() = 0;
	virtual HRESULT setTemplate(IN MCSUID Value) = 0;
	// Обозначение
	virtual McsString getName() = 0;                     // A4, A3x3 и т.п.
	virtual HRESULT setName(IN LPCTSTR Value) = 0;
	// Тип формата
	virtual McFormatEnum getFormat() = 0;
	virtual HRESULT setFormat(IN McFormatEnum Value) = 0;
	virtual HRESULT setFormat(int iWidth, int iHeight) = 0;
	// Кратность.
	// Стандарт ограничивает список возможных кратностей.
	// Список возможных значений можно получить через getPropertyInfo(MCS_PROP_FMT_MULTIPLICITY, ...)
	virtual int getMultiplicity() = 0;
	virtual HRESULT setMultiplicity(IN int Value) = 0;
	// Размеры формата
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	// Смена стандарта
	virtual HRESULT setStandard(IN MCS_STANDARD Value) = 0;
	// Ориентация листа
	virtual bool getHorizontal() = 0;
	virtual HRESULT setHorizontal(IN bool Value) = 0;
	// Первый или следующий лист. Влияет на внешний вид надписей.
	virtual bool getFirst() = 0;
	virtual HRESULT setFirst(IN bool Value) = 0;
	// Автонумерация
	virtual bool getAutonum() = 0;
	virtual HRESULT setAutonum(IN bool Value) = 0;
	// Начать нумерацию с этого листа
	virtual bool getStart() = 0;
	virtual void setStart(IN bool Value) = 0;
	// Номер листа
	virtual int getSheet() = 0;
	virtual HRESULT setSheet(IN int Value) = 0;
	virtual McsString getSheetEx() = 0;
	virtual HRESULT setSheetEx(IN McsString Value) = 0;
	// Количество листов
	virtual int getSheetCount() = 0;
	virtual HRESULT setSheetCount(IN int Value) = 0;
	virtual McsString getSheetCountEx() = 0;
	virtual HRESULT setSheetCountEx(IN McsString Value) = 0;
	// Дополнительные поля в надписях.
	virtual bool getAdditionalFields() = 0;
	virtual HRESULT setAdditionalFields(IN bool Value) = 0;
	// Маркеры центровки (для ISO).
	virtual bool getCentringMarks() = 0;
	virtual HRESULT setCentringMarks(IN bool Value) = 0;
	// Обозначать зоны
	virtual bool getZones() = 0;
	virtual HRESULT setZones(IN bool Value) = 0;
	// Начало нумерации зон в формате (в многолистовых документах нумерация зон сквозная,
	// при включенной автонумерации корректируется автоматически).
	virtual int getFirstZone() = 0;
	virtual HRESULT setFirstZone(IN int Value) = 0;
	virtual int getLastZone() = 0;
	// Масштаб измерений внутри формата.
	virtual double getDimScale() = 0;
	virtual HRESULT setDimScale(IN double Value) = 0;
	// Обозначение неуказанной шероховатости поверхностей.
	// Самостоятельный объект, привязанный к координатам рамки.
	virtual mcsWorkID getRoughness() = 0;
	virtual HRESULT setRoughness(IN const mcsWorkID& id) = 0;
	// Точка вставки шероховатости.
	virtual mcsPoint getRoughnessPos() = 0;
	// Координаты левого нижнего угла рамки.
	virtual mcsPoint getOrigin() = 0;
	virtual HRESULT setOrigin(IN const mcsPoint& Value) = 0;

	// ФУНКЦИИ
	// Подобрать размер, кратность, положение формата, чтобы он вместил указанный прямоугольник
	virtual HRESULT SelectFormatFor(IN const mcsBoundBlock& drawing_bounds) = 0;
	// Проверяет, лежит ли точка внутри формата и возвращает обозначение зоны, в которой находится точка
	virtual bool PointInFormat(IN const mcsPoint& Value, OUT OPTIONAL McsString* pZone = NULL) = 0;
	// Время создания формата
	virtual CTime getCreateTime() = 0;
	// Основная надпись. Объект типа IMcFormatStamp или IMcTable2
	virtual IMcEntityPtr getMainStamp() = 0;
	virtual HRESULT setMainStamp(IN IMcEntity* Value) = 0;
	// Координаты области технических требований.
	// Index - номер столбца текста, начиная с нуля.
	virtual HRESULT getTechReqBlock(IN int Index, OUT mcsBoundBlock& Block) = 0;
	virtual HRESULT getTechReqBlock_OCS(IN int Index, OUT mcsBoundBlock& Block) = 0;

	// Изменить порядок следования автонумерованных форматов
	virtual HRESULT MoveSheet(IN int iNewSheet) = 0;
	// Внутренняя область формата за вычетом надписей.
	// В локальной системе координат.
	virtual HRESULT getClient(OUT mcsPolyline& plInternalContour) = 0;
	// Прямоугольник максимальной площади, вписанный во внутреннюю область формата.
	// В локальной системе координат.
	virtual HRESULT getClient(OUT mcsBoundBlock& Bounds) = 0;

	// Логический тип формата. Задаётся в шаблоне.
	enum Type {
		kType_Drawing = 0,               // графический или текстовый документ
		kType_Title = 1,                 // титульный лист
		kType_Cover = 2                  // обложка
	};
	virtual Type getType() = 0;
	virtual McsString getTextStyle() = 0;
	virtual HRESULT setTextStyle(IN McsString Value) = 0;
	virtual bool getObliqueByStyle() = 0;
	virtual HRESULT setObliqueByStyle(bool bValue) = 0;
	virtual bool getXScaleByStyle() = 0;
	virtual HRESULT setXScaleByStyle(bool bValue) = 0;

	// Индекс области печати
	virtual int getPrintAreaIndex() = 0;
	virtual HRESULT setPrintAreaIndex(IN int Value) = 0;

	//---------------------------------------------------------------------------
	enum StandardVersion
	{
		ksvUndefined,
		ksv1997,
		ksv2009,
		ksv2013,
	};
	virtual StandardVersion getStandardVersion() const = 0;
	virtual HRESULT setStandardVersion(StandardVersion eValue) = 0;

	// Граница бумаги
	virtual bool getPaperBoundVisibility() const = 0;
	virtual HRESULT setPaperBoundVisibility(IN bool Value) = 0;

	// Источник св-в для формата, по умолчанию тот же документ, в котором находится формат.
	// Но его можно переназначить.
	virtual IMcPropertySourcePtr getLinkedPropSource(OUT mcsPropertyType& propsType, OUT bool& bReadOnlyPropSet) = 0;

	// Автоматически подключить формат к объекту, с которым должен синхронизироваться масштаб в основной надписи.
	virtual bool attachToDScaleSrcObj() { return false; }

	// Загрузка свойств из связанного источника, возвращаемого методом getLinkedPropSource()
	virtual HRESULT loadDataFromLinkedPropSource() { return E_NOTIMPL; }
};



//------------------------------------------------------------------------
// Встроенные свойства формата (getProperties)
const McsString MCS_PROP_FMT_ZONE         = _T("Zone");              // Начальный индекс зоны
const McsString MCS_PROP_FMT_AUTONUM      = _T("Autonumerated");     // Автонумерация листов
const McsString MCS_PROP_FMT_FIRST        = _T("First sheet");       // Первый лист документа
const McsString MCS_PROP_FMT_ZONES        = _T("Show zones");        // Показывать зоны
const McsString MCS_PROP_FMT_XVIEW        = _T("Extended view");     // Расширенный вид надписей
const McsString MCS_PROP_FMT_ORIENTATION  = _T("Orientation");       // Горизонтальный или вертикальный
const McsString MCS_PROP_FMT_MULTIPLICITY = _T("Multiplicity");      // Кратность
const McsString MCS_PROP_FMT_VERSION      = _T("Std version");       // Версия стандарта. 0 - ГОСТ 21.101-97, 1 - ГОСТ 21.1101-2009, 2 - ГОСТ 21.1101-2013.
const McsString MCS_PROP_FMT_2013_5MM     = _T("GOST2013.5mm");      // Нижний отступ - 5мм
const McsString MCS_PROP_FMT_PAPER_BOUND  = _T("PaperBound");        // Отображение границы бумаги
// pt
const McsString MCS_PROP_FMT_LEFT         = _T("Margin.left");       // Отступ слева
const McsString MCS_PROP_FMT_RIGHT        = _T("Margin.right");      // Отступ справа
const McsString MCS_PROP_FMT_TOP          = _T("Margin.top");        // Отступ сверху
const McsString MCS_PROP_FMT_BOTTOM       = _T("Margin.bottom");     // Отступ снизу
const McsString MCS_PROP_FMT_OBLIQUE_BYSTYLE = _T("ObliqueByStyle");
const McsString MCS_PROP_FMT_XSCALE_BYSTYLE = _T("XScaleByStyle");



//////////////////////////////////////////////////////////////////////////
// Надпись (штамп формата)
interface IMcFormatStamp : public IMcEntity
{
	// Идентификатор шаблона с классом STAMP_CLASS в базе стандартных элементов.
	virtual MCSUID getTemplate() const = 0;
	virtual void getTemplate(
		OUT MCSUID& Value,                    // идентификатор шаблона
		OUT bool& fFirst,                     // вид для первого листа
		OUT bool& fExtended                   // вид с дополнительными полями
	) const = 0;
	virtual bool setTemplate(IN MCSUID Value, IN bool fFirst, IN bool fExtended) = 0;

// Для внутреннего использования.
	// Связать объект с шаблоном из базы. Объект не перечитывается, просто запоминает,
	// откуда брать геометрию. Сделано специально для вставки из браузера
	virtual bool assignTemplate(IN MCSUID Value) = 0;
	virtual HRESULT setGeometry(IN const mcsGeomEntArray& Content) = 0;
	// Загрузить значения полей по умолчанию.
	virtual HRESULT loadDefaults() = 0;
	// Сохранить текущие значения полей как значения по умолчанию.
	virtual HRESULT saveDefaults() = 0;
	// Показывать имена полей вместо значений.
	virtual bool getShowFieldNames() = 0;
	virtual void setShowFieldNames(bool Value) = 0;

	virtual IMcFormat::StandardVersion getStandardVersion() const = 0;
	virtual HRESULT setStandardVersion(IMcFormat::StandardVersion eValue) = 0;
};


//////////////////////////////////////////////////////////////////////////
// Управление форматами документа
struct IMcFormatManager
{
	// Получить формат, содержащий указанную точку.
	virtual IMcFormatPtr GetFormatAtPoint(IN const mcsPoint& pt,
															OUT OPTIONAL McsString* pZone = NULL,		// Имя зоны, в которой находится точка. Например, "B3"
															IN OPTIONAL IMcDocument* pDoc = NULL,		// по умолчанию поиск ведется в активном документе
																										// ----------------------------------------------------
																										// Читай комм. к GetAllFormats()
															IN OPTIONAL bool bGetTopDoc = true) = 0;	// true - вызывает getTopDoc, false - нет

	// Получить измерительный масштаб из формата в текущем листе, который содержит указанную точку.
	// Если точка не попадает в формат, вернёт глобальный масштаб измерений из текущего листа.
	virtual double GetScaleAtPoint(IN const mcsPoint& pt,
																 IN OPTIONAL IMcDocument* pDoc = NULL) = 0;        // по умолчанию поиск ведется в активном документе

	// Найти следующий формат.
	virtual HRESULT GetNextSheet(IN OUT IMcFormatPtr& pSheet,                        // Если pSheet == NULL, вернет последний лист
															 IN OPTIONAL IMcDocument* pDoc = NULL,               // по умолчанию поиск ведется в активном документе
															 IN OPTIONAL bool only_auto = false) = 0;            // можно получить только автонумерованные форматы

	// Найти предыдущий формат.
	virtual HRESULT GetPrevSheet(IN OUT IMcFormatPtr& pSheet,                        // Если pSheet == NULL, вернет первый лист
															 IN OPTIONAL IMcDocument* pDoc = NULL,               // по умолчанию поиск ведется в активном документе
															 IN OPTIONAL bool only_auto = false) = 0;            // можно получить только автонумерованные форматы

	// Создать следующий формат в документе. Автоматически присваивается обозначение, наименование, номер листа и т.п.
	virtual IMcFormatPtr CreateNextFormat(IN OPTIONAL IMcFormat* pPrev = NULL) = 0;

	// Список доступных наменований форматов, которые можно передавать в IMcFormat::setName.
	// Для ЕСКД, СПДС и DIN допускается добавлять к наименованию кратность в виде <имя>x<кратность_числом>.
	virtual HRESULT GetAvailableFormats(OUT mcsStringArray& names,
																			IN OPTIONAL MCS_STANDARD Std = MCS_STD_CUSTOM) = 0;  // по умолчанию берется текущий стандарт

	// Получить список форматов из документа. Форматы отсортированы времени создания.
	virtual HRESULT GetAllFormats(
		OUT mcsFormatArray& Res,
		IN OPTIONAL IMcDocument* pDoc = NULL,				// по умолчанию поиск ведется в активном документе
		IN OPTIONAL bool only_auto = false,					// можно получить только автонумерованные форматы
															// --------------------------------------------------------------------------------------------------------------------------------
															// По умолчанию для активного или переданного документа pDoc
															// вызывается функция GetTopDoc и поиск форматов ведется в родительском документе и функция
															// возвращает форматы всех дочерних документов.
															// Такое поведение приводит к
															// #5221 - Выноска спецификации неправильно берет зону с формата:
															//
															// Выноска спецификации вызывает IMcFormatManager.GetFormatAtPoint() для получения зоны.
															// Внутри происходит вызов IMcFormatManager.GetAllFormats() куда передается лист, на котором стоит выноска.
															// Но из-за вызова pDoc->GetTopDoc поиск форматов происходит по всем листам. Далее ищется формат, который содержит переданную точку.
															// И находится такой формат, на другом листе, который расположен ранее. Этот формат имеет совсем другую нумерацию зон.
															// Флаг bGetTopDoc позволяет отключить вызов функции GetTopDoc и производить поиск форматов только в активном\переданном документе.
															//
		IN OPTIONAL bool bGetTopDoc = true) = 0;			// true - вызывает getTopDoc, false - нет

	// Обновить нумерацию форматов в документе.
	virtual HRESULT UpdateFormats(IN mcsFormatArray& list) = 0;

	// Начало отсчета для автонумерации
	virtual int GetStartSheet() = 0;
	virtual HRESULT SetStartSheet(IN int Value) = 0;

	// Начало отсчета для зон
	virtual int GetStartZone() = 0;
	virtual HRESULT SetStartZone(IN int Value) = 0;

	// Листы, которые нужно пропускать при автонумерации
	virtual HRESULT GetSheetsToSkip(OUT mcsIntArray& Result) { return E_NOTIMPL; }
	virtual HRESULT SetSheetsToSkip(IN const mcsIntArray& Value) { return E_NOTIMPL; }

// Для внутреннего использования.
	// Реакторы на изменение форматов. Вызываются самими форматами.
	virtual HRESULT OnCreateFormat(IN IMcFormat* pObject) = 0;
	virtual HRESULT OnChangeFormat(IN IMcFormat* pObject) = 0;
	virtual HRESULT OnEraseFormat(IN IMcFormat* pObject) = 0;

	// Копирует общие свойства документа с формата pForm на форматы pTo
	virtual HRESULT CopyCommonFields(IN IMcFormat* pFrom, IN mcsFormatArray& pTo) = 0;

	// Получение списка шаблонов форматов
	virtual HRESULT GetFormatTemplates(IN MCS_STANDARD std, OUT mcsStringArray& names, OUT mcsMCSUIDArray& uids) = 0;
};


//////////////////////////////////////////////////////////////////////////
// Константы для базы
#define FORMAT_CLASS        806
#define TITLE_CLASS         809
#define FORMAT_DOC          _T("Sheet")

#define STAMP_CLASS         807
#define STAMP_DOC_FIRST     _T("First sheet")
#define STAMP_DOC_NEXT      _T("Next sheet")
#define STAMP_DOC_FIRST_X   _T("First sheet extended")
#define STAMP_DOC_NEXT_X    _T("Next sheet extended")

// Предопределённые форматы для стандартов
static const MCSUID UID_STDFRAME_GOST      (0);
static const MCSUID UID_STDFRAME_ISO       (-1);
static const MCSUID UID_STDFRAME_DIN       (-2);
static const MCSUID UID_STDFRAME_SPDS      (-3);
static const MCSUID UID_STDFRAME_GB        (-4);
static const MCSUID UID_STDFRAME_NF        (-5);
static const MCSUID UID_STDFRAME_IS        (-6);
static const MCSUID UID_STDFRAME_SPDS_2009 (-9);
static const MCSUID UID_STDFRAME_SPDS_2013 (-10);
static const MCSUID UID_STDFRAME_NONE      (-20);

