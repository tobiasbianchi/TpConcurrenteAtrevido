#include <mesa.h>
#include <signal.h>
#include <HandlerSenial.h>
#include <iostream>
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

void Mesa::hacerEsperarFinTurno(Semaforo &turnoTermino){
	for (int j = 0; j < moderadorTurnos.size(); j++){
		turnoTermino.liberar();
	}
}

bool Mesa::hacerJugada(unsigned char carta, Semaforo &turnoTermino)
{
	bool repitioUltima = maso.invocar()->ponerCarta(carta);

	switch (carta){
		case 10:
			hacerEsperarFinTurno(turnoTermino);
			HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGNAL_10);
			break;
		case 11:
			hacerEsperarFinTurno(turnoTermino);
			HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGNAL_11);
			break;
		case 12:
			hacerEsperarFinTurno(turnoTermino);
			HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGNAL_12);
			break;
		case 7:
			hacerEsperarFinTurno(turnoTermino);
			HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGATREVIDO);
			break;
	}

	if (repitioUltima && ((int)carta != 7)){
		hacerEsperarFinTurno(turnoTermino);
		HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIG_REPETIDA);
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
