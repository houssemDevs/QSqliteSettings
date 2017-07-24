#ifndef QSQLITESETTINGS_H
#define QSQLITESETTINGS_H

#include "sqlite_settings_globals.h"

#include <QSettings>

/**
 * @brief The QSqliteSettings class
 * Extend the QSettings class to store settings as an sqlite database.
 * Simples keys (e.g. size, user_id, password), are stored in the settings table,
 * complex keys (e.g. server/address, user/id, user/password), are stored in
 * a table which its name is the first part of the key (e.g.: key = server/address, table = server)
 */
class SQLITESETTINGS_LIBRARY QSqliteSettings: public QSettings
{
public:
    QSqliteSettings(Scope scope = UserScope, QObject* parent = Q_NULLPTR);
    QSqliteSettings(const QString& organization,
                    const QString& application,
                    QSettings::Scope scope = QSettings::UserScope,
                    QObject* parent = Q_NULLPTR);
    ~QSqliteSettings();
};

#endif // QSQLITESETTINGS_H
