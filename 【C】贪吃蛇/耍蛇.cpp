#include<stdio.h>
#include<stdlib.h>
#include<conio.h>			 
#include<windows.h>

#define N 1000

void goto_xy(int x, int y)	//定位光标位置到指定坐标
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//获取标准输出句柄 
	COORD pos={x,y};			//坐标结构体 
	SetConsoleCursorPosition(hOut,pos);	//定位光标位置 
}

int x_xianzhi(int sx)		//限制x坐标的移动范围（0~39）
{
	if(sx==-1)
		return 39;
	else if(sx==40)
		return 0;
	return sx;
}

int y_xianzhi(int sy)		//限制y坐标的移动范围（0~19）
{
	if(sy==-1)
		return 19;
	else if(sy==20)
		return 0;
	return sy;
}

void huan(char *a,char *b)		//交换*a和*b指向的字符（把蛇身搬到下一个位置）
{
	char temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void ban(int dong,int fen,int b[N],char a[20][40],int *y,int *x)	//根据b数组里的移动数据把蛇身搬到下一个位置
{
	int jiance;
	for(jiance=dong;jiance>dong-fen-1;jiance--)
	{
		switch(b[jiance])
		{
			case 1:
				huan(&a[*y][*x],&a[y_xianzhi(*y+1)][*x]);
				*y=y_xianzhi(*y+1);
				break;
			case 2:
				huan(&a[*y][*x],&a[y_xianzhi(*y-1)][*x]);
				*y=y_xianzhi(*y-1);
				break;
			case 3:
				huan(&a[*y][*x],&a[*y][x_xianzhi(*x+1)]);
				*x=x_xianzhi(*x+1);
				break;
			case 4:
				huan(&a[*y][*x],&a[*y][x_xianzhi(*x-1)]);
				*x=x_xianzhi(*x-1);
				break;
		}
	}
}

void toushi(char a[20][40],int fen)			//投食
{
	if(fen==799)		//如果分数=799，蛇将填满整个地图，不用投食
		return;
	int shix,shiy;
	while(1)
	{
		shiy=rand()%20;
		shix=rand()%40;
		if(a[shiy][shix]==' ')
		{
			a[shiy][shix]='*';
			return;
		}
	}
}

int main()
{
	char R,E;
	int flag=1;
	system("mode con cols=40 lines=21");
	printf("\n\n\tWASD控制上下左右朝向\n\n\t按'E'开始游戏");
	E=getch();
	if(E=='e' || E=='E')	//按的不是e就退出游戏(作用见末尾)
		flag=1;
	else
		flag=0;
	while(flag)
	{
		char a[20][40],shuru='w',temp;
		int i,j,y,x,iy,ix,fen=0,ming=1,b[N]={0},dong=0;
		for(i=0;i<20;i++)
			for(j=0;j<40;j++)
				a[i][j]=' ';	//初始化地图
		a[10][10]='@';	//蛇身是'@'
		iy=10,ix=10;	//用iy和ix表示蛇头位置坐标
		
		a[12][14]='*';	//初始投喂
		
		while(ming)		//当生命值不为0时一直循环
		{
			//system("cls");	//清屏
			goto_xy(0,0);
			for(i=0;i<20;i++)	//打印地图
			{
				for(j=0;j<40;j++)
					printf("%c",a[i][j]);
				putchar('\n');
			}
			printf(" 蛇头坐标 x:%d\ty:%d\t分数:%d",ix,iy,fen);	//打印蛇头坐标和分数
			
			if(kbhit())	//kbhit()获取键盘敲击事件，如果敲了键盘，此函数返回1 
			{
				temp=getch();		//temp用来记录上次输入 
				switch(temp)
				{
					case 'W':
					case 'w': if(shuru=='s' || shuru=='S') break; else shuru=temp; break;
					case 'A':
					case 'a': if(shuru=='d' || shuru=='D') break; else shuru=temp; break;
					case 'S':
					case 's': if(shuru=='w' || shuru=='W') break; else shuru=temp; break;
					case 'D':
					case 'd': if(shuru=='a' || shuru=='A') break; else shuru=temp; break;
				}	
			}
			switch(shuru)
			{
				case 'w':
				case 'W':
					a[iy][ix]='A';	//'w'向上移动，蛇头变为'A'
					b[dong]=1;		//在b数组里存储移动数据 1上2下3左4右
					iy=y_xianzhi(iy-1);		//蛇头移动
					x=ix,y=iy;
					if(a[y][x]=='*')	//食物是'*'，吃到食物时触发
					{
						a[y][x]='@';	//食物变为蛇身
						fen+=1;			//分数+1
						huan(&a[y][x],&a[y_xianzhi(y+1)][x]);	//交换蛇身和蛇头
						toushi(a,fen);		//投食
						break;			//退出switch，等待下一个移动指令
					}
					else if(a[y][x]=='@')
					{
						ming=0;
						break;
					}
					ban(dong,fen,b,a,&y,&x);		//搬蛇身
					break;			//退出switch，等待下一个移动指令
				case 'a':
				case 'A':
					a[iy][ix]='<';	//'a'向左移动，蛇头变为'<'
					b[dong]=3;
					ix=x_xianzhi(ix-1);
					x=ix,y=iy;
					if(a[y][x]=='*')	//食物是'*'
					{
						a[y][x]='@';
						fen+=1;
						huan(&a[y][x],&a[y][x_xianzhi(x+1)]);
						toushi(a,fen);
						break;
					}
					else if(a[y][x]=='@')
					{
						ming=0;
						break;
					}
					ban(dong,fen,b,a,&y,&x);		//搬蛇身
					break;
				case 's':
				case 'S':
					a[iy][ix]='V';	//蛇头变为'V'
					b[dong]=2;
					iy=y_xianzhi(iy+1);
					x=ix,y=iy;
					if(a[y][x]=='*')	//食物是'*'
					{
						a[y][x]='@';
						fen+=1;
						huan(&a[y][x],&a[y_xianzhi(y-1)][x]);
						toushi(a,fen);
						break;
					}
					else if(a[y][x]=='@')
					{
						ming=0;
						break;
					}
					ban(dong,fen,b,a,&y,&x);		//搬蛇身
					break;
				case 'd':
				case 'D':
					a[iy][ix]='>';	//蛇头变为'>'
					b[dong]=4;
					ix=x_xianzhi(ix+1);
					x=ix,y=iy;
					if(a[y][x]=='*')	//食物是'*'
					{
						a[y][x]='@';
						fen+=1;
						huan(&a[y][x],&a[y][x_xianzhi(x-1)]);
						toushi(a,fen);
						break;
					}
					else if(a[y][x]=='@')
					{
						ming=0;
						break;
					}
					ban(dong,fen,b,a,&y,&x);		//搬蛇身
					break;
			}
			dong+=1;
			if(dong==N)		//b数组满了就根据分数（蛇身长度）清数据
			{
				for(i=0;i<fen;i++)
					b[i]=b[N-fen+i];
				dong=fen;
			}
			Sleep(100);
		}
		system("cls");
		if(fen==799)	//分数为799就是蛇铺满界面(真滴闲) 
			printf("\n你通关了！");
		else
			printf("\n你吃到了自己的身体！\n你的分数:%d",fen);
		printf("\n按R键重新开始");
		R=getch();
		if(R=='r' || R=='R')
			flag=1;
		else
			flag=0;
	}
	return 0;
}
