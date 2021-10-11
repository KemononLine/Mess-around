#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *); //重写paintEvent画背景图
    //场景切换
    ChooseLevelScene *chooseScene =nullptr;
    ~MainScene();

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
