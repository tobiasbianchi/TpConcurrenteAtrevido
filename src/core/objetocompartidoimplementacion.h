#include "excepciones.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
 #include <string.h>

template<typename T> template<typename ...Argumentos> ObjetoCompartido<T>::ObjetoCompartido(int idObjeto, const char* rutaArchivo, Argumentos... args) : id(0), memoria(NULL)
{
	bool existia = estabaCreado(idObjeto, rutaArchivo);

	key_t clave = ftok(rutaArchivo, idObjeto);

	if(clave == -1)
		throw Error("Generacion de clave", strerror(errno));

	id = shmget(clave, sizeof(T), IPC_CREAT | 0666);

	if(id == -1)
		throw Error("Creacion del segmento de memoria compartida", strerror(errno));

	void *memAux = shmat(id, NULL, 0);

	if(memAux == (void*)(-1))
		throw Error("Mapeo del memoria compartida", strerror(errno));

	if(!existia)
		memoria = new(memAux) T(args...);
	else
		memoria = static_cast<T*>(memAux);
}

template<typename T> bool ObjetoCompartido<T>::estabaCreado(int idObjeto, const char* rutaArchivo)
{
	key_t clave = ftok(rutaArchivo, idObjeto);

	if(clave == -1)
		throw Error("Generacion de clave", strerror(errno));

	id = shmget(clave, sizeof(T), IPC_CREAT | IPC_EXCL | 0666);

	if(id == -1)
		if(errno == EEXIST)
			return true;
		else
			throw Error("Creacion del segmento de memoria compartida", strerror(errno));

	shmctl(id, IPC_RMID, NULL);
	return false;
}

template<typename T> ObjetoCompartido<T>::~ObjetoCompartido()
{
	if(memoria)
	{
		//Agregar destruir objeto;
		shmdt(memoria);
		memoria = NULL;
	}

	if(id)
	{
		shmctl(id, IPC_RMID, NULL);
		id = 0;
	}
}

template<typename T> T* ObjetoCompartido<T>::invocar()
{
	return memoria;
}
