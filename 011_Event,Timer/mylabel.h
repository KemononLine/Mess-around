#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QWidget>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    myLabel(QWidget *parent=nullptr);
    void leaveEvent(QEvent *event);
    void enterEvent(QEnterEvent *event);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void mouseMoveEvent(QMouseEvent *ev);

    //通过事件分发器拦截鼠标按下事件

    bool event(QEvent *e);

};

#endif // MYLABEL_H
