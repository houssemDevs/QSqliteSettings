#include "sqliteconnection.h"

#include <QThread>

SqliteConnection::SqliteConnection(const QString &filename)
{
    _connectionName = QString("SQLITE_SETTINGS_CNN_%1")
                            .arg(reinterpret_cast<int>(QThread::currentThreadId()));
    auto db = QSqlDatabase::addDatabase("QSQLITE", _connectionName);
    db.setDatabaseName(filename);
    db.open();
}

SqliteConnection::~SqliteConnection()
{
    QSqlDatabase::database(_connectionName).close();
    QSqlDatabase::removeDatabase(_connectionName);
}

QSqlDatabase SqliteConnection::db() const
{
    return QSqlDatabase::database(_connectionName, true);
}
