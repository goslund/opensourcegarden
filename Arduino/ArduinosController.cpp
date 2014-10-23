#include "ArduinosController.h"
#include <cstddef>
#include <string>

bool ArduinosController::instanceFlag = false;
ArduinosController* ArduinosController::instance = NULL;

ArduinosController* ArduinosController::getInstance() {
	if (!instanceFlag) {
		instance = new ArduinosController();
		instanceFlag = true;
	}
	return instance;
}

std::string ArduinosController::run(std::string some_str) {
	return "test string";
}

ArduinoFacade* ArduinosController::findArduino(std::string name) {
	std::map<std::string,ArduinoFacade*>::iterator it;
	it = arduinos.find(name);
	return it->second;

}