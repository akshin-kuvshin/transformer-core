#ifndef __RANDOMPOINTCLOUDVERTEXITERATOR_H__
#define __RANDOMPOINTCLOUDVERTEXITERATOR_H__

#include "Exports.h"
#include "PointCloudDefs.h"
#include "PointCloudVertexIterator.h"

namespace NPC_API
{
  struct RandomPointCloudVertexIteratorImpl;

  class PointCloudInsertion;
  class PointCloudDefinition;

  class RandomPointCloudVertexIterator : public PointCloudVertexIterator
  {
    friend class NPC_API::PointCloudInsertion;
    friend class NPC_API::PointCloudDefinition;
    friend struct NPC_API::PointCloudBridgeImpl;

  protected:
    RandomPointCloudVertexIteratorImpl*           m_pImpl;

  protected:
                                                  RandomPointCloudVertexIterator();

  public:
    _EXPORT virtual                               ~RandomPointCloudVertexIterator();
    _EXPORT RandomPointCloudVertexIterator&       operator=(const RandomPointCloudVertexIterator& rhs);
    _EXPORT                                       RandomPointCloudVertexIterator(const RandomPointCloudVertexIterator& rhs);

    _EXPORT double                                getXAt(_CompositeIndexType) const;
    _EXPORT double                                getYAt(_CompositeIndexType) const;
    _EXPORT double                                getZAt(_CompositeIndexType) const;
    _EXPORT bool                                  setXYZAt(_CompositeIndexType, double, double, double);
    _EXPORT _Point3d                              getVertexAt(_CompositeIndexType) const;
    _EXPORT bool                                  setVertexAt(_CompositeIndexType, const _Point3d&);

    _EXPORT _IntencityType                        getIntensityAt(_CompositeIndexType) const;
    _EXPORT bool                                  setIntensityAt(_CompositeIndexType, _IntencityType);

    _EXPORT _EchoNumberType                       getEchoNumberAt(_CompositeIndexType) const;
    _EXPORT bool                                  setEchoNumberAt(_CompositeIndexType, _EchoNumberType);

    _EXPORT _EchoCountType                        getEchoCountAt(_CompositeIndexType) const;
    _EXPORT bool                                  setEchoCountAt(_CompositeIndexType, _EchoCountType);

    _EXPORT _ScanDirectionType                    getScanDirectionAt(_CompositeIndexType) const;
    _EXPORT bool                                  setScanDirectionAt(_CompositeIndexType, _ScanDirectionType);

    _EXPORT _EdgeOfFlightLineType                 getEdgeOfFlightLineAt(_CompositeIndexType) const;
    _EXPORT bool                                  setEdgeOfFlightLineAt(_CompositeIndexType, _EdgeOfFlightLineType);

    _EXPORT _ScanAngleRankType                    getScanAngleRankAt(_CompositeIndexType) const;
    _EXPORT bool                                  setScanAngleRankAt(_CompositeIndexType, _ScanAngleRankType);

    _EXPORT _ClassType                            getClassAt(_CompositeIndexType) const;
    _EXPORT bool                                  setClassAt(_CompositeIndexType, _ClassType);

    _EXPORT _TimeType                             getTimeAt(_CompositeIndexType) const;
    _EXPORT bool                                  setTimeAt(_CompositeIndexType, _TimeType);

    _EXPORT _RGBType                              getColorRGBAt(_CompositeIndexType) const;
    _EXPORT bool                                  setColorRGBAt(_CompositeIndexType, _RGBType);

    _EXPORT _SourceIDType                         getSourceIDAt(_CompositeIndexType) const;
    _EXPORT bool                                  setSourceIDAt(_CompositeIndexType, _SourceIDType);

    _EXPORT _NormalType                           getNormalAt(_CompositeIndexType) const;
    _EXPORT bool                                  setNormalAt(_CompositeIndexType, const _NormalType&);

    _EXPORT _DeviationType                        getDeviationAt(_CompositeIndexType) const;
    _EXPORT bool                                  setDeviationAt(_CompositeIndexType, _DeviationType);

    _EXPORT _GeometricFeatureType                 getGeometricFeatureAt(_CompositeIndexType) const;
  };
}

#endif