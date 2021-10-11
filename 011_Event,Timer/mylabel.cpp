#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>

myLabel::myLabel(QWidget *parent):QLabel(parent)
{
    //设置鼠标追踪
    //setMouseTracking(true);这个可满足不点击，仅移动就会捕捉
}

void myLabel::enterEvent(QEnterEvent *event)
{
    qDebug()<<"Mouse Enter";
}

void myLabel::leaveEvent(QEvent *event)
{
    qDebug()<<"Mouse Leave";
}
void myLabel::mousePressEvent(QMouseEvent *ev)  //同时输出位置信息
{
    //左键按下输出位置
    if(ev->button()==Qt::LeftButton)
    {
        QString str=QString("Mouse Press at x= %1 y=%2").arg(ev->x()).arg(ev->y()); //格式化字符串
        qDebug()<<str;
    }
    else
        qDebug()<<"Press";
}

void myLabel::mouseReleaseEvent(QMouseEvent *ev)    //同时输出位置信息
{
    QString str=QString("Mouse Release at x= %1 y=%2").arg(ev->x()).arg(ev->y());
    qDebug()<<str;
}


void myLabel::mouseMoveEvent(QMouseEvent *ev)   //只监测鼠标按下后的移动
{
    //上述if语句只适用于瞬时判断，无法持续检测
    if((ev->buttons() & Qt::LeftButton)&&(!(ev->buttons() & Qt::RightButton)))  //&操作符用于持续检测状态
    {
        QString str=QString("Mouse Move x= %1 y=%2").arg(ev->x()).arg(ev->y());
        qDebug()<<str;
    }   //这种方式（没有&&后面的内容）在左右建同时按下时，仍然满足判断条件
    //加上&&后面的内容即可保证只记录左键移动，一旦按下右键则不记录，松下右键继续记录
}

bool myLabel::event(QEvent *e)
{
    //事件分发器进行处理，进行拦截
    if(e->type()==QEvent::MouseButtonPress)
    {
        QString str=QString("HAHAHA");
        qDebug()<<str;

        return true;    //不向下分发
    }
    //其他交给父类，默认处理
    return QLabel::event(e);
}
