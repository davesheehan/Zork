#include "nonplayercharacter.h"

NonPlayerCharacter::NonPlayerCharacter(string name, string dialogue)
{
    this->name = name;
    this->dialogue = dialogue;
}

QString NonPlayerCharacter::getName() {
    return QString::fromStdString( this->name );
}

QString NonPlayerCharacter::getDialogue() {
    return QString::fromStdString( this->dialogue );
}

void NonPlayerCharacter::setDialogue(const string input ) {
    this->dialogue = input;
}

void NonPlayerCharacter::setName( const string input ) {
    this->name = input;
}
