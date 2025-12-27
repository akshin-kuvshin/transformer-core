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

#include "IMtStream.h"
#include "McsGeometry.h"
#include "McsVariant.h"

class FPoint;
struct exValue;
class mcsExValueArray;

//===========================================================================
// Extensions	for MechaniCS, implementation in McTyp.dll 
struct IMcsStream : public virtual IMtStream
{
	virtual HRESULT putSubStreamBegin(IN OUT IMcsStreamPtr& pSubStream) = 0;

  virtual HRESULT putFPoint(const FPoint& FPnt) = 0;
  virtual HRESULT putPoint(const mcsPoint&) = 0;
  virtual HRESULT putPointArray(const mcsPoint3dArray&) = 0;
  virtual HRESULT putVector(const mcsVector&) = 0;
  virtual HRESULT putVectorArray(const mcsVector3dArray&) = 0;
  virtual HRESULT putGE(const McsEntityGeometry&) = 0;
	
	// для оптимизации места и скорости можно указать fKeepOrder == false;
	// но порядок при этом будет теряться, однако скорость записи/чтения будет выще
  virtual HRESULT putGEArr(const mcsGeomEntArray&, bool fKeepOrder = true) = 0;

  virtual HRESULT putVariant(const MCSVariant&) = 0;
  virtual HRESULT putVariantArr(const mcsVariantArray&) = 0;
	virtual HRESULT putExValue(const exValue&) = 0; 
	virtual HRESULT putExValueArr(const mcsExValueArray&) = 0; 
  virtual HRESULT putMatrix(const mcsMatrix&) = 0;
  virtual HRESULT putBounds(const mcsBoundBlock&) = 0;

  virtual HRESULT getFPoint(OUT FPoint&) = 0;
  virtual HRESULT getPoint(OUT mcsPoint&) = 0;
  virtual HRESULT getPointArray(OUT mcsPoint3dArray&) = 0;
  virtual HRESULT getVector(OUT mcsVector&) = 0;
  virtual HRESULT getVectorArray(OUT mcsVector3dArray&) = 0;
  virtual HRESULT getGE(OUT McsEntityGeometry&) = 0;
  virtual HRESULT getGEArr(OUT mcsGeomEntArray&) = 0; // automatically detects array size
  virtual HRESULT getVariant(OUT MCSVariant&) = 0;
  virtual HRESULT getVariantArr(OUT mcsVariantArray&) = 0; // automatically detects array size
	virtual HRESULT getExValue(OUT exValue&) = 0; 
	virtual HRESULT getExValueArr(OUT mcsExValueArray&) = 0; 
  virtual HRESULT getMatrix(OUT mcsMatrix&) = 0;
  virtual HRESULT getBounds(OUT mcsBoundBlock&) = 0;

		// if bUseParentStreamBuffer == true, pSubStream will use a memory of this->stream,
		// (!) NOTE: The parent stream MUST BE alive while reading from 'pSubStream'
	virtual HRESULT getStream(OUT IMcsStreamPtr& pSubStream, IN OPTIONAL bool bUseParentStreamBuffer = false) = 0;
};
//===========================================================================

// Creates stream with ability to read/write complex data types
MCTYP_API HRESULT mcsCreateStream(OUT IMcsStreamPtr&, DWORD dwTypeFalgs = kMSType_Default);
