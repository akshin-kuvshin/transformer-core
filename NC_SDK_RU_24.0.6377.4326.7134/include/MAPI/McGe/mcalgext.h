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

class  McGeCompositeCurve3d;
struct McGeCurve3dOffsetData;
class  McGeCompositeCurve2d;
struct McGeCurve2dOffsetData;

class McGeOffsetCurve3d;
class McGeNurbCurve3d;

struct IMcGeomAlgoExtension
{
	virtual HRESULT getContourTrimmedOffset(IN const McGeCompositeCurve3d& contour, IN OUT McGeCurve3dOffsetData& ofsData, bool bStoreAsTestSample) {
		return E_NOTIMPL;
	}

	virtual int gto_test_getSamplesNumber() {
		return 0;
	}

	virtual HRESULT gto_test_doTestSample(int idxSample) {
		return E_NOTIMPL;
	}

	// dtol = -1 means "don't care", choose a context-dependent tolerance
	virtual HRESULT approxOffsetCurveByNURBs(IN const McGeOffsetCurve3d& ofsCrv, OUT McGeNurbCurve3d*& pApproxSpline, IN OPTIONAL double dtol = -1) {
		return E_NOTIMPL;
	}
};

extern "C" MCGEL_API IMcGeomAlgoExtension* gpGeomAlgoExt;
