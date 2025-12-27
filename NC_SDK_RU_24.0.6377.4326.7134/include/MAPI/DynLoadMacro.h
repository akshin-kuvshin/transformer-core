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

#define DYN_GET_PROC_ADDRESS(FARPROC_ptrvar,ModuleName,FunctionName,CoModuleInstance) \
{                                                                                   \
  HINSTANCE hMod=NULL;                                                              \
  FARPROC_ptrvar=NULL;                                                              \
  HINSTANCE hInstLoaded=GetModuleHandle(ModuleName);                                \
  if(CoModuleInstance)                                                              \
  {                                                                                 \
    TCHAR PrevCurDir[1024];                                                         \
    TCHAR NewCurDir[1024];                                                          \
    GetCurrentDirectory(STRBUFSIZE(PrevCurDir), PrevCurDir);                        \
    unsigned long dwres=                                                            \
      GetModuleFileName(CoModuleInstance,NewCurDir, STRBUFSIZE(NewCurDir));         \
    if(dwres)                                                                       \
    {                                                                               \
      TCHAR* pslash=(TCHAR*)_tcsrchr(NewCurDir,'\\');                               \
      *pslash=0;                                                                    \
      SetCurrentDirectory(NewCurDir);                                               \
      HINSTANCE hInst_co=GetModuleHandle(ModuleName);                               \
      if(hInst_co)                                                                  \
        hInstLoaded=hInst_co;                                                       \
      else                                                                          \
        hInstLoaded=LoadLibrary(ModuleName);                                        \
      SetCurrentDirectory(PrevCurDir);                                              \
    }                                                                               \
  }                                                                                 \
  if(hInstLoaded==NULL)                                                             \
    hInstLoaded=LoadLibrary(ModuleName);                                            \
  if(hInstLoaded)                                                                   \
  {                                                                                 \
    ((FARPROC&)(FARPROC_ptrvar))=GetProcAddress(hInstLoaded,FunctionName);          \
  }                                                                                 \
}                                                                                   
