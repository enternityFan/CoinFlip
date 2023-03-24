#include "coinbutton.h"
#include <QPainter>
CoinButton::CoinButton(QWidget *parent) : QPushButton (parent)
{
     this->setStat(0);

    this->setStyleSheet("QPushButton{border:0px;}");

    connect(&this->mTimer,&QTimer::timeout,[=](){
        if (this->mStat){
            this->mFrame--;

        }
        else {
                   this->mFrame++;

        }
        QString frameName =  QString(":/res/Coin000%1.png").arg(QString::number( this->mFrame));
       this->setIcon(QIcon(frameName));
        if(this->mFrame==8 || this->mFrame == 1 ){
            this->mTimer.stop();
        }


    });
}

int CoinButton::stat() const
{
    return mStat;
}

void CoinButton::setStat(int stat)
{
    mStat = stat;
    if(mStat == 1){
        //金币
        this->setIcon(QIcon( ":/res/Coin0001.png"));

    }
    else {
        //银币
        this->setIcon(QIcon( ":/res/Coin0008.png"));

    }
    this->setIconSize(this->size());


}

void CoinButton::setStatWithAnimation(int stat)
{
    //金币翻银币的过程
    this->setStat(stat);
    if (this->stat())
    {
        this->mFrame = 8;

    }
    else {
        this->mFrame = 1;

    }
    this->mTimer.start(30);




}

void CoinButton::flip()
{
     //this->setStat( 1 - this->stat());


    this->setStatWithAnimation(!this->stat());
}

void CoinButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/res/BoardNode.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    QPushButton::paintEvent(event);
}
