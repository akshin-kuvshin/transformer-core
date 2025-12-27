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
#include "IMcDocuments.h"
#include "IMcAreaEntity.h"

IMCS_DECL_INTERFACE(IMcArrowsExtension,       "00000001-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcBaseLeader,            "00000007-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityPolyLeader,      "00000008-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityNote,            "0000000A-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityNoteComb,        "0000000D-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityNoteChain,       "00000010-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityNoteSecant,      "00000011-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityNoteKnot,        "00000014-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityNotePosition,    "00000015-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityLinearMark,      "00000016-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityNoteMultiLayer,  "00000017-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(ISpdsAxis,                "00000009-0008-AAAA-AAAA-050B00000000") //интерфейс оси (не entity)
IMCS_DECL_INTERFACE(ISpdsEntityCLine,         "00000001-0008-AAAA-AAAA-050B00000000") //отдельная ось (entity)
IMCS_DECL_INTERFACE(ISpdsEntityCLOrient,      "00000003-0008-AAAA-AAAA-050B00000000") //указатель ориентации
IMCS_DECL_INTERFACE(ISpdsGrid,                "00000006-0008-AAAA-AAAA-050B00000000") //абстрактный (предок)
IMCS_DECL_INTERFACE(ISpdsRectGrid,            "00000007-0008-AAAA-AAAA-050B00000000") //ортогональный массив
IMCS_DECL_INTERFACE(ISpdsPolarGrid,           "00000008-0008-AAAA-AAAA-050B00000000") //полярный массив
IMCS_DECL_INTERFACE(IMcEntityVS,              "00000002-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityView,            "00000004-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityEView,           "00000019-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntitySection,         "00000005-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntityVSLegend,        "00000006-0004-AAAA-AAAA-050B00000000")

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Расширение для работы со стрелочками объектов
//---------------------------------------------------------------------------
struct IMcArrowsExtension : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcArrowsExtension);
	IMCS_QI_METHOD_DEFINITION(IMcArrowsExtension, IMcObject);

	virtual HRESULT GetArrowByPoint(const mcsPoint& pnt, MCS_ARROW& arrow, int& idArrow, double rApperture) = 0;
	virtual HRESULT GetAllowedArrows(MCS_ARROW*& pArrows, int& iCount) = 0;
	virtual HRESULT SetArrow(MCS_ARROW arrow, int idArrow) = 0;

	virtual MCS_ARROW GetArrow()
	{
		return MCS_ArrUnknown;
	}
	virtual HRESULT SetArrow(MCS_ARROW arrow)
	{
		return E_NOTIMPL;
	}
	// Идентификаторы параметров размеров стрелок. Количество и порядок должны совпадать с результатом GetAllowedArrows.
	virtual HRESULT GetAllowedArrowsParams(int*& pSize, int*& pWidth, int& iCount)
	{
		return E_NOTIMPL;
	}

	// Проверяет стрелку на соответствие списку GetAllowedArrows
	MECHCTL_API static bool CheckArrow(IMcArrowsExtension* pAE, MCS_ARROW arrow);

	MECHCTL_API static HRESULT getAEProperties(IMcArrowsExtension* pAE, mcsStringArray& astNames);
	MECHCTL_API static HRESULT getAEProperty(IMcArrowsExtension* pAE, const McsString& stName, MCSVariant& data);
	MECHCTL_API static HRESULT setAEProperty(IMcArrowsExtension* pAE, const McsString& stName, const MCSVariant& data);
	MECHCTL_API static HRESULT getAEPropertyInfo(IMcArrowsExtension* pAE, const McsString& stName, McPropertyInfo& info);
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcBaseLeader - базовый интерфейс для "ПолиЛидера"
//---------------------------------------------------------------------------

//аналогичный енум описан в src/OleServer/OleServer.idl
//называется SegmentIndex

// Индекс корневого сегмента
#define MCBL_ROOT -1
// Ближайший сегмент
#define MCBL_NEAREST -2
// Ничего
#define MCBL_NONE -3

struct McTBLSegment
{
	mcsPoint pntStart;
	mcsPoint pntEnd;
	MCS_ARROW eArrow;
	double rArrSize;
	double rArrWidth;
	double rParam;
	int iParent;
	mcsIntArray aiChilds;
	McGeometryParam companion;

	McTBLSegment()
	{
		iParent = MCBL_ROOT;
		eArrow = MCS_ArrNone;
		rArrSize = rArrWidth = rParam = 0.0;
	};
};
typedef McsArray<McTBLSegment, McTBLSegment&> McTBLSegmentArray;

//---------------------------------------------------------------------------
struct IMcBaseLeader : public IMcArrowsExtension
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcBaseLeader);
	IMCS_QI_METHOD_DEFINITION(IMcBaseLeader, IMcArrowsExtension);

	// Возвращает в stError текст сообщения об ошибке iError
	virtual HRESULT getErrorMessage(McsString& stError, HRESULT hRes) const = 0;

	// Возвращает геометрию для подсветки дерева, начиная с сегмента iFrom с параметром rParam
	virtual HRESULT highlight(IMcGeometryBuilder *p2dGeometry, int iFrom, double rParam) const = 0;

	// Добавляет к сегменту iToSegment дерево pBL. При iToSegment == MCBL_NEAREST - дерево pBL
	// добавляется к сегменту, ближайшему к корню pBL
	virtual HRESULT addBaseLeader(const IMcBaseLeader* pBL, int iToSegment = MCBL_NEAREST) = 0;
	// Добавляет к корневому сегменту pBL дерево начиная с iFrom
	virtual HRESULT getBaseLeader(IMcBaseLeader* pBL, int iFrom) const = 0;

	// Обновляет дочерние сегменты iFrom в соответствии с изменениями в его геометрии
	// Если bInclude == true, то выполняется поиск родителя и обновление сегмента iFrom
	virtual HRESULT update(int iFrom = MCBL_ROOT, bool bInclude = true) = 0;

	// В pntNearest возвращает точку, лежащую на сегменте и ближайшую к pntBase
	virtual HRESULT getNearestPoint(mcsPoint& pntNearest, const mcsPoint& pntBase, int iSegment) const = 0;
	virtual HRESULT getNearestPointOCS(mcsPoint& pntNearest, const mcsPoint& pntBase, int iSegment) const = 0;
	// Возвращает индекс сегмента ближайшего к точке pnt,
	// исключая дерево сегментов, начиная с iExcludeFrom
	virtual int getNearestSegment(const mcsPoint& pnt, int iExcludeFrom = MCBL_NONE) const = 0;
	virtual int getNearestSegmentOCS(const mcsPoint& pnt, int iExcludeFrom = MCBL_NONE) const = 0;

	// Эти функции позволяют однозначно определить положение точки по double
	// параметру и наоборот, вне зависимости от текущих параметров сегмента
	// Параметр изменяется от 0 (pntStart) до 1 (pntEnd) для стандартных сегментов
	virtual HRESULT getSegParamAtPoint(double& rParam, const mcsPoint& pnt, int iSegment) const = 0;
	virtual HRESULT getSegParamAtPointOCS(double& rParam, const mcsPoint& pnt, int iSegment) const = 0;
	virtual HRESULT getSegPointAtParam(mcsPoint& pnt, double rParam, int iSegment) const = 0;
	virtual HRESULT getSegPointAtParamOCS(mcsPoint& pnt, double rParam, int iSegment) const = 0;

	// Возвращает количество сегментов (без корневого)
	virtual int getNumSegments() const = 0;
	// В aiSegs возвращает индексы сегментов, к началу которых не прицеплено других сегментов
	// Т.е. сегменты, на которые обычно нужно/можно ставить стрелки
	// Возвращает количество найденных сегментов
	virtual int getFreeSegments(mcsIntArray& aiSegs) const = 0;
	// Устанавливает стрелку на все свободные сегменты, и убирает с остальных
	virtual void setArrow(MCS_ARROW arrow, double size, double width = 0) = 0;
	// Добавляет в aiSegmentTree дерево сегментов, начиная с iStartSegment
	virtual HRESULT getSegmentTree(mcsIntArray& aiSegmentTree, int iStartSegment) const = 0;

	// Возвращает в Segment сегмент iSegment
	virtual HRESULT getSegment(McTBLSegment& Segment, int iSegment) const = 0;
	virtual HRESULT getSegmentOCS(McTBLSegment& Segment, int iSegment) const = 0;
	// Записывает Segment в сегмент iSegment
	// ВСЕ ДАННЫЕ В СТРУКТУРЕ ДОЛЖНЫ БЫТЬ КОРРЕКТНЫ
	virtual HRESULT setSegment(const McTBLSegment& Segment, int iSegment) = 0;
	virtual HRESULT setSegmentOCS(const McTBLSegment& Segment, int iSegment) = 0;
	// Добавляет сегмент, ВСЕ ДАННЫЕ В СТРУКТУРЕ ДОЛЖНЫ БЫТЬ КОРРЕКТНЫ
	// Использовать нужно ОЧЕНЬ осторожно, лучше пользоваться вторым вариантом
	// Сегмент всегда добавляется в конец списка
	virtual HRESULT addSegment(const McTBLSegment& Segment) = 0;
	virtual HRESULT addSegmentOCS(const McTBLSegment& Segment) = 0;
	virtual HRESULT addSegment(const mcsPoint& pntStart,
		const mcsPoint& pntEnd,
		int iToSegment,
		MCS_ARROW eArrow = MCS_ArrNone,
		double rArrSize = 0.0,
		double rArrWidth = 0.0,
		const McGeometryParam* pCompanion = NULL) = 0;
	virtual HRESULT addSegmentOCS(const mcsPoint& pntStart,
		const mcsPoint& pntEnd,
		int iToSegment,
		MCS_ARROW eArrow = MCS_ArrNone,
		double rArrSize = 0.0,
		double rArrWidth = 0.0,
		const McGeometryParam* pCompanion = NULL) = 0;
	// Вставляет сегмент нулевой длинны между iBefore и его родительским сегментом
	// Сегмент добавляется в конец списка
	virtual HRESULT insertSegment(int iBefore,
		MCS_ARROW eArrow = MCS_ArrNone,
		double rArrSize = 0.0,
		double rArrWidth = 0.0,
		const McGeometryParam* pCompanion = NULL) = 0;

	// Удаляет из дерева сегмент iSegment
	// Все дочерние сегменты iSegment перецепляются к его родителю
	virtual HRESULT delSegment(int iSegment) = 0;
	// Удаляет дерево, начиная с сегмента iStartSegment
	virtual HRESULT delSegmentTree(int iStartSegment) = 0;

	// Следующие функции записывают/читают данные из сегмента iSegment
	virtual HRESULT setSegStart(const mcsPoint& pntStart, int iSegment) = 0;
	virtual HRESULT setSegStartOCS(const mcsPoint& pntStart, int iSegment) = 0;
	virtual HRESULT setSegEnd(const mcsPoint& pntEnd, int iSegment) = 0;
	virtual HRESULT setSegEndOCS(const mcsPoint& pntEnd, int iSegment) = 0;
	virtual HRESULT setSegArrow(MCS_ARROW eArrow, int iSegment) = 0;
	virtual HRESULT setSegArrSize(double rArrSize, int iSegment) = 0;
	virtual HRESULT setSegArrWidth(double rArrWidth, int iSegment) = 0;
	virtual HRESULT setSegParent(int iParent, int iSegment) = 0;
	virtual HRESULT setSegParam(double rParam, int iSegment) = 0;
	virtual HRESULT setSegCompanion(const McGeometryParam& companion, int iSegment) = 0;
	virtual HRESULT delSegCompanion(int iSegment) = 0;
	virtual HRESULT setSegChilds(mcsIntArray& aiChilds, int iSegment) = 0;
	virtual HRESULT addSegChild(int iChild, int iSegment) = 0;
	virtual HRESULT delSegChild(int iChild, int iSegment) = 0;

	virtual mcsPoint  getSegStart(int iSegment) const = 0;
	virtual mcsPoint  getSegStartOCS(int iSegment) const = 0;
	virtual mcsPoint  getSegEnd(int iSegment) const = 0;
	virtual mcsPoint  getSegEndOCS(int iSegment) const = 0;
	virtual MCS_ARROW getSegArrow(int iSegment) const = 0;
	virtual double    getSegArrSize(int iSegment) const = 0;
	virtual double    getSegArrWidth(int iSegment) const = 0;
	virtual int       getSegParent(int iSegment) const = 0;
	virtual double    getSegParam(int iSegment) const = 0;
	virtual McGeometryParam getSegCompanion(int iSegment) const = 0;
	virtual int       getSegChilds(mcsIntArray& aiChilds, int iSegment) const = 0;
};

MECHCTL_API double McGetDefaultLeaderArrowSize(IMcEntity* pEnt, MCS_ARROW arrow, MCS_STANDARD standard);
MECHCTL_API double McGetDefaultLeaderArrowWidth(IMcEntity* pEnt, MCS_ARROW arrow, MCS_STANDARD standard);

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Полилидер
//---------------------------------------------------------------------------
struct IMcEntityPolyLeader : public virtual IMcBaseLeader, public IMcEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2(IMcEntityPolyLeader, IID_DesignElement);
	IMCS_ENT_METHOD_DEFINITION4(IMcEntityPolyLeader, IMcEntity, IMcDbEntity, IMcBaseLeader);

	virtual mcsPoint getRoot() const = 0;
	virtual void setRoot(const mcsPoint& pnt) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Универсальная выноска
//---------------------------------------------------------------------------
// Элемент выноски (также используется в выноске для многослойных конструкций)
struct McTNoteUnit
{
	McsString st;                 // Текст
	McsHorizTextAlignEnum eAlign; // Выравнивание текста

	McTNoteUnit()
		{ eAlign = kTextHorizAlign_Left; }
	McTNoteUnit(LPCTSTR _st, McsHorizTextAlignEnum _eAlign)
	{
		if(_st)
			st = _st;
		eAlign = _eAlign;
	}
};
class McTNoteUnitArray : public McsArray<McTNoteUnit, const McTNoteUnit&>
{
public:
	bool getAlign(McsHorizTextAlignEnum& align) const
	{
		if(m_nSize == 0)
			return false;
		for(int i = 1; i < m_nSize; i++)
		{
			if(m_pData[0].eAlign != m_pData[i].eAlign)
				return false;
		}
		align = m_pData[0].eAlign;
		return true;
	}
	void setAlign(McsHorizTextAlignEnum align)
	{
		for(int i = 1; i < m_nSize; i++)
			m_pData[i].eAlign = align;
	}
};

//---------------------------------------------------------------------------
struct IMcEntityNote : public virtual IMcBaseLeader, public IMcCdEntity, public IMcWizSymbol
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2(IMcEntityNote, IID_DesignElement);
	IMCS_ENT_METHOD_DEFINITION5(IMcEntityNote, IMcCdEntity, IMcDbEntity, IMcBaseLeader, IMcWizSymbol);

	enum Type
	{
		kSimple = 0,
		kCorner = 1,
		kSurface = 2,
		kDim = 3,
		kOther = 4,
	};//аналогичный енум описан в src/OleServer/OleServer.idl, называется NOTE_TYPE.

	virtual mcsPoint  getOrigin() const = 0;
	virtual double    getDir() const = 0;
	virtual MCS_ARROW getArrow() const = 0;
	virtual Type      getType() const = 0;
	virtual bool      isDulling() const = 0;
	virtual const McTNoteUnitArray& getUnits() const = 0;
	virtual double    getTextSize() const = 0;
	virtual McsString getTextStyle() const = 0;
	virtual bool      getMultiline() const = 0;
	virtual double    getRackLength() const = 0;
	virtual double    getTextXScale() const = 0;
	virtual bool      getFrame() const = 0;
	virtual double    getTextLineSpacing() const = 0;
	virtual bool      getHangingLastLine() const = 0;

	virtual void setOrigin(const mcsPoint& pnt) = 0;
	virtual void setDir(double r) = 0;
	virtual void setArrow(MCS_ARROW arrow) = 0;
	virtual void setType(Type type) = 0;
	virtual void setDulling(bool isDulling) = 0;
	virtual void setUnits(const McTNoteUnitArray& units) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;
	virtual void setMultiline(bool b) = 0;
	virtual void setRackLength(double r) = 0;
	virtual void setTextXScale(double r) = 0;
	virtual void setFrame(bool b) = 0;
	virtual void setTextLineSpacing(double r) = 0;
	virtual void setHangingLastLine(bool b) = 0;

	virtual double getArrowSize(MCS_ARROW arrow) const = 0;
	virtual double getArrowWidth(MCS_ARROW arrow) const = 0;

	virtual void setGeometryLock(bool b) = 0;
	virtual bool getGeometryLock() const = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Гребенчатая выноска
//---------------------------------------------------------------------------
struct IMcEntityNoteComb : public virtual IMcBaseLeader, public IMcCdEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2(IMcEntityNoteComb, IID_DesignElement);
	IMCS_ENT_METHOD_DEFINITION4(IMcEntityNoteComb, IMcCdEntity, IMcDbEntity, IMcBaseLeader);

	virtual mcsPoint  getStart() const = 0;
	virtual mcsPoint  getStartOCS() const = 0;
	virtual mcsPoint  getEnd() const = 0;
	virtual mcsPoint  getEndOCS() const = 0;
	virtual mcsPoint  getRackRubber() const = 0;
	virtual double    getDir() const = 0;
	virtual double    getDAngle() const = 0;
	virtual double    getTextSize() const = 0;
	virtual double    getSmallTextSize() const = 0;
	virtual McsHorizTextAlignEnum getAlign() const = 0;
	virtual LPCTSTR   getSt1() const = 0;
	virtual LPCTSTR   getSt2() const = 0;
	virtual McsString getTextStyle() const = 0;
	virtual MCS_ARROW getArrow() const = 0;
	virtual bool      getOnStart() const = 0;
	virtual bool      getMultiline() const = 0;
	virtual double    getRackLength() const = 0;
	virtual double    getTextXScale() const = 0;
	virtual bool      getFrame() const = 0;
	virtual double    getTextLineSpacing() const = 0;

	virtual void setStart(const mcsPoint& pnt) = 0;
	virtual void setEnd(const mcsPoint& pnt) = 0;
	virtual void setRackRubber(const mcsPoint& pnt) = 0;
	virtual void setDir(double r) = 0;
	virtual void setDAngle(double r) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setSmallTextSize(double r) = 0;
	virtual void setAlign(McsHorizTextAlignEnum align) = 0;
	virtual void setSt1(LPCTSTR st) = 0;
	virtual void setSt2(LPCTSTR st) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;
	virtual void setArrow(MCS_ARROW arrow) = 0;
	virtual void setOnStart(bool b) = 0;
	virtual void setMultiline(bool b) = 0;
	virtual void setRackLength(double r) = 0;
	virtual void setTextXScale(double r) = 0;
	virtual void setFrame(bool b) = 0;
	virtual void setTextLineSpacing(double r) = 0;

	virtual bool updateSegmentsOCS(const mcsPoint& pntBase, double rSegAngle, double rLineAngle = -1) = 0;
	virtual double getArrowSize(MCS_ARROW arrow) const = 0;
	virtual double getArrowWidth(MCS_ARROW arrow) const = 0;
	virtual void setDrawRack(bool b) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Цепная выноска
//---------------------------------------------------------------------------
struct IMcEntityNoteChain : public virtual IMcBaseLeader, public IMcCdEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2(IMcEntityNoteChain, IID_DesignElement);
	IMCS_ENT_METHOD_DEFINITION4(IMcEntityNoteChain, IMcCdEntity, IMcDbEntity, IMcBaseLeader);

	virtual mcsPoint  getOrigin() const = 0;
	virtual mcsPoint  getRackRubber() const = 0;
	virtual double    getAngle() const = 0;
	virtual double    getDir() const = 0;
	virtual double    getTextSize() const = 0;
	virtual double    getSmallTextSize() const = 0;
	virtual LPCTSTR   getSt1() const = 0;
	virtual LPCTSTR   getSt2() const = 0;
	virtual McsString getTextStyle() const = 0;
	virtual McsHorizTextAlignEnum getAlign() const = 0;
	virtual MCS_ARROW getArrow() = 0;
	virtual bool      getMultiline() const = 0;
	virtual double    getRackLength() const = 0;
	virtual double    getTextXScale() const = 0;
	virtual bool      getFrame() const = 0;
	virtual double    getTextLineSpacing() const = 0;

	virtual void setOrigin(const mcsPoint& pnt) = 0;
	virtual void setRackRubber(const mcsPoint& pnt) = 0;
	virtual void setAngle(double r) = 0;
	virtual void setDir(double r) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setSmallTextSize(double r) = 0;
	virtual void setSt1(LPCTSTR st) = 0;
	virtual void setSt2(LPCTSTR st) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;
	virtual void setAlign(McsHorizTextAlignEnum align) = 0;
	virtual void setArrow(MCS_ARROW arrow) = 0;
	virtual void setMultiline(bool b) = 0;
	virtual void setRackLength(double r) = 0;
	virtual void setTextXScale(double r) = 0;
	virtual void setFrame(bool b) = 0;
	virtual void setTextLineSpacing(double r) = 0;

	virtual double getArrowSize(MCS_ARROW arrow) const = 0;
	virtual double getArrowWidth(MCS_ARROW arrow) const = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Узловая секущая выноска
//---------------------------------------------------------------------------
struct IMcEntityNoteSecant : public IMcCdEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2(IMcEntityNoteSecant, IID_DesignElement);
	IMCS_ENT_METHOD_DEFINITION(IMcEntityNoteSecant, IMcCdEntity, IMcDbEntity);

	virtual mcsPoint  getPnt1() const = 0;
	virtual mcsPoint  getPnt1OCS() const = 0;
	virtual mcsPoint  getPnt2() const = 0;
	virtual mcsPoint  getPnt2OCS() const = 0;
	virtual mcsPoint  getRack() const = 0;
	virtual mcsPoint  getRackOCS() const = 0;
	virtual mcsPoint  getRackRubber() const = 0;
	virtual mcsPoint  getRackRubberOCS() const = 0;
	virtual double    getDir() const = 0;
	virtual double    getTextSize() const = 0;
	virtual double    getSmallTextSize() const = 0;
	virtual LPCTSTR   getKnot() const = 0;
	virtual LPCTSTR   getSheet() const = 0;
	virtual LPCTSTR   getNote() const = 0;
	virtual McsString getTextStyle() const = 0;
	virtual McsHorizTextAlignEnum getAlign() const = 0;
	virtual bool      isSingleStroke() = 0;
	virtual double    getTextXScale() const = 0;

	virtual void setPnt1(const mcsPoint& pnt) = 0;
	virtual void setPnt1OCS(const mcsPoint& pnt) = 0;
	virtual void setPnt2(const mcsPoint& pnt) = 0;
	virtual void setPnt2OCS(const mcsPoint& pnt) = 0;
	virtual void setRack(const mcsPoint& pnt) = 0;
	virtual void setRackOCS(const mcsPoint& pnt) = 0;
	virtual void setRackRubber(const mcsPoint& pnt) = 0;
	virtual void setRackRubberOCS(const mcsPoint& pnt) = 0;
	virtual void setDir(double r) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setSmallTextSize(double r) = 0;
	virtual void setKnot(LPCTSTR st) = 0;
	virtual void setSheet(LPCTSTR st) = 0;
	virtual void setNote(LPCTSTR st) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;
	virtual void setAlign(McsHorizTextAlignEnum align) = 0;
	virtual void setSingleStroke(bool b) = 0;
	virtual void setTextXScale(double r) = 0;

	virtual void setDrawRack(bool b) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Узловая выноска
//---------------------------------------------------------------------------
struct IMcEntityNoteKnot : public IMcCdEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2(IMcEntityNoteKnot, IID_DesignElement);
	IMCS_ENT_METHOD_DEFINITION(IMcEntityNoteKnot, IMcCdEntity, IMcDbEntity);

	virtual mcsPoint  getCenter() const = 0;
	virtual mcsPoint  getRack() const = 0;
	virtual double    getOvaloRotate() const = 0;
	virtual double    getXRadius() const = 0;
	virtual double    getYRadius() const = 0;
	virtual double    getDir() const = 0;
	virtual double    getDAngle() const = 0;
	virtual double    getTextSize() const = 0;
	virtual double    getSmallTextSize() const = 0;
	virtual LPCTSTR   getKnot() const = 0;
	virtual LPCTSTR   getSheet() const = 0;
	virtual LPCTSTR   getNote() const = 0;
	virtual McsString getTextStyle() const = 0;
	virtual McsHorizTextAlignEnum getAlign() const = 0;
	virtual bool      isCircle() = 0;
	virtual double    getTextXScale() const = 0;

	virtual void setCenter(const mcsPoint& pnt) = 0;
	virtual void setRack(const mcsPoint& pnt) = 0;
	virtual void setOvaloRotate(double r) = 0;
	virtual void setXRadius(double r) = 0;
	virtual void setYRadius(double r) = 0;
	virtual void setDir(double r) = 0;
	virtual void setDAngle(double r) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setSmallTextSize(double r) = 0;
	virtual void setKnot(LPCTSTR st) = 0;
	virtual void setSheet(LPCTSTR st) = 0;
	virtual void setNote(LPCTSTR st) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;
	virtual void setAlign(McsHorizTextAlignEnum align) = 0;
	virtual void setCircle(bool b) = 0;
	virtual void setTextXScale(double r) = 0;

	virtual void setDrawRack(bool b) = 0;
	virtual bool updateDAngle(bool bCenterFix) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Позиционная выноска
//---------------------------------------------------------------------------
struct IMcEntityNotePosition : public virtual IMcBaseLeader, public IMcCdEntity, public IMcAnnotation
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2(IMcEntityNotePosition, IID_DesignElement);
	IMCS_ENT_METHOD_DEFINITION5(IMcEntityNotePosition, IMcCdEntity, IMcDbEntity, IMcBaseLeader, IMcAnnotation);

	virtual mcsPoint  getOrigin() const = 0;
	virtual double    getDir() const = 0;
	virtual double    getDAngle() const = 0;
	virtual double    getTextSize() const = 0;
	virtual double    getSmallTextSize() const = 0;
	virtual LPCTSTR   getSt1() const = 0;
	virtual LPCTSTR   getSt2() const = 0;
	virtual McsString getTextStyle() const = 0;
	virtual McsHorizTextAlignEnum getAlign() const = 0;
	virtual MCS_ARROW getArrow() const = 0;
	virtual bool      getMultiline() const = 0;
	virtual double    getRackLength() const = 0;
	virtual double    getTextXScale() const = 0;
	virtual bool      getFrame() const = 0;
	virtual double    getTextLineSpacing() const = 0;

	virtual void setOrigin(const mcsPoint& pnt) = 0;
	virtual void setDir(double r) = 0;
	virtual void setDAngle(double r) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setSmallTextSize(double r) = 0;
	virtual void setSt1(LPCTSTR st) = 0;
	virtual void setSt2(LPCTSTR st) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;
	virtual void setAlign(McsHorizTextAlignEnum align) = 0;
	virtual void setArrow(MCS_ARROW arrow) = 0;
	virtual void setMultiline(bool b) = 0;
	virtual void setRackLength(double r) = 0;
	virtual void setTextXScale(double r) = 0;
	virtual void setFrame(bool b) = 0;
	virtual void setTextLineSpacing(double r) = 0;

	virtual double getArrowSize(MCS_ARROW arrow) const = 0;
	virtual double getArrowWidth(MCS_ARROW arrow) const = 0;

	virtual void setGeometryLock(bool b) = 0;
	virtual bool getGeometryLock() const = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Маркировка линейных объектов
//---------------------------------------------------------------------------
struct IMcEntityLinearMark : public IMcCdEntity, public IMcAnnotation
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2(IMcEntityLinearMark, IID_DesignElement);
	IMCS_ENT_METHOD_DEFINITION4(IMcEntityLinearMark, IMcCdEntity, IMcDbEntity, IMcAnnotation); 

	virtual mcsPoint  getPnt1() const = 0;
	virtual mcsPoint  getPnt2() const = 0;
	virtual mcsPoint  getPntText() const = 0;
	virtual double    getTextSize() const = 0;
	virtual double    getSmallTextSize() const = 0;
	virtual LPCTSTR   getSt1() const = 0;
	virtual LPCTSTR   getSt2() const = 0;
	virtual McsString getTextStyle() const = 0;
	virtual McsHorizTextAlignEnum getAlign() const = 0;
	virtual McGeometryParam getPar1() const = 0;
	virtual McGeometryParam getPar2() const = 0;
	virtual bool      getMultiline() const = 0;
	virtual double    getRackLength() const = 0;
	virtual double    getTextXScale() const = 0;
	virtual double    getTextLineSpacing() const = 0;

	virtual void setPnt1(const mcsPoint& pnt) = 0;
	virtual void setPnt2(const mcsPoint& pnt) = 0;
	virtual void setPntText(const mcsPoint& pnt) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setSmallTextSize(double r) = 0;
	virtual void setSt1(LPCTSTR st) = 0;
	virtual void setSt2(LPCTSTR st) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;
	virtual void setAlign(McsHorizTextAlignEnum align) = 0;
	virtual void setPar1(const McGeometryParam& par) = 0;
	virtual void setPar2(const McGeometryParam& par) = 0;
	virtual void setMultiline(bool b) = 0;
	virtual void setRackLength(double r) = 0;
	virtual void setTextXScale(double r) = 0;
	virtual void setTextLineSpacing(double r) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Выноска для многослойных конструкций
//---------------------------------------------------------------------------
struct IMcEntityNoteMultiLayer : public IMcCdEntity, public IMcArrowsExtension
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2(IMcEntityNoteMultiLayer, IID_DesignElement);
	IMCS_ENT_METHOD_DEFINITION4(IMcEntityNoteMultiLayer, IMcCdEntity, IMcDbEntity, IMcArrowsExtension); 

	virtual mcsPoint  getStart() const = 0;
	virtual mcsPoint  getStartOCS() const = 0;
	virtual mcsPoint  getEnd() const = 0;
	virtual mcsPoint  getEndOCS() const = 0;
	virtual double    getDir() const = 0;
	virtual double    getRackLength() const = 0;
	virtual double    getTextSize() const = 0;
	virtual McsString getTextStyle() const = 0;
	virtual MCS_ARROW getArrow() const = 0;
	virtual bool      getUpCorner() const = 0;
	virtual bool      getLine() const = 0;
	virtual bool      getMultiline() const = 0;
	virtual const McTNoteUnitArray& getUnits() const = 0;
	virtual double    getTextXScale() const = 0;
	virtual bool      getFrame() const = 0;
	virtual double    getTextLineSpacing() const = 0;
	virtual bool      getHangingLastLine() const = 0;

	virtual void setStart(const mcsPoint& pnt) = 0;
	virtual void setStartOCS(const mcsPoint& pnt) = 0;
	virtual void setEnd(const mcsPoint& pnt) = 0;
	virtual void setEndOCS(const mcsPoint& pnt) = 0;
	virtual void setDir(double r) = 0;
	virtual void setRackLength(double r) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;
	virtual void setArrow(MCS_ARROW arrow) = 0;
	virtual void setUpCorner(bool b) = 0;
	virtual void setLine(bool b) = 0;
	virtual void setMultiline(bool b) = 0;
	virtual void setUnits(const McTNoteUnitArray& units) = 0;
	virtual void setTextXScale(double r) = 0;
	virtual void setFrame(bool b) = 0;
	virtual void setTextLineSpacing(double r) = 0;
	virtual void setHangingLastLine(bool b) = 0;

	virtual double getArrowSize(MCS_ARROW arrow) const = 0;
	virtual double getArrowWidth(MCS_ARROW arrow) const = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Отдельная строительная ось
//---------------------------------------------------------------------------
//типы осей
enum axis_type
{
	axis_type_unknown = 0,//неизвестный (недопустимый) тип
	axis_type_linear,//прямая ось
	axis_type_arc,//дуговая ось
	axis_type_circ//круговая ось
};

//тип нумерации (буквенная или цифровая)
enum chunk_naming_type
{
	chunk_naming_type_unknown = 0,//некорректное значение
	chunk_naming_type_digits,//только цифры
	chunk_naming_type_letters,//только буквы
	chunk_naming_type_digits_or_letters,//цифры или буквы
	chunk_naming_type_any//отключить проверку имен маркеров
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Строительная ось. Может указывать как на отдельную строительную ось, так и на ось внутри массива.
//---------------------------------------------------------------------------
struct ISpdsAxis : virtual public IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(ISpdsAxis);
	IMCS_STD_METHOD_DEFINITION(ISpdsAxis, IMcObject);

	// основные
	virtual bool IsValidAxis() const = 0;//вернет true, если интерфейс всё еще указывает на какую-то валидную ось
	virtual bool setType(axis_type type) = 0;//установить новый тип оси (все настройки сбрасываются)
	virtual axis_type getType() const = 0;//получить тип оси (от него в дальнейшем зависит, какие методы можно вызывать)

	// методы для работы с осями любого типа (set)
	// методы возвращают true в случае успешного завершения операции
	virtual bool addMarker(LPCTSTR text) = 0;//добавить маркер с указанным текстом
	virtual bool setMarkerText(int idx, LPCTSTR text) = 0;//изменить текст существующего маркера
	virtual bool setMarkers(mcsStringArray& names) = 0;//заменить все маркеры на указанные в массиве

	virtual bool removeMarker(LPCTSTR text) = 0;//удалить первый маркер с указанным текстом
	virtual bool removeMarker(int idx) = 0;//удалить маркер под номером idx
	virtual bool removeMarkers() = 0;//удалить все маркеры
	virtual bool hideMarker(bool hide) = 0;//установить признак скрытия маркеров
	virtual bool setNamingType(chunk_naming_type namingType) = 0;//установить или снять ограничение на имена маркеров

	virtual bool setAxisVisible(bool visible) = 0;//установить признак скрытия осевой линии

	virtual bool setLength(double len) = 0;//установить длину осевой линии

	// методы для работы с осями любого типа (get)
	virtual mcsPoint getMarkerCenter(int idx = 0) const = 0;//получить центр маркера idx
	virtual mcsPoint getMarkerCenterOCS(int idx = 0) const = 0;//получить центр маркера idx
	virtual McsString getMarkerText(int idx = 0) const = 0;//получить текст маркера idx
	virtual double getMarkerRadius(int idx = 0) const = 0;//получить радиус маркера idx
	virtual mcsPoint getMiddlePointOCS() const = 0;//получить среднюю точку осевой линии
	virtual mcsStringArray getMarkers() const = 0;//получить массив текстов маркеров
	virtual int getNumMarker() const = 0;//получить количество маркеров
	virtual bool isHideMarker() const = 0;//получить признак скрытия маркеров
	virtual chunk_naming_type getNamingType() const = 0;//плдучить текущий режим ограничения на имена маркеров 
	virtual double getLength() const = 0;//получить длину осевой линии
	virtual bool isAxisVisible() const = 0;//получить признак скрытия осевой линии
	virtual mcsWorkID getGUID() const = 0;//получить уникальный идентификатор оси

	// методы для работы с осями, содержащими прямой участок (axis_type_linear и axis_type_arc) (set)
	// методы возвращают true в случае успешного завершения операции

	//(!!!) в методах с параметром back, когда back == true, возвращаются соответствующие показатели
	//(!!!) для противоположного конца оси.
	virtual bool setTailAngle(double angle, bool back = false) = 0;//установить угол отклонения "хвоста" оси от направления её прямого участка
	virtual bool setTailAngleOCS(const mcsPoint& tailPoint, bool back = false) = 0;//то же, но используя точку на "хвосте"

	virtual bool hideBackMarker(bool hide) = 0;//установить признак скрытия инвертированных маркеров

	// методы для работы с осями, содержащими прямой участок (axis_type_linear и axis_type_arc) (get)
	virtual mcsPoint getStartPoint() const = 0;//получить начальную точку осевой линии
	virtual mcsPoint getStartPointOCS() const = 0;//получить начальную точку осевой линии
	virtual mcsPoint getEndPoint() const = 0;//получить конечную точку осевой линии
	virtual mcsPoint getEndPointOCS() const = 0;//получить конечную точку осевой линии
	virtual double getStraightLength(bool back = false) const = 0;//получить длину прямого участка оси (у линейной оси прямой участок вырожден, поэтому вернет 0)
	virtual mcsPoint getStraightEndPointOCS(bool back = false) const = 0;//получить конечную точку прямого участка оси
	virtual double getTailProjectionLength() const = 0;//получить длину проекции "хвоста" на направление прямого участка оси
	virtual mcsPoint getTailEndPointOCS(bool back = false) const = 0;//получить конечную точку "хвоста" оси
	virtual mcsVector getTailDirectionOCS(bool back = false) const = 0;//получить направление "хвоста" оси
	virtual double getTailLength(bool back = false) const = 0;//получить длину "хвоста" оси	
	virtual bool isHideBackMarker() const = 0;//получить признак скрытия инвертированных маркеров
	virtual mcsVector getDirectionOCS(bool back = false) const = 0;//получить направление прямого участка оси
	virtual double getTailAngle(bool back = false) const = 0;//получить угол отклонения "хвоста"
	virtual mcsPoint getPlaitEndPointOCS(bool back = true) const = 0;//получить конечную точку "косички" оси ("косичка" - прямое продолжение оси за начальную точку)
	virtual double getPlaitLength() const = 0;//получить длину "косички"
	virtual mcsPoint getMarkerCenter(int idx, bool back) const = 0;//получить центр маркера, позволяет получить центр заднего маркера
	virtual mcsPoint getMarkerCenterOCS(int idx, bool back) const = 0;//получить центр маркера, позволяет получить центр заднего маркера

	// методы для работы с осями, содержащими дуговой участок (axis_type_arc и axis_type_circ) (set)
	// методы возвращают true в случае успешного завершения операции
	virtual bool setCenter(const mcsPoint& center) = 0;//установить центр дугового участка оси
	virtual bool setCenterOCS(const mcsPoint& center) = 0;//установить центр дугового участка оси
	virtual bool setRadius(double radius) = 0;//установить радиус дугового участка оси

	// методы для работы с осями, содержащими дуговой участок (axis_type_arc и axis_type_circ) (get)
	virtual mcsPoint getCenter() const = 0;//получить центр дугового участка оси
	virtual mcsPoint getCenterOCS() const = 0;//получить центр дугового участка оси
	virtual double getRadius() const = 0;//получить радиус дугового участка оси

	// методы для работы с линейными осями (axis_type_linear) (set)
	virtual bool setStartPoint(const mcsPoint& startPt) = 0;//установить начальную точку осевой линии
	virtual bool setStartPointOCS(const mcsPoint& startPt) = 0;//установить начальную точку осевой линии
	virtual bool setEndPoint(const mcsPoint& endPt) = 0;//установить конечную точку осевой линии
	virtual bool setEndPointOCS(const mcsPoint& endPt) = 0;//установить конечную точку осевой линии
	virtual bool setPoints(const mcsPoint& startPt, const mcsPoint& endPt) = 0;//установить начальную и конечную точки осевой линии
	virtual bool setPointsOCS(const mcsPoint& startPt, const mcsPoint& endPt) = 0;//установить начальную и конечную точки осевой линии

	// методы для работы с дуговыми осями (axis_type_arc) (set)
	virtual bool setAngles(double sAngle, double eAngle) = 0;//установить углы начала и конца дуги
	virtual bool setStartAngle(double ang) = 0;//установить угол начала дуги (0 <= ang < 2PI)
	virtual bool setEndAngle(double ang) = 0;//установить угол конца дуги (getStartAngle() < ang < getStartAngle() + 2PI)

	// методы для работы с дуговыми осями (axis_type_arc) (get)
	virtual double getStartAngle() const = 0;//получить угол начала дуги
	virtual double getEndAngle() const = 0;//получить угол конца дуги

	// методы для работы с круговыми осями (axis_type_circ) (set)
	virtual bool setMarkerAngle(double ang) = 0;//установить угол расположения маркера (0 <= ang < 2PI)

	// методы для работы с круговыми осями (axis_type_circ) (get)
	virtual double getMarkerAngle() const = 0;//получить угол расположения маркера
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Строительная ось.
//---------------------------------------------------------------------------
struct ISpdsEntityCLine : virtual public IMcEntity, virtual public ISpdsAxis
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(ISpdsEntityCLine);
	virtual const GUID& getClassID() const
	{
		return __uuidof(ISpdsEntityCLine);
	}
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvobj)
	{
		*ppvobj = NULL;
		if(riid == __uuidof(ISpdsEntityCLine))
		{
			*ppvobj = (ISpdsEntityCLine*)this;
			AddRef();
			return S_OK;
		}
		if(riid == __uuidof(ISpdsAxis))
		{
			*ppvobj = (ISpdsAxis*)this;
			AddRef();
			return S_OK;
		}
		return IMcEntity::QueryInterface(riid, ppvobj);
	}
};


//тип массива осей
enum SpdsGridType
{
	SpdsGridType_Unknown = 0,
	SpdsGridType_Rectangular,
	SpdsGridType_Polar
};

//типы (направление) осей в массиве
enum GridAxisKind
{
	GridAxisKind_First = 0,
	GridAxisKind_X = 0,			//оси в прямоугольном массиве, относительно которых рассчитывается угол поворота
	GridAxisKind_Y = 1,			//оси в прямоугольном массиве, перпендиулярные осям RectAxisType_X
	GridAxisKind_Radial = 0,	//прямые оси в полярном массиве, относительно которых рассчитывается угол поворота
	GridAxisKind_Angular = 1,	//дуговые или круговые оси в полярном массиве
	GridAxisKind_Last = 1
};

//режим автонумерации
enum chunk_naming_mode {
	chunk_naming_mode_manual = 0,	//средства автонумерации выключены
	chunk_naming_mode_inc,			//включен режим автонумерации "с начала массива"
	chunk_naming_mode_dec			//включен режим автонумерации "с конца массива"
};

//относительная позиция маркеров какого-либо направления осей в массиве
enum relative_markers_position {
	relative_markers_position_mixed = 0, //маркеры направлены в разные стороны, значение только для get
	relative_markers_position_forward,   //маркеры направлены по направлению осей
	relative_markers_position_backward,  //маркеры направлены против направления осей
	relative_markers_position_both,      //маркеры присутствуют с обоих сторон осей
	relative_markers_position_hidden,	 //маркеры скрыты
	relative_markers_position_circullar  //кольцевые маркеры (только для полярных осей)
};

//абсолютная (в координатах viewport'а) позиция маркеров какого-либо направления осей в массиве
enum absolute_markers_position {
	absolute_markers_position_mixed = 0,		//маркеры направлены в разные стороны, значение только для get
	absolute_markers_position_left,				//маркеры направлены влево
	absolute_markers_position_right,			//маркеры направлены вправо
	absolute_markers_position_top,				//маркеры направлены вверх
	absolute_markers_position_bottom,			//маркеры направлены вниз
	absolute_markers_position_top_and_bottom,	//маркеры присутствуют сверху и снизу
	absolute_markers_position_left_and_right,	//маркеры присутствуют слева и справа
	absolute_markers_position_hidden			//маркеры скрыты
};

// массив осей вообще (абстрактный тип)
struct ISpdsGrid : public IMcEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(ISpdsGrid);
	IMCS_STD_METHOD_DEFINITION(ISpdsGrid, IMcEntity);

	//returns grid type
	virtual SpdsGridType getGridType() const = 0;

	//добавляет готовую ось в массив.
	//если ось не подходит по направлению - возвращает false.
	//если задано eraseOriginal, то исходная ось удаляется из документа.
	//если задан указатель на index, то в него сохраняется индекс, присвоенный оси
	virtual bool addAxis(GridAxisKind direction, ISpdsEntityCLinePtr pCLine, bool eraseOriginal = true, OUT unsigned int* index = NULL) = 0;

	//добавляет готовую ось в массив.
	//в отличие от предыдущего метода, пытается самостоятельно определить направление.
	//если не получается добавить ось - возвращает false.
	//если задан указатель на index, то в него сохраняется индекс, присвоенный оси
	//если задан указатель на direction, то в него сохраняется направление, по которому добавлена ось
	virtual bool addAxis(ISpdsEntityCLinePtr pCLine, bool eraseOriginal = true, OUT GridAxisKind* direction = NULL, OUT unsigned int* index = NULL) = 0;

	//добавляет готовую ось в массив.
	//еще более либерально относится к добавляемой оси
	//пытается самостоятельно подкорректировать добавляемую ось так, чтобы она подходила к массиву
	//внимание: метод изменяет исходную ось pCLine
	//если задан указатель на index, то в него сохраняется индекс, присвоенный оси
	//если задан указатель на direction, то в него сохраняется направление, по которому добавлена ось
	virtual bool addAxisFuzzy(ISpdsEntityCLinePtr pCLine, bool eraseOriginal = true, OUT GridAxisKind* direction = NULL, OUT unsigned int* index = NULL) = 0;

	//дублирует ось с индексом src_index и сдвигает её на расстояние distance
	//относительно родительской оси. distance может быть и отрицательным, тогда
	//ось будет сдвинута в сторону уменьшения индексов.
	//при удачном выполнении src_index будет содержать новый индекс родительской оси,
	//dst_index - индекс дубликата, а функция вернет true	
	virtual bool duplicateAxis(IN GridAxisKind direction, IN OUT unsigned int& src_index, OUT unsigned int& dst_index, double distance) = 0;

	//добавляет одну или несколько осей по указанному направлению с
	//расстоянием distance между ними.
	virtual bool addAxes(GridAxisKind direction, double distance, unsigned int count) = 0;

	//добавляет ось из массива в документ как отдельный объект,
	//возвращает указатель на объект
	//если задано removeFromGrid = true - ось удаляется из массива.
	virtual ISpdsEntityCLinePtr extractAxis(GridAxisKind direction, unsigned int index, bool removeFromGrid) = 0;
	virtual ISpdsEntityCLinePtr extractAxis(GridAxisKind direction, unsigned int index) const = 0;

	//получает указатель на ось в массиве
	//помните, что на ось в массиве действуют ограничения, накладываемые массивом, поэтому
	//многие методы будут возвращать false
	virtual ISpdsAxisPtr getAxis(GridAxisKind kind, unsigned int index) = 0;

	//получить индексы осей, пересечение которых ближе всего к pnt
	//first - индекс оси направления GridAxisKind_X или GridAxisKind_Radial
	//second - индекс оси направления GridAxisKind_Y или GridAxisKind_Angular
	//возвращает false, если в массиве нет пересекающихся осей
	virtual bool getAxesIntersectionByPoint(unsigned int& first, unsigned int& second, const mcsPoint& pnt) const = 0;

	//возвращает нормализованный вектор-направление затребованного типа осей
	//если направление не может быть определено (массив из осей-окружностей),
	//то возвращается вектор нулевой длины
	virtual mcsVector getAxesDirection(GridAxisKind direction) const = 0;
	virtual mcsVector getAxesDirectionOCS(GridAxisKind direction) const = 0;

	//возвращает true, если ось может быть добавлена в массив по заданному направлению
	virtual bool isAxisValidForDirection(GridAxisKind direction, ISpdsEntityCLinePtr pCLine) const = 0;

	//возвращает направление и индекс оси, ближайшей к pickPnt
	virtual bool getAxisByPoint(GridAxisKind& direction, unsigned int& index, const mcsPoint& pickPnt) const = 0;

	//возвращает направление и индекс оси по её уникальному идентификатору
	virtual bool getAxisByGUID(GridAxisKind& direction, unsigned int& index, const mcsWorkID& guid) const = 0;

	//adds a new set of count axis with distance between them, named started from first_title
	//returns index of first added axis
	//virtual unsigned int addAxes(GridAxisKind direction, double distance, unsigned int count = 1, LPCTSTR first_title = NULL) = 0;

	//removes one axis with index
	//returns false if index is out of range
	virtual bool removeAxis(GridAxisKind direction, unsigned int index) = 0;

	//removes all axes for direction	
	virtual bool removeAllAxes(GridAxisKind direction) = 0;

	//removes one group
	//return false if index out of range
	virtual bool removeGroup(GridAxisKind direction, unsigned int index) = 0;

	//returns axis type in specified direction
	virtual axis_type getAxesType(GridAxisKind direction) const = 0;

	//returns axis count in specified direction
	virtual unsigned int getAxesCount(GridAxisKind direction) const = 0;

	//returns marker text of index axis of direction
	//returns blank string if index out of range
	virtual McsString getAxisText(GridAxisKind direction, unsigned int index, unsigned int marker_index = 0) const = 0;

	//set marker text of index axis of direction
	//if text is NULL and marker_index > 0, then remove specified marker
	//returns false if index is out of range
	virtual bool setAxisText(GridAxisKind direction, unsigned int index, LPCTSTR text, unsigned int marker_index = 0) = 0;

	//return axis_index axis markers count
	//return 0 in case of error
	virtual unsigned int getAxisMarkersCount(GridAxisKind direction, unsigned int axis_index) const = 0;

	//returns distance between index and index-1 axis of direction
	//returns negative value if index out of range	
	//if grid type is Polar and AxisDirection is Y, then when index = 0, returns distance between first axis and center of the grid
	//in other cases when index = 0, returns 0.
	virtual double getAxisDistance(GridAxisKind direction, unsigned int index) const = 0;

	//set distance of index axis of direction
	//returns false if index is out of range
	//returns also false if trying to set distance of index 0
	//if bMoveOthers == true, then all axes after index axis also moves
	virtual bool setAxisDistance(GridAxisKind direction, unsigned int index, double distance, bool bMoveOthers = true) = 0;

	//AxisGroup is one or more axes with the same distances between them
	/*

	axis_index:   0  1  2    3    4 5    6    7 8 9 10    11

	group_index:  0   1        2    3      4      5       6
	              |  /--\    /----\ |    /----\ /---\     |

	              o  o  o    o    o o    o    o o o o     o
	              |  |  |    |    | |    |    | | | |     |
	              |  |  |    |    | |    |    | | | |     |
	              |  |  |    |    | |    |    | | | |     |
	              |  |  |    |    | |    |    | | | |     |
	              |  |  |    |    | |    |    | | | |     |
	              |  |  |    |    | |    |    | | | |     |

	distance:     0  2  2    4    4 1    4    4 1 1 1     5

	*/

	//returns count of groups within selected direction
	virtual unsigned int getAxesGroupsCount(GridAxisKind direction) const = 0;

	//returns axis index of first axis, which belongs to group_index group
	//returns -1 if group_index is out of range
	virtual int getAxesGroupFirstIndex(GridAxisKind direction, unsigned int group_index) const = 0;

	//returns axis index of last axis, which belongs to group_index group
	//returns -1 if group_index is out of range
	virtual int getAxesGroupLastIndex(GridAxisKind direction, unsigned int group_index) const = 0;

	//returns count of axes, which belongs to group_index group
	//returns zero if group_index is out of range
	virtual unsigned int getAxesGroupLength(GridAxisKind direction, unsigned int group_index) const = 0;

	//returns group index for axis axis_index
	//returns -1 if axis_index is out of range
	virtual int getGroupForAxis(GridAxisKind direction, unsigned int axis_index) const = 0;

	//returns distance between axes, which belongs to group_index group
	//returns negative value if group_index is out of range
	virtual double getAxesGroupDistance(GridAxisKind direction, unsigned int group_index) const = 0;

	//set distance between axes, which belongs to group_index group
	//returns false if group_index is out of range
	virtual bool setAxesGroupDistance(GridAxisKind direction, unsigned int group_index, double distance) = 0;

	//set axes count in group group_index to length
	//setting length = 0 equals to removing the group
	//returns false if group_index is out of range
	virtual bool setAxesGroupLength(GridAxisKind direction, unsigned int group_index, unsigned int length) = 0;

	//total length
	virtual double getTotalLength(GridAxisKind direction) const = 0;

	//enable/disable total dimension
	virtual bool isDimTotalEnabled(GridAxisKind direction) const = 0;
	virtual void enableDimTotal(GridAxisKind direction, bool enable) = 0;

	//вернет true, если idDim - идентификатор общего размера по направлению direction
	virtual bool isDimTotal(GridAxisKind direction, const mcsWorkID& idDim) const = 0;

	//enable/disable chain dimension
	virtual bool isDimChainEnabled(GridAxisKind direction) const = 0;
	virtual void enableDimChain(GridAxisKind direction, bool enable) = 0;

	//enable/disable chain dimension grouping
	virtual bool isDimChainGroupEnabled(GridAxisKind direction) const = 0;
	virtual void enableDimChainGroup(GridAxisKind direction, bool enable) = 0;

	//возвращает направление и индекс оси по идентификатору привязанного к ней цепочечного размера
	virtual bool getAxisByDimension(GridAxisKind& kind, unsigned int& index, const mcsWorkID& idDim) const = 0;

	//returns true, if that kind has chain dims, erased by user manually
	virtual bool hasErasedChainDims(GridAxisKind kind) const = 0;

	//для ортогонального массива возвращает начало системы координат массива
	//для полярного массива возвращает центр массива
	virtual mcsPoint getBasePoint() const = 0;
	virtual mcsPoint getBasePointOCS() const = 0;

	//для ортогонального массива возвращает угол поворота осей GridAxesKind_X
	//для полярного массива возвращает угол поворота первой радиальной оси
	//углы отсчитываются по часовой стрелки относительно оси -X
	virtual double getAngle() const = 0;

	//установить/получить режим нумерации
	virtual bool setNamingMode(GridAxisKind direction, chunk_naming_mode nMode) = 0;
	virtual chunk_naming_mode getNamingMode(GridAxisKind direction) const = 0;

	//установить/получить тип автонумерации (цифровая или буквенная)
	//типы автонумерации всегда разные у ортогональных осей
	//установка типа по одному направлению может повлиять на тип по другому направлению
	virtual bool setNamingType(GridAxisKind direction, chunk_naming_type nType) = 0;
	virtual chunk_naming_type getNamingType(GridAxisKind direction) const = 0;

	//установить/получить относительную позицию маркеров для осей
	virtual bool setRelativeMarkersPosition(GridAxisKind direction, relative_markers_position position) = 0;
	virtual relative_markers_position getRelativeMarkersPosition(GridAxisKind direction) const = 0;

	//установить/получить абсолютную позицию маркеров для осей
	virtual bool setAbsoluteMarkersPosition(GridAxisKind direction, absolute_markers_position position) = 0;
	virtual absolute_markers_position getAbsoluteMarkersPosition(GridAxisKind direction) const = 0;

	// Преобразование индексов осей между абсолютной и относительной адресацией.
	// Относительная адресация - индексы осей начинаются от некоторой характерной точки массива:
	//  - от центра/по часовой стрелке - для полярного массива осей;
	//  - от точки пересечения осей, которые были первыми добавлены в массив - для ортогонального массива.
	// Относительная адресация всегда постоянна и не зависит от ориентации массива в пространстве или
	// от включенного режима именования осей. Именна эта адресация используется в остальных методах,
	// принимающих индекс оси.
	// Абсолютная адресация  - индексы осей меняются в зависимости от положения массива в пространстве и
	// режима именования осей:
	//  - для полярного массива осей, если включен режим именования осей chunk_naming_mode_manual,
	//    chunk_naming_mode_inc или chunk_naming_mode_gost, то совпадает с относительной адресацией;
	//  - для полряного массива осей, если включен режим именования осей chunk_naming_mode_dec, то
	//    индексы исчисляются к центру массива или против часовой стрелки;
	//  - для ортогонального массива осей, если включен режим именования chunk_naming_mode_manual или
	//    chunk_naming_mode_inc, то совпадает с относительной адресацией;
	//  - для ортогонального массива осей, если включен режим именования chunk_naming_mode_dec, то
	//    индексы исчисляются по направлению к точке пересечения осей, которые были первыми добавлены
	//    в массив;
	//  - для ортогонального массива осей, если включен режим именования chunk_naming_mode_gost, то
	//    индексы исчисляются в зависимости от положения массива в глобальной системе координат:
	//    слева направо либо снизу вверх, в зависимости от того, к какому из направлений (горизонтали
	//    или вертикали) ориентация массива осей ближе в данный момент.
	virtual unsigned int getAbsoluteAxisIndex(GridAxisKind kind, unsigned int relative_axis_index) const = 0;
	virtual unsigned int getRelativeAxisIndex(GridAxisKind kind, unsigned int absolute_axis_index) const = 0;

	//растягивает оси в массиве так, что их концы оказываются
	//линейно выровненными.
	//если указано allow_shrinking, то после выравнивания происходит
	//"обрезка" выступающих частей осей в массиве и подтягивание
	//укороченных.
	virtual void fit(bool allow_shrinking = false) = 0;

	//return kind of axes, which are most in count
	virtual GridAxisKind getLongestKind() const = 0;

	//copy specified kind of pSourceGrid to specified kind of this grid
	virtual bool copyFrom(GridAxisKind kind, ISpdsGridPtr pSourceGrid, GridAxisKind sourceKind) = 0;

	//позволяет получить идентификатор направления осей в массиве по типу их нумерации
	//вернет false, если направления с запрашиваемым типом нумерации не найдено в массиве
	virtual bool getKindByNamingType( GridAxisKind& kind, chunk_naming_type naming_type ) const = 0;

	//установить/получить тип набора букв для осей
	//наборы букв определены в секции ConstructionAxes файла settings.xml
	virtual bool setLettersType(LPCTSTR spzSubType) = 0;
	virtual McsString getLettersType() const = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Ортогональный массив осей
//---------------------------------------------------------------------------

//характерные точки для ортогонального массива
enum RectGridPoint
{
	RectGridPoint_Base = 0, //то же, что и getBasePoint()

	//относительно системы координат массива
	RectGridPoint_MinX_MinY,
	RectGridPoint_MinX_MaxY,
	RectGridPoint_MaxX_MaxY, //то же, что и getBasePoint()
	RectGridPoint_MaxX_MinY,
	//===========================

	//относительно глобальной системы координат
	RectGridPoint_TopLeft,
	RectGridPoint_TopRight,
	RectGridPoint_BottomLeft,
	RectGridPoint_BottomRight
	//=========================================
};

struct ISpdsRectGrid : public virtual ISpdsGrid
{  
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(ISpdsRectGrid);
	IMCS_STD_METHOD_DEFINITION(ISpdsRectGrid, ISpdsGrid);

	//создает первую ось по соответствущему направлению
	//работает только если по второму направлению уже есть как минимум одна ось
	//если по другому направлению только одна ось, то длина новой оси будет равна длине этой одной оси
	//или если length > 0, то length
	//если по другому направлению больше одной оси, то длина новой оси будет равна ширине массива по
	//второму направлению или length, если length больше этой ширины
	virtual bool createFirstAxis(GridAxisKind kind, double length = -1) = 0;

	//return true if specified kind axes are more horizontal rather
	//than vertical
	virtual bool isHorizontal(GridAxisKind kind) const = 0;

	//возвращает характерную точку массива
	virtual mcsPoint getPoint(RectGridPoint ip_type) const = 0;
	virtual mcsPoint getPointOCS(RectGridPoint ip_type) const = 0;
};


/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Полярный массив осей
//---------------------------------------------------------------------------

//характерные точки для полярного массива
enum PolarGridPoint
{
	PolarGridPoint_Center = 0,  //центр массива, //то же, что и getBasePoint()
	PolarGridPoint_Begin,		//точка, образованная пересечением первой радиальной оси и последней угловой оси
	PolarGridPoint_End			//точка, образованная пересечением последней радиальной оси и последней угловой оси
};

struct ISpdsPolarGrid : public virtual ISpdsGrid
{  
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(ISpdsPolarGrid);
	IMCS_STD_METHOD_DEFINITION(ISpdsPolarGrid, ISpdsGrid);

	// !!! все углы считаются от отрицательного направления оси X по часовой стрелке !!!
	// !!! все углы в радианах !!!
	// !!! все углы лежат в полуинтервале [0, 2PI) !!!

	//создает первую радиальную ось
	//работает только если уже есть хотя бы одна угловая ось
	//если есть только одна угловая ось, то длина новой оси будет равна длине этой угловой оси или
	//length, если length > 0
	//если есть хотя бы две угловых оси, то длина новой оси будет равна радиусу последней угловой оси или 
	//length, если length > этого радиуса
	virtual bool	createFirstRadialAxis(double length = -1) = 0;

	//создает первую угловую ось
	//работает только если уже есть хотя бы одна радиальная ось
	//конечный угол оси задается по начальному углу массива (т.е. по углу первой радиальной оси)
	//если есть только одна радиальная ось, то начальный угол оси выбирается так,
	//чтобы общий угол оси был 90 градусов, или если startAngle >= 0, то startAngle
	//если есть более одной радиальной оси, то начальный угол - угол последней радиальной оси или
	//startAngle, если он дальше от конечного угла.
	//радиус оси - длина самой короткой радиальной оси или radius, если radius > 0
	virtual bool	createFirstAngularAxis(double radius = -1, double startAngle = -1) = 0;

	//получить/установить начальный (ближний к маркерам) угол полярных осей
	virtual double	getStartAngle() const = 0;
	virtual bool	setStartAngle(double startAngle) = 0;

	//получить/установить конечный (противоположный маркерам) угол полярных осей
	virtual double	getEndAngle() const = 0;
	virtual bool	setEndAngle(double endAngle) = 0;

	//установить оба угла полярных осей сразу
	virtual bool	setAngles(double startAngle, double endAngle) = 0;

	//получить/установить угол положения замковых маркеров
	virtual double	getMarkersAngle() const = 0;
	virtual bool	setMarkersAngle(double rAngle) = 0;

	//возвращает характерную точку массива
	virtual mcsPoint getPoint(PolarGridPoint ip_type) const = 0;
	virtual mcsPoint getPointOCS(PolarGridPoint ip_type) const = 0;

	//объединять противоположные радиальные оси?
	virtual bool combineOppsiteRadialAxes(bool bCombine) = 0;
	virtual bool isOppositeRadialAxesCombined() const = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Указатель ориентации оси
//---------------------------------------------------------------------------
struct ISpdsEntityCLOrient : public IMcEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(ISpdsEntityCLOrient);

	// Начальная точка указателя
	virtual mcsPoint GetStartPoint() const = 0;
	virtual void SetStartPoint(const mcsPoint& pnt) = 0;// Отвяжет указатель от строительной оси

	// Центр маркера указателя
	virtual mcsPoint GetEndPoint() const = 0;
	virtual void SetEndPoint(const mcsPoint& pnt) = 0;// Отвяжет указатель от строительной оси

	// Текст маркера указателя
	virtual LPCTSTR GetMarkerText() const = 0;
	virtual void SetMarkerText(LPCTSTR st, bool withValidnessCheck = true) = 0;// Установит настройку АВТО_ТЕКСТ в false

	// Связанная ось. Может быть как отдельной, так и находится в массиве.
	// Также может вернуть пустой указатель
	virtual ISpdsAxisPtr GetAxis() const = 0;
	// Связывает указатель со строительной осью pLine типа axis_type_linear или axis_type_arc
	// Можно передать нулевой указатель, чтобы отвязать.
	virtual HRESULT SetCLine(ISpdsEntityCLine* pLine) = 0;
	// Связывает указатель со строительной осью (kind, index) в массиве pGrid.
	// Можно передать нулевой указатель, чтобы отвязать.
	virtual HRESULT SetGridCLine(ISpdsGrid* pGrid, GridAxisKind eKind, unsigned int iIndex) = 0;

	// Отдельная ось, с которой связан указатель, либо массив к которому принадлежит связанная ось
	// Может быть пустым
	virtual mcsWorkID GetConnectedID() const = 0;

	// Признак связи текста маркера указателя с текстом маркера связанной оси
	virtual bool GetAutoname() const = 0;
	virtual void SetAutoname(bool bAutoname) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Виды, разрезы, сечения...
//---------------------------------------------------------------------------

#define MCVS_SHEETUNDEFINED -1

struct McVSTypes
{
	enum Type
	{
		vstUndefined    = 0x00000000, // не определен
		vstView         = 0x00000001, // вид
		vstEView        = 0x00000002, // выносной вид
		vstCut          = 0x00000004, // разрез
		vstSection      = 0x00000008, // сечение
		vstLegend       = 0x00000010, // обозначение вида, разреза...
		vstBase         = 0x00000020, // обозначение базы
		vstTolerance    = 0x00000040, // допуск формы и расположения
		vstSurface      = 0x00000080, // поверхность
		vstDim          = 0x00000100, // размер
		vstOther        = 0x00000200, // другое

		vstVLegend      = vstLegend | vstView,     // обозначение вида
		vstCLegend      = vstLegend | vstCut,      // обозначение разреза
		vstSLegend      = vstLegend | vstSection,  // обозначение сечения
	};
	enum EraseStatus
	{
		esAlways   = 0, // Удалять всегда
		esNever    = 1, // Никогда не удалять
		esPrompt   = 2, // Спрашивать пользователя
	};
};
typedef McsArray<McVSTypes::Type, McVSTypes::Type> McVSTypeArray;

struct McTViewSection
{
	McsString stPrefix;     // Префикс
	McsString stLetter;     // Буква
	McsString stIndex;      // Индекс
	McsString stZone;       // Зона
	McsString stLScale;     // Масштаб вида, разреза...
	McsString stComment;
	int iSheet;             // Номер листа
	McVSTypes::Type eType;  // Тип объекта
	bool bTurned;           // Повернуто
	bool bUnfolded;         // Развернуто
	bool bRotated;          // Повернуто по часовой
	bool bRotated2;         // Повернуто против часовой

	McTViewSection()
	{
		iSheet = MCVS_SHEETUNDEFINED;
		eType = McVSTypes::vstUndefined;
		bTurned = bUnfolded = bRotated = bRotated2 = false;
	}
};

//---------------------------------------------------------------------------
struct IMcEntityVS : public IMcCdEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcEntityVS);
	IMCS_ENT_METHOD_DEFINITION(IMcEntityVS, IMcCdEntity, IMcDbEntity);

	virtual void getVSData(McTViewSection& data) const = 0;
	virtual LPCTSTR getPrefix() const
		{ return m_stPrefix; }
	virtual LPCTSTR getLetter() const
		{ return m_stLetter; }
	virtual LPCTSTR getIndex() const
		{ return m_stIndex; }
	virtual LPCTSTR getZone() const
		{ return m_stZone; }
	virtual int getSheet() const
		{ return m_iSheet; }

	virtual HRESULT setVSData(const McTViewSection& data) = 0;
	virtual void setPrefix(LPCTSTR st)
		{ writeEnabled(); m_stPrefix = st; }
	virtual void setLetter(LPCTSTR st)
		{ writeEnabled(); m_stLetter = st; }
	virtual void setIndex(LPCTSTR st)
		{ writeEnabled(); m_stIndex = st; }
	virtual void setZone(LPCTSTR st)
		{ writeEnabled(); m_stZone = st; }
	virtual void setSheet(int i)
		{ writeEnabled(); m_iSheet = (i < 1 ? MCVS_SHEETUNDEFINED : i); }

	virtual mcsPoint getZonePoint() const = 0;

protected:
	McsString m_stPrefix;
	McsString m_stLetter;
	McsString m_stIndex;
	McsString m_stZone;
	int m_iSheet;
};
typedef McsArray<IMcEntityVSPtr, IMcEntityVS*> IMcEntityVSPtrArray;

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcVSSorter - сортировка видов, разрезов, сечениий
//---------------------------------------------------------------------------
struct McTExistingLetters
{
	McsString stName;
	McsString stEnt;
	McsString stLegend;
};
typedef McsArray<McTExistingLetters, const McTExistingLetters&> McTExistingLettersArray;

//---------------------------------------------------------------------------
struct IMcVSSorter : public virtual IMcObject
{
	// Инициализация
	virtual HRESULT Init() = 0;
	virtual bool IsInitialized() = 0;
	// Очистка
	virtual void Free() = 0;

	// Сортировка
	virtual HRESULT Sort(bool bUpdate = true) = 0;
	// Исключение из дальнейшей обработки
	virtual void Exclude(const mcsWorkID& id) = 0;
	// Добавить объект в уже проинициализированный сортировщик
	virtual HRESULT Append(const mcsWorkID& id, const mcsWorkID& idPair) = 0;

	// Возвращает следующие букву и индекс для объекта типа eType
	virtual HRESULT GetNextAttributes(McsString& stLetter, McsString& stIndex, McVSTypes::Type eType) = 0;

	// Возвращает id обозначения с заданными атрибутами
	virtual HRESULT GetLegend(LPCTSTR stLetter, LPCTSTR stIndex, mcsWorkID& id) = 0;
	// Возвращает массив id видов, разрезов или сечений с заданными атрибутами
	virtual HRESULT GetEnts(LPCTSTR stLetter, LPCTSTR stIndex, mcsWorkIDArray& ids) = 0;

	// Возвращает уже проставленные на чертеже буквы
	virtual HRESULT GetLetters(McTExistingLettersArray& data) = 0;

	// Показывает диалог проставленных букв
	virtual HRESULT ShowLettersDialog(HWND hParent, McsString* pst = NULL) = 0;

	// Обновление зон и листов в видах, разрезах...
	virtual HRESULT UpdateZonesAndSheets() = 0;

};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Вид
//---------------------------------------------------------------------------
struct IMcEntityView : public IMcEntityVS
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcEntityView);

	virtual mcsPoint    getOrigin() const = 0;
	virtual double      getAngle() const = 0;
	virtual double      getLen() const = 0;
	virtual double      getTextSize() const = 0;
	virtual double      getSmallTextSize() const = 0;
	virtual McsString   getTextStyle() const = 0;

	virtual void setOrigin(const mcsPoint& pnt) = 0;
	virtual void setAngle(double r) = 0;
	virtual void setLen(double r) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setSmallTextSize(double r) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;

	// Используется только для конвертации из старых версий, никогда звать не нужно
	virtual void setDimScale(double rScale) = 0;
};

//---------------------------------------------------------------------------
struct IMcEntityEView : public IMcEntityVS
{
	enum Type
	{
		kCircle = 0,
		kRectangle = 1,
	};

	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcEntityEView);

	virtual mcsPoint    getCenter() const = 0;
	virtual mcsPoint    getCenterOCS() const = 0;
	virtual mcsPoint    getRack() const = 0;
	virtual mcsPoint    getRackOCS() const = 0;
	virtual double      getXRadius() const = 0;
	virtual double      getYRadius() const = 0;
	virtual mcsWorkID   getViewport() const = 0;
	virtual IMcEntityEView::Type getType() const = 0;

	virtual void setCenter(const mcsPoint& pnt) = 0;
	virtual void setCenterOCS(const mcsPoint& pnt) = 0;
	virtual void setRack(const mcsPoint& pnt) = 0;
	virtual void setRackOCS(const mcsPoint& pnt) = 0;
	virtual void setXRadius(double r) = 0;
	virtual void setYRadius(double r) = 0;
	virtual void setViewport(const mcsWorkID& id) = 0;
	virtual void setType(IMcEntityEView::Type type) = 0;

	virtual void setDrawRack(bool bDrawRack) = 0;
	virtual bool getContour(mcsPolyline& pline, mcsPoint* pPnt = NULL) const = 0;
	virtual bool getContourOCS(mcsPolyline& pline, mcsPoint* pPnt = NULL) const = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Разрез/сечение
//---------------------------------------------------------------------------
struct IMcEntitySection : public IMcEntityVS
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcEntitySection);

	virtual void        getPoints(mcsPoint3dArray& points) const = 0;
	virtual void        getPointsOCS(mcsPoint3dArray& points) const = 0;
	virtual double      getLen() const = 0;
	virtual double      getTextSize() const = 0;
	virtual double      getSmallTextSize() const = 0;
	virtual McsString   getTextStyle() const = 0;
	virtual int         getDir() const = 0;
	virtual bool        isSection() const = 0;
	virtual bool        isSheetOnStart() const = 0;
	virtual bool        isDrawSectionLine() const = 0;
	virtual double      getBulge() const = 0;

	virtual void setPoints(const mcsPoint3dArray& points) = 0;
	virtual void setPointsOCS(const mcsPoint3dArray& points) = 0;
	virtual void setLen(double r) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setSmallTextSize(double r) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;
	virtual void setDir(int i) = 0;
	virtual void setSection(bool b) = 0;
	virtual void setSheetOnStart(bool b) = 0;
	virtual void setDrawSectionLine(bool b) = 0;
	virtual void setBulge(double rBulge) = 0;

	// Используется только для конвертации из старых версий, никогда звать не нужно
	virtual void setDimScale(double rScale) = 0;

	virtual HRESULT setParam(IN int iIndex, IN const McGeometryParam& param) = 0;
	virtual HRESULT getParam(IN int iIndex, OUT McGeometryParam& param) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Обозначение видов, разрезов...
//---------------------------------------------------------------------------
struct IMcEntityVSLegend : public IMcEntityVS
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcEntityVSLegend);

	virtual mcsPoint    getOrigin() const = 0;
	virtual double      getTextSize() const = 0;
	virtual double      getSmallTextSize() const = 0;
	virtual LPCTSTR     getLScale() const = 0;
	virtual LPCTSTR     getComment() const = 0;
	virtual McsString   getTextStyle() const = 0;
	virtual McVSTypes::Type getType() const = 0;
	virtual bool        isTurned() const = 0;
	virtual bool        isUnfolded() const = 0;
	virtual bool        isRotated() const = 0;
	virtual bool        isRotated2() const = 0;

	virtual void setOrigin(const mcsPoint& pnt) = 0;
	virtual void setTextSize(double r) = 0;
	virtual void setSmallTextSize(double r) = 0;
	virtual void setLScale(LPCTSTR st) = 0;
	virtual void setComment(LPCTSTR st) = 0;
	virtual void setTextStyle(LPCTSTR st) = 0;
	virtual void setType(McVSTypes::Type type) = 0;
	virtual void setTurned(bool b) = 0;
	virtual void setUnfolded(bool b) = 0;
	virtual void setRotated(bool b) = 0;
	virtual void setRotated2(bool b) = 0;

	// Используется только для конвертации из старых версий, никогда звать не нужно
	virtual void setDimScale(double rScale) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Местный разрез
//---------------------------------------------------------------------------
struct IMcBrokenOutSection : public IMcCdEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcBrokenOutSection);
	IMCS_STD_METHOD_DEFINITION(IMcBrokenOutSection, IMcCdEntity);

	virtual mcsPoint getCenter() const = 0;
	virtual mcsVector getXAxis() const = 0;
	virtual double getXRadius() const = 0;
	virtual double getYRadius() const = 0;
	virtual bool isCircle() const = 0;

	virtual void setCenter(const mcsPoint& pnt) = 0;
	virtual void setXAxis(const mcsVector& vec) = 0;
	virtual void setXRadius(double r) = 0;
	virtual void setYRadius(double r) = 0;
	virtual void setCircle(bool b) = 0;

	virtual HRESULT UpdateSection() = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcPolylineBasedEntity
//---------------------------------------------------------------------------
struct IMcPolylineBasedEntity : virtual public IMcCdEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcPolylineBasedEntity);
	IMCS_ENT_METHOD_DEFINITION(IMcPolylineBasedEntity, IMcCdEntity, IMcDbEntity);

	// Direct Access to internal Polyline (in OCS)
	// Returned pointer is address of internal mcsPolyline object! Don't try to delete him! 
	virtual mcsPolyline* GetPolyline() = 0;

	// Associated link with prototype-drawing-polyline	
	virtual HRESULT SetAssociation(const mcsWorkID& idAssocObj) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Площади, форма помещения
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////

struct ISpdsEntitySquare : public virtual IMcPolylineBasedEntity, public virtual IMcAreaEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(ISpdsEntitySquare);
	IMCS_STD_METHOD_DEFINITION3(ISpdsEntitySquare, IMcPolylineBasedEntity, IMcAreaEntity);	

	// area
	virtual bool getArea(double& area) const = 0;
	virtual bool getArea(McsString &str) const = 0;		//formatted

	// perimeter
	virtual bool getPerimetr(double& perimetr) const = 0;
	virtual bool getShowBorder() const = 0;
	virtual bool setShowBorder(bool bShow) = 0;

	// text query
	virtual mcsPoint	getTextPosition() const = 0;	
	virtual McsString	getTextUp(bool bNoDefault = false) const = 0;
	virtual McsString	getTextDown() const = 0;
	virtual McsString	getTextForward() const = 0;

	// text edit
	virtual bool		setTextPosition(const mcsPoint& pnt) = 0;	
	virtual bool		setTextUp(LPCTSTR txt) = 0;
	virtual bool		setTextDown(LPCTSTR txt) = 0;
	virtual bool		setTextForward(LPCTSTR txt) = 0;

	// virtual height
	virtual bool		setVirtualHeight(double height) = 0;
	virtual double		getVirtualHeight() const = 0;

	// dim scale
	virtual bool		setDimScale(double rDimScale) = 0;
	virtual double		getDimScale() const = 0;

	// set area border

	//first area only (deprecated)
	//if used, all areas except first will be removed
	virtual bool		set( const mcsPolyline& pline ) = 0; //DEPRECATED
	virtual bool		set( const mcsPolylineArray& plines, bool bWithLoop = false ) = 0; //DEPRECATED

	//all areas
	//first pline in plines is outer positive contour, other plines are subtracted holes
	virtual bool		addLoops( const mcsPolylineArray& plines ) = 0;
	//iArea - area number, starting from 0
	virtual bool		setLoops( int iArea, const mcsPolylineArray& plines ) = 0;
	virtual void		clearLoops( int iArea ) = 0; //entirely remove area iArea

	//clears all loops
	virtual void		clearLoops() = 0;

	// get area border

	//first area only (deprecated)
	virtual int					getNumLoops() const = 0; //DEPRECATED
	virtual mcsPolylineArray	getLoops() const = 0; //DEPRECATED

	// get all polylines
	typedef McsArray<mcsPolylineArray, const mcsPolylineArray&> mcsPolylineArrayArray;
	virtual mcsPolylineArrayArray getAllLoops() const = 0; //DEPRECATED
	//all areas
	virtual int					getAreasCount() const = 0;
	//iArea - area number, starting from 0
	virtual int					getAreaLoopsCount(int iArea) const = 0;
	virtual mcsPolylineArray	getAreaLoops(int iArea) const = 0;
};

enum QuarterDrawType
{
	QDT_MARKER		= 0x1,
	QDT_UNDERLINED	= 0x2,
	QDT_SIMPLE		= 0x4
};

enum QuarterType
{
	QT_WORKING	= 0x1,
	QT_LIVING	= 0x2,
	QT_DOMESTIC	= 0x4,
	QT_OFFICE	= 0x8,
	QT_OTHER	= 0x100
};

enum RoomDrawType
{
	LABEL_ROOM_NAME_AND_AREA,
	LABEL_ROOM_NUMBER,
	LABEL_FLOORING,
	LABEL_UNKNOWN,
	LABEL_AREA,
	LABEL_ROOM_NAME_AND_FINISHED_AREA,
	LABEL_FINISHED_AREA,
};

enum QuarterMsrType
{
	QMT_CLEAR	= 0x1,
	QMT_FULL	= 0x2,
	QMT_CONTOUR = 0x4,
	QMT_RECT	= 0x8,		
	QMT_PLINE	= 0x10,
	QMT_EMPTY	= 0x20
};

struct ISpdsEntityQuarters : public virtual ISpdsEntitySquare
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(ISpdsEntityQuarters);
	IMCS_STD_METHOD_DEFINITION(ISpdsEntityQuarters, ISpdsEntitySquare);

	virtual void		setNumber(LPCTSTR number) = 0;
	virtual McsString	getNumber() const = 0;

	virtual void		setDescription(LPCTSTR description) = 0;
	virtual McsString	getDescription() const = 0;

	virtual bool		getArea(double &fullArea) const = 0;
	virtual bool		getArea(McsString &fullArea) const = 0;

	virtual void		setHeight(double rHeight) = 0;
	virtual double		getHeight()	const = 0;

	virtual void		setQType(QuarterType type) = 0;
	virtual QuarterType	getQType() const = 0;

	virtual void			setQDrawType(QuarterDrawType type) = 0;
	virtual QuarterDrawType	getQDrawType() const = 0;

	virtual void		setOtherQType(LPCTSTR otherQType) = 0;
	virtual McsString	getOtherQType() const = 0;

	virtual void		setFloorType(LPCTSTR floorType) = 0;
	virtual McsString	getFloorType() const = 0;

	virtual void		setPlasterWidth(double rPlasterWidth) = 0;
	virtual double		getPlasterWidth() const = 0;

	virtual void		setCeilingType(LPCTSTR ceilingType) = 0;
	virtual McsString	getCeilingType() const = 0;

	virtual void		setExtraData(LPCTSTR extraData) = 0;
	virtual McsString	getExtraData() const = 0;

	// unattached area position control
	// used only with QuarterDrawType::QDT_MARKER
	virtual mcsPoint	getAreaPoint(bool bAttached = false) const = 0;
	virtual void		setAreaPoint(const mcsPoint& point) = 0;
	virtual void		setAreaOffset(const mcsVector& offset) = 0;
};

// Структура, предоставляющая информацию о маркере помещения.
struct McRoomStdMarkerInfo
{
	RoomDrawType	markerType;
	mcsPoint3d		markerLocation;
};
typedef McsArray<McRoomStdMarkerInfo, const McRoomStdMarkerInfo&> McRoomStdMarkerInfoArray;

struct IMcRoom: public virtual ISpdsEntitySquare
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcRoom);
	IMCS_STD_METHOD_DEFINITION(IMcRoom, ISpdsEntitySquare);

	virtual void		setNumber(LPCTSTR number) = 0;
	virtual McsString	getNumber() const = 0;

	virtual void		setDescription(LPCTSTR description) = 0;
	virtual McsString	getDescription() const = 0;

	virtual bool		getArea(double &fullArea) const = 0;
	virtual bool		getArea(McsString &fullArea) const = 0;

	virtual void		setHeight(double rHeight) = 0;
	virtual double		getHeight()	const = 0;

	virtual void		setFloor(LPCTSTR floorType) = 0;
	virtual McsString	getFloor() const = 0;

	virtual void		setGroup(LPCTSTR group_room) = 0;
	virtual McsString	getGroup() const = 0;

	virtual void		setCategory(LPCTSTR category) = 0;
	virtual McsString	getCategory() const = 0;

	virtual void		setAppartment(LPCTSTR appartment) = 0;
	virtual McsString	getAppartment() const = 0;

	virtual void		setDrawBoundary(bool drBound) = 0;
	virtual bool		isDrawBoundary() = 0;

	//	virtual void		setPlasterWidth(double rPlasterWidth) = 0;
	//	virtual double		getPlasterWidth() const = 0;

	virtual void		setLabelFlooring(LPCTSTR labelFlooring) = 0;
	virtual McsString	getLabelFlooring() const = 0;

	// unattached area position control
	// used only with QuarterDrawType::QDT_MARKER
	virtual mcsPoint	getAreaPoint(bool bAttached = false) const = 0;
	virtual void		setAreaPoint(const mcsPoint& point) = 0;
	virtual void		setAreaOffset(const mcsVector& offset) = 0;
	virtual double		getAreaWithOffset(double thickness) = 0;
	virtual double		getPerimetrWithOffset(double thickness, bool bExcludeDoorways = false) = 0;
	// Вычисляет периметр (суммарную ширину) дверных проемов в помещении.
	virtual double		getPerimetrForDoorwaysOnly() = 0;

	//	virtual mcsWorkIDArray getArrayOfApertures() = 0; 
	virtual HRESULT		onUpdateContur() = 0;

	virtual const McsEntityGeometry* getEntHatch() = 0;
	virtual void		setEntHatch(const McsEntityGeometry* htch) = 0;
	virtual bool		displayHatch() = 0;

	virtual mcsBoundBlock getBoudBlockMarker(RoomDrawType drType) = 0;

	virtual mcsWorkIDArray& getMarkersFromBase() = 0;
	virtual MCSDoubleArray getMarkersMCSUID() = 0;
	virtual HRESULT setMarkersFromBase(const mcsWorkIDArray& extArray, const mcsDoubleArray& uids) = 0;

	virtual mcsVector3dArray getMarkersOffsets() = 0;
	virtual mcsMatrix3d getSummaryTransform() = 0;
	virtual void setSummaryTransform(const mcsMatrix3d& nTr) = 0;

	virtual HENHMETAFILE GetMarkerImage(RoomDrawType rDrTp, int hg, int wd) = 0;

	virtual bool rebuildContour() = 0;
	virtual void verificationIncludedMarkers() = 0;

	/// <summary>
	/// Проверяет, имеет ли помещение стандартный маркер указанного типа.
	/// </summary>
	/// <param name="markerType">Тип маркера.</param>
	/// <returns>Значение true, если помещение имеет стандартный маркер указанного типа, false в противном случае.</returns>
	virtual bool hasStandardMarker(RoomDrawType markerType) const = 0;
	/// <summary>
	/// Получает информацию обо всех стандартных маркерах помещения.
	/// </summary>
	/// <returns>Массив структур, содержащих информацию о стандартном маркере.</returns>
	virtual McRoomStdMarkerInfoArray getStandardMarkers() const = 0;
	/// <summary>
	/// Получает количество стандартных маркеров помещения.
	/// </summary>
	/// <returns>Количество стандартных маркеров помещения.</returns>
	virtual int getStandardMarkersCount() const = 0;
	/// <summary>
	/// Получает координаты стандартного маркера указанного типа на чертеже.
	/// </summary>
	/// <param name="markerType">Тип маркера.</param>
	/// <param name="pntMarkerLocation">Ссылка на объект для координат маркера в мировой системе координат.</param>
	/// <returns>
	/// Значение true и координаты маркера через объект pntMarkerLocation, если маркер указанного типа существует, в
	/// противном случае значение false.
	/// </returns>
	virtual bool getStandardMarkerLocation(RoomDrawType markerType, OUT mcsPoint3d& pntMarkerLocation) const = 0;
	/// <summary>
	/// Задаёт координаты стандартного маркера указанного типа на чертеже.
	/// </summary>
	/// <param name="markerType">Тип маркера.</param>
	/// <param name="pntMarkerLocation">Новые координаты маркера в мировой системе координат.</param>
	/// <returns>
	/// Значение true, если маркер указанного типа существует, в противном случае значение false.
	/// </returns>
	virtual bool setStandardMarkerLocation(RoomDrawType markerType, const mcsPoint3d& pntMarkerLocation) = 0;
	/// <summary>
	/// Добавляет стандартный маркер помещения с заранее заданными координатами на чертеже.
	/// </summary>
	/// <param name="markerType">Тип маркера.</param>
	/// <param name="pntMarkerLocation">Координаты маркера в мировой системе координат.</param>
	/// <returns>
	/// <para>Если значение параметра markerType равно LABEL_UNKNOWN, матод возвращает значение false.</para>
	/// <para>Если маркер уже существует, матод возвращает значение false.</para>
	/// <para>В остальных случаях матод возвращает значение true.</para>
	/// </returns>
	virtual bool addStandardMarkerAtLocation(RoomDrawType markerType, const mcsPoint3d& pntMarkerLocation) = 0;
	/// <summary>
	/// Удаляет стандартный маркер помещения.
	/// </summary>
	/// <param name="markerType">Тип маркера.</param>
	/// <returns>Значение true, если маркер укзанного типа существует, false в противном случае.</returns>
	virtual bool removeStandardMarker(RoomDrawType markerType) = 0;
	/// <summary>
	/// Удаляет все стандартные маркеры помещения.
	/// </summary>
	virtual void removeAllStandardMarkers() = 0;

	/// <summary>
	/// Получает площадь помещения с учётом отделки стен.
	/// </summary>
	virtual double getFinishedArea() = 0;
};

typedef McsArray<IMcRoomPtr, IMcRoom*> mcRoomsArray;
