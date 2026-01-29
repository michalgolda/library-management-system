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
        )",
        R"(
            CREATE TABLE IF NOT EXISTS books (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL UNIQUE,
                description TEXT NOT NULL,
                pageCount INTEGER NOT NULL
            )
        )",
        R"(
            CREATE TABLE IF NOT EXISTS readercards (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                firstName TEXT NOT NULL,
                lastName TEXT NOT NULL,
                email TEXT NOT NULL UNIQUE,
                age INTEGER NOT NULL
            )
        )",
        R"(
            CREATE TABLE IF NOT EXISTS borrowings (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                book_id INTEGER NOT NULL,
                readercard_id INTEGER NOT NULL
    )
)"
    };
    QSqlQuery schemaQuery(db);
    for (const QString& sql : schema) {
        if (!schemaQuery.exec(sql)) {
            qDebug() << schemaQuery.lastError().text();
        }
    }
}
