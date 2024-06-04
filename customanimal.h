#ifndef CUSTOMANIMAL_H
#define CUSTOMANIMAL_H

#include <QWidget>

namespace Ui {
class CustomAnimal;
}

class CustomAnimal : public QWidget
{
    Q_OBJECT

public:
    explicit CustomAnimal(QWidget *parent = nullptr);
    ~CustomAnimal();

private slots:
    void on_comboBox_activated(int index);

private:
    Ui::CustomAnimal *ui;
};

#endif // CUSTOMANIMAL_H
