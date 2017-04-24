#include <jugador.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <HandlerSenial.h>
#include <signal.h>
#include <iostream>

Jugador::Jugador(unsigned char numeroJugador, Mesa &mesa) : maso(numeroJugador, RUTAJUGADOR), numeroJugador(numeroJugador), mesa(mesa)
{
	HandlerSenial::getInstancia()->registrarHandler(SIGUSR1,&diezHandler);
	HandlerSenial::getInstancia()->registrarHandler(SIGUSR2,&onceHandler);
	HandlerSenial::getInstancia()->registrarHandler(SIGTTIN,&doceHandler);
	HandlerSenial::getInstancia()->registrarHandler(SIGCHLD,&sieteHandler);
}

void Jugador::pensar()
{
	int srand(clock());
    int remaining_time = sleep(rand() % MAXIMOTIEMPOTURNO);
	while (remaining_time != 0){ //if interrupted in sleep, will wait whole time
        sleep(remaining_time);
    }
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
