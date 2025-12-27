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

#include "mcvec2d.h"

class McGeMatrix2d;
class McGeVector2d;
class McGeLinearEnt2d;
class McGeLine2d;

class OdGePoint2d;

//==================================================================================================
class McGePoint2d
{
public:
		// The co-ordinates of the point.
	double x, y;

public:
	MCGEL_API McGePoint2d();
	MCGEL_API McGePoint2d(const McGePoint2d& pnt);
	MCGEL_API McGePoint2d(double x, double y);

		// The origin, or (0, 0).
	MCGEL_API static const   McGePoint2d kOrigin;

	// Matrix multiplication.
	friend MCGEL_API McGePoint2d operator * (const McGeMatrix2d& mat, const McGePoint2d& pnt);
	MCGEL_API McGePoint2d&   setToProduct(const McGeMatrix2d& mat, const McGePoint2d& pnt);
	MCGEL_API McGePoint2d&   transformBy (const McGeMatrix2d& leftSide);
	MCGEL_API McGePoint2d&   rotateBy    (double angle, const McGePoint2d& wrtPoint = McGePoint2d::kOrigin); 
	MCGEL_API McGePoint2d&   mirror      (const McGeLine2d& line);
	MCGEL_API McGePoint2d&   scaleBy     (double scaleFactor, const McGePoint2d& wrtPoint = McGePoint2d::kOrigin);

		// Scale multiplication.
	MCGEL_API McGePoint2d    operator *  (double) const;
	MCGEL_API friend
	McGePoint2d    operator *  (double, const McGePoint2d& scl);
	MCGEL_API McGePoint2d&   operator *= (double scl);
	MCGEL_API McGePoint2d    operator /  (double scl) const;
	MCGEL_API McGePoint2d&   operator /= (double scl);
	MCGEL_API McGePoint2d&   operator =  (const McGePoint2d& pnt);

		// Translation by a vector.
	MCGEL_API McGePoint2d    operator +  (const McGeVector2d& vec) const;
	MCGEL_API McGePoint2d&   operator += (const McGeVector2d& vec);
	MCGEL_API McGePoint2d    operator -  (const McGeVector2d& vec) const;
	MCGEL_API McGePoint2d&   operator -= (const McGeVector2d& vec);
	MCGEL_API McGePoint2d&   setToSum    (const McGePoint2d& pnt, const McGeVector2d& vec);

		// Get vector between two points.
	MCGEL_API McGeVector2d   operator -  (const McGePoint2d& pnt) const;
	MCGEL_API McGeVector2d   asVector() const;
	MCGEL_API McGePoint3d    asPoint3d() const;

		// Distance to other geometric objects.
	MCGEL_API double         distanceTo  (const McGePoint2d& pnt) const;

		// Tests for equivalence using the Euclidean norm.
	MCGEL_API bool operator == (const McGePoint2d& pnt) const;
	MCGEL_API bool operator != (const McGePoint2d& pnt) const;
	MCGEL_API bool isEqualTo   (const McGePoint2d& pnt, const McGeTol& tol = McGeContext::gTol) const;

		// For convenient access to the data.
	MCGEL_API double         operator [] (unsigned int i) const;
	MCGEL_API double&        operator [] (unsigned int idx);
	MCGEL_API McGePoint2d&   set(double x, double y);
	MCGEL_API McGePoint2d    project(const McGeLine2d& line) const;

	operator const OdGePoint2d&() const
	{
		return *(OdGePoint2d*)this;
	}

	operator OdGePoint2d&()
	{
		return *(OdGePoint2d*)this;
	}

#ifdef MCGE_OD_SUPPORT
	McGePoint2d(const OdGePoint2d& src) : x(src.x), y(src.y)
	{
	}
#endif//#ifdef MCGE_OD_SUPPORT
};
//==================================================================================================

template <> MCGEL_API void __stdcall McsConstructElements(McGePoint2d* pElements, INT_PTR nCount);
template <> MCGEL_API void __stdcall McsDestructElements(McGePoint2d* pElements, INT_PTR nCount);
template <> MCGEL_API void __stdcall McsCopyElements(McGePoint2d* pDest, const McGePoint2d* pSrc, INT_PTR nCount);

//==================================================================================================

// Creates a point at the origin.
inline
McGePoint2d::McGePoint2d() : x(0.0), y(0.0)
{
}

inline
McGePoint2d::McGePoint2d(const McGePoint2d& src) : x(src.x), y(src.y)
{
}

// Creates a point intialized to ( xx, yy ).
inline
McGePoint2d::McGePoint2d(double xx, double yy) : x(xx), y(yy)
{
}

inline bool
McGePoint2d::operator == (const McGePoint2d& p) const
{
	return this->isEqualTo(p);
}

// This operator is the logical negation of the `==' operator.
inline bool
McGePoint2d::operator != (const McGePoint2d& p) const
{
	return !this->isEqualTo(p);
}

// Returns a point such that each of the coordinates of this point
// have been multiplied by val.
inline McGePoint2d
McGePoint2d::operator * (double val) const
{
	return McGePoint2d(x*val, y*val);
}

// Returns a point such that each of the coordinates of this point
// have been multiplied by val.
inline McGePoint2d
operator * (double val, const McGePoint2d& p)
{
	return McGePoint2d(p.x*val, p.y*val);
}

// This is equivalent to the statement `p = p * val;'
// Each coordinate of this point is multiplied by val.
inline McGePoint2d&
McGePoint2d::operator *= (double val)
{
	x *= val;
	y *= val;
	return *this;
}

// Returns a point such that each of the coordinates of this point
// have been divided by val.
inline McGePoint2d
McGePoint2d::operator / (double val) const
{
	return McGePoint2d (x/val, y/val);
}

// This is equivalent to the statement `p = p / val;'
// Each coordinate of this point is divided by val.
inline McGePoint2d&
McGePoint2d::operator /= (double val)
{
	x /= val;
	y /= val;
	return *this;
}

// Returns a point that is equivalent to the result of translating
// this point by the vector `v'.  (It yields the same result as if
// the vector had been cast to a translation matrix and then
// multiplied with the point.)
inline McGePoint2d
McGePoint2d::operator + (const McGeVector2d& v) const
{
	return McGePoint2d(x + v.x, y + v.y);
}

// This is equivalent to the statement `p = p + v;'
inline McGePoint2d&
McGePoint2d::operator += (const McGeVector2d& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

// This is equivalent to the statement `p + (-v);'
inline McGePoint2d
McGePoint2d::operator - (const McGeVector2d& v) const
{
	return McGePoint2d(x - v.x, y - v.y);
}

// This is equivalent to the statement `p = p - v;'
inline McGePoint2d&
McGePoint2d::operator -= (const McGeVector2d& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

// This operator returns a vector such that if `v = p1 - p0',
// then, `v' is equivalent to the translation that takes
// `p0' to `p1'.  (This point is `p1').
inline McGeVector2d
McGePoint2d::operator - (const McGePoint2d& p) const
{
	return McGeVector2d(x - p.x, y - p.y);
}

// This operator returns the vector that would have resulted
// from the operation `p1 - McGePoint2d::kOrigin', which is
// a common operation to perform.
inline McGeVector2d
McGePoint2d::asVector() const
{
	return McGeVector2d(x, y);
}

// Sets the point to ( xx, yy ).
inline McGePoint2d&
McGePoint2d::set(double xx, double yy)
{
	x = xx;
	y = yy;
	return *this;
}

//     Indexes the point as if it were an array.  `x' is index `0',
//     `y' is index `1'.
inline double
McGePoint2d::operator [] (unsigned int i) const
{
	return *(&x+i);
}

inline double&
McGePoint2d::operator [] (unsigned int i)
{
	return *(&x+i);
}
