#include <mesa.h>
#include <signal.h>
#include <HandlerSenial.h>
#include <iostream>
#include "mesa.h"
#include "../core/HandlerSenial.h"


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
	moderadorTurnos.at(numeroJugador-1).tomar();
	*(turnoJugador.invocar()) = numeroJugador;
}

bool Mesa::hacerJugada(unsigned char carta, Semaforo &turnoTermino)
{
	bool repitioUltima = maso.invocar()->ponerCarta(carta);
	switch (carta){
		case 10:
			for (int j = 0; j < 5; j++){
				turnoTermino.liberar();
			}
			HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGNAL_10);
			break;
		case 11:
			for (int j = 0; j < 5; j++){
				turnoTermino.liberar();
			}
			HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGNAL_11);
			break;
		case 12:
			for (int j = 0; j < 5; j++){
				turnoTermino.liberar();
			}
			HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGNAL_12);
			break;
		case 7:
			for (int j = 0; j < 5; j++){
				turnoTermino.liberar();
			}
			HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGATREVIDO);
			HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIG_MANO);
			break;
	}

	if (repitioUltima && ((int)carta != 7)){
		for (int j = 0; j < 5; j++){
			turnoTermino.liberar();
		}
		HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIG_MANO);
	}
	imprimir();
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
