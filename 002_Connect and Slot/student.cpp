#include "student.h"
#include <QDebug>

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::treat()
{
    qDebug()<<"Invite teacher to dinner";
}

void Student::treat(QString foodName)
{
    qDebug()<<"Invite teacher to"<<foodName;
    //chips出现蜜汁引号的原因是参数类型是Qstring，我们将Qstring->char *
    //QT里无法直接转，需要先转成 QByteArray
    //qDebug()<<"Invite teacher to"<<foodName.touUtf8().data();

}
