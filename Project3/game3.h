#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdio.h>

//函数及符号的声明

//学生信息符号说明
#define MAX_NAME 20 //最长的名字
#define MAX_TELE 12 //最长电话
#define MAX_ADDR 20 //最长地址
#define MAX 100  //最大学生人数

struct date
{
	int year;
	int month;
	int day;
};
typedef struct Stu //typedef 作用：定义自己习惯的数据类型名称 例如：将struct Stu->Stu；
{
	char StuID[10];
	char name[MAX_NAME];
	char gender[10];
	struct date birth;
	char addr[MAX_ADDR];
	char tele[MAX_TELE];
	char email[30];
}Stu;

typedef struct Contact //同上，将数据类型struct Contact 重定义为 Contact
{
	Stu data[MAX];
	int sz_Stu;  //sz_Stu:已储存结构体Stu的数量
}Contact;



//函数的声明


//初始化con1
void InitContact(Contact* pc);
//学生信息维护功能
void Stu_mess_main(Contact* pc); //Contact是和int 一样是一种数据类型
//增删改查
void Stu_mess_add(Contact* pc);
void Stu_mess_dele(Contact* pc);
void Stu_mess_modify(Contact* pc);
void Stu_mess_enquire(Contact* pc);



//课程信息的维护 
//课程信息符号说明
#define MAX_CLA_NUMBER 10 //最长课程号
#define MAX_CLA_NAME 12 //最长课程名称
#define MAX_CLA 100 //可储存最大课程数量

typedef struct Cal
{
	char cla_number[MAX_CLA_NUMBER]; //cla_number 课程号
	char cla_name[MAX_CLA_NAME]; //课程名称
	double  credit; //credit 学分
}Cal;


typedef struct Contact2
{
	Cal data[MAX_CLA];
	int sz_Cla; //已储存的课程号数量
}Contact2;

void Cla_mess_main(Contact2* pc);
//初始化con2
void InitContact2(Contact2* pc);
void Cla_mess_add(Contact2* pc);
void Cla_mess_dele(Contact2* pc);
void Cla_mess_modify(Contact2* pc);
void Cla_mess_enquire(Contact2* pc);




//成绩信息维护
typedef struct Gra
{
	char cla_number[MAX_CLA_NUMBER];
	char cla_name[MAX_CLA_NAME];
	char StuID[10];
	char name[MAX_NAME];
	double grade; //课程成绩
}Gra;

typedef struct Contact3
{
	Gra data[MAX_CLA * MAX];  //最大学生人数*最大课程数量  （每位学生会有多门成绩）
	int sz_Gra; //记录已储存的成绩
}Contact3;

void Gra_mess_main(Contact3* pc);
void InitContact3(Contact3* pc); //初始化con3
void Gra_mess_add(Contact3* pc);
void Gra_mess_dele(Contact3* pc);
void Gra_mess_modify(Contact3* pc);
void Gra_mess_enquire(Contact3* pc);




//打印该学生所有课程成绩，并计算输出平均分
void Aver_gra_enquire(Contact3* pc);
void FindbyStuID_printfGra(Contact3* pc, char StuID[]); //通过学号查找并打印


//double sum_credit = 0;
//void Tot_cred_enquire(Contact2* pa, Contact3* pc);
//打印该学生所有课程成绩，和已取得的总学分
//void FindbyStuID_printfCredit(Contact2* pa, Contact3* pc, char StuID[]);


//课程成绩排名功能：输入课程编号，输出成绩排序
void Cla_gra_rank(Contact* pa, Contact3* pc);
void Rank_Grade(double rank[], int n); ////成绩排序


//学生平均分排名功能：计算每位学生的平均分，并排序输出
void Aver_gra_rank(Contact* pa, Contact3* pc);
double FindbyStuID_averageRank(Contact3* pc, char StuID[]); //通过学号查找算出平均分，再排序输出

// 读取保存数据
void Pre_read_main(Contact* con1, Contact2* con2, Contact3* con3);
void Exit_main(Contact* con1, Contact2* con2, Contact3* con3);
#pragma once
