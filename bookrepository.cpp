#include "bookrepository.h"
#include "bookmapper.h"
#include "bookentity.h"

BookRepository::BookRepository(QSqlDatabase db) : db(std::move(db)) {}

std::optional<BookEntity> BookRepository::getById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM books WHERE books.id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next())
    {
        return bookFromQuery(query);
    }

    return std::nullopt;
}

std::optional<int> BookRepository::create(BookEntity book)
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO books (title, description, pageCount)
        VALUES (:title, :description, :pageCount)
    )");
    query.bindValue(":title", book.title);
    query.bindValue(":description", book.description);
    query.bindValue(":pageCount", book.pageCount);

    if (query.exec())
    {
        return query.lastInsertId().toInt();
    }

    return std::nullopt;
}
