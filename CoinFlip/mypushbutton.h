#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //构造函数
    MyPushButton(QString normalImag,QString pressImag="");  //pressImag设置有默认参，可以让非换图按钮和换图按钮用同一个函数
    //保存mainscene传入的默认显示路径，以及按下后的路径
    QString normalImagPath;
    QString pressImagPath;

    //弹跳特效
    void zoomdown();
    void zoomup();
    //重写按钮的按下和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
