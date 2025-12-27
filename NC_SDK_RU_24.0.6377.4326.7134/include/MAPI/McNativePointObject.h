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

#include "mcNativeLongObject.h"
#include "Controls/CxImage.h"

//---------------------------------------------------------
enum McsNativePointTypeEnum
{
	NPT_SIMPLE_POINT = 0,							// точка
	NPT_SIMPLE_CIRCLE,								// окружность
	//---------------------------------------------------------------------------------------------
	// ППР::Точечные объекты
	//---------------------------------------------------------------------------------------------
	NPT_PPR_AUTOMOBILE_GATE,						// Ворота
	NPT_PPR_PEDESTRIAN_DOOR,						// Калитка
	NPT_PPR_MOBILE_CRANE_STOP,						// Стоянка крана
	NPT_PPR_WIND_DISTRIBUTION,						// Роза ветров
	NPT_PPR_COMPASS,								// Компас
	NPT_PPR_INFORMATION_STAND,						// Информационный щит
	NPT_PPR_FIRE_STAND,								// Противопожарный щит
	NPT_PPR_BREAKOUT_AXIS,							// Знак разбивочных осей
	NPT_PPR_LIGHT_MAST,								// Прожекторная мачта
	NPT_PPR_LIGHT_STAND,							// Опора со светильником
	NPT_PPR_LIGHT_STRETCH_STAND,					// Опора с оттяжкой и светильником
	NPT_PPR_FIRE_HYDRANT,							// Пожарный гидрант
	NPT_PPR_DISTRIBUTOR_BOX,						// Шкаф распределительный
	NPT_PPR_DISTRIBUTOR_PANEL,						// Щиток подключения
	NPT_PPR_CRANE_LIMIT_SIGN,						// Знак предупреждения об ограничении зоны действия крана
	NPT_PPR_NO_LIFT_SIGN,							// Знак, запрещающий пронос груза
	NPT_PPR_CRANE_WORK_SIGN,						// Знак, предупреждающий о работе крана, с поясняющей надписью
	NPT_PPR_ELECTRICAL_POWER_PANEL,					// Шкаф электропитания крана
	NPT_PPR_ENTRANCE_TRANSPORT_SCHEME,				// Въездной стенд с транспортной схемой
	NPT_PPR_CARGO_LIFT_STAND,						// Стенд со схемами строповки и таблицей масс грузов
	NPT_PPR_ACETYLINE_STORAGE_BOX,					// Шкаф для хранения баллонов с ацетиленом
	NPT_PPR_OXYGEN_STORAGE_BOX,						// Шкаф для хранения баллонов с кислородом
	NPT_PPR_SIGNAL_MAN_PLACE,						// Местонахождение сигнальщика (стропальщика)
	NPT_PPR_WELL,									// Колодец
	NPT_PPR_STAND,									// Опора
	NPT_PPR_CUSTOM_SIGN,							// Знак с пользовательской графикой и атрибутами (дорожный знак, знак безопасности и т.д.)
	NPT_PPR_MOBILE_CRANE_STOP2,						// Стоянка крана 2 (с крестом вместо точки)
	NPT_PPR_SUMP,									// Зумпф ( Отстойник )
	NPT_PPR_TANK_SUMP,								// Резервуар-отстойник
	NPT_PPR_COVERED_CANOPY,							// Крытый навес
	NPT_PPR_GARBAGE_DUMP,							// Мусоросброс
	NPT_PPR_DISMANTLING_OBJECT,						// Объект демонтажа
	//---------------------------------------------------------------------------------------------
	NPT_MAX_INDEX,									// добавлять новые типы до этой метки
	//---------------------------------------------------------------------------------------------
};

//----------------------------------------
enum PointTypeParamEnum
{
	PTPAR_UNDEFINED = 0,
	PTPAR_SIMPLE_POINT_DIAMETER,
	PTPAR_SIMPLE_CIRCLE_DIAMETER,
	PTPAR_PPR_AUTOMOBILE_GATE_SIZE,					// ВОРОТА : Размер
	PTPAR_PPR_PEDESTRIAN_DOOR_SIZE,					// КАЛИТКА : Размер
	PTPAR_PPR_CRANE_CIRCLE_DIAMETER,				// СТОЯНКА КРАНА : Диаметр окружности
	PTPAR_PPR_CRANE_POINT_DIAMETER,					// СТОЯНКА КРАНА : Диаметр точки
	PTPAR_PPR_WELL_DIAMETER,						// КОЛОДЕЦ : Диаметр
	PTPAR_PPR_STAND_DIAMETER,						// ОПОРА : Диаметр
	PTPAR_PPR_INFORMATION_STAND_LENGTH,				// ИНФОРМАЦИОННЫЙ ЩИТ : Длина
	PTPAR_PPR_INFORMATION_STAND_WIDTH,				// ИНФОРМАЦИОННЫЙ ЩИТ : Ширина
	PTPAR_PPR_FIRE_STAND_LENGTH,					// ПРОТИВОПОЖАРНЫЙ ЩИТ : Длина
	PTPAR_PPR_FIRE_STAND_WIDTH,						// ПРОТИВОПОЖАРНЫЙ ЩИТ : Ширина
	PTPAR_PPR_DISTRIBUTOR_BOX_LENGTH,				// ШКАФ РАСПРЕДЕЛИТЕЛЬНЫЙ : Длина
	PTPAR_PPR_DISTRIBUTOR_BOX_WIDTH,				// ШКАФ РАСПРЕДЕЛИТЕЛЬНЫЙ : Ширина
	PTPAR_PPR_DISTRIBUTOR_PANEL_LENGTH,				// ЩИТОК ПОДКЛЮЧЕНИЯ : Длина
	PTPAR_PPR_DISTRIBUTOR_PANEL_WIDTH,				// ЩИТОК ПОДКЛЮЧЕНИЯ : Ширина
	PTPAR_PPR_ENTRANCE_TRANSPORT_SCHEME_LENGTH,		// ВЬЕЗДНОЙ СТЕНД С ТРАНСПОРТНОЙ СХЕМОЙ : Длина
	PTPAR_PPR_ENTRANCE_TRANSPORT_SCHEME_WIDTH,		// ВЬЕЗДНОЙ СТЕНД С ТРАНСПОРТНОЙ СХЕМОЙ : Ширина
	PTPAR_PPR_CARGO_LIFT_STAND_LENGTH,				// СТЕНД СО СХЕМАМИ СТРОПОВКИ : Длина
	PTPAR_PPR_CARGO_LIFT_STAND_WIDTH,				// СТЕНД СО СХЕМАМИ СТРОПОВКИ : Ширина
	PTPAR_PPR_ELECTRICAL_POWER_PANEL_LENGTH,		// ШКАФ ЭЛЕКТРОПИТАНИЯ КРАНА : Длина
	PTPAR_PPR_ELECTRICAL_POWER_PANEL_WIDTH,			// ШКАФ ЭЛЕКТРОПИТАНИЯ КРАНА : Ширина
	PTPAR_PPR_ACETYLINE_STORAGE_BOX_DIAMETER,		// ШКАФ ДЛЯ ХРАНЕНИЯ БАЛЛОНОВ С АЦЕТИЛЕНОМ : Диаметр
	PTPAR_PPR_OXYGEN_STORAGE_BOX_DIAMETER,			// ШКАФ ДЛЯ ХРАНЕНИЯ БАЛЛОНОВ С КИСЛОРОДОМ : Диаметр
	PTPAR_PPR_BREAKOUT_AXIS_DIAMETER,				// ЗНАК РАЗБИВОЧНЫХ ОСЕЙ : Диаметр
	PTPAR_PPR_FIRE_HYDRANT_DIAMETER,				// ПОЖАРНЫЙ ГИДРАНТ : Диаметр
	PTPAR_PPR_SIGNAL_MAN_PLACE_DIAMETER,			// МЕСТОНАХОЖДЕНИЕ СИГНАЛЬЩИКА : Диаметр
	PTPAR_PPR_CRANE_LIMIT_SIGN_SIZE,				// ЗНАК ПРЕДУПРЕЖДЕНИЯ ОБ ОГРАНИЧЕНИИ ЗОНЫ ДЕЙСТВИЯ КРАНА : Размер
	PTPAR_PPR_NO_LIFT_SIGN_DIAMETER,				// ЗНАК, ЗАПРЕЩАЮЩИЙ ПРОНОС ГРУЗА : Диаметр
	PTPAR_PPR_CRANE_WORK_SIGN_SIZE,					// ЗНАК, ПРЕДУПРЕЖДАЮЩИЙ О РАБОТЕ КРАНА, С ПОЯСНЯЮЩЕЙ НАДПИСЬЮ : Размер
	PTPAR_PPR_LIGHT_MAST_LENGTH,					// ПРОЖЕКТОРНАЯ МАЧТА : Длина
	PTPAR_PPR_LIGHT_MAST_WIDTH,						// ПРОЖЕКТОРНАЯ МАЧТА : Ширина
	PTPAR_PPR_LIGHT_MAST_OUTSIZE,					// ПРОЖЕКТОРНАЯ МАЧТА : Длина выступающей линии
	PTPAR_PPR_LIGHT_MAST_OUTANGLE,					// ПРОЖЕКТОРНАЯ МАЧТА : Угол выступающей линии
	PTPAR_PPR_LIGHT_STAND_DIAMETER,					// ОПОРА СО СВЕТИЛЬНИКОМ : Диаметр
	PTPAR_PPR_LIGHT_STAND_OUTSIZE,					// ОПОРА СО СВЕТИЛЬНИКОМ : Длина выступающей линии
	PTPAR_PPR_LIGHT_STAND_OUTANGLE,					// ОПОРА СО СВЕТИЛЬНИКОМ : Угол выступающей линии
	PTPAR_PPR_LIGHT_STRETCH_STAND_DIAMETER,			// ОПОРА С ОТТЯЖКОЙ И СВЕТИЛЬНИКОМ : Диаметр
	PTPAR_PPR_LIGHT_STRETCH_STAND_OUTSIZE,			// ОПОРА С ОТТЯЖКОЙ И СВЕТИЛЬНИКОМ : Длина выступающей линии
	PTPAR_PPR_LIGHT_STRETCH_STAND_OUTANGLE,			// ОПОРА С ОТТЯЖКОЙ И СВЕТИЛЬНИКОМ : Угол выступающей линии
	PTPAR_PPR_LIGHT_STRETCH_STAND_S_HEIGHT,			// ОПОРА С ОТТЯЖКОЙ И СВЕТИЛЬНИКОМ : Высота оттяжки
	PTPAR_PPR_LIGHT_STRETCH_STAND_S_WIDTH,			// ОПОРА С ОТТЯЖКОЙ И СВЕТИЛЬНИКОМ : Ширина оттяжки
	PTPAR_PPR_LIGHT_STRETCH_STAND_S_ANGLE,			// ОПОРА С ОТТЯЖКОЙ И СВЕТИЛЬНИКОМ : Угол оттяжки
	PTPAR_PPR_CRANE_STATION_TYPE,					// СТОЯНКА КРАНА : Тип стоянки
	PTPAR_PPR_SUMP_EXTERNAL_DIAMETER,				// ЗУМПФ (Отстойник) : Наружный диаметр
	PTPAR_PPR_TANK_SUMP_LENGTH,						// РЕЗЕРВУАР-ОТСТОЙНИК : Длина
	PTPAR_PPR_TANK_SUMP_WIDTH,						// РЕЗЕРВУАР-ОТСТОЙНИК : Ширина
	PTPAR_PPR_COVERED_CANOPY_LENGTH,				// КРЫТЫЙ НАВЕС : Длина
	PTPAR_PPR_COVERED_CANOPY_WIDTH,					// КРЫТЫЙ НАВЕС : Ширина
	PTPAR_PPR_GARBAGE_DUMP_DIAMETER,				// МУСОРОСБРОС : Диаметр
	PTPAR_PPR_DISMANTLING_OBJECT_CROSS_LENGTH,		// ОБЪЕКТ ДЕМОНТАЖА : Длина линий креста
	PTPAR_UNDEFINEDMAX
};

//----------------------------------------
struct IMcNativePointTypeMaker : public virtual IMcObject
{
public:
	IMCS_STD_METHOD_DEFINITION(IMcNativePointTypeMaker, IMcObject)

	// Инициализация
	virtual HRESULT Init(
		IMcGeometryBuilder *p2dGeometry,
		McsNativePointTypeEnum pointType,
		McsNativeLineTypeEnum linetypeParent = NLT_BYOBJECT,
		double rScale = 1.0,
		double rDScale = 1.0, 
		int nGSMarkerStart = 4096) = 0;

	// Черчение
	virtual bool Draw(const mcsPoint& ptPos, const mcsVector& vDir, const mcsVector& vOrthoDir, mcsPolylineArray* pArrCutContours = NULL) = 0;

	// Параметры для типа точки
	virtual bool GetNPParameters(McNativeParamArray& arrParams) const = 0;
	virtual bool SetNPParameters(const McNativeParamArray& arrParams) = 0;

	// Вспомогательная информация о типах точек
	virtual McsString GetNPName(McsNativePointTypeEnum pointType) const = 0;
	virtual COLORREF  GetNPColor(McsNativePointTypeEnum pointType) const = 0;
};

IMCS_DECL_INTERFACE(IMcPointEntity,	"799D130C-60B5-4E6D-A123-3BBFF8732494")

//----------------------------------------
// Интерфейс для определения точечного объекта
// Пример использования - маркировка коннекторов
//----------------------------------------
struct IMcPointEntity : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcPointEntity);
	IMCS_QI_METHOD_DEFINITION(IMcPointEntity, IMcObject);

	virtual HRESULT GetEntityPoint(mcsPoint& pnt) const = 0;
};

//----------------------------------------
#define AS_READONLY						0x00000000
#define AS_SYSTEM						0x00000001
#define AS_CHANGEABLE					0x00000002
#define AS_CHECKBOX						0x00000004

#define ATTR_STYLE_READONLY				_T("AS_READONLY")
#define ATTR_STYLE_SYSTEM				_T("AS_SYSTEM")
#define ATTR_STYLE_CHANGEABLE			_T("AS_CHANGEABLE")
#define ATTR_STYLE_CHECKBOX				_T("AS_CHECKBOX")

#define ATTR_SID_GROUP_DB_UID			_T("AUidG")
#define ATTR_SID_RESOURCE_DB_UID		_T("AUidR")
#define ATTR_SID_OBJ_NAME				_T("AName")			// Наименование знака
#define ATTR_SID_OBJ_SIZE				_T("ASize")			// Размер знака
#define ATTR_SID_OBJ_STANDARD			_T("AStandard")		// ГОСТ
#define ATTR_SID_OBJ_STD_LINK			_T("AStdLink")		// normacs URL
#define ATTR_SID_OBJ_STD_NUMBER			_T("AStdNumber")	// Номер знака
#define ATTR_SID_OBJ_PLAN_NUMBER		_T("APlanNumber")	// Номер на плане
#define ATTR_SID_OBJ_TYPE				_T("AType")			// Тип знака (например, "Запрещающие знаки")
#define ATTR_SID_OBJ_DESIGN				_T("ADesign")		// Исполнение (на данный момент - слово "Знак")
#define ATTR_SID_OBJ_TWO_STANDS			_T("ALegs")			// Флаг для знаков на двух опорах ("1")
#define ATTR_SID_OBJ_STAND_HEIGHT		_T("ALegsHeight")	// Высота опоры

//----------------------------------------
#define PARAM_PO_ENABLED_ATTACH_TO_LO	_T("EnabledAttachToLO")

//----------------------------------------
struct McCustomAttribute
{
	McsString sSysName;
	McsString sUserName;
	McsString sValue;
	DWORD     dwStyle;
	
	McCustomAttribute()
	{
		dwStyle = 0;
	}
	McCustomAttribute(const McCustomAttribute& attr)
	{
		*this = attr;
	}
	McCustomAttribute& operator = (const McCustomAttribute& attr)
	{
		if (this == &attr)
			return *this;
		sSysName  = attr.sSysName;
		sUserName = attr.sUserName;
		sValue    = attr.sValue;
		dwStyle   = attr.dwStyle;
		return *this;
	}
	bool operator == (const McCustomAttribute& attr) const
	{
		return sSysName == attr.sSysName;
	}
	bool operator != (const McCustomAttribute& attr) const
	{
		return sSysName != attr.sSysName;
	}
	bool operator > (const McCustomAttribute& attr) const
	{
		return sSysName > attr.sSysName;
	}
	bool operator < (const McCustomAttribute& attr) const
	{
		return sSysName < attr.sSysName;
	}
};
typedef McsArray<McCustomAttribute, const McCustomAttribute&> McCustomAttributeArray;

//----------------------------------------
struct McCustomDesign
{
	McsString     sDesignName;
	CxImage       image;
	mcsByteArray  arrRawParametricStream;
	McCustomAttributeArray arrAttributes;
	
	McCustomDesign()
	{
	}
	McCustomDesign(const McCustomDesign& design)
	{
		*this = design;
	}
	~McCustomDesign()
	{
	}
	
	McCustomDesign& operator = (const McCustomDesign& design)
	{
		if (this == &design)
			return *this;

		sDesignName   = design.sDesignName;
		image         = design.image;
		arrAttributes = design.arrAttributes;
		arrRawParametricStream = design.arrRawParametricStream;
		return *this;
	}
	bool operator == (const McCustomDesign& design) const
	{
		return sDesignName == design.sDesignName;
	}
	bool operator > (const McCustomDesign& design) const
	{
		return sDesignName > design.sDesignName;
	}
	bool operator < (const McCustomDesign& design) const
	{
		return sDesignName < design.sDesignName;
	}
};
typedef McsArray<McCustomDesign, const McCustomDesign&> McCustomDesignArray;

//----------------------------------------
struct McCustomSignData
{
	McsString sSignName;
	McCustomDesignArray arrDesigns;
	
	McCustomSignData()
	{
	}
	McCustomSignData(const McCustomSignData& data)
	{
		*this = data;
	}
	~McCustomSignData()
	{
	}
	
	McCustomSignData& operator = (const McCustomSignData& data)
	{
		if (this == &data)
			return *this;

		sSignName  = data.sSignName;
		arrDesigns = data.arrDesigns;
		return *this;
	}
	bool operator == (const McCustomSignData& data) const
	{
		return sSignName == data.sSignName;
	}
	bool operator > (const McCustomSignData& data) const
	{
		return sSignName > data.sSignName;
	}
	bool operator < (const McCustomSignData& data) const
	{
		return sSignName < data.sSignName;
	}
};
typedef McsArray<McCustomSignData, const McCustomSignData&> McCustomSignDataArray;

//----------------------------------------
struct McCustomSignGroup
{
	McsString sGroupName;
	McCustomSignDataArray arrSignData;
	
	McCustomSignGroup()
	{
	}
	McCustomSignGroup(const McCustomSignGroup& group)
	{
		*this = group;
	}
	~McCustomSignGroup()
	{
	}
	
	McCustomSignGroup& operator = (const McCustomSignGroup& group)
	{
		if (this == &group)
			return *this;

		sGroupName  = group.sGroupName;
		arrSignData = group.arrSignData;
		return *this;
	}
	bool operator == (const McCustomSignGroup& group) const
	{
		return sGroupName == group.sGroupName;
	}
	bool operator > (const McCustomSignGroup& group) const
	{
		return sGroupName > group.sGroupName;
	}
	bool operator < (const McCustomSignGroup& group) const
	{
		return sGroupName < group.sGroupName;
	}
};
typedef McsArray<McCustomSignGroup, const McCustomSignGroup&> McCustomSignGroupArray;

//----------------------------------------
struct McCustomSignAggregation
{
	McsString sAggregationName;
	McCustomSignGroupArray arrSignGroup;
	
	McCustomSignAggregation()
	{
	}
	McCustomSignAggregation(const McCustomSignAggregation& aggr)
	{
		*this = aggr;
	}
	~McCustomSignAggregation()
	{
	}
	
	McCustomSignAggregation& operator = (const McCustomSignAggregation& aggr)
	{
		if (this == &aggr)
			return *this;

		sAggregationName = aggr.sAggregationName;
		arrSignGroup     = aggr.arrSignGroup;
		return *this;
	}
	bool operator == (const McCustomSignAggregation& aggr) const
	{
		return sAggregationName == aggr.sAggregationName;
	}
	bool operator > (const McCustomSignAggregation& aggr) const
	{
		return sAggregationName > aggr.sAggregationName;
	}
	bool operator < (const McCustomSignAggregation& aggr) const
	{
		return sAggregationName < aggr.sAggregationName;
	}
};
typedef McsArray<McCustomSignAggregation, const McCustomSignAggregation&> McCustomSignAggregationArray;

//----------------------------------------
// Менеджер доступа к пользовательской графике в БД
//----------------------------------------
struct IMcCustomSignDbManager : public IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcCustomSignDbManager)
	IMCS_STD_METHOD_DEFINITION(IMcCustomSignDbManager, IMcObject)

	virtual long GetRoadSignsFolderId() = 0;
	virtual long GetSafetySignsFolderId() = 0;
	
	virtual bool InitSignAggregation(IN long lFolderId, OUT McCustomSignAggregation& aggr, OUT bool& bLoadFromCache) = 0;

	virtual bool LocalizeAttributes(MCSUID uidResElem, McCustomAttributeArray& arrAttributes) = 0;
};

//----------------------------------------
// Ассистент базового "точечного" объекта
//----------------------------------------
struct IMcBasePointObjectAssistant : public IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcBasePointObjectAssistant)
	IMCS_STD_METHOD_DEFINITION(IMcBasePointObjectAssistant, IMcObject)

	// Assist PointObject
	//----------------------------------------
	virtual HRESULT SetPointObject(IMcCdEntity* pAssistedPointObject) = 0;
	virtual IMcCdEntityPtr GetPointObject() const = 0;

	// IMcEntity redirected methods
	//----------------------------------------
	virtual HRESULT onDraw(	IMcGeometryBuilder *pG, 
							const mcsByteArray* pPreferredArrRawParametricStream = NULL,
							const McCustomAttributeArray* pPreferredArrAttributes = NULL) = 0;
	virtual HRESULT onTransform(IN const mcsMatrix& tfm) = 0;
	virtual HRESULT getTfm(OUT mcsMatrix& tfm) const = 0;
	virtual HRESULT getBoundingBox(OUT mcsBoundBlock &box) const = 0;
	virtual HRESULT onGetGripPoints(mcsPoint3dArray& gripPoints, bool bStretch) const = 0;
	virtual HRESULT onMoveGripPointsAt(const mcsIntArray& indices, const mcsVector3d& offset, bool bStretch) = 0;
	virtual HRESULT onGetGripPoints(McGripDataPtrArray& grips, double rViewUnitSize, int iGripSize, const mcsVector& vecViewDir, int iFlags) const = 0;
	virtual HRESULT onMoveGripPointsAt(const McGripDataPtrArray& grips, const mcsVector& offset, int iFlags) = 0;
	virtual HRESULT onEdit(IN const mcsPoint3d& pnt, long lFlag = 0) = 0;
	virtual HRESULT onWrite(OUT IMcsStream* pStream) const = 0;
	virtual HRESULT onRead(IN IMcsStream* pStream) = 0;
	virtual HRESULT onReactor(IMcDbObject *pObj, mcReactorsType action) = 0;
	virtual HRESULT onEvent(IMcEventType event, mcsExValueArray *pAdditionalParameters = NULL) = 0;
	virtual HRESULT onErase() = 0;
	virtual HRESULT placeObject(long lInsertType = kMcPlace_Normal, mcsExValueArray *pAdditionalParameters = NULL) = 0;
 	virtual HRESULT getProperties(mcsStringArray& props) = 0;
	virtual HRESULT getProperty(const McsString& stName, MCSVariant& data) = 0;
	virtual HRESULT setProperty(const McsString& stName, const MCSVariant& data) = 0;
	virtual HRESULT getPropertyInfo(const McsString& stName, OUT McPropertyInfo& info) = 0;

	// PointType
	//----------------------------------------
	virtual HRESULT SetNativePointType(McsNativePointTypeEnum pointType) = 0;
	virtual McsNativePointTypeEnum GetNativePointType() const = 0;
	virtual McsString GetNativePTName(McsNativePointTypeEnum pointType) const = 0;
	
	// Parameters of current PointType
	//----------------------------------------
	virtual HRESULT GetNPParameters(McNativeParamArray& arrParams) const = 0;
	virtual HRESULT SetNPParameters(const McNativeParamArray& arrParams) = 0;
	virtual PointTypeParamEnum GetParamType(LPCTSTR pszSystemName) const = 0;
	virtual McsString GetParamSystemName(PointTypeParamEnum typeParam) const = 0;
	virtual McsString GetParamLocalName(PointTypeParamEnum typeParam) const = 0;

	// Attach\Detach to LongObject
	//----------------------------------------
	virtual HRESULT AttachToLongObject(const mcsWorkID& idLongObj) = 0;
	virtual HRESULT DetachFromLongObject() = 0;
	virtual mcsWorkID GetLongObjectId() const = 0;

	// Cutting chunk from Long object
	//----------------------------------------
	virtual double GetCutLength() const = 0;

	// Custom graphics
	//----------------------------------------
	virtual HRESULT SetCustomParametricData(const mcsByteArray& arrRawParametricStream) = 0;
	virtual HRESULT GetCustomParametricData(mcsByteArray& arrRawParametricStream) const = 0;
	
	// Custom attributes
	//----------------------------------------
	virtual HRESULT SetCustomArrayAttributes(const McCustomAttributeArray& arrAttributes) = 0;
	virtual HRESULT GetCustomArrayAttributes(McCustomAttributeArray& arrAttributes) const = 0;
	virtual HRESULT SetCustomAttribute(LPCTSTR pszAttrSysName, const McCustomAttribute& attr) = 0;
	virtual HRESULT GetCustomAttribute(LPCTSTR pszAttrSysName, McCustomAttribute& attr) const = 0;
	
	// Built-In CustomSignDbManager
	//----------------------------------------
	virtual IMcCustomSignDbManagerPtr GetBuiltInSignDbMgr() const = 0;
};

//----------------------------------------
// Базовый "точечный" объект
//----------------------------------------
struct IMcNativePointObject : public virtual IMcCdEntity
{
public:
	IMCS_ENT_METHOD_DEFINITION(IMcNativePointObject, IMcCdEntity, IMcDbEntity);

	//----------------------------------------
	IMcNativePointObject() : IMcCdEntity()
	{
		IMCS_REGISTER_THIS_IID_4KINDOF;

		m__lSystemFlag = kMcCoveringEnt;

		m_pNPAssist = gpMcObjManager->createObject(IID_IMcBasePointObjectAssistant);
		if (m_pNPAssist)
			m_pNPAssist->SetPointObject(this);
	}
	
	//----------------------------------------
	virtual ~IMcNativePointObject()
	{
		m_pNPAssist = UNKNULL;
	}

#ifndef NOPASSIST
#define NOPASSIST(retval) if (!m_pNPAssist) return retval;
#endif
	//----------------------------------------
	// IMcEntity methods
	virtual HRESULT onDraw(IMcGeometryBuilder *pG) override
	{
		NOPASSIST(E_NOTIMPL)
		m_2dOriginalCache.RemoveAll();
		clearContours();
		pG->setContainer(&m_2dOriginalCache);
		return m_pNPAssist->onDraw(pG);
	}
	//----------------------------------------
	virtual HRESULT onTransform(IN const mcsMatrix& tfm) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onTransform(tfm);
	}
	//----------------------------------------
	virtual HRESULT getTfm(mcsMatrix& tfm) const override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->getTfm(tfm);
	}
	//----------------------------------------
	virtual HRESULT getBoundingBoxOCS(OUT mcsBoundBlock &box) const override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->getBoundingBox(box);
	}
	//----------------------------------------
	virtual HRESULT onGetGripPoints(mcsPoint3dArray& gripPoints, bool bStretch) const override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onGetGripPoints(gripPoints, bStretch);
	}
	//----------------------------------------
	virtual HRESULT onMoveGripPointsAt(const mcsIntArray& indices, const mcsVector3d& offset, bool bStretch) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onMoveGripPointsAt(indices, offset, bStretch);
	}
	//----------------------------------------
	virtual HRESULT onGetGripPoints(McGripDataPtrArray& grips, double rViewUnitSize, int iGripSize, const mcsVector& vecViewDir, int iFlags) const override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onGetGripPoints(grips, rViewUnitSize, iGripSize, vecViewDir, iFlags);
	}
	//----------------------------------------
	virtual HRESULT onMoveGripPointsAt(const McGripDataPtrArray& grips, const mcsVector& offset, int iFlags) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onMoveGripPointsAt(grips, offset, iFlags);
	}
	//----------------------------------------
	virtual HRESULT onEdit(IN const mcsPoint3d& pnt, long lFlag = 0) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onEdit(pnt, lFlag);
	}
	//----------------------------------------
	virtual HRESULT onWrite(OUT IMcsStream* pStream) const override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onWrite(pStream);
	}
	//----------------------------------------
	virtual HRESULT onRead(IN IMcsStream* pStream) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onRead(pStream);
	}
	//----------------------------------------
	virtual HRESULT onReactor(IMcDbObject *pObj, mcReactorsType action) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onReactor(pObj, action);
	}
	//----------------------------------------
	virtual HRESULT onEvent(IMcEventType event, mcsExValueArray *pAdditionalParameters = NULL) override
	{
		if (kMcEvent_Custom == event && NULL != pAdditionalParameters)
		{
			// Process this event for parameter <PARAM_PO_ENABLED_ATTACH_TO_LO> for Enable\Disable AttachToLongObject with income linetype
			int idxLinetype = -1;
			if (pAdditionalParameters->findByName(idxLinetype, PARAM_PO_ENABLED_ATTACH_TO_LO))
			{
				const exValue& xval = (*pAdditionalParameters)[idxLinetype];
				McsNativeLineTypeEnum lineTypeLongObject = (McsNativeLineTypeEnum)(int)xval.val.m_num;
				return S_OK;
			}
		}
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onEvent(event, pAdditionalParameters);
	}
	//----------------------------------------
	virtual HRESULT onErase() override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->onErase();
	}
	//----------------------------------------
	virtual HRESULT placeObject(long lInsertType = kMcPlace_Normal, mcsExValueArray *pAdditionalParameters = NULL) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->placeObject(lInsertType, pAdditionalParameters);
	}
	//----------------------------------------
	virtual HRESULT getProperties(mcsStringArray& props) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->getProperties(props);
	}
	//----------------------------------------
	virtual HRESULT getProperty(const McsString& name, MCSVariant& data) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->getProperty(name, data);
	}
	//----------------------------------------
	virtual HRESULT setProperty(const McsString& name, const MCSVariant& data) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->setProperty(name, data);
	}
	//----------------------------------------
	virtual HRESULT getPropertyInfo(const McsString& systemName, OUT McPropertyInfo& info) override
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->getPropertyInfo(systemName, info);
	}

	// Assistant
	//----------------------------------------
	virtual IMcBasePointObjectAssistantPtr GetAssistant() const { return m_pNPAssist; }

	// PointType
	//----------------------------------------
	virtual HRESULT SetNativePointType(McsNativePointTypeEnum pointType)
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->SetNativePointType(pointType);
	}
	//----------------------------------------
	virtual McsNativePointTypeEnum GetNativePointType() const
	{
		NOPASSIST(NPT_SIMPLE_POINT)
		return m_pNPAssist->GetNativePointType();
	}
	//----------------------------------------
	virtual McsString GetNativePTName(McsNativePointTypeEnum pointType) const
	{
		NOPASSIST(_T(""))
		return m_pNPAssist->GetNativePTName(pointType);
	}
	
	// Custom parameters of current PointType
	//----------------------------------------
	virtual HRESULT GetNPParameters(McNativeParamArray& arrParams) const
	{
		NOPASSIST(asLeft)
		return m_pNPAssist->GetNPParameters(arrParams);
	}
	//----------------------------------------
	virtual HRESULT SetNPParameters(const McNativeParamArray& arrParams)
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->SetNPParameters(arrParams);
	}
	//----------------------------------------
	virtual PointTypeParamEnum GetParamType(LPCTSTR pszSystemName) const
	{
		NOPASSIST(PTPAR_UNDEFINED)
		return m_pNPAssist->GetParamType(pszSystemName);
	}
	//----------------------------------------
	virtual McsString GetParamSystemName(PointTypeParamEnum typeParam) const
	{
		NOPASSIST(_T(""))
		return m_pNPAssist->GetParamSystemName(typeParam);
	}
	//----------------------------------------
	virtual McsString GetParamLocalName(PointTypeParamEnum typeParam) const
	{
		NOPASSIST(_T(""))
		return m_pNPAssist->GetParamLocalName(typeParam);
	}

	// Attach\Detach to LongObject
	//----------------------------------------
	virtual HRESULT AttachToLongObject(const mcsWorkID& idLongObj)
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->AttachToLongObject(idLongObj);
	}
	//----------------------------------------
	virtual HRESULT DetachFromLongObject()
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->DetachFromLongObject();
	}
	//----------------------------------------
	virtual mcsWorkID GetLongObjectId() const
	{
		NOPASSIST(mcsWorkID())
		return m_pNPAssist->GetLongObjectId();
	}

	// Cutting chunk from Long object
	//----------------------------------------
	virtual double GetCutLength() const
	{
		NOPASSIST(0.0)
		return m_pNPAssist->GetCutLength();
	}

	// Custom graphics
	//----------------------------------------
	virtual HRESULT SetCustomParametricData(const mcsByteArray& arrRawParametricStream)
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->SetCustomParametricData(arrRawParametricStream);
	}
	//----------------------------------------
	virtual HRESULT GetCustomParametricData(mcsByteArray& arrRawParametricStream) const
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->GetCustomParametricData(arrRawParametricStream);
	}
	
	// Custom attributes
	//----------------------------------------
	virtual HRESULT SetCustomArrayAttributes(const McCustomAttributeArray& arrAttributes)
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->SetCustomArrayAttributes(arrAttributes);
	}
	//----------------------------------------
	virtual HRESULT GetCustomArrayAttributes(McCustomAttributeArray& arrAttributes) const
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->GetCustomArrayAttributes(arrAttributes);
	}
	//----------------------------------------
	virtual HRESULT SetCustomAttribute(LPCTSTR pszAttrSysName, const McCustomAttribute& attr)
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->SetCustomAttribute(pszAttrSysName, attr);
	}
	//----------------------------------------
	virtual HRESULT GetCustomAttribute(LPCTSTR pszAttrSysName, McCustomAttribute& attr) const
	{
		NOPASSIST(E_NOTIMPL)
		return m_pNPAssist->GetCustomAttribute(pszAttrSysName, attr);
	}

protected:
	IMcBasePointObjectAssistantPtr m_pNPAssist;
};

//----------------------------------------
// Список состояний для параметра PTPAR_PPR_CRANE_STATION_TYPE
//----------------------------------------
enum
{
	PPR_CRANE_BOUND_WORK_STATION = 0,
	PPR_CRANE_WORK_STATION,
	PPR_CRANE_IDLE_STATION,
};

//----------------------------------------
