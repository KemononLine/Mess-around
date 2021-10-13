#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#define BLOCK_SIZE 20 // 每个小格子的长宽大小 
#define HEIGHT 30 // 高度上一共30个小格子
#define WIDTH 40 //  宽度上一共40个小格子 
using namespace std;

// 全局变量定义
int Blocks[HEIGHT][WIDTH] = { 0 }; //  二维数组，用于记录所有的游戏数据
char moveDirection;  //  小蛇移动方向
int food_i, food_j; //  食物的位置
int isFailure = 0; //  是否游戏失败

void moveSnake();
void startup();
void show();
void updateWithoutInput();
void updateWithInput();

void moveSnake() //  移动小蛇及相关处理函数
{
	int i, j;
	for (i = 0;i < HEIGHT;i++) // 对行遍历 
		for (j = 0;j < WIDTH;j++) // 对列遍历
			if (Blocks[i][j] > 0) // 大于0的为小蛇元素 
				Blocks[i][j]++; //  让其+1
	int oldTail_i, oldTail_j, oldHead_i, oldHead_j; // 定义变量，存储旧蛇尾、旧蛇头坐标  
	int max = 0; // 用于记录最大值 
	for (i = 0;i < HEIGHT;i++) //  对行列遍历
	{
		for (j = 0;j < WIDTH;j++)
		{
			if (max < Blocks[i][j]) //  如果当前元素值比max大
			{
				max = Blocks[i][j]; // 更新max的值
				oldTail_i = i; //  记录最大值的坐标，就是旧蛇尾的位置
				oldTail_j = j; //  
			}
			if (Blocks[i][j] == 2) // 找到数值为2 
			{
				oldHead_i = i; //  数值为2恰好是旧蛇头的位置
				oldHead_j = j; //  
			}
		}
	}
	int newHead_i = oldHead_i; //  设定变量存储新蛇头的位置
	int newHead_j = oldHead_j;

	//  根据用户按键，设定新蛇头的位置
	if (moveDirection == 'w') // 向上移动
		newHead_i = oldHead_i - 1;
	else if (moveDirection == 's' ) // 向下移动
		newHead_i = oldHead_i + 1;
	else if (moveDirection == 'a' ) // 向左移动
		newHead_j = oldHead_j - 1;
	else if (moveDirection == 'd' ) // 向右移动
		newHead_j = oldHead_j + 1;
	//  如果蛇头超出边界，或者蛇头碰到蛇身，游戏失败
	if (newHead_i >= HEIGHT || newHead_i < 0 || newHead_j >= WIDTH || newHead_j < 0
		|| Blocks[newHead_i][newHead_j]>0)
	{
		isFailure = 1; //  游戏失败
		return; // 函数返回
	}

	Blocks[newHead_i][newHead_j] = 1;  // 新蛇头位置数值为1	
	if (newHead_i == food_i && newHead_j == food_j) //  如果新蛇头正好碰到食物
	{
		food_i = rand() % (HEIGHT - 5) + 2; //  食物重新随机位置
		food_j = rand() % (WIDTH - 5) + 2; //  
		// 不对旧蛇尾处理，相当于蛇的长度+1
	}
	else // 新蛇头没有碰到食物
		Blocks[oldTail_i][oldTail_j] = 0; // 旧蛇尾变成空白，不吃食物时保持蛇的长度不变
}

void startup()  //  初始化函数
{
	int i;
	Blocks[HEIGHT / 2][WIDTH / 2] = 1; // 画面中间画蛇头，数字为1
	for (i = 1;i <= 4;i++) //  向左依次4个蛇身，数值依次为2,3,4,5
		Blocks[HEIGHT / 2][WIDTH / 2 - i] = i + 1;
	moveDirection = 'd';	 //  初始向右移动
	food_i = rand() % (HEIGHT - 5) + 2; //  初始化随机食物位置
	food_j = rand() % (WIDTH - 5) + 2; //  
	initgraph(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE); //  新开画面
	setlinecolor(RGB(200, 200, 200)); // 设置线条颜色
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	cleardevice(); // 清屏
	int i, j;
	for (i = 0;i < HEIGHT;i++) //  对二维数组所有元素遍历
	{
		for (j = 0;j < WIDTH;j++)
		{
			if (Blocks[i][j] > 0) // 元素大于0表示是蛇，这里让蛇的身体为黄色
				setfillcolor(RGB(255, 255, 0));
			else
				setfillcolor(RGB(150, 150, 150)); // 元素为0表示为空，颜色为灰色
			// 在对应位置处，以对应颜色绘制小方格
			fillrectangle(j * BLOCK_SIZE, i * BLOCK_SIZE,
				(j + 1) * BLOCK_SIZE, (i + 1) * BLOCK_SIZE);
		}
	}
	setfillcolor(RGB(255, 0, 0)); //  食物为红色
	//  绘制食物小方块
	fillrectangle(food_j * BLOCK_SIZE, food_i * BLOCK_SIZE,
		(food_j + 1) * BLOCK_SIZE, (food_i + 1) * BLOCK_SIZE);
	if (isFailure) //  如果游戏失败
	{
		setbkmode(TRANSPARENT); // 文字字体透明    
		settextcolor(RGB(0, 255, 255));// 设定文字颜色
		settextstyle(80, 0, _T("宋体")); //  设定文字大小、样式
		outtextxy(240, 220, _T("游戏失败")); //  输出文字内容
	}
	FlushBatchDraw(); // 批量绘制
}

void updateWithoutInput() // 与输入无关的更新函数
{
	if (isFailure) //  如果游戏失败，函数返回
		return;
	static int waitIndex = 1; // 静态局部变量，初始化时为1
	waitIndex++; // 每一帧+1
	if (waitIndex == 10) // 如果等于10才执行，这样小蛇每隔10帧移动一次
	{
		moveSnake(); //  调用小蛇移动函数
		waitIndex = 1; // 再变成1
	}
}

void updateWithInput()  // 和输入有关的更新函数
{
	if (_kbhit() && isFailure == 0)  //  如果有按键输入，并且不失败
	{
		char input = _getch(); //  获得按键输入
		if (input == 'a' || input == 's' || input == 'd' || input == 'w') // 如果是asdw 
		{
			moveDirection = input;  // 设定移动方向
			moveSnake(); // 调用小蛇移动函数
		}
	}
}

int main() //  主函数
{
	startup();  // 初始化函数，仅执行一次	
	while (1)   // 一直循环
	{
		show();  // 进行绘制
		updateWithoutInput(); // 和输入无关的更新 
		updateWithInput();    // 和输入有关的更新
	}
	return 0;
}