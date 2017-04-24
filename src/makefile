CC = g++
CFLAGS = -pthread
ESTANDAR = -std=gnu++11
INCLUDES = -I core -I handlers -I modelo
DEBUG = -g

make:
	$(CC) $(CFLAGS) $(ESTANDAR) $(INCLUDES) $(DEBUG) -o TP *.* core/*.cpp handlers/*.cpp modelo/*.cpp 
