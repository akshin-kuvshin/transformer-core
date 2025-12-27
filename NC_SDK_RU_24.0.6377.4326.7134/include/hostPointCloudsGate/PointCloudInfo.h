#ifndef __POINTCLOUDINFO_H__
#define __POINTCLOUDINFO_H__

#include <map>
#include "BitSet.h"
#include "Exports.h"
#include "PointCloudDefs.h"

namespace NPC_API
{
  struct PointCloudInfoImpl;
  struct PointCloudBridgeImpl;

  class Clipping;
  class GeometricFeature;
  class VisualizationParams;
  class PointCloudInsertion;
  class PointCloudDefinition;
  class PointCloudVertexIterator;

  class PointCloudInfo
  {
    friend class NPC_API::Clipping;
    friend class NPC_API::VisualizationParams;
    friend class NPC_API::PointCloudInsertion;
    friend class NPC_API::PointCloudDefinition;
    friend struct NPC_API::PointCloudBridgeImpl;
    friend class NPC_API::PointCloudVertexIterator;

  protected:
    PointCloudInfoImpl*                           m_pImpl;

  protected:
                                                  PointCloudInfo();

  public:
    _EXPORT                                       ~PointCloudInfo();
    _EXPORT PointCloudInfo&                       operator=(const PointCloudInfo& rhs);
    _EXPORT                                       PointCloudInfo(const PointCloudInfo& rhs);
    //@}
    //! transformators
    //@{ 
    _EXPORT const _Matrix3d&                      getTransformation() const;
    _EXPORT const _Matrix3d&                      getBackTransformation() const;
     //@}
     //! extents
     //@{ 
    _EXPORT _Vector3d                             getMainAxisX() const;
    _EXPORT _Vector3d                             getMainAxisY() const;
    _EXPORT _Vector3d                             getMainAxisZ() const;
    _EXPORT _Point3d                              getMinPoint() const;
    _EXPORT _Point3d                              getMaxPoint() const;
    _EXPORT bool                                  getExtents(_Point3d&, _Point3d&) const;
     //@}
     //! meta information
     //@{ 
    _EXPORT bool                                  isDataValid(_DataType) const;
    _EXPORT _DataType                             getDataScheme() const;
    _EXPORT _DataEncoderState                     getDataEncoderState() const;
     //@}
     //! statistics
     //@{ 
    _EXPORT _CompositeIndexType                   getPointsCount() const;
    _EXPORT _NodeIndexType                        getNodesCount() const;
    _EXPORT _NodeIndexType                        getMaxNodeID() const;
    _EXPORT _TreeLevelType                        getTreeDepth() const;
    _EXPORT _PointIndexType                       getDesignationPointsInNode() const;
    _EXPORT void                                  calcTreeHistograms(std::map<_TreeLevelType, _NodeIndexType>&,
                                                                     std::map<_PointIndexType, _NodeIndexType>&) const;
     //@}
     //! sets
     //@{ 
    _EXPORT const BITSET::BitSet<_ClassType>&     getUsedClasses() const;
    _EXPORT const BITSET::BitSet<_EchoNumberType>&
                                                  getUsedEchoNumber() const;
     //@}
     //! histograms
     //@{ 
    _EXPORT const std::map<_IntencityType, _CompositeIndexType>&
                                                  getIntensityHistogram() const;
    _EXPORT const std::map<_ClassType, _CompositeIndexType>&
                                                  getClassHistogram() const;
    _EXPORT const std::map<_EchoNumberType, _CompositeIndexType>&
                                                  getEchoNumberHistogram() const;
     //@}
     //! geometric features
     //@{ 
    _EXPORT _GeometricFeatureType                 getNextGeometricFeature(_GeometricFeatureType) const;
    _EXPORT GeometricFeature                      getGeometricFeature(_GeometricFeatureType)     const;
    _EXPORT bool                                  isGeometricFeatureValid(_GeometricFeatureType) const;
    _EXPORT _GeometricFeatureType                 getFirstGeometricFeature(_TypeOfGeometricFeature type = _TypeOfGeometricFeature::AnyType) const;
    _EXPORT unsigned                              getGeometricFeaturesCount(_TypeOfGeometricFeature type = _TypeOfGeometricFeature::AnyType) const;
  };
}

#endif