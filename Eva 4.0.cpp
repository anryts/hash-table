https://github.com/durakprostak/1grade.git
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include <time.h>
#define SIZE 15
typedef struct node
{
	node* next;
	float a;
	char* key;
};

int scan(int& sort);
int scanw(int& mode);
void ReadTxtFilename(char* filename);
int hashing_key(int size, char* key);
int hs_table_search(node* hs_table[], char* key, int size);
int size_hs_table(node* hs_table[], int size);
void file_hs_print(node* hs_table[], int size, FILE*& fp);
void hs_table_print(node* hs_table[], int size);
int inserting_hs_table(node* hs_table[], char* key, float a, int size);
void input_key(char* key);
void input_data(float& data);
node** new_hs_table(node* hs_table[], int curr_size, int new_size);
int hs_delete_key(node* hs_table[], char* key, int size);
node** init_hs_table(int size);
int hashing_key(int size, char* key);
void in_hs_print(node* hs_table[], int size, FILE*& fp);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	node** hs_table = NULL;
	FILE* fp;					// дескриптор файлу
	char key[SIZE];				//ключ
	float a = 0;                        // данні
	char filename[SIZE];				// змінні для вибору режиму роботи програми
	int size_of_hs_table = 100; int new_size_of_hs_table = NULL;       //розмір хеш-таблиці
	int sort,                            //вибір елемента меню
		check,
		printer;                        // спосіб додавання елементу
	do
	{
		printf("1.Створити хеш-таблицю на 100 елементів\n2.Додати елемент до хеш-таблиці\n3.Вивести хеш-таблицю\n");
		printf("4.Знайти елемент в хеш-таблиці\n5.Розмір хеш-таблиці\n6.Змінити розмір хеш-таблиці\n");
		printf("7.Видалити елемент\n8.Записати у файл\n9.Завершення роботи\n");
		scan(sort);
		if (sort == 1) {      //Створити хеш-таблицю
			if (hs_table)
			{
				printf("Хеш-таблиця вже існує\n");
			}
			else {
				hs_table = init_hs_table(size_of_hs_table);
				if (!hs_table)
				{
					printf("Хеш-таблиця не існує\n");
					return -1;
				}
			}
		}
		if (sort == 2) {      //Додати елемент
			if (!hs_table)
			{
				printf("Хеш-таблиця не існує\n");
			}
			else {
				printf("Додати елемент\n1.В ручну\n2.З файлу\n");
				scanw(printer);
				if (printer == 1)
				{
					input_key(key);
					input_data(a);
					check = inserting_hs_table(hs_table, key, a, size_of_hs_table);
					if (check != 0)
					{
						if (check == -2)
						{
							printf("Такий ключ вже існує, спробуйте інший\n");
						}
						if (check == -1)
						{
							printf("Не хватає пам'яті\n");
							return -1;
						}
					}
				}
				if (printer == 2) {
					{
						printf("\nВведіть назву файлу типу name.txt:\n ");
						ReadTxtFilename(filename);
						if ((fp = fopen(filename, "r")) == NULL)
						{
							printf("Виникла помилка при відкритті файлу %s! \n", filename);
							return -1;
						}
						in_hs_print(hs_table, size_of_hs_table, fp);
					}
				}
			}
		}
		if (sort == 3) {        //Вивести хеш-таблицю
			if (!hs_table)
			{
				printf("Хеш-таблиця не існує\n");
			}
			else {
				hs_table_print(hs_table, size_of_hs_table);
			}
		}
		if (sort == 4) {     // Знайти елемент в хеш-таблиці
			if (!hs_table)
			{
				printf("Хеш-таблиця не існує\n");
			}
			else {
				input_key(key);
				check = hs_table_search(hs_table, key, size_of_hs_table);
				if (check == 0)
				{
				}
				if (check == -1)
				{
					printf("\nТакого ключа не існує!\n\n");
				}
			}
		}
		if (sort == 5) {       //Розмір хеш-таблиці
			if (!hs_table)
			{
				printf("Хеш-таблиця не існує\n");
			}
			else {
				printf("Розмір хеш-таблиці:%d\n", size_hs_table(hs_table, size_of_hs_table));
			}
		}
		if (sort == 6) {      //Змінити розмір
			if (!hs_table)
			{
				printf("Хеш-таблиця не існує\n");
			}
			else {
				printf("Введіть новий розмір хеш-таблиці\n");
				scanf("%d", &new_size_of_hs_table);
				hs_table = new_hs_table(hs_table, size_of_hs_table, new_size_of_hs_table);
				size_of_hs_table = new_size_of_hs_table;
				if (!hs_table)
				{
					printf("Хеш-таблиця не існує");
					return -1;
				}
			}
		}
		if (sort == 7) {   //Видалити елемент
			if (!hs_table)
			{
				printf("Хеш-таблиця не існує\n");
			}
			else {
				input_key(key);
				check = hs_delete_key(hs_table, key, size_of_hs_table);
				if (check != 0)
				{
					printf("\nТакого ключа не існує\n");
				}
			}
		}
		if (sort == 8) {            //Записати у файл
			if (!hs_table)
			{
				printf("Хеш-таблиця не існує\n");
			}
			else {
				printf("Введіть назву файлу\n");
				scanf("%s", filename);
				if ((fp = fopen(filename, "w")) == NULL)
				{
					return -1;
				}
				file_hs_print(hs_table, size_of_hs_table, fp);
			}
		}
	} while (sort != 9);      //Завершення роботи
	return 0;
}
/* Функція scan
Функція для визначення пункта меню
Вхід:
sort - змінна для заповнення, передача за посиланням
Результат:
Змінна з записаним числом
*/
int scan(int& sort) {
	bool check = false;
	do {
		while (!scanf("%d", &sort)) {
			printf("Введене значення не є допустимим, спробуйте ще раз: ");
			while (getchar() != '\n');
		}
		if (sort < 1 || sort > 8) {
			printf("Введене значення не є допустимим, спробуйте ще раз: ");
		}
		else {
			check = true;
		}
	} while (check == false);
	return sort;
}
/* Функція scanw
Функція для визначення способу вводу
Вхід:
mode - змінна для заповнення, передача за посиланням
Результат:
Змінна з записаним числом
*/
int scanw(int& mode) {
	bool check = false;
	do {
		while (!scanf("%d", &mode)) {
			printf("Введено не число, спробуйте ще раз:");
			while (getchar() != '\n');
		}
		if (mode != 1 && mode != 2) {
			printf("Неправильний режим вводу, спробуйте ще раз:");
		}
		else {
			check = true;
		}
	} while (check == false);
	return mode;
}
/* Функція ReadTxtFilename
Функція для визначення назви файлу
Вхід:
filename - змінна для заповнення, передача за посиланням
Результат:
Змінна з записаним числом
*/
void ReadTxtFilename(char* filename) {// передаємо масив для назви файлу
	int flag = 0;
	do {
		fgets(filename, 1024, stdin);// у рядок записуємо назву фалйу 
		if (filename[0] == '\n' && flag == 1) {
			printf("Текст не повинен бути пустим, спробуйте ще раз:");
		}
		flag = 1;
	} while (filename[0] == '\n');// цикл буде виконуватись доки користувач не введе вірну назву файлу
	bool check = false;
	for (int i = strlen(filename); i > 0; i--)
	{
		if (filename[i] == '.')
		{
			if (filename[i + 1] != 't' || filename[i + 2] != 'x' || filename[i + 3] != 't' || filename[i + 4] != '\n')
			{
				filename[strlen(filename) - 1] = '.';
				strcat(filename, "txt");
			}
			else {
				filename[strlen(filename) - 1] = ' ';
			}
			check = true;
		}
	}
	if (check == false) {
		filename[strlen(filename) - 1] = '.';
		strcat(filename, "txt");
	}
}
/*
Функція init_hs_table
ініцілізує хеш-таблицю
Вхід: розмір хеш-таблиці
Вихід: ініціалізована таблиця
*/
node** init_hs_table(int size)
{
	node** hash_table = NULL;                                //ініціалізація покажчика самої таблиці 
	if (!(hash_table = (node**)malloc(size * sizeof(node)))) // виділення пам'яті під вузли таблиці
	{
		return NULL;								       	// у випадку якщо пам'ять не була виділена, то функці буде повертати 0
	}
	for (int j = 0; j < size; j++)
	{
		hash_table[j] = NULL;								// ініціалізація кожного вузла таблиці
	}
	return hash_table;										// повернення ініціалізованої таблиці
}
/*Функція hs_delete_key
 видаляє елемент з хеш-таблиці
 Вхід: хеш-таблиця, ключ, розмір хеш-таблиці
 Вихід: видалений елемент
*/
int hs_delete_key(node* hs_table[], char* key, int size)
{
	node* curr_hs_table;
	node* prevv_hs_table;
	int hs_table_index = hashing_key(size, key);				//дізнаємося індекс, елемента котрий потрібно видалити
	curr_hs_table = hs_table[hs_table_index];
	prevv_hs_table = curr_hs_table;
	while (curr_hs_table && strcmp(curr_hs_table->key, key))	//пошук ключа у вузлі
	{
		prevv_hs_table = curr_hs_table;
		curr_hs_table = curr_hs_table->next;
	}
	if (!curr_hs_table)
	{
		return -2;
	}
	if (hs_table[hs_table_index] == curr_hs_table)			//якщо елемент є корнем 
	{
		prevv_hs_table = hs_table[hs_table_index]->next;
		free(curr_hs_table);
		hs_table[hs_table_index] = prevv_hs_table;
	}
	else if (!curr_hs_table->next)							// якщо елемент останній у вузлі
	{
		free(curr_hs_table);
		prevv_hs_table->next = NULL;
	}
	else
	{
		prevv_hs_table->next = curr_hs_table->next;
		free(curr_hs_table);
	}
	return 0;
}
/*
Функція new_hs_table
створює нову хеш-таблицю
Вхід:хеш-таблиця, поточний розмір таблиці, новий розмір таблиці
Вихід: нова ініціалізована хеш-таблиця
*/
node** new_hs_table(node* hs_table[], int curr_size, int new_size)
{
	node** new_hs_table = init_hs_table(new_size);	              // ініціалізація нової таблиці
	float buf;
	char* supp_key;
	for (int j = 0; j < curr_size; j++)
	{
		while (hs_table[j])										 // перенесення всіх елементів  вузла до нової таблиці
		{
			supp_key = (char*)malloc(strlen(hs_table[j]->key + 1));
			if (!supp_key)
			{
				return NULL;
			}
			strcpy(supp_key, hs_table[j]->key);
			buf = hs_table[j]->a;
			hs_delete_key(hs_table, hs_table[j]->key, curr_size);
			inserting_hs_table(new_hs_table, supp_key, buf, new_size);
		}
	}
	return new_hs_table;
}
/*Функція hashing_key
 хешує ключ
 Вхід:розмір хеш-таблиці, ключ
 Вихід: індекс в хеш-таблиці
*/
int hashing_key(int size, char* key)											 // функція хешування ключа
{
	int hash = 0;
	int length = strlen(key);
	for (long int i = 0; i < length; i++)
	{
		hash = hash + (int)key[i];
	}

	return hash % size;
}
void input_key(char* key)
{
	printf("Введіть ключ:");
	scanf("%s", key);
	key[strlen(key)] = '\0';
}
void input_data(float& data)
{
	printf("Введіть значення");
	scanf("%lf", &data);
}
/*Функція inserting_hs_table
 додає елемент в хеш-таблицю
 Вхід:хеш-таблиця, ключ, комплексне число, розмір хеш-таблиці
 Вихід: доданий елемент в хеш-таблицю
*/
int inserting_hs_table(node* hs_table[], char* key, float a, int size)
{
	node* main_hs_table;
	node* supp_hs_table;
	main_hs_table = (node*)malloc(sizeof(node));
	if (!main_hs_table)
	{
		return -1;
	}
	main_hs_table->key = (char*)malloc(sizeof(char) * strlen(key));
	if (!main_hs_table->key)
	{
		return -1;
	}
	for (int j = 0; j < size; j++)      /*перевірка на унікальність ключа в хеш-таблиці*/
	{
		if (hs_table == NULL)
		{
			continue;
		}
		supp_hs_table = hs_table[j];
		while (supp_hs_table)
		{
			if (strcmp(supp_hs_table->key, key) == 0)
			{
				return -2;
			}
			supp_hs_table = supp_hs_table->next;
		}
	}
	strcpy(main_hs_table->key, key);
	main_hs_table->a = a;
	main_hs_table->next = hs_table[hashing_key(size, key)];					//вставляємо на місце колишнього першого елементу
	hs_table[hashing_key(size, key)] = main_hs_table;						//встановлюємо адресу нового першого елементу в хеш-таблицю
	return 0;
}
/*Функція hs_table_print
 друкує елементи хеш-таблицю
 Вхід: хеш-таблиця, розмір хеш-таблиці
 Вихід: нічого
*/
void hs_table_print(node* hs_table[], int size)
{
	node* supp_table;
	for (int j = 0; j < size; j++)
	{
		if (hs_table[j] == NULL)
		{
			continue;
		}
		supp_table = hs_table[j];
		printf("[%d]\t", j);
		while (supp_table)
		{
			printf("%s ", supp_table->key);
			printf("%lf", supp_table->a);
			supp_table = supp_table->next;
			printf("\n\t");
		}
		printf("\r");
	}
}
void file_hs_print(node* hs_table[], int size, FILE*& fp)
{
	node* supp_hs_table;
	for (int j = 0; j < size; j++)
	{
		if (hs_table[j] == NULL)
		{
			continue;
		}
		supp_hs_table = hs_table[j];
		while (supp_hs_table)
		{
			fprintf(fp, "%s %lf\n", supp_hs_table->key, supp_hs_table->a);
			supp_hs_table = supp_hs_table->next;
		}
	}
}
void in_hs_print(node* hs_table[], int size, FILE*& fp)
{
	char supp_key[SIZE];
	float supp=0;
	while (!feof(fp))
	{
		fscanf(fp, "%s", supp_key);
		fscanf(fp, "%f", &supp);
		inserting_hs_table(hs_table, supp_key, supp, size);
	}
}
/* Функція size_hs_table
 визначає кількість елементів хеш-таблиці
 Вхід: хеш-таблиці, розмір хеш-таблиці
 Вихід: кількість елементів в хеш-таблиці
*/
int size_hs_table(node* hs_table[], int size)
{
	int hs_size = 0;
	for (int j = 0; j < size; j++)
	{
		if (hs_table[j] != NULL)
		{
			hs_size++;
		}
	}
	return hs_size;
}
/*Функція hs_table_search
 шукає елемент в хеш-таблиці
 Вхід:хеш-таблиця, ключ, розмір хеш-таблиці
 Вихід: знайдений елемент
*/
int hs_table_search(node* hs_table[], char* key, int size)
{
	int hs_index = hashing_key(size, key);
	node* supp_table = hs_table[hs_index];
	while (supp_table)
	{
		if (strcmp(supp_table->key, key) == 0)
		{
			printf("%lf %s\n", supp_table->a, supp_table->key);
			return 0;
		}
		supp_table = supp_table->next;
	}
	return -1;
}
