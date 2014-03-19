#include "sampledialog.h"
#include "ui_sampledialog.h"
#include <QEventLoop>
#include <QDesktopWidget>

SampleDialog::SampleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SampleDialog)
{
    ui->setupUi(this);
    QRect applicationGeometry=QApplication::desktop()->availableGeometry();
    this->setFixedHeight(applicationGeometry.height());
    this->setFixedWidth(applicationGeometry.width());
}

SampleDialog::~SampleDialog()
{
    delete ui;
}

void SampleDialog::on_pushButton_2_clicked()
{
    QNetworkRequest request(QUrl("https://wac-songziming.rhcloud.com/"));
    QNetworkReply *reply=manager.get(request);
    QEventLoop loop;
    connect(&manager,&QNetworkAccessManager::finished,[&loop](){loop.exit();});
    loop.exec();
    ui->textBrowser->setHtml(QString(reply->readAll()));
}
