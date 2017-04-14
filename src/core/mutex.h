#ifndef MUTEX	
#define MUTEX

#include "semaforo.h"

class Mutex : public Semaforo
{
public:
	Mutex(int idProyecto);
};

#endif
