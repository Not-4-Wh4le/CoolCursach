#include "customanimal.h"
#include "ui_customanimal.h"

CustomAnimal::CustomAnimal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CustomAnimal)
{
    ui->setupUi(this);
}

CustomAnimal::~CustomAnimal()
{
    delete ui;
}

void CustomAnimal::on_comboBox_activated(int index)
{
    if(index == 0){
        qDebug() << 0;
    }
    else if(index == 1){
        qDebug() << 1;
    }
    else{
        qDebug() << 2;
    }
}

