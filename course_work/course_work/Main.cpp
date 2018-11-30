#include "Lists.h"

int main()
{
	Information *start = NULL;
	Information *clip = NULL;
	Purchase *start_record = NULL;
	Technics *start_tech = NULL;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i, access = 1, delet = 0;
	while (1)
	{
		system("cls");
		puts("***** Главное меню *****\n");
		puts("1)Вход администратора");
		puts("2)Вход пользователя");
		puts("0)Выход\n");
		printf("Выбор >> ");
		i = test();
		system("cls");
		switch (i)
		{
		case 1: if (check_admin() == 0) admin(&start, &start_record, &start_tech, &access);
				else _getch();
				break;
		case 2: if (check_user(&clip, start) == 0) user(clip, &start, &start_record, &start_tech, &access);
				else _getch();
				break;
		case 0: delete_technics(&start_tech);
			delete_records(&start_record, &delet);
			delete_accounts(&start, &delet);
			break;
		default: puts("Выберите действие от 0 до 2");
			_getch();
		}
		if (i == 0) break;
	}
	return 0;
}

void admin(Information **start, Purchase **start_record, Technics **start_tech, int *access)
{
	Admin *start_a = NULL;
	Purchase *searc = NULL;
	int i, delet = 1;
	char key[15], key2[15];
	while (1)
	{
		system("cls");
		puts("***** Меню администратора *****\n");
		puts("1)Считывание данных с файлов");
		puts("2)Запись техники на закупку");
		puts("3)Просмотр список техники");
		puts("4)Создание пользователя");
		puts("5)Просмотр рейтинга");
		puts("6)Просмотр информации победителя");
		puts("7)Поиск записей");
		puts("8)Фильтрация записей");
		puts("9)Удаление пользователя и его записи");
		puts("10)Удаление всех пользователей и их записей");
		puts("11)Сохранить изменения в файлах");
		puts("0)Назад\n");
		printf("Выбор >> ");
		i = test();
		system("cls");
		if (i == 0) break;
		else
		{
			switch (i)
			{
			case 1:  if (*access != 1) puts("Данные уже считаны.\n");
					 else
					 {
						 open_data_file(start_record, start_tech, start);
						 *access += 1;
					 }
					 _getch();
					 break;

			case 2: input_technics(start_tech, start_record);
				break;

			case 3: inf_technics(*start_tech);
				break;

			case 4: if (create_account(start) == 1) puts("Пользователь с таким логином уже создан.\n");
					else puts("Пользователь добавлен.\n");
					_getch();
					break;

			case 5: rating(*start_record);
				break;

			case 6: if (winner(*start_record) == 1) puts("Информация о записях на тендер отсутствует");
				_getch();
				break;

			case 7: printf("Введите название предприятия, чьего запись Вы ищите: ");
				scanf("%s", key2);
				fflush(stdin);
				searc = search(*start_record, key2);
				if(search == NULL)
				{
					puts("Пользователь с записью не найден");
				}
				else
				{
					search_output(searc);
				}
				_getch();
					break;
			case 8: filtration(*start_record);
				_getch();
				break;
			case 9:	printf("Введите название предприятия, чья запись будет удалена: ");
				scanf("%s", key);
				fflush(stdin);
				if (delete_user_record(start_record, start, key) == 1)
				{
					puts("Пользователь с записью не найден");
				}
				else
				{
					puts("Пользователь с записью удален.");
				}
				_getch();
				break;
			case 10: delete_records(start_record, &delet);
				delete_accounts(start, &delet);
				puts("Список пользователей  и записей очищен.");
				_getch();
				break;
			case 11: close_account_file(*start);
				close_record_file(*start_record);
				_getch();
				break;
			default: puts("Выберите действие от 0 до 11");
			}
		}
	}
}

void user(Information *clip, Information **start, Purchase **start_record, Technics **start_tech, int *access)
{
	int i, create, check = 1;
	Purchase *searc = NULL;
	char key2[15];
	while (1)
	{
		system("cls");
		puts("***** Меню пользователя *****\n");
		puts("1)Считывание данных с файлов");
		puts("2)Создание записи");
		puts("3)Изменение записи");
		puts("4)Просмотр рейтинга");
		puts("5)Просмотр пяти самых дорогих предложений");
		puts("6)Просмотр собстенного результата");
		puts("7)Поиск записей");
		puts("8)Фильтрация записей");
		puts("9)Сохранить изменения в файлах");
		puts("0)Назад\n");
		printf("Выбор >> ");
		i = test();
		system("cls");
		if (i == 0) break;
		else
		{
			switch (i)
			{
			case 1: if (*access != 1) puts("Данные уже считаны.\n");
					else
					{
						open_data_file(start_record, start_tech, start);
						*access += 1;
					}
					_getch();
					break;
			case 2: if (check != 1) puts("Запись уже создана.\nВы не можете оставить больше одной записи.\n");
					else
					{
						check++;
						create = create_record(start_record, *start_tech, clip);
						if (create == 1) puts("Данными по технике отсутствуют. Подождите когда администратор добавит их.\n");
						else puts("Ваша запись пошла на обработку.\n");
					}
					_getch();
					break;
			case 3: if (change_record(start_record, *start_tech, clip) == 1)
			{
				puts("Запись еще не создана");
				_getch();
			}
					break;
			case 4:  rating(*start_record);
				break;
			case 5: if (sorting(*start_record) == 1)
						{
						puts("Информация о записях на тендер отсутствует.");
						}
						_getch();
				break;
			case 6:	if (my_record(*start_record, clip) == 1)
			{
				puts("Запись еще не создана");
			}
					_getch();
					break;
			case 7: printf("Введите название предприятия, чьего запись Вы ищите: ");
				scanf("%s", key2);
				fflush(stdin);
			
				searc = search(*start_record, key2);
				if (searc == NULL)
				{
					puts("Пользователь с записью не найден");
				}
				else
				{
					search_output(searc);
				}
				_getch();
				break;
			case 8:  filtration(*start_record);
				_getch();
				break;
			case 9: close_account_file(*start);
				close_record_file(*start_record);
				_getch();
				break;
			default: puts("Выберите действие от 0 до 9");
				_getch();
				break;
			}
		}
	}
}
