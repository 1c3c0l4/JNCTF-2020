CREATE DATABASE IF NOT EXISTS `JNCTF`
  DEFAULT CHARACTER SET utf8 COLLATE utf8_bin;
use JNCTF;
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `username` varchar(6) NOT NULL,
  `password` varchar(10) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO `users` VALUES ('admin','i2pos3cba');