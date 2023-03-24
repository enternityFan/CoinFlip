#include "selectscene.h"
#include<QPushButton>
#include <QPainter>
#include<QMenuBar>
#include "mypushbutton.h"
#include "playscene.h"
#include<QSound>
SelectScene::SelectScene(QWidget *parent) : MyMainWindow(parent)
{
    this->setWindowTitle("选择关卡");
    MyPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btnBack->setText("Back");
    btnBack->resize(72,32);
    connect(btnBack,&QPushButton::clicked,this,&SelectScene::backBtnClicked);
    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    const int colWidth = 70;
    const int rowHeight = 70;
    const int xoffset = 25;
    const int yoffset = 130;
    for (int i=0;i<20;++i){
        MyPushButton *btn = new MyPushButton(":/res/LevelIcon.png",":/res/LevelIcon.png",this);
        btn->setText(QString::number(i+1));
        int row = i / 4;
        int col = i % 4;
        int x = col * colWidth+xoffset;
        int y = row * rowHeight+yoffset;
        btn->resize(57,57);
        btn->move(x,y);
        connect(btn,&MyPushButton::clicked,[=](){
            PlayScene *playScene = new PlayScene(i+1);
            playScene->setAttribute(Qt::WA_DeleteOnClose);
            playScene->move(this->pos());
            playScene->show();
            this->hide();
            connect(playScene,&PlayScene::backBtnClicked,[=](){
                QSound::play(":/res/TapButtonSound.wav");
                this->show();
                this->move(playScene->pos());
                playScene->close();
            });
        });

    }

}

void SelectScene::paintEvent(QPaintEvent *event)
{

    //绘制背景图片
    QPainter painter(this);
    //搬运画家到菜单栏下面
    painter.translate(0,this->menuBar()->height());
    QPixmap pix(":/res/OtherSceneBg.png");
    QPixmap title(":/res/Title.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    painter.drawPixmap(0,0,title);
}
