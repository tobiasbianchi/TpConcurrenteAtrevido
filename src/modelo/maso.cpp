#include <maso.h>
#include <vector>
#include <mutex.h>

Maso::Maso(int idProyecto, const char *rutaArchivo) : mutex(idProyecto, rutaArchivo)
{	
}

void Maso::ponerCarta(unsigned char carta)
{
	mutex.tomar();

	cartas.ponerCarta(carta);

	mutex.liberar();
}

unsigned char Maso::sacarCarta()
{
	mutex.tomar();
	unsigned char cartaAux = cartas.sacarCarta();
	mutex.liberar();
	return cartaAux;
}

void Maso::mostrarCartas()
{
	mutex.tomar();

	for(int i=0;i<cartas.cantidadCartas;i++)
		std::cout << (int)cartas.cartas[i] << std::endl;
	
	mutex.liberar();
}
