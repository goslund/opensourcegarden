#ifndef ARDUINOSCONTROLLER_H
#define	ARDUINOSCONTROLLER_H
#include <cstddef>
#include <string>
#include <yaml-cpp/yaml.h>
#include <driver.h>
#include "ArduinoFacade.h"
#include <map>

class ArduinosController {
public:
	static ArduinosController* getInstance();
	std::string run(std::string);
	ArduinoFacade* findArduino(std::string name);
private:
	ArduinosController() {
		YAML::Node file = YAML::LoadFile("version1.yml");
		// std::cout << file["config"];
		YAML::Node config = file["config"];
		std::string database_name = config["database"].as<std::string>();
		std::string username = config["username"].as<std::string>();
		std::string password = config["password"].as<std::string>();
		std::string url = config["hostname"].as<std::string>();
		driver = get_driver_instance();
		
		//std::cout << database_name;
		// for(YAML::const_iterator it = config.begin(); it != config.end(); ++it) {
			
		// 	YAML::Node node = it->second;
		// 	std::string name = node["name"].as<std::string>();
		// 	std::string port = node["port"].as<std::string>();

		// 	ArduinoFacade* facade = new ArduinoFacade(name, port);
		// 	arduinos.insert ( std::pair<std::string, ArduinoFacade*>(name, facade));
		// }
	}


	static bool instanceFlag;
	static ArduinosController* instance;
	map<std::string, ArduinoFacade*> arduinos;
};
#endif /* ARDUINOSCONTROLLER_H */