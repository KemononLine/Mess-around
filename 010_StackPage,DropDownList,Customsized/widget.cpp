#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置默认展示页
    ui->stackedWidget->setCurrentIndex(0);
    //设置stack的切换
    connect(ui->btn_tab,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->btn_tool,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    //下拉框的应用
    ui->comboBox->addItem("Benz");
    ui->comboBox->addItem("Lamborghnia");
    ui->comboBox->addItem("QQ");

    connect(ui->selecttlj,&QPushButton::clicked,this,[=](){
        ui->comboBox->setCurrentIndex(2);
    });

    //点击获取当前控件的值
    connect(ui->btnCur,&QPushButton::clicked,[=](){
        ui->widget->getNum();
        qDebug()<<ui->widget->getNum();
    });
    //设置一半
    connect(ui->btnHal,&QPushButton::clicked,[=](){
        ui->widget->setNum((ui->widget->getNum())/2);
    });
}

Widget::~Widget()
{
    delete ui;
}

