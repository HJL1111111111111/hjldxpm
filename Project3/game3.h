#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdio.h>

//���������ŵ�����

//ѧ����Ϣ����˵��
#define MAX_NAME 20 //�������
#define MAX_TELE 12 //��绰
#define MAX_ADDR 20 //���ַ
#define MAX 100  //���ѧ������

struct date
{
	int year;
	int month;
	int day;
};
typedef struct Stu //typedef ���ã������Լ�ϰ�ߵ������������� ���磺��struct Stu->Stu��
{
	char StuID[10];
	char name[MAX_NAME];
	char gender[10];
	struct date birth;
	char addr[MAX_ADDR];
	char tele[MAX_TELE];
	char email[30];
}Stu;

typedef struct Contact //ͬ�ϣ�����������struct Contact �ض���Ϊ Contact
{
	Stu data[MAX];
	int sz_Stu;  //sz_Stu:�Ѵ���ṹ��Stu������
}Contact;



//����������


//��ʼ��con1
void InitContact(Contact* pc);
//ѧ����Ϣά������
void Stu_mess_main(Contact* pc); //Contact�Ǻ�int һ����һ����������
//��ɾ�Ĳ�
void Stu_mess_add(Contact* pc);
void Stu_mess_dele(Contact* pc);
void Stu_mess_modify(Contact* pc);
void Stu_mess_enquire(Contact* pc);



//�γ���Ϣ��ά�� 
//�γ���Ϣ����˵��
#define MAX_CLA_NUMBER 10 //��γ̺�
#define MAX_CLA_NAME 12 //��γ�����
#define MAX_CLA 100 //�ɴ������γ�����

typedef struct Cal
{
	char cla_number[MAX_CLA_NUMBER]; //cla_number �γ̺�
	char cla_name[MAX_CLA_NAME]; //�γ�����
	double  credit; //credit ѧ��
}Cal;


typedef struct Contact2
{
	Cal data[MAX_CLA];
	int sz_Cla; //�Ѵ���Ŀγ̺�����
}Contact2;

void Cla_mess_main(Contact2* pc);
//��ʼ��con2
void InitContact2(Contact2* pc);
void Cla_mess_add(Contact2* pc);
void Cla_mess_dele(Contact2* pc);
void Cla_mess_modify(Contact2* pc);
void Cla_mess_enquire(Contact2* pc);




//�ɼ���Ϣά��
typedef struct Gra
{
	char cla_number[MAX_CLA_NUMBER];
	char cla_name[MAX_CLA_NAME];
	char StuID[10];
	char name[MAX_NAME];
	double grade; //�γ̳ɼ�
}Gra;

typedef struct Contact3
{
	Gra data[MAX_CLA * MAX];  //���ѧ������*���γ�����  ��ÿλѧ�����ж��ųɼ���
	int sz_Gra; //��¼�Ѵ���ĳɼ�
}Contact3;

void Gra_mess_main(Contact3* pc);
void InitContact3(Contact3* pc); //��ʼ��con3
void Gra_mess_add(Contact3* pc);
void Gra_mess_dele(Contact3* pc);
void Gra_mess_modify(Contact3* pc);
void Gra_mess_enquire(Contact3* pc);




//��ӡ��ѧ�����пγ̳ɼ������������ƽ����
void Aver_gra_enquire(Contact3* pc);
void FindbyStuID_printfGra(Contact3* pc, char StuID[]); //ͨ��ѧ�Ų��Ҳ���ӡ


//double sum_credit = 0;
//void Tot_cred_enquire(Contact2* pa, Contact3* pc);
//��ӡ��ѧ�����пγ̳ɼ�������ȡ�õ���ѧ��
//void FindbyStuID_printfCredit(Contact2* pa, Contact3* pc, char StuID[]);


//�γ̳ɼ��������ܣ�����γ̱�ţ�����ɼ�����
void Cla_gra_rank(Contact* pa, Contact3* pc);
void Rank_Grade(double rank[], int n); ////�ɼ�����


//ѧ��ƽ�����������ܣ�����ÿλѧ����ƽ���֣����������
void Aver_gra_rank(Contact* pa, Contact3* pc);
double FindbyStuID_averageRank(Contact3* pc, char StuID[]); //ͨ��ѧ�Ų������ƽ���֣����������

// ��ȡ��������
void Pre_read_main(Contact* con1, Contact2* con2, Contact3* con3);
void Exit_main(Contact* con1, Contact2* con2, Contact3* con3);
#pragma once
