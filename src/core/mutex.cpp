#include "mutex.h"

Mutex::Mutex(int idProyecto) : Semaforo(idProyecto, 1)
{
}
