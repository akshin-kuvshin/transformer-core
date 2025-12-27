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
#include "IMcObjects.h"
#include "IMcCutter.h"

/// Интерфейс для поддержки коннекта к площадным объектам
/// объекты поддерживающие этот интерфейс будут обрабатыватся в специальном менеджере и их ID будет попадать в монитор при
/// попадании курсора в область контура
struct IMcAreaEntity : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcAreaEntity);
	IMCS_QI_METHOD_DEFINITION(IMcAreaEntity, IMcObject);
	//Заполнить массив площадей, при попадании в которые объект будет считаться попавшим в зону действия, контура желательно простые
	virtual HRESULT GetArea(mcsPolylineArray& contours) { return E_NOTIMPL; }
	virtual HRESULT GetArea(CHoledAreaArray& contours) { return E_NOTIMPL; }
	virtual HRESULT GetInsideObjects(mcsWorkIDArray& ids) { return E_NOTIMPL; }
	// Вырезать по контуру. Внутри, если bInside == true, снаружи если bInside == false.
	virtual HRESULT Cut(const mcsPolyline& contour, bool bInside) { return E_NOTIMPL; }
};

//Класс для выбора площадных объектов, при попадании нескольких в объектов подбирает лучший по площади и истории запросов
struct IMcAreaObjectsManager
{
	virtual mcsWorkID GetObject(const mcsPoint& pnt) = 0;
	virtual mcsWorkID GetObject(const mcsPoint& pnt, const GUID& objectType) = 0;
	virtual mcsWorkID GetObject(const mcsPoint& pnt, const mcsGUIDArray& objectTypes) = 0;
	virtual HRESULT		GetObjects(mcsWorkIDArray& ids, const mcsPoint& pnt) = 0;
};


extern "C" // force undecorated names
{
	extern MECHCTL_API IMcAreaObjectsManager      *gpMcAreaManager;
}

