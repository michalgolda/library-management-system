#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "userentity.h"
#include <QSqlDatabase>

class UserRepository {
public:
    explicit UserRepository(QSqlDatabase db);
    std::optional<UserEntity> getByUsername(QString username);
    std::optional<int> create(UserEntity user);
private:
    QSqlDatabase db;
};

#endif // USERREPOSITORY_H
