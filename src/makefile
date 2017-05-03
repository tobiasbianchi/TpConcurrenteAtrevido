CC = g++
CFLAGS = -pthread
ESTANDAR = -std=gnu++11
INCLUDES = -I core -I handlers -I modelo -I log
DEBUG = -g

make:
	$(CC) $(CFLAGS) $(ESTANDAR) $(INCLUDES) $(DEBUG) -o TP *.cpp core/*.cpp modelo/*.cpp log/*.cpp
