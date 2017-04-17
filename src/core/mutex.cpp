#include "mutex.h"

Mutex::Mutex(int idProyecto, bool iniciarBloqueado, const char *rutaArchivo) : Semaforo(idProyecto, 1, rutaArchivo)
{
	if(iniciarBloqueado)
		tomar();
}
