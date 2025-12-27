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

#include "mccurv3d.h"

//==================================================================================================
struct McGeCurveIndex
{
	int idxCurve;
	int idxSubCurve; // -1 usually means whole curve.

	MCGEL_API McGeCurveIndex(int idxCurve = -1, int idxSubCurve = -1);
	MCGEL_API McGeCurveIndex(const McGeCurveIndex& offidx);
	MCGEL_API McGeCurveIndex& operator=(const McGeCurveIndex& offidx);
	MCGEL_API bool operator == (const McGeCurveIndex& other) const;
};

typedef McsArray<McGeCurveIndex> McGeCurveIndicesArr;
typedef McsMapEx<int, int, double, double> mcsMapIntToDbl;
//==================================================================================================

template<> __inline UINT __stdcall McsHashKey(const McGeCurveIndex& key)
{
	__int64 i64 = ((__int64)key.idxCurve << 32) | ((__int64)key.idxSubCurve & 0xFFFFFFFF);
	return McsHashKey<__int64>(i64);
}
//==================================================================================================

struct McGeCurve3dOffsetData
{
	// Блок входных данных ...........................................

	double                 distance;
	McGeVector3d           planeNormal;
	McGe::OffsetCrvExtType extensionType;
	McGeTol                tolerance;

		// 09.03.2015
		// Если заполнена любая пара SegIdx->DistVal в мапе ниже тогда для этого сегмента будет
		// использовано именно это расстояние вместо общего значения 'distance'.
		// Соответственно, если для какого-то сегмента нет данных в мапе, для него будет 
		// использовано общее расстояние смещения.
		//
		// (!)
		// Смещение от контура с переменным расстоянием нормально работает только если контур не
		// требует дополнительных скруглений.
	mcsMapIntToDbl         idxSegToDist;

	bool _bLockExtensions; // используется для блокировки внешних алгоритмов, для системных целей

	bool bUseCommonAlgoForAllCases; // использовать общий алгоритм для всех входных данных

		// идентификатор общего алгоритма построения эквидистанты
		// 1 - по умолчанию (08.2015, 11.2015)
		// 2 - доработанный для эллипсов и сплайнов (01.2016)
		// 3 -
	int  idCmnAlgo;

	// Блок выходных данных ..........................................

	McsArray<McGeCurve3d*> offsetCurves;

		// Отображение индекса каждой исходной кривой на набор индексов кривых смещения в 'offsetCurves'
		// Пример: на входе список из двух кривых.
		// На выходе две составные кривые, одна от первой кривой, вторая - от второй.
		// В первой два сегмента, во второй - три.
		// Отображение в этом случае может иметь вид:
		// 0 -> Arr( {0, 0}, {0, 1} )
		// 1 -> Arr( {1, 0}, {1, 1}, {1, 2} )
		// Т.е. от первой кривой построилась составная кривая (индекс 0) из двух сегментов (индексы 0 и 1)
		// А от второй кривой построилась другая составная кривая (индекс 1) из трех сегментов (индексы 0, 1 и 2)
	McsMapEx<int, int, McGeCurveIndicesArr, const McGeCurveIndicesArr&> assoc;

	MCGEL_API void Clear();
	MCGEL_API void ClearOut();

	MCGEL_API McGeCurve3dOffsetData(
		IN OPTIONAL double distance = 0,
		IN OPTIONAL McGe::OffsetCrvExtType extensionType = McGe::kFillet,
		IN OPTIONAL const McGeVector3d& planeNormal = McGeVector3d::kZAxis,
		IN OPTIONAL const McGeTol& tolerance = McGeContext::gTol,
		IN OPTIONAL mcsMapIntToDbl* pIdxToDist = NULL);

	MCGEL_API McGeCurve3dOffsetData(const McGeCurve3dOffsetData& offd);
	MCGEL_API McGeCurve3dOffsetData& operator= (const McGeCurve3dOffsetData& offd);

	MCGEL_API ~McGeCurve3dOffsetData();

	MCGEL_API double getSeg2Ofs(int idx); // returns an offset value for the specified segment
	MCGEL_API double getMinSeg2Ofs(IN const mcsIntArray& indices); // returns minimal offset value for specified segments
	MCGEL_API bool   isZeroDistance(double tol); // returns true if the specified distance is nearly 0 with the given tolerance
};
//==================================================================================================
class MCGEL_API McGeCompositeCurve3d : public McGeCurve3d
{
public:
	McGeCompositeCurve3d ();
	McGeCompositeCurve3d (const McGePVoidArray& curveList);
	McGeCompositeCurve3d (const McGePVoidArray& curveList, const McGeIntArray& isOwnerOfCurves);
	McGeCompositeCurve3d (const McGeCompositeCurve3d& compCurve);

		// Definition of trimmed curve
	virtual void getCurveList(McGePVoidArray& curveList) const;

		// Set methods
	virtual McGeCompositeCurve3d& setCurveList(const McGePVoidArray& curveList);
	virtual McGeCompositeCurve3d& setCurveList(const McGePVoidArray& curveList, const McGeIntArray& isOwnerOfCurves);

		// Convert parameter on composite to parameter on component curve and vice-versa.
	virtual double globalToLocalParam ( double param, int& segNum ) const; 
	virtual double localToGlobalParam ( double param, int segNum ) const; 

	// McGe only !!!
	virtual bool mcs_intersectWithPlanarEnt (const McGePlanarEnt& plane, OUT McGePoint3dArray& points, const McGeTol& tol = McGeContext::gTol) const;

	bool mcs_intersectWithPlanarEntEx (
			const McGePlanarEnt&         plane,
			OUT McGePoint3dArray&        points,
			const McGeTol&               tol = McGeContext::gTol,
			OUT OPTIONAL mcsDoubleArray* pPointParams = NULL) const;

	virtual void mcs_getTrimmedOffsetEx(McGeCurve3dOffsetData& offd) const;

		// Assignment operator.
	virtual McGeCompositeCurve3d& operator = (const McGeCompositeCurve3d& compCurve);
};
//==================================================================================================

	// оптимизированные методы получения расстояния между дуговыми сегментами, 
	// лежащими в одной плоскости, внутри компланарность не проверяется
MCGEL_API double mcgeDist_CA_CA_coplanar(
	const McGeCircArc3d&      CA1,
	const McGeCircArc3d&      CA2,
	const McGeTol&            tol,
	OUT OPTIONAL McGePoint3d* pPtOnCA1 = NULL,
	OUT OPTIONAL McGePoint3d* pPtOnCA2 = NULL);

	// оптимизированный метод получения расстояния между линейным отрезком и 
	// круговой дугой, лежащими в одной плоскости, компланарность внутри не проверяется
MCGEL_API double mcgeDist_LS_CA_coplanar(
	const McGeLineSeg3d&      LS,
	const McGeCircArc3d&      CA,
	const McGeTol&            tol,
	OUT OPTIONAL McGePoint3d* pPtOnLS = NULL,
	OUT OPTIONAL McGePoint3d* pPtOnCA = NULL);

	// Проверяет планарность списка кривых.
	// Также возвращает вычисленную плоскость.
	// NOTE: Если указан параметр pPlaneThickness, то плоскость вычислится в любом случае
	// и в *pPlaneThickness будет возвращена т.н. "толщина" плоскости.
	// (если толщина в пределах tol.equalPoint(), планарность подтверждается)
MCGEL_API bool isCurvesListPlanar(
	const McGeCurve3d**  ppCurves,
	int                  nCurves,
	OUT McGePlane&       plane,
	const McGeTol&       tol,
	OUT OPTIONAL double* pPlaneThickness = NULL);
