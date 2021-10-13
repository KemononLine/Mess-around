#include <QPainter>

#include "constants.h"
#include "gamecontroller.h"
#include "snake.h"

static const qreal SNAKE_SIZE = TILE_SIZE;  //sanke的格子大小等同于map的格子大小

Snake::Snake(GameController &controller) :
    head(0, 0),
    growing(1),
    speed(4),
    moveDirection(NoMove),
    controller(controller)
{
}   //snake的构造

QRectF Snake::boundingRect() const
{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    for (QPointF p: tail)
    {
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }   //范围for，遍历tail

    QPointF tl = mapFromScene(QPointF(minX, minY));
    QPointF br = mapFromScene(QPointF(maxX, maxY));

    QRectF bound = QRectF(tl.x(),  // x
                          tl.y(),  // y
                          br.x() - tl.x() + SNAKE_SIZE,      // width
                          br.y() - tl.y() + SNAKE_SIZE       //height
                          );
    return bound;
}   //设置图形边界

QPainterPath Snake::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(QRectF(0, 0, SNAKE_SIZE, SNAKE_SIZE));

    for (QPointF p: tail)
    {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x(), itemp.y(), SNAKE_SIZE, SNAKE_SIZE));
    }

    return path;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillPath(shape(), Qt::yellow);
    painter->restore();
}

void Snake::setMoveDirection(Direction direction)
{
    if (moveDirection == MoveLeft && direction == MoveRight)
        return;
    if (moveDirection == MoveRight && direction == MoveLeft)
        return;
    if (moveDirection == MoveUp && direction == MoveDown)
        return;
    if (moveDirection == MoveDown && direction == MoveUp)
        return;
    moveDirection = direction;
}

Snake::Direction Snake::currentDirection()
{
	return moveDirection;
}

void Snake::advance(int step)
{
    if (!step)
    {
        return;
    }
    if (tickCounter++ % speed != 0)
    {
        return;
    }
    if (moveDirection == NoMove)
    {
        return;
    }

    if (growing > 0)
    {
		QPointF tailPoint = head;
        tail << tailPoint;
        growing -= 1;
    }   //初始growing增长，每涨一格，head变成tailipoint并将其追加到tail里，growing自减
    else
    {
        tail.removeFirst();
        tail << head;
    }

    switch (moveDirection)
    {
        case MoveLeft:
            moveLeft();
            break;
        case MoveRight:
            moveRight();
            break;
        case MoveUp:
            moveUp();
            break;
        case MoveDown:
            moveDown();
            break;
        default:
            break;
    }

    setPos(head);
    handleCollisions();
}

void Snake::moveLeft()
{
    head.rx() -= SNAKE_SIZE;
    if (head.rx() < -100)
    {
        head.rx() = 90; //设置穿透
    }
}

void Snake::moveRight()
{
    head.rx() += SNAKE_SIZE;
    if (head.rx() >= 100)
    {
        head.rx() = -100; //设置穿透
    }
}

void Snake::moveUp()
{
    head.ry() -= SNAKE_SIZE;
    if (head.ry() < -100)
    {
        head.ry() = 90; //设置穿透
    }
}

void Snake::moveDown()
{
    head.ry() += SNAKE_SIZE;
    if (head.ry() >= 100)
    {
        head.ry() = -100; //设置穿透
    }
}

void Snake::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();

    // 检查碰撞
    for (QGraphicsItem *collidingItem: collisions)
    {
        if (collidingItem->data(GD_Type) == GO_Food)
        {
            //让gamecotroller增加食物
            controller.snakeAteFood((Food *)collidingItem);
            growing += 1;
        }
    }

    //碰撞是否是头与身体
    if (tail.contains(head))
    {
        controller.snakeAteItself();
    }
}
