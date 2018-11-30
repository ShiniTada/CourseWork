#define _CRT_SECURE_NO_WARNINGS

#ifndef LISTS_H
#define LISTS_H

#include <stdio.h> 
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h> 

struct Technics
{
	char name_technics[15];		//�������� �������
	int guarantee;				//����������� ��������
	Technics *next;
};

struct Suppliers
{
	char name_company[15];		//�������� ��������
	char name_user[20];			//��� �������������
	Suppliers *next;			//���������
};

struct Purchase
{
	char clip[15];				//�������� ������ � ��������
	Suppliers supplier;			//�������� � ����������
	char res_technics[15];		//�������� � �������
	double price;				//���� �������
	char date[11];				//���� ������ ������
	Purchase *next;  			//���������
};

struct Admin
{
	char login_adm[20];			 //����� �������������� 
	char password_adm[20];		 //������ ��������������
};


struct Information
{
	char login_str[20];      //����� ������������ 
	char password_str[20];   //������ ������������  
	Information *next;  	 //���������
};

int test();
void admin(Information **, Purchase **, Technics **, int *);
void user(Information *, Information **, Purchase **, Technics **, int *);
int check_admin();
int check_user(Information **, Information *);

void open_data_file(Purchase **, Technics **, Information **);
int create_account(Information **);
int input_technics(Technics **, Purchase **);
void inf_technics(Technics *);
int create_record(Purchase **, Technics *, Information *);
void input_record_supplier(Purchase **);
int input_record_res_technics(Purchase **, Technics *);
int change_record(Purchase **, Technics *, Information *);

int delete_user_record(Purchase **, Information **, char[]);
void delete_one_record(Purchase **, Purchase **);
void delete_records(Purchase **, int *);
void delete_accounts(Information **, int *);
void delete_technics(Technics **);
void rating(Purchase *);


Purchase *sorting_by_price(Purchase *);
void bubbleSort(Purchase *, int );
Purchase* toArray(Purchase *);
int sorting(Purchase *);
void search_output(Purchase *);
Purchase *search(Purchase *, char []);
void filtration(Purchase *);
int filtering_by_price(Purchase *);
int filtering_by_date(Purchase *);

int length(Purchase *);

int winner(Purchase *);
int my_record(Purchase *, Information *);

void close_account_file(Information *);
int close_record_file(Purchase *);

#endif