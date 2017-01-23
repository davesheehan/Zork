#ifndef APPAREL_H
#define APPAREL_H

#include"item.h"

class Apparel : public Item
{
public:
    Apparel(string name = "Hospital Gown", string description = "This should keep me safe", int modifier = 1);
    virtual QString toString() const;

private:
    int modifier;
};

#endif // APPAREL_H
