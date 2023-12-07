#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QPainter>
#include <Qicon>
#include <QScreen>
#include <QDebug>
#include "penguin.h"
#include "setwidget.h"
#include "aboutwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SetAcction; }
QT_END_NAMESPACE

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();


    //创建企鹅对象的指针
    Penguin * m_penguin;

    //记录自动移动的位置(实际位置)
    QPoint m_Auto_Pos;

    //获取屏幕 整个桌面的大小
    double screenX;
    double screenY;

    //自动移动定时器
    QTimer * timer;

    //重写绘图事件
    void paintEvent(QPaintEvent * );

    void LowSpeed();  //走

    void HighSpeed(); //跑

    void Fall();     //坠落

    void sleep();

    //设置窗口
    SetWidget * my_setting_widget;
    AboutWidget * my_about_widget;

private:
    Ui::SetAcction *ui;
};
#endif // MAINSCENE_H
