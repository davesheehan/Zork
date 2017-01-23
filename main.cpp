#include "mainwindow.h"
#include "room.h"
#include <QApplication>

//Creates the main window
int main(int argc, char *argv[])
{
    QApplication mainProgram(argc, argv);

    MainWindow w;
    w.show();

    return mainProgram.exec();
}
