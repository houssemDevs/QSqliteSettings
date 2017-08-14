#ifndef SQLITESETTINGS_READ_WRITE_H
#define SQLITESETTINGS_READ_WRITE_H

#include <QIODevice>
#include <QTemporaryFile>
#include <QSettings>
#include "sqliteconnection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool sqliteSettingsWrite(QIODevice& device, const QSettings::SettingsMap& map) {
    QTemporaryFile file;
    if(!file.open()) {
        return false;
    }
    QString filename = file.fileName();
    file.close();
    SqliteConnection cnn(filename);
    auto db = cnn.db();
    for (auto& s: map.keys()) {
        QStringList tokens = s.split('/');
        if(tokens.count() > 1) {
            QString tableName = tokens[0];
            tokens.pop_front();
            QString key = tokens.join('/');
            QString query =
                    QString("CREATE TABLE IF NOT EXISTS %1 (Key TEXT PRIMARY KEY, Value TEXT);")
                    .arg(tableName);
            db.exec(query);
            query = QString("INSERT INTO %1 (Key,Value) Values(\"%2\",\"%3\");")
                    .arg(tableName)
                    .arg(key)
                    .arg(map.value(s).toString());
            db.exec(query);
        } else {
            db.exec("CREATE TABLE IF NOT EXISTS settings (Key TEXT PRIMARY KEY, Value TEXT);");
            db.exec(QString("INSERT INTO settings (Key,Value) Values(\"%1\",\"%2\");")
                    .arg(s)
                    .arg(map.value(s).toString()));
        }
    }
    if(!file.open()) {
        return false;
    }
    auto bytesCount = device.write(file.readAll());
    return bytesCount > 0;
}

bool sqliteSettingsRead(QIODevice& device, QSettings::SettingsMap& map) {
    QTemporaryFile file;
    if(!file.open()) {
        return false;
    }
    qDebug() << "QSqliteSettings " << file.fileName();
    file.write(device.readAll());
    file.close();
    QString filename = file.fileName();
    SqliteConnection cnn(filename);
    auto db = cnn.db();
    auto tablesNames = db.tables();
    tablesNames.removeAll("sqlite_master");
    if(tablesNames.contains("settings")) {
        QString queryStr("SELECT Key,Value FROM settings;");
        QSqlQuery query(db);
        query.setForwardOnly(true);
        if(query.exec(queryStr)) {
            while(query.next()) {
                map.insert(query.value(0).toString(), query.value(1));
            }
        } else {
            return false;
        }
        tablesNames.removeAll("settings");
    }
    for(QString table: tablesNames) {
        QString queryStr = QString("SELECT Key,Value FROM %1;")
                                  .arg(table);
        QSqlQuery query(db);
        query.setForwardOnly(true);
        if(query.exec(queryStr)) {
            while(query.next()) {
                map.insert(QString("%1/%2")
                           .arg(table)
                           .arg(query.value(0).toString()), query.value(1));
            }
        } else {
            return false;
        }
    }
    return true;
}

#endif // SQLITESETTINGS_READ_WRITE_H
