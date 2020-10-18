DROP DATABASE IF EXISTS `security`;
CREATE DATABASE `security`;
USE `security`;
CREATE TABLE `users` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Id`)
);
INSERT INTO `users` VALUES (1,'admin','7asg2m16b28j');
