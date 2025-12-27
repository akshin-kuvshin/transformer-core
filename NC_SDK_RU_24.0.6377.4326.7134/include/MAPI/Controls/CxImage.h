
#pragma once

IMCS_DECL_INTERFACE(ImageHolder, "00088001-0002-AAAA-AAAA-050B00000000");

#define PICTYPE_FILE      20
#define PICTYPE_3D        21

#include "cmnmacro.h"

#ifndef D3DCOLOR_DEFINED
	typedef DWORD D3DCOLOR;
	#define D3DCOLOR_DEFINED
#endif

#ifndef D3DCOLOR_ARGB
	#define D3DCOLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#endif

#ifndef D3DCOLOR_XRGB
	#define D3DCOLOR_XRGB(r,g,b)   D3DCOLOR_ARGB(0xff,r,g,b)
#endif


#define COLORREF_2_D3D_XRGB(clrref) D3DCOLOR_XRGB(GetRValue(clrref), GetGValue(clrref), GetBValue(clrref))
#define COLORREF_2_D3D_ARGB(clrref) D3DCOLOR_ARGB(BYTE4(clrref), GetRValue(clrref), GetGValue(clrref), GetBValue(clrref))

//==============================================================================
//#define D3DFVF_XYZ
struct D3DVertex_XYZ
{
	float x, y, z;

	void operator = (const mcsPoint& pt) {
		x = (float)pt.x;
		y = (float)pt.y;
		z = (float)pt.z;
	}

	void operator = (const D3DVertex_XYZ& cf) {
		memcpy(this, &cf, sizeof(*this));
	}
};

typedef McsArray<D3DVertex_XYZ, const D3DVertex_XYZ&> D3DBUF_XYZ;
//==============================================================================
#define D3DFVF_XYZN (D3DFVF_XYZ|D3DFVF_NORMAL)
struct D3DVertex_XYZN
{
	float x, y, z;
	float nx, ny, nz;

	void operator = (const mcsPoint& pt) {
		x = (float)pt.x;
		y = (float)pt.y;
		z = (float)pt.z;
	}

	void operator = (const mcsVector& n) {
		nx = (float)n.x;
		ny = (float)n.y;
		nz = (float)n.z;
	}

	void operator = (const D3DVertex_XYZN& cf) {
		memcpy(this, &cf, sizeof(*this));
	}
};

typedef McsArray<D3DVertex_XYZN, const D3DVertex_XYZN&> D3DBUF_XYZN;
//==============================================================================
#define D3DFVF_XYZD (D3DFVF_XYZ|D3DFVF_DIFFUSE)
struct D3DVertex_XYZD
{
	float x, y, z;
	DWORD color; // D3DCOLOR_ARGB

	void operator = (const mcsPoint& pt) {
		x = (float)pt.x;
		y = (float)pt.y;
		z = (float)pt.z;
	}

	void setCOLORREF_Alpha(COLORREF c) {
		color = COLORREF_2_D3D_ARGB(c);
	}

	void setCOLORREF_NoAlpha(COLORREF c) {
		color = COLORREF_2_D3D_XRGB(c);
	}

	void operator = (const D3DVertex_XYZD& cf) {
		memcpy(this, &cf, sizeof(*this));
	}
};

typedef McsArray<D3DVertex_XYZD, const D3DVertex_XYZD&> D3DBUF_XYZD;
//==============================================================================
#define D3DFVF_XYZND (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE)
struct D3DVertex_XYZND
{
	float x, y, z;
	float nx, ny, nz;
	DWORD color; // D3DCOLOR_ARGB

	void operator = (const mcsPoint& pt) {
		x = (float)pt.x;
		y = (float)pt.y;
		z = (float)pt.z;
	}

	void operator = (const mcsVector& n) {
		nx = (float)n.x;
		ny = (float)n.y;
		nz = (float)n.z;
	}

	void setCOLORREF_Alpha(COLORREF c) {
		color = COLORREF_2_D3D_ARGB(c);
	}

	void setCOLORREF_NoAlpha(COLORREF c) {
		color = COLORREF_2_D3D_XRGB(c);
	}

	void operator = (const D3DVertex_XYZND& cf) {
		memcpy(this, &cf, sizeof(*this));
	}
};
typedef McsArray<D3DVertex_XYZND, const D3DVertex_XYZND&> D3DBUF_XYZND;
//==============================================================================


//===========================================================================
struct Mc3dImageDepth
{
	mcsSphere bndSphere;
	double dmin, dmax;
	Mc3dImageDepth(){
		dmin=0; dmax=0;
	}

	MCTYP_API void setMax(const mcsPoint& ptEye);
	MCTYP_API void setMax(const mcsPlane& projPlane);
	MCTYP_API void calc(const mcsSphere& s, const mcsPoint& ptEye);
	MCTYP_API void calc(const mcsSphere& s, const mcsPlane& projPlane);
	MCTYP_API bool operator > (const Mc3dImageDepth& cw) const;
	MCTYP_API bool operator >= (const Mc3dImageDepth& cw) const;
	MCTYP_API bool operator < (const Mc3dImageDepth& cw) const;
	MCTYP_API bool operator <= (const Mc3dImageDepth& cw) const;
	MCTYP_API bool operator == (const Mc3dImageDepth& cw) const;
	MCTYP_API bool operator != (const Mc3dImageDepth& cw) const;
};
//===========================================================================
struct Mc3dImages;
struct IDirect3DDevice9;

typedef McsArray<D3DBUF_XYZN, const D3DBUF_XYZN&> D3DBUF_XYZN_Array;
typedef McsArray<D3DBUF_XYZD, const D3DBUF_XYZD&> D3DBUF_XYZD_Array;
typedef McsArray<WORD, WORD> mcsWordArray;
typedef McsArray<mcsWordArray, const mcsWordArray&> mcsWordArray_Array;
//==================================================================================================

struct MCTYP_API Mc3dImageExtColorData
{
	COLORREF         m_shapeAmbientColor;
	COLORREF         m_shapeEmissiveColor;
	COLORREF         m_shapeSpecularColor;
	double           m_dblReflectivity;
	double           m_dblTransparency;

	Mc3dImageExtColorData();
	void reset();
};
//==================================================================================================

struct Mc3dImageDrawData
{
public:

	// буфера фасетов и точек для ребер разбиты на подмассивы;
	// связано с тем, что D3D драйвер ограничивает максимальное кол-во индексов и
	// примитивов за один вызов DrawPrimitiveXXX; ограничения определются полями 
	// D3DCAPS9.MaxPrimitiveCount и D3DCAPS9.MaxVertexIndex;
	bool             m_fD3DBufValid; // true if contents of temp D3D buffers are valid
	D3DBUF_XYZN_Array m__d3d_facets_VNBuf; // float-point buffer with vertices and normals
	mcsWordArray_Array m__d3d_facets_Indices; // reversed order 1-3-2 instead of 1-2-3 (because of LH CS)
	mcsDwordArray    m__d3d_strokesPolylinesLengths; // same as m_strokesPolylinesLengths, but accepts limits from D3D driver
	D3DBUF_XYZD      m__d3d_strokes_VBuf; // float-point buffer with vertices for strokes
	COLORREF         m__d3d_usedStrokesColor; // stored color in tmp <m__d3d_strokes_VBuf> buffer

	// Context and DC used for GL List below, need to be stored here to allow correct list deleting
	HDC              m_GLDC;
	HGLRC            m_GLCtx;
	UINT             m_GLDrawListF; // name of GL list to draw for facets
	UINT             m_GLDrawListS; // name of GL list to draw for strokes

	mcsIUnknownArray m_pMeshes; // D3D meshes array for facets

	Mc3dImageDepth   m__depth; // used internal for sort images by distance

		// для подсветки, не используется при записи/загрузке
	bool                  m__fHighLighted;
	bool                  m__bPrevFSimpleColor;
	Mc3dImageExtColorData m__prevExColorF;
	COLORREF              m__prevColorF;
	COLORREF              m__prevColorS;

		// используется для оптимизации определения видимых/невидимых картинок;
		// индексы в порядке от 0..4 соответствуют плоскостям LTRB,
		// если картинка была отброшена как невидимая по некоторому индексу, то он
		// помещается на первое место, чтобы в след. раз по возможности быстрее
		// определить факт невидимости, используется как в отрисовке, так и в селекции
	int               m__visVolIndices[4];

	//..............................................................................................

public:
	MCTYP_API Mc3dImageDrawData();
	MCTYP_API ~Mc3dImageDrawData();
};
//==================================================================================================

struct Mc3dImageIdsData
{
	// ИД картинки по-сути служит только для идентификации внутри Painter-а
	// для обратной связи со средой, откуда была импортирована картинка 
	// используется <m_externalIDdata>
	//
	mcsWorkID        m_ID;

	// ИД более крупного объекта, в состав которого, входит данный;
	// например изображение поверхности входит в состав детали, тогда
	// <m_parentID> будет идентифицировать деталь,
	// член добавлен для ускорения селекции в рисовалке, например, простой запрос 
	// селекции в сцену из 50000 элементов длится 1/3 секунды, а деталей всего 400,
	// этот запрос выполняется за 1/50 секунды, после получения результата можно 
	// выполнить запрос селекции в детализированном варианте только к тем деталям,
	// которые были получены в результате первого
	//
	mcsWorkID        m_parentID;

	// возможный внешний ID, например после импорта документа из INV можно
	// оставить ссылку на оригинальный объект, для которого получено изображение;
	// здесь будет храниться только сам внешний ИД, а информация о том, в каком 
	// документе и контексте он ссылается на объект хранится в CxImage
	//
	mcsByteArray     m_externalIDdata;
};
//==================================================================================================

struct Mc3dImageGeomData
{
	// геометрия картинки, без ограничений (если есть обрезанный цилиндр, то
	// здесь он представлен полностью:
	// координаты геометрии указаны в том же пространстве, что и сама графика;
	// если картинка содержит несколько примитивов геометрии по смыслу, то тип
	// геометрии не определен
	//
	McsEntityGeometry m_geometry;

	// маска флажков из EntityGeometryTypeEnum;
	// во всех случаях, когда геометрия не определяется через <m_geometry>
	// здесь меожно получить тип сплайновой поверхности, тип компонетна (тела);
	// если и это поле сброшено, то внутри находится набор геометрии
	// произвольных типов или просто тип не определен (произвольная картинка)
	//
	DWORD             m_geometryTypes;

	Mc3dImageGeomData() {
		m_geometryTypes = 0;
	}
};
//==================================================================================================

struct Mc3dImageLinksData
{
	// Для ребра - соседствующие грани.
	// Может быть только одна, второй маркер в этом случае будет = -1.
	// Если это грань, то оба = -1
	McGSMarker         m_faceMarker1, m_faceMarker2;

	// Для грани - соседствующие ребра.
	mcsMcGsMarkerArray m_edgesMarkers;

	Mc3dImageLinksData()
	{
		m_faceMarker1 = -1;
		m_faceMarker2 = -1;
	}
};
//==================================================================================================

struct Mc3dImage : public virtual IMcObject
{
protected:

	// if m_pShapeExtClrData == NULL
	// only the 'm_shapeDiffuseColor' color is used,
	// and is interpreted as RGBA,
	// A channel will indicate transparency, 0 - transparent, 1 - opaque
	//
	COLORREF         m_shapeDiffuseColor;
	mutable Mc3dImageExtColorData* m_pShapeExtClrData;
	bool             m_bFaceDoubleSided;

	mcsPoint3dArray  m_facetsVertices;
	mcsVector3dArray m_facetsNormals;
	mutable mcsDwordArray m_facetsIndices;

	COLORREF         m_edgeColor;

	mcsPoint3dArray  m_strokesVertices;
	mcsDwordArray    m_strokesPolylinesLengths;

	// bounds
	mcsBoundBlock    m_bounds;
	bool             m_fBSphereValid; // <true> if m_bndSphere is valid
	mcsSphere        m_bndSphere;

	// отклонение от оригинальной поверхности, если применимо, иначе = UNKNOWNVALUE
	mutable double   m_deviation;

protected:

	// true - индексы вершин фасетов содержат префикс - кол-во вершин.
	// пример заполнения для двух треугольников:
	// true:  3 0 1 2 3 2 3 0
	// false:   0 1 2   2 3 0
	// Т.е. старый формат (с false) без префикса, более компактный
	mutable bool m_bHasIndicesCountForFacets;

	mutable Mc3dImageDrawData* m_pDrawData;

	// 04.06.2008, AGL, набор для идентификации и селекции в Painter
	mutable Mc3dImageIdsData* m_pIdsData;

	mutable Mc3dImageGeomData* m_pGeomData;

	mutable Mc3dImageLinksData* m_pLinksData;

	//............................................................................

public:

	MCTYP_API Mc3dImage();
	virtual ~Mc3dImage();

	// can return IMcsStream, in this case stream will contain internal data
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj) override;

	virtual const mcsWorkID& ID() const override;
	virtual const mcsWorkID& setID(const mcsWorkID& id);
	virtual mcsWorkID& setID();

	virtual const mcsWorkID& parentID() const;
	virtual const mcsWorkID& setParentID(const mcsWorkID& idParent);
	virtual mcsWorkID& setParentID();

	virtual const mcsByteArray* getExternalIdData() const;
	virtual mcsByteArray& setExternalIdData();

	// face<->edge links data
	virtual McGSMarker getLinkedFaceMarker1() const;
	virtual McGSMarker getLinkedFaceMarker2() const;
	virtual McGSMarker& setLinkedFaceMarker1();
	virtual McGSMarker& setLinkedFaceMarker2();
	virtual const mcsMcGsMarkerArray* getLinkedEdgesMarkers() const;
	virtual mcsMcGsMarkerArray& setLinkedEdgesMarkers();

public:

	__inline const mcsPoint3dArray& facesPoints() const
		{ return m_facetsVertices; }
	__inline const mcsVector3dArray& facesNormals() const
		{ return m_facetsNormals; }
	__inline const mcsDwordArray& facesIndices() const
		{ return m_facetsIndices; }

	__inline mcsPoint3dArray& setFacesPoints()
		{ return m_facetsVertices; }
	__inline mcsVector3dArray& setFacesNormals()
		{ return m_facetsNormals; }
	__inline mcsDwordArray& setFacesIndices()
		{ return m_facetsIndices; }

	__inline const mcsPoint3dArray& edgesPoints() const
		{ return m_strokesVertices; }
	__inline const mcsDwordArray& edgesPolylinesLengths() const
		{ return m_strokesPolylinesLengths; }

	__inline mcsPoint3dArray& setEdgesPoints()
		{ return m_strokesVertices; }
	__inline mcsDwordArray& setEdgesPolylinesLengths()
		{ return m_strokesPolylinesLengths; }

	virtual const mcsSphere& boundSphere() const;
	virtual int& visVolIdx(int idx) const;

	virtual Mc3dImageDepth& depth() const;

	virtual void ResetImmDrawData();
	virtual void Append(const Mc3dImage& data);
	virtual Mc3dImage& operator += (const Mc3dImage& data) {Append(data); return *this;}

		// структура фасетов:
		// <pVerticesCoords> задает вершины на поверхности, их может быть сколько угодно;
		// <pNormalsCoords> нормали в вершинах, соответственно их количество должно совпадать
		//   с количеством вершин;
		// <pIndices> - индексы вершин треугольников в массиве вершин, 
		//   направление нормали треугольника определяется по правилу правостороннего
		//   умножения векторов, количество элементов в массиве - <nFacets>, т.к. задаются
		//   треугольники, то кол-во индексов должно быть кратно 3;
		// множитель <k> задает кратность для координат вершин, удобно для перевода 
		//   координат м/д системами счисления, по-умолчанию принимаются 
		//   "миллиметровые попугаи"
		//
	virtual bool InitFacets(
		DWORD        coordSize, // 8 = double, 4 = float
		const void*  pVerticesCoords, 
		const void*  pNormalsCoords, // OPTIONAL; если NULL, генерируются автоматически по координатам фасетов
		const DWORD* pIndices,
		DWORD        nVertices,
		DWORD        nFacets,
		COLORREF     shapeColor = 0,
		double       k = 1);

	virtual bool AppendFacets(
		DWORD        coordSize, // 8 = double, 4 = float
		const void*  pVerticesCoords, 
		const void*  pNormalsCoords, // OPTIONAL; если NULL, генерируются автоматически по координатам фасетов
		const DWORD* pIndices,
		DWORD        nVertices,
		DWORD        nFacets,
		double       k = 1);

		// структура данных для ребер (кривых):
		// <pVerticesCoords> задает упорядоченный набор вершин на кривой, 
		//   разбитой отрезками;
		// <nPolylines> количество раздельных кривых, которые "упакованы" в
		//   массиве вершин;
		// <pPolylineVerticesCounts> массив размерности <nPolylines>, в котором
		//   элементы означают количество точек из массива вершин, которые относятся 
		//   к отдельной кривой, т.е. если первый элемент массива =10, то первые 10 
		//   вершин относятся к одной кривой, следующий элемент массива 
		//   <pPolylineVerticesCounts> будет указывать какое кол-во вершин отведено
		//   под вторую кривую начиная с 11-ой точки в массиве вершин
		//
	virtual bool InitStrokes(
		DWORD        coordSize, // 8 = double, 4 = float
		const void*  pVerticesCoords, 
		const DWORD* pPolylineVerticesCounts,
		DWORD        nVertices,
		DWORD        nPolylines,
		COLORREF     edgeColor = 0,
		double       k = 1);

	virtual bool AppendStrokes(
		DWORD        coordSize, // 8 = double, 4 = float
		const void*  pVerticesCoords, 
		const DWORD* pPolylineVerticesCounts,
		DWORD        nVertices,
		DWORD        nPolylines,
		double       k = 1);

	virtual bool GenerateLostNormals(int scanIndicesFrom = 0);

	// Метод выбрасывает для фасетов поверхностей префиксы кол-ва вершин в массиве индексов
	virtual bool CompactFaceIndices() const;

	// Метод добавляет для фасетов поверхностей префиксы кол-во вершин в массиве индексов
	virtual bool ExpandFaceIndices() const;

	virtual bool HasCountsInFacetIndices() const {
		return m_bHasIndicesCountForFacets;
	}

	virtual void Clear(bool fClearFacets = true, bool fClearStrokes = true);
	virtual void ClearD3DData();
	virtual Mc3dImagePtr getCopy(bool fCopyFacets = true, bool fCopyStrokes = true) const;

	virtual HRESULT save(IMcsStream* pS) const;
	virtual HRESULT load(IMcsStream* pS);
	virtual HRESULT getAsRawData(OUT mcsByteArray& data, bool fCompressed = true) const;
	virtual HRESULT setFromRawData(IN LPCVOID pData, IN DWORD size);

	virtual HRESULT Check(bool fFull=false) const; // check internal data integrity

	virtual DWORD getContainingGeometryTypes() const;
	virtual DWORD setContainingGeometryTypes(DWORD newTypes, bool bAdd);
	virtual DWORD& setContainingGeometryTypes(); // прямой доступ, менять синхронно с ContainingGeometry

	// Получить отклонение фасетов/ребер от оригинальной геометрии.
	// Если не применимо или невозможно определить возвращается UNKNOWNVALUE.
	// Если изначально отклонение не было задано и указан bAutodetect, пытается определить отклонение автоматически
	virtual double getDeviation(bool bAutodetect) const;
	virtual void   setDeviation(double dev);

	virtual const McsEntityGeometry* getContainingGeometry() const;
	virtual void setContainingGeometry(const McsEntityGeometry& newGeom, bool bUpdateContainingGeomTypes);
	virtual McsEntityGeometry& setContainingGeometry();  // прямой доступ, менять синхронно с ContainingGeometryTypes
	virtual McGSMarker getContainingGeomSelMarker() const;

	virtual Mc3dImage& transformBy(const mcsMatrix& tfm);

	virtual mcsBoundBlock getBounds(bool fRecalc = false);
	virtual mcsBoundBlock getBounds() const;
	virtual mcsBoundBlock getOrthoBounds() const;
	virtual bool getBoundingSphere(OUT mcsSphere& bndSphere, bool fRecalc = false);
	virtual bool getBoundingSphere(OUT mcsSphere& bndSphere) const;
	virtual bool validateBoundSphere(bool fRecalc = false);
	virtual void resetBounds();

	// определяет, относится ли изображение к классу детализированных.
	// такое изображение имеет след. св-ва:
	// - содержит данные ассоциированной геометрии, и это единственный тип геометрии, хранимый в изображении
	// - ассоциированная геометрия имеет присвоенный маркер селекции
	virtual bool isDetailed() const;

	virtual bool hasFasets() const {return m_facetsVertices.GetSize()>0;}
	virtual bool hasStrokes() const {return m_strokesVertices.GetSize()>0;}
	virtual bool isEmpty() const {return !hasFasets() && !hasStrokes();}

		// Для поверхностей возвращает признак того, что графика должна прорисовываться с двух сторон
	virtual bool facesDoubleSided() const { return m_bFaceDoubleSided; }

		// установка признака двусторонней графики поверхностей
	virtual void setDoubleSidedFaces(bool bDoubleSided) { m_bFaceDoubleSided = bDoubleSided; }

	virtual bool isTransparent()
	{
		if(hasFasets() && getTransparency()>0)
			return true;
		return false;
	}

	// 0 - opaque, 1 - transparent
	virtual double  getTransparency() const;
	virtual void    setTransparency(double t);

	virtual void    setFacesSimpleColor(COLORREF clr = -1);
	virtual void    setEdgesColor(COLORREF clr = -1);

	virtual COLORREF facesColor() const;
	virtual COLORREF edgesColor() const;

	virtual void    setFacesExtendedColor(
		COLORREF diffusionColor,
		COLORREF ambientColor,
		COLORREF specularColor,
		COLORREF emissionColor,
		double   kTransparency,  // 0..1
		double   kReflectivity); // 0..1

	virtual void    setFacesExtendedColor(
		COLORREF                     diffusionColor,
		const Mc3dImageExtColorData& exColorData);

	__inline COLORREF facesDiffuseColor() const
		{ return facesColor(); }

	virtual bool     hasSimpleFacesColor() const;
	virtual COLORREF facesAmbientColor() const;
	virtual COLORREF facesSpecularColor() const;
	virtual COLORREF facesEmissionColor() const;
	virtual double   facesReflectivity() const;

		// GL helpers
		// draws 3D image using GL commands, context must be set before call;
		// fReinit forces GL list recreation;
		// colors must be set before, need for simplify "preselect" and "selected"
		// coloring;
		// separate methods for facets and strokes need for highlighting 
		// single image with facets and strokes and using GL lists
	virtual HRESULT GL_DrawFacets(bool fReinit);
	virtual HRESULT GL_DrawStrokes(bool fReinit);

	virtual HRESULT _D3D_PrepareBuffers(DWORD maxIndices, DWORD maxPrimitives);
	virtual HRESULT D3D_DrawFacets(IMcPainter* pIP, DWORD maxIndices, DWORD maxPrimitives, bool fReinit, bool fPickMode);
	virtual HRESULT D3D_DrawStrokes(IMcPainter* pIP, DWORD maxIndices, DWORD maxPrimitives, bool fReinit, bool fPickMode, IN bool fUseOverrideColor, IN OPTIONAL COLORREF overrideColor = 0);

		// initializes colors for further drawing
	virtual HRESULT GL_InitFacetsColor(IN bool fUseOverrideColor, IN OPTIONAL COLORREF overrideColor = 0);
	virtual HRESULT GL_InitStrokesColor(IN bool fUseOverrideColor, IN OPTIONAL COLORREF overrideColor = 0);

	virtual HRESULT D3D_InitFacetsColor(IMcPainter* pIP, IN bool fUseOverrideColor, IN OPTIONAL COLORREF overrideColor = 0);

		// объединяет графические данные в <this>, с оптимизацией;
		// все данные о ID сбрасываются;
		// (тип геометрии обновляется, но толку маловато от этого)
	virtual HRESULT setMergedFrom(IN Mc3dImages& imgsToMerge);

	virtual bool    isHighlighted();
	virtual HRESULT highlight(COLORREF hlColor);
	virtual HRESULT unhighlight();

	virtual void    setMajorVisVolIdx(int idxFallEntry);
	virtual HRESULT getAsGeomEntArray(mcsGeomEntArray& GeArr, bool fClearInput = true);

protected:

	virtual Mc3dImageDrawData&     DrawData() const;
	virtual Mc3dImageExtColorData& ColorExData() const;
	virtual Mc3dImageGeomData&     GeomData() const;
	virtual Mc3dImageIdsData&      IdsData() const;
	virtual Mc3dImageLinksData&    LinksData() const;

	virtual void DropGeomData();
	virtual void DropColorExData();
	virtual void DropIdsData();
	virtual void DropLinksData();
};
//===========================================================================
struct Mc3dImages : public McsArray<Mc3dImagePtr, Mc3dImage*>
{
	MCTYP_API mcsBoundBlock getBounds();
	MCTYP_API Mc3dImages& transformBy(const mcsMatrix& tfm);
	MCTYP_API HRESULT setColor(COLORREF shapeColor, IN OPTIONAL COLORREF edgeColor=0);
	MCTYP_API void setTransparency(double t);
	MCTYP_API void setExtendedColorAttributes(
		COLORREF diffusionColor,
		COLORREF ambientColor,
		COLORREF specularColor,
		COLORREF emissionColor,
		double   kTransparency,  // 0..1
		double   kReflectivity); // 0..1

	MCTYP_API HRESULT sortByDepth_parallelProj(IN const mcsPlane& projPlane, IN bool fFromDistToNearest);
	MCTYP_API HRESULT sortByDepth_centralProj(IN const mcsPoint& eyePoint, IN bool fFromDistToNearest);

		// метод объединяет все изображения, которые не попадают в указанную маску в одно
		// остальные остаются без изменения, необходимо для ускорения отрисовки сцены 
		// с возможностью идентификации с фильтром определенного типа геометрии
	MCTYP_API HRESULT mergeByGeometryType(DWORD typesMask);
	MCTYP_API HRESULT getCopy(OUT Mc3dImages& copy) const;
	MCTYP_API HRESULT ResetImmDrawData();
	MCTYP_API HRESULT getAsGeomEntArray(mcsGeomEntArray& GeArr, bool fClearInput = true);
};
//===========================================================================
class CxImage
{
protected:
	ImageHolder* m_pImg;

public:

	enum FileFmt
	{
		kEmf = 1,
		kBmp = 2,
		kJpg = 3,
		kGif = 4,
		kPng = 5,
		kTiff = 6,
	};

	MCTYP_API CxImage();
	MCTYP_API CxImage(const CxImage&);
	MCTYP_API CxImage& operator=(const CxImage&);

	MCTYP_API virtual ~CxImage();

	//Load/Save
	MCTYP_API HRESULT load(LPCTSTR file = NULL, HWND hWnd = NULL); //При file == NULL запрос на открытие файла
	MCTYP_API HRESULT load(IN LPCVOID pImgData, IN DWORD dataSize);
	MCTYP_API HRESULT load(HINSTANCE hInst, LPCTSTR resourceID); //	load from resource of specific module
	MCTYP_API HRESULT load(IMcsStream* pS);

		// Формат содержимого должен соответстовать типу файла, автоматического преобразование
		// не выполняется, т.к. для разных преобразований нужны разные параметры.
		// Например, для EMF->BMP нужно знать размер растра и цвет фона,
		// для 3D->BMP нужно знать размер вьюпорта, фон и положение наблюдателя.
		// Поэтому, например для записи EMF в JPEG, нужно санчала явно сделать из него CxImage
		// с типом HBMP и уже его записывать в формате JPEG
		//
		// Для формата JPEG возможно указать качество сжатия, параметр 'jpegQuality' (0..100]
		//
	MCTYP_API HRESULT save(LPCTSTR lpszFile, FileFmt eFileFormat, int jpegQuality = 80) const;

	MCTYP_API HRESULT save(OUT mcsByteArray& imgData, IN OPTIONAL bool fCompressStreamData = true) const;
	MCTYP_API HRESULT save(IMcsStream* pS, IN OPTIONAL bool fCompressStreamData = true) const;

#ifdef __AFXCOLL_H__ // for MFC funs
	MCTYP_API HRESULT save(OUT CByteArray& imgData, IN OPTIONAL bool fCompressStreamData = true) const;
#endif

	// if image has GL type then bitmap/metafile is implied as it's preview
	MCTYP_API HRESULT setHBMP(HBITMAP bmp, bool bAttach = false); 
	MCTYP_API HRESULT setHEMF(HENHMETAFILE emf, bool bAttach = false);

	MCTYP_API HRESULT set3dImages(IN Mc3dImages&); // image will be cleared before accept input
	MCTYP_API HRESULT add3dImage(IN Mc3dImage*); // image must have GL type or be empty
	MCTYP_API Mc3dImagePtr add3dImage(); // создаёт внутри новое 3D изображение и отдаёт его для заполнения
	MCTYP_API HRESULT add3dImages(IN Mc3dImages); // image must have GL type or be empty
	MCTYP_API HRESULT remove3dImages();
	MCTYP_API HRESULT getCopy(OUT CxImage&) const;

	//Эти методы копируют image.
	MCTYP_API HBITMAP getHBMP(long BkGrnd = 0, int cx = -1, int cy = -1);
	MCTYP_API HBITMAP getHBMPRot(long BkGrnd = 0, int cx = -1, int cy = -1, float angle = 0);
	MCTYP_API HBITMAP getHBMPFrame(long BkGrnd = 0, int x = 0, int y = 0, int cx = -1, int cy = -1);
	MCTYP_API HBITMAP getHBMPScaled(long BkGrnd = 0, int cx = -1, int cy = -1, double shrinkingScale = 1); // shrinkingScale >= 1

	MCTYP_API HENHMETAFILE getHEMF(IN OPTIONAL LPCTSTR enfFilePath=NULL);
	MCTYP_API HRESULT get3dImages(OUT Mc3dImages&) const; // image must have GL type
	MCTYP_API int     get3dImagesCount() const; // image must have GL type
	MCTYP_API Mc3dImagePtr _get3dImage(int idx) const; // optimization
	MCTYP_API mcsBoundBlock getBounds() const;

	//по умолчанию включено
	MCTYP_API void Transparents(bool bON); 

		// Экспортирует изображение в указанный формат с заданием прозрачности.
		// Если на момент вызова формат картинки внутри не HBMP, будет ошибка.
		// Все пикселы указанного цвета transpColor будут сделаны прозрачными.
		// blendingWidth задаёт плавность прозрачности относительно цвета transpColor;
		// К примеру, если указать blendingWidth = 10, цвета, отдалённые от transpColor дальше,
		// чем на 10 ступеней будут полностью непрозрачны (видимы), а на 5 ступеней - будет иметь прозрачность 50%;
	MCTYP_API HRESULT exportTrueTransparentImage(LPCTSTR lpszFile, FileFmt eFileFormat, COLORREF transpColor = 0xC0C0C0, int blendingWidth = 1);

	//Возвращает внутренний хэндл, нельзя уничтожать!
	MCTYP_API operator HENHMETAFILE() const;
	MCTYP_API operator HBITMAP() const;

	MCTYP_API int getRawFormat() const;//PICTYPE_ICON,PICTYPE_BITMAP и т.п. 
	MCTYP_API bool isValid() const;
	MCTYP_API void clear();//Destroy
	MCTYP_API int getWidth() const;
	MCTYP_API int getHeight() const;


	//helper: loads data from file to byte array
	MCTYP_API HRESULT loadAndSaveToArr(OUT mcsByteArray&src, LPCTSTR file = NULL, HWND hWnd = NULL);

protected:
	MCTYP_API bool _append3dData(IN OUT mcsByteArray& data, IN OPTIONAL bool fCompressed = true) const;

public:
	bool m_bTransparent;

	//............................................................................
	// 04.06.2008, AGL, набор для идентификации и селекции в Painter

		// путь к документу, откуда было импортировано изображение;
	McsString    m_strExternalDocPth;

		// данные, содержащие дополнительную информацию, которая нужна для 
		// идентификации объектов-изображений, содержащихся в данном CxImage;
		// для INV это RefContextData
	mcsByteArray m_externalDocAddonData;
};
//===========================================================================
struct CxImages : public McsArray<CxImage, const CxImage&>
{
	MCTYP_API mcsBoundBlock getBounds();
};
//===========================================================================

// IMCS_DECL_INTERFACE(IMcCxImage, "D077649E-1B02-4680-8857-7400092BF6B6");
// 
// struct IMcCxImage {
// public:
// 	IMcCxImage() {};
// 	virtual ~IMcCxImage() {};
// 	//
// 	IMcCxImage(IMcCxImage& aImg) {
// 		m_image = aImg.m_image;
// 	}
// 
// 	IMcCxImage(CxImage& aImg) {
// 		m_image = aImg;
// 	}
// 
// 	virtual CxImage& operator &() {
// 		return m_image;
// 	};
// 
// 	virtual CxImage& operator = (CxImage& aImg) {
// 		m_image = aImg;
// 		return m_image;
// 	}
// 	//--------------------------
// protected:
// 	CxImage m_image;
// };