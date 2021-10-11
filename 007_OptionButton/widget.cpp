#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QListWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置默认单选选项
    ui->rBtnMan->setChecked(true);
    //监听用户的选择
    connect(ui->rBtnWoman,&QRadioButton::clicked,this,[=](){
        qDebug()<<"Choose Woman";
    });
    connect(ui->checkBox,&QCheckBox::clicked,this,[=](){
        QMessageBox::information(this,"Info","HHHH");

    });
    //数字来显示是否选中
    connect(ui->checkBox_2,&QCheckBox::stateChanged,this,[=](int state){
        qDebug()<<state;
    });

    //使用listwidget
    QListWidgetItem *item=new QListWidgetItem("锄禾日当午");
    ui->listWidget->addItem(item);
    item->setTextAlignment(Qt::AlignHCenter);   //设置文字对齐格式

    //QStringList 快速导入文字，但无法设置对齐格式
    QStringList list;
    list<<"aaa"<<"bbb"<<"ccc";
    ui->listWidget->addItems(list);
}

Widget::~Widget()
{
    delete ui;
}

