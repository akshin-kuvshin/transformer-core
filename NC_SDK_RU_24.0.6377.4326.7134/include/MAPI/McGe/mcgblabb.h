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

#include "mcgblge.h"

#ifndef ACGATE

const int eGood = McGe::eGood;
const int eBad = McGe::eBad;

typedef McGe::EntityId EntityId;

const McGe::EntityId kEntity2d = McGe::kEntity2d;
const McGe::EntityId kEntity3d = McGe::kEntity3d;
const McGe::EntityId kPointEnt2d = McGe::kPointEnt2d;
const McGe::EntityId kPointEnt3d = McGe::kPointEnt3d;
const McGe::EntityId kPosition2d = McGe::kPosition2d;
const McGe::EntityId kPosition3d = McGe::kPosition3d;
const McGe::EntityId kPointOnCurve2d = McGe::kPointOnCurve2d;
const McGe::EntityId kPointOnCurve3d = McGe::kPointOnCurve3d;
const McGe::EntityId kBoundedPlane = McGe::kBoundedPlane;
const McGe::EntityId kCircArc2d = McGe::kCircArc2d;
const McGe::EntityId kCircArc3d = McGe::kCircArc3d;
const McGe::EntityId kConic2d = McGe::kConic2d;
const McGe::EntityId kConic3d = McGe::kConic3d;
const McGe::EntityId kCurve2d = McGe::kCurve2d;
const McGe::EntityId kCurve3d = McGe::kCurve3d;
const McGe::EntityId kEllipArc2d = McGe::kEllipArc2d;
const McGe::EntityId kEllipArc3d = McGe::kEllipArc3d;
const McGe::EntityId kLine2d = McGe::kLine2d;
const McGe::EntityId kLine3d = McGe::kLine3d;
const McGe::EntityId kLinearEnt2d = McGe::kLinearEnt2d;
const McGe::EntityId kLinearEnt3d = McGe::kLinearEnt3d;
const McGe::EntityId kLineSeg2d = McGe::kLineSeg2d;
const McGe::EntityId kLineSeg3d = McGe::kLineSeg3d;
const McGe::EntityId kPlanarEnt = McGe::kPlanarEnt;
const McGe::EntityId kExternalCurve3d = McGe::kExternalCurve3d;
const McGe::EntityId kExternalCurve2d = McGe::kExternalCurve2d;
const McGe::EntityId kPlane = McGe::kPlane;
const McGe::EntityId kRay2d = McGe::kRay2d;
const McGe::EntityId kRay3d = McGe::kRay3d;
const McGe::EntityId kSurface = McGe::kSurface;
const McGe::EntityId kSphere = McGe::kSphere;
const McGe::EntityId kCone = McGe::kCone;
const McGe::EntityId kTorus = McGe::kTorus;
const McGe::EntityId kCylinder = McGe::kCylinder;
const McGe::EntityId kSplineEnt2d = McGe::kSplineEnt2d;
const McGe::EntityId kSurfaceCurve2dTo3d = McGe::kSurfaceCurve2dTo3d;
const McGe::EntityId kSurfaceCurve3dTo2d = McGe::kSurfaceCurve3dTo2d;

const McGe::EntityId kPolyline2d = McGe::kPolyline2d;
const McGe::EntityId kAugPolyline2d = McGe::kAugPolyline2d;
const McGe::EntityId kNurbCurve2d = McGe::kNurbCurve2d;
const McGe::EntityId kDSpline2d = McGe::kDSpline2d;
const McGe::EntityId kCubicSplineCurve2d = McGe::kCubicSplineCurve2d;
const McGe::EntityId kSplineEnt3d = McGe::kSplineEnt3d;
const McGe::EntityId kPolyline3d = McGe::kPolyline3d;
const McGe::EntityId kAugPolyline3d = McGe::kAugPolyline3d;
const McGe::EntityId kNurbCurve3d = McGe::kNurbCurve3d;
const McGe::EntityId kDSpline3d = McGe::kDSpline3d;
const McGe::EntityId kCubicSplineCurve3d = McGe::kCubicSplineCurve3d;
const McGe::EntityId kTrimmedCrv2d = McGe::kTrimmedCrv2d;
const McGe::EntityId kCompositeCrv2d = McGe::kCompositeCrv2d;
const McGe::EntityId kCompositeCrv3d = McGe::kCompositeCrv3d;
const McGe::EntityId kEnvelope2d = McGe::kEnvelope2d;
const McGe::EntityId kMcPolyline = McGe::kMcPolyline;

const McGe::EntityId kExternalSurface = McGe::kExternalSurface;
const McGe::EntityId kNurbSurface = McGe::kNurbSurface;
const McGe::EntityId kOffsetSurface = McGe::kOffsetSurface;
const McGe::EntityId kTrimmedSurface = McGe::kTrimmedSurface;
const McGe::EntityId kCurveBoundedSurface = McGe::kCurveBoundedSurface;
const McGe::EntityId kPointOnSurface = McGe::kPointOnSurface;
const McGe::EntityId kExternalBoundedSurface = McGe::kExternalBoundedSurface;
const McGe::EntityId kCurveCurveInt2d = McGe::kCurveCurveInt2d;
const McGe::EntityId kCurveCurveInt3d = McGe::kCurveCurveInt3d;
const McGe::EntityId kBoundBlock2d = McGe::kBoundBlock2d;
const McGe::EntityId kBoundBlock3d = McGe::kBoundBlock3d;
const McGe::EntityId kOffsetCurve2d = McGe::kOffsetCurve2d;
const McGe::EntityId kOffsetCurve3d = McGe::kOffsetCurve3d;
const McGe::EntityId kPolynomCurve3d = McGe::kPolynomCurve3d;
const McGe::EntityId kBezierCurve3d = McGe::kBezierCurve3d;
const McGe::EntityId kObject = McGe::kObject;
const McGe::EntityId kFitData3d = McGe::kFitData3d;
const McGe::EntityId kHatch = McGe::kHatch;
const McGe::EntityId kTrimmedCurve2d = McGe::kTrimmedCurve2d;
const McGe::EntityId kTrimmedCurve3d = McGe::kTrimmedCurve3d;
const McGe::EntityId kCurveSampleData = McGe::kCurveSampleData;

const McGe::EntityId kEllipCone = McGe::kEllipCone;
const McGe::EntityId kEllipCylinder = McGe::kEllipCylinder;
const McGe::EntityId kIntervalBoundBlock = McGe::kIntervalBoundBlock;
const McGe::EntityId kClipBoundary2d = McGe::kClipBoundary2d;
const McGe::EntityId kExternalObject = McGe::kExternalObject;
const McGe::EntityId kCurveSurfaceInt = McGe::kCurveSurfaceInt;
const McGe::EntityId kSurfaceSurfaceInt = McGe::kSurfaceSurfaceInt;


typedef McGe::ExternalEntityKind ExternalEntityKind;

const McGe::ExternalEntityKind kAcisEntity = McGe::kAcisEntity;
const McGe::ExternalEntityKind kExternalEntityUndefined
                                = McGe::kExternalEntityUndefined;

typedef McGe::NurbSurfaceProperties NurbSurfaceProperties;

const McGe::NurbSurfaceProperties kOpen = McGe::kOpen;
const McGe::NurbSurfaceProperties kClosed = McGe::kClosed;
const McGe::NurbSurfaceProperties kPeriodic = McGe::kPeriodic;
const McGe::NurbSurfaceProperties kRational = McGe::kRational;
const McGe::NurbSurfaceProperties kNoPoles= McGe::kNoPoles;
const McGe::NurbSurfaceProperties kPoleAtMin = McGe::kPoleAtMin;
const McGe::NurbSurfaceProperties kPoleAtMax = McGe::kPoleAtMax;
const McGe::NurbSurfaceProperties kPoleAtBoth = McGe::kPoleAtBoth;

typedef McGe::PointContainment PointContainment;

const McGe::PointContainment kInside = McGe::kInside;
const McGe::PointContainment kOutside = McGe::kOutside;
const McGe::PointContainment kOnBoundary = McGe::kOnBoundary;

const McGe::McGeXConfig kNotDefined = McGe::kNotDefined;
const McGe::McGeXConfig kUnknown = McGe::kUnknown;
const McGe::McGeXConfig kLeftRight = McGe::kLeftRight;
const McGe::McGeXConfig kRightLeft = McGe::kRightLeft;
const McGe::McGeXConfig kLeftLeft = McGe::kLeftLeft;
const McGe::McGeXConfig kRightRight = McGe::kRightRight;
const McGe::McGeXConfig kPointLeft = McGe::kPointLeft;
const McGe::McGeXConfig kPointRight = McGe::kPointRight;
const McGe::McGeXConfig kLeftOverlap = McGe::kLeftOverlap;
const McGe::McGeXConfig kOverlapLeft = McGe::kOverlapLeft;
const McGe::McGeXConfig kRightOverlap = McGe::kRightOverlap;
const McGe::McGeXConfig kOverlapRight = McGe::kOverlapRight;
const McGe::McGeXConfig kOverlapStart = McGe::kOverlapStart;
const McGe::McGeXConfig kOverlapEnd = McGe::kOverlapEnd;
const McGe::McGeXConfig kOverlapOverlap = McGe::kOverlapOverlap;

const McGe::ErrorCondition	kOk = McGe::kOk;
const McGe::ErrorCondition	k0This = McGe::k0This;
const McGe::ErrorCondition	k0Arg1 = McGe::k0Arg1;
const McGe::ErrorCondition	k0Arg2 = McGe::k0Arg2;
const McGe::ErrorCondition	kPerpendicularArg1Arg2 = McGe::kPerpendicularArg1Arg2;     
const McGe::ErrorCondition	kEqualArg1Arg2 = McGe::kEqualArg1Arg2;
const McGe::ErrorCondition	kEqualArg1Arg3 = McGe::kEqualArg1Arg3;
const McGe::ErrorCondition	kEqualArg2Arg3 = McGe::kEqualArg2Arg3;
const McGe::ErrorCondition	kLinearlyDependentArg1Arg2Arg3 = McGe::kLinearlyDependentArg1Arg2Arg3;
const McGe::ErrorCondition	kArg1TooBig = McGe::kArg1TooBig;
const McGe::ErrorCondition	kArg1OnThis = McGe::kArg1OnThis;
const McGe::ErrorCondition	kArg1InsideThis = McGe::kArg1InsideThis;

const McGe::McGeIntersectError kXXOk = McGe::kXXOk;
const McGe::McGeIntersectError kXXIndexOutOfRange = McGe::kXXIndexOutOfRange;
const McGe::McGeIntersectError kXXWrongDimensionAtIndex = McGe::kXXWrongDimensionAtIndex;
const McGe::McGeIntersectError kXXUnknown = McGe::kXXUnknown;

#endif // ACGATE

typedef McGe::McGeXConfig McGeXConfig;
typedef McGe::ErrorCondition  McGeError;
typedef McGe::McGeIntersectError McGeIntersectError;
