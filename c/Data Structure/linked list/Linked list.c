#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef int Status;
typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;



void CreatList_L(LinkList L, int n)
{
	
	L->next = NULL;
	int i;
	LinkList q = L;
	for (i = 0;i < n;i++)
	{
		printf("请输入第%d个数据\n",i+1);
		LinkList p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &p->data);
		p->next = NULL;
		q->next = p;
		q = p;
		
	}
}

void PrintList_L(LinkList L, int n)
{
	LinkList p = L->next;
	int i = 0;
	printf("链表中的数据为：\n");
	while (p != NULL && i < n)
	{
		printf("%d,", p->data);
		p = p->next;
		i++;
	}
	printf("\n\n");

}

void MergeList_L(LinkList La, LinkList Lb)
{
	LinkList pa,  pb,  pc;
	pa = La->next;
	pb = Lb->next;
	pc = La;
	while (pa != NULL && pb != NULL)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	if (pa == NULL)
		pc->next = pb;
	else pc->next = pa;
	free(Lb);
}

int main()
{
	int n1,n2;
	LinkList L1 = (LinkList)malloc(sizeof(LNode));
	LinkList L2 = (LinkList)malloc(sizeof(LNode));
	

	printf("请输入链表1的长度\n");
	scanf("%d",&n1);
	CreatList_L(L1, n1);
	PrintList_L(L1, n1);

	printf("请输入链表2的长度\n");
	scanf("%d", &n2);
	CreatList_L(L2, n2);
	PrintList_L(L2, n2);


	MergeList_L(L1, L2);
	printf("合并后的链表为：\n");
	PrintList_L(L1, n1+n2);
	return 0;
}