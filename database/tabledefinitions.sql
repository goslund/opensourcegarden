drop table if exists arduinos;

create table if not exists arduinos (
	id integer auto_increment primary key,
	name varchar(255) not null unique,
	port varchar(255) not null unique
);

insert into arduinos (name, port) values ("Aleph","/dev/ttyACM0");



drop table if exists device_pin_attachment;

create table if not exists device_pin_attachment (
	id integer auto_increment primary key,
	arduino_id integer not null,
	index ard_id (arduino_id),
	foreign key (arduino_id) references arduinos(id) on delete cascade,
	device_name varchar(255) not null unique,
	pin varchar(255) not null unique
);

insert into device_pin_attachment (device_name, pin, arduino_id) values ("Light1", "13", (
	select id from arduinos where name = "Aleph"
));

select * from device_pin_attachment;

create table if not exists programs (
	id integer auto_increment primary key,
	name varchar(255) not null unique,
	program longtext not null unique
)

