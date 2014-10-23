#ifndef NINTHSTREETONE_H
#define NINTHSTREETONE_H
#include "../Arduino/ArduinoFacade.h"
#include <boost/thread.hpp>

class NinthStreetOne {
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

#endif /* NINTHSTREETONE_H */