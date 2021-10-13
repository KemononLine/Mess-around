#include <QGraphicsView>
#include <QTimer>
#include <QAction>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include <QIcon>
#include <QPushButton>
//#include <QPixmap>
//#include <QPainter>
//#include <QPaintEvent>
//#include <QDebug>

#include "constants.h"
#include "gamecontroller.h"
#include "mainwindow.h"
#include "snake.h"
#include "food.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameController(*scene, this))
{
    setCentralWidget(view);

    setFixedSize(600,600);  //设置固定窗口大小
    setWindowIcon(QIcon(":/images/snake_ico")); //设置图标

    QPushButton *btn=new QPushButton;
    //btn->show();  //以新窗口弹出
    btn->setParent(this);   //依赖于原窗口
    btn->resize(100,60);
    btn->move(250,500);
    btn->setText("START!");
    btn->setIcon(QIcon(":/images/snake_ico"));
    //btn->setShortcut(Qt::Key_Up);

//    QPainter painter(this);
//    QPixmap pix;
//    pix.load(":/../Pictures/Cyberpunk 2077/0001.png");
//    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    connect(btn,&QPushButton::clicked,[=](){
        Food *a1 = new Food(0, -50);
        scene->addItem(a1);
        btn->hide();
    }); //点击btn后btn消失,并且产生食物


	createActions();
	createMenus();
    //部件

    initScene();
    initSceneBackground();
    //初始化场景
    QTimer::singleShot(0,this,[=](){
        adjustViewSize();
    });//定时器控制延时
}

MainWindow::~MainWindow()
{
    //qDebug()<<"Destruct!";    //测试析构
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio); //设置视角模式
}

void MainWindow::createActions()    //菜单栏，状态栏，工具栏中各种部件的产生
{
    //产生新游戏
    newGameAction = new QAction(tr("&New Game"), this); //生成并挂到对象树上
    newGameAction->setShortcuts(QKeySequence::New); //生成一个新文件
	newGameAction->setStatusTip(tr("Start a new game"));
    connect(newGameAction, &QAction::triggered, this, &MainWindow::newGame);    //设置信号与槽函数连接

    //退出键
	exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));  //快捷键设置
	exitAction->setStatusTip(tr("Exit the game"));
	connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    //暂停键
	pauseAction = new QAction(tr("&Pause"), this);
	pauseAction->setStatusTip(tr("Pause..."));
	connect(pauseAction, &QAction::triggered, game, &GameController::pause);

    //开始建
	resumeAction = new QAction(tr("&Resume"), this);
	resumeAction->setStatusTip(tr("Resume..."));
    resumeAction->setEnabled(false);
    game->setResumeAction(resumeAction);
    connect(resumeAction, &QAction::triggered, game, &GameController::resume);

    //帮助键
	gameHelpAction = new QAction(tr("Game &Help"), this);
	gameHelpAction->setShortcut(tr("Ctrl+H"));
	gameHelpAction->setStatusTip(tr("Help on this game"));
	connect(gameHelpAction, &QAction::triggered, this, &MainWindow::gameHelp);

    //关于游戏键
    aboutAction = new QAction(tr("&About Snake"), this);
	aboutAction->setStatusTip(tr("Show the application's about box"));
	connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    //关于QT键
	aboutQtAction = new QAction(tr("About &Qt"), this);
	aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);
}

//菜单栏设置
void MainWindow::createMenus()
{
	QMenu *options = menuBar()->addMenu(tr("&Options"));
	options->addAction(newGameAction);
	options->addSeparator();
	options->addAction(pauseAction);
	options->addAction(resumeAction);
	options->addSeparator();
	options->addAction(exitAction);

	QMenu *help = menuBar()->addMenu(tr("&Help"));
	help->addAction(gameHelpAction);
	help->addAction(aboutAction);
	help->addAction(aboutQtAction);
}

//初始化场景
void MainWindow::initScene()
{
    scene->setSceneRect(-100, -100, 200, 200);  //设置大小位置
}

//初始化背景
void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}

//游戏的结束与产生
void MainWindow::newGame()
{
    QTimer::singleShot(0, game, SLOT(gameOver()));  //利用QT4的接受方式
}

//关于游戏
void MainWindow::about()
{
	QMessageBox::about(this, tr("About this Game"), tr("<h2>Snake Game</h2>"
        "<p>Copyright &copy; LCY."
        "<p>This game is a small Qt application. It is written by NNU-LCY."));
}

//游戏帮助
void MainWindow::gameHelp()
{
	QMessageBox::about(this, tr("Game Help"), tr("Using direction keys to control the snake to eat the food"
		"<p>Space - pause & resume"));
}
