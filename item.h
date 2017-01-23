#ifndef ITEM_H
#define ITEM_H

#include<QString>
#include <string>
using namespace std;

class Item
{
public:
    Item(string name = "Medical items", string description = "An assortment of clutter, not very useful."): name(name), description(description){}
    QString getName() const;
    void setName(string name);
    double getWeight() const;
    QString getDescription() const;
    void setDescription(string des);
    virtual QString toString() const;

    bool operator ==(const Item& right);

private:
    string name;
    double weight;
    string description;
};

#endif // ITEM_H
