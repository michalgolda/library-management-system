#pragma once
#include <QSqlQuery>
#include "readercardentity.h"

inline ReaderCardEntity readerCardFromQuery(const QSqlQuery& q)
{
    ReaderCardEntity r;
    r.id = q.value("id").toInt();
    r.firstName = q.value("firstName").toString();
    r.lastName = q.value("lastName").toString();
    r.email = q.value("email").toString();
    r.age = q.value("age").toInt();
    return r;
}

