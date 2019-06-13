##########数据库的备份方法一#################################################
[xx] mysqldump -u root -p db_name > db_name_path

yyy> create database if not exits db_name;
yyy> use db_name;
yyy> source db_name_path;

##########数据库的备份方法二#################################################

[xx] ysqldump -u root -p -B db_name > db_name_path

yyy> source db_name_path;

#############################################################

