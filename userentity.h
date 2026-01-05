#ifndef USERENTITY_H
#define USERENTITY_H

#include <QString>

struct UserEntity {
    int id;
    QString username;
    QString password;

    bool validatePassword(QString password)
    {
        return password == this->password;
    }

    QString toString()
    {
        return QString("UserEntity(id=%1, username=%2)").arg(id).arg(username);
    }
};

#endif // USERENTITY_H
