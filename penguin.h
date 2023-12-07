#ifndef PENGUIN_H
#define PENGUIN_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QMenu>
#include <QSoundEffect>

class Penguin : public QWidget
{
    Q_OBJECT
public:
    explicit Penguin(QWidget *parent = nullptr);

    QPixmap penguinPix;  //企鹅图像的呈现

    QTimer * timer;    //定时器(设置一个就好辣)
    QTimer * error; //哈哈哈
    int clockCNT=0;

    QSoundEffect * startSound = new QSoundEffect(this);

    QPoint m_Pos;    //记录分量坐标


    float speedX = 2;    //默认
    float speedY = 1;

    int PlayMode = 0;  //当前动作
    int Flag=1;        //动作分组标志位

    bool IsWholeScreen = false;  //是否为整个屏幕
    bool IsMouseTrack = true;

    int min=1;
    int max=8;

    QTime lastPressedTime;


    //执行动画  播放声音
    void start();
    void PlaySound();


    int getRand(int small, int big);

    //所有的运动模式
    void Hello();
    void WalkToLeft();
    void WalkToRight();
    void RunToLeft();
    void RunToRight();

    void Fall();          //3
    void Wine();
    void LieDown();
    void Post();
    void Fish();
    void DrinkWater();
    void Medician();
    void RubEye();
    void ScratchHead();

    void WatchOver();
    void Jump();

    void Hungry();
    void Kiss();
    void LookUp();
    void RollOver();

    void Yes();
    void No();
    void Mad();



    //鼠标按下事件
    void mousePressEvent(QMouseEvent *);

    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *);

    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *);

    //鼠标按下的状态
    bool mouseDown = false;


    //右键菜单 实现退出
    QMenu * m_Menu;


signals:
    //自定义信号 正在切换图片
    void changepix();

    //自定义信号 拖拽后场景移动的位置
    void moving(QPoint point);

};

#endif // PENGUIN_H
