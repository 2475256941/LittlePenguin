#ifndef SETWIDGET_H
#define SETWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QSlider>

namespace Ui {
class SetWidget;
}

class SetWidget : public QWidget
{
    Q_OBJECT

signals:
    void IsMoveOutScreen(bool val);
    void moveSpeedXChange(double val);
    void moveSpeedYChange(double val);


public:
    explicit SetWidget(QWidget *parent = nullptr);
    ~SetWidget();


private:
    Ui::SetWidget *ui;
};

#endif // SETWIDGET_H
