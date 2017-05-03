#ifndef MUTEX	
#define MUTEX

#include <semaforo.h>
#include "semaforo.h"
#include "Log.h"

class Mutex : public Semaforo
{
public:
	Mutex(int idProyecto, const char *rutaArchivo = "/bin/bash");
};

#endif
