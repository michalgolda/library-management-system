#ifndef USERENTITY_H
#define USERENTITY_H

#include <QString>
#include "entity.h"

struct UserEntity : Entity {
    int id;
    QString username;
    QString password;

    bool validatePassword(QString password)
    {
        return password == this->password;
    }

    QString toString() override
    {
        return QString("UserEntity(id=%1, username=%2)").arg(id).arg(username);
    }
};

#endif // USERENTITY_H
