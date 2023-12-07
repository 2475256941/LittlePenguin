#include "mainscene.h"
#include "ui_mainscene.h"
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QSoundEffect>


MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SetAcction)
{
    ui->setupUi(this);
    /*初始化设置窗口  不可见*/
    this->my_setting_widget=new SetWidget;
    this->my_setting_widget->show();
    my_setting_widget->setVisible(false);

    this->my_about_widget=new AboutWidget;
    this->my_about_widget->show();
    my_about_widget->setVisible(false);

    //设置软件图标
    this->setWindowIcon(QIcon(":/falling/qqpet/falling/2.png"));
    this->setWindowTitle("南极贱畜");

    //创建企鹅的对象
    this->m_penguin = new Penguin;

    //将企鹅对象显示到窗口中
    this->m_penguin->setParent(this);

    //设置软件窗口尺寸  (先实例化指针再做)
    this->setFixedSize(this->m_penguin->width(),this->m_penguin->height());

    //启动动画 定时器开始（定时器）
    this->m_penguin->start();




    //监听切图的信号
    connect(this->m_penguin,&Penguin::changepix,[=](){
            update();  //手动调用绘图事件
    });


    //监听 鼠标拖拽移动的信号/
    connect(this->m_penguin,&Penguin::moving,[=](QPoint point){
        this->move(point);
        m_Auto_Pos = point;
        //鼠标拖拽的时候要更新当前位置坐标,将自动移动的位置关联
    });


    //创建定时器的对象   自动移动
    this->timer = new QTimer(this);

    //启动定时器     //移动的时间间隔
    this->timer -> start(30);


    //获取当前屏幕的大小
    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    screenX = screenRect.width();
    screenY = screenRect.height();

    //监听定时器
    connect(timer,&QTimer::timeout,[=](){

        this->move(this->m_Auto_Pos); //同步窗口和企鹅

        //如果鼠标没有按下，才能向前移动
        if(!this->m_penguin->mouseDown)
        {
            LowSpeed();
            HighSpeed();
            Fall();
            //可以在这里写不同方向的速度函数
        }
    });



    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    //设置顶层窗体 120号属性
    this->setAttribute(Qt::WA_TranslucentBackground);

    //设置窗口顶层
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);

    //设置企鹅的起始位置 程序启动时的位置
    this->m_Auto_Pos.setY(screenX * 0.2 - this->m_penguin->height());
    this->m_Auto_Pos.setX(screenY * 0.3 - this->m_penguin->width());



    //菜单创建，各类子菜单设置完成
    m_penguin->m_Menu = new QMenu();
    QAction * setAction = m_penguin->m_Menu->addAction("设置");        //点击更改属性
    QAction * aboutAction = m_penguin->m_Menu->addAction("关于游戏...");

    //点击设置  弹出窗口
    connect(setAction,&QAction::triggered,[=](){
        this->my_setting_widget->move(screenX/2.0,screenY/2.0);
        this->my_setting_widget->setFixedSize(350,250);
        this->my_setting_widget->setVisible(true);
    });

    connect(aboutAction,&QAction::triggered,[=](){
        this->my_about_widget->move(screenX/2.0,screenY/2.0);
        this->my_about_widget->setFixedSize(300,180);
        this->my_about_widget->setVisible(true);
    });

    //连接菜单中退出的选项的信号槽
    connect(m_penguin->m_Menu->addAction("退出"),&QAction::triggered,[=](){
        exit(0);
    });

    //更改是否超出屏幕
    connect(this->my_setting_widget,&SetWidget::IsMoveOutScreen,[=](bool val)
            {
                if(val)
                    m_penguin->IsWholeScreen=true;
                else m_penguin->IsWholeScreen=false;
            });

    //更改企鹅移动的速度
    connect(this->my_setting_widget,&SetWidget::moveSpeedXChange,[=](double val)
            {
                m_penguin->speedX=2+val/33;
                qDebug()<<"speedX="<<m_penguin->speedX;
            });

    connect(this->my_setting_widget,&SetWidget::moveSpeedYChange,[=](double val)
            {
                m_penguin->speedY=1+val/35;
                qDebug()<<"speedY="<<m_penguin->speedY;
            });   //更改竖直方向速度


}


void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->m_penguin->penguinPix);   //调用企鹅绘图时事件
}

void MainScene::LowSpeed()
{
    if((m_penguin->PlayMode==1) || (m_penguin->PlayMode ==-1))//向右跑
    {
        if(m_penguin->PlayMode==1)   //向右跑
        {
            this->m_Auto_Pos.setX(this->m_Auto_Pos.x() + m_penguin->speedX);
            this->m_Auto_Pos.setY(this->m_Auto_Pos.y() + m_penguin->speedY);
        }
        else if(m_penguin->PlayMode==-1)  //向左跑
        {
            this->m_Auto_Pos.setX(this->m_Auto_Pos.x() - m_penguin->speedX);
            this->m_Auto_Pos.setY(this->m_Auto_Pos.y() + m_penguin->speedY);
        }

        if(m_penguin->IsWholeScreen)  //全屏 屏幕之外
        {
            if(this->m_Auto_Pos.x() > this->m_penguin->width()+screenX)
            {
                this->m_Auto_Pos.setX(-this->m_penguin->width());
            }
            else if(this->m_Auto_Pos.x() < -this->m_penguin->width())
            {
                this->m_Auto_Pos.setX(screenX+this->m_penguin->width());
            }

            if(this->m_Auto_Pos.y()>this->m_penguin->height()+screenY)
            {
                this->m_Auto_Pos.setY(-this->m_penguin->height());
            }
            else if(this->m_Auto_Pos.y()<-this->m_penguin->height())
            {
                this->m_Auto_Pos.setY(screenY+this->m_penguin->height());
            }
        }

        else if(!m_penguin->IsWholeScreen)   //非全屏幕
        {
            if((this->m_Auto_Pos.x()>screenX) || (this->m_Auto_Pos.x()<-this->m_penguin->width()))
                m_penguin->PlayMode = - m_penguin->PlayMode;
            if((this->m_Auto_Pos.y()>screenY) || (this->m_Auto_Pos.y()<-this->m_penguin->height()))
                m_penguin->speedY = - m_penguin->speedY;

        }
    }
}

void MainScene::HighSpeed()
{
    if((m_penguin->PlayMode==2) || (m_penguin->PlayMode ==-2))//向右跑
    {
        if(m_penguin->PlayMode==2)   //向右跑
        {
            this->m_Auto_Pos.setX(this->m_Auto_Pos.x() + m_penguin->speedX*1.6);
            this->m_Auto_Pos.setY(this->m_Auto_Pos.y() + m_penguin->speedY);
        }
        else if(m_penguin->PlayMode==-2)  //想左跑
        {
            this->m_Auto_Pos.setX(this->m_Auto_Pos.x() - m_penguin->speedX*1.6);
            this->m_Auto_Pos.setY(this->m_Auto_Pos.y() + m_penguin->speedY);

        }

        if(m_penguin->IsWholeScreen)  //全屏
        {
            if(this->m_Auto_Pos.x()>this->m_penguin->width()+screenX)
            {
                this->m_Auto_Pos.setX(-this->m_penguin->width());
            }
            else if(this->m_Auto_Pos.x()<-this->m_penguin->width())
            {
                this->m_Auto_Pos.setX(screenX+this->m_penguin->width());
            }

            if(this->m_Auto_Pos.y()>this->m_penguin->height()+screenY)
            {
                this->m_Auto_Pos.setY(-this->m_penguin->height());
            }
            else if(this->m_Auto_Pos.y()<-this->m_penguin->height())
            {
                this->m_Auto_Pos.setY(screenY+this->m_penguin->height());
            }
        }

        else if(!m_penguin->IsWholeScreen)   //非全屏幕
        {
            if((this->m_Auto_Pos.x()>screenX) || (this->m_Auto_Pos.x()<-this->m_penguin->width()))
                m_penguin->PlayMode = - m_penguin->PlayMode;
            if((this->m_Auto_Pos.y()>screenY) || (this->m_Auto_Pos.y()<-this->m_penguin->height()))
                m_penguin->speedY = -m_penguin->speedY;
        }
    }
}

void MainScene::Fall()
{
    if(m_penguin->PlayMode==3)
    {
        this->m_Auto_Pos.setY(this->m_Auto_Pos.y()+10);
        if(this->m_Auto_Pos.y() > this->screenY + this->m_penguin->height())
        {   //不间断向下掉落 +this->m_penguin->height()
            this->m_Auto_Pos.setY(-this->m_penguin->height());
        }
    }
}

MainScene::~MainScene()
{
    delete ui;
}
