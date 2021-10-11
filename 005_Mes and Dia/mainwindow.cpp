#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //点击按钮弹出对话框
    connect(ui->actionNew,&QAction::triggered,[=](){
        //对话框分为模态对话框（不可对其他窗口进行操作，eg，弹出错误警报时，无法点击其他窗口）和非模态对话框（可以对其他窗口进行操作）
//        QDialog dlg(this);  //模态
//        dlg.resize(200,100);
//        dlg.exec();

          //QDialog *dlg2=new QDialog(this);  //非模态
          //dlg2->resize(200,100);
          //dlg2->show();
          //此时关闭对话框，并不能释放new的内存，可能会造成内存溢出
          //dlg2->setAttribute(Qt::WA_DeleteOnClose);

          //消息对话框
          //QMessageBox::critical(this,"Error","WARNING!");   //错误对话框
          //QMessageBox::information(this,"Info","All Rights Reserved");  //信息对话框
          //QMessageBox::warning(this,"WARNING","LowBattery");    //警告对话框
          if(QMessageBox::Save==QMessageBox::question(this," ","Are You Sure?",QMessageBox::Save|QMessageBox::Cancel))
              {
              qDebug()<<"Choose Save";
          }
          else
              {
              qDebug()<<"Choose Cancel";
          }//询问对话框
          //还可设置第五个参数，为默认选择按钮是哪个
          //参数一：父亲，参数二：标题，参数三：显示内容，参数四：选项，参数五：默认选择项
          //其他标准对话框
          //QColor color=QColorDialog::getColor(QColor(255,0,0));
          //qDebug()<<color.red()<<color.green()<<color.blue();   //颜色对话框
          //QFile file=QFileDialog::getOpenFileName(this,"OPEN","C:/"); //文件对话框
          bool flag;
          QFont font=QFontDialog::getFont(&flag,QFont("华文彩云",28));

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

