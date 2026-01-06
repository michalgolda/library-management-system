#ifndef READERCARDENTITY_H
#define READERCARDENTITY_H

#include <QString>
#include "entity.h"

struct ReaderCardEntity : Entity {
    int id;
    QString firstName;
    QString lastName;
    QString email;
    int age;

    QString toString() override
    {
        return QString("ReaderCardEntity(id=%1, firstName=%2, lastName=%3, email=%4, age=%5)").arg(id).arg(firstName).arg(lastName).arg(email).arg(age);
    }
};


#endif // READERCARDENTITY_H
