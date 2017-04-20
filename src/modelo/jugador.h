#ifndef JUGADOR
#define JUGADOR

#include <objetocompartido.h>
#include <maso.h>
#include <mesa.h>

#define MAXIMOTIEMPOTURNO 4

#define RUTAJUGADOR "archivos/jugador"

class Jugador
{
private:
	unsigned char numeroJugador;
	Maso maso;
	Mesa &mesa;
public:
	Jugador(unsigned char numeroJugador, Mesa &mesa);
	void pensar();
	void jugar();
};



#endif
