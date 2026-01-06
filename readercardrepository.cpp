#include <QSqlQuery>
#include "readercardrepository.h"
#include "readercardentity.h"
#include "readercardmapper.h"

ReaderCardRepository::ReaderCardRepository(QSqlDatabase db) : db(std::move(db)) {}

std::optional<ReaderCardEntity> ReaderCardRepository::getById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM readercards WHERE readercards.id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next())
    {
        return readerCardFromQuery(query);
    }

    return std::nullopt;

}

std::optional<int> ReaderCardRepository::create(ReaderCardEntity readerCard)
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO readercards (firstName, lastName, email, age)
        VALUES (:firstName, :lastName, :email, :age)
    )");
    query.bindValue(":firstName", readerCard.firstName);
    query.bindValue(":lastName", readerCard.lastName);
    query.bindValue(":email", readerCard.email);
    query.bindValue(":age", readerCard.age);

    if (query.exec())
    {
        return query.lastInsertId().toInt();
    }

    return std::nullopt;
}
