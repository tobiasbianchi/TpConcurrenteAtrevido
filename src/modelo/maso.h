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

		unsigned char ultimaCarta(){
			if (cantidadCartas > 0){
				return cartas[cantidadCartas - 1];
			}
			return 0;
		}

		unsigned char contarCartas(){
			return cantidadCartas;
		}
	};

	struct arregloCartas cartas;
	Mutex mutex;
	int manosApoyadas = 0;
public:
	Maso(int idProyecto, const char *rutaArchivo = "/bin/bash");
	Maso(int idProyecto, std::vector<unsigned char> cartas, const char *rutaArchivo = "/bin/bash");
	bool ponerCarta(unsigned char carta);
	unsigned char sacarCarta();
	void mostrarCartas();
	void agregarCartas(std::vector<unsigned char> cartas);
	bool ponerMano( int cantidadJugadores);
	int contarCartas();
	std::vector<unsigned char> robarMaso();
	void destruir(){
		mutex.destruir();
	}
};


#endif
