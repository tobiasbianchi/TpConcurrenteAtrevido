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
#include "../handlers/PonerManoHandler.h"
#include "../handlers/SieteHandler.h"
#include "../handlers/DoceHandler.h"
#include "../handlers/OnceHandler.h"
#include "../handlers/DiezHandler.h"

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
	PonerManoHandler ponerManoHandler;
    SIGINT_Handler quitHandler;
	Maso maso;
	Mesa &mesa;
    Semaforo &inicio;
	Semaforo &turnoTermino;
	void decir(std::string mensaje);
public:
	Jugador(unsigned char numeroJugador, Mesa &mesa, Semaforo &inicio, Semaforo &turnoTermino);
	void pensar();
	void jugar();
	static const std::string ATREVIDO;
	static const std::string BUENOSDIAS;
	static const std::string BUENASNOCHES;
	static const std::string VENIA;
};



#endif
