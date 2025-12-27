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

#ifndef _HOSTQT_H_
#define _HOSTQT_H_

#include "QWidget"
#include "hostUI.h"

#include "Qt/qtwinmigrate/qwinwidget.h"

#ifndef HOSTQT_API
  #ifdef HOSTQT_API_INTERNAL
    #define HOSTQT_API  __declspec(dllexport)
  #else
    #define HOSTQT_API  __declspec(dllimport)
  #endif
#endif

class HOSTQT_API hostQtPalette : public hostUiPalette
{
  DECLARE_DYNAMIC(hostQtPalette)

public:
  hostQtPalette();
  virtual ~hostQtPalette();

  BOOL Create(DWORD dwStyle, LPCTSTR pszName, hostUiPaletteSet* pParent, DWORD dwPaletteStyle = 0);

  QWidget *paletteWidget();

  bool CanFrameworkTakeFocus() { return false; };

protected:
  afx_msg void    OnSize(UINT nType, int cx, int cy);

  QWinWidget *m_pWinWidget;

  DECLARE_MESSAGE_MAP()
};

#endif // _HOSTQT_H_

