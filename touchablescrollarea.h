#ifndef TOUCHABLESCROLLAREA_H
#define TOUCHABLESCROLLAREA_H

#include <QScrollArea>

class TouchableScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit TouchableScrollArea(QWidget *parent = 0);

    qreal getSpeed() const;
    void setSpeed(const qreal &value);

signals:

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

public slots:

private:
    QPointF LastPos;
    qreal DecimalX;
    qreal DecimalY;
    qreal Speed;

};

#endif // TOUCHABLESCROLLAREA_H
