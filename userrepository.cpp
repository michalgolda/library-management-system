#include "userrepository.h"
#include "userentity.h"
#include <utility>
#include <QSqlQuery>
#include "usermapper.h"

UserRepository::UserRepository(QSqlDatabase db) : db(std::move(db)) {}

std::optional<UserEntity> UserRepository::getByUsername(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE users.username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next())
    {
        return userFromQuery(query);
    }

    return std::nullopt;
}

std::optional<int> UserRepository::create(UserEntity user)
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO users (username, password)
        VALUES (:username, :password)
    )");
    query.bindValue(":username", user.username);
    query.bindValue(":password", user.password);

    if (query.exec())
    {
        return query.lastInsertId().toInt();
    }

    return std::nullopt;
}
