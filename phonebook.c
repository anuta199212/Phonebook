#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//-----------------------------------
int Menu_show(void);
void Add_ab(int *number_in_list, int *count_abonents);
void Del_ab(int *number_in_list, int *count_abonents);
void List_ab(int count_abonents);
void Search_abonent(int *count_abonents);
int Read_inputstr(int input_string_parametr, int *number_in_list);
void Find_value(int input_parametr, int *count_abonents);
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
void main (void)
{
	int result = 0;
	int count_list = 0;//количество абонентов
	int count_ab = 0; //номер абонента в списке

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
				Search_abonent(&count_list);
				break;
			case QUIT:
				return;
			default:
				printf("Error: Invalid menu item entered!\r\n");
				break;
		}
	}
	return;
}
//---------------------------------------------
int Menu_show(void)
{
	int key = 0;
	int err_symb = 0;
	unsigned char tmp[10];

	printf("\t=====Menu====\r\n");
	printf("Add subscribers:\t\"1\" \r\n");
	printf("List subscribers:\t\"2\" \r\n");
	printf("Delete subscribers:\t\"3\" \r\n");
	printf("Search subscribers:\t\"4\" \r\n");
	printf("Quit:\t\t\t\"5\" \r\n");
 	printf("Please, select the menu item: ");

	while(1)
	{
		fgets(tmp,sizeof(tmp),stdin);

		if (*tmp != EOF)
		{
			if ((tmp[1] == EOF)|| (tmp[1] == '\n'))
			{
				key = atoi(tmp);
			}
			else
			{
				do
				{
					err_symb = getchar();
				}
				while ((err_symb == EOF)||(err_symb != '\n'));
				key = 0;
			}
			break;
		}
	}
	return(key);
}
//-----------------------------------------------
void Add_ab(int *number_in_list, int *count_abonents)
{
	int result = 0;

	do
	{
		printf("Please, enter the name of the subscriber: ");
		result = Read_inputstr(NAME, number_in_list);
	}
	while (!result);
	result = 0;

	do
	{
		printf("Please, enter the surname of the subscriber: ");
		result = Read_inputstr(SURNAME, number_in_list);
	}
	while (!result);
	result = 0;

	do
	{
		printf("Please, enter the phonenumber of the subscriber: ");
		result = Read_inputstr(NUMBER, number_in_list);
	}
	while (!result);
	if ((*Abonent[*number_in_list].name != '\0')||(*Abonent[*number_in_list].surname != '\0')||(*Abonent[*number_in_list].number != '\0'))
	{
		if ((*count_abonents) < sizeof(Abonent)/sizeof(Abonent[0]))
			(*count_abonents)++;
		(*number_in_list)++;
		if((*number_in_list) >= sizeof(Abonent)/sizeof(Abonent[0]))
			(*number_in_list) = 0;
	}
	return;
}
//-----------------------------------------------
int Read_inputstr(int input_string_parametr, int *number_in_list)
{
	char flag = 0;
	char tmp = 0;
	unsigned char inputstr[30] = {};

	while(1)
	{
		fgets(inputstr, sizeof(inputstr), stdin);
		if (*inputstr != EOF)
		{
			for (int i = 0; i < sizeof(inputstr); i++)
			if (inputstr[i] == '\n')
			{
				inputstr[i] = '\0';
				flag++;
			}
			break;
		}
	}

	if (!flag)
	{
		do
		{
			tmp = getchar();
		}
		while ((tmp == EOF)||(tmp != '\n'));
		printf("Incorrect number of symbols entered! Should be less than 30!\n ");
		return(0);
	}
	switch (input_string_parametr)
	{
		case NAME:
			memcpy(Abonent[*number_in_list].name, inputstr, sizeof(Abonent[*number_in_list].name));
			break;
		case SURNAME:
			memcpy(Abonent[*number_in_list].surname, inputstr, sizeof(Abonent[*number_in_list].surname));
			break;
		case NUMBER:
			memcpy(Abonent[*number_in_list].number, inputstr, sizeof(Abonent[*number_in_list].number));
			break;
	}
	return(1);
}

//-----------------------------------------------
void Del_ab(int *number_in_list, int *count_abonents)
{
	int sub_num;
	unsigned char tmp[10];

	if (!(*count_abonents))//если в списке нет абонентов
	{
		printf("There are no subscribers in the list to delete!\r\n");
		return;
	}

	printf("Please, enter the subscriber's rownumber to delete: ");
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

	if((sub_num > 0)&&(sub_num <= (*count_abonents)))
	{
		sub_num--;
		memset(Abonent[sub_num].name, '\0', sizeof(Abonent[sub_num].name));
		memset(Abonent[sub_num].surname, '\0', sizeof(Abonent[sub_num].surname));
		memset(Abonent[sub_num].number, '\0', sizeof(Abonent[sub_num].number));
		for (int i = sub_num; i < *count_abonents; i++)
		{
			memcpy(Abonent[i].name, Abonent[i + 1].name, sizeof(Abonent[i + 1].name));
			memcpy(Abonent[i].surname, Abonent[i + 1].surname, sizeof(Abonent[i + 1].surname));
			memcpy(Abonent[i].number, Abonent[i + 1].number, sizeof(Abonent[i + 1].number));
		}
		(*number_in_list)--;
		(*count_abonents)--;
	}
	else
	{
		printf("Error: Incorrect subscriber's rownumber entered!\r\n");
	}
	return;
}
//-----------------------------------------------
void List_ab(int count_abonents)
{
	if(!count_abonents)//если в списке нет абонентов
	{
		printf("There are no subscribers to list!\r\n");
		return;
	}
	for(int i = 0; i < count_abonents; i++)
	{
		printf("%d \t Name: %s \t\t\t Surname: %s \t\t\t Phone number: %s \r\n", i+1, Abonent[i].name,\
			 Abonent[i].surname, Abonent[i].number);
	}
	return;
}
//-----------------------------------------------
void Search_abonent(int *count_abonents)
{
	int parametr = 0;
	char tmp[10];

	if(!(*count_abonents))
	{
		printf("There are no subscribers in the list for search!\r\n");
		return;
	}

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
			//Find_name(&(*count));
			printf("\r\nPlease, enter the name for search: ");
			Find_value(NAME, (&(*count_abonents)));
			break;
		case SURNAME:
			//Find_surname(&(*count));
			printf("\r\nPlease, enter the surname for search: ");
			Find_value(SURNAME, (&(*count_abonents)));
			break;
		case NUMBER:
			//Find_number(&(*count));
			printf("\r\nPlease, enter the phone number for search: ");
			Find_value(NUMBER, (&(*count_abonents)));
			break;
		default:
			printf("Error: Invalid parametr entered!\r\n");
			break;
	}
	return;
}
//-------------------------------------------------------------------------
void Find_value(int input_parametr, int *count_abonents)
{
	char parametr[30] = {};
	char flag = 0;
	int size = 0;

	while(1)
	{
		fgets(parametr,sizeof(parametr),stdin);

		if (*parametr != EOF)
		{
			for (int i = 0; i < sizeof(parametr); i++)

			if (parametr[i] == '\n')
			{
				parametr[i] = '\0';
				size = i;
			}
			break;
		}
	}
	switch (input_parametr)
	{
		case NAME:
			for (int i = 0; i <= *count_abonents; i++)
			{
				if ((memcmp(Abonent[i].name, parametr, sizeof(parametr))) == 0)
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
			break;
		case SURNAME:
			for (int i = 0; i <= *count_abonents; i++)
			{
				if ((memcmp(Abonent[i].surname, parametr, sizeof(parametr))) == 0)
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
			break;
		case NUMBER:
			for (int i = 0; i <= *count_abonents; i++)
			{
				if ((memcmp(Abonent[i].number, parametr, sizeof(parametr))) == 0)
				{
					flag = 1;
					printf("%d \t Name: %s \t\t\t Surname: %s \t\t\t Phone number: %s \r\n", i+1, Abonent[i].name,\
						 Abonent[i].surname, Abonent[i].number);
				}
			}
			if (!flag)
			{
				printf("There are no subscribers with the set phone number! \r\n");
			}
			break;
		}
	return;
}
//---------------------------------------------------------
