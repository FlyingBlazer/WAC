#ifndef DAYLYRECORD_H
#define DAYLYRECORD_H

#include <QDialog>

namespace Ui {
class DaylyRecord;
}

class DaylyRecord : public QDialog
{
    Q_OBJECT

public:
    explicit DaylyRecord(QWidget *parent = 0);
    ~DaylyRecord();

private slots:
    void on_acceptButton_clicked();

private:
    Ui::DaylyRecord *ui;
};

#endif // DAYLYRECORD_H
