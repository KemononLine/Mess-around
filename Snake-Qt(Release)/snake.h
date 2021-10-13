#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
//#include <QRect>
#include <QRectF>   //避免使用QRect，QRect在使用bottom或者right相关函数时会产生错误的返回值

class GameController;

class Snake : public QGraphicsItem
{
public:
    enum Direction
    {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    Snake(GameController & controller);

    QRectF boundingRect() const;    //使用boundingRect来套住图形，检测碰撞
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void setMoveDirection(Direction direction);
	Direction currentDirection();

protected:
    void advance(int step);

private:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void handleCollisions();

    QPointF        head;
    int            growing;
    int            speed;
    QList<QPointF> tail;
    int            tickCounter;
    Direction      moveDirection;
    GameController &controller;
};

#endif // SNAKE_H
