#include "mypushbutton.h"
#include <QDebug>

mypushbutton::mypushbutton(QWidget *parent) : QPushButton(parent)
{
    qDebug()<<"my button consturct!";
}
mypushbutton::~mypushbutton()
{
    qDebug()<<"my button desctruct!";
}
