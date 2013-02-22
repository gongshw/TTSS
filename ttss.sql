/*
 Navicat Premium Data Transfer

 Source Server         : localhost
 Source Server Type    : MySQL
 Source Server Version : 50528
 Source Host           : localhost
 Source Database       : ttss

 Target Server Type    : MySQL
 Target Server Version : 50528
 File Encoding         : utf-8

 Date: 02/22/2013 23:39:07 PM
*/

SET NAMES utf8;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
--  Table structure for `depart`
-- ----------------------------
DROP TABLE IF EXISTS `depart`;
CREATE TABLE `depart` (
  `did` int(11) NOT NULL AUTO_INCREMENT,
  `date` date NOT NULL,
  `remain_seats` int(11) NOT NULL,
  `tid` int(11) DEFAULT NULL,
  PRIMARY KEY (`did`),
  UNIQUE KEY `did_UNIQUE` (`did`),
  KEY `trainCons` (`tid`),
  CONSTRAINT `trainCons` FOREIGN KEY (`tid`) REFERENCES `train` (`tid`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

-- ----------------------------
--  Records of `depart`
-- ----------------------------
BEGIN;
INSERT INTO `depart` VALUES ('1', '2013-02-20', '66', '1');
COMMIT;

-- ----------------------------
--  Table structure for `station`
-- ----------------------------
DROP TABLE IF EXISTS `station`;
CREATE TABLE `station` (
  `sid` int(11) NOT NULL AUTO_INCREMENT,
  `city` varchar(45) NOT NULL,
  `name` varchar(45) NOT NULL,
  PRIMARY KEY (`sid`),
  UNIQUE KEY `sid_UNIQUE` (`sid`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
--  Records of `station`
-- ----------------------------
BEGIN;
INSERT INTO `station` VALUES ('1', '南京', '南京南站'), ('2', '南京', '南京站'), ('3', '扬州', '扬州站');
COMMIT;

-- ----------------------------
--  Table structure for `ticket`
-- ----------------------------
DROP TABLE IF EXISTS `ticket`;
CREATE TABLE `ticket` (
  `ticid` int(11) NOT NULL AUTO_INCREMENT,
  `number` int(11) NOT NULL,
  `did` int(11) NOT NULL,
  `consumer` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ticid`),
  UNIQUE KEY `ticid_UNIQUE` (`ticid`),
  KEY `departCons_idx` (`did`),
  CONSTRAINT `departCons` FOREIGN KEY (`did`) REFERENCES `depart` (`did`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- ----------------------------
--  Records of `ticket`
-- ----------------------------
BEGIN;
INSERT INTO `ticket` VALUES ('1', '33', '1', 'gongshw'), ('2', '34', '1', 'gongshw');
COMMIT;

-- ----------------------------
--  Table structure for `train`
-- ----------------------------
DROP TABLE IF EXISTS `train`;
CREATE TABLE `train` (
  `tid` int(11) NOT NULL AUTO_INCREMENT,
  `start_station_id` int(11) NOT NULL,
  `arrival_station_id` int(11) NOT NULL,
  `number` varchar(45) NOT NULL,
  `price` double NOT NULL,
  `seats` int(11) NOT NULL,
  `start_time` time NOT NULL,
  `arrival_time` time NOT NULL,
  PRIMARY KEY (`tid`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- ----------------------------
--  Records of `train`
-- ----------------------------
BEGIN;
INSERT INTO `train` VALUES ('1', '1', '3', 'K1123', '40', '100', '07:46:09', '12:00:00'), ('2', '2', '3', 'T1242', '59', '50', '00:00:00', '00:00:00');
COMMIT;

-- ----------------------------
--  Table structure for `user`
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `uid` int(11) NOT NULL AUTO_INCREMENT,
  `uname` varchar(45) NOT NULL,
  `password` varchar(128) NOT NULL,
  `real_name` varchar(45) NOT NULL,
  PRIMARY KEY (`uid`),
  UNIQUE KEY `uname_UNIQUE` (`uname`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8;

-- ----------------------------
--  Records of `user`
-- ----------------------------
BEGIN;
INSERT INTO `user` VALUES ('1', 'gongshw', '123', '龚世伟'), ('2', 'zsh', '123', '张书豪');
COMMIT;

-- ----------------------------
--  View structure for `depart_view`
-- ----------------------------
DROP VIEW IF EXISTS `depart_view`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `depart_view` AS select `depart`.`date` AS `date`,`depart`.`remain_seats` AS `remain_seats`,`train_view`.`arrival_station_city` AS `arrival_station_city`,`train_view`.`start_station_city` AS `start_station_city`,`train_view`.`arrival_station_name` AS `arrival_station_name`,`train_view`.`number` AS `number`,`train_view`.`price` AS `price`,`train_view`.`seats` AS `seats`,`train_view`.`start_time` AS `start_time`,`train_view`.`arrival_time` AS `arrival_time`,`train_view`.`start_station_name` AS `start_station_name`,`depart`.`did` AS `did` from (`depart` join `train_view` on((`depart`.`tid` = `train_view`.`tid`)));

-- ----------------------------
--  View structure for `ticket_view`
-- ----------------------------
DROP VIEW IF EXISTS `ticket_view`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `ticket_view` AS select `ticket`.`consumer` AS `consumer`,`ticket`.`did` AS `did`,`ticket`.`number` AS `ticket_number`,`depart_view`.`date` AS `date`,`depart_view`.`start_time` AS `start_time`,`depart_view`.`arrival_time` AS `arrival_time`,`depart_view`.`start_station_name` AS `start_station_name`,`depart_view`.`arrival_station_name` AS `arrival_station_name`,`depart_view`.`remain_seats` AS `remain_seats`,`depart_view`.`arrival_station_city` AS `arrival_station_city`,`depart_view`.`start_station_city` AS `start_station_city`,`depart_view`.`number` AS `number`,`depart_view`.`price` AS `price`,`depart_view`.`seats` AS `seats` from (`ticket` join `depart_view` on((`ticket`.`did` = `depart_view`.`did`)));

-- ----------------------------
--  View structure for `train_view`
-- ----------------------------
DROP VIEW IF EXISTS `train_view`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `train_view` AS select `train`.`number` AS `number`,`train`.`price` AS `price`,`train`.`seats` AS `seats`,`train`.`start_time` AS `start_time`,`train`.`arrival_time` AS `arrival_time`,`start_station`.`name` AS `start_station_name`,`arrival_station`.`name` AS `arrival_station_name`,`start_station`.`city` AS `start_station_city`,`arrival_station`.`city` AS `arrival_station_city`,`train`.`tid` AS `tid` from ((`train` join `station` `start_station` on((`train`.`start_station_id` = `start_station`.`sid`))) join `station` `arrival_station` on((`train`.`arrival_station_id` = `arrival_station`.`sid`)));

SET FOREIGN_KEY_CHECKS = 1;
