#include "setwidget.h"
#include "ui_setwidget.h"

SetWidget::SetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetWidget)
{
    ui->setupUi(this);

    connect(ui->radioButton,&QRadioButton::clicked,[=]()
            {//选择是
                IsMoveOutScreen(true);
            });
    connect(ui->radioButton_2,&QRadioButton::clicked,[=]()
            {//选择否
                IsMoveOutScreen(false);
            });

    connect(ui->horizontalSlider,&QSlider::valueChanged,[=]()
            {//滑条移动
                moveSpeedXChange(ui->horizontalSlider->value());
            });

    connect(ui->horizontalSlider_2,&QSlider::valueChanged,[=]()
            {//滑条移动
                moveSpeedYChange(ui->horizontalSlider_2->value());
            });


}

SetWidget::~SetWidget()
{
    delete ui;
}



void IsMoveOutScreen(bool val);
