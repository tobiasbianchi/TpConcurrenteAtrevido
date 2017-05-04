#include "Log.h"

bool Log::dbg;
std::string Log::path;
struct flock Log::fl;
int Log::fd;

void Log::init(std::string path, bool debug){
	dbg = debug;
	path = path;
	fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fd = open(  path.c_str(), O_CREAT|O_WRONLY, 0777 );
    if (fd == -1){
    	throw Error("Error al crear el lock del log",strerror(errno));
    }
}

void Log::info(std::string data){
	Log::writeData( INFO, data);
    std::cout << data << std::endl;
}

void Log::error(std::string data){
	Log::writeData( ERROR, data + ". Errno: " + strerror(errno) );
}

void Log::debug(std::string data){
	if (Log::dbg)
		Log::writeData( DEBUG, data);
}

ssize_t Log::writeData(std::string type, std::string data){
	std::string result = type + ":" + data + "\n";
    Log::tomarLock();
    lseek(Log::fd,0,SEEK_END );
    ssize_t wrote = write(Log::fd, static_cast<const void*>(result.c_str()), result.size());
    Log::liberarLock();
    if (wrote != result.size()){
    	throw Error("Error al escribir en archivo de log",strerror(errno));
    }
    return wrote;
}

void Log::tomarLock () {
    Log::fl.l_type = F_WRLCK;
    int success = fcntl ( Log::fd,F_SETLKW,&(Log::fl) );
    if (success == -1){
    	throw Error("Error al tomar lock de escritura",strerror(errno));
    }
}

void Log::liberarLock () {
    Log::fl.l_type = F_UNLCK;
    int success = fcntl ( Log::fd,F_SETLK,&(Log::fl) );
    if (success == -1){
    	throw Error("Error al liberar lock de escritura", strerror(errno));
    }
}

void Log::destroy(){
	close(Log::fd);
}