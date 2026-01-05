#pragma once
#include <QSqlQuery>
#include "userentity.h"

inline UserEntity userFromQuery(const QSqlQuery& q)
{
    UserEntity u;
    u.id = q.value("id").toInt();
    u.username = q.value("username").toString();
    u.password = q.value("password").toString();
    return u;
}
