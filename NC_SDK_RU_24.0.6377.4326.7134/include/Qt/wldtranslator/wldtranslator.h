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

#ifndef WLDRANSLATOR_H
#define WLDRANSLATOR_H

#include <QObject>
#include <QTranslator>
#include <QVector>


class  WldTranslator : public QTranslator 
{
	Q_OBJECT
public:
	explicit WldTranslator(QObject *parent = 0);
	QString translate(const char *context, const char *sourceText, const char *disambiguation = 0, int n = -1) const override;
	bool	isEmpty() const override;
	bool    isNonTranslatingContext(const QString& context) const;
protected:
	QStringList _nonTranslatingContextArray;

};

#endif // WLDRANSLATOR_H

