#ifndef BOOKENTITY_H
#define BOOKENTITY_H
#include <QString>
#include "entity.h"

struct BookEntity : Entity{
    int id;
    QString title;
    QString description;
    int pageCount;

    QString toString() override
    {
        return QString("BookEntity(id=%1, title=%2, description=%3, pageCount=%4)").arg(id).arg(title).arg(description).arg(pageCount);
    }
};

#endif // BOOKENTITY_H
