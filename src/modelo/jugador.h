#ifndef JUGADOR
#define JUGADOR


#include <objetocompartido.h>
#include <maso.h>
#include <mesa.h>
#include <iostream>

#define RUTAJUGADOR "archivos/jugador"

class Jugador
{
private:
	unsigned char numeroJugador;
	ObjetoCompartido<Maso> maso;
	Mesa mesa;
	

public:
	Jugador(unsigned char numeroJugador, Mesa &mesa) : maso(numeroJugador, RUTAOBJETOCOMPARTIDO, numeroJugador, RUTAJUGADOR), numeroJugador(numeroJugador), mesa(mesa)
	{

	}

	void jugar()
	{
		while(mesa.hacerJugada(numeroJugador, numeroJugador))
		{
			std::cout << "Ya jugue!" << numeroJugador << std::endl;
			sleep(5);
		}
	}
};



#endif
