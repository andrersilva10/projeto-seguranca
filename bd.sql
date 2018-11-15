create database keylogger;
use keylogger;

create table logs(
	id int auto_increment primary key,
	value varchar(5000),
	date datetime,
	ip varchar(20)
);