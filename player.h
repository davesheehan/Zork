#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include"item.h"
#include<vector>
#include<QString>
using namespace std;

//Class definition, contains prototypes
class Player
{
public:
    Player(string name = "Player");
    string getName();
    double getCurrCarryingWeight();
    double getMaxWeight();
    double getCurrHealth();
    double getMaxHealth();
    double getEndurance();
    int getStrength();
    void setStrength(int newStrength);
    void setName(string name);
    void setHealth(int input);
    void setWeight(int input);
    void addItem(Item *inItem);
    void dropItem(QString name);
    vector<Item> getInventory();
    QString toString();

private:
    string name;
    int currentHealth;
    int maxHealth;
    double currentCarryingWeight;
    double maxCarryingWeight;
    double endurance;       //damage taken from attacks and environment
    double strength;        //damage dealt with attacks
    vector<Item> inventory;

};

#endif // PLAYER_H
