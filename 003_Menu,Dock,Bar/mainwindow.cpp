#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QDebug>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600,400);

    //创建菜单栏(唯一
    QMenuBar *bar=menuBar();
    setMenuBar(bar);    //将菜单栏放在窗口中
    QMenu *fliemenu=bar->addMenu("Files");  //创建菜单
    QMenu *editmenu=bar->addMenu("Edit");
    //创建菜单项
    QAction *newaction=fliemenu->addAction("New");
    fliemenu->addAction("Open");
    fliemenu->addSeparator();
    fliemenu->addAction("Close");
    editmenu->addAction("Undo");
    editmenu->addAction("Select All");
    //创建工具栏(唯一
    QToolBar *toolBar=new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea,toolBar);    //将工具栏放到窗口中的同时设置工具栏位置
    //设置允许移动的范围
    toolBar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);
    //设置浮动
    toolBar->setFloatable(false);
    //移动总开关
    toolBar->setMovable(false);
    //工具栏选项
    toolBar->addAction(newaction);
    //添加工具栏控件
    QPushButton *btn=new QPushButton("test",this);
    toolBar->addWidget(btn);

    //状态栏添加(唯一
    QStatusBar *stBar=statusBar();
    setStatusBar(stBar);
    //放标签控件
    QLabel *label=new QLabel("Tips",this);
    stBar->addWidget(label);

    //设置中心部件(唯一
    QTextEdit *edit=new QTextEdit(this);
    setCentralWidget(edit);

    //浮动窗口(可多个
    QDockWidget *dockWidget=new QDockWidget("Dock",this);
    addDockWidget(Qt::BottomDockWidgetArea,dockWidget);


}

MainWindow::~MainWindow()
{
}

