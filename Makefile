TARGET = osgd
LDFLAGS = -lyaml-cpp
INCLUDES = -I/usr/local/include \
-IServer  \
-INeopixel \
-IArduino \
-I/usr/include/cppconn \
-I/usr/include/boost

#Arduino/ArduinosController.cpp
#Arduino/ProgramController.cpp

all:
	g++ main.cpp  $(INCLUDES) -lboost_thread  -lboost_date_time -lboost_filesystem -lboost_system -lpthread  -L/usr/include -L/usr/local/lib -L/usr/lib -lyaml-cpp -o $(TARGET) 

