#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);
    //接受teacher信号的槽函数
    //void,需要声明也需要实现，可以有参数，可以重载

    void treat();
    void treat(QString foodName);

signals:

};

#endif // STUDENT_H
