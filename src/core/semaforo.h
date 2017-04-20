#ifndef SEMAFORO
#define SEMAFORO

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {  int val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };

class Semaforo
{
private:
	int id;
public:

	Semaforo(int idProyecto, int cantidadRecursos, const char* rutaArchivo = "/bin/bash");

	//No se puden copiar semaforos.
	Semaforo &operator=(const Semaforo &) = delete;

	void tomar();
	void liberar();
	int obtenerValor();
	~Semaforo();
};

#endif

