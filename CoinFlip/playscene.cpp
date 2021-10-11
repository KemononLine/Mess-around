#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QTimer>
#include <QPainter>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QString>
#include <QPropertyAnimation>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    this->levelIndex=levelNum;  //成员属性，记住这个值，以后可能有用
    QString str=QString("进入了第 %1 关").arg(levelNum);
    qDebug()<<str;
    QString str2=QString("第 %1 关").arg(levelNum);
    //初始化游戏场景
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/resource/Coin0001.png"));
    this->setWindowTitle(str2);
    //菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");
    QAction *exitAction=startMenu->addAction("Exit");

    connect(exitAction,&QAction::triggered,[=](){
        this->close();
    });
    //返回选关界面
    MyPushButton *backBtn=new MyPushButton(":/resource/BackButton.png",":/resource/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了返回";


        //场景延时切换
        //写一个自定义信号，让选关场景监听这个信号，如果收到则选关场景重新显示
        QTimer::singleShot(300,this,[=](){
                qDebug()<<"发出了信号";
                emit this->playSceneBack();
        });

    });

    //显示当前关卡数
    //对标签设置字体与字号
    QLabel *label=new QLabel(this);
    QFont font;
    font.setFamily("APJapanesefont");
    font.setPointSize(20);
    QString str_2=QString("Level %1 ").arg(this->levelIndex);
    label->setFont(font);
    label->setText(str_2);
    label->setGeometry(30,this->height()-50,120,50);

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel* winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/resource/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());



    //显示金币背景图片
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QLabel* label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/resource/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);


        //创建金币
        QString str_3;
        if(this->gameArray[i][j]==1)
        {
            str_3=":/resource/Coin0001.png";
        }
        else
        {
            str_3=":/resource/Coin0008.png";
        }


        MyCoin* coin=new MyCoin(str_3);
        coin->setParent(this);
        coin->move(59+i*50,204+j*50);

        //给金币属性赋值
        coin->posX=i;
        coin->posY=j;
        coin->flag=this->gameArray[i][j];   //1正，0反

        //
        coinBtn[i][j]=coin;

        //点击金币进行翻转
        connect(coin,&MyCoin::clicked,[=](){
            //修复在胜利后迅速点击其他按钮，仍可以翻转的bug
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    this->coinBtn[i][j]->isWin=true;
                }
            }
            //
            coin->changeFlag();
            this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;

            //翻转周围的硬币

            if(coin->posX+1<=3) //右侧金币可翻转
            {
                coinBtn[coin->posX+1][coin->posY]->changeFlag();
                this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;
            }

            if(coin->posX-1>=0)
            {
                coinBtn[coin->posX-1][coin->posY]->changeFlag();
                this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
            }

            if(coin->posY+1<=3)
            {
                coinBtn[coin->posX][coin->posY+1]->changeFlag();
                this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
            }

            if(coin->posY-1>=0)
            {
                coinBtn[coin->posX][coin->posY-1]->changeFlag();
                this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
            }

            //继续修复胜利后快速点击仍可翻转的bug
            //在周围硬币完全翻转后，其他硬币又可翻转
            //之前的isAnimation只能控制自己本身不能翻转
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    this->coinBtn[i][j]->isWin=false;
                }
            }

            //判断是否胜利
            this->isWin=true;
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    if(coinBtn[i][j]->flag==false)
                    {
                        this->isWin=false;
                        break;
                    }
                }
            }
            if(this->isWin==true)
            {
                qDebug()<<"WIN!";
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        coinBtn[i][j]->isWin=true;
                    }
                }

                //将胜利图片移下来
                QPropertyAnimation* animation=new QPropertyAnimation(winLabel,"geometry");
                animation->setDuration(1000);
                //设置开始，结束，弹跳曲线
                animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                animation->setEndValue(QRect(winLabel->x(),winLabel->y()+144,winLabel->width(),winLabel->height()));
                animation->setEasingCurve(QEasingCurve::OutBounce);
                animation->start();

            }

        });

        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
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

//    pix.load(":/resource/BoardNode.png");
//    for(int i=0;i<4;i++)
//    {
//        for(int j=0;j<4;j++)
//        {
//            painter.drawPixmap(57+i*50,200+j*50,pix.width(),pix.height(),pix);
//        }
//    }


}

