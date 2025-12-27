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

#include "mcent3d.h"
#pragma pack (push, 8)

class McGePoint3d;
class McGeVector3d;
class mcsBoundBlock;
class McGeBoundBlock2d;
//==============================================================================
class MCGEL_API  McGeBoundBlock3d : public McGeEntity3d
{
public:
	McGeBoundBlock3d ();
	McGeBoundBlock3d (const McGePoint3d& base, const McGeVector3d& dir1, const McGeVector3d& dir2, const McGeVector3d& dir3);
	McGeBoundBlock3d (const McGeBoundBlock3d& block);
	~McGeBoundBlock3d();

	//............................................................................
		// McGeEntity3d 
		// ввиду особееноси реализации этого класса, данные методы должны 
		// быть явно указаны здесь
	virtual bool isKindOf(McGe::EntityId entType) const;
	virtual McGe::EntityId type() const;
	virtual McGeEntity3d* copy() const;
	virtual McGeEntity3d& operator =  (const McGeEntity3d& entity);
	//virtual bool operator == (const McGeEntity3d& entity) const;
	//virtual bool operator != (const McGeEntity3d& entity) const;
	virtual bool isEqualTo(const McGeEntity3d& ent, const McGeTol& tol = McGeContext::gTol) const;
	virtual McGeEntity3d& transformBy(const McGeMatrix3d& xfm);
	//virtual McGeEntity3d& translateBy(const McGeVector3d& translateVec);
	//virtual McGeEntity3d& rotateBy(double angle, const McGeVector3d& vec, const McGePoint3d& wrtPoint = McGePoint3d::kOrigin);
	//virtual McGeEntity3d& mirror(const McGePlane& plane);
	//virtual McGeEntity3d& scaleBy(double scaleFactor, const McGePoint3d& wrtPoint = McGePoint3d::kOrigin);
	virtual bool isOn(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;

		// Access methods.
	virtual void getMinMaxPoints (McGePoint3d& point1, McGePoint3d& point2) const;
	virtual void get (McGePoint3d& base, McGeVector3d& dir1, McGeVector3d& dir2, McGeVector3d& dir3) const;

		// Set methods.
	virtual McGeBoundBlock3d& set(const McGePoint3d& point1, const McGePoint3d& point2);
	virtual McGeBoundBlock3d& set(const McGePoint3d& base, const McGeVector3d& dir1, const McGeVector3d& dir2, const McGeVector3d& dir3);

		// Expand to contain point.
	virtual McGeBoundBlock3d& extend(const McGePoint3d& point);

		// Expand by a specified distance.
	virtual McGeBoundBlock3d& swell(double distance);

		// Containment and intersection tests
	virtual bool contains(const McGePoint3d& point) const;
	virtual bool isDisjoint(const McGeBoundBlock3d& block) const;

	bool mcs_isDisjoint_XOY(const McGeBoundBlock3d& blockOther) const;

		// Assignment operator
	virtual McGeBoundBlock3d& operator = (const McGeBoundBlock3d& block);

	virtual bool isBox () const;
	virtual McGeBoundBlock3d&  setToBox (bool);

		// MCS stuff, returning object is an alias for 'this' and may be modified
	const mcsBoundBlock& mcs_bounds () const
	{
		return *(const mcsBoundBlock*)m_pImpl;
	}

	mcsBoundBlock& mcs_bounds ()
	{
		return *(mcsBoundBlock*)m_pImpl;
	}
	friend class McCompositeCurve2dImpl;
};
#pragma pack(pop)
//==============================================================================
