#include "mypushbutton.h"
#include <QMessageBox>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImag,QString pressImag)
{
    this->normalImagPath=normalImag;
    this->pressImagPath=pressImag;

    QPixmap pix;
    bool ret=pix.load(normalImag);
    if(!ret)
    {
        QMessageBox::warning(this,"ERROR","FAIL TO LOAD THE IMAG");
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标
    this->setIcon(pix);
    //设置图标
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::zoomdown()
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //设置始末位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置动画过渡（弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

void MyPushButton::zoomup()
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //设置始末位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置动画过渡（弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImagPath!="") //传入对象不为空，要切换
    {
        QPixmap pix;
        bool ret=pix.load(this->pressImagPath);
        if(!ret)
        {
            QMessageBox::warning(this,"ERROR","FAIL TO LOAD THE IMAG");
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他操作
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImagPath!="") //传入对象不为空，要切换
    {
        QPixmap pix;
        bool ret=pix.load(this->normalImagPath);
        if(!ret)
        {
            QMessageBox::warning(this,"ERROR","FAIL TO LOAD THE IMAG");
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他操作
    return QPushButton::mouseReleaseEvent(e);
}
