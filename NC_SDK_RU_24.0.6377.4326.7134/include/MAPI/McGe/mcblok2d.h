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

#pragma  once

#ifdef _VERBOSEHEADERS_
#pragma message("Use " __FILE__)
#endif

#include "mcent2d.h"
#pragma pack (push, 8)

class McGePoint2d;
class McGeVector2d;
class mcsBoundBlock;
class McGeBoundBlock2d;
//==============================================================================
class MCGEL_API  McGeBoundBlock2d : public McGeEntity2d
{
public:
	McGeBoundBlock2d();
	McGeBoundBlock2d(const McGePoint2d& base, const McGeVector2d& dir1, const McGeVector2d& dir2);
	McGeBoundBlock2d(const McGeBoundBlock2d& block);
	~McGeBoundBlock2d();

	//............................................................................
		// McGeEntity2d 
		// ввиду особееноси реализации этого класса, данные методы должны 
		// быть явно указаны здесь
	virtual bool isKindOf(McGe::EntityId entType) const;
	virtual McGe::EntityId type() const;
	virtual McGeEntity2d* copy() const;
	virtual McGeEntity2d& operator =  (const McGeEntity2d& entity);
	//virtual bool operator == (const McGeEntity2d& entity) const;
	//virtual bool operator != (const McGeEntity2d& entity) const;
	virtual bool isEqualTo(const McGeEntity2d& ent, const McGeTol& tol = McGeContext::gTol) const;
	virtual McGeEntity2d& transformBy(const McGeMatrix2d& xfm);
	//virtual McGeEntity2d& translateBy(const McGeVector2d& translateVec);
	//virtual McGeEntity2d& rotateBy(double angle, const McGeVector2d& vec, const McGePoint2d& wrtPoint = McGePoint2d::kOrigin);
	//virtual McGeEntity2d& mirror(const McGePlane& plane);
	//virtual McGeEntity2d& scaleBy(double scaleFactor, const McGePoint2d& wrtPoint = McGePoint2d::kOrigin);
	virtual bool isOn(const McGePoint2d& pnt, const McGeTol& tol = McGeContext::gTol) const;

	// Access methods.
	virtual void getMinMaxPoints(McGePoint2d& point1, McGePoint2d& point2) const;
	virtual void get(McGePoint2d& base, McGeVector2d& dir1, McGeVector2d& dir2) const;

	// Set methods.
	virtual McGeBoundBlock2d& set(const McGePoint2d& point1, const McGePoint2d& point2);
	virtual McGeBoundBlock2d& set(const McGePoint2d& base, const McGeVector2d& dir1, const McGeVector2d& dir2);

	// Expand to contain point.
	virtual McGeBoundBlock2d& extend(const McGePoint2d& point);

	// Expand by a specified distance.
	virtual McGeBoundBlock2d& swell(double distance);

	// Containment and intersection tests
	virtual bool contains(const McGePoint2d& point) const;
	virtual bool isDisjoint(const McGeBoundBlock2d& block) const;

	// Assignment operator
	virtual McGeBoundBlock2d& operator = (const McGeBoundBlock2d& block);

	virtual bool isBox() const;
	virtual McGeBoundBlock2d&  setToBox(bool);

	// MCS stuff, returning object is an alias for 'this' and may be modified
	const mcsBoundBlock& mcs_bounds() const
	{
		return *(const mcsBoundBlock*)m_pImpl;
	}

	mcsBoundBlock& mcs_bounds()
	{
		return *(mcsBoundBlock*)m_pImpl;
	}
};
#pragma pack(pop)
//==============================================================================
