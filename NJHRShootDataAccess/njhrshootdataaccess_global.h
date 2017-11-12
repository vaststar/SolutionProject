#ifndef njhrshootdataaccess_global_h__
#define njhrshootdataaccess_global_h__

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NJHRSHOOTDATAACCESS_LIB)
#  define NJHRSHOOTDATAACCESS_EXPORT Q_DECL_EXPORT
# else
#  define NJHRSHOOTDATAACCESS_EXPORT Q_DECL_IMPORT
# endif
#else
# define NJHRSHOOTDATAACCESS_EXPORT
#endif
#endif // njhrshootdataaccess_global_h__
