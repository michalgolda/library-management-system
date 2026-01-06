#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

inline void initSchema(QSqlDatabase db)
{
    QStringList schema = {
        R"(
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT NOT NULL UNIQUE,
                password TEXT NOT NULL
            )
        )"
    };
    QSqlQuery schemaQuery;
    for (const QString& sql : schema) {
        if (!schemaQuery.exec(sql)) {
            qDebug() << schemaQuery.lastError().text();
        }
    }
}
