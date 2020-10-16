#!/bin/bash

sed -i "s/flag{here_is_the_flag}/$1/g" /var/www/html/flag.php
