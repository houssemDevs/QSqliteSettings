#include "qsqlitesettings.h"
#include "sqlitesettings_read_write.h"
#include <QCoreApplication>

QSqliteSettings::QSqliteSettings(Scope scope, QObject *parent):
    QSettings(registerFormat("sdb",sqliteSettingsRead,sqliteSettingsWrite),
              scope,
              QCoreApplication::organizationName(),
              QCoreApplication::applicationName(),
              parent)
{
}

QSqliteSettings::QSqliteSettings(const QString &organization, const QString &application, QSettings::Scope scope, QObject *parent):
    QSettings(QSettings::registerFormat("sdb",sqliteSettingsRead,sqliteSettingsWrite),
              scope,
              organization,
              application,
              parent)
{
}

QSqliteSettings::~QSqliteSettings()
{
}
