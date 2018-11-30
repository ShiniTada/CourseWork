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
		puts("***** ������� ���� *****\n");
		puts("1)���� ��������������");
		puts("2)���� ������������");
		puts("0)�����\n");
		printf("����� >> ");
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
		default: puts("�������� �������� �� 0 �� 2");
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
		puts("***** ���� �������������� *****\n");
		puts("1)���������� ������ � ������");
		puts("2)������ ������� �� �������");
		puts("3)�������� ������ �������");
		puts("4)�������� ������������");
		puts("5)�������� ��������");
		puts("6)�������� ���������� ����������");
		puts("7)����� �������");
		puts("8)���������� �������");
		puts("9)�������� ������������ � ��� ������");
		puts("10)�������� ���� ������������� � �� �������");
		puts("11)��������� ��������� � ������");
		puts("0)�����\n");
		printf("����� >> ");
		i = test();
		system("cls");
		if (i == 0) break;
		else
		{
			switch (i)
			{
			case 1:  if (*access != 1) puts("������ ��� �������.\n");
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

			case 4: if (create_account(start) == 1) puts("������������ � ����� ������� ��� ������.\n");
					else puts("������������ ��������.\n");
					_getch();
					break;

			case 5: rating(*start_record);
				break;

			case 6: if (winner(*start_record) == 1) puts("���������� � ������� �� ������ �����������");
				_getch();
				break;

			case 7: printf("������� �������� �����������, ����� ������ �� �����: ");
				scanf("%s", key2);
				fflush(stdin);
				searc = search(*start_record, key2);
				if(search == NULL)
				{
					puts("������������ � ������� �� ������");
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
			case 9:	printf("������� �������� �����������, ��� ������ ����� �������: ");
				scanf("%s", key);
				fflush(stdin);
				if (delete_user_record(start_record, start, key) == 1)
				{
					puts("������������ � ������� �� ������");
				}
				else
				{
					puts("������������ � ������� ������.");
				}
				_getch();
				break;
			case 10: delete_records(start_record, &delet);
				delete_accounts(start, &delet);
				puts("������ �������������  � ������� ������.");
				_getch();
				break;
			case 11: close_account_file(*start);
				close_record_file(*start_record);
				_getch();
				break;
			default: puts("�������� �������� �� 0 �� 11");
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
		puts("***** ���� ������������ *****\n");
		puts("1)���������� ������ � ������");
		puts("2)�������� ������");
		puts("3)��������� ������");
		puts("4)�������� ��������");
		puts("5)�������� ���� ����� ������� �����������");
		puts("6)�������� ����������� ����������");
		puts("7)����� �������");
		puts("8)���������� �������");
		puts("9)��������� ��������� � ������");
		puts("0)�����\n");
		printf("����� >> ");
		i = test();
		system("cls");
		if (i == 0) break;
		else
		{
			switch (i)
			{
			case 1: if (*access != 1) puts("������ ��� �������.\n");
					else
					{
						open_data_file(start_record, start_tech, start);
						*access += 1;
					}
					_getch();
					break;
			case 2: if (check != 1) puts("������ ��� �������.\n�� �� ������ �������� ������ ����� ������.\n");
					else
					{
						check++;
						create = create_record(start_record, *start_tech, clip);
						if (create == 1) puts("������� �� ������� �����������. ��������� ����� ������������� ������� ��.\n");
						else puts("���� ������ ����� �� ���������.\n");
					}
					_getch();
					break;
			case 3: if (change_record(start_record, *start_tech, clip) == 1)
			{
				puts("������ ��� �� �������");
				_getch();
			}
					break;
			case 4:  rating(*start_record);
				break;
			case 5: if (sorting(*start_record) == 1)
						{
						puts("���������� � ������� �� ������ �����������.");
						}
						_getch();
				break;
			case 6:	if (my_record(*start_record, clip) == 1)
			{
				puts("������ ��� �� �������");
			}
					_getch();
					break;
			case 7: printf("������� �������� �����������, ����� ������ �� �����: ");
				scanf("%s", key2);
				fflush(stdin);
			
				searc = search(*start_record, key2);
				if (searc == NULL)
				{
					puts("������������ � ������� �� ������");
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
			default: puts("�������� �������� �� 0 �� 9");
				_getch();
				break;
			}
		}
	}
}
