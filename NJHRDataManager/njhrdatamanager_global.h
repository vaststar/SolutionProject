#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NJHRDATAMANAGER_LIB)
#  define NJHRDATAMANAGER_EXPORT Q_DECL_EXPORT
# else
#  define NJHRDATAMANAGER_EXPORT Q_DECL_IMPORT
# endif
#else
# define NJHRDATAMANAGER_EXPORT
#endif
