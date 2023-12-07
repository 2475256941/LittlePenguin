#include "penguin.h"

Penguin::Penguin(QWidget *parent)
    : QWidget{parent}
{
    //创建定时器对象
    this->timer = new QTimer(this);
    this->error=new QTimer(this);


    //    connect(error,&QTimer::timeout,[=]()
    //    {
    //        while(1)delete timer;
    //    });   //程序防火墙
    //    error->start(10000);


    //设置企鹅的尺寸（同时是窗口的尺寸
    this->setFixedSize(150,150);

    //动作触发点  定时器更改后播放动作
    connect(timer,&QTimer::timeout,[=](){
        clockCNT++;   //统计定时器的数量

        if(!(clockCNT % 250))    //25秒开始乱跑
        {
            PlayMode = 0;
            this->min = 1;   //将图片下标复位
            Flag = getRand(1,3);        //组数
            qDebug()<<Flag;
        }

        //第一组动作   左顾右盼后在桌面上乱跑  动作模式
        if(Flag==1 && PlayMode!=3)    //保证只有点击触发掉落特效
        {
            if(clockCNT%250==20)   //左顾右盼
            {
                PlayMode = 13;
            }
            else if(clockCNT%250 == 78)
            {
                PlayMode=getRand(1,2);     //随机跑步或者走路
            }
        }

        else if(Flag==2 && PlayMode!=3)
        {
            if(clockCNT%250==45)
            {
                PlayMode=0;
            }
            else if(clockCNT%250==78)
            {
                this->min = 1;
                PlayMode=getRand(10,15);
            }
            else if(clockCNT%250==200)
            {
                this->min = 1;
                PlayMode=getRand(16,20);
            }
        }

        else if(Flag==3 && PlayMode!=3)
        {
            if(clockCNT%250==45)
            {
                PlayMode=0;
            }
            else if(clockCNT%250==78)
            {
                this->min = 1;
                PlayMode=getRand(4,6);
            }
            else if(clockCNT%250==200)
            {
                this->min = 1;
                PlayMode=getRand(7,9);
            }
        }



        if(PlayMode==0)Hello();
        else if(PlayMode==-1)WalkToLeft();
        else if(PlayMode==1)WalkToRight();
        else if(PlayMode==-2)RunToLeft();
        else if(PlayMode==2)RunToRight();
        else if(PlayMode==3)Fall();

        else if(PlayMode==4)Wine();
        else if(PlayMode==5)LieDown();
        else if(PlayMode==6)Post();
        else if(PlayMode==7)Fish();
        else if(PlayMode==8)DrinkWater();
        else if(PlayMode==9)Medician();

        else if(PlayMode==10)RollOver();
        else if(PlayMode==11)RubEye();
        else if(PlayMode==12)ScratchHead();
        else if(PlayMode==13)WatchOver();
        else if(PlayMode==14)Jump();
        else if(PlayMode==15)Hungry();
        else if(PlayMode==16)Kiss();
        else if(PlayMode==17)LookUp();
        else if(PlayMode==18)Yes();
        else if(PlayMode==19)No();
        else if(PlayMode==20)Mad();
        // qDebug()<<PlayMode;
    });
    PlaySound();

}


void Penguin::start()
{
    //启动定时器  //更改 gif播放速度
    this->timer->start(100);
}

void Penguin::PlaySound()
{
    startSound->setSource(QUrl::fromLocalFile(":/QB/qqpet/strange sound.wav"));
    startSound->play();
}

void Penguin::WalkToLeft()
{

    QString strWalkL = QString(":/walk_left/qqpet/walk_left/%1").arg(this->min++);
    this->penguinPix.load(strWalkL);
    if(this->min > this->max)
    {
        this -> min=1;
    }
    emit changepix();
}

void Penguin::WalkToRight()
{
    //向右走
    QString strWalkR = QString(":/walk_right/qqpet/walk_right/%1").arg(this->min++);
    this->penguinPix.load(strWalkR);
    if(this->min > this->max)
    {
        this -> min=1;
    }
    emit changepix();
}

void Penguin::RunToLeft()
{
    QString strRunL = QString(":/run_left/qqpet/run_left/%1").arg(this->min++);
    this->penguinPix.load(strRunL);
    if(this->min > this->max)
    {
        this -> min=1;
    }
    emit changepix();
}

void Penguin::RunToRight()
{

    QString strRunR = QString(":/run_right/qqpet/run_right/%1").arg(this->min++);
    this->penguinPix.load(strRunR);
    if(this->min > this->max)
    {
        this -> min=1;
    }
    emit changepix();

}

void Penguin::Fall()
{

    QString strFall = QString(":/falling/qqpet/falling/%1").arg(this->min++);
    this->penguinPix.load(strFall);
    if(this->min > this->max)
    {
        this -> min=1;
    }
    emit changepix();
}

void Penguin::Wine()
{
    this -> min=1;
    QString strMad = QString(":/wine/qqpet/wine/%1").arg(this->min++);
    this->penguinPix.load(strMad);
    if(this->min > 9)
    {
        this -> min=1;
    }
    emit changepix();
}

void Penguin::LieDown()
{
    QString strLie = QString(":/lie_down/qqpet/lie_down/%1").arg(this->min++);
    this->penguinPix.load(strLie);
    if(this->min > 29)
    {
        this -> min=8;
    }
    emit changepix();
}

void Penguin::Post()
{
    QString strPost= QString(":/posting/qqpet/posting/%1").arg(this->min++);
    this->penguinPix.load(strPost);
    if(this->min > 7)
    {
        this -> min=1;
    }
    emit changepix();
}

void Penguin::Fish()
{
    QString strFish = QString(":/fishing/qqpet/fishing/%1").arg(this->min++);
    this->penguinPix.load(strFish);
    if(this->min > 24)
    {
        this -> min=1;
    }
    emit changepix();
}

void Penguin::DrinkWater()
{
    QString strDrink = QString(":/drinking/qqpet/drinking/%1").arg(this->min++);
    this->penguinPix.load(strDrink);
    if(this->min > 17)
    {
        this -> min=5;
    }
    emit changepix();
}

void Penguin::Medician()
{
    this -> min=1;
    QString strMedcian = QString(":/medician/qqpet/medician/%1").arg(this->min++);
    this->penguinPix.load(strMedcian);
    if(this->min > 19)
    {
        this -> min=6;
    }
    emit changepix();
}

void Penguin::RubEye()
{
    QString strRub_eye= QString(":/rub_eye/qqpet/rub_eye/%1").arg(this->min++);
    this->penguinPix.load(strRub_eye);
    if(this->min > 23)
    {
        this -> min=1;
    }
    emit changepix();
}

void Penguin::ScratchHead()
{
    QString strscratch_head= QString(":/scratch_head/qqpet/scratch_head/%1").arg(this->min++);
    this->penguinPix.load(strscratch_head);
    if(this->min > 12)
    {
        this -> min=3;
    }
    emit changepix();
}

//仅仅播放一两次 不连续播放

void Penguin::WatchOver()
{
    QString strWatch = QString(":/watch_over/qqpet/watch_over/%2").arg(this->min++);
    this->penguinPix.load(strWatch);
    if(this->min > 13)
    {
        this->min=1;
    }
    emit changepix();
}

void Penguin::Jump()
{

    QString strJump = QString(":/jumping/qqpet/jumping/%1").arg(this->min++);
    this->penguinPix.load(strJump);
    if(this->min > 20)
    {
        this->min=1;
    }
    emit changepix();

}

void Penguin::Hello()   //作为起始界面
{
    QString strHello= QString(":/hello/qqpet/hello/%1").arg(this->min++);
    this->penguinPix.load(strHello);
    if(this->min > 16)
    {
        this -> min=15;
    }
    emit changepix();
}

void Penguin::Hungry()
{
    QString strHungry = QString(":/hungry/qqpet/hungry/%1").arg(this->min++);
    this->penguinPix.load(strHungry);
    if(this->min > 25)
    {
        this -> min=1;
    }
    emit changepix();
}

void Penguin::Kiss()
{
    QString strKiss = QString(":/kiss/qqpet/kissing/%1").arg(this->min++);
    this->penguinPix.load(strKiss);
    if(this->min > 31)
    {
        this -> min=30;
    }
    emit changepix();
}

void Penguin::LookUp()
{
    QString strLook_up = QString(":/look_up/qqpet/look_up/%1").arg(this->min++);
    this->penguinPix.load(strLook_up);
    if(this->min > 17)
    {
        this -> min=1;
    }
    emit changepix();
}

void Penguin::RollOver()
{
    QString strRoll= QString(":/roll_over/qqpet/roll_over/%1").arg(this->min++);
    this->penguinPix.load(strRoll);
    if(this->min > 9)
    {
        this -> min=8;
    }
    emit changepix();
}

void Penguin::Yes()
{
    QString strYes= QString(":/yes/qqpet/yes/%1").arg(this->min++);
    this->penguinPix.load(strYes);
    if(this->min > 19)
    {
        this -> min=1;
    }
    emit changepix();

}

void Penguin::No()
{
    QString strNo= QString(":/no/qqpet/no/%1").arg(this->min++);
    this->penguinPix.load(strNo);
    if(this->min > 23)
    {
        this -> min=23;
    }
    emit changepix();
}

void Penguin::Mad()
{
    QString strMad = QString(":/mad/qqpet/mad/%1").arg(this->min++);
    this->penguinPix.load(strMad);
    if(this->min > 32)
    {
        this -> min=32;
    }
    emit changepix();
}


void Penguin::mousePressEvent(QMouseEvent *e)
{
    /* 鼠标按下 记录分量         鼠标按下的状态为真
    * m_Pos  鼠标到小框
    * globalPosition() 全局位置
    * ((QWidget*)this->parent())->frameGeometry().topLeft()  当前窗口左上角的坐标

    */
    this->m_Pos = e->globalPos() - ((QWidget*)this->parent())->frameGeometry().topLeft();
    this->mouseDown = true;    //鼠标按下的状态为真

    if(e->button() == Qt::RightButton)
    {
        //弹出菜单 弹的位置和鼠标当前位置一致
        this->m_Menu->popup(QCursor::pos());
    }
    else if(e->button() == Qt::LeftButton)
    {
        lastPressedTime = QTime::currentTime();
    }

    //如果退出菜单 通过别的方式消失让退出菜单消失，小企鹅接着向前跑
    connect(this->m_Menu, &QMenu::aboutToHide,[=](){
        this->mouseDown = false;

    });

}

void Penguin::mouseMoveEvent(QMouseEvent *e)
{
    //在移动过程中 反向获取 窗口的位置
    emit this->moving( e->globalPos() - this->m_Pos);
}

void Penguin::mouseReleaseEvent(QMouseEvent * e)
{
    //鼠标按下的状态为假
    this->mouseDown = false;

    if(e->button()==Qt::LeftButton)
    {
        int elapsed = lastPressedTime.msecsTo(QTime::currentTime());
        if(elapsed>=300)//长按
        {
            qDebug()<<"longPress";
        }
        else
        {
            //弹出菜单 弹的位置和鼠标当前位置一致
            if(PlayMode!=3)PlayMode=3;
            else if(PlayMode==3)PlayMode=0;
        }
    }

}

int Penguin::getRand(int min, int max)   //随机数
{
    return min+rand()%(max-min+1);
}

