#ifndef MASO
#define MASO

#include <vector>
#include <mutex.h>
#include <iostream>

#define CARTASBARAJA 52

class Maso
{
private:
	struct arregloCartas
	{
		unsigned char cantidadCartas;
		unsigned char cartas[CARTASBARAJA];

		arregloCartas() : cantidadCartas(0)
		{
		}

		void ponerCarta(unsigned char carta)
		{
			cartas[cantidadCartas] = carta;
			
			if(cantidadCartas != CARTASBARAJA-1)
				cantidadCartas++;
		}

		unsigned char sacarCarta()
		{
			if(cantidadCartas)
			{
				cantidadCartas--;
				return cartas[cantidadCartas];
			}
			return 0;
		}

	};

	struct arregloCartas cartas;
	Mutex mutex;
public:
	Maso(int idProyecto, const char *rutaArchivo = "/bin/bash");
	void ponerCarta(unsigned char carta);
	unsigned char sacarCarta();
	
	void mostrarCartas()
	{
		mutex.tomar();

		for(int i=0;i<cartas.cantidadCartas;i++)
			std::cout << (int)cartas.cartas[i] << std::endl;
		
		mutex.liberar();
	}
};


#endif
