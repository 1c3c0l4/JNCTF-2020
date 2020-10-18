#!/bin/bash

sed -i "s/flag{hello easy}/$1/g" /var/www/html/flag.php
