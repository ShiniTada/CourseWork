#include "Lists.h"

int sorting(Purchase *start_record)
{
	system("cls");
	if (start_record == NULL) return 1;
	puts("-----------------------------------------------------------------------");
	puts("|Компания       |Представитель  |Пакет техники  |Цена      |Дата      |");
	puts("-----------------------------------------------------------------------");
	Purchase *array = sorting_by_price(start_record);
	int size = length(start_record);
	int count = 0;
	for (int i = 0; i < size; i++) 
	{
		double price = array[i].price;
		Purchase *p = start_record;
		while (p != NULL)
		{
			if (p->price == price)
			{
					if (p->price != 10000000 && count < 5)
					{
						printf("|%-15s|%-15s|%-15s|%-10.0lf|%-10s|\n", p->supplier.name_company, p->supplier.name_user, p->res_technics, p->price, p->date);
						puts("-----------------------------------------------------------------------");
						count++;
						break;
					}
			}
			p = p->next;
		}
	}
	delete array;
	return 0;
}

int length(Purchase *start_record)
{
	Purchase *p = start_record;
	int count = 0;

	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
} 

Purchase* toArray(Purchase *start_record)
{
	Purchase *array = new Purchase[length(start_record)];
	int i = 0;
	Purchase *p = start_record;
	while (p != NULL) 
	{
		array[i++] = *p;
		p = p->next;
	}
	return array;
}

void bubbleSort(Purchase *arrayPtr, int length_array)
{
	Purchase  temp;
	bool exit = false;
	while (!exit)
	{
		exit = true;
		for (int i = 0; i < (length_array - 1); i++)
		{
			if (arrayPtr[i].price < arrayPtr[i + 1].price)
			{

				temp = arrayPtr[i];
				arrayPtr[i] = arrayPtr[i + 1];
				arrayPtr[i + 1] = temp;
				exit = false;
			}
		}
	}
}

Purchase *sorting_by_price(Purchase *start_record)
{
	Purchase *array = toArray(start_record);
	int size = length(start_record);
	bubbleSort(array, size);
	return array;
}