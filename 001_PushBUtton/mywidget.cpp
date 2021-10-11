#include "mywidget.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *btn=new QPushButton;
    //btn->show();  //以新窗口弹出
    btn->setParent(this);   //依赖于原窗口
    btn->setText("Close");
    QPushButton *btn2=new QPushButton("Close",this);
    resize(600,400);    //设置窗口大小
    btn2->move(100,100);    //移动，防止两个按钮重叠
    setWindowTitle("Test"); //设置窗口名称
    setFixedSize(600,400);  //固定窗口大小


    mypushbutton *myBtn=new mypushbutton;   //研究QT的析构
    myBtn->setText("MY BUTTON");
    myBtn->move(200,0);
    myBtn->setParent(this);

    //按钮交互&信号和槽
    //参数1：信号发送者 参数2：发送的信号（附上函数的地址）  参数3：信号的接收者  参数4：处理的槽函数
    connect(myBtn,&mypushbutton::clicked,this,&QWidget::close);


}

MyWidget::~MyWidget()
{
    qDebug()<<"my widget desctruct!";   //研究QT的析构
}

