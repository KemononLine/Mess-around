#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
      MyCoin(QString btnImg);

      //金币属性
      int posX;
      int posY;
      bool flag;

      //改变正反
      void changeFlag();
      QTimer* timer1;    //正翻反
      QTimer* timer2;    //反翻正
      int min=1;
      int max=8;

      //执行动画的标志
      bool isAnimation=false;

      //重写他的按下状态，在执行动画时不允许再按下
      void mousePressEvent(QMouseEvent* e);

      //是否胜利
      bool isWin=false;
signals:

};

#endif // MYCOIN_H
