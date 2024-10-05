#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define True	1
#define False	0

typedef char Data;

typedef struct _node
{
	Data data;
	struct _node* next;
	struct _node* prev;
}Node;

typedef struct _dblinkedlist
{
	Node* head;
	Node* tail;
	Node* cur;
	int numofdata;
}DbLinkedList;

typedef DbLinkedList List;

void ListInit(List* plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->tail = (Node*)malloc(sizeof(Node));

	plist->head->prev = NULL;
	plist->head->next = plist->tail;

	plist->tail->next = NULL;
	plist->tail->prev = plist->head;

	plist->numofdata = 0;
}

void LInsert(List* plist, Data data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;

	newnode->next = plist->tail;
	newnode->prev = plist->tail->prev;

	plist->tail->prev->next = newnode;
	plist->tail->prev = newnode;

	plist->numofdata++;
}

void LInsert_mid(List* plist, Data data) // cur 노드 뒤에로 연결하기 
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;

	newnode->next = plist->cur;
	newnode->prev = plist->cur->prev;

	plist->cur->prev->next = newnode;
	plist->cur->prev = newnode;

	plist->numofdata++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->head->next == plist->tail)
		return False;

	plist->cur = plist->head->next;
	*pdata = plist->cur->data;

	return True;
}

int LNext(List* plist, Data* pdata)
{
	if (plist->cur->next == plist->tail)
		return False;

	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;

	return True;
}

Data LRemove(List* plist)
{
	Node* rpos = plist->cur;
	Data rdata = plist->cur->data;

	plist->cur->prev->next = plist->cur->next;
	plist->cur->next->prev = plist->cur->prev;
	plist->cur = plist->cur->prev;

	free(rpos);
	plist->numofdata--;

	return rdata;
}

int LCount(List* plist)
{
	return plist->numofdata;
}


int main()
{
	List list;
	char cal;
	int count, n; // count : 연산 횟수, n : 순위 
	Data data;

	scanf("%d", &count);
	getchar();

	ListInit(&list);
	
	while (count > 0)
	{
		scanf("%c", &cal);
		getchar();
		switch (cal)
		{
		case'A': // add
		{
			scanf("%d %c", &n, &data);
			getchar();
			
			Data tmp = data;
			
			if (LCount(&list) + 1 < n || n < 1)
			{
				printf("invalid position\n");
				break;
			}
			if (LCount(&list) + 1 == n)
			{
				LInsert(&list, data);
			}
			else 
			{
				if (LFirst(&list, &data))
				{
					if (n == 1)
					{
						LInsert_mid(&list, tmp);
						break;
					}
					n--;
					while (n != 0 && LNext(&list, &data))
					{
						n--;
					}
					LInsert_mid(&list, tmp);
				}
			}
			break;
		}
		case'D': // delete
		{
			scanf("%d", &n);
			getchar();
			if (LCount(&list) < n || n < 1)
			{
				printf("invalid position\n");
				break;
			}
			if (LFirst(&list, &data))
			{
				if (n == 1)
				{
					LRemove(&list);
					break;
				}
				n--;
				while (n != 0 && LNext(&list, &data))
				{
					n--;
				}
				LRemove(&list);
			}
			break;
		}
		case 'G': // get
		{
			scanf("%d", &n);
			getchar();
			if (LCount(&list) < n || n < 1)
			{
				printf("invalid position\n");
				break;
			}
			if (LFirst(&list, &data))
			{
				if (n == 1)
				{
					printf("%c\n", data);
					break;
				}
				n--;
				while (n != 0 && LNext(&list, &data))
				{
					n--;
				}
				printf("%c\n", data);
			}
			break;
		}
		case 'P': // print
		{
			if (LFirst(&list, &data))
			{
				printf("%c", data);
				while (LNext(&list, &data))
				{
					printf("%c", data);
				}
			}
			printf("\n");
			break;
		}
		}
		count--;
	}
	return 0;
}
