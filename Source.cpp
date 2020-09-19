#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include < string.h >
#include "windows.h"
#include <fstream>
int StrToInt(char *s)
{
	int temp = 0, i = 0, sign = 0, numchar = 0;
	if (s[i] == '-')
	{
		sign = 1;
		i++;
	}
	while (s[i] != '\0')
	{
		if (s[i] >= 0x30 && s[i] <= 0x39)
		{
			temp = temp + (s[i] & 0x0F);
			temp = temp * 10;
		}
		else
			numchar++;
		i++;
	}
	if (numchar == 0)
	{
		temp = temp / 10;
		if (sign == 1)
			temp = -temp;
		return(temp);
	}
	else
		return 0;
}
struct list
{
	int Position;
	int ModelYear;
	char *Producer;
	char *Model;
	char *BodyType;
	int Mileage;
	struct list *next;
};
struct list * init(int a, char *b, char *c, char *d, int e)
{
	struct list *lst;
	lst = new list;
	lst->Producer = new char[strlen(b)];
	lst->Model = new char[strlen(c)];
	lst->BodyType = new char[strlen(d)];
	lst->Position = 1;
	lst->ModelYear = a;
	int i;
	for (i = 0; i < strlen(b); i++)
		lst->Producer[i] = b[i];
	lst->Producer[i] = '\0';
	for (i = 0; i < strlen(c); i++)
		lst->Model[i] = c[i];
	lst->Model[i] = '\0';
	for (i = 0; i < strlen(d); i++)
		lst->BodyType[i] = d[i];
	lst->BodyType[i] = '\0';
	lst->Mileage = e;
	lst->next = NULL;
	return(lst);
}
void ListPrint(list *head)
{
	struct list *tmp;
	tmp = (struct list*)malloc(sizeof(struct list));
	tmp = head;
	printf("Model Year / Producer / Model / Body Type / Mileage\n");
	do {
		printf("%d) %d ", tmp->Position, tmp->ModelYear);
		for (int i = 0; i < strlen(tmp->Producer); i++)
			printf("%c", tmp->Producer[i]);
		printf(" ");
		for (int i = 0; i < strlen(tmp->Model); i++)
			printf("%c", tmp->Model[i]);
		printf(" ");
		for (int i = 0; i < strlen(tmp->BodyType); i++)
			printf("%c", tmp->BodyType[i]);
		printf(" %d\n", tmp->Mileage);
		tmp = tmp->next;
	} while (tmp != NULL);
}
void AddElement(list *head, int a, char *b, char *c, char *d, int e)
{
	struct list *tmp;
	tmp = (struct list*)malloc(sizeof(struct list));
	tmp = head;
	struct list *lst;
	lst = (struct list*)malloc(sizeof(struct list));
	lst->Producer = new char[strlen(b)];
	lst->Model = new char[strlen(c)];
	lst->BodyType = new char[strlen(d)];
	lst->ModelYear = a;
	int i;
	for (i = 0; i < strlen(b); i++)
		lst->Producer[i] = b[i];
	lst->Producer[i] = '\0';
	for (i = 0; i < strlen(c); i++)
		lst->Model[i] = c[i];
	lst->Model[i] = '\0';
	for (i = 0; i < strlen(d); i++)
		lst->BodyType[i] = d[i];
	lst->BodyType[i] = '\0';
	lst->Mileage = e;
	lst->next = NULL;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = lst;
	lst->Position = tmp->Position + 1;
}
int PrintSelectedCar(list *head, int selectedcar)
{
	struct list *tmp;
	tmp = (struct list*)malloc(sizeof(struct list));
	tmp = head;
	while (tmp->Position != selectedcar)
	{
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break;
	}
	if (tmp->Position == selectedcar)
	{
		system("cls");
		printf("%d) %d ", tmp->Position, tmp->ModelYear);
		for (int i = 0; i < strlen(tmp->Producer); i++)
			printf("%c", tmp->Producer[i]);
		printf(" ");
		for (int i = 0; i < strlen(tmp->Model); i++)
			printf("%c", tmp->Model[i]);
		printf(" ");
		for (int i = 0; i < strlen(tmp->BodyType); i++)
			printf("%c", tmp->BodyType[i]);
		printf(" %d\n", tmp->Mileage);
		return 1;
	}
	else
		return 0;
}
void EditInform(list *head, int selectedcar, int selectededit)
{
	char *b = new char[10];
	struct list *tmp;
	tmp = (struct list*)malloc(sizeof(struct list));
	tmp = head;
	while (tmp->Position != selectedcar)
		tmp = tmp->next;
	if (selectededit == 1)
	{
		printf("Do you want to change information from %d to ", tmp->ModelYear);
		scanf("%d", &tmp->ModelYear);
	}
	if (selectededit == 2)
	{
		printf("Do you want to change information from %s to ", tmp->Producer);
		scanf("%s", b);
		tmp->Producer = b;
	}
	if (selectededit == 3)
	{
		printf("Do you want to change information from %s to ", tmp->Model);
		scanf("%s", b);
		tmp->Model = b;
	}
	if (selectededit == 4)
	{
		printf("Do you want to change information from %s to ", tmp->BodyType);
		scanf("%s", b);
		tmp->BodyType = b;
	}
	if (selectededit == 5)
	{
		printf("Do you want to change information from %d to ", tmp->Mileage);
		scanf("%d", &tmp->Mileage);
	}
	printf("\nAll done\nPress 'Enter' to exit into main menu");
	while (GetKeyState(0x0D) == 0)
	{
	}
}
void WriteFile(FILE *Queue, list *head)
{
	struct list *tmp;
	tmp = (struct list*)malloc(sizeof(struct list));
	tmp = head;
	do {
		fprintf(Queue, "%d) %d ", tmp->Position, tmp->ModelYear);
		for (int i = 0; i < strlen(tmp->Producer); i++)
			fprintf(Queue, "%c", tmp->Producer[i]);
		fprintf(Queue, " ");
		for (int i = 0; i < strlen(tmp->Model); i++)
			fprintf(Queue, "%c", tmp->Model[i]);
		fprintf(Queue, " ");
		for (int i = 0; i < strlen(tmp->BodyType); i++)
			fprintf(Queue, "%c", tmp->BodyType[i]);
		fprintf(Queue, " %d\n", tmp->Mileage);
		tmp = tmp->next;
	} while (tmp != NULL);
}
struct list* DeleteElement(list* head, int position)
{
	struct list *tmp,*delectedelement,*tmp1;
	tmp1=tmp=delectedelement = (struct list*)malloc(sizeof(struct list));
	tmp = head;
	if (position != 1)
	{
		while ((tmp->next)->Position != position)
			tmp = tmp->next;
		tmp->next = tmp->next->next;
		delectedelement = tmp->next;
		tmp = tmp->next;
	}
	else
	{
		head = head->next;
		delectedelement = tmp;
	}
	while (tmp != NULL)
	{
		tmp->Position--;
		tmp = tmp->next;
	}
	return head;
}
int main()
{
	FILE *Queue;
	Queue = fopen("queue1.txt", "a+");
	int counter = 0, count = 0;
	int a; char *b = new char[40]; char *c = new char[40]; char *d = new char[40]; int e;
	struct list *head;
	head = (struct list*)malloc(sizeof(struct list));
	char b1 = fgetc(Queue);
	if (b1 == EOF || b1 == '\n')
	{
		head = init(2016, "BMW", "X5", "SUV", 120548);
		AddElement(head, 1986, "VAZ", "2131", "SUV", 256847);
		AddElement(head, 2010, "Volkswagen", "Polo", "Sedan", 54032);
		WriteFile(Queue, head);
	}
	else
	{
		b1=fgetc(Queue);
		fscanf(Queue, " %d %s %s %s %d", &a, b, c, d, &e);
		head = init(a, b, c, d, e);
		fscanf(Queue, "\n");
		while (fgetc(Queue) != EOF)
		{
			fgetc(Queue);
			fscanf(Queue, "%d %s %s %s %d", &a, b, c, d, &e);
			AddElement(head, a, b, c, d, e);
			fscanf(Queue, "\n");
		}
	}
	ListPrint(head);
	char *str=new char [40];
	while (counter != 3)
	{
		bool PassButton = false;
		system("cls");
		printf("Main menu\nWhat would you like to do?\n1)View the directory or select auto\n2)Add the auto\n3)Exit\n");
		scanf("%s", str);
		counter = StrToInt(str);
		while (counter < 1 || counter > 3)
		{
			printf("Incorrect input, please try again!\n");
			scanf("%s", str);
			counter = StrToInt(str);
		}
		if (counter == 1)
		{
			int selectedcar = 0;
			system("cls");
			ListPrint(head);
			printf("\n1)Select auto\n2)Exit into main menu\n");
			scanf("%s", str);
			count = StrToInt(str);
			while (count < 1 || count > 2)
			{
				printf("Incorrect input, please try again!\n");
				scanf("%s", str);
				count = StrToInt(str);
			}
			if (count == 1)
			{
				printf("Which car would you like to choose?\n");
				scanf("%s", str);
				selectedcar = StrToInt(str);
				while (PrintSelectedCar(head, selectedcar) != 1)
				{
					printf("Incorrect input, please try again!\n");
					scanf("%s", str);
					selectedcar = StrToInt(str);
				}
				printf("\nWhat would you like to do?\n1)Delete this auto\n2)Edit information\n3)Exit into main menu\n");
				scanf("%d", &count);
				if (count == 1)
				{
					head=DeleteElement(head, selectedcar);
					Queue = fopen("queue1.txt", "wb");
					WriteFile(Queue, head);
				}
				if (count == 2)
				{
					int selectededit;
					printf("What would you like to change?\n1)Model year\n2)Producer\n3)Model\n4)Body type\n5)Milleage\n");
					scanf("%d", &selectededit);
					EditInform(head, selectedcar, selectededit);
					Queue = fopen("queue1.txt", "wb");
					WriteFile(Queue, head);
				}
				if (count == 3)
					continue;
			}
			if (count == 2)
				continue;
			else
			{
				while (count < 1 || count > 2)
				{
					printf("Incorrect input, please try again!\n");
					scanf("%s", str);
					count = StrToInt(str);
				}
			}
		}
		if (counter == 2)
		{
			system("cls");
			printf("Please, enter a Model Year\n");
			scanf("%d", &a);
			printf("Please, enter a Producer\n");
			scanf("%s", b);
			printf("Please, enter a Model\n");
			scanf("%s", c);
			printf("Please, enter a Body Type\n");
			scanf("%s", d);
			printf("Please, enter a Mileage (km)\n");
			scanf("%d", &e);
			AddElement(head, a, b, c, d, e);
			Queue = fopen("queue1.txt", "wb");
			WriteFile(Queue, head);
			printf("\nAll done\nPress 'Enter' to exit into main menu");
			while (PassButton == false)
			{
				if (GetKeyState(0x0D) == 1)
					PassButton = true;
			}
		}
	}
}