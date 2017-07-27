#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

int plane_x, plane_y;//plane position
int bullet_x, bullet_y;//bullet position
int enemy_x, enemy_y;//enemy position
int score;//score
int life;//life
int hight, width;//window size

void gotoxy(int x, int y)//类似于清屏函数，光标移动到原点位置进行重画
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()
{
	hight = 20;
	width = 30;
	plane_x = hight / 2;
	plane_y = width / 2;
	bullet_x = 0;
	bullet_y = plane_y;
	enemy_x = 0;
	enemy_y = plane_y;
	score = 0;
	life = 3;
}

void show()
{
	gotoxy(0, 0);//clear screen
	HideCursor();
	int i, j;
	for (i = 0; i < hight; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((i == plane_x) && (j == plane_y))
				printf("*");//plane
			else if ((i == enemy_x) && (j == enemy_y))
				printf("@");//enemy
			else if ((i == bullet_x) && (j == bullet_y))
				printf("|");//bullet
			else
				printf(" ");//blank space
		}
		printf("\n");
	}
	printf("score:%d\n", score);
	printf("life:%d\n", life);
}

void updateWithoutInput()
{
	if (bullet_x > -1)
		bullet_x--;

	if ((bullet_x == enemy_x) && (bullet_y == enemy_y))
	{
		score++;
		enemy_x = -1;           // 产生新的飞机
		enemy_y = rand() % width;
		bullet_x = -2;//子弹消失
	}

	if (enemy_x > hight)//敌机飞出界限
	{
		enemy_x = -1;           // 产生新的飞机
		enemy_y = rand() % width;
		life--;
	}

	static int speed = 0;
	if (speed<12)
		speed++;
	if (speed == 12)
	{
		enemy_x++;
		speed = 0;
	}
}

void updateWithInput()
{
	char input;
	if (kbhit())
	{
		input = getch();
		if (input == 'a')
			plane_y--;

		if (input == 'd')
			plane_y++;

		if (input == 'w')
			plane_x--;

		if (input == 's')
			plane_x++;
		
		if (input == ' ')
		{
			bullet_x = plane_x - 1;
			bullet_y = plane_y;
		}
	}
}

void gameover()
{
	if (score >= 15)
		printf("你很棒棒哟(＾Ｕ＾)ノ~ＹＯ\n");
	else if ((score >= 5) && (score < 15))
		printf("还要继续努力哟o(*￣▽￣*)ブ\n");
	else if (score < 5)
		printf("你个战五渣！\n");
	printf("Game Over!\n");
}

// 函数外全局变量定义
void main()
{
	startup();    // 数据初始化
	while (life>0)  //  游戏循环执行
	{
		show();   // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();    // 与用户输入有关的更新
	}

	gameover();
	getch();
}