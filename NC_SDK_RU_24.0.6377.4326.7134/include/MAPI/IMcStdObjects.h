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

#define CLSID_IMcLine        IID_IMcLine
#define CLSID_IMcXLine       IID_IMcXLine
#define CLSID_IMcRay         IID_IMcRay
#define CLSID_IMcArc         IID_IMcArc
#define CLSID_IMcCircle      IID_IMcCircle
#define CLSID_IMcPolyline    IID_IMcPolyline
#define CLSID_IMcPoint       IID_IMcPoint
#define CLSID_IMcEllipticArc IID_IMcEllipticArc
#define CLSID_IMcSpline      IID_IMcSpline

//Интерфейс геометрии общий
//Если это новый объект, можно установить любой тип геометрии.
struct IMcGeometry : public virtual IMcObject
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcGeometry);
  virtual const GUID&      getClassID() const {return IID_IMcGeometry;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;
	
	virtual const McsEntityGeometry& asEntityGeometry() = 0;
	virtual HRESULT set(const McsEntityGeometry& geom) = 0; //can change type of geometry ONLY
	//if its new uninited object, another E_FAIL

	virtual IMcDbEntityPtr Entity() = 0;
};

//////////////////////////////////////////////////////////////////////////
//Интерфейс линии
struct IMcLine : public virtual IMcGeometry
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcLine);
  virtual const GUID&      getClassID() const {return CLSID_IMcLine;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;

	virtual HRESULT set(const mcsPoint3d& pntStart, const mcsPoint3d& pntEnd) = 0;
	virtual HRESULT set(const mcsLineSeg& line) = 0;
	virtual HRESULT setStartPnt(const mcsPoint3d& pntStart) = 0;
	virtual HRESULT setEndPnt(const mcsPoint3d& pntStart) = 0;

	virtual HRESULT get(mcsPoint3d& pntStart, mcsPoint3d& pntEnd) = 0;
	virtual mcsPoint3d startPoint() const = 0;
	virtual mcsPoint3d endPoint() const  = 0;
	virtual const mcsLineSeg& asMcsLine() const = 0;
};

//////////////////////////////////////////////////////////////////////////
//Интерфейс X-линии
struct IMcXLine : public virtual IMcGeometry
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcXLine);
	virtual const GUID&      getClassID() const {return IID_IMcXLine;}
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;
};

//////////////////////////////////////////////////////////////////////////
//Интерфейс луча
struct IMcRay : public virtual IMcGeometry
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcRay);
	virtual const GUID&      getClassID() const {return IID_IMcRay;}
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;
};

//////////////////////////////////////////////////////////////////////////
//Интерфейс дуги
struct IMcArc : public virtual IMcGeometry
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcArc);
  virtual const GUID&      getClassID() const {return CLSID_IMcArc;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;

	virtual HRESULT set(const mcsPoint& center, double radius, double startAng, double endAng) = 0;
	virtual HRESULT set(const mcsCircArc& arc) = 0;
	virtual HRESULT setRadius(double rRadius) = 0;
	virtual HRESULT setCenter(const mcsPoint3d& pntCenter) = 0;

	virtual double radius() const = 0;
	virtual mcsPoint3d center() const = 0;
	virtual const mcsCircArc& asMcsArc() const = 0;
};

//////////////////////////////////////////////////////////////////////////
//Интерфейс точки
struct IMcPoint : public virtual IMcGeometry
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcPoint);
  virtual const GUID&      getClassID() const {return CLSID_IMcPoint;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;

	virtual HRESULT setPosition(const mcsPoint3d& position) = 0;
	virtual mcsPoint3d position() const = 0;
};

struct IMcHatch: public virtual IMcGeometry 
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcHatch);
  virtual const GUID&      getClassID() const {return IID_IMcHatch;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;
	virtual HRESULT setAssociative(mcsWorkIDArray& ids)	= 0;
};


//////////////////////////////////////////////////////////////////////////
struct IMcCircle : public virtual IMcGeometry
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcCircle);
  virtual const GUID&      getClassID() const {return CLSID_IMcCircle;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;

	virtual HRESULT set(const mcsPoint& center, double radius) = 0;
	virtual HRESULT set(const mcsCircArc& arc) = 0;
	virtual HRESULT setRadius(double rRadius) = 0;
	virtual HRESULT setCenter(const mcsPoint3d& pntCenter) = 0;

	virtual double radius() const = 0;
	virtual mcsPoint3d center() const = 0;
	virtual const mcsCircArc& asMcsArc() const = 0;
};

//////////////////////////////////////////////////////////////////////////
struct IMcSpline : public virtual IMcGeometry
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcSpline);
  virtual const GUID&      getClassID() const {return CLSID_IMcSpline;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;

	virtual HRESULT set(const mcsSpline& spline) = 0;
	virtual const mcsSpline& asMcsSpline() const = 0;
};

//////////////////////////////////////////////////////////////////////////
struct IMcCurve : public virtual IMcObject
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcCurve);
  virtual const GUID&      getClassID() const {return IID_IMcCurve;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;
	virtual const mcsCurve* asMcsCurve() const = 0;
	virtual IMcDbEntityPtr Entity() = 0;
};

//Интерфейс полилинии
struct IMcPolyline : public virtual IMcGeometry
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcPolyline);
  virtual const GUID&      getClassID() const {return CLSID_IMcPolyline;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;

	virtual HRESULT set(const mcsPolyline& polyline) = 0;
	virtual const mcsPolyline& asMcsPolyline() const = 0;
};

//Интерфейс текста
struct IMcText : public virtual IMcGeometry
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcText);
  virtual const GUID&      getClassID() const {return IID_IMcText;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;
	
	virtual HRESULT set(const mcsText& text) = 0;
	virtual const mcsText& asMcsText() const = 0;
};

//Интерфейс элипса
struct IMcEllipticArc : public virtual IMcGeometry
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcEllipticArc);
  virtual const GUID&      getClassID() const {return IID_IMcEllipticArc;}
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) = 0;
	
	virtual HRESULT set(const mcsEllipArc& ellipArc) = 0;
	virtual const mcsEllipArc& asEllipArc() const = 0;
};

//////////////////////////////////////////////////////////////////////////

// Множество значений типов блока/внешней ссылки с точки зрения 3D моделирования
// Не менять, пишется в файл!

enum Block3dTypeEnum
{
	k3dBlkType_Unknown = 0,

	// 2D сущность (вообще нет объектов, относящихся к 3D)
	k3dBlkType_2D = 1,

	// Деталь, нет 3D тел вообще, но есть 3D построения
	k3dBlkType_PartConstructionsOnly = 2,

	// Деталь (Одно 3D тело в составе на всех уровнях вложения)
	k3dBlkType_Part = 3,

	// Сборка (Два и более 3D тел на всех уровнях вложения)
	k3dBlkType_Assembly = 4,

	k3dBlkType_AlienPart = 5, // деталь только с Alien-телами (можно классифицировать как НЕ 3D блок)
	k3dBlkType_AlienAssembly = 6, // сборка только с Alien-телами (можно классифицировать как НЕ 3D блок)

	// Стандартное изделие (Одно стандартное 3D тело в составе на всех уровнях вложения)
	k3dBlkType_StdPart = 7,
};

//---------------------------------------------------------------------------
struct McBlockReferenceAttribute
{
	McsString stTag;
	McsString stText;
};
typedef McsArray<McBlockReferenceAttribute, const McBlockReferenceAttribute> McBlockReferenceAttributeArray;

//---------------------------------------------------------------------------
//Block Reference в Acad
struct IMcBlockRef : public virtual IMcCdEntity, public virtual IMc3dConstraintCompatible
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcBlockRef);
	IMCS_ENT_METHOD_DEFINITION4(IMcBlockRef, IMcCdEntity, IMcDbEntity, IMc3dConstraintCompatible); 

	virtual HRESULT getInsertPoint(mcsPoint& pnt) const = 0;
	virtual HRESULT setInsertPoint(const mcsPoint& pnt) = 0;

	//Разбивает блок на отдельные объекты, и добавляет их в базу. (это для упрощения, то же самое можно через explode и т.д.)
	virtual HRESULT decompose(mcsWorkIDArray& ids, bool bExplode = true) = 0;

	//Специальный метод только для блоков, они в перекрытии обрабатываются отдельно
	virtual HRESULT setBlockName(const McsString &strBlock) = 0;
	virtual LPCTSTR getBlockName() const = 0;

	virtual HRESULT setScaleFactor(double rX, double rY, double rZ) = 0;
	virtual double getScaleFactorBy(int i) const = 0; //X,Y,Z

	virtual HRESULT setRotation(double rRotation) = 0;
	virtual double getRotation() const = 0;

	virtual bool isExtRef() const = 0;
	virtual bool isDynamic() const = 0;

	//Вобще вредная функция, надо бы припахать getTfm() но лучше не трогать из за
	//экстентов, decompose и прочего
	virtual HRESULT getTfmMatrix(mcsMatrix& tf) const = 0;

	// Возвращает документ вставки блока (документ его содержимого)
	virtual IMcDocumentPtr getBlock() const
		{ return UNKNULL; }

		// (!) базовая реализация медленная
		//
		// Определяет, содержит ли блок по этому вхождению объекты 3D построений,
		// если bCheckFor3dPartsOnly == true, проверяет только наличие тел
		// (в этом случае если тел не будет, но даже будут эскизы, WP-объекты, то результат все равно будет false)
	MCTYP_API virtual bool has3d(bool bCheckFor3dPartsOnly = false) const;

		// IMc3dConstraintCompatible
	MCTYP_API virtual bool    canBeConstrained() const override;
	MCTYP_API virtual HRESULT getAttached3dConstraints(OUT mcsWorkIDArray& ids3dCtrs) const override;

		// Позволяет узнать, какой булевой фичей использовано данное вхождение блока.
		// Имеет смысл только для блоков, у которых has3d(true) == true
	MCTYP_API virtual mcsWorkID getHost3dBooleanFeature(bool bGetTopmostUnsuppressedBoolFtr) const;

		// Тип блока/внешней ссылки с точки зрения 3D моделирования
	virtual Block3dTypeEnum get3dType() const
		{ return k3dBlkType_Unknown; }

		// возвращает призак того, что вставка блока зафиксирована и не может быть перемещена
	MCTYP_API virtual bool isFixed() const;

		// устанавливает новое значение признака фиксации блока
	MCTYP_API virtual bool setIsFixed(bool bFixed);

	// Метод позволяет получить содержимое блока, а также подгрузить его при необходимости, если это xref
	virtual IMcDocumentPtr getBlock(bool bForceLoadXref) const
		{ return UNKNULL; }

	virtual HRESULT getNormal(OUT mcsVector&) const = 0;
	virtual HRESULT setNormal(IN const mcsVector&) = 0;

	// для 3D, для блоков-деталей/сборок, см. также комментарий к методу IMc3dHistoryItem::setOrderAsmObjBefore.
	virtual bool  setOrderAsmObjBefore(const mcsWorkID& idAsmObjBefore, bool bTryOnly, bool bOnlySet = false) {
		return false;
	}

	// для 3D, для блоков-деталей/сборок, см. также комментарий к методу IMc3dHistoryItem::getOrderAsmObjBefore.
	virtual mcsWorkID getOrderAsmObjBefore() const {
		return WID_NULL;
	}

	// для 3D, для блоков-деталей/сборок
	virtual void      setCreationTime(__int64 creationTime) { }
	virtual __int64   getCreationTime() const { return 0; }
			
	// Устанавливает документ вставки блока (документ его содержимого).
	// Документ должен быть в том же top-документе, что и вставка блока.
	// Документ должен быть блоком (не может быть листом или пространством модели).
	// Вызывающая сторона должна гарантировать, что установка нового документа для вставки блока
	// не приведёт к циклическим ссылкам в документе.
	virtual HRESULT setBlock(IMcDocument* pBlockDoc)
	{
		return E_NOTIMPL;
	}
};
//---------------------------------------------------------------------------

class McR2VConvertorParams {
public:
	// recognize
	bool bRecLines, bRecArcs, bRecText, bRecTextAreas;
	
	// text parameters
	BOOL bUsePatterns;
	McsString sPatterns, sOCR;
	
	// raster params
	double rMinLength;
	double rMaxWidth;
	double rMaxBreak;
	double rTextHeight;
	
	McR2VConvertorParams() {
		bRecLines = true;
		bRecArcs = true;
		bRecText = false;
		bRecTextAreas = false;
		bUsePatterns = true;
		sPatterns =  _T("%D");
		sOCR = _T("default.ocr");
		rMinLength = 5;
		rMaxWidth = 5;
		rMaxBreak = 3;
		rTextHeight = 60;
	}
};


//////////////////////////////////////////////////////////////////////////
// Растр
struct IMcImageRef : public virtual IMcEntity
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcImageRef);
	IMCS_ENT_METHOD_DEFINITION(IMcImageRef, IMcEntity, IMcDbEntity); 

	virtual HRESULT Vectorize(OUT mcsGeomEntArray& ents, IN const McR2VConvertorParams& params) = 0;
	virtual HRESULT getPixelToModelTransform(OUT mcsMatrix& tfm) = 0;
	virtual HRESULT setClipBoundary(IN bool isRectangular, IN const mcsPoint3dArray& points) = 0;
	virtual HRESULT getClipBoundary(OUT bool& isRectangular, OUT mcsPoint3dArray& points) = 0;
	virtual HRESULT setImageName(IN LPCTSTR stName) = 0;
	virtual McsString getImageName() = 0;
	virtual HRESULT setOrientation(IN const mcsPoint& pntOrigin, IN const mcsVector& vecWidth, IN const mcsVector& vecHeight) = 0;
	virtual HRESULT getOrientation(OUT mcsPoint& pntOrigin, OUT mcsVector& vecWidth, OUT mcsVector& vecHeight) = 0;
};

//////////////////////////////////////////////////////////////////////////
__inline bool isStdObject(const GUID& clsID)
{
	if(clsID == IID_IMcGeometry) return true;
	if(clsID == IID_IMcCurve) return true;
	if(clsID == IID_IMcLine) return true;
	if(clsID == IID_IMcArc) return true;
	if(clsID == IID_IMcCircle) return true;
	if(clsID == IID_IMcPolyline) return true;
	if(clsID == IID_IMcHatch) return true;
	if(clsID == IID_IMcText) return true;
	if(clsID == IID_IMcMText) return true;
	if(clsID == IID_IMcEllipticArc) return true;
	if(clsID == IID_IMcPoint) return true;
	if(clsID == IID_IMcSpline) return true;
	if(clsID == IID_IMcCdGeometry) return true;
	if(clsID == IID_IMc3DPolyline) return true;
	if(clsID == IID_IMcMLine) return true;
	if(clsID == IID_IMcAttribute) return true;
	if(clsID == IID_IMcViewport) return true;
	if(clsID == IID_IMcXLine) return true;
	if(clsID == IID_IMcRay) return true;
	if(clsID == IID_IMcRegion) return true;
	if(clsID == IID_IMcPolyFaceMesh) return true;
	if(clsID == IID_IMcPolygonMesh) return true;
	if(clsID == IID_IMcShape) return true;
	if(clsID == IID_IMcSolid) return true;
	if(clsID == IID_IMcWipeout) return true;
	if(clsID == IID_IMcSubDMesh) return true;
	if(clsID == IID_IMc2DPolyline) return true;
	if(clsID == IID_IMcImageRef) return true;
	if(clsID == IID_IMcMLeader) return true;
	if(clsID == IID_IMcDWGTable) return true;
	if(clsID == IID_IMcBimIfcEntity) return true;
	return false;
}

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcAlienEntity - неизвестный объект
//---------------------------------------------------------------------------
struct IMcAlienEntity : public virtual IMcCdEntity
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcAlienEntity);
	IMCS_ENT_METHOD_DEFINITION(IMcAlienEntity, IMcEntity, IMcDbEntity);//здесь специально IMcEntity, по умолчанию
	//он не IMcCd, это включается в гейте при наличии соответствующей поддержки, там же поправить isKindOf

	virtual HRESULT getInsertPoint(mcsPoint& pnt) = 0;
	virtual HRESULT explode(mcsGeomEntArray& geometry) const
		{ return E_FAIL; }
};

