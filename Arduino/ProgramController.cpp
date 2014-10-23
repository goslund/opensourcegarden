#include "ProgramController.h"
#include <cstddef>
#include <string>
#include "ArduinoFacade.h"
#include "ArduinosController.h"
#include <stdio.h>
#include <string.h>
#include "../Programs/NinthStreetOne.h"
bool ProgramController::instanceFlag = false;
ProgramController* ProgramController::instance = NULL;

ProgramController* ProgramController::getInstance() {
	if (!instanceFlag) {
		instance = new ProgramController();
		instanceFlag = true;
	}
	return instance;
}

std::string ProgramController::run(std::string command_str) {
	if(command_str.compare("exit") == 0) {
		return command_str;
	}

	//split string by :
	char* arduino_name;
	char* program_name;
	char* pin;

	char* pch;
	pch = strtok((char*) command_str.c_str(), ":");
	if (pch != NULL) {
		arduino_name = pch;
		pch = strtok(NULL, ":");
	}

	if (pch != NULL) {
		program_name = pch;
		pch = strtok(NULL, ":");
	}

	if (pch != NULL) {
		pin = pch;
		pch = strtok(NULL, ":");
	}

	ArduinoFacade* arduino = ArduinosController::getInstance()->findArduino((std::string) arduino_name);
	if (arduino == NULL) {
		return "arduino not found...";
	}

	if (program_name == NULL) {
		return "missing program argument to run";
	} else {
		if (strcmp(program_name, "NinthStreetOne") == 0) {
			NinthStreetOne* program = new NinthStreetOne(arduino);
			program->run();
		}
	}


	
  	return "whee";

}