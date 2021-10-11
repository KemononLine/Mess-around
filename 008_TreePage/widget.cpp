#include "widget.h"
#include "ui_widget.h"
#include <QStringList>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //treeWidget的使用
    ui->treeWidget->setHeaderLabels(QStringList()<<"Hero"<<"Intrduction");  //设置水平头
    //加载顶层节点
    QTreeWidgetItem *sItem=new QTreeWidgetItem(QStringList()<<"Strength");
    QTreeWidgetItem *rItem=new QTreeWidgetItem(QStringList()<<"Reaction");
    QTreeWidgetItem *iItem=new QTreeWidgetItem(QStringList()<<"Intelligence");
    ui->treeWidget->addTopLevelItem(sItem);
    ui->treeWidget->addTopLevelItem(rItem);
    ui->treeWidget->addTopLevelItem(iItem);

    //追加子节点
    QStringList heroL1;
    heroL1<<"aaaaaaa"<<"llll,lllaaaaa";
    QTreeWidgetItem *l1=new QTreeWidgetItem(heroL1);
    sItem->addChild(l1);
}

Widget::~Widget()
{
    delete ui;
}

