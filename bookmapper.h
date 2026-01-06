#pragma once
#include <QSqlQuery>
#include "bookentity.h"

inline BookEntity bookFromQuery(const QSqlQuery& q)
{
    BookEntity b;
    b.id = q.value("id").toInt();
    b.title = q.value("title").toString();
    b.description = q.value("description").toString();
    b.pageCount = q.value("pageCount").toInt();
    return b;
}

