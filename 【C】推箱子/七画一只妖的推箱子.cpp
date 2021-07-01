
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>


void color(short x)//设置字体颜色 固定写法 
{
	if(x>=0 && x<=15)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}



int map[8][8] =//画地图 
{
	1,1,1,1,1,1,1,1,
	1,1,1,1,6,1,1,1,
	1,1,1,1,2,1,1,1,
	1,6,2,5,0,1,1,1,
	1,1,1,0,0,2,6,1,
	1,1,1,2,1,1,1,1,
	1,1,1,6,1,1,1,1,
	1,1,1,1,1,1,1,1
};


int map_File[8][8] =//重置地图的备份 
{
	1,1,1,1,1,1,1,1,
	1,1,1,1,6,1,1,1,
	1,1,1,1,2,1,1,1,
	1,6,2,5,0,1,1,1,
	1,1,1,0,0,2,6,1,
	1,1,1,2,1,1,1,1,
	1,1,1,6,1,1,1,1,
	1,1,1,1,1,1,1,1
};

/*---------------------------------------------------------

0          空地
1            墙壁 □
2            箱子
2+6=8            箱子在目的地上面
5+6=11            人在目的地上面
5            人
6            目的地

■☆★⊙⊕

----------------------------------------------------------*/
void ChongZhi_Map()//重置地图 
{
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			map[i][j] = map_File[i][j]; 
		}
	}
}

void Hua_Map()//画地图 
{
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			switch (map[i][j])//浏览数组，将每个元素的值对应的图案输出出来 
			{
			case 0:printf("  ");break;
			case 1:printf("■");break;
			case 2:printf("☆");break;
			case 8:color(2);printf("★");color(7);break;
			case 11:case 5:printf("⊙");break;
			case 6:printf("⊕");break;
			}
		}
		printf("\n");//每8个图案换一行 
	}
}

void Ding_Wei()//定位以及键盘交互 
{
	int i, j;
	for (i = 0;i < 8;i++)//浏览地图，找到小人的位置 
	{
		for (j = 0;j < 8;j++)
		{
			if (map[i][j] == 11 || map[i][j] == 5)
			{
				break;//找到了小人的位置跳出循环 
			}
		}
		if (map[i][j] == 11 || map[i][j] == 5)
		{
			break;//找到了小人的位置跳出循环 
		}
	}

	char key = _getch();//获取的按下的键的字符放到字符型变量char里面 
	switch (key)//控制小人 
	{
	case 'w':case 'W':
		if (map[i - 1][j] == 0 || map[i - 1][j] == 6)//前进方向是空地或者目的地 
		{
			map[i][j] -= 5;map[i - 1][j] += 5;
		}
		else if (map[i - 1][j] == 2 || map[i - 1][j] == 8)//前进方向是箱子 
		{
			if (map[i - 2][j] == 0 || map[i - 2][j] == 6)//箱子的前方是空地或者目的地 
			{
				map[i][j] -= 5;
				map[i - 1][j] += 5;
				map[i - 1][j] -= 2;
				map[i - 2][j] += 2;
			}
		}

		break;

	case 's':case 'S':
		if (map[i + 1][j] == 0 || map[i + 1][j] == 6)//前进方向是空地或者目的地 
		{
			map[i][j] -= 5;map[i + 1][j] += 5;
		}
		else if (map[i + 1][j] == 2 || map[i + 1][j] == 8)//前进方向是箱子 
		{
			if (map[i + 2][j] == 0 || map[i + 2][j] == 6)//箱子的前方是空地或者目的地 
			{
				map[i][j] -= 5;
				map[i + 1][j] += 5;
				map[i + 1][j] -= 2;
				map[i + 2][j] += 2;
			}
		}
		break;

	case 'a':case 'A':
		if (map[i][j - 1] == 0 || map[i][j - 1] == 6)//前进方向是空地或者目的地 
		{
			map[i][j] -= 5;map[i][j - 1] += 5;
		}
		else if (map[i][j - 1] == 2 || map[i][j - 1] == 8)//前进方向是箱子 
		{
			if (map[i][j - 2] == 0 || map[i][j - 2] == 6)//箱子的前方是空地或者目的地 
			{
				map[i][j] -= 5;
				map[i][j - 1] += 5;
				map[i][j - 1] -= 2;
				map[i][j - 2] += 2;
			}
		}
		break;

	case 'd':case 'D':
		if (map[i][j + 1] == 0 || map[i][j + 1] == 6)//前进方向是空地或者目的地 
		{
			map[i][j + 1] += 5;map[i][j] -= 5;
		}
		else if (map[i][j + 1] == 2 || map[i][j + 1] == 8)//前进方向是箱子 
		{
			if (map[i][j + 2] == 0 || map[i][j + 2] == 6)//箱子的前方是空地或者目的地 
			{
				map[i][j] -= 5;
				map[i][j + 1] += 5;
				map[i][j + 1] -= 2;
				map[i][j + 2] += 2;
			}
		}
		break;
	case 'R':case 'r': {ChongZhi_Map();break;}//按R重置地图 
	}
}

int Pass_PanDuan()//判断此时地图还要多少个目的地上面没有箱子 
{
	int z = 0;
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			if (map[i][j] == 6)
				z++;
		}
	}
	return (z);//返回目的地上面没有箱子的个数 
}

void goto_xy(int x, int y)	//刷新屏幕，固定写法 
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//获取标准输出句柄 
	COORD pos={x,y};			//坐标结构体 
	SetConsoleCursorPosition(hOut,pos);	//定位光标位置 
}


int main()
{
	system("mode con cols=30 lines=10");//自定义窗口大小 
	int flag = 1;//设定一个一键结束游戏的变量 

	while (flag)//当flag不为0时一直循环 
	{
		Hua_Map();//显示地图 
		color(4);printf("按R重置");color(7);
		Ding_Wei();//操作 
		//system("cls");//重置屏幕 
		goto_xy(0,0);
		if (Pass_PanDuan() == 0)//当目的地上面没有箱子的个数为0时进入IF 
		{
			system("cls");
			printf("你过关了\n");
			color(4);printf("按R重置，按O结束游戏");color(7);
			char key = _getch();
			switch (key)
			{
			case 'R':case 'r': {system("cls");ChongZhi_Map();break;} 
			case 'O':case 'o':flag = 0;break;
			}
		}
	}
	return 0;
}



