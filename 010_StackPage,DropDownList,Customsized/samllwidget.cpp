#include "samllwidget.h"
#include "ui_samllwidget.h"

samllWidget::samllWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::samllWidget)
{
    ui->setupUi(this);
    //SpinBox调整，Slider滑动
    void (QSpinBox::*spSignal)(int)=&QSpinBox::valueChanged;
    connect(ui->spinBox,spSignal,ui->horizontalSlider,&QSlider::setValue);
    //Slider滑动，Spin调整
    void (QSlider::*slSignal)(int)=&QSlider::valueChanged;
    connect(ui->horizontalSlider,slSignal,ui->spinBox,&QSpinBox::setValue);
}

void samllWidget::setNum(int num)
{
    ui->spinBox->setValue(num);
}

int samllWidget::getNum()
{
    return ui->spinBox->value();
}

samllWidget::~samllWidget()
{
    delete ui;
}
