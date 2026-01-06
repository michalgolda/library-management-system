#pragma once
#include <QString>

struct Entity {
    virtual QString toString() = 0;
    virtual ~Entity() = default;
};
