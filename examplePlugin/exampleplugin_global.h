#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EXAMPLEPLUGIN_LIB)
#  define EXAMPLEPLUGIN_EXPORT Q_DECL_EXPORT
# else
#  define EXAMPLEPLUGIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define EXAMPLEPLUGIN_EXPORT
#endif
