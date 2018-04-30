#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//-----------------------------------
int Menu_show(void);
void Add_ab(int *count1, int *count2);
void Del_ab(int *count1, int *count2);
void List_ab(int count);
void Search(int *count);
void Find_name(int *count);
void Find_surname(int *count);
void Find_number(int *count);
//-----------------------------------
#define ADD	1	//добавить абонента в список
#define LIST	2	//вывести список абонентов
#define DEL	3	//удалить абонента из списка
#define SEARCH	4	//поиск абонента в списке
#define QUIT	5	//выход


#define NAME	1
#define SURNAME	2
#define NUMBER	3

struct phonebook
{
	unsigned char name[30];
	unsigned char surname[30];
	unsigned char number[30];
};

struct phonebook Abonent[30];



//-----------------------------------
int main (void)
{
	int result = 0;
	int count_list = 0;
	int count_ab = 0;

	while(1)
	{
		result = Menu_show();
		switch (result)
		{
			case ADD:
				Add_ab(&count_ab, &count_list);
				break;
			case LIST:
				List_ab(count_list);
				break;
			case DEL:
				Del_ab(&count_ab, &count_list);
				break;
			case SEARCH:
				Search(&count_list);
				break;
			case QUIT:
				return(0);
			default:
				printf("Error: Invalid menu item entered!\r\n");
				break;
		}
	}
	return(1);

}
//---------------------------------------------
int Menu_show(void)
{
	int key = 0;
	unsigned char tmp[10];

	printf("\t=====Menu====\r\n");
	printf("Add subscribers:\t\"1\" \r\n");
	printf("List subscribers:\t\"2\" \r\n");
	printf("Delete subscribers:\t\"3\" \r\n");
	printf("Search subscribers:\t\"4\" \r\n");
	printf("Quit:\t\t\t\"5\" \r\n");
	printf("Please, select the menu item: ");

//	do
//	{
//		key = getchar();
//	}
//	while ( (key == EOF) || (key == '\n') );


	while(1)
	{
		fgets(tmp,sizeof(tmp),stdin);

		if (*tmp != EOF)
		{
			for (int i = 0; i < sizeof(tmp); i++)
			if (tmp[i] == '\n')
				tmp[i] = '\0';
			key = atoi(tmp);
			break;
		}
	}

	return(key);
}
//-----------------------------------------------
void Add_ab(int *count1, int *count2)
{

	printf("Please, enter the name of the subscriber: ");

	while(1)
	{
		fgets(Abonent[*count1].name, sizeof(Abonent[*count1].name), stdin);
		if (*Abonent[*count1].name != EOF)
		{
			for (int i = 0; i < sizeof(Abonent[*count1].name); i++)
			if (Abonent[*count1].name[i] == '\n')
				Abonent[*count1].name[i] = '\0';
			break;
		}
	}

	printf("Please, enter the surname of the subscriber: ");

	while(1)
	{
		fgets(Abonent[*count1].surname, sizeof(Abonent[*count1].surname), stdin);
		if (*Abonent[*count1].surname != EOF)
		{
			for (int i = 0; i < sizeof(Abonent[*count1].surname); i++)
			if (Abonent[*count1].surname[i] == '\n')
				Abonent[*count1].surname[i] = '\0';
			break;
		}
	}

	printf("Please, enter the phone number of the subscriber: ");

	while(1)
	{
		fgets(Abonent[*count1].number, sizeof(Abonent[*count1].number), stdin);
		if (*Abonent[*count1].surname != EOF)
		{
			for (int i = 0; i < sizeof(Abonent[*count1].number); i++)
			if (Abonent[*count1].number[i] == '\n')
				Abonent[*count1].number[i] = '\0';
			break;
		}
	}

	if ((*Abonent[*count1].name != '\0')||(*Abonent[*count1].surname != '\0')||(*Abonent[*count1].number != '\0'))
	{
		if ((*count2) < sizeof(Abonent)/sizeof(Abonent[0]))
			(*count2)++;
		(*count1)++;
		if((*count1) >= sizeof(Abonent)/sizeof(Abonent[0]))
			(*count1) = 0;
	}
	return;

}
//-----------------------------------------------
void Del_ab(int *count1, int *count2)
{
	int sub_num;
	unsigned char tmp[10];

	if (*count2)//если в списке есть абоненты
	{
		printf("Please, enter the subscriber's number to delete: ");

		while(1)
		{
			fgets(tmp,sizeof(tmp),stdin);
			if (*tmp != EOF)
			{
				for (int i = 0; i < sizeof(tmp); i++)
				if (tmp[i] == '\n')
					tmp[i] = '\0';
				sub_num = atoi(tmp);
				break;
			}
		}

		if((sub_num > 0)&&(sub_num <= (*count2)))
		{
			sub_num--;
			memset(Abonent[sub_num].name, '\0', sizeof(Abonent[sub_num].name));
			memset(Abonent[sub_num].surname, '\0', sizeof(Abonent[sub_num].surname));
			memset(Abonent[sub_num].number, '\0', sizeof(Abonent[sub_num].number));
			for (int i = sub_num; i < *count2; i++)
			{
				memcpy(Abonent[i].name, Abonent[i + 1].name, sizeof(Abonent[i + 1].name));
				memcpy(Abonent[i].surname, Abonent[i + 1].surname, sizeof(Abonent[i + 1].surname));
				memcpy(Abonent[i].number, Abonent[i + 1].number, sizeof(Abonent[i + 1].number));
			}
			(*count1)--;
			(*count2)--;
		}
		else
		{
			printf("Error: Incorrect subscriber's number entered!\r\n");
		}
	}
	else
	{
		printf("There are no subscribers in the list to delete!\r\n");
	}

	return;
}
//-----------------------------------------------
void List_ab(int count)
{
	if(count)//если в списке есть абоненты
	{
		for(int i = 0; i < count; i++)
		{
			printf("%d \t Name: %s \t\t\t Surname: %s \t\t\t Phone number: %s \r\n", i+1, Abonent[i].name,\
				 Abonent[i].surname, Abonent[i].number);
		}
	}
	else
	{
		printf("There are no subscribers to list!\r\n");
	}
	return;
}
//-----------------------------------------------
void Search(int *count)
{
	int parametr = 0;
	char tmp[10];

	if(count)
	{
		printf("\r\nPlease, enter the parametr for search: \r\n");
		printf("Name:\t\t\"1\" \r\n");
		printf("Surname:\t\"2\" \r\n");
		printf("Phone number:\t\"3\" \r\n");

		while(1)
		{
			fgets(tmp,sizeof(tmp),stdin);
			if (*tmp != EOF)
			{
				for (int i = 0; i < sizeof(tmp); i++)
				if (tmp[i] == '\n')
					tmp[i] = '\0';
				parametr = atoi(tmp);
				break;
			}
		}

		switch (parametr)
		{
			case NAME:
				Find_name(&(*count));
				break;
			case SURNAME:
				Find_surname(&(*count));
				break;
			case NUMBER:
				Find_number(&(*count));
				break;
			default:
				printf("Error: Invalid parametr entered!\r\n");
				break;
		}

	}
	else
	{
		printf("There are no subscribers in the list for search!\r\n");
	}
	return;
}
//---------------------------------------------------------
void Find_name(int *count)
{
	char Name[30] = {};
	char flag = 0;
	int size = 0;

	printf("\r\nPlease, enter the name for search: ");


	while(1)
	{
		fgets(Name,sizeof(Name),stdin);

		if (*Name != EOF)
		{
			for (int i = 0; i < sizeof(Name); i++)

			if (Name[i] == '\n')
			{
				Name[i] = '\0';
				size = i;
			}
			break;
		}
	}


	for (int i = 0; i <= *count; i++)
	{

		if ((memcmp(Abonent[i].name, Name, sizeof(Name))) == 0)
		{
			flag = 1;
			printf("%d \t Name: %s \t\t\t Surname: %s \t\t\t Phone number: %s \r\n", i+1, Abonent[i].name,\
				 Abonent[i].surname, Abonent[i].number);
		}
	}
	if (!flag)
	{
		printf("There are no subscribers with the set name! \r\n");
	}
	return;

}
//---------------------------------------------------------

void Find_surname(int *count)
{
	char Surname[30] = {};
	char flag = 0;
	int size = 0;

	printf("\r\nPlease, enter the surname for search: ");


	while(1)
	{
		fgets(Surname,sizeof(Surname),stdin);

		if (*Surname != EOF)
		{
			for (int i = 0; i < sizeof(Surname); i++)

			if (Surname[i] == '\n')
			{
				Surname[i] = '\0';
				size = i;
			}
			break;
		}
	}


	for (int i = 0; i <= *count; i++)
	{

		if ((memcmp(Abonent[i].surname, Surname, sizeof(Surname))) == 0)
		{
			flag = 1;
			printf("%d \t Name: %s \t\t\t Surname: %s \t\t\t Phone number: %s \r\n", i+1, Abonent[i].name,\
				 Abonent[i].surname, Abonent[i].number);
		}
	}
	if (!flag)
	{
		printf("There are no subscribers with the set surname! \r\n");
	}
	return;

}
//---------------------------------------------------------
void Find_number(int *count)
{
	char Number[30] = {};
	char flag = 0;
	int size = 0;

	printf("\r\nPlease, enter the number for search: ");


	while(1)
	{
		fgets(Number,sizeof(Number),stdin);

		if (*Number != EOF)
		{
			for (int i = 0; i < sizeof(Number); i++)

			if (Number[i] == '\n')
			{
				Number[i] = '\0';
				size = i;
			}
			break;
		}
	}


	for (int i = 0; i <= *count; i++)
	{

		if ((memcmp(Abonent[i].number, Number, sizeof(Number))) == 0)
		{
			flag = 1;
			printf("%d \t Name: %s \t\t\t Surname: %s \t\t\t Phone number: %s \r\n", i+1, Abonent[i].name,\
				 Abonent[i].surname, Abonent[i].number);
		}
	}
	if (!flag)
	{
		printf("There are no subscribers with the set number! \r\n");
	}
	return;

}
//---------------------------------------------------------
