#pragma once
#include "mcpent3d.h"

class McGePoint2d;

class McGePointOnSurface : public McGePointEnt3d
{
public:
	MCGEL_API McGePointOnSurface();
	MCGEL_API McGePointOnSurface(const McGeSurface& surf);
	MCGEL_API McGePointOnSurface(const McGeSurface& surf, McGePoint2d param);
	MCGEL_API McGePointOnSurface(const McPointOnSurfaceImpl& src);
	MCGEL_API ~McGePointOnSurface();

	// McEnt3d methods
	MCGEL_API virtual bool isKindOf(McGe::EntityId entType) const override;
	MCGEL_API virtual McGe::EntityId type() const override;
	MCGEL_API virtual McGeEntity3d* copy() const override;
	MCGEL_API virtual McGePointOnSurface& operator=(const McGePointOnSurface& pocImpl);
	MCGEL_API virtual bool isEqualTo(const McGeEntity3d& ent, const McGeTol& tol = McGeContext::gTol) const override;
	MCGEL_API virtual McGeEntity3d& transformBy(const McGeMatrix3d& xfm) override;
	MCGEL_API virtual bool isOn(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const override;

	// McPointEnt3d methods
	MCGEL_API virtual McGePoint3d point3d() const;
	MCGEL_API virtual operator McGePoint3d() const;

	// McPointOnSurface methods
	MCGEL_API virtual const McGeSurface* surface() const;
	MCGEL_API virtual McGePointOnSurface& setSurface(const McGeSurface& surf);
	MCGEL_API virtual McGePointOnSurface& setParameter(const McGePoint2d& param);
	MCGEL_API virtual McGePoint2d parameter() const;

	MCGEL_API virtual McGeVector3d vDeriv(int order, const McGePoint2d& param);
	MCGEL_API virtual McGeVector3d vDeriv(int order);
	MCGEL_API virtual McGeVector3d vDeriv(int order, const McGeSurface& surf, const McGePoint2d& param);

	MCGEL_API virtual McGeVector3d uDeriv(int order, const McGePoint2d& param);
	MCGEL_API virtual McGeVector3d uDeriv(int order);
	MCGEL_API virtual McGeVector3d uDeriv(int order, const McGeSurface& surf, const McGePoint2d& param);

	MCGEL_API virtual McGeVector3d tangentVector(const McGeVector2d& vec);
	MCGEL_API virtual McGeVector3d tangentVector(const McGeVector2d& vec, const McGePoint2d& param);
	MCGEL_API virtual McGeVector3d tangentVector(const McGeVector2d& vec, const McGeSurface& vecSurf, const McGePoint2d& param);

	MCGEL_API virtual McGePoint3d point() const;
	MCGEL_API virtual McGePoint3d point(const McGePoint2d& param);
	MCGEL_API virtual McGePoint3d point(const McGeSurface& surf, const McGePoint2d& param);

	MCGEL_API virtual McGeVector3d normal() const;
	MCGEL_API virtual McGeVector3d normal(const McGePoint2d& param);
	MCGEL_API virtual McGeVector3d normal(const McGeSurface& surf, const McGePoint2d& param);

	MCGEL_API virtual McGeVector3d mixedPartial() const;
	MCGEL_API virtual McGeVector3d mixedPartial(const McGePoint2d& param) const;
	MCGEL_API virtual McGeVector3d mixedPartial(const McGeSurface& surf, const McGePoint2d& param) const;
};