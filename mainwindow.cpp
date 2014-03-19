#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sampledialog.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect applicationGeometry=QApplication::desktop()->availableGeometry();
    this->setFixedHeight(applicationGeometry.height());
    this->setFixedWidth(applicationGeometry.width());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    SampleDialog dialog;
    dialog.exec();
}
