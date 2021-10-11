 #include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QMessageBox>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "playscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/resource/Coin0001.png"));
    this->setWindowTitle("选择关卡场景");
    //创建菜单栏（没使用添加设计师界面，代码添加

    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu *startMenu=bar->addMenu("开始");
    QAction *actionExit=startMenu->addAction("Exit");

    connect(actionExit,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/resource/BackButton.png",":/resource/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //图片切换
    //在mypushbutton中实现

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了返回";


        //场景延时切换
        //写一个自定义信号，让主场景监听这个信号，如果收到则主场景重新显示
        QTimer::singleShot(300,this,[=](){
                emit this->chooseSceneBack();
        });

    });

    //创建关卡按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton *levelBtn=new MyPushButton(":/resource/LevelIcon.png");
        levelBtn->setParent(this);
        //移动布局20个按钮
        levelBtn->move(25+i%4*70,130+i/4*70);

        //监听每个按钮的点击事件
        connect(levelBtn,&MyPushButton::clicked,[=](){
            //创建不同关卡


            play=new PlayScene(i+1);
            //设置游戏场景的位置
            play->setGeometry(this->geometry());

            //进入与隐藏场景
            this->hide();
            play->show();

            connect(play,&PlayScene::playSceneBack,this,[=](){
                this->setGeometry(play->geometry());

                qDebug()<<"接收了信号";
                this->show();
                delete play;
                play=nullptr;
            });

        });



        //设置按钮上的数字
        QLabel *label=new QLabel(this);
        label->setFixedSize(levelBtn->width(),levelBtn->height());
        label->setText(QString::number(1+i));
        //设置位置
        label->move(25+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //允许鼠标透过label点击button
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }


}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    bool rec=pix.load(":/resource/Title.png");
    if(!rec)
    {
        QMessageBox::warning(this,"ERROR","FAIL TO LOAD TITLE");
        return;
    }
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
