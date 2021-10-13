#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QAction>
#include <iostream>
#include <QTime>
#include <QRandomGenerator>
#include <QPushButton>
//#include <QDebug>

#include "gamecontroller.h"
#include "food.h"
#include "snake.h"
#include "mainwindow.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(*this)),
    isPause(false)
{
    timer.start( 30 );

//	Food *a1 = new Food(0, -50);
//    scene.addItem(a1);


    scene.addItem(snake);
    scene.installEventFilter(this);
    //resume();
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));    //Qt4的信号槽连接方式，虽然可能出现槽函数与信号类型不匹配，但是小心使用还是可以的
   isPause = false;
}

GameController::~GameController()
{
    //qDeug()<<"GameCotrollerDestruct!";
}

void GameController::snakeAteFood(Food *food)
{
    scene.removeItem(food);

    addNewFood();
}

void GameController::snakeAteItself()
{
    QTimer::singleShot(0, this, [=](){
        gameOver();
    });  //lambda表达式yyds
}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    if (!isPause)
        switch (event->key()) {
            case Qt::Key_Left:
                snake->setMoveDirection(Snake::MoveLeft);
                break;
            case Qt::Key_Right:
                snake->setMoveDirection(Snake::MoveRight);
                break;
            case Qt::Key_Up:
                snake->setMoveDirection(Snake::MoveUp);
                break;
            case Qt::Key_Down:
                snake->setMoveDirection(Snake::MoveDown);
                break;
            case Qt::Key_Space:
                pause();
                break;
        }
    else resume();
}

void GameController::addNewFood()
{
    int x, y;

    do
    {

        x = QRandomGenerator::global()->bounded(200)/10-10;
        y = QRandomGenerator::global()->bounded(200)/10-10; //随机产生食物的位置

        x *= 10;
        y *= 10;
	} while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));

	Food *food = new Food(x, y);
    scene.addItem(food);
}

void GameController::gameOver()
{
    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    if (QMessageBox::Yes == QMessageBox::information(NULL,
                            tr("Game Over"), tr("Again?"),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::Yes))
    {
        connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
        scene.clear();

        snake = new Snake(*this);
        scene.addItem(snake);
        addNewFood();
    }
    else
    {
        exit(0);
    }
}//控制游戏的结束与重置

void GameController::pause()
{
    disconnect(&timer, SIGNAL(timeout()),&scene, SLOT(advance()));
    isPause = true;
    setResume();
}

void GameController::resume()
{
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
   isPause = false;
   setResume();
}

void GameController :: setResume()
{
    if(isPause == true)
    {
        resumeAction->setEnabled(true);
    }
    else
    {
        resumeAction->setEnabled(false);
    }
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    }
    else
    {
        return QObject::eventFilter(object, event);
    }
}   //时间过滤器
