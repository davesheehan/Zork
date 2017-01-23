#ifndef COMMANDBOX_H
#define COMMANDBOX_H

#include <QGroupBox>

namespace Ui {
class CommandBox;
}

class CommandBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit CommandBox(QWidget *parent = 0);
    ~CommandBox();

private slots:
    void on_search_clicked();

private:
    Ui::CommandBox *ui;
};

#endif // COMMANDBOX_H
