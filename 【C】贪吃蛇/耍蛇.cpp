#include<stdio.h>
#include<stdlib.h>
#include<conio.h>			 
#include<windows.h>

#define N 1000

void goto_xy(int x, int y)	//��λ���λ�õ�ָ������
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//��ȡ��׼������ 
	COORD pos={x,y};			//����ṹ�� 
	SetConsoleCursorPosition(hOut,pos);	//��λ���λ�� 
}

int x_xianzhi(int sx)		//����x������ƶ���Χ��0~39��
{
	if(sx==-1)
		return 39;
	else if(sx==40)
		return 0;
	return sx;
}

int y_xianzhi(int sy)		//����y������ƶ���Χ��0~19��
{
	if(sy==-1)
		return 19;
	else if(sy==20)
		return 0;
	return sy;
}

void huan(char *a,char *b)		//����*a��*bָ����ַ���������ᵽ��һ��λ�ã�
{
	char temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void ban(int dong,int fen,int b[N],char a[20][40],int *y,int *x)	//����b��������ƶ����ݰ�����ᵽ��һ��λ��
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

void toushi(char a[20][40],int fen)			//Ͷʳ
{
	if(fen==799)		//�������=799���߽�����������ͼ������Ͷʳ
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
	printf("\n\n\tWASD�����������ҳ���\n\n\t��'E'��ʼ��Ϸ");
	E=getch();
	if(E=='e' || E=='E')	//���Ĳ���e���˳���Ϸ(���ü�ĩβ)
		flag=1;
	else
		flag=0;
	while(flag)
	{
		char a[20][40],shuru='w',temp;
		int i,j,y,x,iy,ix,fen=0,ming=1,b[N]={0},dong=0;
		for(i=0;i<20;i++)
			for(j=0;j<40;j++)
				a[i][j]=' ';	//��ʼ����ͼ
		a[10][10]='@';	//������'@'
		iy=10,ix=10;	//��iy��ix��ʾ��ͷλ������
		
		a[12][14]='*';	//��ʼͶι
		
		while(ming)		//������ֵ��Ϊ0ʱһֱѭ��
		{
			//system("cls");	//����
			goto_xy(0,0);
			for(i=0;i<20;i++)	//��ӡ��ͼ
			{
				for(j=0;j<40;j++)
					printf("%c",a[i][j]);
				putchar('\n');
			}
			printf(" ��ͷ���� x:%d\ty:%d\t����:%d",ix,iy,fen);	//��ӡ��ͷ����ͷ���
			
			if(kbhit())	//kbhit()��ȡ�����û��¼���������˼��̣��˺�������1 
			{
				temp=getch();		//temp������¼�ϴ����� 
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
					a[iy][ix]='A';	//'w'�����ƶ�����ͷ��Ϊ'A'
					b[dong]=1;		//��b������洢�ƶ����� 1��2��3��4��
					iy=y_xianzhi(iy-1);		//��ͷ�ƶ�
					x=ix,y=iy;
					if(a[y][x]=='*')	//ʳ����'*'���Ե�ʳ��ʱ����
					{
						a[y][x]='@';	//ʳ���Ϊ����
						fen+=1;			//����+1
						huan(&a[y][x],&a[y_xianzhi(y+1)][x]);	//�����������ͷ
						toushi(a,fen);		//Ͷʳ
						break;			//�˳�switch���ȴ���һ���ƶ�ָ��
					}
					else if(a[y][x]=='@')
					{
						ming=0;
						break;
					}
					ban(dong,fen,b,a,&y,&x);		//������
					break;			//�˳�switch���ȴ���һ���ƶ�ָ��
				case 'a':
				case 'A':
					a[iy][ix]='<';	//'a'�����ƶ�����ͷ��Ϊ'<'
					b[dong]=3;
					ix=x_xianzhi(ix-1);
					x=ix,y=iy;
					if(a[y][x]=='*')	//ʳ����'*'
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
					ban(dong,fen,b,a,&y,&x);		//������
					break;
				case 's':
				case 'S':
					a[iy][ix]='V';	//��ͷ��Ϊ'V'
					b[dong]=2;
					iy=y_xianzhi(iy+1);
					x=ix,y=iy;
					if(a[y][x]=='*')	//ʳ����'*'
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
					ban(dong,fen,b,a,&y,&x);		//������
					break;
				case 'd':
				case 'D':
					a[iy][ix]='>';	//��ͷ��Ϊ'>'
					b[dong]=4;
					ix=x_xianzhi(ix+1);
					x=ix,y=iy;
					if(a[y][x]=='*')	//ʳ����'*'
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
					ban(dong,fen,b,a,&y,&x);		//������
					break;
			}
			dong+=1;
			if(dong==N)		//b�������˾͸��ݷ����������ȣ�������
			{
				for(i=0;i<fen;i++)
					b[i]=b[N-fen+i];
				dong=fen;
			}
			Sleep(100);
		}
		system("cls");
		if(fen==799)	//����Ϊ799��������������(�����) 
			printf("\n��ͨ���ˣ�");
		else
			printf("\n��Ե����Լ������壡\n��ķ���:%d",fen);
		printf("\n��R�����¿�ʼ");
		R=getch();
		if(R=='r' || R=='R')
			flag=1;
		else
			flag=0;
	}
	return 0;
}
