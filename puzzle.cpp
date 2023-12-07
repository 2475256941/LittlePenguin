#include "puzzle.h"

Puzzle::Puzzle(QWidget *parent)
    : QMainWindow{parent}
{

}


#include "mainscene.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <QPainter>
#include <string.h>
#include<QDebug>
#include<QKeyEvent>
#include<iostream>
#include<QMediaPlayer>
#include<QMessageBox>
#include<QPushButton>
#include<QLabel>
#include<QTimerEvent>
#define NEWBLOCK rand ( ) %2+1#define NEWPOINT rand ( )%EDGEint steps,Time ,timerId=0;
Mainwindow : : Mainwindow( Qwidget *parent) :
QMainwindow(parent),
ui(new Ui: :Mainwindow)
I
ui->setupui(this) ;
this->setFixedsize(WINWIDTH,WINHEIGHT);
this->setwindowIcon(QPixmap( " :/ game /image/Icon.png"));this->setwindowTitle( "2048");
connect(ui->action1,&QAction: :triggered,[=](){
NewGame ( ) ;
this->update() ;});
connect(ui->action2.&0Action: :triggered .[=1(){
