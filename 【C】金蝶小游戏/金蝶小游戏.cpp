#include<stdio.h>
#include<windows.h>
#include<conio.h>

/*
	0=��ɫ    8=��ɫ
 ��	1=��ɫ    9=����ɫ  ʮ������  ����      
����	2=��ɫ    10=����ɫ  0xa
����	3=����ɫ    11=��ǳ��ɫ  0xb
����	4=��ɫ    12=����ɫ  0xc
����	5=��ɫ    13=����ɫ  0xd
����	6=��ɫ    14=����ɫ  0xe
����	7=��ɫ    15=����ɫ  0xf
*/

void goto_xy(int x, int y)	//��λ���λ�õ�ָ������
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//��ȡ��׼������
	COORD pos={x,y};			//����ṹ��
	SetConsoleCursorPosition(hOut,pos);	//��λ���λ��
}

void color(short x)	//�Զ��庯���ݲ����ı���ɫ
{
	if(x>=0 && x<=15)	//������0-15�ķ�Χ��ɫ
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//ֻ��һ���������ı�������ɫ
	else	//Ĭ�ϵ���ɫ��ɫ
 		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int main()
{
	system("mode con cols=40 lines=7");
	
	int i;
	int coin=10;
	int gold;
	int cursor;
	int move=0;	//0��1�� 
	int flag=1;
	int position;
	int time=10;
	char input;
	
	while(flag)
	{
		gold=rand()%29;
		cursor=0;
		move=0;
		position=0;
		
		system("cls");
		printf(	"\n\n\tcoin=%d\n\t",coin);
		system("pause");
		
		coin-=1;
		
		system("cls");
		printf( "\n\tcoin-1"
			"\n\tcoin=%d"
			"\n\tѡ���Ѷ�(1~5) :",coin);
		input=getchar();
		getchar();
		switch(input)
		{
			case '1': time=100; break;
			case '2': time=70; break;
			case '3': time=55; break;
			case '4': time=30; break;
			case '5': time=10; break;
		}
		
		system("cls");
		while(1)
		{
			if(kbhit())
			{
				input=getch();
				(move)?cursor+=1:cursor-=1;
				if(input==' ')
				{
					if((cursor>gold && cursor<gold+5) || (cursor>gold+7 && cursor<gold+12))
					{
						coin+=10;
						position=2;
						break;
					}
					else if(cursor>gold+4 && cursor<gold+8)
					{
						coin+=25;
						position=1;
						break;
					}
					else
					{
						position=3;
						break;
					}
				}
			}
			
			goto_xy(0,0);
			
			//printf("gold=%d\tcursor=%d\n",gold,cursor);
				
			for(i=0;i<cursor;i++)
				printf(" ");
			printf("V");
			for(i=0;i<39-cursor;i++)
				printf(" ");
			
			for(i=0;i<gold;i++)
				printf("#");
			color(13);
			printf("####");
			color(14);
			printf("###");
			color(13);
			printf("####");
			color(15);
			for(i=0;i<29-gold;i++)
				printf("#");
			
			for(i=0;i<cursor;i++)
				printf(" ");
			printf("A");
			for(i=0;i<39-cursor;i++)
				printf(" ");
			
			printf("\n\n coin=%d\t   ���ո��ȷ��",coin);
			
			if(move)
				cursor-=1;
			else
				cursor+=1;
			if(cursor==40)
			{
				move=1;
				cursor-=1;
			}
			else if(cursor==-1)
			{
				move=0;
				cursor+=1;
			}
			
			Sleep(time);
		}
		
		system("cls");
		switch(position)
		{
			case 1:
				printf("\n\tcoin+25");
				break;
			case 2:
				printf("\n\tcoin+10");
				break;
			case 3:
				printf("\n\tcoin+0");
				break;
		}
		printf("\n\tcoin=%d",coin);
		while(1)
		{
			printf("\n\n\tcontinue? (y/n) :");
			input=getchar();
			getchar();
			if(input=='y' || input=='Y')
			{
				flag=1;
				break;
			}
			else if(input=='n' || input=='N')
			{
				flag=0;
				break;
			}
			system("cls");
			printf("\n\n\tcoin=%d",coin);
		}
	}
	return 0;
}
