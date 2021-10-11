#include "widget.h"
#include <QPushButton>
#include <QDebug>

//下课后，老师饿了，学生请客吃饭
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->zt=new Teacher(this); //创建一老师对象
    this->st=new Student(this); //创建一个学生对象
//    connect(zt,&Teacher::hungry,st,&Student::treat);
//    classIsOver();  //调用下课函数

    //用函数指针来指向重载函数
    void(Teacher::*teachersignal)(QString)=&Teacher::hungry;
    void(Student::*studentslot)(QString)=&Student::treat;
    connect(zt,teachersignal,st,studentslot);
    //classIsOver();
    //发现输出chips带有蜜汁引号

    //通过下课按钮来下课
    QPushButton *btn=new QPushButton("Class is over",this);
    resize(200,300);
    connect(btn,&QPushButton::clicked,this,&Widget::classIsOver);

    //无参信号和槽连接
    void(Teacher::*teachersignal2)(void)=&Teacher::hungry;
    void(Student::*studentslot2)(void)=&Student::treat;
    connect(zt,teachersignal2,st,studentslot2);

    //QT4信号槽连接,在SIGNAL(SLOT)里面选择重载函数
    connect(zt,SIGNAL(hungry()),st,SLOT(treat())); //缺点，不检测信号与槽的类型是否匹配

    //信号连接信号
    connect(btn,&QPushButton::clicked,zt,teachersignal2);   //clicked无法连接teachersignal，因为clicked的信号参数是bool型，返回0或1，无法满足Qstring类型

    //断开信号
    disconnect(btn,&QPushButton::clicked,this,&Widget::classIsOver);

    //一个信号对应多个槽函数
    connect(zt,teachersignal2,this,&Widget::close);

    //一个槽函数也可对应多个信号
    //槽函数和信号的参数类型必须一一对应，个数不必一致，信号的参数个数可比槽参数多

    //Lambda表达式
    [=](){
        btn->setText("下课了");
    }();//[&]

    //mutable关键字可以在值传递时修改值传递进来的拷贝
    //如
    //int m=10
    //[m]()mutable{m=100+10;qDebug()<<m;}

    int ret=[]()->int{return 1000;}();
    //返回值类型由->指出，如果return只有一个类型可以省略
    qDebug()<<"ret= "<<ret;

    //利用lambda表达式实现非同类型信号与槽函数的连接

    QPushButton *btn666=new QPushButton;
    btn666->setText("lambda");
    btn666->setParent(this);
    btn666->move(100,60);
    connect(btn666,&QPushButton::clicked,this,[=](){
        emit zt->hungry("Chips");
        btn666->setText("LAMBDA");
        //this->close();
    });

}

void Widget::classIsOver()
{
    //下课函数调用后，触发老师饿了
    //emit zt->hungry();
    emit zt->hungry("Chips");
}

Widget::~Widget()
{
}

