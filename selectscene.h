#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include <QMainWindow>
#include"mymainwindow.h"
class SelectScene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit SelectScene(QWidget *parent = nullptr);

signals:
    void backBtnClicked();
public slots:

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // SELECTSCENE_H
