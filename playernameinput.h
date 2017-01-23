#ifndef PLAYERNAMEINPUT_H
#define PLAYERNAMEINPUT_H

#include <QGroupBox>

namespace Ui {
class PlayerNameInput;
}

class PlayerNameInput : public QGroupBox
{
    Q_OBJECT

public:
    explicit PlayerNameInput(QWidget *parent = 0);
    ~PlayerNameInput();
    std::string getPlayerName() const;

private slots:
    void on_startButton_clicked();

private:
    Ui::PlayerNameInput *ui;
    std::string playerName;
};

#endif // PLAYERNAMEINPUT_H
