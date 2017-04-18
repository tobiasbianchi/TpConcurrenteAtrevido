#ifndef JUGADOR
#define JUGADOR


#include <objetocompartido.h>
#include <maso.h>
#include <mesa.h>

#define RUTAJUGADOR "archivos/jugador"

class Jugador
{
private:
	unsigned char numeroJugador;
	Maso maso;
	Mesa &mesa;
	

public:
	Jugador(unsigned char numeroJugador, Mesa &mesa) : maso(numeroJugador, RUTAJUGADOR), numeroJugador(numeroJugador), mesa(mesa)
	{

	}

	void jugar()
	{
		while(mesa.hacerJugada(numeroJugador, numeroJugador))
			sleep(1);
	}
};



#endif
