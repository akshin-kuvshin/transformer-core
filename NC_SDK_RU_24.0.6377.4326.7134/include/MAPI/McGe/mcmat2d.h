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
#include "mcpnt2d.h"

class McGeVector2d;
class McGeLine2d;
class McGeTol;

//==============================================================================
// (!)the matrix is stored in a transposed state;
// Therefore, if you want to multiply A*B, use the reversed order: B*A, or A.preMultBy(B)

class MCGEL_API McGeMatrix2d
{
public:
		// The components of the matrix.
	double         entry[3][3]; // [row][column]

public:
	McGeMatrix2d();
	McGeMatrix2d(const McGeMatrix2d& src);

		// The multiplicative identity.
	static const   McGeMatrix2d   kIdentity;

		// Reset matrix.
	McGeMatrix2d&  setToIdentity();

		// Multiplication.
	McGeMatrix2d   operator *   (const McGeMatrix2d& mat) const;
	McGeMatrix2d&  operator *=  (const McGeMatrix2d& mat);
	McGeMatrix2d&  preMultBy    (const McGeMatrix2d& leftSide); // this = leftSide * this
	McGeMatrix2d&  postMultBy   (const McGeMatrix2d& rightSide); // this = this * rightSide
	McGeMatrix2d&  setToProduct (const McGeMatrix2d& mat1, const McGeMatrix2d& mat2); // this = mat1 * mat2

		// Multiplicative inverse.
	McGeMatrix2d&  invert       ();
	McGeMatrix2d   inverse      () const;

		// Test if it is a singular matrix. A singular matrix is not invertable.
	bool isSingular   (const McGeTol& tol = McGeContext::gTol) const;

		// Matrix transposition.
	McGeMatrix2d&  transposeIt  ();
	McGeMatrix2d   transpose    () const;

		// Tests for equivalence using the infinity norm.
	bool operator ==  (const McGeMatrix2d& mat) const;
	bool operator !=  (const McGeMatrix2d& mat) const;
	bool isEqualTo    (const McGeMatrix2d& mat, const McGeTol& tol = McGeContext::gTol) const;

		// Test scaling effects of matrix
	bool isUniScaledOrtho(const McGeTol& tol = McGeContext::gTol) const;
	bool isScaledOrtho(const McGeTol& tol = McGeContext::gTol) const;

		// Returns scale factor of matrix.
		// The returned scale is the square root of the maximum length of the two column vectors
	double         scale(void) const;

		// Determinant
	double         det          () const;

		// Set/retrieve translation.
	McGeMatrix2d&  setTranslation(const McGeVector2d& vec);
	McGeVector2d   translation  () const;

		// Retrieve scaling, rotation, mirror components
	bool isConformal (double& scale, double& angle, bool& isMirror, McGeVector2d& reflex) const;

		// The resulting matrix represents
		// a Local CS to World CS transformation
	McGeMatrix2d&  setCoordSystem(const McGePoint2d& origin, const McGeVector2d& e0, const McGeVector2d& e1);
	void           getCoordSystem(McGePoint2d& origin, McGeVector2d& e0, McGeVector2d& e1) const;

		// Set the matrix to be a specified transformation
	McGeMatrix2d& setToTranslation(const McGeVector2d& vec);
	McGeMatrix2d& setToRotation (double angle, const McGePoint2d& center = McGePoint2d::kOrigin);
	McGeMatrix2d& setToScaling  (double scaleAll, const McGePoint2d& center = McGePoint2d::kOrigin);
	McGeMatrix2d& setToMirroring(const McGePoint2d& pnt);
	McGeMatrix2d& setToMirroring(const McGeLine2d& line);

		// Object ARX description:
		//   Sets this matrix to the matrix which maps the coordinate system with the origin formOrigin and
		//   the axes formE0 and fromE1 to the coordinate system with the origin toOrigin and the axes toE0 and toE1. 
		// Multicad API description:
		//   Makes this matrix for an entity transformation in GCS.
		//   Apply the resulting matrix to an entity in the global coordinate system (GCS).
		//   After transformation, you'll get the modified entity in GCS
		//   (If you need to recalculate local coordinates from on CS to another, use 'setToRecalcCoordSys' method)
	McGeMatrix2d& setToAlignCoordSys(
		const McGePoint2d&  fromOrigin,
		const McGeVector2d& fromE0,
		const McGeVector2d& fromE1,
		const McGePoint2d&  toOrigin,
		const McGeVector2d& toE0,
		const McGeVector2d& toE1);

		// The method makes the matrix that enables the caller to convert
		// local coordinates between coordinate systems (CS): 'from' -> 'to'.
		// Apply this matrix to an entity in a local space of the 'from' CS.
		// After transformation, you'll get the same entity in local coordinates of 'to' system.
		// (!) The global coordinates of the transforming entity will remain the same !
	McGeMatrix2d&  setToRecalcCoordSys(
		const McGePoint2d&  fromOrigin,
		const McGeVector2d& fromE0,
		const McGeVector2d& fromE1,
		const McGePoint2d&  toOrigin,
		const McGeVector2d& toE0,
		const McGeVector2d& toE1);

		// acts like setToRecalcCoordSys does but uses GCS as a 'to' system.
	McGeMatrix2d& setToRecalcFromLocalToGlobalCoordSys(
		const McGePoint2d&  localOrigin,
		const McGeVector2d& localE0,
		const McGeVector2d& localE1);

		// acts like setToRecalcCoordSys does but uses GCS as a 'from' system.
	McGeMatrix2d& setToRecalcFromGlobalToLocalCoordSys(
		const McGePoint2d&  localOrigin,
		const McGeVector2d& localE0,
		const McGeVector2d& localE1);

		// Functions that make a 2d transformation matrix using various approaches
	static McGeMatrix2d translation    (const McGeVector2d& vec);
	static McGeMatrix2d rotation       (double angle, const McGePoint2d& center = McGePoint2d::kOrigin);
	static McGeMatrix2d scaling        (double scaleAll, const McGePoint2d& center = McGePoint2d::kOrigin);
	static McGeMatrix2d mirroring      (const McGePoint2d& pnt);
	static McGeMatrix2d mirroring      (const McGeLine2d& line);

		// Object ARX description:
		//   Returns matrix that maps the coordinate system with the origin fromOrigin and the axes fromE0 and fromE1 to
		//   the coordinate system with the origin toOrigin and the axes toE0 and toE1 
		// Multicad API description:
		//   acts like setToAlignCoordSys but returns the new matrix object
	static McGeMatrix2d alignCoordSys(
		const McGePoint2d& fromOrigin,
		const McGeVector2d& fromE0,
		const McGeVector2d& fromE1,
		const McGePoint2d&  toOrigin,
		const McGeVector2d& toE0,
		const McGeVector2d& toE1);

		// acts like setToRecalcCoordSys but returns the new matrix object
	static McGeMatrix2d recalcCoordSys(
		const McGePoint2d& fromOrigin,
		const McGeVector2d& fromE0,
		const McGeVector2d& fromE1,
		const McGePoint2d&  toOrigin,
		const McGeVector2d& toE0,
		const McGeVector2d& toE1);

		// acts like setToRecalcFromLocalToGlobalCoordSys but returns the new matrix object
	static McGeMatrix2d recalcFromLocalToGlobalCoordSys(
		const McGePoint2d&  localOrigin,
		const McGeVector2d& localE0,
		const McGeVector2d& localE1);

		// acts like setToRecalcFromGlobalToLocalCoordSys but returns the new matrix object
	static McGeMatrix2d recalcFromGlobalToLocalCoordSys(
		const McGePoint2d&  localOrigin,
		const McGeVector2d& localE0,
		const McGeVector2d& localE1);

		// For convenient access to the data.
	double         operator ()  (unsigned int, unsigned int) const;
	double&        operator ()  (unsigned int, unsigned int);
};

//==============================================================================

inline bool
McGeMatrix2d::operator == (const McGeMatrix2d& otherMatrix) const
{
	return this->isEqualTo(otherMatrix);
}

// This operator is the logical negation of the `==' operator.
inline bool
McGeMatrix2d::operator != (const McGeMatrix2d& otherMatrix) const
{
	return !this->isEqualTo(otherMatrix);
}

// Return a reference to the element in position [row][column]
// of the `entry' array.
inline double
McGeMatrix2d::operator () 
(unsigned int row,
 unsigned int column) const
{
	return entry[row][column];
}

inline double&
McGeMatrix2d::operator () 
(unsigned int row,
 unsigned int column)
{
	return entry[row][column];
}
