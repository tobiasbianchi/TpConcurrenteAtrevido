#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "Excepciones.h"
#include <errno.h>
#include <string>
#include "Definiciones.h"

class Semaforo
{
private:
	int id;
public:

	Semaforo(int idProyecto)
	{
		key_t clave = ftok("/bin/bash", idProyecto);

		if(clave == -1)
			throw Error("Generacion de clave", strerror(errno));

		id = semget(clave, 0, IPC_CREAT);

		if(id == -1)
			throw Error("Creacion del semaforo", strerror(errno));
	}

	void tomar()
	{

	}

	void liberar()
	{

	}
}

