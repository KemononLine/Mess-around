#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->actionNew->setIcon(QIcon("C:\\Users\\123\\Pictures\\Cyberpunk 2077\\photomode_13122020_122249.png"));
    //楼上操作为绝对应用
    //我们应将资源添加到QT项目中，并且使用他们:+前缀名+文件名
    ui->actionNew->setIcon(QIcon(":/new/prefix1/Cyberpunk 2077/photomode_13122020_122249.png"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

