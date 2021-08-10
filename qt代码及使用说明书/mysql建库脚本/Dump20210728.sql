-- MySQL dump 10.13  Distrib 8.0.23, for Win64 (x86_64)
--
-- Host: localhost    Database: student_manager
-- ------------------------------------------------------
-- Server version	8.0.23

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `admin`
--

DROP TABLE IF EXISTS `admin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `admin` (
  `aid` int NOT NULL DEFAULT '0',
  `adminName` varchar(10) DEFAULT NULL,
  `password` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`aid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admin`
--

LOCK TABLES `admin` WRITE;
/*!40000 ALTER TABLE `admin` DISABLE KEYS */;
INSERT INTO `admin` VALUES (1,'admin','bdafe63038dfa0ac509cc80321e5433c'),(2,'admin2','bdafe63038dfa0ac509cc80321e5433c'),(3,'yjz','bdafe63038dfa0ac509cc80321e5433c');
/*!40000 ALTER TABLE `admin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `class`
--

DROP TABLE IF EXISTS `class`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `class` (
  `classId` varchar(20) NOT NULL,
  `className` varchar(20) DEFAULT NULL,
  `major` varchar(20) DEFAULT NULL,
  `sNum` int DEFAULT NULL,
  `master` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`classId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `class`
--

LOCK TABLES `class` WRITE;
/*!40000 ALTER TABLE `class` DISABLE KEYS */;
INSERT INTO `class` VALUES ('101','软件二班','软件工程',35,'张海英'),('102','软件三班','软件工程',30,'宋亮');
/*!40000 ALTER TABLE `class` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `course`
--

DROP TABLE IF EXISTS `course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `course` (
  `cId` varchar(20) NOT NULL DEFAULT '0',
  `object` varchar(20) DEFAULT NULL,
  `teacher` varchar(20) DEFAULT NULL,
  `time` varchar(20) DEFAULT NULL,
  `location` varchar(20) DEFAULT NULL,
  `period` varchar(20) DEFAULT NULL,
  `credit` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`cId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `course`
--

LOCK TABLES `course` WRITE;
/*!40000 ALTER TABLE `course` DISABLE KEYS */;
INSERT INTO `course` VALUES ('101','计算机网络','黄炜','大二下','一号楼B506','3-4节','4'),('102','Java程序设计','王美红','大二下','四号楼A402','1-4节','2'),('103','微积分I-1','李伟','大一上','一号楼A201','1-4节','4'),('104','微积分I-2','李伟','大一下','一号楼A202','1-4节','4'),('105','大学物理C','许清池','大一下','一号楼A504','9-11节','4'),('106','XML设计基础','宋亮','大二上','一号楼A104','5-6节','4'),('107','数据结构与算法','李贵林','大二上','一号楼B204','1-2节','4');
/*!40000 ALTER TABLE `course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `score`
--

DROP TABLE IF EXISTS `score`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `score` (
  `sid` varchar(20) NOT NULL,
  `cid` varchar(20) NOT NULL,
  `object` varchar(20) DEFAULT NULL,
  `score` varchar(20) DEFAULT NULL,
  `teacher` varchar(20) DEFAULT NULL,
  KEY `fk_teacher_idx` (`teacher`),
  KEY `fk_sId_idx` (`sid`),
  KEY `fk_sId_idx1` (`cid`),
  CONSTRAINT `fk_courseId` FOREIGN KEY (`sid`) REFERENCES `student` (`sId`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_sId` FOREIGN KEY (`cid`) REFERENCES `course` (`cId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `score`
--

LOCK TABLES `score` WRITE;
/*!40000 ALTER TABLE `score` DISABLE KEYS */;
INSERT INTO `score` VALUES ('11920192203642','102','Java程序设计','95','王美红'),('11920192203643','102','Java程序设计','99','王美红'),('11920192203642','103','微积分I-1','97','李伟'),('11920192203642','105','大学物理C','67','许清池'),('11920192203643','104','微积分I-2','95','李伟'),('11920192203642','104','微积分I-2','59','李伟');
/*!40000 ALTER TABLE `score` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `student` (
  `sId` varchar(20) NOT NULL,
  `name` varchar(20) DEFAULT NULL,
  `sex` varchar(20) DEFAULT NULL,
  `age` int DEFAULT NULL,
  `major` varchar(20) DEFAULT NULL,
  `class` varchar(20) DEFAULT NULL,
  `address` varchar(20) DEFAULT NULL,
  `phonenumber` varchar(20) DEFAULT NULL,
  `password` varchar(32) DEFAULT NULL,
  `status` varchar(20) DEFAULT '正常',
  PRIMARY KEY (`sId`),
  KEY `fk_classId_idx` (`class`),
  CONSTRAINT `fk_classId` FOREIGN KEY (`class`) REFERENCES `class` (`classId`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
INSERT INTO `student` VALUES ('11920192203642','袁佳哲','男',19,'软件工程','101','河南省','18603899634','bdafe63038dfa0ac509cc80321e5433c','正常'),('11920192203643','程昊天','男',19,'软件工程','102','湖北省','110','e10adc3949ba59abbe56e057f20f883e','冻结'),('11920192203644','徐荪睿','男',19,'软件工程','101','安徽省','120','e10adc3949ba59abbe56e057f20f883e','正常'),('11920192203645','谢建祥','男',19,'软件工程','101','福建省','119','e10adc3949ba59abbe56e057f20f883e','正常'),('11920192203646','李云龙','男',20,'网络安全','101','山东省','120','e10adc3949ba59abbe56e057f20f883e','正常');
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student_course`
--

DROP TABLE IF EXISTS `student_course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `student_course` (
  `sId` varchar(20) NOT NULL,
  `cId` varchar(20) NOT NULL,
  PRIMARY KEY (`sId`,`cId`),
  KEY `fk_cid_idx` (`cId`),
  CONSTRAINT `fk_c` FOREIGN KEY (`cId`) REFERENCES `course` (`cId`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_s` FOREIGN KEY (`sId`) REFERENCES `student` (`sId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student_course`
--

LOCK TABLES `student_course` WRITE;
/*!40000 ALTER TABLE `student_course` DISABLE KEYS */;
INSERT INTO `student_course` VALUES ('11920192203642','102'),('11920192203643','102'),('11920192203642','103'),('11920192203642','104'),('11920192203643','104'),('11920192203642','105');
/*!40000 ALTER TABLE `student_course` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-07-28  8:12:53
