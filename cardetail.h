#ifndef CARDETAIL_H
#define CARDETAIL_H

#include <QDialog>

namespace Ui {
class CarDetail;
}

class CarDetail : public QDialog
{
    Q_OBJECT

public:
    explicit CarDetail(QWidget *parent = 0);
    ~CarDetail();

    long getId() const;
    void setId(long value);

private:
    Ui::CarDetail *ui;
    long id;
};

#endif // CARDETAIL_H
