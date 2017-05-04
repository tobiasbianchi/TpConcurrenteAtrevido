
#ifndef TPCONCURRENTEATREVIDO_LOG
#define TPCONCURRENTEATREVIDO_LOG

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "definiciones.h"
#include "excepciones.h"
#include <errno.h>
#include <iostream>

class Log {
private:
	static std::string path;
	static bool dbg;
	static struct flock fl;
	static int fd;
	static void writeData(std::string type, std::string data);
	static void tomarLock();
	static void liberarLock();
public:
	static void init(std::string path, bool debug = false);
	static void info(std::string data);
	static void error(std::string data);
	static void debug(std::string data);
	static void destroy();
};

#endif