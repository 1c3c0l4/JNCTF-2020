FROM zita0212/apache-php-mysql8.0.19:2

RUN rm /var/www/html/index.php
COPY src/*.php /var/www/html/
ADD src/avatar /var/www/html/avatar
ADD src/css /var/www/html/css
ADD src/js /var/www/html/js
RUN chmod +777 /var/www/html/avatar
RUN apt-get update
COPY flag.txt /flag.txt
COPY run.sh /run.sh
COPY sql.sql /tmp/sql.sql
RUN chmod +x /run.sh

EXPOSE 80
EXPOSE 22

CMD ["/run.sh"]
