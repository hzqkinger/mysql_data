/*************************************************************************
    > File Name: mysql_database.c
    > Author: 黄志强
    > Mail: 2069085311@qq.com 
    > Created Time: 2019年06月01日 星期六 20时22分51秒
 ************************************************************************/

#include<stdio.h>
#include<mysql/mysql.h>
#include<stdlib.h>//exit
#include<string.h>//strlen
void print(MYSQL *conn)/*{{{*/
{
	MYSQL_RES *res = mysql_use_result(conn);//得到二维结果集
	if(res)/*{{{*/
	{
		unsigned int num_fields = mysql_num_fields(res);//得到列数
		MYSQL_FIELD *colInfo = mysql_fetch_fields(res);//得到每一列的列信息
		for(int i = 0; i < num_fields ;++i)
			printf("%-10s",colInfo[i].name);
		printf("\n");

		MYSQL_ROW row;/*{{{*/
		while((row = mysql_fetch_row(res)) != NULL)//循环得到一行结果
		{
			for(int i = 0; i < num_fields;++i)
				printf("%-10s",row[i]);
			printf("\n");
		}/*}}}*/
	}/*}}}*/
}/*}}}*/

int main()/*{{{*/
{
	MYSQL *conn = mysql_init(NULL);//初始化MYSQL*指针
	if(!mysql_real_connect(conn,"localhost","root","123",NULL,0,NULL,0))/*{{{*/
	{
		printf("%d\t%s\n",mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	else
	{
		printf("charset: %s\n",mysql_character_set_name(conn));
		const char *set_charset = "set names utf8";//方法一
	//	mysql_real_query(conn,set_charset,strlen(set_charset));
		mysql_set_character_set(conn,"utf8");//方法二
	}/*}}}*/

//	if(mysql_query(conn,"show databases"))/*{{{*/
//	{
//		printf("%d\t%s\n",mysql_errno(conn),mysql_error(conn));
//		exit(2);
//	}
//	else
//		print(conn);
//	printf("\n");/*}}}*/
//	mysql_query(conn,"use hz_student");
//	mysql_query(conn,"select *from student");
//	print(conn);
	
	mysql_query(conn,"create database if not exists hzFromCApi default charset=utf8");
	if(mysql_query(conn,"use hzFromCApi"))
		printf("%d\t%s\n",mysql_errno(conn),mysql_error(conn));
	if(mysql_query(conn,"create table if not exists hz_stu2(id int comment \"学号\",name varchar(32) comment '姓名',grade float comment '总分数')charset=utf8;"))
		printf("%d\t%s\n",mysql_errno(conn),mysql_error(conn));
	if(mysql_query(conn,"insert into hz_stu2 values(2,'纸墙',87.5)"))
		printf("%d\t%s\n",mysql_errno(conn),mysql_error(conn));
	return 0;
}/*}}}*/
