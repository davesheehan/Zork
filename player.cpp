#include "player.h"
#include<QString>

Player::Player(string name)
{
    setName(name);

    this->currentHealth = 0;
    setHealth(30);
    this->maxHealth = 100.0;
    this->currentCarryingWeight = 0.0;
    this->maxCarryingWeight = 100.0;
    this->endurance = 5.0;        //damage taken from attacks and environment
    this->strength = 5;           //damage dealt by attacks
}

string Player::getName() {
    return this->name;
}

double Player::getCurrHealth() {
    return currentHealth;
}

double Player::getMaxHealth() {
    return maxHealth;
}

double Player::getCurrCarryingWeight() {
    return currentCarryingWeight;
}

double Player::getMaxWeight() {
    return maxCarryingWeight;
}

double Player::getEndurance() {
    return endurance;
}

int Player::getStrength() {
    return strength;
}

void Player::setName(string name) {
    this->name = name;
}

void Player::setHealth(int input) {
    this->currentHealth += input;
    if (currentHealth > 100) currentHealth = 100;
}

void Player::setWeight(int input) {
    this->currentCarryingWeight += input;
    if(this->currentCarryingWeight < 0)
        this->currentCarryingWeight = 0;
}

void Player::addItem(Item* inItem) {
    setWeight(20);
    inventory.push_back(*inItem);
}

void Player::dropItem(QString name) {
    for(int i = 0; i < inventory.size(); i++) {
        if(name == inventory.at(i).getName()) {
            this->currentCarryingWeight -= 20;
            inventory.erase(inventory.begin() + i);
            break;
        }
    }
}

vector<Item> Player::getInventory() {
    return inventory;
}

void Player::setStrength(int newStrength) {
    this->strength = newStrength;
}

QString Player::toString() {
    QString message = "";

    message += QString::fromStdString("Name: " + getName() + "\n");
    message += QString::fromStdString("Health: ") + QString::number(getCurrHealth()) + QString::fromStdString("/") + QString::number(getMaxHealth()) + QString::fromStdString("\n");
    message += QString::fromStdString("Current Carrying Weight: ") + QString::number(getCurrCarryingWeight()) + QString::fromStdString("/") + QString::number(getMaxWeight()) + QString::fromStdString("\n");
    message += QString::fromStdString("Endurance: ") + QString::number(getEndurance()) + QString::fromStdString("\n");
    message += QString::fromStdString("Strength: ") + QString::number(getStrength());
    return message;
}
