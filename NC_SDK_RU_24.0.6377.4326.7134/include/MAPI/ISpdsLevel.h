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


//////////////////////////////////////////////////////////////////////////
// Отметка уровня
struct ISpdsAnker;
struct ISpdsLevel : public IMcCdEntity
{
public:
	// Текст на полке
	virtual McsString getDisplayText() = 0;                        // то, что видно на чертеже
	virtual McsString getText() = 0;
	// Комментарий под полкой
	virtual McsString getComment() = 0;
	virtual HRESULT setComment(LPCTSTR Value) = 0;
	// Значение уровня в метрах
	// Для ассоциативных отметок вычисляется из расположения отметки относительно базовой и
	// из значения в базовой отметке. setValue работает только для неассоциативных отметок.
	virtual double getValue() = 0;
	virtual HRESULT setValue(double Value) = 0;
	// Можно установить не только число, но и текст. Правда, использовать такую отметку в
	// качестве базовой - бессмысленно.
	virtual HRESULT setValue(LPCTSTR Value) = 0;
	// Ассоциативность. Если базовая отметка не задана, а ассоциативность = true,
	// значение рассчитвается от getOrigin.
	virtual bool getAssociated() = 0;
	virtual HRESULT setAssociated(bool Value) = 0;
	// Масштаб измерений для ассоциативных отметок
	virtual double getDimScale() = 0;
	virtual HRESULT setDimScale(double Value) = 0;
	// Точка начала отсчета в метрах
	virtual mcsPoint getOrigin() = 0;
	virtual HRESULT setOrigin(const mcsPoint& Value) = 0;               // вместо setOwner
	// Координаты отметки
	virtual mcsPoint getPosition() = 0;
	virtual void setPosition(const mcsPoint& Value, const mcsWorkID& idSnap = WID_NULL) = 0;
	// Направление в котором рисуется полка, на которой стоит отметка уровня
	virtual mcsVector getShelfDirection() = 0;
	virtual HRESULT setShelfDirection(const mcsVector& Value) = 0;           // вместо setOwner
	// Точка конца полки
	virtual mcsPoint getShelfEndPoint() const = 0;
	// Направление, в котором отсчитывается значение отметки от getOrigin()
	virtual mcsVector getMeasuringDirection() const = 0;
	// Положение текста
	virtual mcsPoint getTextPos() = 0;
	virtual HRESULT setTextPos(const mcsPoint& Value) = 0;
	// Положение полки: над или под линией
	virtual bool getMirrored() = 0;
	virtual HRESULT setMirrored(bool Value) = 0;
	// Получить зависимые отметки
	virtual HRESULT getReferences(mcsWorkIDArray& ids) = 0;
	// Добавить зависимую отметку. Если текущая отметка сама зависит от другой,
	// то зависимость установится от исходной. То есть, древовидный зависимостей не бывает.
	virtual HRESULT AddReference(const mcsWorkID& id) = 0;
	// Убрать зависимость от этой отметки к id
	virtual HRESULT RemoveReference(const mcsWorkID& id) = 0;
	// Убрать все зависимость от этой отметки
	virtual HRESULT RemoveAllReferenses() = 0;
	// Базовая отметка
	virtual mcsWorkID getOwner() = 0;
	virtual HRESULT setOwner(const mcsWorkID& Value) = 0;

	// Высота текста
	virtual double getTextHeight() = 0;
	virtual HRESULT setTextHeight(double Value) = 0;
	// Высота комментария
	virtual double getCommentHeight() = 0;
	virtual HRESULT setCommentHeight(double Value) = 0;
	// Стиль текста
	virtual McsString getStyleName() = 0;
	virtual HRESULT setStyleName(LPCTSTR Value) = 0;

	virtual HRESULT setAnker(ISpdsAnker* pAnker) = 0;
};




