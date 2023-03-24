#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mymainwindow.h"
#include <coinbutton.h>
class PlayScene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(int level,QWidget *parent = nullptr);
    void flip(int row,int col); //翻动[row][col]处的硬币
    void judgeWin(); //判断是否游戏胜利
signals:
    void backBtnClicked();
public slots:

protected:
    void paintEvent(QPaintEvent* event);
private:
    int level;
    CoinButton *mCoins[4][4];
    bool mHaveWin=false;
};

#endif // PLAYSCENE_H
