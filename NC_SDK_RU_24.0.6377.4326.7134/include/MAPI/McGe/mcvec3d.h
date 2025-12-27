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

#include "mctol.h"

class McGeMatrix3d;
class McGeVector2d;
class McGePlane;
class McGePlanarEnt;

class OdGeVector3d;

//==============================================================================
class McGeVector3d
{
public:
	double x, y, z;

public:
	DECLARE_OBJ_NEWDEL;
	MCGEL_API McGeVector3d();
	MCGEL_API McGeVector3d(const McGeVector3d& vec);
	MCGEL_API McGeVector3d(double x, double y, double z);
	MCGEL_API McGeVector3d(const McGePlanarEnt&, const McGeVector2d&);

	// The additive identity, x-axis, y-axis, and z-axis.
	MCGEL_API static const   McGeVector3d kIdentity;
	MCGEL_API static const   McGeVector3d kXAxis;
	MCGEL_API static const   McGeVector3d kYAxis;
	MCGEL_API static const   McGeVector3d kZAxis;

	// Multiplication with matrices.
	friend MCGEL_API McGeVector3d operator * (const McGeMatrix3d& mat, const McGeVector3d& vec);
	MCGEL_API McGeVector3d&  setToProduct(const McGeMatrix3d& mat, const McGeVector3d& vec);

	MCGEL_API McGeVector3d&  transformBy (const McGeMatrix3d& leftSide);
	MCGEL_API McGeVector3d&  rotateBy    (double ang , const McGeVector3d& axis );
	MCGEL_API McGeVector3d&  mirror      (const McGeVector3d& normalToPlane);
	MCGEL_API McGeVector2d   convert2d   (const McGePlanarEnt& pln) const;

	// Multiplication by scalar.
	MCGEL_API McGeVector3d   operator *  (double scl) const;
	friend McGeVector3d operator * (double s, const McGeVector3d& v);

	MCGEL_API McGeVector3d&  operator *= (double scl);
	MCGEL_API McGeVector3d&  setToProduct(const McGeVector3d& vec, double scl);
	MCGEL_API McGeVector3d   operator /  (double scl) const;
	MCGEL_API McGeVector3d&  operator /= (double scl);

	// Addition and subtraction of vectors.
	MCGEL_API McGeVector3d   operator +  (const McGeVector3d& vec) const;
	MCGEL_API McGeVector3d&  operator += (const McGeVector3d& vec);
	MCGEL_API McGeVector3d   operator -  (const McGeVector3d& vec) const;
	MCGEL_API McGeVector3d&  operator -= (const McGeVector3d& vec);
	MCGEL_API McGeVector3d&  setToSum    (const McGeVector3d& vec1, const McGeVector3d& vec2);
	MCGEL_API McGeVector3d   operator -  () const;
	MCGEL_API McGeVector3d&  negate();
	MCGEL_API McGeVector2d   asVector2d() const;

		// Perpendicular vector
	MCGEL_API McGeVector3d   perpVector  () const;

		// Angle argument.
	MCGEL_API double         angleTo     (const McGeVector3d& vec) const;
	MCGEL_API double         angleTo     (const McGeVector3d& vec, const McGeVector3d& refVec) const;
	MCGEL_API double         angleOnPlane(const McGePlanarEnt& pln) const;

		// Vector length operations.
	MCGEL_API McGeVector3d   normal      (const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API McGeVector3d&  normalize   (const McGeTol& tol = McGeContext::gTol);
	MCGEL_API McGeVector3d&  normalize   (const McGeTol& tol, McGeError& flag);

		// strict normalization
	MCGEL_API McGeVector3d mcs_normal() const;

		// Possible errors:  k0This.  Returns object unchanged on error. 
	MCGEL_API double         length      () const;
	MCGEL_API double         lengthSqrd  () const;
	MCGEL_API bool isUnitLength(const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API bool isZeroLength(const McGeTol& tol = McGeContext::gTol) const;

		// Direction tests.
	MCGEL_API bool isParallelTo(const McGeVector3d& vec, const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API bool isParallelTo(const McGeVector3d& vec, const McGeTol& tol, McGeError& flag) const;

		// Possible errors:  k0This, k0Arg1. 
		// Returns kFalse on error.
	MCGEL_API bool isCodirectionalTo(const McGeVector3d& vec, const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API bool isCodirectionalTo(const McGeVector3d& vec, const McGeTol& tol, McGeError& flag) const;
			// Possible errors: k0Arg1, k0Arg2, kPerpendicularArg1Arg2. 
			// Returns copy of unchanged object on error.
	MCGEL_API bool isPerpendicularTo(const McGeVector3d& vec, const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API bool isPerpendicularTo(const McGeVector3d& vec, const McGeTol& tol, McGeError& flag) const;
			// Possible errors: k0Arg1, k0Arg2, kPerpendicularArg1Arg2. 
			// Returns copy of unchanged object on error.

		// Dot and Cross product.
	MCGEL_API double         dotProduct  (const McGeVector3d& vec) const;
	MCGEL_API McGeVector3d   crossProduct(const McGeVector3d& vec) const;

		// Calculate rotation.
	MCGEL_API McGeMatrix3d   rotateTo(const McGeVector3d& vec, const McGeVector3d& axis = McGeVector3d::kIdentity) const;

		// Projection on plane
	MCGEL_API McGeVector3d   project(const McGeVector3d& planeNormal, const McGeVector3d& projectDirection) const;
	MCGEL_API McGeVector3d   project(
		const McGeVector3d& planeNormal,
		const McGeVector3d& projectDirection,  
		const McGeTol& tol, McGeError& flag) const;

		// Possible errors: k0Arg1, k0Arg2, kPerpendicularArg1Arg2. 
		// Returns copy of unchanged object on error.
	MCGEL_API McGeVector3d   orthoProject (const McGeVector3d& planeNormal) const;
	MCGEL_API McGeVector3d   orthoProject (const McGeVector3d& planeNormal, const McGeTol& tol, McGeError& flag) const;
		// Possible errors:  k0Arg1.
		// Returns a copy of unchanged object on error. 

		// Tests for equivalence using the Euclidean norm.
	MCGEL_API bool operator == (const McGeVector3d& vec) const;
	MCGEL_API bool operator != (const McGeVector3d& vec) const;
	MCGEL_API bool isEqualTo   (const McGeVector3d& vec, const McGeTol& tol = McGeContext::gTol) const;

	// For convenient access to the data.
	MCGEL_API double operator [] (unsigned int i) const;
	MCGEL_API double& operator [] (unsigned int i);
	MCGEL_API unsigned int largestElement() const;
	MCGEL_API McGeVector3d&  set         (double x, double y, double z);
	MCGEL_API McGeVector3d&  set         (const McGePlanarEnt& pln, const McGeVector2d& vec);

	// Convert to the matrix of translation.
	MCGEL_API operator       McGeMatrix3d() const;

	operator const OdGeVector3d&() const
	{
		return *(OdGeVector3d*)this;
	}

	operator OdGeVector3d&()
	{
		return *(OdGeVector3d*)this;
	}

#ifdef MCGE_OD_SUPPORT
	McGeVector3d(const OdGeVector3d& src) : x(src.x), y(src.y), z(src.z)
	{
	}
#endif//#ifdef MCGE_OD_SUPPORT
};
//==================================================================================================

template <> MCGEL_API void __stdcall McsConstructElements(McGeVector3d* pElements, INT_PTR nCount);
template <> MCGEL_API void __stdcall McsDestructElements(McGeVector3d* pElements, INT_PTR nCount);
template <> MCGEL_API void __stdcall McsCopyElements(McGeVector3d* pDest, const McGeVector3d* pSrc, INT_PTR nCount);

//==================================================================================================

// Creates the identity vector.
inline McGeVector3d::McGeVector3d() : x(0.0), y(0.0), z(0.0)
{
}
//==============================================================================
inline McGeVector3d::McGeVector3d(const McGeVector3d& src) : x(src.x),y(src.y),z(src.z)
{
}
//==============================================================================
// Creates a vector intialized to ( xx, yy, zz ).
inline McGeVector3d::McGeVector3d(double xx, double yy, double zz) : x(xx),y(yy),z(zz)
{
}
//==============================================================================
inline bool McGeVector3d::operator == (const McGeVector3d& v) const
{
	return this->isEqualTo(v);
}
//==============================================================================
// This operator is the logical negation of the `==' operator.
inline bool McGeVector3d::operator != (const McGeVector3d& v) const
{
	return !this->isEqualTo(v);
}
//==============================================================================
// Returns a vector that is formed from adding the components of
// this vector with `v'.
inline McGeVector3d McGeVector3d::operator + (const McGeVector3d& v) const
{
	return McGeVector3d (x + v.x, y + v.y, z + v.z);
}
//==============================================================================
// This is equivalent to the statement `thisVec = thisVec + v;'
inline McGeVector3d& McGeVector3d::operator += (const McGeVector3d& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
//==============================================================================
// Using this operator is equivalent to using `thisVec + (-v);'
inline McGeVector3d McGeVector3d::operator - (const McGeVector3d& v) const
{
	return McGeVector3d (x - v.x, y - v.y, z - v.z);
}
//==============================================================================
// This is equivalent to the statement `thisVec = thisVec - v;'
inline McGeVector3d& McGeVector3d::operator -= (const McGeVector3d& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
//==============================================================================
inline McGeVector3d& McGeVector3d::setToSum(const McGeVector3d& v1, const McGeVector3d& v2)
{
	x = v1.x + v2.x;
	y = v1.y + v2.y;
	z = v1.z + v2.z;
	return *this;
}
//==============================================================================
// Returns a vector that is formed by negating each of the components
// of this vector.
inline McGeVector3d McGeVector3d::operator - () const
{
	return McGeVector3d (-x, -y, -z);
}
//==============================================================================
// `v.negate()' is equivalent to the statement `v = -v;'
inline McGeVector3d& McGeVector3d::negate()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}
//==============================================================================
// This operator returns a vector that is the scalar product of
// `s' and this vector.
inline McGeVector3d McGeVector3d::operator * (double s) const
{
	return McGeVector3d (x * s, y * s, z * s);
}
//==============================================================================
inline McGeVector3d operator * (double s, const McGeVector3d& v)
{
	return McGeVector3d (v.x * s, v.y * s, v.z * s);
}
//==============================================================================
// This is equivalent to the statement `v = v * s'.
inline McGeVector3d& McGeVector3d::operator *= (double s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
//==============================================================================
inline McGeVector3d& McGeVector3d::setToProduct(const McGeVector3d& v, double s)
{
	x = s * v.x;
	y = s * v.y;
	z = s * v.z;
	return *this;
}
//==============================================================================
// Returns a vector such that each of the coordinates of this vector
// have been divided by val.
inline McGeVector3d McGeVector3d::operator / (double val) const
{
	return McGeVector3d (x/val, y/val, z/val);
}
//==============================================================================
// This is equivalent to the statement `v = v / val;'
// Each coordinate of this vector is divided by val.
inline McGeVector3d& McGeVector3d::operator /= (double val)
{
	x /= val;
	y /= val;
	z /= val;
	return *this;
}
//==============================================================================
// Returns the square of the Euclidean length of this vector.
inline double McGeVector3d::lengthSqrd() const
{
	return x*x + y*y + z*z;
}
//==============================================================================
// Returns the dot product of this vector and `v'.
inline double McGeVector3d::dotProduct(const McGeVector3d& v) const
{
	return x * v.x + y * v.y + z * v.z;
}
//==============================================================================
// Sets the vector to ( xx, yy, zz ).
inline McGeVector3d& McGeVector3d::set(double xx, double yy, double zz)
{
	x = xx;
	y = yy;
	z = zz;
	return *this;
}
//==============================================================================
// Indexes the vector as if it were an array.  `x' is index `0',
// `y' is index `1' and `z' is index `2'.
inline double McGeVector3d::operator [] (unsigned int i) const
{
	return *(&x+i);
}
//==============================================================================
inline double& McGeVector3d::operator [] (unsigned int i)
{
	return *(&x+i);
}
//==============================================================================
