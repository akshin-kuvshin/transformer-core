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
#include "mcpnt3d.h"

class McGeLine3d;
class McGeVector3d;
class McGePlane;
class McGeTol;

class OdGeMatrix3d;

#ifndef _4DBL_
	#define _4DBL_
	struct __fourDoubles {double val[4];};
#endif

//==============================================================================
// (!)the matrix is stored in a transposed state;
// Therefore, if you want to multiply A*B, use the reversed order: B*A, or A.preMultBy(B)

class McGeMatrix3d
{
public:
		// The components of the matrix.
	double entry[4][4];    // [row][column]

public:
	MCGEL_API McGeMatrix3d();
	MCGEL_API McGeMatrix3d(const McGeMatrix3d& src);

		// The multiplicative identity.
	MCGEL_API static const McGeMatrix3d    kIdentity;

		// Reset matrix.
	MCGEL_API McGeMatrix3d&  setToIdentity();

		// Multiplication.
	MCGEL_API McGeMatrix3d   operator *      (const McGeMatrix3d& mat) const;
	MCGEL_API McGeMatrix3d&  operator *=     (const McGeMatrix3d& mat);
	MCGEL_API McGeMatrix3d&  preMultBy       (const McGeMatrix3d& leftSide); // this = leftSide * this
	MCGEL_API McGeMatrix3d&  postMultBy      (const McGeMatrix3d& rightSide); // this = this * rightSide
	MCGEL_API McGeMatrix3d&  setToProduct    (const McGeMatrix3d& mat1, const McGeMatrix3d& mat2); // this = mat1 * mat2

		// Multiplicative inverse.
	MCGEL_API McGeMatrix3d&  invert          ();
	MCGEL_API McGeMatrix3d   inverse         () const;

		// Test if it is a singular matrix.  A singular matrix is not invertable.
	MCGEL_API bool isSingular(const McGeTol& tol = McGeContext::gTol) const;

		// Matrix transposition.
	MCGEL_API McGeMatrix3d&  transposeIt     ();
	MCGEL_API McGeMatrix3d   transpose       () const;

		// Tests for equivalence using the infinity norm.
	MCGEL_API bool operator == (const McGeMatrix3d& mat) const;
	MCGEL_API bool operator != (const McGeMatrix3d& mat) const;
	MCGEL_API bool isEqualTo(const McGeMatrix3d& mat, const McGeTol& tol = McGeContext::gTol) const;

		// Test scaling effects of matrix
	MCGEL_API bool isUniScaledOrtho(const McGeTol& tol = McGeContext::gTol) const;
	MCGEL_API bool isScaledOrtho   (const McGeTol& tol = McGeContext::gTol) const;

		// Determinant
	MCGEL_API double         det             () const;

		// Set/retrieve translation.
	MCGEL_API McGeMatrix3d&  setTranslation  (const McGeVector3d& vec);
	MCGEL_API McGeVector3d   translation     () const;

		// The resulting matrix represents
		// a Local CS to World CS transformation
	MCGEL_API McGeMatrix3d&  setCoordSystem(
		const McGePoint3d& origin,
		const McGeVector3d& xAxis,
		const McGeVector3d& yAxis,
		const McGeVector3d& zAxis);

	MCGEL_API void getCoordSystem(
		McGePoint3d& origin,
		McGeVector3d& xAxis,
		McGeVector3d& yAxis,
		McGeVector3d& zAxis) const;

		// Set the matrix to be a specified transformation
	MCGEL_API McGeMatrix3d&  setToTranslation(const McGeVector3d& vec);
	MCGEL_API McGeMatrix3d&  setToRotation(double angle, const McGeVector3d& axis, const McGePoint3d& center = McGePoint3d::kOrigin);
	MCGEL_API McGeMatrix3d&  setToScaling    (double scaleAll, const McGePoint3d& center = McGePoint3d::kOrigin);
	MCGEL_API McGeMatrix3d&  setToMirroring  (const McGePlane& pln);
	MCGEL_API McGeMatrix3d&  setToMirroring  (const McGePoint3d& pnt);
	MCGEL_API McGeMatrix3d&  setToMirroring  (const McGeLine3d& line);
	MCGEL_API McGeMatrix3d&  setToProjection (const McGePlane& projectionPlane, const McGeVector3d& projectDir);

		// Object ARX description:
		//   Sets this matrix of the matrix which maps coordinate system with the origin fromOrigin and
		//   the axes fromXAis, fromYAxis and fromZAxis to coordinate system with
		//   the origin toOrigin and the axes toXAxis, toYAxis, and toZAxis.
		// Multicad API description:
		//   Makes this matrix for an entity transformation in GCS.
		//   Apply the resulting matrix to an entity in the global coordinate system (GCS).
		//   After transformation, you'll get the modified entity in GCS
		//   (If you need to recalculate local coordinates from on CS to another, use 'setToRecalcCoordSys' method)
	MCGEL_API McGeMatrix3d&  setToAlignCoordSys(
		const McGePoint3d& fromOrigin,
		const McGeVector3d& fromXAxis,
		const McGeVector3d& fromYAxis,
		const McGeVector3d& fromZAxis,
		const McGePoint3d& toOrigin,
		const McGeVector3d& toXAxis,
		const McGeVector3d& toYAxis,
		const McGeVector3d& toZAxis);

		// The method makes the matrix that enables the caller to convert
		// local coordinates between coordinate systems (CS): 'from' -> 'to'.
		// Apply this matrix to an entity in a local space of the 'from' CS.
		// After transformation, you'll get the same entity in local coordinates of 'to' system.
		// (!) The global coordinates of the transforming entity will remain the same !
	MCGEL_API McGeMatrix3d&  setToRecalcCoordSys(
		const McGePoint3d& fromOrigin,
		const McGeVector3d& fromXAxis,
		const McGeVector3d& fromYAxis,
		const McGeVector3d& fromZAxis,
		const McGePoint3d& toOrigin,
		const McGeVector3d& toXAxis,
		const McGeVector3d& toYAxis,
		const McGeVector3d& toZAxis);

		// acts like setToRecalcCoordSys does but uses GCS as a 'to' system.
	MCGEL_API McGeMatrix3d& setToRecalcFromLocalToGlobalCoordSys(
		const McGePoint3d&  localOrigin,
		const McGeVector3d& localXAxis,
		const McGeVector3d& localYAxis,
		const McGeVector3d& localZAxis);

		// acts like setToRecalcCoordSys does but uses GCS as a 'from' system.
	MCGEL_API McGeMatrix3d& setToRecalcFromGlobalToLocalCoordSys(
		const McGePoint3d&  localOrigin,
		const McGeVector3d& localXAxis,
		const McGeVector3d& localYAxis,
		const McGeVector3d& localZAxis);

	MCGEL_API McGeMatrix3d& setToWorldToPlane(const McGeVector3d& normal);
	MCGEL_API McGeMatrix3d& setToWorldToPlane(const McGePlane& plane);
	MCGEL_API McGeMatrix3d& setToPlaneToWorld(const McGeVector3d& normal);
	MCGEL_API McGeMatrix3d& setToPlaneToWorld(const McGePlane& plane);

		// Similar to above, but creates matrix on the stack.
	MCGEL_API static McGeMatrix3d translation(const McGeVector3d& vec);
	MCGEL_API static McGeMatrix3d rotation(double angle, const McGeVector3d& axis,const McGePoint3d& center= McGePoint3d::kOrigin);
	MCGEL_API static McGeMatrix3d scaling(double scaleAll, const McGePoint3d& center = McGePoint3d::kOrigin);
	MCGEL_API static McGeMatrix3d mirroring(const McGePlane& pln);
	MCGEL_API static McGeMatrix3d mirroring(const McGePoint3d& pnt);
	MCGEL_API static McGeMatrix3d mirroring(const McGeLine3d& line);
	MCGEL_API static McGeMatrix3d projection(const McGePlane& projectionPlane, const McGeVector3d& projectDir);

		// Object ARX description:
		//   Returns matrix that maps coordinate system with the origin fromOrigin and the axes fromXAxis, fromYAxis, and fromZAxis
		//   to coordinate system with the origin toOrigin and the axes toXAxis, toYAxis, and toZAxis 
		// Multicad API description:
		//   acts like setToAlignCoordSys but returns the new matrix object
	MCGEL_API static McGeMatrix3d alignCoordSys(
		const McGePoint3d&  fromOrigin,
		const McGeVector3d& fromXAxis,
		const McGeVector3d& fromYAxis,
		const McGeVector3d& fromZAxis,
		const McGePoint3d&  toOrigin,
		const McGeVector3d& toXAxis,
		const McGeVector3d& toYAxis,
		const McGeVector3d& toZAxis);

		// acts like setToRecalcCoordSys but returns the new matrix object
	MCGEL_API static McGeMatrix3d recalcCoordSys(
		const McGePoint3d&  fromOrigin,
		const McGeVector3d& fromXAxis,
		const McGeVector3d& fromYAxis,
		const McGeVector3d& fromZAxis,
		const McGePoint3d&  toOrigin,
		const McGeVector3d& toXAxis,
		const McGeVector3d& toYAxis,
		const McGeVector3d& toZAxis);

		// acts like setToRecalcFromLocalToGlobalCoordSys but returns the new matrix object
	MCGEL_API static McGeMatrix3d recalcFromLocalToGlobalCoordSys(
		const McGePoint3d&  localOrigin,
		const McGeVector3d& localXAxis,
		const McGeVector3d& localYAxis,
		const McGeVector3d& localZAxis);

		// acts like setToRecalcFromGlobalToLocalCoordSys but returns the new matrix object
	MCGEL_API static McGeMatrix3d recalcFromGlobalToLocalCoordSys(
		const McGePoint3d&  localOrigin,
		const McGeVector3d& localXAxis,
		const McGeVector3d& localYAxis,
		const McGeVector3d& localZAxis);

	MCGEL_API static McGeMatrix3d   worldToPlane    (const McGeVector3d& normal);
	MCGEL_API static McGeMatrix3d   worldToPlane    (const McGePlane&);
	MCGEL_API static McGeMatrix3d   planeToWorld    (const McGeVector3d& normal);
	MCGEL_API static McGeMatrix3d   planeToWorld    (const McGePlane&);

	// Returns scale factor of matrix. The returned scale is the square root of
	// the maximum length of the three column vectors
	MCGEL_API double scale(void) const;

	// Takes the absolute value of each element of the upper 3x3 of the matrix and returns
	// the absolute value of the largest such element
	MCGEL_API double norm() const;

	MCGEL_API McGeMatrix2d convertToLocal(McGeVector3d& normal, double& elev) const;

		// For convenient access to the data.
	MCGEL_API double operator ()(unsigned int, unsigned int) const;
	MCGEL_API double& operator()(unsigned int, unsigned int);

	MCGEL_API bool inverse(McGeMatrix3d& inv, double tol) const;

	operator const OdGeMatrix3d&() const
	{
		return *(OdGeMatrix3d*)this;
	}

	operator OdGeMatrix3d&()
	{
		return *(OdGeMatrix3d*)this;
	}

#ifdef MCGE_OD_SUPPORT
	McGeMatrix3d(const OdGeMatrix3d& src)
	{
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				entry[i][j] = od.entry[i][j];
	}
#endif//#ifdef MCGE_OD_SUPPORT

	// MCS-stuff

	MCGEL_API bool setCoordSystemPVV(
		IN const McGePoint3d&  origin,
		IN const McGeVector3d& verDir,
		IN const McGeVector3d& verPlane);

	MCGEL_API void getCoordSystemPVV(
		OUT McGePoint3d&  origin,
		OUT McGeVector3d& verDir,
		OUT McGeVector3d& verPlane);

	MCGEL_API bool setToRelative(IN const McGeMatrix3d& from, IN const McGeMatrix3d& to);

	bool isIdentical(const McGeTol& tol = McGeContext::gTol) const {
		return isEqualTo(McGeMatrix3d::kIdentity, tol);
	}

	// Test mirror effects of matrix
	MCGEL_API bool isMirroring() const;

	// Checks if the tfm's CS is parallel to XY
	MCGEL_API bool isXyParallelTfm() const;
};

typedef McGeMatrix3d mcsMatrix;

//==============================================================================

inline bool
McGeMatrix3d::operator == (const McGeMatrix3d& otherMatrix) const
{
	return this->isEqualTo(otherMatrix);
}

// This operator is the logical negation of the `==' operator.
inline bool
McGeMatrix3d::operator != (const McGeMatrix3d& otherMatrix) const
{
	return !this->isEqualTo(otherMatrix);
}

// Return the element in position [row][column] of the `entry' array.
inline double
McGeMatrix3d::operator () 
(unsigned int row,
 unsigned int column) const
{
	return entry[row][column];
}

inline double&
McGeMatrix3d::operator () 
(unsigned int row,
 unsigned int column)
{
	return entry[row][column];
}
//==============================================================================
