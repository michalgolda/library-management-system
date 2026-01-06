#ifndef READERCARDREPOSITORY_H
#define READERCARDREPOSITORY_H
#include <QSqlDatabase>
#include "readercardentity.h"

class ReaderCardRepository {
public:
    explicit ReaderCardRepository(QSqlDatabase db);
    std::optional<ReaderCardEntity> getById(int id);
    std::optional<int> create(ReaderCardEntity readerCard);
private:
    QSqlDatabase db;
};

#endif // READERCARDREPOSITORY_H
