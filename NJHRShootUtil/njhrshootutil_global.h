#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NJHRSHOOTUTIL_LIB)
#  define NJHRSHOOTUTIL_EXPORT Q_DECL_EXPORT
# else
#  define NJHRSHOOTUTIL_EXPORT Q_DECL_IMPORT
# endif
#else
# define NJHRSHOOTUTIL_EXPORT
#endif
