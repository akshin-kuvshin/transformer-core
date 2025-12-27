#ifndef ND_NCDBABB_H
#define ND_NCDBABB_H
#include "typesDb.h"

typedef Nano::ErrorStatus       ErrorStatus;

typedef NcDb::OpenMode          OpenMode;
typedef NcDb::OsnapMode         OsnapMode;
typedef NcDb::CoordAxis         CoordAxis;
typedef NcDb::CoordSystem       CoordSystem;
typedef NcDb::Intersect         Intersect;
typedef NcDb::Visibility        Visibility;
typedef NcDb::SaveType          SaveType;
typedef NcDb::DxfCode           DxfCode;
typedef NcDb::DwgDataType       DwgDataType;
typedef NcDb::TextHorzMode      TextHorzMode;
typedef NcDb::TextVertMode      TextVertMode;
typedef NcDb::LineSpacingStyle  LineSpacingStyle;
typedef NcDb::Planarity         Planarity;
typedef NcDb::PointIndex        PointIndex;
typedef NcDb::EdgeIndex         EdgeIndex;
typedef NcDb::Poly2dType        Poly2dType;
typedef NcDb::Poly3dType        Poly3dType;
typedef NcDb::PolyMeshType      PolyMeshType;
typedef NcDb::Vertex2dType      Vertex2dType;
typedef NcDb::Vertex3dType      Vertex3dType;
typedef NcDb::SpaceValueType    SpaceValueType;
typedef NcDb::BoolOperType      BoolOperType;
typedef NcDb::SubentType        SubentType;
typedef NcDb::GeomId            GeomId;
typedef NcDb::GeomType          GeomType;
typedef NcDb::OrthographicView  OrthographicView;

const Nano::ErrorStatus eInvalidDwgVersion = Nano::eInvalidDwgVersion;
const Nano::ErrorStatus eInvalidDxfCode = Nano::eInvalidDxfCode;
const Nano::ErrorStatus eFSMError = Nano::eFSMError;
const Nano::ErrorStatus eFileLockedByNCAD = Nano::eFileLockedByNCAD;
const Nano::ErrorStatus eBadMaterialName = Nano::eBadMaterialName;
const Nano::ErrorStatus eXrefReloaded = Nano::eXrefReloaded;
const Nano::ErrorStatus eNullNodeId = Nano::eNullNodeId;
const Nano::ErrorStatus eNoNodeActive = Nano::eNoNodeActive;
const Nano::ErrorStatus eGraphContainsProxies = Nano::eGraphContainsProxies;
const Nano::ErrorStatus eBackgroundPlotInProgress = Nano::eBackgroundPlotInProgress;
const Nano::ErrorStatus eGraphEdgeNotFound = Nano::eGraphEdgeNotFound;
const Nano::ErrorStatus eGraphNodeNotFound = Nano::eGraphNodeNotFound;
const Nano::ErrorStatus eGraphNodeAlreadyExists = Nano::eGraphNodeAlreadyExists;
const Nano::ErrorStatus eGraphEdgeAlreadyExists = Nano::eGraphEdgeAlreadyExists;
const Nano::ErrorStatus eGraphCyclesFound = Nano::eGraphCyclesFound;
const Nano::ErrorStatus eAlreadyHasRepresentation = Nano::eAlreadyHasRepresentation;
const Nano::ErrorStatus eNoRepresentation = Nano::eNoRepresentation;
const Nano::ErrorStatus eNoIntersections = Nano::eNoIntersections;
const Nano::ErrorStatus eEmbeddedIntersections = Nano::eEmbeddedIntersections;
const Nano::ErrorStatus eFailedToSetEdgeChamfers = Nano::eFailedToSetEdgeChamfers;
const Nano::ErrorStatus eNoConnectedBlendSet = Nano::eNoConnectedBlendSet;
const Nano::ErrorStatus eFailedToBlend = Nano::eFailedToBlend;
const Nano::ErrorStatus eFailedToSetEdgeRounds = Nano::eFailedToSetEdgeRounds;
const Nano::ErrorStatus eFailedToSetVertexRounds = Nano::eFailedToSetVertexRounds;
const Nano::ErrorStatus eFailedToEvaluate = Nano::eFailedToEvaluate;
const Nano::ErrorStatus eFailedToEvaluateDependents = Nano::eFailedToEvaluateDependents;
const Nano::ErrorStatus eInvalidExpression = Nano::eInvalidExpression;
const Nano::ErrorStatus eCyclicDependency = Nano::eCyclicDependency;
const Nano::ErrorStatus eInconsistentConstraint = Nano::eInconsistentConstraint;
const Nano::ErrorStatus eOverDefinedConstraint = Nano::eOverDefinedConstraint;
const Nano::ErrorStatus eInvalidParameterName = Nano::eInvalidParameterName;
const Nano::ErrorStatus eReferencedInEquation = Nano::eReferencedInEquation;
const Nano::ErrorStatus eStringNotAllowedInExpression = Nano::eStringNotAllowedInExpression;
const Nano::ErrorStatus eTooManyActiveCommands = Nano::eTooManyActiveCommands;
const Nano::ErrorStatus eUnableToTrimLastPiece = Nano::eUnableToTrimLastPiece;
const Nano::ErrorStatus eUnableToTrimSurface = Nano::eUnableToTrimSurface;
const Nano::ErrorStatus eModifyingAssociativeEntity = Nano::eModifyingAssociativeEntity;
const Nano::ErrorStatus eModifyingDimensionWithExpression = Nano::eModifyingDimensionWithExpression;
const Nano::ErrorStatus eDependentOnObjectErased = Nano::eDependentOnObjectErased;
const Nano::ErrorStatus eSelfIntersecting = Nano::eSelfIntersecting;
const Nano::ErrorStatus eNotOnBoundary = Nano::eNotOnBoundary;
const Nano::ErrorStatus eNotConnected = Nano::eNotConnected;
const Nano::ErrorStatus eNoInputPath = Nano::eNoInputPath;
const Nano::ErrorStatus eNotAssociative = Nano::eNotAssociative;
const Nano::ErrorStatus eNotG1Continuous = Nano::eNotG1Continuous;
const Nano::ErrorStatus eChangedAgainstAssociativity = Nano::eChangedAgainstAssociativity;

const NcDb::ShowImagesMode kNeverShow      = NcDb::kNeverShow;
const NcDb::ShowImagesMode kAlwaysShow     = NcDb::kAlwaysShow;
const NcDb::ShowImagesMode kBoundingBoxShow     = NcDb::kBoundingBoxShow;

const NcDb::SaveImagesMode kNeverSave      = NcDb::kNeverSave;
const NcDb::SaveImagesMode kAlwaysSave     = NcDb::kAlwaysSave;

const NcDb::CoordAxis kX = NcDb::kX;
const NcDb::CoordAxis kY = NcDb::kY;
const NcDb::CoordAxis kZ = NcDb::kZ;

const NcDb::CoordSystem kWorldCS = NcDb::kWorldCS;
const NcDb::CoordSystem kUserCS = NcDb::kUserCS;
const NcDb::CoordSystem kCurDisplayCS = NcDb::kCurDisplayCS;
const NcDb::CoordSystem kPaperDisplayCS = NcDb::kPaperDisplayCS;
const NcDb::CoordSystem kEntityCS = NcDb::kEntityCS;

const NcDb::Intersect kOnBothOperands = NcDb::kOnBothOperands;
const NcDb::Intersect kExtendThis = NcDb::kExtendThis;
const NcDb::Intersect kExtendArg = NcDb::kExtendArg;
const NcDb::Intersect kExtendBoth = NcDb::kExtendBoth;

const NcDb::Visibility kInvisible = NcDb::kInvisible;
const NcDb::Visibility kVisible = NcDb::kVisible;

const NcDb::DxfCode kDxfInvalid = NcDb::kDxfInvalid;
const NcDb::DxfCode kDxfXDictionary = NcDb::kDxfXDictionary;
const NcDb::DxfCode kDxfPReactors = NcDb::kDxfPReactors;
const NcDb::DxfCode kDxfOperator = NcDb::kDxfOperator;
const NcDb::DxfCode kDxfXDataStart = NcDb::kDxfXDataStart;
const NcDb::DxfCode kDxfHeaderId = NcDb::kDxfHeaderId;
const NcDb::DxfCode kDxfEnd = NcDb::kDxfEnd;
const NcDb::DxfCode kDxfStart = NcDb::kDxfStart;
const NcDb::DxfCode kDxfText = NcDb::kDxfText;
const NcDb::DxfCode kDxfShapeName = NcDb::kDxfShapeName;
const NcDb::DxfCode kDxfSymbolTableName = NcDb::kDxfSymbolTableName;
const NcDb::DxfCode kDxfBlockName = NcDb::kDxfBlockName;
const NcDb::DxfCode kDxfAttributeTag = NcDb::kDxfAttributeTag;
const NcDb::DxfCode kDxfAttributePrompt = NcDb::kDxfAttributePrompt;
const NcDb::DxfCode kDxfDimStyleName = NcDb::kDxfDimStyleName;
const NcDb::DxfCode kDxfXRefPath = NcDb::kDxfXRefPath;
const NcDb::DxfCode kDxfHandle = NcDb::kDxfHandle;
const NcDb::DxfCode kDxfLinetypeName = NcDb::kDxfLinetypeName;
const NcDb::DxfCode kDxfTextStyleName = NcDb::kDxfTextStyleName;
const NcDb::DxfCode kDxfCLShapeText = NcDb::kDxfCLShapeText;
const NcDb::DxfCode kDxfCLShapeName = NcDb::kDxfCLShapeName;
const NcDb::DxfCode kDxfLayerName = NcDb::kDxfLayerName;
const NcDb::DxfCode kDxfLayoutName = NcDb::kDxfLayoutName;
const NcDb::DxfCode kDxfXCoord = NcDb::kDxfXCoord;
const NcDb::DxfCode kDxfYCoord = NcDb::kDxfYCoord;
const NcDb::DxfCode kDxfZCoord = NcDb::kDxfZCoord;
const NcDb::DxfCode kDxfElevation = NcDb::kDxfElevation;
const NcDb::DxfCode kDxfThickness = NcDb::kDxfThickness;
const NcDb::DxfCode kDxfReal = NcDb::kDxfReal;
const NcDb::DxfCode kDxfXReal = NcDb::kDxfXReal;
const NcDb::DxfCode kDxfInt8 = NcDb::kDxfInt8;
const NcDb::DxfCode kDxfBool = NcDb::kDxfBool;
const NcDb::DxfCode kDxfLinetypeScale = NcDb::kDxfLinetypeScale;
const NcDb::DxfCode kDxfLinetypeElement = NcDb::kDxfLinetypeElement;
const NcDb::DxfCode kDxfAngle = NcDb::kDxfAngle;
const NcDb::DxfCode kDxfVisibility = NcDb::kDxfVisibility;
const NcDb::DxfCode kDxfLayerLinetype = NcDb::kDxfLayerLinetype;
const NcDb::DxfCode kDxfColor = NcDb::kDxfColor;
const NcDb::DxfCode kDxfHasSubentities = NcDb::kDxfHasSubentities;
const NcDb::DxfCode kDxfViewportVisibility = NcDb::kDxfViewportVisibility;
const NcDb::DxfCode kDxfViewportActive = NcDb::kDxfViewportActive;
const NcDb::DxfCode kDxfViewportNumber = NcDb::kDxfViewportNumber;
const NcDb::DxfCode kDxfInt16 = NcDb::kDxfInt16;
const NcDb::DxfCode kDxfXInt16 = NcDb::kDxfXInt16;
const NcDb::DxfCode kDxfXXInt16 = NcDb::kDxfXXInt16;
const NcDb::DxfCode kDxfInt32 = NcDb::kDxfInt32;
const NcDb::DxfCode kDxfInt64 = NcDb::kDxfInt64;
const NcDb::DxfCode kDxfControlString = NcDb::kDxfControlString;
const NcDb::DxfCode kDxfSymTableRecComments = NcDb::kDxfSymTableRecComments;
const NcDb::DxfCode kDxfDimVarHandle = NcDb::kDxfDimVarHandle;
const NcDb::DxfCode kDxfUCSOrg = NcDb::kDxfUCSOrg;
const NcDb::DxfCode kDxfUCSOriX = NcDb::kDxfUCSOriX;
const NcDb::DxfCode kDxfUCSOriY = NcDb::kDxfUCSOriY;
const NcDb::DxfCode kDxfSubclass = NcDb::kDxfSubclass;
const NcDb::DxfCode kDxfEmbeddedObjectStart = NcDb::kDxfEmbeddedObjectStart;
const NcDb::DxfCode kDxfNormalX = NcDb::kDxfNormalX;
const NcDb::DxfCode kDxfNormalY = NcDb::kDxfNormalY;
const NcDb::DxfCode kDxfNormalZ = NcDb::kDxfNormalZ;
const NcDb::DxfCode kDxfXTextString = NcDb::kDxfXTextString;
const NcDb::DxfCode kDxfBinaryChunk = NcDb::kDxfBinaryChunk;
const NcDb::DxfCode kDxfArbHandle   = NcDb::kDxfArbHandle;
const NcDb::DxfCode kDxfSoftPointerId = NcDb::kDxfSoftPointerId;
const NcDb::DxfCode kDxfHardPointerId = NcDb::kDxfHardPointerId;
const NcDb::DxfCode kDxfSoftOwnershipId = NcDb::kDxfSoftOwnershipId;
const NcDb::DxfCode kDxfHardOwnershipId = NcDb::kDxfHardOwnershipId;
const NcDb::DxfCode kDxfLineWeight = NcDb::kDxfLineWeight;
const NcDb::DxfCode kDxfPlotStyleNameType = NcDb::kDxfPlotStyleNameType;
const NcDb::DxfCode kDxfPlotStyleNameId = NcDb::kDxfPlotStyleNameId;
const NcDb::DxfCode kDxfXXXInt16 = NcDb::kDxfXXXInt16;
const NcDb::DxfCode kDxfComment = NcDb::kDxfComment;
const NcDb::DxfCode kDxfXdAsciiString = NcDb::kDxfXdAsciiString;
const NcDb::DxfCode kDxfRegAppName = NcDb::kDxfRegAppName;
const NcDb::DxfCode kDxfXdControlString = NcDb::kDxfXdControlString;
const NcDb::DxfCode kDxfXdLayerName = NcDb::kDxfXdLayerName;
const NcDb::DxfCode kDxfXdBinaryChunk = NcDb::kDxfXdBinaryChunk;
const NcDb::DxfCode kDxfXdHandle = NcDb::kDxfXdHandle;
const NcDb::DxfCode kDxfXdXCoord = NcDb::kDxfXdXCoord;
const NcDb::DxfCode kDxfXdYCoord = NcDb::kDxfXdYCoord;
const NcDb::DxfCode kDxfXdZCoord = NcDb::kDxfXdZCoord;
const NcDb::DxfCode kDxfXdWorldXCoord = NcDb::kDxfXdWorldXCoord;
const NcDb::DxfCode kDxfXdWorldYCoord = NcDb::kDxfXdWorldYCoord;
const NcDb::DxfCode kDxfXdWorldZCoord = NcDb::kDxfXdWorldZCoord;
const NcDb::DxfCode kDxfXdWorldXDisp = NcDb::kDxfXdWorldXDisp;
const NcDb::DxfCode kDxfXdWorldYDisp = NcDb::kDxfXdWorldYDisp;
const NcDb::DxfCode kDxfXdWorldZDisp = NcDb::kDxfXdWorldZDisp;
const NcDb::DxfCode kDxfXdWorldXDir = NcDb::kDxfXdWorldXDir;
const NcDb::DxfCode kDxfXdWorldYDir = NcDb::kDxfXdWorldYDir;
const NcDb::DxfCode kDxfXdWorldZDir = NcDb::kDxfXdWorldZDir;
const NcDb::DxfCode kDxfXdReal = NcDb::kDxfXdReal;
const NcDb::DxfCode kDxfXdDist = NcDb::kDxfXdDist;
const NcDb::DxfCode kDxfXdScale = NcDb::kDxfXdScale;
const NcDb::DxfCode kDxfXdInteger16 = NcDb::kDxfXdInteger16;
const NcDb::DxfCode kDxfXdInteger32 = NcDb::kDxfXdInteger32;
const NcDb::DxfCode kDxfColorRGB =  NcDb::kDxfColorRGB; 
const NcDb::DxfCode kDxfColorName =  NcDb::kDxfColorName;
const NcDb::DxfCode kDxfAlpha =  NcDb::kDxfAlpha;    
const NcDb::DxfCode kDxfMaterialId =  NcDb::kDxfMaterialId;
const NcDb::DxfCode kDxfViewportGridDisplay = NcDb::kDxfViewportGridDisplay;
const NcDb::DxfCode kDxfObjVisualStyleId = NcDb::kDxfObjVisualStyleId;
const NcDb::DxfCode kDxfVpVisualStyleId = NcDb::kDxfVpVisualStyleId;
const NcDb::DxfCode kDxfDragVisualStyleId = NcDb::kDxfDragVisualStyleId;
const NcDb::DxfCode kDxfShadowFlags = NcDb::kDxfShadowFlags;
const NcDb::DxfCode kDxfFaceStyleId = NcDb::kDxfFaceStyleId;
const NcDb::DxfCode kDxfEdgeStyleId = NcDb::kDxfEdgeStyleId;
const NcDb::DxfCode kDxfVisualStyleId = NcDb::kDxfVisualStyleId;

const NcDb::DxfCode kDxfGradientObjType  = NcDb::kDxfGradientObjType;
const NcDb::DxfCode kDxfGradientPatType  = NcDb::kDxfGradientPatType;
const NcDb::DxfCode kDxfGradientTintType = NcDb::kDxfGradientTintType;
const NcDb::DxfCode kDxfGradientColCount = NcDb::kDxfGradientColCount;
const NcDb::DxfCode kDxfGradientAngle    = NcDb::kDxfGradientAngle;
const NcDb::DxfCode kDxfGradientShift    = NcDb::kDxfGradientShift;
const NcDb::DxfCode kDxfGradientTintVal  = NcDb::kDxfGradientTintVal;
const NcDb::DxfCode kDxfGradientColVal   = NcDb::kDxfGradientColVal;
const NcDb::DxfCode kDxfGradientName     = NcDb::kDxfGradientName;

const NcDb::DwgDataType kDwgNull = NcDb::kDwgNull;
const NcDb::DwgDataType kDwgReal = NcDb::kDwgReal;
const NcDb::DwgDataType kDwgInt64 = NcDb::kDwgInt64;
const NcDb::DwgDataType kDwgInt32 = NcDb::kDwgInt32;
const NcDb::DwgDataType kDwgInt16 = NcDb::kDwgInt16;
const NcDb::DwgDataType kDwgInt8 = NcDb::kDwgInt8;
const NcDb::DwgDataType kDwgText = NcDb::kDwgText;
const NcDb::DwgDataType kDwgBChunk = NcDb::kDwgBChunk;
const NcDb::DwgDataType kDwgHandle = NcDb::kDwgHandle;
const NcDb::DwgDataType kDwgHardOwnershipId = NcDb::kDwgHardOwnershipId;
const NcDb::DwgDataType kDwgSoftOwnershipId = NcDb::kDwgSoftOwnershipId;
const NcDb::DwgDataType kDwgHardPointerId   = NcDb::kDwgHardPointerId;
const NcDb::DwgDataType kDwgSoftPointerId   = NcDb::kDwgSoftPointerId;
const NcDb::DwgDataType kDwg3Real = NcDb::kDwg3Real;
const NcDb::DwgDataType kDwgNotRecognized = NcDb::kDwgNotRecognized;

const NcDb::OsnapMask kOsMaskEnd = NcDb::kOsMaskEnd;
const NcDb::OsnapMask kOsMaskMid = NcDb::kOsMaskMid;
const NcDb::OsnapMask kOsMaskCen = NcDb::kOsMaskCen;
const NcDb::OsnapMask kOsMaskNode = NcDb::kOsMaskNode;
const NcDb::OsnapMask kOsMaskQuad = NcDb::kOsMaskQuad;
const NcDb::OsnapMask kOsMaskInt = NcDb::kOsMaskInt;
const NcDb::OsnapMask kOsMaskIns = NcDb::kOsMaskIns;
const NcDb::OsnapMask kOsMaskPerp = NcDb::kOsMaskPerp;
const NcDb::OsnapMask kOsMaskTan = NcDb::kOsMaskTan;
const NcDb::OsnapMask kOsMaskNear = NcDb::kOsMaskNear;
const NcDb::OsnapMask kOsMaskQuick = NcDb::kOsMaskQuick;
const NcDb::OsnapMask kOsMaskImmediate = NcDb::kOsMaskImmediate;
const NcDb::OsnapMask kOsMaskAllowTan = NcDb::kOsMaskAllowTan;
const NcDb::OsnapMask kOsMaskDisablePerp = NcDb::kOsMaskDisablePerp;
const NcDb::OsnapMask kOsMaskRelCartesian = NcDb::kOsMaskRelCartesian;
const NcDb::OsnapMask kOsMaskRelPolar = NcDb::kOsMaskRelPolar;
const NcDb::OsnapMask kOsMaskNoneOverride = NcDb::kOsMaskNoneOverride;

const NcDb::OsnapMode kOsModeEnd = NcDb::kOsModeEnd;
const NcDb::OsnapMode kOsModeMid = NcDb::kOsModeMid;
const NcDb::OsnapMode kOsModeCen = NcDb::kOsModeCen;
const NcDb::OsnapMode kOsModeNode = NcDb::kOsModeNode;
const NcDb::OsnapMode kOsModeQuad = NcDb::kOsModeQuad;
const NcDb::OsnapMode kOsModeIns = NcDb::kOsModeIns;
const NcDb::OsnapMode kOsModePerp = NcDb::kOsModePerp;
const NcDb::OsnapMode kOsModeTan = NcDb::kOsModeTan;
const NcDb::OsnapMode kOsModeNear = NcDb::kOsModeNear;

const NcDb::TextHorzMode kTextLeft = NcDb::kTextLeft;
const NcDb::TextHorzMode kTextCenter = NcDb::kTextCenter;
const NcDb::TextHorzMode kTextRight = NcDb::kTextRight;
const NcDb::TextHorzMode kTextAlign = NcDb::kTextAlign;
const NcDb::TextHorzMode kTextMid = NcDb::kTextMid;
const NcDb::TextHorzMode kTextFit = NcDb::kTextFit;

const NcDb::TextVertMode kTextBase = NcDb::kTextBase;
const NcDb::TextVertMode kTextBottom = NcDb::kTextBottom;
const NcDb::TextVertMode kTextVertMid = NcDb::kTextVertMid;
const NcDb::TextVertMode kTextTop = NcDb::kTextTop;

const NcDb::LineSpacingStyle kAtLeast = NcDb::kAtLeast;
const NcDb::LineSpacingStyle kExactly = NcDb::kExactly;

const NcDb::Planarity kNonPlanar = NcDb::kNonPlanar;
const NcDb::Planarity kPlanar = NcDb::kPlanar;
const NcDb::Planarity kLinear = NcDb::kLinear;

const NcDb::PointIndex kMPoint1 = NcDb::kMPoint1;
const NcDb::PointIndex kMPoint2 = NcDb::kMPoint2;
const NcDb::PointIndex kMPoint3 = NcDb::kMPoint3;
const NcDb::PointIndex kMPoint4 = NcDb::kMPoint4;

const NcDb::EdgeIndex kMEdge1 = NcDb::kMEdge1;
const NcDb::EdgeIndex kMEdge2 = NcDb::kMEdge2;
const NcDb::EdgeIndex kMEdge3 = NcDb::kMEdge3;
const NcDb::EdgeIndex kMEdge4 = NcDb::kMEdge4;

const NcDb::Poly2dType k2dSimplePoly = NcDb::k2dSimplePoly;
const NcDb::Poly2dType k2dFitCurvePoly = NcDb::k2dFitCurvePoly;
const NcDb::Poly2dType k2dQuadSplinePoly = NcDb::k2dQuadSplinePoly;
const NcDb::Poly2dType k2dCubicSplinePoly = NcDb::k2dCubicSplinePoly;

const NcDb::Poly3dType k3dSimplePoly = NcDb::k3dSimplePoly;
const NcDb::Poly3dType k3dQuadSplinePoly = NcDb::k3dQuadSplinePoly;
const NcDb::Poly3dType k3dCubicSplinePoly = NcDb::k3dCubicSplinePoly;

const NcDb::PolyMeshType kSimpleMesh = NcDb::kSimpleMesh;
const NcDb::PolyMeshType kQuadSurfaceMesh = NcDb::kQuadSurfaceMesh;
const NcDb::PolyMeshType kCubicSurfaceMesh = NcDb::kCubicSurfaceMesh;
const NcDb::PolyMeshType kBezierSurfaceMesh = NcDb::kBezierSurfaceMesh;

const NcDb::Vertex2dType k2dVertex = NcDb::k2dVertex;
const NcDb::Vertex2dType k2dSplineCtlVertex = NcDb::k2dSplineCtlVertex;
const NcDb::Vertex2dType k2dSplineFitVertex = NcDb::k2dSplineFitVertex;
const NcDb::Vertex2dType k2dCurveFitVertex = NcDb::k2dCurveFitVertex;

const NcDb::Vertex3dType k3dSimpleVertex = NcDb::k3dSimpleVertex;
const NcDb::Vertex3dType k3dControlVertex = NcDb::k3dControlVertex;
const NcDb::Vertex3dType k3dFitVertex = NcDb::k3dFitVertex;

const NcDb::SpaceValueType kUndefined = NcDb::kUndefined;
const NcDb::SpaceValueType kStubPtr = NcDb::kStubPtr;
const NcDb::SpaceValueType kEndOfFile = NcDb::kEndOfFile;
const NcDb::SpaceValueType kBackwardBranch = NcDb::kBackwardBranch;
const NcDb::SpaceValueType kForwardBranch = NcDb::kForwardBranch;
const NcDb::SpaceValueType kDetour = NcDb::kDetour;

const NcDb::BoolOperType kBoolUnite = NcDb::kBoolUnite;
const NcDb::BoolOperType kBoolIntersect = NcDb::kBoolIntersect;
const NcDb::BoolOperType kBoolSubtract = NcDb::kBoolSubtract;

const NcDb::SubentType kNullSubentType   = NcDb::kNullSubentType;
const NcDb::SubentType kVertexSubentType = NcDb::kVertexSubentType;
const NcDb::SubentType kEdgeSubentType   = NcDb::kEdgeSubentType;
const NcDb::SubentType kFaceSubentType   = NcDb::kFaceSubentType;
const NcDb::SubentType kMlineSubentCache = NcDb::kMlineSubentCache;
const NcDb::SubentType kClassSubentType  = NcDb::kClassSubentType;
const NcDb::SubentType kAxisSubentType = NcDb::kAxisSubentType;

const NcDb::GeomId kNoGeom = NcDb::kNoGeom;

const NcDb::GeomType kInvalidGeom = NcDb::kInvalidGeom;
const NcDb::GeomType kPointGeom = NcDb::kPointGeom;
const NcDb::GeomType kLineGeom = NcDb::kLineGeom;
const NcDb::GeomType kCircleGeom = NcDb::kCircleGeom;
const NcDb::GeomType kPlaneGeom = NcDb::kPlaneGeom;

const NcDb::UnitsValue kUnitsUndefined      = NcDb::kUnitsUndefined;
const NcDb::UnitsValue kUnitsInches         = NcDb::kUnitsInches;
const NcDb::UnitsValue kUnitsFeet           = NcDb::kUnitsFeet;
const NcDb::UnitsValue kUnitsMillimeters    = NcDb::kUnitsMillimeters;
const NcDb::UnitsValue kUnitsMeters         = NcDb::kUnitsMeters;
const NcDb::UnitsValue kUnitsMicroinches    = NcDb::kUnitsMicroinches;
const NcDb::UnitsValue kUnitsMils           = NcDb::kUnitsMils;
const NcDb::UnitsValue kUnitsYards          = NcDb::kUnitsYards;
const NcDb::UnitsValue kUnitsMiles          = NcDb::kUnitsMiles;
const NcDb::UnitsValue kUnitsAngstroms      = NcDb::kUnitsAngstroms;
const NcDb::UnitsValue kUnitsNanometers     = NcDb::kUnitsNanometers;
const NcDb::UnitsValue kUnitsMicrons        = NcDb::kUnitsMicrons;
const NcDb::UnitsValue kUnitsDecimeters     = NcDb::kUnitsDecimeters;
const NcDb::UnitsValue kUnitsCentimeters    = NcDb::kUnitsCentimeters;
const NcDb::UnitsValue kUnitsDekameters     = NcDb::kUnitsDekameters;
const NcDb::UnitsValue kUnitsHectometers    = NcDb::kUnitsHectometers;
const NcDb::UnitsValue kUnitsKilometers     = NcDb::kUnitsKilometers;
const NcDb::UnitsValue kUnitsGigameters     = NcDb::kUnitsGigameters;
const NcDb::UnitsValue kUnitsAstronomical   = NcDb::kUnitsAstronomical;
const NcDb::UnitsValue kUnitsLightYears     = NcDb::kUnitsLightYears;
const NcDb::UnitsValue kUnitsParsecs        = NcDb::kUnitsParsecs;
const NcDb::UnitsValue kUnitsMax            = NcDb::kUnitsMax;

const NcDb::OrthographicView kTopView      = NcDb::kTopView;
const NcDb::OrthographicView kBottomView   = NcDb::kBottomView;
const NcDb::OrthographicView kFrontView    = NcDb::kFrontView;
const NcDb::OrthographicView kBackView     = NcDb::kBackView;
const NcDb::OrthographicView kLeftView     = NcDb::kLeftView;
const NcDb::OrthographicView kRightView    = NcDb::kRightView;
const NcDb::OrthographicView kNonOrthoView = NcDb::kNonOrthoView;

const NcDb::CellType kUnknownCell          =  NcDb::kUnknownCell;	
const NcDb::CellType kTextCell             =  NcDb::kTextCell;	
const NcDb::CellType kBlockCell            =  NcDb::kBlockCell;	

const NcDb::CellEdgeMask kTopMask          =  NcDb::kTopMask;	
const NcDb::CellEdgeMask kRightMask        =  NcDb::kRightMask;	
const NcDb::CellEdgeMask kBottomMask       =  NcDb::kBottomMask;	
const NcDb::CellEdgeMask kLeftMask         =  NcDb::kLeftMask;	

const NcDb::FlowDirection kTtoB            =  NcDb::kTtoB;	
const NcDb::FlowDirection kBtoT            =  NcDb::kBtoT;

const NcDb::RotationAngle kDegrees000      =  NcDb::kDegrees000;	
const NcDb::RotationAngle kDegrees090      =  NcDb::kDegrees090;	
const NcDb::RotationAngle kDegrees180      =  NcDb::kDegrees180;	
const NcDb::RotationAngle kDegrees270      =  NcDb::kDegrees270;	
const NcDb::RotationAngle kDegreesUnknown  =  NcDb::kDegreesUnknown;	

const NcDb::CellAlignment kTopLeft		   =  NcDb::kTopLeft;
const NcDb::CellAlignment kTopCenter	   =  NcDb::kTopCenter;	
const NcDb::CellAlignment kTopRight		   =  NcDb::kTopRight;	
const NcDb::CellAlignment kMiddleLeft	   =  NcDb::kMiddleLeft;	
const NcDb::CellAlignment kMiddleCenter	   =  NcDb::kMiddleCenter;	
const NcDb::CellAlignment kMiddleRight	   =  NcDb::kMiddleRight;	
const NcDb::CellAlignment kBottomLeft	   =  NcDb::kBottomLeft;	
const NcDb::CellAlignment kBottomCenter	   =  NcDb::kBottomCenter;	
const NcDb::CellAlignment kBottomRight	   =  NcDb::kBottomRight;	

const NcDb::GridLineType kInvalidGridLine  =  NcDb::kInvalidGridLine;
const NcDb::GridLineType kHorzTop		   =  NcDb::kHorzTop;	
const NcDb::GridLineType kHorzInside	   =  NcDb::kHorzInside;	
const NcDb::GridLineType kHorzBottom	   =  NcDb::kHorzBottom;	
const NcDb::GridLineType kVertLeft		   =  NcDb::kVertLeft;	
const NcDb::GridLineType kVertInside	   =  NcDb::kVertInside;	
const NcDb::GridLineType kVertRight		   =  NcDb::kVertRight;	

const NcDb::GridLineTypes kAllGridLines	=  NcDb::kAllGridLines;	

const NcDb::RowType kUnknownRow			   =  NcDb::kUnknownRow;
const NcDb::RowType kDataRow			   =  NcDb::kDataRow;	
const NcDb::RowType kTitleRow			   =  NcDb::kTitleRow;	
const NcDb::RowType kHeaderRow			   =  NcDb::kHeaderRow;	

const NcDb::RowTypes kAllRows               =  NcDb::kAllRows;	

const NcDb::TableStyleFlags kHorzInsideLineFirst =  NcDb::kHorzInsideLineFirst;
const NcDb::TableStyleFlags kHorzInsideLineSecond =  NcDb::kHorzInsideLineSecond;
const NcDb::TableStyleFlags kHorzInsideLineThird =  NcDb::kHorzInsideLineThird;
const NcDb::TableStyleFlags kTableStyleModified =  NcDb::kTableStyleModified;

const NcDb::SliceModelType kKeepBothSides    =  NcDb::kKeepBothSides;	
const NcDb::SliceModelType kUseCurrentColor  =  NcDb::kUseCurrentColor;	

const NcDbGripOperations::ReturnValue eGripOpFailure = NcDbGripOperations::ReturnValue::eFailure;
const NcDbGripOperations::ReturnValue eGripOpNoRedrawGrip = NcDbGripOperations::ReturnValue::eNoRedrawGrip;
const NcDbGripOperations::ReturnValue eGripOpGripHotToWarm = NcDbGripOperations::ReturnValue::eGripHotToWarm;
const NcDbGripOperations::ReturnValue eGripOpGetNewGripPoints = NcDbGripOperations::ReturnValue::eGetNewGripPoints;
#endif //ND_NCDBABB_H