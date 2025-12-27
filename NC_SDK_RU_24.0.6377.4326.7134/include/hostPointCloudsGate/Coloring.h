#ifndef __COLORING_H__
#define __COLORING_H__

#include "Exports.h"
#include "PointCloudDefs.h"

namespace NPC_API
{
  struct ColoringImpl;
  class VisualizationParams;

  class ColoringWithColor;
  class ColoringByElevation;
  class ColoringByIntensity;
  class ColoringByEchoNumber;
  class ColoringByCode;
  class ColoringWithDefaultColor;
  class ColoringBySourceId;
  class ColoringByDeviation;
  class ColoringByNormals;
  class ColoringByFeatures;
  class ColoringByFeatureTypes;
  //@}
  //! base wrapper
  //@{ 
  class Coloring
  {
    friend class NPC_API::ColoringWithColor;
    friend class NPC_API::ColoringByElevation;
    friend class NPC_API::ColoringByIntensity;
    friend class NPC_API::ColoringByEchoNumber;
    friend class NPC_API::ColoringByCode;
    friend class NPC_API::ColoringWithDefaultColor;
    friend class NPC_API::ColoringBySourceId;
    friend class NPC_API::ColoringByDeviation;
    friend class NPC_API::ColoringByNormals;
    friend class NPC_API::ColoringByFeatures;
    friend class NPC_API::ColoringByFeatureTypes;

    friend class NPC_API::VisualizationParams;
    friend struct NPC_API::PointCloudBridgeImpl;

  protected:
    ColoringImpl*                                 m_pImpl;

  public:
    _EXPORT                                       Coloring();
    _EXPORT virtual                               ~Coloring();

    _EXPORT                                       Coloring(const Coloring& rhs);
    _EXPORT Coloring&                             operator=(const Coloring& rhs);

    enum class _ColoringType : unsigned __int32
    {
      DEFAULT = 0,
      WITH_COLOR = 1,
      BY_ELEVATION = 2,
      BY_INTENSITY = 3,
      BY_ECHO = 4,
      BY_CODE = 5,
      BY_DEFAULT_COLOR = 6,
      BY_SOURCE_ID = 7,
      BY_DEVIATION = 8,
      BY_NORMAL = 9,
      BY_FEATURES = 10,
      BY_FEATURE_TYPES = 11,
    };
    _EXPORT _ColoringType                         getType() const;
  };
  //@}
  //! trivial coloring
  //@{ 
  class ColoringWithColor : public Coloring
  {
  protected:
                                                  ColoringWithColor() {}
  public:
    _EXPORT                                       ColoringWithColor(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringWithColor() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::WITH_COLOR);
    }
    static _EXPORT ColoringWithColor              asType(const Coloring& rhs);//throws PointCloudException

    _EXPORT _RGBType                              getColor() const;
    _EXPORT void                                  setColor(_RGBType);
  };
  //@}
  //! elevation coloring
  //@{ 
  class ColoringByElevation : public Coloring
  {
  protected:
                                                  ColoringByElevation() {}
  public:
    _EXPORT                                       ColoringByElevation(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringByElevation() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::BY_ELEVATION);
    }
    static _EXPORT ColoringByElevation            asType(const Coloring& rhs);//throws PointCloudException

    enum class _ElevationColoringScheme : unsigned __int32
    {
      DEFAULT = 1,
      CUSTOM_COLOR = 2,
      CUSTOM_Z = 3,
      CUSTOM_COLOR_Z = 4
    };
    _EXPORT _ElevationColoringScheme              getColoringScheme() const;
    _EXPORT void                                  setColoringScheme(_ElevationColoringScheme);
    _EXPORT unsigned                              getNumberOfElevationIntervalParts() const;
    _EXPORT void                                  setElevationColor(unsigned, _RGBType);
    _EXPORT _RGBType                              getElevationColor(unsigned) const;
    _EXPORT double                                getStartElevation() const;
    _EXPORT double                                getEndElevation() const;
  };
  //@}
  //! intensity coloring
  //@{ 
  class ColoringByIntensity : public Coloring
  {
  protected:
                                                  ColoringByIntensity() {}

  public:
    _EXPORT                                       ColoringByIntensity(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringByIntensity() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::BY_INTENSITY);
    }
    static _EXPORT ColoringByIntensity            asType(const Coloring& rhs);//throws PointCloudException

    enum class _IntensityColoringScheme : unsigned __int32
    { 
      DEFAULT = 1,
      CUSTOM_COLOR = 2,
      CUSTOM_INTERVAL = 3,
      CUSTOM_INTERVAL_COLOR = 4
    };
    _EXPORT _IntensityColoringScheme              getColoringScheme() const;
    _EXPORT void                                  setColoringScheme(_IntensityColoringScheme);
    _EXPORT unsigned                              getNumberOfIntensityIntervalParts() const;
    _EXPORT void                                  setIntensityIndexColor(unsigned, _RGBType);
    _EXPORT _RGBType                              getIntensityIndexColor(unsigned) const;
    _EXPORT double                                getStartIntensity() const;
    _EXPORT double                                getEndIntensity() const;
  };
  //@}
  //! echo coloring
  //@{ 
  class ColoringByEchoNumber : public Coloring
  {
  protected:
                                                  ColoringByEchoNumber() {}

  public:
    _EXPORT                                       ColoringByEchoNumber(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringByEchoNumber() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::BY_ECHO);
    }
    static _EXPORT ColoringByEchoNumber           asType(const Coloring& rhs);//throws PointCloudException

    enum class _EchoNumberColoringScheme : unsigned __int32
    {
      DEFAULT = 1,
      CUSTOM = 2,
    };
    _EXPORT _EchoNumberColoringScheme             getColoringScheme() const;
    _EXPORT void                                  setColoringScheme(_EchoNumberColoringScheme);
    _EXPORT unsigned                              getEchoNumberCount() const;
    _EXPORT void                                  setEchoNumberColor(_EchoNumberType, _RGBType) const;
    _EXPORT _RGBType                              getEchoNumberColor(_EchoNumberType);
    _EXPORT void                                  addNewEchoNumber(_EchoNumberType, _RGBType);
    _EXPORT _EchoNumberType                       getEchoNumberByIndex(unsigned) const;
    _EXPORT _RGBType                              getEchoNumberIndexColor(unsigned) const;
    _EXPORT void                                  setEchoNumberIndexColor(unsigned, _RGBType);
  };
  //@}
  //! code coloring
  //@{ 
  class ColoringByCode : public Coloring
  {
  protected:
                                                  ColoringByCode() {}

  public:
    _EXPORT                                       ColoringByCode(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringByCode() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::BY_CODE);
    }
    static _EXPORT ColoringByCode                 asType(const Coloring& rhs);//throws PointCloudException

    enum class _CodeColoringScheme : unsigned __int32
    {
      DEFAULT = 1,
      CUSTOM = 2,
    };
    _EXPORT _CodeColoringScheme                   getColoringScheme() const;
    _EXPORT void                                  setColoringScheme(_CodeColoringScheme);
    _EXPORT unsigned                              getCodesCount() const;
    _EXPORT _RGBType                              getCodeColor(_ClassType) const;
    _EXPORT void                                  setCodeColor(_ClassType, _RGBType);
    _EXPORT void                                  addNewCode(_ClassType, _RGBType);
    _EXPORT _ClassType                            getCodeByIndex(unsigned) const;
    _EXPORT _RGBType                              getCodeIndexColor(unsigned) const;
    _EXPORT void                                  setCodeIndexColor(unsigned, _RGBType);
  };
  //@}
  //! rgb coloring
  //@{ 
  class ColoringWithDefaultColor : public Coloring
  {
  protected:
                                                  ColoringWithDefaultColor() {}

  public:
    _EXPORT                                       ColoringWithDefaultColor(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringWithDefaultColor() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::BY_DEFAULT_COLOR);
    }
    static _EXPORT ColoringWithDefaultColor       asType(const Coloring& rhs);//throws PointCloudException
  };
  //@}
  //! source id coloring
  //@{ 
  class ColoringBySourceId : public Coloring
  {
  protected:
                                                  ColoringBySourceId() {}

  public:
    _EXPORT                                       ColoringBySourceId(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringBySourceId() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::BY_SOURCE_ID);
    }
    static _EXPORT ColoringBySourceId             asType(const Coloring& rhs);//throws PointCloudException
  };
  //@}
  //! deviation coloring
  //@{ 
  class ColoringByDeviation : public Coloring
  {
  protected:
                                                  ColoringByDeviation() {}

  public:
    _EXPORT                                       ColoringByDeviation(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringByDeviation() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::BY_DEVIATION);
    }
    static _EXPORT ColoringByDeviation            asType(const Coloring& rhs);//throws PointCloudException

    _EXPORT bool                                  isDefaultColoring() const;
    _EXPORT bool                                  isCustomColoring() const;
    _EXPORT void                                  resetColoring();
    _EXPORT double                                getMinDistance() const;
    _EXPORT double                                getMaxDistance() const;
    _EXPORT double                                getTolerance() const;
    _EXPORT unsigned                              getNumberOfIntervals() const;
    _EXPORT void                                  scaleParams(float, float, unsigned, float);
    _EXPORT unsigned                              getStartInterval() const;
    _EXPORT unsigned                              getEndInterval() const;
    _EXPORT void                                  setInterval(unsigned, unsigned);
    _EXPORT float                                 getIntervalStart(unsigned) const;
    _EXPORT float                                 getIntervalEnd(unsigned) const;
    _EXPORT _RGBType                              getIntervalColor(unsigned) const;
    _EXPORT void                                  setIntervalColor(unsigned, _RGBType);
  };
  //@}
  //! normals coloring
  //@{ 
  class ColoringByNormals : public Coloring
  {
  protected:
                                                  ColoringByNormals() {}

  public:
    _EXPORT                                       ColoringByNormals(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringByNormals() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::BY_NORMAL);
    }
    static _EXPORT ColoringByNormals              asType(const Coloring& rhs);//throws PointCloudException

    enum class _NormalsColoringScheme : unsigned __int32
    {
      DEFAULT = 0,
      BI_DIRECTIONAL_COLORS = 1,
    };
    _EXPORT _NormalsColoringScheme                getColoringScheme() const;
    _EXPORT void                                  setColoringScheme(_NormalsColoringScheme value);
    _EXPORT bool                                  getShowNormalsAsVectors() const;
    _EXPORT void                                  setShowNormalsAsVectors(bool value);
  };
  //@}
  //! features coloring
  //@{ 
  class ColoringByFeatures : public Coloring
  {
  protected:
                                                  ColoringByFeatures() {}

  public:
    _EXPORT                                       ColoringByFeatures(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringByFeatures() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::BY_NORMAL);
    }
    static _EXPORT ColoringByFeatures             asType(const Coloring& rhs);//throws PointCloudException

    _EXPORT unsigned                              getFeaturesCount() const;
    _EXPORT _RGBType                              getFeatureColor(_GeometricFeatureType _feature) const;
    _EXPORT void                                  setFeatureColor(_GeometricFeatureType _feature, _RGBType _color);
    _EXPORT void                                  addNewFeature(_GeometricFeatureType _feature);
    _EXPORT void                                  addNewFeature(_GeometricFeatureType _feature, _RGBType _color);
    _EXPORT _GeometricFeatureType                 getFeatureByIndex(unsigned _index) const;
    _EXPORT _RGBType                              getFeatureIndexColor(unsigned _index) const;
    _EXPORT bool                                  setFeatureIndexColor(unsigned _index, _RGBType _color);
  };
  //@}
  //! feature type coloring
  //@{ 
  class ColoringByFeatureTypes : public Coloring
  {
  protected:
                                                  ColoringByFeatureTypes() {}

  public:
    _EXPORT                                       ColoringByFeatureTypes(NcApDocument* _pDocument);//throws PointCloudException
    _EXPORT virtual                               ~ColoringByFeatureTypes() {}

    __forceinline static bool                     isA(const Coloring& rhs)
    {
      return (rhs.getType() == Coloring::_ColoringType::BY_NORMAL);
    }
    static _EXPORT ColoringByFeatureTypes         asType(const Coloring& rhs);//throws PointCloudException

    enum class _FeatureTypesColoringScheme : unsigned __int32
    {
      DEFAULT = 1,
      CUSTOM = 2,
    };
    _EXPORT _FeatureTypesColoringScheme           getColoringScheme() const;
    _EXPORT void                                  resetColoringScheme();
    _EXPORT unsigned                              getFeatureTypesCount() const;
    _EXPORT _RGBType                              getFeatureTypeColor(_GeometricFeatureType _feature) const;
    _EXPORT void                                  setFeatureTypeColor(_GeometricFeatureType _feature, _RGBType _color);
    _EXPORT void                                  addNewFeatureType(_GeometricFeatureType _feature);
    _EXPORT void                                  addNewFeatureType(_GeometricFeatureType _feature, _RGBType _color);
    _EXPORT _TypeOfGeometricFeature               getFeatureTypeByIndex(unsigned _index) const;
    _EXPORT _RGBType                              getFeatureTypeIndexColor(unsigned _index) const;
    _EXPORT bool                                  setFeatureTypeIndexColor(unsigned _index, _RGBType _color);
  };
}

#endif