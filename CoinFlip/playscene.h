#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    int levelIndex;
    void paintEvent(QPaintEvent *);

    //维护每个关卡的具体数据
    int gameArray[4][4];

    //维护每个coin的上下左右
    MyCoin* coinBtn[4][4];

    bool isWin;
signals:
    void playSceneBack();

};

#endif // PLAYSCENE_H
