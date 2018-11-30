#include "Lists.h"

FILE *admin_file;
FILE *tech_file;
FILE *purchase_file;
FILE *account_file;

int check_admin()
{
	int i = 0;
	char login[20], password[20];
	Admin *adm = new Admin;
	admin_file = fopen("admin.txt", "a+");
	rewind(admin_file);
	system("cls");
	if (getc(admin_file) == EOF)
	{
		printf("В программе нет администратора. Задайте логин и пароль для администратора\n\n");
		printf("Введите логин: ");
		scanf("%s", (adm)->login_adm);
		printf("Введите пароль: ");
		scanf("%s", (adm)->password_adm);
		fprintf(admin_file, "%s\n%s", (adm)->login_adm, (adm)->password_adm);
		fclose(admin_file);
		printf("\nЛогин и пароль для администратора успешно созданы\n");
		return 1;
	}
	puts("***** Вход для администратора *****\n");

	printf("Введите логин: ");
	while (true)
	{
		login[i] = _getch();
		if (login[i] == '\r') break;
		if (login[i] == '\b')
		{
			printf("%s", "\b\b");
			i--;
		}
		else
		{
			printf("%c", '*');
			i++;
		}
	}
	login[i] = '\0';
	puts("");
	i = 0;
	printf("Введите пароль: ");
	while (true)
	{
		password[i] = _getch();
		if (password[i] == '\r') break;
		if (password[i] == '\b')
		{
			printf("%s", "\b\b");
			i--;
		}
		else
		{
			printf("%c", '*');
			i++;
		}
	}
	password[i] = '\0';
	puts("");
	rewind(admin_file);
	fscanf(admin_file, "%s", (adm)->login_adm);
	fscanf(admin_file, "%s", (adm)->password_adm);
	fclose(admin_file);
	if (strcmp(login, (adm)->login_adm) == 0 && strcmp((adm)->password_adm, password) == 0) return 0;
	else
	{
		puts("Логин или пароль введён неверно.");
		return 1;
	}
}

void open_data_file(Purchase **start_record, Technics **start_tech, Information **start)
{
	system("cls");
	purchase_file = fopen("purchase.txt", "r");
	if (purchase_file == NULL)
	{
		puts("Файл с информацией о записях на тендер еще не создан.\n");
	}
	else
	{
		if (getc(purchase_file) == EOF)
		{
			puts("Файл с информацией о записях на тендер пуст.\n");
			fclose(purchase_file);
		}
		else
		{
			rewind(purchase_file);
			int data2 = 0;
			while (!feof(purchase_file))
			{

				Purchase *pur = new Purchase;
				fscanf(purchase_file, "%s%s%s%s%lf%s", &pur->clip, &pur->supplier.name_company, &pur->supplier.name_user, &pur->res_technics, &pur->price, &pur->date);
				if (data2 == 0)
				{
					pur->next = NULL;
					*start_record = pur;
					data2++;
				}
				else
				{
					Purchase *prev = *start_record, *post = *start_record;
					while (1)
					{
						while (post != NULL)
						{
							if (post->price > pur->price)
							{
								//поместим новый узел между узлами, задаваемыми prev и post
								pur->next = post;
								if (post == *start_record)
									*start_record = pur;
								else
									prev->next = pur;
								break;
							}
							prev = post;
							post = post->next;
						}
						//поместим новый узел в конец списка
						pur->next = NULL;
						prev->next = pur;
						break;
					}
				}
			}
			puts("Информация о записях на тендер успешно считана.\n");
			fclose(purchase_file);
		}
	}
	tech_file = fopen("technics.txt", "r");
	if (tech_file == NULL)
	{
		puts("Файл с данными по технике еще не создан.\n");
	}
	else
	{
		if (getc(tech_file) == EOF)
		{
			puts("Файл с данными по технике пуст.\n");
			fclose(tech_file);
		}
		else
		{
			rewind(tech_file);
			int data = 0;
			while (!feof(tech_file))
			{
				Technics *t = new Technics;
				fscanf(tech_file, "%s%d", &t->name_technics, &t->guarantee);
				if (data == 0)
				{
					t->next = NULL;
					*start_tech = t;
					data++;
				}
				else
				{
					t->next = *start_tech;
					*start_tech = t;
				}
			}
			puts("Данные по технике успешно считаны.\n");
			fclose(tech_file);
		}
	}

	account_file = fopen("account.txt", "r");
	if (account_file == NULL)
	{
		puts("Файл с информацией об аккаунтах еще не создан.\n");
	}
	else
	{
		if (getc(account_file) == EOF)
		{
			puts("Файл с информацией об аккаунтах пуст.\n");
			fclose(account_file);
		}
		
		else
		{
			rewind(account_file);
			int data3 = 0;
			while (!feof(account_file))
			{
				Information *in = new Information;
				fscanf(account_file, "%s%s", &in->login_str, &in->password_str);
				if (data3 == 0)
				{
					in->next = NULL;
					*start = in;
					data3++;
				}
				else
				{
					in->next = *start;
					*start = in;
				}
			}
			puts("Информация об аккаунтах успешно считана.\n");
			fclose(account_file);
		}
	}

}

int close_record_file(Purchase *start_record)
{
	purchase_file = fopen("purchase.txt", "w");
	if (start_record != NULL)
	{
		Purchase *pur = start_record;
		while (pur != NULL)
		{
			fprintf(purchase_file, "%s\t%s\t%s\t%s\t\t%.0lf\t%s", pur->clip, pur->supplier.name_company, pur->supplier.name_user, pur->res_technics, pur->price, pur->date);
			pur = pur->next;
			if (pur != NULL) fprintf(account_file, "\n");
		}
		puts("Информация о записях на тендер перезаписана в файл.\n");
		return 0;
	}
	else
	{
		puts("Информация о записях на тендер отсутствует.\n");
		fclose(purchase_file);
		return 1;
	}
}

void close_account_file(Information *start)
{
	account_file = fopen("account.txt", "w");
	if (start != NULL)
	{
		Information *p = start;
		while (p != NULL)
		{
			fprintf(account_file, "%s\t%s", p->login_str, p->password_str);
			p = p->next;
			if (p != NULL) fprintf(account_file, "\n");
		}
		puts("Информация об аккаутах перезаписана в файл.\n");
	}
	else puts("Информация об аккаутах отсутствует");
	fclose(account_file);
}

int input_technics(Technics **start_tech, Purchase **start_record)
{
	int i = 0, delet = 1;
	tech_file = fopen("technics.txt", "a+");
	rewind(tech_file);
	system("cls");
	puts("***** Ввод техники *****\n");
	if (getc(tech_file) != EOF)
	{
		int j;
		puts("Список техники уже составлен!!! Вы уверены что хотите изменить его?");
		puts("Это приведёт к удалению всех записей, созданных пользователями.\n");
		puts("1)Перезаписать");
		puts("2)Отмена");
		printf("Выбор >> ");
		while (1)
		{
			j = test();
			if (j != 1 && j != 2) puts("Выберите действие 1 или 2");
			else break;
		}
		if (j == 2) return 1;
		else
		{
			delete_records(start_record, &delet);
			delete_technics(start_tech);
			fclose(tech_file);
			tech_file = fopen("technics.txt", "w");
		}
	}
	while (1)
	{
		Technics *tech = new Technics;
		printf("Введите название техники: ");
		scanf("%s", tech->name_technics);
		fflush(stdin);
		printf("Введите минимальную гарантию необходимую Вамна эту технику (в мес.): ");
		tech->guarantee = test();
		fprintf(tech_file, "\n%s\t%d", tech->name_technics, tech->guarantee);
		if (*start_tech == NULL)
		{
			tech->next = NULL;
			*start_tech = tech;
		}
		else
		{
			tech->next = *start_tech;
			*start_tech = tech;
		}
		puts("Добавить техику?\n1)да\n2)нет");
		int res;
		while (1)
		{
			res = test();
			if (res != 1 && res != 2) puts("Выберите действие 1 или 2");
			else break;
		}
		if (res == 2)
		{
			fclose(tech_file);
			return 0;
		}
	}

}

int check_user(Information **clip, Information *start)
{
	int i = 0;
	char login[20], password[20];
	account_file = fopen("account.txt", "r");

	system("cls");
	if (account_file == NULL || getc(account_file) == EOF)
	{
		printf("Для пользователей нет ни одного аккаунта, чтобы войти в систему\n\n");
		if (getc(account_file) == EOF) fclose(account_file);
		return 1;
	}
	else
	{
		puts("***** Вход для пользователя *****\n");
		printf("Введите логин: ");
		while (true)
		{
			login[i] = _getch();
			if (login[i] == '\r') break;
			if (login[i] == '\b')
			{
				printf("%s", "\b\b");
				i--;
			}
			else
			{
				printf("%c", '*');
				i++;
			}
		}
		login[i] = '\0';
		puts("");
		i = 0;
		printf("Введите пароль: ");
		while (true)
		{
			password[i] = _getch();
			if (password[i] == '\r') break;
			if (password[i] == '\b')
			{
				printf("%s", "\b\b");
				i--;
			}
			else
			{
				printf("%c", '*');
				i++;
			}
		}
		password[i] = '\0';
		puts("");
		rewind(account_file);
		while (!feof(account_file))
		{
			Information *user = new Information;
			fscanf(account_file, "%s%s", &user->login_str, &user->password_str);
			if (strcmp(login, user->login_str) == 0 && strcmp(user->password_str, password) == 0)
			{
				*clip = user;
				fclose(account_file);
				return 0;
			}
			user = user->next;
		}
		puts("Логин или пароль введён неверно.\n");
		fclose(account_file);
		return 1;
	}

}

void delete_technics(Technics **start_tech)
{
	Technics *p = *start_tech;
	while (p != NULL)
	{
		*start_tech = p->next;
		free(p);
		p = *start_tech;
	}
	*start_tech = NULL;
}

void delete_records(Purchase **start_record, int *delet)
{
	if (*delet == 1)
	{
		purchase_file = fopen("purchase.txt", "w");
		fclose(purchase_file);
	}
	Purchase *r = *start_record;
	while (r != NULL)
	{
		*start_record = r->next;
		free(r);
		r = *start_record;
	}
	*start_record = NULL;
}

void delete_accounts(Information **start, int *delet)
{
	if (*delet == 1)
	{
		account_file = fopen("account.txt", "w");
		fclose(account_file);
	}
	Information *i = *start;
	while (i != NULL)
	{
		*start = i->next;
		free(i);
		i = *start;
	}
	*start = NULL;
}
