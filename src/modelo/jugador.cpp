#include <jugador.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <HandlerSenial.h>
#include <signal.h>
#include <iostream>
#include "jugador.h"

Jugador::Jugador(unsigned char numeroJugador, Mesa &mesa, Semaforo &inicio) : maso(numeroJugador, RUTAJUGADOR),
                                                                              numeroJugador(numeroJugador), mesa(mesa),
                                                                              inicio(inicio)
{
	HandlerSenial::getInstancia()->registrarHandler(SIGUSR1,&diezHandler);
	HandlerSenial::getInstancia()->registrarHandler(SIGUSR2,&onceHandler);
	HandlerSenial::getInstancia()->registrarHandler(SIGTTIN,&doceHandler);
	HandlerSenial::getInstancia()->registrarHandler(SIGCHLD,&sieteHandler);
    HandlerSenial::getInstancia()->registrarHandler(SIGINT,&quitHandler);
    inicio.tomar();
    inicio.esperarACero();
}

void Jugador::pensar()
{
	int srand(clock());
    int remaining_time = sleep(rand() % MAXIMOTIEMPOTURNO);
	while (remaining_time != 0 and remaining_time != -1){ //if interrupted in sleep, will wait whole time
        remaining_time = sleep(remaining_time);
    }
}

void Jugador::jugar()
{
	while(quitHandler.getGracefulQuit() == 0)
	{
        try{
            mesa.pedirTurno(numeroJugador);
            pensar();
            mesa.hacerJugada(numeroJugador);
            mesa.pasarTurno();
        }catch (Error e){
            if (errno != EINTR){
                throw e;
            }
        }

	}
}
