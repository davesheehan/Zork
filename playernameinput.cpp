#include "playernameinput.h"
#include "ui_playernameinput.h"
#include <string>

PlayerNameInput::PlayerNameInput(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::PlayerNameInput)
{
    ui->setupUi(this);
}

PlayerNameInput::~PlayerNameInput()
{
    delete ui;
}

void PlayerNameInput::on_startButton_clicked()
{
    this->playerName = ui->lineEdit->text().toStdString();
}

std::string PlayerNameInput::getPlayerName() const {
    return this->playerName;
}
