#ifndef SAMLLWIDGET_H
#define SAMLLWIDGET_H

#include <QWidget>

namespace Ui {
class samllWidget;
}

class samllWidget : public QWidget
{
    Q_OBJECT

public:
    explicit samllWidget(QWidget *parent = nullptr);
    void setNum(int num);
    int getNum();
    ~samllWidget();

private:
    Ui::samllWidget *ui;
};

#endif // SAMLLWIDGET_H
