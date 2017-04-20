#include <jugador.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

Jugador::Jugador(unsigned char numeroJugador, Mesa &mesa) : maso(numeroJugador, RUTAJUGADOR), numeroJugador(numeroJugador), mesa(mesa)
{

}

void Jugador::pensar()
{
	int srand(clock());
	sleep(rand() % MAXIMOTIEMPOTURNO);
}

void Jugador::jugar()
{
	while(mesa.pedirTurno(numeroJugador))
	{
		pensar();
		mesa.hacerJugada(numeroJugador);
		mesa.pasarTurno();			
	}
}
