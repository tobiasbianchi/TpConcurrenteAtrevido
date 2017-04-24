#ifndef JUGADOR
#define JUGADOR

#include <objetocompartido.h>
#include <maso.h>
#include <mesa.h>
#include "DiezHandler.h"
#include "OnceHandler.h"
#include "DoceHandler.h"
#include "SieteHandler.h"

#define MAXIMOTIEMPOTURNO 2

#define RUTAJUGADOR "archivos/jugador"

class Jugador
{
private:
	unsigned char numeroJugador;
	DiezHandler diezHandler;
	OnceHandler onceHandler;
	DoceHandler doceHandler;
	SieteHandler sieteHandler;
	Maso maso;
	Mesa &mesa;
public:
	Jugador(unsigned char numeroJugador, Mesa &mesa);
	void pensar();
	void jugar();
};



#endif
