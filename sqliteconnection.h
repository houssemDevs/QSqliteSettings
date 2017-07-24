#ifndef SQLITECONNECTION_H
#define SQLITECONNECTION_H

#include <QString>
#include <QSqlDatabase>

class SqliteConnection
{
public:
    SqliteConnection(const QString& filename);
    ~SqliteConnection();

    QSqlDatabase db() const;

private:
    QString _connectionName;
};

#endif // SQLITECONNECTION_H
