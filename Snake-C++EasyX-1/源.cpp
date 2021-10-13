#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#define BLOCK_SIZE 20 // ÿ��С���ӵĳ����С 
#define HEIGHT 30 // �߶���һ��30��С����
#define WIDTH 40 //  �����һ��40��С���� 
using namespace std;

// ȫ�ֱ�������
int Blocks[HEIGHT][WIDTH] = { 0 }; //  ��ά���飬���ڼ�¼���е���Ϸ����
char moveDirection;  //  С���ƶ�����
int food_i, food_j; //  ʳ���λ��
int isFailure = 0; //  �Ƿ���Ϸʧ��

void moveSnake();
void startup();
void show();
void updateWithoutInput();
void updateWithInput();

void moveSnake() //  �ƶ�С�߼���ش�����
{
	int i, j;
	for (i = 0;i < HEIGHT;i++) // ���б��� 
		for (j = 0;j < WIDTH;j++) // ���б���
			if (Blocks[i][j] > 0) // ����0��ΪС��Ԫ�� 
				Blocks[i][j]++; //  ����+1
	int oldTail_i, oldTail_j, oldHead_i, oldHead_j; // ����������洢����β������ͷ����  
	int max = 0; // ���ڼ�¼���ֵ 
	for (i = 0;i < HEIGHT;i++) //  �����б���
	{
		for (j = 0;j < WIDTH;j++)
		{
			if (max < Blocks[i][j]) //  �����ǰԪ��ֵ��max��
			{
				max = Blocks[i][j]; // ����max��ֵ
				oldTail_i = i; //  ��¼���ֵ�����꣬���Ǿ���β��λ��
				oldTail_j = j; //  
			}
			if (Blocks[i][j] == 2) // �ҵ���ֵΪ2 
			{
				oldHead_i = i; //  ��ֵΪ2ǡ���Ǿ���ͷ��λ��
				oldHead_j = j; //  
			}
		}
	}
	int newHead_i = oldHead_i; //  �趨�����洢����ͷ��λ��
	int newHead_j = oldHead_j;

	//  �����û��������趨����ͷ��λ��
	if (moveDirection == 'w') // �����ƶ�
		newHead_i = oldHead_i - 1;
	else if (moveDirection == 's' ) // �����ƶ�
		newHead_i = oldHead_i + 1;
	else if (moveDirection == 'a' ) // �����ƶ�
		newHead_j = oldHead_j - 1;
	else if (moveDirection == 'd' ) // �����ƶ�
		newHead_j = oldHead_j + 1;
	//  �����ͷ�����߽磬������ͷ����������Ϸʧ��
	if (newHead_i >= HEIGHT || newHead_i < 0 || newHead_j >= WIDTH || newHead_j < 0
		|| Blocks[newHead_i][newHead_j]>0)
	{
		isFailure = 1; //  ��Ϸʧ��
		return; // ��������
	}

	Blocks[newHead_i][newHead_j] = 1;  // ����ͷλ����ֵΪ1	
	if (newHead_i == food_i && newHead_j == food_j) //  �������ͷ��������ʳ��
	{
		food_i = rand() % (HEIGHT - 5) + 2; //  ʳ���������λ��
		food_j = rand() % (WIDTH - 5) + 2; //  
		// ���Ծ���β�����൱���ߵĳ���+1
	}
	else // ����ͷû������ʳ��
		Blocks[oldTail_i][oldTail_j] = 0; // ����β��ɿհף�����ʳ��ʱ�����ߵĳ��Ȳ���
}

void startup()  //  ��ʼ������
{
	int i;
	Blocks[HEIGHT / 2][WIDTH / 2] = 1; // �����м仭��ͷ������Ϊ1
	for (i = 1;i <= 4;i++) //  ��������4��������ֵ����Ϊ2,3,4,5
		Blocks[HEIGHT / 2][WIDTH / 2 - i] = i + 1;
	moveDirection = 'd';	 //  ��ʼ�����ƶ�
	food_i = rand() % (HEIGHT - 5) + 2; //  ��ʼ�����ʳ��λ��
	food_j = rand() % (WIDTH - 5) + 2; //  
	initgraph(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE); //  �¿�����
	setlinecolor(RGB(200, 200, 200)); // ����������ɫ
	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ���ƺ���
{
	cleardevice(); // ����
	int i, j;
	for (i = 0;i < HEIGHT;i++) //  �Զ�ά��������Ԫ�ر���
	{
		for (j = 0;j < WIDTH;j++)
		{
			if (Blocks[i][j] > 0) // Ԫ�ش���0��ʾ���ߣ��������ߵ�����Ϊ��ɫ
				setfillcolor(RGB(255, 255, 0));
			else
				setfillcolor(RGB(150, 150, 150)); // Ԫ��Ϊ0��ʾΪ�գ���ɫΪ��ɫ
			// �ڶ�Ӧλ�ô����Զ�Ӧ��ɫ����С����
			fillrectangle(j * BLOCK_SIZE, i * BLOCK_SIZE,
				(j + 1) * BLOCK_SIZE, (i + 1) * BLOCK_SIZE);
		}
	}
	setfillcolor(RGB(255, 0, 0)); //  ʳ��Ϊ��ɫ
	//  ����ʳ��С����
	fillrectangle(food_j * BLOCK_SIZE, food_i * BLOCK_SIZE,
		(food_j + 1) * BLOCK_SIZE, (food_i + 1) * BLOCK_SIZE);
	if (isFailure) //  �����Ϸʧ��
	{
		setbkmode(TRANSPARENT); // ��������͸��    
		settextcolor(RGB(0, 255, 255));// �趨������ɫ
		settextstyle(80, 0, _T("����")); //  �趨���ִ�С����ʽ
		outtextxy(240, 220, _T("��Ϸʧ��")); //  �����������
	}
	FlushBatchDraw(); // ��������
}

void updateWithoutInput() // �������޹صĸ��º���
{
	if (isFailure) //  �����Ϸʧ�ܣ���������
		return;
	static int waitIndex = 1; // ��̬�ֲ���������ʼ��ʱΪ1
	waitIndex++; // ÿһ֡+1
	if (waitIndex == 10) // �������10��ִ�У�����С��ÿ��10֡�ƶ�һ��
	{
		moveSnake(); //  ����С���ƶ�����
		waitIndex = 1; // �ٱ��1
	}
}

void updateWithInput()  // �������йصĸ��º���
{
	if (_kbhit() && isFailure == 0)  //  ����а������룬���Ҳ�ʧ��
	{
		char input = _getch(); //  ��ð�������
		if (input == 'a' || input == 's' || input == 'd' || input == 'w') // �����asdw 
		{
			moveDirection = input;  // �趨�ƶ�����
			moveSnake(); // ����С���ƶ�����
		}
	}
}

int main() //  ������
{
	startup();  // ��ʼ����������ִ��һ��	
	while (1)   // һֱѭ��
	{
		show();  // ���л���
		updateWithoutInput(); // �������޹صĸ��� 
		updateWithInput();    // �������йصĸ���
	}
	return 0;
}