#include "commandbox.h"
#include "ui_commandbox.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

CommandBox::CommandBox(QWidget *parent) : QGroupBox(parent), ui(new Ui::CommandBox)
{
    ui->setupUi(this);
}

CommandBox::~CommandBox()
{
    delete ui;
}
