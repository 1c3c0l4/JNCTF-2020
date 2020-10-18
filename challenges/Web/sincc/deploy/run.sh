#!/bin/bash

/etc/init.d/apache2 restart && /etc/init.d/ssh start
service mysqld start && echo 'service runing~'
mysql -uroot -ppassword < /tmp/sql.sql
rm -rf /tmp/sql.sql
sleep infinity
