#include "selectcar.h"
#include "ui_selectcar.h"
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QProcessEnvironment>
#include <QLabel>

SelectCar::SelectCar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectCar)
{
    ui->setupUi(this);
    if(QProcessEnvironment::systemEnvironment().value("OS")!=QString("Windows_NT"))
    {
        QRect applicationGeometry=QApplication::desktop()->availableGeometry();
        this->setFixedSize(applicationGeometry.size());
    }
    panel=new TouchableScrollArea(this);
    ui->verticalLayout->insertWidget(0,panel);
    QWidget *w=new QWidget(panel);
    QVBoxLayout *layout=new QVBoxLayout(w);
    w->setLayout(layout);
    for(int i=0;i<100;i++)
    {
        layout->addWidget(new QLabel(QString::number(i)));
    }
    panel->setWidget(w);
}

SelectCar::~SelectCar()
{
    delete ui;
}
