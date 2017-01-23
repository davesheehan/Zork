#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include<QListWidgetItem>
#include "room.h"
#include "player.h"
#include "item.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateLog(QString);
    void setUpWestWing();
    void setCurrentRoom(Room *newCurrentRoom);
    void checkValidExit(string dir);
    void updatePlayerStats(Player* currPlayer);
    void takeItem(QListWidgetItem *item);
    void updateInventory();
    void checkObjective(Room* currentRoom);

private slots:
    void on_northButton_clicked();

    void on_westButton_clicked();

    void on_eastButton_clicked();

    void on_southButton_clicked();

    void on_searchRoom_clicked();

    void on_takeItem_clicked();

    void on_inspectItem_clicked();

    void on_dropItemButton_clicked();

    void on_roomContentsList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
