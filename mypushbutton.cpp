#include "mypushbutton.h"
#include <QPushButton>
#include <QPainter>
#include<QDebug>
#include <QPropertyAnimation>
MyPushButton::MyPushButton(QString normalImg,QString pressedImg,QWidget *parent)
    : QPushButton(parent),mNormalImg(normalImg),mPressedImg(pressedImg)
{
    mStat = Normal;
}

void MyPushButton::moveDown()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);


}

void MyPushButton::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPixmap pix;
    if(mStat==Normal)
    pix.load(this->mNormalImg);
    else {
        pix.load(this->mPressedImg);
    }
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    painter.drawText(0,0 ,this->width(),this->height(),
                     Qt::AlignHCenter|Qt::AlignVCenter,this->text());
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //鼠标按下的时候状态切换。
    this->mStat = Pressed;
    update();
    //保证信号和槽的功能
    QPushButton::mousePressEvent(e);

}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //鼠标按下的时候状态切换。
    this->mStat = Normal;
    update();
    //保证信号和槽的功能
    QPushButton::mouseReleaseEvent(e);

}
