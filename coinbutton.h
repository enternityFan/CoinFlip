#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CoinButton(QWidget *parent = nullptr);

    int stat() const;
    void setStat(int stat);
    void setStatWithAnimation(int stat);
    void flip();
protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:

private:
    int mStat; // 硬币状态，0银币或者1金币
    int mFrame;
    QTimer mTimer;

};

#endif // COINBUTTON_H
