#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

void  Widget::paintEvent(QPaintEvent *)
{

//    //设置画笔
//    QPen pen(QColor(255,255,0));
//    pen.setWidth(3);
//    pen.setStyle(Qt::DotLine);
//    //让画家使用画笔
//    //画刷填充颜色
//    QBrush brush(Qt::darkBlue);
//    brush.setStyle(Qt::Dense1Pattern);
//    QPainter painter(this);
//    painter.setBrush(brush);
//    painter.setPen(pen);
//    painter.drawLine(QPoint(0,0),QPoint(100,100));
//    painter.drawEllipse(QPoint(100,100),50,50);
//    painter.drawText(QRect(10,200,20,10),"QT YYDS");

    ////////////////////////////////更高级的绘画//////////////////////////////////////
      QPainter painter(this);
//      painter.drawEllipse(QPoint(100,50),50,50);
//      //抗锯齿
//      painter.setRenderHint(QPainter::Antialiasing);
//      painter.drawEllipse(QPoint(200,50),50,50);
      //painter.drawRect(QRect(20,20,50,50));
      //painter.translate(100,0); //把画家移动100，0
      //painter.drawRect(QRect(20,20,50,50));
      //利用画家画资源图片
        //painter.drawPixmap(20,0,QPixmap(":/Screenshots/屏幕截图(182).png")) //警告永远不要使用中文文件名，谁用谁伞兵！！！
}

Widget::~Widget()
{
    delete ui;
}

