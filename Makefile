TARGET = osgd
LDFLAGS = -lyaml-cpp
INCLUDES = -I/usr/local/include \
-IServer  \
-INeopixel \
-IArduino \
-I/usr/include/cppconn \


#Arduino/ArduinosController.cpp
#Arduino/ProgramController.cpp

all:
	g++ main.cpp  $(INCLUDES) -lboost_thread-mt  -lboost_date_time -lboost_filesystem -lboost_system -lpthread   -L/usr/local/lib -L/usr/lib -lyaml-cpp -lserial  -o $(TARGET) 

