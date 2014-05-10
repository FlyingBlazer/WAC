#ifndef SHOWCLIENTINFO_H
#define SHOWCLIENTINFO_H

#include <QDialog>

namespace Ui {
class ShowCLientInfo;
}

class ShowClientInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ShowClientInfo(QWidget *parent = 0);
    ~ShowClientInfo();

private:
    Ui::ShowCLientInfo *ui;
};

#endif // SHOWCLIENTINFO_H
