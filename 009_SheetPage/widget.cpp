#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3); //设置列数
    //设置水平表头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Name"<<"Gender"<<"Age");
    //设置行数
    ui->tableWidget->setRowCount(5);
    //设置正文
    //ui->tableWidget->setItem(0,0,new QTableWidgetItem("Author"));
    //队列来快速设置正文
    QStringList nameList;
    nameList<<"亚瑟"<<"妲己"<<"安琪拉"<<"赵云"<<"孙悟空";
    QList<QString> sexList;
    sexList<<"男"<<"女"<<"女"<<"男"<<"中立";
    QList<int> ageList;
    ageList<<18<<19<<20<<21<<22;
    for(int i=0;i<5;i++)
    {
        int col=0;
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(nameList[i]));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(sexList.at(i)));  //用at可以防止越界
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString::number(ageList[i])));
        //number将int型转换为QString型
    }
}

Widget::~Widget()
{
    delete ui;
}

