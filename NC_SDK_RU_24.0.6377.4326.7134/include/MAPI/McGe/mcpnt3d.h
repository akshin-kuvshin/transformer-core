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

#include "mcvec3d.h"

class McGeMatrix3d;
class McGeLinearEnt3d;
class McGePlane;
class McGePlanarEnt;
class McGeVector3d;
class McGePoint3d;
class McGePoint2d;

class OdGePoint3d;

//==============================================================================
class McGePoint3d
{
public:
	double x, y, z;

public:
	DECLARE_OBJ_NEWDEL;
	MCGEL_API McGePoint3d();
	MCGEL_API McGePoint3d(const McGePoint3d& pnt);
	MCGEL_API McGePoint3d(double x, double y, double z);
	MCGEL_API McGePoint3d(const McGePlanarEnt& pln, const McGePoint2d& pnt2d);

	// The origin, or (0, 0, 0).
	MCGEL_API static const   McGePoint3d    kOrigin;

	// Matrix multiplication.
	friend MCGEL_API McGePoint3d operator * (const McGeMatrix3d& mat, const McGePoint3d& pnt);
	MCGEL_API McGePoint3d&   setToProduct(const McGeMatrix3d& mat, const McGePoint3d& pnt);
	MCGEL_API McGePoint3d&   transformBy (const McGeMatrix3d& leftSide);
	MCGEL_API McGePoint3d&   rotateBy    (double angle, const McGeVector3d& vec, const McGePoint3d& wrtPoint = McGePoint3d::kOrigin);
	MCGEL_API McGePoint3d&   mirror      (const McGePlane& pln);
	MCGEL_API McGePoint3d&   scaleBy     (double scaleFactor, const McGePoint3d& wrtPoint = McGePoint3d::kOrigin);
	MCGEL_API McGePoint2d    convert2d   (const McGePlanarEnt& pln) const;

	// Scale multiplication.
	MCGEL_API McGePoint3d    operator *  (double scl) const;
	MCGEL_API McGePoint3d&   operator *= (double scl);
	MCGEL_API McGePoint3d    operator /  (double scl) const;
	MCGEL_API McGePoint3d&   operator /= (double scl);

	// Translation by a vector.
	MCGEL_API McGePoint3d    operator +  (const McGeVector3d& vec) const;
	MCGEL_API McGePoint3d&   operator += (const McGeVector3d& vec);
	MCGEL_API McGePoint3d    operator -  (const McGeVector3d& vec) const;
	MCGEL_API McGePoint3d&   operator -= (const McGeVector3d& vec);
	MCGEL_API McGePoint3d&   setToSum    (const McGePoint3d& pnt, const McGeVector3d& vec);

	// Get the vector between two points.
	MCGEL_API McGeVector3d   operator -  (const McGePoint3d& pnt) const;
	MCGEL_API McGeVector3d   asVector() const;
	MCGEL_API McGePoint2d   asPoint2d() const;

	// Distance to other geometric objects.
	MCGEL_API double         distanceTo       (const McGePoint3d& pnt) const;

	// Projection on plane
	MCGEL_API McGePoint3d    project       (const McGePlane& pln, const McGeVector3d& vec) const;
	MCGEL_API McGePoint3d    orthoProject  (const McGePlane& pln) const;

	// Tests for equivalence using the Euclidean norm.
	MCGEL_API bool operator == (const McGePoint3d& pnt) const;
	MCGEL_API bool operator != (const McGePoint3d& pnt) const;
	MCGEL_API bool isEqualTo   (const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;

	// For convenient access to the data.
	MCGEL_API double         operator [] (unsigned int i) const;
	MCGEL_API double&        operator [] (unsigned int idx);
	MCGEL_API McGePoint3d&   set         (double x, double y, double z);
	MCGEL_API McGePoint3d&   set         (const McGePlanarEnt& pln, const McGePoint2d& pnt);

	operator const OdGePoint3d&() const
	{
		return *(OdGePoint3d*)this;
	}

	double _sqrDistanceTo(const McGePoint3d& pnt) const;

	operator OdGePoint3d&()
	{
		return *(OdGePoint3d*)this;
	}

#ifdef MCGE_OD_SUPPORT
	McGePoint3d(const OdGePoint3d& src) : x(src.x), y(src.y), z(src.z)
	{
	}
#endif//#ifdef MCGE_OD_SUPPORT
};
//==============================================================================

template <> MCGEL_API void __stdcall McsConstructElements(McGePoint3d* pElements, INT_PTR nCount);
template <> MCGEL_API void __stdcall McsDestructElements(McGePoint3d* pElements, INT_PTR nCount);
template <> MCGEL_API void __stdcall McsCopyElements(McGePoint3d* pDest, const McGePoint3d* pSrc, INT_PTR nCount);

//==============================================================================
inline McGePoint3d::McGePoint3d() : x(0.0), y(0.0), z(0.0)
{
}
//==============================================================================
// Creates a point with the same values as `src'.
inline McGePoint3d::McGePoint3d(const McGePoint3d& src) : x(src.x), y(src.y), z(src.z)
{
}

//==============================================================================
// Creates a point intialized to ( xx, yy, zz ).
inline McGePoint3d::McGePoint3d(double xx, double yy, double zz) : x(xx), y(yy), z(zz)
{
}
//==============================================================================
inline bool McGePoint3d::operator == (const McGePoint3d& p) const
{
	return this->isEqualTo(p);
}
//==============================================================================
// This operator is the logical negation of the `==' operator.
inline bool McGePoint3d::operator != (const McGePoint3d& p) const
{
	return !this->isEqualTo(p);
}
//==============================================================================
// Returns a point such that each of the coordinates of this point
// have been multiplied by val.
inline McGePoint3d McGePoint3d::operator * (double val) const
{
	return McGePoint3d(x*val, y*val, z*val);
}
//==============================================================================
// Returns a point such that each of the coordinates of this point
// have been multiplied by val.
inline McGePoint3d operator * (double val, const McGePoint3d& p)
{
	return McGePoint3d(p.x*val, p.y*val, p.z*val);
}
//==============================================================================
// This is equivalent to the statement `p = p * val;'
// Each coordinate of this point is multiplied by val.
inline McGePoint3d& McGePoint3d::operator *= (double val)
{
	x *= val;
	y *= val;
	z *= val;
	return *this;
}
//==============================================================================
// Returns a point such that each of the coordinates of this point
// have been divided by val.
inline McGePoint3d McGePoint3d::operator / (double val) const
{
	return McGePoint3d (x/val, y/val, z/val);
}
//==============================================================================
// This is equivalent to the statement `p = p / val;'
// Each coordinate of this point is divided by val.
inline McGePoint3d& McGePoint3d::operator /= (double val)
{
	x /= val;
	y /= val;
	z /= val;
	return *this;
}
//==============================================================================
// Returns a point that is equivalent to the result of translating
// this point by the vector `v'.  (It yields the same result as if
// the vector had been cast to a translation matrix and then
// multiplied with the point.)
inline McGePoint3d McGePoint3d::operator + (const McGeVector3d& v) const
{
	return McGePoint3d (x + v.x, y + v.y, z + v.z);
}
//==============================================================================
// This is equivalent to the statement `p = p + v;'
inline McGePoint3d& McGePoint3d::operator += (const McGeVector3d& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
//==============================================================================
// This is equivalent to the statement `p + (-v);'
inline McGePoint3d McGePoint3d::operator - (const McGeVector3d& v) const
{
	return McGePoint3d (x - v.x, y - v.y, z - v.z);
}
//==============================================================================
// This is equivalent to the statement `p = p - v;'
inline McGePoint3d& McGePoint3d::operator -= (const McGeVector3d& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
//==============================================================================
// This operator returns a vector such that if `v = p1 - p0',
// then, `v' is equivalent to the translation that takes
// `p0' to `p1'.  (This point is `p1').
inline McGeVector3d McGePoint3d::operator - (const McGePoint3d& p) const
{
	return McGeVector3d (x - p.x, y - p.y, z - p.z);
}
//==============================================================================
// This operator returns the vector that would have resulted
// from the operation `p1 - McGePoint3d::kOrigin', which is
// a common operation to perform.
inline McGeVector3d McGePoint3d::asVector() const
{
	return McGeVector3d(x, y, z);
}
//==============================================================================
// This meth is faster than 'distanceTo' because we don't calculate 'sqrt' here
inline double McGePoint3d::_sqrDistanceTo(const McGePoint3d& pnt) const
{
	double dx = pnt.x - x;
	double dy = pnt.y - y;
	double dz = pnt.z - z;
	double l = dx * dx + dy * dy + dz * dz;
	return l;
}
//==============================================================================
// Sets the point to ( xx, yy, zz ).
inline McGePoint3d& McGePoint3d::set(double xx, double yy, double zz)
{
	x = xx;
	y = yy;
	z = zz;
	return *this;
}
//==============================================================================
// Indexes the point as if it were an array.  `x' is index `0',
// `y' is index `1', `z' is index `2'.
__forceinline double McGePoint3d::operator [] (unsigned int i) const
{
	return *(&x+i);
}
//==============================================================================
__forceinline double& McGePoint3d::operator [] (unsigned int i)
{
	return *(&x+i);
}
//==============================================================================

#define CM2D_UNK_X_PT 1.1e+50
#define CM2D_UNK_Y_PT 1.2e+50
#define CM2D_UNK_Z_PT 1.3e+50

extern MCGEL_API const mcsPoint gMcUnkPt;
#define UNKNOWNPOINT gMcUnkPt

MCGEL_API bool isPointKnown(const mcsPoint& pt);
MCGEL_API bool isPointUnknown(const mcsPoint& pt);
MCGEL_API void setPointToUnknown(mcsPoint& pt);
