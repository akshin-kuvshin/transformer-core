#ifndef __POINTCLOUDDEFINITIONS_H__
#define __POINTCLOUDDEFINITIONS_H__

#include "Exports.h"
#ifdef NRX3GATE
#include "nrxdbgate/typesDb.h"
#include "nrxhostgate/typesHost.h"
#include "nrxdbgate/array.h"
#include "nrxdbgate/core.h"
#include "nrxdbgate/ncstring.h"
#include "nrxdbgate/nc64BitHelpers.h"
#include "nrxdbgate/geometry.h"
#include "nrxdbgate/objectid.h"
#include "nrxdbgate/filer.h"
#include "nrxdbgate/graphics.h"
#include "nrxdbgate/objptr.h"
#include "nrxdbgate/document.h"
#include "nrxdbgate/idmapping.h"
#include "nrxdbgate/database.h"
#include "nrxdbgate/applicationDb.h"
#include "nrxhostgate/applicationHost.h"
#else
#include "nrxgate/types.h"
#include "nrxgate/array.h"
#include "nrxgate/core.h"
#include "nrxgate/ncstring.h"
#include "nrxgate/nc64BitHelpers.h"
#include "nrxgate/geometry.h"
#include "nrxgate/objectid.h"
#include "nrxgate/filer.h"
#include "nrxgate/graphics.h"
#include "nrxgate/objptr.h"
#include "nrxgate/document.h"
#include "nrxgate/idmapping.h"
#include "nrxgate/database.h"
#include "nrxgate/application.h"
#endif

namespace NPC_API
{
  //@}
  //! geometry types
  //@{ 
  typedef NRX::GsMarker _GsMarker;
  typedef NcGeMatrix3d _Matrix3d;
  typedef NcGeVector3d _Vector3d;
  typedef NcGePoint3d _Point3d;
  typedef NcGePoint3dArray _Point3dArray;
  typedef NcGePoint2d _Point2d;
  typedef NcGePoint2dArray _Point2dArray;
  //@}
  //! point cloud data
  //@{ 
  typedef unsigned __int32 _RGBType;
  typedef __time64_t       _TimeType;
  typedef unsigned __int8  _ClassType;
  typedef unsigned __int16 _SourceIDType;
  typedef _Vector3d        _NormalType;
  typedef unsigned __int16 _IntencityType;
  typedef float            _DeviationType;
  typedef unsigned __int8  _EchoCountType;
  typedef unsigned __int8  _EchoNumberType;
  typedef float            _ScanAngleRankType;
  typedef bool             _ScanDirectionType;
  typedef bool             _EdgeOfFlightLineType;
  typedef enum class _GeomFeature : __int32 {} _GeometricFeatureType;

  typedef unsigned __int16 _DataType;
  typedef unsigned __int16 _PointSize;
  typedef unsigned __int16 _TreeLevelType;
  typedef unsigned __int32 _NodeIndexType;
  typedef unsigned __int16 _PointIndexType;
  typedef unsigned __int64 _CompositeIndexType;
  typedef unsigned __int64 _ViewportHandle;
  typedef unsigned __int32 _DataEncoderState;
  typedef unsigned __int32 _VisualizationParamIndex;

  enum class _TypeOfGeometricFeature : __int32
  {
    NullFeature = 0,
    Plane = 1,
    Cylinder = 2,
    TwoPlanesIntersection = 3,
    ThreePlanesIntersection = 4,
    Pipe = 5,
    Aggregate = 6,
    Sphere = 7,
    Tee = 8,
    Cone = 9,
    Torus = 10,
    Construction = 11,
    FeatureTypeCount,
    AnyType = 0xFF,
  };
  enum class _TypeOfContour : unsigned __int8
  {
    CNTR_BOUND = 0,
    CNTR_HOLE = 1
  };
  //@}
  //! point cloud consts
  //@{ 
   static const _DataType NODATA                   = 0;
   static const _DataType XYZ                      = 1;
   static const _DataType INTENSITY                = 2;
   static const _DataType CLASS                    = 4;
   static const _DataType ECHO                     = 8;
   static const _DataType SCANDIRECTION            = 16;
   static const _DataType EDGEOFFLIGHTLINE         = 32;
   static const _DataType SCANANGLERANK            = 64;
   static const _DataType TIME                     = 128;
   static const _DataType RGB                      = 256;
   static const _DataType SOURCEID                 = 512;
   static const _DataType TD_CURVATURE             = 1024;
   static const _DataType TD_SPHERICAL_COORDINATES = 2048;
   static const _DataType TD_NORMAL                = 4096;
   static const _DataType TD_GEOMETRIC_POTENTIAL   = 8192;
   static const _DataType TD_DEVIATION             = 16384;
   static const _DataType TD_GEOMETRIC_FEATURE     = 32768;
   static const _DataType TD_ALL                   = 65535;

   static const _DataEncoderState _DEFAULT_SCANANGLE_RANK = 0;
   static const _DataEncoderState _EXTENDED_SCANANGLE_RANK = 1;

   static const _ViewportHandle _NO_VIEWPORT = 0;
   static const _VisualizationParamIndex _DEFAULT_PARAMS = 0;
   static const _GeometricFeatureType _NULL_FEATURE = (_GeometricFeatureType)0xFFFFFFFF;
  //@}
  //! exceptions
  //@{ 
  class _EXPORT PointCloudException
  {
  public:
    enum class CODES : unsigned __int32
    {
      UNKNOWN_ERROR = 0,
      NULL_ARGUMENT_ERROR = 1,
      INVALID_ARGUMENT_ERROR = 2,
    };

  protected:
    CODES _Code;

  public:
    PointCloudException(CODES _C = CODES::UNKNOWN_ERROR)
      : _Code(_C) {}
    ~PointCloudException() {}
    CODES asCode()
    {
      return _Code;
    }
  };
}

#endif