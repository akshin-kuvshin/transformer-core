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

//==============================================================================
class MCGEL_API McGeInterval
{
protected:
	double mLow, mHi, mTol; //	low limit, hi limit, tolerance
	bool   mfBL, mfBH; //	bounded lower, bounded upper

public:
	McGeInterval(double tol = 1.e-12);
	McGeInterval(const McGeInterval& src);
	McGeInterval(double lower, double upper, double tol = 1.e-12);
	McGeInterval(bool boundedBelow, double bound, double tol = 1.e-12);
	virtual ~McGeInterval();

	// Assignment operator.
	virtual McGeInterval&  operator = (const McGeInterval& otherInterval);

	// Get/set methods.
	virtual double lowerBound() const;
	virtual double upperBound() const;
	virtual double element() const;
	virtual void   getBounds(double& lower, double& upper) const;
	virtual double length() const;
	virtual double tolerance() const;

	virtual McGeInterval&  set(double lower, double upper);
	virtual McGeInterval&  set(bool boundedBelow, double bound);
	virtual McGeInterval&  set();
	virtual McGeInterval&  setUpper(double upper);
	virtual McGeInterval&  setLower(double lower);
	virtual McGeInterval&  setTolerance(double tol);

	// Interval editing.
	virtual void getMerge(const McGeInterval& otherInterval, McGeInterval& result) const;
	virtual int  subtract(const McGeInterval& otherInterval, McGeInterval& lInterval, McGeInterval& rInterval) const;
	virtual bool intersectWith(const McGeInterval& otherInterval, McGeInterval& result) const;

	// Interval characterization.
	virtual bool isBounded() const;
	virtual bool isBoundedAbove() const;
	virtual bool isBoundedBelow() const;
	virtual bool isUnBounded() const;
	virtual bool isSingleton() const;

	// Relation to other intervals.
	virtual bool isDisjoint(const McGeInterval& otherInterval) const;
	virtual bool contains(const McGeInterval& otherInterval) const;
	virtual bool contains(double val) const;

	// Continuity
	virtual bool isContinuousAtUpper(const McGeInterval& otherInterval) const;
	virtual bool isOverlapAtUpper(const McGeInterval& otherInterval, McGeInterval& overlap) const;
	// Equality
	virtual bool operator == (const McGeInterval& otherInterval) const;
	virtual bool operator != (const McGeInterval& otherInterval) const;
	virtual bool isEqualAtUpper(const McGeInterval& otherInterval) const;
	virtual bool isEqualAtUpper(double value) const;
	virtual bool isEqualAtLower(const McGeInterval& otherInterval) const;
	virtual bool isEqualAtLower(double value) const;

	// To be used with periodic curves
	virtual bool isPeriodicallyOn(double period, double& val);
};
//==============================================================================

struct McGeIntervalsArr : public McsArray<McGeInterval>
{
	MCGEL_API double lowerBound() const;
	MCGEL_API double upperBound() const;

	MCGEL_API bool isSingleton() const;
	MCGEL_API bool isBounded() const;
	MCGEL_API bool isBoundedAbove() const;
	MCGEL_API bool isBoundedBelow() const;
	MCGEL_API bool isUnBounded() const;
};
//==============================================================================
