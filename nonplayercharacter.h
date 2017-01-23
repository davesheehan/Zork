#ifndef NONPLAYERCHARACTER_H
#define NONPLAYERCHARACTER_H

#include <QString>
#include <string>
using namespace std;

class NonPlayerCharacter
{
public:
    NonPlayerCharacter(string name = "Unknown", string dialogue = "Need to get out. Need to go. Need to run.");
    QString getName();
    void setName(string);
    QString getDialogue();
    void setDialogue(string);


private:
    string name;
    string dialogue;
};

#endif // NONPLAYERCHARACTER_H
