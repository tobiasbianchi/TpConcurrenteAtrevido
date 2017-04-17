#include "semaforo.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "excepciones.h"
#include <errno.h>
#include <string>
#include <string.h>
#include "definiciones.h"

Semaforo::Semaforo(int idProyecto, int cantidadRecursos, const char *rutaArchivo) : id(0)
{
	key_t clave = ftok(rutaArchivo, idProyecto);

	if(clave == -1)
		throw Error("Generacion de clave", strerror(errno));

	id = semget(clave, 1, IPC_CREAT | 0666);

	if(id == -1)
		throw Error("Creacion del semaforo", strerror(errno));

	union semun sem;
	sem.val = cantidadRecursos;

	if(semctl(id, 0, SETVAL, sem) == -1)
		throw Error("Configuracion del semaforo", strerror(errno));
};

void Semaforo::tomar()
{
	struct sembuf operacion;

	operacion.sem_num = 0;
	operacion.sem_flg = 0;
	operacion.sem_op = -1;

	if(semop(id, &operacion, 1) == -1)
		throw Error("Adquisicion del semaforo", strerror(errno));
};

void Semaforo::liberar()
{
	struct sembuf operacion;

	operacion.sem_num = 0;
	operacion.sem_flg = 0;
	operacion.sem_op = 1;

	if(semop(id, &operacion, 1) == -1)
		throw Error("Liberacion del semaforo", strerror(errno));
};

Semaforo::~Semaforo()
{
	if(id)	
		semctl(id, 0, IPC_RMID);
}
