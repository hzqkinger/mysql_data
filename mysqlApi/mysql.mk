# libmysqlclient.a与libmysqlclient.so 都在/usr/lib64/mysql的目录下面
#
# <mysql/mysql.h>的头文件 在/usr/include的目录下面

src1 = mysql_select.c
src2 = mysql_create_tab_db.c

mysql:$(src2)
	g++ -o $@ $^ -lmysqlclient -L/usr/lib64/mysql
.PHONY:clean
clean:
	@rm -rf mysql

# make -f mysql.mk
# make -f mysql.mk clean
