#include "startscene.h"
#include<QPushButton>
#include"mypushbutton.h"
#include<QTimer>
#include<QSound>
StartScene::StartScene(QWidget *parent) : MyMainWindow(parent)
{
    this->setWindowTitle("开始场景");
    MyPushButton *btnStart = new MyPushButton(":/res/MenuSceneStartButton.png",":/res/MenuSceneStartButton.png",this);
    btnStart->resize(114,114);
    btnStart->move(this->width()/2 - btnStart->width()/2,this->height()*3/4 - btnStart->height() /2);

    connect(&this->mSelectScene,&SelectScene::backBtnClicked,[=](){
        // 当第二个窗口的返回按钮电机的时候。
        QSound::play(":/res/BackButtonSound.wav");
        this->move(this->mSelectScene.pos());
        this->show();
        this->mSelectScene.hide();
    });

    connect(btnStart,&QPushButton::clicked,[=](){
        QSound::play(":/res/TapButtonSound.wav");
        btnStart->setEnabled(false);
        btnStart->moveDown();
        QTimer::singleShot(150,[=](){
            btnStart->moveUp();
        });
        QTimer::singleShot(300,[=](){
            btnStart->setEnabled(true);
            //场景切换，隐藏当前场景，显示第二个窗口
            this->hide();
            this->mSelectScene.move(this->pos());
            this->mSelectScene.show();
        });

    });


}
