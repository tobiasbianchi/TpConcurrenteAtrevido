#ifndef MASO
#define MASO

#include <vector>
#include <mutex.h>
#include <iostream>

#define CARTASBARAJA 48

class Maso
{
private:
	struct arregloCartas
	{
		int cantidadCartas;
		int cartas[CARTASBARAJA];

		arregloCartas() : cantidadCartas(0)
		{
		}

		void ponerCarta(int carta)
		{
			cartas[cantidadCartas] = carta;
			
			if(cantidadCartas != CARTASBARAJA-1)
				cantidadCartas++;
		}

		int sacarCarta()
		{
			if(cantidadCartas)
			{
				cantidadCartas--;
				return cartas[cantidadCartas];
			}
			return 0;
		}

		int ultimaCarta(){
			if (cantidadCartas > 0){
				return cartas[cantidadCartas - 1];
			}
			return 0;
		}

		int contarCartas(){
			return cantidadCartas;
		}
	};

	struct arregloCartas cartas;
	Mutex mutex;
	int manosApoyadas = 0;
public:
	Maso(int idProyecto, const char *rutaArchivo = "/bin/bash");
	Maso(int idProyecto, std::vector<int> cartas, const char *rutaArchivo = "/bin/bash");
	bool ponerCarta(int carta);
	int sacarCarta();
	void mostrarCartas();
	void agregarCartas(std::vector<int> cartas);
	bool ponerMano( int cantidadJugadores);
	int contarCartas();
	std::vector<int> robarMaso();
	void destruir(){
		mutex.destruir();
	}
};


#endif
