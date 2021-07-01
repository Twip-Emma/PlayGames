
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>


void color(short x)//����������ɫ �̶�д�� 
{
	if(x>=0 && x<=15)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}



int map[8][8] =//����ͼ 
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


int map_File[8][8] =//���õ�ͼ�ı��� 
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

0          �յ�
1            ǽ�� ��
2            ����
2+6=8            ������Ŀ�ĵ�����
5+6=11            ����Ŀ�ĵ�����
5            ��
6            Ŀ�ĵ�

�����Ѩ�

----------------------------------------------------------*/
void ChongZhi_Map()//���õ�ͼ 
{
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			map[i][j] = map_File[i][j]; 
		}
	}
}

void Hua_Map()//����ͼ 
{
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			switch (map[i][j])//������飬��ÿ��Ԫ�ص�ֵ��Ӧ��ͼ��������� 
			{
			case 0:printf("  ");break;
			case 1:printf("��");break;
			case 2:printf("��");break;
			case 8:color(2);printf("��");color(7);break;
			case 11:case 5:printf("��");break;
			case 6:printf("��");break;
			}
		}
		printf("\n");//ÿ8��ͼ����һ�� 
	}
}

void Ding_Wei()//��λ�Լ����̽��� 
{
	int i, j;
	for (i = 0;i < 8;i++)//�����ͼ���ҵ�С�˵�λ�� 
	{
		for (j = 0;j < 8;j++)
		{
			if (map[i][j] == 11 || map[i][j] == 5)
			{
				break;//�ҵ���С�˵�λ������ѭ�� 
			}
		}
		if (map[i][j] == 11 || map[i][j] == 5)
		{
			break;//�ҵ���С�˵�λ������ѭ�� 
		}
	}

	char key = _getch();//��ȡ�İ��µļ����ַ��ŵ��ַ��ͱ���char���� 
	switch (key)//����С�� 
	{
	case 'w':case 'W':
		if (map[i - 1][j] == 0 || map[i - 1][j] == 6)//ǰ�������ǿյػ���Ŀ�ĵ� 
		{
			map[i][j] -= 5;map[i - 1][j] += 5;
		}
		else if (map[i - 1][j] == 2 || map[i - 1][j] == 8)//ǰ������������ 
		{
			if (map[i - 2][j] == 0 || map[i - 2][j] == 6)//���ӵ�ǰ���ǿյػ���Ŀ�ĵ� 
			{
				map[i][j] -= 5;
				map[i - 1][j] += 5;
				map[i - 1][j] -= 2;
				map[i - 2][j] += 2;
			}
		}

		break;

	case 's':case 'S':
		if (map[i + 1][j] == 0 || map[i + 1][j] == 6)//ǰ�������ǿյػ���Ŀ�ĵ� 
		{
			map[i][j] -= 5;map[i + 1][j] += 5;
		}
		else if (map[i + 1][j] == 2 || map[i + 1][j] == 8)//ǰ������������ 
		{
			if (map[i + 2][j] == 0 || map[i + 2][j] == 6)//���ӵ�ǰ���ǿյػ���Ŀ�ĵ� 
			{
				map[i][j] -= 5;
				map[i + 1][j] += 5;
				map[i + 1][j] -= 2;
				map[i + 2][j] += 2;
			}
		}
		break;

	case 'a':case 'A':
		if (map[i][j - 1] == 0 || map[i][j - 1] == 6)//ǰ�������ǿյػ���Ŀ�ĵ� 
		{
			map[i][j] -= 5;map[i][j - 1] += 5;
		}
		else if (map[i][j - 1] == 2 || map[i][j - 1] == 8)//ǰ������������ 
		{
			if (map[i][j - 2] == 0 || map[i][j - 2] == 6)//���ӵ�ǰ���ǿյػ���Ŀ�ĵ� 
			{
				map[i][j] -= 5;
				map[i][j - 1] += 5;
				map[i][j - 1] -= 2;
				map[i][j - 2] += 2;
			}
		}
		break;

	case 'd':case 'D':
		if (map[i][j + 1] == 0 || map[i][j + 1] == 6)//ǰ�������ǿյػ���Ŀ�ĵ� 
		{
			map[i][j + 1] += 5;map[i][j] -= 5;
		}
		else if (map[i][j + 1] == 2 || map[i][j + 1] == 8)//ǰ������������ 
		{
			if (map[i][j + 2] == 0 || map[i][j + 2] == 6)//���ӵ�ǰ���ǿյػ���Ŀ�ĵ� 
			{
				map[i][j] -= 5;
				map[i][j + 1] += 5;
				map[i][j + 1] -= 2;
				map[i][j + 2] += 2;
			}
		}
		break;
	case 'R':case 'r': {ChongZhi_Map();break;}//��R���õ�ͼ 
	}
}

int Pass_PanDuan()//�жϴ�ʱ��ͼ��Ҫ���ٸ�Ŀ�ĵ�����û������ 
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
	return (z);//����Ŀ�ĵ�����û�����ӵĸ��� 
}

void goto_xy(int x, int y)	//ˢ����Ļ���̶�д�� 
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//��ȡ��׼������ 
	COORD pos={x,y};			//����ṹ�� 
	SetConsoleCursorPosition(hOut,pos);	//��λ���λ�� 
}


int main()
{
	system("mode con cols=30 lines=10");//�Զ��崰�ڴ�С 
	int flag = 1;//�趨һ��һ��������Ϸ�ı��� 

	while (flag)//��flag��Ϊ0ʱһֱѭ�� 
	{
		Hua_Map();//��ʾ��ͼ 
		color(4);printf("��R����");color(7);
		Ding_Wei();//���� 
		//system("cls");//������Ļ 
		goto_xy(0,0);
		if (Pass_PanDuan() == 0)//��Ŀ�ĵ�����û�����ӵĸ���Ϊ0ʱ����IF 
		{
			system("cls");
			printf("�������\n");
			color(4);printf("��R���ã���O������Ϸ");color(7);
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



