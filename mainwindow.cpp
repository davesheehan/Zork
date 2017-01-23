#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "room.h"
#include "player.h"
#include "item.h"
#include "apparel.h"
#include "weapon.h"
#include "nonplayercharacter.h"

#include <iostream>
#include <string>
#include <QApplication>
#include <QPixmap>

using namespace std;

Room* currentRoom;
Player* currPlayer;
bool buttonsAdded = true;

//MainWindow constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);      //Set up GUI
    setWindowTitle("Dereliction");  //Set game title

    //Create a new player
    currPlayer = new Player();

    //Set labels to be appropriate text
    ui->nameLabel->setText(QString::fromStdString("Name: " + currPlayer->getName()));
    ui->carryingWeightLabel->setText(QString::fromStdString("Weight: ") + QString::number(currPlayer->getCurrCarryingWeight()));
    ui->healthLabel->setText(QString::fromStdString("Health: ") + QString::number(currPlayer->getCurrHealth()) +
                             QString::fromStdString("/") + QString::number(currPlayer->getMaxHealth()));

    setUpWestWing();
    updatePlayerStats(currPlayer);

    //Give player thier initial prompt
    updateLog("You awake in a hosital bed. You feel sluggish with various pains all over your body.");
    updateLog("OBJECTIVE: Find medical attention.");
}

//Updates the stats window
void MainWindow::updatePlayerStats(Player* currPlayer) {
    ui->statDisplay->setText(currPlayer->toString());
}

//MainWindow destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//Takes a string and appends it to the log
void MainWindow::updateLog(QString logInput){
    ui->mainLog->append(logInput);
}

//Create all the rooms and their pointers, add the map image to the UI
void MainWindow::setUpWestWing(){
    ui->locationLabel->setText(QString::fromStdString("Location: West Wing"));
    QPixmap lvlMap = QPixmap(":/West Wing Map.png");
    ui->mapDisplay->setPixmap(lvlMap);

    Room *startRoom, *corridorSeg1, *corridorSeg2, *corridorSeg3, *bramRoom, *kateRoom, *daveRoom, *westRoom, *northRoom;

    startRoom = new Room("Your Room");

    corridorSeg1 = new Room("Corridor");
    corridorSeg2 = new Room("Corridor");
    corridorSeg3 = new Room("Corridor");

    bramRoom = new Room("Bram's Room");
    kateRoom = new Room("Kate's Room");
    daveRoom = new Room("Dave's Room");
    westRoom = new Room("West Room");
    northRoom = new Room("North Room");

    NonPlayerCharacter bram;
    NonPlayerCharacter* bramPtr = &bram;
    bramPtr->setName("Bram");

    //Add content to rooms
    northRoom->setExits(NULL, NULL, NULL, corridorSeg3);
        northRoom->addItem(new Item("First Aid Kit"));
        northRoom->addItem(new Apparel("Doctor's Coat", "It isn't the time, but I really want to wear it...") );
        northRoom->setDescription("");

    corridorSeg1->setExits(corridorSeg2, NULL, daveRoom, startRoom);
        corridorSeg1->addItem(new Item("An IV Stand", "It's heavy, but I might have some kind of use for it..."));
        corridorSeg1->addItem(new Weapon("Bedpan"));
        corridorSeg1->setDescription("There are two doors to the left and right. The left reads 'ME@T', the right: 'Dave'. Dave has it good it seems...");

    corridorSeg2->setExits(corridorSeg3, corridorSeg1, bramRoom, westRoom);
        corridorSeg2->addItem(new Item("Waste basket"));
        corridorSeg2->addItem(new Item());
        corridorSeg2->setDescription("There are two doors to the left and right. The right reads 'BRAM', the left is blank...");

    corridorSeg3->setExits(NULL, corridorSeg2, northRoom, kateRoom);
        corridorSeg3->setDescription("There are two doors to the left and right. The right is blank, the left reads 'Kate'");
        corridorSeg3->addItem(new Apparel("Face Mask", "This place is so filthy, this might be useful..."));

    startRoom->setExits(NULL, NULL, corridorSeg1, NULL);
        startRoom->addItem(new Item("A Walking Cane", "I can hit someone with this..."));
        startRoom->addItem(new Item("Stethoscope", "I can't think of when to use this, but I really want to wear it..."));
        startRoom->addItem(new Item("First Aid Kit", "There's some stuff in here that'll make me feel better"));
        startRoom->setDescription("A standard patient's room, all the charts have my name on them. The windows are covered from the outside, I can't see out."
                                  "The walls and floor are dirty and unkept. It resembles a prison more than a hospital.\n"
                                  "Where am I?");

    westRoom->setExits(NULL, NULL, corridorSeg2, NULL);
        westRoom->addItem(new Apparel("Latex Gloves", "They won't protect me in a fight, but I have an urge to take them..."));
        westRoom->addItem(new Weapon("Surgical Hook", "It's a little rusty, but I can use this."));
        westRoom->addItem(new Item ("Organ Cooler", "Thankfully it's empty..."));
        westRoom->setDescription("No names on the door or any documents here. Looks like this room was used as storage,"
                                 " there's a lot of useful stuff here.");

    bramRoom->setExits(NULL, NULL, NULL, corridorSeg2);
        bramRoom->setDescription("This room looks like it's been lived in a long time. The occupant is handcuffed to the radiator here. "
                                 "He's got long black hair and he looks like he's been sleeping in his clothes a long time. "
                                 "Everything in the room has been moved out of his reach... is he dangerous?");
        bramRoom->addItem(new Weapon("Bedpan"));
        bramRoom->addItem(new Item(""));
        bramRoom->addPerson(bramPtr);

    kateRoom->setExits(NULL, NULL, corridorSeg3, NULL);
        kateRoom->addItem(new Item("First Aid Kit", "There's some stuff in here that'll make me feel better"));
        kateRoom->setDescription("This room is pretty delapitated. There's water leaking through the roof and the bed is overturned."
                                 "It looks like there was a struggle here recently. I guess Kate didn't want to leave...");

    daveRoom->setExits(NULL, NULL, NULL, corridorSeg1);
        daveRoom->addItem(new Item("Withering Flowers", "These have been here a long time. Looks like Tulips."));
        daveRoom->addItem(new Weapon("Scalpal", "It's a little blunt, but I can use this"));
        daveRoom->setDescription("There isn't anyone here. This room looks like it was occupied until recently."
                                 "Where did everyone go?");


    //Set the current room to the player's room on the map
    currentRoom = startRoom;
    updateInventory();
    setCurrentRoom(startRoom);
}

//Set the UI to match the current room
void MainWindow::setCurrentRoom(Room* newCurrentRoom) {
    string name = newCurrentRoom->getName();
    ui->roomLabel->setText(QString::fromStdString("Room: " + name));
    ui->contentsOfLabel->setText(QString::fromStdString("Contents of: " + name));
    ui->roomContentsList->clear();

    updatePlayerStats(currPlayer);

    //Create three buttons and connect them to slots
    QPushButton* a = new QPushButton("Inspect Room", this);
    QPushButton* b = new QPushButton("Inspect Item", this);
    QPushButton* c = new QPushButton("Take Item", this);

    QObject::connect(a, SIGNAL(clicked()), this, SLOT(on_searchRoom_clicked()));
    QObject::connect(b, SIGNAL(clicked()), this, SLOT(on_inspectItem_clicked()));
    QObject::connect(c, SIGNAL(clicked()), this, SLOT(on_takeItem_clicked()));

    //Add the buttons to the command box
    if(buttonsAdded == true) {

        ui->commandButtonBox->addWidget(a);
        ui->commandButtonBox->addWidget(b);
        ui->commandButtonBox->addWidget(c);

        buttonsAdded = false;
    }

    //Add contents to the room
    if(currentRoom->getNumberOfItems() <= 0) {
        ui->roomContentsList->addItem("There's nothing here");
    }
    else {
        for(int i = 0; i < currentRoom->getRoomItems().size(); i++) {
            ui->roomContentsList->addItem(currentRoom->getRoomItems().at(i).getName());
        }
    }

    //Set the dialogue in the dialogue window
    if(currentRoom->getNumberOfPeople() <= 0) {
        ui->speakerLabel->setText("No one in the room");
        ui->dialogueDisplay->clear();
        ui->dialogueDisplay->setText(". . . .");
    }
    else {
        checkObjective(currentRoom);
        ui->dialogueDisplay->clear();
        NonPlayerCharacter* temp = currentRoom->getPerson();
        ui->speakerLabel->setText(temp->getName() + ":");
        ui->dialogueDisplay->append(temp->getDialogue());
    }
}

//Set NPC dialogue depending if conditions have been met
void MainWindow::checkObjective(Room* currentRoom) {
    if(currPlayer->getCurrHealth() < 50) {
        currentRoom->getPerson()->setDialogue("You look pretty spaced out, are you sick or something? Go find fix yourself up, you're not going to be any help in your condition.");
    }
    else {
        //currentRoom->getPerson()->setDialogue("Great, you look better, I need to get out of these handcuffs, is there any way you can help me here?");
        currentRoom->getPerson()->setDialogue("Listen buddy, I'm not supposed to be here! They take people here and do horrible things to them, you need to help me! "
                                                "I escaped already, but they caught me and handcuffed to the radiator here.\n"
                                                "Listen, I picked the lock to the door before, I just need something to open these handcuffs. "
                                                "If you could find me a tension wrench and a pin rake I can get out of here and help you out!");
        vector <Item> playersInv = currPlayer->getInventory();
        int itemCount = 0;
        for(int i = 0; i < playersInv.size(); i++) {
            if(playersInv.at(i).getName() == "Scalpal" || playersInv.at(i).getName() == "Surgical Hook") {
                itemCount++;
                if(2 == itemCount) {
                    currentRoom->getPerson()->setDialogue("Wait! Give me those! I'm an expert at this, I can use that scalpal and hook get these handcuffs off!\n"
                                                          ". . . .\n"
                                                          "Now that that's done, I'm getting out of here!");
                    updateLog("OBJECTIVE: Bram runs from the room.");
                    updateLog("The locked door at the end of the hall is now open.");
                }
            }
        }
    }
}

//Update the items displayed on the inventory window
void MainWindow::updateInventory() {
    vector<Item> playersCurrInventory = currPlayer->getInventory();
    ui->inventoryList->clear();

    if(playersCurrInventory.size() <= 0) {
        ui->inventoryList->addItem("You aren't carrying anything");
    }
    else {
        for(int i = 0; i < playersCurrInventory.size(); i++) {
            ui->inventoryList->addItem(playersCurrInventory.at(i).getName());
        }
    }
}

//Show item description when Inspect Item is clicked
void MainWindow::on_inspectItem_clicked() {
    QListWidgetItem* item =  ui->roomContentsList->currentItem();
    if(item != NULL) {
        QString temp = item->text();
        if(temp == "There's nothing here"){
                updateLog("Thought that was clever, didn't you?");
        }
        else {
            for(int i = 0 ; i < currentRoom->getNumberOfItems(); i++) {
                if(currentRoom->getRoomItems().at(i).getName() == temp) {
                    updateLog(currentRoom->getRoomItems().at(i).getDescription());
                    break;
                }
            }
        }
    }
    else {
        updateLog("Select an item to inspect.");
    }
}

//When the Take Item button is clicked it calls takeItem
void MainWindow::on_takeItem_clicked() {
    QListWidgetItem* item =  ui->roomContentsList->currentItem();
    takeItem(item);
}

//When an item is double clicked it calls takeItem
void MainWindow::on_roomContentsList_itemDoubleClicked(QListWidgetItem *item)
{
    takeItem(item);
}

//Checks if player can add an item to inventory and adds
void MainWindow::takeItem(QListWidgetItem *item) {
    if(currPlayer->getCurrCarryingWeight() >= currPlayer->getMaxWeight())
        updateLog("I can't carry any more!");
    else {
        if(item != NULL) {
            QString temp = item->text();

            if(temp == "There's nothing here"){
                updateLog("Thought that was clever, didn't you?");
            }
            else {
                ui->roomContentsList->removeItemWidget(item);
                currentRoom->removeItem(temp);
                if(temp == "First Aid Kit") {
                    updateLog("You feel much healthier. HEALTH +10");
                    currPlayer->setHealth(10);
                    ui->healthLabel->setText(QString::fromStdString("Health: ") + QString::number(currPlayer->getCurrHealth()) +
                                             QString::fromStdString("/") + QString::number(currPlayer->getMaxHealth()));
                }
                else {
                    currPlayer->addItem(new Item(temp.toStdString()));
                    updateLog(temp + " is now in your inventory.");
                }
                updateInventory();
                setCurrentRoom(currentRoom);
                ui->carryingWeightLabel->setText(QString::fromStdString("Weight: ") + QString::number(currPlayer->getCurrCarryingWeight()));

            }
        }
        else {
            updateLog("Select an item to take.");
        }
    }
}

//Displays the room description when Inspect Room is clicked
void MainWindow::on_searchRoom_clicked() {
    updateLog(currentRoom->getDescription());
}

//Directional buttons
void MainWindow::on_northButton_clicked()
{
    updateLog("Moving North.");
    checkValidExit("North");
}

void MainWindow::on_westButton_clicked()
{
    updateLog("Moving West.");
    checkValidExit("West");
}

void MainWindow::on_eastButton_clicked()
{
    updateLog("Moving East.");
    checkValidExit("East");
}

void MainWindow::on_southButton_clicked()
{
    updateLog("Moving South.");
    checkValidExit("South");
}

//checks if the room has an exit in the direction specified
void MainWindow::checkValidExit(string dir) {
    if(currentRoom->hasExit(dir) == true) {
        updateLog(QString::fromStdString("There is a " + dir + " Exit, which you take."));
        currentRoom = currentRoom->takeExit(dir);
        setCurrentRoom(currentRoom);
    }
    else
        updateLog("Can't leave through here, better check the map.");
}

//Removes item from inventory if valid
void MainWindow::on_dropItemButton_clicked()
{
    QListWidgetItem* item =  ui->inventoryList->currentItem();
    if(item != NULL) {
        QString temp = item->text();
        if(temp == "You aren't carrying anything"){
                updateLog("Thought that was clever, didn't you?");
        }
        else {
            currPlayer->dropItem(temp);
            ui->inventoryList->removeItemWidget(item);
            currentRoom->addItem(new Item(temp.toStdString(), "I dropped this here earlier..."));
            updateLog("You dropped " + temp);
            updateInventory();
            setCurrentRoom(currentRoom);
            ui->carryingWeightLabel->setText(QString::fromStdString("Weight: ") + QString::number(currPlayer->getCurrCarryingWeight()));
        }
    }
    else {
        updateLog("Select an item to drop.");
    }
}
