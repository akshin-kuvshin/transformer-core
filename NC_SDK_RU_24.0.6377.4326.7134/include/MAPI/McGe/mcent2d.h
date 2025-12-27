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

#include "mcpnt2d.h"

class McEnt2dImpl;
class McGeLine2d;
struct IMtStream;

//==============================================================================
class MCGEL_API McGeEntity2d
{
private:
	McEnt2dImpl* m_pImpl;

protected:
	void               setImpl(McEnt2dImpl*);
	McEnt2dImpl*       getImpl();
	const McEnt2dImpl* getImpl() const;

protected:
	McGeEntity2d();
	McGeEntity2d(const McGeEntity2d& ent);
public:
	DECLARE_OBJ_NEWDEL;
	virtual ~McGeEntity2d();

	// Run time type information.
	virtual bool isKindOf(McGe::EntityId entType) const;
	virtual McGe::EntityId type() const;

	// Make a copy of the entity.
	virtual McGeEntity2d* copy() const;
	virtual McGeEntity2d& operator =  (const McGeEntity2d& entity);

	// Equivalence
	virtual bool operator == (const McGeEntity2d& entity) const;
	virtual bool operator != (const McGeEntity2d& entity) const;
	virtual bool isEqualTo(const McGeEntity2d& ent, const McGeTol& tol = McGeContext::gTol) const;

	// Matrix multiplication
	virtual McGeEntity2d& transformBy(const McGeMatrix2d& xfm);
	virtual McGeEntity2d& translateBy(const McGeVector2d& translateVec);
	virtual McGeEntity2d& rotateBy(double angle, const McGePoint2d& center = McGePoint2d::kOrigin);
	virtual McGeEntity2d& mirror(const McGeLine2d& line);
	virtual McGeEntity2d& mirror(const McGePoint2d& pnt);
	virtual McGeEntity2d& scaleBy(double scaleFactor, const McGePoint2d& wrtPoint = McGePoint2d::kOrigin);

	//Reading and writing geometry library objects
	bool mcs_write(IMtStream* pStream) const;
	bool mcs_read(IMtStream* pStream);
	bool mcs_write(LPCTSTR lpszFileName) const;
	static McGeEntity2d* mcs_read(LPCTSTR lpszFileName);

	// Writes the entity type and the entity itself into a stream.
	static bool mcs_writeEnt(const McGeEntity2d* pEnt, IMtStream* pStream);

	// Restores the previously saved by method mcs_writeEnt entity from a stream.
	static McGeEntity2d* mcs_readEnt(IMtStream* pStream);

	// Point containment
	virtual bool isOn(const McGePoint2d& pnt, const McGeTol& tol = McGeContext::gTol) const;

	friend McEnt2dImpl* MCGE_IMPLENT2D(const McGeEntity2d*);

	friend class McPointOnCurve2dImpl;
	friend class McGeLinearEnt2d;
	friend class McGeBoundBlock2d;
	friend class McLinearEnt2dImpl;
	friend class McCircArc2dImpl;
	friend class McCircArc2d;
	friend class McGeEllipArc2d;
	friend class McGeCurve2dImpl;
	friend class McEllipticArc2dImpl;
	friend class McOffsetCurve2dImpl;
	friend class McGePosition2dImpl;
	friend class McNurbCurve2dImpl;
	friend class McGePolyline2dImpl;
	friend class McCurveCurveInt2dImpl;
	friend class McCompositeCurve2dImpl;

	friend void calcOrthoBoundBock4Ellipse(
		OUT McGeBoundBlock2d& res,
		const McGeInterval& range,
		const McGePoint2d& center,
		const McGeVector2d& vMajorMR,
		const McGeVector2d& vMinorMR);

};
//==============================================================================
