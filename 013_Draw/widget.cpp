#include "widget.h"
#include "ui_widget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <QPicture>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //点击移动，移动图片
   // connect(ui->btn,&QPushButton::clicked,[=](){
        //用update函数调用paintEvent
        //update();
    //});
    //用定时器控制，自动移动图片
//    QTimer *timer=new QTimer(this);
//    timer->start(500);
//    connect(timer,&QTimer::timeout,[=](){
//        update();
//    });

    //pixmap绘图设备
    QPixmap pix(300,300);
    QPainter painter(&pix);
    painter.setPen(QPen(Qt::blue));
    //设置背景填充色
    pix.fill(Qt::white);    //注意填充色和圆的顺序
    painter.drawEllipse(QPoint(150,150),100,100);
    pix.save("F:/pix.png");

    //qimage绘图设备
    QImage img(300,300,QImage::Format_A2BGR30_Premultiplied);
    //img.fill(Qt::white);
    QPainter painter2(&img);
    img.save("F:/img.png");


    //QPicture 绘图设备
    QPicture pic;
    QPainter painter3;
    painter3.begin(&pic);
    //画的内容
    painter.setPen(QPen(Qt::cyan));
    painter.drawEllipse(QPoint(150,150),100,100);
    painter3.end();

    pic.save("F:/pic.lcy"); //乱起的文件名也可以在绘图事件中重现
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPen pen(QColor(255,0,255));
    pen.setWidth(2);
    pen.setStyle(Qt::DashDotLine);
    QBrush brush(Qt::blue);
    brush.setStyle(Qt::Dense2Pattern);
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawEllipse(QPoint(50,50),25,25);
    //painter.drawPixmap(posx,0,QPixmap(":/Cyberpunk 2077/0001.png"));
    //如果超出屏幕，则从零开始
//    if(posx>this->width())
//    {
//        posx=0;
//    }
//    else
//        posx+=100;
    QImage img;
    img.load(":/Cyberpunk 2077/0001.png");
    //修改像素点
    for(int i=50;i<100;i++)
    {
        for(int j=50;j<100;j++)
        {
            QRgb value=qRgb(255,0,0);
            img.setPixel(i,j,value);
        }
    }
    //重现pic
    painter.drawImage(0,0,img);
    QPicture pic;
    pic.load("F:/pic.lcy");
    painter.drawPicture(0,0,pic);

}
//综上所述，QPixmap是一般绘图设备，QImage与pixmap类似，但他可以修改像素，QPicture是记录和重现绘图指令
Widget::~Widget()
{
    delete ui;
}

