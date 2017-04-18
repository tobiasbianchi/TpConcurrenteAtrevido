#include <mutex.h>

Mutex::Mutex(int idProyecto, const char *rutaArchivo) : Semaforo(idProyecto, 1, rutaArchivo)
{
}
