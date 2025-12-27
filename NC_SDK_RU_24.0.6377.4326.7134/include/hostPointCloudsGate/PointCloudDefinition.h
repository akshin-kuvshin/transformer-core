#ifndef __POINTCLOUDDEFINITION_H__
#define __POINTCLOUDDEFINITION_H__

#include "Exports.h"
#include "PointCloudDefs.h"
#include "PointCloudInfo.h"
#include "VisualizationParams.h"
#include "PointCloudVertexIterator.h"

namespace NPC_API
{
  class PointCloudBridge;
  class PointCloudInsertion;
  struct PointCloudDefinitionImpl;

  class PointCloudDefinition
  {
    friend struct NPC_API::PointCloudBridgeImpl;
    friend class NPC_API::PointCloudInsertion;
    friend class NPC_API::PointCloudBridge;

  protected:
    PointCloudDefinitionImpl*                     m_pImpl;

  protected:
                                                  PointCloudDefinition();

  public:
    _EXPORT                                       ~PointCloudDefinition();
    _EXPORT PointCloudDefinition&                 operator=(const PointCloudDefinition& rhs);
    _EXPORT                                       PointCloudDefinition(const PointCloudDefinition& rhs);
    //@}
    //! file
    //@{ 
    _EXPORT bool                                  isLoaded() const;
    _EXPORT bool                                  isNotFound() const;
    _EXPORT bool                                  isLoadProvided() const;
    _EXPORT void                                  provideLoading(bool);
    _EXPORT bool                                  isFreezed() const;
    _EXPORT void                                  setFreezed(bool);
    _EXPORT bool                                  isUsingAbsoluteFilePath() const;
    _EXPORT void                                  setUsingAbsoluteFilePath(bool);
    _EXPORT std::wstring                          getCloudFileName() const;
    _EXPORT void                                  saveCloudFile(const std::wstring&);
    _EXPORT void                                  changeCloudFile(const std::wstring&);
    //@}
    //! point cloud name
    //@{ 
    _EXPORT std::wstring                          getName() const;
    _EXPORT bool                                  setName(const std::wstring&);
    //@}
    //! transforms
    //@{ 
    _EXPORT bool                                  isTransformProtected() const;
    _EXPORT bool                                  setTransformProtected(bool);
    _EXPORT bool                                  transformBy(const _Matrix3d&);
    //@}
    //! insertions
    //@{ 
    _EXPORT bool                                  hasInsertions() const;
    _EXPORT unsigned int                          InsertionsCount() const;
    //@}
    //! iterators
    //@{ 
    _EXPORT PointCloudVertexIterator              getAllVertexIterator(_VisualizationParamIndex _paramsIndex = _DEFAULT_PARAMS,
                                                                       bool _bUpdateOnReleasing = true, bool _bProgress = false);
    _EXPORT PointCloudVertexIterator              getHybridVertexIterator(const Clipping& _Clipping,
                                                                          _VisualizationParamIndex _paramsIndex = _DEFAULT_PARAMS,
                                                                          bool _bUpdateOnReleasing = true, bool _bProgress = false);
    _EXPORT PointCloudVertexIterator              getLevelVertexIterator(_TreeLevelType _level, bool _onlyPointsOfThisLevel,
                                                                         _VisualizationParamIndex _paramsIndex = _DEFAULT_PARAMS,
                                                                         bool _bUpdateOnReleasing = true, bool _bProgress = false);
    //@}
    //! point cloud information
    //@{ 
    _EXPORT PointCloudInfo                        getCloudInfo(_VisualizationParamIndex _paramsIndex = _DEFAULT_PARAMS) const;
    _EXPORT _TreeLevelType                        getTreeLevelCount() const;
    //@}
    //! meta information
    //@{ 
    _EXPORT bool                                  updateTypesOfMetaData(_DataType _cOriginalDataValid = XYZ, bool _bProgress = false);
    _EXPORT bool                                  updateMetaDataEncoder(_DataEncoderState in_eDataEncoderState = _DEFAULT_SCANANGLE_RANK, bool _bProgress = false);
  };
}

#endif