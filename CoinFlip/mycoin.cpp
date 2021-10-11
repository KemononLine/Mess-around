#include "mycoin.h"
#include <QMessageBox>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret)
    {
        QMessageBox::warning(this,"ERROR","FAIL TO LOAD TITLE");
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1=new QTimer(this);
    timer2=new QTimer(this);

    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/resource/Coin000%1").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断是否翻完了
        if(this->min>this->max)
        {
            this->min=1;
            timer1->stop();
            isAnimation=false;
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/resource/Coin000%1").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断是否翻完了
        if(this->max<this->min)
        {
            this->max=8;
            timer2->stop();
            isAnimation=false;
        }
    });
}

void MyCoin::mousePressEvent(QMouseEvent* e)
{
    if(this->isAnimation||MyCoin::isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);    //将点击事件传递下去
    }
}

void MyCoin::changeFlag()
{
    //正翻反
    if(this->flag)
    {
        timer1->start(30);
        isAnimation=true;
        this->flag=false;
    }
    else
    {
        timer2->start(30);
        isAnimation=true;
        this->flag=true;
    }
}
