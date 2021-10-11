#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    //重写定时器事件
    void timerEvent(QTimerEvent *);
    int id1;
    int id2;
    //重写事件过滤器
    bool eventFilter(QObject *,QEvent *);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
