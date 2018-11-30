#include "Lists.h"
#include <time.h> 

int test()
{
	int res2, i;
	do {
		res2 = scanf("%d", &i);
		while (getchar() != '\n');
		if (res2 != 1) printf("Введите число!\n");
	} while (res2 != 1);
	return i;
}

int create_account(Information **start)
{
	puts("***** Создание аккаунтов *****\n");
	Information *us = new Information;
	printf("Введите имя аккаунта: ");
	scanf("%s", us->login_str);
	Information	*p = *start;
	while (p != NULL)
	{
		if (strcmp(us->login_str, p->login_str) == 0) return 1;
		p = p->next;
	}
	printf("Введите для него пароль: ");
	scanf("%s", us->password_str);
	if (*start == NULL)
	{
		us->next = NULL;
		*start = us;
		return 0;
	}
	else
	{
		Information *prev = *start, *post = *start;
		while (post != NULL)
		{
			if (strcmp(post->login_str, us->login_str) > 0)
			{
				//поместим новый узел между узлами, задаваемыми prev и post
				us->next = post;
				if (post == *start)
					*start = us;
				else
					prev->next = us;
				return 0;
			}
			prev = post;
			post = post->next;
		}
		//поместим новый узел в конец списка
		us->next = NULL;
		prev->next = us;
		return 0;
	}
}

void input_record_supplier(Purchase **record)
{
	printf("Введите название компании: ");
	scanf("%s", (*record)->supplier.name_company);
	fflush(stdin);
	printf("Введите имя представителя: ");
	scanf("%s", (*record)->supplier.name_user);
	fflush(stdin);
}

int input_record_res_technics(Purchase **record, Technics *start_tech)
{
	if (start_tech == NULL) return 1;
	else
	{
		Technics *p = start_tech;
		double total_amount = 0, amount;
		while (p != NULL)
		{
			printf("\nВведите Вашу цену за %s в руб. Гатантия >= %d месяцев.\nЕсли эту технику не предоставляете, введите 0.\n", p->name_technics, p->guarantee);
			printf("Ввод >> ");
			amount = test();
			if (amount == 0)
			{
				char t[] = "неполный";
				strcpy((*record)->res_technics, t);
				(*record)->price = 10000000;
				return 0;
			}
			total_amount += amount;
			p = p->next;
		}
		char t[] = "полный";
		strcpy((*record)->res_technics, t);
		(*record)->price = total_amount;
		return 0;
	}
}

int create_record(Purchase **start_record, Technics *start_tech, Information *clip) 
{
	puts("***** Создание записи *****\n");
	Purchase *record = new Purchase;
	Purchase *pr = *start_record;
	while (pr != NULL)
	{
		if (strcmp(pr->clip, clip->login_str) == 0) return 1;
		pr = pr->next;
	}
	strcpy(record->clip, clip->login_str);
	input_record_supplier(&record);
	if (input_record_res_technics(&record, start_tech) == 1) return 1;
	struct tm *u;
	const time_t timer = time(NULL);
	u = localtime(&timer);
	strftime(record->date, 11, "%d.%m.%Y", u);
	if (*start_record == NULL)
	{
		record->next = NULL;
		*start_record = record;
		return 0;
	}
	else
	{
		Purchase *prev = *start_record, *post = *start_record;
		while (post != NULL)
		{
			if (post->price > record->price)
			{
				//поместим новый узел между узлами, задаваемыми prev и post
				record->next = post;
				if (post == *start_record)
					*start_record = record;
				else
					prev->next = record;
				return 0;
			}
			prev = post;
			post = post->next;
		}
		//поместим новый узел в конец списка
		record->next = NULL;
		prev->next = record;
		return 0;
	}
}

int winner(Purchase *start_record)
{
	if (start_record != NULL)
	{
		Purchase *winner = start_record;
		Purchase *pur = start_record;
		pur = pur->next;
		while (pur != NULL)
		{
			if (winner->price > pur->price)
			{
				winner = pur;
			}
			pur = pur->next;
		}
		system("cls");
		puts("***** Победитель *****\n");
		puts("-----------------------------------------------------------------------");
		puts("|Компания       |Представитель  |Пакет техники  |Цена      |Дата      |");
		puts("-----------------------------------------------------------------------");
		printf("|%-15s|%-15s|%-15s|%-10.0lf|%-10s|\n", winner->supplier.name_company, winner->supplier.name_user, winner->res_technics, winner->price, winner->date);
		puts("-----------------------------------------------------------------------");
		return 0;
	}
	else return 1;
}

void inf_technics(Technics *start_tech)
{

	if (start_tech != NULL)
	{
		puts("---------------------------------");
		puts("|Теxника        |Гарантия       |");
		puts("---------------------------------");
		Technics *p = start_tech;
		while (p != NULL)
		{
			printf("|%-15s|%-15d|\n", p->name_technics, p->guarantee);
			puts("---------------------------------");
			p = p->next;
		}
	}
	else puts("Информация о технике отсутствует.");
	_getch();
}

void rating(Purchase *start_record)
{

	if (start_record != NULL)
	{
		puts("-----------------------------------------------------------------------");
		puts("|Компания       |Представитель  |Пакет техники  |Цена      |Дата      |");
		puts("-----------------------------------------------------------------------");
		Purchase *pur = start_record;
		while (pur != NULL)
		{
			printf("|%-15s|%-15s|%-15s|%-10.0lf|%-10s|\n", pur->supplier.name_company, pur->supplier.name_user, pur->res_technics, pur->price, pur->date);
			puts("-----------------------------------------------------------------------");
			pur = pur->next;
		}
	}
	else puts("Информация о записях на тендер отсутствует.");
	_getch();
}

int my_record(Purchase *start_record, Information *clip)
{
	system("cls");
	Purchase *record = start_record;
	int res = 0;
	while (record != NULL)
	{
		if (strcmp(record->clip, clip->login_str) == 0)
		{
			res++;
			break;
		}
		record = record->next;
	}
	if (res == 0) return 1;
	else
	{
		system("cls");
		puts("***** Мой результат *****\n");
		if (record->price == 10000000)
		{
			puts("Ваша заявка на участие была отклонена!\nВы не смогли предоставить всю необходимую офисную технику.\n");
			return 0;
		}
		Purchase *winner = start_record;
		Purchase *pur = start_record;
		pur = pur->next;
		while (pur != NULL)
		{
			if (winner->price > pur->price)
			{
				winner = pur;
			}
			pur = pur->next;
		}
		if (record->price == winner->price) puts("Вы победили в тендере на закупку офисной технники!\nПоздравляем!!!");
		else puts("Вы проиграли в тендере на закупку офисной технники!");
		return 0;
	}
}

int change_record(Purchase **start_record, Technics *start_tech, Information *clip)
{
	system("cls");
	Purchase *record = *start_record;
	int res = 0;
	while (record != NULL)
	{
		if (strcmp(record->clip, clip->login_str) == 0)
		{
			res++;
			break;
		}
		record = record->next;
	}
	if (res == 0) return 1;
	int i;
	puts("***** Изменение записи *****\n");
	puts("Какую часть записи Вы хотите изменить?\n");
	puts("1)Сведения о поставщике");
	puts("2)Наличие техники и цены на них");
	puts("0)Назад\n");
	printf("Выбор >> ");
	i = test();
	system("cls");
	if (i == 0) return 2;
	Purchase *record2 = new Purchase;
	strcpy(record2->clip, record->clip);
	strcpy(record2->supplier.name_company, record->supplier.name_company);
	strcpy(record2->supplier.name_user, record->supplier.name_user);
	strcpy(record2->res_technics, record->res_technics);
	record2->price = record->price;
	strcpy(record2->date, record->date);

	delete_one_record(start_record, &record);
	Purchase *prev = *start_record, *post = *start_record;
	switch (i)
	{
	case 1: input_record_supplier(&record2);
		break;
	case 2: input_record_res_technics(&(record2), start_tech);
		break;
	default: puts("Выберите действие от 0 до 2");
		_getch();
	}
	if (*start_record == NULL)
	{
		record2->next = NULL;
		*start_record = record2;
		return 0;
	}
	else
	{
		while (post != NULL)
		{
			if (post->price > record2->price)
			{
				//поместим новый узел между узлами, задаваемыми prev и post
				record2->next = post;
				if (post == *start_record) *start_record = record2;
				else prev->next = record2;
				return 0;
			}
			prev = post;
			post = post->next;
		}
		//поместим новый узел в конец списка
		record2->next = NULL;
		prev->next = record2;
		return 0;
	}
}

void delete_one_record(Purchase **start_record, Purchase **record)
{
	if (*record == *start_record)
	{
		*start_record = (*start_record)->next;
	}
	else
	{
		Purchase *pre = *start_record;
		while (pre != NULL)
		{
			if (pre->next == *record)
				break;            //нашли предшествующий узел и выходим из цикла
			pre = pre->next;
		}
		pre->next = (*record)->next;
	}
	delete *record;
}

Purchase *search(Purchase *start_record, char key[])
{

	if (start_record == NULL) return NULL;
	else
	{
		Purchase *p = start_record;
		while (p != NULL)
		{
			if (strcmp(p->supplier.name_company, key) == 0)
			{
				return p;
			}
			p = p->next;
		}
		return NULL;
	}
}

void search_output(Purchase *record)
{
	puts("-----------------------------------------------------------------------");
	puts("|Компания       |Представитель  |Пакет техники  |Цена      |Дата      |");
	puts("-----------------------------------------------------------------------");
	printf("|%-15s|%-15s|%-15s|%-10.0lf|%-10s|\n", record->supplier.name_company, record->supplier.name_user, record->res_technics, record->price, record->date);
	puts("-----------------------------------------------------------------------");
	record = record->next;
	
}

void filtration(Purchase *start_record)
{
	int i;
	puts("***** Фильтрация записей *****\n");
	puts("1)По цене закупки");
	puts("2)По дате записи");
	puts("0)Назад\n");
	printf("Выбор >> ");
	i = test();
	system("cls");
	if (i == 0) return ;
	switch (i)
	{
	case 1: if(filtering_by_price(start_record) == 1) puts("\t\tЗаписей в этом диапазоне нет.");
		break; 
	case 2:if (filtering_by_date(start_record) == 1) puts("\t\tЗаписей в этом диапазоне нет.");
		break;
	default: puts("Выберите действие от 0 до 2");
		_getch();
		return ;
	}
}

int filtering_by_price(Purchase *start_record)
{
	int min, max, flag = 0;
	puts("Необходимо ввести диапазон цены");
	printf("ВВедите минимальную цену: ");
	min = test();
	printf("ВВедите максимальную цену: ");
	max = test();
	if (start_record == NULL) return 1;
	else
	{
		puts("-----------------------------------------------------------------------");
		puts("|Компания       |Представитель  |Пакет техники  |Цена      |Дата      |");
		puts("-----------------------------------------------------------------------");
		Purchase *p = start_record;
		while (p != NULL)
		{
			if (p->price >= min && p->price <= max)
			{
				printf("|%-15s|%-15s|%-15s|%-10.0lf|%-10s|\n", p->supplier.name_company, p->supplier.name_user, p->res_technics, p->price, p->date);
				puts("-----------------------------------------------------------------------");
				flag++;
			}
			p = p->next;
		}
		if (flag != 0) return 0;
		else return 1;
	}
}

int filtering_by_date(Purchase *start_record)
{
	char mind[3], maxd[3], minm[3], maxm[3];
	int flag = 0;
	puts("Необходимо ввести диапазон дат");
	printf("------Введите минимальную дату------\nВведите день: ");
	while (1)
	{
		scanf("%s", mind);
		if (mind[0] == 51 && mind[1] >= 48 && mind[1] <= 49) break;
		if (mind[0] == 48 && mind[1] >= 49 && mind[1] <= 57) break;
		if (mind[0] >= 49 && mind[0] <= 50 && mind[1] >= 48 && mind[1] <= 57) break;

		printf("Неправильный ввод.\nВведите корректно день: ");
		fflush(stdin);

	}
	printf("\nВведите мecяц: ");
	while (1)
	{
		scanf("%s", minm);
		if (minm[0] == 48 && minm[1] >= 49 && minm[1] <= 57) break;
		if (minm[0] == 49 && minm[1] >= 48 && minm[1] <= 50) break;

		printf("Неправильный ввод.\nВведите корректно месяц: ");
		fflush(stdin);
	}
	while (1)
	{
		printf("\n------Введите максимальную дату------\nВведите день: ");
		while (1)
		{
			scanf("%s", maxd);
			if (maxd[0] == 51 && maxd[1] >= 48 && maxd[1] <= 49) break;
			if (maxd[0] == 48 && maxd[1] >= 49 && maxd[1] <= 57) break;
			if (maxd[0] >= 49 && maxd[0] <= 50 && maxd[1] >= 48 && maxd[1] <= 57) break;
			printf("Неправильный ввод.\nВведите корректно день: ");
			fflush(stdin);
		}

		printf("\nВведите мecяц: ");
		while (1)
		{
			scanf("%s", maxm);
			if (maxm[0] == 48 && maxm[1] >= 49 && maxm[1] <= 57) break;
			if (maxm[0] == 49 && maxm[1] >= 48 && maxm[1] <= 50) break;
			printf("Неправильный ввод.\nВведите корректно месяц: ");
			fflush(stdin);
		}
		if (strcmp(maxm, minm) >= 0) break;
		if (strcmp(maxm, minm) == 0 && strcmp(maxd, mind) >= 0) break;
		printf("Минимальная дата больше максимальной.\nИсправьте максимальную дату.");
		fflush(stdin);
	}
	if (start_record == NULL) return 1;
	else
	{
		puts("-----------------------------------------------------------------------");
		puts("|Компания       |Представитель  |Пакет техники  |Цена      |Дата      |");
		puts("-----------------------------------------------------------------------");
		Purchase *p = start_record;
		while (p != NULL)
		{
			if (
					(
						(p->date[3] >= minm[0] && p->date[4] > minm[1]) ||
						(p->date[0] >= mind[0] && p->date[1] >= mind[1] && p->date[3] == minm[0] && p->date[4] == minm[1])
					)
					&&
					(
						(p->date[3] <= maxm[0] && p->date[4] < maxm[1]) ||
						(p->date[0] <= maxd[0] && p->date[1] <= maxd[1] && p->date[3] == maxm[0] && p->date[4] == maxm[1])
					)
				)
			{
				printf("|%-15s|%-15s|%-15s|%-10.0lf|%-10s|\n", p->supplier.name_company, p->supplier.name_user, p->res_technics, p->price, p->date);
				puts("-----------------------------------------------------------------------");
				flag++;
			}
			p = p->next;
		}
		if (flag != 0) return 0;
		else return 1;
	}
}

int delete_user_record(Purchase **start_record, Information **start, char key[])
{
	Purchase *p;
	p = search(*start_record, key);
	if (p == NULL) return 1;
	Information *i = *start;
	int res = 0;
	while (i != NULL)
	{
		if (strcmp(p->clip, i->login_str) == 0)
		{
			res++;
			break;
		}
		i = i->next;
	}
	if (res == 0) puts("Аккаунт не найден.");
	else
	{
		if (i == *start)
		{
			*start = (*start)->next;
		}
		else
		{
			Information *pre = *start;
			while (pre != NULL)
			{
				if (pre->next == i)
					break;            //нашли предшествующий узел и выходим из цикла
				pre = pre->next;
			}
			pre->next = i->next;
		}
		delete i;
	}
	delete_one_record(start_record, &p);
	return 0;
}
