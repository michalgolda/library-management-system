#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H
#include <QSqlDatabase>
#include "bookentity.h"

class BookRepository {
public:
    explicit BookRepository(QSqlDatabase db);
    std::optional<BookEntity> getById(int id);
    std::optional<int> create(BookEntity book);
private:
    QSqlDatabase db;
};

#endif // BOOKREPOSITORY_H
