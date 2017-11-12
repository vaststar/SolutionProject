#ifndef FacilityUtil_global_h__
#define FacilityUtil_global_h__

#ifdef FACILITYUTIL_LIB
#define FACILITYUTIL_EXPORT _declspec(dllexport)
#else
#define FACILITYUTIL_EXPORT _declspec(dllimport)
#endif
#endif // FacilityUtil_global_h__