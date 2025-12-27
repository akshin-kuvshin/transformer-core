#pragma once
#ifdef NRXDBGATE_BUILD_SHARED
#define NRXDBGATE_EXPORT
#else
#ifdef NRXDBGATE_BUILD
#define NRXDBGATE_EXPORT __declspec(dllexport)
#else
#define NRXDBGATE_EXPORT __declspec(dllimport)
#endif //nrxdbgate_BUILD
#endif //NRXDBGATE_BUILD_SHARED