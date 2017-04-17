#ifndef MUTEX	
#define MUTEX

#include "semaforo.h"

class Mutex : public Semaforo
{
public:
	Mutex(int idProyecto, bool iniciarBloqueado = false, const char *rutaArchivo = "/bin/bash");
};

#endif
