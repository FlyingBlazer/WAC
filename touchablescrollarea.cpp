#include "touchablescrollarea.h"
#include <QMouseEvent>
#include <QScrollBar>
#include <QProcessEnvironment>
#include <QDesktopWidget>

TouchableScrollArea::TouchableScrollArea(QWidget *parent) :
    QScrollArea(parent),DecimalX(0),DecimalY(0),Speed(1)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TouchableScrollArea::mouseMoveEvent(QMouseEvent *e)
{
    // Horizontal slide
    int ValX=this->horizontalScrollBar()->value();
    int MaxX=this->horizontalScrollBar()->maximum();
    int MinX=this->horizontalScrollBar()->minimum();
    qreal RatioX=(e->pos().x()-LastPos.x())/static_cast<qreal>(this->widget()->width());
    qreal MoveX=(MaxX-MinX)*RatioX*Speed*1.35;
    if((MoveX>0?MoveX:-MoveX)<1)
    {
        DecimalX+=MoveX;
    } else
    {
        DecimalX+=MoveX-(int)MoveX;
        this->horizontalScrollBar()->setValue(ValX-(int)MoveX);
        ValX=this->horizontalScrollBar()->value();
    }
    if((DecimalX>0?DecimalX:-DecimalX)>1)
    {
        this->horizontalScrollBar()->setValue(ValX-DecimalX);
        DecimalX-=(int)DecimalX;
    }

    // Vertical slide
    int ValY=this->verticalScrollBar()->value();
    int MaxY=this->verticalScrollBar()->maximum();
    int MinY=this->verticalScrollBar()->minimum();
    qreal RatioY=(e->pos().y()-LastPos.y())/static_cast<qreal>(this->widget()->height());
    qreal MoveY=(MaxY-MinY)*RatioY*Speed*1.35;
    if((MoveY>0?MoveY:-MoveY)<1)
    {
        DecimalY+=MoveY;
    } else {
        DecimalY+=MoveY-(int)MoveY;
        this->verticalScrollBar()->setValue(ValY-(int)MoveY);
        ValY=this->verticalScrollBar()->value();
    }
    if((DecimalY>0?DecimalY:-DecimalY)>1)
    {
        this->verticalScrollBar()->setValue(ValY-(int)DecimalY);
        DecimalY-=(int)DecimalY;
    }

    LastPos=e->pos();
    QScrollArea::mouseMoveEvent(e);
}

void TouchableScrollArea::mousePressEvent(QMouseEvent *e)
{
    LastPos=e->pos();
    QScrollArea::mousePressEvent(e);
}

qreal TouchableScrollArea::getSpeed() const
{
    return Speed;
}

void TouchableScrollArea::setSpeed(const qreal &value)
{
    Speed = value;
}
