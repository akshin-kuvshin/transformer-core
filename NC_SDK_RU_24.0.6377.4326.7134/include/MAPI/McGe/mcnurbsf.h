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

class McGeKnotVector;

//==============================================================================
class MCGEL_API McGeNurbSurface : public McGeSurface
{
public:
	McGeNurbSurface();

	McGeNurbSurface(
		int degreeU, int degreeV, int propsInU, int propsInV,
		int numControlPointsInU, int numControlPointsInV,
		const McGePoint3d controlPoints[],
		const double weights[],
		const McGeKnotVector& uKnots,
		const McGeKnotVector& vKnots,
		const McGeTol& tol = McGeContext::gTol);

	McGeNurbSurface(const McGeNurbSurface& nurb);

	// Assignment.
	McGeNurbSurface& operator = (const McGeNurbSurface& nurb);

	// Geometric properties.
	virtual bool isRationalInU() const;
	virtual bool isPeriodicInU(double&) const;
	virtual bool isRationalInV() const;
	virtual bool isPeriodicInV(double&) const;

	virtual int singularityInU () const;
	virtual int singularityInV () const;

	// Definition data.
	virtual int degreeInU() const;
	virtual int numControlPointsInU () const;
	virtual int degreeInV() const;
	virtual int numControlPointsInV() const;
	virtual void getControlPoints(McGePoint3dArray& points) const;
	virtual bool getWeights(McGeDoubleArray& weights) const;

	virtual int numKnotsInU() const;
	virtual void getUKnots(McGeKnotVector& uKnots) const;

	virtual int numKnotsInV() const;
	virtual void getVKnots(McGeKnotVector& vKnots) const;

	virtual void getDefinition (
		int& degreeU, int& degreeV,
		int& propsInU,	int& propsInV,
		int& numControlPointsInU,
		int& numControlPointsInV,
		McGePoint3dArray& controlPoints,
		McGeDoubleArray& weights,
		McGeKnotVector& uKnots,
		McGeKnotVector& vKnots) const;

	// Reset surface
	virtual McGeNurbSurface& set(
		int degreeU, int degreeV,
		int propsInU, int propsInV,
		int numControlPointsInU,
		int numControlPointsInV,
		const McGePoint3d controlPoints[],
		const double weights[],
		const McGeKnotVector& uKnots,
		const McGeKnotVector& vKnots,
		const McGeTol& tol = McGeContext::gTol);
};
//==============================================================================
