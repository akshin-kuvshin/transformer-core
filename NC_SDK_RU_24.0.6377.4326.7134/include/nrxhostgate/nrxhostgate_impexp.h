#pragma once
#ifdef NRXHOSTGATE_BUILD_SHARED
#define NRXDBGATE_EXPORT
#else
#ifdef NRXHOSTGATE_BUILD
#define NRXHOSTGATE_EXPORT __declspec(dllexport)
#else
#define NRXHOSTGATE_EXPORT __declspec(dllimport)
#endif //NRXHOSTGATE_BUILD
#endif //NRXHOSTGATE_BUILD_SHARED
