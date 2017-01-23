#include "apparel.h"

Apparel::Apparel(string name, string description, int modifier)
{
    this->setName(name);
    this->setDescription(description);
    this->modifier = modifier;
}

QString Apparel::toString() const {
    return QString::fromStdString("This is a weapon");
}

