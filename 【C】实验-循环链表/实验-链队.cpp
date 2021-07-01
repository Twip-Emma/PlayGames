#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef char EMT;

typedef struct node //����
{
	EMT data;
	struct node *next;
} Node;

void init(Node *&L) //��ʼ������
{
	L = (Node *)malloc(sizeof(Node));
	L->next = L;
	if (L == NULL)
	{
		printf("ʧ��");
	}
	else
	{
		printf("�ɹ�");
	}
}

int empty(Node *L) //�ж������Ƿ�Ϊ�� ���г�ͻ
{
	if (L == NULL)
	{
		printf("����û�г�ʼ��");
		return 0;
	}
	if (L->next == L)
	{
		printf("����Ϊ��");
		return 0;
	}
	else
	{
		printf("���Ӳ�Ϊ��");
		return 1;
	}
}

int empty_P(Node *L) //�����ж�
{
	if (L == NULL)
	{
		printf("����û�г�ʼ��");
		return 0;
	}
	if (L->next == L)
	{
		printf("����Ϊ��");
		return 1;
	}
	else
	{
		printf("���Ӳ�Ϊ��");
		return 2;
	}
}

void enter(Node *&L, EMT a) //����
{
	Node *p;
	p = (Node *)malloc(sizeof(Node)); //�����½ڵ�
	if (p == NULL)
	{
		printf("ʧ��");
		return;
	}
	p->data = a;			//�½ڵ㣬���ڴ��Ԫ��a
	p->next = L->next;		//�ƶ��ڵ�
	L->next = p;			//�ƶ��ڵ�
	if (L->next->data == a) //�ж��Ƿ���ӳɹ�
	{
		printf("���ӳɹ�\n");
	}
	else
	{
		printf("����ʧ��\n");
	}
}

void out(Node *&L) //���Ӳ���,���Ԫ��
{
	if (!empty(L))
	{
		printf("����Ϊ�գ��޷�����");
		return;
	}
	Node *pre, *con, *p;

	for (pre = L, con = pre->next; con->next != L; con = con->next, pre = pre->next)
	//�ж��ǲ���ָ��һ��λ�ã��ǲ��ǿ��ˣ�         //�ƶ��ڵ�
	{
		p = con;
	}
	pre->next = con->next; //����
	printf("���ӣ�%c\n", p->data);
	free(L);
}

void display(Node *L) //������Ӷ��� ,������
{
	if (!empty(L))
	{
		printf("�������޷����");
	}
	Node *p, *tail;
	for (tail = L->next; tail->next != L; tail = tail->next)
	//�ж�β�ڵ��Ƿ�ָ���׽ڵ�
	{
		printf("������У�%c", tail->data);
	}
	for (; tail != L->next; tail = p)
	{
		for (p = L->next; p->next != tail; p = p->next)
		{
			printf("%c", p->data);
		}
	}
}

void freeQueue(Node *&L) //�ͷ����ӿռ�
{
	Node *pre, *con;
	int sum = 0;
	if (empty(L) == 1) //�������Ϊ�գ���һ���ڵ�Ҫ�ͷ�
	{
		free(L);
		L = NULL;
		sum += 1;
		printf("�ͷ���%d���ڵ�", sum);
		return;
	}

	for (pre = L, con = pre->next; con->next != L; pre = con, con = con->next) //�ͷŽڵ㲢����
	{
		free(pre);
		sum += 1;
	}
	free(pre);
	free(con);
	sum += 2;
	L = NULL;
	printf("�ͷ���%d���ڵ�", sum);
}

int main()
{
	Node *L;
	init(L);	  //��ʼ��
	int flag = 1; //������ʱ����
	int input, n; //������ֲ���
	int i;
	EMT a; //EMT

	while (flag)
	{
		scanf("%d", &input); //�����������еĹ���

		/*----------------------------------------------------------------------------
		
			1.�ж�ѭ�������Ƿ�Ϊ��
			2.����
			3.���Ӳ����Ԫ��
			4.��ʾ��������
			5.�ͷ�ѭ������
			6.��ʼ��ѭ������
			7.�˳�����
		
		---------------------------------------------------------------*/
		switch (input)
		{
		case 1:
			empty(L);
			break;

		case 2:
			printf("������������Ԫ�صĸ�����");
			scanf("%d", &n);
			getchar();
			for (i = 0; i < n; i++)
			{
				printf("Ԫ��%d��", i + 1);
				a = getchar();
				getchar();
				enter(L, a);
			}
			break;
		case 3:
			out(L);
			break;
		case 4:
			display(L);
			break;
		case 5:
			freeQueue(L);
			break;
		case 6:
			init(L);
			break;
		case 7:
			flag = 0;
			break;
		default:
			printf("û���������\n");
		}
	}
}
