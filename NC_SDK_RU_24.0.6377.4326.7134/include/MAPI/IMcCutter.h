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
#include "IMcObjects.h"
#include "IMcStream.h"
#include "cmnmacro.h"

struct mcsFilter;
//////////////////////////////////////////////////////////////////////////

// вырезание векторов по контуру
struct CutterParams
{
	bool  fCreateInside;   // создавать ли entities, лежащие внутри контура
	bool fCreateOutside;  // создавать ли остающиеся куски от удаляемых entities
	bool  fDelCoincident;  // true - удалять накладывающиеся элементы
	bool  fDelReverse; // по умолчанию не используется. использовать со флагом fDelCoincident = false.
	// при склейки стен используется функция CutPerimeter, при склейки стен границы стираются,
	// если стены касаются внешним образом. Удаляются общие границы, в которых направления обхода не совпадают.

	//DWORD dwSupportTypes;  // типы рассматриваемых объектов
	// при передаче массива объектов действительны параметры:
	//bool fWithoutClone;			// использовать входные объекты в качестве выходные, не создавая копии
	//bool fDeleteBrokenObject;   // удалять разрезанные Contour объекты, вызывается delete! - не использовать для открытых Autocad
	bool  fWatchSkipGost;  // true - не рассматривать объекты с типами линий, заданными в arSkipLineGost
	mcsIntArray  arSkipLineGost; // объекты с данным гостом не рассматриваются
	mcsTol mTol; // это погрешность с которой работает ICutter в реализации OperatePolylinesEx.

	// флаг используется только в функции: HRESULT Cut(const McsEntityGeometry&, mcsFilter&);
	bool fSkipDesignElement; // по умолчанию объекты DesignElement не режутся.


	CutterParams() 
	{
		fCreateInside  = true;
		fCreateOutside = true;
		fDelCoincident = false;
		fWatchSkipGost = false;
		fDelReverse = false;
		fSkipDesignElement = true;
  // 3: "GOST2.303 3"
  // 4: "GOST4", "GOST2.303 5"
  // 5: "GOST5", "GOST2.303 4"
  // 6: "GOST6", "GOST2.303 6"
  // 7: "GOST7", "GOST2.303 9"
//		arSkipLineGost.Add(3); //GOST2,  
		arSkipLineGost.Add(4);	//Осевая линия
		//dwSupportTypes = kMcsAllEntities;
		//fWithoutClone=false;
		//fDeleteBrokenObject=false;
		mTol.setEqualPoint(1e-5);
		mTol.setEqualVector(1e-5);
	}
	CutterParams& CutterParams::operator=(const CutterParams& obj) {
		if(this == &obj) return *this;
		fCreateInside = obj.fCreateInside;
		fCreateOutside = obj.fCreateOutside;
		fDelCoincident = obj.fDelCoincident;
		fWatchSkipGost = obj.fWatchSkipGost;
		arSkipLineGost = obj.arSkipLineGost;
		mTol = obj.mTol;
		fDelReverse = obj.fDelReverse;
		fSkipDesignElement = obj.fSkipDesignElement;
		return *this;
	}
};

//////////////////////////////////////////////////////////////////////////
// 
//pCore - контур, который режется
//pCutter - контур, который режет
//hparam - параметры для формирования контура-оболочки pCover	

struct ShellHatchParam
{
		// in 
	double	rWidth;		// distance between expand and base polyline
	bool	bAsHatch;

		// out
	mcsHatch		pHatch;				// only if bAsHatch				
	mcsPolyline		pExpandPoly;		// only if !bAsHatch
	mcsGeomEntArray externHatchShell;	// only if bAsHatch				
	ShellHatchParam() { bAsHatch=true; rWidth=-1; }
};

//////////////////////////////////////////////////////////////////////////
IMCS_DECL_INTERFACE(ICrossPointStorage,	"616F6F82-A918-47d1-AF41-D1B65CF53DAE")
// ICrossPointStorage - идея хранить точки пересечения,// аналог NodeStorage в PT.
// Допустим мы знаем что во время выполнения некой команды нужно работать с геометриями и геомтрии в документе не меняются.
// Занумеруем геометрии и сохраним все точки пересечения геометрий в ICrossPointStorage.
// Пример использования. Пусть нам надо часто вызывать GetInternalContour.
// За нумерацией геометрий следит ICrossPointStorage::init(). Вызываем init() для разбиения геометрий. 
// ICrossPointStorage::GetInternalContour вернёт полилинию в которой каждому сегменту присвоен id. 
// Для работы с этой полилинией кутеру нужно передать указатель на ICrossPointStorage.
// Другой способ получить полилинию в которой, каждому сегменту присвоен номер вызвать ICrossPointStorage::setLinks() 
struct ICrossPointStorage : public virtual IMcObject {
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(ICrossPointStorage);
	IMCS_STD_METHOD_DEFINITION(ICrossPointStorage, IMcObject);
	virtual void init(const mcsGeomEntArray& ents, const mcsTol& tol) = 0;
	virtual HRESULT setLinks(IN OUT mcsPolyline& pol, const mcsIntArray& nIndex) = 0;
	virtual void removeLinks(IN OUT mcsPolyline& pol) = 0;
	virtual HRESULT GetInternalContour(OUT mcsPolyline& pline, const mcsPoint3d& inPnt) = 0;
};

//////////////////////////////////////////////////////////////////////////

struct ICutter : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(ICutter);
	IMCS_STD_METHOD_DEFINITION(ICutter, IMcObject);

    // init
	virtual void Init(CutterParams* pCutterParams) = 0;

		// cut methods
	virtual HRESULT Cut(const mcsGeomEntArray& pSacrificialAltar, const McsEntityGeometry& pPriest) = 0;
	virtual HRESULT Cut(const mcsGeomEntArray& pSacrificialAltar, const mcsGeomEntArray& pPriests) = 0;
	virtual HRESULT Cut(const mcsGeomEntArray& pSacrificialAltar, const mcsPolylineArray& pPriests) = 0;
	virtual HRESULT Cut(const mcsPolylineArray& sacrifice, const mcsPolylineArray &priests, OUT mcsPolylineArray &inside, OUT mcsPolylineArray &outside)  = 0;
	virtual HRESULT CutPerimeter(const mcsPolylineArray &sacrifice, const mcsPolylineArray &priests, OUT mcsPolylineArray &inside, OUT mcsPolylineArray &outside) = 0;

		//filter.lMask |= kMcsFilter_ByBounds | kMcsFilter_ByCurentSheet will be set automatic
		// pPriest - mcsPolyline or mcsCircArc now
	virtual HRESULT Cut(const McsEntityGeometry& pPriest, IN OUT mcsFilter &filter) = 0;
 
		// создать копию лежащего внутри контура
	virtual HRESULT CreateInside(OUT mcsGeomEntArray& pEntArray) = 0;

		// создать остающиеся куски от удаляемых entities
	virtual HRESULT CreateOutside(OUT mcsGeomEntArray& pEntArray) = 0;

		// дать entities, полностью или частично попадающих внутрь контура
	virtual HRESULT GetInsideEntities(OUT mcsWorkIDArray& pEntArray, bool bOnlyUnchangedObjects = false) = 0;

	// не используется.
	virtual HRESULT CreateShellHatch( mcsPolyline& core, mcsPolyline& cutter, ShellHatchParam* pParam) = 0;
	virtual void setStorage(ICrossPointStorage* p) {};
};

//////////////////////////////////////////////////////////////////////////

IMCS_DECL_INTERFACE(IComfortableCutter,	"E313130A-5BB8-4a71-A4E6-9B1B33B1D0EB")
IMCS_DECL_INTERFACE(IHoledAreaCutter,	"1C723385-1A2A-4edc-9C6D-BDF07C3E815B")

#define NRM_DEL_INTERSECT 0x00000002
#define NRM_DEL_MIDDLE_POINTS 0x00000001

struct IComfortableCutter : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IComfortableCutter);
	IMCS_STD_METHOD_DEFINITION(IComfortableCutter, IMcObject);

	virtual HRESULT cut(const mcsPolyline& pol1, const mcsPolyline& pol2, OUT mcsPolylineArray& res) = 0;
	virtual HRESULT join(const mcsPolyline& pol1, const mcsPolyline& pol2, OUT mcsPolylineArray& res) = 0;
	virtual HRESULT intersect(const mcsPolyline& pol1, const mcsPolyline& pol2, OUT mcsPolylineArray& res) = 0;
	virtual HRESULT intersectPairs(const mcsPolylineArray& pol1, const mcsPolylineArray& pol2, OUT mcsPolylineArray& res) = 0;
	virtual HRESULT cut(const mcsPolylineArray& arr1, const mcsPolylineArray& arr2, OUT mcsPolylineArray& res) = 0;
	virtual bool    isInnerPoint(const mcsPolyline& pol, const mcsPoint& pnt, OUT bool& bIsBound) = 0;
	virtual bool	isInnerPline(const mcsPolyline& outPol, const mcsPolyline& inPol) = 0;
	virtual bool    isIntersectItself(const mcsPolyline& pol) = 0;
	virtual HRESULT normalize(IN OUT mcsPolyline& pol, DWORD types = 0) = 0;
	virtual bool    isEqual(const mcsPolyline& pol1, const mcsPolyline& pol2, double dTol = -1) = 0;
	virtual bool    getArea(const mcsPolyline& pol, OUT double& dArea) const = 0;
	virtual bool flat_UpdateContour(const mcsPolylineArray& arr, OUT mcsPolyline& pol) = 0;
	virtual void setTol(const mcsTol& tol) = 0;
	virtual mcsTol getTol() = 0;
	virtual bool isClockWise(const mcsPolyline& pol) = 0;
	virtual void setStorage(ICrossPointStorage* p) = 0;
	virtual HRESULT divideAreaByCurve(const mcsPolyline& pol,
		const mcsCurve* pCurve,
		const mcsTol& tol,
		OUT mcsPolylineArray& leftCont) = 0;
};
//////////////////////////////////////////////////////////////////////////

struct CHoledArea
{
	mcsPolyline      mPol; // внешний контур
	mcsPolylineArray mHoles; // дырки

	MCTYP_API CHoledArea();
	MCTYP_API CHoledArea(const mcsPolyline& pol);
	MCTYP_API CHoledArea(const mcsPolylineArray& plines);

	MCTYP_API void reset();
	MCTYP_API bool isEmpty() const;
	MCTYP_API CHoledArea& transformBy(const mcsMatrix3d& tfm);

	MCTYP_API HRESULT write(OUT IMcsStream* pStream) const;
	MCTYP_API HRESULT read(IMcsStream* pStream);

	MCTYP_API bool operator == (const CHoledArea& other) const;
	MCTYP_API bool operator != (const CHoledArea& other) const;
	MCTYP_API bool isEqualTo(const CHoledArea& other, const mcsTol& tol = gDefPolTol) const;
};

//////////////////////////////////////////////////////////////////////////
typedef McsArray <CHoledArea> CHoledArea_arr;

struct CHoledAreaArray : public CHoledArea_arr
{
	MCTYP_API CHoledAreaArray();
	MCTYP_API CHoledAreaArray(const CHoledAreaArray& cf);
	MCTYP_API CHoledAreaArray(INT_PTR size);

	MCTYP_API CHoledAreaArray& transformBy(const mcsMatrix3d& tfm);
	MCTYP_API bool getArea(double& dArea) const;

	MCTYP_API bool isEqualTo(const CHoledAreaArray& other, const mcsTol& tol = gDefPolTol) const;
};

//////////////////////////////////////////////////////////////////////////

struct IHoledAreaCutter : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IHoledAreaCutter);
	IMCS_STD_METHOD_DEFINITION(IHoledAreaCutter, IMcObject);

	virtual HRESULT cut(const CHoledArea& pol1, const CHoledArea& pol2, OUT CHoledAreaArray& res) = 0;
	virtual HRESULT join(const CHoledArea& pol1, const CHoledArea& pol2, OUT CHoledAreaArray& res) = 0;
	virtual HRESULT intersect(const CHoledArea& pol1, const CHoledArea& pol2, OUT CHoledAreaArray& res) = 0;
	virtual HRESULT cut(IN OUT CHoledAreaArray& res, const mcsPolyline& pol) = 0;
	virtual HRESULT cut(IN OUT CHoledAreaArray& res, const CHoledArea& pol) = 0;
	virtual HRESULT cut(IN OUT CHoledAreaArray& res, const mcsPolylineArray& pol) = 0;
	virtual HRESULT join(IN OUT CHoledAreaArray& res, const mcsPolyline& pol) = 0;
	virtual HRESULT join(IN OUT CHoledAreaArray& res, const CHoledArea& pol) = 0;
	virtual bool    isEqual(const CHoledArea& area1, const CHoledArea& area2) = 0;
	virtual bool    isInnerPoint(const CHoledArea& area1, const mcsPoint& pnt, OUT bool& bIsBound) = 0;
	virtual bool    isCorrect(const CHoledArea& oArea) = 0;
	virtual bool isIntersect(const CHoledArea& pol1, const CHoledArea& pol2) = 0;
	virtual void setTol(const mcsTol& tol) = 0;
	virtual void setStorage(ICrossPointStorage* p) = 0;
	virtual HRESULT xor(const CHoledArea& pol1, const CHoledArea& pol2, OUT CHoledAreaArray& res) = 0;
	virtual HRESULT xor(IN OUT CHoledAreaArray& res, const CHoledArea& pol) = 0;
	virtual HRESULT xor(IN OUT CHoledAreaArray& res, const mcsPolyline& pol) = 0;
	virtual HRESULT cut(const mcsGeomEntArray& res, const CHoledAreaArray& regs,
		OUT mcsGeomEntArray& outside, OUT mcsGeomEntArray& inside, const CutterParams* pCutterParams) = 0;
	virtual HRESULT GetInsideEntities(const CHoledArea& region, IN OUT mcsFilter &filter, 
		OUT mcsWorkIDArray& aCommonEnts, IN CutterParams* pCutterParams, bool bOnlyUnchangedObjects = false) = 0;
};

//////////////////////////////////////////////////////////////////////////

