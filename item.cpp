#include "item.h"

/*Item::Item(string name, string description) {
    setName(name);
    weight = 20.0;
    setDescription(description);
}*/

QString Item::getName() const {
    return QString::fromStdString(name);
}

QString Item::getDescription() const {
    return QString::fromStdString(description);
}

double Item::getWeight() const {
    return this->weight;
}

void Item::setName(string name) {
    this->name = name;
}

void Item::setDescription(string des) {
    this->description = des;
}

QString Item::toString() const {
    return this->getName() + this->getDescription();
}

bool Item::operator ==(const Item& right) {
    if(this->getName() == right.getName())
        return true;
}
