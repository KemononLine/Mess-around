#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //固定窗口属性
    setFixedSize(320,588);

    setWindowIcon(QIcon(":/resource/Coin0001.png"));
    setWindowTitle("翻金币");
    //UI菜单项设置
    connect(ui->actionExit,&QAction::triggered,[=](){
        this->close();
    });

    //开始按键
    MyPushButton *startBtn= new MyPushButton(":/resource/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooseScene=new ChooseLevelScene;

    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        this->setGeometry(chooseScene->geometry()); //修复窗口移动bug

        chooseScene->hide();
        this->show();
    });

    //开始按键的按动效果
    connect(startBtn,&QPushButton::clicked,[=](){
        qDebug()<<"点击了开始";
        startBtn->zoomdown();
        startBtn->zoomup();

        //进入选择关卡场景
        //设置延时，展示动画效果
        QTimer::singleShot(500,this,[=](){
            //设置choosescene的位置，以修复不同窗口之间错位的bug
            chooseScene->setGeometry(this->geometry());

            this->hide();
            chooseScene->show();
        });
        //延时时间，执行对象，执行操作

        //监听选择关卡的信号，重新显示
        /*connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
            chooseScene->hide();
            this->show();
        });*/ //我们注意到，此段代码放在这里，每点击一次开始，就跑一次，效率低，将其放到外面
    });
}
//设置主场景
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //在背景下画图标
    pix.load(":/resource/Title.png");

    //修改图标大小
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}

