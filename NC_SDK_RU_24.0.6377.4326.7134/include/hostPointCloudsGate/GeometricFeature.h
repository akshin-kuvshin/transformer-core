#ifndef __GEOMETRICFEATURE_H__
#define __GEOMETRICFEATURE_H__

#include "Exports.h"
#include "Clipping.h"
#include "PointCloudDefs.h"

namespace NPC_API
{
  class PointCloudInfo;
  struct GeometricFeatureImpl;
  struct PipeFeature_SegmentParamImpl;

  class PlaneFeature;
  class Planes2IntersectionFeature;
  class Planes3IntersectionFeature;
  class CylinderFeature;
  class PipeFeature;
  class SphereFeature;
  class AggregateGeometricFeature;
  class TeeFeature;
  class ConeFeature;
  class TorusFeature;
  class ConstructionGeometricFeature;

  class GeometricFeature
  {
    friend class NPC_API::PlaneFeature;
    friend class NPC_API::Planes2IntersectionFeature;
    friend class NPC_API::Planes3IntersectionFeature;
    friend class NPC_API::CylinderFeature;
    friend class NPC_API::PipeFeature;
    friend class NPC_API::SphereFeature;
    friend class NPC_API::AggregateGeometricFeature;
    friend class NPC_API::TeeFeature;
    friend class NPC_API::ConeFeature;
    friend class NPC_API::TorusFeature;
    friend class NPC_API::ConstructionGeometricFeature;

    friend class NPC_API::PointCloudInfo;
    friend struct NPC_API::PointCloudBridgeImpl;

  protected:
    GeometricFeatureImpl*                         m_pImpl;

  protected:
                                                  GeometricFeature();

  public:
    _EXPORT                                       ~GeometricFeature();

    _EXPORT GeometricFeature&                     operator=(const GeometricFeature& rhs);
    _EXPORT                                       GeometricFeature(const GeometricFeature& rhs);

    _EXPORT _TypeOfGeometricFeature               getType() const;
    _EXPORT _GeometricFeatureType                 getFeature() const;
    _EXPORT double                                getDeviation() const;
    _EXPORT _CompositeIndexType                   getPopulation() const;

    _EXPORT Clipping                              asClipping() const;

    _EXPORT _GeometricFeatureType                 getFirstDependentFeature();
    _EXPORT _GeometricFeatureType                 getNextDependentFeature(_GeometricFeatureType feature);
  };

  class PlaneFeature
  {
  protected:
    PlaneFeatureImpl*                             m_pImpl;

  protected:
                                                  PlaneFeature();
                                                  PlaneFeature(const GeometricFeature& rhs);

  public:
    _EXPORT                                       ~PlaneFeature();

    _EXPORT PlaneFeature&                         operator=(const PlaneFeature& rhs);
    _EXPORT                                       PlaneFeature(const PlaneFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::Plane);
    }
    static _EXPORT PlaneFeature                   asType(const GeometricFeature& rhs);//throws PointCloudException

    _EXPORT _Point3d                              getOrigin() const;
    _EXPORT _Vector3d                             getNormal() const;
    _EXPORT unsigned __int32                      getContourCount(_TypeOfContour type) const;
    _EXPORT _Point3dArray                         getContour(unsigned __int32 number, _TypeOfContour type) const;
  };

  class Planes2IntersectionFeature
  {
  protected:
    Planes2IntersectionFeatureImpl*               m_pImpl;

  protected:
                                                  Planes2IntersectionFeature();
                                                  Planes2IntersectionFeature(const GeometricFeature& rhs);

  public:
    _EXPORT                                       ~Planes2IntersectionFeature();

    _EXPORT Planes2IntersectionFeature&           operator=(const Planes2IntersectionFeature& rhs);
    _EXPORT                                       Planes2IntersectionFeature(const Planes2IntersectionFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::TwoPlanesIntersection);
    }
    static _EXPORT Planes2IntersectionFeature     asType(const GeometricFeature& rhs);// throws PointCloudException

    _EXPORT _Point3d                              getStart() const;
    _EXPORT _Point3d                              getEnd() const;
    _EXPORT _GeometricFeatureType                 getPlane1() const;
    _EXPORT _GeometricFeatureType                 getPlane2() const;
  };

  class Planes3IntersectionFeature
  {
  protected:
    Planes3IntersectionFeatureImpl*               m_pImpl;

  protected:
                                                  Planes3IntersectionFeature();
                                                  Planes3IntersectionFeature(const GeometricFeature& rhs);

  public:
    _EXPORT                                       ~Planes3IntersectionFeature();

    _EXPORT Planes3IntersectionFeature&           operator=(const Planes3IntersectionFeature& rhs);
    _EXPORT                                       Planes3IntersectionFeature(const Planes3IntersectionFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::ThreePlanesIntersection);
    }
    static _EXPORT Planes3IntersectionFeature     asType(const GeometricFeature& rhs);// throws PointCloudException

    _EXPORT _Point3d                              getPoint() const;
    _EXPORT _GeometricFeatureType                 getPlane1() const;
    _EXPORT _GeometricFeatureType                 getPlane2() const;
    _EXPORT _GeometricFeatureType                 getPlane3() const;
  };

  class CylinderFeature
  {
  protected:
    CylinderFeatureImpl*                          m_pImpl;

  protected:
                                                  CylinderFeature();
                                                  CylinderFeature(const GeometricFeature& rhs);
  public:
    _EXPORT                                       ~CylinderFeature();

    _EXPORT CylinderFeature&                      operator=(const CylinderFeature& rhs);
    _EXPORT                                       CylinderFeature(const CylinderFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::Cylinder);
    }
    static _EXPORT CylinderFeature                asType(const GeometricFeature& rhs);// throws PointCloudException

    _EXPORT _Point3d                              getOrigin() const;
    _EXPORT _Vector3d                             getGuide() const;
    _EXPORT double                                getHeight() const;
    _EXPORT double                                getRadius() const;
  };

  class PipeFeature
  {
  protected:
    PipeFeatureImpl*                              m_pImpl;

  protected:
                                                  PipeFeature();
                                                  PipeFeature(const GeometricFeature& rhs);

  public:
    _EXPORT                                       ~PipeFeature();

    _EXPORT PipeFeature&                          operator=(const PipeFeature& rhs);
    _EXPORT                                       PipeFeature(const PipeFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::Pipe);
    }
    static _EXPORT PipeFeature                    asType(const GeometricFeature& rhs);// throws PointCloudException

    enum class _SegmentType : unsigned __int32
    {
      STRAIT_PIPE = 0,
      BEND,
      DIAMETER_CHANGE,
      FLANGE,
      SEGMENT_TYPE_COUNT
    };
    _EXPORT _SegmentType                          getTypeOfSegment() const;
    _EXPORT _Point3d                              getStart();       // start poind of pipe axe
    _EXPORT _Point3d                              getEnd();         // end point of pipe axe
    _EXPORT _Point3d                              getMid();         // Midpoint of [start,end] segment for straight pipes
                                                                    // or incoming and outgoing axes intersection for bends
    _EXPORT double                                getRadiusStart();// radius of pipe on start
    _EXPORT double                                getRadiusEnd();   // radius of pipe on end - conical segments may be represented including conical bends (not suported yet though)  };
    _EXPORT unsigned char                         getFlangeType();
   };

  class SphereFeature
  {
  protected:
    SphereFeatureImpl*                            m_pImpl;

  protected:
                                                  SphereFeature();
                                                  SphereFeature(const GeometricFeature& rhs);
  public:
    _EXPORT                                       ~SphereFeature();

    _EXPORT SphereFeature&                        operator=(const SphereFeature& rhs);
    _EXPORT                                       SphereFeature(const SphereFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::Sphere);
    }
    static _EXPORT SphereFeature                  asType(const GeometricFeature& rhs);// throws PointCloudException

    _EXPORT _Point3d                              getCenter() const;
    _EXPORT double                                getRadius() const;
  };

  class AggregateGeometricFeature
  {
  protected:
    AggregateGeometricFeatureImpl*                m_pImpl;

  protected:
                                                  AggregateGeometricFeature();
                                                  AggregateGeometricFeature(const GeometricFeature& rhs);
  public:
    _EXPORT                                       ~AggregateGeometricFeature();

    _EXPORT AggregateGeometricFeature&            operator=(const AggregateGeometricFeature& rhs);
    _EXPORT                                       AggregateGeometricFeature(const AggregateGeometricFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::Aggregate);
    }
    static _EXPORT AggregateGeometricFeature      asType(const GeometricFeature& rhs);// throws PointCloudException

    _GeometricFeatureType                         getFirstAggregatedFeature() const;
    _GeometricFeatureType                         getNextAggregatedFeature(_GeometricFeatureType) const;
  };

  class ConstructionGeometricFeature
  {
  protected:
    ConstructionGeometricFeatureImpl* m_pImpl;

  protected:
    ConstructionGeometricFeature();
    ConstructionGeometricFeature(const GeometricFeature& rhs);
  public:
    _EXPORT                                       ~ConstructionGeometricFeature();

    _EXPORT ConstructionGeometricFeature& operator=(const ConstructionGeometricFeature& rhs);
    _EXPORT                                       ConstructionGeometricFeature(const ConstructionGeometricFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::Construction);
    }
    static _EXPORT ConstructionGeometricFeature      asType(const GeometricFeature& rhs);// throws PointCloudException

    _GeometricFeatureType                         getFirstAggregatedFeature() const;
    _GeometricFeatureType                         getNextAggregatedFeature(_GeometricFeatureType) const;
  };

  class TeeFeature
  {
  protected:
    TeeFeatureImpl* m_pImpl;

  protected:
    TeeFeature();
    TeeFeature(const GeometricFeature& rhs);

  public:
    _EXPORT                                       ~TeeFeature();

    _EXPORT TeeFeature& operator=(const TeeFeature& rhs);
    _EXPORT                                       TeeFeature(const TeeFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::Tee);
    }
    static _EXPORT TeeFeature     asType(const GeometricFeature& rhs);// throws PointCloudException

    _EXPORT _Point3d                              getPoint() const;
    _EXPORT _GeometricFeatureType                 getPipe1() const;
    _EXPORT _GeometricFeatureType                 getPipe2() const;
    _EXPORT _GeometricFeatureType                 getPipe3() const;
  };

  class ConeFeature
  {
  protected:
    ConeFeatureImpl* m_pImpl;

  protected:
    ConeFeature();
    ConeFeature(const GeometricFeature& rhs);
  public:
    _EXPORT                                       ~ConeFeature();

    _EXPORT ConeFeature& operator=(const ConeFeature& rhs);
    _EXPORT                                       ConeFeature(const ConeFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::Cone);
    }
    static _EXPORT ConeFeature                asType(const GeometricFeature& rhs);// throws PointCloudException

    _EXPORT _Point3d                              getOrigin() const;
    _EXPORT _Vector3d                             getGuide() const;
    _EXPORT double                                getHeight() const;
    _EXPORT double                                getRadius1() const;
    _EXPORT double                                getRadius2() const;
  };

  class TorusFeature
  {
  protected:
    TorusFeatureImpl* m_pImpl;

  protected:
    TorusFeature();
    TorusFeature(const GeometricFeature& rhs);
  public:
    _EXPORT                                       ~TorusFeature();

    _EXPORT TorusFeature& operator=(const TorusFeature& rhs);
    _EXPORT                                       TorusFeature(const TorusFeature& rhs);

    __forceinline static bool                     isA(const GeometricFeature& rhs)
    {
      return (rhs.getType() == _TypeOfGeometricFeature::Torus);
    }
    static _EXPORT TorusFeature                asType(const GeometricFeature& rhs);// throws PointCloudException

    _EXPORT _Point3d                              getOrigin() const;
    _EXPORT _Vector3d                             getGuide() const;
    _EXPORT double                                getMinorRadius() const;
    _EXPORT double                                getMajorRadius() const;
  };

}

#endif