#include"game3.h"
#pragma warning( pop ) 


void InitContact(Contact* pc)
{
	pc->sz_Stu = 0;
	memset(pc->data, 0, sizeof(pc->data));
}

// 初始化读取信息 
void Pre_read_main(Contact* con1, Contact2* con2, Contact3* con3) {
	FILE* fp = NULL;
	// 读取学生信息
	fp = fopen("./stu.txt", "r");
	if (fp != NULL)
	{
		fscanf(fp, "%d\n", &con1->sz_Stu);
		for (int i = 0; i < con1->sz_Stu; i++) 
		{
			fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\n",
				con1->data[i].StuID, con1->data[i].name, con1->data[i].gender,
				con1->data[i].addr, con1->data[i].tele, con1->data[i].email,
				&con1->data[i].birth.year, &con1->data[i].birth.month, &con1->data[i].birth.day);
		}
	}
	fclose(fp);

	// 读取课程信息
	fp = fopen("./cal.txt", "r");
	if (fp != NULL)
	{
		fscanf(fp, "%d\n", &con2->sz_Cla);
		for (int i = 0; i < con2->sz_Cla; i++) {
			fscanf(fp, "%s\t%s\t%lf\n",
				con2->data[i].cla_number, con2->data[i].cla_name, &con2->data[i].credit);
		}
	}
	fclose(fp);

	// 读取成绩信息
	fp = fopen("./gra.txt", "r");
	if (fp != NULL)
	{
		fscanf(fp, "%d\n", &con3->sz_Gra);
		for (int i = 0; i < con3->sz_Gra; i++) {
			fscanf(fp, "%s\t%s\t%s\t%s\t%lf\n",
				con3->data[i].cla_number, con3->data[i].cla_name,
				con3->data[i].StuID, con3->data[i].name, &con3->data[i].grade);
		}
	}
	fclose(fp);
}

//退出系统
void Exit_main(Contact* con1, Contact2* con2, Contact3* con3) {
	FILE* fp = NULL;

	// 保存学生信息
	fp = fopen("./stu.txt", "w");
	char num[10];
	sprintf(num, "%d", con1->sz_Stu);
	fprintf(fp, num);
	fputc('\n', fp);
	for (int i = 0; i < con1->sz_Stu; i++) {
		fprintf(fp, con1->data[i].StuID);
		fputc('\t', fp);
		fprintf(fp, con1->data[i].name);
		fputc('\t', fp);
		fprintf(fp, con1->data[i].gender);
		fputc('\t', fp);
		fprintf(fp, con1->data[i].addr);
		fputc('\t', fp);
		fprintf(fp, con1->data[i].tele);
		fputc('\t', fp);
		fprintf(fp, con1->data[i].email);
		fputc('\t', fp);
		char year[5], month[5], day[5];
		sprintf(year, "%d", con1->data[i].birth.year);
		sprintf(month, "%d", con1->data[i].birth.month);
		sprintf(day, "%d", con1->data[i].birth.day);
		fprintf(fp, year);
		fputc('\t', fp);
		fprintf(fp, month);
		fputc('\t', fp);
		fprintf(fp, day);
		fputc('\n', fp);
	}
	fclose(fp);


	// 保存课程信息
	fp = fopen("./cal.txt", "w");
	sprintf(num, "%d", con2->sz_Cla);
	fprintf(fp, num);
	fputc('\n', fp);
	for (int i = 0; i < con2->sz_Cla; i++) {
		fprintf(fp, con2->data[i].cla_number);
		fputc('\t', fp);
		fprintf(fp, con2->data[i].cla_name);
		fputc('\t', fp);
		char credit[10];
		sprintf(credit, "%f", con2->data[i].credit);
		fprintf(fp, credit);
		fputc('\n', fp);
	}
	fclose(fp);

	
	// 保存成绩信息
	fp = fopen("./gra.txt", "w");
	sprintf(num, "%d", con3->sz_Gra);
	fprintf(fp, num);
	fputc('\n', fp);
	for (int i = 0; i < con3->sz_Gra; i++) {
		fprintf(fp, con3->data[i].cla_number);
		fputc('\t', fp);
		fprintf(fp, con3->data[i].cla_name);
		fputc('\t', fp);
		fprintf(fp, con3->data[i].StuID);
		fputc('\t', fp);
		fprintf(fp, con3->data[i].name);
		fputc('\t', fp);
		char grade[10];
		sprintf(grade, "%f", con3->data[i].grade);
		fprintf(fp, grade);
		fputc('\n', fp);
	}
	fclose(fp);
}

//学生信息维护功能
void Stu_mess_main(Contact* pc)
{
	printf("*********************************************************\n");
	printf("*************       1.学生信息增加           ************\n");
	printf("*************       2.学生信息删除           ************\n");
	printf("*************       3.学生信息修改           ************\n");
	printf("*************       4.学生信息查询           ************\n");
	printf("*********************************************************\n");
	printf("请输入您的选择：\n");
	int choice1;
	scanf_s("%d", &choice1);
	switch (choice1)
	{
	case 1: Stu_mess_add(pc); break;
	case 2: Stu_mess_dele(pc); break;
	case 3: Stu_mess_modify(pc); break;
	case 4: Stu_mess_enquire(pc); break;
	deflault: printf("选项不存在，请重新选择"); break;
	}
}


//性别，出生年月，地址，电话，E-mail

 int FindbyStuID(Contact* pc, char StuID[]) //通过学号查找
{
	int i = 0;
	for (i = 0; i < pc->sz_Stu; i++)
	{
		if (strcmp(pc->data[i].StuID, StuID) == 0)
		{
			return i;
		}
	}
	return -1; //找不到
}
void Stu_mess_add(Contact* pc)
{
	if (pc->sz_Stu == MAX)
	{
		printf("学生人数以满，无法添加\n");
		return;
	}

	char StuID[10] = { 0 };
	printf("请输入第%d位学生的学号：\n", pc->sz_Stu + 1);//第几位学生从1开始计数,而stu[]从零开始，需要加1
	scanf("%s", StuID);
	//判断学号是否重复
	int pos = FindbyStuID(pc, StuID);
	if (pos != -1)
	{
		printf("该学号已存在\n");
		return;
	}
	else
	{
		printf("请输入第%d位学生学号:\n", pc->sz_Stu + 1);
		scanf("%s", pc->data[pc->sz_Stu].StuID);
		printf("请输入第%d位学生姓名:\n", pc->sz_Stu + 1);
		scanf("%s", pc->data[pc->sz_Stu].name);
		printf("请输入第%d位学生性别:\n", pc->sz_Stu + 1);
		scanf("%s", pc->data[pc->sz_Stu].gender);
		printf("请输入第%d位学生出生年月:\n", pc->sz_Stu + 1);
		scanf("%d%d%d", &(pc->data[pc->sz_Stu].birth.year), &(pc->data[pc->sz_Stu].birth.month), &(pc->data[pc->sz_Stu].birth.day));
		printf("请输入第%d位学生地址:\n", pc->sz_Stu + 1);
		scanf("%s", pc->data[pc->sz_Stu].addr);
		printf("请输入第%d位学生电话:\n", pc->sz_Stu + 1);
		scanf("%s", pc->data[pc->sz_Stu].tele);
		printf("请输入第%d位学生电子邮件:\n", pc->sz_Stu + 1);
		scanf("%s", pc->data[pc->sz_Stu].email);
		pc->sz_Stu++;
		printf("添加完成！！！\n");
	}

}


void Stu_mess_dele(Contact* pc)
{
	char StuID[10] = { 0 };
	if (pc->sz_Stu == 0)
	{
		printf("学生信息为空，无需删除\n");
		return;
	}

	printf("请输入您想要删除的学生学号：\n");
	scanf("%s", StuID);

	int pos = FindbyStuID(pc, StuID);
	if (pos == -1)
	{
		printf("要删除的学号不存在\n");
		return;
	}
	int i = 0;
	for (i = pos; i < pc->sz_Stu - 1; i++)
	{
		pc->data[i] = pc->data[i + 1];
	}
	pc->sz_Stu--;
	printf("删除成功\n");
}

void Stu_mess_modify(Contact* pc)
{
	char StuID[10] = { 0 };
	printf("请输入您想要修改的学生学号：\n");
	scanf("%s", StuID);
	int pos = FindbyStuID(pc, StuID);
	if (pos == -1)
	{
		printf("要修改的学生不存在\n");
		return;
	}
	else
	{
		printf("请输入第%d名学生学号:\n", pc->sz_Stu );
		scanf("%s", pc->data[pc->sz_Stu].StuID);
		printf("请输入第%d名学生姓名:\n", pc->sz_Stu );
		scanf("%s", pc->data[pc->sz_Stu].name);
		printf("请输入第%d名学生性别:\n", pc->sz_Stu);
		scanf("%s", pc->data[pc->sz_Stu].gender);
		printf("请输入第%d名学生出生年月:\n", pc->sz_Stu );
		scanf("%d%d%d", &(pc->data[pc->sz_Stu].birth.year), &(pc->data[pc->sz_Stu].birth.month), &(pc->data[pc->sz_Stu].birth.day));
		printf("请输入第%d名学生地址:\n", pc->sz_Stu );
		scanf("%s", pc->data[pc->sz_Stu].addr);
		printf("请输入第%d名学生电话:\n", pc->sz_Stu);
		scanf("%s", pc->data[pc->sz_Stu].tele);
		printf("请输入第%d名学生电子邮件:\n", pc->sz_Stu);
		scanf("%s", pc->data[pc->sz_Stu].email);
		printf("修改成功！\n");
	}
}


void Stu_mess_enquire(Contact* pc)
{
	char StuID[10] = { 0 };
	printf("请输入您想要查询的学生学号：\n");
	scanf("%s", StuID);
	int pos = FindbyStuID(pc, StuID);
	if (pos == -1)
	{
		printf("要查询的学生不存在\n");
		return;
	}
	else
	{
		printf("该学生学号为：%s\n", pc->data[pos].StuID);
		printf("姓名：%s\n", pc->data[pos].name);
		printf("性别：%s\n", pc->data[pos].gender);
		printf("出生年月：%d%d%d\n", pc->data[pos].birth.year, pc->data[pos].birth.month, pc->data[pos].birth.day);
		printf("地址：%s\n", pc->data[pos].addr);
		printf("电话：%s\n", pc->data[pos].tele);
		printf("电子邮件：%s\n", pc->data[pos].email);
	}
}









//课程信息包括：课程号，课程名称，学分。成绩信息包括：课程号、课程名称、学号、姓名、成绩。
//设计学生成绩系统，




//学生信息维护功能

void InitContact2(Contact2* pc)
{
	pc->sz_Cla = 0;
	memset(pc->data, 0, sizeof(pc->data));
}
void Cla_mess_main(Contact2* pc)
{
	printf("*********************************************************\n");
	printf("*************       1.课程信息增加           ************\n");
	printf("*************       2.课程信息删除           ************\n");
	printf("*************       3.课程信息修改           ************\n");
	printf("*************       4.课程信息查询           ************\n");
	printf("*********************************************************\n");
	printf("请输入您的选择：\n");
	int choice1;
	scanf_s("%d", &choice1);
	switch (choice1)
	{
	case 1: Cla_mess_add(pc); break;
	case 2: Cla_mess_dele(pc); break;
	case 3: Cla_mess_modify(pc); break;
	case 4: Cla_mess_enquire(pc); break;
	deflault: printf("选项不存在，请重新选择"); break;
	}
}

static int FindbyCla_number(Contact2* pc, char cla_number[]) //通过课程号查找
{
	int i = 0;
	for (i = 0; i < pc->sz_Cla; i++)
	{
		if (strcmp(pc->data[i].cla_number, cla_number) == 0)
		{
			return i;
		}
	}
	return -1; //找不到
}
//课程信息包括：课程号，课程名称，学分。
void Cla_mess_add(Contact2* pc)
{
	if (pc->sz_Cla == MAX_CLA)
	{
		printf("课程数量已满，无法添加\n");
		return;
	}
	else
	{
		char cla_number[MAX_CLA_NUMBER] = { 0 };
		printf("请输入第%d个课程号：\n", pc->sz_Cla + 1);
		scanf("%s", cla_number);
		//判断学号是否重复
		int pos = FindbyCla_number(pc, cla_number);
		if (pos != -1)
		{
			printf("该课程已存在\n");
			return;
		}
		printf("请输入第%d个课程号:\n", pc->sz_Cla + 1);
		scanf("%s", pc->data[pc->sz_Cla].cla_number);
		printf("请输入第%d个课程号名称:\n", pc->sz_Cla + 1);
		scanf("%s", pc->data[pc->sz_Cla].cla_name);
		printf("请输入第%d个课程号的学分:\n", pc->sz_Cla + 1);
		scanf("%lf", &(pc->data[pc->sz_Cla].credit));
		pc->sz_Cla++;
		printf("添加完成！\n");
	}

}


void Cla_mess_dele(Contact2* pc)
{
	if (pc->sz_Cla == 0)
	{
		printf("课程信息为空，无需删除\n");
		return;
	}
	else
	{
		char cla_number[MAX_CLA_NUMBER] = { 0 };
		printf("请输入您想要删除的课程号：\n");
		scanf("%s", cla_number);
		int pos = FindbyCla_number(pc, cla_number);
		if (pos == -1)
		{
			printf("要删除的课程不存在\n");
			return;
		}
		else
		{
			int i = 0;
			for (i = pos; i < pc->sz_Cla - 1; i++)
			{
				pc->data[i] = pc->data[i + 1];
			}
			pc->sz_Cla--;
			printf("删除成功\n");
		}
	}
}

void Cla_mess_modify(Contact2* pc)
{
	char cla_number[MAX_CLA_NUMBER] = { 0 };
	printf("请输入您想要修改的课程号：\n");
	scanf("%s", cla_number);
	int pos = FindbyCla_number(pc, cla_number);
	if (pos == -1)
	{
		printf("要修改的课程不存在\n");
		return;
	}
	else
	{
		printf("请输入第%d个课程号:\n", pc->sz_Cla);
		scanf("%s", pc->data[pc->sz_Cla].cla_number);
		printf("请输入第%d个课程号名称:\n", pc->sz_Cla);
		scanf("%s", pc->data[pc->sz_Cla].cla_name);
		printf("请输入第%d个课程号的学分:\n", pc->sz_Cla);
		scanf("%lf", &(pc->data[pc->sz_Cla].credit));
		printf("修改成功！\n");
	}
}


void Cla_mess_enquire(Contact2* pc)
{
	char cla_number[MAX_CLA_NUMBER] = { 0 };
	printf("请输入您想要查询的课程号：\n");
	scanf("%s", cla_number);
	int pos = FindbyCla_number(pc, cla_number);
	if (pos == -1)
	{
		printf("要查询的课程不存在\n");
		return;
	}
	else
	{
		printf("该课程号为：%s\n", pc->data[pos].cla_number);
		printf("课程名称：%s\n", pc->data[pos].cla_name);
		printf("学分：%lf\n", pc->data[pos].credit);
	}

}









//学生成绩维护功能
//成绩信息包括：课程号、课程名称、学号、姓名、成绩。




void Gra_mess_main(Contact3* pc)
{
	printf("*********************************************************\n");
	printf("*************       1.成绩信息增加           ************\n");
	printf("*************       2.成绩信息删除           ************\n");
	printf("*************       3.成绩信息修改           ************\n");
	printf("*************       4.成绩信息查询           ************\n");
	printf("*********************************************************\n");
	printf("请输入您的选择：\n");
	int choice1;
	scanf("%d", &choice1);
	switch (choice1)
	{
	case 1: Gra_mess_add(pc); break;
	case 2: Gra_mess_dele(pc); break;
	case 3: Gra_mess_modify(pc); break;
	case 4: Gra_mess_enquire(pc); break;
	deflault: printf("选项不存在，请重新选择"); break;
	}
}

 int FindbyStuID3(Contact3* pc, char StuID[])
{
	int i = 0;
	for (i = 0; i < pc->sz_Gra; i++)
	{
		if (strcmp(pc->data[i].StuID, StuID) == 0)
		{
			return i;
		}
	}
	return -1; //找不到
}
 int FindbyCla_number3(Contact3* pc, char cla_number[])
{
	int i = 0;
	for (i = 0; i < pc->sz_Gra; i++)
	{
		if (strcmp(pc->data[i].cla_number, cla_number) == 0)
		{
			return i;
		}
	}
	return -1; //找不到
}
//成绩信息包括：课程号、课程名称、学号、姓名、成绩。
void InitContact3(Contact3* pc)
{
	pc->sz_Gra = 0;
	memset(pc->data, 0, sizeof(pc->data));
}
void Gra_mess_add(Contact3* pc)
{
	if (pc->sz_Gra == MAX_CLA * MAX)
	{
		printf("成绩信息数量已满，无法添加\n");
		return;
	}
	char StuID[10] = { 0 };
	char cla_number[MAX_CLA_NUMBER] = { 0 };
	printf("请输入第%d位学生的学号：\n", pc->sz_Gra + 1);
	scanf("%s", StuID);
	printf("请输入第%d位该学生的课程号：\n", pc->sz_Gra + 1);
	scanf("%s", cla_number);
	//判断学号是否重复
	int pos = FindbyStuID3(pc, StuID);
	int pospos = FindbyCla_number3(pc, cla_number);

	if (pos != -1 && pospos != -1 && pos == pospos)
	{
		printf("该学生该门课程成绩信息已存在\n");
		return;
	}
	else
	{
		printf("请输入该学生学号:\n");
		scanf("%s", pc->data[pc->sz_Gra].StuID);
		printf("请输入该课程号:\n");
		scanf("%s", pc->data[pc->sz_Gra].cla_number);
		printf("请输入该课程号名称:\n");
		scanf("%s", pc->data[pc->sz_Gra].cla_name);
		printf("请输入该学生姓名:\n");
		scanf("%s", pc->data[pc->sz_Gra].name);
		printf("请输入该门课成绩:\n");
		scanf("%lf", &(pc->data[pc->sz_Gra].grade));
		pc->sz_Gra++;
		printf("添加完成！\n");
	}

}


void Gra_mess_dele(Contact3* pc)
{
	if (pc->sz_Gra == 0)
	{
		printf("成绩信息为空，无需删除\n");
		return;
	}

	char StuID[10] = { 0 };
	char cla_number[MAX_CLA_NUMBER] = { 0 };
	printf("请输入您想要删除成绩的学号和课程号：\n");
	scanf("%s%s", StuID, cla_number);

	int pos = FindbyStuID3(pc, StuID);
	int pospos = FindbyCla_number3(pc, cla_number);

	if (pos == -1 && pospos == -1)
	{
		printf("该学生该门课程成绩信息不存在\n");
		return;
	}
	if (pos == pospos)
	{
		int i = 0;
		for (i = pos; i < pc->sz_Gra - 1; i++)
		{
			pc->data[i] = pc->data[i + 1];
		}
		pc->sz_Gra--;
		printf("删除成功\n");
	}
}

void Gra_mess_modify(Contact3* pc)
{
	char StuID[10] = { 0 };
	char cla_number[MAX_CLA_NUMBER] = { 0 };
	printf("请输入第%d位学生的学号：\n", pc->sz_Gra);
	scanf("%s", StuID);
	printf("请输入第%d位该学生的课程号：\n", pc->sz_Gra);
	scanf("%s", cla_number);
	//判断学号是否重复
	int pos = FindbyStuID3(pc, StuID);
	int pospos = FindbyCla_number3(pc, cla_number);

	if (pos == -1 && pospos == -1)
	{
		printf("该学生该门课程成绩信息不存在\n");
		return;
	}
	else
	{
		printf("请输入该学生学号:\n");
		scanf("%s", pc->data[pc->sz_Gra].StuID);
		printf("请输入该课程号:\n");
		scanf("%s", pc->data[pc->sz_Gra].cla_number);
		printf("请输入该课程号名称:\n");
		scanf("%s", pc->data[pc->sz_Gra].cla_name);
		printf("请输入该学生姓名:\n");
		scanf("%s", pc->data[pc->sz_Gra].name);
		printf("请输入该门课成绩:\n");
		scanf("%lf", &(pc->data[pc->sz_Gra].grade));
		pc->sz_Gra++;
		printf("修改成功！\n");
	}
}


void Gra_mess_enquire(Contact3* pc)
{
	char StuID[10] = { 0 };
	char cla_number[MAX_CLA_NUMBER] = { 0 };
	printf("请输入第%d位学生的学号：\n", pc->sz_Gra);
	scanf("%s", StuID);
	printf("请输入第%d位该学生的课程号：\n", pc->sz_Gra);
	scanf("%s", cla_number);
	//判断学号是否重复
	int pos = FindbyStuID3(pc, StuID);
	int pospos = FindbyCla_number3(pc, cla_number);

	if (pos == -1 && pospos == -1)
	{
		printf("该学生该门课程成绩信息不存在\n");
		return;
	}
	if (pos == pospos)
	{
		printf("请输入该学生学号:%s\n", pc->data[pos].StuID);
		printf("请输入该课程号:%s\n", pc->data[pos].cla_number);
		printf("请输入该课程号名称:%s\n", pc->data[pos].cla_name);
		printf("请输入该学生姓名:%s\n", pc->data[pos].name);
		printf("请输入该门课成绩:%lf\n", pc->data[pos].grade);
	}
}

//统计分析功能：输入学生学号，打印该学生所有课程成绩，并计算输出平均分

double average = 0;

void FindbyStuID_printfGra(Contact3* pc, char StuID[])
{
	double sum_grade = 0;
	int count = 0;
	for (int i = 0; i < pc->sz_Gra; i++)
	{
		if (strcmp(pc->data[i].StuID, StuID) == 0)
		{
			printf("%s成绩：%lf\n", pc->data[i].cla_name, pc->data[i].grade);
			count++;
			sum_grade += pc->data[i].grade;
		}
	}
	average = sum_grade / count;
	return;
}



void Aver_gra_enquire(Contact3* pc)
{
	char StuID[10] = { 0 };
	printf("请输入学生的学号：\n");
	scanf("%s", StuID);
	int pos = FindbyStuID3(pc, StuID);
	if (pos == -1)
	{
		printf("该学号不存在\n");
		return;
	}
	else
	{
		FindbyStuID_printfGra(pc, StuID);
		printf("平均分：%lf\n", average);
	}

}




/*课程成绩排名功能：输入课程编号，输出成绩排序
	学生平均分排名功能：计算每位学生的平均分，并排序输出*/
void Rank_Grade(double rank[], int n)
{
	int i, j;
	double temp;
	for (i = 1; i < n; i++)
	{
		for (j = 0; j < n - i; j++)
		{
			if (rank[j] > rank[j + 1])//相邻两个数如果逆序，则交换位置
			{
				temp = rank[j];
				rank[j] = rank[j + 1];
				rank[j + 1] = temp;
			}
		}
	}
	return;
}
void Cla_gra_rank(Contact* pa, Contact3* pc)
{
	char cla_number[MAX_CLA_NUMBER] = { 0 };
	double rank_grade[MAX] = { 0 };
	printf("请输入课程号：\n");
	scanf("%s", cla_number);
	int i = 0;
	for (i = 0; i < pc->sz_Gra; i++)
	{
		if (strcmp(pc->data[i].cla_number, cla_number) == 0)
		{
			rank_grade[i] = pc->data[i].grade;
		}
	}
	Rank_Grade(rank_grade, pa->sz_Stu);
	for (i = pa->sz_Stu - 1; i >= 0; i--)
	{
		printf("%d: %lf\n", rank_grade[i]);
	}
	return;
}


double FindbyStuID_averageRank(Contact3* pc, char StuID[])
{
	int i = 0;
	int count = 0;
	double average_part = 0;
	int sum_grade = 0;
	for (i = 0; i < pc->sz_Gra; i++)
	{
		if (strcmp(pc->data[i].StuID, StuID) == 0)
		{
			count++;
			sum_grade += pc->data[i].grade;
			break;
		}
	}
	average_part = sum_grade / count;
	return average_part;
}
void Aver_gra_rank(Contact* pa, Contact3* pc)
{
	int j = 0;
	double rank_average[MAX] = { 0 };
	for (j = 0; j < pa->sz_Stu; j++)
	{
		rank_average[j] = FindbyStuID_averageRank(pc, pa->data[j].StuID);
	}
	Rank_Grade(rank_average, pa->sz_Stu);
	for (j = pa->sz_Stu - 1; j >= 0; j--)
	{
		printf("%d: %lf\n", pa->sz_Stu - j, rank_average[j]);
	}
	return;
}