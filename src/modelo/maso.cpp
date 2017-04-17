#include <maso.h>
#include <vector>
#include <mutex.h>

Maso::Maso(int idProyecto, const char *rutaArchivo) : mutex(idProyecto, false, rutaArchivo)
{	
}

void Maso::ponerCarta(unsigned char carta)
{
	mutex.tomar();
	cartas.push_back(carta);
	mutex.liberar();
}

unsigned char Maso::sacarCarta()
{
	mutex.tomar();
	unsigned char cartaAux = cartas.back();
	cartas.pop_back();
	mutex.liberar();
	return cartaAux;
}
