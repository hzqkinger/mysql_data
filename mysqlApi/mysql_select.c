/*************************************************************************
    > File Name: mysql_select.c
    > Author: 黄志强
    > Mail: 2069085311@qq.com 
    > Created Time: 2019年05月27日 星期一 18时20分58秒
 ************************************************************************/

#include<stdio.h>
#include<mysql/mysql.h>
//<mysql/mysql.h>这个头文件在/usr/include中
#include<stdlib.h>//exit
#include<string.h>//strlen

//有乱码问题，不能打印出中文
int main()
{
	MYSQL *conn;
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn,"localhost","root","123","hz_student",0,NULL,0))
	{
		printf("%s:\t%d\n",mysql_error(conn),mysql_errno(conn));
		exit(1);//#include<stdlib.h>
	}
	else
	{
		printf("connect success\n");

		//跟字符集相关的函数(保证不乱码)
	//	printf("charset:\t%s\n",mysql_character_set_name(conn));
	//	mysql_set_character_set(conn,"utf8");//方法一
	//	printf("charset:\t%s\n",mysql_character_set_name(conn));

		printf("charset:\t%s\n",mysql_character_set_name(conn));
		mysql_query(conn,"set names utf8");//方法二
		printf("charset:\t%s\n",mysql_character_set_name(conn));

		MY_CHARSET_INFO info;//得到字符集相关的info
		mysql_get_character_set_info(conn,&info);
		printf("%d\n%d\n%s\n%s\n%s\n%s\n",info.number,info.state,info.csname,info.name,\
											info.comment,info.dir);
	}

	//mysql_query执行语句成功后返回0，失败返回非零
	if(mysql_query(conn,"select *from student order by math limit 2,4"))//执行语句
		printf("error making query:%s\n",mysql_error(conn));
	else{
		printf("query made...\n");
		MYSQL_RES *res = mysql_use_result(conn);//返回并且存储执行语句返回的结果集
		if(res){
			unsigned int num_fields = mysql_num_fields(res);//得到res结果集的列数

			MYSQL_FIELD *colInfo = mysql_fetch_fields(res);//得到res结果集每一列的信息
			for(int i = 0;i < num_fields;++i)
				printf("%-8s%-9d",colInfo[i].name,colInfo[i].type);//这里只打印出列名
				printf("\n");

			for(int i = 0;i < num_fields;++i)
				printf("%-17s",mysql_fetch_field_direct(res,i)->name);//得到res结果集中指定列的信息
				printf("\n");

			MYSQL_ROW row;
			while((row = mysql_fetch_row(res)) != NULL)//从res结果集中一行行检索
			{
				unsigned long *len = mysql_fetch_lengths(res);//得到当前检索行的每列所占字节数

				for(int i = 0; i < num_fields;++i)
					printf("%d , %-13s",len[i],row[i]);
				printf("\n");
			}
		}
		mysql_free_result(res);
	}
	mysql_close(conn);

	return 0;
}
