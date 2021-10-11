#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启动定时器
    id1=startTimer(1000);
    id2=startTimer(2000);

    QTimer *timer=new QTimer(this);
    timer->start(500);

    connect(timer,&QTimer::timeout,[=](){
        static int num3=1;
        ui->label_4->setText(QString::number(num3++));
    });

    connect(ui->btn,&QPushButton::clicked,[=](){
        timer->stop();
    });

    //给label安装事件过滤器
    ui->label->installEventFilter(this);//步骤1

}

bool Widget::eventFilter(QObject * obj,QEvent * e)
{
    if(obj==ui->label)
    {
        if(e->type()==QEvent::MouseButtonPress)
        {
            QString str="KUKUKU";
            qDebug()<<str;

            return true;
        }
    }

    return QWidget::eventFilter(obj,e);

}//步骤2

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent * ev)
{
    if(ev->timerId()==id1)
    {
        static int num=1;
        ui->label_2->setText(QString::number(num++));
    }
    if(ev->timerId()==id2)
    {
        static int num2=1;
        ui->label_3->setText(QString::number(num2+=2));
    }
}
