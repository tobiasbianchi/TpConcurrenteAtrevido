#include <semaforo.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <excepciones.h>
#include <errno.h>
#include <string>
#include <string.h>
#include <definiciones.h>

#include <iostream>

Semaforo::Semaforo(int idProyecto, int cantidadRecursos, const char *rutaArchivo) : id(-1)
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

void Semaforo::esperarACero()
{
	struct sembuf operacion;

	operacion.sem_num = 0;
	operacion.sem_flg = 0;
	operacion.sem_op = 0;

	if(semop(id, &operacion, 1) == -1)
		throw Error("Esperar a cero semaforo", strerror(errno));
};

int Semaforo::obtenerValor()
{
	 return(semctl(id, 0, GETVAL, 0));
}

Semaforo::~Semaforo()
{

	if(id != -1)
	{
		semctl(id, 0, IPC_RMID);
		std::cout << "deleting semaforo id: " << id <<std::endl;
		id = -1;
	}
}
