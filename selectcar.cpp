#include "selectcar.h"
#include "ui_selectcar.h"
#include "selectwidget.h"
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
    SelectWidget *w=new SelectWidget(panel);
    panel->setWidget(w);
}

SelectCar::~SelectCar()
{
    delete ui;
}

QList<QString> SelectCar::getCarList() const
{
    return CarList;
}

void SelectCar::setCarList(const QList<QString> &value)
{
    CarList = value;
}

int SelectCar::exec()
{
    for(int i=0;i<CarList.size();i++)
    {
        static_cast<SelectWidget *>(panel->widget())->addItem(CarList.at(i));
    }
    return QDialog::exec();
}
