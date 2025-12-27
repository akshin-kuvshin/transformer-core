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

#include "IMcObjects.h"
#include "cmnmacro.h"

//---------------------------------------------------------------------------
#define MCSCLC_SCRIPTFUNC_UPDATE      _T("UpdateCalculator")
#define MCSCLC_SCRIPTFUNC_REMOVECALC  _T("RemoveCalcConstraints")

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcCalculator - расчет в общем виде
//---------------------------------------------------------------------------
struct IMcCalculator : public IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcCalculator);
	IMCS_STD_METHOD_DEFINITION(IMcCalculator, IMcObject);

	virtual HRESULT CreateCalc(HWND hParent) = 0;
	virtual HRESULT EditCalc(HWND hParent) = 0;

	virtual HRESULT onRead(IN IMcsStream* pStream) = 0;
	virtual HRESULT onWrite(OUT IMcsStream* pStream) const = 0;

	virtual HRESULT SetValue(const MCSVariant& vValue, int iIndex) = 0;
	virtual HRESULT GetValue(MCSVariant& vValue, int iIndex) const = 0;
	virtual HRESULT SetValue(const MCSVariant& vValue, LPCTSTR stName) = 0;
	virtual HRESULT GetValue(MCSVariant& vValue, LPCTSTR stName) const = 0;

	virtual IMcReportManagerPtr GetReportManager() const = 0;

	virtual bool CanSave() const
		{ return true; };

	// Общие индексы параметров (должны поддерживаться всеми расчетами)
	enum CommonParamIndexes
	{
		piVersion       = 1000,//Версия(double/char*)
		piName          = 1001,//Имя расчета(char*)
		// 1002 - не использовать
		piStringType    = 1003,//Тип расчета(char*)
		piComment       = 1006,//Комментарий к расчету(char*)
		piParentUID1    = 1010,//UID родительского расчета 1(mcsWorkID)
		piParentUID2    = 1011,//UID родительского расчета 2(mcsWorkID)
	};

	// Общие для всех расчетов наборы параметров
	enum CommonParamSets
	{
		psAll           = 1000,//Все параметры
		psResult        = 1001,//Расчитанные параметры в порядке текущего расчета (те, что отображаются в окне результатов)
		psInit          = 1002,//Исходные данные
		psAllCalculated = 1003,
	};
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Report manager
//---------------------------------------------------------------------------
struct IMcReportManager : public IMcObject
{
	virtual HRESULT AddKeyword(LPCTSTR stKeyword, LPCTSTR stValue) = 0;
	// с вызовом диалога
	virtual HRESULT Generate(HWND hParent, LPCTSTR pStrDefTemplate = NULL, LPCTSTR pStrDefReport = NULL) = 0;
	// без вызова диалога
	virtual HRESULT Generate(LPCTSTR stTemplateFile, LPCTSTR stReportFile, HWND hParent) = 0;
	virtual HRESULT Generate(McsStringA& stResult, LPCSTR stTemplate) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcCalculatorManager - менеджер расчетов
//---------------------------------------------------------------------------
struct IMcCalculatorManager : public IMcObject
{
	virtual HRESULT Init(const GUID* piid = NULL, bool bAdd = true) = 0;
	virtual HRESULT Show(HWND hParent) = 0;
	virtual HRESULT Select(mcsWorkID& idCalc, HWND hParent) = 0;

	virtual HRESULT Exists(const mcsWorkID& idCalc) = 0;
	virtual int GetInited(mcsWorkIDArray& aidCalcs) = 0;
	virtual IMcCalculatorPtr GetCalc(const mcsWorkID& idCalc) = 0;

	virtual HRESULT InsertCalc(IMcCalculator* pCalc, mcsWorkID& idCalc) = 0;
	virtual HRESULT EditCalc(const mcsWorkID& idCalc) = 0;
	virtual HRESULT EraseCalc(const mcsWorkID& idCalc) = 0;
	virtual HRESULT UpdateCalc(const mcsWorkID& idCalc) = 0;

	virtual HRESULT LoadCalc(IMcCalculator** ppC, LPCTSTR stFileName, HWND hParent = NULL) = 0;
	virtual HRESULT SaveCalc(IMcCalculator* pC, LPCTSTR stFileName, HWND hParent = NULL) = 0;

	virtual HRESULT Register(IN LPCTSTR stType,       // Строковый тип расчета
	                         IN LPCTSTR stSubType,    // Подтип расчета (может быть NULL)
	                         IN MCSUID idStdObject,   // UID скрипта
	                         IN const GUID& iid) = 0; // IID интерфейса
};

