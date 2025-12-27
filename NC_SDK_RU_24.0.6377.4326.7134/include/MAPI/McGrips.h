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

#include "IMcObjects.h"
#include "IMcSymbols.h"
#include "McAPIs.h"

#define MCGRIP_COLOR_BASE 0x00FFBF00// Основной цвет интеллектуальных грипов
#define MCGRIP_COLOR_ADD  0x0000FF00// Добавление чего либо
#define MCGRIP_COLOR_DEL  0x000000FF// Удаление чего либо
#define MCGRIP_COLOR_ADD_COPY  0x00AFBF00// Добавление копии
//---------------------------------------------------------------------------
// Придёт onMoveGripPointsAt() в обычном порядке
struct MECHCTL_API McGripBLAddLeader : public McGripData
{
	McGripBLAddLeader(const mcsPoint& pnt, HANDLE handle, const mcsPoint& pntBase, double rRotation);
};

//---------------------------------------------------------------------------
// Если задан handle, то вызовет onMoveGripPointsAt(), иначе IMcArrowsExtension::SetArrow()
struct MECHCTL_API McGripArrowMenu : public McGripData
{
	IMcArrowsExtensionPtr m_pAE;
	int m_idArrow;

	McGripArrowMenu(const mcsPoint& pnt, IMcArrowsExtension* pAE, int idArrow, HANDLE handle = NULL);
	virtual HRESULT GetMenu(mcsCtxMenuItemArray& menu);
	virtual HRESULT OnCommand(UINT id);
};

//---------------------------------------------------------------------------
// Придёт onMoveGripPointsAt() в обычном порядке
struct MECHCTL_API McGripMirror : public McGripData
{
	IMcEntityPtr m_pEnt;

	McGripMirror(const mcsPoint& pnt, HANDLE handle, IMcEntity* pEnt, double rAngle, LPCTSTR stTooltip = NULL);
	virtual HRESULT OnCommand(UINT id);
};

//---------------------------------------------------------------------------
// Придёт onMoveGripPointsAt(), выравнивание будет передано в параметре iFlags
struct MECHCTL_API McGripTextAlign : public McGripData
{
	IMcEntityPtr m_pEnt;
	McsHorizTextAlignEnum m_align;

	McGripTextAlign(const mcsPoint& pnt, HANDLE handle, IMcEntity* pEnt, McsHorizTextAlignEnum align, double rDirection);
	virtual HRESULT OnCommand(UINT id);
};

//---------------------------------------------------------------------------
// Придёт onMoveGripPointsAt(), в нём оперируем McGripAttachTo::getPoint() и McGripAttachTo::getParam()
struct MECHCTL_API McGripAttachTo : public McGripData
{
	double m_rDAngle;
	McGeometryParam m_param;
	bool m_isInteractive;
	mcsMatrix m_ocs;

	McGripAttachTo(const mcsPoint& pnt, HANDLE handle, const mcsMatrix& ocs, Appearance appearance = kgaStandard, double rRotation = 0, McGripData::Type type = McGripData::kgtSimple, const mcsPoint* ppntAlt = NULL, double rDAngle = 0, LPCTSTR stComment = NULL, COLORREF color = MCS_ENTCOLOR_BYCONTEXT);
	mcsPoint getPoint(const mcsVector& offset);
	McGeometryParam getParam();
	virtual HRESULT ActiveEnt(const EM_Entity& ent) override;
};

//---------------------------------------------------------------------------
// Умная ручка на контуре, умеющая циклически переключаться между доступными режимами работы аналогично платформенной полилинии
// и выполнять действие, соответствующее текущему режиму.
//---------------------------------------------------------------------------
// Придёт onMoveGripPointsAt(), в нем dynamic_cast<McContourSmartGripData*>,
// получаем индекс контура с помощью GetContourIndex, берем контур, накладываем матрицу трансформации в мировые координаты и завем SmartMouseMove.
// Если SmartMouseMove вернул true, то сохраняем контур в объекте
//---------------------------------------------------------------------------
enum McContourGripMode
{
	kcgmNormalStretch = 0,
	kcgmAddVertex,
	kcgmRemoveVertex,
	kcgmLine2Arc,
	kcgmArc2Line,
};
struct MECHCTL_API McContourSmartGripData : public McGripData
{
	virtual int  GetContourIndex() const { return -1; }
	virtual int  GetSegmentIndex() const { return -1; }
	virtual int  GetVertexIndex()  const { return -1; }
	virtual bool SmartMouseMove(mcsPolyline& contour, const mcsVector3d& offset) { return false; }
};
// Метод для создания умных ручек типа McContourSmartGripData
// contour     - контур из объекта в мировых кооординатах
// idxContour  - уникальный индекс контура, назначается/контролируется в объекте
// idStartGrip - стартовое значение идентификатора создаваемых ручек
// grips       - содержит указатели на McContourSmartGripData
MECHCTL_API bool GetSmartGrips4Contour(const mcsPolyline& contour, int idxContour, int idStartGrip, OUT McGripDataPtrArray& grips);
