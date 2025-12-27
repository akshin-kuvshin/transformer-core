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
#include "mcintrvl.h"

class McEnt3dImpl;
struct IMtStream;

//==============================================================================
class MCGEL_API McGeEntity3d
{
private:
	McEnt3dImpl* m_pImpl;

protected:
	void               setImpl(McEnt3dImpl*);
	McEnt3dImpl*       getImpl();
	const McEnt3dImpl* getImpl() const;

protected:
	McGeEntity3d();

public:
	DECLARE_OBJ_NEWDEL;
	virtual ~McGeEntity3d();

	// Run time type information.
	virtual bool isKindOf(McGe::EntityId entType) const;
	virtual McGe::EntityId type() const;

	// Make a copy of the entity.
	virtual McGeEntity3d* copy() const;
	virtual McGeEntity3d& operator =  (const McGeEntity3d& entity);

	// Equivalence
	virtual bool operator == (const McGeEntity3d& entity) const;
	virtual bool operator != (const McGeEntity3d& entity) const;
	virtual bool isEqualTo(const McGeEntity3d& ent, const McGeTol& tol = McGeContext::gTol) const;

	// Matrix multiplication
	virtual McGeEntity3d& transformBy(const McGeMatrix3d& xfm);
	virtual McGeEntity3d& translateBy(const McGeVector3d& translateVec);
	virtual McGeEntity3d& rotateBy(double angle, const McGeVector3d& vec, const McGePoint3d& wrtPoint = McGePoint3d::kOrigin);
	virtual McGeEntity3d& mirror(const McGePlane& plane);
	virtual McGeEntity3d& scaleBy(double scaleFactor, const McGePoint3d& wrtPoint = McGePoint3d::kOrigin);

	// Point containment
	virtual bool isOn(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;

	// Reading and writing geometry library objects
	bool mcs_write(IMtStream* pStream) const;
	bool mcs_read(IMtStream* pStream);
	bool mcs_write(LPCTSTR lpszFileName) const;
	static McGeEntity3d* mcs_read(LPCTSTR lpszFileName);

	// Writes the entity type and the entity itself into a stream.
	static bool mcs_writeEnt(const McGeEntity3d* pEnt, IMtStream* pStream);

	// Restores the previously saved by method mcs_writeEnt entity from a stream.
	static McGeEntity3d* mcs_readEnt(IMtStream* pStream);

	friend class McGeTorusImpl;
	friend class McGeCylinderImpl;
	friend class McGeSphereImpl;
	friend class McGeConeImpl;
	friend class McLinearEnt3dImpl;
	friend class McPlanarEntImpl;
	friend class McCircArc3dImpl;
	friend class McEllipticArc3dImpl;
	friend class McPointOnCurve3dImpl;
	friend class McPointOnSurfaceImpl;
	friend class McCurveCurveInt3dImpl;
	friend class McBlock3dImpl;
	friend class McCompositeCurve3dImpl;
	friend class McGeEllipArc3d;
	friend class McGeLinearEnt3d;
	friend class McPointEnt3dImpl;
	friend class McGePlanarEnt;
	friend class McGePlane;
	friend struct ToCcSegment;
	friend class McGeBoundBlock3d;
	friend class McNurbCurve3dImpl;
	friend class McNurbCurve2dImpl;
	friend class McGePosition3dImpl;
	friend class McGePolyline3dImpl;
	friend class McGeAugPolyline3dImpl;
	friend class McNurbSurfImpl;
	friend class McOffsetCurve3dImpl;
	friend class McGeBoundedPlane;
	friend struct splineHullCalcData;
	friend struct splinePiecePolygonHull;

	friend void calcOrthoBoundBock4Ellipse(
		OUT McGeBoundBlock3d& res,
		const McGeInterval& range,
		const McGePoint3d& center,
		const McGeVector3d& vMajorMR,
		const McGeVector3d& vMinorMR);

	friend McEnt3dImpl* MCGE_IMPLENT3D(const McGeEntity3d*);
};
//==============================================================================
