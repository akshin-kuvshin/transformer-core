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

#ifndef __NANOTHUNK_GRAPHICS_H__
#define __NANOTHUNK_GRAPHICS_H__

#include "nrxdbgate_impexp.h"
#include "typesDb.h"
#include "hostArray.h"

class NcDbAttribute;
class NcDbBlockTable;
class NcDbBlockTableIterator;
class NcDbBlockTableRecord;
class NcDbDatabase;
class NcDbDictionary;
class NcDbDimStyleTable;
class NcDbDimStyleTableIterator;
class NcDbDimStyleTableRecord;
class NcDbExtents;
class NcDbLayerTable;
class NcDbLayerTableIterator;
class NcDbLayerTableRecord;
class NcDbLinetypeTable;
class NcDbLinetypeTableIterator;
class NcDbLinetypeTableRecord;
class NcDbPolyline;
class NcDbRegAppTable;
class NcDbRegAppTableIterator;
class NcDbRegAppTableRecord;
class NcDbTextStyleTable;
class NcDbTextStyleTableIterator;
class NcDbTextStyleTableRecord;
class NcDbUCSTable;
class NcDbUCSTableIterator;
class NcDbUCSTableRecord;
class NcDbViewportTable;
class NcDbViewportTableIterator;
class NcDbViewportTableRecord;
class NcDbViewTable;
class NcDbViewTableIterator;
class NcDbViewTableRecord;
class NcGiDrawable;
class NcGiGdiDrawObject;
class NcGiGeometry;
class NcGiCommonDraw;
class NcGiEdgeData;
class NcGiEdgeStyle;
class NcGiFaceData;
class NcGiTextStyle;
class NcGiVariant;
class NcGiVertexData;
class NcGiViewport;
class NcGiWorldGeometry;
class NcGsClassFactory;
class NcGsDevice;
class NcGsModel;
class NcGsNode;
class NcGiPolyline;
class NcGiImageBGRA32;
class OwnerDraw;
class OdGsDCPoint;
class OdGsDCRect;

typedef enum{
	kNcGiMain = 0,
	kNcGiSprite,
	kNcGiDirectShortTerm,
	kNcGiHighlight,
	kNcGiDirectTopmost,
	kNcGiContrast,
	kNcGiDrawingModeCount
} NcGiTransientDrawingMode;

// NRX-specific flags to be used in subDrawingMode parameter of addTransient()
typedef enum{
  kNcGiNonInterruptable     = 0x00000100, // Non-interruptable like cursor
  kNcGiForceRegen           = 0x00000200, // Regen on each draw
} NcGiTransientOptions;

///////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiClipBoundary
struct OdGiClipBoundary;
struct NRXDBGATE_EXPORT NcGiClipBoundary
{
	NcGiClipBoundary();
	NcGiClipBoundary(const OdGiClipBoundary& boundary);

	NcGeVector3d      m_vNormal;
	NcGePoint3d       m_ptPoint;
	NcGePoint2dArray  m_aptPoints;

	NcGeMatrix3d      m_xToClipSpace;
	NcGeMatrix3d      m_xInverseBlockRefXForm;

	double            m_dFrontClipZ;
	double            m_dBackClipZ;

	NRX::Boolean      m_bClippingFront;
	NRX::Boolean      m_bClippingBack;
	NRX::Boolean      m_bDrawBoundary;

	OdGiClipBoundary native();
};

typedef enum {
	kLineTypeSolid                            = 0x00,
	kDashed                                    = 0x01,
	kDotted                                    = 0x02,
	kDash_Dot                                = 0x03,
	kShort_Dash                                = 0x04,
	kMedium_Dash                            = 0x05,
	kLong_Dash                                = 0x06,
	kShort_Dash_X2                            = 0x07,
	kMedium_Dash_X2                            = 0x08,
	kLong_Dash_X2                            = 0x09,
	kMedium_Long_Dash                        = 0x0A,
	kMedium_Dash_Short_Dash_Short_Dash        = 0x0B,
	kLong_Dash_Short_Dash                    = 0x0C,
	kLong_Dash_Dot_Dot                        = 0x0D,
	kLong_Dash_Dot                            = 0x0E,
	kMedium_Dash_Dot_Short_Dash_Dot            = 0x0F,
	kSparse_Dot                                = 0x10,
	kISO_Dash                                = 0x11,
	kISO_Dash_Space                            = 0x12,
	kISO_Long_Dash_Dot                        = 0x13,
	kISO_Long_Dash_Double_Dot                = 0x14,
	kISO_Long_Dash_Triple_Dot                = 0x15,
	kISO_Dot                                = 0x16,
	kISO_Long_Dash_Short_Dash                = 0x17,
	kISO_Long_Dash_Double_Short_Dash        = 0x18,
	kISO_Dash_Dot                            = 0x19,
	kISO_Double_Dash_Dot                    = 0x1A,
	kISO_Dash_Double_Dot                    = 0x1B,
	kISO_Double_Dash_Double_Dot                = 0x1C,
	kISO_Dash_Triple_Dot                    = 0x1D,
	kISO_Double_Dash_Triple_Dot                = 0x1E,
	kLineTypeNone                           = 0x1F,
	kSolid_6_Pixels_Blank_6_Pixels          = 0x20
} NcGiLineType;

typedef enum {
	kNcGiWorldPosition,
	kNcGiViewportPosition,
	kNcGiScreenPosition,
	kNcGiScreenLocalOriginPosition,
	kNcGiWorldWithScreenOffsetPosition
} NcGiPositionTransformBehavior;

typedef enum {
	kNcGiWorldScale,
	kNcGiViewportScale,
	kNcGiScreenScale,
	kNcGiViewportLocalOriginScale,
	kNcGiScreenLocalOriginScale
} NcGiScaleTransformBehavior;

typedef enum {
	kNcGiWorldOrientation,
	kNcGiScreenOrientation,
	kNcGiZAxisOrientation
} NcGiOrientationTransformBehavior;

struct NcGiSentScanLines
{
	enum IsmRequestStatus {
		eOk,
		eInvalidInput,
		eInvalidColorDepth,
		eInvalidPixelRequest,
		eInvalidDeliveryMethod,
		eNoValidCompressors,
		eInsufficientMemory
	};

	NRX::Int8 *    mpPixelBuffer;
	NRX::UInt32    mRowBytes;
	void *           mpImageId;
	NRX::Int16     mIsCancelled;
	NRX::Int16     mHasFailed;
	NRX::UInt32    mBytes;
	IsmRequestStatus mRequestStatus;
};

struct NcGiRequestScanLines
{
	enum IEDitherMethod 
	{
		kIEAnyPalette,
		kCustomDithering,
		kCustomDitheringMethod
	};

	enum IEColorSystem
	{
		kBitonal,
		kCMY,
		kCMYK,
		kRGB
	};

	enum ImagePaletteType
	{
		kFromDevice,
		kFromIeWholeImage
	};

	NcGiRequestScanLines()
	    : mPixelMinX          (0)
	    , mPixelMinY          (0)
	    , mPixelMaxX          (0)
	    , mPixelMaxY          (0)
	    , mpImageId           (0)
	    , mImageOrg           (kNcGiBitonal)
	    , mImageOrient        (kNcGiXLeftToRightTopFirst)
	    , mWindowId           (0)
	    , mColorDepth         (8)
	    , mPaletteIncarnation (0)
	    , mpPalette           (0)
	    , mIsDisplay          (0)
	    , mRasterRatio        (1.0)
	    , mPaletteType        (kFromDevice)
	    , mpDataBuffer        (0)
	    , mRowWidth           (0)
	    , mpBoundaryPoints    (0)
	    , mnContours          (0)
	    , mpCounts            (0)
	    , mScalingType        (kDefaultScale)
	    , mScaleFilterType    (kDefaultScaleFilter)
	    , mRotationFilterType (kDefaultRotationFilter)
	    , mnTotalChunks       (0)
	    , mnThisChunk         (0)
	{
	}

	NRX::UInt32       mPixelMinX;
	NRX::UInt32       mPixelMinY;
	NRX::UInt32       mPixelMaxX;
	NRX::UInt32       mPixelMaxY;
	NcGePoint2d         mLowerLeft;
	NcGePoint2d         mUpperRight;
	void *              mpImageId;
	NcGiImageOrg        mImageOrg;
	NcGiImageOrient     mImageOrient;
	NRX::Int16        mWindowId;
	NRX::Int16        mColorDepth;
	union {
		NRX::Int16 mBackgroundIndex;
		NRX::Int8 mBackgroundRGB[3];
	}                mBackgroundColor;
	union {
		NRX::Int16 mTransparentIndex;
		NRX::Int8 mTransparentRGB[3];
	} mTransparentColor;
	union {
		NRX::Int16 mEntityIndex;
		NRX::Int8 mEntityRGB[3];
	}                   mEntityColor;
	NRX::Int32        mPaletteIncarnation;
	NRX::Int8 *       mpPalette;
	NRX::Int16        mIsDisplay;
	double              mRasterRatio;
	NcGeMatrix2d        mPixelToDc;
	ImagePaletteType    mPaletteType;
	void *              mpDataBuffer;
	NRX::Int32        mRowWidth;
	NRX::Int32        mNumRows;
	NRX::Int32 const *mpBoundaryPoints;
	NRX::UInt32       mnContours;
	NRX::Int32 const *mpCounts;
	NcGiScaleType          mScalingType;
	NcGiScaleFilterType    mScaleFilterType;
	NcGiRotationFilterType mRotationFilterType;
	short                  mnTotalChunks;
	short                  mnThisChunk;
};

class NcGiMaterialColor;
class NcGiMaterialMap;
class NcGiImpMaterialColor;
class NcGiImpMaterialMap;
class NcGiImpLinetypeEngine;

struct NcGsRenderStatistics
{
public:
	float fRenderTime;
	size_t iMemory;
	size_t iMaterialCount;
	size_t iLightCount;
	size_t iTriangleCount;
};

typedef double dwg3dp[3];

namespace Ntil
{
	class Image;
	class FileReadDescriptor;
	class ImageFormatCodec;
	class ProgressCallbackInterface;
};

enum NcGiHighlightStyle {
	kNcGiHighlightNone,
	kNcGiHighlightCustom,
	kNcGiHighlightDashedAndThicken,
	kNcGiHighlightDim,
	kNcGiHighlightThickDim
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
// NcCmTransparency
class OdCmTransparency;
class NcDbDwgFiler;
class NRXDBGATE_EXPORT NcCmTransparency
{
public:
	NCRX_HEAP_OPERATORS();
	typedef NcCmTransparency  wrapper_class;
	typedef OdCmTransparency  native_class;
public:
	enum transparencyMethod
	{
		kByLayer = 0, // Use the setting for the layer.
		kByBlock = 1, // Use the setting for the block.
		kByAlpha = 2, // Use the Alpha-value in this object.
		kErrorValue = 3  // Error value.
	};
	NcCmTransparency();
	NcCmTransparency(transparencyMethod method);
	NcCmTransparency(NRX::UInt8 alpha);
	NcCmTransparency(double alphaPercent);
	NcCmTransparency(const OdCmTransparency& other);

	bool operator==(
		const NcCmTransparency& transparency);
	bool operator!=(
		const NcCmTransparency& transparency);

	void setAlpha(NRX::UInt8 alpha);
	NRX::UInt8 alpha() const;

	void setAlphaPercent(
		double alphaPercent);
	double alphaPercent() const;

	transparencyMethod method() const;
	void setMethod(
		transparencyMethod method);

	bool isByAlpha() const;
	bool isByBlock() const;
	bool isByLayer() const;
	bool isInvalid() const;
	bool isClear() const;
	bool isSolid() const;

	NRX::UInt32 serializeOut();
	void serializeIn(
		NRX::UInt32 transparency);
	void dwgIn(
		NcDbDwgFiler* pFiler);
	void dwgOut(
		NcDbDwgFiler* pFiler) const;

private:
	NRX::UInt32 m_AM;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiMapper
class OdGiMapper;
class NRXDBGATE_EXPORT NcGiMapper
{
public:
	enum Projection
	{
		kInheritProjection = 0,
		kPlanar = 1,
		kBox = 2,
		kCylinder = 3,
		kSphere = 4,
		kDgnParametric = 0x32,
		kDgnPlanar = 0x33,
		kDgnCylinder = 0x34,
		kDgnCylinderCapped = 0x35,
		kDgnSphere = 0x36
	};
	enum Tiling
	{
		kInheritTiling = 0,
		kTile = 1,
		kCrop = 2,
		kClamp = 3,
		kMirror = 4
	};
	enum AutoTransform
	{
		kInheritAutoTransform = 0x0,
		kNone = 0x1,
		kObject = 0x2,
		kModel = 0x4,
		kPredefinedBim = 0x8,
	};

	static const NcGiMapper kIdentity;
	NcGiMapper();
	NcGiMapper(const NcGiMapper& mapper) = default;
	NcGiMapper(const OdGiMapper& mapper);

	NcGiMapper& operator=(const NcGiMapper& mapper) = default;
	NcGiMapper& operator=(const OdGiMapper& mapper);

	bool operator==(const NcGiMapper& mapper) const;
	bool operator!=(const NcGiMapper& mapper) const;

	void setProjection(Projection projection);
	void setUTiling(Tiling tiling);
	void setVTiling(Tiling tiling);
	void setAutoTransform(AutoTransform autoTransform);

	Projection projection() const;
	Tiling uTiling() const;
	Tiling vTiling() const;
	AutoTransform autoTransform() const;

	NcGeMatrix3d& transform();
	const NcGeMatrix3d& transform() const;
	void setTransform(const NcGeMatrix3d& tm);

private:
	Projection    m_projection;
	Tiling        m_uTiling;
	Tiling        m_vTiling;
	AutoTransform m_autoTransform;
	NcGeMatrix3d  m_transform;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiGeometry
class OdGiGeometry;
class NRXDBGATE_EXPORT NcGiGeometry : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiGeometry);

	NcGiGeometry();
	NcGiGeometry(OdRxObject* _object);

public:
	typedef NcGiGeometry  wrapper_class;
	typedef OdGiGeometry  native_class;

	enum TransparencyMode
	{
		kTransparencyOff,  // pixel alpha ignored, all pixels are opaque
		kTransparency1Bit, // pixel alpha determines transparency on/off,
		// with 0 to 254 completely transparent and 255 completely opaque
		kTransparency8Bit, // pixel alpha determines transparency level,
		// from 0 (completely transparent) to 255 (completely opaque)
	};
public:
	virtual void getModelToWorldTransform(NcGeMatrix3d& matrix) const;
	virtual void getWorldToModelTransform(NcGeMatrix3d& matrix) const;

	virtual NRX::Boolean pushModelTransform(const NcGeVector3d& normal);
	virtual NRX::Boolean pushModelTransform(const NcGeMatrix3d& matrix);
	virtual NRX::Boolean popModelTransform();

	virtual NRX::Boolean circle(const NcGePoint3d& center, const double radius, const NcGeVector3d& normal) const;
	virtual NRX::Boolean circle(const NcGePoint3d& start, const NcGePoint3d& ref, const NcGePoint3d& end) const;

	virtual NRX::Boolean circularArc(const NcGePoint3d& center, const double radius, const NcGeVector3d& normal,
	                                 const NcGeVector3d& startVector, const double sweepAngle,
	                                 const NcGiArcType type = kNcGiArcSimple) const;
	virtual NRX::Boolean circularArc(const NcGePoint3d& start, const NcGePoint3d& point, const NcGePoint3d& end,
	                                 const NcGiArcType type = kNcGiArcSimple) const;

	virtual NRX::Boolean polyline(const NRX::UInt32 num, const NcGePoint3d* vertices,
	                              const NcGeVector3d* normal = NULL,
	                              NRX::LongPtr lBaseSubEntMarker = -1) const;
	virtual NRX::Boolean polyline(const NcGiPolyline& polylineObj) const; // = 0;

	virtual NRX::Boolean polygon(const NRX::UInt32 num, const NcGePoint3d* vertices) const;

	virtual NRX::Boolean polyPolygon(const NRX::UInt32 numPolygonIndices, const NRX::UInt32* pNumPolygonPositions,
	                                 const NcGePoint3d* pPolygonPositions,const NRX::UInt32* pNumPolygonPoints,
	                                 const NcGePoint3d* polygonPoints, const NcCmEntityColor* outlineColors = NULL,
	                                 const NcGiLineType* outlineTypes = NULL, const NcCmEntityColor* fillColors = NULL,
	                                 const NcCmTransparency* fillOpacities = NULL) const;

	virtual NRX::Boolean mesh(const NRX::UInt32 rows, const NRX::UInt32 columns,
	                          const NcGePoint3d* vertices, const NcGiEdgeData* edge_data = NULL,
	                          const NcGiFaceData* face_data = NULL, const NcGiVertexData* vertex_data = NULL,
	                          const bool generate_normals = true) const;

	virtual NRX::Boolean shell(const NRX::UInt32 nbVertex, const NcGePoint3d* vertices,
	                           const NRX::UInt32 face_number, const NRX::Int32* faces,
	                           const NcGiEdgeData* edge_data = NULL, const NcGiFaceData* face_data = NULL,
	                           const NcGiVertexData* vertex_data = NULL, const struct resbuf* rb = NULL,
	                           const bool generate_normals = true) const;

	virtual NRX::Boolean text(const NcGePoint3d& position, const NcGeVector3d& normal,
	                          const NcGeVector3d& direction, const double height, const double width,
	                          const double oblique, const NCHAR* message) const;
	virtual NRX::Boolean text(const NcGePoint3d& position, const NcGeVector3d& normal,
	                          const NcGeVector3d& direction, const NCHAR* message, const NRX::Int32 length,
	                          const NRX::Boolean raw, const NcGiTextStyle& style) const;

	virtual NRX::Boolean xline(const NcGePoint3d& first, const NcGePoint3d& second) const;

	virtual NRX::Boolean ray(const NcGePoint3d& base, const NcGePoint3d& through) const;

	virtual NRX::Boolean pline(const NcDbPolyline& pline, NRX::UInt32 start = 0,
	                           NRX::UInt32 segnum = 0) const;
	virtual NRX::Boolean draw(NcGiDrawable* object) const;

	virtual NRX::Boolean pushClipBoundary(NcGiClipBoundary* boundary);
	virtual void popClipBoundary();

	virtual NRX::Boolean worldLine(const NcGePoint3d points[2]);

	virtual NRX::Boolean polypoint(const NRX::UInt32 number, const NcGePoint3d* vertices,
	                               const NcGeVector3d* normal = NULL, const NRX::Int32* marker = NULL) const;

	virtual NRX::Boolean  ellipticalArc(const NcGePoint3d&    center,
	                                    const NcGeVector3d& normal,
	                                    double              majorAxisLength,
	                                    double              minorAxisLength,
	                                    double              startDegreeInRads,
	                                    double              endDegreeInRads,
	                                    double              tiltDegreeInRads,
	                                    NcGiArcType         arcType = kNcGiArcSimple
	                                    ) const; // = 0;

	virtual NRX::Boolean  image(const NcGiImageBGRA32& imageSource,
	                            const NcGePoint3d& position,
	                            const NcGeVector3d& u,
	                            const NcGeVector3d& v,
	                            TransparencyMode transparencyMode = kTransparency8Bit
	                            ) const; // = 0;

	virtual NRX::Boolean ownerDraw(NcGiGdiDrawObject*         pObject,
	                               const NcGePoint3d&       position,
	                               const NcGeVector3d&      u,
	                               const NcGeVector3d&      v
	                               ) const
	{
		return NRX::kTrue;
	}

	virtual NRX::Boolean polyPolyline (NRX::UInt32 nbPolylines,
	                                   const NcGiPolyline* pPolylines) const; // = 0;

	virtual NcGeMatrix3d pushOrientationTransform (NcGiOrientationTransformBehavior behavior); // = 0;
	virtual NcGeMatrix3d pushPositionTransform (NcGiPositionTransformBehavior behavior, const NcGePoint3d& offset); // = 0;
	virtual NcGeMatrix3d pushPositionTransform (NcGiPositionTransformBehavior behavior, const NcGePoint2d& offset); // = 0;
	virtual NcGeMatrix3d pushScaleTransform (NcGiScaleTransformBehavior behavior, const NcGePoint3d& extents); // = 0;
	virtual NcGeMatrix3d pushScaleTransform (NcGiScaleTransformBehavior behavior, const NcGePoint2d& extents); // = 0;
	virtual NRX::Boolean  rowOfDots(int count,
	                                  const NcGePoint3d&     start,
	                                  const NcGeVector3d&     step
	                                 ) const; // = 0;

public:
	OdGiGeometry* native() const;

protected:
	friend NcGiWorldDraw;
	friend NcGiViewportDrawNrx;

	NcGiCommonDraw* m_pCommonDraw;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiWorldGeometry
class OdGiWorldGeometry;
class NRXDBGATE_EXPORT NcGiWorldGeometry : public NcGiGeometry
{
public:
	NCRX_DECLARE_MEMBERS(NcGiWorldGeometry);

	NcGiWorldGeometry();
	NcGiWorldGeometry(OdRxObject* _object);

public:
	typedef NcGiWorldGeometry  wrapper_class;
	typedef OdGiWorldGeometry  native_class;

public:
	virtual void setExtents(NcGePoint3d* pNewExtents) const;

	virtual void startAttributesSegment();

	virtual NcGeMatrix3d pushPositionTransform(NcGiPositionTransformBehavior,const NcGePoint2d &);
	virtual NcGeMatrix3d pushPositionTransform(NcGiPositionTransformBehavior,const NcGePoint3d &);
	virtual NcGeMatrix3d pushScaleTransform(NcGiScaleTransformBehavior,const NcGePoint2d &);
	virtual NcGeMatrix3d pushScaleTransform(NcGiScaleTransformBehavior,const NcGePoint3d &);
	virtual NcGeMatrix3d pushOrientationTransform(NcGiOrientationTransformBehavior);
	virtual NRX::Boolean polyline(const NcGiPolyline &) const    ;
	virtual NRX::Boolean polyline(const NRX::UInt32 num, const NcGePoint3d *vertices, const NcGeVector3d *normal = NULL,
	                              NRX::LongPtr lBaseSubEntMarker = -1) const {return __super::polyline(num,vertices,normal,lBaseSubEntMarker);}
	virtual NRX::Boolean polyPolyline(NRX::UInt32,const NcGiPolyline *) const ;
	virtual NRX::Boolean image(const NcGiImageBGRA32 &,const NcGePoint3d &,const NcGeVector3d &,const NcGeVector3d &,TransparencyMode) const     ;
	virtual NRX::Boolean rowOfDots(int,const NcGePoint3d &,const NcGeVector3d &) const;

	virtual NRX::Boolean ellipticalArc(const NcGePoint3d& center, const NcGeVector3d& normal, double majorAxisLength,
	                                   double minorAxisLength, double startDegreeInRads, double endDegreeInRads,
	                                   double tiltDegreeInRads, NcGiArcType arcType = kNcGiArcSimple) const;

public:
	OdGiWorldGeometry* native() const;
};

//////////////////////////////////////////////////////////////////////////
// OwnerDraw3d
class OwnerDraw3d {
public:
	virtual ~OwnerDraw3d(void) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiViewportGeometry
class OdGiViewportGeometry;
class NRXDBGATE_EXPORT NcGiViewportGeometry : public NcGiGeometry
{
public:
	NCRX_DECLARE_MEMBERS(NcGiViewportGeometry);

	NcGiViewportGeometry();
	NcGiViewportGeometry(OdRxObject *_object);

public:
	typedef NcGiViewportGeometry  wrapper_class;
	typedef OdGiViewportGeometry  native_class;

public:
	virtual NRX::Boolean polylineEye(const NRX::UInt32 num, const NcGePoint3d* points) const;
	virtual NRX::Boolean polygonEye(const NRX::UInt32 num, const NcGePoint3d* points) const;

	virtual NRX::Boolean polylineDc(const NRX::UInt32 num, const NcGePoint3d* points) const;
	virtual NRX::Boolean polygonDc(const NRX::UInt32 num, const NcGePoint3d* points) const;

	enum ImageSource
	{
		kFromDwg,
		kFromOleObject,
		kFromRender
	};

	virtual NRX::Boolean rasterImageDc(const NcGePoint3d& origin, const NcGeVector3d& u, const NcGeVector3d& v,
	                                   const NcGeMatrix2d& pixelToDc, NcDbObjectId entityId,
	                                   NcGiImageOrg imageOrg, NRX::UInt32 imageWidth,
	                                   NRX::UInt32 imageHeight, NRX::Int16 imageColorDepth,
	                                   NRX::Boolean transparency, ImageSource source,
	                                   const NcGeVector3d& unrotatedU, const NcGiImageOrg origionalImageOrg,
	                                   const NcGeMatrix2d& unrotatedPixelToDc,
	                                   const NRX::UInt32 unrotatedImageWidth,
	                                   const NRX::UInt32 unrotatedImageHeight) const;

	virtual NcGeMatrix3d pushPositionTransform(NcGiPositionTransformBehavior,const NcGePoint2d &);
	virtual NcGeMatrix3d pushPositionTransform(NcGiPositionTransformBehavior,const NcGePoint3d &);
	virtual NcGeMatrix3d pushScaleTransform(NcGiScaleTransformBehavior,const NcGePoint2d &);
	virtual NcGeMatrix3d pushScaleTransform(NcGiScaleTransformBehavior,const NcGePoint3d &);
	virtual NcGeMatrix3d pushOrientationTransform(NcGiOrientationTransformBehavior);
	virtual NRX::Boolean polyline(const NcGiPolyline &) const    ;
	virtual NRX::Boolean polyPolyline(NRX::UInt32,const NcGiPolyline *) const ;

	virtual NRX::Boolean polyline(const NRX::UInt32 num, const NcGePoint3d *vertices, const NcGeVector3d *normal = NULL,
		NRX::LongPtr lBaseSubEntMarker = -1) const {return __super::polyline(num,vertices,normal,lBaseSubEntMarker);}

	virtual NRX::Boolean polyPolygon(const NRX::UInt32,const NRX::UInt32 *,const NcGePoint3d *,const NRX::UInt32 *,
	                                 const NcGePoint3d *,const NcCmEntityColor *,const NcGiLineType *,const NcCmEntityColor *,const NcCmTransparency *) const ;
	virtual NRX::Boolean image(const NcGiImageBGRA32 &,const NcGePoint3d &,const NcGeVector3d &,const NcGeVector3d &,TransparencyMode) const     ;
	virtual NRX::Boolean rowOfDots(int,const NcGePoint3d &,const NcGeVector3d &) const;
	virtual NRX::Boolean ellipticalArc(const NcGePoint3d& center, const NcGeVector3d& normal, double majorAxisLength,
	                                   double minorAxisLength, double startDegreeInRads, double endDegreeInRads,
	                                   double tiltDegreeInRads, NcGiArcType arcType = kNcGiArcSimple) const;
	virtual NRX::Boolean ownerDrawDc(long vpnumber, long left, long top, long right, long bottom, const OwnerDraw *pOwnerDraw) const; // = 0;
	
	virtual NRX::Boolean ownerDraw3d(NcGePoint3d &minBounds, NcGePoint3d &maxBounds, OwnerDraw3d *pOwnerDraw)
	{
		return NRX::kFalse;
	}

public:
	OdGiViewportGeometry* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiSubEntityTraits
class OdGiSubEntityTraits;
class NRXDBGATE_EXPORT NcGiSubEntityTraits : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiSubEntityTraits);

	NcGiSubEntityTraits();
	NcGiSubEntityTraits(OdRxObject* _object);

public:
	typedef NcGiSubEntityTraits wrapper_class;
	typedef OdGiSubEntityTraits native_class;

public:
	enum DrawFlags
	{
		kNoDrawFlags,  //= ::kNoDrawFlags,
		kDrawBackfaces //= ::kDrawBackfaces,
	};

	enum ShadowFlags
	{
		kShadowsCastAndReceive = 0,   // Geometry could cast and receive shadows.
		kShadowsDoesNotCast    = 1,   // Geometry doesn't cast shadows.
		kShadowsDoesNotReceive = 2,   // Geometry doesn't receive shadows.
		kShadowsIgnore         = kShadowsDoesNotCast | kShadowsDoesNotReceive
	};

	enum SelectionFlags
	{
		kNoSelectionFlags     = 0, // No selection flags set.
		kSelectionIgnore      = 1, // Avoid geometry selection.
		kHighlightingGeometry = 2  // Geometry drawn only in case if entire entity highlighted.
	};

public:
	virtual void setColor(const NRX::UInt16 color);
	virtual void setTrueColor(const NcCmEntityColor& color);
	virtual void setLayer(const NcDbObjectId layer);
	virtual void setLineType(const NcDbObjectId linetype);
	virtual void setSelectionMarker(const NRX::LongPtr marker);
	virtual void setFillType(const NcGiFillType type);
	virtual void setLineWeight(const NcDb::LineWeight lineweight);
	virtual void setLineTypeScale(double scale = 1.0);
	virtual void setThickness(double thickness);
	virtual void setVisualStyle(const NcDbObjectId style);
	virtual Nano::ErrorStatus setEdgeStyleOverride(NcGiEdgeStyleMask mask, const NcGiEdgeStyle& edgeStyle);
	virtual void setPlotStyleName(NcDb::PlotStyleNameType type, const NcDbObjectId& id = NcDbObjectId::kNull);
	virtual void setMaterial(const NcDbObjectId material);
	virtual void setMapper(const NcGiMapper* mapper);
	virtual void setSectionable(bool bSectionable);
	virtual Nano::ErrorStatus setDrawFlags(NRX::UInt32 flags);
	virtual Nano::ErrorStatus setShadowFlags(ShadowFlags flags);
	virtual void setSelectionGeom(bool bSelectionflag);

	virtual NRX::UInt16 color() const;
	virtual NcCmEntityColor trueColor() const;
	virtual NcDbObjectId layerId() const;
	virtual NcDbObjectId lineTypeId() const;
	virtual NcGiFillType fillType() const;
	virtual NcDb::LineWeight lineWeight() const;
	virtual double lineTypeScale() const;
	virtual double thickness() const;
	virtual NcDbObjectId visualStyle() const;
	virtual Nano::ErrorStatus edgeStyleOverride(NcGiEdgeStyleMask& mask, NcGiEdgeStyle& edgeStyle) const;

	virtual NcDb::PlotStyleNameType getPlotStyleNameId(NcDbObjectId& id) const;

	virtual NcDbObjectId materialId() const;
	virtual const NcGiMapper* mapper() const;
	virtual bool sectionable() const;
	virtual NRX::UInt32 drawFlags() const;
	virtual ShadowFlags shadowFlags() const;
	virtual bool selectionGeom() const;

	virtual void setTransparency (const NcCmTransparency& transparency);
	virtual NcCmTransparency transparency (void) const;

	// NcGiDrawableTraits part
public:
	virtual void setupForEntity(NcDbEntity* entity);
	virtual void addLight(const NcDbObjectId& light);

protected:
	enum LayerFlags {
		kNone       = 0x00,
		kOff        = 0x01,
		kFrozen     = 0x02,
		kZero       = 0x04,
		kLocked     = 0x08
	};

	virtual void setLayerFlags (NRX::UInt8 flags){}

	// NcGiDrawableTraits2 part
public:
	enum HighlightProperty
	{
		kVertexRolloverHighlightSize,
	};
	virtual void              setLinePattern       (const NcGiLineType linePattern);
	virtual NcGiLineType      linePattern          (void) const;
	virtual Nano::ErrorStatus setSelectionFlags    (const SelectionFlags flags);
	virtual SelectionFlags    selectionFlags       (void) const;
	virtual Nano::ErrorStatus setHighlightProperty (HighlightProperty property,
	                                                NcGiVariant&       value);
	virtual NcGiVariant       highlightProperty    (HighlightProperty property) const;

public:
	OdGiSubEntityTraits* native() const;
protected:
  bool isThunk() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiDrawableTraits
class NcGiDrawableTraits : public NcGiSubEntityTraits
{
public:
	NCRX_DECLARE_MEMBERS(NcGiDrawableTraits);

	NcGiDrawableTraits();
	NcGiDrawableTraits(OdRxObject* _object);

#if 0 // moved to NcGiSubEntityTraits
public:
	virtual void setupForEntity(NcDbEntity* entity);
	virtual void addLight(const NcDbObjectId& light);

protected:
	enum LayerFlags {
		kNone       = 0x00,
		kOff        = 0x01,
		kFrozen     = 0x02,
		kZero       = 0x04,
		kLocked     = 0x08
	};

	virtual void setLayerFlags (NRX::UInt8 flags){}
#endif
// eliminated
//public:
//	typedef NcGiDrawableTraits wrapper_class;
//	typedef OdGiDrawableTraits native_class;
//
//	OdGiDrawableTraits* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcGiDrawableTraits2
class NRXDBGATE_EXPORT NcGiDrawableTraits2: public NcGiDrawableTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiDrawableTraits2);
	NcGiDrawableTraits2() {}
	NcGiDrawableTraits2(OdRxObject* _object) : NcGiDrawableTraits(_object) {}
#if 0 // moved to NcGiSubEntityTraits
	enum HighlightProperty
	{
		kVertexRolloverHighlightSize,
	};
	virtual void              setLinePattern       (const NcGiLineType linePattern);
	virtual NcGiLineType      linePattern          (void) const;
	virtual Nano::ErrorStatus setSelectionFlags    (const SelectionFlags flags);
	virtual SelectionFlags    selectionFlags       (void) const;
	virtual Nano::ErrorStatus setHighlightProperty (HighlightProperty property,
	                                                NcGiVariant&       value);
	virtual NcGiVariant       highlightProperty    (HighlightProperty property) const;
#endif
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiVariant
class OdGiVariant;
class NcGiVariant : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiVariant);

	typedef NcGiVariant wrapper_class;
	typedef OdGiVariant native_class;

public:
	NcGiVariant(void);
	virtual ~NcGiVariant(void);

public:
	NcGiVariant (const NcGiVariant & value);
	NcGiVariant &operator=(const NcGiVariant & value);
	virtual bool operator==(const NcGiVariant & value) const;

	virtual Nano::ErrorStatus copyFrom(const NcRxObject* other);

	enum VariantType
	{
		kUndefined = 0,
		kBoolean,
		kInt,
		kDouble,
		kColor,
		kString,
		kTable,
	};

	class EnumType
	{
	public:
		explicit EnumType(int value) :
		    m_value(value)
		{ }

		template <typename T>
		operator T ()
		{ return static_cast < T > (m_value); }

		template <typename T>
		bool operator==(T right) const
		{ return static_cast<int>(right) == m_value; }

		template <typename T>
		bool operator!=(T right) const
		{ return !(*this == right); }

	protected:
		int m_value;
	};

	NcGiVariant(bool value_);
	NcGiVariant(long value_);
	NcGiVariant(double value_);
	NcGiVariant(const NcCmColor &color_);
	NcGiVariant(const NCHAR *string_);

	VariantType type() const;

	void set(bool value_);
	void set(long value_);
	void set(double value_);
	void set(const NcCmColor &color_);
	void set(const NCHAR *string_);

	bool asBoolean() const;
	int asInt() const;
	double asDouble() const;
	NcCmColor asColor() const;
	//    NcString asString() const;

	float asFloat() const;
	char asChar() const;
	unsigned char asUchar() const;
	short asShort() const;
	unsigned short asUshort() const;
	unsigned int asUint() const;
	long asLong() const;
	unsigned long asUlong() const;
	EnumType asEnum() const;

	Nano::ErrorStatus getElem(const NCHAR *, NcGiVariant &value) const;
	const NcGiVariant *getElem(const NCHAR *) const;
	void setElem(const NCHAR *, const NcGiVariant &);
	void deleteElem(const NCHAR *);

	int getElemCount() const;

	Nano::ErrorStatus getElemAt(const int, NCHAR*&, NcGiVariant &variant_) const;
	NcGiVariant *getElemAt(const int, NCHAR*&) const;

public:
	static bool isEquivalent(NcGiVariant *first_, NcGiVariant *second_);

public:
	OdGiVariant *native() const;
};

template <typename T>
inline bool operator== (T left, const NcGiVariant::EnumType right)
{ return (right == left); }

template <typename T>
inline bool operator!= (T left, const NcGiVariant::EnumType right)
{ return (right != left); }

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiContext
class OdGiContext;
class NRXDBGATE_EXPORT NcGiContext : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiContext);

	NcGiContext();
	NcGiContext(OdRxObject* _object);

public:
	typedef NcGiContext       wrapper_class;
	typedef OdGiContext       native_class;
public:
	virtual NcDbDatabase*     database() const;
	virtual NRX::Boolean      isPsOut() const;
	virtual NRX::Boolean      isPlotGeneration() const;
	virtual bool              isBoundaryClipping() const;

	virtual void              disableFastMoveDrag() const {}
	virtual bool              isNesting() const { return false; }

	virtual NcCmEntityColor   effectiveColor()          const { return NcCmEntityColor(); }
	virtual NcDb::LineWeight  byBlockLineWeight()       const { return NcDb::kLnWt000; }
	virtual NcDbObjectId      byBlockPlotStyleNameId()  const { return NULL; }
	virtual NcDbObjectId      byBlockMaterialId()       const { return NcDbObjectId::kNull; }

	virtual bool              supportsTrueTypeText() { return false; }
	virtual bool              supportsOwnerDraw()    { return false; }
public:
	OdGiContext* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiCommonDraw
class OdGiCommonDraw;
class NRXDBGATE_EXPORT NcGiCommonDraw : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiCommonDraw);

protected:
	NcGiCommonDraw();
	NcGiCommonDraw(OdRxObject *_object);

public:
	typedef NcGiCommonDraw  wrapper_class;
	typedef OdGiCommonDraw  native_class;

public:
	virtual NcGiRegenType         regenType() const = 0;
	virtual NRX::Boolean          regenAbort() const = 0;

	virtual NcGiSubEntityTraits&  subEntityTraits() const = 0;
	virtual NcGiGeometry*         rawGeometry() const = 0;

	virtual NRX::Boolean          isDragging() const = 0;

	virtual double                deviation(const NcGiDeviationType type, const NcGePoint3d& pointOnCurve) const = 0;
	virtual NRX::UInt32           numberOfIsolines() const = 0;

	virtual NcGiContext*          context() = 0;

	virtual bool                  secondaryCall() const { return false; }
public:
	OdGiCommonDraw* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiWorldDraw
class OdGiWorldDraw;
class NRXDBGATE_EXPORT NcGiWorldDraw : public NcGiCommonDraw
{
public:
	NCRX_DECLARE_MEMBERS(NcGiWorldDraw);

protected:
	NcGiWorldDraw();
	NcGiWorldDraw(OdRxObject* _object);

public:
	typedef NcGiWorldDraw  wrapper_class;
	typedef OdGiWorldDraw  native_class;
public:
	virtual NcGiWorldGeometry& geometry() const = 0;

public:
	OdGiWorldDraw* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiViewportDrawNrx
class OdGiViewportDraw;
class NRXDBGATE_EXPORT NcGiViewportDrawNrx : public NcGiCommonDraw
{
public:
	NCRX_DECLARE_MEMBERS(NcGiViewportDrawNrx);

protected:
	NcGiViewportDrawNrx();
	NcGiViewportDrawNrx(OdRxObject* _object);

public:
	typedef NcGiViewportDrawNrx  wrapper_class;
	typedef OdGiViewportDraw  native_class;

public:
	virtual NcGiViewport&         viewport() const = 0;
	virtual NcGiViewportGeometry& geometry() const = 0;
	virtual NRX::UInt32           sequenceNumber() const = 0;
	virtual NRX::Boolean          isValidId(const NRX::ULongPtr id) const = 0;
	virtual NcDbObjectId          viewportObjectId() const = 0;

public:
	OdGiViewportDraw* native() const;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGiContextualColors
class NcGiContextualColors : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiContextualColors);

	// Access to colors.
	virtual NRX::UInt32 gridMajorLines() const = 0;
	virtual NRX::UInt32 gridMinorLines() const = 0;
	virtual NRX::UInt32 gridAxisLines() const = 0;
	virtual int gridMajorLineTintXYZ() const = 0;
	virtual int gridMinorLineTintXYZ() const = 0;
	virtual int gridAxisLineTintXYZ() const = 0;

	virtual NRX::UInt32 lightGlyphs() const = 0;
	virtual NRX::UInt32 lightHotspot() const = 0;
	virtual NRX::UInt32 lightFalloff() const = 0;
	virtual NRX::UInt32 lightStartLimit() const = 0;
	virtual NRX::UInt32 lightEndLimit() const = 0;

	virtual NRX::UInt32 cameraGlyphs() const = 0;
	virtual NRX::UInt32 cameraFrustrum() const = 0;
	virtual NRX::UInt32 cameraClipping() const = 0;

	// Access to context parameters.
	virtual void setContextFlags(NRX::UInt32 flag, bool set = true) = 0;
	virtual bool flagsSet(NRX::UInt32 flg) const = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiViewport
class OdGiViewport;
class NRXDBGATE_EXPORT NcGiViewport : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiViewport);

public:
	NcGiViewport();
	NcGiViewport(OdRxObject* _object);

public:
	typedef NcGiViewport  wrapper_class;
	typedef OdGiViewport  native_class;

public:
	virtual void getModelToEyeTransform(NcGeMatrix3d& matrix) const;
	virtual void getEyeToModelTransform(NcGeMatrix3d& matrix) const;
	virtual void getWorldToEyeTransform(NcGeMatrix3d& matrix) const;
	virtual void getEyeToWorldTransform(NcGeMatrix3d& matrix) const;

	virtual NRX::Boolean isPerspective() const;
	virtual NRX::Boolean doPerspective(NcGePoint3d& point) const;
	virtual NRX::Boolean doInversePerspective(NcGePoint3d& point) const;

	virtual void getNumPixelsInUnitSquare(const NcGePoint3d& point, NcGePoint2d& area, bool perspective = true) const;

	virtual void getCameraLocation(NcGePoint3d& location) const;
	virtual void getCameraTarget(NcGePoint3d& target) const;
	virtual void getCameraUpVector(NcGeVector3d& vector) const;

	virtual NRX::ULongPtr viewportId() const;
	virtual NRX::Int16 ncadWindowId() const;
	virtual void getViewportDcCorners(NcGePoint2d& lower_left, NcGePoint2d& upper_right) const;

	virtual NRX::Boolean getFrontAndBackClipValues(NRX::Boolean& clip_front, NRX::Boolean& clip_back,
	                                               double& front, double& back) const;

	virtual double linetypeScaleMultiplier() const;

	virtual double linetypeGenerationCriteria() const;

	virtual NRX::Boolean layerVisible(const NcDbObjectId& layer) const;

	virtual NcGeVector3d viewDir() const;

	virtual const NcGiContextualColors *contextualColors() const { return NULL; }

public:
	OdGiViewport* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiDrawable
class OdGiDrawable;
class NRXDBGATE_EXPORT NcGiDrawable : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiDrawable);

	NcGiDrawable();
	NcGiDrawable(OdRxObject* _object);
	virtual ~NcGiDrawable();

public:
	typedef NcGiDrawable  wrapper_class;
	typedef OdGiDrawable  native_class;

public:
	enum SetAttributesFlags
	{
		kDrawableNone                         = 0, // Default flags; the drawable object uses only OdGi primitives, 
		                                           // with no nested calls to draw().
		kDrawableIsAnEntity                   = 1, // Classes derived from OdDbEntity must set this flag,
		                                           // which is set by the default implementation of 
		                                           // OdDbEntity::subSetAttributes().
		kDrawableUsesNesting                  = 2, // The drawable uses nested calls to draw(), but makes no
		                                           // calls to other OdGi primatives. 
		kDrawableIsCompoundObject             = 4, // The drawable is to be treated as a block. Valid only when combined 
		                                           // with kDrawableIsAnEntity. If set, you must override 
		                                           // OdDbEntity::getCompoundObjectTransform().
		kDrawableViewIndependentViewportDraw  = 8,  // Currently not supported.
		kDrawableIsInvisible                  = 16, // Object is invisible, and should not be rendered.
		kDrawableHasAttributes                = 32, // Currently not supported.
		kDrawableRegenTypeDependantGeometry   = 64, // This flag must be set for objects which is drawn differently in different regen type modes.
		kDrawableRegenTypeDependentGeometry   = kDrawableRegenTypeDependantGeometry,
		kDrawableIsDimension                  = (kDrawableIsAnEntity + kDrawableIsCompoundObject + 128), // Dimension objects must set these flags
		                                            // which are set by the default implementation of OdDbDimension.
		kDrawableRegenDraw                    = 256, // The drawable must be always regenerated.
		kDrawableStandardDisplaySingleLOD     = 512,   // Currently not supported.
		kDrawableShadedDisplaySingleLOD       = 1024,  // Currently not supported.
		kDrawableViewDependentViewportDraw    = 2048,  // Currently not supported.
		kDrawableBlockDependentViewportDraw   = 4096,  // Currently not supported.
		kDrawableIsExternalReference          = 8192,  // Currently not supported.
		kDrawableNotPlottable                 = 16384, // Currently not supported.

		kLastFlag                             = kDrawableNotPlottable // Marker
		// kDrawableNotAllowLCS                 = 32768, // Not supported yet in Teigha
		// kDrawableMergeControlOff             = 65536  // Not supported yet in Teigha
	};

	// These are the Drawable types
	enum DrawableType
	{
		kGeometry              = 0, 
		kDistantLight          = 1, // this number is important!
		kPointLight            = 2, // this number is important!
		kSpotLight             = 3, // this number is important!
		kAmbientLight,
		kSolidBackground,
		kGradientBackground,
		kImageBackground,
		kGroundPlaneBackground,
		kViewport,
		kWebLight,
		kSkyBackground,
		kImageBasedLightingBackground
	};

public:
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source);

public:
	virtual NRX::UInt32 setAttributes(NcGiDrawableTraits* traits) sealed;

	virtual NRX::Boolean worldDraw(NcGiWorldDraw* wd) sealed;
	virtual void viewportDraw(NcGiViewportDrawNrx* vd) sealed;

	virtual NRX::UInt32 viewportDrawLogicalFlags(NcGiViewportDrawNrx* vd) sealed;

	virtual NRX::Boolean RolloverHit(NRX::ULongPtr id, NRX::ULongPtr nMouseFlags,
	                                 NRX::Boolean reset);

	virtual bool bounds(NcDbExtents& bounds) const;

	// For default attributes
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits);

	// For geometry shared between multiple viewports
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd);

	// For viewport-specific geometry
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd);

	virtual NRX::UInt32 subViewportDrawLogicalFlags (NcGiViewportDrawNrx * vd) { return 0; }

	// Persistent/transient
	virtual NRX::Boolean isPersistent() const;
	virtual NcDbObjectId id() const;

	// Drawable type.
	virtual NcGiDrawable::DrawableType drawableType() const;

	virtual void setGsNode(NcGsNode* node);
	virtual NcGsNode* gsNode() const;

public:
	OdGiDrawable* native() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiEdgeData
class OdGiEdgeData;
class NRXDBGATE_EXPORT NcGiEdgeData : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiEdgeData);

	NcGiEdgeData();
	NcGiEdgeData(const NcGiEdgeData& source);

	//NcGiEdgeData(OdRxObject *_object);

public:
	virtual ~NcGiEdgeData();

public:
	typedef NcGiEdgeData  wrapper_class;
	typedef OdGiEdgeData  native_class;

public:
	virtual NcGiEdgeData& operator=(const NcGiEdgeData& src);

	virtual void setColors(const short* colors);
	virtual void setTrueColors(const NcCmEntityColor* colors);
	virtual void setLayers(const NcDbObjectId* layers);
	virtual void setLineTypes(const NcDbObjectId* linetypes);
	virtual void setSelectionMarkers(const NRX::LongPtr* markers); // !!! Int32
	virtual void setVisibility(const NRX::UInt8* pVisibility);

	virtual short* colors() const;
	virtual NcCmEntityColor* trueColors() const;
	virtual NcDbObjectId* layerIds() const;
	virtual NcDbObjectId* linetypeIds() const;
	virtual NRX::LongPtr* selectionMarkers() const;
	virtual NRX::UInt8* visibility() const;

public:
	OdGiEdgeData* native() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiFaceData
class OdGiFaceData;
class NRXDBGATE_EXPORT NcGiFaceData : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiFaceData);

	NcGiFaceData();
	NcGiFaceData(const NcGiFaceData& source);
	//NcGiFaceData(OdRxObject *_object);

public:
	virtual ~NcGiFaceData();

public:
	typedef NcGiFaceData  wrapper_class;
	typedef OdGiFaceData  native_class;

public:
	virtual NcGiFaceData& operator=(const NcGiFaceData& src);

	virtual void setColors(const short* colors);
	virtual void setTrueColors(const NcCmEntityColor* colors);
	virtual void setLayers(const NcDbObjectId* layers);
	virtual void setSelectionMarkers(const NRX::LongPtr* markers);
	virtual void setNormals(const NcGeVector3d* normals);
	virtual void setVisibility(const NRX::UInt8* vis);
	virtual void setMaterials(const NcDbObjectId* materials);
	virtual void setMappers(const NcGiMapper* mappers);

	virtual short* colors() const;
	virtual NcCmEntityColor* trueColors() const;
	virtual NcDbObjectId* layerIds() const;
	virtual NRX::LongPtr* selectionMarkers() const;
	virtual NcGeVector3d* normals() const;
	virtual NRX::UInt8* visibility() const;
	virtual NcDbObjectId* materials() const;
	virtual NcGiMapper* mappers() const;

	//array of NcCmTransparency
	virtual void setTransparency(const NcCmTransparency *transparency);
	virtual NcCmTransparency* transparency() const;

public:
	OdGiFaceData* native() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiVertexData
class OdGiVertexData;
class NRXDBGATE_EXPORT NcGiVertexData : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiVertexData);

	NcGiVertexData();
	NcGiVertexData(const NcGiVertexData& source);
	//NcGiVertexData(OdRxObject *_object);

public:
	virtual ~NcGiVertexData();

public:
	typedef NcGiVertexData  wrapper_class;
	typedef OdGiVertexData  native_class;

	enum MapChannel
	{
		kAllChannels,
		kMapChannels
	};

public:
	virtual NcGiVertexData& operator=(const NcGiVertexData& src);

	virtual void setNormals(const NcGeVector3d* normals);
	virtual NcGeVector3d* normals() const;
	virtual void setOrientationFlag(const NcGiOrientationType type);
	virtual NcGiOrientationType orientationFlag() const;
	virtual void setTrueColors(const NcCmEntityColor* colors);
	virtual NcCmEntityColor* trueColors() const;
	NcGePoint3d* mappingCoords (MapChannel mapChannel) const;
	void setMappingCoords (MapChannel mapChannel, const NcGePoint3d* pCoords);

public:
	OdGiVertexData* native() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiTextStyle
class OdGiTextStyle;
class NRXDBGATE_EXPORT NcGiTextStyle : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiTextStyle);

	NcGiTextStyle(NcDbDatabase* pDb = NULL);
	NcGiTextStyle(const NCHAR* fontName, const NCHAR* bigFontName, const double textSize, const double xScale,
	              const double obliqueAngle, const double trPercent, const NRX::Boolean isBackward,
	              const NRX::Boolean isUpsideDown, const NRX::Boolean isVertical,
	              const NRX::Boolean isOverlined, const NRX::Boolean isUnderlined,
	              const NCHAR* styleName = NULL);

	NcGiTextStyle(OdGiTextStyle* _native);

public:
	~NcGiTextStyle();

public:
	typedef NcGiTextStyle  wrapper_class;
	typedef OdGiTextStyle  native_class;

public:
	virtual int loadStyleRec(NcDbDatabase* pDb = NULL) const;
	virtual void setTextSize(const double size);
	virtual void setXScale(const double xScale);
	virtual void setObliquingAngle(const double angle);

	virtual void setTrackingPercent(const double percent);

	virtual void setBackward(const NRX::Boolean backward);
	virtual void setUpsideDown(const NRX::Boolean upsidedown);
	virtual void setVertical(const NRX::Boolean vertical);

	virtual void setUnderlined(const NRX::Boolean underlined);
	virtual void setOverlined(const NRX::Boolean overlined);

	virtual void setFileName(const NCHAR* fontName);
	virtual void setBigFontFileName(const NCHAR* bigFontFileName);

	virtual double textSize() const;
	virtual double xScale() const;
	virtual double obliquingAngle() const;

	virtual double trackingPercent() const;

	virtual NRX::Boolean isBackward() const;
	virtual NRX::Boolean isUpsideDown() const;
	virtual NRX::Boolean isVertical() const;

	virtual NRX::Boolean isUnderlined() const;
	virtual NRX::Boolean isOverlined() const;

	virtual const NCHAR* fileName() const;
	virtual const NCHAR* bigFontFileName() const;

	virtual NcGePoint2d extents(const NCHAR* pStr, const NRX::Boolean penups, const int len,
	                            const NRX::Boolean raw, NcGiWorldDraw* ctxt = NULL) const;

	virtual const NCHAR* styleName() const;
	virtual Nano::ErrorStatus setStyleName(const NCHAR* name);

	virtual Nano::ErrorStatus setFont(const NCHAR* typeface, NRX::Boolean bold, NRX::Boolean italic,
	                                  int charset, int pitchAndFamily);

	virtual Nano::ErrorStatus font(NCHAR*& pTypeface, NRX::Boolean& bold, NRX::Boolean& italic, int& charset,
	                               int& pitchAndFamily) const;

	virtual Nano::ErrorStatus extentsBox(const NCHAR* text, const NRX::Boolean penups, const int len,
	                                     const NRX::Boolean raw, NcGePoint2d& extMin, NcGePoint2d& extMax,
	                                     NcGiWorldDraw* ctxt = NULL) const;

	virtual void setTrackKerning(double trackPercent) const;

	virtual bool preLoaded() const;
	virtual void setPreLoaded(bool);

public:
	OdGiTextStyle* native() const;

private:
	bool m_isAttached;
};

///////////////////////////////////////////////////////////////////////////////////////////
// fromNcDbTextStyle
NRXDBGATE_EXPORT Nano::ErrorStatus fromNcDbTextStyle(NcGiTextStyle& style, const NcDbObjectId& id);
NRXDBGATE_EXPORT Nano::ErrorStatus fromNcDbTextStyle(NcGiTextStyle& style, const NCHAR* name);

///////////////////////////////////////////////////////////////////////////////////////////
// toNcDbTextStyle
NRXDBGATE_EXPORT Nano::ErrorStatus toNcDbTextStyle(NcGiTextStyle& style, NcDbObjectId& id);
NRXDBGATE_EXPORT Nano::ErrorStatus toNcDbTextStyle(const NcDbObjectId id, NcGiTextStyle& style);
NRXDBGATE_EXPORT Nano::ErrorStatus toNcDbTextStyle(NcGiTextStyle& style, const NCHAR* name);
NRXDBGATE_EXPORT Nano::ErrorStatus toNcDbTextStyle(NcGiTextStyle& style, const NCHAR* name, NcDbObjectId& id);

///////////////////////////////////////////////////////////////////////////////////////////
// namespace GS
class OdGiFaceStyle;
class NRXDBGATE_EXPORT NcGiFaceStyle : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiFaceStyle);

	typedef NcGiFaceStyle wrapper_class;
	typedef OdGiFaceStyle native_class;

public:
	enum LightingModel
	{
		kInvisible,
		kConstant,
		kPhong,
		kGooch
	};

	enum LightingQuality
	{
		kNoLighting,
		kPerFaceLighting,
		kPerVertexLighting
	};

	enum FaceColorMode
	{
		kNoColorMode,
		kObjectColor,
		kBackgroundColor,
		kMono,
		kTint,
		kDesaturate
	};

	enum FaceModifier
	{
		kNoFaceModifiers = 0,
		kOpacity         = 1,
		kSpecular        = 2
	};

public:
	NcGiFaceStyle();
	NcGiFaceStyle(const NcGiFaceStyle& style);

public:
	virtual ~NcGiFaceStyle();

public:
	virtual void set(const NcGiFaceStyle& style);

public:
	virtual NcGiFaceStyle& operator=(const NcGiFaceStyle& style);
	virtual bool operator==(const NcGiFaceStyle& style) const;

public:
	virtual void setLightingModel(LightingModel model);
	virtual LightingModel lightingModel() const;

public:
	virtual void setLightingQuality(LightingQuality lightingQuality);

	virtual LightingQuality lightingQuality() const;

	virtual void setFaceColorMode(FaceColorMode mode);

	virtual FaceColorMode faceColorMode() const;

	virtual void setFaceModifiers(unsigned long nModifiers);

	virtual void setFaceModifierFlag(FaceModifier flag, bool enable);

	virtual unsigned long faceModifiers() const;

	virtual bool isFaceModifierFlagSet(FaceModifier flag) const;

	virtual void setOpacityLevel(double nLevel, bool bEnableModifier);
	virtual double opacityLevel() const;

	virtual void setSpecularAmount(double nAmount, bool bEnableModifier);

	virtual double specularAmount() const;

	virtual void setMonoColor(const NcCmColor& color, bool bEnableMode);

	virtual const NcCmColor& monoColor() const;

	virtual NcCmColor& monoColor();

public:
	OdGiFaceStyle *native() const;
};

////////////////////////////////////////////////////////////////////////
// class NcGiEdgeStyle
class OdGiEdgeStyle;
class NRXDBGATE_EXPORT NcGiEdgeStyle : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiEdgeStyle);

	typedef NcGiEdgeStyle  wrapper_class;
	typedef OdGiEdgeStyle  native_class;

public:
	enum EdgeModel
	{
		kNoEdges,
		kIsolines,
		kFacetEdges
	};

	enum EdgeStyle
	{
		kNoEdgeStyle  = 0,
		kVisible      = 1,
		kSilhouette   = 2,
		kObscured     = 4,
		kIntersection = 8
	};

	enum EdgeModifier
	{
		kNoEdgeModifiers = 0,
		kOverhang        = 1,
		kJitter          = 2,
		kWidth           = 4,
		kColor           = 8,
		kHaloGap         = 16,
		kAlwaysOnTop     = 64,
		kOpacity         = 128,
	};

	enum JitterAmount
	{
		kJitterLow = 1,
		kJitterMedium,
		kJitterHigh,
	};

	enum Linetype
	{
		kSolid = 1,
		kDashed,
		kDotted,
		kShortDash,
		kMediumDash,
		kLongDash,
		kDoubleShortDash,
		kDoubleMediumDash,
		kDoubleLongDash,
		kMediumLongDash,
		kSparseDot
	};

	enum EdgeStyleApply
	{
		kDefault,
		kAll
	};

public:
	NcGiEdgeStyle();
	NcGiEdgeStyle(const NcGiEdgeStyle& style);

	virtual ~NcGiEdgeStyle();

public:
	virtual void set(const NcGiEdgeStyle& style);

public:
	virtual NcGiEdgeStyle& operator=(const NcGiEdgeStyle& style);

	virtual bool operator==(const NcGiEdgeStyle& style) const;

public:
	virtual void setEdgeModel(EdgeModel model);
	virtual EdgeModel edgeModel() const;

	virtual void setEdgeStyles(unsigned long nStyles);
	virtual void setEdgeStyleFlag(EdgeStyle flag, bool enable);

	virtual unsigned long edgeStyles() const;
	virtual bool isEdgeStyleFlagSet(EdgeStyle flag) const;

	virtual void setIntersectionColor(const NcCmColor& color);
	virtual const NcCmColor& intersectionColor() const;

	virtual NcCmColor& intersectionColor();
	virtual void setObscuredColor(const NcCmColor& color);

	virtual const NcCmColor& obscuredColor() const;
	virtual NcCmColor& obscuredColor();

	virtual void setObscuredLinetype(Linetype ltype);
	virtual Linetype obscuredLinetype() const;

	virtual void setIntersectionLinetype(Linetype ltype);
	virtual Linetype intersectionLinetype() const;

	virtual void setCreaseAngle(double nAngle);
	virtual double creaseAngle() const;

public:
	virtual void setEdgeModifiers(unsigned long nModifiers);
	virtual unsigned long edgeModifiers() const;

	virtual void setEdgeModifierFlag(EdgeModifier flag, bool enable);
	virtual bool isEdgeModifierFlagSet(EdgeModifier flag) const;

public:
	virtual void setEdgeColor(const NcCmColor& color, bool bEnableModifier);
	virtual const NcCmColor& edgeColor() const;
	virtual NcCmColor& edgeColor();

	virtual void setOpacityLevel(double nLevel, bool bEnableModifier);
	virtual double opacityLevel() const;

	virtual void setEdgeWidth(int nWidth, bool bEnableModifier);
	virtual int edgeWidth() const;

	virtual void setOverhangAmount(int nAmount, bool bEnableModifier);
	virtual int overhangAmount() const;

	virtual void setJitterAmount(JitterAmount amount, bool bEnableModifier);
	virtual JitterAmount jitterAmount() const;

	virtual void setSilhouetteColor(const NcCmColor& color);
	virtual const NcCmColor& silhouetteColor() const;
	virtual NcCmColor& silhouetteColor();

	virtual void setSilhouetteWidth(short nWidth);
	virtual short silhouetteWidth() const;

	virtual void setHaloGap(int nHaloGap, bool bEnableModifier);
	virtual int haloGap() const;

	virtual void setIsolines(unsigned short nIsolines);
	virtual unsigned short isolines() const;

	virtual void setHidePrecision(bool bHidePrecision);
	virtual bool hidePrecision() const;

	virtual void setEdgeStyleApply(EdgeStyleApply apply);
	virtual EdgeStyleApply edgeStyleApply() const;

public:
	OdGiEdgeStyle *native() const;
};

////////////////////////////////////////////////////////////////////////
// class NcGiDisplayStyle
class OdGiDisplayStyle;
class NRXDBGATE_EXPORT NcGiDisplayStyle : public NcRxObject
{
public:
	typedef NcGiDisplayStyle wrapper_class;
	typedef OdGiDisplayStyle native_class;

public:
	enum DisplaySettings
	{
		kNone        = 0,
		kBackgrounds = 1,
		kLighting    = 2,
		kMaterials   = 4,
		kTextures    = 8
	};

	enum ShadowType
	{
		kShadowsNone,
		kShadowsGroundPlane,
		kShadowsFull,
		kShadowsFullAndGround,
	};

	NCRX_DECLARE_MEMBERS(NcGiDisplayStyle);

public:
	NcGiDisplayStyle();
	NcGiDisplayStyle(const NcGiDisplayStyle& style);

public:
	virtual ~NcGiDisplayStyle();

public:
	virtual void set(const NcGiDisplayStyle& style);

public:
	virtual NcGiDisplayStyle& operator=(const NcGiDisplayStyle& style);

	virtual bool operator==(const NcGiDisplayStyle& style) const;

public:
	virtual void setDisplaySettings(unsigned long nSettings);
	virtual unsigned long displaySettings() const;

	virtual void setDisplaySettingsFlag(DisplaySettings flag, bool enable);
	virtual bool isDisplaySettingsFlagSet(DisplaySettings flag) const;

	virtual void setBrightness(double value);
	virtual double brightness() const;

	virtual void setShadowType(ShadowType type);
	virtual ShadowType shadowType() const;

public:
	OdGiDisplayStyle *native() const;
};

namespace NcGiVisualStyleProperties
{
	enum Property
	{
		kInvalidProperty = -1,
		kFaceLightingModel,
		kFaceLightingQuality,
		kFaceColorMode,
		kFaceModifiers,
		kFaceOpacity,
		kFaceSpecular,
		kFaceMonoColor,
		kEdgeModel,
		kEdgeStyles,
		kEdgeIntersectionColor,
		kEdgeObscuredColor,
		kEdgeObscuredLinePattern,
		kEdgeIntersectionLinePattern,
		kEdgeCreaseAngle,
		kEdgeModifiers,
		kEdgeColor,
		kEdgeOpacity,
		kEdgeWidth,
		kEdgeOverhang,
		kEdgeJitterAmount,
		kEdgeSilhouetteColor,
		kEdgeSilhouetteWidth,
		kEdgeHaloGap,
		kEdgeIsolines,
		kEdgeHidePrecision,
		kDisplayStyles,
		kDisplayBrightness,
		kDisplayShadowType,
		kPropertyCount
	};

	enum FaceLightingModel
	{
		kInvisible,
		kConstant,
		kPhong,
		kGooch
	};

	enum FaceLightingQuality
	{
		kNoLighting,
		kPerFaceLighting,
		kPerVertexLighting,
		kPerPixelLighting
	};

	enum FaceColorMode
	{
		kNoColorMode,
		kObjectColor,
		kBackgroundColor,
		kMono,
		kTint,
		kDesaturate
	};

	enum FaceModifiers
	{
		kNoFaceModifiers    = 0,
		kFaceOpacityFlag    = 1,
		kSpecularFlag       = 2
	};

	enum  EdgeModel
	{
		kNoEdges,
		kIsolines,
		kFacetEdges
	};

	enum EdgeStyles
	{
		kNoEdgeStyle        =  0,
		kVisibleFlag        =  1,
		kSilhouetteFlag     =  2,
		kObscuredFlag       =  4,
		kIntersectionFlag   = 8
	};

	enum EdgeModifiers
	{
		kNoEdgeModifiers    =   0,
		kEdgeOverhangFlag       =   1,
		kEdgeJitterFlag     =   2,
		kEdgeWidthFlag      =   4,
		kEdgeColorFlag      =   8,
		kEdgeHaloGapFlag    =  16,
		kAlwaysOnTopFlag    =  64,
		kEdgeOpacityFlag        = 128,
	};

	enum EdgeJitterAmount
	{
		kJitterLow = 1,
		kJitterMedium,
		kJitterHigh,
	};

	enum EdgeLinePattern
	{
		kSolid = 1,
		kDashedLine,
		kDotted,
		kShortDash,
		kMediumDash,
		kLongDash,
		kDoubleShortDash,
		kDoubleMediumDash,
		kDoubleLongDash,
		kMediumLongDash,
		kSparseDot
	};

	enum DisplayStyles
	{
		kNoDisplayStyle      =  0,
		kBackgroundsFlag     =  1,
		kLightingFlag        =  2,
		kMaterialsFlag       =  4,
		kTexturesFlag        =  8,
	};

	enum DisplayShadowType
	{
		kShadowsNone,
		kShadowsGroundPlane,
		kShadowsFull,
		kShadowsFullAndGround,
	};
};

namespace NcGiVisualStyleOperations
{
	enum Operation
	{
		kInvalidOperation = -1,
		kInherit = 0,
		kSet,
		kDisable,
		kEnable
	};
};

////////////////////////////////////////////////////////////////////////
// class NcGiVisualStyle
class OdGiVisualStyle;
class NRXDBGATE_EXPORT NcGiVisualStyle : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiVisualStyle);

	typedef NcGiVisualStyleProperties::Property Property;
	typedef NcGiVisualStyleOperations::Operation Operation;

	enum Type
	{
		kFlat,
		kFlatWithEdges,
		kGouraud,
		kGouraudWithEdges,
		k2DWireframe,
		k3DWireframe,
		kHidden,
		kBasic,
		kRealistic,
		kConceptual,
		kCustom,
		kDim,
		kBrighten,
		kThicken,
		kLinePattern,
		kFacePattern,
		kColorChange
	};

public:
	NcGiVisualStyle();
	NcGiVisualStyle(Type type);
	NcGiVisualStyle(const NcGiVisualStyle& visualStyle);

	NcGiVisualStyle(OdRxObject* _object);

	~NcGiVisualStyle();

public:
	typedef NcGiVisualStyle  wrapper_class;
	typedef OdGiVisualStyle  native_class;

public:
	NcGiVisualStyle& operator=(const NcGiVisualStyle& visualStyle);

	bool operator==(const NcGiVisualStyle& visualStyle) const;

public:
	void configureForType(Type type);

	NcGiFaceStyle& faceStyle();
	NcGiEdgeStyle& edgeStyle();
	NcGiDisplayStyle& displayStyle();

	const NcGiFaceStyle& faceStyle() const;
	const NcGiEdgeStyle& edgeStyle() const;
	const NcGiDisplayStyle& displayStyle() const;

	void setFaceStyle(const NcGiFaceStyle& style);
	void setEdgeStyle(const NcGiEdgeStyle& style);
	void setDisplayStyle(const NcGiDisplayStyle& style);

	virtual Operation operation (Property prop) const;
	static NcGiVariant::VariantType propertyType(Property prop);
	virtual bool setTrait (Property prop, Operation op);
	virtual bool setTrait (Property prop,
	                       bool bVal, Operation op = NcGiVisualStyleOperations::kSet);
	virtual bool setTrait (Property prop, const NcCmColor*pColor,
	                       Operation op = NcGiVisualStyleOperations::kSet);
	virtual bool setTrait (Property prop, const NcGiVariant*pVal,
	                       Operation op = NcGiVisualStyleOperations::kSet);
	virtual bool setTrait (Property prop, double red, double green, double blue,
	                       Operation op = NcGiVisualStyleOperations::kSet);
	virtual bool setTrait (Property prop,double dVal,
	                       Operation op = NcGiVisualStyleOperations::kSet);
	virtual bool setTrait (Property prop, int nVal,
	                       Operation op = NcGiVisualStyleOperations::kSet);
	virtual bool setTraitFlag(Property flagProp,
	                          NRX::UInt32 flagVal,
	                          bool bEnable = true);
	bool setType(Type type);
	virtual const NcGiVariant& trait (Property prop,
	                                  Operation *pOp = NULL) const;
	virtual bool traitFlag (Property flagProp,
	                        NRX::UInt32 flagVal) const;
	Type type (void) const;

private:
	void configureForFlat();
	void configureForFlatWithEdges();
	void configureForGouraud();
	void configureForGouraudWithEdges();
	void configureForBasic();
	void configureFor2DWireframe();
	void configureFor3DWireframe();
	void configureForHidden();
	void configureForRealistic();
	void configureForConceptual();
	void configureForDim();
	void configureForBrighten();
	void configureForThicken();
	void configureForLinePattern();
	void configureForFacePattern();
	void configureForColorChange();

	NcGiFaceStyle mFaceStyle;
	NcGiEdgeStyle mEdgeStyle;
	NcGiDisplayStyle mDisplayStyle;

public:
	OdGiVisualStyle* native() const;
};

////////////////////////////////////////////////////////////////////////
// class NcGiVisualStyleTraits
class NRXDBGATE_EXPORT NcGiVisualStyleTraits : public NcGiDrawableTraits
{
public:
	NCRX_DECLARE_MEMBERS(NcGiVisualStyleTraits);

	virtual void setNcGiVisualStyle(const NcGiVisualStyle& visualStyle) = 0;

	virtual const NcGiVisualStyle& ncgiVisualStyle() const = 0;
};

////////////////////////////////////////////////////////////////////////
// class NcGiGlyph
class NRXDBGATE_EXPORT NcGiGlyph : public NcGiDrawable
{
public:
	NCRX_DECLARE_MEMBERS(NcGiGlyph);

	NcGiGlyph(){}
	NcGiGlyph(OdRxObject* _object);

public:
	typedef NcGiGlyph  wrapper_class;
	//    typedef OdGiGlyph native_class;

public:
	virtual Nano::ErrorStatus setLocation(const NcGePoint3d& point);

	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits)
	{
		return 0;
	}

	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw*)
	{
		return NRX::kFalse;
	}

	virtual void subViewportDraw(NcGiViewportDrawNrx* context);

	virtual NRX::Boolean isPersistent() const
	{
		return NRX::kFalse;
	}
	virtual NcDbObjectId id() const
	{
		return NcDbObjectId::kNull;
	}
	virtual void setGsNode(NcGsNode* node) {}
	virtual NcGsNode* gsNode() const
	{
		return NULL;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////
// namespace GS
namespace GS
{
	enum ErrorStatus
	{
		kSuccess,
		kOutOfRange,
		kInvalidInput
	};

	enum DeviceType
	{
		kScreenDevice    = 0,
		kOffScreenDevice = 1,
		kSelectionDevice = 2
	};

	enum HighlightStyle
	{
		kHighlightDashed           = 0,
		kHighlightThicken          = 1,
		kHighlightDashedAndThicken = 2,
		kHighlightCustom           = 3
	};
};

#define SCALAR_MIN  (-2147483647 - 1) // minimum(signed) int value
#define SCALAR_MAX  2147483647 // maximum(signed) int value

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsDCPoint
class NRXDBGATE_EXPORT NcGsDCPoint
{
public:
	enum MaxFlag { Maximum };
	enum MinFlag { Minimum };

public:
	NcGsDCPoint();
	NcGsDCPoint(const NcGsDCPoint& src);
	NcGsDCPoint(long xin, long yin);

	NcGsDCPoint(NcGsDCPoint::MaxFlag flag);
	NcGsDCPoint(NcGsDCPoint::MinFlag flag);

	NcGsDCPoint(const OdGsDCPoint* src);
	virtual ~NcGsDCPoint();

	NcGsDCPoint& operator=(const OdGsDCPoint* src);
	bool operator!=  (NcGsDCPoint const & r) const;
	void operator=   (NcGsDCPoint const & r);
	void operator=   (MaxFlag);
	void operator=   (MinFlag);
	bool operator==  (NcGsDCPoint const & r) const;

public:
	long x;
	long y;

	OdGsDCPoint* native() const;

protected:
	OdGsDCPoint* m_pNative;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsDCRect
class NRXDBGATE_EXPORT NcGsDCRect
{
public:
	enum NullFlag { Null };

public:
	NcGsDCRect();
	NcGsDCRect(const NcGsDCRect& src);
	NcGsDCRect(const NcGsDCPoint& min, const NcGsDCPoint& max);
	NcGsDCRect(long l, long r, long b, long t);
	NcGsDCRect(NcGsDCRect::NullFlag flag);

	NcGsDCRect(const OdGsDCRect* src);
	virtual ~NcGsDCRect();

	NcGsDCRect& operator=(const OdGsDCRect* src);
	NcGsDCRect &NcGsDCRect::operator= (NcGsDCRect const & other);

	bool is_null (void) const;
	bool operator!= (NcGsDCRect const & rightside) const;
	bool operator== (NcGsDCRect const & rightside) const;
	void set_null (void);
	bool within (NcGsDCRect const & rightside) const;

public:
	NcGsDCPoint m_min;
	NcGsDCPoint m_max;

	OdGsDCRect* native() const;

protected:
	OdGsDCRect* m_pNative;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsColor
struct NcGsColor
{
	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;
	unsigned char m_filler;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsWindowingSystemID -> HWND
typedef void*  NcGsWindowingSystemID;
typedef void* NcGsWindowId;

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsNode
class OdGsNode;
class NRXDBGATE_EXPORT NcGsNode
{
public:
	NcGsNode();
	NcGsNode(OdGsNode *pNative);

	virtual ~NcGsNode();
	virtual NcGiDrawable* drawable() const;
	virtual void setDrawableNull();

	OdGsNode *native() const;

	mutable NcGiDrawable* m_pDrawable;
	OdGsNode* m_pNative;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsView
class OdGsView;
class NRXDBGATE_EXPORT NcGsView
{
public:
	enum RenderMode
	{
		k2DOptimized, // Standard AutoCAD 2D Display
		kBoundingBox, // Bounding Box(when simpler than the geometry)
		kWireframe, // Same display as k2Doptimized(but using the 3D Pipeline)
		kHiddenLine, // Wireframe display with hidden lines removed
		kFlatShaded, // Faceted - constant color per face
		kGouraudShaded, // Smooth shaded - colors interpolated between vertices
		kFlatShadedWithWireframe, // Faceted with wireframe overlayed
		kGouraudShadedWithWireframe, // Smooth shaded with wireframe overlayed
		kCount,
		kNone = kCount
	};

	enum Projection
	{
		kParallel,
		kPerspective
	};

	enum SelectionMode
	{
		kWindow,
		kCrossing,
		kFence,
		kWPoly,
		kCPoly,
	};

	enum DefaultLightingType
	{
		kOneLight,
		kTwoLights
	};

public:
	NcGsView(OdGsView* _object);

public:
	virtual ~NcGsView();

public:
	typedef NcGsView  wrapper_class;
	typedef OdGsView  native_class;

public:
	virtual void setViewport(const NcGePoint2d& lower_left, const NcGePoint2d& upper_right);
	virtual void setViewport(const NcGsDCRect& screen_rect);
	virtual void getViewport(NcGePoint2d& lower_left, NcGePoint2d& upper_right) const;
	virtual void getViewport(NcGsDCRect& screen_rect) const;


public:
	virtual void setViewportClipRegion(int contours, const int* counts, const NcGsDCPoint* points);
	virtual void removeViewportClipRegion();

public:
	virtual void setViewportBorderProperties(const NcGsColor& color, int weight);
	virtual void getViewportBorderProperties(NcGsColor& color, int& weight) const;

	virtual void setViewportBorderVisibility(bool visible);
	virtual bool isViewportBorderVisible() const;

public:
	virtual void setView(const NcGePoint3d& position, const NcGePoint3d& target, const NcGeVector3d& vector,
	                     double field_width, double field_height, Projection projection = kParallel);

	virtual NcGePoint3d position() const;
	virtual NcGePoint3d target() const;
	virtual NcGeVector3d upVector() const;
	virtual bool isPerspective() const;
	virtual double fieldWidth() const;
	virtual double fieldHeight() const;

public:
	virtual void setEnableFrontClip(bool enable);
	virtual bool isFrontClipped() const;
	virtual void setFrontClip(double distance);
	virtual double frontClip() const;

	virtual void setEnableBackClip(bool enable);
	virtual bool isBackClipped() const;
	virtual void setBackClip(double distance);
	virtual double backClip() const;

public:
	virtual NcGeMatrix3d viewingMatrix() const;
	virtual NcGeMatrix3d projectionMatrix() const;
	virtual NcGeMatrix3d screenMatrix() const;
	virtual NcGeMatrix3d worldToDeviceMatrix() const;
	virtual NcGeMatrix3d objectToDeviceMatrix() const;

public:
#ifndef ODGI_NO_RENDER_MODE
	virtual void setMode(RenderMode mode);
	virtual RenderMode mode() const;
#endif

public:
	virtual bool add(NcGiDrawable* drawable, NcGsModel* model);
	virtual bool erase(NcGiDrawable* drawable);
	virtual void eraseAll();

public:
	virtual void invalidate();
	virtual void invalidate(const NcGsDCRect& rect);
	virtual bool isValid() const;

public:
	virtual void update();
	virtual void beginInteractivity(double frame_rate);
	virtual void endInteractivity();
	virtual void flush();

public:
	virtual void setMaximumUpgrade(int step);
	virtual int maximumUpgrade();
	virtual void setMinimumDegrade(int step);
	virtual int minimumDegrade();

public:
	virtual void hide();
	virtual void show();
	virtual bool isVisible();

public:
	virtual void freezeLayer(LONG_PTR id);
	virtual void thawLayer(LONG_PTR id);
	virtual void clearFrozenLayers();

public:
	virtual void invalidateCachedViewportGeometry();

public:
	virtual void dolly(const NcGeVector3d& vector);
	virtual void dolly(double x, double y, double z);
	virtual void roll(double angle);
	virtual void orbit(double x, double y);
	virtual void zoom(double factor);
	virtual void zoomExtents(const NcGePoint3d& min, const NcGePoint3d& max);
	virtual void zoomWindow(const NcGePoint2d& lower_left, const NcGePoint2d& upper_right);
	virtual void pan(double x, double y);

	virtual bool pointInView(const NcGePoint3d& point);
	virtual bool extentsInView(const NcGePoint3d& min, const NcGePoint3d& max);

	virtual NcGsView* clone(bool vlone_parameters = true, bool clone_geometry = false);

public:
	virtual bool exceededBounds();

public:
	virtual void enableStereo(bool enable);
	virtual bool isStereoEnabled() const;
	virtual void setStereoParameters(double magnitude, double parallax);
	virtual void getStereoParameters(double& magnitude, double& parallax) const;

public:
	virtual void getSnapShot(Ntil::Image *output, NcGsDCPoint const &offset);
	virtual bool RenderToImage(Ntil::Image* output, NcGiDrawable *settings, void *progress_monitor, const NcGsDCRect &rect, bool reuse = false);

public:
	virtual NcGsDevice* getDevice() const;

public:
	virtual void setVisualStyle(const NcDbObjectId style);
	virtual NcDbObjectId visualStyle() const;
	virtual void setVisualStyle(const NcGiVisualStyle& style);
	virtual bool visualStyle(NcGiVisualStyle& style) const;

public:
	virtual void setBackground(const NcDbObjectId id);
	virtual NcDbObjectId background() const;

public:
	virtual void enableDefaultLighting(bool enable, DefaultLightingType type = kTwoLights);

	virtual void getNumPixelsInUnitSquare(const NcGePoint3d& givenWorldpt, NcGePoint2d& pixelArea,
	                                      bool perspective = true) const;
	virtual bool isInteractive (void) const;
public:
	OdGsView* native() const;

protected:
	OdGsView* m_pNative;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsModel
//
// Lion007 note : make it semi-abstract. All the logic live in base NcGsModel class,
//                but actual native() method reside in derived classes.
//                See NcGsModelImpl and NcGsDocModelImpl (graphics.cpp)
///////////////////////////////////////////////////////////////////////////////////////////
class OdGsModel;
class NRXDBGATE_EXPORT NcGsModel
{
public:
	enum RenderType
	{
		kMain, // Use main Z-buffer
		kSprite, // Use alternate Z-buffer, for sprites
		kDirect, // Render into frame buffer without the z-test
		kHighlight, // Render directly onto the device(skipping the frame buffer and the z-test)
		kHighlightSelection, // Render directly onto the device in selection highlight style(internal only)
		kCount // Count of RenderTypes
	};

	enum InvalidationHint
	{
		kInvalidateNone,
		kInvalidateIsolines,
		kInvalidateViewportCache,
		kInvalidateAll,
		kInvalidateAllStatic,
		kInvalidateFacets,
		kInvalidateFills,
		kInvalidateLinetypes,
		kInvalidateMaterials,
	};

public:
	//NcGsModel(OdGsModel* _object, NcApDocument * pDoc/* = NULL*/);

public:
	virtual ~NcGsModel();

public:
	typedef NcGsModel  wrapper_class;
	typedef OdGsModel  native_class;

public:
	virtual bool addSceneGraphRoot(NcGiDrawable* root);
	virtual bool eraseSceneGraphRoot(NcGiDrawable* root);

public:
	virtual void onAdded(NcGiDrawable* added, NcGiDrawable* parent);
	virtual void onAdded(NcGiDrawable* added, LONG_PTR parentID);

	virtual void onModified(NcGiDrawable* modified, NcGiDrawable* parent);
	virtual void onModified(NcGiDrawable* modified, LONG_PTR parentID);

	virtual void onErased(NcGiDrawable* erased, NcGiDrawable* parent);
	virtual void onErased(NcGiDrawable* erased, LONG_PTR parentID);

	virtual void onPaletteModified();

public:
	virtual void setTransform(const NcGeMatrix3d&);
	virtual NcGeMatrix3d transform() const;
	virtual void setExtents(const NcGePoint3d&, const NcGePoint3d&);

public:
	virtual void invalidate(InvalidationHint hint);

public:
	virtual void setViewClippingOverride(bool enable);
	virtual void setRenderModeOverride(NcGsView::RenderMode mode = NcGsView::kNone);

public:
	virtual void setVisualStyle(const NcDbObjectId style);
	virtual NcDbObjectId visualStyle() const;
	virtual void setVisualStyle(const NcGiVisualStyle& style);
	virtual bool visualStyle(NcGiVisualStyle& style) const;

public:
	virtual void setBackground(const NcDbObjectId background);
	virtual NcDbObjectId background() const;

public:
	virtual void enableLinetypes(bool enable);
	virtual bool linetypesEnabled() const;

public:
	virtual void setEnableSectioning(bool enable);
	virtual bool isSectioningEnabled() const;
	virtual bool setSectioning(const NcGePoint3dArray& points, const NcGeVector3d& vector);
	virtual bool setSectioning(const NcGePoint3dArray& points, const NcGeVector3d& vector, double top, double bottom);
	virtual void setSectioningVisualStyle(const NcDbObjectId style);

public:
	virtual RenderType renderType();

public:
	virtual double shadowPlaneLocation() const;
	virtual void setShadowPlaneLocation(double location);

	virtual bool selectable(void) const; // = 0;
	virtual void setSelectable(bool bEnable); // = 0;

public:
	OdGsModel * native() const;
  virtual OdGsModel * subNative() const = 0;
  static NcGsModel * getDbModel(); // Lion007 : get\create GsModel for current doc
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsDevice
class OdGsDevice;
class NRXDBGATE_EXPORT NcGsDevice
{
public:
	enum RendererType
	{
		kDefault,
		kSoftware,
		kSoftwareNewViewsOnly,
		kFullRender,
		kSelectionRender
	};

public:
	NcGsDevice(OdGsDevice* _object);

public:
	virtual ~NcGsDevice();

public:
	typedef NcGsDevice  wrapper_class;
	typedef OdGsDevice  native_class;

public:
	virtual void invalidate();
	virtual void invalidate(const NcGsDCRect& rect);
	virtual bool isValid() const;

public:
	virtual void update(NcGsDCRect* rect = NULL);

public:
	virtual void onSize(int width, int height);
	virtual void onRealizeForegroundPalette();
	virtual void onRealizeBackgroundPalette();
	virtual void onDisplayChange(int bits_per_pixel, int xres, int yres);

public:
	virtual bool add(NcGsView* view);
	virtual bool erase(NcGsView* view);
	virtual void eraseAll();

	virtual bool setBackgroundColor(NcGsColor color);
	virtual NcGsColor getBackgroundColor();

	virtual void setLogicalPalette(const NcGsColor* palette, int count);
	virtual void setPhysicalPalette(const NcGsColor* palette, int count);

public:
	virtual void getSnapShot(Ntil::Image *output, NcGsDCPoint const & offset);

public:
	virtual void setDeviceRenderer(RendererType type);
	virtual RendererType getDeviceRenderer();

	virtual NcGsModel* createModel();
	virtual NcGsView* createView();
public:
	OdGsDevice* native() const;
private:
	NRX::UInt32 *odPalette;

protected:
	OdGsDevice* m_pNative;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsManager
class NcGsManager
{
public:
	NcGsManager() {}
	virtual ~NcGsManager() {}

	virtual NcGsModel* createAutoCADModel() = 0;
	virtual NcGsView* createAutoCADViewport(NcDbViewportTableRecord* record) = 0;
	virtual NcGsView* createAutoCADView(NcGiDrawable* drawable) = 0;

public:
	virtual NcGsDevice* createAutoCADDevice(HWND hWnd) = 0;
	virtual NcGsDevice* createAutoCADOffScreenDevice() = 0;

	virtual void destroyAutoCADModel(NcGsModel* model) = 0;
	virtual void destroyAutoCADView(NcGsView* view) = 0;
	virtual void destroyAutoCADDevice(NcGsDevice* device) = 0;

	virtual NcGsClassFactory* getGSClassFactory() = 0;
	virtual NcGsModel* getDBModel() = 0;
	virtual NcGsDevice* getGUIDevice() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsDrawablePath
struct NcGsDrawableLink
{
	LONG_PTR id;
	NcGiDrawable *pDrawable;
	NcGsNode *pNode;
};

typedef NcArray<NcGsDrawableLink> NcGsDrawablePath;

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsClientViewInfo
struct NcGsClientViewInfo
{
	NcGsClientViewInfo();

	LONG_PTR              viewportId;
	LONG_PTR              ncadWindowId;
	LONG_PTR              viewportObjectId;
	NcGiContextualColors* contextColors;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsConfig
class NcGsConfig
{
public:
	enum Handedness
	{
		kLeft,
		kRight
	};

	enum Quality
	{
		kLowQuality,
		kMediumQuality,
		kHighQuality
	};

	enum DegradationChannel
	{
		kViewportDraw,
		kLineAntialias,
		kLighting,
		kTransparencyQuality,
		kShadowsFull,
		kTransparency,
		kDiscardBackfaces,
		kShadowsGround,
		kEdgeStyles,
		kFacetEdges,
		kFastSilhouette,
		kTextures,
		kMaterials,
		kLightingQuality,
		kBackgrounds,
		kIntersectEdges,
		kFaceted,
		kWireframe,
		kDegradationChannels
	};

	enum HardwareFeature
	{
		kHwAcceleration,
		kHwGeometryAccel,
		kHwAntiAliasing,
		kHwGooch,
		kHwShadows,
		kHwFeatures
	};

	virtual ~NcGsConfig();

public:
	virtual bool configure(const NCHAR* info, bool show_dialog) = 0;
	virtual bool saveSettings() = 0;

public:
	virtual void driverName(NCHAR* path, int length) const = 0;
	virtual int driverVersion() const = 0;
	virtual int driverRevision() const = 0;
	virtual void driverPath(NCHAR* path, int nStrLen) const = 0;
	virtual void setDriverPath(const NCHAR* path) = 0;

	virtual void currentDisplayDriver(NCHAR* path, int path_length, NCHAR* driver, int driver_length,
	                                  bool& hardware_accelerated) = 0;

	virtual void hardwareAcceleratedDriver(NCHAR* path, int path_length, NCHAR* driver, int driver_length) = 0;
	virtual void setHardwareAcceleratedDriver(const NCHAR* path, const NCHAR* driver) = 0;

	virtual void defaultHardwareAcceleratedDriver(NCHAR* path, int path_length, NCHAR* driver, int driver_length) = 0;
	virtual void hardwareAcceleratedDrivers(NCHAR* path, int path_length, NCHAR** drivers, int driver_number) = 0;
	virtual int numHardwareAcceleratedDrivers() = 0;

public:
	virtual void setDynamicTessellation(bool enable) = 0;
	virtual bool dynamicTessellation() = 0;

	virtual GS::ErrorStatus setMaxLODs(int levels) = 0;
	virtual int maxLODs() = 0;

	virtual GS::ErrorStatus setSurfaceTessellationTol(int tolerance) = 0;
	virtual int surfaceTessellationTol() = 0;

	virtual GS::ErrorStatus setCurveTessellationTol(int tolerance) = 0;
	virtual int curveTessellationTol() = 0;

	virtual void setUseHalfPixelDeviation(bool deviation) = 0;
	virtual bool useHalfPixelDeviation() = 0;

public:
	virtual int frameRate() = 0;
	virtual GS::ErrorStatus setFrameRate(int fps) = 0;

	virtual void setAdaptiveDegradation(bool enable) = 0;
	virtual bool adaptiveDegradation() = 0;

	virtual int degradationChainPosition(DegradationChannel channel) = 0;
	virtual DegradationChannel degradationChannelAt(int position) = 0;
	virtual void shiftDegradationChainPosition(DegradationChannel channel, bool bShiftDown) = 0;
	virtual bool canDegradeChannel(DegradationChannel channel) = 0;
	virtual void setCanDegradeChannel(DegradationChannel channel, bool degrade) = 0;

public:
	virtual void setCacheViewportDrawGeometry(bool enable) = 0;
	virtual bool cacheViewportDrawGeometry() const = 0;

	virtual void setUseDisplayLists(bool bDegrade) = 0; // internal use
	virtual bool useDisplayLists() = 0;

	virtual void setRedrawOnWindowExpose(bool bDegrade) = 0; // internal use
	virtual bool redrawOnWindowExpose() = 0;

public:
	virtual Handedness handedness() const = 0;
	virtual void setHandedness(Handedness) = 0;

	virtual bool discardBackFaces() = 0;
	virtual void setDiscardBackFaces(bool discard) = 0;

	virtual Quality transparency() = 0;
	virtual void setTransparency(Quality quality) = 0;

public:
	virtual bool isFeatureEnabled(HardwareFeature feature) = 0;
	virtual void setFeatureEnabled(HardwareFeature feature, bool enable = true) = 0;
	virtual bool isFeatureAvailable(HardwareFeature feature) = 0;
	virtual bool isFeatureRecommended(HardwareFeature feature) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsReactor
class NcGsReactor
{
public:
	NcGsReactor(void) {}
	virtual ~NcGsReactor() {}

public:
	virtual void viewWasCreated(NcGsView* view) {}
	virtual void viewToBeDestroyed(NcGsView* view) {}
	virtual void gsToBeUnloaded(NcGsClassFactory* factory) {}
	virtual void configWasModified() {}
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGsClassFactory

typedef NcGiDrawable* (*NcGsGetInterfaceFunc)(long id, bool needs_validation);
typedef void (*NcGsReleaseInterfaceFunc)(NcGiDrawable* drawable);

class NcGsClassFactory
{
public:
	virtual ~NcGsClassFactory() {}

	virtual NcGsModel* createModel(NcGsModel::RenderType, long database, NcGsGetInterfaceFunc,
	                               NcGsReleaseInterfaceFunc) = 0;
	virtual void deleteModel(NcGsModel* model) = 0;

	virtual NcGsView* createView(const NcGsClientViewInfo* info = NULL, bool layer_visibility_per_view = false) = 0;
	virtual void deleteView(NcGsView* view) = 0;

	virtual NcGsDevice* createDevice(NcGsWindowingSystemID id, GS::DeviceType deviceType = GS::kScreenDevice) = 0;
	virtual NcGsDevice* createOffScreenDevice() = 0;
	virtual void deleteDevice(NcGsDevice* device) = 0;

	virtual NcGsConfig* getConfig() = 0;
	virtual void releaseConfig(NcGsConfig* config) = 0;

	virtual void addReactor(NcGsReactor* reactor) = 0;
	virtual void removeReactor(NcGsReactor* reactor) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////
// Driver(DLL) entry points
typedef NcGsClassFactory*(*NcGsCreateClassFactoryFunc)();
typedef void (*NcGsDeleteClassFactoryFunc)(NcGsClassFactory*);

#define NCGS_CREATE_CLASS_FACTORY  "CreateClassFactory"
#define NCGS_DELETE_CLASS_FACTORY  "DeleteClassFactory"

///////////////////////////////////////////////////////////////////////////////////////////
// NcGiPixelBGRA32
class NcGiPixelBGRA32
{
public:
	NcGiPixelBGRA32();
	NcGiPixelBGRA32(NRX::UInt32 bgra);
	NcGiPixelBGRA32(NRX::UInt8 blue, NRX::UInt8 green, NRX::UInt8 red, NRX::UInt8 alpha);

	NRX::UInt32 getBGRA() const;
	NRX::UInt32 getRGBA() const;
	NRX::UInt8 blue() const;
	NRX::UInt8 green() const;
	NRX::UInt8 red() const;
	NRX::UInt8 alpha() const;

	void setBGRA(NRX::UInt32 bgra);
	void setBGRA(NRX::UInt8 blue, NRX::UInt8 green, NRX::UInt8 red, NRX::UInt8 alpha);
	void setRGBA(NRX::UInt32 rgba);
	void setRGBA(NRX::UInt8 red, NRX::UInt8 green, NRX::UInt8 blue, NRX::UInt8 alpha);
	void setBlue(NRX::UInt8 blue);
	void setGreen(NRX::UInt8 green);
	void setRed(NRX::UInt8 red);
	void setAlpha(NRX::UInt8 alpha);

private:
	union
	{
		NRX::UInt32 m_whole;

		struct PIXEL
		{
			NRX::UInt8 b;
			NRX::UInt8 g;
			NRX::UInt8 r;
			NRX::UInt8 a;
		} m_bgra;
	};
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcGiImageBGRA32
class NcGiImageBGRA32
{
public:
	NcGiImageBGRA32();
	NcGiImageBGRA32(NRX::UInt32 width, NRX::UInt32 height, NcGiPixelBGRA32* image);

	NcGiPixelBGRA32* image() const;
	NRX::UInt32 width() const;
	NRX::UInt32 height() const;

	void setImage(NRX::UInt32 width, NRX::UInt32 height, NcGiPixelBGRA32* image);

private:
	NcGiPixelBGRA32* m_pImageData;
	NRX::UInt32 m_nImageWidth;
	NRX::UInt32 m_nImageHeight;
};

///////////////////////////////////////////////////////////////////////////////////////////
//NcGiPolyline
class OdGiPolyline;
class NcGiPolyline
{
public:
	NCRX_DECLARE_MEMBERS(NcGiPolyline);

	typedef NcGiPolyline  wrapper_class;
	typedef OdGiPolyline  native_class;

public:
	NRXDBGATE_EXPORT NcGiPolyline();
	NRXDBGATE_EXPORT NcGiPolyline(NRX::UInt32 count, NcGePoint3d* points, NcGeVector3d* normal = NULL,
	                              NRX::LongPtr marker = -1);

	NRXDBGATE_EXPORT NRX::UInt32 points() const;
	NRXDBGATE_EXPORT NcGePoint3d* vertexList() const;
	NRXDBGATE_EXPORT NcGeVector3d* normal() const;
	NRXDBGATE_EXPORT NRX::LongPtr baseSubEntMarker() const;

	NRXDBGATE_EXPORT void setVertexList(NRX::UInt32 count, NcGePoint3d* points);
	NRXDBGATE_EXPORT void setNormal(NcGeVector3d* normal);
	NRXDBGATE_EXPORT void setBaseSubEntMarker(NRX::LongPtr marker);

private:
	NRX::UInt32  m_nbPoints;
	NcGePoint3d*      m_pVertexList;
	NcGeVector3d*     m_pNormal;
	NRX::LongPtr m_lBaseSubEntMarker;

public:
	OdGiPolyline native() const;
};


///////////////////////////////////////////////////////////////////////////////////////////
// NcGiTransientManager
class NcGiTransientManager
{
public:
	virtual ~NcGiTransientManager() { }

	virtual bool addTransient(NcGiDrawable* pDrawable, NcGiTransientDrawingMode mode, int subDrawingMode, const NcArray< int > &viewports_) = 0;
	virtual bool eraseTransient(NcGiDrawable* pDrawable, const NcArray< int > &viewports_) = 0;
	virtual bool eraseTransients(NcGiTransientDrawingMode mode, int subDrawingMode, const NcArray< int > &viewports_) = 0;
	virtual void updateTransient(NcGiDrawable* pDrawable, const NcArray< int > &viewports_) = 0;
	virtual bool addChildTransient(NcGiDrawable* pDrawable, NcGiDrawable* pParentDrawable) = 0;
	virtual bool eraseChildTransient(NcGiDrawable* pDrawable, NcGiDrawable* pParentDrawable) = 0;
	virtual void updateChildTransient(NcGiDrawable* pDrawable, NcGiDrawable* pParentDrawable) = 0;
	virtual int getFreeSubDrawingMode(NcGiTransientDrawingMode mode, int& subDrawingMode, const NcArray<int>& viewportNumbers) = 0;
};

NRXDBGATE_EXPORT NcGiTransientManager* ncgiGetTransientManager();
NRXDBGATE_EXPORT void ncgiSetTransientManager(NcGiTransientManager* transientManager);

NRXDBGATE_EXPORT NRX::Boolean ncgsGetDisplayInfo(int &drawingWidth, int &drawingHeight, int &aspectWidth, int &aspectHeight);
NRXDBGATE_EXPORT NRX::Boolean ncgsGetViewportInfo(int viewport_, int &left, int &bottom, int &right, int &top);

class NcGsScreenShot
{
public:
	NcGsScreenShot();
	virtual ~NcGsScreenShot () = 0;

public:
	virtual NRX::Boolean getSize(int & width, int & height, int & depth) const = 0;
	virtual NRX::Boolean getColorMap(int index, NRX::UInt8 &red, NRX::UInt8 &green, NRX::UInt8 &blue) const = 0;

	virtual void const *getScanline(int offsetFromLeft, int offsetFromTop) const = 0;

	void operator delete (void * p);
};

// Compatibility definition
//
#define ScreenShot NcGsScreenShot

NRXDBGATE_EXPORT NcGsScreenShot *ncgsGetScreenShot(int viewport_);

NRXDBGATE_EXPORT void ncgsSetViewportRenderFlag (int viewport_);

NRXDBGATE_EXPORT NRX::Boolean ncgsDisplayImage (int viewport_, long originLeft, long originTop, int imageWidth, int imageHeight, void const *imageData, int hasTransparency);

NRXDBGATE_EXPORT NRX::Boolean ncgsRemoveAnonymousGraphics(int viewport_);

typedef void (*ncgsCustomUpdateMethod) (void * pParm, int left, int right, int bottom, int top);
NRXDBGATE_EXPORT NRX::Boolean ncgsSetCustomUpdateMethod(ncgsCustomUpdateMethod custom_update_method, void * pParm);

NRXDBGATE_EXPORT void ncgsRedrawShortTermGraphics(short minx, short miny, short maxx, short maxy);

struct NcGsNrx
{
	enum LinePattern
	{
		eSolid                         = 0,
		eDashed                        = 1,
		eDotted                        = 2,
		eDashDot                       = 3,
		eShortDash                     = 4,
		eMediumDash                    = 5,
		eLongDash                      = 6,
		eDoubleShortDash               = 7,
		eDoubleMediumDash              = 8,
		eDoubleLongDash                = 9,
		eMediumLongDash                = 10,
		eMediumDashShortDashShortDash  = 11,
		eLongDashShortDash             = 12,
		eLongDashDotDot                = 13,
		eLongDashDot                   = 14,
		eMediumDashDotShortDashDot     = 15,
		eSparseDot                     = 16,
		eDefaultLinePattern            = eDotted
	};
};

NRXDBGATE_EXPORT void ncgsSetHighlightColor(NRX::UInt16 colorIndex);
NRXDBGATE_EXPORT NRX::UInt16 ncgsGetHighlightColor();
NRXDBGATE_EXPORT void ncgsSetHighlightLinePattern(NcGsNrx::LinePattern pattern);
NRXDBGATE_EXPORT NcGsNrx::LinePattern ncgsGetHighlightLinePattern();
NRXDBGATE_EXPORT void ncgsSetHighlightLineWeight(NRX::UInt16 weight);
NRXDBGATE_EXPORT NRX::UInt16 ncgsGetHighlightLineWeight();

NRXDBGATE_EXPORT NRX::Boolean ncgsSetViewParameters(int viewport_, const NcGsView * view_, bool bRegenRequired, bool bRescaleRequired, bool bSyncRequired = false);
NRXDBGATE_EXPORT NRX::Boolean ncgsGetViewParameters(int viewport_, NcGsView *view_);
NRXDBGATE_EXPORT NRX::Boolean ncgsSetLensLength(int viewport_, const double &lensLength);
NRXDBGATE_EXPORT NRX::Boolean ncgsGetLensLength(int viewport_, double &lensLength);
NRXDBGATE_EXPORT void ncgsWriteViewToUndoController(int viewport_);
NRXDBGATE_EXPORT NRX::Boolean ncgsSetView2D(int viewport_);

NRXDBGATE_EXPORT NcGsView *ncgsGetGsView(int viewport_, bool create_);

// For compatibility with projects without mfc
class CView;
NRXDBGATE_EXPORT NcGsManager* ncgsGetGsManager(CView* view_ = NULL);

NRXDBGATE_EXPORT NRX::Boolean ncgsGetOrthoViewParameters(int viewport_, NcDb::OrthographicView view, NcGeVector3d *view_, NcGeVector3d *up_);

class NcGs2DViewLimitManager
{
public:
	virtual ~NcGs2DViewLimitManager  (void) { }
	virtual bool testView(NcGePoint3d const &target_, double height_) = 0;
};

NRXDBGATE_EXPORT NcGs2DViewLimitManager *ncgsCreate2DViewLimitManager(int viewport_);
NRXDBGATE_EXPORT void ncgsDestroy2DViewLimitManager(NcGs2DViewLimitManager *pLimitManager);

// AutoGern:

//////////////////////////////////////////////////////////////////////////
// NcGiColorRGB
class NcGiColorRGB {
public:
	NcGiColorRGB (void)
	    : red   (0.0)
	    , green (0.0)
	    , blue  (0.0)
	{ }
	NcGiColorRGB (double r, double g, double b)
	    : red   (r)
	    , green (g)
	    , blue  (b)
	{ }
	double red;
	double green;
	double blue;
};

inline NcGiColorRGB operator* (const NcGiColorRGB& c1, const NcGiColorRGB& c2)
{
	return NcGiColorRGB(c1.red   * c2.red,
	                    c1.green * c2.green,
	                    c1.blue  * c2.blue);
}

inline NcGiColorRGB operator* (const NcGiColorRGB& c, double s)
{
	return NcGiColorRGB(s * c.red,
	                    s * c.green,
	                    s * c.blue);
}

inline NcGiColorRGB operator* (double s, const NcGiColorRGB& c)
{
	return c * s;
}

inline NcGiColorRGB operator+ (const NcGiColorRGB& c1, const NcGiColorRGB& c2)
{
	return NcGiColorRGB(c1.red   + c2.red,
	                    c1.green + c2.green,
	                    c1.blue  + c2.blue);
}

//////////////////////////////////////////////////////////////////////////
// NcGiColorRGBA
class NcGiColorRGBA {
public:
	NcGiColorRGBA (void)
	    : red   (0.0)
	    , green (0.0)
	    , blue  (0.0)
	    , alpha (1.0)
	{ }
	NcGiColorRGBA (double r, double g, double b, double a)
	    : red   (r)
	    , green (g)
	    , blue  (b)
	    , alpha (a)
	{ }
	double red;
	double green;
	double blue;
	double alpha;
};

inline NcGiColorRGBA operator* (const NcGiColorRGBA& c1, const NcGiColorRGBA& c2)
{
	return NcGiColorRGBA(c1.red   * c2.red, 
	                     c1.green * c2.green, 
	                     c1.blue  * c2.blue, 
	                     c1.alpha * c2.alpha);
}

inline NcGiColorRGBA operator*(const NcGiColorRGBA& c, double s)
{
	return NcGiColorRGBA(s * c.red, 
	                     s * c.green, 
	                     s * c.blue, 
	                     s * c.alpha);
}

inline NcGiColorRGBA operator* (double s, const NcGiColorRGBA& c)
{
	return c * s;
}

inline NcGiColorRGBA operator+ (const NcGiColorRGBA& c1, const NcGiColorRGBA& c2)
{
	return NcGiColorRGBA(c1.red   + c2.red, 
	                     c1.green + c2.green, 
	                     c1.blue  + c2.blue, 
	                     c1.alpha + c2.alpha);
}

//////////////////////////////////////////////////////////////////////////
// NcGiContextualColors2
class NcGiContextualColors2 : public NcGiContextualColors {
public:
	NCRX_DECLARE_MEMBERS(NcGiContextualColors2);
	virtual NcCmColor     webMeshColor        (void) const = 0;
	virtual NcCmColor     webMeshMissingColor (void) const = 0;
	virtual NcCmColor     lightShapeColor     (void) const = 0;
	virtual NcCmColor     lightDistanceColor  (void) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiNonEntityTraits
class NRXDBGATE_EXPORT NcGiNonEntityTraits : public NcGiDrawableTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiNonEntityTraits);
	virtual void                setupForEntity      (NcDbEntity* pEntity);
	virtual void                addLight(const NcDbObjectId& id);
	virtual void                setColor            (const NRX::UInt16 color);
	virtual NRX::UInt16       color               (void) const;
	virtual void                setTrueColor        (const NcCmEntityColor& color);
	virtual NcCmEntityColor     trueColor           (void) const;
	virtual void                setLayer            (const NcDbObjectId layerId);
	virtual NcDbObjectId        layerId             (void) const;
	virtual void                setLineType         (const NcDbObjectId linetypeId);
	virtual NcDbObjectId        lineTypeId          (void) const;
	virtual void                setSelectionMarker  (const NRX::LongPtr markerId);
	virtual void                setFillType         (const NcGiFillType fillType);
	virtual NcGiFillType        fillType            (void) const;
	virtual void                setLineWeight       (const NcDb::LineWeight lw);
	virtual NcDb::LineWeight    lineWeight          (void) const;
	virtual void                setThickness        (double thickness);
	virtual double              thickness           (void) const;
	virtual void                setLineTypeScale    (double dScale);
	virtual double              lineTypeScale       (void) const;
	virtual void                setMaterial         (const NcDbObjectId matId);
	virtual NcDbObjectId        materialId          (void) const;
	virtual void                setSelectionGeom    (bool bSelectionflag);
	virtual bool                selectionGeom       ( void ) const;
	virtual void                setTransparency     (const NcCmTransparency& transparency);
	virtual NcCmTransparency    transparency        (void) const;
};

//////////////////////////////////////////////////////////////////////////
// NcGiGdiDrawObject
class NRXDBGATE_EXPORT NcGiGdiDrawObject: public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcGiGdiDrawObject);
	virtual NRX::Boolean    draw(HDC hDC, int x, int y, int w, int h) = 0;
	virtual int               width() const = 0;
	virtual int               height() const = 0;
	virtual void              addRef() = 0;
	virtual void              delRef() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiLightTraits
class NRXDBGATE_EXPORT NcGiLightTraits : public NcGiNonEntityTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiLightTraits);
	virtual void setOn(bool on) = 0;
	virtual bool isOn() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiShadowParameters
class NRXDBGATE_EXPORT NcGiShadowParameters : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcGiShadowParameters);
	NcGiShadowParameters();
	virtual ~NcGiShadowParameters();
	bool operator==(const NcGiShadowParameters& params) const;
	virtual void setShadowsOn(bool on);
	virtual bool shadowsOn() const;
	enum ShadowType {
		kShadowsRayTraced = 0,
		kShadowMaps,
		kAreaSampled
	};
	virtual void setShadowType(ShadowType typ);
	virtual ShadowType shadowType() const;
	virtual bool setShadowMapSize(NRX::UInt16 sz);
	virtual NRX::UInt16 shadowMapSize() const;
	virtual bool setShadowMapSoftness(NRX::UInt8 soft);
	virtual NRX::UInt8 shadowMapSoftness() const;
private:
	bool            mShadowsOn;
	ShadowType      mShadowType;
	NRX::UInt16   mShadowMapSize;
	NRX::UInt8    mShadowMapSoftness;
};

//////////////////////////////////////////////////////////////////////////
// NcGiShadowParameters2
class NRXDBGATE_EXPORT NcGiShadowParameters2 : public NcGiShadowParameters {
public:
	NCRX_DECLARE_MEMBERS(NcGiShadowParameters2);
	NcGiShadowParameters2 (void);
	explicit  NcGiShadowParameters2 (const NcGiShadowParameters& params);
	virtual  ~NcGiShadowParameters2 (void);
	bool operator==(const NcGiShadowParameters2& params) const;
	virtual bool setShadowSamples(NRX::UInt16 samples);
	virtual NRX::UInt16 shadowSamples() const;
	virtual void setShapeVisibility(bool visible);
	virtual bool shapeVisibility() const;
	enum ExtendedLightShape {
		kLinear = 0,
		kRectangle,
		kDisk,
		kCylinder,
		kSphere
	};
	virtual bool setExtendedLightShape(ExtendedLightShape shape);
	virtual ExtendedLightShape extendedLightShape() const;
	virtual bool setExtendedLightLength(double length);
	virtual double extendedLightLength() const;
	virtual bool setExtendedLightWidth(double width);
	virtual double extendedLightWidth() const;
	virtual bool setExtendedLightRadius(double radius);
	virtual double extendedLightRadius() const;
protected:
	NRX::UInt16       mShadowSamples;
	bool                mbShapeVisibility;
	ExtendedLightShape  mExtLightShape;
	double              mExtLightLength;
	double              mExtLightWidth;
	double              mExtLightRadius;
};

//////////////////////////////////////////////////////////////////////////
// NcGiLightAttenuation
class NRXDBGATE_EXPORT NcGiLightAttenuation : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcGiLightAttenuation);
	NcGiLightAttenuation();
	virtual ~NcGiLightAttenuation();
	bool operator==(const NcGiLightAttenuation& atten) const;
	enum AttenuationType {
		kNone = 0,
		kInverseLinear,
		kInverseSquare
	};
	virtual void setAttenuationType(AttenuationType typ);
	virtual AttenuationType attenuationType() const;
	virtual void setUseLimits(bool on);
	virtual bool useLimits() const;
	virtual void setLimits(double startlim, double endlim);
	virtual double startLimit() const;
	virtual double endLimit() const;
private:
	AttenuationType mAttenType;
	bool            mUseAttenLimits;
	double          mAttenStartLimit;
	double          mAttenEndLimit;
};

//////////////////////////////////////////////////////////////////////////
// NcGiSkyParameters
class NRXDBGATE_EXPORT NcGiSkyParameters : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcGiSkyParameters);
	NcGiSkyParameters();
	virtual ~NcGiSkyParameters();
	bool operator==(const NcGiSkyParameters& params) const;
	void setIllumination(bool enable)   { return setIlluminationImp(enable); }
	bool illumination() const { return illuminationImp(); }
	bool setIntensityFactor(double intensity)   { return setIntensityFactorImp(intensity); }
	double intensityFactor() const { return intensityFactorImp(); }
	bool setHaze(double haze) { return setHazeImp(haze); }
	double haze() const { return hazeImp(); }
	bool setHorizonHeight(double height) { return setHorizonHeightImp(height); }
	double horizonHeight() const    { return horizonHeightImp(); }
	bool setHorizonBlur(double blur) { return setHorizonBlurImp(blur); }
	double horizonBlur() const { return horizonBlurImp(); }
	void setGroundColor(const NcCmColor& color) { return setGroundColorImp(color); }
	NcCmColor groundColor() const { return groundColorImp(); }
	void setNightColor(const NcCmColor& color) { setNightColorImp(color); }
	NcCmColor nightColor() const    { return nightColorImp(); }
	void setAerialPerspective(bool apply) { setAerialPerspectiveImp(apply); }
	bool aerialPerspective() const { return aerialPerspectiveImp(); }
	bool setVisibilityDistance(double distance) { return setVisibilityDistanceImp(distance); }
	double visibilityDistance() const { return visibilityDistanceImp(); }
	bool setDiskScale(double scale) { return setDiskScaleImp(scale); }
	double diskScale() const { return diskScaleImp(); }
	bool setGlowIntensity (double intensity) { return setGlowIntensityImp(intensity); }
	double glowIntensity() const { return glowIntensityImp(); }
	bool setDiskIntensity(double intensity) { return setDiskIntensityImp(intensity); }
	double diskIntensity() const { return diskIntensityImp(); }
	bool setSolarDiskSamples(NRX::UInt16 samples) { return setSolarDiskSamplesImp(samples); }
	NRX::UInt16 solarDiskSamples() const { return solarDiskSamplesImp(); }
	bool setSunDirection(const NcGeVector3d& sundir) { return setSunDirectionImp(sundir); }
	const NcGeVector3d& sunDirection() const { return sunDirectionImp(); }
	bool setRedBlueShift (double redBlueShift)  { return setRedBlueShiftImp(redBlueShift); }
	double redBlueShift  (void) const           { return redBlueShiftImp(); }
	bool setSaturation (double saturation)      { return setSaturationImp(saturation); }
	double saturation (void) const              { return saturationImp(); }
protected:
	virtual void setIlluminationImp (bool enable);
	virtual bool illuminationImp (void) const;
	virtual bool setIntensityFactorImp (double intensity);
	virtual double intensityFactorImp () const;
	virtual bool setHazeImp (double haze);
	virtual double hazeImp (void) const;
	virtual bool setHorizonHeightImp        (double height);
	virtual double horizonHeightImp (void) const;
	virtual bool setHorizonBlurImp (double blur);
	virtual double horizonBlurImp () const;
	virtual void setGroundColorImp (const NcCmColor& color);
	virtual NcCmColor groundColorImp () const;
	virtual void setNightColorImp (const NcCmColor& color);
	virtual NcCmColor nightColorImp () const;
	virtual void setAerialPerspectiveImp (bool apply);
	virtual bool aerialPerspectiveImp () const;
	virtual bool setVisibilityDistanceImp (double distance);
	virtual double visibilityDistanceImp () const;
	virtual bool setDiskScaleImp (double scale);
	virtual double diskScaleImp () const;
	virtual bool setGlowIntensityImp (double intensity);
	virtual double glowIntensityImp () const;
	virtual bool setDiskIntensityImp (double intensity);
	virtual double diskIntensityImp () const;
	virtual bool setSolarDiskSamplesImp (NRX::UInt16 samples);
	virtual NRX::UInt16 solarDiskSamplesImp (void) const;
	virtual bool  setSunDirectionImp (const NcGeVector3d& sundir);
	virtual const NcGeVector3d& sunDirectionImp (void) const;
	virtual bool setRedBlueShiftImp  (double redBlueShift);
	virtual double  redBlueShiftImp (void) const;
	virtual bool setSaturationImp (double saturation);
	virtual double  saturationImp (void) const;
private:
	bool            mStatus;
	double          mIntensityFactor;
	double          mHaze;
	double          mHorizonHeight;
	double          mHorizonBlur;
	NcCmColor       mGroundColor;
	NcCmColor       mNightColor;
	bool            mAerialPerspective;
	double          mVisibilityDistance;
	double          mDiskScale;
	double          mGlowIntensity;
	double          mDiskIntensity;
	NRX::UInt16   mSolarDiskSamples;
	NcGeVector3d    mSunDirection;
	double          mRedBlueShift;
	double          mSaturation;
};

//////////////////////////////////////////////////////////////////////////
// NcGiStandardLightTraits
class NRXDBGATE_EXPORT NcGiStandardLightTraits : public NcGiLightTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiStandardLightTraits);
	virtual void setIntensity(double inten) = 0;
	virtual double intensity() const = 0;
	virtual void setLightColor(const NcCmColor& color) = 0;
	virtual NcCmColor lightColor() const = 0;
	virtual void setShadowParameters(const NcGiShadowParameters& params) = 0;
	virtual void shadowParameters(NcGiShadowParameters& params) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiPointLightTraits
class NRXDBGATE_EXPORT NcGiPointLightTraits : public NcGiStandardLightTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiPointLightTraits);
	virtual void setPosition(const NcGePoint3d& pos) = 0;
	virtual NcGePoint3d position() const = 0;
	virtual void lightAttenuation(NcGiLightAttenuation& atten) const = 0;
	virtual void setAttenuation(const NcGiLightAttenuation& atten) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiPointLightTraits2
class NRXDBGATE_EXPORT NcGiPointLightTraits2 : public NcGiPointLightTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiPointLightTraits2);
	virtual void setPhysicalIntensity(double physicalIntensity) = 0;
	virtual double physicalIntensity() const = 0;
	virtual void setLampColor (const NcGiColorRGB& rgbColor) = 0;
	virtual void lampColor (NcGiColorRGB& rgbColor) const = 0;
	virtual void setShadowParameters(const NcGiShadowParameters2& params) = 0;
	virtual void shadowParameters(NcGiShadowParameters2& params) const = 0;
	virtual void setHasTarget (bool bHasTarget) = 0;
	virtual bool hasTarget (void) const = 0;
	virtual void setTargetLocation(const NcGePoint3d& loc) = 0;
	virtual NcGePoint3d targetLocation() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiSpotLightTraits
class NRXDBGATE_EXPORT NcGiSpotLightTraits : public NcGiStandardLightTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiSpotLightTraits);
	virtual void setPosition(const NcGePoint3d& pos) = 0;
	virtual NcGePoint3d position() const = 0;
	virtual void setTargetLocation(const NcGePoint3d& loc) = 0;
	virtual NcGePoint3d targetLocation() const = 0;
	virtual bool setHotspotAndFalloff(double hotspot, double falloff) = 0;
	virtual double hotspot() const = 0;
	virtual double falloff() const = 0;
	virtual void lightAttenuation(NcGiLightAttenuation& atten) const = 0;
	virtual void setAttenuation(const NcGiLightAttenuation& atten) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiSpotLightTraits2
class NRXDBGATE_EXPORT NcGiSpotLightTraits2 : public NcGiSpotLightTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiSpotLightTraits2);
	virtual void setPhysicalIntensity(double physicalIntensity) = 0;
	virtual double physicalIntensity() const = 0;
	virtual void setLampColor (const NcGiColorRGB& rgbColor) = 0;
	virtual void lampColor (NcGiColorRGB& rgbColor) const = 0;
	virtual void setShadowParameters(const NcGiShadowParameters2& params) = 0;
	virtual void shadowParameters(NcGiShadowParameters2& params) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiDistantLightTraits
class NRXDBGATE_EXPORT NcGiDistantLightTraits : public NcGiStandardLightTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiDistantLightTraits);
	virtual void setLightDirection(const NcGeVector3d& vec) = 0;
	virtual NcGeVector3d lightDirection() const = 0;
	virtual void setIsSunlight(bool isSunlight) = 0;
	virtual bool isSunlight() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiDistantLightTraits2
class NRXDBGATE_EXPORT NcGiDistantLightTraits2 : public NcGiDistantLightTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiDistantLightTraits2);
	virtual void setPhysicalIntensity(double physicalIntensity) = 0;
	virtual double physicalIntensity() const = 0;
	virtual void setLampColor (const NcGiColorRGB& rgbColor) = 0;
	virtual void lampColor (NcGiColorRGB& rgbColor) const = 0;
	virtual void setShadowParameters(const NcGiShadowParameters2& params) = 0;
	virtual void shadowParameters(NcGiShadowParameters2& params) const = 0;
	virtual void setSkyParameters(const NcGiSkyParameters& params) = 0;
	virtual void skyParameters(NcGiSkyParameters& params) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiWebLightTraits
class NRXDBGATE_EXPORT NcGiWebLightTraits : public NcGiPointLightTraits2 {
public:
	NCRX_DECLARE_MEMBERS(NcGiWebLightTraits);
	enum WebFileType
	{
		kTypeC = 1,
		kTypeB = 2,
		kTypeA = 3
	};
	enum WebSymmetry
	{
		kNoSymmetry = 0,
		kSingleSymmetry = 1,
		kDoubleSymmetry = 2,
		kAxialSymmetry = 3,
	};
	virtual void setWebFile(const NCHAR* webFile) = 0;
	virtual void webFile(NcString& webFile) const = 0;
	virtual void setWebRotation(NcGeVector3d rotation) = 0;
	virtual void webRotation(NcGeVector3d& rotation) const = 0;
	virtual void setWebFlux(double flux) const = 0;
	virtual double webFlux() const = 0;
	virtual void setWebFileType (WebFileType type) = 0;
	virtual WebFileType webFileType (void) const = 0;
	virtual void setWebSymmetry (WebSymmetry symmetry) = 0;
	virtual WebSymmetry webSymmetry (void) const = 0;
	virtual void setWebHorzAng90to270 (bool bIs90to270) = 0;
	virtual bool webHorzAng90to270 (void) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiLineAttributes
class NRX_NO_VTABLE NcGiLineAttributes {
public:
	virtual ~NcGiLineAttributes() { }
	virtual NcDb::LineWeight    getLineweight    () const                        = 0;
	virtual void setLineweight                    (NcDb::LineWeight lweight)        = 0;
	virtual NcGiLineJoinStyle    getJoinstyle    () const                        = 0;
	virtual void setJoinstyle                    (NcGiLineJoinStyle joinstyle)    = 0;
	virtual NcGiLineEndStyle    getEndstyle        () const                        = 0;
	virtual void setEndstyle                    (NcGiLineEndStyle endstyle)        = 0;
	virtual NcGiLineType        getLinetype        () const                        = 0;
	virtual void setLinetype                    (NcGiLineType linetype)            = 0;
	virtual NcGiLineFillStyle    getFillstyle    () const                        = 0;
	virtual void setFillstyle                    (NcGiLineFillStyle fillstyle)    = 0;
	virtual bool isLinetypeAdaptive                () const                        = 0;
	virtual void setLinetypeAdaptive            (bool isAdaptive)                = 0;
	virtual bool isLineWeightByLayer            () const                        = 0;
	virtual void setLineWeightByLayer            (bool isLineweightByLayer)        = 0;
	virtual bool hasCustomLineweight            () const                        = 0;
	virtual void setCustomLineweight            (bool isCustomLineweight)        = 0;
	virtual bool isLineweightDefault            () const                        = 0;
	virtual void setLineweightDefault           ()                              = 0;
	virtual NcGiLineAttributes* clone           () const                        = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiLineAttrUtils
class NRXDBGATE_EXPORT NcGiLineAttrUtils {
public:
	static char __stdcall ncgiLineWeightToIndex(NcDb::LineWeight lw);
	static NcDb::LineWeight __stdcall ncgiIndexToLineWeight(char index);
};

//////////////////////////////////////////////////////////////////////////
// NcGiMaterialTraits
class NRXDBGATE_EXPORT NcGiMaterialTraits : public NcGiNonEntityTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiMaterialTraits);
	enum IlluminationModel {
		kBlinnShader = 0,
		kMetalShader,
	};
	enum ChannelFlags
	{
		kNone          = 0x00000,
		kUseDiffuse    = 0x00001,
		kUseSpecular   = 0x00002,
		kUseReflection = 0x00004,
		kUseOpacity    = 0x00008,
		kUseBump       = 0x00010,
		kUseRefraction = 0x00020,
		kUseNormalMap  = 0x00040,
		kUseAll        = (kUseDiffuse | kUseSpecular | kUseReflection
		                    | kUseOpacity | kUseBump | kUseRefraction
		                    | kUseNormalMap),
	};
	enum Mode {
		kRealistic = 0,
		kAdvanced,
	};
	virtual void setAmbient     (const NcGiMaterialColor & color)   = 0;
	virtual void setDiffuse     (const NcGiMaterialColor & color,
	                             const NcGiMaterialMap & map)       = 0;
	virtual void setSpecular    (const NcGiMaterialColor & color,
	                             const NcGiMaterialMap & map,
	                             double dGloss)                     = 0;
	virtual void setReflection  (const NcGiMaterialMap & map)       = 0;
	virtual void setOpacity     (double dPercentage,
	                             const NcGiMaterialMap & map)       = 0;
	virtual void setBump        (const NcGiMaterialMap & map)       = 0;
	virtual void setRefraction  (double dIndex,
	                             const NcGiMaterialMap & map)       = 0;
	virtual void setTranslucence(double value)                      = 0;
	virtual void setSelfIllumination(double value)                  = 0;
	virtual void setReflectivity(double value)                      = 0;
	virtual void setIlluminationModel(IlluminationModel model)      = 0;
	virtual void setChannelFlags(ChannelFlags flags)                = 0;
	virtual void setMode(Mode value)                                = 0;
	virtual void ambient        (NcGiMaterialColor & color) const   = 0;
	virtual void diffuse        (NcGiMaterialColor & color,
	                             NcGiMaterialMap & map) const       = 0;
	virtual void specular       (NcGiMaterialColor & color,
	                             NcGiMaterialMap & map,
	                             double & dGloss) const             = 0;
	virtual void reflection     (NcGiMaterialMap & map) const       = 0;
	virtual void opacity        (double & dPercentage,
	                             NcGiMaterialMap & map) const       = 0;
	virtual void bump           (NcGiMaterialMap & map) const       = 0;
	virtual void refraction     (double & dIndex,
	                             NcGiMaterialMap & map) const       = 0;
	virtual double translucence() const                             = 0;
	virtual double selfIllumination() const                         = 0;
	virtual double reflectivity() const                             = 0;
	virtual IlluminationModel illuminationModel() const             = 0;
	virtual ChannelFlags channelFlags() const                       = 0;
	virtual Mode mode() const                                       = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiMaterialTraits2
class NRXDBGATE_EXPORT NcGiMaterialTraits2 : public NcGiMaterialTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiMaterialTraits2);
	enum LuminanceMode
	{
		kSelfIllumination = 0,
		kLuminance,
	};
	enum NormalMapMethod
	{
		kTangentSpace
	};
	enum GlobalIlluminationMode
	{
		kGlobalIlluminationNone,
		kGlobalIlluminationCast,
		kGlobalIlluminationReceive,
		kGlobalIlluminationCastAndReceive
	};
	enum FinalGatherMode
	{
		kFinalGatherNone,
		kFinalGatherCast,
		kFinalGatherReceive,
		kFinalGatherCastAndReceive
	};
	virtual void setColorBleedScale(double value)                   = 0;
	virtual void setIndirectBumpScale(double value)                 = 0;
	virtual void setReflectanceScale(double value)                  = 0;
	virtual void setTransmittanceScale(double value)                = 0;
	virtual void setTwoSided(bool value)                            = 0;
	virtual void setLuminanceMode(LuminanceMode value)              = 0;
	virtual void setLuminance(double value)                         = 0;
	virtual void setNormalMap(const NcGiMaterialMap & map,
	                          NormalMapMethod method,
	                          double strength)                      = 0;
	virtual void setGlobalIllumination(GlobalIlluminationMode mode) = 0;
	virtual void setFinalGather(FinalGatherMode mode)               = 0;
	virtual double colorBleedScale() const                          = 0;
	virtual double indirectBumpScale() const                        = 0;
	virtual double reflectanceScale() const                         = 0;
	virtual double transmittanceScale() const                       = 0;
	virtual bool   twoSided() const                                 = 0;
	virtual LuminanceMode luminanceMode() const                     = 0;
	virtual double luminance() const                                = 0;
	virtual void normalMap(NcGiMaterialMap & map,
	                       NormalMapMethod &method,
	                       double &strength) const                  = 0;
	virtual GlobalIlluminationMode globalIllumination() const       = 0;
	virtual FinalGatherMode finalGather() const                     = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiMaterialColor
class OdGiMaterialColor;
class NRXDBGATE_EXPORT NcGiMaterialColor: public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiMaterialColor);

	typedef NcGiMaterialColor  wrapper_class;
	typedef OdGiMaterialColor  native_class;

	enum Method {
		kInherit = 0,
		kOverride,
	};

	static const NcGiMaterialColor kNull;

	NcGiMaterialColor();
	NcGiMaterialColor(const NcGiMaterialColor& matColor);
	NcGiMaterialColor(const OdGiMaterialColor& color);

	virtual ~NcGiMaterialColor();

	NcGiMaterialColor& operator= (const NcGiMaterialColor& matColor);
	bool               operator==(const NcGiMaterialColor& matColor)const;

	virtual void set       (const NcGiMaterialColor& matColor);
	        void set       (const OdGiMaterialColor& matColor);
	virtual void setMethod (Method method);
	virtual void setFactor (double dFactor);
	virtual void setColor  (const NcCmEntityColor& color);

	virtual Method                 method() const;
	virtual double                 factor() const;
	virtual const NcCmEntityColor  color()  const; // Return color by value to prevent local object address return

public:
	OdGiMaterialColor* native() const;

private:
	OdGiMaterialColor* m_pImpl;
};

//////////////////////////////////////////////////////////////////////////
// NcGiMaterialTexture
class OdGiMaterialTexture;
class NRXDBGATE_EXPORT NcGiMaterialTexture : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcGiMaterialTexture);

	typedef NcGiMaterialTexture  wrapper_class;
	typedef OdGiMaterialTexture  native_class;

	NcGiMaterialTexture();
	NcGiMaterialTexture(OdRxObject *_object);
	virtual ~NcGiMaterialTexture();

	virtual bool operator==(const NcGiMaterialTexture & texture) const;

public:
	OdGiMaterialTexture* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcGiImageTexture
class OdGiImageTexture;
class NRXDBGATE_EXPORT NcGiImageTexture : public NcGiMaterialTexture {
public:
	NCRX_DECLARE_MEMBERS(NcGiImageTexture);

	typedef NcGiImageTexture  wrapper_class;
	typedef OdGiImageTexture  native_class;

	NcGiImageTexture();
	NcGiImageTexture(OdRxObject *_object);
	virtual ~NcGiImageTexture();

public:
	OdGiImageTexture* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcGiImageFileTexture
class OdGiImageFileTexture;
class NRXDBGATE_EXPORT NcGiImageFileTexture : public NcGiImageTexture {
public:
	NCRX_DECLARE_MEMBERS(NcGiImageFileTexture);

	typedef NcGiImageFileTexture  wrapper_class;
	typedef OdGiImageFileTexture  native_class;

	NcGiImageFileTexture();
	NcGiImageFileTexture(OdRxObject *_object);
	virtual ~NcGiImageFileTexture();
	NcGiImageFileTexture(const NcGiImageFileTexture &texture);

	NcGiImageFileTexture & operator= (const NcGiImageFileTexture &texture);
	virtual bool operator==(const NcGiMaterialTexture & texture) const;

	virtual Nano::ErrorStatus copyFrom(const NcRxObject* other);
	virtual void setSourceFileName(const NCHAR * fileName);
	virtual const NCHAR * sourceFileName(void) const;

public:
	OdGiImageFileTexture* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcGiProceduralTexture
class NRXDBGATE_EXPORT NcGiProceduralTexture : public NcGiMaterialTexture {
public:
	NCRX_DECLARE_MEMBERS(NcGiProceduralTexture);
	enum Type
	{
		kWood = 0,
		kMarble,
		kGeneric,
	};
};

//////////////////////////////////////////////////////////////////////////
// NcGiGenericTexture
class NRXDBGATE_EXPORT NcGiGenericTexture : public NcGiProceduralTexture {
public:
	NCRX_DECLARE_MEMBERS(NcGiGenericTexture);
	NcGiGenericTexture              (void);
	virtual ~NcGiGenericTexture      (void);
	NcGiGenericTexture              (const NcGiGenericTexture &texture);
	NcGiGenericTexture & operator=  (const NcGiGenericTexture &texture);
	virtual bool         operator== (const NcGiMaterialTexture &texture) const;
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* other);
	void            setDefinition   (const NcGiVariant& definition);
	NcGiVariant     definition      (void) const;
	void            definition      (NcGiVariant*& pDefinition);
protected:
	NcGiVariant     m_definition;
};

//////////////////////////////////////////////////////////////////////////
// NcGiWoodTexture
class NRXDBGATE_EXPORT NcGiWoodTexture : public NcGiProceduralTexture {
public:
	NCRX_DECLARE_MEMBERS(NcGiWoodTexture);
	NcGiWoodTexture             (void);
	virtual ~NcGiWoodTexture    (void);
	NcGiWoodTexture             (const NcGiWoodTexture &texture);
	NcGiWoodTexture & operator= (const NcGiWoodTexture &texture);
	virtual bool      operator==(const NcGiMaterialTexture & texture) const;
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* other);
	virtual void setColor1      (const NcGiMaterialColor &woodColor1);
	virtual const NcGiMaterialColor & color1  (void) const;
	virtual void setColor2      (const NcGiMaterialColor &woodColor2);
	virtual const NcGiMaterialColor & color2  (void) const;
	virtual void setRadialNoise (double radialNoise);
	virtual double radialNoise  (void) const;
	virtual void setAxialNoise  (double axialNoise);
	virtual double axialNoise   (void) const;
	virtual void setGrainThickness  (double grainThickness);
	virtual double grainThickness   (void) const;
};

//////////////////////////////////////////////////////////////////////////
// NcGiMarbleTexture
class NRXDBGATE_EXPORT NcGiMarbleTexture : public NcGiProceduralTexture {
public:
	NCRX_DECLARE_MEMBERS(NcGiMarbleTexture);
	NcGiMarbleTexture             (void);
	virtual ~NcGiMarbleTexture    (void);
	NcGiMarbleTexture             (const NcGiMarbleTexture &texture);
	NcGiMarbleTexture & operator= (const NcGiMarbleTexture &texture);
	virtual bool        operator==(const NcGiMaterialTexture & texture) const;
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* other);
	virtual void setStoneColor     (const NcGiMaterialColor &stoneColor);
	virtual const NcGiMaterialColor & stoneColor  (void) const;
	virtual void setVeinColor      (const NcGiMaterialColor &veinColor);
	virtual const NcGiMaterialColor & veinColor  (void) const;
	virtual void setVeinSpacing    (double veinSpacing);
	virtual double veinSpacing     (void) const;
	virtual void setVeinWidth      (double veinWidth);
	virtual double veinWidth       (void) const;
};

//////////////////////////////////////////////////////////////////////////
// NcGiMaterialMap
class OdGiMaterialMap;
class NRXDBGATE_EXPORT NcGiMaterialMap: public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcGiMaterialMap);

	typedef NcGiMaterialMap  wrapper_class;
	typedef OdGiMaterialMap  native_class;

	enum Source {
		kScene = 0,
		kFile,
		kProcedural
	};

	enum Filter
	{
		kFilterDefault = 0,
		kFilterNone
	};

	static const NcGiMaterialMap kNull;

	NcGiMaterialMap();
	NcGiMaterialMap(const NcGiMaterialMap& matMap);
	NcGiMaterialMap(const OdGiMaterialMap& matMap);
	virtual ~NcGiMaterialMap();

	
	NcGiMaterialMap& operator=   (const NcGiMaterialMap& matMap);
	bool              operator== (const NcGiMaterialMap& matMap) const;

	virtual void      set            (const NcGiMaterialMap& matMap);
	virtual void      set            (const OdGiMaterialMap& matMap);

	NRX_DEPRECATED virtual void         setSourceFileName (const NCHAR* fileName);
	NRX_DEPRECATED virtual const NCHAR* sourceFileName    () const;

	virtual void      setSource      (Source source);
	virtual void      setTexture     (const NcGiMaterialTexture* pTexture);
	virtual void      setBlendFactor (double blendFactor);
	virtual void      setMapper      (const NcGiMapper& mapper);
	Nano::ErrorStatus setFilter      (Filter filter);

	virtual Source                     source      () const;
	virtual const NcGiMaterialTexture* texture     () const;
	virtual double                     blendFactor () const;
	virtual const NcGiMapper           mapper      () const;
	Filter                             filter      () const;

public:
	OdGiMaterialMap* native() const;

protected:
	const NcGiMaterialTexture * m_tex;
	bool m_texPrivate;

protected:
	OdGiMaterialMap* m_pImpl;
};

//////////////////////////////////////////////////////////////////////////
// NcGiStyleAttributes
class NRX_NO_VTABLE NcGiStyleAttributes {
public:
	enum AttributeFlags {
		kNothing                = 0x00,
		kColor                  = 0x01,
		kLine                   = 0x02,
		kLineType               = 0x04,
		kPlotStyle              = 0x08,
		kEverything             = 0x0F
	};
	NcGiStyleAttributes()   { }
	NcGiStyleAttributes(const NcGiStyleAttributes& source);
	virtual ~NcGiStyleAttributes()  { }
	NcCmEntityColor& getColorAttribute();
	const NcCmEntityColor& getColorAttribute() const;
	void setColorAttribute(const NcCmEntityColor& color);
	NcDbObjectId linetypeObjectId() const;
	void setLinetypeObjectId(const NcDbObjectId& newId);
	NcDbObjectId plotStyleNameId() const;
	void setPlotStyleName(const NcDbObjectId& newId);
	virtual NcGiLineAttributes* getLineAttribute()                              = 0;
	virtual const NcGiLineAttributes* getLineAttribute() const                  = 0;
	virtual void setLineAttribute(const NcGiLineAttributes* pLineAttributes)    = 0;
	virtual void EnsureColorVisibility (NcCmEntityColor& color)                 = 0;
protected:
	NcCmEntityColor m_colorAttribute;
	NcDbObjectId    m_idLinetype;
	NcDbObjectId    m_idPlotstyle;
};

//////////////////////////////////////////////////////////////////////////
// CNcGradientThumbnailEngine
class CNcGradientThumbnailEngine {
public:
	virtual ~CNcGradientThumbnailEngine() {}
	virtual Nano::ErrorStatus gradientThumbnailsSetRotation( double angle ) = 0;
	virtual Nano::ErrorStatus gradientThumbnailsSetShift( bool bShifted ) = 0;
	virtual Nano::ErrorStatus gradientThumbnailsSetStartColor( NcCmEntityColor startColor ) = 0;
	virtual Nano::ErrorStatus gradientThumbnailsSetStopColor( NcCmEntityColor stopColor ) = 0;
	virtual Nano::ErrorStatus gradientThumbnailsRender(void) = 0;
	virtual Nano::ErrorStatus gradientThumbnailsDrawBitmap( int gradientNumber, HDC hDC, int xPos, int yPos ) = 0;
};

CNcGradientThumbnailEngine *createGradientThumbnailEngine();

//////////////////////////////////////////////////////////////////////////
// NcGsRenderProgressMonitor
class NcGsRenderProgressMonitor {
public:
	enum Phase
	{
		kTranslation,
		kPhotonEmission,
		kFinalGather,
		kRender
	};
	virtual bool OnProgress(Phase ePhase, float fProgress) = 0;
	virtual void OnTile(int x, int y, int w, int h, const BYTE* pPixels) = 0;
	virtual void SetStatistics(const NcGsRenderStatistics* pStats) = 0;
	virtual bool ShouldReuseDatabase() { return false; }
};

//////////////////////////////////////////////////////////////////////////
// NcGsConfig2
class NcGsConfig2 : public NcGsConfig {
public:
	virtual bool                generateVertexNormals           (void) const                    = 0;
	virtual void                setGenerateVertexNormals        (bool bEnable)                  = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiLinetypeEngine
class NRXDBGATE_EXPORT NcGiLinetypeEngine : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcGiLinetypeEngine);
	NcGiLinetypeEngine();
	virtual ~NcGiLinetypeEngine();
	virtual Nano::ErrorStatus tessellate (bool                 bIsArc,
	                                      bool                 bIsCircle,
	                                      const NRX::UInt32  nPoints,
	                                      const NcGePoint3d  * pVertexList,
	                                      NcGiWorldDraw *      pWorldDraw,
	                                      const NcDbObjectId   linetypeId,
	                                      double               linetypeScale,
	                                      const NcGeVector3d * pNormal);
	virtual Nano::ErrorStatus tessellate (bool                 bIsArc,
	                                      bool                 bIsCircle,
	                                      const NRX::UInt32  nPoints,
	                                      const NcGePoint3d  * pVertexList,
	                                      NcGiViewportDrawNrx *   pViewportDraw,
	                                      const NcDbObjectId   linetypeId,
	                                      double               linetypeScale,
	                                      const NcGeVector3d * pNormal);
	virtual Nano::ErrorStatus tessellate (const NcGeCircArc3d& arcSeg,
	                                      const NcGeMatrix3d&  ecsMat,
	                                      double               startWidth,
	                                      double               endWidth,
	                                      NcGiCommonDraw *     pDraw,
	                                      const NcDbObjectId   linetypeId,
	                                      double               linetypeScale,
	                                      double               thick);
	virtual Nano::ErrorStatus tessellate (const NcGeLineSeg3d& lineSeg,
	                                      const NcGeMatrix3d&  ecsMat,
	                                      double               startWidth,
	                                      double               endWidth,
	                                      NcGiCommonDraw *     pDraw,
	                                      const NcDbObjectId   linetypeId,
	                                      double               linetypeScale);
};

//////////////////////////////////////////////////////////////////////////
// NcReCallout
class NcReCallout {
	public :
	  virtual void e2fHeaderData(struct e2f_hdr *hdr) { }
	  virtual void e2fLayerData(struct e2f_layer *lyr) { }
	  virtual void e2fBlockData(struct e2f_ent *ent,
	                            struct e2f_xform *xform) { }
	  virtual void e2fEntityData(struct e2f_ent *ent) { }
	  virtual void e2fVertexData(dwg3dp *vertex_array) { }
	  virtual void e2fNormalData(dwg3dp *normals_array) { }
	  virtual void e2fMeshData(struct scn_pmsh *polymesh,
	                           long **polyindex) { }
	  int flag;
};

//////////////////////////////////////////////////////////////////////////
// NcGiTextEngine
class NRXDBGATE_EXPORT NcGiTextEngine {
public:
	static   NcGiTextEngine * create();
	virtual ~NcGiTextEngine() { ; }
	virtual void getExtents (NcGiTextStyle &    ts,
	                         NCHAR const *      pStr,
	                         int                nLength,
	                         bool               bPenUp,
	                         bool               bRaw,
	                         NcGePoint2d &      extents) = 0;
	virtual void tessellate (NcGiTextStyle &    ts,
	                         NCHAR const *      pStr,
	                         int                nLength,
	                         bool               bRaw,
	                         double             deviation,
	                         void *             pVoid,
	                         PolylineCallback   pPolylineCallback) = 0;
	virtual void tessellate (NcGiTextStyle &    ts,
	                         NCHAR const *      pString,
	                         int                nLength,
	                         bool               bRaw,
	                         void *             pVoid,
	                         UnicodeCallback    pUnicodeCallback,
	                         PolylineCallback   pPolylineCallback) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiSolidBackgroundTraits
class NRXDBGATE_EXPORT NcGiSolidBackgroundTraits : public NcGiNonEntityTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiSolidBackgroundTraits);
	virtual void            setColorSolid           (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor colorSolid              (void) const            = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiGradientBackgroundTraits
class NRXDBGATE_EXPORT NcGiGradientBackgroundTraits : public NcGiNonEntityTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiGradientBackgroundTraits);
	virtual void            setColorTop             (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor colorTop                (void) const           = 0;
	virtual void            setColorMiddle          (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor colorMiddle             (void) const           = 0;
	virtual void            setColorBottom          (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor colorBottom             (void) const           = 0;
	virtual void            setHorizon              (double horizon)       = 0;
	virtual double          horizon                 (void) const           = 0;
	virtual void            setHeight               (double height)        = 0;
	virtual double          height                  (void) const           = 0;
	virtual void            setRotation             (double rotation)      = 0;
	virtual double          rotation                (void) const           = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiImageBackgroundTraits
class NRXDBGATE_EXPORT NcGiImageBackgroundTraits : public NcGiNonEntityTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiImageBackgroundTraits);
	virtual void            setImageFilename        (const NCHAR* filename) = 0;
	virtual const NCHAR *   imageFilename           (void) const           = 0;
	virtual void            setFitToScreen          (bool bFitToScreen)    = 0;
	virtual bool            fitToScreen             (void) const           = 0;
	virtual void            setMaintainAspectRatio  (bool bMaintainAspectRatio) = 0;
	virtual bool            maintainAspectRatio     (void) const           = 0;
	virtual void            setUseTiling            (bool bUseTiling)      = 0;
	virtual bool            useTiling               (void) const           = 0;
	virtual void            setXOffset              (double xOffset)       = 0;
	virtual double          xOffset                 (void) const           = 0;
	virtual void            setYOffset              (double yOffset)       = 0;
	virtual double          yOffset                 (void) const           = 0;
	virtual void            setXScale               (double xScale)        = 0;
	virtual double          xScale                  (void) const           = 0;
	virtual void            setYScale               (double yScale)        = 0;
	virtual double          yScale                  (void) const           = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiGroundPlaneBackgroundTraits
class NRXDBGATE_EXPORT NcGiGroundPlaneBackgroundTraits : public NcGiNonEntityTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiGroundPlaneBackgroundTraits);
	virtual void            setColorSkyZenith       (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor colorSkyZenith          (void) const           = 0;
	virtual void            setColorSkyHorizon      (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor colorSkyHorizon         (void) const           = 0;
	virtual void            setColorUndergroundHorizon  (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor colorUndergroundHorizon     (void) const           = 0;
	virtual void            setColorUndergroundAzimuth  (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor colorUndergroundAzimuth     (void) const           = 0;
	virtual void            setColorGroundPlaneNear (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor colorGroundPlaneNear    (void) const           = 0;
	virtual void            setColorGroundPlaneFar  (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor colorGroundPlaneFar     (void) const           = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiSkyBackgroundTraits
class NRXDBGATE_EXPORT NcGiSkyBackgroundTraits : public NcGiNonEntityTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiSkyBackgroundTraits);
	virtual void setSkyParameters(const NcGiSkyParameters& params) = 0;
	virtual void skyParameters(NcGiSkyParameters& params) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiRenderEnvironmentTraits
class NRXDBGATE_EXPORT NcGiRenderEnvironmentTraits : public NcGiNonEntityTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiRenderEnvironmentTraits);
	virtual void            setEnable               (const bool bEnable)    = 0;
	virtual bool            enable                  (void) const            = 0;
	virtual void            setIsBackground         (const bool bEnable)    = 0;
	virtual bool            isBackground            (void) const            = 0;
	virtual void            setFogColor             (const NcCmEntityColor & color) = 0;
	virtual NcCmEntityColor fogColor                (void) const            = 0;
	virtual void            setNearDistance         (const double nearDist) = 0;
	virtual double          nearDistance            (void) const            = 0;
	virtual void            setFarDistance          (const double farDist)  = 0;
	virtual double          farDistance             (void) const            = 0;
	virtual void            setNearPercentage       (const double nearPct)  = 0;
	virtual double          nearPercentage          (void) const            = 0;
	virtual void            setFarPercentage        (const double farPct)   = 0;
	virtual double          farPercentage           (void) const            = 0;
	virtual void            setEnvironmentMap       (const NcGiMaterialTexture * map) = 0;
	virtual NcGiMaterialTexture * environmentMap    (void) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiRenderSettingsTraits
class NRXDBGATE_EXPORT NcGiRenderSettingsTraits : public NcGiNonEntityTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiRenderSettingsTraits);
	virtual void setMaterialEnabled(bool enabled) = 0;
	virtual bool materialEnabled() const = 0;
	virtual void setTextureSampling(bool enabled) = 0;
	virtual bool textureSampling() const = 0;
	virtual void setBackFacesEnabled(bool enabled) = 0;
	virtual bool backFacesEnabled() const = 0;
	virtual void setShadowsEnabled(bool enabled) = 0;
	virtual bool shadowsEnabled() const = 0;
	virtual void setDiagnosticBackgroundEnabled(bool enabled) = 0;
	virtual bool diagnosticBackgroundEnabled() const = 0;
	virtual void            setModelScaleFactor     (double scaleFactor)    = 0;
	virtual double          modelScaleFactor        (void) const            = 0;
};

// The available filtering methods (kernels) used to combine samples into
// a pixel color.
//
typedef enum {
	krBox = 0,
	krTriangle,
	krGauss,
	krMitchell,
	krLanczos
} NcGiMrFilter;

// The available methods for computing ray-traced shadows.
//
typedef enum {
	krSimple = 0,
	krSorted,
	krSegments
} NcGiMrShadowMode;

typedef enum {
	krOff = 0,
	krGrid,
	krPhoton,
	krSamples,
	krBSP
} NcGiMrDiagnosticMode;

typedef enum {
	krObject = 0,
	krWorld,
	krCamera
} NcGiMrDiagnosticGridMode;

typedef enum {
	krDensity = 0,
	krIrradiance
} NcGiMrDiagnosticPhotonMode;

typedef enum {
	krDepth = 0,
	krSize
} NcGiMrDiagnosticBSPMode;

typedef enum {
	krHilbert = 0,
	krSpiral,
	krLeftToRight,
	krRightToLeft,
	krTopToBottom,
	krBottomToTop
} NcGiMrTileOrder;

typedef enum {
	krAutomatic = 0,
	krLogarithmic
} NcGiMrExposureType;

typedef enum {
	krFinalGatherOff = 0,
	krFinalGatherOn,
	krFinalGatherAuto
} NcGiMrFinalGatheringMode;

typedef enum {
	krExportMIOff = 0,
	krExportMIWithRender,
	krExportMIOnly
} NcGiMrExportMIMode;

//////////////////////////////////////////////////////////////////////////
// NcGiMentalRayRenderSettingsTraits
class NRXDBGATE_EXPORT NcGiMentalRayRenderSettingsTraits : public NcGiRenderSettingsTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiMentalRayRenderSettingsTraits);
	virtual void setSampling(int min, int max) = 0;
	virtual void sampling(int& min, int& max) const = 0;
	virtual void setSamplingFilter(NcGiMrFilter filter, double width, double height) = 0;
	virtual void SamplingFilter(NcGiMrFilter& filter, double& width, double& height) const = 0;
	virtual void setSamplingContrastColor(float r, float g, float b, float a) = 0;
	virtual void samplingContrastColor(float& r, float& g, float& b, float& a) const = 0;
	virtual void setShadowMode(NcGiMrShadowMode mode) = 0;
	virtual NcGiMrShadowMode shadowMode() const = 0;
	virtual void setShadowMapEnabled(bool enabled) = 0;
	virtual bool shadowMapEnabled() const = 0;
	virtual void setRayTraceEnabled(bool enabled) = 0;
	virtual bool rayTraceEnabled() const = 0;
	virtual void setRayTraceDepth(int reflection, int refraction, int sum) = 0;
	virtual void rayTraceDepth(int& reflection, int& refraction, int& sum) const = 0;
	virtual void setGlobalIlluminationEnabled(bool enabled) = 0;
	virtual bool globalIlluminationEnabled() const = 0;
	virtual void setGISampleCount(int num) = 0;
	virtual int giSampleCount() const = 0;
	virtual void setGISampleRadiusEnabled(bool enabled) = 0;
	virtual bool giSampleRadiusEnabled() const = 0;
	virtual void setGISampleRadius(double radius) = 0;
	virtual double giSampleRadius() const = 0;
	virtual void setGIPhotonsPerLight(int num) = 0;
	virtual int giPhotonsPerLight() const = 0;
	virtual void setPhotonTraceDepth(int reflection, int refraction, int sum) = 0;
	virtual void photonTraceDepth(int& reflection, int& refraction, int& sum) const = 0;
	virtual void setFinalGatheringEnabled(bool enabled) = 0;
	virtual bool finalGatheringEnabled() const = 0;
	virtual void setFGRayCount(int num) = 0;
	virtual int fgRayCount() const = 0;
	virtual void setFGRadiusState(bool bMin, bool bMax, bool bPixels) = 0;
	virtual void fgSampleRadiusState(bool& bMin, bool& bMax, bool& bPixels) = 0;
	virtual void setFGSampleRadius(double min, double max) = 0;
	virtual void fgSampleRadius(double& min, double& max) const = 0;
	virtual void setLightLuminanceScale(double luminance) = 0;
	virtual double lightLuminanceScale() const = 0;
	virtual void setDiagnosticMode(NcGiMrDiagnosticMode mode) = 0;
	virtual NcGiMrDiagnosticMode diagnosticMode() const = 0;
	virtual void setDiagnosticGridMode(NcGiMrDiagnosticGridMode mode, float fSize) = 0;
	virtual void diagnosticGridMode(NcGiMrDiagnosticGridMode& mode, float& fSize) const = 0;
	virtual void setDiagnosticPhotonMode(NcGiMrDiagnosticPhotonMode mode) = 0;
	virtual NcGiMrDiagnosticPhotonMode diagnosticPhotonMode() const = 0;
	virtual void setDiagnosticBSPMode(NcGiMrDiagnosticBSPMode mode) = 0;
	virtual NcGiMrDiagnosticBSPMode diagnosticBSPMode() const = 0;
	virtual void setExportMIEnabled(bool enabled) = 0;
	virtual bool exportMIEnabled() const = 0;
	virtual void setExportMIFileName(const NCHAR* miName) = 0;
	virtual const NCHAR* exportMIFileName() const = 0;
	virtual void setTileSize(int size) = 0;
	virtual int tileSize() const = 0;
	virtual void setTileOrder(NcGiMrTileOrder order) = 0;
	virtual NcGiMrTileOrder tileOrder() const = 0;
	virtual void setMemoryLimit(int limit) = 0;
	virtual int memoryLimit() const = 0;
	virtual void setEnergyMultiplier(float fScale) = 0;
	virtual float energyMultiplier() const = 0;
	virtual void setProgressMonitor(void* pMonitor) = 0;
	virtual const void* progressMonitor(void) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiMentalRayRenderSettingsTraits2
class NRXDBGATE_EXPORT NcGiMentalRayRenderSettingsTraits2 : public NcGiMentalRayRenderSettingsTraits {
public:
	NCRX_DECLARE_MEMBERS(NcGiMentalRayRenderSettingsTraits2);
	virtual void setExposureType(NcGiMrExposureType type) = 0;
	virtual NcGiMrExposureType exposureType() const = 0;
	virtual void setFinalGatheringMode(NcGiMrFinalGatheringMode mode) = 0;
	virtual NcGiMrFinalGatheringMode finalGatheringMode() const = 0;
	virtual void setShadowSamplingMultiplier(double multiplier) = 0;
	virtual double shadowSamplingMultiplier() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiMentalRayRenderSettingsTraits3
class NRXDBGATE_EXPORT NcGiMentalRayRenderSettingsTraits3 : public NcGiMentalRayRenderSettingsTraits2 {
public:
	NCRX_DECLARE_MEMBERS(NcGiMentalRayRenderSettingsTraits3);
	virtual void setExportMIMode(NcGiMrExportMIMode mode) = 0;
	virtual NcGiMrExportMIMode exportMIMode() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGiToneOperatorParameters
class NRXDBGATE_EXPORT NcGiToneOperatorParameters : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcGiToneOperatorParameters);
	NcGiToneOperatorParameters();
	virtual ~NcGiToneOperatorParameters();
	bool operator==(const NcGiToneOperatorParameters& params) const;
	virtual void setIsActive(bool );
	virtual bool isActive() const;
	virtual void setChromaticAdaptation(bool enable);
	virtual bool chromaticAdaptation() const;
	virtual void setColorDifferentiation(bool enable);
	virtual bool colorDifferentiation() const;
	virtual void setWhiteColor(const NcCmColor& color);
	virtual NcCmColor whiteColor() const;
	virtual void setProcessBackground(bool processBG);
	virtual bool processBackground() const;
	virtual bool setBrightness(double brightness);
	virtual double brightness() const;
	virtual bool setContrast(double contrast);
	virtual double contrast() const;
	virtual bool setMidTones(double midTones);
	virtual double midTones() const;
	enum ExteriorDaylightMode {
		kDaylightOff = 0,
		kDaylightOn,
		kDaylightAuto
	};
	virtual bool setExteriorDaylight(ExteriorDaylightMode mode);
	virtual ExteriorDaylightMode exteriorDaylight() const;
private:
	bool                    mbIsActive;
	bool                    mbChromaticAdaptation;
	bool                    mbColorDifferentiation;
	NcCmColor               mWhiteColor;
	bool                    mbProcessBackground;
	double                  mBrightness;
	double                  mContrast;
	double                  mMidTones;
	ExteriorDaylightMode    mExteriorDaylight;
};

//////////////////////////////////////////////////////////////////////////
// NcGiViewportTraits2

//class NcGiViewportTraits2 : public NcGiViewportTraits {
//public:
	//    NCRX_DECLARE_MEMBERS(NcGiViewportTraits2);
//    virtual void setToneOperatorParameters(const NcGiToneOperatorParameters& params) = 0;
//    virtual void toneOperatorParameters(NcGiToneOperatorParameters& params) const = 0;
//};


//////////////////////////////////////////////////////////////////////////
// NcGiDrawableOverrule
class NRXDBGATE_EXPORT NcGiDrawableOverrule : public NcRxOverrule {
public:
	NCRX_DECLARE_MEMBERS(NcGiDrawableOverrule);
	NcGiDrawableOverrule();
	virtual NRX::UInt32 setAttributes(NcGiDrawable* pSubject, NcGiDrawableTraits * traits);
	virtual NRX::Boolean worldDraw(NcGiDrawable* pSubject, NcGiWorldDraw * wd);
	virtual void viewportDraw(NcGiDrawable* pSubject, NcGiViewportDrawNrx * vd);
	virtual NRX::UInt32 viewportDrawLogicalFlags(NcGiDrawable* pSubject, NcGiViewportDrawNrx * vd);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGiViewportTraits
class OdGiViewportTraits;
class OdGiDrawableTraits;
class NRXDBGATE_EXPORT NcGiViewportTraits : public NcGiDrawableTraits
{
public:
	NCRX_DECLARE_MEMBERS(NcGiViewportTraits);
	typedef NcGiDrawableTraits  wrapper_class;
	typedef OdGiViewportTraits  native_class;
	NcGiViewportTraits();
	NcGiViewportTraits(OdGiDrawableTraits* src);

	virtual NcCmColor ambientLightColor() const;
	virtual NcDbObjectId background () const;

	enum DefaultLightingType {
		kOneDistantLight = 0,
		kTwoDistantLights,
		kBackLighting,
	};

	virtual double brightness() const;
	virtual double contrast() const;
	virtual DefaultLightingType defaultLightingType() const;
	virtual bool isDefaultLightingOn() const;
	virtual NcDbObjectId renderEnvironment () const;
	virtual NcDbObjectId renderSettings () const;
	virtual void setAmbientLightColor(const NcCmColor& clr);
	virtual void setBackground(const NcDbObjectId backgroundId);
	virtual void setBrightness (double brightness);
	virtual void setContrast (double contrast);
	virtual void setDefaultLightingOn(bool on);
	virtual void setDefaultLightingType(DefaultLightingType typ);
	virtual void setRenderEnvironment (const NcDbObjectId renderEnvId);
	virtual void setRenderSettings (const NcDbObjectId renderSettingsId);

public:
	OdGiViewportTraits* native() const;
};


Nano::ErrorStatus ncgiGetRegenBlockRefStack(NcDbObjectIdArray& blkRefs);
bool ncgiIsValidClipBoundary(const NcGePoint2dArray& pts);
NRX::Boolean ncgsDrawableErased(NcGiDrawable *pDrawable,
                                NcGiDrawable *pParentDrawable);
NRX::Boolean ncgsDrawableModified(NcGiDrawable *pDrawable,
                                  NcGiDrawable *pParentDrawable);
NcGsModel * ncgsGetGsModel(NcGiTransientDrawingMode mode,
                           int subDrawingMode,
                           int viewportNumber);
Nano::ErrorStatus ncreEntityToFaces(nds_name ss, NCHAR** const name, int normal);
int ncreRegisterCallout(NcReCallout * imp);

// AutoGern.

#endif // __NANOTHUNK_GRAPHICS_H__
