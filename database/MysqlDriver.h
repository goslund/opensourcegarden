#ifndef MYSQLDRIVER_H
#define MYSQLDRIVER_H
#include <driver.h>
#include <connection.h>
#include <statement.h>
#include <prepared_statement.h>
#include <resultset.h>
#include <metadata.h>
#include <resultset_metadata.h>
#include <exception.h>
#include <warning.h>

#define DBHOST "tcp://127.0.0.1:3306"
#define USER "root"
#define PASSWORD "admin"
#define DATABASE "test"
class MysqlDriver {
public:
	NinthStreetOne(ArduinoFacade* controller) {
		this->controller = controller;
	};

	void run() {
		controller->sendMessage("digitalWrite:13:1");
	}

private:
	ArduinoFacade* controller;

};

#endif /* MYSQLDRIVER_H */