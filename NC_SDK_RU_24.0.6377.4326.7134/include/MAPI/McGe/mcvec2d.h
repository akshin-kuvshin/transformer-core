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

#include "mcgbl.h"
#include "mcgblabb.h"
#include "mcvec3d.h"

class McGeMatrix2d;
class McGeVector3d;
class OdGeVector2d;

class McGeVector2d
{
public:
	double x, y;

public:
	MCGEL_API McGeVector2d();
	MCGEL_API McGeVector2d(const McGeVector2d& vec);
	MCGEL_API McGeVector2d(double x, double y);

		// The additive identity, x-axis, and y-axis.
	MCGEL_API static const   McGeVector2d kIdentity;
	MCGEL_API static const   McGeVector2d kXAxis;
	MCGEL_API static const   McGeVector2d kYAxis;

		// Matrix multiplication.
	friend MCGEL_API McGeVector2d   operator * (const McGeMatrix2d& mat, const McGeVector2d& vec);
	MCGEL_API McGeVector2d&  setToProduct(const McGeMatrix2d& mat, const McGeVector2d& vec);
	MCGEL_API McGeVector2d&  transformBy (const McGeMatrix2d& leftSide);
	MCGEL_API McGeVector2d&  rotateBy    (double angle);
	MCGEL_API McGeVector2d&  mirror      (const McGeVector2d& line );

		// Scale multiplication.
	MCGEL_API McGeVector2d   operator *  (double scl) const;
	MCGEL_API friend McGeVector2d operator * (double s, const McGeVector2d& v);
	MCGEL_API McGeVector2d&  operator *= (double scl);
	MCGEL_API McGeVector2d&  setToProduct(const McGeVector2d& vec, double scl);
	MCGEL_API McGeVector2d   operator /  (double scl) const;
	MCGEL_API McGeVector2d&  operator /= (double scl);

		// Addition and subtraction of vectors.
	MCGEL_API McGeVector2d   operator +  (const McGeVector2d& vec) const;
	MCGEL_API McGeVector2d&  operator += (const McGeVector2d& vec);
	MCGEL_API McGeVector2d   operator -  (const McGeVector2d& vec) const;
	MCGEL_API McGeVector2d&  operator -= (const McGeVector2d& vec);
	MCGEL_API McGeVector2d&  setToSum    (const McGeVector2d& vec1, const McGeVector2d& vec2);
	MCGEL_API McGeVector2d   operator -  () const;
	MCGEL_API McGeVector2d&  negate      ();

		// Perpendicular vector
	MCGEL_API McGeVector2d   perpVector  () const;

		// Angle argument.
	MCGEL_API double         angle       () const;
	MCGEL_API double         angleTo	 (const McGeVector2d& vec) const;

		// Vector length operations.
	MCGEL_API McGeVector2d   normal      (const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API McGeVector2d&  normalize   (const McGeTol& tol = McGeContext::gTol);
	MCGEL_API McGeVector2d&  normalize   (const McGeTol& tol, McGeError& flag);

		// Possible errors:  k0This.  Returns object unchanged on error. 
	MCGEL_API double         length      () const;
	MCGEL_API double         lengthSqrd  () const;
	MCGEL_API bool isUnitLength(const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API bool isZeroLength(const McGeTol& tol = McGeContext::gTol) const;

		// Direction tests.
	MCGEL_API bool isParallelTo(const McGeVector2d& vec, const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API bool isParallelTo(const McGeVector2d& vec, const McGeTol& tol, McGeError& flag) const;

		// Possible errors:  k0This, k0Arg1. 
		// Returns kFalse on error.
	MCGEL_API bool isCodirectionalTo(const McGeVector2d& vec, const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API bool isCodirectionalTo(const McGeVector2d& vec, const McGeTol& tol, McGeError& flag) const;

		// Possible errors:  k0This, k0Arg1. 
		// Returns kFalse on error.
	MCGEL_API bool isPerpendicularTo(const McGeVector2d& vec, const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API bool isPerpendicularTo(const McGeVector2d& vec, const McGeTol& tol, McGeError& flag) const;

		// Possible errors:  k0This, k0Arg1. 
		// Returns kFalse on error.

		// Dot product.
	MCGEL_API double         dotProduct  (const McGeVector2d& vec) const;

		// Tests for equivalence using the Euclidean norm.
	MCGEL_API bool operator == (const McGeVector2d& vec) const;
	MCGEL_API bool operator != (const McGeVector2d& vec) const;
	MCGEL_API bool isEqualTo   (const McGeVector2d& vec, const McGeTol& tol = McGeContext::gTol) const;

		// For convenient access to the data.
	MCGEL_API double         operator [] (unsigned int i) const;
	MCGEL_API double&        operator [] (unsigned int i) ;
	MCGEL_API McGeVector2d&  set(double x, double y);
	MCGEL_API McGeVector3d asVector3d() const;
	MCGEL_API McGeVector2d orthoProject(const McGeVector2d& vec) const;

		// Convert to/from matrix form.
	MCGEL_API operator       McGeMatrix2d() const;

	operator const OdGeVector2d&() const
	{
		return *(OdGeVector2d*)this;
	}

	operator OdGeVector2d&()
	{
		return *(OdGeVector2d*)this;
	}

#ifdef MCGE_OD_SUPPORT
	McGeVector2d(const OdGeVector2d& src) : x(src.x), y(src.y)
	{
	}
#endif//#ifdef MCGE_OD_SUPPORT
};
//==================================================================================================

template <> MCGEL_API void __stdcall McsConstructElements(McGeVector2d* pElements, INT_PTR nCount);
template <> MCGEL_API void __stdcall McsDestructElements(McGeVector2d* pElements, INT_PTR nCount);
template <> MCGEL_API void __stdcall McsCopyElements(McGeVector2d* pDest, const McGeVector2d* pSrc, INT_PTR nCount);

//==================================================================================================

// Creates the identity translation vector.
inline
McGeVector2d::McGeVector2d() : x(0.0), y(0.0)
{
}

inline
McGeVector2d::McGeVector2d(const McGeVector2d& src) : x(src.x), y(src.y)
{
}

// Creates a vector intialized to ( xx, yy ).
inline
McGeVector2d::McGeVector2d(double xx, double yy) : x(xx), y(yy)
{
}

inline bool
McGeVector2d::operator == (const McGeVector2d& v) const
{
	return this->isEqualTo(v);
}

// This operator is the logical negation of the `==' operator.
inline bool
McGeVector2d::operator != (const McGeVector2d& v) const
{
	return !this->isEqualTo(v);
}

// This operator returns a vector that is the scalar product of
// `s' and this vector.
inline McGeVector2d
McGeVector2d::operator * (double s) const
{
	return McGeVector2d (x * s, y * s);
}

// This is equivalent to the statement `v = v * s'.
inline McGeVector2d&
McGeVector2d::operator *= (double s)
{
	x *= s;
	y *= s;
	return *this;
}

inline McGeVector2d&
McGeVector2d::setToProduct(const McGeVector2d& v, double s)
{
	x = s * v.x;
	y = s * v.y;
	return *this;
}

inline McGeVector2d operator * (double s, const McGeVector2d& v)
{
	return McGeVector2d (v.x * s, v.y * s);
}

// Returns a vector such that each of the coordinates of this vector
// have been divided by val.
inline McGeVector2d
McGeVector2d::operator / (double val) const
{
	return McGeVector2d (x/val, y/val);
}

// This is equivalent to the statement `v = v / val;'
// Each coordinate of this vector is divided by val.
inline McGeVector2d&
McGeVector2d::operator /= (double val)
{
	x /= val;
	y /= val;
	return *this;
}

// Returns a vector that is formed from adding the components of
// this vector with `v'.
inline McGeVector2d
McGeVector2d::operator + (const McGeVector2d& v) const
{
	return McGeVector2d (x + v.x, y + v.y);
}

// This is equivalent to the statement `thisVec = thisVec + v;'
inline McGeVector2d&
McGeVector2d::operator += (const McGeVector2d& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

// Using this operator is equivalent to using `thisVec + (-v);'
//
inline McGeVector2d
McGeVector2d::operator - (const McGeVector2d& v) const
{
	return McGeVector2d (x - v.x, y - v.y);
}

// This is equivalent to the statement `thisVec = thisVec - v;'
//
inline McGeVector2d&
McGeVector2d::operator -= (const McGeVector2d& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

inline McGeVector2d&
McGeVector2d::setToSum(const McGeVector2d& v1, const McGeVector2d& v2)
{
	x = v1.x + v2.x;
	y = v1.y + v2.y;
	return *this;
}

// Returns a vector that is formed by negating each of the components
// of this vector.
inline McGeVector2d
McGeVector2d::operator - () const
{
	return McGeVector2d (-x, -y);
}

// `v.negate()' is equivalent to the statement `v = -v;'
inline McGeVector2d&
McGeVector2d::negate()
{
	x = -x;
	y = -y;
	return *this;
}

// Returns a vector orthogonal to this vector.
inline McGeVector2d
McGeVector2d::perpVector() const
{
	return McGeVector2d (-y, x);
}

// Returns the square of the Euclidean length of this vector.
inline double
McGeVector2d::lengthSqrd() const
{
	return x*x + y*y;
}

// Returns the dot product of this vector and `v'.
inline double
McGeVector2d::dotProduct(const McGeVector2d& v) const
{
	return x * v.x + y * v.y;
}

// Sets the vector to ( xx, yy ).
inline McGeVector2d&
McGeVector2d::set(double xx, double yy)
{
	x = xx;
	y = yy;
	return *this;
}

// Indexes the vector as if it were an array.  `x' is index `0',
// `y' is index `1'.
inline double
McGeVector2d::operator [] (unsigned int i) const
{
	return *(&x+i);
}

inline double&
McGeVector2d::operator [] (unsigned int i)
{
	return *(&x+i);
}

inline McGeVector2d McGeVector2d::orthoProject(const McGeVector2d& vec) const
{
	McGeVector2d perp = vec.perpVector().normal();
	McGeVector2d res = perp * perp.dotProduct(*this);
	return res;
}
