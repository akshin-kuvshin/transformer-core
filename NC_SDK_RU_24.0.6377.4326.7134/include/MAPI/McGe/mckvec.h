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

class McGeInterval;

//==============================================================================
class McGeKnotVector
{
protected:
	McGeDoubleArray mData;
	double          mTolerance;

public:
	MCGEL_API McGeKnotVector(double eps = 1.e-9);
	MCGEL_API McGeKnotVector(int size, int growSize, double eps = 1.e-9);
	MCGEL_API McGeKnotVector(int size, const double [], double eps = 1.e-9);

	MCGEL_API McGeKnotVector(int plusMult, const McGeKnotVector& src);
	MCGEL_API McGeKnotVector(const McGeKnotVector& src);
	MCGEL_API McGeKnotVector(const McGeDoubleArray& src, double eps = 1.e-9);

	MCGEL_API ~McGeKnotVector();

	MCGEL_API McGeKnotVector& operator = (const McGeKnotVector& src);
	MCGEL_API McGeKnotVector& operator = (const McGeDoubleArray& src);


	double&      operator [] (int);
	const double operator [] (int) const;

	MCGEL_API bool isEqualTo (const McGeKnotVector& other) const;

	// Inquiry functions
	MCGEL_API double startParam() const;
	MCGEL_API double endParam() const;
	MCGEL_API int    multiplicityAt(int i) const;
	MCGEL_API int    numIntervals() const;

	// Evaluate functions
	MCGEL_API int             getInterval(int ord, double par, McGeInterval& interval ) const;
	MCGEL_API void            getDistinctKnots(McGeDoubleArray& knots) const;
	MCGEL_API bool contains(double param) const;
	MCGEL_API bool isOn(double knot) const;

	// Edit function
	MCGEL_API McGeKnotVector& reverse();
	MCGEL_API McGeKnotVector& removeAt(int);
	MCGEL_API McGeKnotVector& removeSubVector(int startIndex, int endIndex);
	MCGEL_API McGeKnotVector& insertAt(int indx, double u, int multiplicity = 1);
	MCGEL_API McGeKnotVector& insert(double u);
	MCGEL_API int             append(double val);
	MCGEL_API McGeKnotVector& append(McGeKnotVector& tail, double knotRatio = 0.);
	MCGEL_API McGeKnotVector& setRange           (double lower, double upper);
	double          tolerance          () const;
	McGeKnotVector& setTolerance       (double tol);

	MCGEL_API int split(
		double par, McGeKnotVector* pKnot1,
		int multLast, McGeKnotVector* pKnot2,
		int multFirst) const;

	// Array length.
	MCGEL_API int             length() const; // Logical length.
	MCGEL_API bool isEmpty() const;
	MCGEL_API int             logicalLength() const;
	MCGEL_API McGeKnotVector& setLogicalLength(int);
	MCGEL_API int             physicalLength() const;
	MCGEL_API McGeKnotVector& setPhysicalLength(int);

	// Automatic resizing.
	MCGEL_API int growLength  () const;
	MCGEL_API McGeKnotVector& setGrowLength(int);

	// Treat as simple array of double.
	const double* asArrayPtr() const;
	double* asArrayPtr();

	MCGEL_API McGeKnotVector& set(int size, const double [], double eps = 1.e-9);

	// возвращает индекс узла, с которого начинается ненулевой кнот-спан, такой
	// что newVal принадлежит кнот-спану [ )
	// newVal может быть равен концу кнот-спана только если newVal равен
	// конечному узлу
	// в случае неверных значений возвращается -1
	MCGEL_API int mcs_findSpan(const int degree, double newVal) const;

protected:
	bool isValid (int) const;
	friend int findKnot(const McGeKnotVector& knots, double newVal);
};
//==============================================================================
inline double McGeKnotVector::tolerance() const
{
	return mTolerance;
}
//==============================================================================
inline McGeKnotVector& McGeKnotVector::setTolerance(double eps)
{
	mTolerance = eps;
	return *this;
}
//==============================================================================
inline bool McGeKnotVector::isValid(int i) const
{
	return i >= 0 && i < mData.logicalLength();
}
//==============================================================================
inline double& McGeKnotVector::operator [] (int i)
{
	MCSASSERT(isValid(i)); 
	return mData[i]; 
}
//==============================================================================
inline const double McGeKnotVector::operator [] (int i) const
{
	MCSASSERT(isValid(i)); 
	return mData[i]; 
}
//==============================================================================
inline const double* McGeKnotVector::asArrayPtr() const
{
	return mData.asArrayPtr();
}
//==============================================================================
inline double* McGeKnotVector::asArrayPtr()
{
	return mData.asArrayPtr();
}
//==============================================================================
