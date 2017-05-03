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

// inicializa el semaforo en de id/archivo con el valor cantidad de recursos
Semaforo::Semaforo(int idProyecto, int cantidadRecursos, const char *rutaArchivo) : id(-1)
{
	obtenerSemaforo(idProyecto, rutaArchivo);

	union semun sem;
	sem.val = cantidadRecursos;
	if(semctl(id, 0, SETVAL, sem) == -1){
		Log::error("Configuracion del semaforo");
		throw Error("Configuracion del semaforo", strerror(errno));
	}
	Log::debug("Semaforo inicializado en " + std::to_string(cantidadRecursos));
};


//solo obtienene el semaforo, asegurarse de usarlo cuando ya se creo el semaforo
Semaforo::Semaforo(int idProyecto, const char* rutaArchivo){
	obtenerSemaforo(idProyecto, rutaArchivo);
	Log::debug("Semaforo obtenido ,valor actual es " + std::to_string(obtenerValor()));
}

void Semaforo::obtenerSemaforo(int idProyecto, const char* rutaArchivo){
	key_t clave = ftok(rutaArchivo, idProyecto);

	if(clave == -1){
		Log::error("Generacion de clave");
		throw Error("Generacion de clave", strerror(errno));
	}

	id = semget(clave, 1, IPC_CREAT | 0666);

	if(id == -1){
		Log::error("Obtencion del semaforo");
		throw Error("Obtencion del semaforo", strerror(errno));
	}
}

void Semaforo::tomar()
{
	struct sembuf operacion;

	operacion.sem_num = 0;
	operacion.sem_flg = 0;
	operacion.sem_op = -1;

	if(semop(id, &operacion, 1) == -1){
		throw Error("Adquisicion del semaforo", strerror(errno));
	}
};

void Semaforo::liberar()
{
	struct sembuf operacion;

	operacion.sem_num = 0;
	operacion.sem_flg = 0;
	operacion.sem_op = 1;

	if(semop(id, &operacion, 1) == -1){
		Log::error("Liberacion del semaforo");
		throw Error("Liberacion del semaforo", strerror(errno));
	}
};

void Semaforo::esperarACero()
{
	struct sembuf operacion;

	operacion.sem_num = 0;
	operacion.sem_flg = 0;
	operacion.sem_op = 0;

	if(semop(id, &operacion, 1) == -1){
		Log::error("Esperar a cero semaforo");
		throw Error("Esperar a cero semaforo", strerror(errno));
	}
};

int Semaforo::obtenerValor()
{
	 return(semctl(id, 0, GETVAL, 0));
}

void Semaforo::destruir()
{

	if(id != -1)
	{
		semctl(id, 0, IPC_RMID);
		id = -1;
		Log::debug("Semaforo destruido");
	}
}
