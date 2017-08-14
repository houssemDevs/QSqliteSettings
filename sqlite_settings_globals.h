#ifndef SQLITE_SETTINGS_GLOBALS_H
#define SQLITE_SETTINGS_GLOBALS_H

#include <qglobal.h>

#if defined SQLITESETTINGS_STATIC
#   define SQLITESETTINGS_LIBRARY
#elif defined SQLITESETTINGS_SHARED
#   define SQLITESETTINGS_LIBRARY Q_DECL_EXPORT
#else
#   define SQLITESETTINGS_LIBRARY Q_DECL_IMPORT
#endif

#endif // SQLITE_SETTINGS_GLOBALS_H
