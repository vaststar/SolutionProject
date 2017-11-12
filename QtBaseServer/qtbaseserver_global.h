#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTBASESERVER_LIB)
#  define QTBASESERVER_EXPORT Q_DECL_EXPORT
# else
#  define QTBASESERVER_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTBASESERVER_EXPORT
#endif
