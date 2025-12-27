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

#include "DynLoadMacro.h"
#include "MCSTempl.h"
#include "MCSGeometry.h"

IMCS_DECL_INTERFACE(IMechWizardCreator,	"00000002-0010-AAAA-AAAA-050B00000000")

//////////////////////////////////////////////////////////////////////////
// автоматически создать параметрический объект по его графическому представлению
struct IMechWizardCreator : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMechWizardCreator);
	IMCS_STD_METHOD_DEFINITION(IMechWizardCreator, IMcObject);

	virtual HRESULT Create (bool fCreateExtraObject, const mcsWorkIDArray* pReadyObjects = NULL, bool fAskForSelect = true)	= 0;	// TRUE - попросить селектировать вектора; FALSE - взять все (без запроса)
	virtual HRESULT CreateR(bool fCreateExtraObject, const mcsWorkIDArray* pReadyObjects = NULL, bool fAskForSelect = true, LPCTSTR stPrompt = NULL)	= 0;	// TRUE - попросить селектировать вектора; FALSE - взять все (без запроса)
	virtual LPCTSTR GetDrawCode()	= 0;
	virtual HRESULT GetGrips(IMcsStreamPtr &pStream)	= 0;
	virtual HRESULT GetPreview(HENHMETAFILE &pPreview)	= 0;
	virtual HRESULT AskPreview(HENHMETAFILE &pPreview)	= 0;
	virtual mcsPoint GetOrigin() = 0;
};

IMCS_DECL_INTERFACE(IMechWizard,	"00000001-0010-AAAA-AAAA-050B00000000")

//////////////////////////////////////////////////////////////////////////

struct McInternalContour
{
	// здесь хранится некоторая информация для повторного получения внутреннего контура, 
	// предполагается, что геометрии изменились, и где теперь внутренния точка неизвестно.
	mcsIntArray maCurves; // номера геометрий из которых взялись сегменты, для формирования результата(некоторые индексы могут повторятся.)
	mcsBoolArray maDirections; // направления по которому в прошлый раз шло решение.
	bool mbClockwise; // направления обхода результата.
};

//---------------------------------------------------------------------------
struct IMcGeometryFilter
{
	// Позволяет переопределить алогоритм, по которому с объектов берется геометрия.
	// В массиве idsObjects находятся идентификаторы объектов, по которым предполагается строить контур.
	// Задача метода собрать с этих объектов геометрию, которая должна участвовать в формировании контура,
	// и сложить её в массив geometry.
	// Если pexarr != NULL, то в него нужно положить те идентификаторы объектов из idsObjects, с которых
	// была использована хотя бы какая-то геометрия.
	virtual HRESULT GetGeometry(const mcsWorkIDArray& idsObjects, OUT mcsGeomEntArray& geometry, OUT OPTIONAL mcsWorkIDArray* pexarr) = 0;
};

//////////////////////////////////////////////////////////////////////////
// автоматически создать параметрический объект по его графическому представлению
struct IMechWizard: public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMechWizard);
	IMCS_STD_METHOD_DEFINITION(IMechWizard, IMcObject);

	virtual HRESULT GetInternalContour(
		OUT mcsPolyline& pline,
		const mcsGeomEntArray& ents,
		const mcsPoint3d& inPnt,
		double rTol,
		mcsIntArray* parSkipLineGost = NULL,
		bool bTryPlmAlgorithm = true) = 0; // pass false to use (old) internal on-board algorithm

	virtual HRESULT JoinContours(OUT mcsPolyline& pline, const mcsGeomEntArray& ents, double rTol, mcsIntArray*  parSkipLineGost = NULL) = 0;

		// return all separate contours from ents
	virtual HRESULT JoinContours(OUT mcsPolylineArray& plines, const mcsGeomEntArray& ents, double rTol, mcsIntArray*  parSkipLineGost = NULL) = 0;
	virtual HRESULT GetArrayUsedGeomtries(OUT mcsIntArray& aIndices) = 0;

	// Метод GetContoursByPickPoint позволяет получить наименьший контур на чертеже, в который
	// входит точка pnt.
	//
	// Если bOnlyExternLoop == false, то в дополнению к внешнему контуру определяются все внутренние
	// замкнутые контура, которые находятся целиком внутри внешнего контура.
	//
	// pexarr - указатель на массив, в который будут помещены ID объектов, участвовавших в
	// формировании внешнего контура.
	//
	// Если передан указатель на GetGeometryProc, то она будет использована для получения
	// с объектов той геометрии, которую следует использовать при определении контуров.
	// Если же такая функция не задана, то используется геометрия из функции IMcDbEntity::explode().
	// Штриховки и объекты оформления (IID_DesignElement) игнорируются в любом случае.
	// Функция GetGeometryProc должна также поместить в переданный ей массив pexarr ID тех объектов,
	// геометрию которых она использовала для формирования массива geometry.
	//
	// rTol определяет наибольшее расстояние между точками, при котором они считаются одной и той же точкой.
	//
	// bUseEllipses включает/отключает учет эллиптических кривых при нахождении контура.
	// Если отключено, то геометрические сегменты, отличные от линий и концентрических дуг, могут быть проигнорированы.
	//
	// bUseGetInternalContourOpt включает использование оптимизированного алгоритма (рекомендуется).
	// Кроме того, этот алгоритм лучше работает с самопересекающимися полилиниями.
	virtual HRESULT GetContoursByPickPoint(
		IN const mcsPoint& pnt,
		IN bool bOnlyExternLoop,
		OUT mcsPolylineArray& contours,
		IN OPTIONAL double rTol = DEF_TOL,
		OUT OPTIONAL mcsWorkIDArray* pexarr = NULL,
		IN bool bUseEllipses = false,
		IN bool bUseGetInternalContourOpt = false,
		IN IMcGeometryFilter* pGeomFilter = NULL) = 0;

		// повторного получения внутреннего контура.
	virtual HRESULT GetInternalContourRepetition(OUT mcsPolyline& pline, const mcsGeomEntArray& ents, const McInternalContour& pol, IN double rTol) = 0;
	virtual HRESULT GetLastContourData(OUT McInternalContour& pol) = 0;
	virtual HRESULT RecalculateIndices(IN OUT McInternalContour& pol) = 0;
};
//////////////////////////////////////////////////////////////////////////
