
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

#ifndef __OPENDWG_GEOMETRY_H__
#define __OPENDWG_GEOMETRY_H__

#include "nrxdbgate_impexp.h"


#ifndef PI
	#define PI  3.1415926535897932384626433832795
#endif

#ifndef PI2
	#define PI2  6.283185307179586476925286766559
#endif

class NcGeLine2d;
class NcGeLine3d;
class NcGeLinearEnt2d;
class NcGeLinearEnt3d;
class NcGeMatrix2d;
class NcGeMatrix3d;
class NcGePlane;
class NcGePlanarEnt;
class NcGePoint2d;
class NcGePoint3d;
class NcGeVector2d;
class NcGeVector3d;
class NcGePolyline3d;

class OdGeScale3d;

#define MCGE_OD_SUPPORT

typedef McGe  NcGe;

#define NcGeVector2d        McGeVector2d
#define NcGeContext         McGeContext
#define NcGeTol             McGeTol
#define NcGeError           McGeError
#define NcGePointOnCurve3d  McGePointOnCurve3d
#define NcGeBoundBlock3d    McGeBoundBlock3d

class OdGeExternalSurface;
class OdGeExternalBoundedSurface;
class OdGeCubicSplineCurve3d;

#ifdef NcGePoint2dArray
	#undef NcGePoint2dArray
#endif
typedef NcArray< NcGePoint2d, HostMemoryAllocator<NcGePoint2d> >  NcGePoint2dArray;
template class NRXDBGATE_EXPORT NcArray<NcGePoint2d, HostMemoryAllocator<NcGePoint2d>>;

#ifdef NcGePoint3dArray
	#undef NcGePoint3dArray
#endif
typedef NcArray< NcGePoint3d, HostMemoryAllocator<NcGePoint3d> >  NcGePoint3dArray;
template class NRXDBGATE_EXPORT NcArray<NcGePoint3d, HostMemoryAllocator<NcGePoint3d>>;

#ifdef NcGeVector2dArray
	#undef NcGeVector2dArray
#endif
typedef NcArray< NcGeVector2d, HostMemoryAllocator<NcGeVector2d>>  NcGeVector2dArray;
template class NRXDBGATE_EXPORT NcArray<NcGeVector2d, HostMemoryAllocator<NcGeVector2d>>;

#ifdef NcGeVector3dArray
	#undef NcGeVector3dArray
#endif
typedef NcArray< NcGeVector3d, HostMemoryAllocator<NcGeVector3d>>  NcGeVector3dArray;
template class NRXDBGATE_EXPORT NcArray<NcGeVector3d, HostMemoryAllocator<NcGeVector3d>>;

class NcGeCurve2d;
class NcGePointOnCurve2d;
class NcGeRay3d;

#define NcGeIntersectError McGeIntersectError
#define NcGeXConfig McGeXConfig

class NcConstrainedGeometry;
class NcHelpParameter;
class NcCompositeConstraint;
class NcEqualHelpParameterConstraint;
class NcGePointOnSurface;
class NcGeCurveBoundary;
class NcGePosition3d;
class NcGeNurbCurve2d;
class NcGeFiler;
class NcGeLibVersion;
class NcGeScale2d;
class NcGePosition2d;
class NcGeOffsetCurve2d;
class NcGeOffsetCurve3d;
class NcGeTorus;
class NcGeOffsetSurface;
class NcGeNurbSurface;
class NcGeExternalBoundedSurface;
class NcGeSphere;
class NcGeEllipCone;
class NcGePoint2d;

typedef void (*PolylineCallback) (int, int const *, NcGePoint3d const *, void *);
typedef void (*UnicodeCallback) (NRX::LongPtr, wchar_t const *, int, void *);

enum KnotParameterization {
	kChord = 0,
	kSqrtChord,
	kUniform,
	kCustomParameterization = 15
};

typedef enum {
	kMiterJoin                                = 0x00,
	kBevelJoin                                = 0x01,
	kRoundJoin                                = 0x02,
	kDiamondJoin                              = 0x03,
} NcGiLineJoinStyle;

typedef enum {
	kButtCap                                  = 0x00,
	kSquareCap                                = 0x01,
	kRoundCap                                 = 0x02,
	kDiamondCap                               = 0x03,
} NcGiLineEndStyle;

typedef enum {
	kFillStyleSolid                           = 0x00,
	kCheckerboard                             = 0x01,
	kCrosshatch                               = 0x02,
	kDiamonds                                 = 0x03,
	kHorizontal_Bars                          = 0x04,
	kSlant_Left                               = 0x05,
	kSlant_Right                              = 0x06,
	kSquare_Dots                              = 0x07,
	kVertical_Bars                            = 0x08,
	kUser_Defined                             = 0x09
} NcGiLineFillStyle;

typedef NRX::UInt32 NcConstraintGroupNodeId;

class NcImpConstraintGroupNode;
class NcConstrainedRigidSet;
class NcGeomConstraint;

struct scn_cmesh {
	char   id;
	short  flags;
	long   next;
	short  mshtype;
	short  color;
	short  nverts;
	short  m;
	short  n;
};

struct scn_vrtc {
	char   id;
	double vert[3];
};

struct scn_pmsh {
	char   id;
	short  flags;
#ifndef _WIN64
	long   adr1;
	long   adr2;
#else
	__int64  adr1;
	__int64  adr2;
#endif
	long   layerindex;
	short  color;
	long   truecolor;
	short  ncvrtx;
#ifndef _WIN64
	long   mapperId;
#else
	__int64  mapperId;
#endif
};

struct scn_cvrt {
	char   id;
	long   index;
};

struct scn_node {
	double vertex[3];
	double normal[3];
	long left;
	long right;
};

struct e2f_hdr {
	char id;
	short flags;
	short version;
	long nents;
	long npoly;
	long nlayers;
	unsigned long bgcolor;
	short cmaplen;
	char*cmap;
};

struct e2f_layer {
	char id;
	short layernamelen;
	NCHAR*lname;
};

struct e2f_ent {
	char id;
	short flags;
	short type;
#ifndef _WIN64
	long  adr1;
	long  adr2;
#else
	__int64  adr1;
	__int64  adr2;
#endif
	long  npoly;
	long  nverts;
	short color;
	long  truecolor;
	long  layerindex;
#ifndef _WIN64
	long  materialId;
#else
	__int64 materialId;
#endif
};

struct e2f_xform {
	char id;
	short flags;
	double xfmatrix[4][4];
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeInterval

class NRXDBGATE_EXPORT NcGeInterval : public McGeInterval
{
public:
	NcGeInterval(double tol = 1.e-12);
	NcGeInterval(const McGeInterval& src);
	NcGeInterval(const NcGeInterval& src);
	NcGeInterval(double lower, double upper, double tol = 1.e-12);
	NcGeInterval(NRX::Boolean boundedBelow, double bound, double tol = 1.e-12);

	NcGeInterval& operator =(const NcGeInterval& src);
	NcGeInterval& operator =(const McGeInterval& src);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGePoint2d

class NcGePoint2d : public McGePoint2d
{
public:
	NRXDBGATE_EXPORT NcGePoint2d();
	NRXDBGATE_EXPORT NcGePoint2d(const McGePoint2d& pnt);
	NRXDBGATE_EXPORT NcGePoint2d(double x, double y);

	NRXDBGATE_EXPORT NcGePoint2d& operator=(const McGePoint2d& src);
	NRXDBGATE_EXPORT NcGePoint2d operator+(const McGeVector2d& vec) const;
	NRXDBGATE_EXPORT NcGePoint2d& mirror(const NcGeLine2d& line);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGePoint3d

class NcGePoint3d : public McGePoint3d
{
public:
	NRXDBGATE_EXPORT NcGePoint3d();
	NRXDBGATE_EXPORT NcGePoint3d(const NcGePoint3d& pnt);
	NRXDBGATE_EXPORT NcGePoint3d(double x, double y, double z);
	NRXDBGATE_EXPORT NcGePoint3d(const NcGePlanarEnt& pln, const NcGePoint2d& pnt2d);
	NRXDBGATE_EXPORT NcGePoint3d(const McGePoint3d& pnt);


	NRXDBGATE_EXPORT static const NcGePoint3d kOrigin;

	friend NRXDBGATE_EXPORT
	NcGePoint3d  operator *  (const NcGeMatrix3d& mat, const NcGePoint3d& pnt);

	NRXDBGATE_EXPORT NcGePoint3d& setToProduct(const NcGeMatrix3d& mat, const NcGePoint3d& pnt);
	NRXDBGATE_EXPORT NcGePoint3d& transformBy (const NcGeMatrix3d& leftSide);
	NRXDBGATE_EXPORT NcGePoint3d& rotateBy    (double angle, const NcGeVector3d& vec,
	                          const NcGePoint3d& wrtPoint = NcGePoint3d::kOrigin);
	NRXDBGATE_EXPORT NcGePoint3d& mirror      (const NcGePlane& pln);
	NRXDBGATE_EXPORT NcGePoint3d& scaleBy     (double scaleFactor, const NcGePoint3d& wrtPoint = NcGePoint3d::kOrigin);
	NRXDBGATE_EXPORT NcGePoint2d  convert2d   (const NcGePlanarEnt& pln) const;

	NRXDBGATE_EXPORT NcGePoint3d  operator *  (double scl) const;
	NRXDBGATE_EXPORT NcGePoint3d& operator *= (double scl);
	NRXDBGATE_EXPORT NcGePoint3d  operator /  (double scl) const;
	NRXDBGATE_EXPORT NcGePoint3d& operator /= (double scl);

	NRXDBGATE_EXPORT NcGePoint3d  operator +  (const NcGeVector3d& vec) const;
	NRXDBGATE_EXPORT NcGePoint3d& operator += (const NcGeVector3d& vec);
	NRXDBGATE_EXPORT NcGePoint3d  operator -  (const NcGeVector3d& vec) const;
	NRXDBGATE_EXPORT NcGePoint3d& operator -= (const NcGeVector3d& vec);
	NRXDBGATE_EXPORT NcGePoint3d& setToSum    (const NcGePoint3d& pnt, const NcGeVector3d& vec);

	NRXDBGATE_EXPORT NcGeVector3d operator -  (const NcGePoint3d& pnt) const;
	NRXDBGATE_EXPORT NcGeVector3d asVector    () const;

	NRXDBGATE_EXPORT double       distanceTo  (const NcGePoint3d& pnt) const;

	NRXDBGATE_EXPORT NcGePoint3d  project     (const NcGePlane& pln, const NcGeVector3d& vec) const;
	NRXDBGATE_EXPORT NcGePoint3d  orthoProject(const NcGePlane& pln) const;

	NRXDBGATE_EXPORT bool         operator == (const NcGePoint3d& pnt) const;
	NRXDBGATE_EXPORT bool         operator != (const NcGePoint3d& pnt) const;
	NRXDBGATE_EXPORT bool         isEqualTo   (const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;

	NRXDBGATE_EXPORT double       operator [] (unsigned int i) const;
	NRXDBGATE_EXPORT double&      operator [] (unsigned int idx);
	NRXDBGATE_EXPORT NcGePoint3d& set         (double x, double y, double z);
	NRXDBGATE_EXPORT NcGePoint3d& set         (const NcGePlanarEnt& pln, const NcGePoint2d& pnt);

	NRXDBGATE_EXPORT operator const OdGePoint3d&() const;
	NRXDBGATE_EXPORT operator OdGePoint3d&();
	NRXDBGATE_EXPORT NcGePoint3d(const OdGePoint3d& src);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeVector3d

class NcGeVector3d :  public McGeVector3d
{
public:
	NRXDBGATE_EXPORT NcGeVector3d();
	NRXDBGATE_EXPORT NcGeVector3d(const NcGeVector3d& vec);
	NRXDBGATE_EXPORT NcGeVector3d(double x, double y, double z);
	NRXDBGATE_EXPORT NcGeVector3d(const NcGePlanarEnt&, const NcGeVector2d&);

	NRXDBGATE_EXPORT static const NcGeVector3d kIdentity;
	NRXDBGATE_EXPORT static const NcGeVector3d kXAxis;
	NRXDBGATE_EXPORT static const NcGeVector3d kYAxis;
	NRXDBGATE_EXPORT static const NcGeVector3d kZAxis;

	friend NcGeVector3d NRXDBGATE_EXPORT operator *(const NcGeMatrix3d& mat, const NcGeVector3d& vec);

	NRXDBGATE_EXPORT NcGeVector3d& setToProduct(const NcGeMatrix3d& mat, const NcGeVector3d& vec);

	NRXDBGATE_EXPORT NcGeVector3d& transformBy(const NcGeMatrix3d& leftSide);
	NRXDBGATE_EXPORT NcGeVector3d& rotateBy   (double ang , const NcGeVector3d& axis );
	NRXDBGATE_EXPORT NcGeVector3d& mirror     (const NcGeVector3d& normalToPlane);
	NRXDBGATE_EXPORT NcGeVector2d  convert2d  (const NcGePlanarEnt& pln) const;

	NRXDBGATE_EXPORT NcGeVector3d  operator *(double scl) const;

	friend NcGeVector3d NRXDBGATE_EXPORT operator *(double s, const NcGeVector3d& v);

	NRXDBGATE_EXPORT NcGeVector3d& operator *= (double scl);
	NRXDBGATE_EXPORT NcGeVector3d& setToProduct(const NcGeVector3d& vec, double scl);
	NRXDBGATE_EXPORT NcGeVector3d  operator /  (double scl) const;
	NRXDBGATE_EXPORT NcGeVector3d& operator /= (double scl);

	NRXDBGATE_EXPORT NcGeVector3d   operator +  (const NcGeVector3d& vec) const;
	NRXDBGATE_EXPORT NcGeVector3d&  operator += (const NcGeVector3d& vec);
	NRXDBGATE_EXPORT NcGeVector3d   operator -  (const NcGeVector3d& vec) const;
	NRXDBGATE_EXPORT NcGeVector3d&  operator -= (const NcGeVector3d& vec);
	NRXDBGATE_EXPORT NcGeVector3d&  setToSum    (const NcGeVector3d& vec1, const NcGeVector3d& vec2);
	NRXDBGATE_EXPORT NcGeVector3d   operator -  () const;
	NRXDBGATE_EXPORT NcGeVector3d&  negate      ();

	NRXDBGATE_EXPORT NcGeVector3d   perpVector  () const;

	NRXDBGATE_EXPORT double         angleTo     (const NcGeVector3d& vec) const;
	NRXDBGATE_EXPORT double         angleTo     (const NcGeVector3d& vec, const NcGeVector3d& refVec) const;

	NRXDBGATE_EXPORT double         angleOnPlane(const NcGePlanarEnt& pln) const;

	NRXDBGATE_EXPORT NcGeVector3d   normal      (const NcGeTol& tol = NcGeContext::gTol) const;
	NRXDBGATE_EXPORT NcGeVector3d&  normalize   (const NcGeTol& tol = NcGeContext::gTol);
	NRXDBGATE_EXPORT NcGeVector3d&  normalize   (const NcGeTol& tol, NcGeError& flag);

	NRXDBGATE_EXPORT double         length      () const;
	NRXDBGATE_EXPORT double         lengthSqrd  () const;

	NRXDBGATE_EXPORT bool isUnitLength(const NcGeTol& tol = NcGeContext::gTol) const;
	NRXDBGATE_EXPORT bool isZeroLength(const NcGeTol& tol = NcGeContext::gTol) const;

	NRXDBGATE_EXPORT bool isParallelTo(const NcGeVector3d& vec, const NcGeTol& tol = NcGeContext::gTol) const;
	NRXDBGATE_EXPORT bool isParallelTo(const NcGeVector3d& vec, const NcGeTol& tol, NcGeError& flag) const;

	NRXDBGATE_EXPORT bool isCodirectionalTo(const NcGeVector3d& vec, const NcGeTol& tol = NcGeContext::gTol) const;
	NRXDBGATE_EXPORT bool isCodirectionalTo(const NcGeVector3d& vec, const NcGeTol& tol, NcGeError& flag) const;

	NRXDBGATE_EXPORT bool isPerpendicularTo(const NcGeVector3d& vec, const NcGeTol& tol = NcGeContext::gTol) const;
	NRXDBGATE_EXPORT bool isPerpendicularTo(const NcGeVector3d& vec, const NcGeTol& tol, NcGeError& flag) const;

	NRXDBGATE_EXPORT double         dotProduct  (const NcGeVector3d& vec) const;
	NRXDBGATE_EXPORT NcGeVector3d   crossProduct(const NcGeVector3d& vec) const;

	NRXDBGATE_EXPORT NcGeMatrix3d   rotateTo(const NcGeVector3d& vec, const NcGeVector3d& axis = NcGeVector3d::kIdentity) const;

	NRXDBGATE_EXPORT NcGeVector3d   project(const NcGeVector3d& planeNormal, const NcGeVector3d& projectDirection) const;
	NRXDBGATE_EXPORT NcGeVector3d   project(NcGeVector3d& planeNormal, NcGeVector3d& projectDirection,
	                       NcGeTol& tol, NcGeError& flag) const;

	NRXDBGATE_EXPORT NcGeVector3d   orthoProject(const NcGeVector3d& planeNormal) const;
	NRXDBGATE_EXPORT NcGeVector3d   orthoProject(const NcGeVector3d& planeNormal, const NcGeTol& tol, NcGeError& flag) const;

	NRXDBGATE_EXPORT bool operator ==(const NcGeVector3d& vec) const;
	NRXDBGATE_EXPORT bool operator !=(const NcGeVector3d& vec) const;
	NRXDBGATE_EXPORT bool isEqualTo  (const NcGeVector3d& vec, const NcGeTol& tol = NcGeContext::gTol) const;

	NRXDBGATE_EXPORT double  operator [](unsigned int i) const;
	NRXDBGATE_EXPORT double& operator [](unsigned int i);

	NRXDBGATE_EXPORT unsigned int  largestElement() const;

	NRXDBGATE_EXPORT NcGeVector3d& set(double x, double y, double z);
	NRXDBGATE_EXPORT NcGeVector3d& set(const NcGePlanarEnt& pln, const NcGeVector2d& vec);

	NRXDBGATE_EXPORT operator NcGeMatrix3d() const;

	NRXDBGATE_EXPORT NcGeVector3d(const McGeVector3d& src);

	NRXDBGATE_EXPORT operator const OdGeVector3d&() const;
	NRXDBGATE_EXPORT operator OdGeVector3d&();
	NRXDBGATE_EXPORT NcGeVector3d(const OdGeVector3d& src);
};

NRXDBGATE_EXPORT NcGePoint2d __asPnt2d(const NcGePoint3d& pnt3d);
NRXDBGATE_EXPORT NcGePoint2d __asPnt2d(const McGePoint3d& pnt3d);
NRXDBGATE_EXPORT NcGePoint3d __asPnt3d(const NcGePoint2d& pnt2d);
NRXDBGATE_EXPORT NcGeVector2d __asVec2d(const NcGeVector3d& vec3d);
NRXDBGATE_EXPORT NcGeVector2d __asVec2d(const McGeVector3d& vec3d);
NRXDBGATE_EXPORT NcGeVector3d __asVec3d(const NcGeVector2d& vec2d);

template < class ArrayType1, class ArrayType2 >
void convertArray(const ArrayType1& src, ArrayType2& dst)
{
	dst.removeAll();
	for (int i = 0; i < (int)src.length(); i++)
	{
		dst.append(src[i]);
	}
}

template < class ArrayType1, class ArrayTypeOd >
void convertArrayOd(const ArrayType1& src, ArrayTypeOd& dst)
{
	dst.clear();
	for (int i = 0; i < (int)src.length(); i++)
	{
		dst.append(src[i]);
	}
}

NRXDBGATE_EXPORT void convertVoidPointerArray(const McGePVoidArray& src, NcGeVoidPointerArray& dst);
NRXDBGATE_EXPORT void convertVoidPointerArray(const NcGeVoidPointerArray& src, McGePVoidArray& dst);

NRXDBGATE_EXPORT NcGePoint2d convertFn(const NcGePoint3d& pnt);
NRXDBGATE_EXPORT NcGePoint3d convertFn(const NcGePoint2d& pnt);
NRXDBGATE_EXPORT NcGeVector2d convertFn(const NcGeVector3d& pnt);
NRXDBGATE_EXPORT NcGeVector3d convertFn(const NcGeVector2d& pnt);

template < class ArrayType1, class ArrayType2 > void convertArrayWithFn(const ArrayType1& src, ArrayType2& dst)
{
	dst.removeAll();
	for (int i = 0; i < src.length(); i++)
	{
		dst.append(convertFn(src[i]));
	}
}

class NRXDBGATE_EXPORT NcGeMatrix2d : public McGeMatrix2d
{
public:
	NcGeMatrix2d();
	NcGeMatrix2d(const McGeMatrix2d& mcM);

	static const NcGeMatrix2d kIdentity;

	static NcGeMatrix2d mirroring(const NcGeLine2d& line);
	static NcGeMatrix2d mirroring(const NcGePoint2d& pnt);

	NRX::Boolean isConformal(double& scale, double& angle, NRX::Boolean& isMirror, NcGeVector2d& reflex) const;
	NcGeMatrix2d& operator=(const McGeMatrix2d& src);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeEntity2d
class NRXDBGATE_EXPORT NcGeEntity2d
{
protected:
	NcGeEntity2d();

public:
	NcGeEntity2d(McGeEntity3d* _object);
	virtual ~NcGeEntity2d();

public:
	virtual NRX::Boolean isKindOf(NcGe::EntityId entType) const;
	virtual NcGe::EntityId type() const;

	virtual NcGeEntity2d* copy() const;

	virtual NcGeEntity2d& transformBy(const NcGeMatrix2d& xfm);
	virtual NcGeEntity2d& rotateBy(double angle, const NcGePoint2d& wrtPoint = NcGePoint2d::kOrigin);

	NcGeEntity2d& mirror(const NcGeLine2d& line);
	NRX::Boolean isEqualTo (const NcGeEntity2d& entity,
	                        const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isOn (const NcGePoint2d& pnt,
	                   const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean operator != (const NcGeEntity2d& entity) const;
	NcGeEntity2d& operator = (const NcGeEntity2d& entity);
	NRX::Boolean operator == (const NcGeEntity2d& entity) const;
	NcGeEntity2d& scaleBy (double scaleFactor,
	                       const NcGePoint2d& wrtPoint = NcGePoint2d::kOrigin);
	NcGeEntity2d& translateBy (const NcGeVector2d& translateVec);

public:
	McGeEntity3d* native() const
	{
		return (McGeEntity3d*)m_pImpl;
	}

	static NcGeEntity2d* NewNcGeEntity(McGeEntity3d *pNative, bool bAssert=false);

	McGeEntity3d* m_pImpl;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeBoundBlock2d
class NRXDBGATE_EXPORT NcGeBoundBlock2d : public NcGeEntity2d
{
public:
	NcGeBoundBlock2d();
	NcGeBoundBlock2d(const McGeBoundBlock3d& _object);
	NcGeBoundBlock2d(const NcGeBoundBlock2d& block);
	NcGeBoundBlock2d(const NcGePoint2d& point1, const NcGePoint2d& point2);
	NcGeBoundBlock2d(const NcGePoint2d& base, const NcGeVector2d& dir1, const NcGeVector2d& dir2);

public:
	virtual NRX::Boolean contains(const NcGePoint2d& point) const;
	virtual void getMinMaxPoints(NcGePoint2d& point1, NcGePoint2d& point2) const;
	virtual void get(NcGePoint2d& base, NcGeVector2d& dir1, NcGeVector2d& dir2) const;
	virtual NcGeBoundBlock2d& set(const NcGePoint2d& point1, const NcGePoint2d& point2);
	virtual NcGeBoundBlock2d& set(const NcGePoint2d& base, const NcGeVector2d& dir1, const NcGeVector2d& dir2);

	NcGeBoundBlock2d& swell(double distance);

	NRX::Boolean isDisjoint(const NcGeBoundBlock2d& block) const;

	NcGeBoundBlock2d& extend(const NcGePoint2d& point);

	NRX::Boolean isBox () const;
	NcGeBoundBlock2d& operator = (const NcGeBoundBlock2d& block);
	NcGeBoundBlock2d& setToBox (NRX::Boolean);

public:
	McGeBoundBlock3d* native() const
	{
		return (McGeBoundBlock3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeCurve2d
class NRXDBGATE_EXPORT NcGeCurve2d : public NcGeEntity2d
{
protected:
	NcGeCurve2d();

public:
	NcGeCurve2d(McGeCurve3d* _curve);

public:
	virtual void getInterval(NcGeInterval& intrvl) const;
	virtual void getInterval(NcGeInterval& intrvl, NcGePoint2d& start, NcGePoint2d& end) const;
	virtual NcGeCurve2d& reverseParam();
	virtual NcGeCurve2d& setInterval();
	virtual NRX::Boolean setInterval(const NcGeInterval& intrvl);

	virtual double distanceTo(const NcGePoint2d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual double distanceTo(const NcGeCurve2d& curve, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGePoint2d closestPointTo(const NcGePoint2d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NcGePoint2d closestPointTo(const NcGeCurve2d& curve, NcGePoint2d& pntOnOtherCrv,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getClosestPointTo(const NcGePoint2d& pnt, NcGePointOnCurve2d& pntOnCrv,
	                               const NcGeTol& tol = NcGeContext::gTol) const;
	virtual void getClosestPointTo(const NcGeCurve2d& curve2d, NcGePointOnCurve2d& pntOnThisCrv,
	                               NcGePointOnCurve2d& pntOnOtherCrv, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean getNormalPoint(const NcGePoint2d& pnt, NcGePointOnCurve2d& pntOnCrv,
	                                    const NcGeTol& tol = NcGeContext::gTol) const;

	NcGeBoundBlock2d boundBlock() const;
	NcGeBoundBlock2d boundBlock(const NcGeInterval& range) const;
	NcGeBoundBlock2d orthoBoundBlock() const;
	NcGeBoundBlock2d orthoBoundBlock(const NcGeInterval& range) const;

	virtual NRX::Boolean isOn(const NcGePoint2d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(const NcGePoint2d& pnt, double& param, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(double param, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual double paramOf(const NcGePoint2d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getTrimmedOffset(double distance, NcGeVoidPointerArray& offsetCurveList,
	                              NcGe::OffsetCrvExtType extensionType = NcGe::kFillet,
	                              const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isClosed(const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isPlanar(NcGePlane& plane, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isLinear(NcGeLine2d& line, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isCoplanarWith(const NcGeCurve2d& curve, NcGePlane& plane, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isPeriodic(double& period) const;

	virtual double length(double fromParam, double toParam, double tol = NcGeContext::gTol.equalPoint()) const;

	virtual double paramAtLength(double datumParam, double length, NRX::Boolean posParamDir = true,
	                             double tol = NcGeContext::gTol.equalPoint()) const;

	virtual NRX::Boolean area(double startParam, double endParam, double& value, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isDegenerate(NcGe::EntityId& degenerateType, const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isDegenerate(NcGeEntity2d*& pConvertedEntity,
                              const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getSplitCurves(double param, NcGeCurve2d*& piece1, NcGeCurve2d*& piece2) const;

	virtual NRX::Boolean explode(McGePVoidArray& explodedCurves, NcGeIntArray& newExplodedCurvesDelFlags,
	                             const NcGeInterval* intrvl = NULL) const;
	virtual NRX::Boolean explode(NcGeVoidPointerArray& explodedCurves, NcGeIntArray& newExplodedCurve,
                                 const NcGeInterval* intrvl = NULL ) const;
	virtual void getLocalClosestPoints(const NcGePoint2d& point, NcGePointOnCurve2d& approxPnt,
	                                   const NcGeInterval* nbhd = 0, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getLocalClosestPoints(const NcGeCurve2d& otherCurve, NcGePointOnCurve2d& approxPntOnThisCrv,
	                                   NcGePointOnCurve2d& approxPntOnOtherCrv, const NcGeInterval* nbhd1 = 0,
	                                   const NcGeInterval* nbhd2 = 0, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean hasStartPoint(NcGePoint2d& startPnt) const;

	virtual NRX::Boolean hasEndPoint(NcGePoint2d& endPnt) const;

	virtual NcGePoint2d evalPoint(double param) const;
	virtual NcGePoint2d evalPoint(double param, int numDeriv, NcGeVector2dArray& derivArray) const;

	virtual void getSamplePoints(double fromParam, double toParam, double approxEps, NcGePoint2dArray& pointArray,
	                             NcGeDoubleArray& paramArray) const;
	virtual void getSamplePoints(int numSample, McGePoint2dArray& pointArray) const;
	virtual void getSamplePoints(int numSample, NcGePoint2dArray& pointArray) const;

	virtual NcGeCurve2d& operator=(const NcGeCurve2d& curve);

public:
	McGeCurve3d* native() const;

	static NcGeCurve2d* NewNcGeCurve(McGeEntity3d *pNative, bool bAssert=false);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeLinearEnt2d
class NRXDBGATE_EXPORT NcGeLinearEnt2d : public NcGeCurve2d
{
protected:
	NcGeLinearEnt2d() {}

public:
	NcGeLinearEnt2d(McGeLinearEnt3d* _object);

public:
	virtual NRX::Boolean intersectWith(const NcGeLinearEnt2d& line, NcGePoint2d& intPt,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean intersectWith(const NcGePlanarEnt& plane, NcGePoint2d& intPnt,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean projIntersectWith(const NcGeLinearEnt2d& line, const NcGeVector2d& projDir,  NcGePoint2d& pntOnThisLine,
	                                       NcGePoint2d& pntOnOtherLine, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean overlap(const NcGeLinearEnt2d& line, NcGeLinearEnt2d*& overlap,
	                             const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isOn(const NcGePoint2d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(const NcGePoint2d& pnt, double& param, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(double param, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(const NcGePlane& plane, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isParallelTo(const NcGeLinearEnt2d& line, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isParallelTo(const NcGePlanarEnt& plane, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isPerpendicularTo(const NcGeLinearEnt2d& line, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isPerpendicularTo(const NcGePlanarEnt& plane, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isColinearTo(const NcGeLinearEnt2d& line, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getPerpPlane(const NcGePoint2d& pnt, NcGePlane& plane) const;

	void getPerpLine(const NcGePoint2d& pnt, NcGeLine2d& perpLine) const;

	virtual NcGePoint2d pointOnLine() const;
	virtual NcGeVector2d direction() const;
	virtual void getLine(NcGeLine2d& line) const;

	virtual NcGeLinearEnt2d& operator =(const NcGeLinearEnt2d& line);

public:
	McGeLinearEnt3d* native() const
	{
		return (McGeLinearEnt3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeLineSeg2d
class NRXDBGATE_EXPORT NcGeLineSeg2d : public NcGeLinearEnt2d
{
public:
	NcGeLineSeg2d();
	NcGeLineSeg2d(McGeLineSeg3d* _object);
	NcGeLineSeg2d(const NcGeLineSeg2d& line);
	NcGeLineSeg2d(const NcGePoint2d& pnt, const NcGeVector2d& vec);
	NcGeLineSeg2d(const NcGePoint2d& pnt1, const NcGePoint2d& pnt2);

public:
	virtual NcGeEntity2d* copy() const;

	virtual void getBisector(NcGePlane& plane) const;
	void getBisector(NcGeLine2d& line) const;

	virtual NcGePoint2d baryComb(double blendCoeff) const;

	virtual NcGePoint2d startPoint() const;
	virtual NcGePoint2d midPoint() const;
	virtual NcGePoint2d endPoint() const;

	virtual double length() const;
	virtual double length(double fromParam, double toParam, double tol = NcGeContext::gTol.equalPoint()) const;

	virtual NcGeLineSeg2d& set(const NcGePoint2d& pnt, const NcGeVector2d& vec);
	virtual NcGeLineSeg2d& set(const NcGePoint2d& pnt1, const NcGePoint2d& pnt2);
	virtual NcGeLineSeg2d& set(const NcGeCurve2d& curve1, const NcGeCurve2d& curve2, double& param1, double& param2,
	                           bool& success);
	virtual NcGeLineSeg2d& set(const NcGeCurve2d& curve, const NcGePoint2d& point, double& param, bool& success);

	virtual void getTrimmedOffset(double distance, NcGeVoidPointerArray& offsetCurveList,
	                              NcGe::OffsetCrvExtType extensionType = NcGe::kFillet,
	                              const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGeLineSeg2d& operator =(const NcGeLineSeg2d& line);

public:
	McGeLineSeg3d* native() const
	{
		return (McGeLineSeg3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeLine2d
class NRXDBGATE_EXPORT NcGeLine2d : public NcGeLinearEnt2d
{
public:
	NcGeLine2d();
	NcGeLine2d(McGeLine3d* _object);
	NcGeLine2d(const NcGeLine2d& line);
	NcGeLine2d(const NcGePoint2d& pnt, const NcGeVector2d& vec);
	NcGeLine2d(const NcGePoint2d& pnt1, const NcGePoint2d& pnt2);

public:
	virtual NcGeEntity2d* copy() const;

	virtual NcGeLine2d& set(const NcGePoint2d& pnt, const NcGeVector2d& vec);
	virtual NcGeLine2d& set(const NcGePoint2d& pnt1, const NcGePoint2d& pnt2);

	virtual NcGeLine2d& operator = (const NcGeLine2d& line);

	//	operator const McGeLine2d&() { return (const McGeLine2d&)(*m_pImpl); }

public:
	McGeLine3d* native() const
	{
		return (McGeLine3d*)m_pImpl;
	}

public:
	static const NcGeLine2d kXAxis;
	static const NcGeLine2d kYAxis;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeCircArc2d
class NRXDBGATE_EXPORT NcGeCircArc2d : public NcGeCurve2d
{
public:
	NcGeCircArc2d();
	NcGeCircArc2d(McGeCircArc3d* _object);
	NcGeCircArc2d(const NcGeCircArc2d& arc);
	NcGeCircArc2d(const NcGePoint2d& cent, double radius);
	NcGeCircArc2d(const NcGePoint2d& cent, double radius, double startAngle, double endAngle,
	              const NcGeVector2d& refVec = NcGeVector2d::kXAxis,
	              NRX::Boolean isClockWise = NRX::kFalse);
	NcGeCircArc2d(const NcGePoint2d& startPoint, const NcGePoint2d& pnt, const NcGePoint2d& endPoint);
	NcGeCircArc2d(const NcGePoint2d& startPoint, const NcGePoint2d& endPoint, double bulge,
	              NRX::Boolean bulgeFlag = NRX::kTrue);

public:
	virtual NcGeEntity2d* copy() const;

	NcGeCircArc2d& rotateBy(double angle, const NcGePoint2d& wrtPoint = NcGePoint2d::kOrigin);

	NRX::Boolean intersectWith(const NcGeLinearEnt2d& line, int& intn, NcGePoint2d& p1, NcGePoint2d& p2,
	                           const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean intersectWith(const NcGeCircArc2d& arc, int& intn, NcGePoint2d& p1, NcGePoint2d& p2,
	                           const NcGeTol& tol = NcGeContext::gTol) const;

	NRX::Boolean tangent(const NcGePoint2d& pnt, NcGeLine2d& line, const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean tangent(const NcGePoint2d& pnt, NcGeLine2d& line, const NcGeTol& tol, McGeError& error) const;

	NRX::Boolean isInside(const NcGePoint2d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;

	NcGePoint2d center() const;
	NcGeVector2d refVec() const;
	double radius() const;
	double startAng() const;
	double endAng() const;
	NRX::Boolean isClockWise() const;
	NcGePoint2d startPoint() const;
	NcGePoint2d endPoint() const;

	NcGeCircArc2d& setCenter(const NcGePoint2d& pt);
	NcGeCircArc2d& setAxes(const NcGeVector2d& normal, const NcGeVector2d& refVec);
	NcGeCircArc2d& setRadius(double param);
	NcGeCircArc2d& setAngles(double startAngle, double endAngle);

	NcGeCircArc2d& setToComplement();
	NcGeCircArc2d& set(const NcGePoint2d& cent, double radius);
	NcGeCircArc2d& set(const NcGePoint2d& cent, double radius, double ang1, double ang2,
	                   const NcGeVector2d& refVec = NcGeVector2d::kXAxis,
	                   NRX::Boolean isClockWise = NRX::kFalse);

	NcGeCircArc2d& set(const NcGePoint2d& startPoint, const NcGePoint2d& pnt, const NcGePoint2d& endPoint);
	NcGeCircArc2d& set(const NcGePoint2d& startPoint, const NcGePoint2d& pnt, const NcGePoint2d& endPoint,
	                   NcGeError& error);
	NcGeCircArc2d& set(const NcGePoint2d& startPoint, const NcGePoint2d& endPoint, double bulge,
	                   NRX::Boolean bulgeFlag = NRX::kTrue);
	NcGeCircArc2d& set(const NcGeCurve2d& curve1, const NcGeCurve2d& curve2, double radius, double& param1,
	                   double& param2, bool& success);
	NcGeCircArc2d& set(const NcGeCurve2d& curve1, const NcGeCurve2d& curve2, const NcGeCurve2d& curve3, double& param1,
	                   double& param2, double& param3, bool& success);
	NcGeCircArc2d& setRefVec (const NcGeVector2d& vec);

	// Assignment operator.
	NcGeCircArc2d& operator = (const NcGeCircArc2d& arc);

public:
	McGeCircArc3d* native() const
	{
		return (McGeCircArc3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeSplineEnt2d
class NRXDBGATE_EXPORT NcGeSplineEnt2d : public NcGeCurve2d
{
protected:
	NcGeSplineEnt2d() {}

public:
	NcGeSplineEnt2d(McGeSplineEnt3d* _object) : NcGeCurve2d(_object) {}

	virtual int degree() const;
	virtual int order() const;
	virtual int numKnots() const;
	virtual int numControlPoints() const;
	virtual int continuityAtKnot(int idx, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isRational() const;
	virtual McGeKnotVector knots() const;
	//virtual const NcGeKnotVector& knots() const;

	virtual double startParam() const;
	virtual double endParam() const;
	virtual NcGePoint2d startPoint() const;
	virtual NcGePoint2d endPoint() const;

	virtual NRX::Boolean hasFitData() const;

	virtual double knotAt(int idx) const;
	virtual NcGeSplineEnt2d& setKnotAt(int idx, double val);
	virtual NcGePoint2d controlPointAt(int idx) const;
	virtual NcGeSplineEnt2d& setControlPointAt(int idx, const NcGePoint2d& pnt);

	NcGeSplineEnt2d& operator = (const NcGeSplineEnt2d& spline);

public:
	McGeSplineEnt3d* native() const
	{
		return (McGeSplineEnt3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeKnotVector
class NRXDBGATE_EXPORT NcGeKnotVector
{
public:
	NcGeKnotVector(McGeKnotVector* _object)
	{
		m_pImpl = _object;
	}
	NcGeKnotVector(double eps = 1.e-9)
	{
		m_pImpl = new McGeKnotVector(eps);
	}
	NcGeKnotVector(int size, int growSize, double eps = 1.e-9)
	{
		m_pImpl = new McGeKnotVector(size, growSize, eps);
	}
	NcGeKnotVector(int size, const double arr[], double eps = 1.e-9)
	{
		m_pImpl = new McGeKnotVector(size, arr, eps);
	}

	NcGeKnotVector(int plusMult, const NcGeKnotVector& src)
	{
		m_pImpl = new McGeKnotVector(plusMult, *src.native());
	}
	NcGeKnotVector(const NcGeKnotVector& src)
	{
		m_pImpl = new McGeKnotVector(*src.native());
	}
	NcGeKnotVector(const McGeKnotVector& src)
	{
		m_pImpl = new McGeKnotVector(src);
	}
	NcGeKnotVector(const NcGeDoubleArray& src, double eps = 1.e-9)
	{
		McGeDoubleArray mcArr;
		convertArray(src, mcArr);
		m_pImpl = new McGeKnotVector(mcArr, eps);
	}

	~NcGeKnotVector()
	{
		delete m_pImpl;
	}

public:
	NcGeKnotVector& operator=(const NcGeKnotVector& src);
	NcGeKnotVector& operator=(const NcGeDoubleArray& src);

	double& operator[](int index);
	const double operator[](int index) const;

	NRX::Boolean isEqualTo(const NcGeKnotVector& other) const;

	double startParam() const;
	double endParam() const;
	int multiplicityAt(int i) const;
	int numIntervals() const;

	int getInterval(int ord, double par, NcGeInterval& interval) const;
	void getDistinctKnots(NcGeDoubleArray& knots) const;
	NRX::Boolean contains(double param) const;
	NRX::Boolean isOn(double knot) const;

	NcGeKnotVector& reverse();
	NcGeKnotVector& removeAt(int index);
	NcGeKnotVector& removeSubVector(int startIndex, int endIndex);
	NcGeKnotVector& insertAt(int indx, double u, int multiplicity);
	NcGeKnotVector& insert(double u);
	int append(double val);
	NcGeKnotVector& append(NcGeKnotVector& tail, double knotRatio);
	NcGeKnotVector& setRange(double lower, double upper);
	double tolerance() const;
	NcGeKnotVector& setTolerance(double tol);

	int split(double par, NcGeKnotVector* pKnot1, int multLast, NcGeKnotVector* pKnot2, int multFirst) const;
	int length() const;
	NRX::Boolean isEmpty() const;
	int logicalLength() const;
	NcGeKnotVector& setLogicalLength(int length);
	int physicalLength() const;
	NcGeKnotVector& setPhysicalLength(int length);

	int growLength() const;
	NcGeKnotVector& setGrowLength(int length);

	const double* asArrayPtr() const;
	double* asArrayPtr();

	NcGeKnotVector& set(int size, const double arr[], double eps = 1.e-9);

public:
	McGeKnotVector* native() const
	{
		return (McGeKnotVector*)m_pImpl;
	}

protected:
	McGeKnotVector* m_pImpl;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGePolyline2d
class NRXDBGATE_EXPORT NcGePolyline2d : public NcGeSplineEnt2d
{
public:
	NcGePolyline2d();
	NcGePolyline2d(McGePolyline3d* _object);
	NcGePolyline2d(const NcGePolyline2d& src);
	NcGePolyline2d(const NcGePoint2dArray& points);
	NcGePolyline2d(const NcGeCurve2d& crv, double apprEps);
	NcGePolyline2d(const NcGeKnotVector& knots, const NcGePoint2dArray& points);

public:
	virtual NcGeEntity2d* copy() const;

	int numFitPoints() const;
	NcGePoint2d fitPointAt(int fitPointIndex) const;
	double paramOf(const NcGePoint2d& point, const NcGeTol& tol = NcGeContext::gTol) const;
	void getClosestPointTo(const NcGePoint2d& pnt, NcGePointOnCurve2d& pntOnCrv,
	                       const NcGeTol& tol = NcGeContext::gTol) const;
	double length(double fromParam, double toParam, double tol = NcGeContext::gTol.equalPoint()) const;
	NcGePoint2d startPoint() const;
	NcGePoint2d endPoint() const;
	NRX::Boolean hasFitData() const;
	int numControlPoints() const;
	NcGePolyline2d& setFitPointAt(int index, const NcGePoint2d& point);
	//NcGeSplineEnt2d& setFitPointAt(int index, const NcGePoint2d& point);
	NcGePolyline2d& operator = (const NcGePolyline2d& src);

public:
	McGePolyline3d* native() const
	{
		return (McGePolyline3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeClipBoundary2d
class OdGeClipBoundary2d;
class NRXDBGATE_EXPORT NcGeClipBoundary2d
{
public:
	NcGeClipBoundary2d();
	NcGeClipBoundary2d(const NcGePoint2d& cornerA, const NcGePoint2d& cornerB);
	NcGeClipBoundary2d(const NcGePoint2dArray& clipBoundary);
	NcGeClipBoundary2d(const NcGeClipBoundary2d& src);
	~NcGeClipBoundary2d();

public:
	NcGe::ClipError set(const NcGePoint2d& cornerA, const NcGePoint2d& cornerB);
	NcGe::ClipError set(const NcGePoint2dArray& clipBoundary);

	NcGe::ClipError clipPolygon(const NcGePoint2dArray& rawVertices, NcGePoint2dArray& clippedVertices,
	                            NcGe::ClipCondition& condition, NcGeIntArray* label = 0) const;
	NcGe::ClipError clipPolyline(const NcGePoint2dArray& rawVertices, NcGePoint2dArray& clippedVertices,
	                             NcGe::ClipCondition& condition, NcGeIntArray* label = 0) const;

	NcGeClipBoundary2d& operator=(const NcGeClipBoundary2d& src);

public:
	OdGeClipBoundary2d* native() const;

protected:
	OdGeClipBoundary2d* m_pNative;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeRay2d
class NRXDBGATE_EXPORT NcGeRay2d : public NcGeLinearEnt2d
{
public:
	NcGeRay2d()
	{
		m_pImpl = new McGeRay3d;
	}
	NcGeRay2d(const NcGeRay2d& line)
	{
		m_pImpl   = new McGeRay3d(*line.native());
		m_startPt = line.m_startPt;
		m_dir     = line.m_dir;
	}
	NcGeRay2d(const NcGePoint2d& pnt, const NcGeVector2d& vec)
	{
		m_startPt = __asPnt3d(pnt);
		m_dir     = __asVec3d(vec);
		m_pImpl   = new McGeRay3d(m_startPt, m_dir);
	}
	NcGeRay2d(const NcGePoint2d& pnt1, const NcGePoint2d& pnt2)
	{
		m_startPt = __asPnt3d(pnt1);
		m_dir     = (__asPnt3d(pnt2) - m_startPt).normalize();
		m_pImpl   = new McGeRay3d(m_startPt, m_dir);
	}
	NcGeRay2d(McGeRay3d* _object)
	{
		m_pImpl = _object;
	}

public:
	NcGeRay2d& set(const NcGePoint2d& pnt, const NcGeVector2d& vec);
	NcGeRay2d& set(const NcGePoint2d& pnt1, const NcGePoint2d& pnt2);

	NRX::Boolean intersectWith(const NcGeLinearEnt2d& line, NcGePoint2d& intPnt,
	                           const NcGeTol& tol = NcGeContext::gTol) const;

	NcGePoint2d closestPointTo(const NcGeCurve2d& curve2d, NcGePoint2d& pntOnOtherCrv,
	                           const NcGeTol& tol = NcGeContext::gTol) const;
	NcGePoint2d closestPointTo(const NcGePoint2d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;

	double distanceTo(const NcGeCurve2d&, const NcGeTol& tol = NcGeContext::gTol) const;
	double distanceTo(const NcGePoint2d& pnt, const NcGeTol& = NcGeContext::gTol) const;

	NRX::Boolean isOn(const NcGePoint2d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isOn(const NcGePoint2d& pnt, double& param, const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isOn(double param, const NcGeTol& tol = NcGeContext::gTol) const;

	NcGeRay2d& operator=(const NcGeRay2d& line);

public:
	NcGePoint3d  m_startPt;
	NcGeVector3d m_dir;
	McGeRay3d* native() const
	{
		return (McGeRay3d*)m_pImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcGeMatrix3d
class NcGeMatrix3d : public McGeMatrix3d
{
public:
	NRXDBGATE_EXPORT NcGeMatrix3d();
	NRXDBGATE_EXPORT NcGeMatrix3d(const McGeMatrix3d& src);
	NRXDBGATE_EXPORT NcGeMatrix3d(const OdGeMatrix3d& od);

	NRXDBGATE_EXPORT static const NcGeMatrix3d kIdentity;

	NRXDBGATE_EXPORT NcGeMatrix3d&  setToIdentity();
	NRXDBGATE_EXPORT NcGeMatrix3d   operator *      (const NcGeMatrix3d& mat) const;
	NRXDBGATE_EXPORT NcGeMatrix3d&  operator *=     (const NcGeMatrix3d& mat);
	NRXDBGATE_EXPORT NcGeMatrix3d&  preMultBy       (const NcGeMatrix3d& leftSide);
	NRXDBGATE_EXPORT NcGeMatrix3d&  postMultBy      (const NcGeMatrix3d& rightSide);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToProduct    (const NcGeMatrix3d& mat1, const NcGeMatrix3d& mat2);
	NRXDBGATE_EXPORT NcGeMatrix3d&  invert          ();
	NRXDBGATE_EXPORT NcGeMatrix3d   inverse         () const;
	NRXDBGATE_EXPORT NcGeMatrix3d   inverse         (const NcGeTol& tol) const;
	NRXDBGATE_EXPORT NRX::Boolean isSingular      (const NcGeTol& tol = NcGeContext::gTol) const;
	NRXDBGATE_EXPORT NcGeMatrix3d&  transposeIt     ();
	NRXDBGATE_EXPORT NcGeMatrix3d   transpose       () const;
	NRXDBGATE_EXPORT bool operator ==     (const NcGeMatrix3d& mat) const;
	NRXDBGATE_EXPORT bool operator !=     (const NcGeMatrix3d& mat) const;
	NRXDBGATE_EXPORT bool isEqualTo       (const NcGeMatrix3d& mat, const NcGeTol& tol
	                                = NcGeContext::gTol) const;
	NRXDBGATE_EXPORT NRX::Boolean isUniScaledOrtho(const NcGeTol& tol = NcGeContext::gTol) const;
	NRXDBGATE_EXPORT NRX::Boolean isScaledOrtho   (const NcGeTol& tol = NcGeContext::gTol) const;
	NRXDBGATE_EXPORT double         det             () const;
	NRXDBGATE_EXPORT NcGeMatrix3d&  setTranslation  (const NcGeVector3d& vec);
	NRXDBGATE_EXPORT NcGeVector3d   translation     () const;
	NRXDBGATE_EXPORT NcGeMatrix3d&  setCoordSystem  (const NcGePoint3d& origin,
	                                const NcGeVector3d& xAxis,
	                                const NcGeVector3d& yAxis,
	                                const NcGeVector3d& zAxis);
	NRXDBGATE_EXPORT void           getCoordSystem  (NcGePoint3d& origin,
	                                NcGeVector3d& xAxis,
	                                NcGeVector3d& yAxis,
	                                NcGeVector3d& zAxis) const;
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToTranslation(const NcGeVector3d& vec);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToRotation   (double angle, const NcGeVector3d& axis,
	                                const NcGePoint3d& center
	                                = NcGePoint3d::kOrigin);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToScaling    (double scaleAll, const NcGePoint3d& center
	                                = NcGePoint3d::kOrigin);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToMirroring  (const NcGePlane& pln);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToMirroring  (const NcGePoint3d& pnt);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToMirroring  (const NcGeLine3d& line);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToProjection (const NcGePlane& projectionPlane,
	                                const NcGeVector3d& projectDir);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToAlignCoordSys(const NcGePoint3d& fromOrigin,
	                                  const NcGeVector3d& fromXAxis,
	                                  const NcGeVector3d& fromYAxis,
	                                  const NcGeVector3d& fromZAxis,
	                                  const NcGePoint3d& toOrigin,
	                                  const NcGeVector3d& toXAxis,
	                                  const NcGeVector3d& toYAxis,
	                                  const NcGeVector3d& toZAxis);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToWorldToPlane(const NcGeVector3d& normal);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToWorldToPlane(const NcGePlane& plane);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToPlaneToWorld(const NcGeVector3d& normal);
	NRXDBGATE_EXPORT NcGeMatrix3d&  setToPlaneToWorld(const NcGePlane& plane);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   translation     (const NcGeVector3d& vec);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   rotation        (double angle, const NcGeVector3d& axis,
	                                const NcGePoint3d& center
	                                = NcGePoint3d::kOrigin);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   scaling         (double scaleAll, const NcGePoint3d& center
	                                = NcGePoint3d::kOrigin);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   mirroring       (const NcGePlane& pln);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   mirroring       (const NcGePoint3d& pnt);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   mirroring       (const NcGeLine3d& line);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   projection      (const NcGePlane& projectionPlane,
	                                const NcGeVector3d& projectDir);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   alignCoordSys   (const NcGePoint3d&  fromOrigin,
	                                const NcGeVector3d& fromXAxis,
	                                const NcGeVector3d& fromYAxis,
	                                const NcGeVector3d& fromZAxis,
	                                const NcGePoint3d&  toOrigin,
	                                const NcGeVector3d& toXAxis,
	                                const NcGeVector3d& toYAxis,
	                                const NcGeVector3d& toZAxis);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   worldToPlane    (const NcGeVector3d& normal);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   worldToPlane    (const NcGePlane&);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   planeToWorld    (const NcGeVector3d& normal);
	NRXDBGATE_EXPORT static
	NcGeMatrix3d   planeToWorld    (const NcGePlane&);
	NRXDBGATE_EXPORT double scale(void) const;
	NRXDBGATE_EXPORT double          norm            () const;
	NRXDBGATE_EXPORT NcGeMatrix2d convertToLocal     (NcGeVector3d& normal, double& elev) const;
	NRXDBGATE_EXPORT double         operator ()     (unsigned int, unsigned int) const;
	NRXDBGATE_EXPORT double&        operator ()     (unsigned int, unsigned int);
	NRXDBGATE_EXPORT NRX::Boolean  inverse(NcGeMatrix3d& inv, double tol) const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeEntity3d
class NRXDBGATE_EXPORT NcGeEntity3d
{
protected:
	NcGeEntity3d();

public:
	NcGeEntity3d(McGeEntity3d* _object);
	virtual ~NcGeEntity3d();

public:
	virtual NRX::Boolean isKindOf(McGe::EntityId entType) const;
	virtual McGe::EntityId type() const;
	virtual NcGeEntity3d* copy() const;
	virtual NcGeEntity3d& operator=(const NcGeEntity3d& entity);
	virtual NRX::Boolean operator==(const NcGeEntity3d& entity) const;
	virtual NRX::Boolean operator!=(const NcGeEntity3d& entity) const;
	virtual NRX::Boolean isEqualTo(const NcGeEntity3d& ent, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NcGeEntity3d& transformBy(const NcGeMatrix3d& xfm);
	virtual NcGeEntity3d& translateBy(const NcGeVector3d& translateVec);
	virtual NcGeEntity3d& rotateBy(double angle, const NcGeVector3d& vec,
	                               const NcGePoint3d& wrtPoint = NcGePoint3d::kOrigin);
	virtual NcGeEntity3d& mirror(const NcGePlane& plane);
	virtual NcGeEntity3d& scaleBy(double scaleFactor, const NcGePoint3d& wrtPoint = NcGePoint3d::kOrigin);
	virtual NRX::Boolean isOn(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;

public:
	McGeEntity3d* native() const
	{
		return m_pImpl;
	}

	static NcGeEntity3d* NewNcGeEntity(McGeEntity3d *pNative, bool bAssert=false);

public:
	McGeEntity3d* m_pImpl;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeCurve3d
class NRXDBGATE_EXPORT NcGeCurve3d : public NcGeEntity3d
{
public:
	NcGeCurve3d(McGeCurve3d* _curve)
	{
		m_pImpl = _curve;
	}

public:
	virtual NcGeEntity3d* copy() const;

	virtual void getInterval(NcGeInterval& intrvl) const;
	virtual void getInterval(NcGeInterval& intrvl, NcGePoint3d& start, NcGePoint3d& end) const;
	virtual NcGeCurve3d& reverseParam();
	virtual NcGeCurve3d& setInterval();
	virtual NRX::Boolean setInterval(const NcGeInterval& intrvl);

	virtual double distanceTo(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual double distanceTo(const NcGeCurve3d& curve, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGePoint3d closestPointTo(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NcGePoint3d closestPointTo(const NcGeCurve3d& curve3d, NcGePoint3d& pntOnOtherCrv,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getClosestPointTo(const NcGePoint3d& pnt, NcGePointOnCurve3d& pntOnCrv,
	                               const NcGeTol& tol = NcGeContext::gTol) const;
	virtual void getClosestPointTo(const NcGeCurve3d& curve3d, NcGePointOnCurve3d& pntOnThisCrv,
	                               NcGePointOnCurve3d& pntOnOtherCrv, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGePoint3d projClosestPointTo(const NcGePoint3d& pnt, const NcGeVector3d& projectDirection,
	                                       const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NcGePoint3d projClosestPointTo(const NcGeCurve3d& curve3d, const NcGeVector3d& projectDirection,
	                                       NcGePoint3d& pntOnOtherCrv, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getProjClosestPointTo(const NcGePoint3d& pnt, const NcGeVector3d& projectDirection,
	                                   NcGePointOnCurve3d& pntOnCrv, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual void getProjClosestPointTo(const NcGeCurve3d& curve3d, const NcGeVector3d& projectDirection,
	                                   NcGePointOnCurve3d& pntOnThisCrv, NcGePointOnCurve3d& pntOnOtherCrv,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean getNormalPoint(const NcGePoint3d& pnt, NcGePointOnCurve3d& pntOnCrv,
	                                    const NcGeTol& tol = NcGeContext::gTol) const;

	NcGeBoundBlock3d boundBlock() const;
	NcGeBoundBlock3d boundBlock(const NcGeInterval& range) const;

	NcGeBoundBlock3d orthoBoundBlock() const;
	NcGeBoundBlock3d orthoBoundBlock(const NcGeInterval& range) const;

	virtual NcGeEntity3d* project(const NcGePlane& projectionPlane, const NcGeVector3d& projectDirection,
	                              const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGeEntity3d* orthoProject(const NcGePlane& projectionPlane, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isOn(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(const NcGePoint3d& pnt, double& param, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(double param, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual double paramOf(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getTrimmedOffset(double distance, const NcGeVector3d& planeNormal, McGePVoidArray& offsetCurveList,
	                              NcGe::OffsetCrvExtType extensionType = NcGe::kFillet,
	                              const NcGeTol& tol = NcGeContext::gTol) const;
	virtual void getTrimmedOffset(double distance, const NcGeVector3d& planeNormal,
	                              NcGeVoidPointerArray& offsetCurveList,
	                              NcGe::OffsetCrvExtType extensionType = NcGe::kFillet,
	                              const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isClosed(const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isPlanar(NcGePlane& plane, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isLinear(NcGeLine3d& line, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isCoplanarWith(const NcGeCurve3d& curve3d, NcGePlane& plane,
	                                    const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isPeriodic(double& period) const;

	virtual double length(double fromParam, double toParam, double tol = NcGeContext::gTol.equalPoint()) const;

	virtual double paramAtLength(double datumParam, double length, NRX::Boolean posParamDir = true,
	                             double tol = NcGeContext::gTol.equalPoint()) const;

	virtual NRX::Boolean area(double startParam, double endParam, double& value, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isDegenerate(NcGe::EntityId& degenerateType, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isDegenerate(NcGeEntity3d*& pConvertedEntity, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getSplitCurves(double param, NcGeCurve3d*& piece1, NcGeCurve3d*& piece2) const;

	virtual NRX::Boolean explode(McGePVoidArray& explodedCurves, NcGeIntArray& newExplodedCurvesDelFlags,
	                             const NcGeInterval* intrvl = NULL) const;
	virtual NRX::Boolean explode(NcGeVoidPointerArray& explodedCurves, NcGeIntArray& newExplodedCurves,
                                 const NcGeInterval* intrvl = NULL ) const;
	virtual void getLocalClosestPoints(const NcGePoint3d& point, NcGePointOnCurve3d& approxPnt,
	                                   const NcGeInterval* nbhd = 0, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual void getLocalClosestPoints(const NcGeCurve3d& otherCurve, NcGePointOnCurve3d& approxPntOnThisCrv,
	                                   NcGePointOnCurve3d& approxPntOnOtherCrv, const NcGeInterval* nbhd1 = 0,
	                                   const NcGeInterval* nbhd2 = 0, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean hasStartPoint(NcGePoint3d& startPnt) const;
	virtual NRX::Boolean hasEndPoint(NcGePoint3d& endPnt) const;

	virtual NcGePoint3d evalPoint(double param) const;
	virtual NcGePoint3d evalPoint(double param, int numDeriv, NcGeVector3dArray& derivArray) const;

	virtual void getSamplePoints(double fromParam, double toParam, double approxEps, NcGePoint3dArray& pointArray,
	                             NcGeDoubleArray& paramArray, bool forceResampling = false) const;
	virtual void getSamplePoints(int numSample, McGePoint3dArray& pointArray) const;
	virtual void getSamplePoints(int numSample, NcGePoint3dArray& pointArray) const;
	virtual void getSamplePoints(int numSample, NcGePoint3dArray& pointArray, NcGeDoubleArray& paramArray) const;

	virtual NcGeCurve3d& operator = (const NcGeCurve3d& curve);

public:
	McGeCurve3d* native() const
	{
		return (McGeCurve3d*)m_pImpl;
	}

	static NcGeCurve3d* NewNcGeCurve(McGeEntity3d *pNative, bool bAssert=false);

protected:
	NcGeCurve3d()
	{
		m_pImpl = NULL;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeLinearEnt3d
class NRXDBGATE_EXPORT NcGeLinearEnt3d : public NcGeCurve3d
{
public:
	NcGeLinearEnt3d(McGeLinearEnt3d* _object)
	{
		m_pImpl = _object;
	}

	virtual NcGeEntity3d* copy() const;

	virtual NRX::Boolean intersectWith(const NcGeLinearEnt3d& line, NcGePoint3d& intPt,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean intersectWith(const NcGePlanarEnt& plane, NcGePoint3d& intPnt,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean projIntersectWith(const NcGeLinearEnt3d& line, const NcGeVector3d& projDir,
	                                       NcGePoint3d& pntOnThisLine, NcGePoint3d& pntOnOtherLine,
	                                       const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean overlap(const NcGeLinearEnt3d& line, NcGeLinearEnt3d*& overlap,
	                             const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isOn(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(const NcGePoint3d& pnt, double& param, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(double param, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(const NcGePlane& plane, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isParallelTo(const NcGeLinearEnt3d& line, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isParallelTo(const NcGePlanarEnt& plane, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isPerpendicularTo(const NcGeLinearEnt3d& line, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isPerpendicularTo(const NcGePlanarEnt& plane, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isColinearTo(const NcGeLinearEnt3d& line, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getPerpPlane(const NcGePoint3d& pnt, NcGePlane& plane) const;

	virtual NcGePoint3d pointOnLine() const;
	virtual NcGeVector3d direction() const;
	virtual void getLine(NcGeLine3d& line) const;

	virtual NcGeLinearEnt3d& operator = (const NcGeLinearEnt3d& line);

public:
	McGeLinearEnt3d* native() const
	{
		return (McGeLinearEnt3d*)m_pImpl;
	}

protected:
	NcGeLinearEnt3d() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeLineSeg3d
class NRXDBGATE_EXPORT NcGeLineSeg3d : public NcGeLinearEnt3d
{
public:
	NcGeLineSeg3d()
	{
		m_pImpl = new McGeLineSeg3d;
	}
	NcGeLineSeg3d(McGeLineSeg3d* _object)
	{
		m_pImpl = _object;
	}
	NcGeLineSeg3d(const NcGeLineSeg3d& line)
	{
		m_pImpl = new McGeLineSeg3d(*line.native());
	}
	NcGeLineSeg3d(const NcGePoint3d& pnt, const NcGeVector3d& vec)
	{
		m_pImpl = new McGeLineSeg3d(pnt, vec);
	}
	NcGeLineSeg3d(const NcGePoint3d& pnt1, const NcGePoint3d& pnt2)
	{
		m_pImpl = new McGeLineSeg3d(pnt1, pnt2);
	}

public:
	virtual NcGeEntity3d* copy() const;

	virtual void getBisector(NcGePlane& plane) const;

	virtual NcGePoint3d baryComb(double blendCoeff) const;

	virtual NcGePoint3d startPoint() const;
	virtual NcGePoint3d midPoint() const;
	virtual NcGePoint3d endPoint() const;
	virtual double length() const;
	virtual double length(double fromParam, double toParam, double tol = NcGeContext::gTol.equalPoint()) const;

	virtual NcGeLineSeg3d& set(const NcGePoint3d& pnt, const NcGeVector3d& vec);
	virtual NcGeLineSeg3d& set(const NcGePoint3d& pnt1, const NcGePoint3d& pnt2);
	virtual NcGeLineSeg3d& set(const NcGeCurve3d& curve1, const NcGeCurve3d& curve2, double& param1, double& param2,
	                           bool& success);
	virtual NcGeLineSeg3d& set(const NcGeCurve3d& curve, const NcGePoint3d& point, double& param, bool& success);

	virtual NcGeLineSeg3d& operator =(const NcGeLineSeg3d& line);

public:
	McGeLineSeg3d* native() const
	{
		return (McGeLineSeg3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeLine3d
class NRXDBGATE_EXPORT NcGeLine3d : public NcGeLinearEnt3d
{
public:
	NcGeLine3d()
	{
		m_pImpl = new McGeLine3d;
	}
	NcGeLine3d(McGeLine3d* _object)
	{
		m_pImpl = _object;
	}
	NcGeLine3d(const NcGeLine3d& line)
	{
		m_pImpl = new McGeLine3d(*line.native());
	}
	NcGeLine3d(const NcGePoint3d& pnt, const NcGeVector3d& vec)
	{
		m_pImpl = new McGeLine3d(pnt, vec);
	}
	NcGeLine3d(const NcGePoint3d& pnt1, const NcGePoint3d& pnt2)
	{
		m_pImpl = new McGeLine3d(pnt1, pnt2);
	}

public:
	virtual NcGeEntity3d* copy() const;

	virtual NcGeLine3d& set(const NcGePoint3d& pnt, const NcGeVector3d& vec);
	virtual NcGeLine3d& set(const NcGePoint3d& pnt1, const NcGePoint3d& pnt2);

	virtual NcGeLine3d& operator = (const NcGeLine3d& line);

public:
	McGeLine3d* native() const
	{
		return (McGeLine3d*)m_pImpl;
	}

public:
	static const NcGeLine3d kXAxis;
	static const NcGeLine3d kYAxis;
	static const NcGeLine3d kZAxis;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeCircArc3d
class NRXDBGATE_EXPORT NcGeCircArc3d : public NcGeCurve3d
{
public:
	NcGeCircArc3d();
	NcGeCircArc3d(McGeCircArc3d* _object);
	NcGeCircArc3d(const NcGeCircArc3d& arc);
	NcGeCircArc3d(const NcGePoint3d& cent, const NcGeVector3d& nrm, double radius);
	NcGeCircArc3d(const NcGePoint3d& startPoint, const NcGePoint3d& pnt, const NcGePoint3d& endPoint);
	NcGeCircArc3d(const NcGePoint3d& cent, const NcGeVector3d& nrm, const NcGeVector3d& refVec, double radius,
	              double startAngle, double endAngle);

public:
	virtual NcGeEntity3d* copy() const;

	virtual NcGePoint3d closestPointToPlane(const NcGePlanarEnt& plane, NcGePoint3d& pointOnPlane,
	                                        const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean intersectWith(const NcGeLinearEnt3d& line, int& intn, NcGePoint3d& p1, NcGePoint3d& p2,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean intersectWith(const NcGeCircArc3d& arc, int& intn, NcGePoint3d& p1, NcGePoint3d& p2,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean intersectWith(const NcGePlanarEnt& plane, int& numOfIntersect, NcGePoint3d& p1, NcGePoint3d& p2,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean projIntersectWith(const NcGeLinearEnt3d& line, const NcGeVector3d& projDir, int& numInt,
	                                       NcGePoint3d& pntOnArc1, NcGePoint3d& pntOnArc2, NcGePoint3d& pntOnLine1,
	                                       NcGePoint3d& pntOnLine2, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean tangent(const NcGePoint3d& pnt, NcGeLine3d& line, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean tangent(const NcGePoint3d& pnt, NcGeLine3d& line, const NcGeTol& tol, McGeError& error) const;

	virtual void getPlane(NcGePlane& plane) const;

	virtual NRX::Boolean isInside(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGePoint3d center() const;
	virtual NcGeVector3d normal() const;
	virtual NcGeVector3d refVec() const;
	virtual double radius() const;
	virtual double startAng() const;
	virtual double endAng() const;
	virtual NcGePoint3d startPoint() const;
	virtual NcGePoint3d endPoint() const;

	virtual NcGeCircArc3d& setCenter(const NcGePoint3d& pt);
	virtual NcGeCircArc3d& setAxes(const NcGeVector3d& normal, const NcGeVector3d& refVec);
	virtual NcGeCircArc3d& setRadius(double param);
	virtual NcGeCircArc3d& setAngles(double startAngle, double endAngle);

	virtual NcGeCircArc3d& set(const NcGePoint3d& cent, const NcGeVector3d& nrm, double radius);
	virtual NcGeCircArc3d& set(const NcGePoint3d& cent, const NcGeVector3d& nrm, const NcGeVector3d& refVec,
	                           double radius, double startAngle, double endAngle);
	virtual NcGeCircArc3d& set(const NcGePoint3d& startPoint, const NcGePoint3d& pnt, const NcGePoint3d& endPoint);
	virtual NcGeCircArc3d& set(const NcGePoint3d& startPoint, const NcGePoint3d& pnt, const NcGePoint3d& endPoint,
	                           NcGeError& error);
	virtual NcGeCircArc3d& set(const NcGeCurve3d& curve1, const NcGeCurve3d& curve2, double radius, double& param1,
	                           double& param2, bool& success);
	virtual NcGeCircArc3d& set(const NcGeCurve3d& curve1, const NcGeCurve3d& curve2, const NcGeCurve3d& curve3,
	                           double& param1, double& param2, double& param3, bool& success);

	virtual void getTrimmedOffset(double distance, const NcGeVector3d& planeNormal,
	                              NcGeVoidPointerArray& offsetCurveList,
	                              NcGe::OffsetCrvExtType extensionType = NcGe::kFillet,
	                              const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGeCircArc3d& operator = (const NcGeCircArc3d& arc);

public:
	McGeCircArc3d* native() const
	{
		return (McGeCircArc3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeEllipArc3d
class NRXDBGATE_EXPORT NcGeEllipArc3d : public NcGeCurve3d
{
public:
	NcGeEllipArc3d()
	{
		m_pImpl = new McGeEllipArc3d;
	}
	NcGeEllipArc3d(McGeEllipArc3d* _object)
	{
		m_pImpl = _object;
	}
	NcGeEllipArc3d(const NcGeEllipArc3d& ell)
	{
		m_pImpl = new McGeEllipArc3d(*ell.native());
	}
	NcGeEllipArc3d(const NcGeCircArc3d& arc)
	{
		m_pImpl = new McGeEllipArc3d(*arc.native());
	}
	NcGeEllipArc3d(const NcGePoint3d& cent, const NcGeVector3d& majorAxis, const NcGeVector3d& minorAxis,
	               double majorRadius, double minorRadius)
	{
		m_pImpl = new McGeEllipArc3d(cent, majorAxis, minorAxis, majorRadius, minorRadius);
	}

	NcGeEllipArc3d(const NcGePoint3d& cent, const NcGeVector3d& majorAxis, const NcGeVector3d& minorAxis,
	               double majorRadius, double minorRadius, double ang1, double ang2)
	{
		m_pImpl = new McGeEllipArc3d(cent, majorAxis, minorAxis, majorRadius, minorRadius, ang1, ang2);
	}

public:
	virtual NcGeEntity3d* copy() const;

	virtual NcGePoint3d closestPointToPlane(const NcGePlanarEnt& plane, NcGePoint3d& pointOnPlane,
	                                        const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean intersectWith(const NcGeLinearEnt3d& line, int& intn, NcGePoint3d& p1, NcGePoint3d& p2,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean intersectWith(const NcGePlanarEnt& plane, int& numOfIntersect, NcGePoint3d& p1, NcGePoint3d& p2,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean projIntersectWith(const NcGeLinearEnt3d& line, const NcGeVector3d& projDir, int& numInt,
	                                       NcGePoint3d& pntOnEllipse1, NcGePoint3d& pntOnEllipse2, NcGePoint3d& pntOnLine1,
	                                       NcGePoint3d& pntOnLine2, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getPlane(McGePlane& plane) const;
	virtual void getPlane(NcGePlane& plane) const;

	virtual NRX::Boolean isCircular(const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isInside(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGePoint3d center() const;
	virtual double minorRadius() const;
	virtual double majorRadius() const;
	virtual NcGeVector3d minorAxis() const;
	virtual NcGeVector3d majorAxis() const;
	virtual NcGeVector3d normal() const;
	virtual double startAng() const;
	virtual double endAng() const;
	virtual NcGePoint3d startPoint() const;
	virtual NcGePoint3d endPoint() const;

	virtual NcGeEllipArc3d& setCenter(const NcGePoint3d& cent);
	virtual NcGeEllipArc3d& setMinorRadius(double rad);
	virtual NcGeEllipArc3d& setMajorRadius(double rad);
	virtual NcGeEllipArc3d& setAxes(const NcGeVector3d& majorAxis, const NcGeVector3d& minorAxis);
	virtual NcGeEllipArc3d& setAngles(double startAngle, double endAngle);

	virtual NcGeEllipArc3d& set(const NcGePoint3d& cent, const NcGeVector3d& majorAxis, const NcGeVector3d& minorAxis,
	                            double majorRadius, double minorRadius);
	virtual NcGeEllipArc3d& set(const NcGePoint3d& cent, const NcGeVector3d& majorAxis, const NcGeVector3d& minorAxis,
	                            double majorRadius, double minorRadius, double startAngle, double endAngle);
	virtual NcGeEllipArc3d& set(const NcGeCircArc3d& carc);
	virtual NcGeEllipArc3d& operator = (const NcGeEllipArc3d& ell);

public:
	McGeEllipArc3d* native() const
	{
		return (McGeEllipArc3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeSplineEnt3d
class NRXDBGATE_EXPORT NcGeSplineEnt3d : public NcGeCurve3d
{
protected:
	NcGeSplineEnt3d();

public:
	NcGeSplineEnt3d(McGeSplineEnt3d* _object);

public:
	virtual NcGeEntity3d* copy() const;
	virtual int degree() const;
	virtual int order() const;
	virtual int numKnots() const;
	virtual int numControlPoints() const;
	virtual int continuityAtKnot(int idx, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isRational() const;
	virtual NcGeKnotVector knots() const;
	virtual double startParam() const;
	virtual double endParam() const;
	virtual NcGePoint3d startPoint() const;
	virtual NcGePoint3d endPoint() const;
	virtual NRX::Boolean hasFitData() const;
	virtual double knotAt(int idx) const;
	virtual NcGeSplineEnt3d& setKnotAt(int idx, double val);
	virtual NcGePoint3d controlPointAt(int idx) const;
	virtual NcGeSplineEnt3d& setControlPointAt(int idx, const NcGePoint3d& pnt);

	NcGeSplineEnt3d& operator = (const NcGeSplineEnt3d& spline);

public:
	McGeSplineEnt3d* native() const
	{
		return (McGeSplineEnt3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeNurbCurve3d
class OdGeNurbCurve3d;
class NRXDBGATE_EXPORT NcGeNurbCurve3d : public NcGeSplineEnt3d
{
public:
	NcGeNurbCurve3d();
	NcGeNurbCurve3d(McGeNurbCurve3d* _object);
	NcGeNurbCurve3d(NcGeNurbCurve3d* _object);
	NcGeNurbCurve3d(const NcGeNurbCurve3d& src);
	NcGeNurbCurve3d(int degree, const NcGeKnotVector& knots, const McGePoint3dArray& cntrlPnts,
	                NRX::Boolean isPeriodic = false);
	NcGeNurbCurve3d(int degree, const NcGeKnotVector& knots, const NcGePoint3dArray& cntrlPnts,
	                NRX::Boolean isPeriodic = false);
	NcGeNurbCurve3d(int degree, const NcGeKnotVector& knots, const McGePoint3dArray& cntrlPnts,
	                const McGeDoubleArray& weights, NRX::Boolean isPeriodic = false);
	NcGeNurbCurve3d(int degree, const NcGeKnotVector& knots, const NcGePoint3dArray& cntrlPnts,
	                const NcGeDoubleArray& weights, NRX::Boolean isPeriodic = false);
	NcGeNurbCurve3d(int degree, const McGePolyline3d& fitPolyline, NRX::Boolean isPeriodic = false);
	NcGeNurbCurve3d(int degree, const NcGePolyline3d& fitPolyline, NRX::Boolean isPeriodic = false);
	NcGeNurbCurve3d(const McGePoint3dArray& fitPoints, const NcGeVector3d& startTangent,
	                const NcGeVector3d& endTangent, NRX::Boolean startTangentDefined = true, NRX::Boolean endTangentDefined = true,
	                const NcGeTol& fitTolerance = NcGeContext::gTol);
	NcGeNurbCurve3d(const NcGePoint3dArray& fitPoints, const NcGeVector3d& startTangent,
	                const NcGeVector3d& endTangent, NRX::Boolean startTangentDefined = true, NRX::Boolean endTangentDefined = true,
	                const NcGeTol& fitTolerance = NcGeContext::gTol);
	NcGeNurbCurve3d(const NcGePoint3dArray& fitPoints, const NcGeTol& fitTolerance = NcGeContext::gTol);
	NcGeNurbCurve3d(const McGePoint3dArray& fitPoints, const McGeVector3dArray& fitTangents,
	                const NcGeTol& fitTolerance = NcGeContext::gTol, NRX::Boolean isPeriodic = false);
	NcGeNurbCurve3d(const NcGePoint3dArray& fitPoints, const NcGeVector3dArray& fitTangents,
	                const NcGeTol& fitTolerance = NcGeContext::gTol, NRX::Boolean isPeriodic = false);
	NcGeNurbCurve3d(const NcGeEllipArc3d& ellipse);
	NcGeNurbCurve3d(const NcGeLineSeg3d& linSeg);
	NcGeNurbCurve3d(const NcGeCurve3d& curve, 
                    double epsilon = NcGeContext::gTol.equalPoint());

public:
	virtual NcGeEntity3d* copy() const;

	virtual int numFitPoints() const;
	virtual NRX::Boolean getFitPointAt(int index, NcGePoint3d& point) const;
	virtual NRX::Boolean getFitTolerance(NcGeTol& fitTolerance) const;
	virtual NRX::Boolean getFitTangents(NcGeVector3d& startTangent, NcGeVector3d& endTangent) const;

	virtual NRX::Boolean getFitTangents(NcGeVector3d& startTangent, NcGeVector3d& endTangent, bool& startTangentDefined,
	                                    bool& endTangentDefined) const;

	virtual NRX::Boolean getFitData(NcGePoint3dArray& fitPoints, NcGeTol& fitTolerance, bool& tangentsExist,
	                                NcGeVector3d& startTangent, NcGeVector3d& endTangent) const;

	virtual void getDefinitionData(int& degree, bool& rational, bool& periodic, NcGeKnotVector& knots,
	                               McGePoint3dArray& controlPoints, McGeDoubleArray& weights) const;
	virtual void getDefinitionData(int& degree, bool& rational, bool& periodic, NcGeKnotVector& knots,
	                               NcGePoint3dArray& controlPoints, NcGeDoubleArray& weights) const;

	virtual int numWeights() const;
	virtual double weightAt(int idx) const;

	virtual NRX::Boolean evalMode() const;
	virtual NRX::Boolean getParamsOfC1Discontinuity(McGeDoubleArray& params, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean getParamsOfC1Discontinuity(NcGeDoubleArray& params, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean getParamsOfG1Discontinuity(McGeDoubleArray& params, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean getParamsOfG1Discontinuity(NcGeDoubleArray& params, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean setFitPointAt(int index, const NcGePoint3d& point);
	virtual NRX::Boolean addFitPointAt(int index, const NcGePoint3d& point);
	virtual NRX::Boolean deleteFitPointAt(int index);
	virtual NRX::Boolean setFitTolerance(const NcGeTol& fitTol = NcGeContext::gTol);
	virtual NRX::Boolean setFitTangents(const NcGeVector3d& startTangent, const NcGeVector3d& endTangent);

	virtual NRX::Boolean setFitTangents(const NcGeVector3d& startTangent, const NcGeVector3d& endTangent,
	                                    NRX::Boolean startTangentDefined, NRX::Boolean endTangentDefined) const;

	virtual NcGeNurbCurve3d& setFitData(const McGePoint3dArray& fitPoints, const NcGeVector3d& startTangent,
	                                    const NcGeVector3d& endTangent, const NcGeTol& fitTol = NcGeContext::gTol);
	virtual NcGeNurbCurve3d& setFitData(const NcGePoint3dArray& fitPoints, const NcGeVector3d& startTangent,
	                                    const NcGeVector3d& endTangent, const NcGeTol& fitTol = NcGeContext::gTol);
	virtual NcGeNurbCurve3d& setFitData(const NcGeKnotVector& fitKnots, const McGePoint3dArray& fitPoints,
	                                    const NcGeVector3d& startTangent, const NcGeVector3d& endTangent,
	                                    const NcGeTol& fitTol = NcGeContext::gTol, NRX::Boolean isPeriodic = false);
	virtual NcGeNurbCurve3d& setFitData(const NcGeKnotVector& fitKnots, const NcGePoint3dArray& fitPoints,
	                                    const NcGeVector3d& startTangent, const NcGeVector3d& endTangent,
	                                    const NcGeTol& fitTol = NcGeContext::gTol, NRX::Boolean isPeriodic = false);
	virtual NcGeNurbCurve3d& setFitData(int degree, const McGePoint3dArray& fitPoints,
	                                    const NcGeTol& fitTol = NcGeContext::gTol);
	virtual NcGeNurbCurve3d& setFitData(int degree, const NcGePoint3dArray& fitPoints,
	                                    const NcGeTol& fitTol = NcGeContext::gTol);

	virtual NRX::Boolean purgeFitData();
	virtual NcGeNurbCurve3d& addKnot(double newKnot);
	virtual NcGeNurbCurve3d& insertKnot(double newKnot);
	virtual NcGeSplineEnt3d& setWeightAt(int idx, double val);
	virtual NcGeNurbCurve3d& setEvalMode(NRX::Boolean evalMode = false);
	virtual NcGeNurbCurve3d& joinWith(const NcGeNurbCurve3d& curve);
	virtual NcGeNurbCurve3d& hardTrimByParams(double newStartParam, double newEndParam);
	virtual NcGeNurbCurve3d& makeRational(double weight = 1.0);
	virtual NcGeNurbCurve3d& makeClosed();
	virtual NcGeNurbCurve3d& makePeriodic();
	virtual NcGeNurbCurve3d& makeNonPeriodic();
	virtual NcGeNurbCurve3d& makeOpen();
	virtual NcGeNurbCurve3d& elevateDegree(int plusDegree);

	NRX::Boolean addControlPointAt(double newKnot, const NcGePoint3d& point, double weight = 1.0);
	NRX::Boolean buildFitData();
	NRX::Boolean deleteControlPointAt(int index);
	NRX::Boolean getFitKnotParameterization(KnotParameterization& knotParam) const;
	NRX::Boolean setFitKnotParameterization(KnotParameterization knotParam);

	virtual NcGeNurbCurve3d& operator = (const NcGeNurbCurve3d& spline);
	void set(const OdGeNurbCurve3d& odCurve);


public:
	McGeNurbCurve3d* native() const
	{
		return (McGeNurbCurve3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGePolyline3d
class NRXDBGATE_EXPORT NcGePolyline3d : public NcGeSplineEnt3d
{
public:
	NcGePolyline3d();
	NcGePolyline3d(McGePolyline3d* _object);
	NcGePolyline3d(const NcGePolyline3d& src);
	NcGePolyline3d(const McGePoint3dArray& points);
	NcGePolyline3d(const NcGePoint3dArray& points);
	NcGePolyline3d(const NcGeKnotVector& knots, const McGePoint3dArray& cntrlPnts);
	NcGePolyline3d(const NcGeKnotVector& knots, const NcGePoint3dArray& cntrlPnts);
	NcGePolyline3d(const NcGeCurve3d& crv, double apprEps);

public:
	virtual NcGeEntity3d* copy() const;

	virtual int numFitPoints() const;
	virtual NcGePoint3d fitPointAt(int idx) const;
	virtual NcGeSplineEnt3d& setFitPointAt(int idx, const NcGePoint3d& point);

	NcGePolyline3d& operator =(const NcGePolyline3d& pline);

public:
	McGePolyline3d* native() const
	{
		return (McGePolyline3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeCompositeCurve3d
class NRXDBGATE_EXPORT NcGeCompositeCurve3d : public NcGeCurve3d
{
public:
	NcGeCompositeCurve3d();
	NcGeCompositeCurve3d(McGeCompositeCurve3d* _object);
	NcGeCompositeCurve3d(const McGePVoidArray& curveList);
	NcGeCompositeCurve3d(const NcGeVoidPointerArray& curveList);
	NcGeCompositeCurve3d(const McGePVoidArray& curveList, const McGeIntArray& isOwnerOfCurves);
	NcGeCompositeCurve3d(const NcGeVoidPointerArray& curveList, const NcGeIntArray& isOwnerOfCurves);
	NcGeCompositeCurve3d(const NcGeCompositeCurve3d& compCurve);

public:
	virtual NcGeEntity3d* copy() const;

	virtual void getCurveList(McGePVoidArray& curveList) const;
	virtual void getCurveList(NcGeVoidPointerArray& curveList) const;
	virtual NcGeCompositeCurve3d& setCurveList(const McGePVoidArray& curveList);
	virtual NcGeCompositeCurve3d& setCurveList(const NcGeVoidPointerArray& curveList);
	virtual NcGeCompositeCurve3d& setCurveList(const McGePVoidArray& curveList, const McGeIntArray& isOwnerOfCurves);
	virtual NcGeCompositeCurve3d& setCurveList(const NcGeVoidPointerArray& curveList,
	                                           const NcGeIntArray& isOwnerOfCurves);

	virtual double globalToLocalParam(double param, int& segNum) const;
	virtual double localToGlobalParam(double param, int segNum) const;

	virtual NcGeCompositeCurve3d& operator = (const NcGeCompositeCurve3d& compCurve);

public:
	McGeCompositeCurve3d* native() const
	{
		return (McGeCompositeCurve3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeRay3d
class NRXDBGATE_EXPORT NcGeRay3d : public NcGeLinearEnt3d
{
public:
	NcGeRay3d();
	NcGeRay3d(McGeRay3d* _object);
	NcGeRay3d(const NcGePoint3d& start, const NcGePoint3d& end);
	NcGeRay3d(const NcGePoint3d& start, const NcGeVector3d& dir);
	NcGeRay3d(const NcGeRay3d& src);

public:
	NcGeRay3d& set(const NcGePoint3d& pnt1, const NcGePoint3d& pnt2);
	NcGeRay3d& set(const NcGePoint3d& pnt, const NcGeVector3d& vec);

	NRX::Boolean intersectWith(const NcGeLinearEnt3d& line, NcGePoint3d& intPt, const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean intersectWith(const NcGePlanarEnt& plane, NcGePoint3d& intPt, const NcGeTol& tol = NcGeContext::gTol) const;

	NRX::Boolean isOn(const McGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isOn(const McGePoint3d& pnt, double& param, const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isOn(double param, const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isOn(const McGePlane& plane, const NcGeTol& tol = NcGeContext::gTol) const;

	double distanceTo(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	double distanceTo(const NcGeCurve3d& curve, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGePoint3d closestPointTo(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NcGePoint3d closestPointTo(const NcGeCurve3d& curve3d, NcGePoint3d& pntOnOtherCrv,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;

	NRX::Boolean hasStartPoint(NcGePoint3d& startPnt) const;
	NRX::Boolean hasEndPoint(NcGePoint3d& endPnt) const;

	NcGeRay3d& operator = (const NcGeRay3d& src);

public:
	NcGePoint3d  m_startPt;
	NcGeVector3d m_dir;
	McGeRay3d* native() const
	{
		return (McGeRay3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeCompositeCurve2d
class NRXDBGATE_EXPORT NcGeCompositeCurve2d : public NcGeCurve2d
{
public:
	NcGeCompositeCurve2d();
	NcGeCompositeCurve2d(McGeCompositeCurve3d* _object);

	NcGeCompositeCurve2d(const NcGeVoidPointerArray& curveList);
	NcGeCompositeCurve2d(const NcGeVoidPointerArray& curveList, const NcGeIntArray& isOwnerOfCurves);
	NcGeCompositeCurve2d(const NcGeCompositeCurve2d& compCurve);

public:
	void getCurveList(NcGeVoidPointerArray& curveList) const;
	NcGeCompositeCurve2d& setCurveList(const NcGeVoidPointerArray& curveList);
	NcGeCompositeCurve2d& setCurveList(const NcGeVoidPointerArray& curveList, const NcGeIntArray& isOwnerOfCurves);

	double globalToLocalParam(double param, int& crvNum) const;
	double localToGlobalParam(double param, int crvNum) const;

	NcGeCompositeCurve2d& operator = (const NcGeCompositeCurve2d& compCurve);

public:
	McGeCompositeCurve3d* native() const
	{
		return (McGeCompositeCurve3d*)m_pImpl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGeCurveCurveInt2d
class NRXDBGATE_EXPORT NcGeCurveCurveInt2d : public NcGeEntity2d
{
public:
	NcGeCurveCurveInt2d ();
	NcGeCurveCurveInt2d (const NcGeCurve2d& curve1, const NcGeCurve2d& curve2,
	                     const NcGeTol& tol = NcGeContext::gTol );
	NcGeCurveCurveInt2d (const NcGeCurve2d& curve1, const NcGeCurve2d& curve2,
	                     const NcGeInterval& range1, const NcGeInterval& range2,
	                     const NcGeTol& tol = NcGeContext::gTol);
	NcGeCurveCurveInt2d (const NcGeCurveCurveInt2d& src);

public:
	const NcGeCurve2d  *curve1     () const;
	const NcGeCurve2d  *curve2     () const;
	void               getIntRanges(NcGeInterval& range1, NcGeInterval& range2) const;
	NcGeTol            tolerance   () const;

public:
	int          numIntPoints     () const;
	NcGePoint2d  intPoint         (int intNum) const;
	void         getIntParams     (int intNum, double& param1, double& param2) const;
	void         getPointOnCurve1 (int intNum, NcGePointOnCurve2d&) const;
	void         getPointOnCurve2 (int intNum, NcGePointOnCurve2d&) const;
	//void         getIntConfigs    (int intNum, OdGe::OdGeXConfig& config1wrt2, OdGe::OdGeXConfig& config2wrt1) const;
	void         getIntConfigs    (int intNum, NcGe::NcGeXConfig& config1wrt2, NcGe::NcGeXConfig& config2wrt1) const;
	NRX::Boolean isTangential     (int intNum) const;
	NRX::Boolean isTransversal    (int intNum) const;
	double       intPointTol      (int intNum) const;
	int          overlapCount     () const;
	NRX::Boolean overlapDirection () const;
	void         getOverlapRanges (int overlapNum, NcGeInterval& range1, NcGeInterval& range2) const;

	void         changeCurveOrder ();

	NcGeCurveCurveInt2d& orderWrt1  ();
	NcGeCurveCurveInt2d& orderWrt2  ();

	NcGeCurveCurveInt2d& set(const NcGeCurve2d& curve1, const NcGeCurve2d& curve2, const NcGeTol& tol = NcGeContext::gTol);
	NcGeCurveCurveInt2d& set(const NcGeCurve2d& curve1, const NcGeCurve2d& curve2, const NcGeInterval& range1,
	                         const NcGeInterval& range2,
	                         const NcGeTol& tol = NcGeContext::gTol);

	NcGeCurveCurveInt2d& operator = (const NcGeCurveCurveInt2d& src);

public:
	McGeCurveCurveInt3d* native() const
	{
		return (McGeCurveCurveInt3d*) m_pImpl;
	}

};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility functions
NRXDBGATE_EXPORT NcGePoint2d& asPnt2d(const double* point);
NRXDBGATE_EXPORT NcGeVector2d& asVec2d(const double* vector);
NRXDBGATE_EXPORT double* asDblArray(const NcGePoint2d& point);
NRXDBGATE_EXPORT double* asDblArray(const NcGeVector2d& vector);

NRXDBGATE_EXPORT NcGePoint3d& asPnt3d(const double* point);
NRXDBGATE_EXPORT NcGeVector3d& asVec3d(const double* vector);

NRXDBGATE_EXPORT double* asDblArray(const NcGePoint3d& point);
NRXDBGATE_EXPORT double* asDblArray(const NcGeVector3d& vector);

// AutoGen:

//////////////////////////////////////////////////////////////////////////
// NcGeAugPolyline3d
class NRXDBGATE_EXPORT
NcGeAugPolyline3d : public NcGePolyline3d {
public:
	NcGeAugPolyline3d();
	NcGeAugPolyline3d(const NcGeAugPolyline3d& apline);
	NcGeAugPolyline3d(const NcGeKnotVector& knots,
	                  const NcGePoint3dArray& cntrlPnts,
	                  const NcGeVector3dArray& vecBundle);
	NcGeAugPolyline3d(const NcGePoint3dArray& cntrlPnts,
	                  const NcGeVector3dArray& vecBundle);
	NcGeAugPolyline3d(const NcGeCurve3d& curve,
	                  double fromParam, double toParam,
	                  double apprEps);
	NcGeAugPolyline3d& operator = (const NcGeAugPolyline3d& apline);
	NcGePoint3d           getPoint(int idx) const;
	NcGeAugPolyline3d&    setPoint(int idx, NcGePoint3d pnt);
	void                  getPoints(NcGePoint3dArray& pnts) const;
	NcGeVector3d          getVector(int idx) const;
	NcGeAugPolyline3d&    setVector(int idx, NcGeVector3d pnt);
	void                  getD1Vectors(NcGeVector3dArray& tangents) const;
	NcGeVector3d          getD2Vector(int idx) const;
	NcGeAugPolyline3d&    setD2Vector(int idx, NcGeVector3d pnt);
	void                  getD2Vectors(NcGeVector3dArray& d2Vectors) const;
	double                approxTol      () const;
	NcGeAugPolyline3d&    setApproxTol   (double approxTol);
};

//////////////////////////////////////////////////////////////////////////
// NcGeSurface
class OdGeSurface;
class OdGeEntity3d;
class NRXDBGATE_EXPORT NcGeSurface : public NcGeEntity3d
{
public:
	virtual NcGePoint2d paramOf(const NcGePoint3d& pnt,
	                            const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(const NcGePoint3d& pnt,
	                          const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(const NcGePoint3d& pnt, NcGePoint2d& paramPoint,
	                          const NcGeTol& tol = NcGeContext::gTol ) const;
	virtual NcGePoint3d closestPointTo(const NcGePoint3d& pnt,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;
	virtual void getClosestPointTo(const NcGePoint3d& pnt, NcGePointOnSurface& result,
	                               const NcGeTol& tol = NcGeContext::gTol) const;
	virtual double distanceTo(const NcGePoint3d& pnt,
	                          const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isNormalReversed () const;
	virtual NcGeSurface& reverseNormal    ();
	virtual NcGeSurface& operator = (const NcGeSurface& otherSurface);
	virtual void getEnvelope (NcGeInterval& intrvlX, NcGeInterval& intrvlY) const;
	virtual NRX::Boolean isClosedInU (const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isClosedInV (const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NcGePoint3d evalPoint (const NcGePoint2d& param) const;
	virtual NcGePoint3d evalPoint (const NcGePoint2d& param, int derivOrd,
	                               NcGeVector3dArray& derivatives) const;
	virtual NcGePoint3d evalPoint(const NcGePoint2d& param, int derivOrd,
	                              NcGeVector3dArray& derivatives,
	                              NcGeVector3d& normal) const;
public:
	virtual NRX::Boolean isKindOf(McGe::EntityId entType) const;
	virtual McGe::EntityId type() const;
	virtual NcGeEntity3d* copy() const;
	virtual NcGeEntity3d& operator=(const NcGeEntity3d& entity);
	virtual NRX::Boolean operator==(const NcGeEntity3d& entity) const;
	virtual NRX::Boolean operator!=(const NcGeEntity3d& entity) const;
	virtual NRX::Boolean isEqualTo(const NcGeEntity3d& ent, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NcGeEntity3d& transformBy(const NcGeMatrix3d& xfm);
	virtual NcGeEntity3d& translateBy(const NcGeVector3d& translateVec);
	virtual NcGeEntity3d& rotateBy(double angle, const NcGeVector3d& vec,
	                               const NcGePoint3d& wrtPoint = NcGePoint3d::kOrigin);

	virtual NcGeEntity3d& mirror(const NcGePlane& plane);

	virtual NcGeEntity3d& scaleBy(double scaleFactor, const NcGePoint3d& wrtPoint = NcGePoint3d::kOrigin);
public:
	NcGeSurface(McGeSurface*);
	NcGeSurface(OdGeSurface*);
	virtual ~NcGeSurface();

protected:
	NcGeSurface ();
	NcGeSurface (const NcGeSurface&);

public:
	McGeSurface* native() const;
	OdGeSurface* nativeOd() const;

	static NcGeEntity3d* NewNcGeEntity(OdGeEntity3d *pNative, bool bAssert=false);

protected:
	OdGeSurface* m_pOdImpl;
};


//////////////////////////////////////////////////////////////////////////
// NcGePlanarEnt
class NRXDBGATE_EXPORT NcGePlanarEnt : public NcGeSurface
{
public:
	NRX::Boolean  intersectWith    (const NcGeLinearEnt3d& linEnt, NcGePoint3d& pnt,
	                                const NcGeTol& tol = NcGeContext::gTol) const;
	NcGePoint3d     closestPointToLinearEnt (const NcGeLinearEnt3d& line,
	                                         NcGePoint3d& pointOnLine,
	                                         const NcGeTol& tol
	                                         = NcGeContext::gTol) const;
	NcGePoint3d     closestPointToPlanarEnt (const NcGePlanarEnt& otherPln,
	                                         NcGePoint3d& pointOnOtherPln,
	                                         const NcGeTol& tol
	                                         = NcGeContext::gTol) const;
	NRX::Boolean isParallelTo      (const NcGeLinearEnt3d& linEnt,
	                                const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isParallelTo      (const NcGePlanarEnt& otherPlnEnt,
	                                const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isPerpendicularTo (const NcGeLinearEnt3d& linEnt,
	                                const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isPerpendicularTo (const NcGePlanarEnt& linEnt,
	                                const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isCoplanarTo      (const NcGePlanarEnt& otherPlnEnt,
	                                const NcGeTol& tol = NcGeContext::gTol) const;
	void              get            (NcGePoint3d&, NcGeVector3d& uVec,
	                                  NcGeVector3d& vVec) const;
	void              get            (NcGePoint3d&, NcGePoint3d& origin,
	                                  NcGePoint3d&) const;
	NcGePoint3d    pointOnPlane      () const;
	NcGeVector3d   normal            () const;
	void           getCoefficients(double& a, double& b, double& c, double& d) const;
	void           getCoordSystem(NcGePoint3d& origin, NcGeVector3d& axis1,
	                              NcGeVector3d& axis2) const;
	NcGePlanarEnt& operator =        (const NcGePlanarEnt& src);

protected:
	NcGePlanarEnt ();
	NcGePlanarEnt (const NcGePlanarEnt&);

public:
	McGePlanarEnt* native() const
	{
		return (McGePlanarEnt*)m_pImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcGeBoundedPlane
class NRXDBGATE_EXPORT
NcGeBoundedPlane : public NcGePlanarEnt {
public:
	NcGeBoundedPlane();
	NcGeBoundedPlane(const NcGeBoundedPlane& plane);
	NcGeBoundedPlane(const NcGePoint3d& origin, const NcGeVector3d& uVec,
	                 const NcGeVector3d& vVec);
	NcGeBoundedPlane(const NcGePoint3d& p1, const NcGePoint3d& origin,
	                 const NcGePoint3d& p2);
	NRX::Boolean    intersectWith (const NcGeLinearEnt3d& linEnt, NcGePoint3d& point,
	                               const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean    intersectWith (const NcGePlane& plane, NcGeLineSeg3d& results,
	                               const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean    intersectWith (const NcGeBoundedPlane& plane, NcGeLineSeg3d& result,
	                               const NcGeTol& tol = NcGeContext::gTol) const;
	NcGeBoundedPlane& set           (const NcGePoint3d& origin,
	                                 const NcGeVector3d& uVec,
	                                 const NcGeVector3d& vVec);
	NcGeBoundedPlane& set           (const NcGePoint3d& p1,
	                                 const NcGePoint3d& origin,
	                                 const NcGePoint3d& p2);
	NcGeBoundedPlane& operator =    (const NcGeBoundedPlane& bplane);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGePlane
class NRXDBGATE_EXPORT NcGePlane : public NcGePlanarEnt
{
public:
	NcGePlane();
	NcGePlane(const McGePlane& src);
	NcGePlane(const NcGePlane& src);
	NcGePlane(const NcGePoint3d& origin, const NcGeVector3d& normal);
	NcGePlane(const NcGePoint3d& pntU, const NcGePoint3d& or, const NcGePoint3d& pntV);
	NcGePlane(const NcGePoint3d& or, const NcGeVector3d& uAxis, const NcGeVector3d& vAxis);
	NcGePlane(double a, double b, double c, double d);

	static const NcGePlane kXYPlane; // XY *plane*.
	static const NcGePlane kYZPlane; // YZ *plane*.
	static const NcGePlane kZXPlane; // ZY *plane*.

	NRX::Boolean isBox () const;
	NcGeBoundBlock2d& operator = (const NcGeBoundBlock2d& block);
	NcGeBoundBlock2d& setToBox (NRX::Boolean);

public:
	double signedDistanceTo(const NcGePoint3d& pnt) const;

	NRX::Boolean intersectWith(const NcGeLinearEnt3d& linEnt, NcGePoint3d& resultPnt,
	                           const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean intersectWith(const NcGePlane& otherPln, NcGeLine3d& resultLine,
	                           const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean intersectWith(const NcGeBoundedPlane& bndPln, NcGeLineSeg3d &resultLineSeg,
		                       const NcGeTol &tol = NcGeContext::gTol) const;

	NcGePlane& set(const NcGePoint3d& pnt, const NcGeVector3d& normal);
	NcGePlane& set(const NcGePoint3d& pntU, const NcGePoint3d& or, const NcGePoint3d& pntV);
	NcGePlane& set(double a, double b, double c, double d);
	NcGePlane& set(const NcGePoint3d& or, const NcGeVector3d& uAxis, const NcGeVector3d& vAxis);
	NcGePlane& operator=(const NcGePlane& src);

public:
	McGePlane* native() const
	{
		return (McGePlane*)m_pImpl;
	}
};


//////////////////////////////////////////////////////////////////////////
// NcGeCurveBoundary
class NRXDBGATE_EXPORT
NcGeCurveBoundary {
public:
	NcGeCurveBoundary();
	NcGeCurveBoundary(int numberOfCurves, const NcGeEntity3d *const * crv3d,
	                  const NcGeCurve2d *const * crv2d,
	                  NRX::Boolean* orientation3d,
	                  NRX::Boolean* orientation2d,
	                  NRX::Boolean makeCopy = NRX::kTrue);
	NcGeCurveBoundary(const NcGeCurveBoundary&);
	~NcGeCurveBoundary();
	NcGeCurveBoundary& operator =   (const NcGeCurveBoundary& src);
	NRX::Boolean     isDegenerate () const;
	NRX::Boolean     isDegenerate (NcGePosition3d& degenPoint, NcGeCurve2d** paramCurve) const;
	int                numElements  () const;
	void               getContour   (int& n, NcGeEntity3d*** crv3d,
	                                 NcGeCurve2d*** paramGeometry,
	                                 NRX::Boolean** orientation3d,
	                                 NRX::Boolean** orientation2d) const;
	NcGeCurveBoundary& set (int numElements, const NcGeEntity3d *const * crv3d,
	                        const NcGeCurve2d *const * crv2d,
	                        NRX::Boolean* orientation3d,
	                        NRX::Boolean* orientation2d,
	                        NRX::Boolean makeCopy = NRX::kTrue);
	NRX::Boolean     isOwnerOfCurves() const;
	NcGeCurveBoundary& setToOwnCurves ();
protected:
	int                     mDelBnd;
};

//////////////////////////////////////////////////////////////////////////
// NcGeCurveCurveInt3d
class NRXDBGATE_EXPORT
NcGeCurveCurveInt3d : public NcGeEntity3d {
public:
	NcGeCurveCurveInt3d ();
	NcGeCurveCurveInt3d (const NcGeCurve3d& curve1, const NcGeCurve3d& curve2,
	                     const NcGeVector3d& planeNormal =
	                     NcGeVector3d::kIdentity,
	                     const NcGeTol& tol = NcGeContext::gTol );
	NcGeCurveCurveInt3d (const NcGeCurve3d& curve1, const NcGeCurve3d& curve2,
	                     const NcGeInterval& range1, const NcGeInterval& range2,
	                     const NcGeVector3d& planeNormal=NcGeVector3d::kIdentity,
	                     const NcGeTol& tol = NcGeContext::gTol);
	NcGeCurveCurveInt3d (const NcGeCurveCurveInt3d& src);
	const NcGeCurve3d  *curve1          () const;
	const NcGeCurve3d  *curve2          () const;
	void               getIntRanges     (NcGeInterval& range1,
	                                     NcGeInterval& range2) const;
	NcGeVector3d       planeNormal        () const;
	NcGeTol            tolerance        () const;
	int                numIntPoints     () const;
	NcGePoint3d        intPoint         (int intNum) const;
	void               getIntParams     (int intNum,
	                                     double& param1, double& param2) const;
	void               getPointOnCurve1 (int intNum, NcGePointOnCurve3d& pntOnCrv) const;
	void               getPointOnCurve2 (int intNum, NcGePointOnCurve3d& pntOnCrv) const;
	void               getIntConfigs    (int intNum, NcGe::NcGeXConfig& config1wrt2,
	                                     NcGe::NcGeXConfig& config2wrt1) const;
	NRX::Boolean     isTangential     (int intNum) const;
	NRX::Boolean     isTransversal    (int intNum) const;
	double             intPointTol      (int intNum) const;
	int                overlapCount     () const;
	NRX::Boolean       overlapDirection () const;
	void               getOverlapRanges (int overlapNum,
	                                     NcGeInterval& range1,
	                                     NcGeInterval& range2) const;
	void               changeCurveOrder ();
	NcGeCurveCurveInt3d& orderWrt1  ();
	NcGeCurveCurveInt3d& orderWrt2  ();
	NcGeCurveCurveInt3d& set        (const NcGeCurve3d& curve1,
	                                 const NcGeCurve3d& curve2,
	                                 const NcGeVector3d& planeNormal =
	                                 NcGeVector3d::kIdentity,
	                                 const NcGeTol& tol = NcGeContext::gTol);
	NcGeCurveCurveInt3d& set        (const NcGeCurve3d& curve1,
	                                 const NcGeCurve3d& curve2,
	                                 const NcGeInterval& range1,
	                                 const NcGeInterval& range2,
	                                 const NcGeVector3d& planeNormal =
	                                 NcGeVector3d::kIdentity,
	                                 const NcGeTol& tol = NcGeContext::gTol);
	NcGeCurveCurveInt3d& operator = (const NcGeCurveCurveInt3d& src);
};

//////////////////////////////////////////////////////////////////////////
// NcGeCone
class OdGeCone;
class NRXDBGATE_EXPORT
NcGeCone : public NcGeSurface {
public:
	NcGeCone();
	NcGeCone(double cosineAngle, double sineAngle,
	         const  NcGePoint3d& baseOrigin, double baseRadius,
	         const  NcGeVector3d& axisOfSymmetry);
	NcGeCone(double cosineAngle, double sineAngle,
	         const  NcGePoint3d& baseOrigin, double baseRadius,
	         const  NcGeVector3d& axisOfSymmetry,
	         const  NcGeVector3d& refAxis, const  NcGeInterval& height,
	         double startAngle, double endAngle);
	NcGeCone(const NcGeCone& cone);

	double           baseRadius        () const;
	NcGePoint3d      baseCenter        () const;
	void             getAngles         (double& start, double& end) const;
	double           halfAngle         () const;
	void             getHalfAngle      (double& cosineAngle, double& sineAngle)
	                                             const;
	void             getHeight         (NcGeInterval& range) const;
	double           heightAt          (double u) const;
	NcGeVector3d     axisOfSymmetry    () const;
	NcGeVector3d     refAxis           () const;
	NcGePoint3d      apex              () const;
	NRX::Boolean   isClosed          (const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean   isOuterNormal     () const;
	NcGeCone&        setBaseRadius     (double radius);
	NcGeCone&        setAngles         (double startAngle, double endAngle);
	NcGeCone&        setHeight         (const NcGeInterval& height);
	NcGeCone&        set               (double cosineAngle, double sineAngle,
	                                    const  NcGePoint3d& baseCenter,
	                                    double baseRadius,
	                                    const  NcGeVector3d& axisOfSymmetry);
	NcGeCone&        set               (double cosineAngle, double sineAngle,
	                                    const  NcGePoint3d& baseCenter,
	                                    double baseRadius,
	                                    const  NcGeVector3d& axisOfSymmetry,
	                                    const  NcGeVector3d& refAxis,
	                                    const  NcGeInterval& height,
	                                    double startAngle, double endAngle);
	NcGeCone&        operator =        (const NcGeCone& cone);
	NRX::Boolean   intersectWith     (const NcGeLinearEnt3d& linEnt, int& intn,
	                                  NcGePoint3d& p1, NcGePoint3d& p2,
	                                  const NcGeTol& tol = NcGeContext::gTol) const;
public:
	OdGeCone* native() const
	{
		return (OdGeCone*)m_pOdImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcGeCurveSurfInt
class NRXDBGATE_EXPORT
NcGeCurveSurfInt : public NcGeEntity3d {
public:
	NcGeCurveSurfInt ();
	NcGeCurveSurfInt (const NcGeCurve3d& crv, const NcGeSurface& srf,
	                  const NcGeTol& tol = NcGeContext::gTol );
	NcGeCurveSurfInt (const NcGeCurveSurfInt& src);
	const NcGeCurve3d  *curve           () const;
	const NcGeSurface  *surface         () const;
	NcGeTol            tolerance        () const;
	int  numIntPoints (NcGeIntersectError& err) const;
	NcGePoint3d  intPoint (int intNum, NcGeIntersectError& err) const;
	void               getIntParams (int intNum,
	                                 double& param1, NcGePoint2d& param2, NcGeIntersectError& err) const;
	void               getPointOnCurve (int intNum, NcGePointOnCurve3d&, NcGeIntersectError& err) const;
	void               getPointOnSurface (int intNum, NcGePointOnSurface&, NcGeIntersectError& err) const;
	void               getIntConfigs (int intNum, NcGe::csiConfig& lower,
	                                  NcGe::csiConfig& higher, NRX::Boolean& smallAngle, NcGeIntersectError& err) const;
	NcGeCurveSurfInt& set (const NcGeCurve3d& cvr,
	                       const NcGeSurface& srf,
	                       const NcGeTol& tol = NcGeContext::gTol);
	NcGeCurveSurfInt& operator = (const NcGeCurveSurfInt& crvInt);
};

//////////////////////////////////////////////////////////////////////////
// NcGeCubicSplineCurve2d
class NRXDBGATE_EXPORT
NcGeCubicSplineCurve2d : public NcGeSplineEnt2d {
public:
	NcGeCubicSplineCurve2d();
	NcGeCubicSplineCurve2d(const NcGeCubicSplineCurve2d& spline);
	NcGeCubicSplineCurve2d(const NcGePoint2dArray& fitPnts,
	                       const NcGeTol& tol = NcGeContext::gTol);
	NcGeCubicSplineCurve2d(const NcGePoint2dArray& fitPnts,
	                       const NcGeVector2d& startDeriv,
	                       const NcGeVector2d& endDeriv,
	                       const NcGeTol& tol = NcGeContext::gTol);
	NcGeCubicSplineCurve2d(const NcGeCurve2d& curve,
	                       double epsilon = NcGeContext::gTol.equalPoint());
	NcGeCubicSplineCurve2d(const NcGeKnotVector& knots,
                           const NcGePoint2dArray& fitPnts,
                           const NcGeVector2dArray& firstDerivs,
                           NRX::Boolean isPeriodic = NRX::kFalse );
    int                     numFitPoints   ()        const;
    NcGePoint2d             fitPointAt     (int idx) const;
    NcGeCubicSplineCurve2d& setFitPointAt  (int idx, const NcGePoint2d& point);
    NcGeVector2d            firstDerivAt   (int idx) const;
    NcGeCubicSplineCurve2d& setFirstDerivAt(int idx, const NcGeVector2d& deriv);
    NcGeCubicSplineCurve2d&  operator = (const NcGeCubicSplineCurve2d& spline);
};

//////////////////////////////////////////////////////////////////////////
// NcGeCubicSplineCurve3d
class NRXDBGATE_EXPORT
NcGeCubicSplineCurve3d : public NcGeSplineEnt3d {
public:
	NcGeCubicSplineCurve3d();
	NcGeCubicSplineCurve3d(const NcGeCubicSplineCurve3d& spline);
	NcGeCubicSplineCurve3d(const NcGePoint3dArray& fitPnts,
	                       const NcGeTol& tol = NcGeContext::gTol);
	NcGeCubicSplineCurve3d(const NcGePoint3dArray& fitPnts,
	                       const NcGeVector3d& startDeriv,
	                       const NcGeVector3d& endDeriv,
	                       const NcGeTol& tol = NcGeContext::gTol);
	NcGeCubicSplineCurve3d(const NcGeCurve3d& curve,
	                       double epsilon = NcGeContext::gTol.equalPoint());
	NcGeCubicSplineCurve3d(const NcGeKnotVector& knots,
	                       const NcGePoint3dArray& fitPnts,
	                       const NcGeVector3dArray& firstDerivs,
	                       NRX::Boolean isPeriodic = NRX::kFalse);
	~NcGeCubicSplineCurve3d();

	int                     numFitPoints   ()        const;
	NcGePoint3d             fitPointAt     (int idx) const;
	NcGeCubicSplineCurve3d& setFitPointAt  (int idx, const NcGePoint3d& point);
	NcGeVector3d            firstDerivAt   (int idx) const;
	NcGeCubicSplineCurve3d& setFirstDerivAt(int idx, const NcGeVector3d& deriv);
	NcGeCubicSplineCurve3d&  operator = (const NcGeCubicSplineCurve3d& spline);

// methods NcGeSplineEnt3d
public:
	virtual NcGeEntity3d* copy() const;
	virtual int degree() const;
	virtual int order() const;
	virtual int numKnots() const;
	virtual int numControlPoints() const;
	virtual int continuityAtKnot(int idx, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isRational() const;
	virtual NcGeKnotVector knots() const;
	virtual double startParam() const;
	virtual double endParam() const;
	virtual NcGePoint3d startPoint() const;
	virtual NcGePoint3d endPoint() const;
	virtual NRX::Boolean hasFitData() const;
	virtual double knotAt(int idx) const;
	virtual NcGeSplineEnt3d& setKnotAt(int idx, double val);
	virtual NcGePoint3d controlPointAt(int idx) const;
	virtual NcGeSplineEnt3d& setControlPointAt(int idx, const NcGePoint3d& pnt);

// methods NcGeCurve3d
public:
	virtual void getInterval(NcGeInterval& intrvl) const;
	virtual void getInterval(NcGeInterval& intrvl, NcGePoint3d& start, NcGePoint3d& end) const;
	virtual NcGeCurve3d& reverseParam();
	virtual NcGeCurve3d& setInterval();
	virtual NRX::Boolean setInterval(const NcGeInterval& intrvl);

	virtual double distanceTo(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual double distanceTo(const NcGeCurve3d& curve, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGePoint3d closestPointTo(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NcGePoint3d closestPointTo(const NcGeCurve3d& curve3d, NcGePoint3d& pntOnOtherCrv,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getClosestPointTo(const NcGePoint3d& pnt, NcGePointOnCurve3d& pntOnCrv,
	                               const NcGeTol& tol = NcGeContext::gTol) const;
	virtual void getClosestPointTo(const NcGeCurve3d& curve3d, NcGePointOnCurve3d& pntOnThisCrv,
	                               NcGePointOnCurve3d& pntOnOtherCrv, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGePoint3d projClosestPointTo(const NcGePoint3d& pnt, const NcGeVector3d& projectDirection,
	                                       const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NcGePoint3d projClosestPointTo(const NcGeCurve3d& curve3d, const NcGeVector3d& projectDirection,
	                                       NcGePoint3d& pntOnOtherCrv, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getProjClosestPointTo(const NcGePoint3d& pnt, const NcGeVector3d& projectDirection,
	                                   NcGePointOnCurve3d& pntOnCrv, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual void getProjClosestPointTo(const NcGeCurve3d& curve3d, const NcGeVector3d& projectDirection,
	                                   NcGePointOnCurve3d& pntOnThisCrv, NcGePointOnCurve3d& pntOnOtherCrv,
	                                   const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean getNormalPoint(const NcGePoint3d& pnt, NcGePointOnCurve3d& pntOnCrv,
	                                    const NcGeTol& tol = NcGeContext::gTol) const;

	NcGeBoundBlock3d boundBlock() const;
	NcGeBoundBlock3d boundBlock(const NcGeInterval& range) const;

	NcGeBoundBlock3d orthoBoundBlock() const;
	NcGeBoundBlock3d orthoBoundBlock(const NcGeInterval& range) const;

	virtual NcGeEntity3d* project(const NcGePlane& projectionPlane, const NcGeVector3d& projectDirection,
	                              const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NcGeEntity3d* orthoProject(const NcGePlane& projectionPlane, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isOn(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(const NcGePoint3d& pnt, double& param, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isOn(double param, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual double paramOf(const NcGePoint3d& pnt, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getTrimmedOffset(double distance, const NcGeVector3d& planeNormal, McGePVoidArray& offsetCurveList,
	                              NcGe::OffsetCrvExtType extensionType = NcGe::kFillet,
	                              const NcGeTol& tol = NcGeContext::gTol) const;
	virtual void getTrimmedOffset(double distance, const NcGeVector3d& planeNormal,
	                              NcGeVoidPointerArray& offsetCurveList,
	                              NcGe::OffsetCrvExtType extensionType = NcGe::kFillet,
	                              const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isClosed(const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isPlanar(NcGePlane& plane, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isLinear(NcGeLine3d& line, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isCoplanarWith(const NcGeCurve3d& curve3d, NcGePlane& plane,
	                                    const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isPeriodic(double& period) const;

	virtual double length(double fromParam, double toParam, double tol = NcGeContext::gTol.equalPoint()) const;

	virtual double paramAtLength(double datumParam, double length, NRX::Boolean posParamDir = true,
	                             double tol = NcGeContext::gTol.equalPoint()) const;

	virtual NRX::Boolean area(double startParam, double endParam, double& value, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean isDegenerate(NcGe::EntityId& degenerateType, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual NRX::Boolean isDegenerate(NcGeEntity3d*& pConvertedEntity, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual void getSplitCurves(double param, NcGeCurve3d*& piece1, NcGeCurve3d*& piece2) const;

	virtual NRX::Boolean explode(McGePVoidArray& explodedCurves, NcGeIntArray& newExplodedCurvesDelFlags,
	                             const NcGeInterval* intrvl = NULL) const;
	virtual NRX::Boolean explode(NcGeVoidPointerArray& explodedCurves, NcGeIntArray& newExplodedCurves,
                                 const NcGeInterval* intrvl = NULL ) const;
	virtual void getLocalClosestPoints(const NcGePoint3d& point, NcGePointOnCurve3d& approxPnt,
	                                   const NcGeInterval* nbhd = 0, const NcGeTol& tol = NcGeContext::gTol) const;
	virtual void getLocalClosestPoints(const NcGeCurve3d& otherCurve, NcGePointOnCurve3d& approxPntOnThisCrv,
	                                   NcGePointOnCurve3d& approxPntOnOtherCrv, const NcGeInterval* nbhd1 = 0,
	                                   const NcGeInterval* nbhd2 = 0, const NcGeTol& tol = NcGeContext::gTol) const;

	virtual NRX::Boolean hasStartPoint(NcGePoint3d& startPnt) const;
	virtual NRX::Boolean hasEndPoint(NcGePoint3d& endPnt) const;

	virtual NcGePoint3d evalPoint(double param) const;
	virtual NcGePoint3d evalPoint(double param, int numDeriv, NcGeVector3dArray& derivArray) const;

	virtual void getSamplePoints(double fromParam, double toParam, double approxEps, NcGePoint3dArray& pointArray,
	                             NcGeDoubleArray& paramArray, bool forceResampling = false) const;
	//virtual void getSamplePoints(int numSample, McGePoint3dArray& pointArray) const;
	virtual void getSamplePoints(int numSample, NcGePoint3dArray& pointArray) const;
	virtual void getSamplePoints(int numSample, NcGePoint3dArray& pointArray, NcGeDoubleArray& paramArray) const;

	virtual NcGeCurve3d& operator = (const NcGeCurve3d& curve);


private:
	OdGeCubicSplineCurve3d* m_pOdImpl;

public:
	OdGeCubicSplineCurve3d* native() const
	{
		return (OdGeCubicSplineCurve3d*)m_pOdImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcGeCylinder
class OdGeCylinder;
class NRXDBGATE_EXPORT NcGeCylinder : public NcGeSurface {
public:
	NcGeCylinder ();
	NcGeCylinder (double radius, const NcGePoint3d& origin,
	              const NcGeVector3d& axisOfSymmetry);
	NcGeCylinder (double radius, const NcGePoint3d& origin,
	              const NcGeVector3d& axisOfSymmetry,
	              const NcGeVector3d& refAxis,
	              const NcGeInterval& height,
	              double startAngle, double endAngle);
	NcGeCylinder (const NcGeCylinder&);

	double         radius        () const;
	NcGePoint3d    origin        () const;
	void           getAngles     (double& start, double& end) const;
	void           getHeight     (NcGeInterval& height) const;
	double         heightAt      (double u) const;
	NcGeVector3d   axisOfSymmetry() const;
	NcGeVector3d   refAxis       () const;
	NRX::Boolean isOuterNormal () const;
	NRX::Boolean isClosed      (const NcGeTol& tol = NcGeContext::gTol) const;
	NcGeCylinder&  setRadius     (double radius);
	NcGeCylinder&  setAngles     (double start, double end);
	NcGeCylinder&  setHeight     (const NcGeInterval& height);
	NcGeCylinder&  set           (double radius, const NcGePoint3d& origin,
	                              const NcGeVector3d& axisOfSym);
	NcGeCylinder&  set           (double radius, const NcGePoint3d& origin,
	                              const NcGeVector3d& axisOfSym,
	                              const NcGeVector3d& refAxis,
	                              const NcGeInterval& height,
	                              double startAngle, double endAngle);
	NcGeCylinder&  operator =    (const NcGeCylinder& cylinder);
	NRX::Boolean intersectWith (const NcGeLinearEnt3d& linEnt, int& intn,
	                            NcGePoint3d& p1, NcGePoint3d& p2,
	                            const NcGeTol& tol = NcGeContext::gTol) const;

public:
	OdGeCylinder* native() const
	{
		return (OdGeCylinder*)m_pOdImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcGeEllipArc2d
class NRXDBGATE_EXPORT NcGeEllipArc2d : public NcGeCurve2d {
public:
	NcGeEllipArc2d::NcGeEllipArc2d(McGeCurve3d* _object);
	NcGeEllipArc2d();
	NcGeEllipArc2d(const NcGeEllipArc2d& ell);
	NcGeEllipArc2d(const NcGeCircArc2d& arc);
	NcGeEllipArc2d(const NcGePoint2d& cent, const NcGeVector2d& majorAxis,
	               const NcGeVector2d& minorAxis, double majorRadius,
	               double minorRadius);
	NcGeEllipArc2d(const NcGePoint2d& cent, const NcGeVector2d& majorAxis,
	               const NcGeVector2d& minorAxis, double majorRadius,
	               double minorRadius, double startAngle, double endAngle);
	NRX::Boolean intersectWith (const NcGeLinearEnt2d& line, int& intn,
	                            NcGePoint2d& p1, NcGePoint2d& p2,
	                            const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isCircular    (const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isInside      (const NcGePoint2d& pnt,
	                            const NcGeTol& tol = NcGeContext::gTol) const;
	NcGePoint2d    center        () const;
	double         minorRadius   () const;
	double         majorRadius   () const;
	NcGeVector2d   minorAxis     () const;
	NcGeVector2d   majorAxis     () const;
	double         startAng      () const;
	double         endAng        () const;
	NcGePoint2d    startPoint    () const;
	NcGePoint2d    endPoint      () const;
	NRX::Boolean isClockWise   () const;
	NcGeEllipArc2d& setCenter     (const NcGePoint2d& cent);
	NcGeEllipArc2d& setMinorRadius(double rad);
	NcGeEllipArc2d& setMajorRadius(double rad);
	NcGeEllipArc2d& setAxes       (const NcGeVector2d& majorAxis, const NcGeVector2d& minorAxis);
	NcGeEllipArc2d& setAngles     (double startAngle, double endAngle);
	NcGeEllipArc2d& set           (const NcGePoint2d& cent,
	                               const NcGeVector2d& majorAxis,
	                               const NcGeVector2d& minorAxis,
	                               double majorRadius, double minorRadius);
	NcGeEllipArc2d& set           (const NcGePoint2d& cent,
	                               const NcGeVector2d& majorAxis,
	                               const NcGeVector2d& minorAxis,
	                               double majorRadius, double minorRadius,
	                               double startAngle, double endAngle);
	NcGeEllipArc2d& set           (const NcGeCircArc2d& arc);
	NcGeEllipArc2d& operator =    (const NcGeEllipArc2d& ell);

	McGeEllipArc3d* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcGeExternalCurve2d
class NRXDBGATE_EXPORT NcGeExternalCurve2d : public NcGeCurve2d {
public:
	NcGeExternalCurve2d();
	NcGeExternalCurve2d(const NcGeExternalCurve2d&);
	NcGeExternalCurve2d(void* curveDef, NcGe::ExternalEntityKind curveKind,
	                    NRX::Boolean makeCopy = NRX::kTrue);
	NRX::Boolean isNurbCurve() const;
	NRX::Boolean isNurbCurve(NcGeNurbCurve2d& nurbCurve) const;
	NRX::Boolean isDefined  () const;
	void           getExternalCurve(void*& curveDef) const;
	NcGe::ExternalEntityKind externalCurveKind() const;
	NcGeExternalCurve2d& set(void* curveDef, NcGe::ExternalEntityKind curveKind,
	                         NRX::Boolean makeCopy = NRX::kTrue);
	NcGeExternalCurve2d& operator = (const NcGeExternalCurve2d& src);
	NRX::Boolean       isOwnerOfCurve() const;
	NcGeExternalCurve2d& setToOwnCurve();
};

//////////////////////////////////////////////////////////////////////////
// NcGeExternalCurve3d
class NRXDBGATE_EXPORT
NcGeExternalCurve3d : public NcGeCurve3d {
public:
	NcGeExternalCurve3d();
	NcGeExternalCurve3d(const NcGeExternalCurve3d& src);
	NcGeExternalCurve3d(void* curveDef, NcGe::ExternalEntityKind curveKind,
	                    NRX::Boolean makeCopy = NRX::kTrue);
	NRX::Boolean isLine     () const;
	NRX::Boolean isRay      () const;
	NRX::Boolean isLineSeg  () const;
	NRX::Boolean isCircArc  () const;
	NRX::Boolean isEllipArc () const;
	NRX::Boolean isNurbCurve() const;
	NRX::Boolean isDefined  () const;
	NRX::Boolean isNativeCurve  (NcGeCurve3d*& nativeCurve) const;
	void           getExternalCurve (void*& curveDef) const;
	NcGe::ExternalEntityKind externalCurveKind() const;
	NcGeExternalCurve3d& set(void* curveDef, NcGe::ExternalEntityKind curveKind,
	                         NRX::Boolean makeCopy = NRX::kTrue);
	NcGeExternalCurve3d& operator = (const NcGeExternalCurve3d& src);
	NRX::Boolean       isOwnerOfCurve   () const;
	NcGeExternalCurve3d& setToOwnCurve    ();
};

//////////////////////////////////////////////////////////////////////////
// NcGeExternalSurface
class NRXDBGATE_EXPORT NcGeExternalSurface : public NcGeSurface {
public:
	NcGeExternalSurface();
	NcGeExternalSurface(void* surfaceDef, NcGe::ExternalEntityKind surfaceKind,
	                    NRX::Boolean makeCopy = NRX::kTrue);
	NcGeExternalSurface(const NcGeExternalSurface&);
	void getExternalSurface(void*& surfaceDef) const;
	NcGe::ExternalEntityKind  externalSurfaceKind() const;
	NRX::Boolean    isPlane      () const;
	NRX::Boolean    isSphere     () const;
	NRX::Boolean    isCylinder   () const;
	NRX::Boolean    isCone       () const;
	NRX::Boolean    isTorus      () const;
	NRX::Boolean    isNurbSurface() const;
	NRX::Boolean    isDefined    () const;
	NRX::Boolean isNativeSurface(NcGeSurface*& nativeSurface) const;
	NcGeExternalSurface& operator = (const NcGeExternalSurface& src);
	NcGeExternalSurface& set(void* surfaceDef,
	                         NcGe::ExternalEntityKind surfaceKind,
	                         NRX::Boolean makeCopy = NRX::kTrue);
	NRX::Boolean       isOwnerOfSurface    () const;
	NcGeExternalSurface& setToOwnSurface     ();

public:
	OdGeExternalSurface* native() const
	{
		return (OdGeExternalSurface*)m_pOdImpl;
	}

};

//////////////////////////////////////////////////////////////////////////
// NcGeFiler
class NRXDBGATE_EXPORT NRX_NO_VTABLE
NcGeFiler {
protected:
	NcGeFiler();
public:
	virtual
	Nano::ErrorStatus      readBoolean(NRX::Boolean*) = 0;
	virtual
	Nano::ErrorStatus      writeBoolean(NRX::Boolean) = 0;
	virtual
	Nano::ErrorStatus      readBool(bool*) = 0;
	virtual
	Nano::ErrorStatus      writeBool(bool) = 0;
	virtual
	Nano::ErrorStatus      readSignedByte(char *) = 0;
	virtual
	Nano::ErrorStatus      writeSignedByte(char) = 0;
	virtual
	Nano::ErrorStatus      readString(NcString &) = 0;
	virtual
	Nano::ErrorStatus      writeString(const NcString &) = 0;
	virtual
	Nano::ErrorStatus      readShort(short*) = 0;
	virtual
	Nano::ErrorStatus      writeShort(short) = 0;
	virtual
	Nano::ErrorStatus      readLong(NRX::Int32*) = 0;
	virtual
	Nano::ErrorStatus      writeLong(NRX::Int32) = 0;
	virtual
	Nano::ErrorStatus      readUChar(unsigned char*) = 0;
	virtual
	Nano::ErrorStatus      writeUChar(unsigned char) = 0;
	virtual
	Nano::ErrorStatus      readUShort(unsigned short*) = 0;
	virtual
	Nano::ErrorStatus      writeUShort(unsigned short) = 0;
	virtual
	Nano::ErrorStatus      readULong(NRX::UInt32*) = 0;
	virtual
	Nano::ErrorStatus      writeULong(NRX::UInt32) = 0;
	virtual
	Nano::ErrorStatus      readDouble(double*) = 0;
	virtual
	Nano::ErrorStatus      writeDouble(double) = 0;
	virtual
	Nano::ErrorStatus      readPoint2d(NcGePoint2d*) = 0;
	virtual
	Nano::ErrorStatus      writePoint2d(const NcGePoint2d&) = 0;
	virtual
	Nano::ErrorStatus      readPoint3d(NcGePoint3d*) = 0;
	virtual
	Nano::ErrorStatus      writePoint3d(const NcGePoint3d&) = 0;
	virtual
	Nano::ErrorStatus      readVector2d(NcGeVector2d*) = 0;
	virtual
	Nano::ErrorStatus      writeVector2d(const NcGeVector2d&) = 0;
	virtual
	Nano::ErrorStatus      readVector3d(NcGeVector3d*) = 0;
	virtual
	Nano::ErrorStatus      writeVector3d(const NcGeVector3d&) = 0;
	virtual
	NcDbDwgFiler*          dwgFiler();
	virtual
	Nano::ErrorStatus      readBytes(void*, NRX::UInt32) = 0;
	virtual
	Nano::ErrorStatus      writeBytes(const void*, NRX::UInt32) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcGeNurbSurface
class OdGeNurbSurface;
class NRXDBGATE_EXPORT NcGeNurbSurface : public NcGeSurface {
public:
	NcGeNurbSurface();
	NcGeNurbSurface(McGeNurbSurface* _object);
	NcGeNurbSurface& operator = (const OdGeNurbSurface& odSurf);
	NcGeNurbSurface(int degreeU, int degreeV, int propsInU, int propsInV,
	                int numControlPointsInU, int numControlPointsInV,
	                const NcGePoint3d controlPoints[],
	                const double weights[],
	                const NcGeKnotVector& uKnots,
	                const NcGeKnotVector& vKnots,
	                const NcGeTol& tol = NcGeContext::gTol);
	NcGeNurbSurface(const NcGeNurbSurface& nurb);
	NcGeNurbSurface& operator = (const NcGeNurbSurface& nurb);
	NRX::Boolean   isRationalInU      () const;
	NRX::Boolean   isPeriodicInU      (double&) const;
	NRX::Boolean   isRationalInV      () const;
	NRX::Boolean   isPeriodicInV      (double&) const;
	int singularityInU () const;
	int singularityInV () const;
	int            degreeInU            () const;
	int            numControlPointsInU  () const;
	int            degreeInV            () const;
	int            numControlPointsInV  () const;
	void           getControlPoints     (NcGePoint3dArray& points) const;
	NRX::Boolean getWeights           (NcGeDoubleArray& weights) const;
	int       numKnotsInU    () const;
	void      getUKnots      (NcGeKnotVector& uKnots) const;
	int       numKnotsInV    () const;
	void      getVKnots      (NcGeKnotVector& vKnots) const;
	void      getDefinition  (int& degreeU, int& degreeV,
	                          int& propsInU,    int& propsInV,
	                          int& numControlPointsInU,
	                          int& numControlPointsInV,
	                          NcGePoint3dArray& controlPoints,
	                          NcGeDoubleArray& weights,
	                          NcGeKnotVector& uKnots,
	                          NcGeKnotVector& vKnots) const;
	NcGeNurbSurface& set     (int degreeU, int degreeV,
	                          int propsInU, int propsInV,
	                          int numControlPointsInU,
	                          int numControlPointsInV,
	                          const NcGePoint3d controlPoints[],
	                          const double weights[],
	                          const NcGeKnotVector& uKnots,
	                          const NcGeKnotVector& vKnots,
	                          const NcGeTol& tol = NcGeContext::gTol);

public:
	McGeNurbSurface* native() const
	{
		return (McGeNurbSurface*)m_pImpl;
	}

};

//////////////////////////////////////////////////////////////////////////
// NcGeOffsetCurve2d
class NRXDBGATE_EXPORT
NcGeOffsetCurve2d : public NcGeCurve2d {
public:
	NcGeOffsetCurve2d (const NcGeCurve2d& baseCurve, double offsetDistance);
	NcGeOffsetCurve2d (const NcGeOffsetCurve2d& offsetCurve);
	NcGeOffsetCurve2d (McGeOffsetCurve3d* _object)
	{
		m_pImpl = _object;
	}

  const NcGeCurve2d*  curve             () const;
	double              offsetDistance    () const;
	NRX::Boolean        paramDirection    () const;
	NcGeMatrix2d        transformation    () const;
	NcGeOffsetCurve2d&  setCurve          (const NcGeCurve2d& baseCurve);
	NcGeOffsetCurve2d&  setOffsetDistance (double distance);
	NcGeOffsetCurve2d&  operator = (const NcGeOffsetCurve2d& offsetCurve);
};

//////////////////////////////////////////////////////////////////////////
// NcGeOffsetCurve3d
class NRXDBGATE_EXPORT NcGeOffsetCurve3d : public NcGeCurve3d {
public:
	NcGeOffsetCurve3d (const NcGeCurve3d& baseCurve, const NcGeVector3d& planeNormal,
	                   double offsetDistance);
	NcGeOffsetCurve3d (const NcGeOffsetCurve3d& offsetCurve);
	NcGeOffsetCurve3d (McGeOffsetCurve3d* _object)
	{
		m_pImpl = _object;
	}

	const NcGeCurve3d*  curve             () const;
	NcGeVector3d        normal            () const;
	double              offsetDistance    () const;
	NRX::Boolean        paramDirection    () const;
	NcGeMatrix3d        transformation    () const;
	NcGeOffsetCurve3d&  setCurve          (const NcGeCurve3d& baseCurve);
	NcGeOffsetCurve3d&  setNormal         (const NcGeVector3d& planeNormal);
	NcGeOffsetCurve3d&  setOffsetDistance (double offsetDistance);
	NcGeOffsetCurve3d&  operator = (const NcGeOffsetCurve3d& offsetCurve);
};

//////////////////////////////////////////////////////////////////////////
// NcGeOffsetSurface
class NRXDBGATE_EXPORT NcGeOffsetSurface : public NcGeSurface {
public:
	NcGeOffsetSurface();
	NcGeOffsetSurface(NcGeSurface* baseSurface,
	                  double offsetDist,
	                  NRX::Boolean makeCopy = NRX::kTrue);
	NcGeOffsetSurface(const NcGeOffsetSurface& offset);
	NRX::Boolean    isPlane        () const;
	NRX::Boolean    isBoundedPlane () const;
	NRX::Boolean    isSphere       () const;
	NRX::Boolean    isCylinder     () const;
	NRX::Boolean    isCone         () const;
	NRX::Boolean    isTorus        () const;
	    NRX::Boolean    getSurface(NcGeSurface*&) const;
	void              getConstructionSurface (NcGeSurface*& base) const;
	double            offsetDist     () const;
	NcGeOffsetSurface& set        (NcGeSurface*, double offsetDist,
	                               NRX::Boolean makeCopy = NRX::kTrue);
	NcGeOffsetSurface& operator =  (const NcGeOffsetSurface& offset);
};

//////////////////////////////////////////////////////////////////////////
// NcGePointEnt2d
class NRXDBGATE_EXPORT NcGePointEnt2d : public NcGeEntity2d {
public:
	NcGePointEnt2d (McGePointEnt3d* _object);
	NcGePoint2d     point2d     () const;
	operator        NcGePoint2d () const;
	NcGePointEnt2d& operator =  (const NcGePointEnt2d& pnt);

	static NcGePointEnt2d* NewNcGePointEnt(McGeEntity3d *pNative, bool bAssert=false);
protected:
	NcGePointEnt2d ();
	NcGePointEnt2d (const NcGePointEnt2d&);
};

//////////////////////////////////////////////////////////////////////////
// NcGePointEnt3d
class NRXDBGATE_EXPORT NcGePointEnt3d : public NcGeEntity3d {
public:
	NcGePointEnt3d(McGeEntity3d* _object);
	NcGePoint3d     point3d     () const;
	operator        NcGePoint3d () const;
	NcGePointEnt3d& operator =  (const NcGePointEnt3d& pnt);

	McGePointEnt3d* native() const;

	static NcGePointEnt3d* NewNcGePointEnt(McGeEntity3d *pNative, bool bAssert=false);
protected:
	NcGePointEnt3d ();
	NcGePointEnt3d (const NcGePointEnt3d&);
};

//////////////////////////////////////////////////////////////////////////
// NcGePointOnSurface
class NRXDBGATE_EXPORT NcGePointOnSurface : public NcGePointEnt3d {
public:
	NcGePointOnSurface();
	NcGePointOnSurface(const NcGeSurface& surf);
	NcGePointOnSurface(const NcGeSurface& surf, const NcGePoint2d& param);
	NcGePointOnSurface(const NcGePointOnSurface& src);
	NcGePointOnSurface(McGePointOnSurface* _object);

	NcGePointOnSurface& operator =     (const NcGePointOnSurface& src);
	const NcGeSurface*  surface        () const;
	NcGePoint2d         parameter      () const;
	NcGePoint3d         point          () const;
	NcGePoint3d         point          (const NcGePoint2d& param );
	NcGePoint3d         point          (const NcGeSurface& surf,
	                                    const NcGePoint2d& param);
	NcGeVector3d        normal         () const;
	NcGeVector3d        normal         (const NcGePoint2d& param );
	NcGeVector3d        normal         (const NcGeSurface& surf,
	                                    const NcGePoint2d& param);
	NcGeVector3d        uDeriv         (int order) const;
	NcGeVector3d        uDeriv         (int order, const NcGePoint2d& param);
	NcGeVector3d        uDeriv         (int order, const NcGeSurface& surf,
	                                    const NcGePoint2d& param);
	NcGeVector3d        vDeriv         (int order) const;
	NcGeVector3d        vDeriv         (int order, const NcGePoint2d& param);
	NcGeVector3d        vDeriv         (int order, const NcGeSurface& surf,
	                                    const NcGePoint2d& param);
	NcGeVector3d        mixedPartial   () const;
	NcGeVector3d        mixedPartial   (const NcGePoint2d& param);
	NcGeVector3d        mixedPartial   (const NcGeSurface& surf,
	                                    const NcGePoint2d& param);
	NcGeVector3d        tangentVector  (const NcGeVector2d& vec) const;
	NcGeVector3d        tangentVector  (const NcGeVector2d& vec,
	                                    const NcGePoint2d& param);
	NcGeVector3d        tangentVector  (const NcGeVector2d& vec,
	                                    const NcGeSurface& vecSurf,
	                                    const NcGePoint2d& param);
	NcGeVector2d        inverseTangentVector  (const NcGeVector3d& vec) const;
	NcGeVector2d        inverseTangentVector  (const NcGeVector3d& vec,
	                                           const NcGePoint2d& param);
	NcGeVector2d        inverseTangentVector  (const NcGeVector3d& vec,
	                                           const NcGeSurface& surf,
	                                           const NcGePoint2d& param);
	NcGePointOnSurface& setSurface     (const NcGeSurface& surf);
	NcGePointOnSurface& setParameter   (const NcGePoint2d& param);
};

//////////////////////////////////////////////////////////////////////////

// NcGePosition2d
class NRXDBGATE_EXPORT NcGePosition2d : public NcGePointEnt2d {
public:
	NcGePosition2d ();
	NcGePosition2d (const NcGePoint2d& pnt);
	NcGePosition2d (double x, double y);
	NcGePosition2d (const NcGePosition2d& pos);
	NcGePosition2d (McGePosition3d* _object);
	NcGePosition2d&  set        (const NcGePoint2d&);
	NcGePosition2d&  set        (double x, double y );
	NcGePosition2d& operator =  (const NcGePosition2d& pos);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcGePointOnCurve2d
class NRXDBGATE_EXPORT NcGePointOnCurve2d : public NcGePointEnt2d
{
public:
	NcGePointOnCurve2d();
	NcGePointOnCurve2d(const NcGeCurve2d& crv);
	NcGePointOnCurve2d(const NcGeCurve2d& crv, double param);
	NcGePointOnCurve2d(const NcGePointOnCurve2d& src);
	NcGePointOnCurve2d(McGePointOnCurve3d* _object);
	~NcGePointOnCurve2d();

	NcGePointOnCurve2d& operator =(const NcGePointOnCurve2d& src);

	const NcGeCurve2d* curve() const;

	double parameter() const;
	NcGePoint2d point() const;
	NcGePoint2d point(double param);
	NcGePoint2d point(const NcGeCurve2d& crv, double param);
	NcGeVector2d deriv(int order) const;
	NcGeVector2d deriv(int order, double param);
	NcGeVector2d deriv(int order, const NcGeCurve2d& crv, double param);
	NRX::Boolean isSingular(const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean curvature(double& res);
	NRX::Boolean curvature(double param, double& res);
	NcGePointOnCurve2d& setCurve(const NcGeCurve2d& crv);
	NcGePointOnCurve2d& setParameter(double param);
	NcGePoint2d point2d();

public:
	inline McGePointOnCurve3d* native() const
	{
		return m_ptImpl;
	}

public:
	McGePointOnCurve3d*  m_ptImpl;
	mutable NcGeCurve2d* m_crv;
};

//////////////////////////////////////////////////////////////////////////
// NcGePosition3d
class NRXDBGATE_EXPORT NcGePosition3d : public NcGePointEnt3d {
public:
	NcGePosition3d ();
	NcGePosition3d (const NcGePoint3d& pnt);
	NcGePosition3d (double x, double y, double z);
	NcGePosition3d (const NcGePosition3d& pos);
	NcGePosition3d (McGePosition3d* _object);

	NcGePosition3d&  set        (const NcGePoint3d&);
	NcGePosition3d&  set        (double x, double y, double z );
	NcGePosition3d& operator =  (const NcGePosition3d& pos);
};

//////////////////////////////////////////////////////////////////////////
// NcGeScale3d
class NRXDBGATE_EXPORT NcGeScale3d
{
public:
	NcGeScale3d() throw();
	explicit NcGeScale3d(const OdGeScale3d* src) throw();
	NcGeScale3d(const NcGeScale3d& src) throw();
	NcGeScale3d(double factor) throw();
	NcGeScale3d(double xFact, double yFact, double zFact) throw();

public:
	static const   NcGeScale3d kIdentity;

	operator OdGeScale3d() const;
	NcGeScale3d& operator = (const OdGeScale3d& rh);

	NcGeScale3d    operator *  (const NcGeScale3d& sclVec) const;
	NcGeScale3d&   operator *= (const NcGeScale3d& scl);
	NcGeScale3d&   preMultBy   (const NcGeScale3d& leftSide);
	NcGeScale3d&   postMultBy  (const NcGeScale3d& rightSide);
	NcGeScale3d&   setToProduct(const NcGeScale3d& sclVec1, const NcGeScale3d& sclVec2);
	NcGeScale3d    operator *  (double s) const;
	NcGeScale3d&   operator *= (double s);
	NcGeScale3d&   setToProduct(const NcGeScale3d& sclVec, double s);
	NcGeScale3d    inverse        () const;
	NcGeScale3d&   invert         ();
	NRX::Boolean isProportional(const NcGeTol& tol = NcGeContext::gTol) const;
	bool operator == (const NcGeScale3d& sclVec) const;
	bool operator != (const NcGeScale3d& sclVec) const;
	bool isEqualTo   (const NcGeScale3d& scaleVec,
	                  const NcGeTol& tol = NcGeContext::gTol) const;
	double         operator [] (unsigned int i) const;
	double&        operator [] (unsigned int i);
	NcGeScale3d&   set         (double sc0, double sc1, double sc2);

	operator       NcGeMatrix3d   () const;
	void getMatrix(NcGeMatrix3d& mat) const;
	NcGeScale3d&   extractScale   ( const NcGeMatrix3d& mat );
	NcGeScale3d&   removeScale    ( NcGeMatrix3d& mat );

	double         sx, sy, sz;
};

//////////////////////////////////////////////////////////////////////////
// NcGeScale2d
class NRXDBGATE_EXPORT NcGeScale2d {
public:
	NcGeScale2d();
	NcGeScale2d(const NcGeScale2d& src);
	NcGeScale2d(double factor);
	NcGeScale2d(double xFactor, double yFactor);
	static const   NcGeScale2d kIdentity;
	NcGeScale2d    operator *  (const NcGeScale2d& sclVec) const;
	NcGeScale2d&   operator *= (const NcGeScale2d& scl);
	NcGeScale2d&   preMultBy   (const NcGeScale2d& leftSide);
	NcGeScale2d&   postMultBy  (const NcGeScale2d& rightSide);
	NcGeScale2d&   setToProduct(const NcGeScale2d& sclVec1, const NcGeScale2d& sclVec2);
	NcGeScale2d    operator *  (double s) const;
	NcGeScale2d&   operator *= (double s);
	NcGeScale2d&   setToProduct(const NcGeScale2d& sclVec, double s);
	friend
NRXDBGATE_EXPORT
	NcGeScale2d    operator *  (double, const NcGeScale2d& scl);
	NcGeScale2d    inverse        () const;
	NcGeScale2d&   invert         ();
	NRX::Boolean isProportional(const NcGeTol& tol = NcGeContext::gTol) const;
	bool operator == (const NcGeScale2d& sclVec) const;
	bool operator != (const NcGeScale2d& sclVec) const;
	bool isEqualTo   (const NcGeScale2d& scaleVec,
	                  const NcGeTol& tol = NcGeContext::gTol) const;
	double         operator [] (unsigned int i) const;
	double&        operator [] (unsigned int i);
	NcGeScale2d&   set         (double sc0, double sc1);
	operator       NcGeMatrix2d   () const;
	void           getMatrix      (NcGeMatrix2d& mat) const;
	NcGeScale2d&   extractScale   ( const NcGeMatrix2d& mat );
	NcGeScale2d&   removeScale    ( NcGeMatrix2d& mat );
	operator       NcGeScale3d    () const;
	double         sx, sy;
};

//////////////////////////////////////////////////////////////////////////
// NcGeSphere
class OdGeSphere;
class NRXDBGATE_EXPORT NcGeSphere : public NcGeSurface {
public:
	NcGeSphere();
	NcGeSphere(double radius, const NcGePoint3d& center);
	NcGeSphere(double radius, const NcGePoint3d& center,
	           const NcGeVector3d& northAxis, const NcGeVector3d& refAxis,
	           double startAngleU, double endAngleU,
	           double startAngleV, double endAngleV);
	NcGeSphere(const NcGeSphere& sphere);

	double         radius            () const;
	NcGePoint3d    center            () const;
	void           getAnglesInU      (double& start, double& end) const;
	void           getAnglesInV      (double& start, double& end) const;
	NcGeVector3d   northAxis         () const;
	NcGeVector3d   refAxis           () const;
	NcGePoint3d    northPole         () const;
	NcGePoint3d    southPole         () const;
	NRX::Boolean isOuterNormal     () const;
	NRX::Boolean isClosed       (const NcGeTol& tol = NcGeContext::gTol) const;
	NcGeSphere&    setRadius         (double);
	NcGeSphere&    setAnglesInU      (double start, double end);
	NcGeSphere&    setAnglesInV      (double start, double end);
	NcGeSphere&    set               (double radius, const NcGePoint3d& center);
	NcGeSphere&    set               (double radius, const NcGePoint3d& center,
	                                  const NcGeVector3d& northAxis,
	                                  const NcGeVector3d& refAxis,
	                                  double startAngleU,
	                                  double endAngleU,
	                                  double startAngleV,
	                                  double endAngleV);
	NcGeSphere&    operator =     (const NcGeSphere& sphere);
	NRX::Boolean intersectWith  (const NcGeLinearEnt3d&, int& intn,
	                             NcGePoint3d& p1, NcGePoint3d& p2,
	                             const NcGeTol& tol = NcGeContext::gTol) const;
public:
	OdGeSphere* native() const
	{
		return (OdGeSphere*)m_pOdImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcGeSurfSurfInt
class NRXDBGATE_EXPORT NcGeSurfSurfInt  : public NcGeEntity3d {
public:
	NcGeSurfSurfInt ();
	NcGeSurfSurfInt (
	                    const NcGeSurface& srf1,
	                    const NcGeSurface& srf2,
	                    const NcGeTol& tol = NcGeContext::gTol );
	NcGeSurfSurfInt (const NcGeSurfSurfInt& src);
	virtual ~NcGeSurfSurfInt();

	const NcGeSurface  *surface1 () const;
	const NcGeSurface  *surface2 () const;
	NcGeTol            tolerance() const;
	int                numResults (NcGe::NcGeIntersectError& err) const;
	NcGeCurve3d*   intCurve (int intNum, NRX::Boolean isExternal, NcGe::NcGeIntersectError& err) const;
	NcGeCurve2d*   intParamCurve(int num, NRX::Boolean isExternal, NRX::Boolean isFirst, NcGe::NcGeIntersectError& err) const;
	NcGePoint3d  intPoint (int intNum, NcGe::NcGeIntersectError& err) const;
	void               getIntPointParams (int intNum,
	                                      NcGePoint2d& param1, NcGePoint2d& param2, NcGe::NcGeIntersectError& err) const;
	void getIntConfigs (int intNum, NcGe::ssiConfig& surf1Left,  NcGe::ssiConfig& surf1Right,
	                    NcGe::ssiConfig& surf2Left,  NcGe::ssiConfig& surf2Right,
	                    NcGe::ssiType& intType, int& dim, NcGe::NcGeIntersectError& err ) const;
	int        getDimension (int intNum, NcGe::NcGeIntersectError& err) const;
	NcGe::ssiType    getType(int intNum, NcGe::NcGeIntersectError& err ) const;
	NcGeSurfSurfInt& set (const NcGeSurface& srf1,
	                      const NcGeSurface& srf2,
	                      const NcGeTol& tol = NcGeContext::gTol);
	NcGeSurfSurfInt& operator = (const NcGeSurfSurfInt& crvInt);

private:
	class NcGeSurfSurfIntPD;
	NcGeSurfSurfIntPD* pd;
};

//////////////////////////////////////////////////////////////////////////
// NcGeTorus
class NRXDBGATE_EXPORT NcGeTorus : public NcGeSurface {
public:
	NcGeTorus();
	NcGeTorus(double majorRadius, double minorRadius,
	          const NcGePoint3d& origin, const NcGeVector3d& axisOfSymmetry);
	NcGeTorus(double majorRadius, double minorRadius,
	          const NcGePoint3d&  origin, const NcGeVector3d& axisOfSymmetry,
	          const NcGeVector3d& refAxis,
	          double startAngleU, double endAngleU,
	          double startAngleV, double endAngleV);
	NcGeTorus(const NcGeTorus& torus);
	double          majorRadius    () const;
	double          minorRadius    () const;
	void            getAnglesInU   (double& start, double& end) const;
	void            getAnglesInV   (double& start, double& end) const;
	NcGePoint3d     center         () const;
	NcGeVector3d    axisOfSymmetry () const;
	NcGeVector3d    refAxis        () const;
	NRX::Boolean  isOuterNormal  () const;
	NcGeTorus&      setMajorRadius (double radius);
	NcGeTorus&      setMinorRadius (double radius);
	NcGeTorus&      setAnglesInU   (double start, double end);
	NcGeTorus&      setAnglesInV   (double start, double end);
	NcGeTorus&      set            (double majorRadius, double minorRadius,
	                                const NcGePoint3d& origin,
	                                const NcGeVector3d& axisOfSymmetry);
	NcGeTorus&      set            (double majorRadius, double minorRadius,
	                                const NcGePoint3d&  origin,
	                                const NcGeVector3d& axisOfSymmetry,
	                                const NcGeVector3d& refAxis,
	                                double startAngleU, double endAngleU,
	                                double startAngleV, double endAngleV);
	NcGeTorus&      operator =     (const NcGeTorus& torus);
	NRX::Boolean  intersectWith  (const NcGeLinearEnt3d& linEnt, int& intn,
	                              NcGePoint3d& p1, NcGePoint3d& p2,
	                              NcGePoint3d& p3, NcGePoint3d& p4,
	                              const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isLemon     () const;
	NRX::Boolean isApple     () const;
	NRX::Boolean isVortex    () const;
	NRX::Boolean isDoughnut  () const;
	NRX::Boolean isDegenerate() const;
	NRX::Boolean isHollow    () const;
};

//////////////////////////////////////////////////////////////////////////
// NcGeExternalBoundedSurface
class NRXDBGATE_EXPORT NcGeExternalBoundedSurface : public NcGeSurface {
public:
	NcGeExternalBoundedSurface();
	NcGeExternalBoundedSurface(void* surfaceDef, NcGe::ExternalEntityKind surfaceKind,
	                           NRX::Boolean makeCopy = NRX::kTrue);
	NcGeExternalBoundedSurface(const NcGeExternalBoundedSurface&);
	~NcGeExternalBoundedSurface();

	NcGe::ExternalEntityKind   externalSurfaceKind  () const;
	NRX::Boolean             isDefined            () const;
	void                       getExternalSurface   (void*& surfaceDef) const;
	void getBaseSurface        (NcGeSurface*& surfaceDef) const;
	void getBaseSurface        (NcGeExternalSurface& unboundedSurfaceDef) const;
	NRX::Boolean isPlane() const;
	NRX::Boolean isSphere() const;
	NRX::Boolean isCylinder() const;
	NRX::Boolean isCone() const;
	NRX::Boolean isTorus() const;
	NRX::Boolean isNurbs() const;
	NRX::Boolean isExternalSurface() const;
	int          numContours  () const;
	void         getContours  (int& numContours, NcGeCurveBoundary*& curveBoundaries) const;
	NcGeExternalBoundedSurface& set  (void* surfaceDef,
	                                  NcGe::ExternalEntityKind surfaceKind,
	                                  NRX::Boolean makeCopy = NRX::kTrue);
	NcGeExternalBoundedSurface& operator = (const NcGeExternalBoundedSurface&);
	NRX::Boolean               isOwnerOfSurface() const;
	NcGeExternalBoundedSurface&  setToOwnSurface();

// NcGeSurface methods
public:
	NcGePoint2d     paramOf        (const NcGePoint3d& pnt,
	                                const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean  isOn           (const NcGePoint3d& pnt,
	                              const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean  isOn           (const NcGePoint3d& pnt, NcGePoint2d& paramPoint,
	                              const NcGeTol& tol = NcGeContext::gTol ) const;
	NcGePoint3d closestPointTo(const NcGePoint3d& pnt,
	                           const NcGeTol& tol = NcGeContext::gTol) const;
	void getClosestPointTo(const NcGePoint3d& pnt, NcGePointOnSurface& result,
	                       const NcGeTol& tol = NcGeContext::gTol) const;
	double          distanceTo     (const NcGePoint3d& pnt,
	                                const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean  isNormalReversed () const;
	NcGeSurface&    reverseNormal    ();
	NcGeSurface&    operator =     (const NcGeSurface& otherSurface);
	void   getEnvelope  (NcGeInterval& intrvlX, NcGeInterval& intrvlY) const;
	NRX::Boolean isClosedInU       (const NcGeTol& tol = NcGeContext::gTol) const;
	NRX::Boolean isClosedInV       (const NcGeTol& tol = NcGeContext::gTol) const;
	NcGePoint3d   evalPoint   (const NcGePoint2d& param) const;
	NcGePoint3d   evalPoint   (const NcGePoint2d& param, int derivOrd,
	                           NcGeVector3dArray& derivatives) const;
	NcGePoint3d   evalPoint   (const NcGePoint2d& param, int derivOrd,
	                           NcGeVector3dArray& derivatives,
	                           NcGeVector3d& normal) const;

public:
	OdGeExternalBoundedSurface* native() const
	{
		return (OdGeExternalBoundedSurface*)m_pOdImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcGeNurbCurve2d
class NRXDBGATE_EXPORT NcGeNurbCurve2d : public NcGeSplineEnt2d {
public:
	NcGeNurbCurve2d(McGeSplineEnt3d* _object);
	NcGeNurbCurve2d ();
	NcGeNurbCurve2d (const NcGeNurbCurve2d& src );
	NcGeNurbCurve2d (int degree, const NcGeKnotVector& knots,
	                 const NcGePoint2dArray& cntrlPnts,
	                 NRX::Boolean isPeriodic = NRX::kFalse );
	NcGeNurbCurve2d (int degree, const NcGeKnotVector& knots,
	                 const NcGePoint2dArray& cntrlPnts,
	                 const NcGeDoubleArray&  weights,
	                 NRX::Boolean isPeriodic = NRX::kFalse );
	NcGeNurbCurve2d (int degree, const NcGePolyline2d& fitPolyline,
	                 NRX::Boolean isPeriodic = NRX::kFalse );
	NcGeNurbCurve2d (const NcGePoint2dArray& fitPoints,
	                 const NcGeVector2d& startTangent,
	                 const NcGeVector2d& endTangent,
	                 NRX::Boolean startTangentDefined = NRX::kTrue,
	                 NRX::Boolean endTangentDefined   = NRX::kTrue,
	                 const NcGeTol& fitTolerance = NcGeContext::gTol);
	//NcGeNurbCurve2d (const NcGePoint2dArray& fitPoints,
	//                 const NcGeVector2d& startTangent,
	//                 const NcGeVector2d& endTangent,
	//                 NRX::Boolean startTangentDefined,
	//                 NRX::Boolean endTangentDefined,
	//                 NcGe::KnotParameterization knotParam,
	//                 const NcGeTol& fitTolerance = NcGeContext::gTol);
	NcGeNurbCurve2d (const NcGePoint2dArray& fitPoints,
	                 const NcGeTol& fitTolerance = NcGeContext::gTol);
	NcGeNurbCurve2d (const NcGePoint2dArray& fitPoints,
	                 const NcGeVector2dArray& fitTangents,
	                 const NcGeTol& fitTolerance = NcGeContext::gTol,
	                 NRX::Boolean isPeriodic = NRX::kFalse);
	NcGeNurbCurve2d (const NcGeEllipArc2d&  ellipse);
	NcGeNurbCurve2d (const NcGeLineSeg2d& linSeg);
	NcGeNurbCurve2d(const NcGeCurve2d& curve,
	                double epsilon = NcGeContext::gTol.equalPoint());
	int             numFitPoints      () const;
	NRX::Boolean  getFitPointAt     (int index, NcGePoint2d& point) const;
	NRX::Boolean  getFitTolerance   (NcGeTol& fitTolerance) const;
	NRX::Boolean  getFitTangents    (NcGeVector2d& startTangent,
	                                 NcGeVector2d& endTangent) const;
	NRX::Boolean  getFitKnotParameterization(KnotParameterization& knotParam) const;
	NRX::Boolean  getFitData        (NcGePoint2dArray& fitPoints,
	                                 NcGeTol& fitTolerance,
	                                 NRX::Boolean& tangentsExist,
	                                 NcGeVector2d& startTangent,
	                                 NcGeVector2d& endTangent) const;
	NRX::Boolean  getFitData        (NcGePoint2dArray& fitPoints,
	                                 NcGeTol& fitTolerance,
	                                 NRX::Boolean& tangentsExist,
	                                 NcGeVector2d& startTangent,
	                                 NcGeVector2d& endTangent,
	                                 KnotParameterization& knotParam) const;
	void            getDefinitionData (int& degree, NRX::Boolean& rational,
	                                   NRX::Boolean& periodic,
	                                   NcGeKnotVector& knots,
	                                   NcGePoint2dArray& controlPoints,
	                                   NcGeDoubleArray& weights) const;
	int             numWeights        () const;
	double          weightAt          (int idx) const;
	NRX::Boolean  evalMode          () const;
	NRX::Boolean  getParamsOfC1Discontinuity (NcGeDoubleArray& params,
                                              const NcGeTol& tol
                                              = NcGeContext::gTol) const;
	NRX::Boolean    getParamsOfG1Discontinuity (NcGeDoubleArray& params,
	                                            const NcGeTol& tol
	                                            = NcGeContext::gTol) const;
	NRX::Boolean   setFitPointAt    (int index, const NcGePoint2d& point);
	NRX::Boolean   addFitPointAt    (int index, const NcGePoint2d& point);
	NRX::Boolean   deleteFitPointAt (int index);
	NRX::Boolean   setFitTolerance  (const NcGeTol& fitTol=NcGeContext::gTol);
	NRX::Boolean   setFitTangents   (const NcGeVector2d& startTangent,
	                                 const NcGeVector2d& endTangent);
	NRX::Boolean   setFitKnotParameterization(KnotParameterization knotParam);
	NcGeNurbCurve2d& setFitData       (const NcGePoint2dArray& fitPoints,
	                                   const NcGeVector2d& startTangent,
	                                   const NcGeVector2d& endTangent,
	                                   const NcGeTol& fitTol=NcGeContext::gTol);
	NcGeNurbCurve2d& setFitData       (const NcGePoint2dArray& fitPoints,
	                                   const NcGeVector2d& startTangent,
	                                   const NcGeVector2d& endTangent,
	                                   KnotParameterization knotParam,
	                                   const NcGeTol& fitTol=NcGeContext::gTol);
	NcGeNurbCurve2d& setFitData       (const NcGeKnotVector& fitKnots,
	                                   const NcGePoint2dArray& fitPoints,
	                                   const NcGeVector2d& startTangent,
	                                   const NcGeVector2d& endTangent,
	                                   const NcGeTol& fitTol=NcGeContext::gTol,
	                                   NRX::Boolean isPeriodic=NRX::kFalse);
	NcGeNurbCurve2d&  setFitData      (int degree,
	                                   const NcGePoint2dArray& fitPoints,
	                                   const NcGeTol& fitTol=NcGeContext::gTol);
	NRX::Boolean    purgeFitData    ();
	NRX::Boolean    buildFitData    ();
	NcGeNurbCurve2d&  addKnot         (double newKnot);
	NcGeNurbCurve2d&  insertKnot      (double newKnot);
	NcGeSplineEnt2d&  setWeightAt     (int idx, double val);
	NcGeNurbCurve2d&  setEvalMode     (NRX::Boolean evalMode=NRX::kFalse );
	NcGeNurbCurve2d&  joinWith        (const NcGeNurbCurve2d& curve);
	NcGeNurbCurve2d&  hardTrimByParams(double newStartParam,
	                                   double newEndParam);
	NcGeNurbCurve2d&  makeRational    (double weight = 1.0);
	NcGeNurbCurve2d&  makeClosed      ();
	NcGeNurbCurve2d&  makePeriodic    ();
	NcGeNurbCurve2d&  makeNonPeriodic ();
	NcGeNurbCurve2d&  makeOpen        ();
	NcGeNurbCurve2d&  elevateDegree   (int plusDegree);
	NRX::Boolean    addControlPointAt(double newKnot, const NcGePoint2d& point, double weight = 1.0);
	NRX::Boolean    deleteControlPointAt(int index);
	NcGeNurbCurve2d&  operator =      (const NcGeNurbCurve2d& spline);
	McGeNurbCurve3d* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcGeLibVersion
class NRXDBGATE_EXPORT NcGeLibVersion {
public:
	NcGeLibVersion();
	NcGeLibVersion(const NcGeLibVersion&);
	NcGeLibVersion(NRX::UInt8 major, NRX::UInt8 minor,
	               NRX::UInt8 corrective,
	               NRX::UInt8 internal_version);
	NRX::UInt8     majorVersion        () const;
	NRX::UInt8     minorVersion        () const;
	NRX::UInt8     correctiveVersion   () const;
	NRX::UInt8     schemaVersion       () const;
	NcGeLibVersion&     setMajorVersion        (NRX::UInt8 val);
	NcGeLibVersion&     setMinorVersion        (NRX::UInt8 val);
	NcGeLibVersion&     setCorrectiveVersion   (NRX::UInt8 val);
	NcGeLibVersion&     setSchemaVersion       (NRX::UInt8 val);
	NRX::Boolean operator ==      (const NcGeLibVersion&) const;
	NRX::Boolean operator !=      (const NcGeLibVersion&) const;
	NRX::Boolean operator <       (const NcGeLibVersion&) const;
	NRX::Boolean operator <=      (const NcGeLibVersion&) const;
	NRX::Boolean operator >       (const NcGeLibVersion&) const;
	NRX::Boolean operator >=      (const NcGeLibVersion&) const;
	static const NcGeLibVersion kRelease0_95;
	static const NcGeLibVersion kReleaseSed;
	static const NcGeLibVersion kReleaseTah;
private:
	NRX::UInt8   mVersion[10];
};

NRXDBGATE_EXPORT void modelToPixel(const NcGeMatrix3d& modToPix, const NcGePoint3d& modPt, NcGePoint2d& pixPt);
NRXDBGATE_EXPORT void modelToPixel(const NcGeVector3d& viewDir, const NcGeMatrix3d& modToPix,
                         const NcGePlane& plane, const NcGePoint3d& modPt, NcGePoint2d& pixPt);
NRXDBGATE_EXPORT void pixelToModel(const NcGeMatrix3d& pixToMod, const NcGePoint2d& pixPt, NcGePoint3d& modPt);

// AutoGen:
#endif // __OPENDWG_GEOMETRY_H__
