#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NJHRGROUPORGANIZE_LIB)
#  define NJHRGROUPORGANIZE_EXPORT Q_DECL_EXPORT
# else
#  define NJHRGROUPORGANIZE_EXPORT Q_DECL_IMPORT
# endif
#else
# define NJHRGROUPORGANIZE_EXPORT
#endif
