#ifndef __EXPORTS_H__
#define __EXPORTS_H__

#if defined(_WINDOWS)
  #pragma warning( disable: 4275 4251 )
  #define _DLL_EXPORT __declspec(dllexport)
  #define _DLL_IMPORT __declspec(dllimport)
#elif defined(_UNIXOS) // GNU compiler MacOS X (xCode), unix, linex and others
  #define _DLL_EXPORT __attribute__((visibility("default")))
  #define _DLL_IMPORT __attribute__((visibility("default")))
#endif

#if defined(_MSC_VER)
  #define _TOOLKIT_EXPORT  _DLL_EXPORT
  #define _STATIC_EXPORT
  #define _TOOLKIT_IMPORT 
  #define _STATIC_IMPORT   _DLL_IMPORT
#elif defined(__BORLANDC__)
  #define _TOOLKIT_EXPORT  _DLL_EXPORT
  #define _STATIC_EXPORT
  #define _TOOLKIT_IMPORT  _DLL_IMPORT
  #define _STATIC_IMPORT
#else
  #define _TOOLKIT_EXPORT  _DLL_EXPORT
  #define _STATIC_EXPORT
  #define _TOOLKIT_IMPORT
  #define _STATIC_IMPORT   _DLL_IMPORT
#endif

#ifdef _EXPORTS
  #define _EXPORT        _TOOLKIT_EXPORT
  #define _EXPORT_STATIC _STATIC_EXPORT
#else
  #define _EXPORT        _TOOLKIT_IMPORT
  #define _EXPORT_STATIC _STATIC_IMPORT
#endif

#endif
