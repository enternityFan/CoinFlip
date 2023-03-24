#include "playscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include<QMenuBar>
#include<QLabel>
#include "coinbutton.h"
#include "dataconfig.h"
#include<QMessageBox>
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>
PlayScene::PlayScene(int level,QWidget *parent) : MyMainWindow(parent)
{
     this->mHaveWin=false;
    MyPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btnBack->setText("Back");
    btnBack->resize(72,32);
    connect(btnBack,&QPushButton::clicked,this,&PlayScene::backBtnClicked);

    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    // 添加左下角的label
    QLabel *label = new QLabel(this);
    label->setText(QString("lavel: %1").arg(QString::number(level)));
    label->move(30,this->height()-label->height());
    label->resize(150,50);
    label->setFont(QFont("华文新魏",20));

    // 16个硬币按钮
    const int colWidth = 50;
    const int rowHeight = 50;
    const int xoffset = 57;
    const int yoffset = 200;
    // 取出第level关的二维数组
    dataConfig data;
    QVector<QVector<int>> dataArray = data.mData[level];

    for (int row=0;row<4;++row){
        for (int col=0;col <4;++col){
               CoinButton *btn = new CoinButton(this);
               mCoins[row][col] = btn;
               int x = col * colWidth+xoffset;
               int y = row * rowHeight+yoffset;
               btn->setGeometry(x,y,50,50);
               btn->setStat(dataArray[row][col]);

               connect(btn,&CoinButton::clicked,[=](){
                   this->flip(row,col);
               });
        }
    }
}

void PlayScene::flip(int row, int col)
{
    if(this->mHaveWin)return;
    QSound::play(":/res/ConFlipSound.wav");
    this->mCoins[row][col]->flip();
    //为了好看，延时翻动其他硬币
    QTimer::singleShot(200,[= ](){
        if (row +1 < 4)this->mCoins[row+1][col]->flip();

        if (row -1 >= 0)this->mCoins[row-1][col]->flip();
        if (col -1 >= 0)this->mCoins[row][col-1]->flip();
        if (col +1 < 4)this->mCoins[row][col+1]->flip();
        this->judgeWin();
    });


}

void PlayScene::judgeWin()
{

    for (int row=0;row<4;++row){

        for (int col=0;col<4;++col){
            if(!this->mCoins[row][col]->stat()){
                qDebug()<<"游戏尚未结束！"<<row<<col;
                return; // 有一个是银币，那就没事了
            }
        }
    }
    this->mHaveWin=true;
    QSound::play(":/res/LevelWinSound.wav");
    //游戏结束
     //QMessageBox::information(this,"恭喜","你已经胜利了");
    QLabel *labelWin = new QLabel(this);
    QPixmap pix = QPixmap(":/res/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->move(this->width()/2 - labelWin->width()/2,-labelWin->height());
    labelWin->show();

    QPropertyAnimation *animation = new QPropertyAnimation(labelWin,"geometry",this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(),labelWin->y()+100,labelWin->width(),labelWin->height()));
    animation->setDuration(100);
    //设置运动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce); // 这个曲线的感觉，反正很有感觉..
    animation->start(QAbstractAnimation::DeleteWhenStopped);// 动画播放完自动释放



}

void PlayScene::paintEvent(QPaintEvent *event)
{
    //绘制背景图片
    QPainter painter(this);
    //搬运画家到菜单栏下面
    painter.translate(0,this->menuBar()->height());
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    QPixmap title(":/res/Title.png");
    title = title.scaled(title.width()/2,title.height()/2);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    painter.drawPixmap(0,0,title);

}
