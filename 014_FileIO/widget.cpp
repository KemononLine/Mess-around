#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //点击选取，打开选文件对话框
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString path=QFileDialog::getOpenFileName(this,"打开文件","C:/");
        ui->lineEdit->setText(path);    //显示路径

        //读取内容
        QFile file(path);
        //设置打开方式
        file.open(QIODevice::ReadOnly);
        QByteArray array =file.readAll();

        ui->textEdit->setText(array);
        file.close();

        //写的操作

        file.open(QIODevice::Append);   //一追加方式写
        file.write("6666");
        file.close();

        //QFileInfo类
        QFileInfo info(path);
        qDebug()<<info.size()<<" "<<info.suffix();
        qDebug()<<info.birthTime().toString("yyyy/MM/dd hh:mm:ss");
    });
}

Widget::~Widget()
{
    delete ui;
}

