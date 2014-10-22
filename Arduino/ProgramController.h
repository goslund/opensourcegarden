#ifndef PROGRAMCONTROLLER_H
#define	PROGRAMCONTROLLER_H
#include <cstddef>
#include <string>

class ProgramController {
public:
	static ProgramController* getInstance();
	std::string run(std::string);

private:
	static bool instanceFlag;
	static ProgramController* instance;

};

#endif /* PROGRAMCONTROLLER_H */