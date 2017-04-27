#include <mesa.h>
#include <signal.h>
#include <HandlerSenial.h>
#include <iostream>
#include "mesa.h"


Mesa::Mesa(unsigned char numeroPartida, unsigned char cantidadJugadores) : contador(numeroPartida), maso(idRecurso(), RUTAARCHIVOMESA, idRecurso(), RUTAARCHIVOMESA), turnoJugador(idRecurso(), RUTAARCHIVOMESA)
{
	//Como no se pueden copiar semaforos hay que reservar la memoria exacta antes o usar otra estructura contenedora.
	moderadorTurnos.reserve(cantidadJugadores);
	for(unsigned char i = 0; i<cantidadJugadores; i++)
		moderadorTurnos.emplace_back(idRecurso(), (i!=0) ? (0) : (1), RUTAARCHIVOMESA);
}

unsigned int Mesa::idRecurso()
{
	return contador++;
}

bool Mesa::pedirTurno(unsigned char numeroJugador)
{
	std::cout << "pidiendo turno" << std::endl;
	moderadorTurnos.at(numeroJugador-1).tomar();
	std::cout << "turno dado" << std::endl;
	*(turnoJugador.invocar()) = numeroJugador;
}

bool Mesa::hacerJugada(unsigned char carta)
{
	bool repitioUltima = maso.invocar()->ponerCarta(carta);
	switch (carta){
		case 10:
			HandlerSenial::getInstancia()->broadcastSignal(SIGUSR1);
			break;
		case 11:
			HandlerSenial::getInstancia()->broadcastSignal(SIGTTIN);
			break;
		case 12:
			HandlerSenial::getInstancia()->broadcastSignal(SIGUSR2);
			break;
		case 7:
			HandlerSenial::getInstancia()->broadcastSignal(SIGCHLD);
			HandlerSenial::getInstancia()->broadcastSignal(SIGTTOU);
			break;
	}

	if (repitioUltima && carta != 7){
		HandlerSenial::getInstancia()->broadcastSignal(SIGTTOU);
	}

	return true;
}

bool Mesa::pasarTurno()
{
	unsigned char numeroJugador = (*(turnoJugador.invocar()));

	if(numeroJugador < moderadorTurnos.size())
		moderadorTurnos.at(numeroJugador).liberar();
	else
		moderadorTurnos.at(0).liberar();
}

void Mesa::imprimir()
{
	maso.invocar()->mostrarCartas();		
}

bool Mesa::ponerMano() {
	return maso.invocar()->ponerMano(moderadorTurnos.size());
}

std::vector<unsigned char> Mesa::robarCartas(){
	return maso.invocar()->robarMaso();
}
