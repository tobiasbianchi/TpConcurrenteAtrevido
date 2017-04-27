#ifndef JUGADOR
#define JUGADOR

#include <objetocompartido.h>
#include <maso.h>
#include <mesa.h>
#include "DiezHandler.h"
#include "OnceHandler.h"
#include "DoceHandler.h"
#include "SieteHandler.h"
#include "../core/semaforo.h"
#include "../handlers/SIGINT_Handler.h"

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
    SIGINT_Handler quitHandler;
	Maso maso;
	Mesa &mesa;
    Semaforo &inicio;
public:
	Jugador(unsigned char numeroJugador, Mesa &mesa, Semaforo &inicio);
	void pensar();
	void jugar();
};



#endif
