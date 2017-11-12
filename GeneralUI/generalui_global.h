#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GENERALUI_LIB)
#  define GENERALUI_EXPORT Q_DECL_EXPORT
# else
#  define GENERALUI_EXPORT Q_DECL_IMPORT
# endif
#else
# define GENERALUI_EXPORT
#endif
