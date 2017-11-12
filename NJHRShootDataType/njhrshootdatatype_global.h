#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NJHRSHOOTDATATYPE_LIB)
#  define NJHRSHOOTDATATYPE_EXPORT Q_DECL_EXPORT
# else
#  define NJHRSHOOTDATATYPE_EXPORT Q_DECL_IMPORT
# endif
#else
# define NJHRSHOOTDATATYPE_EXPORT
#endif
